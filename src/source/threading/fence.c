void zpl_yield_thread(void) {
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

void zpl_mfence(void) {
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

void zpl_sfence(void) {
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

void zpl_lfence(void) {
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
