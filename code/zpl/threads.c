/** @file threads.c
@brief Threading methods, blocking models...
@defgroup threads Threading management

This module features common threading and blocking principles. It contains thread merge operation based on stb_sync, as well as CPU affinity management.

@{
*/

#ifdef ZPL_THREADING
// Atomics

// TODO: Be specific with memory order?
// e.g. relaxed, acquire, release, acquire_release

#if defined(ZPL_COMPILER_MSVC)
    typedef struct zpl_atomic32  { zpl_i32   volatile value; } zpl_atomic32;
    typedef struct zpl_atomic64  { zpl_i64   volatile value; } zpl_atomic64;
    typedef struct zpl_atomic_ptr { void *volatile value; } zpl_atomic_ptr;
#else
    #if defined(ZPL_ARCH_32_BIT)
        #define ZPL_ATOMIC_PTR_ALIGNMENT 4
    #elif defined(ZPL_ARCH_64_BIT)
        #define ZPL_ATOMIC_PTR_ALIGNMENT 8
    #else
        #error Unknown architecture
    #endif


typedef struct zpl_atomic32   { zpl_i32   volatile value; } __attribute__ ((aligned(4))) zpl_atomic32;
typedef struct zpl_atomic64   { zpl_i64   volatile value; } __attribute__ ((aligned(8))) zpl_atomic64;
typedef struct zpl_atomic_ptr { void *volatile value; }     __attribute__ ((aligned(ZPL_ATOMIC_PTR_ALIGNMENT))) zpl_atomic_ptr;
#endif

ZPL_DEF zpl_i32  zpl_atomic32_load            (zpl_atomic32 const volatile *a);
ZPL_DEF void     zpl_atomic32_store           (zpl_atomic32 volatile *a, zpl_i32 value);
ZPL_DEF zpl_i32  zpl_atomic32_compare_exchange(zpl_atomic32 volatile *a, zpl_i32 expected, zpl_i32 desired);
ZPL_DEF zpl_i32  zpl_atomic32_exchange        (zpl_atomic32 volatile *a, zpl_i32 desired);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_add       (zpl_atomic32 volatile *a, zpl_i32 operand);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_and       (zpl_atomic32 volatile *a, zpl_i32 operand);
ZPL_DEF zpl_i32  zpl_atomic32_fetch_or        (zpl_atomic32 volatile *a, zpl_i32 operand);
ZPL_DEF zpl_b32  zpl_atomic32_spin_lock       (zpl_atomic32 volatile *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void     zpl_atomic32_spin_unlock     (zpl_atomic32 volatile *a);
ZPL_DEF zpl_b32  zpl_atomic32_try_acquire_lock(zpl_atomic32 volatile *a);


ZPL_DEF zpl_i64  zpl_atomic64_load            (zpl_atomic64 const volatile *a);
ZPL_DEF void     zpl_atomic64_store           (zpl_atomic64 volatile *a, zpl_i64 value);
ZPL_DEF zpl_i64  zpl_atomic64_compare_exchange(zpl_atomic64 volatile *a, zpl_i64 expected, zpl_i64 desired);
ZPL_DEF zpl_i64  zpl_atomic64_exchange        (zpl_atomic64 volatile *a, zpl_i64 desired);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_add       (zpl_atomic64 volatile *a, zpl_i64 operand);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_and       (zpl_atomic64 volatile *a, zpl_i64 operand);
ZPL_DEF zpl_i64  zpl_atomic64_fetch_or        (zpl_atomic64 volatile *a, zpl_i64 operand);
ZPL_DEF zpl_b32  zpl_atomic64_spin_lock       (zpl_atomic64 volatile *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void     zpl_atomic64_spin_unlock     (zpl_atomic64 volatile *a);
ZPL_DEF zpl_b32  zpl_atomic64_try_acquire_lock(zpl_atomic64 volatile *a);


ZPL_DEF void     *zpl_atomic_ptr_load            (zpl_atomic_ptr const volatile *a);
ZPL_DEF void      zpl_atomic_ptr_store           (zpl_atomic_ptr volatile *a, void *value);
ZPL_DEF void     *zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr volatile *a, void *expected, void *desired);
ZPL_DEF void     *zpl_atomic_ptr_exchange        (zpl_atomic_ptr volatile *a, void *desired);
ZPL_DEF void     *zpl_atomic_ptr_fetch_add       (zpl_atomic_ptr volatile *a, void *operand);
ZPL_DEF void     *zpl_atomic_ptr_fetch_and       (zpl_atomic_ptr volatile *a, void *operand);
ZPL_DEF void     *zpl_atomic_ptr_fetch_or        (zpl_atomic_ptr volatile *a, void *operand);
ZPL_DEF zpl_b32   zpl_atomic_ptr_spin_lock       (zpl_atomic_ptr volatile *a, zpl_isize time_out); // NOTE: time_out = -1 as default
ZPL_DEF void      zpl_atomic_ptr_spin_unlock     (zpl_atomic_ptr volatile *a);
ZPL_DEF zpl_b32   zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr volatile *a);


// Fences
ZPL_DEF void zpl_yield_thread(void);
ZPL_DEF void zpl_mfence      (void);
ZPL_DEF void zpl_sfence      (void);
ZPL_DEF void zpl_lfence      (void);


#if defined(ZPL_SYSTEM_WINDOWS)
    typedef struct zpl_semaphore { void *win32_handle; }     zpl_semaphore;
#elif defined(ZPL_SYSTEM_OSX)
    typedef struct zpl_semaphore { semaphore_t osx_handle; } zpl_semaphore;
#elif defined(ZPL_SYSTEM_UNIX)
    typedef struct zpl_semaphore { sem_t unix_handle; }      zpl_semaphore;
