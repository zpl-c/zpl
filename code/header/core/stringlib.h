// file: header/core/stringlib.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef char *zpl_string;

typedef struct zpl_string_header {
    zpl_allocator allocator;
    zpl_isize length;
    zpl_isize capacity;
} zpl_string_header;

#define ZPL_STRING_HEADER(str) (cast(zpl_string_header *)(str) - 1)

ZPL_DEF zpl_string zpl_string_make_reserve(zpl_allocator a, zpl_isize capacity);
ZPL_DEF zpl_string zpl_string_make_length(zpl_allocator a, void const *str, zpl_isize num_bytes);
ZPL_DEF zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, zpl_isize num_bytes, const char *fmt, ...);
ZPL_DEF zpl_string zpl_string_sprintf_buf(zpl_allocator a, const char *fmt, ...); // NOTE: Uses locally persistent buffer
ZPL_DEF zpl_string zpl_string_append_length(zpl_string str, void const *other, zpl_isize num_bytes);
ZPL_DEF zpl_string zpl_string_appendc(zpl_string str, const char *other);
ZPL_DEF zpl_string zpl_string_join(zpl_allocator a, const char **parts, zpl_isize count, const char *glue);
ZPL_DEF zpl_string zpl_string_set(zpl_string str, const char *cstr);
ZPL_DEF zpl_string zpl_string_make_space_for(zpl_string str, zpl_isize add_len);
ZPL_DEF zpl_isize  zpl_string_allocation_size(zpl_string const str);
ZPL_DEF zpl_b32    zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs);
ZPL_DEF zpl_string zpl_string_trim(zpl_string str, const char *cut_set);
ZPL_DEF zpl_string zpl_string_append_rune(zpl_string str, zpl_rune r);
ZPL_DEF zpl_string zpl_string_append_fmt(zpl_string str, const char *fmt, ...);

ZPL_DEF_INLINE zpl_string zpl_string_make(zpl_allocator a, const char *str);
ZPL_DEF_INLINE void       zpl_string_free(zpl_string str);
ZPL_DEF_INLINE void       zpl_string_clear(zpl_string str);
ZPL_DEF_INLINE zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str);
ZPL_DEF_INLINE zpl_isize  zpl_string_length(zpl_string const str);
ZPL_DEF_INLINE zpl_isize  zpl_string_capacity(zpl_string const str);
ZPL_DEF_INLINE zpl_isize  zpl_string_available_space(zpl_string const str);
ZPL_DEF_INLINE zpl_string zpl_string_append(zpl_string str, zpl_string const other);
ZPL_DEF_INLINE zpl_string zpl_string_trim_space(zpl_string str); // Whitespace ` \t\r\n\v\f`
ZPL_DEF_INLINE void       zpl__set_string_length(zpl_string str, zpl_isize len);
ZPL_DEF_INLINE void       zpl__set_string_capacity(zpl_string str, zpl_isize cap);

ZPL_IMPL_INLINE void zpl__set_string_length(zpl_string str, zpl_isize len) { ZPL_STRING_HEADER(str)->length = len; }
ZPL_IMPL_INLINE void zpl__set_string_capacity(zpl_string str, zpl_isize cap) { ZPL_STRING_HEADER(str)->capacity = cap; }
ZPL_IMPL_INLINE zpl_string zpl_string_make(zpl_allocator a, const char *str) {
    zpl_isize len = str ? zpl_strlen(str) : 0;
    return zpl_string_make_length(a, str, len);
}

ZPL_IMPL_INLINE void zpl_string_free(zpl_string str) {
    if (str) {
        zpl_string_header *header = ZPL_STRING_HEADER(str);
        zpl_free(header->allocator, header);
    }
}

ZPL_IMPL_INLINE zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str) {
    return zpl_string_make_length(a, str, zpl_string_length(str));
}

ZPL_IMPL_INLINE zpl_isize zpl_string_length(zpl_string const str) { return ZPL_STRING_HEADER(str)->length; }
ZPL_IMPL_INLINE zpl_isize zpl_string_capacity(zpl_string const str) { return ZPL_STRING_HEADER(str)->capacity; }

ZPL_IMPL_INLINE zpl_isize zpl_string_available_space(zpl_string const str) {
    zpl_string_header *h = ZPL_STRING_HEADER(str);
    if (h->capacity > h->length) return h->capacity - h->length;
    return 0;
}

ZPL_IMPL_INLINE void zpl_string_clear(zpl_string str) {
    zpl__set_string_length(str, 0);
    str[0] = '\0';
}

ZPL_IMPL_INLINE zpl_string zpl_string_append(zpl_string str, zpl_string const other) {
    return zpl_string_append_length(str, other, zpl_string_length(other));
}

ZPL_IMPL_INLINE zpl_string zpl_string_trim_space(zpl_string str) { return zpl_string_trim(str, " \t\r\n\v\f"); }


ZPL_END_C_DECLS
