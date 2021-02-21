#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JOBS
#define ZPL_JOBS_ENABLE_DEBUG
#include <zpl.h>

int rand(void);

#define N (10 * 1000)
#define NL 10000
#define CORES 4
#define RAND_RANGE(min,max) (min + rand() % (max-min))

#if defined(ZPL_MODULE_THREADING)

zpl_global zpl_i64 counter = 0;
zpl_global zpl_u32 iter = 0;
zpl_global zpl_atomic32 total_jobs;

void do_work(void *data) {
    zpl_unused(data);
    zpl_atomic32_fetch_add(&total_jobs, 1);
}

const char *levels[] = {
    "REALTIME",
    "HIGH",
    "NORMAL",
    "LOW",
    "IDLE",
};

int main(int argc, char **argv) {
    zpl_u32 num_cores = CORES;
    if (argc > 1) {
        num_cores = zpl_str_to_u64(argv[1], NULL, 10);
    }
    zpl_jobs_system p={0};
    zpl_jobs_init_with_limit(&p, zpl_heap(), num_cores, NL);
    zpl_u64 process_time = 0;
    zpl_f64 avg_delta_time = 0;
    zpl_atomic32_store(&total_jobs, 0);
    counter = N;

    zpl_printf("Jobs test, run duration: %d ms. Ran on %d cores.\nWe spawn %d jobs per cycle.\n", N, num_cores, NL);

    while (counter > 0) {
        zpl_u64 last_time = zpl_time_rel_ms();
        for (int i=0; i<NL; i++) {
            zpl_u32 prio = i % ZPL_JOBS_MAX_PRIORITIES;
            zpl_jobs_enqueue_with_priority(&p, do_work, 0, (zpl_jobs_priority)prio);
        }

        if (iter % 15 == 0) {
            zpl_printf("Time left: %lld ms            \r", counter);
        }

        zpl_u64 curr_time = zpl_time_rel_ms();
        zpl_jobs_process(&p);
        zpl_u64 delta_time = zpl_time_rel_ms() - curr_time;
        avg_delta_time += delta_time;
        iter++;
        counter -= zpl_time_rel_ms() - last_time;
    }

    process_time = avg_delta_time;
    avg_delta_time /= iter;
    zpl_u32 jobs_result = zpl_atomic32_load(&total_jobs);
    zpl_printf("%-80s\n", "Done!");
    zpl_printf("\n\"zpl_jobs_process\" results:\n* %lld ms total.\n* %.08f ms average.\n* total jobs processed: %d.\n", (long long)process_time, avg_delta_time, jobs_result);
    zpl_printf("\nPer priority queue stats:\n");
    for (int i = 0; i < ZPL_JOBS_MAX_PRIORITIES; ++i) {
        zpl_thread_queue *q = &p.queues[i];
        zpl_printf("* %-8s chance: %-4d hits: %d.\n", levels[i], q->chance, q->hits);
    }

    zpl_printf("\nPer thread worker stats:\n");
    for (zpl_usize i = 0; i < p.max_threads; ++i) {
        zpl_thread_worker *tw = p.workers + i;
        zpl_printf("* worker %-2u hits: %-8d idle: %d cy.\n", (unsigned int)i, tw->hits, tw->idle);
    }
    zpl_jobs_free(&p);
    return 0;
}
#else
int main(){return 0;}
#endif
