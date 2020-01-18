#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

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

ZPL_END_C_DECLS
