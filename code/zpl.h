/**
  zpl - Pushing the boundaries of simplicity.

Usage:
#  define ZPL_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:

#  define ZPL_IMPLEMENTATION
#  include "zpl.h"

  You can also use a lightweight version of zpl by using ZPL_NANO, like:

#  define ZPL_IMPLEMENTATION
#  define ZPL_NANO
#  include "zpl.h"

  There is also a distribution that provides only the essential modules, you can enable it by defining ZPL_PICO.
  Currently, the distro offers: preprocessor helpers, debug module, memory API (except vm) and collections.
  Some of these modules used to depend on zpl_printf, but they use the standard library if the distro is enabled now.

#  define ZPL_IMPLEMENTATION
#  define ZPL_PICO
#  include "zpl.h"

Options:
  ZPL_EXPOSE_TYPES - exposes all zpl defined types to the global namespace. This means type such as `zpl_u32` is now available as `u32` globally.
  ZPL_DEFINE_NULL_MACRO - to let zpl define what NULL stands for in case it is undefined.
  ZPL_NO_MATH_H - disables the use of math.h library and replaces it with custom routines or SIMD.
  ZPL_HEAP_ANALYSIS - enables heap allocator analysis tools
  ZPL_PARSER_DISABLE_ANALYSIS - disables the extra parsing logic that would collect more information about node's formatting and structure.
                                this is useful in scenarios where a raw parsing performance is preferred over a more complex analysis.
                                It is not recommended to serialise data back since we lack the extra information about the original source document.

GitHub:
  https://github.com/zpl-c/zpl

Version History:
  @{CHANGELOG}

License:
  @{LICENSE}
*/

#ifndef ZPL_H
#define ZPL_H

#define ZPL_VERSION_MAJOR 19
#define ZPL_VERSION_MINOR 5
#define ZPL_VERSION_PATCH 0
#define ZPL_VERSION_PRE ""

#include "zpl_hedley.h"

#define ZPL_VERSION ZPL_VERSION_ENCODE(ZPL_VERSION_MAJOR, ZPL_VERSION_MINOR, ZPL_VERSION_PATCH)

#ifdef ZPL_IMPL
#    ifndef ZPL_IMPLEMENTATION
#    define ZPL_IMPLEMENTATION
#    endif
#endif

#if defined(__cplusplus) && !defined(ZPL_EXTERN)
#    define ZPL_EXTERN extern "C"
#else
#    define ZPL_EXTERN extern
#endif

#ifndef ZPL_DEF
#    if defined(ZPL_SHARED_LIB)
#        ifdef ZPL_IMPLEMENTATION
#            define ZPL_DEF ZPL_PUBLIC
#        else
#            define ZPL_DEF ZPL_IMPORT
#        endif
#    elif defined(ZPL_STATIC_LIB)
#        ifdef ZPL_IMPLEMENTATION
#            define ZPL_DEF
#        else
#            define ZPL_DEF ZPL_EXTERN
#        endif
#    elif defined(ZPL_STATIC)
#        define ZPL_DEF static
#    else
#        define ZPL_DEF ZPL_EXTERN
#    endif
#endif

#ifndef ZPL_DEF_INLINE
#    if defined(ZPL_STATIC)
#        define ZPL_DEF_INLINE
#        define ZPL_IMPL_INLINE
#    else
#        define ZPL_DEF_INLINE static
#        define ZPL_IMPL_INLINE static inline
#    endif
#endif

/* builtin overrides */
#if defined(__TINYC__) || defined(__EMSCRIPTEN__)
#    if defined(ZPL_ENFORCE_THREADING)
#        define ZPL_ENABLE_THREADING
#    else
#        define ZPL_DISABLE_THREADING
#    endif
#endif

/* Distributions */
#ifndef ZPL_CUSTOM_MODULES
    /* default distribution */
