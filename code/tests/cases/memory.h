MODULE(memory, {
    IT("should be supporting plain memory arena", {
        zpl_arena arena = {0};
        zpl_arena_init_from_allocator(&arena, zpl_heap(), 1024);

        char *buffer1 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 512);
        char *buffer2 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 256);

        EQUALS(arena.total_allocated, 512+256);

        zpl_unused(buffer1);
        zpl_unused(buffer2);

        zpl_arena_free(&arena);
    });

    IT("should be handling the failed allocation for arena", {
        zpl_arena arena = {0};
        zpl_arena_init_from_allocator(&arena, zpl_heap(), 1024);

        char *buffer1 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 512);
        char *buffer2 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 512);
        char *buffer3 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 256);

        NEQUALS(buffer1, NULL); // first pointer should be allocated
        NEQUALS(buffer2, NULL); // second piointer also
        EQUALS(buffer3, NULL); // third should be NULL, as it was not allocated

        EQUALS(arena.total_allocated, 512+512);

        zpl_unused(buffer1);
        zpl_unused(buffer2);
        zpl_unused(buffer3);

        zpl_arena_free(&arena);
    });

    IT("should be handling the failed allocation for arena with partial entry", {
        zpl_arena arena = {0};
        zpl_arena_init_from_allocator(&arena, zpl_heap(), 768);

        char *buffer1 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 512);
        char *buffer2 = (char *)zpl_alloc(zpl_arena_allocator(&arena), 512);

        NEQUALS(buffer1, NULL); // first pointer should be allocated
        EQUALS(buffer2, NULL); // second piointer should be not allocated

        EQUALS(arena.total_allocated, 512);

        zpl_unused(buffer1);
        zpl_unused(buffer2);

        zpl_arena_free(&arena);
    });
});
