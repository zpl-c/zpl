// file: source/threading/fence.c


ZPL_BEGIN_C_DECLS

#if defined(_MSC_VER)
     /* Microsoft C/C++-compatible compiler */
#     include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
     /* GCC-compatible compiler, targeting x86/x86-64 */
#     include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON__)
     /* GCC-compatible compiler, targeting ARM with NEON */
#     include <arm_neon.h>
#elif defined(__GNUC__) && defined(__IWMMXT__)
     /* GCC-compatible compiler, targeting ARM with WMMX */
#     include <mmintrin.h>
#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
     /* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#     include <altivec.h>
#elif defined(__GNUC__) && defined(__SPE__)
     /* GCC-compatible compiler, targeting PowerPC with SPE */
#     include <spe.h>
#endif

void zpl_yield_thread(void) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        _mm_pause();
#    elif defined(ZPL_SYSTEM_OSX) || defined(ZPL_COMPILER_TINYC)
        __asm__ volatile ("" : : : "memory");
#    elif defined(ZPL_CPU_X86)
        _mm_pause();
#    endif
}

void zpl_mfence(void) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        _ReadWriteBarrier();
#    elif defined(ZPL_COMPILER_TINYC)
        __asm__ volatile ("" : : : "memory");
#    elif defined(ZPL_SYSTEM_OSX)
        __sync_synchronize();
#    elif defined(ZPL_CPU_X86)
        _mm_mfence();
#    endif
}

void zpl_sfence(void) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        _WriteBarrier();
#    elif defined(ZPL_SYSTEM_OSX) || defined(ZPL_COMPILER_TINYC)
        __asm__ volatile ("" : : : "memory");
#    elif defined(ZPL_CPU_X86)
        _mm_sfence();
#    endif
}

void zpl_lfence(void) {
#    if defined(ZPL_SYSTEM_WINDOWS)
        _ReadBarrier();
#    elif defined(ZPL_SYSTEM_OSX) || defined(ZPL_COMPILER_TINYC)
        __asm__ volatile ("" : : : "memory");
#    elif defined(ZPL_CPU_X86)
        _mm_lfence();
#    endif
}

ZPL_END_C_DECLS
