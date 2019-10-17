/** @file containers.c
@brief Memory containers
@defgroup containers Memory containers

Memory containers in various types: buffers, arrays, linked lists, ring buffers, ....

@{
*/

////////////////////////////////////////////////////////////////
//
// Fixed Capacity Buffer (POD Types)
//
//
// zpl_buffer(Type) works like zpl_string or zpl_array where the actual type is just a pointer to the first
// element.
//
// Available Procedures for zpl_buffer(Type)
// zpl_buffer_init
// zpl_buffer_free
// zpl_buffer_append
// zpl_buffer_appendv
// zpl_buffer_pop
// zpl_buffer_clear


typedef struct zpl_buffer_header {
    zpl_allocator backing;
    zpl_isize count;
    zpl_isize capacity;
} zpl_buffer_header;

#define zpl_buffer(Type) Type *

#define zpl_buffer_make(Type, Name, allocator, cap) Type *Name; zpl_buffer_init(Name, allocator, cap)

#define ZPL_BUFFER_HEADER(x)   (cast(zpl_buffer_header *)(x) - 1)
#define zpl_buffer_count(x)    (ZPL_BUFFER_HEADER(x)->count)
#define zpl_buffer_capacity(x) (ZPL_BUFFER_HEADER(x)->capacity)
#define zpl_buffer_end(x) (x + (zpl_buffer_count(x) - 1))

#define zpl_buffer_init(x, allocator, cap)                                                                             \
do {                                                                                                               \
    void **nx = cast(void **) & (x);                                                                               \
    zpl_buffer_header *zpl__bh =                                                                                   \
    cast(zpl_buffer_header *) zpl_alloc((allocator), sizeof(zpl_buffer_header) + (cap)*zpl_size_of(*(x)));     \
    zpl__bh->backing = allocator;                                                                                  \
    zpl__bh->count = 0;                                                                                            \
    zpl__bh->capacity = cap;                                                                                       \
    *nx = cast(void *)(zpl__bh + 1);                                                                               \
} while (0)

// DEPRECATED(zpl_buffer_free): Use zpl_buffer_free2 instead
#define zpl_buffer_free(x, allocator) (zpl_free(allocator, ZPL_BUFFER_HEADER(x)))
#define zpl_buffer_free2(x) (zpl_free(ZPL_BUFFER_HEADER(x)->backing, ZPL_BUFFER_HEADER(x)))

#define zpl_buffer_append(x, item)                                                                                     \
do { (x)[zpl_buffer_count(x)++] = (item); } while (0)

#define zpl_buffer_appendv(x, items, item_count)                                                                       \
do {                                                                                                               \
    ZPL_ASSERT(zpl_size_of(*(items)) == zpl_size_of(*(x)));                                                        \
    ZPL_ASSERT(zpl_buffer_count(x) + item_count <= zpl_buffer_capacity(x));                                        \
    zpl_memcopy(&(x)[zpl_buffer_count(x)], (items), zpl_size_of(*(x)) * (item_count));                             \
    zpl_buffer_count(x) += (item_count);                                                                           \
} while (0)

#define zpl_buffer_copy_init(y, x)                                                                                     \
do {                                                                                                               \
    zpl_buffer_init_reserve(y, zpl_buffer_allocator(x), zpl_buffer_capacity(x));                                   \
    zpl_memcopy(y, x, zpl_buffer_capacity(x) * zpl_size_of(*x));                                                   \
    zpl_buffer_count(y) = zpl_buffer_count(x);                                                                     \
} while (0)

#define zpl_buffer_pop(x)                                                                                              \
do {                                                                                                               \
    ZPL_ASSERT(zpl_buffer_count(x) > 0);                                                                           \
    zpl_buffer_count(x)--;                                                                                         \
} while (0)
#define zpl_buffer_clear(x)                                                                                            \
do { zpl_buffer_count(x) = 0; } while (0)

////////////////////////////////////////////////////////////////
//
// Linked List
//
// zpl_list encapsulates pointer to data and points to the next and the previous element in the list.
//
// Available Procedures for zpl_list
// zpl_list_init
// zpl_list_add
// zpl_list_remove

