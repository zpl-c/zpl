// file: source/core/misc.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
    #include <sched.h>
#endif

#if defined(ZPL_SYSTEM_WINDOWS)
    void zpl_exit(zpl_u32 code) { ExitProcess(code); }
#else
    void zpl_exit(zpl_u32 code) { exit(code); }
#endif

void zpl_yield(void) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        Sleep(0);
    #else
        sched_yield();
    #endif
}

const char *zpl_get_env(const char *name) {
    char *buffer = NULL;
    const char *ptr = zpl_get_env_buf(name);

    if (ptr == NULL) {
        return NULL;
    }

    zpl_isize ptr_size = zpl_strlen(ptr);
    buffer = (char *)zpl_malloc(ptr_size * sizeof(char)+1);
    zpl_memcopy((char *)buffer, ptr, ptr_size+1);
    return buffer;
}

const char *zpl_get_env_buf(const char *name) {
    #ifdef ZPL_SYSTEM_WINDOWS
        zpl_local_persist wchar_t wbuffer[32767] = {0};
        zpl_local_persist char buffer[32767] = {0};

        if (!GetEnvironmentVariableW(
                cast(LPCWSTR)zpl_utf8_to_ucs2_buf(cast(const zpl_u8 *)name),
                cast(LPWSTR)wbuffer, 32767)) {
            return NULL;
        }

        zpl_ucs2_to_utf8(cast(zpl_u8*)buffer, 32767, cast(const zpl_u16*)wbuffer);

        return (const char *)buffer;
    #else
        return (const char *)getenv(name);
    #endif
}

zpl_string zpl_get_env_str(const char *name) {
    const char *buf = zpl_get_env_buf(name);

    if (buf == NULL) {
        return NULL;
    }

    zpl_string str = zpl_string_make(zpl_heap(), buf);
    return str;
}

void zpl_set_env(const char *name, const char *value) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        SetEnvironmentVariableA(name, value);
    #else
        setenv(name, value, 1);
    #endif
}

void zpl_unset_env(const char *name) {
    #if defined(ZPL_SYSTEM_WINDOWS)
        SetEnvironmentVariableA(name, NULL);
    #else
        unsetenv(name);
    #endif
}

#if !defined(ZPL_SYSTEM_WINDOWS)
    extern char **environ;
#endif

zpl_u32 zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer) {
    #if defined(ZPL_SYSTEM_EMSCRIPTEN)
        ZPL_PANIC("zpl_system_command not supported");
    #else

        #if defined(ZPL_SYSTEM_WINDOWS)
            FILE *handle = _popen(command, "r");
        #else
            FILE *handle =  popen(command, "r");
        #endif

        if(!handle) return 0;

        int c;
        zpl_usize i=0;
        while ((c = getc(handle)) != EOF && i++ < buffer_len) {
            *buffer++ = c;
        }

        #if defined(ZPL_SYSTEM_WINDOWS)
            _pclose(handle);
        #else
            pclose(handle);
        #endif

    #endif

    return 1;
}

zpl_string zpl_system_command_str(const char *command, zpl_allocator backing) {
    #if defined(ZPL_SYSTEM_EMSCRIPTEN)
        ZPL_PANIC("zpl_system_command not supported");
    #else

        #if defined(ZPL_SYSTEM_WINDOWS)
            FILE *handle = _popen(command, "r");
        #else
            FILE *handle =  popen(command, "r");
        #endif

        if(!handle) return NULL;

        zpl_string output = zpl_string_make_reserve(backing, 4);

        int c;
        while ((c = getc(handle)) != EOF) {
            char ins[2] = {(char)c,0};
            output = zpl_string_appendc(output, ins);
        }

        #if defined(ZPL_SYSTEM_WINDOWS)
            _pclose(handle);
        #else
            pclose(handle);
        #endif
        return output;
    #endif
    return NULL;
}

ZPL_END_C_DECLS
