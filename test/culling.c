#define ZPL_IMPLEMENTATION
#include "zpl.h"

#define ZPL_CULL_IMPLEMENTATION
#include "zpl_cull.h"

int
main(void) {
    zpl_cull_bounds_t b = {0};
    f32 center[3] = {0};
    f32 half[3] = {100};
    zpl_memcopy(b.E, center, 3*4);
    zpl_memcopy(b.half, half, 3*4);
    
    zpl_cull_t root = {0};
    zpl_cull_init(&root, zpl_heap_allocator(), zpl_cull_dim_2d_ev, b, 2);
    
    zpl_cull_node_t e1 = {0};
    e1.E[0] = 20;
    zpl_cull_insert(&root, e1);
    
    zpl_cull_node_t e2 = {0};
    e2.E[0] = 30;
    zpl_cull_insert(&root, e2);
    
    zpl_cull_node_t e3 = {0};
    e3.E[0] = 35;
    zpl_cull_insert(&root, e3);
    
    zpl_cull_node_t e4 = {0};
    e4.E[0] = 12;
    zpl_cull_insert(&root, e4);
    
    zpl_cull_bounds_t search_bounds = {
        .E = {0,0,0},
        .half = {20,20,20},
    };
    
    zpl_array_t(zpl_cull_node_t) search_result;
    zpl_array_init(search_result, zpl_heap_allocator());
    
    zpl_cull_query(&root, search_bounds, search_result);
    
    isize result = zpl_array_count(search_result);
    ZPL_ASSERT(result == 2);
    
    return 0;
}

