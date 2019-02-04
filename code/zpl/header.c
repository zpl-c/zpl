/** @file header.c
@brief Macro helpers and symbols
@defgroup header Macro helpers and symbols

 This module contains many useful macros helpful for debugging as well as development itself.
 
 @{
 */

#if defined(__cplusplus)
#define ZPL_EXTERN extern "C"
#else
#define ZPL_EXTERN extern
#endif

#if defined(_WIN32)
#define ZPL_DLL_EXPORT ZPL_EXTERN __declspec(dllexport)
#define ZPL_DLL_IMPORT ZPL_EXTERN __declspec(dllimport)
#else
#define ZPL_DLL_EXPORT ZPL_EXTERN __attribute__((visibility("default")))
#define ZPL_DLL_IMPORT ZPL_EXTERN
#endif

#ifndef ZPL_DEF
#ifdef ZPL_STATIC
#define ZPL_DEF static
#else
#define ZPL_DEF extern
#endif
#endif

#ifdef ZPL_IMPL
#define ZPL_IMPLEMENTATION
#endif

#ifdef ZPL_DEFINE
#define ZPL_IMPLEMENTATION
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) ||       \
defined(__ppc64__) || defined(__aarch64__)
#ifndef ZPL_ARCH_64_BIT
#define ZPL_ARCH_64_BIT 1
#endif
#else
#ifndef ZPL_ARCH_32_BIT
#define ZPL_ARCH_32_BIT 1
#endif
#endif

#ifndef ZPL_ENDIAN_ORDER
#define ZPL_ENDIAN_ORDER
#define ZPL_IS_BIG_ENDIAN (!*(zpl_u8 *)&(zpl_u16){ 1 })
#define ZPL_IS_LITTLE_ENDIAN (!ZPL_IS_BIG_ENDIAN)
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifndef ZPL_SYSTEM_WINDOWS
#define ZPL_SYSTEM_WINDOWS 1
#endif
#elif defined(__APPLE__) && defined(__MACH__)
#ifndef ZPL_SYSTEM_OSX
#define ZPL_SYSTEM_OSX 1
#endif
#ifndef ZPL_SYSTEM_MACOS
#define ZPL_SYSTEM_MACOS 1
#endif
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
#ifndef ZPL_SYSTEM_IOS
#define ZPL_SYSTEM_IOS 1
#endif
#endif
#elif defined(__unix__)
#ifndef ZPL_SYSTEM_UNIX
#define ZPL_SYSTEM_UNIX 1
#endif

#if defined(ANDROID) || defined(__ANDROID__)
#ifndef ZPL_SYSTEM_ANDROID
#define ZPL_SYSTEM_ANDROID 1
#endif
#ifndef ZPL_SYSTEM_LINUX
#define ZPL_SYSTEM_LINUX 1
#endif
#elif defined(__linux__)
#ifndef ZPL_SYSTEM_LINUX
#define ZPL_SYSTEM_LINUX 1
#endif
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#ifndef ZPL_SYSTEM_FREEBSD
#define ZPL_SYSTEM_FREEBSD 1
#endif
#elif defined(__EMSCRIPTEN__)
#ifndef ZPL_SYSTEM_EMSCRIPTEN
#define ZPL_SYSTEM_EMSCRIPTEN 1
#endif
#else
#error This UNIX operating system is not supported
#endif
#else
#error This operating system is not supported
#endif


#if defined(_MSC_VER)
#define ZPL_COMPILER_MSVC 1
#elif defined(__GNUC__)
#define ZPL_COMPILER_GCC 1
#elif defined(__clang__)
#define ZPL_COMPILER_CLANG 1
#else
#error Unknown compiler
#endif

#if defined(__arm__) || defined(__aarch64__)
#ifndef ZPL_CPU_ARM
#define ZPL_CPU_ARM 1
#endif
#ifndef ZPL_CACHE_LINE_SIZE
#define ZPL_CACHE_LINE_SIZE 64
#endif
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__) || defined(ZPL_SYSTEM_EMSCRIPTEN)
#ifndef ZPL_CPU_X86
#define ZPL_CPU_X86 1
#endif
#ifndef ZPL_CACHE_LINE_SIZE
#define ZPL_CACHE_LINE_SIZE 64
#endif
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#ifndef ZPL_CPU_PPC
#define ZPL_CPU_PPC 1
#endif
#ifndef ZPL_CACHE_LINE_SIZE
#define ZPL_CACHE_LINE_SIZE 128
#endif
#elif defined(__MIPSEL__) || defined(__mips_isa_rev)
#ifndef ZPL_CPU_MIPS
#define ZPL_CPU_MIPS 1
#endif
#ifndef ZPL_CACHE_LINE_SIZE
#define ZPL_CACHE_LINE_SIZE 64
#endif
#else
#error Unknown CPU Type
#endif