#else
    #error
#endif

ZPL_DEF void zpl_semaphore_init   (zpl_semaphore *s);
ZPL_DEF void zpl_semaphore_destroy(zpl_semaphore *s);
ZPL_DEF void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count);
ZPL_DEF void zpl_semaphore_release(zpl_semaphore *s); // NOTE: zpl_semaphore_post(s, 1)
ZPL_DEF void zpl_semaphore_wait   (zpl_semaphore *s);


// Mutex

typedef struct zpl_mutex {
#if defined(ZPL_SYSTEM_WINDOWS)
    CRITICAL_SECTION win32_critical_section;
#else
    pthread_mutex_t pthread_mutex;
#endif
} zpl_mutex;

ZPL_DEF void     zpl_mutex_init    (zpl_mutex *m);
ZPL_DEF void     zpl_mutex_destroy (zpl_mutex *m);
ZPL_DEF void     zpl_mutex_lock    (zpl_mutex *m);
ZPL_DEF zpl_b32  zpl_mutex_try_lock(zpl_mutex *m);
ZPL_DEF void     zpl_mutex_unlock  (zpl_mutex *m);

struct zpl_thread;

typedef zpl_isize (*zpl_thread_proc)(struct zpl_thread *thread);

zpl_isize zpl__async_handler(struct zpl_thread *thread);

typedef struct zpl_thread {
#if defined(ZPL_SYSTEM_WINDOWS)
    void *        win32_handle;
#else
    pthread_t     posix_handle;
#endif

    zpl_thread_proc  proc;
    void *           user_data;
    zpl_isize        user_index;
    zpl_isize        return_value;

    zpl_semaphore    semaphore;
    zpl_isize        stack_size;
    zpl_b32          is_running;
} zpl_thread;

ZPL_DEF void     zpl_thread_init            (zpl_thread *t);
ZPL_DEF void     zpl_thread_destroy         (zpl_thread *t);
ZPL_DEF void     zpl_thread_start           (zpl_thread *t, zpl_thread_proc proc, void *data);
ZPL_DEF void     zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *data, zpl_isize stack_size);
ZPL_DEF void     zpl_thread_join            (zpl_thread *t);
ZPL_DEF zpl_b32  zpl_thread_is_running      (zpl_thread const *t);
ZPL_DEF zpl_u32  zpl_thread_current_id      (void);
ZPL_DEF void     zpl_thread_set_name        (zpl_thread *t, char const *name);


// NOTE: Thread Merge Operation
// Based on Sean Barrett's stb_sync

typedef struct zpl_sync {
    zpl_i32 target;  // Target Number of threads
    zpl_i32 current; // Threads to hit
    zpl_i32 waiting; // Threads waiting

    zpl_mutex start;
    zpl_mutex mutex;
    zpl_semaphore release;
} zpl_sync;

ZPL_DEF void     zpl_sync_init          (zpl_sync *s);
ZPL_DEF void     zpl_sync_destroy       (zpl_sync *s);
ZPL_DEF void     zpl_sync_set_target    (zpl_sync *s, zpl_i32 count);
ZPL_DEF void     zpl_sync_release       (zpl_sync *s);
ZPL_DEF zpl_i32  zpl_sync_reach         (zpl_sync *s);
ZPL_DEF void     zpl_sync_reach_and_wait(zpl_sync *s);



#if defined(ZPL_SYSTEM_WINDOWS)


typedef struct zpl_affinity {
    zpl_b32   is_accurate;
    zpl_isize core_count;
    zpl_isize thread_count;
#define ZPL_WIN32_MAX_THREADS (8 * zpl_size_of(zpl_usize))
    zpl_usize core_masks[ZPL_WIN32_MAX_THREADS];

} zpl_affinity;

#elif defined(ZPL_SYSTEM_OSX)

typedef struct zpl_affinity {
    zpl_b32   is_accurate;
    zpl_isize core_count;
    zpl_isize thread_count;
    zpl_isize threads_per_core;
} zpl_affinity;

#elif defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_EMSCRIPTEN)

typedef struct zpl_affinity {
    zpl_b32   is_accurate;
    zpl_isize core_count;
    zpl_isize thread_count;
    zpl_isize threads_per_core;
} zpl_affinity;
#else
#error TODO: Unknown system
#endif

ZPL_DEF void      zpl_affinity_init   (zpl_affinity *a);
ZPL_DEF void      zpl_affinity_destroy(zpl_affinity *a);
ZPL_DEF zpl_b32   zpl_affinity_set    (zpl_affinity *a, zpl_isize core, zpl_isize thread);
ZPL_DEF zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core);

#endif // ZPL_THREADING

//! @}
//$$

#ifdef ZPL_THREADING

////////////////////////////////////////////////////////////////
//
// Concurrency
//
//
// IMPORTANT TODO: Use compiler intrinsics for the atomics

#if defined(ZPL_COMPILER_MSVC) && !defined(ZPL_COMPILER_CLANG)
zpl_inline zpl_i32  zpl_atomic32_load (zpl_atomic32 const volatile *a)      { return a->value;  }
zpl_inline void     zpl_atomic32_store(zpl_atomic32 volatile *a, zpl_i32 value) { a->value = value; }

zpl_inline zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 volatile *a, zpl_i32 expected, zpl_i32 desired) {
    return _InterlockedCompareExchange(cast(long volatile *)a, desired, expected);
}
zpl_inline zpl_i32 zpl_atomic32_exchange(zpl_atomic32 volatile *a, zpl_i32 desired) {
    return _InterlockedExchange(cast(long volatile *)a, desired);
}
zpl_inline zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 volatile *a, zpl_i32 operand) {
    return _InterlockedExchangeAdd(cast(long volatile *)a, operand);
}
zpl_inline zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 volatile *a, zpl_i32 operand) {
    return _InterlockedAnd(cast(long volatile *)a, operand);
}
zpl_inline zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 volatile *a, zpl_i32 operand) {
    return _InterlockedOr(cast(long volatile *)a, operand);
}

