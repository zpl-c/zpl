/** @file print.c
@brief Printing methods
@defgroup print Printing methods

Various printing methods.
@{
*/

ZPL_DEF isize zpl_printf(char const *fmt, ...) ZPL_PRINTF_ARGS(1);
ZPL_DEF isize zpl_printf_va(char const *fmt, va_list va);
ZPL_DEF isize zpl_printf_err(char const *fmt, ...) ZPL_PRINTF_ARGS(1);
ZPL_DEF isize zpl_printf_err_va(char const *fmt, va_list va);
ZPL_DEF isize zpl_fprintf(zpl_file *f, char const *fmt, ...) ZPL_PRINTF_ARGS(2);
ZPL_DEF isize zpl_fprintf_va(zpl_file *f, char const *fmt, va_list va);

ZPL_DEF char *zpl_bprintf(char const *fmt, ...)
ZPL_PRINTF_ARGS(1);                                    // NOTE: A locally persisting buffer is used internally
ZPL_DEF char *zpl_bprintf_va(char const *fmt, va_list va); // NOTE: A locally persisting buffer is used internally
ZPL_DEF isize zpl_snprintf(char *str, isize n, char const *fmt, ...) ZPL_PRINTF_ARGS(3);
ZPL_DEF isize zpl_snprintf_va(char *str, isize n, char const *fmt, va_list va);


//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Printing
//
//

isize zpl_printf(char const *fmt, ...) {
    isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_printf_va(fmt, va);
    va_end(va);
    return res;
}

isize zpl_printf_err(char const *fmt, ...) {
    isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_printf_err_va(fmt, va);
    va_end(va);
    return res;
}

isize zpl_fprintf(struct zpl_file *f, char const *fmt, ...) {
    isize res;
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

isize zpl_snprintf(char *str, isize n, char const *fmt, ...) {
    isize res;
    va_list va;
    va_start(va, fmt);
    res = zpl_snprintf_va(str, n, fmt, va);
    va_end(va);
    return res;
}

zpl_inline isize zpl_printf_va(char const *fmt, va_list va) {
    return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), fmt, va);
}

zpl_inline isize zpl_printf_err_va(char const *fmt, va_list va) {
    return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_ERROR), fmt, va);
}

zpl_inline isize zpl_fprintf_va(struct zpl_file *f, char const *fmt, va_list va) {
    zpl_local_persist char buf[4096];
    isize len = zpl_snprintf_va(buf, zpl_size_of(buf), fmt, va);
    zpl_file_write(f, buf, len - 1); // NOTE: prevent extra whitespace
    return len;
}

zpl_inline char *zpl_bprintf_va(char const *fmt, va_list va) {
    zpl_local_persist char buffer[4096];
    zpl_snprintf_va(buffer, zpl_size_of(buffer), fmt, va);
    return buffer;
}

enum {
    ZPL_FMT_MINUS = ZPL_BIT(0),
    ZPL_FMT_PLUS = ZPL_BIT(1),
    ZPL_FMT_ALT = ZPL_BIT(2),
    ZPL_FMT_SPACE = ZPL_BIT(3),
    ZPL_FMT_ZERO = ZPL_BIT(4),
    
    ZPL_FMT_CHAR = ZPL_BIT(5),
    ZPL_FMT_SHORT = ZPL_BIT(6),
    ZPL_FMT_INT = ZPL_BIT(7),
    ZPL_FMT_LONG = ZPL_BIT(8),
    ZPL_FMT_LLONG = ZPL_BIT(9),
    ZPL_FMT_SIZE = ZPL_BIT(10),
    ZPL_FMT_INTPTR = ZPL_BIT(11),
    
    ZPL_FMT_UNSIGNED = ZPL_BIT(12),
    ZPL_FMT_LOWER = ZPL_BIT(13),
    ZPL_FMT_UPPER = ZPL_BIT(14),
    
    ZPL_FMT_DONE = ZPL_BIT(30),
    
    ZPL_FMT_INTS =
        ZPL_FMT_CHAR | ZPL_FMT_SHORT | ZPL_FMT_INT | ZPL_FMT_LONG | ZPL_FMT_LLONG | ZPL_FMT_SIZE | ZPL_FMT_INTPTR
};

typedef struct {
    i32 base;
    i32 flags;
    i32 width;
    i32 precision;
} zplprivFmtInfo;

zpl_internal isize zpl__print_string(char *text, isize max_len, zplprivFmtInfo *info, char const *str) {
    // TODO: Get precision and width to work correctly. How does it actually work?!
    // TODO: This looks very buggy indeed.
    isize res = 0, len;
    isize remaining = max_len;
    
    if (info && info->precision >= 0)
        len = zpl_strnlen(str, info->precision);
    else
        len = zpl_strlen(str);
    
    if (info && (info->width == 0 || info->flags & ZPL_FMT_MINUS)) {
        if (info->precision > 0) len = info->precision < len ? info->precision : len;
        
        res += zpl_strlcpy(text, str, len);
        
        if (info->width > res) {
            isize padding = info->width - len;
            char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
            while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
        }
    } else {
        if (info && (info->width > res)) {
            isize padding = info->width - len;
            char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
            while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
        }
        
        res += zpl_strlcpy(text, str, len);
    }
    
    if (info) {
        if (info->flags & ZPL_FMT_UPPER)
            zpl_str_to_upper(text);
        else if (info->flags & ZPL_FMT_LOWER)
            zpl_str_to_lower(text);
    }
    
    return res;
}

