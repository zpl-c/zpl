/** @file file.c
@brief File handling
@defgroup fileio File handling

File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.

@{
*/

typedef zpl_u32 zpl_file_mode;

typedef enum zpl_file_mode_flag {
    ZPL_FILE_MODE_READ   = ZPL_BIT(0),
    ZPL_FILE_MODE_WRITE  = ZPL_BIT(1),
    ZPL_FILE_MODE_APPEND = ZPL_BIT(2),
    ZPL_FILE_MODE_RW     = ZPL_BIT(3),
    ZPL_FILE_MODES       = ZPL_FILE_MODE_READ | ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW,
} zpl_file_mode_flag;

// NOTE: Only used internally and for the file operations
typedef enum zpl_seek_whence_type {
    ZPL_SEEK_WHENCE_BEGIN   = 0,
    ZPL_SEEK_WHENCE_CURRENT = 1,
    ZPL_SEEK_WHENCE_END     = 2,
} zpl_seek_whence_type;

typedef enum zpl_file_error {
    ZPL_FILE_ERROR_NONE,
    ZPL_FILE_ERROR_INVALID,
    ZPL_FILE_ERROR_INVALID_FILENAME,
    ZPL_FILE_ERROR_EXISTS,
    ZPL_FILE_ERROR_NOT_EXISTS,
    ZPL_FILE_ERROR_PERMISSION,
    ZPL_FILE_ERROR_TRUNCATION_FAILURE,
    ZPL_FILE_ERROR_NOT_EMPTY,
    ZPL_FILE_ERROR_NAME_TOO_LONG,
    ZPL_FILE_ERROR_UNKNOWN,
} zpl_file_error;

typedef union zpl_file_descriptor {
    void *p;
    zpl_intptr i;
    zpl_uintptr u;
} zpl_file_descriptor;

typedef struct zpl_file_operations zpl_file_operations;

#define ZPL_FILE_OPEN_PROC(name) zpl_file_error name(zpl_file_descriptor *fd, zpl_file_operations *ops, zpl_file_mode mode, char const *filename)
#define ZPL_FILE_READ_AT_PROC(name) zpl_b32 name(zpl_file_descriptor fd, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read, zpl_b32 stop_at_newline)
#define ZPL_FILE_WRITE_AT_PROC(name) zpl_b32 name(zpl_file_descriptor fd, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written)
#define ZPL_FILE_SEEK_PROC(name) zpl_b32 name(zpl_file_descriptor fd, zpl_i64 offset, zpl_seek_whence_type whence, zpl_i64 *new_offset)
#define ZPL_FILE_CLOSE_PROC(name) void name(zpl_file_descriptor fd)

typedef ZPL_FILE_OPEN_PROC(zpl_file_open_proc);
typedef ZPL_FILE_READ_AT_PROC(zpl_file_read_proc);
typedef ZPL_FILE_WRITE_AT_PROC(zpl_file_write_proc);
typedef ZPL_FILE_SEEK_PROC(zpl_file_seek_proc);
typedef ZPL_FILE_CLOSE_PROC(zpl_file_close_proc);

struct zpl_file_operations {
    zpl_file_read_proc  *read_at;
    zpl_file_write_proc *write_at;
    zpl_file_seek_proc  *seek;
    zpl_file_close_proc *close;
};

extern zpl_file_operations const zpl_default_file_operations;

typedef zpl_u64 zpl_file_time;
typedef enum zpl_dir_type {
    ZPL_DIR_TYPE_FILE,
    ZPL_DIR_TYPE_FOLDER,
    ZPL_DIR_TYPE_UNKNOWN,
} zpl_dir_type;

struct zpl_dir_info;

typedef struct zpl_dir_entry {
    char const *filename;
    struct zpl_dir_info *dir_info;
    zpl_u8 type;
} zpl_dir_entry;

typedef struct zpl_dir_info {
    char const    *fullpath;
    zpl_dir_entry *entries; // zpl_array

    // Internals
    char **filenames; // zpl_array
    zpl_string buf;
} zpl_dir_info;

typedef struct zpl_file {
    zpl_file_operations ops;
    zpl_file_descriptor fd;

    char const    *filename;
    zpl_file_time last_write_time;
    zpl_dir_entry *dir;
} zpl_file;