#if !defined(ZPL_SYSTEM_EMSCRIPTEN) && !defined(ZPL_CPU_ARM) // disabled for __EMSCRIPTEN__
#ifndef ZPL_THREADING
#define ZPL_THREADING 1
#else
#if ZPL_THREADING == 0 || defined(ZPL_NO_THREADING)
#undef ZPL_THREADING
#endif
#endif
#endif



#ifndef ZPL_STATIC_ASSERT
#define ZPL_STATIC_ASSERT3(cond, msg) typedef char static_assertion_##msg[(!!(cond)) * 2 - 1]
#define ZPL_STATIC_ASSERT2(cond, line) ZPL_STATIC_ASSERT3(cond, static_assertion_at_line_##line)
#define ZPL_STATIC_ASSERT1(cond, line) ZPL_STATIC_ASSERT2(cond, line)
#define ZPL_STATIC_ASSERT(cond) ZPL_STATIC_ASSERT1(cond, __LINE__)
#endif

////////////////////////////////////////////////////////////////
//
// Headers
//
//

#if defined(_WIN32) && !defined(__MINGW32__)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#if defined(ZPL_SYSTEM_UNIX)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#endif

#include <math.h>

#if defined(ZPL_SYSTEM_WINDOWS)
#include <direct.h> // TODO: remove and use native winapi methods
#include <io.h>
#include <stdio.h>

#define ZPL_WINMAIN( )                                                                                                 \
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,                 \
_In_ int nCmdShow)

#if !defined(ZPL_NO_WINDOWS_H)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WIN32_MEAN_AND_LEAN
#define VC_EXTRALEAN
#include <windows.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#undef WIN32_MEAN_AND_LEAN
#undef VC_EXTRALEAN
#endif

#include <malloc.h> // NOTE: _aligned_*()

#if !defined(ZPL_NO_SIMD)
#include <intrin.h>
#endif

// TODO(ZaKlaus): Find a better way to get this flag in MinGW.
#if defined(ZPL_COMPILER_GCC) && !defined(WC_ERR_INVALID_CHARS)
#define WC_ERR_INVALID_CHARS 0x0080
#endif

#else

#define ZPL_WINMAIN int main(void)

#if !defined(ZPL_SYSTEM_EMSCRIPTEN)
#include <pthread.h>
#endif

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#ifndef _IOSC11_SOURCE
#define _IOSC11_SOURCE
#endif
#include <stdlib.h> // NOTE: malloc on linux
#include <sys/mman.h>

#if !defined(ZPL_SYSTEM_OSX)
#include <sys/sendfile.h>
#endif

#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#if !defined(ZPL_SYSTEM_ANDROID)
#include <spawn.h>
#endif

#if !defined(ZPL_NO_SIMD)
#if !defined(ZPL_SYSTEM_ANDROID) && !defined(ZPL_SYSTEM_IOS)
#if !defined(ZPL_SYSTEM_EMSCRIPTEN)
#include <emmintrin.h>
#elif defined(ZPL_CPU_X86) && !defined(ZPL_SYSTEM_EMSCRIPTEN)
#include <xmmintrin.h>
#else
#include <sched.h>
#endif
#endif
#endif

#endif

#if defined(ZPL_SYSTEM_OSX)
#include <copyfile.h>
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_init.h>
#include <mach/mach_time.h>
#include <mach/thread_act.h>
#include <mach/thread_policy.h>
#include <stdio.h>
#include <sys/sysctl.h>
#endif

#if defined(ZPL_SYSTEM_UNIX)
#include <semaphore.h>
#endif

#if !defined(ZPL_SYSTEM_WINDOWS)
#include <stdarg.h>
#include <stddef.h>
#endif

////////////////////////////////////////////////////////////////
//
// Base Types
//
//

#if defined(ZPL_COMPILER_MSVC)
#if _MSC_VER < 1300
typedef unsigned char zpl_u8;
typedef signed char zpl_i8;
typedef unsigned short zpl_u16;
typedef signed short zpl_i16;
typedef unsigned int zpl_u32;
typedef signed int zpl_i32;
#else
typedef unsigned __int8 zpl_u8;
typedef signed __int8 zpl_i8;
typedef unsigned __int16 zpl_u16;
typedef signed __int16 zpl_i16;
typedef unsigned __int32 zpl_u32;
typedef signed __int32 zpl_i32;
#endif
typedef unsigned __int64 zpl_u64;
typedef signed __int64 zpl_i64;
#else
#include <stdint.h>
typedef uint8_t zpl_u8;
typedef int8_t zpl_i8;
typedef uint16_t zpl_u16;
typedef int16_t zpl_i16;
typedef uint32_t zpl_u32;
typedef int32_t zpl_i32;
typedef uint64_t zpl_u64;
typedef int64_t zpl_i64;
#endif