zpl_inline zpl_i64 zpl_atomic64_load(zpl_atomic64 const volatile *a) {
#if defined(ZPL_ARCH_64_BIT)
    return a->value;
#elif ZPL_CPU_X86
    // NOTE: The most compatible way to get an atomic 64-bit load on x86 is with cmpxchg8b
    zpl_i64 result;
    __asm {
        mov esi, a;
        mov ebx, eax;
        mov ecx, edx;
        lock cmpxchg8b [esi];
        mov dword ptr result, eax;
        mov dword ptr result[4], edx;
    }
    return result;
#else
#error TODO: atomics for this CPU
#endif
}

zpl_inline void zpl_atomic64_store(zpl_atomic64 volatile *a, zpl_i64 value) {
#if defined(ZPL_ARCH_64_BIT)
    a->value = value;
#elif ZPL_CPU_X86
    // NOTE: The most compatible way to get an atomic 64-bit store on x86 is with cmpxchg8b
    __asm {
        mov esi, a;
        mov ebx, dword ptr value;
        mov ecx, dword ptr value[4];
        retry:
        cmpxchg8b [esi];
        jne retry;
    }
#else
#error TODO: atomics for this CPU
#endif
}

zpl_inline zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 volatile *a, zpl_i64 expected, zpl_i64 desired) {
    return _InterlockedCompareExchange64(cast(zpl_i64 volatile *)a, desired, expected);
}

zpl_inline zpl_i64 zpl_atomic64_exchange(zpl_atomic64 volatile *a, zpl_i64 desired) {
#if defined(ZPL_ARCH_64_BIT)
    return _InterlockedExchange64(cast(zpl_i64 volatile *)a, desired);
#elif ZPL_CPU_X86
    zpl_i64 expected = a->value;
    for (;;) {
        zpl_i64 original = _InterlockedCompareExchange64(cast(zpl_i64 volatile *)a, desired, expected);
        if (original == expected)
            return original;
        expected = original;
    }
#else
#error TODO: atomics for this CPU
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    return _InterlockedExchangeAdd64(cast(zpl_i64 volatile *)a, operand);
#elif ZPL_CPU_X86
    zpl_i64 expected = a->value;
    for (;;) {
        zpl_i64 original = _InterlockedCompareExchange64(cast(zpl_i64 volatile *)a, expected + operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }
#else
#error TODO: atomics for this CPU
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    return _InterlockedAnd64(cast(zpl_i64 volatile *)a, operand);
#elif ZPL_CPU_X86
    zpl_i64 expected = a->value;
    for (;;) {
        zpl_i64 original = _InterlockedCompareExchange64(cast(zpl_i64 volatile *)a, expected & operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }
#else
#error TODO: atomics for this CPU
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    return _InterlockedOr64(cast(zpl_i64 volatile *)a, operand);
#elif ZPL_CPU_X86
    zpl_i64 expected = a->value;
    for (;;) {
        zpl_i64 original = _InterlockedCompareExchange64(cast(zpl_i64 volatile *)a, expected | operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }
#else
#error TODO: atomics for this CPU
#endif
}



#elif defined(ZPL_CPU_X86)

zpl_inline zpl_i32  zpl_atomic32_load (zpl_atomic32 const volatile *a)      { return a->value;  }
zpl_inline void zpl_atomic32_store(zpl_atomic32 volatile *a, zpl_i32 value) { a->value = value; }

zpl_inline zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 volatile *a, zpl_i32 expected, zpl_i32 desired) {
    zpl_i32 original;
    __asm__ volatile(
        "lock; cmpxchgl %2, %1"
        : "=a"(original), "+m"(a->value)
        : "q"(desired), "0"(expected)
        );
    return original;
}

zpl_inline zpl_i32 zpl_atomic32_exchange(zpl_atomic32 volatile *a, zpl_i32 desired) {
    // NOTE: No lock prefix is necessary for xchgl
    zpl_i32 original;
    __asm__ volatile(
        "xchgl %0, %1"
        : "=r"(original), "+m"(a->value)
        : "0"(desired)
        );
    return original;
}

zpl_inline zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 volatile *a, zpl_i32 operand) {
    zpl_i32 original;
    __asm__ volatile(
        "lock; xaddl %0, %1"
        : "=r"(original), "+m"(a->value)
        : "0"(operand)
        );
    return original;
}

zpl_inline zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 volatile *a, zpl_i32 operand) {
    zpl_i32 original;
    zpl_i32 tmp;
    __asm__ volatile(
        "1:     movl    %1, %0\n"
        "       movl    %0, %2\n"
        "       andl    %3, %2\n"
        "       lock; cmpxchgl %2, %1\n"
        "       jne     1b"
        : "=&a"(original), "+m"(a->value), "=&r"(tmp)
        : "r"(operand)
        );
    return original;
}

zpl_inline zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 volatile *a, zpl_i32 operand) {
    zpl_i32 original;
    zpl_i32 temp;
    __asm__ volatile(
        "1:     movl    %1, %0\n"
        "       movl    %0, %2\n"
        "       orl     %3, %2\n"
        "       lock; cmpxchgl %2, %1\n"
        "       jne     1b"
        : "=&a"(original), "+m"(a->value), "=&r"(temp)
        : "r"(operand)
        );
    return original;
}


zpl_inline zpl_i64 zpl_atomic64_load(zpl_atomic64 const volatile *a) {
#if defined(ZPL_ARCH_64_BIT)
    return a->value;
#else
    zpl_i64 original;
    __asm__ volatile(
        "movl %%ebx, %%eax\n"
        "movl %%ecx, %%edx\n"
        "lock; cmpxchg8b %1"
        : "=&A"(original)
        : "m"(a->value)
        );
    return original;
#endif
}

zpl_inline void zpl_atomic64_store(zpl_atomic64 volatile *a, zpl_i64 value) {
#if defined(ZPL_ARCH_64_BIT)
    a->value = value;
#else
    zpl_i64 expected = a->value;
    __asm__ volatile(
        "1:    cmpxchg8b %0\n"
        "      jne 1b"
        : "=m"(a->value)
        : "b"((zpl_i32)value), "c"((zpl_i32)(value >> 32)), "A"(expected)
        );
#endif
}

zpl_inline zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 volatile *a, zpl_i64 expected, zpl_i64 desired) {
#if defined(ZPL_ARCH_64_BIT)
    zpl_i64 original;
    __asm__ volatile(
        "lock; cmpxchgq %2, %1"
        : "=a"(original), "+m"(a->value)
        : "q"(desired), "0"(expected)
        );
    return original;
#else
    zpl_i64 original;
    __asm__ volatile(
        "lock; cmpxchg8b %1"
        : "=A"(original), "+m"(a->value)
        : "b"((zpl_i32)desired), "c"((zpl_i32)(desired >> 32)), "0"(expected)
        );
    return original;
#endif
}

zpl_inline zpl_i64 zpl_atomic64_exchange(zpl_atomic64 volatile *a, zpl_i64 desired) {
#if defined(ZPL_ARCH_64_BIT)
    zpl_i64 original;
    __asm__ volatile(
        "xchgq %0, %1"
        : "=r"(original), "+m"(a->value)
        : "0"(desired)
        );
    return original;
#else
    zpl_i64 original = a->value;
    for (;;) {
        zpl_i64 previous = zpl_atomic64_compare_exchange(a, original, desired);
        if (original == previous)
            return original;
        original = previous;
    }
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    zpl_i64 original;
    __asm__ volatile(
        "lock; xaddq %0, %1"
        : "=r"(original), "+m"(a->value)
        : "0"(operand)
        );
    return original;
#else
    for (;;) {
        zpl_i64 original = a->value;
        if (zpl_atomic64_compare_exchange(a, original, original + operand) == original)
            return original;
    }
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    zpl_i64 original;
    zpl_i64 tmp;
    __asm__ volatile(
        "1:     movq    %1, %0\n"
        "       movq    %0, %2\n"
        "       andq    %3, %2\n"
        "       lock; cmpxchgq %2, %1\n"
        "       jne     1b"
        : "=&a"(original), "+m"(a->value), "=&r"(tmp)
        : "r"(operand)
        );
    return original;
#else
    for (;;) {
        zpl_i64 original = a->value;
        if (zpl_atomic64_compare_exchange(a, original, original & operand) == original)
            return original;
    }
#endif
}

zpl_inline zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 volatile *a, zpl_i64 operand) {
#if defined(ZPL_ARCH_64_BIT)
    zpl_i64 original;
    zpl_i64 temp;
    __asm__ volatile(
        "1:     movq    %1, %0\n"
        "       movq    %0, %2\n"
        "       orq     %3, %2\n"
        "       lock; cmpxchgq %2, %1\n"
        "       jne     1b"
        : "=&a"(original), "+m"(a->value), "=&r"(temp)
        : "r"(operand)
        );
    return original;
#else
    for (;;) {
        zpl_i64 original = a->value;
        if (zpl_atomic64_compare_exchange(a, original, original | operand) == original)
            return original;
    }
#endif
}

#else
#error TODO: Implement Atomics for this CPU
#endif

zpl_inline zpl_b32 zpl_atomic32_spin_lock(zpl_atomic32 volatile *a, zpl_isize time_out) {
    zpl_i32 old_value = zpl_atomic32_compare_exchange(a, 1, 0);
    zpl_i32 counter = 0;
    while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
        zpl_yield_thread();
        old_value = zpl_atomic32_compare_exchange(a, 1, 0);
        zpl_mfence();
    }
    return old_value == 0;
}
zpl_inline void zpl_atomic32_spin_unlock(zpl_atomic32 volatile *a) {
    zpl_atomic32_store(a, 0);
    zpl_mfence();
}

zpl_inline zpl_b32 zpl_atomic64_spin_lock(zpl_atomic64 volatile *a, zpl_isize time_out) {
    zpl_i64 old_value = zpl_atomic64_compare_exchange(a, 1, 0);
    zpl_i64 counter = 0;
    while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
        zpl_yield_thread();
        old_value = zpl_atomic64_compare_exchange(a, 1, 0);
        zpl_mfence();
    }
    return old_value == 0;
}

zpl_inline void zpl_atomic64_spin_unlock(zpl_atomic64 volatile *a) {
    zpl_atomic64_store(a, 0);
    zpl_mfence();
}

zpl_inline zpl_b32 zpl_atomic32_try_acquire_lock(zpl_atomic32 volatile *a) {
    zpl_i32 old_value;
    zpl_yield_thread();
    old_value = zpl_atomic32_compare_exchange(a, 1, 0);
    zpl_mfence();
    return old_value == 0;
}

zpl_inline zpl_b32 zpl_atomic64_try_acquire_lock(zpl_atomic64 volatile *a) {
    zpl_i64 old_value;
    zpl_yield_thread();
    old_value = zpl_atomic64_compare_exchange(a, 1, 0);
    zpl_mfence();
    return old_value == 0;
}



