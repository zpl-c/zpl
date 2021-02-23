// file: header/essentials/collections/ring.h

////////////////////////////////////////////////////////////////
//
// Instantiated Circular buffer
//

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#define ZPL_RING_DECLARE(prefix,type)                                                                                         \
typedef struct {                                                                                                   \
    zpl_allocator backing;                                                                                         \
    zpl_buffer(type) buf;                                                                                          \
    zpl_usize head, tail;                                                                                              \
    zpl_usize capacity;                                                                                                \
} ZPL_JOIN2(prefix, type);                                                                                      \
\
ZPL_DEF void ZPL_JOIN2(prefix, init)(ZPL_JOIN2(prefix, type) * pad, zpl_allocator a, zpl_isize max_size); \
ZPL_DEF void ZPL_JOIN2(prefix, free)(ZPL_JOIN2(prefix, type) * pad);                                  \
ZPL_DEF zpl_b32 ZPL_JOIN2(prefix, full)(ZPL_JOIN2(prefix, type) * pad);                                   \
ZPL_DEF zpl_b32 ZPL_JOIN2(prefix, empty)(ZPL_JOIN2(prefix, type) * pad);                                  \
ZPL_DEF void ZPL_JOIN2(prefix, append)(ZPL_JOIN2(prefix, type) * pad, type data);                     \
ZPL_DEF void ZPL_JOIN2(prefix, append_array)(ZPL_JOIN2(prefix, type) * pad, zpl_array(type) data);    \
ZPL_DEF type *ZPL_JOIN2(prefix, get)(ZPL_JOIN2(prefix, type) * pad);                                  \
ZPL_DEF zpl_array(type)                                                                                            \
ZPL_JOIN2(prefix, get_array)(ZPL_JOIN2(prefix, type) * pad, zpl_usize max_size, zpl_allocator a);

#define ZPL_RING_DEFINE(prefix,type)                                                                                          \
void ZPL_JOIN2(prefix, init)(ZPL_JOIN2(prefix, type) * pad, zpl_allocator a, zpl_isize max_size) {        \
    ZPL_JOIN2(prefix, type) pad_ = { 0 };                                                                       \
    *pad = pad_;                                                                                                   \
    \
    pad->backing = a;                                                                                              \
    zpl_buffer_init(pad->buf, a, max_size + 1);                                                                    \
    pad->capacity = max_size + 1;                                                                                  \
    pad->head = pad->tail = 0;                                                                                     \
}                                                                                                                  \
void ZPL_JOIN2(prefix, free)(ZPL_JOIN2(prefix, type) * pad) {                                         \
    zpl_buffer_free(pad->buf);                                                                       \
}                                                                                                                  \
\
zpl_b32 ZPL_JOIN2(prefix, full)(ZPL_JOIN2(prefix, type) * pad) {                                          \
    return ((pad->head + 1) % pad->capacity) == pad->tail;                                                         \
}                                                                                                                  \
\
zpl_b32 ZPL_JOIN2(prefix, empty)(ZPL_JOIN2(prefix, type) * pad) { return pad->head == pad->tail; }        \
\
void ZPL_JOIN2(prefix, append)(ZPL_JOIN2(prefix, type) * pad, type data) {                            \
    pad->buf[pad->head] = data;                                                                                    \
    pad->head = (pad->head + 1) % pad->capacity;                                                                   \
    \
    if (pad->head == pad->tail) { pad->tail = (pad->tail + 1) % pad->capacity; }                                   \
}                                                                                                                  \
\
void ZPL_JOIN2(prefix, append_array)(ZPL_JOIN2(prefix, type) * pad, zpl_array(type) data) {           \
    zpl_usize c = zpl_array_count(data);                                                                               \
    for (zpl_usize i = 0; i < c; ++i) { ZPL_JOIN2(prefix, append)(pad, data[i]); }                           \
}                                                                                                                  \
\
type *ZPL_JOIN2(prefix, get)(ZPL_JOIN2(prefix, type) * pad) {                                         \
    if (ZPL_JOIN2(prefix, empty)(pad)) { return NULL; }                                                  \
    \
    type *data = &pad->buf[pad->tail];                                                                             \
    pad->tail = (pad->tail + 1) % pad->capacity;                                                                   \
    \
    return data;                                                                                                   \
}                                                                                                                  \
\
zpl_array(type)                                                                                                    \
ZPL_JOIN2(prefix, get_array)(ZPL_JOIN2(prefix, type) * pad, zpl_usize max_size, zpl_allocator a) {    \
    zpl_array(type) vals = 0;                                                                                          \
    zpl_array_init(vals, a);                                                                                       \
    while (--max_size && !ZPL_JOIN2(prefix, empty)(pad)) {                                               \
        zpl_array_append(vals, *ZPL_JOIN2(prefix, get)(pad));                                            \
    }                                                                                                              \
    return vals;                                                                                                   \
}

ZPL_END_C_DECLS
