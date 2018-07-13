////////////////////////////////////////////////////////////////
//
// Char Functions
//
//

ZPL_DEF char zpl_char_to_lower(char c);
ZPL_DEF char zpl_char_to_upper(char c);
ZPL_DEF b32 zpl_char_is_space(char c);
ZPL_DEF b32 zpl_char_is_digit(char c);
ZPL_DEF b32 zpl_char_is_hex_digit(char c);
ZPL_DEF b32 zpl_char_is_alpha(char c);
ZPL_DEF b32 zpl_char_is_alphanumeric(char c);
ZPL_DEF i32 zpl_digit_to_int(char c);
ZPL_DEF i32 zpl_hex_digit_to_int(char c);

// NOTE: ASCII only
ZPL_DEF void zpl_str_to_lower(char *str);
ZPL_DEF void zpl_str_to_upper(char *str);

ZPL_DEF char *zpl_str_trim(char *str, b32 skip_newline);
ZPL_DEF char *zpl_str_skip(char *str, char c);

ZPL_DEF isize zpl_strlen(char const *str);
ZPL_DEF isize zpl_strnlen(char const *str, isize max_len);
ZPL_DEF i32 zpl_strcmp(char const *s1, char const *s2);
ZPL_DEF i32 zpl_strncmp(char const *s1, char const *s2, isize len);
ZPL_DEF char *zpl_strcpy(char *dest, char const *source);
ZPL_DEF char *zpl_strdup(zpl_allocator a, char *src, isize max_len);
ZPL_DEF char *zpl_strncpy(char *dest, char const *source, isize len);
ZPL_DEF isize zpl_strlcpy(char *dest, char const *source, isize len);
ZPL_DEF char *zpl_strrev(char *str); // NOTE: ASCII only

ZPL_DEF char const *zpl_strtok(char *output, char const *src, char const *delimit);

// NOTE: This edits *source* string.
// Returns: zpl_array
ZPL_DEF char **zpl_str_split_lines(zpl_allocator alloc, char *source, b32 strip_whitespace);

ZPL_DEF b32 zpl_str_has_prefix(char const *str, char const *prefix);
ZPL_DEF b32 zpl_str_has_suffix(char const *str, char const *suffix);

ZPL_DEF char const *zpl_char_first_occurence(char const *str, char c);
ZPL_DEF char const *zpl_char_last_occurence(char const *str, char c);

ZPL_DEF void zpl_str_concat(char *dest, isize dest_len, char const *src_a, isize src_a_len, char const *src_b,
                            isize src_b_len);

ZPL_DEF u64 zpl_str_to_u64(char const *str, char **end_ptr,
                           i32 base); // TODO: Support more than just decimal and hexadecimal
ZPL_DEF i64 zpl_str_to_i64(char const *str, char **end_ptr,
                           i32 base); // TODO: Support more than just decimal and hexadecimal
ZPL_DEF f32 zpl_str_to_f32(char const *str, char **end_ptr);
ZPL_DEF f64 zpl_str_to_f64(char const *str, char **end_ptr);
ZPL_DEF void zpl_i64_to_str(i64 value, char *string, i32 base);
ZPL_DEF void zpl_u64_to_str(u64 value, char *string, i32 base);

////////////////////////////////////////////////////////////////
//
// UTF-8 Handling
//
//

// NOTE: Does not check if utf-8 string is valid
ZPL_DEF isize zpl_utf8_strlen(u8 const *str);
ZPL_DEF isize zpl_utf8_strnlen(u8 const *str, isize max_len);

// NOTE: Windows doesn't handle 8 bit filenames well ('cause Micro$hit)
ZPL_DEF u16 *zpl_utf8_to_ucs2(u16 *buffer, isize len, u8 const *str);
ZPL_DEF u8 *zpl_ucs2_to_utf8(u8 *buffer, isize len, u16 const *str);
ZPL_DEF u16 *zpl_utf8_to_ucs2_buf(u8 const *str); // NOTE: Uses locally persisting buffer
ZPL_DEF u8 *zpl_ucs2_to_utf8_buf(u16 const *str); // NOTE: Uses locally persisting buffer

// NOTE: Returns size of codepoint in bytes
ZPL_DEF isize zpl_utf8_decode(u8 const *str, isize str_len, Rune *codepoint);
ZPL_DEF isize zpl_utf8_codepoint_size(u8 const *str, isize str_len);
ZPL_DEF isize zpl_utf8_encode_rune(u8 buf[4], Rune r);

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

