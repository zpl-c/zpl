#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

int main() {
    zpl_path_mkdir_recursive("build/foo/bar/baz/", 0755);
    return 0;
}
