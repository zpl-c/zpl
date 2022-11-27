// file: source/core/print.c


ZPL_BEGIN_C_DECLS

zpl_isize zpl_printf_va(char const *fmt, va_list va) {
    return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), fmt, va);
}

zpl_isize zpl_printf_err_va(char const *fmt, va_list va) {
    return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_ERROR), fmt, va);
}

zpl_isize zpl_fprintf_va(struct zpl_file *f, char const *fmt, va_list va) {
    zpl_local_persist zpl_thread_local char buf[ZPL_PRINTF_MAXLEN];
    zpl_isize len = zpl_snprintf_va(buf, zpl_size_of(buf), fmt, va);
    zpl_b32 res = zpl_file_write(f, buf, len - 1); // NOTE: prevent extra whitespace
    return res ? len : -1;
}

char *zpl_bprintf_va(char const *fmt, va_list va) {
    zpl_local_persist zpl_thread_local char buffer[ZPL_PRINTF_MAXLEN];
    zpl_snprintf_va(buffer, zpl_size_of(buffer), fmt, va);
    return buffer;
}

zpl_isize zpl_asprintf_va(zpl_allocator allocator, char **buffer, char const *fmt, va_list va) {
    zpl_local_persist zpl_thread_local char tmp[ZPL_PRINTF_MAXLEN];
    ZPL_ASSERT_NOT_NULL(buffer);
    zpl_isize res;
    res = zpl_snprintf_va(tmp, zpl_size_of(tmp), fmt, va);
    *buffer = zpl_alloc_str(allocator, tmp);
    return res;
}

zpl_isize zpl_printf(char const *fmt, ...) {
    zpl_isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_printf_va(fmt, va);
    va_end(va);
    return res;
}

zpl_isize zpl_printf_err(char const *fmt, ...) {
    zpl_isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_printf_err_va(fmt, va);
    va_end(va);
    return res;
}

zpl_isize zpl_fprintf(struct zpl_file *f, char const *fmt, ...) {
    zpl_isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_fprintf_va(f, fmt, va);
    va_end(va);
    return res;
}

char *zpl_bprintf(char const *fmt, ...) {
    va_list va;
    char *str;
    va_start(va, fmt);
    str = zpl_bprintf_va(fmt, va);
    va_end(va);
    return str;
}

zpl_isize zpl_asprintf(zpl_allocator allocator, char **buffer, char const *fmt, ...) {
    zpl_isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_asprintf_va(allocator, buffer, fmt, va);
    va_end(va);
    return res;
}

zpl_isize zpl_snprintf(char *str, zpl_isize n, char const *fmt, ...) {
    zpl_isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_snprintf_va(str, n, fmt, va);
    va_end(va);
    return res;
}


enum {
    ZPL_FMT_MINUS = ZPL_BIT(0),
    ZPL_FMT_PLUS  = ZPL_BIT(1),
    ZPL_FMT_ALT   = ZPL_BIT(2),
    ZPL_FMT_SPACE = ZPL_BIT(3),
    ZPL_FMT_ZERO  = ZPL_BIT(4),

    ZPL_FMT_CHAR   = ZPL_BIT(5),
    ZPL_FMT_SHORT  = ZPL_BIT(6),
    ZPL_FMT_INT    = ZPL_BIT(7),
    ZPL_FMT_LONG   = ZPL_BIT(8),
    ZPL_FMT_LLONG  = ZPL_BIT(9),
    ZPL_FMT_SIZE   = ZPL_BIT(10),
    ZPL_FMT_INTPTR = ZPL_BIT(11),

    ZPL_FMT_UNSIGNED = ZPL_BIT(12),
    ZPL_FMT_LOWER    = ZPL_BIT(13),
    ZPL_FMT_UPPER    = ZPL_BIT(14),
    ZPL_FMT_WIDTH    = ZPL_BIT(15),

