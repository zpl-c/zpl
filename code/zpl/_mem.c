////////////////////////////////////////////////////////////////
//
// Memory
//
//

/**
 * a normal member taking two arguments and returning an integer value.
 * @param a an integer argument.
 * @param s a constant character pointer.
 * @see Javadoc_Test()
 * @see ~Javadoc_Test()
 * @see testMeToo()
 * @see publicVar()
 * @return The test results
 */
ZPL_DEF b32 zpl_is_power_of_two(isize x);

ZPL_DEF void *zpl_align_forward(void *ptr, isize alignment);

ZPL_DEF void *zpl_pointer_add(void *ptr, isize bytes);
ZPL_DEF void *zpl_pointer_sub(void *ptr, isize bytes);
ZPL_DEF void const *zpl_pointer_add_const(void const *ptr, isize bytes);
ZPL_DEF void const *zpl_pointer_sub_const(void const *ptr, isize bytes);
ZPL_DEF isize zpl_pointer_diff(void const *begin, void const *end);

#define zpl_ptr_add zpl_pointer_add
#define zpl_ptr_sub zpl_pointer_sub
#define zpl_ptr_add_const zpl_pointer_add_const
#define zpl_ptr_sub_const zpl_pointer_sub_const
#define zpl_ptr_diff zpl_pointer_diff

ZPL_DEF void zpl_zero_size(void *ptr, isize size);
#ifndef zpl_zero_item
#define zpl_zero_item(t) zpl_zero_size((t), zpl_size_of(*(t))) // NOTE: Pass pointer of struct
#define zpl_zero_array(a, count) zpl_zero_size((a), zpl_size_of(*(a)) * count)
#endif

ZPL_DEF void *zpl_memcopy(void *dest, void const *source, isize size);
ZPL_DEF void *zpl_memmove(void *dest, void const *source, isize size);
ZPL_DEF void *zpl_memset(void *data, u8 byte_value, isize size);
ZPL_DEF i32 zpl_memcompare(void const *s1, void const *s2, isize size);
ZPL_DEF void zpl_memswap(void *i, void *j, isize size);
ZPL_DEF void const *zpl_memchr(void const *data, u8 byte_value, isize size);
ZPL_DEF void const *zpl_memrchr(void const *data, u8 byte_value, isize size);

#ifndef zpl_memcopy_array
#define zpl_memcopy_array(dst, src, count) zpl_memcopy((dst), (src), zpl_size_of(*(dst)) * (count))
#endif

#ifndef zpl_memmove_array
#define zpl_memmove_array(dst, src, count) zpl_memmove((dst), (src), zpl_size_of(*(dst)) * (count))
#endif

#ifndef ZPL_BIT_CAST
#define ZPL_BIT_CAST(dest, source)                                                                                     \
do {                                                                                                               \
    ZPL_STATIC_ASSERT(zpl_size_of(*(dest)) <= zpl_size_of(source));                                                \
    zpl_memcopy((dest), &(source), zpl_size_of(*dest));                                                            \
} while (0)
#endif

#ifndef zpl_kilobytes
#define zpl_kilobytes(x) ((x) * (i64)(1024))
#define zpl_megabytes(x) (zpl_kilobytes(x) * (i64)(1024))
#define zpl_gigabytes(x) (zpl_megabytes(x) * (i64)(1024))
#define zpl_terabytes(x) (zpl_gigabytes(x) * (i64)(1024))
#endif

////////////////////////////////////////////////////////////////
//
// Virtual Memory
//
//

#define zpl_virtual_memory_t zpl_virtual_memory
typedef struct zpl_virtual_memory {
    void *data;
    isize size;
} zpl_virtual_memory;

ZPL_DEF zpl_virtual_memory zpl_vm(void *data, isize size);
ZPL_DEF zpl_virtual_memory zpl_vm_alloc(void *addr, isize size);
ZPL_DEF b32 zpl_vm_free(zpl_virtual_memory vm);
ZPL_DEF zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, isize lead_size, isize size);
ZPL_DEF b32 zpl_vm_purge(zpl_virtual_memory vm);
ZPL_DEF isize zpl_virtual_memory_page_size(isize *alignment_out);

////////////////////////////////////////////////////////////////
//
// Custom Allocation
//
//

typedef enum zplAllocationType {
    ZPL_ALLOCATION_ALLOC,
    ZPL_ALLOCATION_FREE,
    ZPL_ALLOCATION_FREE_ALL,
    ZPL_ALLOCATION_RESIZE,
} zplAllocationType;

// NOTE: This is useful so you can define an allocator of the same type and parameters
#define ZPL_ALLOCATOR_PROC(name)                                                                                       \
void *name(void *allocator_data, zplAllocationType type, isize size, isize alignment, void *old_memory,            \
isize old_size, u64 flags)
typedef ZPL_ALLOCATOR_PROC(zpl_allocator_proc);

