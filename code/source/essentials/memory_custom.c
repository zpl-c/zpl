// file: source/essentials/memory_custom.c


#ifndef _IOSC11_SOURCE
#define _IOSC11_SOURCE
#endif

#include <stdlib.h>

#if defined(ZPL_SYSTEM_WINDOWS)
    #include <malloc.h>
#endif

// include errno.h for MinGW
#if defined(ZPL_COMPILER_GCC) || (defined(ZPL_COMPILER_TINYC) && defined(ZPL_SYSTEM_WINDOWS))
    #include <errno.h>
#endif

#if defined(ZPL_COMPILER_MINGW)
    #ifdef __MINGW32__
    #define _aligned_malloc __mingw_aligned_malloc
    #define _aligned_free  __mingw_aligned_free
    #endif //MINGW
#endif

ZPL_BEGIN_C_DECLS

char *zpl_alloc_str(zpl_allocator a, char const *str) {
    return zpl_alloc_str_len(a, str, zpl__strlen(str));
}

////////////////////////////////////////////////////////////////
//
// Custom Allocation
//
//

//
// Heap Allocator
//

#define ZPL_HEAP_STATS_MAGIC 0xDEADC0DE

typedef struct zpl__heap_stats {
    zpl_u32 magic;
    zpl_isize used_memory;
    zpl_isize alloc_count;
} zpl__heap_stats;

zpl_global zpl__heap_stats zpl__heap_stats_info;

void zpl_heap_stats_init(void) {
    zpl_zero_item(&zpl__heap_stats_info);
    zpl__heap_stats_info.magic = ZPL_HEAP_STATS_MAGIC;
}
zpl_isize zpl_heap_stats_used_memory(void) {
    ZPL_ASSERT_MSG(zpl__heap_stats_info.magic == ZPL_HEAP_STATS_MAGIC, "zpl_heap_stats is not initialised yet, call zpl_heap_stats_init first!");
    return zpl__heap_stats_info.used_memory;
}
zpl_isize zpl_heap_stats_alloc_count(void) {
    ZPL_ASSERT_MSG(zpl__heap_stats_info.magic == ZPL_HEAP_STATS_MAGIC, "zpl_heap_stats is not initialised yet, call zpl_heap_stats_init first!");
    return zpl__heap_stats_info.alloc_count;
}
void zpl_heap_stats_check(void) {
    ZPL_ASSERT_MSG(zpl__heap_stats_info.magic == ZPL_HEAP_STATS_MAGIC, "zpl_heap_stats is not initialised yet, call zpl_heap_stats_init first!");
    ZPL_ASSERT(zpl__heap_stats_info.used_memory == 0);
    ZPL_ASSERT(zpl__heap_stats_info.alloc_count == 0);
}