    ZPL_FMT_DONE = ZPL_BIT(30),

    ZPL_FMT_INTS =
        ZPL_FMT_CHAR | ZPL_FMT_SHORT | ZPL_FMT_INT  |
        ZPL_FMT_LONG | ZPL_FMT_LLONG | ZPL_FMT_SIZE | ZPL_FMT_INTPTR
};

typedef struct {
    zpl_i32 base;
    zpl_i32 flags;
    zpl_i32 width;
    zpl_i32 precision;
} zpl__format_info;

zpl_internal zpl_isize zpl__print_string(char *text, zpl_isize max_len, zpl__format_info *info, char const *str) {
    zpl_isize res = 0, len = 0;
    zpl_isize remaining = max_len;
    char *begin = text;

    if (str == NULL && max_len >= 6) {
        res += zpl_strlcpy(text, "(null)", 6);
        return res;
    }

    if (info && info->precision >= 0)
        len = zpl_strnlen(str, info->precision);
    else
        len = zpl_strlen(str);

    if (info && (info->width == 0 && info->flags & ZPL_FMT_WIDTH)) {
        return res;
    }

    if (info && (info->width == 0 || info->flags & ZPL_FMT_MINUS)) {
        if (info->precision > 0) len = info->precision < len ? info->precision : len;
        if (res+len > max_len) return res;
        res += zpl_strlcpy(text, str, len);
        text += res;

        if (info->width > res) {
            zpl_isize padding = info->width - len;

            char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
            while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
        }
    } else {
        if (info && (info->width > res)) {
            zpl_isize padding = info->width - len;
            char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
            while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
        }

        if (res+len > max_len) return res;
        res += zpl_strlcpy(text, str, len);
    }

    if (info) {
        if (info->flags & ZPL_FMT_UPPER)
            zpl_str_to_upper(begin);
        else if (info->flags & ZPL_FMT_LOWER)
            zpl_str_to_lower(begin);
    }

    return res;
}

zpl_internal zpl_isize zpl__print_char(char *text, zpl_isize max_len, zpl__format_info *info, char arg) {
    char str[2] = "";
    str[0] = arg;
    return zpl__print_string(text, max_len, info, str);
}

zpl_internal zpl_isize zpl__print_repeated_char(char *text, zpl_isize max_len, zpl__format_info *info, char arg) {
    zpl_isize res = 0;
    zpl_i32 rem = (info) ? (info->width > 0) ? info->width : 1 : 1;
    res = rem;
    while (rem-- > 0) *text++ = arg;

    return res;
}

zpl_internal zpl_isize zpl__print_i64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_i64 value) {
    char num[130];
    zpl_i64_to_str(value, num, info ? info->base : 10);
    return zpl__print_string(text, max_len, info, num);
}

zpl_internal zpl_isize zpl__print_u64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_u64 value) {
    char num[130];
    zpl_u64_to_str(value, num, info ? info->base : 10);
    return zpl__print_string(text, max_len, info, num);
}

