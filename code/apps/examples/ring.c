#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_EXPOSE_TYPES
#include <zpl.h>

ZPL_RING_DECLARE(zpl_ring_,u32);
ZPL_RING_DEFINE(zpl_ring_,u32);

int main()
{
    zpl_ring_u32 pad={0};
    zpl_ring_init(&pad, zpl_heap(), 3);
    zpl_ring_append(&pad, 1);
    zpl_ring_append(&pad, 2);
    zpl_ring_append(&pad, 3);
    
    while (!zpl_ring_empty(&pad)) {
        zpl_printf("Result is %d\n", *zpl_ring_get(&pad));
    }
    
    zpl_ring_free(&pad);
    
    return 0;
}

