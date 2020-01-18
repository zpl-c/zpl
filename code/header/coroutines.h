/** @file coroutines.c
@brief Coroutines module
@defgroup misc Coroutines module

 This module implements co-routines feature for C99.

 @{
 */
/*
   See test/coroutines.c for an example usage
 */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

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

/**
 * Initializes the coroutines subsystem
 * @param  a           Memory allocator to be used
 * @param  max_threads Maximum amount of threads to use for coroutines execution
 */
ZPL_DEF void   zpl_co_init(zpl_allocator a, zpl_u32 max_threads);

/**
 * Destroys the coroutines subsystem
 *
 * IMPORTANT: This is a blocking method that waits until all the coroutines are finished.
 * Please, make sure your coroutines are correctly designed, so that you
 * won't end up in an infinite loop.
 */
ZPL_DEF void   zpl_co_destroy(void);

// These methods are used by the host to create and run/resume co-routines
// Make sure the co-routine subsystem is initialized first!

/**
 * Create a paused coroutine
 * @param  co Coroutine reference
 * @param  f  Coroutine method
 */
ZPL_DEF void zpl_co_make(zpl_co *co, zpl_co_proc f);

/**
 * Starts/Resumes a coroutine execution.
 *
 * IMPORTANT: Data you pass is stored in a stack of up to ZPL_CO_ARG_STACK_CAPACITY.
 * This means that you can cause stack corruption if you
 * call 'zpl_co_resume' with data passed (ZPL_CO_ARG_STACK_CAPACITY+1) times.
 * Raise the number by defining ZPL_CO_ARG_STACK_CAPACITY if required.
 *
 * @param  co   Coroutine
 * @param  data Data we want to pass (or NULL)
 */
ZPL_DEF void    zpl_co_resume(zpl_co *co, void *data);

/**
 * Is a coroutine running at the moment?
 * @param  co Coroutine
 * @return
 */
ZPL_DEF_INLINE zpl_b32 zpl_co_running(zpl_co *co);

/**
 * Is a coroutine already finished?
 * @param  co Coroutine
 * @return
 */
ZPL_DEF_INLINE zpl_b32 zpl_co_finished(zpl_co *co);

/**
 * Is coroutine waiting? (in yield state)
 * @param  co Coroutine
 * @return
 */
ZPL_DEF_INLINE zpl_b32 zpl_co_waiting(zpl_co *co);

// This method is used by the co-routine to await execution
//

/**
 * Yield the coroutine.
 *
 * IMPORTANT: Only to be used by the coroutine!!
 * @param  co Coroutine
 */
ZPL_DEF void   zpl_co_yield(zpl_co *co);

//! @}

ZPL_IMPL_INLINE zpl_b32 zpl_co_running(zpl_co *co) {
    return zpl_atomic32_load(&co->status) == ZPL_CO_RUNNING;
}

ZPL_IMPL_INLINE zpl_b32 zpl_co_finished(zpl_co *co) {
    return zpl_atomic32_load(&co->status) == ZPL_CO_DEAD;
}

ZPL_IMPL_INLINE zpl_b32 zpl_co_waiting(zpl_co *co) {
    return zpl_atomic32_load(&co->resume) == 0;
}