#define zpl_allocator_t zpl_allocator
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

ZPL_DEF void *zpl_alloc_align(zpl_allocator a, isize size, isize alignment);
ZPL_DEF void *zpl_alloc(zpl_allocator a, isize size);
ZPL_DEF void zpl_free(zpl_allocator a, void *ptr);
ZPL_DEF void zpl_free_all(zpl_allocator a);
ZPL_DEF void *zpl_resize(zpl_allocator a, void *ptr, isize old_size, isize new_size);
ZPL_DEF void *zpl_resize_align(zpl_allocator a, void *ptr, isize old_size, isize new_size, isize alignment);

ZPL_DEF void *zpl_alloc_copy(zpl_allocator a, void const *src, isize size);
ZPL_DEF void *zpl_alloc_copy_align(zpl_allocator a, void const *src, isize size, isize alignment);
ZPL_DEF char *zpl_alloc_str(zpl_allocator a, char const *str);
ZPL_DEF char *zpl_alloc_str_len(zpl_allocator a, char const *str, isize len);

#ifndef zpl_alloc_item
#define zpl_alloc_item(allocator_, Type) (Type *)zpl_alloc(allocator_, zpl_size_of(Type))
#define zpl_alloc_array(allocator_, Type, count) (Type *)zpl_alloc(allocator_, zpl_size_of(Type) * (count))
#endif

// NOTE: Use this if you don't need a "fancy" resize allocation
ZPL_DEF void *zpl_default_resize_align(zpl_allocator a, void *ptr, isize old_size, isize new_size, isize alignment);

ZPL_DEF zpl_allocator zpl_heap_allocator(void);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc);

#ifndef zpl_malloc
#define zpl_malloc(sz) zpl_alloc(zpl_heap_allocator( ), sz)
#define zpl_mfree(ptr) zpl_free(zpl_heap_allocator( ), ptr)
#define zpl_heap zpl_heap_allocator
#endif

//
// Arena Allocator
//
#define zpl_arena_t zpl_arena
typedef struct zpl_arena {
    zpl_allocator backing;
    void *physical_start;
    isize total_size;
    isize total_allocated;
    isize temp_count;
} zpl_arena;

ZPL_DEF void zpl_arena_init_from_memory(zpl_arena *arena, void *start, isize size);
ZPL_DEF void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, isize size);
ZPL_DEF void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, isize size);
ZPL_DEF void zpl_arena_free(zpl_arena *arena);

ZPL_DEF isize zpl_arena_alignment_of(zpl_arena *arena, isize alignment);
ZPL_DEF isize zpl_arena_size_remaining(zpl_arena *arena, isize alignment);
ZPL_DEF void zpl_arena_check(zpl_arena *arena);

// Allocation Types: alloc, free_all, resize
ZPL_DEF zpl_allocator zpl_arena_allocator(zpl_arena *arena);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc);

#define zpl_temp_arena_memory_t zpl_temp_arena_memory
typedef struct zpl_temp_arena_memory {
    zpl_arena *arena;
    isize original_count;
} zpl_temp_arena_memory;

ZPL_DEF zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena);
ZPL_DEF void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp_mem);

//
// Pool Allocator
//

#define zpl_pool_t zpl_pool
typedef struct zpl_pool {
    zpl_allocator backing;
    void *physical_start;
    void *free_list;
    isize block_size;
    isize block_align;
    isize total_size;
} zpl_pool;

ZPL_DEF void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, isize num_blocks, isize block_size);
ZPL_DEF void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, isize num_blocks, isize block_size,
                                 isize block_align);
ZPL_DEF void zpl_pool_free(zpl_pool *pool);

// Allocation Types: alloc, free
ZPL_DEF zpl_allocator zpl_pool_allocator(zpl_pool *pool);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc);

#define zpl_allocation_header_ev_t zpl_allocation_header_ev
typedef struct zpl_allocation_header_ev {
    isize size;
} zpl_allocation_header_ev;

ZPL_DEF zpl_allocation_header_ev *zpl_allocation_header(void *data);
ZPL_DEF void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, isize size);

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

#define zpl_scratch_memory_t zpl_scratch_memory
typedef struct zpl_scratch_memory {
    void *physical_start;
    isize total_size;
    void *alloc_point;
    void *free_point;
} zpl_scratch_memory;

ZPL_DEF void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, isize size);
ZPL_DEF b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr);

// Allocation Types: alloc, free, free_all, resize
ZPL_DEF zpl_allocator zpl_scratch_allocator(zpl_scratch_memory *s);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_scratch_allocator_proc);

//
// Stack Memory Allocator
//

#define zpl_stack_memory_t zpl_stack_memory
typedef struct zpl_stack_memory {
    zpl_allocator backing;
    
    void *physical_start;
    usize total_size;
    usize allocated;
} zpl_stack_memory;

