#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

zpl_b32 zpl_thread_is_running(zpl_thread const *t) { return t->is_running != 0; }

void zpl_thread_init(zpl_thread *t) {
    zpl_zero_item(t);

    #if defined(ZPL_SYSTEM_WINDOWS)
        t->win32_handle = INVALID_HANDLE_VALUE;
    #else
        t->posix_handle = 0;
    #endif

    zpl_semaphore_init(&t->semaphore);
}

void zpl_thread_destroy(zpl_thread *t) {
    if (t->is_running) zpl_thread_join(t);
    zpl_semaphore_destroy(&t->semaphore);
}

void zpl__thread_run(zpl_thread *t) {
    zpl_semaphore_release(&t->semaphore);
    t->return_value = t->proc(t);
}

#if defined(ZPL_SYSTEM_WINDOWS)
    DWORD __stdcall zpl__thread_proc(void *arg) {
        zpl_thread *t = cast(zpl_thread *)arg;
        zpl__thread_run(t);
        t->is_running = false;
        return 0;
    }
#else
    void *zpl__thread_proc(void *arg) {
        zpl_thread *t = cast(zpl_thread *)arg;
        zpl__thread_run(t);
        t->is_running = false;
        return NULL;
    }
#endif

void zpl_thread_start(zpl_thread *t, zpl_thread_proc proc, void *user_data) {
    zpl_thread_start_with_stack(t, proc, user_data, 0);
}

void zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *user_data, zpl_isize stack_size) {
    ZPL_ASSERT(!t->is_running);
    ZPL_ASSERT(proc != NULL);
    t->proc = proc;
    t->user_data = user_data;
    t->stack_size = stack_size;

    #if defined(ZPL_SYSTEM_WINDOWS)
        t->win32_handle = CreateThread(NULL, stack_size, zpl__thread_proc, t, 0, NULL);
        ZPL_ASSERT_MSG(t->win32_handle != NULL, "CreateThread: GetLastError");
    #else
        {
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
            if (stack_size != 0)
                pthread_attr_setstacksize(&attr, stack_size);
            pthread_create(&t->posix_handle, &attr, zpl__thread_proc, t);
            pthread_attr_destroy(&attr);
        }
    #endif

    t->is_running = true;
    zpl_semaphore_wait(&t->semaphore);
}

void zpl_thread_join(zpl_thread *t) {
    if (!t->is_running) return;

    #if defined(ZPL_SYSTEM_WINDOWS)
        WaitForSingleObject(t->win32_handle, INFINITE);
        CloseHandle(t->win32_handle);
        t->win32_handle = INVALID_HANDLE_VALUE;
    #else
        pthread_join(t->posix_handle, NULL);
        t->posix_handle = 0;
    #endif
        t->is_running = false;
    }

    zpl_u32 zpl_thread_current_id(void) {
        zpl_u32 thread_id;
    #if defined(ZPL_SYSTEM_WINDOWS)
        #if defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
            thread_id = (cast(zpl_u32 *)__readfsdword(24))[9];
        #elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
            thread_id = (cast(zpl_u32 *)__readgsqword(48))[18];
        #else
            thread_id = GetCurrentThreadId();
        #endif

    #elif defined(ZPL_SYSTEM_OSX) && defined(ZPL_ARCH_64_BIT)
        thread_id = pthread_mach_thread_np(pthread_self());
    #elif defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
        __asm__("mov %%gs:0x08,%0" : "=r"(thread_id));
    #elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
        __asm__("mov %%fs:0x10,%0" : "=r"(thread_id));
    #else
        #error Unsupported architecture for zpl_thread_current_id()
    #endif

    return thread_id;
}

void zpl_thread_set_name(zpl_thread *t, char const *name) {
    #if defined(ZPL_COMPILER_MSVC)
        #pragma pack(push, 8)
            typedef struct {
                DWORD       type;
                char const *name;
                DWORD       id;
                DWORD       flags;
            } zplprivThreadName;
        #pragma pack(pop)

        zplprivThreadName tn;
        tn.type  = 0x1000;
        tn.name  = name;
        tn.id    = GetThreadId(cast(HANDLE)t->win32_handle);
        tn.flags = 0;

        __try {
            RaiseException(0x406d1388, 0, zpl_size_of(tn)/4, cast(ULONG_PTR *)&tn);
        } __except(1 /*EXCEPTION_EXECUTE_HANDLER*/) {
        }

    #elif defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_COMPILER_MSVC)
        zpl_unused(t);
        zpl_unused(name);
        // IMPORTANT TODO: Set thread name for GCC/Clang on windows
        return;
    #elif defined(ZPL_SYSTEM_OSX)
        // TODO: Test if this works
        pthread_setname_np(name);
    #else
        zpl_unused(t);
        zpl_unused(name);
        // TODO: Test if this works
        //        pthread_set_name_np(t->posix_handle, name);
    #endif
}