#define zpl_string_t zpl_string
typedef char *zpl_string;

// NOTE: If you only need a small string, just use a standard c string or change the size from isize to u16, etc.
#define zpl_string_header_t zpl_string_header
typedef struct zpl_string_header {
    zpl_allocator allocator;
    isize length;
    isize capacity;
} zpl_string_header;

#define ZPL_STRING_HEADER(str) (cast(zpl_string_header *)(str) - 1)

ZPL_DEF zpl_string zpl_string_make_reserve(zpl_allocator a, isize capacity);
ZPL_DEF zpl_string zpl_string_make(zpl_allocator a, char const *str);
ZPL_DEF zpl_string zpl_string_make_length(zpl_allocator a, void const *str, isize num_bytes);
ZPL_DEF zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, isize num_bytes, char const *fmt, ...);
ZPL_DEF zpl_string zpl_string_sprintf_buf(zpl_allocator a, char const *fmt,
                                          ...); // NOTE: Uses locally persistent buffer
ZPL_DEF void zpl_string_free(zpl_string str);
ZPL_DEF zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str);
ZPL_DEF isize zpl_string_length(zpl_string const str);
ZPL_DEF isize zpl_string_capacity(zpl_string const str);
ZPL_DEF isize zpl_string_available_space(zpl_string const str);
ZPL_DEF void zpl_string_clear(zpl_string str);
ZPL_DEF zpl_string zpl_string_append(zpl_string str, zpl_string const other);
ZPL_DEF zpl_string zpl_string_append_length(zpl_string str, void const *other, isize num_bytes);
ZPL_DEF zpl_string zpl_string_appendc(zpl_string str, char const *other);
ZPL_DEF zpl_string zpl_string_set(zpl_string str, char const *cstr);
ZPL_DEF zpl_string zpl_string_make_space_for(zpl_string str, isize add_len);
ZPL_DEF isize zpl_string_allocation_size(zpl_string const str);
ZPL_DEF b32 zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs);
ZPL_DEF zpl_string zpl_string_trim(zpl_string str, char const *cut_set);
ZPL_DEF zpl_string zpl_string_trim_space(zpl_string str); // Whitespace ` \t\r\n\v\f`
ZPL_DEF zpl_string zpl_string_append_rune(zpl_string str, Rune r);
ZPL_DEF zpl_string zpl_string_append_fmt(zpl_string str, char const *fmt, ...);


//!!

////////////////////////////////////////////////////////////////
//
// Char things
//
//

zpl_inline char zpl_char_to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return 'a' + (c - 'A');
    return c;
}

zpl_inline char zpl_char_to_upper(char c) {
    if (c >= 'a' && c <= 'z') return 'A' + (c - 'a');
    return c;
}

zpl_inline b32 zpl_char_is_space(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v') return true;
    return false;
}

