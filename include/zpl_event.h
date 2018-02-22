
/*

ZPL - Event module

Usage:
    #define ZPLEV_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:

    #define ZPLEV_IMPLEMENTATION
    #include"zpl_event.h"

Dependencies:
    zpl.h

Credits:
  Read AUTHORS.md

GitHub:
  https://github.com/zpl-c/zpl

Version History:
    1.0.7 - Small fixes for tiny cpp warnings
    1.0.0 - Initial version

    
    Copyright 2017-2018 Dominik Madarász
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. 
*/

#ifndef ZPL_INCLUDE_ZPL_EVENT_H
#define ZPL_INCLUDE_ZPL_EVENT_H

#include "zpl.h"

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

    typedef void *zplev_data;

#define ZPLEV(name) void name(zplev_data evt)
    typedef ZPLEV(zplev_cb);

#define ZPLEV_CAST(Type, name) Type * name = cast(Type *)evt

    typedef zpl_array_t(zplev_cb*) zplev_block;

    ZPL_TABLE_DECLARE(static, zplev_pool, zplev_pool_, zplev_block);

    ZPL_DEF void zplev_init   (zplev_pool *pool, zpl_allocator alloc);
    ZPL_DEF void zplev_destroy(zplev_pool *pool);
    ZPL_DEF u64  zplev_add    (zplev_pool *pool, u64 slot, zplev_cb cb);
    ZPL_DEF void zplev_remove (zplev_pool *pool, u64 slot, u64 index);
    ZPL_DEF void zplev_trigger(zplev_pool *pool, u64 slot, zplev_data evt);

#ifdef __cplusplus
}
#endif

#if defined(ZPLEV_IMPLEMENTATION) && !defined(ZPLEV_IMPLEMENTATION_DONE)
#define ZPLEV_IMPLEMENTATION_DONE

#ifdef __cplusplus
extern "C" {
#endif

    ZPL_TABLE_DEFINE(zplev_pool, zplev_pool_, zplev_block);

    zpl_inline void zplev_init   (zplev_pool *pool, zpl_allocator alloc) {
        zplev_pool_init(pool, alloc);
    }

    zpl_inline void zplev_destroy(zplev_pool *pool) {
        for (isize i = 0; i < zpl_array_count(pool->entries); ++i) {
            zplev_block *block = &pool->entries[i].value;

            if (block) {
                zpl_array_free(*block);
            }
        }

        zplev_pool_destroy(pool);
    }

    u64 zplev_add(zplev_pool *pool, u64 slot, zplev_cb cb) {
        zplev_block *block = zplev_pool_get(pool, slot);

        if (!block) {
            zplev_block arr;
            zpl_array_init(arr, zpl_heap_allocator());
            zplev_pool_set(pool, slot, arr);
            block = zplev_pool_get(pool, slot);
        }

        u64 offset = zpl_array_count(block);
        zpl_array_append(*block, cb);
        return offset;
    }

    void zplev_remove(zplev_pool *pool, u64 slot, u64 index) {
        zplev_block *block = zplev_pool_get(pool, slot);

        if (block) {
            zpl_array_remove_at(*block, (isize)index);
        }
    }

    void zplev_trigger(zplev_pool *pool, u64 slot, zplev_data evt) {
        zplev_block *block = zplev_pool_get(pool, slot);

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
