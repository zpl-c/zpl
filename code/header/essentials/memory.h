// file: header/essentials/memory.h

/** @file mem.c
@brief Memory manipulation and helpers.
@defgroup memman Memory management

 Consists of pointer arithmetic methods, virtual memory management and custom memory allocators.

 @{
 */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

//! Checks if value is power of 2.
ZPL_DEF_INLINE zpl_b32 zpl_is_power_of_two(zpl_isize x);

//! Aligns address to specified alignment.
ZPL_DEF_INLINE void *zpl_align_forward(void *ptr, zpl_isize alignment);

//! Aligns value to a specified alignment.
ZPL_DEF_INLINE zpl_i64 zpl_align_forward_i64(zpl_i64 value, zpl_isize alignment);

//! Aligns value to a specified alignment.
ZPL_DEF_INLINE zpl_u64 zpl_align_forward_u64(zpl_u64 value, zpl_usize alignment);

//! Moves pointer forward by bytes.
ZPL_DEF_INLINE void *zpl_pointer_add(void *ptr, zpl_isize bytes);

//! Moves pointer backward by bytes.
ZPL_DEF_INLINE void *zpl_pointer_sub(void *ptr, zpl_isize bytes);

//! Moves pointer forward by bytes.
ZPL_DEF_INLINE void const *zpl_pointer_add_const(void const *ptr, zpl_isize bytes);

//! Moves pointer backward by bytes.
ZPL_DEF_INLINE void const *zpl_pointer_sub_const(void const *ptr, zpl_isize bytes);

//! Calculates difference between two addresses.
ZPL_DEF_INLINE zpl_isize zpl_pointer_diff(void const *begin, void const *end);

#define zpl_ptr_add zpl_pointer_add
#define zpl_ptr_sub zpl_pointer_sub
#define zpl_ptr_add_const zpl_pointer_add_const
#define zpl_ptr_sub_const zpl_pointer_sub_const
#define zpl_ptr_diff zpl_pointer_diff

//! Clears up memory at location by specified size.

//! @param ptr Memory location to clear up.
//! @param size The size to clear up with.
ZPL_DEF_INLINE void zpl_zero_size(void *ptr, zpl_isize size);

#ifndef zpl_zero_item
//! Clears up an item.
#define zpl_zero_item(t) zpl_zero_size((t), zpl_size_of(*(t))) // NOTE: Pass pointer of struct

//! Clears up an array.
#define zpl_zero_array(a, count) zpl_zero_size((a), zpl_size_of(*(a)) * count)
#endif

//! Copy memory from source to destination.
ZPL_DEF_INLINE void *zpl_memmove(void *dest, void const *source, zpl_isize size);

//! Set constant value at memory location with specified size.
ZPL_DEF_INLINE void *zpl_memset(void *data, zpl_u8 byte_value, zpl_isize size);

//! Compare two memory locations with specified size.
ZPL_DEF_INLINE zpl_i32 zpl_memcompare(void const *s1, void const *s2, zpl_isize size);

//! Swap memory contents between 2 locations with size.
ZPL_DEF void zpl_memswap(void *i, void *j, zpl_isize size);

//! Search for a constant value within the size limit at memory location.
ZPL_DEF void const *zpl_memchr(void const *data, zpl_u8 byte_value, zpl_isize size);

//! Search for a constant value within the size limit at memory location in backwards.
ZPL_DEF void const *zpl_memrchr(void const *data, zpl_u8 byte_value, zpl_isize size);

//! Copy non-overlapping memory from source to destination.
ZPL_DEF void *zpl_memcopy(void *dest, void const *source, zpl_isize size);

#ifndef zpl_memcopy_array

//! Copy non-overlapping array.
#define zpl_memcopy_array(dst, src, count) zpl_memcopy((dst), (src), zpl_size_of(*(dst)) * (count))
#endif

//! Copy an array.
#ifndef zpl_memmove_array
#define zpl_memmove_array(dst, src, count) zpl_memmove((dst), (src), zpl_size_of(*(dst)) * (count))
#endif

