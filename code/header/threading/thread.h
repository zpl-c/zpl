// file: header/threading/thread.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#else
struct zpl_thread;
#endif

ZPL_BEGIN_C_DECLS

typedef zpl_isize (*zpl_thread_proc)(struct zpl_thread *thread);

typedef struct zpl_thread {
#if defined(ZPL_SYSTEM_WINDOWS)
    void *        win32_handle;
#else
    pthread_t     posix_handle;
#endif

    zpl_thread_proc  proc;
    void *           user_data;
    zpl_isize        user_index;
    zpl_isize        return_value;

    zpl_semaphore    semaphore;
    zpl_isize        stack_size;
    zpl_b32          is_running;
    zpl_b32          nowait;
} zpl_thread;

ZPL_DEF void     zpl_thread_init            (zpl_thread *t);
ZPL_DEF void     zpl_thread_destroy         (zpl_thread *t);
ZPL_DEF void     zpl_thread_start           (zpl_thread *t, zpl_thread_proc proc, void *data);
ZPL_DEF void     zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *data, zpl_isize stack_size);
ZPL_DEF void     zpl_thread_join            (zpl_thread *t);
ZPL_DEF zpl_b32  zpl_thread_is_running      (zpl_thread const *t);
ZPL_DEF zpl_u32  zpl_thread_current_id      (void);
ZPL_DEF void     zpl_thread_set_name        (zpl_thread *t, char const *name);

ZPL_END_C_DECLS