ZPL_DEF void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, isize size);
ZPL_DEF void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, isize size);
ZPL_DEF b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr);
ZPL_DEF void zpl_stack_memory_free(zpl_stack_memory *s);

// Allocation Types: alloc, free, free_all, resize
ZPL_DEF zpl_allocator zpl_stack_allocator(zpl_stack_memory *s);
ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc);

// TODO: Fixed heap allocator
// TODO: General heap allocator. Maybe a TCMalloc like clone?

//$$

b32 zpl_is_power_of_two(isize x) {
    if (x <= 0) return false;
    return !(x & (x - 1));
}

zpl_inline void *zpl_align_forward(void *ptr, isize alignment) {
    uintptr p;
    
    ZPL_ASSERT(zpl_is_power_of_two(alignment));
    
    p = cast(uintptr) ptr;
    return cast(void *)((p + (alignment - 1)) & ~(alignment - 1));
}

zpl_inline void *zpl_pointer_add(void *ptr, isize bytes) { return cast(void *)(cast(u8 *) ptr + bytes); }
zpl_inline void *zpl_pointer_sub(void *ptr, isize bytes) { return cast(void *)(cast(u8 *) ptr - bytes); }
zpl_inline void const *zpl_pointer_add_const(void const *ptr, isize bytes) {
    return cast(void const *)(cast(u8 const *) ptr + bytes);
}
zpl_inline void const *zpl_pointer_sub_const(void const *ptr, isize bytes) {
    return cast(void const *)(cast(u8 const *) ptr - bytes);
}
zpl_inline isize zpl_pointer_diff(void const *begin, void const *end) {
    return cast(isize)(cast(u8 const *) end - cast(u8 const *) begin);
}

zpl_inline void zpl_zero_size(void *ptr, isize size) { zpl_memset(ptr, 0, size); }

#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(__movsb)
#endif

