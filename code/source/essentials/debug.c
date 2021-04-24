// file: source/essentials/debug.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

void zpl_assert_handler(char const *condition, char const *file, zpl_i32 line, char const *msg, ...) {
    zpl__printf_err("%s:(%d): Assert Failure: ", file, line);

    if (condition) zpl__printf_err("`%s` ", condition);

    if (msg) {
        va_list va;
        va_start(va, msg);
        zpl__printf_err_va(msg, va);
        va_end(va);
    }

    zpl__printf_err("%s", "\n");
}

zpl_i32 zpl_assert_crash(char const *condition) {
    ZPL_PANIC(condition);
    return 0;
}

#if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
    #include <sched.h>
#endif

#if defined(ZPL_SYSTEM_WINDOWS)
    void zpl_exit(zpl_u32 code) { ExitProcess(code); }
#else
    #include <stdlib.h>
    void zpl_exit(zpl_u32 code) { exit(code); }
#endif

ZPL_END_C_DECLS
