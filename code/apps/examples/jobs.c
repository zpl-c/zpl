#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JOBS
#include <zpl.h>
#include <stdlib.h>

#define N 30
#define L 0.5
#define H 1.0
#define NL 30
#define NH 50
#define CORES 2
#define RAND_RANGE(min,max) (min + rand() % (max-min))

zpl_global zpl_u8 counter = 0;

#if defined(ZPL_MODULE_THREADING)

void work_low(void *data) {
    zpl_unused(data);
    zpl_sleep_ms(RAND_RANGE(5, 10));
}

void work_high(void *data) {
    zpl_unused(data);
    zpl_sleep_ms(RAND_RANGE(1, 2));
}

int main() {
    zpl_thread_pool p={0};
    zpl_jobs_init(&p, zpl_heap(), CORES);
    zpl_u64 process_time = 0, avg_delta_time = 0;

    zpl_printf("Jobs test, %d iterations ran on %d cores.\nPer each iteration, we spawn:\n* %d low-priority jobs.\n* %d high-priority jobs.\n", N, CORES, NL, NH);

    while (counter < N) {
        if (zpl_jobs_empty(&p)) {
            counter++;
            zpl_printf("Iterations left: %d.      \r", (N-counter));
            for (int i=0; i<NL; i++) {
                zpl_jobs_enqueue_with_priority(&p, work_low, 0, L);
            }
            for (int i=0; i<NH; i++) {
                zpl_jobs_enqueue_with_priority(&p, work_high, 0, H);
            }
        } else {
            zpl_u64 curr_time = zpl_time_rel_ms();
            zpl_jobs_process(&p);
            zpl_u64 delta_time = zpl_time_rel_ms() - curr_time;
            avg_delta_time += delta_time;
            process_time += delta_time;
        }
    }

    avg_delta_time /= N;
    zpl_printf("\nDone!\n");
    zpl_jobs_free(&p);
    zpl_printf("Test is done, results:\n* %lld ms process time (overall).\n* %lld ms process time (average).\n", process_time, avg_delta_time);
    return 0;
}
#else
int main(){return 0;}
#endif
