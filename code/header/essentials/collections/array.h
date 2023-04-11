// file: header/essentials/collections/array.h

////////////////////////////////////////////////////////////////
//
// Dynamic Array (POD Types)
//
// zpl_array(Type) works like zpl_string or zpl_buffer where the actual type is just a pointer to the first
// element.
//
// Available Procedures for zpl_array(Type)
// zpl_array_init
// zpl_array_free
// zpl_array_set_capacity
// zpl_array_grow
// zpl_array_append
// zpl_array_appendv
// zpl_array_pop
// zpl_array_clear
// zpl_array_back
// zpl_array_front
// zpl_array_resize
// zpl_array_reserve
//

#if 0 // Example
void foo(void) {
    zpl_isize i;
    int test_values[] = {4, 2, 1, 7};
    zpl_allocator a = zpl_heap_allocator();
    zpl_array(int) items;

    zpl_array_init(items, a);

    zpl_array_append(items, 1);
    zpl_array_append(items, 4);
    zpl_array_append(items, 9);
    zpl_array_append(items, 16);

    items[1] = 3; // Manually set value
    // NOTE: No array bounds checking

    for (i = 0; i < items.count; i++)
        zpl_printf("%d\n", items[i]);
    // 1
    // 3
    // 9
    // 16

    zpl_array_clear(items);

    zpl_array_appendv(items, test_values, zpl_count_of(test_values));
    for (i = 0; i < items.count; i++)
        zpl_printf("%d\n", items[i]);
    // 4
    // 2
    // 1
    // 7

    zpl_array_free(items);
}
#endif


ZPL_BEGIN_C_DECLS

typedef struct zpl_array_header {
    zpl_isize elem_size;
    zpl_isize count;
    zpl_isize capacity;
    zpl_allocator allocator;
} zpl_array_header;

#define zpl_array(Type) Type *

#define zpl_array_make(Type, Name, allocator) Type *Name; zpl_array_init(Name, allocator)

#ifndef ZPL_ARRAY_GROW_FORMULA
#define ZPL_ARRAY_GROW_FORMULA(x) (2 * (x) + 8)
#endif

ZPL_STATIC_ASSERT(ZPL_ARRAY_GROW_FORMULA(0) > 0, "ZPL_ARRAY_GROW_FORMULA(0) <= 0");

#define ZPL_ARRAY_HEADER(x)    (cast(zpl_array_header *)(x) - 1)
#define zpl_array_allocator(x) (ZPL_ARRAY_HEADER(x)->allocator)
#define zpl_array_elem_size(x) (ZPL_ARRAY_HEADER(x)->elem_size)
#define zpl_array_count(x)     (ZPL_ARRAY_HEADER(x)->count)
#define zpl_array_capacity(x)  (ZPL_ARRAY_HEADER(x)->capacity)
#define zpl_array_end(x)       (x + (zpl_array_count(x) - 1))

ZPL_IMPL_INLINE zpl_b8 zpl__array_init_reserve(void **zpl__array_, zpl_allocator allocator_, zpl_isize elem_size, zpl_isize cap) {
    zpl_array_header *zpl__ah =
    cast(zpl_array_header *) zpl_alloc(allocator_, zpl_size_of(zpl_array_header) + elem_size * cap);
    if (!zpl__ah) return false;
    zpl__ah->allocator = allocator_;
    zpl__ah->elem_size = elem_size;
    zpl__ah->count = 0;
    zpl__ah->capacity = cap;
    *zpl__array_ = cast(void *)(zpl__ah + 1);
    return true;
}

#define zpl_array_init_reserve(x, allocator_, cap) zpl__array_init_reserve(cast(void **) & (x), allocator_, zpl_size_of(*(x)), (cap))

// NOTE: Give it an initial default capacity
#define zpl_array_init(x, allocator) zpl_array_init_reserve(x, allocator, ZPL_ARRAY_GROW_FORMULA(0))

