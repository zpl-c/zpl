// file: source/timer.c

////////////////////////////////////////////////////////////////
//
// Timer
//
//

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
    t->next_call_ts = zpl_time_rel( ) + delay_start;
}

void zpl_timer_stop(zpl_timer *t) {
    ZPL_ASSERT(t && t->enabled);

    t->enabled = false;
}

void zpl_timer_update(zpl_timer *timer) {
    zpl_f64 now = zpl_time_rel();
    if (timer->enabled) {
        if (timer->remaining_calls > 0 || timer->initial_calls == -1) {
            if (timer->next_call_ts <= now) {
                if (timer->initial_calls != -1) { --timer->remaining_calls; }

                if (timer->remaining_calls == 0) {
                    timer->enabled = false;
                } else {
                    timer->next_call_ts = now + timer->duration;
                }

                timer->callback(timer->user_data);
            }
        }
    }
}

void zpl_timer_update_array(zpl_timer_pool pool) {
    ZPL_ASSERT(pool);

    for (zpl_isize i = 0; i < zpl_array_count(pool); ++i) {
        zpl_timer *t = pool + i;

        zpl_timer_update(t);
    }
}

ZPL_END_C_DECLS
