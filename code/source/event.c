////////////////////////////////////////////////////////////////
//
// Event Handler
//
//

ZPL_TABLE_DEFINE(zpl_event_pool, zpl_event_pool_, zpl_event_block);

void zpl_event_init(zpl_event_pool *pool, zpl_allocator alloc) { zpl_event_pool_init(pool, alloc); }

void zpl_event_destroy(zpl_event_pool *pool) {
    for (zpl_isize i = 0; i < zpl_array_count(pool->entries); ++i) {
        zpl_event_block *block = &pool->entries[i].value;

        if (block) { zpl_array_free(*block); }
    }

    zpl_event_pool_destroy(pool);
}

zpl_u64 zpl_event_add(zpl_event_pool *pool, zpl_u64 slot, zpl_event_cb cb) {
    zpl_event_block *block = zpl_event_pool_get(pool, slot);

    if (!block) {
        zpl_event_block arr;
        zpl_array_init(arr, zpl_heap_allocator( ));
        zpl_event_pool_set(pool, slot, arr);
        block = zpl_event_pool_get(pool, slot);
    }

    zpl_u64 offset = zpl_array_count(block);
    zpl_array_append(*block, cb);
    return offset;
}

void zpl_event_remove(zpl_event_pool *pool, zpl_u64 slot, zpl_u64 index) {
    zpl_event_block *block = zpl_event_pool_get(pool, slot);

    if (block) { zpl_array_remove_at(*block, (zpl_isize)index); }
}

void zpl_event_trigger(zpl_event_pool *pool, zpl_u64 slot, zpl_event_data evt) {
    zpl_event_block *block = zpl_event_pool_get(pool, slot);

    if (block) {
        for (zpl_isize i = 0; i < zpl_array_count(*block); ++i) { (*block)[i](evt); }
    }
}
