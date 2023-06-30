// file: header/core/string.h

/** @file string.c
@brief String operations and library
@defgroup string String library

Offers methods for c-string manipulation, but also a string library based on gb_string, which is c-string friendly.

@{
*/

////////////////////////////////////////////////////////////////
//
// Char Functions
//
//


ZPL_BEGIN_C_DECLS

ZPL_DEF_INLINE char    zpl_char_to_lower(char c);
ZPL_DEF_INLINE char    zpl_char_to_upper(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_space(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_digit(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_hex_digit(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_alpha(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_alphanumeric(char c);
ZPL_DEF_INLINE zpl_i32 zpl_digit_to_int(char c);
ZPL_DEF_INLINE zpl_i32 zpl_hex_digit_to_int(char c);
ZPL_DEF_INLINE zpl_u8  zpl_char_to_hex_digit(char c);
ZPL_DEF_INLINE zpl_b32 zpl_char_is_control(char c);

// NOTE: ASCII only
ZPL_DEF_INLINE void zpl_str_to_lower(char *str);
ZPL_DEF_INLINE void zpl_str_to_upper(char *str);

ZPL_DEF_INLINE char const *zpl_str_trim(char const *str, zpl_b32 catch_newline);
ZPL_DEF_INLINE char const *zpl_str_skip(char const *str, char c);
ZPL_DEF_INLINE char const *zpl_str_skip_any(char const *str, char const*char_list);
ZPL_DEF_INLINE char const *zpl_str_skip_literal(char const *str, char c);
ZPL_DEF_INLINE char const *zpl_str_control_skip(char const *str, char c);

ZPL_DEF_INLINE zpl_isize   zpl_strlen(const char *str);
ZPL_DEF_INLINE zpl_isize   zpl_strnlen(const char *str, zpl_isize max_len);
ZPL_DEF_INLINE zpl_i32     zpl_strcmp(const char *s1, const char *s2);
ZPL_DEF_INLINE zpl_i32     zpl_strncmp(const char *s1, const char *s2, zpl_isize len);
ZPL_DEF_INLINE char       *zpl_strcpy(char *dest, const char *source);
ZPL_DEF_INLINE char       *zpl_strcat(char *dest, const char *source);
ZPL_DEF_INLINE char       *zpl_strncpy(char *dest, const char *source, zpl_isize len);
ZPL_DEF_INLINE zpl_isize   zpl_strlcpy(char *dest, const char *source, zpl_isize len);
ZPL_DEF_INLINE char       *zpl_strrev(char *str); // NOTE: ASCII only
ZPL_DEF_INLINE const char *zpl_strtok(char *output, const char *src, const char *delimit);
ZPL_DEF_INLINE const char *zpl_strntok(char *output, zpl_isize len, const char *src, const char *delimit);

ZPL_DEF_INLINE char   *zpl_strdup(zpl_allocator a, char *src, zpl_isize max_len);
ZPL_DEF_INLINE char  **zpl_str_split_lines(zpl_allocator alloc, char *source, zpl_b32 strip_whitespace);

#define zpl_str_expand(str) str, zpl_strlen(str)
#define zpl_str_advance_while(str, cond) \
    do { \
        ++str; \
    } while ((cond));

ZPL_DEF_INLINE zpl_b32 zpl_str_has_prefix(const char *str, const char *prefix);
ZPL_DEF_INLINE zpl_b32 zpl_str_has_suffix(const char *str, const char *suffix);

ZPL_DEF_INLINE const char *zpl_char_first_occurence(const char *str, char c);
ZPL_DEF_INLINE const char *zpl_char_last_occurence(const char *str, char c);
#define zpl_strchr zpl_char_first_occurence

ZPL_DEF_INLINE void zpl_str_concat(char *dest, zpl_isize dest_len, const char *src_a, zpl_isize src_a_len, const char *src_b, zpl_isize src_b_len);

ZPL_DEF zpl_u64 zpl_str_to_u64(const char *str, char **end_ptr, zpl_i32 base); // TODO: Support more than just decimal and hexadecimal
ZPL_DEF zpl_i64 zpl_str_to_i64(const char *str, char **end_ptr, zpl_i32 base); // TODO: Support more than just decimal and hexadecimal
ZPL_DEF zpl_f64 zpl_str_to_f64(const char *str, char **end_ptr);
ZPL_DEF void    zpl_i64_to_str(zpl_i64 value, char *string, zpl_i32 base);
ZPL_DEF void    zpl_u64_to_str(zpl_u64 value, char *string, zpl_i32 base);

ZPL_DEF_INLINE zpl_f32 zpl_str_to_f32(const char *str, char **end_ptr);

////////////////////////////////////////////////////////////////
//
// UTF-8 Handling
//
//

// NOTE: Does not check if utf-8 string is valid
ZPL_IMPL_INLINE zpl_isize zpl_utf8_strlen(zpl_u8 const *str);
ZPL_IMPL_INLINE zpl_isize zpl_utf8_strnlen(zpl_u8 const *str, zpl_isize max_len);

// NOTE: Windows doesn't handle 8 bit filenames well
ZPL_DEF zpl_u16 *zpl_utf8_to_ucs2(zpl_u16 *buffer, zpl_isize len, zpl_u8 const *str);
ZPL_DEF zpl_u8  *zpl_ucs2_to_utf8(zpl_u8 *buffer, zpl_isize len, zpl_u16 const *str);
ZPL_DEF zpl_u16 *zpl_utf8_to_ucs2_buf(zpl_u8 const *str); // NOTE: Uses locally persisting buffer
ZPL_DEF zpl_u8  *zpl_ucs2_to_utf8_buf(zpl_u16 const *str); // NOTE: Uses locally persisting buffer

// NOTE: Returns size of codepoint in bytes
ZPL_DEF zpl_isize zpl_utf8_decode(zpl_u8 const *str, zpl_isize str_len, zpl_rune *codepoint);
ZPL_DEF zpl_isize zpl_utf8_codepoint_size(zpl_u8 const *str, zpl_isize str_len);
ZPL_DEF zpl_isize zpl_utf8_encode_rune(zpl_u8 buf[4], zpl_rune r);

/* inlines */

ZPL_IMPL_INLINE char zpl_char_to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return 'a' + (c - 'A');
    return c;
}

ZPL_IMPL_INLINE char zpl_char_to_upper(char c) {
    if (c >= 'a' && c <= 'z') return 'A' + (c - 'a');
    return c;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_space(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v') return true;
    return false;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_digit(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_hex_digit(char c) {
    if (zpl_char_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return true;
    return false;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_alpha(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
    return false;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_alphanumeric(char c) { return zpl_char_is_alpha(c) || zpl_char_is_digit(c); }

ZPL_IMPL_INLINE zpl_i32 zpl_digit_to_int(char c) { return zpl_char_is_digit(c) ? c - '0' : c - 'W'; }

ZPL_IMPL_INLINE zpl_i32 zpl_hex_digit_to_int(char c) {
    if (zpl_char_is_digit(c))
        return zpl_digit_to_int(c);
    else if (zpl_is_between(c, 'a', 'f'))
        return c - 'a' + 10;
    else if (zpl_is_between(c, 'A', 'F'))
        return c - 'A' + 10;
    return -1;
}

ZPL_IMPL_INLINE zpl_u8 zpl_char_to_hex_digit(char c) {
    if (c >= '0' && c <= '9')
        return (zpl_u8)(c - '0');
    if (c >= 'a' && c <= 'f')
        return (zpl_u8)(c - 'a');
    if (c >= 'A' && c <= 'F')
        return (zpl_u8)(c - 'A');
    return 0;
}

ZPL_IMPL_INLINE void zpl_str_to_lower(char *str) {
    if (!str) return;
    while (*str) {
        *str = zpl_char_to_lower(*str);
        str++;
    }
}

ZPL_IMPL_INLINE void zpl_str_to_upper(char *str) {
    if (!str) return;
    while (*str) {
        *str = zpl_char_to_upper(*str);
        str++;
    }
}

ZPL_IMPL_INLINE zpl_isize zpl_strlen(const char *str) {
    if (str == NULL) { return 0; }
    const char *p = str;
    while (*str) str++;
    return str-p;
}

ZPL_IMPL_INLINE zpl_isize zpl_strnlen(const char *str, zpl_isize max_len) {
    const char *end = cast(const char *) zpl_memchr(str, 0, max_len);
    if (end) return end - str;
    return max_len;
}

ZPL_IMPL_INLINE zpl_isize zpl_utf8_strlen(zpl_u8 const *str) {
    zpl_isize count = 0;
    for (; *str; count++) {
        zpl_u8 c = *str;
        zpl_isize inc = 0;
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

ZPL_IMPL_INLINE zpl_isize zpl_utf8_strnlen(zpl_u8 const *str, zpl_isize max_len) {
    zpl_isize count = 0;
    for (; *str && max_len > 0; count++) {
        zpl_u8 c = *str;
        zpl_isize inc = 0;
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

ZPL_IMPL_INLINE zpl_i32 zpl_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) { s1++, s2++; }
    return *(zpl_u8 *)s1 - *(zpl_u8 *)s2;
}

ZPL_IMPL_INLINE char *zpl_strcpy(char *dest, const char *source) {
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        char *str = dest;
        while (*source) *str++ = *source++;
    }
    return dest;
}

ZPL_IMPL_INLINE char *zpl_strcat(char *dest, const char *source) {
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        char *str = dest;
        while (*str) ++str;
        while (*source) *str++ = *source++;
    }
    return dest;
}

ZPL_IMPL_INLINE char *zpl_strncpy(char *dest, const char *source, zpl_isize len) {
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

ZPL_IMPL_INLINE zpl_isize zpl_strlcpy(char *dest, const char *source, zpl_isize len) {
    zpl_isize result = 0;
    ZPL_ASSERT_NOT_NULL(dest);
    if (source) {
        const char *source_start = source;
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

ZPL_IMPL_INLINE char *zpl_strrev(char *str) {
    zpl_isize len = zpl_strlen(str);
    char *a = str + 0;
    char *b = str + len - 1;
    len /= 2;
    while (len--) {
        zpl_swap(char, *a, *b);
        a++, b--;
    }
    return str;
}

ZPL_IMPL_INLINE zpl_i32 zpl_strncmp(const char *s1, const char *s2, zpl_isize len) {
    for (; len > 0; s1++, s2++, len--) {
        if (*s1 != *s2)
            return ((s1 < s2) ? -1 : +1);
        else if (*s1 == '\0')
            return 0;
    }
    return 0;
}

ZPL_IMPL_INLINE const char *zpl_strtok(char *output, const char *src, const char *delimit) {
    while (*src && zpl_char_first_occurence(delimit, *src) == NULL) *output++ = *src++;

    *output = 0;
    return *src ? src + 1 : src;
}

ZPL_IMPL_INLINE const char *zpl_strntok(char *output, zpl_isize len, const char *src, const char *delimit) {
    ZPL_ASSERT(len > 0);
    *(output+len-1) = 0;
    while (*src && zpl_char_first_occurence(delimit, *src) == NULL && len > 0) {
        *output++ = *src++;
        len --;
    }

    if (len > 0)
        *output = 0;
    return *src ? src + 1 : src;
}

ZPL_IMPL_INLINE zpl_b32 zpl_char_is_control(char c) {
    return !!zpl_strchr("\"\\/bfnrt", c);
}

ZPL_IMPL_INLINE zpl_b32 zpl__is_special_char(char c) { return !!zpl_strchr("<>:/", c); }
ZPL_IMPL_INLINE zpl_b32 zpl__is_assign_char(char c) { return !!zpl_strchr(":=|", c); }
ZPL_IMPL_INLINE zpl_b32 zpl__is_delim_char(char c) { return !!zpl_strchr(",|\n", c); }


ZPL_IMPL_INLINE char const *zpl_str_control_skip(char const *str, char c) {
    while ((*str && *str != c) || (*(str - 1) == '\\' && *str == c && zpl_char_is_control(c))) { ++str; }

    return str;
}


ZPL_IMPL_INLINE zpl_b32 zpl_str_has_prefix(const char *str, const char *prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) return false;
    }
    return true;
}

ZPL_IMPL_INLINE zpl_b32 zpl_str_has_suffix(const char *str, const char *suffix) {
    zpl_isize i = zpl_strlen(str);
    zpl_isize j = zpl_strlen(suffix);
    if (j <= i) return zpl_strcmp(str + i - j, suffix) == 0;
    return false;
}

ZPL_IMPL_INLINE const char *zpl_char_first_occurence(const char *s, char c) {
    char ch = c;
    for (; *s != ch; s++) {
        if (*s == '\0') return NULL;
    }
    return s;
}

ZPL_IMPL_INLINE const char *zpl_char_last_occurence(const char *s, char c) {
    char *result = (char*)NULL;
    do {
        if (*s == c) result = (char *)s;
    } while (*s++);

    return result;
}

ZPL_IMPL_INLINE char const *zpl_str_trim(char const *str, zpl_b32 catch_newline)
{
    while (*str && zpl_char_is_space(*str) && (!catch_newline || (catch_newline && *str != '\n'))) { ++str; }
    return str;
}

ZPL_IMPL_INLINE char const *zpl_str_skip(char const *str, char c) {
    while (*str && *str != c) { ++str; }
    return str;
}

ZPL_IMPL_INLINE char const *zpl_str_skip_any(char const *str, char const*char_list) {
    char const *closest_ptr = cast(char const *) zpl_ptr_add((void*)str, zpl_strlen(str));
    zpl_isize char_list_count = zpl_strlen(char_list);
    for (zpl_isize i = 0; i < char_list_count; i++) {
        char const *p = zpl_str_skip(str, char_list[i]);
        closest_ptr = zpl_min(closest_ptr, p);
    }
    return closest_ptr;
}

ZPL_IMPL_INLINE char const *zpl_str_skip_literal(char const *str, char c) {
    if (*str == '\0' || *str == c)
        return str;
    str++;

    while ((*str && *str != c) || (*str == c && *(str-1) == '\\')) { ++str; }
    return str;
}

ZPL_IMPL_INLINE void zpl_str_concat(char *dest, zpl_isize dest_len, const char *src_a, zpl_isize src_a_len, const char *src_b,
                               zpl_isize src_b_len) {
    ZPL_ASSERT(dest_len >= src_a_len + src_b_len + 1);
    if (dest) {
        zpl_memcopy(dest, src_a, src_a_len);
        zpl_memcopy(dest + src_a_len, src_b, src_b_len);
        dest[src_a_len + src_b_len] = '\0';
    }
}

ZPL_IMPL_INLINE zpl_f32 zpl_str_to_f32(const char *str, char **end_ptr) {
    zpl_f64 f = zpl_str_to_f64(str, end_ptr);
    zpl_f32 r = cast(zpl_f32) f;
    return r;
}

ZPL_IMPL_INLINE char *zpl_strdup(zpl_allocator a, char *src, zpl_isize max_len) {
    ZPL_ASSERT_NOT_NULL(src);
    zpl_isize len = zpl_strlen(src);
    char *dest = cast(char *) zpl_alloc(a, max_len);
    zpl_memset(dest + len, 0, max_len - len);
    zpl_strncpy(dest, src, max_len);

    return dest;
}

ZPL_IMPL_INLINE char **zpl_str_split_lines(zpl_allocator alloc, char *source, zpl_b32 strip_whitespace) {
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

ZPL_END_C_DECLS
