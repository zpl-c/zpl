// file: source/timer.c

////////////////////////////////////////////////////////////////
//
// Timer
//
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

zpl_timer *zpl_timer_add(zpl_timer_pool pool) {
    ZPL_ASSERT(pool);

    zpl_timer t = { 0 };
    zpl_array_append(pool, t);
    return pool + (zpl_array_count(pool) - 1);
}

void zpl_timer_set(zpl_timer *t, zpl_f64 duration, zpl_i32 count, zpl_timer_cb cb) {
    ZPL_ASSERT(t);

    t->duration = duration;
    t->remaining_calls = t->initial_calls = count;
    t->callback = cb;
    t->enabled = false;
}

void zpl_timer_start(zpl_timer *t, zpl_f64 delay_start) {
    ZPL_ASSERT(t && !t->enabled);

    t->enabled = true;
    t->remaining_calls = t->initial_calls;
    t->next_call_ts = zpl_time_now( ) + delay_start;
}

void zpl_timer_stop(zpl_timer *t) {
    ZPL_ASSERT(t && t->enabled);

    t->enabled = false;
}

void zpl_timer_update(zpl_timer_pool pool) {
    ZPL_ASSERT(pool);

    zpl_f64 now = zpl_time_now( );

    for (zpl_isize i = 0; i < zpl_array_count(pool); ++i) {
        zpl_timer *t = pool + i;

        if (t->enabled) {
            if (t->remaining_calls > 0 || t->initial_calls == -1) {
                if (t->next_call_ts <= now) {
                    if (t->initial_calls != -1) { --t->remaining_calls; }

                    if (t->remaining_calls == 0) {
                        t->enabled = false;
                    } else {
                        t->next_call_ts = now + t->duration;
                    }

                    t->callback(t->user_data);
                }
            }
        }
    }
}

ZPL_END_C_DECLS
