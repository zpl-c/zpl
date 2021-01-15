// file: source/jobs.c

///////////////////////////////////////////////////////////////
//
// Thread Pool
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

ZPL_RING_DEFINE(zpl__jobs_ring_, zpl_thread_job);

zpl_isize zpl__jobs_entry(struct zpl_thread *thread) {
    zpl_thread_worker *tw = (zpl_thread_worker *)thread->user_data;

    for (;;) {
        zpl_u32 status = zpl_atomic32_load(&tw->status);

        switch (status) {
            case ZPL_JOBS_STATUS_READY: {
                zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_BUSY);
                tw->job.proc(tw->job.data);
                zpl_atomic32_compare_exchange(&tw->status, ZPL_JOBS_STATUS_BUSY, ZPL_JOBS_STATUS_WAITING);
            } break;

            case ZPL_JOBS_STATUS_WAITING: {
                zpl_yield();
            } break;

            case ZPL_JOBS_STATUS_TERM: {
                return 0;
            } break;
        }
    }

    return 0;
}

void zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads) {
    zpl_jobs_init_with_limit(pool, a, max_threads, ZPL_JOBS_MAX_QUEUE);
}

void zpl_jobs_init_with_limit(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads, zpl_u32 max_jobs) {
    zpl_thread_pool pool_ = { 0 };
    *pool = pool_;

    pool->alloc = a;
    pool->max_threads = max_threads;
    pool->max_jobs = max_jobs;

    zpl_buffer_init(pool->workers, a, max_threads);
    zpl__jobs_ring_init(&pool->jobs, a, max_jobs);

    for (zpl_usize i = 0; i < max_threads; ++i) {
        zpl_thread_worker worker_ = { 0 };
        zpl_thread_worker *tw = pool->workers + i;
        *tw = worker_;

        zpl_thread_init(&tw->thread);
        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_WAITING);
        zpl_thread_start(&tw->thread, zpl__jobs_entry, (void *)tw);
    }
}

void zpl_jobs_free(zpl_thread_pool *pool) {
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;

        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_TERM);
        zpl_thread_destroy(&tw->thread);
    }

    zpl_buffer_free(pool->workers);
    zpl__jobs_ring_free(&pool->jobs);
}

void zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data) {
    ZPL_ASSERT_NOT_NULL(proc);
    zpl_thread_job job = {0};
    job.proc = proc;
    job.data = data;
    zpl__jobs_ring_append(&pool->jobs, job);
}

zpl_b32 zpl_jobs_empty(zpl_thread_pool *pool) {
    return zpl__jobs_ring_empty(&pool->jobs);
}

zpl_b32 zpl_jobs_done(zpl_thread_pool *pool) {
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        if (zpl_atomic32_load(&tw->status) != ZPL_JOBS_STATUS_WAITING) {
            return false;
        }
    }

    return true;
}

zpl_b32 zpl_jobs_process(zpl_thread_pool *pool) {
    if (zpl_jobs_empty(pool)) {
        return false;
    }
    // NOTE: Process the jobs
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        zpl_u32 status = zpl_atomic32_load(&tw->status);

        if (status == ZPL_JOBS_STATUS_WAITING && (!zpl_jobs_empty(pool))) {
            tw->job = *zpl__jobs_ring_get(&pool->jobs);
            zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_READY);
        }
    }

    return true;
}

ZPL_END_C_DECLS
