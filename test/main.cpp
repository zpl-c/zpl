#define ZPL_IMPL
//#define ZPL_NANO
//#define ZPL_DISABLE_THREADING
#include "zpl.h"

int main(int argc, char const *argv[]) {
    char buffer[256] = {0};
    zpl_memcopy(buffer, "hello world\0", 10);

    printf("%s\n", buffer);

    return 0;
}
