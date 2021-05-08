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
    char *data;
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
#define zpl_array_count(x)     (ZPL_ARRAY_HEADER(x)->count)
#define zpl_array_capacity(x)  (ZPL_ARRAY_HEADER(x)->capacity)
#define zpl_array_end(x)       (x + (zpl_array_count(x) - 1))

#define zpl_array_init_reserve(x, allocator_, cap)                                                                     \
do {                                                                                                               \
    void **zpl__array_ = cast(void **) & (x);                                                                      \
    zpl_array_header *zpl__ah =                                                                                    \
    cast(zpl_array_header *) zpl_alloc(allocator_, zpl_size_of(zpl_array_header) + zpl_size_of(*(x)) * (cap)); \
    zpl__ah->allocator = allocator_;                                                                               \
    zpl__ah->count = 0;                                                                                            \
    zpl__ah->data = (char *)x;                                                                                     \
    zpl__ah->capacity = cap;                                                                                       \
    *zpl__array_ = cast(void *)(zpl__ah + 1);                                                                      \
} while (0)

// NOTE: Give it an initial default capacity
#define zpl_array_init(x, allocator) zpl_array_init_reserve(x, allocator, ZPL_ARRAY_GROW_FORMULA(0))

#define zpl_array_free(x)                                                                                              \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    zpl_free(zpl__ah->allocator, zpl__ah);                                                                         \
} while (0)

#define zpl_array_set_capacity(x, capacity)                                                                            \
do {                                                                                                               \
    if (x) {                                                                                                       \
        void **zpl__array_ = cast(void **) & (x);                                                                  \
        *zpl__array_ = zpl__array_set_capacity((x), (capacity), zpl_size_of(*(x)));                                \
    }                                                                                                              \
} while (0)

// NOTE: Do not use the thing below directly, use the macro
ZPL_DEF void *zpl__array_set_capacity(void *array, zpl_isize capacity, zpl_isize element_size);

#define zpl_array_grow(x, min_capacity)                                                                                \
do {                                                                                                               \
    zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(zpl_array_capacity(x));                                            \
    if (new_capacity < (min_capacity)) new_capacity = (min_capacity);                                              \
    zpl_array_set_capacity(x, new_capacity);                                                                       \
} while (0)

#define zpl_array_append(x, item)                                                                                      \
do {                                                                                                               \
    if (zpl_array_capacity(x) < zpl_array_count(x) + 1) zpl_array_grow(x, 0);                                      \
    (x)[zpl_array_count(x)++] = (item);                                                                            \
} while (0)

#define zpl_array_append_at(x, item, ind)                                                                              \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    if (ind >= zpl__ah->count) { zpl_array_append(x, item); break; }                                               \
    if (zpl_array_capacity(x) < zpl_array_count(x) + 1) zpl_array_grow(x, 0);                                      \
    zpl_memmove(&(x)[ind + 1], (x + ind), zpl_size_of(x[0]) * (zpl__ah->count - ind));                             \
    x[ind] = item;                                                                                                 \
    zpl__ah->count++;                                                                                              \
} while (0)

#define zpl_array_appendv(x, items, item_count)                                                                        \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    ZPL_ASSERT(zpl_size_of((items)[0]) == zpl_size_of((x)[0]));                                                    \
    if (zpl__ah->capacity < zpl__ah->count + (item_count)) zpl_array_grow(x, zpl__ah->count + (item_count));       \
    zpl_memcopy(&(x)[zpl__ah->count], (items), zpl_size_of((x)[0]) * (item_count));                                \
    zpl__ah->count += (item_count);                                                                                \
} while (0)

#define zpl_array_appendv_at(x, items, item_count, ind)                                                                        \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    if (ind >= zpl__ah->count) { zpl_array_appendv(x, items, item_count); break; }                                               \
    ZPL_ASSERT(zpl_size_of((items)[0]) == zpl_size_of((x)[0]));                                                    \
    if (zpl__ah->capacity < zpl__ah->count + (item_count)) zpl_array_grow(x, zpl__ah->count + (item_count));       \
    zpl_memmove(x + ind + (item_count), x + ind, zpl_size_of((x)[0]) * zpl__ah->count);                                \
    zpl_memcopy(&(x)[ind], (items), zpl_size_of((x)[0]) * (item_count));                                \
    zpl__ah->count += (item_count);                                                                                \
} while (0)

#define zpl_array_fill(x, begin, end, value)                                                                        \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    ZPL_ASSERT((begin) >= 0 && (end) < zpl__ah->count);                                               \
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

#define zpl_array_copy_init(y, x)                                                                                      \
do {                                                                                                               \
    zpl_array_init_reserve(y, zpl_array_allocator(x), zpl_array_capacity(x));                                      \
    zpl_memcopy(y, x, zpl_array_capacity(x) * zpl_size_of(*x));                                                    \
    zpl_array_count(y) = zpl_array_count(x);                                                                       \
} while (0)

#define zpl_array_pop(x)                                                                                               \
do {                                                                                                               \
    ZPL_ASSERT(ZPL_ARRAY_HEADER(x)->count > 0);                                                                    \
    ZPL_ARRAY_HEADER(x)->count--;                                                                                  \
} while (0)
#define zpl_array_back(x) x[ZPL_ARRAY_HEADER(x)->count - 1]
#define zpl_array_front(x) x[0]
#define zpl_array_clear(x)                                                                                             \
do { ZPL_ARRAY_HEADER(x)->count = 0; } while (0)

#define zpl_array_resize(x, new_count)                                                                                 \
do {                                                                                                               \
    if (ZPL_ARRAY_HEADER(x)->capacity < (new_count)) zpl_array_grow(x, (new_count));                               \
    ZPL_ARRAY_HEADER(x)->count = (new_count);                                                                      \
} while (0)

#define zpl_array_reserve(x, new_capacity)                                                                             \
do {                                                                                                               \
    if (ZPL_ARRAY_HEADER(x)->capacity < (new_capacity)) zpl_array_set_capacity(x, new_capacity);                   \
} while (0)

ZPL_END_C_DECLS
