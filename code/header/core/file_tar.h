// file: header/core/file_tar.h

/** @file file_tar.c
@brief Tar archiving module
@defgroup fileio Tar module

Allows to easily pack/unpack files.
Based on: https://github.com/rxi/microtar/

Disclaimer: The pack method does not support file permissions nor GID/UID information. Only regular files are supported.
It is not possible to pack a folder, please refer to "zpl_dir_info" or "zpl_path_dirlist" to collect a file list.
Empty folders are ignored.

@{
*/

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef enum {
    ZPL_TAR_ERROR_NONE,
    ZPL_TAR_ERROR_INTERRUPTED,
    ZPL_TAR_ERROR_IO_ERROR,
    ZPL_TAR_ERROR_BAD_CHECKSUM,
    ZPL_TAR_ERROR_FILE_NOT_FOUND,
    ZPL_TAR_ERROR_INVALID_INPUT,
} zpl_tar_errors;

typedef enum {
    ZPL_TAR_TYPE_REGULAR    = '0',
    ZPL_TAR_TYPE_LINK       = '1',
    ZPL_TAR_TYPE_SYMBOL     = '2',
    ZPL_TAR_TYPE_CHR        = '3',
    ZPL_TAR_TYPE_BLK        = '4',
    ZPL_TAR_TYPE_DIR        = '5',
    ZPL_TAR_TYPE_FIFO       = '6'
} zpl_tar_file_type;

typedef struct {
    char type;
    char *path;
    zpl_i64 offset;
    zpl_i64 length;
    zpl_isize error;
} zpl_tar_record;

#define ZPL_TAR_UNPACK_PROC(name) zpl_isize name(zpl_file *archive, zpl_tar_record *file, void* user_data)
typedef ZPL_TAR_UNPACK_PROC(zpl_tar_unpack_proc);

/**
 * @brief Packs a list of files
 * Packs a list of provided files. Note that this method only supports regular files
 * and does not provide extended info such as GID/UID or permissions.
 * @param archive file we pack files into
 * @param paths list of files
 * @param paths_len number of files provided
 * @return error
 */
ZPL_DEF zpl_isize zpl_tar_pack(zpl_file *archive, char const **paths, zpl_isize paths_len);

/**
 * @brief Unpacks an existing archive
 * Unpacks an existing archive. Users provide a callback in which information about file is provided.
 * Library does not unpack files to the filesystem nor reads any file data.
 * @param archive archive we unpack files from
 * @param unpack_proc callback we call per each file parsed
 * @param user_data user provided data
 * @return error
 */
ZPL_DEF zpl_isize zpl_tar_unpack(zpl_file *archive, zpl_tar_unpack_proc *unpack_proc, void* user_data);

ZPL_DEF ZPL_TAR_UNPACK_PROC(zpl_tar_default_list_file);

//! @}

ZPL_END_C_DECLS
