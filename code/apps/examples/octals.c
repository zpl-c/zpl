#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

int main() {
    zpl_i64 octal = zpl_str_to_i64("0666", NULL, 8);
    zpl_printf("%lld == %lld\n", octal, 0666);
    return 0;
}
