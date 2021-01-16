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

#ifndef ZPL_JOBS_MAX_QUEUE
#define ZPL_JOBS_MAX_QUEUE 100
#endif

#ifdef ZPL_JOBS_ENABLE_DEBUG
#define ZPL_JOBS_DEBUG
#endif

typedef enum {
    ZPL_JOBS_STATUS_READY,
    ZPL_JOBS_STATUS_BUSY,
    ZPL_JOBS_STATUS_WAITING,
    ZPL_JOBS_STATUS_TERM,
} zpl_jobs_status;

typedef enum {
    ZPL_JOBS_PRIORITY_REALTIME,
    ZPL_JOBS_PRIORITY_HIGH,
    ZPL_JOBS_PRIORITY_NORMAL,
    ZPL_JOBS_PRIORITY_LOW,
    ZPL_JOBS_PRIORITY_IDLE,
    ZPL_JOBS_MAX_PRIORITIES,
} zpl_jobs_priority;

typedef struct {
    zpl_jobs_proc proc;
    void *data;
} zpl_thread_job;

ZPL_RING_DECLARE(zpl__jobs_ring_, zpl_thread_job);

typedef struct {
    zpl_thread thread;
    zpl_atomic32 status;
    zpl_thread_job job;
#ifdef ZPL_JOBS_DEBUG
    zpl_u32 hits;
    zpl_u32 idle;
#endif
} zpl_thread_worker;

typedef struct {
    zpl__jobs_ring_zpl_thread_job jobs; ///< zpl_ring
    zpl_u32 chance;
#ifdef ZPL_JOBS_DEBUG
    zpl_u32 hits;
#endif
} zpl_thread_queue;

typedef struct {
    zpl_allocator alloc;
    zpl_u32 max_threads, max_jobs, counter;
    zpl_thread_worker *workers; ///< zpl_buffer
    zpl_thread_queue queues[ZPL_JOBS_MAX_PRIORITIES];
} zpl_thread_pool;

//! Initialize thread pool with specified amount of fixed threads.
ZPL_DEF void    zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads);

//! Initialize thread pool with specified amount of fixed threads and custom job limit.
ZPL_DEF void    zpl_jobs_init_with_limit(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads, zpl_u32 max_jobs);

//! Release the resources use by thread pool.
ZPL_DEF void    zpl_jobs_free(zpl_thread_pool *pool);

//! Enqueue a job with specified data and custom priority.
ZPL_DEF zpl_b32 zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_jobs_priority priority);

//! Enqueue a job with specified data.
ZPL_DEF zpl_b32 zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data);

//! Check if the work queue is empty.
ZPL_DEF zpl_b32 zpl_jobs_empty(zpl_thread_pool *pool, zpl_jobs_priority priority);

ZPL_DEF zpl_b32 zpl_jobs_empty_all(zpl_thread_pool *pool);
ZPL_DEF zpl_b32 zpl_jobs_full_all(zpl_thread_pool *pool);

//! Check if the work queue is full.
ZPL_DEF zpl_b32 zpl_jobs_full(zpl_thread_pool *pool, zpl_jobs_priority priority);

//! Check if all workers are done.
ZPL_DEF zpl_b32 zpl_jobs_done(zpl_thread_pool *pool);

//! Process all jobs and check all threads. Should be called by Main Thread in a tight loop.
ZPL_DEF zpl_b32 zpl_jobs_process(zpl_thread_pool *pool);

ZPL_END_C_DECLS
