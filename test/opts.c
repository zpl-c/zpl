#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(int argc, char **argv)
{
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);

    zpl_opts_add(&opts, "f", "foo", "the test *foo* entry.", ZPL_OPTS_STRING);
    zpl_opts_add(&opts, "p", "pi", "PI Value Redefined !!!", ZPL_OPTS_FLOAT);
    zpl_opts_add(&opts, "4", "4pay", "hmmmm", ZPL_OPTS_INT);

    zpl_opts_positional_add(&opts, "4pay");

    zpl_opts_compile(&opts, argc, argv);

    zpl_string foo=zpl_opts_string(&opts, "foo", "WRONG!");
    f64 some_num=zpl_opts_real(&opts, "pi", 0.0);
    i32 right=zpl_opts_integer(&opts, "4pay", 42);


    if (zpl_opts_positionals_filled(&opts)) {
        zpl_printf("The arg is %s\nPI value is: %f\nright: %d?\n", foo, some_num,
                                                                right);
    }
    else {
        zpl_opts_print_help(&opts);
    }

    return 0;
}

