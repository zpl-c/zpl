#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_THREADING
#define ZPL_ENABLE_COROUTINES
#define ZPL_ENABLE_JOBS
#include <zpl.h>

#if defined(ZPL_MODULE_THREADING)

typedef struct {
    zpl_u32 x;
} some_data;

// this is our meat of co-routine subsystem
void send_req(zpl_co *co) {
    some_data *d = cast(some_data*)co->data;

    zpl_printf("step 1: %d\n", d->x);

    zpl_sleep_ms(500);

    // wait until main thread resumes the execution
    zpl_co_yield(co);

    some_data *r = cast(some_data*)co->data;
    zpl_printf("step 2: no data, we pass some back\n");

    r->x = 21;

    zpl_printf("step 2: guest val %d\n", r->x);

    zpl_co_yield(co);

    zpl_sleep_ms(500);

    d = cast(some_data*)co->data;

    zpl_printf("step 3: %d\n", d->x);
}

int main (void) {
    // initialize the co-routine subsystem with 4 threads
    zpl_co_init(zpl_heap(), 4);

    // form a new co-routine (be aware of its lifetime)
    zpl_co w1;
    zpl_co_make(&w1, send_req);

    // create our data
    some_data d = {42};
    some_data r = {0};
    some_data d2 = {0};

    // step 1 - start a co-routine, pass data
    zpl_printf("resume step 1\n");
    zpl_co_resume(&w1, cast(void*)&d);

    do {} while (!zpl_co_waiting(&w1));

    // step 2 - resume its execution, read data back
    zpl_printf("resume step 2\n");
    zpl_co_resume(&w1, cast(void*)&r);

    do {} while (!zpl_co_waiting(&w1));

    // step 3 - resume its execution again, pass data
    zpl_printf("resume step 3\n");
    zpl_co_resume(&w1, cast(void*)&d2);

    do {} while (!zpl_co_waiting(&w1));

    d2.x = r.x * 3;
    zpl_printf("r:%d,d:%d,d2:%d\n", r.x, d.x, d2.x);

    // wait until co-routine finishes its execution
    do {} while(!zpl_co_finished(&w1));

    zpl_printf("we're done here!\n");
    zpl_co_destroy();
    return 0;
}
#else
int main(){return 0;}
#endif
