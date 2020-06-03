#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_REGEX
#include <zpl.h>

int main(void) {

    zpl_re re={0};

    char const* pat = "(//<<([\\w._]+)>>)";

    zpl_u32 err = zpl_re_compile(&re, zpl_heap(), pat, zpl_strlen(pat));
    if (err) {
        zpl_printf("Regex pattern is invalid! Error code: %d\n", err);
    }

    zpl_printf("Regex pattern was compiled!\n");

    char const* str = "//<<buffer.c>> aaa //<<hello.c>>\n  aa//<<aaa.c>>//<<test.c>>";

    zpl_array_make(zpl_re_capture, captures, zpl_heap());

    zpl_re_match_all(&re, str, zpl_strlen(str), 2, &captures);

    for (zpl_isize i=0; i < zpl_array_count(captures); i++)
    {
        zpl_printf("Group %ld: %.*s\n", i, (zpl_i32)captures[i].len, captures[i].str);
    }

    return 0;
}