#    define ZPL_MODULE_ESSENTIALS
#    define ZPL_MODULE_CORE
#    define ZPL_MODULE_TIMER
#    define ZPL_MODULE_HASHING
#    define ZPL_MODULE_REGEX
#    define ZPL_MODULE_EVENT
#    define ZPL_MODULE_DLL
#    define ZPL_MODULE_OPTS
#    define ZPL_MODULE_PROCESS
#    define ZPL_MODULE_MATH
#    define ZPL_MODULE_THREADING
#    define ZPL_MODULE_JOBS
#    define ZPL_MODULE_PARSER
#    define ZPL_MODULE_SOCKET

    /* zpl nano distribution */
#    if defined(ZPL_NANO) || defined(ZPL_PICO)
#        undef ZPL_MODULE_TIMER
#        undef ZPL_MODULE_HASHING
#        undef ZPL_MODULE_REGEX
#        undef ZPL_MODULE_EVENT
#        undef ZPL_MODULE_DLL
#        undef ZPL_MODULE_OPTS
#        undef ZPL_MODULE_PROCESS
#        undef ZPL_MODULE_MATH
#        undef ZPL_MODULE_THREADING
#        undef ZPL_MODULE_JOBS
#        undef ZPL_MODULE_PARSER
#        undef ZPL_MODULE_SOCKET
#    endif

#    if defined(ZPL_PICO)
#        undef ZPL_MODULE_CORE
#    endif

    /* module enabling overrides */
#    if defined(ZPL_ENABLE_CORE) && !defined(ZPL_MODULE_CORE)
#        define ZPL_MODULE_CORE
#    endif
#    if defined(ZPL_ENABLE_HASHING) && !defined(ZPL_MODULE_HASHING)
#        define ZPL_MODULE_HASHING
#    endif
#    if defined(ZPL_ENABLE_REGEX) && !defined(ZPL_MODULE_REGEX)
#        define ZPL_MODULE_REGEX
#    endif
#    if defined(ZPL_ENABLE_DLL) && !defined(ZPL_MODULE_DLL)
#        define ZPL_MODULE_DLL
#    endif
#    if defined(ZPL_ENABLE_OPTS) && !defined(ZPL_MODULE_OPTS)
#        define ZPL_MODULE_OPTS
#    endif
#    if defined(ZPL_ENABLE_PROCESS) && !defined(ZPL_MODULE_PROCESS)
#        define ZPL_MODULE_PROCESS
#    endif
#    if defined(ZPL_ENABLE_MATH) && !defined(ZPL_MODULE_MATH)
#        define ZPL_MODULE_MATH
#    endif
#    if defined(ZPL_ENABLE_THREADING) && !defined(ZPL_MODULE_THREADING)
#        define ZPL_MODULE_THREADING
#    endif
#    if defined(ZPL_ENABLE_JOBS) && !defined(ZPL_MODULE_JOBS)
#        ifndef ZPL_MODULE_THREADING
#        define ZPL_MODULE_THREADING /* dependency */
#        endif
#        define ZPL_MODULE_JOBS
#    endif
#    if defined(ZPL_ENABLE_PARSER) && !defined(ZPL_MODULE_PARSER)
#        define ZPL_MODULE_PARSER
#    endif
#    if defined(ZPL_ENABLE_SOCKET) && !defined(ZPL_MODULE_SOCKET)
#        define ZPL_MODULE_SOCKET
#    endif

    /* module disabling overrides */
