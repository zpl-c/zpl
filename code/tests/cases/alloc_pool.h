#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif
#define CLEANUP() \
    do { \
        zpl_pool_free(&pool); \
    } while (0)

#define A zpl_pool_allocator(&pool)

MODULE(alloc_pool, {
    zpl_pool pool = {0};

    IT("allocates 512 blocks of size 2 bytes", {
        zpl_pool_init(&pool, zpl_heap(), 512, zpl_size_of(zpl_u16));

        EQUALS(pool.num_blocks, 512);
        EQUALS(pool.block_size, zpl_size_of(zpl_u16));
        CLEANUP();
    });

    IT("can push 4 blocks into pool", {
        zpl_pool_init(&pool, zpl_heap(), 8, 1);
        
        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 1);

        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 2);

        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 3);

        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 4);

        CLEANUP();
    });

    IT("creates 3 blocks and removes the middle", {
        zpl_pool_init(&pool, zpl_heap(), 8, 1);
        
        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 1);

        void *a = zpl_alloc(A, 1);
        EQUALS(pool.total_size, 2);

        zpl_free(A, a);
        EQUALS(pool.total_size, 1);

        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 2);

        CLEANUP();
    });

    IT("creates 2 blocks, removes all of them and adds 1 block", {
        zpl_pool_init(&pool, zpl_heap(), 2, 1);
        
        zpl_alloc(A, 1);
        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 2);

        zpl_free_all(A);

        EQUALS(pool.total_size, 0);
        EQUALS((zpl_uintptr)pool.physical_start, (zpl_uintptr)pool.free_list);

        zpl_alloc(A, 1);
        EQUALS(pool.total_size, 1);
        NEQUALS((zpl_uintptr)pool.physical_start, (zpl_uintptr)pool.free_list);
        CLEANUP();
    });

});

#undef CLEANUP
#undef A

