/**
  ZPL - Tester framework

Usage:
  #include "unit.h"

  and cover your beautiful code already!

GitHub:
  https://github.com/zpl-c/tester

Version History:
  1.0.0 - Where it all started... (not really)

License:
  See LICENSE
*/

static int _g_modules = 0;
static int _g_modules_err = 0;
static int _g_total = 0;
static int _g_errors = 0;

#ifndef UNIT_MAX_CASES
#define UNIT_MAX_CASES 256
#endif

#ifndef UNIT_SKIP_MAGIC
#define UNIT_SKIP_MAGIC 0xFF
#endif

#ifndef UNIT_JOIN2
#define UNIT_JOIN2(a,b) a##b
#endif

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

// Locally persisting buffer
static inline char* unit__bprintf(const char* fmt, ...)
{
    static char buf[128];
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    return buf;
}

#define MODULE(name, scope) \
    int UNIT_JOIN2(module__,name)() { \
        printf("--------------------------------------\n"); \
        printf(" module: %s\n", #name); \
        printf("--------------------------------------\n"); \
        fflush(stdout); \
        _g_modules++; \
        int _total = 0; \
        int _errors = 0; \
        int _lasterr = 0; \
        char *_errstr = 0; \
        scope; \
        fflush(stdout); \
        printf("\n results: %d total, %s%d failed\x1B[0m, %s%d passed\x1B[0m\n", _total, _errors>0?"\x1B[31m":"", _errors, _errors==0?"\x1B[32m":"", _total - _errors); \
        _g_total += _total; \
        _g_errors += _errors; \
        if (_errors) _g_modules_err++; \
        return (_errors); \
    }

#define IT(desc, scope) \
    _lasterr = 0; \
    _errstr = ""; \
    _total += 1; \
    do scope while(0); \
    if (_lasterr != UNIT_SKIP_MAGIC) _errors += _lasterr; \
    printf(" * [%s]: It %s %s\n", (_lasterr == UNIT_SKIP_MAGIC) ? "\x1B[33mSKIP\x1B[0m" : (_lasterr) ? "\x1B[31mFAIL\x1B[0m" : "\x1B[32mPASS\x1B[0m", desc, _errstr);

#define FAIL(a, b)                             { _errstr = unit__bprintf("\n\n\tassert: \x1B[31m%s:%lld %s %s:%lld\x1B[0m\n\tat %s:%d\n", #a, a, (a == b)?"==":"!=", #b, b, __FILE__, __LINE__); _lasterr = 1; break; }
#define UFAIL(a, b)                             { _errstr = unit__bprintf("\n\n\tassert: \x1B[31m%s:%llu %s %s:%llu\x1B[0m\n\tat %s:%d\n", #a, a, (a == b)?"==":"!=", #b, b, __FILE__, __LINE__); _lasterr = 1; break; }
#define STRFAIL(a, b)                          { _errstr = unit__bprintf("\n\n\tassert: \x1B[31m%s:%s %s %s:%s\x1B[0m\n\tat %s:%d\n", #a, (char *)a, (!strcmp(a,b))?"==":"!=", #b, b, __FILE__, __LINE__); _lasterr = 1; break; }
#define EQUALS(a, b)        if (a != b)        { FAIL(a, b); }
#define UEQUALS(a, b)        if (a != b)        { UFAIL(a, b); }
#define STREQUALS(a, b)     if (!!strcmp(a,b)) { STRFAIL(a, b); }
#define STRCEQUALS(a, b, c)     if (!!strncmp(a,b, c)) { STRFAIL(a, b); }
#define STRCNEQUALS(a, b, c)     if (!strncmp(a,b, c)) { STRFAIL(a, b); }
#define STRNEQUALS(a, b)    if (!strcmp(a,b))  { STRFAIL(a, b); }
#define NEQUALS(a, b)       if (a == b)        { FAIL(a, b); }
#define LESSER(a, b)        if (a >= b)        { FAIL(a, b); }
#define GREATER(a, b)       if (a <=b)         { FAIL(a, b); }
#define LESSEREQ(a, b)      if (a < b)         { FAIL(a, b); }
#define GREATEREQ(a, b)     if (a > b)         { FAIL(a, b); }
#define SKIP()                                 { _lasterr = UNIT_SKIP_MAGIC; break; }

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wattributes"
    #pragma GCC diagnostic ignored "-Wunused-value"
    #pragma GCC diagnostic ignored "-Wignored-qualifiers"
    #pragma GCC diagnostic ignored "-Wunused-variable"
    #pragma GCC diagnostic ignored "-Wunused-function"
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #pragma GCC diagnostic ignored "-Wmissing-braces"
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    #pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4201)
    #pragma warning(disable : 4127) // Conditional expression is constant
#endif

typedef int (*unit_case)();

#define UNIT_CREATE(name) \
    const char *unit_name = name; \
    unit_case unit_cases[UNIT_MAX_CASES] = {0}; \
    int unit_count = 0;

#define UNIT_CASE(name) \
    unit_cases[unit_count++] = UNIT_JOIN2(module__,name)

#define UNIT_RUN() \
        unit_main(unit_name, unit_cases, unit_count)

int unit_main(const char *name, unit_case *cases, int count) {
    int err = 0, cnt = count;
    printf("> testing suite:\n\n");
    printf("   * library: %s\n", name);
    printf("   * modules: %d\n", cnt);
    printf("\n");

    for (int i = 0; i < count; ++i) {
        err += cases[i]();
    }

    fflush(stdout);
    printf("--------------------------------------\n"); \
    printf("> total:\n\n");
    printf(" * modules: %d total, %s%d failed\x1B[0m, %s%d passed\x1B[0m\n", _g_modules, _g_modules_err>0?"\x1B[31m":"" ,_g_modules_err, _g_modules_err==0?"\x1B[32m":"", _g_modules - _g_modules_err);
    printf(" * tests:   %d total, %s%d failed\x1B[0m, %s%d passed\x1B[0m\n", _g_total, _g_errors>0?"\x1B[31m":"" ,_g_errors, _g_errors==0?"\x1B[32m":"", _g_total - _g_errors);
    printf("\n");

    return -err;
}

#if defined(ZPL_COMPILER_MSVC)
    #pragma warning(pop)
#endif

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif
