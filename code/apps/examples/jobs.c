#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_THREADING
#define ZPL_ENABLE_JOBS
#include <zpl.h>
#define TEST_ENQUEUE_JOB 0.8

zpl_mutex print_mut;

void calc_nums(void* data) {
    zpl_unused(data);
    zpl_i64 nums=0;
    zpl_random rnd={0};
    zpl_random_init(&rnd);

    for (int i=0; i<100; ++i) {
        nums+=(zpl_random_gen_u64(&rnd) & 100);
    }

    //zpl_sleep_ms(50*zpl_random_range_i64(&rnd, 2, 8));

    zpl_mutex_lock(&print_mut);
    zpl_printf("Result is: %ld\n", (long)nums);
    zpl_mutex_unlock(&print_mut);
}

int main() {
    zpl_random rng={0};
    zpl_thread_pool p={0};
    zpl_jobs_init(&p, zpl_heap(), 2);
    zpl_random_init(&rng);
    zpl_mutex_init(&print_mut);

    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);
    zpl_jobs_enqueue(&p, calc_nums, NULL);

    zpl_f64 time=zpl_time_rel();

    for (;;) {
        zpl_f64 now=zpl_time_rel();
        zpl_f64 dt =now-time;
        if (dt > TEST_ENQUEUE_JOB) {
            time=now;
            zpl_jobs_enqueue(&p, calc_nums, NULL);
        }

        zpl_jobs_process(&p);
    }

    return 0;
}