zpl_inline b32 zpl_char_is_digit(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

zpl_inline b32 zpl_char_is_hex_digit(char c) {
    if (zpl_char_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return true;
    return false;
}

zpl_inline b32 zpl_char_is_alpha(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
    return false;
}

zpl_inline b32 zpl_char_is_alphanumeric(char c) { return zpl_char_is_alpha(c) || zpl_char_is_digit(c); }

zpl_inline i32 zpl_digit_to_int(char c) { return zpl_char_is_digit(c) ? c - '0' : c - 'W'; }

zpl_inline i32 zpl_hex_digit_to_int(char c) {
    if (zpl_char_is_digit(c))
        return zpl_digit_to_int(c);
    else if (zpl_is_between(c, 'a', 'f'))
        return c - 'a' + 10;
    else if (zpl_is_between(c, 'A', 'F'))
        return c - 'A' + 10;
    return -1;
}

zpl_inline void zpl_str_to_lower(char *str) {
    if (!str) return;
    while (*str) {
        *str = zpl_char_to_lower(*str);
        str++;
    }
}

zpl_inline void zpl_str_to_upper(char *str) {
    if (!str) return;
    while (*str) {
        *str = zpl_char_to_upper(*str);
        str++;
    }
}

zpl_inline isize zpl_strlen(char const *str) {
    if (str == NULL) { return 0; }

    char const *begin = str;
    isize const *w;
    while (cast(uintptr) str % sizeof(usize)) {
        if (!*str) return str - begin;
        str++;
    }
    w = cast(isize const *) str;
    while (!ZPL__HAS_ZERO(*w)) w++;
    str = cast(char const *) w;
    while (*str) str++;
    return str - begin;
}

zpl_inline isize zpl_strnlen(char const *str, isize max_len) {
    char const *end = cast(char const *) zpl_memchr(str, 0, max_len);
    if (end) return end - str;
    return max_len;
}

zpl_inline isize zpl_utf8_strlen(u8 const *str) {
    isize count = 0;
    for (; *str; count++) {
        u8 c = *str;
        isize inc = 0;
        if (c < 0x80)
            inc = 1;
        else if ((c & 0xe0) == 0xc0)
            inc = 2;
        else if ((c & 0xf0) == 0xe0)
            inc = 3;
        else if ((c & 0xf8) == 0xf0)
            inc = 4;
        else
            return -1;

        str += inc;
    }
    return count;
}

zpl_inline isize zpl_utf8_strnlen(u8 const *str, isize max_len) {
    isize count = 0;
    for (; *str && max_len > 0; count++) {
        u8 c = *str;
        isize inc = 0;
        if (c < 0x80)
            inc = 1;
        else if ((c & 0xe0) == 0xc0)
            inc = 2;
        else if ((c & 0xf0) == 0xe0)
            inc = 3;
        else if ((c & 0xf8) == 0xf0)
            inc = 4;
        else
            return -1;

        str += inc;
        max_len -= inc;
    }
    return count;
}

zpl_inline i32 zpl_strcmp(char const *s1, char const *s2) {
    while (*s1 && (*s1 == *s2)) { s1++, s2++; }
    return *(u8 *)s1 - *(u8 *)s2;
}

zpl_inline char *zpl_strcpy(char *dest, char const *source) {
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        char *str = dest;
        while (*source) *str++ = *source++;
    }
    return dest;
}

zpl_inline char *zpl_strdup(zpl_allocator a, char *src, isize max_len) {
    ZPL_ASSERT_NOT_NULL(src);
    isize len = zpl_strlen(src);
    char *dest = cast(char *) zpl_alloc(a, max_len);
    zpl_memset(dest + len, 0, max_len - len);
    zpl_strncpy(dest, src, max_len);

    return dest;
}

zpl_inline char *zpl_strncpy(char *dest, char const *source, isize len) {
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        char *str = dest;
        while (len > 0 && *source) {
            *str++ = *source++;
            len--;
        }
        while (len > 0) {
            *str++ = '\0';
            len--;
        }
    }
    return dest;
}

zpl_inline isize zpl_strlcpy(char *dest, char const *source, isize len) {
    isize result = 0;
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        char const *source_start = source;
        char *str = dest;
        while (len > 0 && *source) {
            *str++ = *source++;
            len--;
        }
        while (len > 0) {
            *str++ = '\0';
            len--;
        }

        result = source - source_start;
    }
    return result;
}

zpl_inline char *zpl_strrev(char *str) {
    isize len = zpl_strlen(str);
    char *a = str + 0;
    char *b = str + len - 1;
    len /= 2;
    while (len--) {
        zpl_swap(char, *a, *b);
        a++, b--;
    }
    return str;
}

zpl_inline i32 zpl_strncmp(char const *s1, char const *s2, isize len) {
    for (; len > 0; s1++, s2++, len--) {
        if (*s1 != *s2)
            return ((s1 < s2) ? -1 : +1);
        else if (*s1 == '\0')
            return 0;
    }
    return 0;
}

zpl_inline char const *zpl_strtok(char *output, char const *src, char const *delimit) {
    while (*src && zpl_char_first_occurence(delimit, *src) != NULL) *output++ = *src++;

    *output = 0;
    return *src ? src + 1 : src;
}

zpl_inline char **zpl_str_split_lines(zpl_allocator alloc, char *source, b32 strip_whitespace) {
    char **lines = NULL, *p = source, *pd = p;
    zpl_array_init(lines, alloc);

    while (*p) {
        if (*pd == '\n') {
            *pd = 0;
            if (*(pd - 1) == '\r') *(pd - 1) = 0;
            if (strip_whitespace && (pd - p) == 0) {
                p = pd + 1;
                continue;
            }
            zpl_array_append(lines, p);
            p = pd + 1;
        }
        ++pd;
    }
    return lines;
}

zpl_inline b32 zpl_str_has_prefix(char const *str, char const *prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) return false;
    }
    return true;
}

zpl_inline b32 zpl_str_has_suffix(char const *str, char const *suffix) {
    isize i = zpl_strlen(str);
    isize j = zpl_strlen(suffix);
    if (j <= i) return zpl_strcmp(str + i - j, suffix) == 0;
    return false;
}

