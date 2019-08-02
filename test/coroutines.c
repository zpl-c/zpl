#define ZPL_IMPLEMENTATION
#include <zpl.h>

zpl_global zpl_mutex test__print;
void printf_safe(const char *fmt, ...);

typedef struct {
    zpl_u32 x;
} some_data;

// this is our meat of co-routine subsystem
void send_req(zpl_co *co) {
    some_data *d = cast(some_data*)co->data;

    printf_safe("step 1: %d\n", d->x);

    // wait until main thread resumes the execution
    zpl_co_yield(co);
    
    some_data *r = cast(some_data*)co->data;
    printf_safe("step 2: no data, we pass some back\n");

    r->x = 21;

    printf_safe("step 2: guest val %d\n", r->x);

    zpl_co_yield(co);

    d = cast(some_data*)co->data;

    printf_safe("step 3: %d\n", d->x);
}

int main (void) {
    zpl_mutex_init(&test__print);

    // initialize the co-routine subsystem with 4 threads
    zpl_co_init(zpl_heap(), 4);

    // form a new co-routine (be aware of its lifetime)
    zpl_co w1 = zpl_co_make(send_req);

    // create our data
    some_data d = {42};
    some_data r = {0};
    some_data d2 = {0};

    // step 1 - start a co-routine, pass data
    printf_safe("resume step 1\n");
    zpl_co_resume(&w1, cast(void*)&d);

    do {} while (!zpl_co_waiting(&w1));

    // step 2 - resume its execution, read data back
    printf_safe("resume step 2\n");
    zpl_co_resume(&w1, cast(void*)&r);

    do {} while (!zpl_co_waiting(&w1));
    
    // step 3 - resume its execution again, pass data
    printf_safe("resume step 3\n");
    zpl_co_resume(&w1, cast(void*)&d2);

    do {} while (!zpl_co_waiting(&w1));

    d2.x = r.x * 3;
    printf_safe("r:%d,d:%d,d2:%d\n", r.x, d.x, d2.x);

    // wait until co-routine finishes its execution
    do {} while(!zpl_co_finished(&w1));

    printf_safe("we're done here!\n");
    zpl_co_destroy();
    return 0;
}


void printf_safe(const char *fmt, ...) {
    zpl_mutex_lock(&test__print);
    va_list va;
    va_start(va, fmt);
    zpl_printf_va(fmt, va);
    va_end(va);
    zpl_mutex_unlock(&test__print);
}

