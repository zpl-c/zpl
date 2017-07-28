/*

ZPL - ES module

License:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.
    
Warranty:
    No warranty is implied, use at your own risk.
    
Usage:
    #define ZPL_ENT_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:
    
    #define ZPL_ENT_IMPLEMENTATION
    #include"zpl_ent.h"
    
Optional Switches:
    USE_128_BITS -- uses 128-bit storage for entity identification handle.
    
Credits:
    Dominik Madarasz (GitHub: zaklaus)
    Vladislav Gritsenko (GitHub: inlife)
    
Version History:
    1.06 - Added small example
    1.05 - Got rid of redundant field
    1.00 - Initial version
    
*/

#ifndef ZPL_INCLUDE_ZPL_ENT_H
#define ZPL_INCLUDE_ZPL_ENT_H

#ifdef  ZPL_ENT_USE_128_BITS
#define ZPL_ENT_ID u64
#else
#define ZPL_ENT_ID u32
#endif

#if defined(__cplusplus)
extern "C" {
#endif
    
    typedef struct zpl_ent_id_t {
        ZPL_ENT_ID id;
        ZPL_ENT_ID generation;
    } zpl_ent_id_t;
    
    typedef struct zpl_ent_node_t {
        zpl_ent_id_t           handle;
        struct zpl_ent_node_t *next;
    } zpl_ent_node_t;
    
    typedef struct zpl_ent_pool_t {
        zpl_allocator_t backing;
        usize           count;
        zpl_buffer_t(zpl_ent_node_t)freelist;
        zpl_ent_node_t             *first_free;
    } zpl_ent_pool_t;
    
    ZPL_DEF void            zpl_ent_init   (zpl_ent_pool_t *pool, zpl_allocator_t allocator, isize count);
    ZPL_DEF void            zpl_ent_free   (zpl_ent_pool_t *pool);
    ZPL_DEF zpl_ent_id_t    zpl_ent_create (zpl_ent_pool_t *pool);
    ZPL_DEF void            zpl_ent_destroy(zpl_ent_pool_t *pool, zpl_ent_id_t handle);
    
    
    // NOTE(ZaKlaus): To be used as:
    #if 0

    // NOTE(ZaKlaus): Header file preferably
    typedef struct {
        i32 x,y,z;
    } ZPL_ENT_COMP_DECLARE(position);
    
    // NOTE(ZaKlaus): Exactly 1 occurence in source file
    ZPL_ENT_COMP_DEFINE(position);
    
    #endif
#define ZPL_ENT_COMP_DECLARE(NAME) \
    ZPL_JOIN2(NAME, _t); \
    typedef struct ZPL_JOIN2(NAME, _meta_ent_t) { \
        zpl_ent_id_t handle; \
        ZPL_ENT_ID   used; \
    } ZPL_JOIN2(NAME, _meta_ent_t); \
    typedef struct ZPL_JOIN2(NAME, _meta_t) { \
        zpl_allocator_t ent_a, data_a; \
        zpl_buffer_t(ZPL_JOIN2(NAME, _meta_ent_t)) entities; \
        zpl_buffer_t(ZPL_JOIN2(NAME, _t))         data; \
    } ZPL_JOIN2(NAME, _meta_t); \
    \
    \
    void                  ZPL_JOIN2(NAME,_init)       (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_pool_t *p, zpl_allocator_t ent_a, zpl_allocator_t data_a); \
    void                  ZPL_JOIN2(NAME,_free)       (ZPL_JOIN2(NAME, _meta_t) *h); \
    ZPL_JOIN2(NAME, _t) * ZPL_JOIN2(NAME,_attach)     (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle, ZPL_JOIN2(NAME, _t) data); \
    void                  ZPL_JOIN2(NAME,_detach)     (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle); \
    ZPL_JOIN2(NAME, _t) * ZPL_JOIN2(NAME,_fetch)      (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle);

#define ZPL_ENT_COMP_DEFINE(NAME) \
    void ZPL_JOIN2(NAME,_init) (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_pool_t *p, zpl_allocator_t ent_a, zpl_allocator_t data_a) { \
        ZPL_ASSERT(h&&p); h->ent_a = ent_a; h->data_a = data_a; \
        zpl_buffer_init(h->entities, ent_a, p->count); \
        zpl_buffer_init(h->data, data_a, p->count); \
    }\
    void ZPL_JOIN2(NAME,_free) (ZPL_JOIN2(NAME, _meta_t) *h) { \
        ZPL_ASSERT(h); \
        zpl_buffer_free(h->entities, h->ent_a); \
        zpl_buffer_free(h->data, h->data_a); \
    } \
    ZPL_JOIN2(NAME, _t) * ZPL_JOIN2(NAME,_attach) (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle, ZPL_JOIN2(NAME, _t) data) { \
        ZPL_ASSERT(h); \
        ZPL_JOIN2(NAME, _meta_ent_t) *meta_ent = (h->entities+handle.id); \
        meta_ent->handle = handle; \
        meta_ent->used = true; \
        *(h->data+handle.id) = data; \
        return (h->data+handle.id); \
    } \
    void ZPL_JOIN2(NAME,_detach) (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle) { \
        ZPL_ASSERT(h); \
        ZPL_JOIN2(NAME, _meta_ent_t) *meta_ent = (h->entities+handle.id); \
        meta_ent->used = false; \
    } \
    ZPL_JOIN2(NAME, _t) * ZPL_JOIN2(NAME, _fetch) (ZPL_JOIN2(NAME, _meta_t) *h, zpl_ent_id_t handle) { \
        ZPL_ASSERT(h); \
        ZPL_JOIN2(NAME, _meta_ent_t) *meta_ent = (h->entities+handle.id); \
        if ((meta_ent->used) && (meta_ent->handle.id == handle.id) && (meta_ent->handle.generation == handle.generation)) { \
            return (h->data+handle.id); \
        } \
        else { \
            return NULL; \
        } \
    }

    
#if defined(__cplusplus)
}
#endif