ZPL_STATIC_ASSERT(sizeof(zpl_u8) == sizeof(zpl_i8));
ZPL_STATIC_ASSERT(sizeof(zpl_u16) == sizeof(zpl_i16));
ZPL_STATIC_ASSERT(sizeof(zpl_u32) == sizeof(zpl_i32));
ZPL_STATIC_ASSERT(sizeof(zpl_u64) == sizeof(zpl_i64));

ZPL_STATIC_ASSERT(sizeof(zpl_u8) == 1);
ZPL_STATIC_ASSERT(sizeof(zpl_u16) == 2);
ZPL_STATIC_ASSERT(sizeof(zpl_u32) == 4);
ZPL_STATIC_ASSERT(sizeof(zpl_u64) == 8);

typedef size_t zpl_usize;
typedef ptrdiff_t zpl_isize;

ZPL_STATIC_ASSERT(sizeof(zpl_usize) == sizeof(zpl_isize));

// NOTE: (u)zpl_intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
#if defined(_WIN64)
typedef signed __int64 zpl_intptr;
typedef unsigned __int64 zpl_uintptr;
#elif defined(_WIN32)
// NOTE; To mark types changing their size, e.g. zpl_intptr
#ifndef _W64
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define _W64 __w64
#else
#define _W64
#endif
#endif

typedef _W64 signed int zpl_intptr;
typedef _W64 unsigned int zpl_uintptr;
#else
typedef uintptr_t zpl_uintptr;
typedef intptr_t zpl_intptr;
#endif

ZPL_STATIC_ASSERT(sizeof(zpl_uintptr) == sizeof(zpl_intptr));

typedef float zpl_f32;
typedef double zpl_f64;

ZPL_STATIC_ASSERT(sizeof(zpl_f32) == 4);
ZPL_STATIC_ASSERT(sizeof(zpl_f64) == 8);

typedef zpl_i32 Rune; // NOTE: Unicode codepoint
typedef zpl_i32 char32;
#define ZPL_RUNE_INVALID cast(Rune)(0xfffd)
#define ZPL_RUNE_MAX cast(Rune)(0x0010ffff)
#define ZPL_RUNE_BOM cast(Rune)(0xfeff)
#define ZPL_RUNE_EOF cast(Rune)(-1)

typedef zpl_i8 zpl_b8;
typedef zpl_i16 zpl_b16;
typedef zpl_i32 zpl_b32;

#if !defined(__cplusplus)
#if (defined(_MSC_VER) && _MSC_VER < 1800) || (!defined(_MSC_VER) && !defined(__STDC_VERSION__))
#ifndef true
#define true(0 == 0)
#endif
#ifndef false
#define false(0 != 0)
#endif
typedef zpl_b8 bool;
#else
#include <stdbool.h>
#endif
#endif

#define u8 zpl_u8
#define i8 zpl_i8
#define u16 zpl_u16
#define i16 zpl_i16
#define u32 zpl_u32
#define i32 zpl_i32
#define u64 zpl_u64
#define i64 zpl_i64
#define b8 zpl_b8
#define b16 zpl_b16
#define b32 zpl_b32
#define f32 zpl_f32
#define f64 zpl_f64
#define usize zpl_usize
#define isize zpl_isize
#define uintptr zpl_uintptr
#define intptr zpl_intptr

#ifndef U8_MIN
#define U8_MIN 0u
#define U8_MAX 0xffu
#define I8_MIN (-0x7f - 1)
#define I8_MAX 0x7f

#define U16_MIN 0u
#define U16_MAX 0xffffu
#define I16_MIN (-0x7fff - 1)
#define I16_MAX 0x7fff

#define U32_MIN 0u
#define U32_MAX 0xffffffffu
#define I32_MIN (-0x7fffffff - 1)
#define I32_MAX 0x7fffffff

#define U64_MIN 0ull
#define U64_MAX 0xffffffffffffffffull
#define I64_MIN (-0x7fffffffffffffffll - 1)
#define I64_MAX 0x7fffffffffffffffll

#if defined(ZPL_ARCH_32_BIT)
#define USIZE_MIN U32_MIN
#define USIZE_MAX U32_MAX

