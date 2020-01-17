#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#if defined(ZPL_SYSTEM_MACOS)
    #include <mach/thread_act.h>
#elif defined(ZPL_SYSTEM_UNIX)
    #include <semaphore.h>
#endif

#if defined(ZPL_SYSTEM_WINDOWS)
    typedef struct zpl_semaphore { void *win32_handle; }     zpl_semaphore;
#elif defined(ZPL_SYSTEM_MACOS)
    typedef struct zpl_semaphore { semaphore_t osx_handle; } zpl_semaphore;
#elif defined(ZPL_SYSTEM_UNIX)
    typedef struct zpl_semaphore { sem_t unix_handle; }      zpl_semaphore;
#else
    #error
#endif

ZPL_DEF void zpl_semaphore_init   (zpl_semaphore *s);
ZPL_DEF void zpl_semaphore_destroy(zpl_semaphore *s);
ZPL_DEF void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count);
ZPL_DEF void zpl_semaphore_release(zpl_semaphore *s); // NOTE: zpl_semaphore_post(s, 1)
ZPL_DEF void zpl_semaphore_wait   (zpl_semaphore *s);
