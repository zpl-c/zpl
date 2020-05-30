// file: source/jobs.c

///////////////////////////////////////////////////////////////
//
// Thread Pool
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

zpl_isize zpl__jobs_entry(struct zpl_thread *thread) {
    zpl_thread_worker *tw = (zpl_thread_worker *)thread->user_data;
    zpl_thread_pool *pool = (zpl_thread_pool *)tw->pool;

    for (;;) {
        zpl_u32 status = zpl_atomic32_load(&tw->status);

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

void zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads) {
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

    for (zpl_usize i = 0; i < max_threads; ++i) {
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
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;

        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_TERM);
        zpl_thread_destroy(&tw->thread);
    }

    zpl_buffer_free(pool->workers, pool->alloc);
    zpl_array_free(pool->jobs);
    zpl_array_free(pool->queue);
    zpl_array_free(pool->available);
}

void zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_i32 priority) {
    ZPL_ASSERT_NOT_NULL(proc);
    zpl_f32 treshold = 0.0f;

    if (zpl_array_count(pool->queue) > 0) {
        treshold = (zpl_array_count(pool->available) / (zpl_f32)zpl_array_count(pool->jobs));
    }

    if (treshold <= pool->job_spawn_treshold) {
        zpl_thread_job job = { 0 };
        job.proc = proc;
        job.data = data;
        job.priority = priority;

        zpl_array_append(pool->jobs, job);
        zpl_u32 jobid = (zpl_u32)zpl_array_count(pool->jobs) - 1;
        zpl_array_append(pool->queue, jobid);
    } else {
        zpl_u32 jobid = zpl_array_back(pool->available);
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
    zpl_jobs_enqueue_with_priority(pool, proc, data, 1);
}

zpl_thread_local zpl_thread_pool *zpl__thread_pool;

ZPL_COMPARE_PROC(zpl___jobs_cmp) {
    zpl_thread_job *p = (zpl_thread_job *)(zpl__thread_pool->jobs + *(zpl_u32 *)a);
    zpl_thread_job *q = (zpl_thread_job *)(zpl__thread_pool->jobs + *(zpl_u32 *)b);
    return p->priority < q->priority ? 1 : p->priority > q->priority;
}

ZPL_COMPARE_PROC_PTR(zpl__jobs_cmp(zpl_thread_pool *pool)) {
    zpl__thread_pool = pool;
    return &zpl___jobs_cmp;
}

zpl_b32 zpl_jobs_process(zpl_thread_pool *pool) {
    // NOTE: Sort the queue based on the job priority
    if (zpl_array_count(pool->queue)) {
        zpl_sort_array(pool->queue, zpl_array_count(pool->queue), zpl__jobs_cmp(pool));
    }

    // NOTE: Process the jobs
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        if (zpl_array_count(pool->queue) == 0) return false;

        zpl_u32 status = zpl_atomic32_load(&tw->status);

        if (status == ZPL_JOBS_STATUS_WAITING) {
            if (tw->jobid != ZPL_INVALID_JOB) { zpl_array_append(pool->available, tw->jobid); }

            zpl_u32 jobid = *pool->queue;
            zpl_array_remove_at(pool->queue, 0);
            tw->jobid = jobid;
            zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_READY);
        }
    }

    return true;
}

ZPL_END_C_DECLS
