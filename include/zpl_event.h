
/*

ZPL - Event module

License:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.
    
Warranty:
    No warranty is implied, use at your own risk.
    
Usage:
    #define ZPL_EVENT_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:
    
    #define ZPL_EVENT_IMPLEMENTATION
    #include"zpl.h"

Credits:
    Dominik Madarasz (GitHub: zaklaus)
    
Version History:
    1.00 - Initial version
    
*/

#ifndef ZPL_INCLUDE_ZPL_EVENT_H
#define ZPL_INCLUDE_ZPL_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif
    
    //////////////////////////////////////////////////////
    //
    // Event handler
    // 
    // Uses hash table to store array of callbacks per
    // each valid event type.
    //
    // Each event callback receives an anonymous pointer
    // which has to be casted to proper base type.
    //
    // Usage:
    // - Initialize event pool.
    // - Declare your event callbacks and any data layout
    //   used by the events.
    // - Add event callbacks to the pool. (Returns callback ID.)
    // - Trigger arbitrary event in pool with specified dataset.
    // - (Optional) Remove arbitrary event callback
    //   by refering to it through event type and its callback ID.
    //

    typedef void *zpl_event_data_t;
    
#define ZPL_EVENT(name) void name(zpl_event_data_t evt)
    typedef ZPL_EVENT(zpl_event_cb);
    
#define ZPL_EVENT_CAST(Type, name) Type * name = cast(Type *)evt
        
    typedef zpl_array_t(zpl_event_cb*) zpl_event_block;
    
    ZPL_TABLE_DECLARE(static, zpl_event_pool, zpl_event_pool_, zpl_event_block);
    
    ZPL_DEF void zpl_event_init   (zpl_event_pool *pool, zpl_allocator_t alloc);
    ZPL_DEF void zpl_event_destroy(zpl_event_pool *pool);
    ZPL_DEF u64  zpl_event_add    (zpl_event_pool *pool, u64 slot, zpl_event_cb cb);
    ZPL_DEF void zpl_event_remove (zpl_event_pool *pool, u64 slot, u64 index);
    ZPL_DEF void zpl_event_trigger(zpl_event_pool *pool, u64 slot, zpl_event_data_t evt);
    
#ifdef __cplusplus
}
#endif

#if defined(ZPL_EVENT_IMPLEMENTATION) && !defined(ZPL_EVENT_IMPLEMENTATION_DONE)
#define ZPL_EVENT_IMPLEMENTATION_DONE

#ifdef __cplusplus
extern "C" {
#endif

    ZPL_TABLE_DEFINE(zpl_event_pool, zpl_event_pool_, zpl_event_block);
    
    zpl_inline void zpl_event_init   (zpl_event_pool *pool, zpl_allocator_t alloc) {
        zpl_event_pool_init(pool, alloc);
    }
    
    zpl_inline void zpl_event_destroy(zpl_event_pool *pool) {
        for (isize i = 0; i < zpl_array_count(pool->entries); ++i) {
            zpl_event_block *block = &pool->entries[i].value;
            
            if (block) {
                zpl_array_free(*block);
            }
        }
        
        zpl_event_pool_destroy(pool);
    }
    
    u64 zpl_event_add(zpl_event_pool *pool, u64 slot, zpl_event_cb cb) {
        zpl_event_block *block = zpl_event_pool_get(pool, slot);
        
        if (!block) {
            zpl_event_block arr;
            zpl_array_init(arr, zpl_heap_allocator());
            zpl_event_pool_set(pool, slot, arr);
            block = zpl_event_pool_get(pool, slot);
        }
        
        u64 offset = zpl_array_count(block);
        zpl_array_append(*block, cb);
        return offset;
    }
    
    void zpl_event_remove(zpl_event_pool *pool, u64 slot, u64 index) {
        zpl_event_block *block = zpl_event_pool_get(pool, slot);
        
        if (block) {
            zpl_array_remove_at(*block, index);
        }
    }
    
    void zpl_event_trigger(zpl_event_pool *pool, u64 slot, zpl_event_data_t evt) {
        zpl_event_block *block = zpl_event_pool_get(pool, slot);
        
        if (block) {
            for (isize i = 0; i < zpl_array_count(*block); ++i) {
                (*block)[i](evt);
            }
        }
    }
    

#ifdef __cplusplus
}
#endif

#endif
#endif //ZPL_INCLUDE_ZPL_EVENT_H
