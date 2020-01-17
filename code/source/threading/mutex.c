void zpl_mutex_init(zpl_mutex *m) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        InitializeCriticalSection(&m->win32_critical_section);
    #else
        pthread_mutex_init(&m->pthread_mutex, NULL);
    #endif
}

void zpl_mutex_destroy(zpl_mutex *m) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        DeleteCriticalSection(&m->win32_critical_section);
    #else
        pthread_mutex_destroy(&m->pthread_mutex);
    #endif
}

void zpl_mutex_lock(zpl_mutex *m) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        EnterCriticalSection(&m->win32_critical_section);
    #else
        pthread_mutex_lock(&m->pthread_mutex);
    #endif
}

zpl_b32 zpl_mutex_try_lock(zpl_mutex *m) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        return TryEnterCriticalSection(&m->win32_critical_section);
    #else
        return pthread_mutex_trylock(&m->pthread_mutex);
    #endif
}

void zpl_mutex_unlock(zpl_mutex *m) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        LeaveCriticalSection(&m->win32_critical_section);
    #else
        pthread_mutex_unlock(&m->pthread_mutex);
    #endif
}
