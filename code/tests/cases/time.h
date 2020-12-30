#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif

#define __WIN32_TIMESTAMP_REFERENCE 13253813593098ull
#define __UNIX_TIMESTAMP_REFERENCE 1609339993098ull

MODULE(time, {
    IT("provides a relative time since the first call with 50ms delay", {
        (void)zpl_time_now_ms();
        zpl_sleep_ms(50);
        zpl_u64 b = zpl_time_now_ms();
        GREATER(b, 0);
    });

    IT("provides a UTC time since Win32 epoch", {
        GREATER(zpl_utc_time_now_ms(), __WIN32_TIMESTAMP_REFERENCE);
    });

    IT("can convert Win32 to UNIX epoch", {
        EQUALS(__WIN32_TIMESTAMP_REFERENCE, zpl_unix_to_win32_epoch(__UNIX_TIMESTAMP_REFERENCE));
    });

    IT("can convert UNIX to Win32 epoch", {
        EQUALS(__UNIX_TIMESTAMP_REFERENCE, zpl_win32_to_unix_epoch(__WIN32_TIMESTAMP_REFERENCE));
    });
});

