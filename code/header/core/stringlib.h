////////////////////////////////////////////////////////////////
//
// zpl_string - C Read-Only-Compatible
//
//
/*
    Reasoning:

    By default, strings in C are null terminated which means you have to count
    the number of character up to the null character to calculate the length.
    Many "better" C string libraries will create a struct for a string.
    i.e.

    struct String {
    Allocator allocator;
    size_t    length;
    size_t    capacity;
    char *    cstring;
    };

    This library tries to augment normal C strings in a better way that is still
    compatible with C-style strings.

    +--------+-----------------------+-----------------+
    | Header | Binary C-style String | Null Terminator |
    +--------+-----------------------+-----------------+
    |
    +-> Pointer returned by functions

    Due to the meta-data being stored before the string pointer and every zpl string
    having an implicit null terminator, zpl strings are full compatible with c-style
    strings and read-only functions.

    Advantages:

    * zpl strings can be passed to C-style string functions without accessing a struct
    member of calling a function, i.e.

    zpl_printf("%s\n", zpl_str);

    Many other libraries do either of these:

    zpl_printf("%s\n", string->cstr);
    zpl_printf("%s\n", get_cstring(string));

    * You can access each character just like a C-style string:

    zpl_printf("%c %c\n", str[0], str[13]);

    * zpl strings are singularly allocated. The meta-data is next to the character
    array which is better for the cache.

    Disadvantages:

    * In the C version of these functions, many return the new string. i.e.
    str = zpl_string_appendc(str, "another string");
    This could be changed to zpl_string_appendc(&str, "another string"); but I'm still not sure.
*/

#if 0
#define ZPL_IMPLEMENTATION
#include "zpl.h"
int main(int argc, char **argv) {
    zpl_string str = zpl_string_make("Hello");
    zpl_string other_str = zpl_string_make_length(", ", 2);
    str = zpl_string_append(str, other_str);
    str = zpl_string_appendc(str, "world!");

    zpl_printf("%s\n", str); // Hello, world!

    zpl_printf("str length = %d\n", zpl_string_length(str));

    str = zpl_string_set(str, "Potato soup");
    zpl_printf("%s\n", str); // Potato soup

    str = zpl_string_set(str, "Hello");
    other_str = zpl_string_set(other_str, "Pizza");
    if (zpl_strings_are_equal(str, other_str))
        zpl_printf("Not called\n");
    else
        zpl_printf("Called\n");

    str = zpl_string_set(str, "Ab.;!...AHello World       ??");
    str = zpl_string_trim(str, "Ab.;!. ?");
    zpl_printf("%s\n", str); // "Hello World"

    zpl_string_free(str);
    zpl_string_free(other_str);

    return 0;
}
#endif


typedef char *zpl_string;

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

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