#define ISIZE_MIN S32_MIN
#define ISIZE_MAX S32_MAX
#elif defined(ZPL_ARCH_64_BIT)
#define USIZE_MIN U64_MIN
#define USIZE_MAX U64_MAX

#define ISIZE_MIN I64_MIN
#define ISIZE_MAX I64_MAX
#else
#error Unknown architecture size. This library only supports 32 bit and 64 bit architectures.
#endif

#define F32_MIN 1.17549435e-38f
#define F32_MAX 3.40282347e+38f

#define F64_MIN 2.2250738585072014e-308
#define F64_MAX 1.7976931348623157e+308

#endif

#ifdef ZPL_DEFINE_NULL_MACRO
#ifndef NULL
#if defined(__cplusplus)
#if __cplusplus >= 201103L
#define NULL nullptr
#else
#define NULL 0
#endif
#else
#define NULL ((void *)0)
#endif
#endif
#endif

#if !defined(__cplusplus)
#if defined(_MSC_VER) && _MSC_VER <= 1800
#define inline __inline
#elif !defined(__STDC_VERSION__)
#define inline __inline__
#else
#define inline
#endif
#endif

#if !defined(zpl_restrict)
#if defined(_MSC_VER)
#define zpl_restrict __restrict
#elif defined(__STDC_VERSION__)
#define zpl_restrict restrict
#else
#define zpl_restrict
#endif
#endif

#if !defined(zpl_inline)
#if defined(_MSC_VER)
#if _MSC_VER < 1300
#define zpl_inline
#else
#define zpl_inline __forceinline
#endif
#else
#define zpl_inline inline //__attribute__ ((__always_inline__)) inline
#endif
#endif

#if !defined(zpl_no_inline)
#if defined(_MSC_VER)
#define zpl_no_inline __declspec(noinline)
#else
#define zpl_no_inline __attribute__((noinline))
#endif
#endif

#if !defined(zpl_thread_local)
#if defined(_MSC_VER) && _MSC_VER >= 1300
#define zpl_thread_local __declspec(thread)
#elif defined(__GNUC__)
#define zpl_thread_local __thread
#else
#define zpl_thread_local thread_local
#endif
#endif

#ifndef cast
#define cast(Type) (Type)
#endif

#ifndef zpl_size_of
#define zpl_size_of(x) (isize)(sizeof(x))
#endif

#ifndef zpl_count_of
#define zpl_count_of(x) ((zpl_size_of(x) / zpl_size_of(0 [x])) / ((isize)(!(zpl_size_of(x) % zpl_size_of(0 [x])))))
#endif

#ifndef zpl_offset_of
#ifdef _MSC_VER
#define zpl_offset_of(Type, element) ((isize) & (((Type *)0)->element))
#else
#define zpl_offset_of(Type, element) __builtin_offsetof(Type, element)
#endif
#endif

#if defined(__cplusplus)
#ifndef zpl_align_of
#if __cplusplus >= 201103L
#define zpl_align_of(Type) (isize)alignof(Type)
#else
extern "C++" {
    template <typename T> struct zpl_alignment_trick {
        char c;
        T member;
    };
#define zpl_align_of(Type) zpl_offset_of(zpl_alignment_trick<Type>, member)
}
#endif
#endif
#else
#ifndef zpl_align_of
#define zpl_align_of(Type)                                                                                             \
zpl_offset_of(                                                                                                     \
struct {                                                                                                       \
    char c;                                                                                                    \
    Type member;                                                                                               \
},                                                                                                             \
member)
#endif
#endif

#ifndef zpl_swap
#define zpl_swap(Type, a, b)                                                                                           \
do {                                                                                                               \
    Type tmp = (a);                                                                                                \
    (a) = (b);                                                                                                     \
    (b) = tmp;                                                                                                     \
} while (0)
#endif

#ifndef zpl_global
#define zpl_global static        // Global variables
#define zpl_internal static      // Internal linkage
#define zpl_local_persist static // Local Persisting variables
#endif

#ifndef zpl_unused
#if defined(_MSC_VER)
#define zpl_unused(x) (__pragma(warning(suppress : 4100))(x))
#elif defined(__GCC__)
#define zpl_unused(x) __attribute__((__unused__))(x)
#else
#define zpl_unused(x) ((void)(zpl_size_of(x)))
#endif
#endif

////////////////////////////////////////////////////////////////
//
// Macro Fun!
//
//

#ifndef ZPL_JOIN_MACROS
#define ZPL_JOIN_MACROS
#define ZPL_JOIN2_IND(a, b) a##b