#if defined(ZPL_ENT_IMPLEMENTATION) && !defined(ZPL_ENT_IMPLEMENTATION_DONE)

#if defined(__cplusplus)
extern "C" {
#endif

    void zpl_ent_init(zpl_ent_pool_t *pool, zpl_allocator_t allocator, isize count) {
        ZPL_ASSERT(pool);
        
        zpl_allocator_t a = pool->backing = allocator;
        pool->count = count;
        
        zpl_buffer_init(pool->freelist, a, zpl_size_of(zpl_ent_node_t)*count);
        
        // NOTE(ZaKlaus): Build the freelist
        pool->first_free = pool->freelist;
        for (usize i = 0; i < count; ++i) {
            zpl_ent_node_t *f = (pool->freelist+i);
            f->handle = (zpl_ent_id_t) { i, 0 };
            f->next = (pool->freelist+i+1);
        }
        (pool->freelist+count-1)->next = NULL;
    }
    
    void zpl_ent_free(zpl_ent_pool_t *pool) {
        ZPL_ASSERT(pool);
        
        zpl_buffer_free(pool->freelist, pool->backing);
    }
    
    zpl_ent_id_t zpl_ent_create(zpl_ent_pool_t *pool) {
        ZPL_ASSERT(pool);
        ZPL_ASSERT(pool->first_free);
        
        zpl_ent_node_t *f = pool->first_free;
        zpl_ent_id_t ent = f->handle;
        pool->first_free = f->next;
        
        return ent;
    }
    
    void zpl_ent_destroy(zpl_ent_pool_t *pool, zpl_ent_id_t handle) {
        ZPL_ASSERT(pool);
        
        if (pool->first_free == NULL) {
            zpl_ent_node_t *f = pool->first_free = pool->freelist;
            f->handle = handle;
            f->next   = NULL;
            ++f->handle.generation;
        }
        else {
            ZPL_ASSERT(pool->first_free - 1 >= pool->freelist);
            zpl_ent_node_t f_ = { (zpl_ent_id_t){ handle.id, handle.generation+1 }, pool->first_free };
            zpl_ent_node_t *f = (pool->first_free - 1);
            *f = f_;
            pool->first_free = f;
        }
    }
    
#if defined(__cplusplus)
}
#endif

#endif
        
#endif // ZPL_INCLUDE_ZPL_ENT_H