#if defined(ZPL_ARCH_32_BIT)

zpl_inline void *zpl_atomic_ptr_load(zpl_atomic_ptr const volatile *a) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_load(cast(zpl_atomic32 const volatile *)a);
}
zpl_inline void zpl_atomic_ptr_store(zpl_atomic_ptr volatile *a, void *value) {
    zpl_atomic32_store(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)value);
}
zpl_inline void *zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr volatile *a, void *expected, void *desired) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_compare_exchange(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)expected, cast(zpl_i32)cast(zpl_intptr)desired);
}
zpl_inline void *zpl_atomic_ptr_exchange(zpl_atomic_ptr volatile *a, void *desired) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_exchange(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)desired);
}
zpl_inline void *zpl_atomic_ptr_fetch_add(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_fetch_add(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)operand);
}
zpl_inline void *zpl_atomic_ptr_fetch_and(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_fetch_and(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)operand);
}
zpl_inline void *zpl_atomic_ptr_fetch_or(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic32_fetch_or(cast(zpl_atomic32 volatile *)a, cast(zpl_i32)cast(zpl_intptr)operand);
}
zpl_inline zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr volatile *a, zpl_isize time_out) {
    return zpl_atomic32_spin_lock(cast(zpl_atomic32 volatile *)a, time_out);
}
zpl_inline void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr volatile *a) {
    zpl_atomic32_spin_unlock(cast(zpl_atomic32 volatile *)a);
}
zpl_inline zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr volatile *a) {
    return zpl_atomic32_try_acquire_lock(cast(zpl_atomic32 volatile *)a);
}

#elif defined(ZPL_ARCH_64_BIT)

zpl_inline void *zpl_atomic_ptr_load(zpl_atomic_ptr const volatile *a) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_load(cast(zpl_atomic64 const volatile *)a);
}
zpl_inline void zpl_atomic_ptr_store(zpl_atomic_ptr volatile *a, void *value) {
    zpl_atomic64_store(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)value);
}
zpl_inline void *zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr volatile *a, void *expected, void *desired) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_compare_exchange(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)expected, cast(zpl_i64)cast(zpl_intptr)desired);
}
zpl_inline void *zpl_atomic_ptr_exchange(zpl_atomic_ptr volatile *a, void *desired) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_exchange(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)desired);
}
zpl_inline void *zpl_atomic_ptr_fetch_add(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_fetch_add(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)operand);
}
zpl_inline void *zpl_atomic_ptr_fetch_and(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_fetch_and(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)operand);
}
zpl_inline void *zpl_atomic_ptr_fetch_or(zpl_atomic_ptr volatile *a, void *operand) {
    return cast(void *)cast(zpl_intptr)zpl_atomic64_fetch_or(cast(zpl_atomic64 volatile *)a, cast(zpl_i64)cast(zpl_intptr)operand);
}
zpl_inline zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr volatile *a, zpl_isize time_out) {
    return zpl_atomic64_spin_lock(cast(zpl_atomic64 volatile *)a, time_out);
}
zpl_inline void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr volatile *a) {
    zpl_atomic64_spin_unlock(cast(zpl_atomic64 volatile *)a);
}
zpl_inline zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr volatile *a) {
    return zpl_atomic64_try_acquire_lock(cast(zpl_atomic64 volatile *)a);
}
#endif


zpl_inline void zpl_yield_thread(void) {
#if defined(ZPL_SYSTEM_WINDOWS)
    _mm_pause();
#elif defined(ZPL_SYSTEM_OSX)
    __asm__ volatile ("" : : : "memory");
#elif defined(ZPL_CPU_X86)
    _mm_pause();
#else
#error Unknown architecture
#endif
}

zpl_inline void zpl_mfence(void) {
#if defined(ZPL_SYSTEM_WINDOWS)
    _ReadWriteBarrier();
#elif defined(ZPL_SYSTEM_OSX)
    __sync_synchronize();
#elif defined(ZPL_CPU_X86)
    _mm_mfence();
#else
#error Unknown architecture
#endif
}

zpl_inline void zpl_sfence(void) {
#if defined(ZPL_SYSTEM_WINDOWS)
    _WriteBarrier();
#elif defined(ZPL_SYSTEM_OSX)
    __asm__ volatile ("" : : : "memory");
#elif defined(ZPL_CPU_X86)
    _mm_sfence();
#else
#error Unknown architecture
#endif
}

zpl_inline void zpl_lfence(void) {
#if defined(ZPL_SYSTEM_WINDOWS)
    _ReadBarrier();
#elif defined(ZPL_SYSTEM_OSX)
    __asm__ volatile ("" : : : "memory");
#elif defined(ZPL_CPU_X86)
    _mm_lfence();
#else
#error Unknown architecture
#endif
}


zpl_inline void zpl_semaphore_release(zpl_semaphore *s) { zpl_semaphore_post(s, 1); }

#if defined(ZPL_SYSTEM_WINDOWS)
zpl_inline void zpl_semaphore_init   (zpl_semaphore *s)            { s->win32_handle = CreateSemaphoreA(NULL, 0, ZPL_I32_MAX, NULL); }
zpl_inline void zpl_semaphore_destroy(zpl_semaphore *s)            { CloseHandle(s->win32_handle); }
zpl_inline void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { ReleaseSemaphore(s->win32_handle, count, NULL); }
zpl_inline void zpl_semaphore_wait   (zpl_semaphore *s)            { WaitForSingleObject(s->win32_handle, INFINITE); }

