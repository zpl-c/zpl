#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    zpl_f64 num = zpl_str_to_f64(argv[1], NULL);
    zpl_printf("original: %f\nhex: %a\n", num, num);

    return 0;
}