zpl_inline void *zpl_memcopy(void *dest, void const *source, isize n) {
    if (dest == NULL) { return NULL; }
    
    return memcpy(dest, source, n);
    
    // TODO: Re-work the whole method
#if 0
#if defined(_MSC_VER)
    __movsb(cast(u8 *) dest, cast(u8 *) source, n);
#elif defined(ZPL_CPU_X86) && !defined(ZPL_SYSTEM_EMSCRIPTEN)
    u8 *__dest8 = cast(u8 *) dest;
    u8 *__source8 = cast(u8 *) source;
    __asm__ __volatile__("rep movsb" : "+D"(__dest8), "+S"(__source8), "+c"(n) : : "memory");
#elif defined(ZPL_CPU_ARM)
    return memcpy(dest, source, n);
#else
    u8 *d = cast(u8 *) dest;
    u8 const *s = cast(u8 const *) source;
    u32 w, x;
    
    for (; cast(uintptr) s % 4 && n; n--) *d++ = *s++;
    
    if (cast(uintptr) d % 4 == 0) {
        for (; n >= 16; s += 16, d += 16, n -= 16) {
            *cast(u32 *)(d + 0) = *cast(u32 *)(s + 0);
            *cast(u32 *)(d + 4) = *cast(u32 *)(s + 4);
            *cast(u32 *)(d + 8) = *cast(u32 *)(s + 8);
            *cast(u32 *)(d + 12) = *cast(u32 *)(s + 12);
        }
        if (n & 8) {
            *cast(u32 *)(d + 0) = *cast(u32 *)(s + 0);
            *cast(u32 *)(d + 4) = *cast(u32 *)(s + 4);
            d += 8;
            s += 8;
        }
        if (n & 4) {
            *cast(u32 *)(d + 0) = *cast(u32 *)(s + 0);
            d += 4;
            s += 4;
        }
        if (n & 2) {
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 1) { *d = *s; }
        return dest;
    }
    
    if (n >= 32) {
#if __BYTE_ORDER == __BIG_ENDIAN
#define LS <<
#define RS >>
#else
#define LS >>
#define RS <<
#endif
        switch (cast(uintptr) d % 4) {
            case 1: {
                w = *cast(u32 *) s;
                *d++ = *s++;
                *d++ = *s++;
                *d++ = *s++;
                n -= 3;
                while (n > 16) {
                    x = *cast(u32 *)(s + 1);
                    *cast(u32 *)(d + 0) = (w LS 24) | (x RS 8);
                    w = *cast(u32 *)(s + 5);
                    *cast(u32 *)(d + 4) = (x LS 24) | (w RS 8);
                    x = *cast(u32 *)(s + 9);
                    *cast(u32 *)(d + 8) = (w LS 24) | (x RS 8);
                    w = *cast(u32 *)(s + 13);
                    *cast(u32 *)(d + 12) = (x LS 24) | (w RS 8);
                    
                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            case 2: {
                w = *cast(u32 *) s;
                *d++ = *s++;
                *d++ = *s++;
                n -= 2;
                while (n > 17) {
                    x = *cast(u32 *)(s + 2);
                    *cast(u32 *)(d + 0) = (w LS 16) | (x RS 16);
                    w = *cast(u32 *)(s + 6);
                    *cast(u32 *)(d + 4) = (x LS 16) | (w RS 16);
                    x = *cast(u32 *)(s + 10);
                    *cast(u32 *)(d + 8) = (w LS 16) | (x RS 16);
                    w = *cast(u32 *)(s + 14);
                    *cast(u32 *)(d + 12) = (x LS 16) | (w RS 16);
                    
                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            case 3: {
                w = *cast(u32 *) s;
                *d++ = *s++;
                n -= 1;
                while (n > 18) {
                    x = *cast(u32 *)(s + 3);
                    *cast(u32 *)(d + 0) = (w LS 8) | (x RS 24);
                    w = *cast(u32 *)(s + 7);
                    *cast(u32 *)(d + 4) = (x LS 8) | (w RS 24);
                    x = *cast(u32 *)(s + 11);
                    *cast(u32 *)(d + 8) = (w LS 8) | (x RS 24);
                    w = *cast(u32 *)(s + 15);
                    *cast(u32 *)(d + 12) = (x LS 8) | (w RS 24);
                    
                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            default: break; // NOTE: Do nowt!
        }
#undef LS
#undef RS
        if (n & 16) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 8) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 4) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 2) {
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 1) { *d = *s; }
    }
    
#endif
#endif
    
    return dest;
}

zpl_inline void *zpl_memmove(void *dest, void const *source, isize n) {
    if (dest == NULL) { return NULL; }
    
    u8 *d = cast(u8 *) dest;
    u8 const *s = cast(u8 const *) source;
    
    if (d == s) return d;
    if (s + n <= d || d + n <= s) // NOTE: Non-overlapping
        return zpl_memcopy(d, s, n);
    
    if (d < s) {
        if (cast(uintptr) s % zpl_size_of(isize) == cast(uintptr) d % zpl_size_of(isize)) {
            while (cast(uintptr) d % zpl_size_of(isize)) {
                if (!n--) return dest;
                *d++ = *s++;
            }
            while (n >= zpl_size_of(isize)) {
                *cast(isize *) d = *cast(isize *) s;
                n -= zpl_size_of(isize);
                d += zpl_size_of(isize);
                s += zpl_size_of(isize);
            }
        }
        for (; n; n--) *d++ = *s++;
    } else {
        if ((cast(uintptr) s % zpl_size_of(isize)) == (cast(uintptr) d % zpl_size_of(isize))) {
            while (cast(uintptr)(d + n) % zpl_size_of(isize)) {
                if (!n--) return dest;
                d[n] = s[n];
            }
            while (n >= zpl_size_of(isize)) {
                n -= zpl_size_of(isize);
                *cast(isize *)(d + n) = *cast(isize *)(s + n);
            }
        }
        while (n) n--, d[n] = s[n];
    }
    
    return dest;
}

zpl_inline void *zpl_memset(void *dest, u8 c, isize n) {
    if (dest == NULL) { return NULL; }
    
    u8 *s = cast(u8 *) dest;
    isize k;
    u32 c32 = ((u32)-1) / 255 * c;
    
    if (n == 0) return dest;
    s[0] = s[n - 1] = c;
    if (n < 3) return dest;
    s[1] = s[n - 2] = c;
    s[2] = s[n - 3] = c;
    if (n < 7) return dest;
    s[3] = s[n - 4] = c;
    if (n < 9) return dest;
    
    k = -cast(intptr) s & 3;
    s += k;
    n -= k;
    n &= -4;
    
    *cast(u32 *)(s + 0) = c32;
    *cast(u32 *)(s + n - 4) = c32;
    if (n < 9) return dest;
    *cast(u32 *)(s + 4) = c32;
    *cast(u32 *)(s + 8) = c32;
    *cast(u32 *)(s + n - 12) = c32;
    *cast(u32 *)(s + n - 8) = c32;
    if (n < 25) return dest;
    *cast(u32 *)(s + 12) = c32;
    *cast(u32 *)(s + 16) = c32;
    *cast(u32 *)(s + 20) = c32;
    *cast(u32 *)(s + 24) = c32;
    *cast(u32 *)(s + n - 28) = c32;
    *cast(u32 *)(s + n - 24) = c32;
    *cast(u32 *)(s + n - 20) = c32;
    *cast(u32 *)(s + n - 16) = c32;
    
    k = 24 + (cast(uintptr) s & 4);
    s += k;
    n -= k;
    
    {
        u64 c64 = (cast(u64) c32 << 32) | c32;
        while (n > 31) {
            *cast(u64 *)(s + 0) = c64;
            *cast(u64 *)(s + 8) = c64;
            *cast(u64 *)(s + 16) = c64;
            *cast(u64 *)(s + 24) = c64;
            
            n -= 32;
            s += 32;
        }
    }
    
    return dest;
}

zpl_inline i32 zpl_memcompare(void const *s1, void const *s2, isize size) {
    u8 const *s1p8 = cast(u8 const *) s1;
    u8 const *s2p8 = cast(u8 const *) s2;
    
    if (s1 == NULL || s2 == NULL) { return 0; }
    
    while (size--) {
        isize d;
        if ((d = (*s1p8++ - *s2p8++)) != 0) return cast(i32) d;
    }
    return 0;
}

void zpl_memswap(void *i, void *j, isize size) {
    if (i == j) return;
    
    if (size == 4) {
        zpl_swap(u32, *cast(u32 *) i, *cast(u32 *) j);
    } else if (size == 8) {
        zpl_swap(u64, *cast(u64 *) i, *cast(u64 *) j);
    } else if (size < 8) {
        u8 *a = cast(u8 *) i;
        u8 *b = cast(u8 *) j;
        if (a != b) {
            while (size--) { zpl_swap(u8, *a++, *b++); }
        }
    } else {
        char buffer[256];
        
        while (size > zpl_size_of(buffer)) {
            zpl_memswap(i, j, zpl_size_of(buffer));
            i = zpl_pointer_add(i, zpl_size_of(buffer));
            j = zpl_pointer_add(j, zpl_size_of(buffer));
            size -= zpl_size_of(buffer);
        }
        
        zpl_memcopy(buffer, i, size);
        zpl_memcopy(i, j, size);
        zpl_memcopy(j, buffer, size);
    }
}

#define ZPL__ONES (cast(usize) - 1 / U8_MAX)
#define ZPL__HIGHS (ZPL__ONES * (U8_MAX / 2 + 1))
#define ZPL__HAS_ZERO(x) (((x)-ZPL__ONES) & ~(x)&ZPL__HIGHS)

void const *zpl_memchr(void const *data, u8 c, isize n) {
    u8 const *s = cast(u8 const *) data;
    while ((cast(uintptr) s & (sizeof(usize) - 1)) && n && *s != c) {
        s++;
        n--;
    }
    if (n && *s != c) {
        isize const *w;
        isize k = ZPL__ONES * c;
        w = cast(isize const *) s;
        while (n >= zpl_size_of(isize) && !ZPL__HAS_ZERO(*w ^ k)) {
            w++;
            n -= zpl_size_of(isize);
        }
        s = cast(u8 const *) w;
        while (n && *s != c) {
            s++;
            n--;
        }
    }
    
    return n ? cast(void const *) s : NULL;
}

void const *zpl_memrchr(void const *data, u8 c, isize n) {
    u8 const *s = cast(u8 const *) data;
    while (n--) {
        if (s[n] == c) return cast(void const *)(s + n);
    }
    return NULL;
}

////////////////////////////////////////////////////////////////
//
// Virtual Memory
//
//

zpl_virtual_memory zpl_vm(void *data, isize size) {
    zpl_virtual_memory vm;
    vm.data = data;
    vm.size = size;
    return vm;
}

#if defined(ZPL_SYSTEM_WINDOWS)
zpl_inline zpl_virtual_memory zpl_vm_alloc(void *addr, isize size) {
    zpl_virtual_memory vm;
    ZPL_ASSERT(size > 0);
    vm.data = VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    vm.size = size;
    return vm;
}

zpl_inline b32 zpl_vm_free(zpl_virtual_memory vm) {
    MEMORY_BASIC_INFORMATION info;
    while (vm.size > 0) {
        if (VirtualQuery(vm.data, &info, zpl_size_of(info)) == 0) return false;
        if (info.BaseAddress != vm.data || info.AllocationBase != vm.data || info.State != MEM_COMMIT ||
            info.RegionSize > cast(usize) vm.size) {
            return false;
        }
        if (VirtualFree(vm.data, 0, MEM_RELEASE) == 0) return false;
        vm.data = zpl_pointer_add(vm.data, info.RegionSize);
        vm.size -= info.RegionSize;
    }
    return true;
}

zpl_inline zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, isize lead_size, isize size) {
    zpl_virtual_memory new_vm = { 0 };
    void *ptr;
    ZPL_ASSERT(vm.size >= lead_size + size);
    
    ptr = zpl_pointer_add(vm.data, lead_size);
    
    zpl_vm_free(vm);
    new_vm = zpl_vm_alloc(ptr, size);
    if (new_vm.data == ptr) return new_vm;
    if (new_vm.data) zpl_vm_free(new_vm);
    return new_vm;
}

zpl_inline b32 zpl_vm_purge(zpl_virtual_memory vm) {
    VirtualAlloc(vm.data, vm.size, MEM_RESET, PAGE_READWRITE);
    // NOTE: Can this really fail?
    return true;
}

isize zpl_virtual_memory_page_size(isize *alignment_out) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    if (alignment_out) *alignment_out = info.dwAllocationGranularity;
    return info.dwPageSize;
}

#else

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

zpl_inline zpl_virtual_memory zpl_vm_alloc(void *addr, isize size) {
    zpl_virtual_memory vm;
    ZPL_ASSERT(size > 0);
    vm.data = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    vm.size = size;
    return vm;
}

zpl_inline b32 zpl_vm_free(zpl_virtual_memory vm) {
    munmap(vm.data, vm.size);
    return true;
}

zpl_inline zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, isize lead_size, isize size) {
    void *ptr;
    isize trail_size;
    ZPL_ASSERT(vm.size >= lead_size + size);
    
    ptr = zpl_pointer_add(vm.data, lead_size);
    trail_size = vm.size - lead_size - size;
    
    if (lead_size != 0) zpl_vm_free(zpl_vm(vm.data, lead_size));
    if (trail_size != 0) zpl_vm_free(zpl_vm(ptr, trail_size));
    return zpl_vm(ptr, size);
}

