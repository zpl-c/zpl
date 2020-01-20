// file: source/core/string.c

////////////////////////////////////////////////////////////////
//
// Char things
//
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

zpl_internal zpl_isize zpl__scan_zpl_i64(const char *text, zpl_i32 base, zpl_i64 *value) {
    const char *text_begin = text;
    zpl_i64 result = 0;
    zpl_b32 negative = false;

    if (*text == '-') {
        negative = true;
        text++;
    }

    if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

    for (;;) {
        zpl_i64 v;
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

zpl_internal zpl_isize zpl__scan_zpl_u64(const char *text, zpl_i32 base, zpl_u64 *value) {
    const char *text_begin = text;
    zpl_u64 result = 0;

    if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

    for (;;) {
        zpl_u64 v;
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
zpl_u64 zpl_str_to_u64(const char *str, char **end_ptr, zpl_i32 base) {
    zpl_isize len;
    zpl_u64 value = 0;

    if (!base) {
        if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
            base = 16;
        else
            base = 10;
    }

    len = zpl__scan_zpl_u64(str, base, &value);
    if (end_ptr) *end_ptr = (char *)str + len;
    return value;
}

zpl_i64 zpl_str_to_i64(const char *str, char **end_ptr, zpl_i32 base) {
    zpl_isize len;
    zpl_i64 value;

    if (!base) {
        if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
            base = 16;
        else
            base = 10;
    }

    len = zpl__scan_zpl_i64(str, base, &value);
    if (end_ptr) *end_ptr = (char *)str + len;
    return value;
}

// TODO: Are these good enough for characters?
zpl_global const char zpl__num_to_char_table[] = "0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"@$";

void zpl_i64_to_str(zpl_i64 value, char *string, zpl_i32 base) {
    char *buf = string;
    zpl_b32 negative = false;
    zpl_u64 v;

    if (value < 0) {
        negative = true;
        value = -value;
    }

    v = cast(zpl_u64) value;
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

void zpl_u64_to_str(zpl_u64 value, char *string, zpl_i32 base) {
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

zpl_f64 zpl_str_to_f64(const char *str, char **end_ptr) {
    zpl_f64 result, value, sign, scale;
    zpl_i32 frac;

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
        zpl_f64 pow10 = 10.0;
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
        zpl_u32 exp;

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



////////////////////////////////////////////////////////////////
//
// Windows UTF-8 Handling
//
//

zpl_u16 *zpl_utf8_to_ucs2(zpl_u16 *buffer, zpl_isize len, zpl_u8 const *str) {
    zpl_rune c;
    zpl_isize i = 0;
    len--;
    while (*str) {
        if (i >= len) return NULL;
        if (!(*str & 0x80)) {
            buffer[i++] = *str++;
        } else if ((*str & 0xe0) == 0xc0) {
            if (*str < 0xc2) return NULL;
            c = (*str++ & 0x1f) << 6;
            if ((*str & 0xc0) != 0x80) return NULL;
            buffer[i++] = cast(zpl_u16)(c + (*str++ & 0x3f));
        } else if ((*str & 0xf0) == 0xe0) {
            if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf)) return NULL;
            if (*str == 0xed && str[1] > 0x9f) // str[1] < 0x80 is checked below
                return NULL;
            c = (*str++ & 0x0f) << 12;
            if ((*str & 0xc0) != 0x80) return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80) return NULL;
            buffer[i++] = cast(zpl_u16)(c + (*str++ & 0x3f));
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

zpl_u8 *zpl_ucs2_to_utf8(zpl_u8 *buffer, zpl_isize len, zpl_u16 const *str) {
    zpl_isize i = 0;
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
            zpl_rune c;
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

zpl_u16 *zpl_utf8_to_ucs2_buf(zpl_u8 const *str) { // NOTE: Uses locally persisting buffer
    zpl_local_persist zpl_u16 buf[4096];
    return zpl_utf8_to_ucs2(buf, zpl_count_of(buf), str);
}

zpl_u8 *zpl_ucs2_to_utf8_buf(zpl_u16 const *str) { // NOTE: Uses locally persisting buffer
    zpl_local_persist zpl_u8 buf[4096];
    return zpl_ucs2_to_utf8(buf, zpl_count_of(buf), str);
}

zpl_global zpl_u8 const zpl__utf8_first[256] = {
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


typedef struct zpl_utf8_accept_range {
    zpl_u8 lo, hi;
} zpl_utf8_accept_range;

zpl_global zpl_utf8_accept_range const zpl__utf8_accept_ranges[] = {
    { 0x80, 0xbf }, { 0xa0, 0xbf }, { 0x80, 0x9f }, { 0x90, 0xbf }, { 0x80, 0x8f },
};

zpl_isize zpl_utf8_decode(zpl_u8 const *str, zpl_isize str_len, zpl_rune *codepoint_out) {

    zpl_isize width = 0;
    zpl_rune codepoint = ZPL_RUNE_INVALID;

    if (str_len > 0) {
        zpl_u8 s0 = str[0];
        zpl_u8 x = zpl__utf8_first[s0], sz;
        zpl_u8 b1, b2, b3;
        zpl_utf8_accept_range accept;
        if (x >= 0xf0) {
            zpl_rune mask = (cast(zpl_rune) x << 31) >> 31;
            codepoint = (cast(zpl_rune) s0 & (~mask)) | (ZPL_RUNE_INVALID & mask);
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
            codepoint = (cast(zpl_rune) s0 & 0x1f) << 6 | (cast(zpl_rune) b1 & 0x3f);
            width = 2;
            goto end;
        }

        b2 = str[2];
        if (!zpl_is_between(b2, 0x80, 0xbf)) goto invalid_codepoint;

        if (sz == 3) {
            codepoint = (cast(zpl_rune) s0 & 0x1f) << 12 | (cast(zpl_rune) b1 & 0x3f) << 6 | (cast(zpl_rune) b2 & 0x3f);
            width = 3;
            goto end;
        }

        b3 = str[3];
        if (!zpl_is_between(b3, 0x80, 0xbf)) goto invalid_codepoint;

        codepoint = (cast(zpl_rune) s0 & 0x07) << 18 | (cast(zpl_rune) b1 & 0x3f) << 12 | (cast(zpl_rune) b2 & 0x3f) << 6 |
            (cast(zpl_rune) b3 & 0x3f);
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

zpl_isize zpl_utf8_codepoint_size(zpl_u8 const *str, zpl_isize str_len) {
    zpl_isize i = 0;
    for (; i < str_len && str[i]; i++) {
        if ((str[i] & 0xc0) != 0x80) break;
    }
    return i + 1;
}

zpl_isize zpl_utf8_encode_rune(zpl_u8 buf[4], zpl_rune r) {
    zpl_u32 i = cast(zpl_u32) r;
    zpl_u8 mask = 0x3f;
    if (i <= (1 << 7) - 1) {
        buf[0] = cast(zpl_u8) r;
        return 1;
    }
    if (i <= (1 << 11) - 1) {
        buf[0] = 0xc0 | cast(zpl_u8)(r >> 6);
        buf[1] = 0x80 | (cast(zpl_u8)(r) & mask);
        return 2;
    }

    // Invalid or Surrogate range
    if (i > ZPL_RUNE_MAX || zpl_is_between(i, 0xd800, 0xdfff)) {
        r = ZPL_RUNE_INVALID;

        buf[0] = 0xe0 | cast(zpl_u8)(r >> 12);
        buf[1] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
        buf[2] = 0x80 | (cast(zpl_u8)(r) & mask);
        return 3;
    }

    if (i <= (1 << 16) - 1) {
        buf[0] = 0xe0 | cast(zpl_u8)(r >> 12);
        buf[1] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
        buf[2] = 0x80 | (cast(zpl_u8)(r) & mask);
        return 3;
    }

    buf[0] = 0xf0 | cast(zpl_u8)(r >> 18);
    buf[1] = 0x80 | (cast(zpl_u8)(r >> 12) & mask);
    buf[2] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
    buf[3] = 0x80 | (cast(zpl_u8)(r) & mask);
    return 4;
}

ZPL_END_C_DECLS