zpl_inline char const *zpl_char_first_occurence(char const *s, char c) {
    char ch = c;
    for (; *s != ch; s++) {
        if (*s == '\0') return NULL;
    }
    return s;
}

zpl_inline char const *zpl_char_last_occurence(char const *s, char c) {
    char const *result = NULL;
    do {
        if (*s == c) result = s;
    } while (*s++);

    return result;
}

zpl_inline char *zpl_str_trim(char *str, b32 skip_newline)
{
    while (*str && zpl_char_is_space(*str) && (!skip_newline || (skip_newline && *str != '\n'))) { ++str; }
    return str;
}

zpl_inline char *zpl_str_skip(char *str, char c) {
    while (*str && *str != c) { ++str; }
    return str;
}

zpl_inline void zpl_str_concat(char *dest, isize dest_len, char const *src_a, isize src_a_len, char const *src_b,
                               isize src_b_len) {
    ZPL_ASSERT(dest_len >= src_a_len + src_b_len + 1);
    if (dest) {
        zpl_memcopy(dest, src_a, src_a_len);
        zpl_memcopy(dest + src_a_len, src_b, src_b_len);
        dest[src_a_len + src_b_len] = '\0';
    }
}

zpl_internal isize zpl__scan_i64(char const *text, i32 base, i64 *value) {
    char const *text_begin = text;
    i64 result = 0;
    b32 negative = false;

    if (*text == '-') {
        negative = true;
        text++;
    }

    if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

    for (;;) {
        i64 v;
        if (zpl_char_is_digit(*text))
            v = *text - '0';
        else if (base == 16 && zpl_char_is_hex_digit(*text))
            v = zpl_hex_digit_to_int(*text);
        else
            break;

        result *= base;
        result += v;
        text++;
    }

    if (value) {
        if (negative) result = -result;
        *value = result;
    }

    return (text - text_begin);
}

zpl_internal isize zpl__scan_u64(char const *text, i32 base, u64 *value) {
    char const *text_begin = text;
    u64 result = 0;

    if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

    for (;;) {
        u64 v;
        if (zpl_char_is_digit(*text))
            v = *text - '0';
        else if (base == 16 && zpl_char_is_hex_digit(*text))
            v = zpl_hex_digit_to_int(*text);
        else {
            break;
        }

        result *= base;
        result += v;
        text++;
    }

    if (value) *value = result;

    return (text - text_begin);
}

// TODO: Make better
u64 zpl_str_to_u64(char const *str, char **end_ptr, i32 base) {
    isize len;
    u64 value = 0;

    if (!base) {
        if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
            base = 16;
        else
            base = 10;
    }

    len = zpl__scan_u64(str, base, &value);
    if (end_ptr) *end_ptr = (char *)str + len;
    return value;
}

i64 zpl_str_to_i64(char const *str, char **end_ptr, i32 base) {
    isize len;
    i64 value;

    if (!base) {
        if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
            base = 16;
        else
            base = 10;
    }

    len = zpl__scan_i64(str, base, &value);
    if (end_ptr) *end_ptr = (char *)str + len;
    return value;
}

// TODO: Are these good enough for characters?
zpl_global char const zpl__num_to_char_table[] = "0123456789"
                                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                 "abcdefghijklmnopqrstuvwxyz"
                                                 "@$";

zpl_inline void zpl_i64_to_str(i64 value, char *string, i32 base) {
    char *buf = string;
    b32 negative = false;
    u64 v;

    if (value < 0) {
        negative = true;
        value = -value;
    }

    v = cast(u64) value;
    if (v != 0) {
        while (v > 0) {
            *buf++ = zpl__num_to_char_table[v % base];
            v /= base;
        }
    } else {
        *buf++ = '0';
    }
    if (negative) *buf++ = '-';
    *buf = '\0';
    zpl_strrev(string);
}

zpl_inline void zpl_u64_to_str(u64 value, char *string, i32 base) {
    char *buf = string;

    if (value) {
        while (value > 0) {
            *buf++ = zpl__num_to_char_table[value % base];
            value /= base;
        }
    } else {
        *buf++ = '0';
    }
    *buf = '\0';

    zpl_strrev(string);
}

zpl_inline f32 zpl_str_to_f32(char const *str, char **end_ptr) {
    f64 f = zpl_str_to_f64(str, end_ptr);
    f32 r = cast(f32) f;
    return r;
}

