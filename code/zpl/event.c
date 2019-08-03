/** @file event.c
@brief Event handler

@n
@n Event handler
@n
@n Uses hash table to store array of callbacks per
@n each valid event type.
@n
@n Each event callback receives an anonymous pointer
@n which has to be casted to proper base type.
@n
@n Usage:
@n - Initialize event pool.
@n - Declare your event callbacks and any data layout
@n   used by the events.
@n - Add event callbacks to the pool. (Returns callback ID.)
@n - Trigger arbitrary event in pool with specified dataset.
@n - (Optional) Remove arbitrary event callback
@n   by refering to it through event type and its callback ID.
@n

@{
*/

typedef void *zpl_event_data;

typedef void (*zpl_event_cb)(zpl_event_data evt);

#define ZPL_EVENT_CAST(Type, name) Type * name = cast(Type *)evt

typedef zpl_event_cb* zpl_event_block; ///< zpl_array

ZPL_TABLE_DECLARE(static, zpl_event_pool, zpl_event_pool_, zpl_event_block);

ZPL_DEF void    zpl_event_init   (zpl_event_pool *pool, zpl_allocator alloc);
ZPL_DEF void    zpl_event_destroy(zpl_event_pool *pool);
ZPL_DEF zpl_u64 zpl_event_add    (zpl_event_pool *pool, zpl_u64 slot, zpl_event_cb cb);
ZPL_DEF void    zpl_event_remove (zpl_event_pool *pool, zpl_u64 slot, zpl_u64 index);
ZPL_DEF void    zpl_event_trigger(zpl_event_pool *pool, zpl_u64 slot, zpl_event_data evt);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Event Handler
//
//

ZPL_TABLE_DEFINE(zpl_event_pool, zpl_event_pool_, zpl_event_block);

zpl_inline void zpl_event_init(zpl_event_pool *pool, zpl_allocator alloc) { zpl_event_pool_init(pool, alloc); }

zpl_inline void zpl_event_destroy(zpl_event_pool *pool) {
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
