#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(void) {

    zpl_re re={0};

    char *pat = "(//<<([\\w._]+)>>)";

    zpl_re_compile(&re, zpl_heap(), pat, zpl_strlen(pat));

    zpl_printf("Regex pattern was compiled!\n");

    zpl_re_capture cps[64] = {0};
    char *str = "//<<buffer.c>>\n//<<hello.c>>\n";

    zpl_re_match(&re, str, zpl_strlen(str), cps, 64);

    for (isize i = 0; i < re.capture_count; i++)
    {
        zpl_printf("Group %lld: %.*s\n", i, cps[i].len, cps[i].str);
    }

    return 0;
}
