// file: source/threading/atomic.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

////////////////////////////////////////////////////////////////
//
// Concurrency
//
//
// IMPORTANT TODO: Use compiler intrinsics for the atomics

#if defined(ZPL_COMPILER_MSVC) && !defined(ZPL_COMPILER_CLANG)
    zpl_i32 zpl_atomic32_load (zpl_atomic32 const *a)      { return a->value;  }
    void     zpl_atomic32_store(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value) { a->value = value; }

    zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired) {
        return _InterlockedCompareExchange(cast(long *)a, desired, expected);
    }
    zpl_i32 zpl_atomic32_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired) {
        return _InterlockedExchange(cast(long *)a, desired);
    }
    zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return _InterlockedExchangeAdd(cast(long *)a, operand);
    }
    zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return _InterlockedAnd(cast(long *)a, operand);
    }
    zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return _InterlockedOr(cast(long *)a, operand);
    }

    zpl_i64 zpl_atomic64_load(zpl_atomic64 const *a) {
        #if defined(ZPL_ARCH_64_BIT)
            return a->value;
        #elif ZPL_CPU_X86
            // NOTE: The most compatible way to get an atomic 64-bit load on x86 is with cmpxchg8b
            zpl_atomicarg(zpl_i64) result;
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

    void zpl_atomic64_store(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value) {
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

    zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired) {
        return _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired, expected);
    }

    zpl_i64 zpl_atomic64_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired) {
        #if defined(ZPL_ARCH_64_BIT)
            return _InterlockedExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired);
        #elif ZPL_CPU_X86
            zpl_atomicarg(zpl_i64) expected = a->value;
            for (;;) {
                zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired, expected);
                if (original == expected)
                    return original;
                expected = original;
            }
        #else
            #error TODO: atomics for this CPU
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            return _InterlockedExchangeAdd64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
        #elif ZPL_CPU_X86
            zpl_atomicarg(zpl_i64) expected = a->value;
            for (;;) {
                zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected + operand, expected);
                if (original == expected)
                    return original;
                expected = original;
            }
        #else
            #error TODO: atomics for this CPU
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            return _InterlockedAnd64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
        #elif ZPL_CPU_X86
            zpl_atomicarg(zpl_i64) expected = a->value;
            for (;;) {
                zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected & operand, expected);
                if (original == expected)
                    return original;
                expected = original;
            }
        #else
            #error TODO: atomics for this CPU
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            return _InterlockedOr64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
        #elif ZPL_CPU_X86
            zpl_atomicarg(zpl_i64) expected = a->value;
            for (;;) {
                zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected | operand, expected);
                if (original == expected)
                    return original;
                expected = original;
            }
        #else
            #error TODO: atomics for this CPU
        #endif
    }

