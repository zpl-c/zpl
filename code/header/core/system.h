// file: header/core/system.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

/* Platform architecture */

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

/* Platform endiannes */

#ifndef ZPL_ENDIAN_ORDER
    #define ZPL_ENDIAN_ORDER
    #define ZPL_IS_BIG_ENDIAN (!*(zpl_u8 *)&(zpl_u16){ 1 })
    #define ZPL_IS_LITTLE_ENDIAN (!ZPL_IS_BIG_ENDIAN)
#endif

/* Platform OS */

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
    #elif defined(__OpenBSD__)
        #ifndef ZPL_SYSTEM_OPENBSD
            #define ZPL_SYSTEM_OPENBSD 1
        #endif
    #elif defined(__EMSCRIPTEN__)
        #ifndef ZPL_SYSTEM_EMSCRIPTEN
            #define ZPL_SYSTEM_EMSCRIPTEN 1
        #endif
    #elif defined(__CYGWIN__)
        #ifndef ZPL_SYSTEM_CYGWIN
            #define ZPL_SYSTEM_CYGWIN 1
        #endif
    #else
        #error This UNIX operating system is not supported
    #endif
#else
    #error This operating system is not supported
#endif

/* Platform compiler */

#if defined(_MSC_VER)
    #define ZPL_COMPILER_MSVC 1
#elif defined(__GNUC__)
    #define ZPL_COMPILER_GCC 1
#elif defined(__clang__)
    #define ZPL_COMPILER_CLANG 1
#elif defined(__MINGW32__)
    #define ZPL_COMPILER_MINGW 1
#elif defined(__TINYC__)
    #define ZPL_COMPILER_TINYC 1
#else
    #error Unknown compiler
#endif

/* Platform CPU */

#if defined(__arm__) || defined(__aarch64__) || defined(__ARM_ARCH)
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

// TODO(ZaKlaus): Find a better way to get this flag in MinGW.
#if defined(ZPL_COMPILER_GCC) && !defined(WC_ERR_INVALID_CHARS)
    #define WC_ERR_INVALID_CHARS 0x0080
#endif

#if defined(ZPL_COMPILER_GCC) && defined(ZPL_SYSTEM_WINDOWS)
    #ifndef ZPL_COMPILER_MINGW
    #define ZPL_COMPILER_MINGW // assume we use mingw as a compiler
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

#if ZPL_GNUC_VERSION_CHECK(3, 3, 0)
    #define ZPL_INFINITY (__builtin_inff())
    #define ZPL_NAN (__builtin_nanf(""))
#else
    #define ZPL_INFINITY (1e10000f)
    #define ZPL_NAN (0.0f / 0.0f)
#endif

ZPL_END_C_DECLS
