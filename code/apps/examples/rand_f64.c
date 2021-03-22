#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main() {
    zpl_random rand;
    zpl_random_init(&rand);
    for (int i=0; i < 100; i++)
    {
        zpl_printf("%f\n", zpl_random_range_f64(&rand, 0.0, 1.0));
    }
    return 0;
}