zpl_inline f64 zpl_str_to_f64(char const *str, char **end_ptr) {
    f64 result, value, sign, scale;
    i32 frac;

    while (zpl_char_is_space(*str)) { str++; }

    sign = 1.0;
    if (*str == '-') {
        sign = -1.0;
        str++;
    } else if (*str == '+') {
        str++;
    }

    for (value = 0.0; zpl_char_is_digit(*str); str++) { value = value * 10.0 + (*str - '0'); }

    if (*str == '.') {
        f64 pow10 = 10.0;
        str++;
        while (zpl_char_is_digit(*str)) {
            value += (*str - '0') / pow10;
            pow10 *= 10.0;
            str++;
        }
    }

    frac = 0;
    scale = 1.0;
    if ((*str == 'e') || (*str == 'E')) {
        u32 exp;

        str++;
        if (*str == '-') {
            frac = 1;
            str++;
        } else if (*str == '+') {
            str++;
        }

        for (exp = 0; zpl_char_is_digit(*str); str++) { exp = exp * 10 + (*str - '0'); }
        if (exp > 308) exp = 308;

        while (exp >= 50) {
            scale *= 1e50;
            exp -= 50;
        }
        while (exp >= 8) {
            scale *= 1e8;
            exp -= 8;
        }
        while (exp > 0) {
            scale *= 10.0;
            exp -= 1;
        }
    }

    result = sign * (frac ? (value / scale) : (value * scale));

    if (end_ptr) *end_ptr = cast(char *) str;

    return result;
}

zpl_inline void zpl__set_string_length(zpl_string str, isize len) { ZPL_STRING_HEADER(str)->length = len; }
zpl_inline void zpl__set_string_capacity(zpl_string str, isize cap) { ZPL_STRING_HEADER(str)->capacity = cap; }

zpl_inline zpl_string zpl_string_make_reserve(zpl_allocator a, isize capacity) {
    isize header_size = zpl_size_of(zpl_string_header);
    void *ptr = zpl_alloc(a, header_size + capacity + 1);

    zpl_string str;
    zpl_string_header *header;

    if (ptr == NULL) return NULL;
    zpl_zero_size(ptr, header_size + capacity + 1);

    str = cast(char *) ptr + header_size;
    header = ZPL_STRING_HEADER(str);
    header->allocator = a;
    header->length = 0;
    header->capacity = capacity;
    str[capacity] = '\0';

    return str;
}

zpl_inline zpl_string zpl_string_make(zpl_allocator a, char const *str) {
    isize len = str ? zpl_strlen(str) : 0;
    return zpl_string_make_length(a, str, len);
}

zpl_string zpl_string_make_length(zpl_allocator a, void const *init_str, isize num_bytes) {
    isize header_size = zpl_size_of(zpl_string_header);
    void *ptr = zpl_alloc(a, header_size + num_bytes + 1);

    zpl_string str;
    zpl_string_header *header;

    if (ptr == NULL) return NULL;
    if (!init_str) zpl_zero_size(ptr, header_size + num_bytes + 1);

    str = cast(char *) ptr + header_size;
    header = ZPL_STRING_HEADER(str);
    header->allocator = a;
    header->length = num_bytes;
    header->capacity = num_bytes;
    if (num_bytes && init_str) zpl_memcopy(str, init_str, num_bytes);
    str[num_bytes] = '\0';

    return str;
}

zpl_string zpl_string_sprintf_buf(zpl_allocator a, char const *fmt, ...) {
    zpl_local_persist char buf[4096] = { 0 };
    va_list va;
    va_start(va, fmt);
    zpl_snprintf_va(buf, 4096, fmt, va);
    va_end(va);

    return zpl_string_make(a, buf);
}

zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, isize num_bytes, char const *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    zpl_snprintf_va(buf, num_bytes, fmt, va);
    va_end(va);

    return zpl_string_make(a, buf);
}

zpl_inline void zpl_string_free(zpl_string str) {
    if (str) {
        zpl_string_header *header = ZPL_STRING_HEADER(str);
        zpl_free(header->allocator, header);
    }
}

zpl_inline zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str) {
    return zpl_string_make_length(a, str, zpl_string_length(str));
}

zpl_inline isize zpl_string_length(zpl_string const str) { return ZPL_STRING_HEADER(str)->length; }
zpl_inline isize zpl_string_capacity(zpl_string const str) { return ZPL_STRING_HEADER(str)->capacity; }

zpl_inline isize zpl_string_available_space(zpl_string const str) {
    zpl_string_header *h = ZPL_STRING_HEADER(str);
    if (h->capacity > h->length) return h->capacity - h->length;
    return 0;
}

