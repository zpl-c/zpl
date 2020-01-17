////////////////////////////////////////////////////////////////
//
// Coroutines
//
//

struct {
    zpl_b32 is_ready;
    zpl_thread_pool coroutines;
    zpl_thread runner;
    zpl_atomic32 request_term;
    zpl_mutex is_processing;
} zpl__co_internals;

zpl_thread_local zpl_u8 zpl__co_yield_barrier;

zpl_isize zpl__co_runner(struct zpl_thread *t) {
    do {
        if (zpl_atomic32_load(&zpl__co_internals.request_term))
            break;

        zpl_b32 lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

        while (!lock) {
            zpl_yield_thread();
            lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

            if (zpl_atomic32_load(&zpl__co_internals.request_term))
                break;

            zpl_mfence();
        }

        zpl_jobs_process(&zpl__co_internals.coroutines);
        zpl_mutex_unlock(&zpl__co_internals.is_processing);
    } while (1);

    return 0;
}

void zpl__co_job(void *data) {
    zpl_co *co = cast(zpl_co *)data;

    zpl_atomic32_store(&co->status, ZPL_CO_RUNNING);
    co->f(co);
    zpl_atomic32_store(&co->status, ZPL_CO_DEAD);
}

void zpl_co_init(zpl_allocator a, zpl_u32 max_threads) {
    if (!zpl__co_internals.is_ready) {
        zpl_zero_item(&zpl__co_internals);
        zpl_mutex_init(&zpl__co_internals.is_processing);
        zpl_jobs_init(&zpl__co_internals.coroutines, a, max_threads);
        zpl_thread_init(&zpl__co_internals.runner);
        zpl_thread_start(&zpl__co_internals.runner, zpl__co_runner, NULL);
        zpl_atomic32_store(&zpl__co_internals.request_term, 0);
        zpl__co_internals.is_ready = 1;

        // Set up a barrier so that we won't let user call zpl_co_yield in a main thread.
        zpl__co_yield_barrier = 1;
    }
}

void zpl_co_destroy(void) {
    zpl_atomic32_exchange(&zpl__co_internals.request_term, 1);
    zpl_thread_destroy(&zpl__co_internals.runner);
    zpl_mutex_destroy(&zpl__co_internals.is_processing);
    zpl_jobs_free(&zpl__co_internals.coroutines);
    zpl__co_internals.is_ready = 0;
    zpl_mfence();
}

void zpl_co_make(zpl_co *co, zpl_co_proc f) {
    ZPL_ASSERT_MSG(zpl__co_internals.is_ready, "Coroutines module is not initialized. Call zpl_co_init first!");
    ZPL_ASSERT_NOT_NULL(co);

    co->f = f;
    zpl_atomic32_store(&co->status, ZPL_CO_READY);
    zpl_atomic32_store(&co->resume, 0);
}

void zpl_co_resume(zpl_co *co, void *data) {
    ZPL_ASSERT_NOT_NULL(co);

    if (data != NULL) {
        zpl_atomic32_store(&co->push_arg, 1);
        co->data_stack[co->data_write_idx++] = data;
        zpl_atomic32_spin_unlock(&co->push_arg);
        zpl_mfence();
    }

    zpl_i32 status = zpl_atomic32_load(&co->status);

    // Initialize a job
    if (status == ZPL_CO_READY) {

        if (data)
            co->data = co->data_stack[co->data_read_idx++];

        zpl_atomic32_store(&co->status, ZPL_CO_ENQUEUED);
        zpl_mfence();

        zpl_mutex_lock(&zpl__co_internals.is_processing);
        zpl_jobs_enqueue(&zpl__co_internals.coroutines, zpl__co_job, cast(void *)co);
        zpl_mutex_unlock(&zpl__co_internals.is_processing);
    }
    else {
        zpl_atomic32_fetch_add(&co->resume, 1);
        zpl_mfence();
    }
}

void zpl_co_yield(zpl_co *co) {
    zpl_i32 value;
    ZPL_ASSERT_NOT_NULL(co);
    ZPL_ASSERT_MSG((!zpl__co_yield_barrier), "zpl_co_yield can only be called inside of coroutines!");

    zpl_atomic32_store(&co->status, ZPL_CO_WAITING);

    value = zpl_atomic32_load(&co->resume);

    while (value == 0) {
        zpl_yield_thread();
        value = zpl_atomic32_load(&co->resume);
        zpl_mfence();
    }

    zpl_atomic32_spin_lock(&co->push_arg, -1);
    co->data = co->data_stack[co->data_read_idx++];

    // null pointer is present, no arg is found, so return back by 1 index
    if (co->data == NULL) {
        co->data_read_idx--;
    }

    zpl_atomic32_spin_unlock(&co->push_arg);

    zpl_atomic32_store(&co->status, ZPL_CO_RUNNING);
    zpl_atomic32_fetch_add(&co->resume, -1);
}