typedef struct zpl__heap_alloc_info {
    zpl_isize size;
    void *physical_start;
} zpl__heap_alloc_info;

ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc) {
    void *ptr = NULL;
    zpl_unused(allocator_data);
    zpl_unused(old_size);
    if (!alignment) alignment = ZPL_DEFAULT_MEMORY_ALIGNMENT;

    #ifdef ZPL_HEAP_ANALYSIS
        zpl_isize alloc_info_size = zpl_size_of(zpl__heap_alloc_info);
        zpl_isize alloc_info_remainder = (alloc_info_size % alignment);
        zpl_isize track_size = zpl_max(alloc_info_size, alignment) + alloc_info_remainder;
        switch (type) {
            case ZPL_ALLOCATION_FREE: {
                if (!old_memory) break;
                zpl__heap_alloc_info *alloc_info = cast(zpl__heap_alloc_info *)(old_memory - alloc_info_size);
                zpl__heap_stats_info.used_memory -= alloc_info->size;
                zpl__heap_stats_info.alloc_count--;
                old_memory = alloc_info->physical_start;
            } break;
            case ZPL_ALLOCATION_ALLOC: {
                size += track_size;
            } break;
            default: break;
        }
    #endif

    switch (type) {
#if defined(ZPL_COMPILER_MSVC) || (defined(ZPL_COMPILER_GCC) && defined(ZPL_SYSTEM_WINDOWS)) || (defined(ZPL_COMPILER_TINYC) && defined(ZPL_SYSTEM_WINDOWS))
        case ZPL_ALLOCATION_ALLOC:
        ptr = _aligned_malloc(size, alignment);
        if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        break;
        case ZPL_ALLOCATION_FREE: _aligned_free(old_memory); break;
        case ZPL_ALLOCATION_RESIZE: ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment); break;

#elif defined(ZPL_SYSTEM_LINUX) && !defined(ZPL_CPU_ARM) && !defined(ZPL_COMPILER_TINYC)
        case ZPL_ALLOCATION_ALLOC: {
            ptr = aligned_alloc(alignment, (size + alignment - 1) & ~(alignment - 1));

            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) { zpl_zero_size(ptr, size); }
        } break;

        case ZPL_ALLOCATION_FREE: {
            free(old_memory);
        } break;

        case ZPL_ALLOCATION_RESIZE: {
            zpl_allocator a = zpl_heap_allocator();
            ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
        } break;
#else
        case ZPL_ALLOCATION_ALLOC: {
            posix_memalign(&ptr, alignment, size);

            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) { zpl_zero_size(ptr, size); }
        } break;

        case ZPL_ALLOCATION_FREE: {
            free(old_memory);
        } break;

        case ZPL_ALLOCATION_RESIZE: {
            zpl_allocator a = zpl_heap_allocator( );
            ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
        } break;
#endif

        case ZPL_ALLOCATION_FREE_ALL: break;
    }

    #ifdef ZPL_HEAP_ANALYSIS
        switch (type) {
            case ZPL_ALLOCATION_ALLOC: {
                zpl__heap_alloc_info alloc_info_ = {0};
                zpl__heap_alloc_info *alloc_info = (ptr + alloc_info_remainder);
                *alloc_info = alloc_info_;
                alloc_info->size = size - track_size;
                alloc_info->physical_start = ptr;
                ptr = cast(void*)(alloc_info + 1);
                zpl__heap_stats_info.used_memory += alloc_info->size;
                zpl__heap_stats_info.alloc_count++;
            } break;
            default: break;
        }
    #endif

    return ptr;
}

//
// Arena Allocator
//

ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc) {
    zpl_arena *arena = cast(zpl_arena *) allocator_data;
    void *ptr = NULL;

    zpl_unused(old_size);

    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            void *end = zpl_pointer_add(arena->physical_start, arena->total_allocated);
            zpl_isize total_size = size + alignment;

            // NOTE: Out of memory
            if (arena->total_allocated + total_size > cast(zpl_isize) arena->total_size) {
                zpl__printf_err("%s", "Arena out of memory\n");
                return NULL;
            }

            ptr = zpl_align_forward(end, alignment);
            arena->total_allocated += total_size;
            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        } break;

        case ZPL_ALLOCATION_FREE:
        // NOTE: Free all at once
        // Use Temp_Arena_Memory if you want to free a block
        break;

        case ZPL_ALLOCATION_FREE_ALL: arena->total_allocated = 0; break;

        case ZPL_ALLOCATION_RESIZE: {
            // TODO: Check if ptr is on top of stack and just extend
            zpl_allocator a = zpl_arena_allocator(arena);
            ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
        } break;
    }
    return ptr;
}

//
// Pool Allocator
//

