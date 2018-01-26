
#define ZPL_IMPLEMENTATION
#include "zpl.h"

#define BUF_LEN 4096

int
main(void) {
    
    char buf[BUF_LEN] = {0};
    
    zpl_system_command("dir", BUF_LEN, buf);
    zpl_printf("Output: %s\n", buf);
    return 0;
}
