// file: header/core/sort.h

/** @file sort.c
@brief Sorting and searching methods.
@defgroup sort Sorting and searching

Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains simple implementation of binary search, as well as an easy to use API to define your own comparators.

@{
*/

ZPL_BEGIN_C_DECLS

#define ZPL_COMPARE_PROC(name) int name(void const *a, void const *b)
typedef ZPL_COMPARE_PROC(zpl_compare_proc);

#define ZPL_COMPARE_PROC_PTR(def) ZPL_COMPARE_PROC((*def))

// Procedure pointers
// NOTE: The offset parameter specifies the offset in the structure
// e.g. zpl_i32_cmp(zpl_offset_of(Thing, value))
// Use 0 if it's just the type instead.

ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_i16_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_u8_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_i32_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_i64_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_isize_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_str_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_f32_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(zpl_f64_cmp(zpl_isize offset));

// TODO: Better sorting algorithms

//! Sorts an array.

//! Uses quick sort for large arrays but insertion sort for small ones.
#define zpl_sort_array(array, count, compare_proc) zpl_sort(array, count, zpl_size_of(*(array)), compare_proc)

//! Perform sorting operation on a memory location with a specified item count and size.
ZPL_DEF void zpl_sort(void *base, zpl_isize count, zpl_isize size, zpl_compare_proc compare_proc);

// NOTE: the count of temp == count of items
#define zpl_radix_sort(Type) zpl_radix_sort_##Type
#define ZPL_RADIX_SORT_PROC(Type) void zpl_radix_sort(Type)(zpl_##Type * items, zpl_##Type * temp, zpl_isize count)

ZPL_DEF ZPL_RADIX_SORT_PROC(u8);
ZPL_DEF ZPL_RADIX_SORT_PROC(u16);
ZPL_DEF ZPL_RADIX_SORT_PROC(u32);
ZPL_DEF ZPL_RADIX_SORT_PROC(u64);

//! Performs binary search on an array.

//! Returns index or -1 if not found
#define zpl_binary_search_array(array, count, key, compare_proc)                                                       \
zpl_binary_search(array, count, zpl_size_of(*(array)), key, compare_proc)

//! Performs binary search on a memory location with specified item count and size.
ZPL_DEF_INLINE zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
                                zpl_compare_proc compare_proc);

#define zpl_shuffle_array(array, count) zpl_shuffle(array, count, zpl_size_of(*(array)))

//! Shuffles a memory.
ZPL_DEF void zpl_shuffle(void *base, zpl_isize count, zpl_isize size);

#define zpl_reverse_array(array, count) zpl_reverse(array, count, zpl_size_of(*(array)))

//! Reverses memory's contents
ZPL_DEF void zpl_reverse(void *base, zpl_isize count, zpl_isize size);

//! @}


ZPL_IMPL_INLINE zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
                                   zpl_compare_proc compare_proc) {
    zpl_isize start = 0;
    zpl_isize end = count;

    while (start < end) {
        zpl_isize mid = start + (end - start) / 2;
        zpl_isize result = compare_proc(key, cast(zpl_u8 *) base + mid * size);
        if (result < 0)
            end = mid;
        else if (result > 0)
            start = mid + 1;
        else
            return mid;
    }

    return -1;
}

ZPL_END_C_DECLS