void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size, zpl_isize block_align) {
    zpl_isize actual_block_size, pool_size, block_index;
    void *data, *curr;
    zpl_uintptr *end;

    zpl_zero_item(pool);

    pool->backing = backing;
    pool->block_size = block_size;
    pool->block_align = block_align;
    pool->num_blocks = num_blocks;

    actual_block_size = block_size + block_align;
    pool_size = num_blocks * actual_block_size;

    data = zpl_alloc_align(backing, pool_size, block_align);

    // NOTE: Init intrusive freelist
    curr = data;
    for (block_index = 0; block_index < num_blocks - 1; block_index++) {
        zpl_uintptr *next = cast(zpl_uintptr *) curr;
        *next = cast(zpl_uintptr) curr + actual_block_size;
        curr = zpl_pointer_add(curr, actual_block_size);
    }

    end = cast(zpl_uintptr *) curr;
    *end = cast(zpl_uintptr) NULL;

    pool->physical_start = data;
    pool->free_list = data;
}

ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc) {
    zpl_pool *pool = cast(zpl_pool *) allocator_data;
    void *ptr = NULL;

    zpl_unused(old_size);

    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            zpl_uintptr next_free;
            ZPL_ASSERT(size == pool->block_size);
            ZPL_ASSERT(alignment == pool->block_align);
            ZPL_ASSERT(pool->free_list != NULL);

            next_free = *cast(zpl_uintptr *) pool->free_list;
            ptr = pool->free_list;
            pool->free_list = cast(void *) next_free;
            pool->total_size += pool->block_size;
            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        } break;

        case ZPL_ALLOCATION_FREE: {
            zpl_uintptr *next;
            if (old_memory == NULL) return NULL;

            next = cast(zpl_uintptr *) old_memory;
            *next = cast(zpl_uintptr) pool->free_list;
            pool->free_list = old_memory;
            pool->total_size -= pool->block_size;
        } break;

        case ZPL_ALLOCATION_FREE_ALL: {
            zpl_isize actual_block_size, block_index;
            void *curr;
            zpl_uintptr *end;

            actual_block_size = pool->block_size + pool->block_align;
            pool->total_size = 0;

            // NOTE: Init intrusive freelist
            curr = pool->physical_start;
            for (block_index = 0; block_index < pool->num_blocks - 1; block_index++) {
                zpl_uintptr *next = cast(zpl_uintptr *) curr;
                *next = cast(zpl_uintptr) curr + actual_block_size;
                curr = zpl_pointer_add(curr, actual_block_size);
            }

            end = cast(zpl_uintptr *) curr;
            *end = cast(zpl_uintptr) NULL;
            pool->free_list = pool->physical_start;
        } break;

        case ZPL_ALLOCATION_RESIZE:
        // NOTE: Cannot resize
        ZPL_PANIC("You cannot resize something allocated by with a pool.");
        break;
    }

    return ptr;
}


//
// Scratch Memory Allocator
//

void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, zpl_isize size) {
    s->physical_start = start;
    s->total_size = size;
    s->alloc_point = start;
    s->free_point = start;
}

zpl_b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr) {
    if (s->free_point == s->alloc_point) return false;
    if (s->alloc_point > s->free_point) return ptr >= s->free_point && ptr < s->alloc_point;
    return ptr >= s->free_point || ptr < s->alloc_point;
}

zpl_allocator zpl_scratch_allocator(zpl_scratch_memory *s) {
    zpl_allocator a;
    a.proc = zpl_scratch_allocator_proc;
    a.data = s;
    return a;
}

