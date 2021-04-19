/* sample files taken from: https://people.sc.fsu.edu/~jburkardt/data/csv/csv.html */

#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_PARSER
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/cities.csv");

    zpl_csv_object root = {0};

    zpl_u8 err;
    err = zpl_csv_parse(&root, (char *)fc.data, zpl_heap_allocator(), true);

    zpl_printf("Error code: %d\n", err);
    zpl_printf("columns: %d, rows: %d\n", zpl_array_count(root.nodes), zpl_array_count(root.nodes[0].nodes));

    zpl_printf("\njson output:\n");
    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);

    zpl_printf("\ncsv output:\n");
    zpl_csv_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root);

    zpl_csv_free(&root);
    zpl_file_free_contents(&fc);
    return 0;
}
