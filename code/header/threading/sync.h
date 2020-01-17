// NOTE: Thread Merge Operation
// Based on Sean Barrett's stb_sync

typedef struct zpl_sync {
    zpl_i32 target;  // Target Number of threads
    zpl_i32 current; // Threads to hit
    zpl_i32 waiting; // Threads waiting

    zpl_mutex start;
    zpl_mutex mutex;
    zpl_semaphore release;
} zpl_sync;

ZPL_DEF void     zpl_sync_init          (zpl_sync *s);
ZPL_DEF void     zpl_sync_destroy       (zpl_sync *s);
ZPL_DEF void     zpl_sync_set_target    (zpl_sync *s, zpl_i32 count);
ZPL_DEF void     zpl_sync_release       (zpl_sync *s);
ZPL_DEF zpl_i32  zpl_sync_reach         (zpl_sync *s);
ZPL_DEF void     zpl_sync_reach_and_wait(zpl_sync *s);

