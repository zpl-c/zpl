#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#include <zpl.h>

int main()
{
    char const* foo = "hello world";

    //NOTE: length of a string + 1 extra byte for null terminator.
    zpl_isize len = strlen(foo) + 1;

    char *bar = zpl_strdup(zpl_heap(), (char *)foo, len);
    zpl_printf("%s == %s\n", foo, bar);
    return 0;
}

