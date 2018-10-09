/** @file time.c
@brief Time helper methods.
@defgroup time Time helpers

 Helper methods for retrieving the current time in many forms under different precisions. It also offers a simple to use timer library.
 
 @{
 */

//! Return CPU timestamp.
ZPL_DEF u64 zpl_rdtsc(void);

//! Return relative time since the application start.
ZPL_DEF f64 zpl_time_now(void);

//! Return time since 1601-01-01 UTC.
ZPL_DEF f64 zpl_utc_time_now(void);

//! Sleep for specified number of milliseconds.
ZPL_DEF void zpl_sleep_ms(u32 ms);

////////////////////////////////////////////////////////////////
//
// Timer
//
//

#define ZPL_TIMER_CB(name) void name(void *user_data)
typedef ZPL_TIMER_CB(zpl_timer_cb);

#define zpl_timer_t zpl_timer
typedef struct zpl_timer {
    zpl_timer_cb *callback;
    b32 enabled;
    i32 remaining_calls;
    i32 initial_calls;
    f64 next_call_ts;
    f64 duration;
    void *user_data;
} zpl_timer;

typedef zpl_array(zpl_timer) zpl_timer_pool;

//! Initialize timer pool.
#define zpl_timer_init(pool, allocator) zpl_array_init(pool, allocator)

//! Add new timer to pool and return it.
ZPL_DEF zpl_timer *zpl_timer_add(zpl_timer_pool pool);

//! Perform timer pool update.

//! Traverse over all timers and update them accordingly. Should be called by Main Thread in a tight loop.
ZPL_DEF void zpl_timer_update(zpl_timer_pool pool);

//! Set up timer.

//! Set up timer with specific options.
//! @param timer
//! @param duration How long/often to fire a timer.
//! @param count How many times we fire a timer. Use -1 for infinity.
//! @param callback A method to execute once a timer triggers.
ZPL_DEF void zpl_timer_set(zpl_timer *timer, f64 /* microseconds */ duration, i32 /* -1 for INFINITY */ count,
                           zpl_timer_cb *callback);

//! Start timer with specified delay.
ZPL_DEF void zpl_timer_start(zpl_timer *timer, f64 delay_start);

//! Stop timer and prevent it from triggering.
ZPL_DEF void zpl_timer_stop(zpl_timer *timer);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Time
//
//

#if defined(ZPL_COMPILER_MSVC) && !defined(__clang__)
zpl_inline u64 zpl_rdtsc(void) { return __rdtsc( ); }
#elif defined(__i386__)
zpl_inline u64 zpl_rdtsc(void) {
    u64 x;
    __asm__ volatile(".byte 0x0f, 0x31" : "=A"(x));
    return x;
}
#elif defined(__x86_64__)
zpl_inline u64 zpl_rdtsc(void) {
    u32 hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return (cast(u64) lo) | ((cast(u64) hi) << 32);
}
#elif defined(__powerpc__)
zpl_inline u64 zpl_rdtsc(void) {
    u64 result = 0;
    u32 upper, lower, tmp;
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
#elif defined(ZPL_CPU_ARM)
zpl_inline u64 zpl_rdtsc(void) {
#if defined(__aarch64__)
    int64_t r = 0;
    asm volatile("mrs %0, cntvct_el0" : "=r"(r));
#elif defined(__ARM_ARCH_7A__)
    uint32_t r = 0;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r));
#elif (__ARM_ARCH >= 6)
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

#if defined(ZPL_SYSTEM_WINDOWS)

zpl_inline f64 zpl_time_now(void) {
    zpl_local_persist LARGE_INTEGER win32_perf_count_freq = { 0 };
    f64 result;
    LARGE_INTEGER counter;
    zpl_local_persist LARGE_INTEGER win32_perf_counter = { 0 };
    if (!win32_perf_count_freq.QuadPart) {
        QueryPerformanceFrequency(&win32_perf_count_freq);
        ZPL_ASSERT(win32_perf_count_freq.QuadPart != 0);
        QueryPerformanceCounter(&win32_perf_counter);
    }
    
    QueryPerformanceCounter(&counter);
    
    result = (counter.QuadPart - win32_perf_counter.QuadPart) / cast(f64)(win32_perf_count_freq.QuadPart);
    return result;
}

zpl_inline f64 zpl_utc_time_now(void) {
    FILETIME ft;
    ULARGE_INTEGER li;
    
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    
    return li.QuadPart / 10 / 10e5;
}

zpl_inline void zpl_sleep_ms(u32 ms) { Sleep(ms); }

#else

#if defined(ZPL_SYSTEM_LINUX)
f64 zpl__unix_getime(void) {
    struct timespec t;
    f64 result;
    
    clock_gettime(1 /*CLOCK_MONOTONIC*/, &t);
    result = t.tv_sec + 1.0e-9 * t.tv_nsec;
    return result;
}
#endif

zpl_inline f64 zpl_time_now(void) {
#if defined(ZPL_SYSTEM_OSX)
    f64 result;
    
    zpl_local_persist f64 timebase = 0.0;
    zpl_local_persist u64 timestart = 0;
    
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
    zpl_local_persist f64 unix_timestart = 0.0;
    
    if (!unix_timestart) { unix_timestart = zpl__unix_getime( ); }
    
    f64 now = zpl__unix_getime( );
    
    return (now - unix_timestart);
#endif
}

zpl_inline f64 zpl_utc_time_now(void) {
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
    return (cast(u64) t.tv_sec * 1000000ull + t.tv_nsec / 1000 + 11644473600000000ull) / 10e5;
}

zpl_inline void zpl_sleep_ms(u32 ms) {
    struct timespec req = { cast(time_t) ms / 1000, cast(long)((ms % 1000) * 1000000) };
    struct timespec rem = { 0, 0 };
    nanosleep(&req, &rem);
}

#endif

////////////////////////////////////////////////////////////////
//
// Timer
//
//

zpl_inline zpl_timer *zpl_timer_add(zpl_timer_pool pool) {
    ZPL_ASSERT(pool);
    
    zpl_timer t = { 0 };
    zpl_array_append(pool, t);
    return pool + (zpl_array_count(pool) - 1);
}

zpl_inline void zpl_timer_set(zpl_timer *t, f64 duration, i32 count, zpl_timer_cb *cb) {
    ZPL_ASSERT(t);
    
    t->duration = duration;
    t->remaining_calls = t->initial_calls = count;
    t->callback = cb;
    t->enabled = false;
}

zpl_inline void zpl_timer_start(zpl_timer *t, f64 delay_start) {
    ZPL_ASSERT(t && !t->enabled);
    
    t->enabled = true;
    t->remaining_calls = t->initial_calls;
    t->next_call_ts = zpl_time_now( ) + delay_start;
}

zpl_inline void zpl_timer_stop(zpl_timer *t) {
    ZPL_ASSERT(t && t->enabled);
    
    t->enabled = false;
}

zpl_inline void zpl_timer_update(zpl_timer_pool pool) {
    ZPL_ASSERT(pool);
    
    f64 now = zpl_time_now( );
    
    for (isize i = 0; i < zpl_array_count(pool); ++i) {
        zpl_timer *t = pool + i;
        
        if (t->enabled) {
            if (t->remaining_calls > 0 || t->initial_calls == -1) {
                if (t->next_call_ts <= now) {
                    if (t->initial_calls != -1) { --t->remaining_calls; }
                    
                    if (t->remaining_calls == 0) {
                        t->enabled = false;
                    } else {
                        t->next_call_ts = now + t->duration;
                    }
                    
                    t->callback(t->user_data);
                }
            }
        }
    }
}
