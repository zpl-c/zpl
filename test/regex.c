#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(void) {

    zpl_re re={0};

    char *pat = "(//<<([\\w._]+)>>)";

    u32 err = zpl_re_compile(&re, zpl_heap(), pat, zpl_strlen(pat));
    if (err) {
        zpl_printf("Regex pattern is invalid! Error code: %d\n", err);
    }

    zpl_printf("Regex pattern was compiled!\n");

    zpl_re_capture cps[2] = {0};
    char *str = "//<<buffer.c>> aaa //<<hello.c>>\n  aa//<<aaa.c>>//<<test.c>>";
    isize str_len = zpl_strlen(str);
    char *end = str + str_len;
    char *p = str;

    isize offset = 0;
    
    while (p < end)
    {
        b32 ok = zpl_re_match(&re, p, end - p, cps, 2, &offset);
        if (!ok) break;
        p += offset;

        zpl_printf("Matched? %s! Offset: %d, String Length: %d\n", ok ? "Yes" : "No", offset, str_len);

        for (isize i = 0; i < re.capture_count; i++)
        {
            zpl_printf("Group %lld: %.*s\n", i, cps[i].len, cps[i].str);
        }
    }

    return 0;
}