zpl_inline void zpl_string_clear(zpl_string str) {
    zpl__set_string_length(str, 0);
    str[0] = '\0';
}

zpl_inline zpl_string zpl_string_append(zpl_string str, zpl_string const other) {
    return zpl_string_append_length(str, other, zpl_string_length(other));
}

zpl_string zpl_string_append_length(zpl_string str, void const *other, isize other_len) {
    if (other_len > 0) {
        isize curr_len = zpl_string_length(str);

        str = zpl_string_make_space_for(str, other_len);
        if (str == NULL) return NULL;

        zpl_memcopy(str + curr_len, other, other_len);
        str[curr_len + other_len] = '\0';
        zpl__set_string_length(str, curr_len + other_len);
    }
    return str;
}

zpl_inline zpl_string zpl_string_appendc(zpl_string str, char const *other) {
    return zpl_string_append_length(str, other, zpl_strlen(other));
}

zpl_string zpl_string_set(zpl_string str, char const *cstr) {
    isize len = zpl_strlen(cstr);
    if (zpl_string_capacity(str) < len) {
        str = zpl_string_make_space_for(str, len - zpl_string_length(str));
        if (str == NULL) return NULL;
    }

    zpl_memcopy(str, cstr, len);
    str[len] = '\0';
    zpl__set_string_length(str, len);

    return str;
}

zpl_string zpl_string_make_space_for(zpl_string str, isize add_len) {
    isize available = zpl_string_available_space(str);

    // NOTE: Return if there is enough space left
    if (available >= add_len) {
        return str;
    } else {
        isize new_len, old_size, new_size;
        void *ptr, *new_ptr;
        zpl_allocator a = ZPL_STRING_HEADER(str)->allocator;
        zpl_string_header *header;

        new_len = zpl_string_length(str) + add_len;
        ptr = ZPL_STRING_HEADER(str);
        old_size = zpl_size_of(zpl_string_header) + zpl_string_length(str) + 1;
        new_size = zpl_size_of(zpl_string_header) + new_len + 1;

        new_ptr = zpl_resize(a, ptr, old_size, new_size);
        if (new_ptr == NULL) return NULL;

        header = cast(zpl_string_header *) new_ptr;
        header->allocator = a;

        str = cast(zpl_string)(header + 1);
        zpl__set_string_capacity(str, new_len);

        return str;
    }
}

zpl_inline isize zpl_string_allocation_size(zpl_string const str) {
    isize cap = zpl_string_capacity(str);
    return zpl_size_of(zpl_string_header) + cap;
}

zpl_inline b32 zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs) {
    isize lhs_len, rhs_len, i;
    lhs_len = zpl_string_length(lhs);
    rhs_len = zpl_string_length(rhs);
    if (lhs_len != rhs_len) return false;

    for (i = 0; i < lhs_len; i++) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

zpl_string zpl_string_trim(zpl_string str, char const *cut_set) {
    char *start, *end, *start_pos, *end_pos;
    isize len;

    start_pos = start = str;
    end_pos = end = str + zpl_string_length(str) - 1;

    while (start_pos <= end && zpl_char_first_occurence(cut_set, *start_pos)) start_pos++;
    while (end_pos > start_pos && zpl_char_first_occurence(cut_set, *end_pos)) end_pos--;

    len = cast(isize)((start_pos > end_pos) ? 0 : ((end_pos - start_pos) + 1));

    if (str != start_pos) zpl_memmove(str, start_pos, len);
    str[len] = '\0';

    zpl__set_string_length(str, len);

    return str;
}

zpl_inline zpl_string zpl_string_trim_space(zpl_string str) { return zpl_string_trim(str, " \t\r\n\v\f"); }

zpl_string zpl_string_append_rune(zpl_string str, Rune r) {
    if (r >= 0) {
        u8 buf[8] = { 0 };
        isize len = zpl_utf8_encode_rune(buf, r);
        return zpl_string_append_length(str, buf, len);
    }

    return str;
}

zpl_string zpl_string_append_fmt(zpl_string str, char const *fmt, ...) {
    isize res;
    char buf[4096] = { 0 };
    va_list va;
    va_start(va, fmt);
    res = zpl_snprintf_va(buf, zpl_count_of(buf) - 1, fmt, va) - 1;
    va_end(va);
    return zpl_string_append_length(str, buf, res);
}

////////////////////////////////////////////////////////////////
//
// Windows UTF-8 Handling
//
//

u16 *zpl_utf8_to_ucs2(u16 *buffer, isize len, u8 const *str) {
    Rune c;
    isize i = 0;
    len--;
    while (*str) {
        if (i >= len) return NULL;
        if (!(*str & 0x80)) {
            buffer[i++] = *str++;
        } else if ((*str & 0xe0) == 0xc0) {
            if (*str < 0xc2) return NULL;
            c = (*str++ & 0x1f) << 6;
            if ((*str & 0xc0) != 0x80) return NULL;
            buffer[i++] = cast(u16)(c + (*str++ & 0x3f));
        } else if ((*str & 0xf0) == 0xe0) {
            if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf)) return NULL;
            if (*str == 0xed && str[1] > 0x9f) // str[1] < 0x80 is checked below
                return NULL;
            c = (*str++ & 0x0f) << 12;
            if ((*str & 0xc0) != 0x80) return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80) return NULL;
            buffer[i++] = cast(u16)(c + (*str++ & 0x3f));
        } else if ((*str & 0xf8) == 0xf0) {
            if (*str > 0xf4) return NULL;
            if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf)) return NULL;
            if (*str == 0xf4 && str[1] > 0x8f) // str[1] < 0x80 is checked below
                return NULL;
            c = (*str++ & 0x07) << 18;
            if ((*str & 0xc0) != 0x80) return NULL;
            c += (*str++ & 0x3f) << 12;
            if ((*str & 0xc0) != 0x80) return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80) return NULL;
            c += (*str++ & 0x3f);
            // UTF-8 encodings of values used in surrogate pairs are invalid
            if ((c & 0xfffff800) == 0xd800) return NULL;
            if (c >= 0x10000) {
                c -= 0x10000;
                if (i + 2 > len) return NULL;
                buffer[i++] = 0xd800 | (0x3ff & (c >> 10));
                buffer[i++] = 0xdc00 | (0x3ff & (c));
            }
        } else {
            return NULL;
        }
    }
    buffer[i] = 0;
    return buffer;
}

