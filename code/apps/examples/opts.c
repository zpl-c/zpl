#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_OPTS
#include <zpl.h>

int main(int argc, char **argv)
{
    zpl_opts opts={0};
    
    zpl_opts_init(&opts, zpl_heap(), argv[0]);
    
    zpl_opts_add(&opts, "?", "help", "the HELP section", ZPL_OPTS_FLAG);
    zpl_opts_add(&opts, "f", "foo", "the test *foo* entry.", ZPL_OPTS_STRING);
    zpl_opts_add(&opts, "p", "pi", "PI Value Redefined !!!", ZPL_OPTS_FLOAT);
    zpl_opts_add(&opts, "4", "4pay", "hmmmm", ZPL_OPTS_INT);
    zpl_opts_add(&opts, "E", "enablegfx", "Enables HD resource pack", ZPL_OPTS_FLAG);
    
    zpl_opts_positional_add(&opts, "4pay");
    
    zpl_b32 ok=zpl_opts_compile(&opts, argc, argv);
    
    if (ok && zpl_opts_positionals_filled(&opts)) {
        
        zpl_b32 help=zpl_opts_has_arg(&opts, "help");
        if (help) {
            zpl_opts_print_help(&opts);
            return 0;
        }
        zpl_string foo=zpl_opts_string(&opts, "foo", "WRONG!");
        zpl_f64 some_num=zpl_opts_real(&opts, "pi", 0.0);
        zpl_i32 right=(zpl_i32)zpl_opts_integer(&opts, "4pay", 42);
        zpl_printf("The arg is %s\nPI value is: %f\nright: %d?\n", foo, some_num,
                   right);
        
        zpl_b32 gfx=zpl_opts_has_arg(&opts, "enablegfx");
        if (gfx) {
            zpl_printf("You wanted HD graphics? Here:\n\n");
            for (int i=0; i<5; ++i) {
                zpl_printf("iiiii\n");
            }
        }
    }
    else {
        zpl_opts_print_errors(&opts);
        zpl_opts_print_help(&opts);
    }
    
    return 0;
}

