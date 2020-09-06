// file: source/core/time.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#if defined(ZPL_SYSTEM_MACOS) || ZPL_SYSTEM_UNIX
    #include <time.h>
#endif

#if defined(ZPL_SYSTEM_MACOS)
    #include <mach/mach.h>
    #include <mach/mach_time.h>
    #include <mach/clock.h>
#endif

#if defined(ZPL_SYSTEM_EMSCRIPTEN)
    #include <emscripten.h>
#endif

ZPL_BEGIN_C_DECLS

//! @}
//$$
////////////////////////////////////////////////////////////////
//
// Time
//
//

#if defined(ZPL_COMPILER_MSVC) && !defined(__clang__)
    zpl_u64 zpl_rdtsc(void) { return __rdtsc( ); }
#elif defined(__i386__)
    zpl_u64 zpl_rdtsc(void) {
        zpl_u64 x;
        __asm__ volatile(".byte 0x0f, 0x31" : "=A"(x));
        return x;
    }
#elif defined(__x86_64__)
    zpl_u64 zpl_rdtsc(void) {
        zpl_u32 hi, lo;
        __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
        return (cast(zpl_u64) lo) | ((cast(zpl_u64) hi) << 32);
    }
#elif defined(__powerpc__)
    zpl_u64 zpl_rdtsc(void) {
        zpl_u64 result = 0;
        zpl_u32 upper, lower, tmp;
        __asm__ volatile("0:                   \n"
                         "\tmftbu   %0         \n"
                         "\tmftb    %1         \n"
                         "\tmftbu   %2         \n"
                         "\tcmpw    %2,%0      \n"
                         "\tbne     0b         \n"
                         : "=r"(upper), "=r"(lower), "=r"(tmp));
        result = upper;
        result = result << 32;
        result = result | lower;

        return result;
    }
#elif defined(ZPL_SYSTEM_EMSCRIPTEN)
    zpl_u64 zpl_rdtsc(void) {
        return (zpl_u64)(emscripten_get_now() * 1e+6);
    }
#elif defined(ZPL_CPU_ARM)
    zpl_u64 zpl_rdtsc(void) {
        #if defined(__aarch64__)
            int64_t r = 0;
            asm volatile("mrs %0, cntvct_el0" : "=r"(r));
        #elif (__ARM_ARCH >= 6)
            uint32_t r = 0;
            uint32_t pmccntr;
            uint32_t pmuseren;
            uint32_t pmcntenset;

            // Read the user mode perf monitor counter access permissions.
            asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
            if (pmuseren & 1) { // Allows reading perfmon counters for user mode code.
                asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
                if (pmcntenset & 0x80000000ul) { // Is it counting?
                    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
                    // The counter is set up to count every 64th cycle
                    return ((int64_t)pmccntr) * 64; // Should optimize to << 6
                }
            }
        #else
            #error "No suitable method for zpl_rdtsc for this cpu type"
        #endif

        return r;
    }
#endif

#if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)

    zpl_f64 zpl_time_now(void) {
        zpl_local_persist LARGE_INTEGER win32_perf_count_freq = { 0 };
        zpl_f64 result;
        LARGE_INTEGER counter;
        zpl_local_persist LARGE_INTEGER win32_perf_counter = { 0 };
        if (!win32_perf_count_freq.QuadPart) {
            QueryPerformanceFrequency(&win32_perf_count_freq);
            ZPL_ASSERT(win32_perf_count_freq.QuadPart != 0);
            QueryPerformanceCounter(&win32_perf_counter);
        }

        QueryPerformanceCounter(&counter);

        result = (counter.QuadPart - win32_perf_counter.QuadPart) / cast(zpl_f64)(win32_perf_count_freq.QuadPart);
        return result;
    }

    zpl_f64 zpl_utc_time_now(void) {
        FILETIME ft;
        ULARGE_INTEGER li;

        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;

        return li.QuadPart / 10 / 10e5;
    }

    void zpl_sleep_ms(zpl_u32 ms) { Sleep(ms); }

#else

    #if defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_FREEBSD) || defined(ZPL_SYSTEM_OPENBSD) || defined(ZPL_SYSTEM_EMSCRIPTEN)
        zpl_f64 zpl__unix_gettime(void) {
            struct timespec t;
            zpl_f64 result;

            clock_gettime(1 /*CLOCK_MONOTONIC*/, &t);
            result = t.tv_sec + 1.0e-9 * t.tv_nsec;
            return result;
        }
    #endif

    zpl_f64 zpl_time_now(void) {
    #if defined(ZPL_SYSTEM_OSX)
        zpl_f64 result;

        zpl_local_persist zpl_f64 timebase = 0.0;
        zpl_local_persist zpl_u64 timestart = 0;

        if (!timestart) {
            mach_timebase_info_data_t tb = { 0 };
            mach_timebase_info(&tb);
            timebase = tb.numer;
            timebase /= tb.denom;
            timestart = mach_absolute_time( );
        }

        // NOTE: mach_absolute_time() returns things in nanoseconds
        result = 1.0e-9 * (mach_absolute_time( ) - timestart) * timebase;
        return result;
    #else
        zpl_local_persist zpl_f64 unix_timestart = 0.0;

        if (!unix_timestart) { unix_timestart = zpl__unix_gettime( ); }

        zpl_f64 now = zpl__unix_gettime( );

        return (now - unix_timestart);
    #endif
    }

    zpl_f64 zpl_utc_time_now(void) {
        struct timespec t;
    #if defined(ZPL_SYSTEM_OSX)
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self( ), CALENDAR_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self( ), cclock);
        t.tv_sec = mts.tv_sec;
        t.tv_nsec = mts.tv_nsec;
    #else
        clock_gettime(0 /*CLOCK_REALTIME*/, &t);
    #endif
        return (cast(zpl_u64) t.tv_sec * 1000000ull + t.tv_nsec / 1000 + 11644473600000000ull) / 10e5;
    }

    void zpl_sleep_ms(zpl_u32 ms) {
        struct timespec req = { cast(time_t) ms / 1000, cast(long)((ms % 1000) * 1000000) };
        struct timespec rem = { 0, 0 };
        nanosleep(&req, &rem);
    }

#endif

ZPL_END_C_DECLS
