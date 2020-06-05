#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

#define FILENAME "build/dump.txt"
#define CONTENT "Hello World!"

int main() {
    zpl_file_contents fcont;
    zpl_file_error err;
    zpl_file_write_contents(FILENAME, zpl_str_expand(CONTENT), &err);
    fcont = zpl_file_read_contents(zpl_heap(), true, FILENAME);

    zpl_printf("err: %d\nstr: %s\n", cast(zpl_u32)err, cast(char const*)fcont.data);

    zpl_file_free_contents(&fcont);
    return 0;
}