zpl_internal isize zpl__print_char(char *text, isize max_len, zplprivFmtInfo *info, char arg) {
    char str[2] = "";
    str[0] = arg;
    return zpl__print_string(text, max_len, info, str);
}

zpl_internal isize zpl__print_i64(char *text, isize max_len, zplprivFmtInfo *info, i64 value) {
    char num[130];
    zpl_i64_to_str(value, num, info ? info->base : 10);
    return zpl__print_string(text, max_len, info, num);
}

zpl_internal isize zpl__print_u64(char *text, isize max_len, zplprivFmtInfo *info, u64 value) {
    char num[130];
    zpl_u64_to_str(value, num, info ? info->base : 10);
    return zpl__print_string(text, max_len, info, num);
}

zpl_internal isize zpl__print_f64(char *text, isize max_len, zplprivFmtInfo *info, f64 arg) {
    // TODO: Handle exponent notation
    isize width, len, remaining = max_len;
    char *text_begin = text;
    
    if (arg) {
        u64 value;
        if (arg < 0) {
            if (remaining > 1) *text = '-', remaining--;
            text++;
            arg = -arg;
        } else if (info->flags & ZPL_FMT_MINUS) {
            if (remaining > 1) *text = '+', remaining--;
            text++;
        }
        
        value = cast(u64) arg;
        len = zpl__print_u64(text, remaining, NULL, value);
        text += len;
        
        if (len >= remaining)
            remaining = zpl_min(remaining, 1);
        else
            remaining -= len;
        arg -= value;
        
        if (info->precision < 0) info->precision = 6;
        
        if ((info->flags & ZPL_FMT_ALT) || info->precision > 0) {
            i64 mult = 10;
            if (remaining > 1) *text = '.', remaining--;
            text++;
            while (info->precision-- > 0) {
                value = cast(u64)(arg * mult);
                len = zpl__print_u64(text, remaining, NULL, value);
                text += len;
                if (len >= remaining)
                    remaining = zpl_min(remaining, 1);
                else
                    remaining -= len;
                arg -= cast(f64) value / mult;
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

zpl_no_inline isize zpl_snprintf_va(char *text, isize max_len, char const *fmt, va_list va) {
    char const *text_begin = text;
    isize remaining = max_len, res;
    
    while (*fmt) {
        zplprivFmtInfo info = { 0 };
        isize len = 0;
        info.precision = -1;
        
        while (*fmt && *fmt != '%' && remaining) *text++ = *fmt++;
        
        if (*fmt == '%') {
            do {
                switch (*++fmt) {
                    case '-': info.flags |= ZPL_FMT_MINUS; break;
                    case '+': info.flags |= ZPL_FMT_PLUS; break;
                    case '#': info.flags |= ZPL_FMT_ALT; break;
                    case ' ': info.flags |= ZPL_FMT_SPACE; break;
                    case '0': info.flags |= ZPL_FMT_ZERO; break;
                    default: info.flags |= ZPL_FMT_DONE; break;
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
            fmt++;
        } else {
            info.width = cast(i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
        }
        
        // NOTE: Optional Precision
        if (*fmt == '.') {
            fmt++;
            if (*fmt == '*') {
                info.precision = va_arg(va, int);
                fmt++;
            } else {
                info.precision = cast(i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
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
            
            case 'z': // NOTE: usize
            info.flags |= ZPL_FMT_UNSIGNED;
            // fallthrough
            case 't': // NOTE: isize
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
            case 'G': len = zpl__print_f64(text, remaining, &info, va_arg(va, f64)); break;
            
            case 'a':
            case 'A':
            // TODO:
            break;
            
            case 'c': len = zpl__print_char(text, remaining, &info, cast(char) va_arg(va, int)); break;
            
            case 's': len = zpl__print_string(text, remaining, &info, va_arg(va, char *)); break;
            
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
                u64 value = 0;
                switch (info.flags & ZPL_FMT_INTS) {
                    case ZPL_FMT_CHAR: value = cast(u64) cast(u8) va_arg(va, int); break;
                    case ZPL_FMT_SHORT: value = cast(u64) cast(u16) va_arg(va, int); break;
                    case ZPL_FMT_LONG: value = cast(u64) va_arg(va, unsigned long); break;
                    case ZPL_FMT_LLONG: value = cast(u64) va_arg(va, unsigned long long); break;
                    case ZPL_FMT_SIZE: value = cast(u64) va_arg(va, usize); break;
                    case ZPL_FMT_INTPTR: value = cast(u64) va_arg(va, uintptr); break;
                    default: value = cast(u64) va_arg(va, unsigned int); break;
                }
                
                len = zpl__print_u64(text, remaining, &info, value);
                
            } else {
                i64 value = 0;
                switch (info.flags & ZPL_FMT_INTS) {
                    case ZPL_FMT_CHAR: value = cast(i64) cast(i8) va_arg(va, int); break;
                    case ZPL_FMT_SHORT: value = cast(i64) cast(i16) va_arg(va, int); break;
                    case ZPL_FMT_LONG: value = cast(i64) va_arg(va, long); break;
                    case ZPL_FMT_LLONG: value = cast(i64) va_arg(va, long long); break;
                    case ZPL_FMT_SIZE: value = cast(i64) va_arg(va, usize); break;
                    case ZPL_FMT_INTPTR: value = cast(i64) va_arg(va, uintptr); break;
                    default: value = cast(i64) va_arg(va, int); break;
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
