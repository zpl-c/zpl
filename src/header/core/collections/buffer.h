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
