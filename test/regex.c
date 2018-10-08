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
    
    char *str = "//<<buffer.c>> aaa //<<hello.c>>\n  aa//<<aaa.c>>//<<test.c>>";
    
    zpl_array_make(zpl_re_capture, captures, zpl_heap());
    
    b32 ok = zpl_re_match_all(&re, str, zpl_strlen(str), 2, &captures); 
    
    for (isize i=0; i < zpl_array_count(captures); i++)
    {
        zpl_printf("Group %lld: %.*s\n", i, (i32)captures[i].len, captures[i].str);
    }
    
    return 0;
}
