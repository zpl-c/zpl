#include "tester_framework.h"

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
#endif

#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4201)
    #pragma warning(disable : 4127) // Conditional expression is constant
#endif

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

#if defined(ZPL_COMPILER_MSVC)
    #pragma warning(pop)
#endif

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif
