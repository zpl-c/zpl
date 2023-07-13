#define ZPL_IMPL
#define ZPL_NANO
#define ZPL_ENABLE_OPTS
#define ZPL_ENABLE_HASHING
#include <zpl.h>

void exit_with_help(zpl_opts *opts);

int main(int argc, char **argv) {
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);
    zpl_opts_add(&opts, "s", "string", "input string.", ZPL_OPTS_STRING);
    zpl_opts_positional_add(&opts, "string");
    zpl_b32 ok = zpl_opts_compile(&opts, argc, argv);
    if (!ok || !zpl_opts_positionals_filled(&opts))
        exit_with_help(&opts);

    zpl_string input = zpl_opts_string(&opts, "string", 0);
    zpl_u8 *encoded_str = zpl_base64_encode(zpl_heap(), cast(void*)input, zpl_string_length(input));
    zpl_printf("Original: %s\nEncoded: %s\n", input, encoded_str);

    zpl_mfree(encoded_str);
    zpl_opts_free(&opts);
    return 0;
}

void exit_with_help(zpl_opts *opts) {
    zpl_opts_print_errors(opts);
    zpl_opts_print_help(opts);
    zpl_exit(1);
}
