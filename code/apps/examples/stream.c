#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

int main(void) {
    char numbers[] = {1, 2, 3, 4};
    zpl_file f;
    zpl_file_stream_open(&f, zpl_heap(), (zpl_u8*)numbers, 4, false);
    for (int i=0; i<4; i++) {
        zpl_u8 b;
        zpl_file_read(&f, &b, 1);
        zpl_printf("Value: %d\n", b);
    }

    zpl_file_stream_close(&f);

    zpl_file_stream_open(&f, zpl_heap(), (zpl_u8*)numbers, 4, true);
    for (int i=0; i<4; i++) {
        zpl_u8 b;
        zpl_file_read(&f, &b, 1);
        zpl_printf("Value: %d\n", b);
    }

    zpl_file_stream_close(&f);
    return 0;
}