ZPL_ALLOCATOR_PROC(zpl_scratch_allocator_proc) {
    zpl_scratch_memory *s = cast(zpl_scratch_memory *) allocator_data;
    void *ptr = NULL;
    ZPL_ASSERT_NOT_NULL(s);

    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            void *pt = s->alloc_point;
            zpl_allocation_header_ev *header = cast(zpl_allocation_header_ev *) pt;
            void *data = zpl_align_forward(header + 1, alignment);
            void *end = zpl_pointer_add(s->physical_start, s->total_size);

            ZPL_ASSERT(alignment % 4 == 0);
            size = ((size + 3) / 4) * 4;
            pt = zpl_pointer_add(pt, size);

            // NOTE: Wrap around
            if (pt > end) {
                header->size = zpl_pointer_diff(header, end) | ZPL_ISIZE_HIGH_BIT;
                pt = s->physical_start;
                header = cast(zpl_allocation_header_ev *) pt;
                data = zpl_align_forward(header + 1, alignment);
                pt = zpl_pointer_add(pt, size);
            }

            if (!zpl_scratch_memory_is_in_use(s, pt)) {
                zpl_allocation_header_fill(header, pt, zpl_pointer_diff(header, pt));
                s->alloc_point = cast(zpl_u8 *) pt;
                ptr = data;
            }

            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        } break;

        case ZPL_ALLOCATION_FREE: {
            if (old_memory) {
                void *end = zpl_pointer_add(s->physical_start, s->total_size);
                if (old_memory < s->physical_start || old_memory >= end) {
                    ZPL_ASSERT(false);
                } else {
                    // NOTE: Mark as free
                    zpl_allocation_header_ev *h = zpl_allocation_header(old_memory);
                    ZPL_ASSERT((h->size & ZPL_ISIZE_HIGH_BIT) == 0);
                    h->size = h->size | ZPL_ISIZE_HIGH_BIT;

                    while (s->free_point != s->alloc_point) {
                        zpl_allocation_header_ev *header = cast(zpl_allocation_header_ev *) s->free_point;
                        if ((header->size & ZPL_ISIZE_HIGH_BIT) == 0) break;

                        s->free_point = zpl_pointer_add(s->free_point, h->size & (~ZPL_ISIZE_HIGH_BIT));
                        if (s->free_point == end) s->free_point = s->physical_start;
                    }
                }
            }
        } break;

        case ZPL_ALLOCATION_FREE_ALL:
        s->alloc_point = s->physical_start;
        s->free_point = s->physical_start;
        break;

        case ZPL_ALLOCATION_RESIZE:
        ptr = zpl_default_resize_align(zpl_scratch_allocator(s), old_memory, old_size, size, alignment);
        break;
    }

    return ptr;
}

//
// Stack Memory Allocator
//
ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc) {
    zpl_stack_memory *s = cast(zpl_stack_memory *) allocator_data;
    void *ptr = NULL;
    ZPL_ASSERT_NOT_NULL(s);
    zpl_unused(old_size);
    zpl_unused(flags);

    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            size += ZPL_STACK_ALLOC_OFFSET;
            zpl_u64 alloc_offset = s->allocated;

            void *curr =
                cast(zpl_u64 *) zpl_align_forward(cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);

            if (cast(zpl_u64 *) zpl_pointer_add(curr, size) > cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->total_size)) {
                if (s->backing.proc) {
                    void *old_start = s->physical_start;
                    s->physical_start =
                        zpl_resize_align(s->backing, s->physical_start, s->total_size, s->total_size + size, alignment);
                    curr = cast(zpl_u64 *)
                        zpl_align_forward(cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);
                    s->total_size = zpl_pointer_diff(old_start, s->physical_start);
                } else {
                    ZPL_PANIC("Can not resize stack's memory! Allocator not defined!");
                }
            }

            s->allocated = zpl_pointer_diff(s->physical_start, curr) + size;

            *(zpl_u64 *)curr = alloc_offset;
            curr = zpl_pointer_add(curr, ZPL_STACK_ALLOC_OFFSET);

            ptr = curr;
        } break;

        case ZPL_ALLOCATION_FREE: {
            if (old_memory) {
                void *curr = old_memory;
                curr = zpl_pointer_sub(curr, ZPL_STACK_ALLOC_OFFSET);

                zpl_u64 alloc_offset = *(zpl_u64 *)curr;
                s->allocated = (zpl_usize)alloc_offset;
            }
        } break;

        case ZPL_ALLOCATION_FREE_ALL: {
            s->allocated = 0;
        } break;

        case ZPL_ALLOCATION_RESIZE: {
            ZPL_PANIC("You cannot resize something allocated by a stack.");
        } break;
    }
    return ptr;
}

ZPL_END_C_DECLS