zpl_internal zpl_isize zpl__print_f64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_b32 is_hexadecimal, zpl_f64 arg) {
    // TODO: Handle exponent notation
    zpl_isize width, len, remaining = max_len;
    char *text_begin = text;

    if (arg) {
        zpl_u64 value;
        if (arg < 0) {
            if (remaining > 1) *text = '-', remaining--;
            text++;
            arg = -arg;
        } else if (info->flags & ZPL_FMT_MINUS) {
            if (remaining > 1) *text = '+', remaining--;
            text++;
        }

        value = cast(zpl_u64) arg;
        len = zpl__print_u64(text, remaining, NULL, value);
        text += len;

        if (len >= remaining)
            remaining = zpl_min(remaining, 1);
        else
            remaining -= len;
        arg -= value;

        if (info->precision < 0) info->precision = 6;

        if ((info->flags & ZPL_FMT_ALT) || info->precision > 0) {
            zpl_i64 mult = 10;
            if (remaining > 1) *text = '.', remaining--;
            text++;
            while (info->precision-- > 0) {
                value = cast(zpl_u64)(arg * mult);
                len = zpl__print_u64(text, remaining, NULL, value);
                text += len;
                if (len >= remaining)
                    remaining = zpl_min(remaining, 1);
                else
                    remaining -= len;
                arg -= cast(zpl_f64) value / mult;
                mult *= 10;
            }
        }
    } else {
        if (remaining > 1) *text = '0', remaining--;
        text++;
        if (info->flags & ZPL_FMT_ALT) {
            if (remaining > 1) *text = '.', remaining--;
            text++;
        }
    }

    width = info->width - (text - text_begin);
    if (width > 0) {
        char fill = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
        char *end = text + remaining - 1;
        len = (text - text_begin);

        for (len = (text - text_begin); len--;) {
            if ((text_begin + len + width) < end) *(text_begin + len + width) = *(text_begin + len);
        }

        len = width;
        text += len;
        if (len >= remaining)
            remaining = zpl_min(remaining, 1);
        else
            remaining -= len;

        while (len--) {
            if (text_begin + len < end) text_begin[len] = fill;
        }
    }

    return (text - text_begin);
}