u8 *zpl_ucs2_to_utf8(u8 *buffer, isize len, u16 const *str) {
    isize i = 0;
    len--;
    while (*str) {
        if (*str < 0x80) {
            if (i + 1 > len) return NULL;
            buffer[i++] = (char)*str++;
        } else if (*str < 0x800) {
            if (i + 2 > len) return NULL;
            buffer[i++] = cast(char)(0xc0 + (*str >> 6));
            buffer[i++] = cast(char)(0x80 + (*str & 0x3f));
            str += 1;
        } else if (*str >= 0xd800 && *str < 0xdc00) {
            Rune c;
            if (i + 4 > len) return NULL;
            c = ((str[0] - 0xd800) << 10) + ((str[1]) - 0xdc00) + 0x10000;
            buffer[i++] = cast(char)(0xf0 + (c >> 18));
            buffer[i++] = cast(char)(0x80 + ((c >> 12) & 0x3f));
            buffer[i++] = cast(char)(0x80 + ((c >> 6) & 0x3f));
            buffer[i++] = cast(char)(0x80 + ((c)&0x3f));
            str += 2;
        } else if (*str >= 0xdc00 && *str < 0xe000) {
            return NULL;
        } else {
            if (i + 3 > len) return NULL;
            buffer[i++] = 0xe0 + (*str >> 12);
            buffer[i++] = 0x80 + ((*str >> 6) & 0x3f);
            buffer[i++] = 0x80 + ((*str) & 0x3f);
            str += 1;
        }
    }
    buffer[i] = 0;
    return buffer;
}

u16 *zpl_utf8_to_ucs2_buf(u8 const *str) { // NOTE: Uses locally persisting buffer
    zpl_local_persist u16 buf[4096];
    return zpl_utf8_to_ucs2(buf, zpl_count_of(buf), str);
}

u8 *zpl_ucs2_to_utf8_buf(u16 const *str) { // NOTE: Uses locally persisting buffer
    zpl_local_persist u8 buf[4096];
    return zpl_ucs2_to_utf8(buf, zpl_count_of(buf), str);
}

zpl_global u8 const zpl__utf8_first[256] = {
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x00-0x0F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x10-0x1F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x20-0x2F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x30-0x3F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x40-0x4F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x50-0x5F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x60-0x6F
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x70-0x7F
    0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0x80-0x8F
    0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0x90-0x9F
    0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xA0-0xAF
    0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xB0-0xBF
    0xf1, 0xf1, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // 0xC0-0xCF
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // 0xD0-0xDF
    0x13, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x23, 0x03, 0x03, // 0xE0-0xEF
    0x34, 0x04, 0x04, 0x04, 0x44, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xF0-0xFF
};

