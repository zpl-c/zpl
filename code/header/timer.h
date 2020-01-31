// file: header/timer.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef void (*zpl_timer_cb)(void *data);

//! Timer data structure
typedef struct zpl_timer {
    zpl_timer_cb callback;
    zpl_b32 enabled;
    zpl_i32 remaining_calls;
    zpl_i32 initial_calls;
    zpl_f64 next_call_ts;
    zpl_f64 duration;
    void *user_data;
} zpl_timer;

typedef zpl_timer *zpl_timer_pool; ///< zpl_array

//! Initialize timer pool.
#define zpl_timer_init(pool, allocator) zpl_array_init(pool, allocator)

//! Add new timer to pool and return it.
ZPL_DEF zpl_timer *zpl_timer_add(zpl_timer_pool pool);

//! Perform timer pool update.

//! Traverse over all timers and update them accordingly. Should be called by Main Thread in a tight loop.
ZPL_DEF void zpl_timer_update(zpl_timer_pool pool);

//! Set up timer.

//! Set up timer with specific options.
//! @param timer
//! @param duration How long/often to fire a timer.
//! @param count How many times we fire a timer. Use -1 for infinity.
//! @param callback A method to execute once a timer triggers.
ZPL_DEF void zpl_timer_set(zpl_timer *timer, zpl_f64 /* microseconds */ duration, zpl_i32 /* -1 for INFINITY */ count,
                           zpl_timer_cb callback);

//! Start timer with specified delay.
ZPL_DEF void zpl_timer_start(zpl_timer *timer, zpl_f64 delay_start);

//! Stop timer and prevent it from triggering.
ZPL_DEF void zpl_timer_stop(zpl_timer *timer);

ZPL_END_C_DECLS