#ifndef ZPL_BIT_CAST
#define ZPL_BIT_CAST(dest, source)                                                                                 \
do {                                                                                                               \
    ZPL_STATIC_ASSERT(zpl_size_of(*(dest)) <= zpl_size_of(source), "zpl_size_of(*(dest)) !<= zpl_size_of(source)");\
    zpl_memcopy((dest), &(source), zpl_size_of(*dest));                                                            \
} while (0)
#endif

#ifndef zpl_kilobytes
#define zpl_kilobytes(x) ((x)              * (zpl_i64)(1024))
#define zpl_megabytes(x) (zpl_kilobytes(x) * (zpl_i64)(1024))
#define zpl_gigabytes(x) (zpl_megabytes(x) * (zpl_i64)(1024))
#define zpl_terabytes(x) (zpl_gigabytes(x) * (zpl_i64)(1024))
#endif


/* inlines */

#define ZPL__ONES (cast(zpl_usize) - 1 / ZPL_U8_MAX)
#define ZPL__HIGHS (ZPL__ONES * (ZPL_U8_MAX / 2 + 1))
#define ZPL__HAS_ZERO(x) (((x)-ZPL__ONES) & ~(x)&ZPL__HIGHS)

ZPL_IMPL_INLINE void *zpl_align_forward(void *ptr, zpl_isize alignment) {
    zpl_uintptr p;

    ZPL_ASSERT(zpl_is_power_of_two(alignment));

    p = cast(zpl_uintptr) ptr;
    return cast(void *)((p + (alignment - 1)) & ~(alignment - 1));
}

ZPL_IMPL_INLINE zpl_i64 zpl_align_forward_i64(zpl_i64 value, zpl_isize alignment) {
    return value + (alignment - value % alignment) % alignment;
}

ZPL_IMPL_INLINE zpl_u64 zpl_align_forward_u64(zpl_u64 value, zpl_usize alignment) {
    return value + (alignment - value % alignment) % alignment;
}

ZPL_IMPL_INLINE void *zpl_pointer_add(void *ptr, zpl_isize bytes) { return cast(void *)(cast(zpl_u8 *) ptr + bytes); }
ZPL_IMPL_INLINE void *zpl_pointer_sub(void *ptr, zpl_isize bytes) { return cast(void *)(cast(zpl_u8 *) ptr - bytes); }
ZPL_IMPL_INLINE void const *zpl_pointer_add_const(void const *ptr, zpl_isize bytes) {
    return cast(void const *)(cast(zpl_u8 const *) ptr + bytes);
}
ZPL_IMPL_INLINE void const *zpl_pointer_sub_const(void const *ptr, zpl_isize bytes) {
    return cast(void const *)(cast(zpl_u8 const *) ptr - bytes);
}
ZPL_IMPL_INLINE zpl_isize zpl_pointer_diff(void const *begin, void const *end) {
    return cast(zpl_isize)(cast(zpl_u8 const *) end - cast(zpl_u8 const *) begin);
}

ZPL_IMPL_INLINE void zpl_zero_size(void *ptr, zpl_isize size) { zpl_memset(ptr, 0, size); }

#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(__movsb)
#endif