#elif defined(ZPL_CPU_X86)

    zpl_i32 zpl_atomic32_load (zpl_atomic32 const *a)      { return a->value;  }
    void zpl_atomic32_store(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value) { a->value = value; }

    zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired) {
        zpl_atomicarg(zpl_i32) original;
        __asm__(
            "lock; cmpxchgl %2, %1"
            : "=a"(original), "+m"(a->value)
            : "q"(desired), "0"(expected)
            );
        return original;
    }

    zpl_i32 zpl_atomic32_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired) {
        // NOTE: No lock prefix is necessary for xchgl
        zpl_atomicarg(zpl_i32) original;
        __asm__(
            "xchgl %0, %1"
            : "=r"(original), "+m"(a->value)
            : "0"(desired)
            );
        return original;
    }

    zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        zpl_atomicarg(zpl_i32) original;
        __asm__(
            "lock; xaddl %0, %1"
            : "=r"(original), "+m"(a->value)
            : "0"(operand)
            );
        return original;
    }

    zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        zpl_atomicarg(zpl_i32) original;
        zpl_atomicarg(zpl_i32) tmp;
        __asm__(
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

    zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        zpl_atomicarg(zpl_i32) original;
        zpl_atomicarg(zpl_i32) temp;
        __asm__(
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


    zpl_i64 zpl_atomic64_load(zpl_atomic64 const *a) {
        #if defined(ZPL_ARCH_64_BIT)
            return a->value;
        #else
            zpl_atomicarg(zpl_i64) original;
            __asm__(
                "movl %%ebx, %%eax\n"
                "movl %%ecx, %%edx\n"
                "lock; cmpxchg8b %1"
                : "=&A"(original)
                : "m"(a->value)
                );
            return original;
        #endif
    }

    void zpl_atomic64_store(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value) {
        #if defined(ZPL_ARCH_64_BIT)
            a->value = value;
        #else
            zpl_atomicarg(zpl_i64) expected = a->value;
            __asm__(
                "1:    cmpxchg8b %0\n"
                "      jne 1b"
                : "=m"(a->value)
                : "b"((zpl_atomicarg(zpl_i32))value), "c"((zpl_atomicarg(zpl_i32))(value >> 32)), "A"(expected)
                );
        #endif
    }

    zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_atomicarg(zpl_i64) original;
            __asm__(
                "lock; cmpxchgq %2, %1"
                : "=a"(original), "+m"(a->value)
                : "q"(desired), "0"(expected)
                );
            return original;
        #else
            zpl_atomicarg(zpl_i64) original;
            __asm__(
                "lock; cmpxchg8b %1"
                : "=A"(original), "+m"(a->value)
                : "b"((zpl_atomicarg(zpl_i32))desired), "c"((zpl_atomicarg(zpl_i32))(desired >> 32)), "0"(expected)
                );
            return original;
        #endif
    }

    zpl_i64 zpl_atomic64_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_atomicarg(zpl_i64) original;
            __asm__(
                "xchgq %0, %1"
                : "=r"(original), "+m"(a->value)
                : "0"(desired)
                );
            return original;
        #else
            zpl_atomicarg(zpl_i64) original = a->value;
            for (;;) {
                zpl_atomicarg(zpl_i64) previous = zpl_atomic64_compare_exchange(a, original, desired);
                if (original == previous)
                    return original;
                original = previous;
            }
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_atomicarg(zpl_i64) original;
            __asm__(
                "lock; xaddq %0, %1"
                : "=r"(original), "+m"(a->value)
                : "0"(operand)
                );
            return original;
        #else
            for (;;) {
                zpl_atomicarg(zpl_i64) original = a->value;
                if (zpl_atomic64_compare_exchange(a, original, original + operand) == original)
                    return original;
            }
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_atomicarg(zpl_i64) original;
            zpl_atomicarg(zpl_i64) tmp;
            __asm__(
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
                zpl_atomicarg(zpl_i64) original = a->value;
                if (zpl_atomic64_compare_exchange(a, original, original & operand) == original)
                    return original;
            }
        #endif
    }

    zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_atomicarg(zpl_i64) original;
            zpl_atomicarg(zpl_i64) temp;
            __asm__(
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
                zpl_atomicarg(zpl_i64) original = a->value;
                if (zpl_atomic64_compare_exchange(a, original, original | operand) == original)
                    return original;
            }
        #endif
    }

