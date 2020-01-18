#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>
#include <stdlib.h>

int main() {
    zpl_set_env("ZPLTMP", "Hello World");

    const char *foo = zpl_get_env("ZPLTMP");
    zpl_printf("%s\n", foo);
    zpl_mfree((char *)foo);

    const char *foo2 = zpl_get_env_buf("ZPLTMP");
    zpl_printf("%s\n", foo2);

    zpl_string bar = zpl_get_env_str("ZPLTMP");
    zpl_printf("%s\n", bar);
    zpl_string_free(bar);

    return 0;
}
