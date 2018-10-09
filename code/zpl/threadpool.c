/** @file threadpool.c
@brief Job system
@defgroup jobs Job system

 This job system follows thread pool pattern to minimize the costs of thread initialization.
 It reuses fixed number of threads to process variable number of jobs.
 
 @{
 */


#ifdef ZPL_THREADING
#define ZPL_JOBS_PROC(name) void name(void *data)
typedef ZPL_JOBS_PROC(zpl_jobs_proc);

#define ZPL_INVALID_JOB U32_MAX

typedef enum {
    ZPL_JOBS_STATUS_READY,
    ZPL_JOBS_STATUS_BUSY,
    ZPL_JOBS_STATUS_WAITING,
    ZPL_JOBS_STATUS_TERM,
} zpl_jobs_status;

typedef struct {
    zpl_jobs_proc *proc;
    void *data;
    
    i32 priority;
} zpl_thread_job;

typedef struct {
    zpl_thread thread;
    zpl_atomic32 status;
    u32 jobid;
    void *pool;
} zpl_thread_worker;

typedef struct {
    zpl_allocator alloc;
    u32 max_threads;
    f32 job_spawn_treshold;
    zpl_mutex access;
    zpl_buffer(zpl_thread_worker) workers;
    zpl_array(zpl_thread_job) jobs;
    zpl_array(u32) queue;
    zpl_array(u32) available;
} zpl_thread_pool;

//! Initialize thread pool with specified amount of fixed threads.
ZPL_DEF void zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, u32 max_threads);

//! Release the resources use by thread pool.
ZPL_DEF void zpl_jobs_free(zpl_thread_pool *pool);

//! Enqueue a job with specified data.
ZPL_DEF void zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data);

//! Enqueue a job with specific priority with specified data.
ZPL_DEF void zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, i32 priority);

//! Process all jobs and check all threads. Should be called by Main Thread in a tight loop.
ZPL_DEF b32 zpl_jobs_process(zpl_thread_pool *pool);
#endif

//! @}
//$$

///////////////////////////////////////////////////////////////
//
// Thread Pool
//

#ifdef ZPL_THREADING

ZPL_THREAD_PROC(zpl__jobs_entry) {
    zpl_thread_worker *tw = (zpl_thread_worker *)thread->user_data;
    zpl_thread_pool *pool = (zpl_thread_pool *)tw->pool;
    
    for (;;) {
        u32 status = zpl_atomic32_load(&tw->status);
        
        switch (status) {
            case ZPL_JOBS_STATUS_READY: {
                zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_BUSY);
                
                zpl_mutex_lock(&pool->access);
                zpl_thread_job *job = pool->jobs + tw->jobid;
                zpl_mutex_unlock(&pool->access);
                
                job->proc(job->data);
                
                zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_WAITING);
            } break;
            
            case ZPL_JOBS_STATUS_WAITING: {
                zpl_yield( );
            } break;
            
            case ZPL_JOBS_STATUS_TERM: {
                return 0;
            } break;
        }
    }
    
    return 0;
}

void zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, u32 max_threads) {
    zpl_thread_pool pool_ = { 0 };
    *pool = pool_;
    zpl_mutex_init(&pool->access);
    
    pool->alloc = a;
    pool->max_threads = max_threads;
    
    // NOTE: Spawn a new job slot when number of available slots is below 25%
    // compared to the total number of slots.
    pool->job_spawn_treshold = 0.25;
    
    zpl_buffer_init(pool->workers, a, max_threads);
    zpl_array_init(pool->jobs, a);
    zpl_array_init(pool->queue, a);
    zpl_array_init(pool->available, a);
    
    for (usize i = 0; i < max_threads; ++i) {
        zpl_thread_worker worker_ = { 0 };
        zpl_thread_worker *tw = pool->workers + i;
        *tw = worker_;
        
        zpl_thread_init(&tw->thread);
        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_WAITING);
        tw->pool = pool;
        tw->jobid = ZPL_INVALID_JOB;
        zpl_thread_start(&tw->thread, zpl__jobs_entry, (void *)tw);
    }
}

void zpl_jobs_free(zpl_thread_pool *pool) {
    for (usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        
        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_TERM);
        zpl_thread_destroy(&tw->thread);
    }
    
    zpl_buffer_free(pool->workers, pool->alloc);
    zpl_array_free(pool->jobs);
    zpl_array_free(pool->queue);
    zpl_array_free(pool->available);
}

void zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, i32 priority) {
    ZPL_ASSERT_NOT_NULL(proc);
    f32 treshold = 0.0f;
    
    if (zpl_array_count(pool->queue) > 0) {
        treshold = (zpl_array_count(pool->available) / (f32)zpl_array_count(pool->jobs));
    }
    
    if (treshold <= pool->job_spawn_treshold) {
        zpl_thread_job job = { 0 };
        job.proc = proc;
        job.data = data;
        job.priority = priority;
        
        zpl_array_append(pool->jobs, job);
        u32 jobid = (u32)zpl_array_count(pool->jobs) - 1;
        zpl_array_append(pool->queue, jobid);
    } else {
        u32 jobid = zpl_array_back(pool->available);
        zpl_thread_job *jp = pool->jobs + jobid;
        zpl_array_pop(pool->available);
        
        jp->proc = proc;
        jp->data = data;
        jp->priority = priority;
        
        zpl_array_append(pool->queue, jobid);
    }
}
void zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data) {
    ZPL_ASSERT_NOT_NULL(proc);
    zpl_jobs_enqueue_with_priority(pool, proc, data, 0);
}

zpl_thread_local zpl_thread_pool *zpl__thread_pool;
ZPL_COMPARE_PROC(zpl___jobs_cmp) {
    zpl_thread_job *p = (zpl_thread_job *)(zpl__thread_pool->jobs + *(u32 *)a);
    zpl_thread_job *q = (zpl_thread_job *)(zpl__thread_pool->jobs + *(u32 *)b);
    return p->priority < q->priority ? 1 : p->priority > q->priority;
}

ZPL_COMPARE_PROC_PTR(zpl__jobs_cmp(zpl_thread_pool *pool)) {
    zpl__thread_pool = pool;
    return &zpl___jobs_cmp;
}

b32 zpl_jobs_process(zpl_thread_pool *pool) {
    // NOTE: Sort the queue based on the job priority
    if (zpl_array_count(pool->queue)) {
        zpl_sort_array(pool->queue, zpl_array_count(pool->queue), zpl__jobs_cmp(pool));
    }
    
    // NOTE: Process the jobs
    for (usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        if (zpl_array_count(pool->queue) == 0) return false;
        
        u32 status = zpl_atomic32_load(&tw->status);
        
        if (status == ZPL_JOBS_STATUS_WAITING) {
            if (tw->jobid != ZPL_INVALID_JOB) { zpl_array_append(pool->available, tw->jobid); }
            
            u32 jobid = *pool->queue;
            zpl_array_remove_at(pool->queue, 0);
            tw->jobid = jobid;
            zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_READY);
        }
    }
    
    return true;
}

#endif // ZPL_THREADING