#elif defined(ZPL_SYSTEM_OSX)
zpl_inline void zpl_semaphore_init   (zpl_semaphore *s)            { semaphore_create(mach_task_self(), &s->osx_handle, SYNC_POLICY_FIFO, 0); }
zpl_inline void zpl_semaphore_destroy(zpl_semaphore *s)            { semaphore_destroy(mach_task_self(), s->osx_handle); }
zpl_inline void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) semaphore_signal(s->osx_handle); }
zpl_inline void zpl_semaphore_wait   (zpl_semaphore *s)            { semaphore_wait(s->osx_handle); }

#elif defined(ZPL_SYSTEM_UNIX)
zpl_inline void zpl_semaphore_init   (zpl_semaphore *s)            { sem_init(&s->unix_handle, 0, 0); }
zpl_inline void zpl_semaphore_destroy(zpl_semaphore *s)            { sem_destroy(&s->unix_handle); }
zpl_inline void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) sem_post(&s->unix_handle); }
zpl_inline void zpl_semaphore_wait   (zpl_semaphore *s)            { int i; do { i = sem_wait(&s->unix_handle); } while (i == -1 && errno == EINTR); }

#else
#error
#endif

zpl_inline void zpl_mutex_init(zpl_mutex *m) {
#if defined(ZPL_SYSTEM_WINDOWS)
    InitializeCriticalSection(&m->win32_critical_section);
#else
    pthread_mutex_init(&m->pthread_mutex, NULL);
#endif
}

zpl_inline void zpl_mutex_destroy(zpl_mutex *m) {
#if defined(ZPL_SYSTEM_WINDOWS)
    DeleteCriticalSection(&m->win32_critical_section);
#else
    pthread_mutex_destroy(&m->pthread_mutex);
#endif
}

zpl_inline void zpl_mutex_lock(zpl_mutex *m) {
#if defined(ZPL_SYSTEM_WINDOWS)
    EnterCriticalSection(&m->win32_critical_section);
#else
    pthread_mutex_lock(&m->pthread_mutex);
#endif
}

zpl_inline zpl_b32 zpl_mutex_try_lock(zpl_mutex *m) {
#if defined(ZPL_SYSTEM_WINDOWS)
    return TryEnterCriticalSection(&m->win32_critical_section);
#else
    return pthread_mutex_trylock(&m->pthread_mutex);
#endif
}

zpl_inline void zpl_mutex_unlock(zpl_mutex *m) {
#if defined(ZPL_SYSTEM_WINDOWS)
    LeaveCriticalSection(&m->win32_critical_section);
#else
    pthread_mutex_unlock(&m->pthread_mutex);
#endif
}

void zpl_thread_init(zpl_thread *t) {
    zpl_zero_item(t);
#if defined(ZPL_SYSTEM_WINDOWS)
    t->win32_handle = INVALID_HANDLE_VALUE;
#else
    t->posix_handle = 0;
#endif
    zpl_semaphore_init(&t->semaphore);
}

void zpl_thread_destroy(zpl_thread *t) {
    if (t->is_running) zpl_thread_join(t);
    zpl_semaphore_destroy(&t->semaphore);
}

zpl_inline void zpl__thread_run(zpl_thread *t) {
    zpl_semaphore_release(&t->semaphore);
    t->return_value = t->proc(t);
}

#if defined(ZPL_SYSTEM_WINDOWS)
zpl_inline DWORD __stdcall zpl__thread_proc(void *arg) {
    zpl_thread *t = cast(zpl_thread *)arg;
    zpl__thread_run(t);
    t->is_running = false;
    return 0;
}
#else
zpl_inline void *zpl__thread_proc(void *arg) {
    zpl_thread *t = cast(zpl_thread *)arg;
    zpl__thread_run(t);
    t->is_running = false;
    return NULL;
}
#endif

zpl_inline void zpl_thread_start(zpl_thread *t, zpl_thread_proc proc, void *user_data) { zpl_thread_start_with_stack(t, proc, user_data, 0); }

zpl_inline void zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *user_data, zpl_isize stack_size) {
    ZPL_ASSERT(!t->is_running);
    ZPL_ASSERT(proc != NULL);
    t->proc = proc;
    t->user_data = user_data;
    t->stack_size = stack_size;

#if defined(ZPL_SYSTEM_WINDOWS)
    t->win32_handle = CreateThread(NULL, stack_size, zpl__thread_proc, t, 0, NULL);
    ZPL_ASSERT_MSG(t->win32_handle != NULL, "CreateThread: GetLastError");
#else
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        if (stack_size != 0)
            pthread_attr_setstacksize(&attr, stack_size);
        pthread_create(&t->posix_handle, &attr, zpl__thread_proc, t);
        pthread_attr_destroy(&attr);
    }
#endif

    t->is_running = true;
    zpl_semaphore_wait(&t->semaphore);
}

zpl_inline void zpl_thread_join(zpl_thread *t) {
    if (!t->is_running) return;

#if defined(ZPL_SYSTEM_WINDOWS)
    WaitForSingleObject(t->win32_handle, INFINITE);
    CloseHandle(t->win32_handle);
    t->win32_handle = INVALID_HANDLE_VALUE;
#else
    pthread_join(t->posix_handle, NULL);
    t->posix_handle = 0;
#endif
    t->is_running = false;
}

zpl_inline zpl_b32 zpl_thread_is_running(zpl_thread const *t) { return t->is_running != 0; }