#if 0
#define ZPL_IMPLEMENTATION
#include "zpl.h"
int main(void)
{
    zpl_list s, *head, *cursor;
    zpl_list_init(&s, "it is optional to call init: ");
    head = cursor = &s;

    // since we can construct an element implicitly this way
    // the second field gets overwritten once we add it to a list.
    zpl_list a = {"hello"};
    cursor = zpl_list_add(cursor, &a);

    zpl_list b = {"world"};
    cursor = zpl_list_add(cursor, &b);

    zpl_list c = {"!!! OK"};
    cursor = zpl_list_add(cursor, &c);

    for (zpl_list *l=head; l; l=l->next) {
        zpl_printf("%s ", cast(char *)l->ptr);
    }
    zpl_printf("\n");

    return 0;
}
#endif


typedef struct zpl__list {
    void const *ptr;
    struct zpl__list *next, *prev;
} zpl_list;

ZPL_DEF void      zpl_list_init(zpl_list *list, void const *ptr);
ZPL_DEF zpl_list *zpl_list_add(zpl_list *list, zpl_list *item);

// NOTE(zaklaus): Returns a pointer to the next node (or NULL if the removed node has no trailing node.)
ZPL_DEF zpl_list *zpl_list_remove(zpl_list *list);

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

ZPL_STATIC_ASSERT(ZPL_ARRAY_GROW_FORMULA(0) > 0);

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
    if (ind == zpl__ah->count) { zpl_array_append(x, item); break; }                                               \
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

#define zpl_array_remove_at(x, index)                                                                                  \
do {                                                                                                               \
    zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
    ZPL_ASSERT(index < zpl__ah->count);                                                                            \
    zpl_memmove(x + index, x + index + 1, zpl_size_of(x[0]) * (zpl__ah->count - index));                           \
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

////////////////////////////////////////////////////////////////
//
// Instantiated Circular buffer
//
/*
int main()
{
    zpl_ring_zpl_u32 pad={0};
    zpl_ring_zpl_u32_init(&pad, zpl_heap(), 3);
    zpl_ring_zpl_u32_append(&pad, 1);
    zpl_ring_zpl_u32_append(&pad, 2);
    zpl_ring_zpl_u32_append(&pad, 3);

    while (!zpl_ring_zpl_u32_empty(&pad)) {
        zpl_printf("Result is %d\n", *zpl_ring_zpl_u32_get(&pad));
    }

    zpl_ring_zpl_u32_free(&pad);

    return 0;
}
*/

#define ZPL_RING_DECLARE(type)                                                                                         \
typedef struct {                                                                                                   \
    zpl_allocator backing;                                                                                         \
    zpl_buffer(type) buf;                                                                                          \
    zpl_usize head, tail;                                                                                              \
    zpl_usize capacity;                                                                                                \
} ZPL_JOIN2(zpl_ring_, type);                                                                                      \
\
ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _init)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_allocator a, zpl_isize max_size); \
ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _free)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
ZPL_DEF zpl_b32 ZPL_JOIN3(zpl_ring_, type, _full)(ZPL_JOIN2(zpl_ring_, type) * pad);                                   \
ZPL_DEF zpl_b32 ZPL_JOIN3(zpl_ring_, type, _empty)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _append)(ZPL_JOIN2(zpl_ring_, type) * pad, type data);                     \
ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _append_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_array(type) data);    \
ZPL_DEF type *ZPL_JOIN3(zpl_ring_, type, _get)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
ZPL_DEF zpl_array(type)                                                                                            \
ZPL_JOIN3(zpl_ring_, type, _get_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_usize max_size, zpl_allocator a);

