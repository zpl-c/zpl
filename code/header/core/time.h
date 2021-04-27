// file: header/core/time.h

/** @file time.c
@brief Time helper methods.
@defgroup time Time helpers

 Helper methods for retrieving the current time in many forms under different precisions. It also offers a simple to use timer library.

 @{
 */


ZPL_BEGIN_C_DECLS

//! Return CPU timestamp.
ZPL_DEF zpl_u64 zpl_rdtsc(void);

//! Return relative time (in seconds) since the application start.
ZPL_DEF zpl_f64 zpl_time_rel(void);

//! Return relative time since the application start.
ZPL_DEF zpl_u64 zpl_time_rel_ms(void);

//! Return time (in seconds) since 1601-01-01 UTC.
ZPL_DEF zpl_f64 zpl_time_utc(void);

//! Return time since 1601-01-01 UTC.
ZPL_DEF zpl_u64 zpl_time_utc_ms(void);

//! Return local system time since 1601-01-01
ZPL_DEF zpl_u64 zpl_time_tz_ms(void);

//! Return local system time in seconds since 1601-01-01
ZPL_DEF zpl_f64 zpl_time_tz(void);

//! Convert Win32 epoch (1601-01-01 UTC) to UNIX (1970-01-01 UTC)
ZPL_DEF_INLINE zpl_u64 zpl_time_win32_to_unix(zpl_u64 ms);

//! Convert UNIX (1970-01-01 UTC) to Win32 epoch (1601-01-01 UTC)
ZPL_DEF_INLINE zpl_u64 zpl_time_unix_to_win32(zpl_u64 ms);

//! Sleep for specified number of milliseconds.
ZPL_DEF void zpl_sleep_ms(zpl_u32 ms);

//! Sleep for specified number of seconds.
ZPL_DEF_INLINE void zpl_sleep(zpl_f32 s);

// Deprecated methods
ZPL_DEPRECATED_FOR(10.9.0, zpl_time_rel)
ZPL_DEF_INLINE zpl_f64 zpl_time_now(void);

ZPL_DEPRECATED_FOR(10.9.0, zpl_time_utc)
ZPL_DEF_INLINE zpl_f64 zpl_utc_time_now(void);


#ifndef ZPL__UNIX_TO_WIN32_EPOCH
#define ZPL__UNIX_TO_WIN32_EPOCH 11644473600000ull
#endif

ZPL_IMPL_INLINE zpl_u64 zpl_time_win32_to_unix(zpl_u64 ms) {
    return ms - ZPL__UNIX_TO_WIN32_EPOCH;
}

ZPL_IMPL_INLINE zpl_u64 zpl_time_unix_to_win32(zpl_u64 ms) {
    return ms + ZPL__UNIX_TO_WIN32_EPOCH;
}

ZPL_IMPL_INLINE void zpl_sleep(zpl_f32 s) {
    zpl_sleep_ms((zpl_u32)(s * 1000));
}

ZPL_IMPL_INLINE zpl_f64 zpl_time_now() {
    return zpl_time_rel();
}

ZPL_IMPL_INLINE zpl_f64 zpl_utc_time_now() {
    return zpl_time_utc();
}

ZPL_END_C_DECLS
