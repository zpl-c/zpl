// file: header/core/time.h

/** @file time.c
@brief Time helper methods.
@defgroup time Time helpers

 Helper methods for retrieving the current time in many forms under different precisions. It also offers a simple to use timer library.

 @{
 */

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

//! Return CPU timestamp.
ZPL_DEF zpl_u64 zpl_rdtsc(void);

//! Return relative time since the application start.
ZPL_DEF zpl_f64 zpl_time_now(void);

//! Return time since 1601-01-01 UTC.
ZPL_DEF zpl_f64 zpl_utc_time_now(void);

//! Sleep for specified number of milliseconds.
ZPL_DEF void zpl_sleep_ms(zpl_u32 ms);

ZPL_END_C_DECLS
