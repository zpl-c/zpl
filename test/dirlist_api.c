#define ZPL_IMPLEMENTATION
#include <zpl.h>

char *get_type(u8 type) {
    switch (type) {
        case ZPL_DIR_TYPE_FILE:
            return "file";
        case ZPL_DIR_TYPE_FOLDER:
            return "folder";

        default:
            return "unknown";
    }
}

int main() {
    zpl_dir_info test={0};
    zpl_dirinfo_init(&test, "misc");

    for (int i=0; i<zpl_array_count(test.entries); ++i) {
        zpl_dir_entry *e = test.entries + i;
        printf("entry [%s]: %s\n", get_type(e->type), e->filename);

        if (e->type != ZPL_DIR_TYPE_FOLDER) continue;

        zpl_dirinfo_step(e);

        if (e->dir_info) {
            for (int j=0; j<zpl_array_count(e->dir_info->entries); ++j) {
                printf("-- subentry [%s]: %s\n", get_type(e->dir_info->entries[j].type), e->dir_info->entries[j].filename);
            }
        }
    }

    zpl_dirinfo_free(&test);
    printf("Done!\n");

    zpl_file foo = {0};
    zpl_file_open(&foo, "code/zpl.h");
    zpl_file_dirinfo_refresh(&foo);
    if (foo.dir) {
        for (int j=0; j<zpl_array_count(foo.dir->dir_info->entries); ++j) {
            printf("-- file entry: %s\n", foo.dir->dir_info->entries[j].filename);
        }
    }
    zpl_file_close(&foo);

    return 0;
}
