// file: header/core/file_misc.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#ifndef ZPL_PATH_SEPARATOR
    #if defined(ZPL_SYSTEM_WINDOWS)
        #define ZPL_PATH_SEPARATOR '\\'
    #else
        #define ZPL_PATH_SEPARATOR '/'
    #endif
#endif

/**
 * Checks if file/directory exists
 * @param  filepath
 */
ZPL_DEF zpl_b32       zpl_fs_exists(char const *filepath);

/**
 * Retrieves node's type (file, folder, ...)
 * @param  path
 */
ZPL_DEF zpl_u8        zpl_fs_get_type(char const *path);

/**
 * Retrieves file's last write time
 * @param  filepath
 */
ZPL_DEF zpl_file_time zpl_fs_last_write_time(char const *filepath);

/**
 * Copies the file to a directory
 * @param  existing_filename
 * @param  new_filename
 * @param  fail_if_exists
 */
ZPL_DEF zpl_b32       zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists);

/**
 * Moves the file to a directory
 * @param  existing_filename
 * @param  new_filename
 */
ZPL_DEF zpl_b32       zpl_fs_move(char const *existing_filename, char const *new_filename);

/**
 * Removes a file from a directory
 * @param  filename
 */
ZPL_DEF zpl_b32       zpl_fs_remove(char const *filename);

ZPL_DEF_INLINE zpl_b32 zpl_path_is_absolute(char const *path);
ZPL_DEF_INLINE zpl_b32 zpl_path_is_relative(char const *path);
ZPL_DEF_INLINE zpl_b32 zpl_path_is_root(char const *path);

ZPL_DEF_INLINE char const *zpl_path_base_name(char const *path);
ZPL_DEF_INLINE char const *zpl_path_extension(char const *path);

ZPL_DEF void    zpl_path_fix_slashes(char *path);

ZPL_DEF zpl_file_error zpl_path_mkdir(char const *path, zpl_i32 mode);
ZPL_DEF zpl_isize zpl_path_mkdir_recursive(char const *path, zpl_i32 mode);
ZPL_DEF zpl_file_error zpl_path_rmdir(char const *path);

ZPL_DEF char       *zpl_path_get_full_name(zpl_allocator a, char const *path);

/**
 * Returns file paths terminated by newline (\n)
 * @param  alloc   [description]
 * @param  dirname [description]
 * @param  recurse [description]
 * @return         [description]
 */
ZPL_DEF /*zpl_string*/char * zpl_path_dirlist(zpl_allocator alloc, char const *dirname, zpl_b32 recurse);

/**
 * Initialize dirinfo from specified path
 * @param dir  [description]
 * @param path [description]
 */
ZPL_DEF void zpl_dirinfo_init(zpl_dir_info *dir, char const *path);
ZPL_DEF void zpl_dirinfo_free(zpl_dir_info *dir);

/**
 * Analyze the entry's dirinfo
 * @param dir_entry [description]
 */
ZPL_DEF void zpl_dirinfo_step(zpl_dir_entry *dir_entry);


/* inlines */

ZPL_IMPL_INLINE zpl_b32 zpl_path_is_absolute(char const *path) {
    zpl_b32 result = false;
    ZPL_ASSERT_NOT_NULL(path);
#if defined(ZPL_SYSTEM_WINDOWS)
    result = (zpl_strlen(path) > 2) && zpl_char_is_alpha(path[0]) && (path[1] == ':' && path[2] == ZPL_PATH_SEPARATOR);
#else
    result = (zpl_strlen(path) > 0 && path[0] == ZPL_PATH_SEPARATOR);
#endif
    return result;
}

ZPL_IMPL_INLINE zpl_b32 zpl_path_is_relative(char const *path) { return !zpl_path_is_absolute(path); }

ZPL_IMPL_INLINE zpl_b32 zpl_path_is_root(char const *path) {
    zpl_b32 result = false;
    ZPL_ASSERT_NOT_NULL(path);
#if defined(ZPL_SYSTEM_WINDOWS)
    result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 3);
#else
    result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 1);
#endif
    return result;
}

ZPL_IMPL_INLINE char const *zpl_path_base_name(char const *path) {
    char const *ls;
    ZPL_ASSERT_NOT_NULL(path);
    zpl_path_fix_slashes((char *)path);
    ls = zpl_char_last_occurence(path, ZPL_PATH_SEPARATOR);
    return (ls == NULL) ? path : ls + 1;
}

ZPL_IMPL_INLINE char const *zpl_path_extension(char const *path) {
    char const *ld;
    ZPL_ASSERT_NOT_NULL(path);
    ld = zpl_char_last_occurence(path, '.');
    return (ld == NULL) ? NULL : ld + 1;
}

ZPL_END_C_DECLS