#define zpl_array_free(x)                                                                                              \
do {                                                                                                               \
    if (x) {                                                                                                       \
        zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                           \
        zpl_free(zpl__ah->allocator, zpl__ah);                                                                     \
    }                                                                                                              \
} while (0)

ZPL_IMPL_INLINE zpl_b8 zpl__array_set_capacity(void **array, zpl_isize capacity) {
    zpl_array_header *h = ZPL_ARRAY_HEADER(*array);
    if (capacity == h->capacity) return true;
    if (capacity < h->count) h->count = capacity;
    zpl_isize size = zpl_size_of(zpl_array_header) + h->elem_size * capacity;
    zpl_array_header *nh = cast(zpl_array_header *) zpl_alloc(h->allocator, size);
    if (!nh) return false;
    zpl_memmove(nh, h, zpl_size_of(zpl_array_header) + h->elem_size * h->count);
    nh->allocator = h->allocator;
    nh->elem_size = h->elem_size;
    nh->count = h->count;
    nh->capacity = capacity;
    zpl_free(h->allocator, h);
    *array = nh + 1;
    return true;
}

#define zpl_array_set_capacity(x, capacity) zpl__array_set_capacity(cast(void **) & (x), (capacity))

ZPL_IMPL_INLINE zpl_b8 zpl__array_grow(void **x, zpl_isize min_capacity) {
    zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(zpl_array_capacity(*x));
    if (new_capacity < min_capacity) new_capacity = min_capacity;
    return zpl__array_set_capacity(x, new_capacity);
}

#define zpl_array_grow(x, min_capacity) zpl__array_grow(cast(void **) & (x), (min_capacity))

ZPL_IMPL_INLINE zpl_b8 zpl__array_append_helper(void **x) {
    if (zpl_array_capacity(*x) < zpl_array_count(*x) + 1) {
        if (!zpl__array_grow(x, 0)) return false;
    }
    return true;
}

#define zpl_array_append(x, item) (zpl__array_append_helper(cast(void **) & (x)) && (((x)[zpl_array_count(x)++] = (item)), true))

ZPL_IMPL_INLINE zpl_b8 zpl__array_append_at_helper(void **x, zpl_isize ind) {
    if (ind >= zpl_array_count(*x)) ind = zpl_array_count(*x) - 1;
    if (ind < 0) ind = 0;
    if (zpl_array_capacity(*x) < zpl_array_count(*x) + 1) {
        if (!zpl__array_grow(x, 0)) return false;
    }
    zpl_i8 *s = (cast(zpl_i8*)*x) + ind*zpl_array_elem_size(*x);
    zpl_memmove(s + zpl_array_elem_size(*x), s, zpl_array_elem_size(*x) * (zpl_array_count(*x) - ind));
    return true;
}

#define zpl_array_append_at(x, item, ind) (zpl__array_append_at_helper(cast(void **) & (x), (ind)) && (((x)[ind] = (item)), zpl_array_count(x)++, true))

ZPL_IMPL_INLINE zpl_b8 zpl__array_appendv(void **x, void *items, zpl_isize item_size, zpl_isize item_count) {
    ZPL_ASSERT(item_size == zpl_array_elem_size(*x));
    if (zpl_array_capacity(*x) < zpl_array_count(*x) + item_count) {
        if (!zpl__array_grow(x, zpl_array_count(*x) + item_count)) return false;
    }
    zpl_memcopy((cast(zpl_i8*)*x) + zpl_array_count(*x)*zpl_array_elem_size(*x), items, zpl_array_elem_size(*x) * item_count);
    zpl_array_count(*x) += item_count;
    return true;
}

#define zpl_array_appendv(x, items, item_count) zpl__array_appendv(cast(void **) & (x), (items), zpl_size_of((items)[0]), (item_count))

