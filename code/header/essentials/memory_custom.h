// file: header/essentials/memory_custom.h

////////////////////////////////////////////////////////////////
//
// Custom Allocation
//
//

ZPL_BEGIN_C_DECLS

typedef enum zplAllocationType {
    ZPL_ALLOCATION_ALLOC,
    ZPL_ALLOCATION_FREE,
    ZPL_ALLOCATION_FREE_ALL,
    ZPL_ALLOCATION_RESIZE,
} zplAllocationType;

// NOTE: This is useful so you can define an allocator of the same type and parameters
#define ZPL_ALLOCATOR_PROC(name)                                                                                       \
void *name(void *allocator_data, zplAllocationType type, zpl_isize size, zpl_isize alignment, void *old_memory,            \
zpl_isize old_size, zpl_u64 flags)
typedef ZPL_ALLOCATOR_PROC(zpl_allocator_proc);


typedef struct zpl_allocator {
    zpl_allocator_proc *proc;
    void *data;
} zpl_allocator;

typedef enum zplAllocatorFlag {
    ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO = ZPL_BIT(0),
} zplAllocatorFlag;

#ifndef ZPL_DEFAULT_MEMORY_ALIGNMENT
#define ZPL_DEFAULT_MEMORY_ALIGNMENT (2 * zpl_size_of(void *))
#endif

#ifndef ZPL_DEFAULT_ALLOCATOR_FLAGS
#define ZPL_DEFAULT_ALLOCATOR_FLAGS (ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO)
#endif

//! Allocate memory with specified alignment.
ZPL_DEF_INLINE void *zpl_alloc_align(zpl_allocator a, zpl_isize size, zpl_isize alignment);

//! Allocate memory with default alignment.
ZPL_DEF_INLINE void *zpl_alloc(zpl_allocator a, zpl_isize size);

//! Free allocated memory.
ZPL_DEF_INLINE void zpl_free(zpl_allocator a, void *ptr);

//! Free all memory allocated by an allocator.
ZPL_DEF_INLINE void zpl_free_all(zpl_allocator a);

//! Resize an allocated memory.
ZPL_DEF_INLINE void *zpl_resize(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size);

//! Resize an allocated memory with specified alignment.
ZPL_DEF_INLINE void *zpl_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment);

//! Allocate memory and copy data into it.
ZPL_DEF_INLINE void *zpl_alloc_copy(zpl_allocator a, void const *src, zpl_isize size);

//! Allocate memory with specified alignment and copy data into it.
ZPL_DEF_INLINE void *zpl_alloc_copy_align(zpl_allocator a, void const *src, zpl_isize size, zpl_isize alignment);

//! Allocate memory for null-terminated C-String.
ZPL_DEF char *zpl_alloc_str(zpl_allocator a, char const *str);

//! Allocate memory for C-String with specified size.
ZPL_DEF_INLINE char *zpl_alloc_str_len(zpl_allocator a, char const *str, zpl_isize len);

#ifndef zpl_alloc_item

//! Allocate memory for an item.
#define zpl_alloc_item(allocator_, Type) (Type *)zpl_alloc(allocator_, zpl_size_of(Type))

//! Allocate memory for an array of items.
#define zpl_alloc_array(allocator_, Type, count) (Type *)zpl_alloc(allocator_, zpl_size_of(Type) * (count))
#endif

//! Allocate/Resize memory using default options.

//! Use this if you don't need a "fancy" resize allocation
ZPL_DEF_INLINE void *zpl_default_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment);

//! The heap allocator backed by operating system's memory manager.
ZPL_DEF_INLINE zpl_allocator zpl_heap_allocator(void);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc);

#ifndef zpl_malloc

//! Helper to allocate memory using heap allocator.
#define zpl_malloc(sz) zpl_alloc(zpl_heap_allocator( ), sz)

//! Helper to free memory allocated by heap allocator.
#define zpl_mfree(ptr) zpl_free(zpl_heap_allocator( ), ptr)

//! Alias to heap allocator.
#define zpl_heap zpl_heap_allocator
#endif

//
// Arena Allocator
//

typedef struct zpl_arena {
    zpl_allocator backing;
    void *physical_start;
    zpl_isize total_size;
    zpl_isize total_allocated;
    zpl_isize temp_count;
} zpl_arena;