#define zpl_utf8_accept_range_t zpl_utf8_accept_range
typedef struct zpl_utf8_accept_range {
    u8 lo, hi;
} zpl_utf8_accept_range;

zpl_global zpl_utf8_accept_range const zpl__utf8_accept_ranges[] = {
    { 0x80, 0xbf }, { 0xa0, 0xbf }, { 0x80, 0x9f }, { 0x90, 0xbf }, { 0x80, 0x8f },
};

isize zpl_utf8_decode(u8 const *str, isize str_len, Rune *codepoint_out) {

    isize width = 0;
    Rune codepoint = ZPL_RUNE_INVALID;

    if (str_len > 0) {
        u8 s0 = str[0];
        u8 x = zpl__utf8_first[s0], sz;
        u8 b1, b2, b3;
        zpl_utf8_accept_range accept;
        if (x >= 0xf0) {
            Rune mask = (cast(Rune) x << 31) >> 31;
            codepoint = (cast(Rune) s0 & (~mask)) | (ZPL_RUNE_INVALID & mask);
            width = 1;
            goto end;
        }
        if (s0 < 0x80) {
            codepoint = s0;
            width = 1;
            goto end;
        }

        sz = x & 7;
        accept = zpl__utf8_accept_ranges[x >> 4];
        if (str_len < zpl_size_of(sz)) goto invalid_codepoint;

        b1 = str[1];
        if (b1 < accept.lo || accept.hi < b1) goto invalid_codepoint;

        if (sz == 2) {
            codepoint = (cast(Rune) s0 & 0x1f) << 6 | (cast(Rune) b1 & 0x3f);
            width = 2;
            goto end;
        }

        b2 = str[2];
        if (!zpl_is_between(b2, 0x80, 0xbf)) goto invalid_codepoint;

        if (sz == 3) {
            codepoint = (cast(Rune) s0 & 0x1f) << 12 | (cast(Rune) b1 & 0x3f) << 6 | (cast(Rune) b2 & 0x3f);
            width = 3;
            goto end;
        }

        b3 = str[3];
        if (!zpl_is_between(b3, 0x80, 0xbf)) goto invalid_codepoint;

        codepoint = (cast(Rune) s0 & 0x07) << 18 | (cast(Rune) b1 & 0x3f) << 12 | (cast(Rune) b2 & 0x3f) << 6 |
                    (cast(Rune) b3 & 0x3f);
        width = 4;
        goto end;

    invalid_codepoint:
        codepoint = ZPL_RUNE_INVALID;
        width = 1;
    }

end:
    if (codepoint_out) *codepoint_out = codepoint;
    return width;
}

isize zpl_utf8_codepoint_size(u8 const *str, isize str_len) {
    isize i = 0;
    for (; i < str_len && str[i]; i++) {
        if ((str[i] & 0xc0) != 0x80) break;
    }
    return i + 1;
}

isize zpl_utf8_encode_rune(u8 buf[4], Rune r) {
    u32 i = cast(u32) r;
    u8 mask = 0x3f;
    if (i <= (1 << 7) - 1) {
        buf[0] = cast(u8) r;
        return 1;
    }
    if (i <= (1 << 11) - 1) {
        buf[0] = 0xc0 | cast(u8)(r >> 6);
        buf[1] = 0x80 | (cast(u8)(r) & mask);
        return 2;
    }

    // Invalid or Surrogate range
    if (i > ZPL_RUNE_MAX || zpl_is_between(i, 0xd800, 0xdfff)) {
        r = ZPL_RUNE_INVALID;

        buf[0] = 0xe0 | cast(u8)(r >> 12);
        buf[1] = 0x80 | (cast(u8)(r >> 6) & mask);
        buf[2] = 0x80 | (cast(u8)(r) & mask);
        return 3;
    }

    if (i <= (1 << 16) - 1) {
        buf[0] = 0xe0 | cast(u8)(r >> 12);
        buf[1] = 0x80 | (cast(u8)(r >> 6) & mask);
        buf[2] = 0x80 | (cast(u8)(r) & mask);
        return 3;
    }

    buf[0] = 0xf0 | cast(u8)(r >> 18);
    buf[1] = 0x80 | (cast(u8)(r >> 12) & mask);
    buf[2] = 0x80 | (cast(u8)(r >> 6) & mask);
    buf[3] = 0x80 | (cast(u8)(r) & mask);
    return 4;
}