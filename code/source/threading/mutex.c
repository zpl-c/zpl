// file: source/threading/mutex.c


ZPL_BEGIN_C_DECLS

zpl_b32 zpl_mutex_init(zpl_mutex *m) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        InitializeCriticalSection((CRITICAL_SECTION*)m->win32_critical_section);
        return 1;
#    else
        return pthread_mutex_init(&m->pthread_mutex, NULL);
#    endif
}

zpl_b32 zpl_mutex_destroy(zpl_mutex *m) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        DeleteCriticalSection((CRITICAL_SECTION*)m->win32_critical_section);
        return 1;
#    else
        return pthread_mutex_destroy(&m->pthread_mutex);
#    endif
}

void zpl_mutex_lock(zpl_mutex *m) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        EnterCriticalSection((CRITICAL_SECTION*)m->win32_critical_section);
#    else
        pthread_mutex_lock(&m->pthread_mutex);
#    endif
}

zpl_b32 zpl_mutex_try_lock(zpl_mutex *m) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        return TryEnterCriticalSection((CRITICAL_SECTION*)m->win32_critical_section);
#    else
        return pthread_mutex_trylock(&m->pthread_mutex);
#    endif
}

void zpl_mutex_unlock(zpl_mutex *m) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        LeaveCriticalSection((CRITICAL_SECTION*)m->win32_critical_section);
#    else
        pthread_mutex_unlock(&m->pthread_mutex);
#    endif
}

ZPL_END_C_DECLS