ZPL_NEVER_INLINE zpl_isize zpl_snprintf_va(char *text, zpl_isize max_len, char const *fmt, va_list va) {
    char const *text_begin = text;
    zpl_isize remaining = max_len, res;

    while (*fmt) {
        zpl__format_info info = { 0 };
        zpl_isize len = 0;
        info.precision = -1;

        while (*fmt && *fmt != '%' && remaining) *text++ = *fmt++;

        if (*fmt == '%') {
            do {
                switch (*++fmt) {
                case '-': {info.flags |= ZPL_FMT_MINUS; break;}
                case '+': {info.flags |= ZPL_FMT_PLUS; break;}
                case '#': {info.flags |= ZPL_FMT_ALT; break;}
                case ' ': {info.flags |= ZPL_FMT_SPACE; break;}
                case '0': {info.flags |= (ZPL_FMT_ZERO|ZPL_FMT_WIDTH); break;}
                default: {info.flags |= ZPL_FMT_DONE; break;}
                }
            } while (!(info.flags & ZPL_FMT_DONE));
        }

        // NOTE: Optional Width
        if (*fmt == '*') {
            int width = va_arg(va, int);
            if (width < 0) {
                info.flags |= ZPL_FMT_MINUS;
                info.width = -width;
            } else {
                info.width = width;
            }
            info.flags |= ZPL_FMT_WIDTH;
            fmt++;
        } else {
            info.width = cast(zpl_i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
            if (info.width != 0) {
                info.flags |= ZPL_FMT_WIDTH;
            }
        }

        // NOTE: Optional Precision
        if (*fmt == '.') {
            fmt++;
            if (*fmt == '*') {
                info.precision = va_arg(va, int);
                fmt++;
            } else {
                info.precision = cast(zpl_i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
            }
            info.flags &= ~ZPL_FMT_ZERO;
        }

        switch (*fmt++) {
            case 'h':
            if (*fmt == 'h') { // hh => char
                info.flags |= ZPL_FMT_CHAR;
                fmt++;
            } else { // h => short
                info.flags |= ZPL_FMT_SHORT;
            }
            break;

            case 'l':
            if (*fmt == 'l') { // ll => long long
                info.flags |= ZPL_FMT_LLONG;
                fmt++;
            } else { // l => long
                info.flags |= ZPL_FMT_LONG;
            }
            break;

            break;

            case 'z': // NOTE: zpl_usize
                info.flags |= ZPL_FMT_UNSIGNED;
                // fallthrough
            case 't': // NOTE: zpl_isize
                info.flags |= ZPL_FMT_SIZE;
                break;

            default: fmt--; break;
        }

        switch (*fmt) {
            case 'u':
                info.flags |= ZPL_FMT_UNSIGNED;
                // fallthrough
            case 'd':
            case 'i': info.base = 10; break;

            case 'o': info.base = 8; break;

            case 'x':
                info.base = 16;
                info.flags |= (ZPL_FMT_UNSIGNED | ZPL_FMT_LOWER);
                break;

            case 'X':
                info.base = 16;
                info.flags |= (ZPL_FMT_UNSIGNED | ZPL_FMT_UPPER);
                break;

            case 'f':
            case 'F':
            case 'g':
            case 'G': len = zpl__print_f64(text, remaining, &info, 0, va_arg(va, zpl_f64)); break;

            case 'a':
            case 'A':
                len = zpl__print_f64(text, remaining, &info, 1, va_arg(va, zpl_f64)); break;

            case 'c': len = zpl__print_char(text, remaining, &info, cast(char) va_arg(va, int)); break;

            case 's': len = zpl__print_string(text, remaining, &info, va_arg(va, char *)); break;

            case 'r': len = zpl__print_repeated_char(text, remaining, &info, va_arg(va, int)); break;

            case 'p':
                info.base = 16;
                info.flags |= (ZPL_FMT_LOWER | ZPL_FMT_UNSIGNED | ZPL_FMT_ALT | ZPL_FMT_INTPTR);
                break;

            case '%': len = zpl__print_char(text, remaining, &info, '%'); break;

            default: fmt--; break;
        }

        fmt++;

        if (info.base != 0) {
            if (info.flags & ZPL_FMT_UNSIGNED) {
                zpl_u64 value = 0;
                switch (info.flags & ZPL_FMT_INTS) {
                    case ZPL_FMT_CHAR:   value = cast(zpl_u64) cast(zpl_u8) va_arg(va, int); break;
                    case ZPL_FMT_SHORT:  value = cast(zpl_u64) cast(zpl_u16) va_arg(va, int); break;
                    case ZPL_FMT_LONG:   value = cast(zpl_u64) va_arg(va, unsigned long); break;
                    case ZPL_FMT_LLONG:  value = cast(zpl_u64) va_arg(va, unsigned long long); break;
                    case ZPL_FMT_SIZE:   value = cast(zpl_u64) va_arg(va, zpl_usize); break;
                    case ZPL_FMT_INTPTR: value = cast(zpl_u64) va_arg(va, zpl_uintptr); break;
                    default: value             = cast(zpl_u64) va_arg(va, unsigned int); break;
                }

                len = zpl__print_u64(text, remaining, &info, value);

            } else {
                zpl_i64 value = 0;
                switch (info.flags & ZPL_FMT_INTS) {
                    case ZPL_FMT_CHAR:   value = cast(zpl_i64) cast(zpl_i8) va_arg(va, int); break;
                    case ZPL_FMT_SHORT:  value = cast(zpl_i64) cast(zpl_i16) va_arg(va, int); break;
                    case ZPL_FMT_LONG:   value = cast(zpl_i64) va_arg(va, long); break;
                    case ZPL_FMT_LLONG:  value = cast(zpl_i64) va_arg(va, long long); break;
                    case ZPL_FMT_SIZE:   value = cast(zpl_i64) va_arg(va, zpl_usize); break;
                    case ZPL_FMT_INTPTR: value = cast(zpl_i64) va_arg(va, zpl_uintptr); break;
                    default: value             = cast(zpl_i64) va_arg(va, int); break;
                }

                len = zpl__print_i64(text, remaining, &info, value);
            }
        }

        text += len;
        if (len >= remaining)
            remaining = zpl_min(remaining, 1);
        else
            remaining -= len;
    }

    *text++ = '\0';
    res = (text - text_begin);
    return (res >= max_len || res < 0) ? -1 : res;
}

ZPL_END_C_DECLS