#    if defined(ZPL_DISABLE_CORE) && defined(ZPL_MODULE_CORE)
#        undef ZPL_MODULE_CORE
#    endif
#    if defined(ZPL_DISABLE_HASHING) && defined(ZPL_MODULE_HASHING)
#        undef ZPL_MODULE_HASHING
#    endif
#    if defined(ZPL_DISABLE_REGEX) && defined(ZPL_MODULE_REGEX)
#        undef ZPL_MODULE_REGEX
#    endif
#    if defined(ZPL_DISABLE_DLL) && defined(ZPL_MODULE_DLL)
#        undef ZPL_MODULE_DLL
#    endif
#    if defined(ZPL_DISABLE_OPTS) && defined(ZPL_MODULE_OPTS)
#        undef ZPL_MODULE_OPTS
#    endif
#    if defined(ZPL_DISABLE_PROCESS) && defined(ZPL_MODULE_PROCESS)
#        undef ZPL_MODULE_PROCESS
#    endif
#    if defined(ZPL_DISABLE_MATH) && defined(ZPL_MODULE_MATH)
#        undef ZPL_MODULE_MATH
#    endif
#    if defined(ZPL_DISABLE_THREADING) && defined(ZPL_MODULE_THREADING)
#        ifdef ZPL_MODULE_JOBS
#        undef ZPL_MODULE_JOBS /* user */
#        endif
#        undef ZPL_MODULE_THREADING
#    endif
#    if defined(ZPL_DISABLE_JOBS) && defined(ZPL_MODULE_JOBS)
#        undef ZPL_MODULE_JOBS
#    endif
#    if defined(ZPL_DISABLE_PARSER) && defined(ZPL_MODULE_PARSER)
#        undef ZPL_MODULE_PARSER
#    endif
#    if defined(ZPL_DISABLE_SOCKET) && defined(ZPL_MODULE_SOCKET)
#        undef ZPL_MODULE_SOCKET
#    endif
#endif

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wunused-function"
#    pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#    pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif

#if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4201)
#    pragma warning(disable : 4127) // Conditional expression is constant
#endif

/* general purpose includes */

#include "header/core/system.h"

#include <stdarg.h>
#include <stddef.h>

#if defined(ZPL_SYSTEM_WINDOWS)
#    include <intrin.h>
#endif

#include "header/essentials/types.h"
#include "header/essentials/helpers.h"

#if defined(ZPL_MODULE_ESSENTIALS)
#    include "header/essentials/debug.h"
#    include "header/essentials/memory.h"
#    include "header/essentials/memory_custom.h"
#    include "header/essentials/collections/array.h"
#    include "header/essentials/collections/buffer.h"
#    include "header/essentials/collections/list.h"
#    include "header/essentials/collections/ring.h"
#    include "header/essentials/collections/hashtable.h"
#    if defined(ZPL_MODULE_CORE)
#        include "header/core/memory_virtual.h"
#        include "header/core/string.h"
#        include "header/core/stringlib.h"
#        include "header/core/file.h"
#        include "header/core/file_stream.h"
#        include "header/core/file_misc.h"
#        include "header/core/file_tar.h"
#        include "header/core/print.h"
#        include "header/core/time.h"
#        include "header/core/random.h"
#        include "header/core/misc.h"
#        include "header/core/sort.h"
#    endif
#endif

#if defined(ZPL_MODULE_HASHING)
#    include "header/hashing.h"
#endif

#if defined(ZPL_MODULE_REGEX)
#    include "header/regex.h"
#endif

#if defined(ZPL_MODULE_DLL)
#    include "header/dll.h"
#endif

#if defined(ZPL_MODULE_OPTS)
#    include "header/opts.h"
#endif

#if defined(ZPL_MODULE_PROCESS)
#    include "header/process.h"
#endif

#if defined(ZPL_MODULE_MATH)
#    include "header/math.h"
#endif

#if defined(ZPL_MODULE_PARSER)
#    include "header/adt.h"

    /* parsers */
#    include "header/parsers/json.h"
#    include "header/parsers/csv.h"
#    include "header/parsers/uri.h"
#endif

#if defined(ZPL_MODULE_SOCKET)
#    include "header/socket.h"
#endif

#if defined(ZPL_MODULE_THREADING)
#    if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
#        include <pthread.h>
#    endif

#    if !defined(zpl_thread_local)
#        if defined(_MSC_VER) && _MSC_VER >= 1300
#            define zpl_thread_local __declspec(thread)
#        elif defined(__GNUC__)
#            define zpl_thread_local __thread
#        elif defined(__TINYC__)
#            define zpl_thread_local
#        else
#            define zpl_thread_local thread_local
#        endif
#    endif

#    include "header/threading/atomic.h"
#    include "header/threading/fence.h"
#    include "header/threading/sem.h"
#    include "header/threading/mutex.h"
#    include "header/threading/thread.h"
#    include "header/threading/sync.h"
#    include "header/threading/affinity.h"

