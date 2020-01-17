typedef struct zpl_mutex {
#if defined(ZPL_SYSTEM_WINDOWS)
    CRITICAL_SECTION win32_critical_section;
#else
    pthread_mutex_t pthread_mutex;
#endif
} zpl_mutex;

ZPL_DEF void     zpl_mutex_init    (zpl_mutex *m);
ZPL_DEF void     zpl_mutex_destroy (zpl_mutex *m);
ZPL_DEF void     zpl_mutex_lock    (zpl_mutex *m);
ZPL_DEF zpl_b32  zpl_mutex_try_lock(zpl_mutex *m);
ZPL_DEF void     zpl_mutex_unlock  (zpl_mutex *m);
