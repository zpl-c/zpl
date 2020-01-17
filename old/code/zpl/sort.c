/** @file sort.c
@brief Sorting and searching methods.
@defgroup sort Sorting and searching

Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains simple implementation of binary search, as well as an easy to use API to define your own comparators.

@{
*/

#define ZPL_COMPARE_PROC(name) int name(void const *a, void const *b)
typedef ZPL_COMPARE_PROC(zpl_compare_proc);

#define ZPL_COMPARE_PROC_PTR(def) ZPL_COMPARE_PROC((*def))

// Procedure pointers
// NOTE: The offset parameter specifies the offset in the structure
// e.g. zpl_i32_cmp(zpl_offset_of(Thing, value))
// Use 0 if it's just the type instead.

ZPL_DEF ZPL_COMPARE_PROC_PTR(i16_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(u8_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(i32_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(i64_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(isize_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(str_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(f32_cmp(zpl_isize offset));
ZPL_DEF ZPL_COMPARE_PROC_PTR(f64_cmp(zpl_isize offset));

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
ZPL_DEF zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
                                zpl_compare_proc compare_proc);

#define zpl_shuffle_array(array, count) zpl_shuffle(array, count, zpl_size_of(*(array)))

//! Shuffles a memory.
ZPL_DEF void zpl_shuffle(void *base, zpl_isize count, zpl_isize size);

#define zpl_reverse_array(array, count) zpl_reverse(array, count, zpl_size_of(*(array)))

//! Reverses memory's contents
ZPL_DEF void zpl_reverse(void *base, zpl_isize count, zpl_isize size);

//! @}
//$$
zpl_inline zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
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

//$$
////////////////////////////////////////////////////////////////
//
// Sorting
//
//

// TODO: Should I make all the macros local?

#define ZPL__COMPARE_PROC(Type)                                                                                        \
zpl_global zpl_isize Type##__cmp_offset;                                                                         \
ZPL_COMPARE_PROC(Type##__cmp) {                                                                              \
    Type const p = *cast(Type const *) zpl_pointer_add_const(a, Type##__cmp_offset);                         \
    Type const q = *cast(Type const *) zpl_pointer_add_const(b, Type##__cmp_offset);                         \
    return p < q ? -1 : p > q;                                                                                     \
}                                                                                                                  \
ZPL_COMPARE_PROC_PTR(Type##_cmp(zpl_isize offset)) {                                                             \
    Type##__cmp_offset = offset;                                                                             \
    return &Type##__cmp;                                                                                     \
}

ZPL__COMPARE_PROC(zpl_u8);
ZPL__COMPARE_PROC(zpl_i16);
ZPL__COMPARE_PROC(zpl_i32);
ZPL__COMPARE_PROC(zpl_i64);
ZPL__COMPARE_PROC(zpl_isize);
ZPL__COMPARE_PROC(zpl_f32);
ZPL__COMPARE_PROC(zpl_f64);

// NOTE: str_cmp is special as it requires a funny type and funny comparison
zpl_global zpl_isize zpl__str_cmp_offset;
ZPL_COMPARE_PROC(zpl__str_cmp) {
    char const *p = *cast(char const **) zpl_pointer_add_const(a, zpl__str_cmp_offset);
    char const *q = *cast(char const **) zpl_pointer_add_const(b, zpl__str_cmp_offset);
    return zpl_strcmp(p, q);
}
ZPL_COMPARE_PROC_PTR(zpl_str_cmp(zpl_isize offset)) {
    zpl__str_cmp_offset = offset;
    return &zpl__str_cmp;
}

#undef ZPL__COMPARE_PROC

// TODO: Make user definable?
#define ZPL__SORT_STACK_SIZE 64
#define zpl__SORT_INSERT_SORT_TRESHOLD 8

#define ZPL__SORT_PUSH(_base, _limit)                                                                                  \
do {                                                                                                               \
    stack_ptr[0] = (_base);                                                                                        \
    stack_ptr[1] = (_limit);                                                                                       \
    stack_ptr += 2;                                                                                                \
} while (0)

#define ZPL__SORT_POP(_base, _limit)                                                                                   \
do {                                                                                                               \
    stack_ptr -= 2;                                                                                                \
    (_base) = stack_ptr[0];                                                                                        \
    (_limit) = stack_ptr[1];                                                                                       \
} while (0)

void zpl_sort(void *base_, zpl_isize count, zpl_isize size, zpl_compare_proc cmp) {
    zpl_u8 *i, *j;
    zpl_u8 *base = cast(zpl_u8 *) base_;
    zpl_u8 *limit = base + count * size;
    zpl_isize threshold = zpl__SORT_INSERT_SORT_TRESHOLD * size;

    // NOTE: Prepare the stack
    zpl_u8 *stack[ZPL__SORT_STACK_SIZE] = { 0 };
    zpl_u8 **stack_ptr = stack;

    for (;;) {
        if ((limit - base) > threshold) {
            // NOTE: Quick sort
            i = base + size;
            j = limit - size;

            zpl_memswap(((limit - base) / size / 2) * size + base, base, size);
            if (cmp(i, j) > 0) zpl_memswap(i, j, size);
            if (cmp(base, j) > 0) zpl_memswap(base, j, size);
            if (cmp(i, base) > 0) zpl_memswap(i, base, size);

            for (;;) {
                do
                    i += size;
                while (cmp(i, base) < 0);
                do
                    j -= size;
                while (cmp(j, base) > 0);
                if (i > j) break;
                zpl_memswap(i, j, size);
            }

            zpl_memswap(base, j, size);

            if (j - base > limit - i) {
                ZPL__SORT_PUSH(base, j);
                base = i;
            } else {
                ZPL__SORT_PUSH(i, limit);
                limit = j;
            }
        } else {
            // NOTE: Insertion sort
            for (j = base, i = j + size; i < limit; j = i, i += size) {
                for (; cmp(j, j + size) > 0; j -= size) {
                    zpl_memswap(j, j + size, size);
                    if (j == base) break;
                }
            }

            if (stack_ptr == stack) break; // NOTE: Sorting is done!
            ZPL__SORT_POP(base, limit);
        }
    }
}

#undef ZPL__SORT_PUSH
#undef ZPL__SORT_POP

#define ZPL_RADIX_SORT_PROC_GEN(Type)                                                                                  \
ZPL_RADIX_SORT_PROC(Type) {                                                                                        \
    zpl_##Type *source = items;                                                                                          \
    zpl_##Type *dest = temp;                                                                                             \
    zpl_isize byte_index, i, byte_max = 8 * zpl_size_of(zpl_##Type);                                                         \
    for (byte_index = 0; byte_index < byte_max; byte_index += 8) {                                                 \
        zpl_isize offsets[256] = { 0 };                                                                                \
        zpl_isize total = 0;                                                                                           \
        /* NOTE: First pass - count how many of each key */                                                        \
        for (i = 0; i < count; i++) {                                                                              \
            zpl_##Type radix_value = source[i];                                                                          \
            zpl_##Type radix_piece = (radix_value >> byte_index) & 0xff;                                                 \
            offsets[radix_piece]++;                                                                                \
        }                                                                                                          \
        /* NOTE: Change counts to offsets */                                                                       \
        for (i = 0; i < zpl_count_of(offsets); i++) {                                                              \
            zpl_isize skcount = offsets[i];                                                                            \
            offsets[i] = total;                                                                                    \
            total += skcount;                                                                                      \
        }                                                                                                          \
        /* NOTE: Second pass - place elements into the right location */                                           \
        for (i = 0; i < count; i++) {                                                                              \
            zpl_##Type radix_value = source[i];                                                                          \
            zpl_##Type radix_piece = (radix_value >> byte_index) & 0xff;                                                 \
            dest[offsets[radix_piece]++] = source[i];                                                              \
        }                                                                                                          \
        zpl_swap(zpl_##Type *, source, dest);                                                                            \
    }                                                                                                              \
}

ZPL_RADIX_SORT_PROC_GEN(u8);
ZPL_RADIX_SORT_PROC_GEN(u16);
ZPL_RADIX_SORT_PROC_GEN(u32);
ZPL_RADIX_SORT_PROC_GEN(u64);

void zpl_shuffle(void *base, zpl_isize count, zpl_isize size) {
    zpl_u8 *a;
    zpl_isize i, j;
    zpl_random random;
    zpl_random_init(&random);

    a = cast(zpl_u8 *) base + (count - 1) * size;
    for (i = count; i > 1; i--) {
        j = zpl_random_gen_isize(&random) % i;
        zpl_memswap(a, cast(zpl_u8 *) base + j * size, size);
        a -= size;
    }
}

void zpl_reverse(void *base, zpl_isize count, zpl_isize size) {
    zpl_isize i, j = count - 1;
    for (i = 0; i < j; i++, j++) zpl_memswap(cast(zpl_u8 *) base + i * size, cast(zpl_u8 *) base + j * size, size);
}
