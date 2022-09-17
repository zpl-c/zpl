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

    IT("should be support growing memory arena", {

    });
});