ZPL_IMPL_INLINE zpl_b8 zpl__array_appendv_at(void **x, void *items, zpl_isize item_size, zpl_isize item_count, zpl_isize ind) {
    if (ind >= zpl_array_count(*x)) return zpl__array_appendv(x, items, item_size, item_count);
    ZPL_ASSERT(item_size == zpl_array_elem_size(*x));
    if (zpl_array_capacity(*x) < zpl_array_count(*x) + item_count) {
        if (!zpl__array_grow(x, zpl_array_count(*x) + item_count)) return false;
    }
    zpl_memmove((cast(zpl_i8*)*x) + (ind + item_count)*zpl_array_elem_size(*x),
    (cast(zpl_i8*)*x) + ind*zpl_array_elem_size(*x), zpl_array_elem_size(*x) * (zpl_array_count(*x) - ind));
    zpl_memcopy((cast(zpl_i8*)*x) + ind*zpl_array_elem_size(*x), items, zpl_array_elem_size(*x) * item_count);
    zpl_array_count(*x) += item_count;
    return true;
}

#define zpl_array_appendv_at(x, items, item_count, ind) zpl__array_appendv_at(cast(void **) & (x), (items), zpl_size_of((items)[0]), (item_count), (ind))

#define zpl_array_fill(x, begin, end, value)                                                                        \
do {                                                                                                               \
    ZPL_ASSERT((begin) >= 0 && (end) <= zpl_array_count(x));                                               \
    ZPL_ASSERT(zpl_size_of(value) == zpl_size_of((x)[0]));                                                    \
    for (zpl_isize i = (begin); i < (end); i++) { x[i] = value; }                                                  \
} while (0)

#define zpl_array_remove_at(x, index)                                                                                  \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    ZPL_ASSERT(index < zpl__ah->count);                                                                            \
    zpl_memmove(x + index, x + index + 1, zpl_size_of(x[0]) * (zpl__ah->count - index - 1));                           \
    --zpl__ah->count;                                                                                              \
} while (0)

ZPL_IMPL_INLINE zpl_b8 zpl__array_copy_init(void **y, void **x) {
    if (!zpl__array_init_reserve(y, zpl_array_allocator(*x), zpl_array_elem_size(*x), zpl_array_capacity(*x)))
        return false;
    zpl_memcopy(*y, *x, zpl_array_capacity(*x) * zpl_array_elem_size(*x));
    zpl_array_count(*y) = zpl_array_count(*x);
    return true;
}

#define zpl_array_copy_init(y, x) zpl__array_copy_init(cast(void **) & (y), cast(void **) & (x))

#define zpl_array_pop(x)                                                                                               \
do {                                                                                                               \
    ZPL_ASSERT(ZPL_ARRAY_HEADER(x)->count > 0);                                                                    \
    ZPL_ARRAY_HEADER(x)->count--;                                                                                  \
} while (0)
#define zpl_array_back(x) x[ZPL_ARRAY_HEADER(x)->count - 1]
#define zpl_array_front(x) x[0]
#define zpl_array_clear(x)                                                                                             \
do { ZPL_ARRAY_HEADER(x)->count = 0; } while (0)

ZPL_IMPL_INLINE zpl_b8 zpl__array_resize(void **x, zpl_isize new_count) {
    if (ZPL_ARRAY_HEADER(*x)->capacity < new_count) {
        if (!zpl__array_grow(x, new_count)) return false;
    }
    ZPL_ARRAY_HEADER(*x)->count = new_count;
    return true;
}

#define zpl_array_resize(x, new_count) zpl__array_resize(cast(void **) & (x), (new_count))

ZPL_IMPL_INLINE zpl_b8 zpl__array_reserve(void **x, zpl_isize new_capacity) {
    if (ZPL_ARRAY_HEADER(*x)->capacity < new_capacity) return zpl__array_set_capacity(x, new_capacity);
    return true;
}

#define zpl_array_reserve(x, new_capacity) zpl__array_reserve(cast(void **) & (x), (new_capacity))

ZPL_END_C_DECLS