#elif !defined(ZPL_COMPILER_MSVC)
    zpl_i32 zpl_atomic32_load (zpl_atomic32 const *a) {
        zpl_atomicarg(zpl_i32) ret;
        __atomic_load((zpl_i32*)&a->value, (zpl_i32*)&ret, __ATOMIC_SEQ_CST);
        return ret;
    }
    void zpl_atomic32_store(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value) {
        __atomic_store((zpl_i32*)&a->value, (zpl_i32*)&value, __ATOMIC_SEQ_CST);
    }

    zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired) {
        zpl_atomicarg(zpl_i32) original = a->value;
        __atomic_compare_exchange_n((zpl_i32*)&a->value, (zpl_i32*)&expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return original;
    }

    zpl_i32 zpl_atomic32_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired) {
        zpl_atomicarg(zpl_i32) ret;
        __atomic_exchange((zpl_i32*)&a->value, (zpl_i32*)&desired, (zpl_i32*)&ret, __ATOMIC_SEQ_CST);
        return ret;
    }

    zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return __atomic_fetch_add((zpl_i32*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

    zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return __atomic_fetch_and((zpl_i32*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

    zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
        return __atomic_fetch_or((zpl_i32*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

    zpl_i64 zpl_atomic64_load(zpl_atomic64 const *a) {
        zpl_atomicarg(zpl_i64) ret;
        __atomic_load((zpl_i64*)&a->value, (zpl_i64*)&ret, __ATOMIC_SEQ_CST);
        return ret;
    }

    void zpl_atomic64_store(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value) {
        __atomic_store((zpl_i64*)&a->value, (zpl_i64*)&value, __ATOMIC_SEQ_CST);
    }

    zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired) {
        zpl_atomicarg(zpl_i64) original = 0;
        __atomic_compare_exchange_n((zpl_i64*)&a->value, (zpl_i64*)&expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return original;
    }

    zpl_i64 zpl_atomic64_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired) {
        zpl_atomicarg(zpl_i64) ret;
        __atomic_exchange((zpl_i64*)&a->value, (zpl_i64*)&desired, (zpl_i64*)&ret, __ATOMIC_SEQ_CST);
        return ret;
    }

    zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        return __atomic_fetch_add((zpl_i64*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

    zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        return __atomic_fetch_and((zpl_i64*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

    zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
        return __atomic_fetch_or((zpl_i64*)&a->value, operand, __ATOMIC_SEQ_CST);
    }

#else
    #error TODO: Implement Atomics for this CPU
#endif



zpl_b32 zpl_atomic32_spin_lock(zpl_atomic32 *a, zpl_isize time_out) {
    zpl_atomicarg(zpl_i32) old_value = zpl_atomic32_compare_exchange(a, 1, 0);
    zpl_i32 counter = 0;
    while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
        zpl_yield_thread();
        old_value = zpl_atomic32_compare_exchange(a, 1, 0);
        zpl_mfence();
    }
    return old_value == 0;
}

void zpl_atomic32_spin_unlock(zpl_atomic32 *a) {
    zpl_atomic32_store(a, 0);
    zpl_mfence();
}

zpl_b32 zpl_atomic64_spin_lock(zpl_atomic64 *a, zpl_isize time_out) {
    zpl_atomicarg(zpl_i64) old_value = zpl_atomic64_compare_exchange(a, 1, 0);
    zpl_atomicarg(zpl_i64) counter = 0;
    while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
        zpl_yield_thread();
        old_value = zpl_atomic64_compare_exchange(a, 1, 0);
        zpl_mfence();
    }
    return old_value == 0;
}

void zpl_atomic64_spin_unlock(zpl_atomic64 *a) {
    zpl_atomic64_store(a, 0);
    zpl_mfence();
}

zpl_b32 zpl_atomic32_try_acquire_lock(zpl_atomic32 *a) {
    zpl_atomicarg(zpl_i32) old_value;
    zpl_yield_thread();
    old_value = zpl_atomic32_compare_exchange(a, 1, 0);
    zpl_mfence();
    return old_value == 0;
}

zpl_b32 zpl_atomic64_try_acquire_lock(zpl_atomic64 *a) {
    zpl_atomicarg(zpl_i64) old_value;
    zpl_yield_thread();
    old_value = zpl_atomic64_compare_exchange(a, 1, 0);
    zpl_mfence();
    return old_value == 0;
}



#if defined(ZPL_ARCH_32_BIT)

    void* zpl_atomic_ptr_load(zpl_atomic_ptr const *a) {
        return (void *)cast(zpl_intptr)zpl_atomic32_load(cast(zpl_atomic32 const *)a);
    }
    void zpl_atomic_ptr_store(zpl_atomic_ptr *a, zpl_atomicarg(void *)value) {
        zpl_atomic32_store(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)value);
    }
    void* zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)expected, zpl_atomicarg(void *)desired) {
        return (void *)cast(zpl_intptr)zpl_atomic32_compare_exchange(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)expected, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)desired);
    }
    void* zpl_atomic_ptr_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)desired) {
        return (void *)cast(zpl_intptr)zpl_atomic32_exchange(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)desired);
    }
    void* zpl_atomic_ptr_fetch_add(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic32_fetch_add(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
    }
    void* zpl_atomic_ptr_fetch_and(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic32_fetch_and(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
    }
    void* zpl_atomic_ptr_fetch_or(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic32_fetch_or(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
    }
    zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr *a, zpl_isize time_out) {
        return zpl_atomic32_spin_lock(cast(zpl_atomic32 *)a, time_out);
    }
    void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr *a) {
        zpl_atomic32_spin_unlock(cast(zpl_atomic32 *)a);
    }
    zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a) {
        return zpl_atomic32_try_acquire_lock(cast(zpl_atomic32 *)a);
    }

#elif defined(ZPL_ARCH_64_BIT)

    void* zpl_atomic_ptr_load(zpl_atomic_ptr const *a) {
        return (void *)cast(zpl_intptr)zpl_atomic64_load(cast(zpl_atomic64 const *)a);
    }
    void zpl_atomic_ptr_store(zpl_atomic_ptr *a, zpl_atomicarg(void *)value) {
        zpl_atomic64_store(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)value);
    }
    void* zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)expected, zpl_atomicarg(void *)desired) {
        return (void *)cast(zpl_intptr)zpl_atomic64_compare_exchange(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)expected, cast(zpl_i64)cast(zpl_intptr)desired);
    }
    void* zpl_atomic_ptr_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)desired) {
        return (void *)cast(zpl_intptr)zpl_atomic64_exchange(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)desired);
    }
    void* zpl_atomic_ptr_fetch_add(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic64_fetch_add(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
    }
    void* zpl_atomic_ptr_fetch_and(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic64_fetch_and(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
    }
    void* zpl_atomic_ptr_fetch_or(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
        return (void *)cast(zpl_intptr)zpl_atomic64_fetch_or(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
    }
    zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr *a, zpl_isize time_out) {
        return zpl_atomic64_spin_lock(cast(zpl_atomic64 *)a, time_out);
    }
    void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr *a) {
        zpl_atomic64_spin_unlock(cast(zpl_atomic64 *)a);
    }
    zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a) {
        return zpl_atomic64_try_acquire_lock(cast(zpl_atomic64 *)a);
    }

#endif

ZPL_END_C_DECLS