zpl_inline b32 zpl_vm_purge(zpl_virtual_memory vm) {
    int err = madvise(vm.data, vm.size, MADV_DONTNEED);
    return err != 0;
}

isize zpl_virtual_memory_page_size(isize *alignment_out) {
    // TODO: Is this always true?
    isize result = cast(isize) sysconf(_SC_PAGE_SIZE);
    if (alignment_out) *alignment_out = result;
    return result;
}

#endif

zpl_inline void *zpl_alloc_align(zpl_allocator a, isize size, isize alignment) {
    return a.proc(a.data, ZPL_ALLOCATION_ALLOC, size, alignment, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
zpl_inline void *zpl_alloc(zpl_allocator a, isize size) {
    return zpl_alloc_align(a, size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}
zpl_inline void zpl_free(zpl_allocator a, void *ptr) {
    if (ptr != NULL) a.proc(a.data, ZPL_ALLOCATION_FREE, 0, 0, ptr, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
zpl_inline void zpl_free_all(zpl_allocator a) {
    a.proc(a.data, ZPL_ALLOCATION_FREE_ALL, 0, 0, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}
zpl_inline void *zpl_resize(zpl_allocator a, void *ptr, isize old_size, isize new_size) {
    return zpl_resize_align(a, ptr, old_size, new_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}
zpl_inline void *zpl_resize_align(zpl_allocator a, void *ptr, isize old_size, isize new_size, isize alignment) {
    return a.proc(a.data, ZPL_ALLOCATION_RESIZE, new_size, alignment, ptr, old_size, ZPL_DEFAULT_ALLOCATOR_FLAGS);
}

zpl_inline void *zpl_alloc_copy(zpl_allocator a, void const *src, isize size) {
    return zpl_memcopy(zpl_alloc(a, size), src, size);
}
zpl_inline void *zpl_alloc_copy_align(zpl_allocator a, void const *src, isize size, isize alignment) {
    return zpl_memcopy(zpl_alloc_align(a, size, alignment), src, size);
}

zpl_inline char *zpl_alloc_str(zpl_allocator a, char const *str) { return zpl_alloc_str_len(a, str, zpl_strlen(str)); }

zpl_inline char *zpl_alloc_str_len(zpl_allocator a, char const *str, isize len) {
    char *result;
    result = cast(char *) zpl_alloc_copy(a, str, len + 1);
    result[len] = '\0';
    return result;
}

zpl_inline void *zpl_default_resize_align(zpl_allocator a, void *old_memory, isize old_size, isize new_size,
                                          isize alignment) {
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

////////////////////////////////////////////////////////////////
//
// Custom Allocation
//
//

//
// Heap Allocator
//

zpl_inline zpl_allocator zpl_heap_allocator(void) {
    zpl_allocator a;
    a.proc = zpl_heap_allocator_proc;
    a.data = NULL;
    return a;
}

ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc) {
    void *ptr = NULL;
    zpl_unused(allocator_data);
    zpl_unused(old_size);
    // TODO: Throughly test!
    switch (type) {
#if defined(ZPL_COMPILER_MSVC) || (defined(ZPL_COMPILER_GCC) && defined(ZPL_SYSTEM_WINDOWS))
        case ZPL_ALLOCATION_ALLOC:
        ptr = _aligned_malloc(size, alignment);
        if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        break;
        case ZPL_ALLOCATION_FREE: _aligned_free(old_memory); break;
        case ZPL_ALLOCATION_RESIZE: ptr = _aligned_realloc(old_memory, size, alignment); break;
        
#elif defined(ZPL_SYSTEM_LINUX) && !defined(ZPL_CPU_ARM)
        case ZPL_ALLOCATION_ALLOC: {
            ptr = aligned_alloc(alignment, size);
            
            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) { zpl_zero_size(ptr, size); }
        } break;
        
        case ZPL_ALLOCATION_FREE: {
            free(old_memory);
        } break;
        
        case ZPL_ALLOCATION_RESIZE: {
            zpl_allocator a = zpl_heap_allocator( );
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
    
    return ptr;
}

//
// Arena Allocator
//

zpl_inline void zpl_arena_init_from_memory(zpl_arena *arena, void *start, isize size) {
    arena->backing.proc = NULL;
    arena->backing.data = NULL;
    arena->physical_start = start;
    arena->total_size = size;
    arena->total_allocated = 0;
    arena->temp_count = 0;
}

zpl_inline void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, isize size) {
    arena->backing = backing;
    arena->physical_start = zpl_alloc(backing, size); // NOTE: Uses default alignment
    arena->total_size = size;
    arena->total_allocated = 0;
    arena->temp_count = 0;
}

zpl_inline void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, isize size) {
    zpl_arena_init_from_allocator(arena, zpl_arena_allocator(parent_arena), size);
}

zpl_inline void zpl_arena_free(zpl_arena *arena) {
    if (arena->backing.proc) {
        zpl_free(arena->backing, arena->physical_start);
        arena->physical_start = NULL;
    }
}

zpl_inline isize zpl_arena_alignment_of(zpl_arena *arena, isize alignment) {
    isize alignment_offset, result_pointer, mask;
    ZPL_ASSERT(zpl_is_power_of_two(alignment));
    
    alignment_offset = 0;
    result_pointer = cast(isize) arena->physical_start + arena->total_allocated;
    mask = alignment - 1;
    if (result_pointer & mask) alignment_offset = alignment - (result_pointer & mask);
    
    return alignment_offset;
}

zpl_inline isize zpl_arena_size_remaining(zpl_arena *arena, isize alignment) {
    isize result = arena->total_size - (arena->total_allocated + zpl_arena_alignment_of(arena, alignment));
    return result;
}

zpl_inline void zpl_arena_check(zpl_arena *arena) { ZPL_ASSERT(arena->temp_count == 0); }

zpl_inline zpl_allocator zpl_arena_allocator(zpl_arena *arena) {
    zpl_allocator allocator;
    allocator.proc = zpl_arena_allocator_proc;
    allocator.data = arena;
    return allocator;
}

ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc) {
    zpl_arena *arena = cast(zpl_arena *) allocator_data;
    void *ptr = NULL;
    
    zpl_unused(old_size);
    
    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            void *end = zpl_pointer_add(arena->physical_start, arena->total_allocated);
            isize total_size = size + alignment;
            
            // NOTE: Out of memory
            if (arena->total_allocated + total_size > cast(isize) arena->total_size) {
                zpl_printf_err("Arena out of memory\n");
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

zpl_inline zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena) {
    zpl_temp_arena_memory tmp;
    tmp.arena = arena;
    tmp.original_count = arena->total_allocated;
    arena->temp_count++;
    return tmp;
}

zpl_inline void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp) {
    ZPL_ASSERT(tmp.arena->total_allocated >= tmp.original_count);
    ZPL_ASSERT(tmp.arena->temp_count > 0);
    tmp.arena->total_allocated = tmp.original_count;
    tmp.arena->temp_count--;
}

//
// Pool Allocator
//

zpl_inline void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, isize num_blocks, isize block_size) {
    zpl_pool_init_align(pool, backing, num_blocks, block_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
}

void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, isize num_blocks, isize block_size, isize block_align) {
    isize actual_block_size, pool_size, block_index;
    void *data, *curr;
    uintptr *end;
    
    zpl_zero_item(pool);
    
    pool->backing = backing;
    pool->block_size = block_size;
    pool->block_align = block_align;
    
    actual_block_size = block_size + block_align;
    pool_size = num_blocks * actual_block_size;
    
    data = zpl_alloc_align(backing, pool_size, block_align);
    
    // NOTE: Init intrusive freelist
    curr = data;
    for (block_index = 0; block_index < num_blocks - 1; block_index++) {
        uintptr *next = cast(uintptr *) curr;
        *next = cast(uintptr) curr + actual_block_size;
        curr = zpl_pointer_add(curr, actual_block_size);
    }
    
    end = cast(uintptr *) curr;
    *end = cast(uintptr) NULL;
    
    pool->physical_start = data;
    pool->free_list = data;
}

zpl_inline void zpl_pool_free(zpl_pool *pool) {
    if (pool->backing.proc) { zpl_free(pool->backing, pool->physical_start); }
}

zpl_inline zpl_allocator zpl_pool_allocator(zpl_pool *pool) {
    zpl_allocator allocator;
    allocator.proc = zpl_pool_allocator_proc;
    allocator.data = pool;
    return allocator;
}
ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc) {
    zpl_pool *pool = cast(zpl_pool *) allocator_data;
    void *ptr = NULL;
    
    zpl_unused(old_size);
    
    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            uintptr next_free;
            ZPL_ASSERT(size == pool->block_size);
            ZPL_ASSERT(alignment == pool->block_align);
            ZPL_ASSERT(pool->free_list != NULL);
            
            next_free = *cast(uintptr *) pool->free_list;
            ptr = pool->free_list;
            pool->free_list = cast(void *) next_free;
            pool->total_size += pool->block_size;
            if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
        } break;
        
        case ZPL_ALLOCATION_FREE: {
            uintptr *next;
            if (old_memory == NULL) return NULL;
            
            next = cast(uintptr *) old_memory;
            *next = cast(uintptr) pool->free_list;
            pool->free_list = old_memory;
            pool->total_size -= pool->block_size;
        } break;
        
        case ZPL_ALLOCATION_FREE_ALL:
        // TODO:
        break;
        
        case ZPL_ALLOCATION_RESIZE:
        // NOTE: Cannot resize
        ZPL_PANIC("You cannot resize something allocated by with a pool.");
        break;
    }
    
    return ptr;
}

zpl_inline zpl_allocation_header_ev *zpl_allocation_header(void *data) {
    isize *p = cast(isize *) data;
    while (p[-1] == cast(isize)(-1)) p--;
    return cast(zpl_allocation_header_ev *) p - 1;
}

zpl_inline void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, isize size) {
    isize *ptr;
    header->size = size;
    ptr = cast(isize *)(header + 1);
    while (cast(void *) ptr < data) *ptr++ = cast(isize)(-1);
}

