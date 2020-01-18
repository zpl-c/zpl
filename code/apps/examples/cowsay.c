#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#include "zpl.h"

#define BUF_LEN 4096

///////////////////////////////////////////////////////////////////////////////////
//
// This demo requires you to have the following packages: "fortune" and "cowsay".
// You should find these in your distro repositories, or 
// at source ports sites.
//


int main(void)
{
    char buf[BUF_LEN] = {0};
    zpl_string text = NULL;
    
    zpl_system_command("fortune | cowsay", BUF_LEN, buf);
    text = zpl_system_command_str("fortune | cowsay", zpl_heap());
    zpl_printf("Output:\n %s\n\n%s", buf, text);
    return 0;
}
