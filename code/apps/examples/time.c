#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

void do_time(void) {
    zpl_f64 a1 = zpl_time_now();
    zpl_u64 a2 = zpl_time_now_ms();
    zpl_u64 u1 = zpl_utc_time_now_ms();
    zpl_f64 u2 = zpl_utc_time_now();
    zpl_u64 unix_timestamp = zpl_win32_to_unix_epoch(u1);

    zpl_printf("Time: f64(%f) u64(%llu) utc_u64(%llu) utc_f64(%f) unix_u64(%llu)\n", a1, a2, u1, u2, unix_timestamp);
}

int main() {
    zpl_time_now_ms();
    zpl_sleep(1.534);
    do_time();

    while(1) {
        zpl_sleep(1);
        do_time();
    }
    return 0;
}