zpl_inline zpl_u32 zpl_thread_current_id(void) {
    zpl_u32 thread_id;
#if defined(ZPL_SYSTEM_WINDOWS)
#if defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
    thread_id = (cast(zpl_u32 *)__readfsdword(24))[9];
#elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
    thread_id = (cast(zpl_u32 *)__readgsqword(48))[18];
#else
    thread_id = GetCurrentThreadId();
#endif

#elif defined(ZPL_SYSTEM_OSX) && defined(ZPL_ARCH_64_BIT)
    thread_id = pthread_mach_thread_np(pthread_self());
#elif defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
    __asm__("mov %%gs:0x08,%0" : "=r"(thread_id));
#elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
    __asm__("mov %%fs:0x10,%0" : "=r"(thread_id));
#else
#error Unsupported architecture for zpl_thread_current_id()
#endif

    return thread_id;
}



void zpl_thread_set_name(zpl_thread *t, char const *name) {
#if defined(ZPL_COMPILER_MSVC)
#pragma pack(push, 8)
    typedef struct {
        DWORD       type;
        char const *name;
        DWORD       id;
        DWORD       flags;
    } zplprivThreadName;
#pragma pack(pop)
    zplprivThreadName tn;
    tn.type  = 0x1000;
    tn.name  = name;
    tn.id    = GetThreadId(cast(HANDLE)t->win32_handle);
    tn.flags = 0;

    __try {
        RaiseException(0x406d1388, 0, zpl_size_of(tn)/4, cast(ULONG_PTR *)&tn);
    } __except(1 /*EXCEPTION_EXECUTE_HANDLER*/) {
    }

#elif defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_COMPILER_MSVC)
    zpl_unused(t);
    zpl_unused(name);
    // IMPORTANT TODO: Set thread name for GCC/Clang on windows
    return;
#elif defined(ZPL_SYSTEM_OSX)
    // TODO: Test if this works
    pthread_setname_np(name);
#else
    zpl_unused(t);
    zpl_unused(name);
    // TODO: Test if this works
    //        pthread_set_name_np(t->posix_handle, name);
#endif
}

void zpl_sync_init(zpl_sync *s) {
    zpl_zero_item(s);
    zpl_mutex_init(&s->mutex);
    zpl_mutex_init(&s->start);
    zpl_semaphore_init(&s->release);
}

void zpl_sync_destroy(zpl_sync *s) {
    if (s->waiting) {
        ZPL_PANIC("Cannot destroy while threads are waiting!");
    }

    zpl_mutex_destroy(&s->mutex);
    zpl_mutex_destroy(&s->start);
    zpl_semaphore_destroy(&s->release);
}

void zpl_sync_set_target(zpl_sync *s, zpl_i32 count) {
    zpl_mutex_lock(&s->start);

    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->target == 0);
    s->target = count;
    s->current = 0;
    s->waiting = 0;
    zpl_mutex_unlock(&s->mutex);
}

void zpl_sync_release(zpl_sync *s) {
    if (s->waiting) {
        zpl_semaphore_release(&s->release);
    } else {
        s->target = 0;
        zpl_mutex_unlock(&s->start);
    }
}

zpl_i32 zpl_sync_reach(zpl_sync *s) {
    zpl_i32 n;
    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->current < s->target);
    n = ++s->current; // NOTE: Record this value to avoid possible race if `return s->current` was done
    if (s->current == s->target)
        zpl_sync_release(s);
    zpl_mutex_unlock(&s->mutex);
    return n;
}

void zpl_sync_reach_and_wait(zpl_sync *s) {
    zpl_mutex_lock(&s->mutex);
    ZPL_ASSERT(s->current < s->target);
    s->current++;
    if (s->current == s->target) {
        zpl_sync_release(s);
        zpl_mutex_unlock(&s->mutex);
    } else {
        s->waiting++;                   // NOTE: Waiting, so one more waiter
        zpl_mutex_unlock(&s->mutex);     // NOTE: Release the mutex to other threads

        zpl_semaphore_wait(&s->release); // NOTE: Wait for merge completion

        zpl_mutex_lock(&s->mutex);       // NOTE: On merge completion, lock mutex
        s->waiting--;                   // NOTE: Done waiting
        zpl_sync_release(s);             // NOTE: Restart the next waiter
        zpl_mutex_unlock(&s->mutex);
    }
}

#if defined(ZPL_SYSTEM_WINDOWS)
void zpl_affinity_init(zpl_affinity *a) {
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION *start_processor_info = NULL;
    DWORD length = 0;
    zpl_b32 result  = GetLogicalProcessorInformation(NULL, &length);

    zpl_zero_item(a);

    if (!result && GetLastError() == 122l /*ERROR_INSUFFICIENT_BUFFER*/ && length > 0) {
        start_processor_info = cast(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)zpl_alloc(zpl_heap_allocator(), length);
        result = GetLogicalProcessorInformation(start_processor_info, &length);
        if (result) {
            SYSTEM_LOGICAL_PROCESSOR_INFORMATION *end_processor_info, *processor_info;

            a->is_accurate  = true;
            a->core_count   = 0;
            a->thread_count = 0;
            end_processor_info = cast(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)zpl_pointer_add(start_processor_info, length);

            for (processor_info = start_processor_info;
                 processor_info < end_processor_info;
                 processor_info++) {
                if (processor_info->Relationship == RelationProcessorCore) {
                    zpl_isize thread = zpl_count_set_bits(processor_info->ProcessorMask);
                    if (thread == 0) {
                        a->is_accurate = false;
                    } else if (a->thread_count + thread > ZPL_WIN32_MAX_THREADS) {
                        a->is_accurate = false;
                    } else {
                        ZPL_ASSERT(a->core_count <= a->thread_count &&
                                   a->thread_count < ZPL_WIN32_MAX_THREADS);
                        a->core_masks[a->core_count++] = processor_info->ProcessorMask;
                        a->thread_count += thread;
                    }
                }
            }
        }

        zpl_free(zpl_heap_allocator(), start_processor_info);
    }

    ZPL_ASSERT(a->core_count <= a->thread_count);
    if (a->thread_count == 0) {
        a->is_accurate   = false;
        a->core_count    = 1;
        a->thread_count  = 1;
        a->core_masks[0] = 1;
    }

}
void zpl_affinity_destroy(zpl_affinity *a) {
    zpl_unused(a);
}


