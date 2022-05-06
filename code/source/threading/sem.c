// file: source/threading/sem.c


ZPL_BEGIN_C_DECLS

void zpl_semaphore_release(zpl_semaphore *s) { zpl_semaphore_post(s, 1); }

#if defined(ZPL_SYSTEM_WINDOWS)

    void zpl_semaphore_init   (zpl_semaphore *s)            { s->win32_handle = CreateSemaphoreA(NULL, 0, ZPL_I32_MAX, NULL); }
    void zpl_semaphore_destroy(zpl_semaphore *s)            { CloseHandle(s->win32_handle); }
    void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { ReleaseSemaphore(s->win32_handle, count, NULL); }
    void zpl_semaphore_wait   (zpl_semaphore *s)            { WaitForSingleObject(s->win32_handle, INFINITE); }
    zpl_b32 zpl_semaphore_trywait(zpl_semaphore *s)         { int r = WaitForSingleObject(s->win32_handle, 0); return (r==0); }

#elif defined(ZPL_SYSTEM_OSX)

    void zpl_semaphore_init   (zpl_semaphore *s)            { semaphore_create(mach_task_self(), &s->osx_handle, SYNC_POLICY_FIFO, 0); }
    void zpl_semaphore_destroy(zpl_semaphore *s)            { semaphore_destroy(mach_task_self(), s->osx_handle); }
    void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) semaphore_signal(s->osx_handle); }
    void zpl_semaphore_wait   (zpl_semaphore *s)            { semaphore_wait(s->osx_handle); }
    zpl_b32 zpl_semaphore_trywait(zpl_semaphore *s)         { mach_timespec_t t; t.tv_sec = t.tv_nsec = 0; kern_return_t r = semaphore_timedwait(s->osx_handle, t); return (r==0); }

#elif defined(ZPL_SYSTEM_UNIX)

    void zpl_semaphore_init   (zpl_semaphore *s)            { sem_init(&s->unix_handle, 0, 0); }
    void zpl_semaphore_destroy(zpl_semaphore *s)            { sem_destroy(&s->unix_handle); }
    void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) sem_post(&s->unix_handle); }
    void zpl_semaphore_wait   (zpl_semaphore *s)            { int i; do { i = sem_wait(&s->unix_handle); } while (i == -1 && errno == EINTR); }
    zpl_b32 zpl_semaphore_trywait(zpl_semaphore *s)         { int r = sem_trywait(&s->unix_handle); return (r==0); }

#else
#    error Semaphores for this OS are not implemented
#endif

ZPL_END_C_DECLS
