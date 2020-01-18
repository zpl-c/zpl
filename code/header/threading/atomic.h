// Atomics
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

// TODO: Be specific with memory order?
// e.g. relaxed, acquire, release, acquire_release

#ifndef __cplusplus
# include <stdatomic.h>
#else
//# include <atomic>
# define _Atomic(X) X volatile /*std::atomic< X >*/
#endif

#if defined(ZPL_COMPILER_MSVC)
    typedef struct zpl_atomic32  { _Atomic(zpl_i32) value; } zpl_atomic32;
    typedef struct zpl_atomic64  { _Atomic(zpl_i64) value; } zpl_atomic64;
    typedef struct zpl_atomic_ptr { _Atomic(void*) value; } zpl_atomic_ptr;
#else
    #if defined(ZPL_ARCH_32_BIT)
        #define ZPL_ATOMIC_PTR_ALIGNMENT 4
    #elif defined(ZPL_ARCH_64_BIT)
        #define ZPL_ATOMIC_PTR_ALIGNMENT 8
    #else
        #error Unknown architecture
    #endif

    typedef struct zpl_atomic32   { _Atomic(zpl_i32) value; } __attribute__ ((aligned(4))) zpl_atomic32;
    typedef struct zpl_atomic64   { _Atomic(zpl_i64) value; } __attribute__ ((aligned(8))) zpl_atomic64;
    typedef struct zpl_atomic_ptr { _Atomic(void*) value; }     __attribute__ ((aligned(ZPL_ATOMIC_PTR_ALIGNMENT))) zpl_atomic_ptr;
#endif

ZPL_DEF zpl_i32  zpl_atomic32_load            (zpl_atomic32 const *a);
ZPL_DEF void     zpl_atomic32_store           (zpl_atomic32 *a, zpl_i32 value);
ZPL_DEF zpl_i32  zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_i32 expected, zpl_i32 desired);
ZPL_DEF zpl_i32  zpl_atomic32_exchange        (zpl_atomic32 *a, zpl_i32 desired);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_add       (zpl_atomic32 *a, zpl_i32 operand);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_and       (zpl_atomic32 *a, zpl_i32 operand);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_or        (zpl_atomic32 *a, zpl_i32 operand);
ZPL_DEF zpl_b32  zpl_atomic32_spin_lock       (zpl_atomic32 *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void     zpl_atomic32_spin_unlock     (zpl_atomic32 *a);
ZPL_DEF zpl_b32  zpl_atomic32_try_acquire_lock(zpl_atomic32 *a);


ZPL_DEF zpl_i64  zpl_atomic64_load            (zpl_atomic64 const *a);
ZPL_DEF void     zpl_atomic64_store           (zpl_atomic64 *a, zpl_i64 value);
ZPL_DEF zpl_i64  zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_i64 expected, zpl_i64 desired);
ZPL_DEF zpl_i64  zpl_atomic64_exchange        (zpl_atomic64 *a, zpl_i64 desired);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_add       (zpl_atomic64 *a, zpl_i64 operand);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_and       (zpl_atomic64 *a, zpl_i64 operand);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_or        (zpl_atomic64 *a, zpl_i64 operand);
ZPL_DEF zpl_b32  zpl_atomic64_spin_lock       (zpl_atomic64 *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void     zpl_atomic64_spin_unlock     (zpl_atomic64 *a);
ZPL_DEF zpl_b32  zpl_atomic64_try_acquire_lock(zpl_atomic64 *a);


ZPL_DEF void     *zpl_atomic_ptr_load            (zpl_atomic_ptr const *a);
ZPL_DEF void      zpl_atomic_ptr_store           (zpl_atomic_ptr *a, void *value);
ZPL_DEF void     *zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, void *expected, void *desired);
ZPL_DEF void     *zpl_atomic_ptr_exchange        (zpl_atomic_ptr *a, void *desired);
ZPL_DEF void     *zpl_atomic_ptr_fetch_add       (zpl_atomic_ptr *a, void *operand);
ZPL_DEF void     *zpl_atomic_ptr_fetch_and       (zpl_atomic_ptr *a, void *operand);
ZPL_DEF void     *zpl_atomic_ptr_fetch_or        (zpl_atomic_ptr *a, void *operand);
ZPL_DEF zpl_b32   zpl_atomic_ptr_spin_lock       (zpl_atomic_ptr *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void      zpl_atomic_ptr_spin_unlock     (zpl_atomic_ptr *a);
ZPL_DEF zpl_b32   zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a);
