#ifdef ZPL_EDITOR
#include <zpl.h>
#endif
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