#    if defined(ZPL_MODULE_JOBS)
#        include "header/jobs.h"
#    endif
#else
#    if !defined(zpl_thread_local)
#        define zpl_thread_local
#    endif
#endif

#if defined(ZPL_COMPILER_MSVC)
#    pragma warning(pop)
#endif

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic pop
#endif

#if defined(ZPL_IMPLEMENTATION) && !defined(ZPL_IMPLEMENTATION_DONE)
#define ZPL_IMPLEMENTATION_DONE

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wattributes"
#    pragma GCC diagnostic ignored "-Wunused-value"
#    pragma GCC diagnostic ignored "-Wunused-function"
#    pragma GCC diagnostic ignored "-Wwrite-strings"
#    pragma GCC diagnostic ignored "-Wunused-parameter"
#    pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#    pragma GCC diagnostic ignored "-Wmissing-braces"
#    pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#    pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#    pragma GCC diagnostic ignored "-Wignored-qualifiers"
#endif

#if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4201)
#    pragma warning(disable : 4996) // Disable deprecated POSIX functions warning
#    pragma warning(disable : 4127) // Conditional expression is constant
#    pragma warning(disable : 4204) // non-constant field initializer
#    pragma warning(disable : 4756) // -INFINITY
#    pragma warning(disable : 4056) // -INFINITY
#    pragma warning(disable : 4702) // unreachable code
#endif

/* general purpose includes */

#include <stdio.h>

// NOTE: Ensure we use standard methods for these calls if we use ZPL_PICO
#if !defined(ZPL_PICO_CUSTOM_ROUTINES)
#    if !defined(ZPL_MODULE_CORE)
#        define zpl__strlen strlen
#        define zpl__printf_err(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#        define zpl__printf_err_va(fmt, va) vfprintf(stderr, fmt, va)
#    else
#        define zpl__strlen zpl_strlen
#        define zpl__printf_err(fmt, ...) zpl_printf_err(fmt, __VA_ARGS__)
#        define zpl__printf_err_va(fmt, va) zpl_printf_err_va(fmt, va)
#    endif
#endif

#include <errno.h>

#if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
#    include <unistd.h>
#elif defined(ZPL_SYSTEM_WINDOWS)
#    if !defined(ZPL_NO_WINDOWS_H)
#        ifndef WIN32_LEAN_AND_MEAN
#            ifndef NOMINMAX
#            define NOMINMAX
#            endif

#            define WIN32_LEAN_AND_MEAN
#            define WIN32_MEAN_AND_LEAN
#            define VC_EXTRALEAN
#        endif
#        include <windows.h>
#        undef NOMINMAX
#        undef WIN32_LEAN_AND_MEAN
#        undef WIN32_MEAN_AND_LEAN
#        undef VC_EXTRALEAN
#    endif
#endif

#if defined(ZPL_MODULE_ESSENTIALS)
#    include "source/essentials/debug.c"
#    include "source/essentials/memory.c"
#    include "source/essentials/memory_custom.c"
#    if defined(ZPL_MODULE_CORE)
#        include "source/core/memory_virtual.c"
#        include "source/core/string.c"
#        include "source/core/stringlib.c"
#        include "source/core/file.c"
#        include "source/core/file_stream.c"
#        include "source/core/file_misc.c"
#        include "source/core/file_tar.c"
#        include "source/core/print.c"
#        include "source/core/time.c"
#        include "source/core/random.c"
#        include "source/core/misc.c"
#        include "source/core/sort.c"
#    endif
#endif

#if defined(ZPL_MODULE_HASHING)
#    include "source/hashing.c"
#endif

#if defined(ZPL_MODULE_REGEX)
#    include "source/regex.c"
#endif

#if defined(ZPL_MODULE_DLL)
#    include "source/dll.c"
#endif

#if defined(ZPL_MODULE_OPTS)
#    include "source/opts.c"
#endif

#if defined(ZPL_MODULE_PROCESS)
#    include "source/process.c"
#endif

#if defined(ZPL_MODULE_MATH)
#    include "source/math.c"
#endif

