// file: header/essentials/types.h


ZPL_BEGIN_C_DECLS

/* Basic types */

#if defined(ZPL_COMPILER_MSVC)
#    if _MSC_VER < 1300
        typedef unsigned char zpl_u8;
        typedef signed char zpl_i8;
        typedef unsigned short zpl_u16;
        typedef signed short zpl_i16;
        typedef unsigned int zpl_u32;
        typedef signed int zpl_i32;
#    else
        typedef unsigned __int8 zpl_u8;
        typedef signed __int8 zpl_i8;
        typedef unsigned __int16 zpl_u16;
        typedef signed __int16 zpl_i16;
        typedef unsigned __int32 zpl_u32;
        typedef signed __int32 zpl_i32;
#    endif
    typedef unsigned __int64 zpl_u64;
    typedef signed __int64 zpl_i64;
#else
#    include <stdint.h>

    typedef uint8_t zpl_u8;
    typedef int8_t zpl_i8;
    typedef uint16_t zpl_u16;
    typedef int16_t zpl_i16;
    typedef uint32_t zpl_u32;
    typedef int32_t zpl_i32;
    typedef uint64_t zpl_u64;
    typedef int64_t zpl_i64;
#endif

ZPL_STATIC_ASSERT(sizeof(zpl_u8) == sizeof(zpl_i8), "sizeof(zpl_u8) != sizeof(zpl_i8)");
ZPL_STATIC_ASSERT(sizeof(zpl_u16) == sizeof(zpl_i16), "sizeof(zpl_u16) != sizeof(zpl_i16)");
ZPL_STATIC_ASSERT(sizeof(zpl_u32) == sizeof(zpl_i32), "sizeof(zpl_u32) != sizeof(zpl_i32)");
ZPL_STATIC_ASSERT(sizeof(zpl_u64) == sizeof(zpl_i64), "sizeof(zpl_u64) != sizeof(zpl_i64)");

ZPL_STATIC_ASSERT(sizeof(zpl_u8) == 1, "sizeof(zpl_u8) != 1");
ZPL_STATIC_ASSERT(sizeof(zpl_u16) == 2, "sizeof(zpl_u16) != 2");
ZPL_STATIC_ASSERT(sizeof(zpl_u32) == 4, "sizeof(zpl_u32) != 4");
ZPL_STATIC_ASSERT(sizeof(zpl_u64) == 8, "sizeof(zpl_u64) != 8");

typedef size_t zpl_usize;
typedef ptrdiff_t zpl_isize;

ZPL_STATIC_ASSERT(sizeof(zpl_usize) == sizeof(zpl_isize), "sizeof(zpl_usize) != sizeof(zpl_isize)");

// NOTE: (u)zpl_intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
#if defined(_WIN64)
    typedef signed __int64 zpl_intptr;
    typedef unsigned __int64 zpl_uintptr;
#elif defined(_WIN32)
    // NOTE; To mark types changing their size, e.g. zpl_intptr
#    ifndef _W64
#        if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#            define _W64 __w64
#        else
#            define _W64
#        endif
#    endif
    typedef _W64 signed int zpl_intptr;
    typedef _W64 unsigned int zpl_uintptr;
#else
    typedef uintptr_t zpl_uintptr;
    typedef intptr_t zpl_intptr;
#endif

ZPL_STATIC_ASSERT(sizeof(zpl_uintptr) == sizeof(zpl_intptr), "sizeof(zpl_uintptr) != sizeof(zpl_intptr)");

typedef float zpl_f32;
typedef double zpl_f64;

ZPL_STATIC_ASSERT(sizeof(zpl_f32) == 4, "sizeof(zpl_f32) != 4");
ZPL_STATIC_ASSERT(sizeof(zpl_f64) == 8, "sizeof(zpl_f64) != 8");

typedef zpl_i32 zpl_rune; // NOTE: Unicode codepoint
typedef zpl_i32 zpl_char32;
#define ZPL_RUNE_INVALID cast(zpl_rune)(0xfffd)
#define ZPL_RUNE_MAX cast(zpl_rune)(0x0010ffff)
#define ZPL_RUNE_BOM cast(zpl_rune)(0xfeff)
#define ZPL_RUNE_EOF cast(zpl_rune)(-1)

typedef zpl_i8 zpl_b8;
typedef zpl_i16 zpl_b16;
typedef zpl_i32 zpl_b32;

#if !defined(__cplusplus)
#    if (defined(_MSC_VER) && _MSC_VER < 1800) || (!defined(_MSC_VER) && !defined(__STDC_VERSION__))
#        ifndef true
#            define true(0 == 0)
#        endif
#        ifndef false
#            define false(0 != 0)
#        endif

        typedef zpl_b8 bool;
#    else
#        include <stdbool.h>
#    endif
#endif

#ifndef ZPL_U8_MIN
#    define ZPL_U8_MIN 0u
#    define ZPL_U8_MAX 0xffu
#    define ZPL_I8_MIN (-0x7f - 1)
#    define ZPL_I8_MAX 0x7f

#    define ZPL_U16_MIN 0u
#    define ZPL_U16_MAX 0xffffu
#    define ZPL_I16_MIN (-0x7fff - 1)
#    define ZPL_I16_MAX 0x7fff

#    define ZPL_U32_MIN 0u
#    define ZPL_U32_MAX 0xffffffffu
#    define ZPL_I32_MIN (-0x7fffffff - 1)
#    define ZPL_I32_MAX 0x7fffffff

#    define ZPL_U64_MIN 0ull
#    define ZPL_U64_MAX 0xffffffffffffffffull
#    define ZPL_I64_MIN (-0x7fffffffffffffffll - 1)
#    define ZPL_I64_MAX 0x7fffffffffffffffll

#    if defined(ZPL_ARCH_32_BIT)
#        define ZPL_USIZE_MIN ZPL_U32_MIN
#        define ZPL_USIZE_MAX ZPL_U32_MAX
#        define ZPL_ISIZE_MIN ZPL_S32_MIN
#    define ZPL_ISIZE_MAX ZPL_S32_MAX
#        elif defined(ZPL_ARCH_64_BIT)
#        define ZPL_USIZE_MIN ZPL_U64_MIN
#        define ZPL_USIZE_MAX ZPL_U64_MAX
#        define ZPL_ISIZE_MIN ZPL_I64_MIN
#        define ZPL_ISIZE_MAX ZPL_I64_MAX
#    else
#        error Unknown architecture size. This library only supports 32 bit and 64 bit architectures.
#    endif

#    define ZPL_F32_MIN 1.17549435e-38f
#    define ZPL_F32_MAX 3.40282347e+38f

#    define ZPL_F64_MIN 2.2250738585072014e-308
#    define ZPL_F64_MAX 1.7976931348623157e+308
#endif

#ifdef ZPL_DEFINE_NULL_MACRO
#    ifndef NULL
#        define NULL ZPL_NULL
#    endif
#endif

ZPL_END_C_DECLS