//! Initialize memory arena from existing memory region.
ZPL_DEF_INLINE void zpl_arena_init_from_memory(zpl_arena *arena, void *start, zpl_isize size);

//! Initialize memory arena using existing memory allocator.
ZPL_DEF_INLINE void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, zpl_isize size);

//! Initialize memory arena within an existing parent memory arena.
ZPL_DEF_INLINE void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, zpl_isize size);

//! Release the memory used by memory arena.
ZPL_DEF_INLINE void zpl_arena_free(zpl_arena *arena);


//! Retrieve memory arena's aligned allocation address.
ZPL_DEF_INLINE zpl_isize zpl_arena_alignment_of(zpl_arena *arena, zpl_isize alignment);

//! Retrieve memory arena's remaining size.
ZPL_DEF_INLINE zpl_isize zpl_arena_size_remaining(zpl_arena *arena, zpl_isize alignment);

//! Check whether memory arena has any temporary snapshots.
ZPL_DEF_INLINE void zpl_arena_check(zpl_arena *arena);

//! Allocation Types: alloc, free_all, resize
ZPL_DEF_INLINE zpl_allocator zpl_arena_allocator(zpl_arena *arena);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc);


typedef struct zpl_temp_arena_memory {
    zpl_arena *arena;
    zpl_isize original_count;
} zpl_temp_arena_memory;

//! Capture a snapshot of used memory in a memory arena.
ZPL_DEF_INLINE zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena);

//! Reset memory arena's usage by a captured snapshot.
ZPL_DEF_INLINE void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp_mem);

//
// Pool Allocator
//


typedef struct zpl_pool {
    zpl_allocator backing;
    void *physical_start;
    void *free_list;
    zpl_isize block_size;
    zpl_isize block_align;
    zpl_isize total_size;
    zpl_isize num_blocks;
} zpl_pool;


//! Initialize pool allocator.
ZPL_DEF_INLINE void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size);

//! Initialize pool allocator with specific block alignment.
ZPL_DEF void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size,
                                 zpl_isize block_align);

//! Release the resources used by pool allocator.
ZPL_DEF_INLINE void zpl_pool_free(zpl_pool *pool);

//! Allocation Types: alloc, free
ZPL_DEF_INLINE zpl_allocator zpl_pool_allocator(zpl_pool *pool);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc);


typedef struct zpl_allocation_header_ev {
    zpl_isize size;
} zpl_allocation_header_ev;

ZPL_DEF_INLINE zpl_allocation_header_ev *zpl_allocation_header(void *data);
ZPL_DEF_INLINE void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, zpl_isize size);

#if defined(ZPL_ARCH_32_BIT)
#define ZPL_ISIZE_HIGH_BIT 0x80000000
#elif defined(ZPL_ARCH_64_BIT)
#define ZPL_ISIZE_HIGH_BIT 0x8000000000000000ll
#else
#error
#endif

//
// Scratch Memory Allocator - Ring Buffer Based Arena
//


typedef struct zpl_scratch_memory {
    void *physical_start;
    zpl_isize total_size;
    void *alloc_point;
    void *free_point;
} zpl_scratch_memory;

//! Initialize ring buffer arena.
ZPL_DEF void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, zpl_isize size);

//! Check whether ring buffer arena is in use.
ZPL_DEF zpl_b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr);

//! Allocation Types: alloc, free, free_all, resize
ZPL_DEF zpl_allocator zpl_scratch_allocator(zpl_scratch_memory *s);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_scratch_allocator_proc);

//
// Stack Memory Allocator
//


typedef struct zpl_stack_memory {
    zpl_allocator backing;

    void *physical_start;
    zpl_usize total_size;
    zpl_usize allocated;
} zpl_stack_memory;

//! Initialize stack allocator from existing memory.
ZPL_DEF_INLINE void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, zpl_isize size);

//! Initialize stack allocator using existing memory allocator.
ZPL_DEF_INLINE void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, zpl_isize size);

//! Check whether stack allocator is in use.
ZPL_DEF_INLINE zpl_b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr);

//! Release the resources used by stack allocator.
ZPL_DEF_INLINE void zpl_stack_memory_free(zpl_stack_memory *s);

