#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#include <string.h>

ZPL_BEGIN_C_DECLS


void zpl_memswap(void *i, void *j, zpl_isize size) {
    if (i == j) return;

    if (size == 4) {
        zpl_swap(zpl_u32, *cast(zpl_u32 *) i, *cast(zpl_u32 *) j);
    } else if (size == 8) {
        zpl_swap(zpl_u64, *cast(zpl_u64 *) i, *cast(zpl_u64 *) j);
    } else if (size < 8) {
        zpl_u8 *a = cast(zpl_u8 *) i;
        zpl_u8 *b = cast(zpl_u8 *) j;
        if (a != b) {
            while (size--) { zpl_swap(zpl_u8, *a++, *b++); }
        }
    } else {
        char buffer[256];

        while (size > zpl_size_of(buffer)) {
            zpl_memswap(i, j, zpl_size_of(buffer));
            i = zpl_pointer_add(i, zpl_size_of(buffer));
            j = zpl_pointer_add(j, zpl_size_of(buffer));
            size -= zpl_size_of(buffer);
        }

        zpl_memcopy(buffer, i, size);
        zpl_memcopy(i, j, size);
        zpl_memcopy(j, buffer, size);
    }
}

void const *zpl_memchr(void const *data, zpl_u8 c, zpl_isize n) {
    zpl_u8 const *s = cast(zpl_u8 const *) data;
    while ((cast(zpl_uintptr) s & (sizeof(zpl_usize) - 1)) && n && *s != c) {
        s++;
        n--;
    }
    if (n && *s != c) {
        zpl_isize const *w;
        zpl_isize k = ZPL__ONES * c;
        w = cast(zpl_isize const *) s;
        while (n >= zpl_size_of(zpl_isize) && !ZPL__HAS_ZERO(*w ^ k)) {
            w++;
            n -= zpl_size_of(zpl_isize);
        }
        s = cast(zpl_u8 const *) w;
        while (n && *s != c) {
            s++;
            n--;
        }
    }

    return n ? cast(void const *) s : NULL;
}

void const *zpl_memrchr(void const *data, zpl_u8 c, zpl_isize n) {
    zpl_u8 const *s = cast(zpl_u8 const *) data;
    while (n--) {
        if (s[n] == c) return cast(void const *)(s + n);
    }
    return NULL;
}

void *zpl_memcopy(void *dest, void const *source, zpl_isize n) {
    if (dest == NULL) { return NULL; }

    return memcpy(dest, source, n);

    // TODO: Re-work the whole method
#if 0
#if defined(_MSC_VER)
    __movsb(cast(zpl_u8 *) dest, cast(zpl_u8 *) source, n);
#elif defined(ZPL_CPU_X86) && !defined(ZPL_SYSTEM_EMSCRIPTEN)
    zpl_u8 *__dest8 = cast(zpl_u8 *) dest;
    zpl_u8 *__source8 = cast(zpl_u8 *) source;
    __asm__ __volatile__("rep movsb" : "+D"(__dest8), "+S"(__source8), "+c"(n) : : "memory");
#elif defined(ZPL_CPU_ARM)
    return memcpy(dest, source, n);
#else
    zpl_u8 *d = cast(zpl_u8 *) dest;
    zpl_u8 const *s = cast(zpl_u8 const *) source;
    zpl_u32 w, x;

    for (; cast(zpl_uintptr) s % 4 && n; n--) *d++ = *s++;

    if (cast(zpl_uintptr) d % 4 == 0) {
        for (; n >= 16; s += 16, d += 16, n -= 16) {
            *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
            *cast(zpl_u32 *)(d + 4) = *cast(zpl_u32 *)(s + 4);
            *cast(zpl_u32 *)(d + 8) = *cast(zpl_u32 *)(s + 8);
            *cast(zpl_u32 *)(d + 12) = *cast(zpl_u32 *)(s + 12);
        }
        if (n & 8) {
            *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
            *cast(zpl_u32 *)(d + 4) = *cast(zpl_u32 *)(s + 4);
            d += 8;
            s += 8;
        }
        if (n & 4) {
            *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
            d += 4;
            s += 4;
        }
        if (n & 2) {
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 1) { *d = *s; }
        return dest;
    }

    if (n >= 32) {
#if __BYTE_ORDER == __BIG_ENDIAN
#define LS <<
#define RS >>
#else
#define LS >>
#define RS <<
#endif
        switch (cast(zpl_uintptr) d % 4) {
            case 1: {
                w = *cast(zpl_u32 *) s;
                *d++ = *s++;
                *d++ = *s++;
                *d++ = *s++;
                n -= 3;
                while (n > 16) {
                    x = *cast(zpl_u32 *)(s + 1);
                    *cast(zpl_u32 *)(d + 0) = (w LS 24) | (x RS 8);
                    w = *cast(zpl_u32 *)(s + 5);
                    *cast(zpl_u32 *)(d + 4) = (x LS 24) | (w RS 8);
                    x = *cast(zpl_u32 *)(s + 9);
                    *cast(zpl_u32 *)(d + 8) = (w LS 24) | (x RS 8);
                    w = *cast(zpl_u32 *)(s + 13);
                    *cast(zpl_u32 *)(d + 12) = (x LS 24) | (w RS 8);

                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            case 2: {
                w = *cast(zpl_u32 *) s;
                *d++ = *s++;
                *d++ = *s++;
                n -= 2;
                while (n > 17) {
                    x = *cast(zpl_u32 *)(s + 2);
                    *cast(zpl_u32 *)(d + 0) = (w LS 16) | (x RS 16);
                    w = *cast(zpl_u32 *)(s + 6);
                    *cast(zpl_u32 *)(d + 4) = (x LS 16) | (w RS 16);
                    x = *cast(zpl_u32 *)(s + 10);
                    *cast(zpl_u32 *)(d + 8) = (w LS 16) | (x RS 16);
                    w = *cast(zpl_u32 *)(s + 14);
                    *cast(zpl_u32 *)(d + 12) = (x LS 16) | (w RS 16);

                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            case 3: {
                w = *cast(zpl_u32 *) s;
                *d++ = *s++;
                n -= 1;
                while (n > 18) {
                    x = *cast(zpl_u32 *)(s + 3);
                    *cast(zpl_u32 *)(d + 0) = (w LS 8) | (x RS 24);
                    w = *cast(zpl_u32 *)(s + 7);
                    *cast(zpl_u32 *)(d + 4) = (x LS 8) | (w RS 24);
                    x = *cast(zpl_u32 *)(s + 11);
                    *cast(zpl_u32 *)(d + 8) = (w LS 8) | (x RS 24);
                    w = *cast(zpl_u32 *)(s + 15);
                    *cast(zpl_u32 *)(d + 12) = (x LS 8) | (w RS 24);

                    s += 16;
                    d += 16;
                    n -= 16;
                }
            } break;
            default: break; // NOTE: Do nowt!
        }
#undef LS
#undef RS
        if (n & 16) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 8) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 4) {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 2) {
            *d++ = *s++;
            *d++ = *s++;
        }
        if (n & 1) { *d = *s; }
    }

#endif
#endif

    return dest;
}

ZPL_END_C_DECLS
