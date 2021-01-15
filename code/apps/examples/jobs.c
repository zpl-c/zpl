#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JOBS
#include <zpl.h>

int rand(void);

#define N 30000
#define NL 100
#define CORES 4
#define JOBS 100
#define RAND_RANGE(min,max) (min + rand() % (max-min))

zpl_global zpl_u32 counter = 0;
zpl_global zpl_u32 iter = 0;

#if defined(ZPL_MODULE_THREADING)

void do_work(void *data) {
    zpl_unused(data);
}

int main() {
    zpl_thread_pool p={0};
    zpl_jobs_init_with_limit(&p, zpl_heap(), CORES, JOBS);
    zpl_u64 process_time = 0;
    zpl_f64 avg_delta_time = 0;

    zpl_printf("Jobs test, %d iterations ran on %d cores.\nPer each iteration, we spawn %d jobs.\n", N, CORES, NL);

    while (counter < N) {
        if (zpl_jobs_done(&p)) {
            counter++;
            zpl_printf("Iterations left: %d.      \r", (N-counter));
            for (int i=0; i<NL; i++) {
                zpl_jobs_enqueue(&p, do_work, 0);
            }
        }

        zpl_u64 curr_time = zpl_time_rel_ms();
        zpl_jobs_process(&p);
        zpl_u64 delta_time = zpl_time_rel_ms() - curr_time;
        avg_delta_time += delta_time;
        iter++;
    }

    process_time = avg_delta_time;
    avg_delta_time /= iter;
    zpl_printf("\nDone!\n");
    zpl_jobs_free(&p);
    zpl_printf("Test is done, results:\n* %lld ms total.\n* %.08f ms average.\n", process_time, avg_delta_time);
    return 0;
}
#else
int main(){return 0;}
#endif
