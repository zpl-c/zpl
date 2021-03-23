#define ZPL_IMPL
#define ZPL_NANO
#include <zpl.h>

zpl_isize print_files(zpl_file *archive, zpl_tar_record *file, void* user_data) {
    (void)archive;
    (void)user_data;
    if (file->error != ZPL_TAR_ERROR_NONE)
        return 0; /* skip file */

    if (file->type != ZPL_TAR_TYPE_REGULAR)
        return 0; /* we only care about regular files */

    if (!zpl_strcmp(file->path, "file_i_expect.txt")) {
        /* we found our requested file, cancel further unpacking */
        zpl_printf("file i required was found! %s\n", file->path);
        return 1;
    }

    /* proceed as usual */
    zpl_printf("name: %s, off: %d, len: %d\n", file->path, file->offset, file->length);
    return 0;
}

int main() {
    char const *paths[] = {"misc/data/glsl_diffuse.json5", "misc/data/test.json5", "misc/data/bg.png"};
    zpl_file a;
    zpl_file_create(&a, "build/test_archive_zpl.tar");
    zpl_tar_pack(&a, paths, 3);
    zpl_file_close(&a);

    zpl_file b;
    zpl_file_open(&b, "misc/data/test_archive.tar");
    zpl_tar_unpack(&b, zpl_tar_default_list_file, 0);
    zpl_file_seek(&b, 0);
    zpl_tar_unpack(&b, print_files, 0);
    zpl_file_seek(&b, 0);
    zpl_tar_unpack(&b, zpl_tar_default_unpack_file, "build");
    zpl_file_close(&b);
    return 0;
}
