#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JOBS
#include <zpl.h>

int rand(void);

#define N 3000
#define NL 1000
#define CORES 4
#define RAND_RANGE(min,max) (min + rand() % (max-min))

zpl_global zpl_u32 counter = 0;
zpl_global zpl_u32 iter = 0;
zpl_global zpl_atomic32 total_jobs;

#if defined(ZPL_MODULE_THREADING)

void do_work(void *data) {
    zpl_unused(data);
    zpl_atomic32_fetch_add(&total_jobs, 1);
}

const char *levels[] = {
    "ZPL_JOBS_PRIORITY_REALTIME",
    "ZPL_JOBS_PRIORITY_HIGH",
    "ZPL_JOBS_PRIORITY_NORMAL",
    "ZPL_JOBS_PRIORITY_LOW",
    "ZPL_JOBS_PRIORITY_IDLE",
};

int used_levels[ZPL_JOBS_MAX_PRIORITIES];

int main() {
    zpl_thread_pool p={0};
    zpl_jobs_init_with_limit(&p, zpl_heap(), CORES, NL);
    zpl_u64 process_time = 0;
    zpl_f64 avg_delta_time = 0;
    zpl_atomic32_store(&total_jobs, 0);
    zpl_zero_array(used_levels, ZPL_JOBS_MAX_PRIORITIES);

    zpl_printf("Jobs test, %d iterations ran on %d cores.\nPer each iteration, we spawn %d jobs.\nTotal jobs to push: %d.\nJobs processed by each core approximately: %d.\n", N, CORES, NL, N*NL, (N*NL)/CORES);

    while (true) {
        if (zpl_jobs_done(&p)) {
            if (counter == N) {
                break;
            }
            counter++;
            zpl_printf("Iterations left: %d.      \r", (N-counter));
            for (int i=0; i<NL; i++) {
                zpl_u32 prio = RAND_RANGE(0, ZPL_JOBS_MAX_PRIORITIES);
                zpl_jobs_enqueue_with_priority(&p, do_work, 0, prio);
                ++used_levels[prio];
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
    zpl_u32 jobs_result = zpl_atomic32_load(&total_jobs);
    zpl_printf("\nDone!\n");
    zpl_printf("Test is done, results:\n* %lld ms total.\n* %.08f ms average.\n* total jobs processed: %d (valid? %s).\n", process_time, avg_delta_time, jobs_result, (jobs_result == N*NL) ? "yes" : "no");
    zpl_printf("Per priority queue stats:\n");
    for (int i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        zpl_thread_queue *q = &p.queues[i];
        printf("* %-26s chance: %-4d hits: %d.\n", levels[i], q->chance, used_levels[i]);
    }
    zpl_jobs_free(&p);
    return 0;
}
#else
int main(){return 0;}
#endif
