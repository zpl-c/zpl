#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main()
{
    zpl_pad_u32 pad={0};
    zpl_pad_u32_init(&pad, zpl_heap(), 3);
    zpl_pad_u32_append(&pad, 1);
    zpl_pad_u32_append(&pad, 2);
    zpl_pad_u32_append(&pad, 3);

    while (!zpl_pad_u32_empty(&pad)) {
        zpl_printf("Result is %d\n", *zpl_pad_u32_get(&pad));
    }

    zpl_pad_u32_free(&pad);

    return 0;
}

