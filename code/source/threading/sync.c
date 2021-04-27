// file: source/threading/sync.c


ZPL_BEGIN_C_DECLS

void zpl_sync_init(zpl_sync *s) {
    zpl_zero_item(s);
    zpl_mutex_init(&s->mutex);
    zpl_mutex_init(&s->start);
    zpl_semaphore_init(&s->release);
}

void zpl_sync_destroy(zpl_sync *s) {
    if (s->waiting) {
        ZPL_PANIC("Cannot destroy while threads are waiting!");
    }

    zpl_mutex_destroy(&s->mutex);
    zpl_mutex_destroy(&s->start);
    zpl_semaphore_destroy(&s->release);
}

void zpl_sync_set_target(zpl_sync *s, zpl_i32 count) {
    zpl_mutex_lock(&s->start);

    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->target == 0);
    s->target = count;
    s->current = 0;
    s->waiting = 0;
    zpl_mutex_unlock(&s->mutex);
}

void zpl_sync_release(zpl_sync *s) {
    if (s->waiting) {
        zpl_semaphore_release(&s->release);
    } else {
        s->target = 0;
        zpl_mutex_unlock(&s->start);
    }
}

zpl_i32 zpl_sync_reach(zpl_sync *s) {
    zpl_i32 n;
    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->current < s->target);
    n = ++s->current; // NOTE: Record this value to avoid possible race if `return s->current` was done
    if (s->current == s->target)
        zpl_sync_release(s);
    zpl_mutex_unlock(&s->mutex);
    return n;
}

void zpl_sync_reach_and_wait(zpl_sync *s) {
    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->current < s->target);
    s->current++;
    if (s->current == s->target) {
        zpl_sync_release(s);
        zpl_mutex_unlock(&s->mutex);
    } else {
        s->waiting++;                   // NOTE: Waiting, so one more waiter
        zpl_mutex_unlock(&s->mutex);     // NOTE: Release the mutex to other threads
        zpl_semaphore_wait(&s->release); // NOTE: Wait for merge completion
        zpl_mutex_lock(&s->mutex);       // NOTE: On merge completion, lock mutex
        s->waiting--;                   // NOTE: Done waiting
        zpl_sync_release(s);             // NOTE: Restart the next waiter
        zpl_mutex_unlock(&s->mutex);
    }
}

ZPL_END_C_DECLS