ZPL_IMPL_INLINE void *zpl_memmove(void *dest, void const *source, zpl_isize n) {
    if (dest == NULL) { return NULL; }

    zpl_u8 *d = cast(zpl_u8 *) dest;
    zpl_u8 const *s = cast(zpl_u8 const *) source;

    if (d == s) return d;
    if (s + n <= d || d + n <= s) // NOTE: Non-overlapping
        return zpl_memcopy(d, s, n);

    if (d < s) {
        if (cast(zpl_uintptr) s % zpl_size_of(zpl_isize) == cast(zpl_uintptr) d % zpl_size_of(zpl_isize)) {
            while (cast(zpl_uintptr) d % zpl_size_of(zpl_isize)) {
                if (!n--) return dest;
                *d++ = *s++;
            }
            while (n >= zpl_size_of(zpl_isize)) {
                *cast(zpl_isize *) d = *cast(zpl_isize *) s;
                n -= zpl_size_of(zpl_isize);
                d += zpl_size_of(zpl_isize);
                s += zpl_size_of(zpl_isize);
            }
        }
        for (; n; n--) *d++ = *s++;
    } else {
        if ((cast(zpl_uintptr) s % zpl_size_of(zpl_isize)) == (cast(zpl_uintptr) d % zpl_size_of(zpl_isize))) {
            while (cast(zpl_uintptr)(d + n) % zpl_size_of(zpl_isize)) {
                if (!n--) return dest;
                d[n] = s[n];
            }
            while (n >= zpl_size_of(zpl_isize)) {
                n -= zpl_size_of(zpl_isize);
                *cast(zpl_isize *)(d + n) = *cast(zpl_isize *)(s + n);
            }
        }
        while (n) n--, d[n] = s[n];
    }

    return dest;
}

ZPL_IMPL_INLINE void *zpl_memset(void *dest, zpl_u8 c, zpl_isize n) {
    if (dest == NULL) { return NULL; }

    zpl_u8 *s = cast(zpl_u8 *) dest;
    zpl_isize k;
    zpl_u32 c32 = ((zpl_u32)-1) / 255 * c;

    if (n == 0) return dest;
    s[0] = s[n - 1] = c;
    if (n < 3) return dest;
    s[1] = s[n - 2] = c;
    s[2] = s[n - 3] = c;
    if (n < 7) return dest;
    s[3] = s[n - 4] = c;
    if (n < 9) return dest;

    k = -cast(zpl_intptr) s & 3;
    s += k;
    n -= k;
    n &= -4;

    *cast(zpl_u32 *)(s + 0) = c32;
    *cast(zpl_u32 *)(s + n - 4) = c32;
    if (n < 9) return dest;
    *cast(zpl_u32 *)(s + 4) = c32;
    *cast(zpl_u32 *)(s + 8) = c32;
    *cast(zpl_u32 *)(s + n - 12) = c32;
    *cast(zpl_u32 *)(s + n - 8) = c32;
    if (n < 25) return dest;
    *cast(zpl_u32 *)(s + 12) = c32;
    *cast(zpl_u32 *)(s + 16) = c32;
    *cast(zpl_u32 *)(s + 20) = c32;
    *cast(zpl_u32 *)(s + 24) = c32;
    *cast(zpl_u32 *)(s + n - 28) = c32;
    *cast(zpl_u32 *)(s + n - 24) = c32;
    *cast(zpl_u32 *)(s + n - 20) = c32;
    *cast(zpl_u32 *)(s + n - 16) = c32;

    k = 24 + (cast(zpl_uintptr) s & 4);
    s += k;
    n -= k;

    {
        zpl_u64 c64 = (cast(zpl_u64) c32 << 32) | c32;
        while (n > 31) {
            *cast(zpl_u64 *)(s + 0) = c64;
            *cast(zpl_u64 *)(s + 8) = c64;
            *cast(zpl_u64 *)(s + 16) = c64;
            *cast(zpl_u64 *)(s + 24) = c64;

            n -= 32;
            s += 32;
        }
    }

    return dest;
}

ZPL_IMPL_INLINE zpl_i32 zpl_memcompare(void const *s1, void const *s2, zpl_isize size) {
    zpl_u8 const *s1p8 = cast(zpl_u8 const *) s1;
    zpl_u8 const *s2p8 = cast(zpl_u8 const *) s2;

    if (s1 == NULL || s2 == NULL) { return 0; }

    while (size--) {
        zpl_isize d;
        if ((d = (*s1p8++ - *s2p8++)) != 0) return cast(zpl_i32) d;
    }
    return 0;
}

ZPL_IMPL_INLINE zpl_b32 zpl_is_power_of_two(zpl_isize x) {
    if (x <= 0) return false;
    return !(x & (x - 1));
}

ZPL_END_C_DECLS