#define ZPL_RING_DEFINE(type)                                                                                          \
void ZPL_JOIN3(zpl_ring_, type, _init)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_allocator a, zpl_isize max_size) {        \
    ZPL_JOIN2(zpl_ring_, type) pad_ = { 0 };                                                                       \
    *pad = pad_;                                                                                                   \
    \
    pad->backing = a;                                                                                              \
    zpl_buffer_init(pad->buf, a, max_size + 1);                                                                    \
    pad->capacity = max_size + 1;                                                                                  \
    pad->head = pad->tail = 0;                                                                                     \
}                                                                                                                  \
void ZPL_JOIN3(zpl_ring_, type, _free)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                         \
    zpl_buffer_free(pad->buf, pad->backing);                                                                       \
}                                                                                                                  \
\
zpl_b32 ZPL_JOIN3(zpl_ring_, type, _full)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                          \
    return ((pad->head + 1) % pad->capacity) == pad->tail;                                                         \
}                                                                                                                  \
\
zpl_b32 ZPL_JOIN3(zpl_ring_, type, _empty)(ZPL_JOIN2(zpl_ring_, type) * pad) { return pad->head == pad->tail; }        \
\
void ZPL_JOIN3(zpl_ring_, type, _append)(ZPL_JOIN2(zpl_ring_, type) * pad, type data) {                            \
    pad->buf[pad->head] = data;                                                                                    \
    pad->head = (pad->head + 1) % pad->capacity;                                                                   \
    \
    if (pad->head == pad->tail) { pad->tail = (pad->tail + 1) % pad->capacity; }                                   \
}                                                                                                                  \
\
void ZPL_JOIN3(zpl_ring_, type, _append_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_array(type) data) {           \
    zpl_usize c = zpl_array_count(data);                                                                               \
    for (zpl_usize i = 0; i < c; ++i) { ZPL_JOIN3(zpl_ring_, type, _append)(pad, data[i]); }                           \
}                                                                                                                  \
\
type *ZPL_JOIN3(zpl_ring_, type, _get)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                         \
    if (ZPL_JOIN3(zpl_ring_, type, _empty)(pad)) { return NULL; }                                                  \
    \
    type *data = &pad->buf[pad->tail];                                                                             \
    pad->tail = (pad->tail + 1) % pad->capacity;                                                                   \
    \
    return data;                                                                                                   \
}                                                                                                                  \
\
zpl_array(type)                                                                                                    \
ZPL_JOIN3(zpl_ring_, type, _get_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_usize max_size, zpl_allocator a) {    \
    zpl_array(type) vals;                                                                                          \
    zpl_array_init(vals, a);                                                                                       \
    while (--max_size && !ZPL_JOIN3(zpl_ring_, type, _empty)(pad)) {                                               \
        zpl_array_append(vals, *ZPL_JOIN3(zpl_ring_, type, _get)(pad));                                            \
    }                                                                                                              \
    return vals;                                                                                                   \
}

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// zpl_list
//

zpl_inline void zpl_list_init(zpl_list *list, void const *ptr) {
    zpl_list list_ = { 0 };
    *list = list_;
    list->ptr = ptr;
}

zpl_inline zpl_list *zpl_list_add(zpl_list *list, zpl_list *item) {
    item->next = NULL;

    if (list->next) { item->next = list->next; }

    list->next = item;
    item->prev = list;
    return item;
}

zpl_inline zpl_list *zpl_list_remove(zpl_list *list) {
    if (list->prev) { list->prev->next = list->next; }

    return list->next;
}

//$$

////////////////////////////////////////////////////////////////
//
// zpl_array
//
//

zpl_no_inline void *zpl__array_set_capacity(void *array, zpl_isize capacity, zpl_isize element_size) {
    zpl_array_header *h = ZPL_ARRAY_HEADER(array);

    ZPL_ASSERT(element_size > 0);

    if (capacity == h->capacity) return array;

    if (capacity < h->count) {
        if (h->capacity < capacity) {
            zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(h->capacity);
            if (new_capacity < capacity) new_capacity = capacity;
            zpl__array_set_capacity(array, new_capacity, element_size);
        }
        h->count = capacity;
    }

    {
        zpl_isize size = zpl_size_of(zpl_array_header) + element_size * capacity;
        zpl_array_header *nh = cast(zpl_array_header *) zpl_alloc(h->allocator, size);
        zpl_memmove(nh, h, zpl_size_of(zpl_array_header) + element_size * h->count);
        nh->allocator = h->allocator;
        nh->count = h->count;
        nh->data = (char *)nh + 1;
        nh->capacity = capacity;
        zpl_free(h->allocator, h);
        return nh + 1;
    }
}