//
// Scratch Memory Allocator
//

void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, isize size) {
    s->physical_start = start;
    s->total_size = size;
    s->alloc_point = start;
    s->free_point = start;
}

b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr) {
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
                s->alloc_point = cast(u8 *) pt;
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

#define ZPL_STACK_ALLOC_OFFSET sizeof(u64)
ZPL_STATIC_ASSERT(ZPL_STACK_ALLOC_OFFSET == 8);

zpl_inline void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, isize size) {
    s->physical_start = start;
    s->total_size = size;
    s->allocated = 0;
}

zpl_inline void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, isize size) {
    s->backing = backing;
    s->physical_start = zpl_alloc(backing, size);
    s->total_size = size;
    s->allocated = 0;
}

zpl_inline b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr) {
    if (s->allocated == 0) return false;
    
    if (ptr > s->physical_start && ptr < zpl_pointer_add(s->physical_start, s->total_size)) { return true; }
    
    return false;
}

zpl_inline void zpl_stack_memory_free(zpl_stack_memory *s) {
    if (s->backing.proc) {
        zpl_free(s->backing, s->physical_start);
        s->physical_start = NULL;
    }
}

zpl_inline zpl_allocator zpl_stack_allocator(zpl_stack_memory *s) {
    zpl_allocator a;
    a.proc = zpl_stack_allocator_proc;
    a.data = s;
    return a;
}

ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc) {
    zpl_stack_memory *s = cast(zpl_stack_memory *) allocator_data;
    void *ptr = NULL;
    ZPL_ASSERT_NOT_NULL(s);
    zpl_unused(old_size);
    zpl_unused(flags);
    
    switch (type) {
        case ZPL_ALLOCATION_ALLOC: {
            size += ZPL_STACK_ALLOC_OFFSET;
            u64 alloc_offset = s->allocated;
            
            void *curr =
                cast(u64 *) zpl_align_forward(cast(u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);
            
            if (cast(u64 *) zpl_pointer_add(curr, size) > cast(u64 *) zpl_pointer_add(s->physical_start, s->total_size)) {
                if (s->backing.proc) {
                    void *old_start = s->physical_start;
                    s->physical_start =
                        zpl_resize_align(s->backing, s->physical_start, s->total_size, s->total_size + size, alignment);
                    curr = cast(u64 *)
                        zpl_align_forward(cast(u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);
                    s->total_size = zpl_pointer_diff(old_start, s->physical_start);
                } else {
                    ZPL_PANIC("Can not resize stack's memory! Allocator not defined!");
                }
            }
            
            s->allocated = zpl_pointer_diff(s->physical_start, curr) + size;
            
            *(u64 *)curr = alloc_offset;
            curr = zpl_pointer_add(curr, ZPL_STACK_ALLOC_OFFSET);
            
            ptr = curr;
        } break;
        
        case ZPL_ALLOCATION_FREE: {
            if (old_memory) {
                void *curr = old_memory;
                curr = zpl_pointer_sub(curr, ZPL_STACK_ALLOC_OFFSET);
                
                u64 alloc_offset = *(u64 *)curr;
                s->allocated = (usize)alloc_offset;
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
