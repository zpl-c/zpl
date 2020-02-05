// file: header/threading/affinity.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#if defined(ZPL_SYSTEM_WINDOWS) || defined (ZPL_SYSTEM_CYGWIN)

    typedef struct zpl_affinity {
        zpl_b32   is_accurate;
        zpl_isize core_count;
        zpl_isize thread_count;

    #define ZPL_WIN32_MAX_THREADS (8 * zpl_size_of(zpl_usize))
        zpl_usize core_masks[ZPL_WIN32_MAX_THREADS];
    } zpl_affinity;

#elif defined(ZPL_SYSTEM_OSX)

    typedef struct zpl_affinity {
        zpl_b32   is_accurate;
        zpl_isize core_count;
        zpl_isize thread_count;
        zpl_isize threads_per_core;
    } zpl_affinity;

#elif defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_FREEBSD) || defined(ZPL_SYSTEM_EMSCRIPTEN) || defined(ZPL_SYSTEM_OPENBSD)

    typedef struct zpl_affinity {
        zpl_b32   is_accurate;
        zpl_isize core_count;
        zpl_isize thread_count;
        zpl_isize threads_per_core;
    } zpl_affinity;

#else
    #error TODO: Unknown system
#endif

ZPL_DEF void      zpl_affinity_init   (zpl_affinity *a);
ZPL_DEF void      zpl_affinity_destroy(zpl_affinity *a);
ZPL_DEF zpl_b32   zpl_affinity_set    (zpl_affinity *a, zpl_isize core, zpl_isize thread);
ZPL_DEF zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core);

ZPL_END_C_DECLS