#if defined(ZPL_MODULE_THREADING)
#    include "source/threading/fence.c"
#    include "source/threading/atomic.c"
#    include "source/threading/sem.c"
#    include "source/threading/mutex.c"
#    include "source/threading/thread.c"
#    include "source/threading/sync.c"
#    include "source/threading/affinity.c"

#    if defined(ZPL_MODULE_JOBS)
#        include "source/jobs.c"
#    endif
#endif

#if defined(ZPL_MODULE_PARSER)
#    include "source/adt.c"

    /* parsers */
#    include "source/parsers/json.c"
#    include "source/parsers/csv.c"
#    include "source/parsers/uri.c"
#endif

#if defined(ZPL_MODULE_SOCKET)
#    include "source/socket.c"
#endif

#if defined(ZPL_COMPILER_MSVC)
#    pragma warning(pop)
#endif

#if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic pop
#endif

#endif // ZPL_IMPLEMENTATION

#if !defined(ZPL_PICO_CUSTOM_ROUTINES)
#    undef zpl__printf_err
#    undef zpl__printf_err_va
#    undef zpl__strlen
#endif

#if defined(ZPL_EXPOSE_TYPES)
    typedef zpl_u8 u8;
    typedef zpl_i8 i8;
    typedef zpl_u16 u16;
    typedef zpl_i16 i16;
    typedef zpl_u32 u32;
    typedef zpl_i32 i32;
    typedef zpl_u64 u64;
    typedef zpl_i64 i64;
    typedef zpl_b8 b8;
    typedef zpl_b16 b16;
    typedef zpl_b32 b32;
    typedef zpl_f32 f32;
    typedef zpl_f64 f64;
    typedef zpl_rune rune;
    typedef zpl_usize usize;
    typedef zpl_isize isize;
    typedef zpl_uintptr uintptr;
    typedef zpl_intptr intptr;
#endif // ZPL_EXPOSE_TYPES

#endif // ZPL_H

// TOC:
// zpl.h
// zpl_hedley.h
// header/opts.h
// header/essentials/helpers.h
// header/essentials/memory.h
// header/essentials/memory_custom.h
// header/essentials/types.h
// header/essentials/collections/buffer.h
// header/essentials/collections/list.h
// header/essentials/collections/hashtable.h
// header/essentials/collections/ring.h
// header/essentials/collections/array.h
// header/essentials/debug.h
// header/process.h
// header/threading/fence.h
// header/threading/mutex.h
// header/threading/sync.h
// header/threading/affinity.h
// header/threading/atomic.h
// header/threading/thread.h
// header/threading/sem.h
// header/math.h
// header/jobs.h
// header/parsers/json.h
// header/parsers/csv.h
// header/parsers/uri.h
// header/dll.h
// header/adt.h
// header/core/file_tar.h
// header/core/memory_virtual.h
// header/core/random.h
// header/core/file_stream.h
// header/core/string.h
// header/core/misc.h
// header/core/file.h
// header/core/stringlib.h
// header/core/sort.h
// header/core/print.h
// header/core/system.h
// header/core/file_misc.h
// header/core/time.h
// header/hashing.h
// header/regex.h
// header/socket.h
// source/hashing.c
// source/adt.c
// source/process.c
// source/essentials/debug.c
// source/essentials/memory_custom.c
// source/essentials/memory.c
// source/dll.c
// source/regex.c
// source/threading/mutex.c
// source/threading/affinity.c
// source/threading/atomic.c
// source/threading/sync.c
// source/threading/thread.c
// source/threading/fence.c
// source/threading/sem.c
// source/parsers/csv.c
// source/parsers/uri.c
// source/parsers/json.c
// source/jobs.c
// source/core/file_stream.c
// source/core/stringlib.c
// source/core/misc.c
// source/core/file_misc.c
// source/core/file.c
// source/core/memory_virtual.c
// source/core/print.c
// source/core/time.c
// source/core/string.c
// source/core/random.c
// source/core/sort.c
// source/core/file_tar.c
// source/opts.c
// source/math.c
// source/socket.c