zpl_b32 zpl_affinity_set(zpl_affinity *a, zpl_isize core, zpl_isize thread) {
    zpl_usize available_mask, check_mask = 1;
    ZPL_ASSERT(thread < zpl_affinity_thread_count_for_core(a, core));

    available_mask = a->core_masks[core];
    for (;;) {
        if ((available_mask & check_mask) != 0) {
            if (thread-- == 0) {
                zpl_usize result = SetThreadAffinityMask(GetCurrentThread(), check_mask);
                return result != 0;
            }
        }
        check_mask <<= 1; // NOTE: Onto the next bit
    }
}

zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
    ZPL_ASSERT(core >= 0 && core < a->core_count);
    return zpl_count_set_bits(a->core_masks[core]);
}

#elif defined(ZPL_SYSTEM_OSX)
void zpl_affinity_init(zpl_affinity *a) {
    zpl_usize count, count_size = zpl_size_of(count);

    a->is_accurate      = false;
    a->thread_count     = 1;
    a->core_count       = 1;
    a->threads_per_core = 1;

    if (sysctlbyname("hw.logicalcpu", &count, &count_size, NULL, 0) == 0) {
        if (count > 0) {
            a->thread_count = count;
            // Get # of physical cores
            if (sysctlbyname("hw.physicalcpu", &count, &count_size, NULL, 0) == 0) {
                if (count > 0) {
                    a->core_count = count;
                    a->threads_per_core = a->thread_count / count;
                    if (a->threads_per_core < 1)
                        a->threads_per_core = 1;
                    else
                        a->is_accurate = true;
                }
            }
        }
    }

}

void zpl_affinity_destroy(zpl_affinity *a) {
    zpl_unused(a);
}

zpl_b32 zpl_affinity_set(zpl_affinity *a, zpl_isize core, zpl_isize thread_index) {
    zpl_isize index;
    thread_t thread;
    thread_affinity_policy_data_t info;
    kern_return_t result;

    ZPL_ASSERT(core < a->core_count);
    ZPL_ASSERT(thread_index < a->threads_per_core);

    index = core * a->threads_per_core + thread_index;
    thread = mach_thread_self();
    info.affinity_tag = cast(integer_t)index;
    result = thread_policy_set(thread, THREAD_AFFINITY_POLICY, cast(thread_policy_t)&info, THREAD_AFFINITY_POLICY_COUNT);
    return result == KERN_SUCCESS;
}

zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
    ZPL_ASSERT(core >= 0 && core < a->core_count);
    return a->threads_per_core;
}

#elif defined(ZPL_SYSTEM_LINUX)
// IMPORTANT TODO: This zpl_affinity stuff for linux needs be improved a lot!
// NOTE(zangent): I have to read /proc/cpuinfo to get the number of threads per core.
#include <stdio.h>

void zpl_affinity_init(zpl_affinity *a) {
    zpl_b32   accurate = true;
    zpl_isize threads = 0;

    a->thread_count     = 1;
    a->core_count       = sysconf(_SC_NPROCESSORS_ONLN);
    a->threads_per_core = 1;


    if(a->core_count <= 0) {
        a->core_count = 1;
        accurate = false;
    }

    // Parsing /proc/cpuinfo to get the number of threads per core.
    // NOTE(zangent): This calls the CPU's threads "cores", although the wording
    // is kind of weird. This should be right, though.
    FILE *cpu_info = fopen("/proc/cpuinfo", "r");
    if (cpu_info != NULL) {
        for (;;) {
            // The 'temporary char'. Everything goes into this char,
            // so that we can check against EOF at the end of this loop.
            int c;

#define AF__CHECK(letter) ((c = getc(cpu_info)) == letter)
            if (AF__CHECK('c') && AF__CHECK('p') && AF__CHECK('u') && AF__CHECK(' ') &&
                AF__CHECK('c') && AF__CHECK('o') && AF__CHECK('r') && AF__CHECK('e') && AF__CHECK('s')) {
                // We're on a CPU info line.
                while (!AF__CHECK(EOF)) {
                    if (c == '\n') {
                        break;
                    } else if (c < '0' || '9' > c) {
                        continue;
                    }
                    threads = threads * 10 + (c - '0');
                }
                break;
            } else {
                while (!AF__CHECK('\n')) {
                    if (c==EOF) {
                        break;
                    }
                }
            }
            if (c == EOF) {
                break;
            }
#undef AF__CHECK
        }

        fclose(cpu_info);
    }

    if (threads == 0) {
        threads  = 1;
        accurate = false;
    }

    a->threads_per_core = threads;
    a->thread_count = a->threads_per_core * a->core_count;
    a->is_accurate = accurate;

}

void zpl_affinity_destroy(zpl_affinity *a) {
    zpl_unused(a);
}

zpl_b32 zpl_affinity_set(zpl_affinity * a, zpl_isize core, zpl_isize thread_index) {
    zpl_unused(a);
    zpl_unused(core);
    zpl_unused(thread_index);
    return true;
}

zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
    ZPL_ASSERT(0 <= core && core < a->core_count);
    return a->threads_per_core;
}
#elif defined(ZPL_SYSTEM_EMSCRIPTEN)
// no code 4 u :(
#else
    #error TODO: Unknown system
#endif

#endif // ZPL_THREADING
