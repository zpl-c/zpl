#define ZPL_IMPL
#include <zpl.h>
static int _g_modules = 0;
static int _g_modules_err = 0;
static int _g_total = 0;
static int _g_errors = 0;

#define MODULE(name, scope) \
    int ZPL_JOIN2(module__,name)() { \
        zpl_printf("--------------------------------------\n"); \
        zpl_printf("  MODULE: %s\n", #name); \
        _g_modules++; \
        int _total = 0; \
        int _errors = 0; \
        int _lasterr = 0; \
        char *_errstr = 0; \
        scope; \
        zpl_printf("  Results: %d total, %d failed, %d passed\n", _total, _errors, _total - _errors); \
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
    _errors += _lasterr; \
    printf("    TEST: %-80s: %s%s\n", desc, (_lasterr) ? "\x1B[31mFAIL\x1B[0m" : "\x1B[32mPASS\x1B[0m", _errstr);

#define FAIL(a, b)                             { _errstr = zpl_bprintf("\n      Reason: %s:%d %s %s:%d\n", #a, a, (a == b)?"==":"!=", #b, b); _lasterr = 1; break; }
#define STRFAIL(a, b)                          { _errstr = zpl_bprintf("\n      Reason: %s:%s %s %s:%s\n", #a, a, (!strcmp(a,b))?"==":"!=", #b, b); _lasterr = 1; break; }
#define EQUALS(a, b)        if (a != b)        { FAIL(a, b); }
#define STREQUALS(a, b)     if (!!strcmp(a,b)) { STRFAIL(a, b); }
#define STRNEQUALS(a, b)    if (!strcmp(a,b))  { STRFAIL(a, b); }
#define NEQUALS(a, b)       if (a == b)        { FAIL(a, b); }
#define LESSER(a, b)        if (a >= b)        { FAIL(a, b); }
#define GREATER(a, b)       if (a <=b)         { FAIL(a, b); }
#define LESSEREQ(a, b)      if (a < b)         { FAIL(a, b); }
#define GREATEREQ(a, b)     if (a > b)         { FAIL(a, b); }
