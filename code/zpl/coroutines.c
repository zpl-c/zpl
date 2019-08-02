/** @file coroutines.c
@brief Coroutines module
@defgroup misc Coroutines module

 This module implements co-routines feature for C99.
 
 @{
 */
/*
   See test/coroutines.c for an example usage
 */

#if ZPL_THREADING

#ifndef ZPL_CO_ARG_STACK_CAPACITY
#define ZPL_CO_ARG_STACK_CAPACITY 128
#endif

typedef enum {
    ZPL_CO_READY,
    ZPL_CO_ENQUEUED,
    ZPL_CO_RUNNING,
    ZPL_CO_WAITING,
    ZPL_CO_DEAD,
} zpl_co_status;

struct zpl_co;

typedef void (*zpl_co_proc)(struct zpl_co *co);

typedef struct zpl_co {
    zpl_atomic32  status;
    zpl_co_proc   f;
    void         *data; // overwritten internally, use inside of co-routines
    void         *data_stack[ZPL_CO_ARG_STACK_CAPACITY];
    zpl_i32       data_read_idx, data_write_idx;
    zpl_atomic32  resume, push_arg;
} zpl_co;

// These methods are used to initialize the co-routine subsystem
ZPL_DEF void   zpl_co_init(zpl_allocator a, zpl_u32 max_threads);
ZPL_DEF void   zpl_co_destroy(void);

// These methods are used by the host to create and run/resume co-routines
// Make sure the co-routine subsystem is initialized first!
ZPL_DEF zpl_co  zpl_co_make(zpl_co_proc f);
ZPL_DEF void    zpl_co_resume(zpl_co *co, void *data);
ZPL_DEF zpl_b32 zpl_co_running(zpl_co *co);
ZPL_DEF zpl_b32 zpl_co_finished(zpl_co *co);
ZPL_DEF zpl_b32 zpl_co_waiting(zpl_co *co);

// This method is used by the co-routine to await execution
ZPL_DEF void   zpl_co_yield(zpl_co *co);

#endif

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Coroutines
//
//

#if ZPL_THREADING

struct {
    zpl_b32 is_ready;
    zpl_thread_pool coroutines;
    zpl_thread runner;
    zpl_atomic32 request_term;
    zpl_mutex is_processing;
} zpl__co_internals = {0};

zpl_isize zpl__co_runner(struct zpl_thread *t) {
    do {
        zpl_b32 lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

        if (zpl_atomic32_load(&zpl__co_internals.request_term))
            break;

        while (!lock) {
            zpl_yield_thread();
            lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

            if (zpl_atomic32_load(&zpl__co_internals.request_term))
                break;

            zpl_mfence();
        }

        zpl_jobs_process(&zpl__co_internals.coroutines);
        zpl_mutex_unlock(&zpl__co_internals.is_processing);
    } while (!zpl_atomic32_load(&zpl__co_internals.request_term));

    return 0;
}

void zpl__co_job(void *data) {
    zpl_co *co = cast(zpl_co *)data;

    zpl_atomic32_store(&co->status, ZPL_CO_RUNNING);
    co->f(co);
    zpl_atomic32_store(&co->status, ZPL_CO_DEAD);
}

zpl_inline void zpl_co_init(zpl_allocator a, zpl_u32 max_threads) {
    if (!zpl__co_internals.is_ready) {
        zpl_mutex_init(&zpl__co_internals.is_processing);
        zpl_jobs_init(&zpl__co_internals.coroutines, a, max_threads);
        zpl_thread_init(&zpl__co_internals.runner);
        zpl_thread_start(&zpl__co_internals.runner, zpl__co_runner, NULL);
        zpl_atomic32_store(&zpl__co_internals.request_term, 0);
        zpl__co_internals.is_ready = 1;
    }
}

zpl_inline void zpl_co_destroy(void) {
    zpl_atomic32_exchange(&zpl__co_internals.request_term, 1);
    zpl_thread_destroy(&zpl__co_internals.runner);
    zpl_mutex_destroy(&zpl__co_internals.is_processing);
    zpl_jobs_free(&zpl__co_internals.coroutines);
    zpl_mfence();
}

zpl_inline zpl_co zpl_co_make(zpl_co_proc f) {
    ZPL_ASSERT_MSG(zpl__co_internals.is_ready, "Coroutines module is not initialized. Call zpl_co_init first!");
    zpl_co co = {0};

    co.f = f;
    zpl_atomic32_store(&co.status, ZPL_CO_READY);
    zpl_atomic32_store(&co.resume, 0);

    return co;
}

zpl_inline void zpl_co_resume(zpl_co *co, void *data) {
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

zpl_inline void zpl_co_yield(zpl_co *co) {
    zpl_i32 value;
    ZPL_ASSERT_NOT_NULL(co);

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

zpl_inline zpl_b32 zpl_co_running(zpl_co *co) {
    return zpl_atomic32_load(&co->status) == ZPL_CO_RUNNING;
}

zpl_inline zpl_b32 zpl_co_finished(zpl_co *co) {
    return zpl_atomic32_load(&co->status) == ZPL_CO_DEAD;
}

zpl_inline zpl_b32 zpl_co_waiting(zpl_co *co) {
    return zpl_atomic32_load(&co->resume) == 0;
}

#endif
