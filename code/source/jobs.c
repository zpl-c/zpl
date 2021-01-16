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
    pool->counter = 0;

    zpl_buffer_init(pool->workers, a, max_threads);

    for (zpl_usize i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        zpl_thread_queue *q = &pool->queues[i];
        zpl__jobs_ring_init(&q->jobs, a, max_jobs);
        q->chance = ((i+1) << 2)/2;
    }

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

    for (zpl_usize i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        zpl_thread_queue *q = &pool->queues[i];
        zpl__jobs_ring_free(&q->jobs);
    }
}

zpl_b32 zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_jobs_priority priority) {
    ZPL_ASSERT_NOT_NULL(proc);
    ZPL_ASSERT(priority >= 0 && priority < ZPL_JOBS_MAX_PRIORITIES);
    zpl_thread_job job = {0};
    job.proc = proc;
    job.data = data;

    if (!zpl_jobs_full(pool, priority)) {
        zpl__jobs_ring_append(&pool->queues[priority].jobs, job);
        return true;
    }
    return false;
}

zpl_b32 zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data) {
    return zpl_jobs_enqueue_with_priority(pool, proc, data, ZPL_JOBS_PRIORITY_NORMAL);
}

zpl_b32 zpl_jobs_empty(zpl_thread_pool *pool, zpl_jobs_priority priority) {
    return zpl__jobs_ring_empty(&pool->queues[priority].jobs);
}

zpl_b32 zpl_jobs_full(zpl_thread_pool *pool, zpl_jobs_priority priority) {
    return zpl__jobs_ring_full(&pool->queues[priority].jobs);
}

zpl_b32 zpl_jobs_done(zpl_thread_pool *pool) {
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        if (zpl_atomic32_load(&tw->status) != ZPL_JOBS_STATUS_WAITING) {
            return false;
        }
    }

    return zpl_jobs_empty_all(pool);
}

zpl_b32 zpl_jobs_empty_all(zpl_thread_pool *pool) {
    for (zpl_usize i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        if (!zpl_jobs_empty(pool, i)) {
            return false;
        }
    }
    return true;
}

zpl_b32 zpl_jobs_full_all(zpl_thread_pool *pool) {
    for (zpl_usize i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        if (!zpl_jobs_full(pool, i)) {
            return false;
        }
    }
    return true;
}

zpl_b32 zpl_jobs_process(zpl_thread_pool *pool) {
    if (zpl_jobs_empty_all(pool)) {
        return false;
    }
    // NOTE: Process the jobs
    for (zpl_usize i = 0; i < pool->max_threads; ++i) {
        zpl_thread_worker *tw = pool->workers + i;
        zpl_u32 status = zpl_atomic32_load(&tw->status);
        zpl_b32 last_empty = false;

        if (status == ZPL_JOBS_STATUS_WAITING) {
            for (zpl_usize i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
                zpl_thread_queue *q = &pool->queues[i];
                if (zpl_jobs_empty(pool, i)) {
                    last_empty = true;
                    continue;
                }
                if (!last_empty && (pool->counter++ % q->chance) != 0) {
                    continue;
                }

                last_empty = false;
                tw->job = *zpl__jobs_ring_get(&q->jobs);
                zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_READY);
                break;
            }
        }
    }

    return true;
}

ZPL_END_C_DECLS
