#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#include "zpl.h"

int main(void)
{
    zpl_printf("0.%0d%d\n", 0, 32);
    zpl_printf("0.%*d%d\n", 0, 42, 32);
    zpl_printf("0.%*d%d\n", 42, 0, 32);
    zpl_printf("0.%0*d%d\n", 42, 0, 32);
    return 0;
}