typedef enum zpl_file_standard_type {
    ZPL_FILE_STANDARD_INPUT,
    ZPL_FILE_STANDARD_OUTPUT,
    ZPL_FILE_STANDARD_ERROR,

    ZPL_FILE_STANDARD_COUNT,
} zpl_file_standard_type;

/**
 * Get standard file I/O.
 * @param  std Check zpl_file_standard_type
 * @return     File handle to standard I/O
 */
ZPL_DEF zpl_file      *zpl_file_get_standard(zpl_file_standard_type std);

/**
 * Connects a system handle to a ZPL file.
 * @param  file   Pointer to ZPL file
 * @param  handle Low-level OS handle to connect
 */
ZPL_DEF void           zpl_file_connect_handle(zpl_file *file, void *handle);

/**
 * Creates a new file
 * @param  file
 * @param  filename
 */
ZPL_DEF zpl_file_error zpl_file_create(zpl_file *file, char const *filename);

/**
 * Opens a file
 * @param  file
 * @param  filename
 */
ZPL_DEF zpl_file_error zpl_file_open(zpl_file *file, char const *filename);

/**
 * Opens a file using a specified mode
 * @param  file
 * @param  mode     Access mode to use
 * @param  filename
 */
ZPL_DEF zpl_file_error zpl_file_open_mode(zpl_file *file, zpl_file_mode mode, char const *filename);

/**
 * Constructs a new file from data
 * @param  file
 * @param  fd       Low-level file descriptor to use
 * @param  ops      File operations to rely upon
 * @param  filename
 */
ZPL_DEF zpl_file_error zpl_file_new(zpl_file *file, zpl_file_descriptor fd, zpl_file_operations ops, char const *filename);

/**
 * Returns a size of the file
 * @param  file
 * @return      File size
 */
ZPL_DEF zpl_i64        zpl_file_size(zpl_file *file);

/**
 * Returns the currently opened file's name
 * @param  file
 */
ZPL_DEF char const    *zpl_file_name(zpl_file *file);

/**
 * Truncates the file by a specified size
 * @param  file
 * @param  size Size to truncate
 */
ZPL_DEF zpl_file_error zpl_file_truncate(zpl_file *file, zpl_i64 size);

/**
 * Checks whether a file's been changed since the last check
 * @param  file
 */
ZPL_DEF zpl_b32 zpl_file_has_changed(zpl_file *file);

/**
 * Retrieves a directory listing relative to the file
 * @param file
 */
ZPL_DEF void zpl_file_dirinfo_refresh(zpl_file *file);

/**
 * Creates a temporary file
 * @param  file
 */
zpl_file_error zpl_file_temp(zpl_file *file);

/**
 * Closes the file
 * @param  file
 */
ZPL_DEF zpl_file_error zpl_file_close(zpl_file *file);

/**
 * Reads file safely
 * @param  file
 * @param  buffer     Buffer to read to
 * @param  size       Size to read
 * @param  offset     Offset to read from
 * @param  bytes_read How much data we've actually read
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_read_at_check(zpl_file *file, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read);

/**
 * Writes to file safely
 * @param  file
 * @param  buffer        Buffer to read from
 * @param  size          Size to write
 * @param  offset        Offset to write to
 * @param  bytes_written How much data we've actually written
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_write_at_check(zpl_file *file, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written);


/**
 * Reads file at a specific offset
 * @param  file
 * @param  buffer     Buffer to read to
 * @param  size       Size to read
 * @param  offset     Offset to read from
 * @param  bytes_read How much data we've actually read
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_read_at(zpl_file *file, void *buffer, zpl_isize size, zpl_i64 offset);

/**
 * Writes to file at a specific offset
 * @param  file
 * @param  buffer        Buffer to read from
 * @param  size          Size to write
 * @param  offset        Offset to write to
 * @param  bytes_written How much data we've actually written
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_write_at(zpl_file *file, void const *buffer, zpl_isize size, zpl_i64 offset);

/**
 * Seeks the file cursor from the beginning of file to a specific position
 * @param  file
 * @param  offset Offset to seek to
 */
ZPL_DEF_INLINE zpl_i64 zpl_file_seek(zpl_file *file, zpl_i64 offset);

/**
 * Seeks the file cursor to the end of the file
 * @param  file
 */
ZPL_DEF_INLINE zpl_i64 zpl_file_seek_to_end(zpl_file *file);

/**
 * Skips N bytes at the current position
 * @param  file
 * @param  bytes Bytes to skip
 */
