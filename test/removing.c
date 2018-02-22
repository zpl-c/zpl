#define ZPL_IMPLEMENTATION
#define ZPLM_IMPLEMENTATION
#define ZPLC_IMPLEMENTATION

#include "zpl.h"
#include "zpl_math.h"
#include "zpl_cull.h"

int main(void) {
    zplc_bounds_t b = {0};

    b.centre = zplm_vec3(0, 0, 0);
    b.half_size = zplm_vec3(400, 400, 400);

    zplm_vec3_t min_bounds = {0};
    min_bounds.x = 50.0f;
    min_bounds.y = 50.0f;

    zplc_t root = {0};
    zplc_init(&root, zpl_heap_allocator(), zplc_dim_2d_ev, b, min_bounds, 32);
    zplc_bounds_t search_bounds = {
        .centre = {0,0,0},
        .half_size = {250,250,250},
    };


    srand(0xDEADBEEF);
    for (isize i = 0; i < 100; ++i) {
        zplc_node_t e = {0};
        e.position.x =  (float)(rand() % 400);
        e.position.y =  (float)(rand() % 400);
        e.tag = i;
        // zplc_insert(&root, e);
        // last = e;
    }

    zplc_node_t my1 = {0};
    my1.position.x = 15.0f;
    my1.position.y = 15.0f;
    my1.tag = 228;

    zplc_t *my1branch = zplc_insert(&root, my1);
    zplc_remove(my1branch, 228);

    zplc_t *my2branch = zplc_insert(&root, my1);
    zplc_remove(my2branch, 228);

    zplc_t *my3branch = zplc_insert(&root, my1);
    zplc_remove(my3branch, 228);

    zplc_t *branch = my1branch;
    b32 contains = zplc__contains(branch->dimensions, branch->boundary, my1.position.e);

    if (!contains) {
        zpl_printf("not contains 288\n");
        // zplc_remove(branch, j);
        // stream->branch = zplc_insert(&ctx->streamer, node);
    } else {
        zpl_printf("contains 288\n");
    }


    zpl_array_t(zplc_node_t) search_result2;
    zpl_array_init(search_result2, zpl_heap_allocator());
    zplc_query(&root, search_bounds, &search_result2);

    isize c = zpl_array_count(search_result2);

    for (int i = 0; i < c; ++i) {
        zpl_printf("we met %ld\n", search_result2[i].tag);
    }

    return 0;
}