//! Allocation Types: alloc, free, free_all
ZPL_DEF_INLINE zpl_allocator zpl_stack_allocator(zpl_stack_memory *s);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc);

// TODO: Fixed heap allocator
// TODO: General heap allocator. Maybe a TCMalloc like clone?


/* inlines */

ZPL_IMPL_INLINE void *zpl_alloc_align(zpl_allocator a, zpl_isize size, zpl_isize alignment) {
    return a.proc(a.data, ZPL_ALLOCATION_ALLOC, size, alignment, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
ZPL_IMPL_INLINE void *zpl_alloc(zpl_allocator a, zpl_isize size) {
    return zpl_alloc_align(a, size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}
ZPL_IMPL_INLINE void zpl_free(zpl_allocator a, void *ptr) {
    if (ptr != NULL) a.proc(a.data, ZPL_ALLOCATION_FREE, 0, 0, ptr, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
ZPL_IMPL_INLINE void zpl_free_all(zpl_allocator a) {
    a.proc(a.data, ZPL_ALLOCATION_FREE_ALL, 0, 0, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
ZPL_IMPL_INLINE void *zpl_resize(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size) {
    return zpl_resize_align(a, ptr, old_size, new_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}
ZPL_IMPL_INLINE void *zpl_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment) {
    return a.proc(a.data, ZPL_ALLOCATION_RESIZE, new_size, alignment, ptr, old_size, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}

ZPL_IMPL_INLINE void *zpl_alloc_copy(zpl_allocator a, void const *src, zpl_isize size) {
    return zpl_memcopy(zpl_alloc(a, size), src, size);
}
ZPL_IMPL_INLINE void *zpl_alloc_copy_align(zpl_allocator a, void const *src, zpl_isize size, zpl_isize alignment) {
    return zpl_memcopy(zpl_alloc_align(a, size, alignment), src, size);
}

ZPL_IMPL_INLINE char *zpl_alloc_str_len(zpl_allocator a, char const *str, zpl_isize len) {
    char *result;
    result = cast(char *) zpl_alloc_copy(a, str, len + 1);
    result[len] = '\0';
    return result;
}

ZPL_IMPL_INLINE void *zpl_default_resize_align(zpl_allocator a, void *old_memory, zpl_isize old_size, zpl_isize new_size,
                                          zpl_isize alignment) {
    if (!old_memory) return zpl_alloc_align(a, new_size, alignment);

    if (new_size == 0) {
        zpl_free(a, old_memory);
        return NULL;
    }

    if (new_size < old_size) new_size = old_size;

    if (old_size == new_size) {
        return old_memory;
    } else {
        void *new_memory = zpl_alloc_align(a, new_size, alignment);
        if (!new_memory) return NULL;
        zpl_memmove(new_memory, old_memory, zpl_min(new_size, old_size));
        zpl_free(a, old_memory);
        return new_memory;
    }
}


//
// Heap Allocator
//

ZPL_IMPL_INLINE zpl_allocator zpl_heap_allocator(void) {
    zpl_allocator a;
    a.proc = zpl_heap_allocator_proc;
    a.data = NULL;
    return a;
}

//
// Arena Allocator
//

ZPL_IMPL_INLINE void zpl_arena_init_from_memory(zpl_arena *arena, void *start, zpl_isize size) {
    arena->backing.proc = NULL;
    arena->backing.data = NULL;
    arena->physical_start = start;
    arena->total_size = size;
    arena->total_allocated = 0;
    arena->temp_count = 0;
}

ZPL_IMPL_INLINE void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, zpl_isize size) {
    arena->backing = backing;
    arena->physical_start = zpl_alloc(backing, size); // NOTE: Uses default alignment
    arena->total_size = size;
    arena->total_allocated = 0;
    arena->temp_count = 0;
}

ZPL_IMPL_INLINE void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, zpl_isize size) {
    zpl_arena_init_from_allocator(arena, zpl_arena_allocator(parent_arena), size);
}

ZPL_IMPL_INLINE void zpl_arena_free(zpl_arena *arena) {
    if (arena->backing.proc) {
        zpl_free(arena->backing, arena->physical_start);
        arena->physical_start = NULL;
    }
}

ZPL_IMPL_INLINE zpl_isize zpl_arena_alignment_of(zpl_arena *arena, zpl_isize alignment) {
    zpl_isize alignment_offset, result_pointer, mask;
    ZPL_ASSERT(zpl_is_power_of_two(alignment));

    alignment_offset = 0;
    result_pointer = cast(zpl_isize) arena->physical_start + arena->total_allocated;
    mask = alignment - 1;
    if (result_pointer & mask) alignment_offset = alignment - (result_pointer & mask);

    return alignment_offset;
}

ZPL_IMPL_INLINE zpl_isize zpl_arena_size_remaining(zpl_arena *arena, zpl_isize alignment) {
    zpl_isize result = arena->total_size - (arena->total_allocated + zpl_arena_alignment_of(arena, alignment));
    return result;
}

ZPL_IMPL_INLINE void zpl_arena_check(zpl_arena *arena) { ZPL_ASSERT(arena->temp_count == 0); }

ZPL_IMPL_INLINE zpl_allocator zpl_arena_allocator(zpl_arena *arena) {
    zpl_allocator allocator;
    allocator.proc = zpl_arena_allocator_proc;
    allocator.data = arena;
    return allocator;
}

ZPL_IMPL_INLINE zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena) {
    zpl_temp_arena_memory tmp;
    tmp.arena = arena;
    tmp.original_count = arena->total_allocated;
    arena->temp_count++;
    return tmp;
}

ZPL_IMPL_INLINE void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp) {
    ZPL_ASSERT(tmp.arena->total_allocated >= tmp.original_count);
    ZPL_ASSERT(tmp.arena->temp_count > 0);
    tmp.arena->total_allocated = tmp.original_count;
    tmp.arena->temp_count--;
}

//
// Pool Allocator
//

ZPL_IMPL_INLINE void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size) {
    zpl_pool_init_align(pool, backing, num_blocks, block_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}

ZPL_IMPL_INLINE void zpl_pool_free(zpl_pool *pool) {
    if (pool->backing.proc) { zpl_free(pool->backing, pool->physical_start); }
}

ZPL_IMPL_INLINE zpl_allocator zpl_pool_allocator(zpl_pool *pool) {
    zpl_allocator allocator;
    allocator.proc = zpl_pool_allocator_proc;
    allocator.data = pool;
    return allocator;
}

ZPL_IMPL_INLINE zpl_allocation_header_ev *zpl_allocation_header(void *data) {
    zpl_isize *p = cast(zpl_isize *) data;
    while (p[-1] == cast(zpl_isize)(-1)) p--;
    return cast(zpl_allocation_header_ev *) p - 1;
}

ZPL_IMPL_INLINE void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, zpl_isize size) {
    zpl_isize *ptr;
    header->size = size;
    ptr = cast(zpl_isize *)(header + 1);
    while (cast(void *) ptr < data) *ptr++ = cast(zpl_isize)(-1);
}

//
// Stack Memory Allocator
//

#define ZPL_STACK_ALLOC_OFFSET sizeof(zpl_u64)
ZPL_STATIC_ASSERT(ZPL_STACK_ALLOC_OFFSET == 8, "ZPL_STACK_ALLOC_OFFSET != 8");

ZPL_IMPL_INLINE void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, zpl_isize size) {
    s->physical_start = start;
    s->total_size = size;
    s->allocated = 0;
}

ZPL_IMPL_INLINE void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, zpl_isize size) {
    s->backing = backing;
    s->physical_start = zpl_alloc(backing, size);
    s->total_size = size;
    s->allocated = 0;
}

ZPL_IMPL_INLINE zpl_b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr) {
    if (s->allocated == 0) return false;

    if (ptr > s->physical_start && ptr < zpl_pointer_add(s->physical_start, s->total_size)) { return true; }

    return false;
}

ZPL_IMPL_INLINE void zpl_stack_memory_free(zpl_stack_memory *s) {
    if (s->backing.proc) {
        zpl_free(s->backing, s->physical_start);
        s->physical_start = NULL;
    }
}

ZPL_IMPL_INLINE zpl_allocator zpl_stack_allocator(zpl_stack_memory *s) {
    zpl_allocator a;
    a.proc = zpl_stack_allocator_proc;
    a.data = s;
    return a;
}

ZPL_END_C_DECLS