ZPL_DEF_INLINE zpl_i64 zpl_file_skip(zpl_file *file, zpl_i64 bytes); // NOTE: Skips a certain amount of bytes

/**
 * Returns the length from the beginning of the file we've read so far
 * @param  file
 * @return      Our current position in file
 */
ZPL_DEF_INLINE zpl_i64 zpl_file_tell(zpl_file *file);

/**
 * Reads from a file
 * @param  file
 * @param  buffer Buffer to read to
 * @param  size   Size to read
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_read(zpl_file *file, void *buffer, zpl_isize size);

/**
 * Writes to a file
 * @param  file
 * @param  buffer Buffer to read from
 * @param  size   Size to read
 */
ZPL_DEF_INLINE zpl_b32 zpl_file_write(zpl_file *file, void const *buffer, zpl_isize size);


typedef struct zpl_file_contents {
    zpl_allocator allocator;
    void *data;
    zpl_isize size;
} zpl_file_contents;

/**
 * Reads the whole file contents
 * @param  a              Allocator to use
 * @param  zero_terminate End the read data with null terminator
 * @param  filepath       Path to the file
 * @return                File contents data
 */
ZPL_DEF zpl_file_contents zpl_file_read_contents(zpl_allocator a, zpl_b32 zero_terminate, char const *filepath);

/**
 * Frees the file content data previously read
 * @param  fc
 */
ZPL_DEF void              zpl_file_free_contents(zpl_file_contents *fc);

/**
 * Reads the file as array of lines
 *
 * Make sure you free both the returned buffer and the lines (zpl_array)
 * @param  alloc            Allocator to use
 * @param  lines            Reference to zpl_array container we store lines to
 * @param  filename         Path to the file
 * @param  strip_whitespace Strip whitespace when we split to lines?
 * @return                  File content we've read itself
 */
ZPL_DEF char *zpl_file_read_lines(zpl_allocator alloc, zpl_array(char *)*lines, char const *filename, zpl_b32 strip_whitespace);

//! @}

/* inlines */


ZPL_INLINE zpl_b32 zpl_file_read_at_check(zpl_file *f, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read) {
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    return f->ops.read_at(f->fd, buffer, size, offset, bytes_read, false);
}

ZPL_INLINE zpl_b32 zpl_file_write_at_check(zpl_file *f, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written) {
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    return f->ops.write_at(f->fd, buffer, size, offset, bytes_written);
}

ZPL_INLINE zpl_b32 zpl_file_read_at(zpl_file *f, void *buffer, zpl_isize size, zpl_i64 offset) {
    return zpl_file_read_at_check(f, buffer, size, offset, NULL);
}

ZPL_INLINE zpl_b32 zpl_file_write_at(zpl_file *f, void const *buffer, zpl_isize size, zpl_i64 offset) {
    return zpl_file_write_at_check(f, buffer, size, offset, NULL);
}

ZPL_INLINE zpl_i64 zpl_file_seek(zpl_file *f, zpl_i64 offset) {
    zpl_i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, offset, ZPL_SEEK_WHENCE_BEGIN, &new_offset);
    return new_offset;
}

ZPL_INLINE zpl_i64 zpl_file_seek_to_end(zpl_file *f) {
    zpl_i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_END, &new_offset);
    return new_offset;
}

// NOTE: Skips a certain amount of bytes
ZPL_INLINE zpl_i64 zpl_file_skip(zpl_file *f, zpl_i64 bytes) {
    zpl_i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, bytes, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
    return new_offset;
}

ZPL_INLINE zpl_i64 zpl_file_tell(zpl_file *f) {
    zpl_i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
    return new_offset;
}

ZPL_INLINE zpl_b32 zpl_file_read(zpl_file *f, void *buffer, zpl_isize size) {
    zpl_i64 cur_offset = zpl_file_tell(f);
    zpl_b32 result = zpl_file_read_at(f, buffer, size, zpl_file_tell(f));
    zpl_file_seek(f, cur_offset + size);
    return result;
}

ZPL_INLINE zpl_b32 zpl_file_write(zpl_file *f, void const *buffer, zpl_isize size) {
    zpl_i64 cur_offset = zpl_file_tell(f);
    zpl_b32 result = zpl_file_write_at(f, buffer, size, zpl_file_tell(f));
    zpl_file_seek(f, cur_offset + size);
    return result;
}
