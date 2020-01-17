//
// Recommends presence of jeopardy.json file, which can be received at: https://www.reddit.com/r/datasets/comments/1uyd0t/200000_jeopardy_questions_in_a_json_file/
//
// Stats on i7-4790k with jeopardy.json file
//   Parsing - ~160 ms
//   Parsing with strip_comments enabled - ~255 ms
//
#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(int argc, char **argv) {
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);

    zpl_opts_add(&opts, "f", "file", "input file name.", ZPL_OPTS_STRING);
    zpl_opts_add(&opts, "s", "strip-comments", "strip comments from JSON file (recommended).", ZPL_OPTS_FLAG);

    zpl_opts_positional_add(&opts, "file");

    b32 ok = zpl_opts_compile(&opts, argc, argv);

    char *filename = NULL;
    b32 strip_comments = false;

    if (ok && zpl_opts_positionals_filled(&opts))
    {
        filename = zpl_opts_string(&opts, "file", NULL);
        strip_comments = zpl_opts_has_arg(&opts, "strip-comments");

        if (filename == NULL)
            goto bad;

        printf("Filename: %s\n", filename);
    }
    else
    {
        bad:
        zpl_opts_print_errors(&opts);
        zpl_opts_print_help(&opts);
        return -1;
    }

    zpl_file_contents fc = zpl_file_read_contents(zpl_heap(), true, filename);

    printf("Parsing JSON5 file!\n");

    zpl_json_object root = {0};

    u8 err;
    f64 time = zpl_time_now();
    zpl_json_parse(&root, fc.size, (char *)fc.data, zpl_heap(), strip_comments, &err);
    f64 delta = zpl_time_now() - time;

    if (err == ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL)
    {
        printf("File not found!\n");
        return -2;
    }

    printf("Delta: %fms\nNo. of nodes: %td\nError code: %d\nFile size: %td bytes\n", delta*1000, zpl_array_count(root.nodes), err, fc.size);

    zpl_json_free(&root);
    zpl_file_free_contents(&fc);
    
    return 0;
}
