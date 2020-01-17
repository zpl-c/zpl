#include "tester_framework.h"

/* TEST CATEGORIES */
#include "unit/json.h"
#include "unit/print.h"

#define MODULE_LIST \
    X(json5_parser) \
    X(print)


int main() {
    int err = 0, cnt = 0;
    zpl_printf("ZPL Automated tests\n");

    #define X(name) cnt++;
        MODULE_LIST
    #undef X

    zpl_printf("Modules to be tested: %d\n", cnt);

    #define X(name) err += ZPL_JOIN2(module__,name)();
        MODULE_LIST
    #undef X

    zpl_printf("--------------------------------------\n");
    zpl_printf("MODULES: %d total, %d failed, %d passed\n", _g_modules, _g_modules_err, _g_modules - _g_modules_err);
    zpl_printf("TESTS:   %d total, %d failed, %d passed\n", _g_total, _g_errors, _g_total - _g_errors);

    return -err;
}
