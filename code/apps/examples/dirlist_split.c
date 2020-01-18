#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#include <zpl.h>

int main()
{
    zpl_string filelst;
    filelst = zpl_path_dirlist(zpl_heap_allocator(), "$HOME/", true);
    
    char **files=zpl_str_split_lines(zpl_heap_allocator(), filelst, false);
    
    for (i32 i=0; i<zpl_array_count(files); ++i) {
        printf("%s\n", files[i]);
    }
    
    zpl_string_free(filelst);
    zpl_array_free(files);
    
    return 0;
}
