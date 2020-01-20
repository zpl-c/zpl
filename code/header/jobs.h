// file: header/jobs.h

/** @file threadpool.c
@brief Job system
@defgroup jobs Job system

 This job system follows thread pool pattern to minimize the costs of thread initialization.
 It reuses fixed number of threads to process variable number of jobs.

 @{
 */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef void (*zpl_jobs_proc)(void *data);

#define ZPL_INVALID_JOB ZPL_U32_MAX

typedef enum {
    ZPL_JOBS_STATUS_READY,
    ZPL_JOBS_STATUS_BUSY,
    ZPL_JOBS_STATUS_WAITING,
    ZPL_JOBS_STATUS_TERM,
} zpl_jobs_status;

typedef struct {
    zpl_jobs_proc proc;
    void *data;

    zpl_i32 priority;
} zpl_thread_job;

typedef struct {
    zpl_thread thread;
    zpl_atomic32 status;
    zpl_u32 jobid;
    void *pool;
} zpl_thread_worker;

typedef struct {
    zpl_allocator alloc;
    zpl_u32 max_threads;
    zpl_f32 job_spawn_treshold;
    zpl_mutex access;
    zpl_thread_worker *workers; ///< zpl_buffer
    zpl_thread_job *jobs; ///< zpl_array
    zpl_u32 *queue; ///< zpl_array
    zpl_u32 *available; ///< zpl_array
} zpl_thread_pool;

//! Initialize thread pool with specified amount of fixed threads.
ZPL_DEF void    zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads);

//! Release the resources use by thread pool.
ZPL_DEF void    zpl_jobs_free(zpl_thread_pool *pool);

//! Enqueue a job with specified data.
ZPL_DEF void    zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data);

//! Enqueue a job with specific priority with specified data.
ZPL_DEF void    zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_i32 priority);

//! Process all jobs and check all threads. Should be called by Main Thread in a tight loop.
ZPL_DEF zpl_b32 zpl_jobs_process(zpl_thread_pool *pool);

ZPL_END_C_DECLS