#define ZPL_JOIN2(a, b) ZPL_JOIN2_IND(a, b)
#define ZPL_JOIN3(a, b, c) ZPL_JOIN2(ZPL_JOIN2(a, b), c)
#define ZPL_JOIN4(a, b, c, d) ZPL_JOIN2(ZPL_JOIN2(ZPL_JOIN2(a, b), c), d)
#endif

#ifndef ZPL_BIT
#define ZPL_BIT(x) (1 << (x))
#endif

#ifndef zpl_min
#define zpl_min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef zpl_max
#define zpl_max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef zpl_min3
#define zpl_min3(a, b, c) zpl_min(zpl_min(a, b), c)
#endif

#ifndef zpl_max3
#define zpl_max3(a, b, c) zpl_max(zpl_max(a, b), c)
#endif

#ifndef zpl_clamp
#define zpl_clamp(x, lower, upper) zpl_min(zpl_max((x), (lower)), (upper))
#endif

#ifndef zpl_clamp01
#define zpl_clamp01(x) zpl_clamp((x), 0, 1)
#endif

#ifndef zpl_is_between
#define zpl_is_between(x, lower, upper) (((lower) <= (x)) && ((x) <= (upper)))
#endif

#ifndef zpl_abs
#define zpl_abs(x) ((x) < 0 ? -(x) : (x))
#endif

#ifndef hard_cast
#define hard_cast(type) *cast(type) &
#endif

// WARN(ZaKlaus): Supported only on GCC via GNU extensions!!!
#ifndef zpl_lambda
#define zpl_lambda(b_) ({ b_ _; })
#endif

#ifndef zpl_when
#define zpl_when(init, type, name)                                                                                     \
type name = init;                                                                                                  \
if (name)
#endif

/* NOTE: Very useful bit setting */
#ifndef ZPL_MASK_SET
#define ZPL_MASK_SET(var, set, mask)                                                                                   \
do {                                                                                                               \
    if (set)                                                                                                       \
    (var) |= (mask);                                                                                           \
    else                                                                                                           \
    (var) &= ~(mask);                                                                                          \
} while (0)
#endif

// NOTE: Some compilers support applying printf-style warnings to user functions.
#if defined(__clang__) || defined(__GNUC__)
#define ZPL_PRINTF_ARGS(FMT) __attribute__((format(printf, FMT, (FMT + 1))))
#else
#define ZPL_PRINTF_ARGS(FMT)
#endif

////////////////////////////////////////////////////////////////
//
// Debug
//
//

#ifndef ZPL_DEBUG_TRAP
#if defined(_MSC_VER)
#if _MSC_VER < 1300
#define ZPL_DEBUG_TRAP( ) __asm int 3 /* Trap to debugger! */
#else
#define ZPL_DEBUG_TRAP( ) __debugbreak( )
#endif
#else
#define ZPL_DEBUG_TRAP( ) __builtin_trap( )
#endif
#endif

#ifndef ZPL_ASSERT_MSG
#define ZPL_ASSERT_MSG(cond, msg, ...)                                                                                 \
do {                                                                                                               \
    if (!(cond)) {                                                                                                 \
        zpl_assert_handler(#cond, __FILE__, cast(zpl_i64) __LINE__, msg, ##__VA_ARGS__);                               \
        ZPL_DEBUG_TRAP( );                                                                                         \
    }                                                                                                              \
} while (0)
#endif

#ifndef ZPL_ASSERT
#define ZPL_ASSERT(cond) ZPL_ASSERT_MSG(cond, NULL)
#endif

#ifndef ZPL_ASSERT_NOT_NULL
#define ZPL_ASSERT_NOT_NULL(ptr) ZPL_ASSERT_MSG((ptr) != NULL, #ptr " must not be NULL")
#endif

// NOTE: Things that shouldn't happen with a message!
#ifndef ZPL_PANIC
#define ZPL_PANIC(msg, ...) ZPL_ASSERT_MSG(0, msg, ##__VA_ARGS__)
#endif

ZPL_DEF void zpl_assert_handler(char const *condition, char const *file, i32 line, char const *msg, ...);
ZPL_DEF i32 zpl_assert_crash(char const *condition);

//! @}
//$$

void zpl_assert_handler(char const *condition, char const *file, i32 line, char const *msg, ...) {
    zpl_printf_err("%s:(%d): Assert Failure: ", file, line);
    if (condition) zpl_printf_err("`%s` ", condition);
    if (msg) {
        va_list va;
        va_start(va, msg);
        zpl_printf_err_va(msg, va);
        va_end(va);
    }
    zpl_printf_err("\n");
}

i32 zpl_assert_crash(char const *condition) {
    ZPL_PANIC(condition);
    
    return 0;
}
