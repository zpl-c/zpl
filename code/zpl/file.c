/** @file file.c
@brief File handling
@defgroup fileio File handling

File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.

@{
*/

typedef u32 zpl_file_mode;
typedef enum zplFileModeFlag {
    ZPL_FILE_MODE_READ = ZPL_BIT(0),
    ZPL_FILE_MODE_WRITE = ZPL_BIT(1),
    ZPL_FILE_MODE_APPEND = ZPL_BIT(2),
    ZPL_FILE_MODE_RW = ZPL_BIT(3),
    
    zpl_file_mode_modes_ev = ZPL_FILE_MODE_READ | ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW,
} zplFileModeFlag;

// NOTE: Only used internally and for the file operations
typedef enum zplSeekWhenceType {
    ZPL_SEEK_WHENCE_BEGIN = 0,
    ZPL_SEEK_WHENCE_CURRENT = 1,
    ZPL_SEEK_WHENCE_END = 2,
} zplSeekWhenceType;

typedef enum zplFileError {
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
} zplFileError;

#define zpl_file_descriptor_t zpl_file_descriptor
typedef union zpl_file_descriptor {
    void *p;
    intptr i;
    uintptr u;
} zpl_file_descriptor;

#define zpl_file_operations_t zpl_file_operations
typedef struct zpl_file_operations zpl_file_operations;

#define ZPL_FILE_OPEN_PROC(name)                                                                                       \
zplFileError name(zpl_file_descriptor *fd, zpl_file_operations *ops, zpl_file_mode mode, char const *filename)
#define ZPL_FILE_READ_AT_PROC(name)                                                                                    \
b32 name(zpl_file_descriptor fd, void *buffer, isize size, i64 offset, isize *bytes_read, b32 stop_at_newline)
#define ZPL_FILE_WRITE_AT_PROC(name)                                                                                   \
b32 name(zpl_file_descriptor fd, void const *buffer, isize size, i64 offset, isize *bytes_written)
#define ZPL_FILE_SEEK_PROC(name) b32 name(zpl_file_descriptor fd, i64 offset, zplSeekWhenceType whence, i64 *new_offset)
#define ZPL_FILE_CLOSE_PROC(name) void name(zpl_file_descriptor fd)
typedef ZPL_FILE_OPEN_PROC(zpl_file_open_proc);
typedef ZPL_FILE_READ_AT_PROC(zpl_file_read_proc);
typedef ZPL_FILE_WRITE_AT_PROC(zpl_file_write_proc);
typedef ZPL_FILE_SEEK_PROC(zpl_file_seek_proc);
typedef ZPL_FILE_CLOSE_PROC(zpl_file_close_proc);

struct zpl_file_operations {
    zpl_file_read_proc *read_at;
    zpl_file_write_proc *write_at;
    zpl_file_seek_proc *seek;
    zpl_file_close_proc *close;
};

extern zpl_file_operations const zpl_default_file_operations;

// typedef struct zpl_dir_info {
//  u8 *buf;
//  isize buf_count;
//  isize buf_pos;
// } zpl_dir_info;

typedef u64 zpl_file_time;

#define zpl_file_t zpl_file
typedef struct zpl_file {
    zpl_file_operations ops;
    zpl_file_descriptor fd;
    char const *filename;
    zpl_file_time last_write_time;
    // zpl_dir_info *   dir_info; // TODO: Get directory info
} zpl_file;

#ifdef ZPL_THREADING

#define zpl_async_file_t zpl_async_file
typedef struct zpl_async_file {
    zpl_file handle;
    isize size;
    void *data;
} zpl_async_file;

#define ZPL_ASYNC_FILE_CB(name) void name(zpl_async_file *file)
typedef ZPL_ASYNC_FILE_CB(zpl_async_file_cb);

#endif // ZPL_THREADING

typedef enum zplFileStandardType {
    ZPL_FILE_STANDARD_INPUT,
    ZPL_FILE_STANDARD_OUTPUT,
    ZPL_FILE_STANDARD_ERROR,
    
    ZPL_FILE_STANDARD_COUNT,
} zplFileStandardType;

ZPL_DEF zpl_file *zpl_file_get_standard(zplFileStandardType std);

ZPL_DEF zplFileError zpl_file_create(zpl_file *file, char const *filename);
ZPL_DEF zplFileError zpl_file_open(zpl_file *file, char const *filename);
ZPL_DEF zplFileError zpl_file_open_mode(zpl_file *file, zpl_file_mode mode, char const *filename);
ZPL_DEF zplFileError zpl_file_new(zpl_file *file, zpl_file_descriptor fd, zpl_file_operations ops,
                                  char const *filename);
ZPL_DEF b32 zpl_file_read_at_check(zpl_file *file, void *buffer, isize size, i64 offset, isize *bytes_read);
ZPL_DEF b32 zpl_file_write_at_check(zpl_file *file, void const *buffer, isize size, i64 offset, isize *bytes_written);
ZPL_DEF b32 zpl_file_read_at(zpl_file *file, void *buffer, isize size, i64 offset);
ZPL_DEF b32 zpl_file_write_at(zpl_file *file, void const *buffer, isize size, i64 offset);
ZPL_DEF i64 zpl_file_seek(zpl_file *file, i64 offset);
ZPL_DEF i64 zpl_file_seek_to_end(zpl_file *file);
ZPL_DEF i64 zpl_file_skip(zpl_file *file, i64 bytes); // NOTE: Skips a certain amount of bytes
ZPL_DEF i64 zpl_file_tell(zpl_file *file);
ZPL_DEF zplFileError zpl_file_close(zpl_file *file);
ZPL_DEF b32 zpl_file_read(zpl_file *file, void *buffer, isize size);
ZPL_DEF b32 zpl_file_write(zpl_file *file, void const *buffer, isize size);
ZPL_DEF i64 zpl_file_size(zpl_file *file);
ZPL_DEF char const *zpl_file_name(zpl_file *file);
ZPL_DEF zplFileError zpl_file_truncate(zpl_file *file, i64 size);
ZPL_DEF b32 zpl_file_has_changed(zpl_file *file); // NOTE: Changed since lasted checked

#ifdef ZPL_THREADING
ZPL_DEF void zpl_async_file_read(zpl_file *file, zpl_async_file_cb *proc);
ZPL_DEF void zpl_async_file_write(zpl_file *file, void const *buffer, isize size, zpl_async_file_cb *proc);
#endif

zplFileError zpl_file_temp(zpl_file *file);

#define zpl_file_contents_t zpl_file_contents
typedef struct zpl_file_contents {
    zpl_allocator allocator;
    void *data;
    isize size;
} zpl_file_contents;

ZPL_DEF zpl_file_contents zpl_file_read_contents(zpl_allocator a, b32 zero_terminate, char const *filepath);
ZPL_DEF void zpl_file_free_contents(zpl_file_contents *fc);

// NOTE: Make sure you free both the returned buffer and the lines (zpl_array)
ZPL_DEF char *zpl_file_read_lines(zpl_allocator alloc, zpl_array(char *) * lines, char const *filename,
                                  b32 strip_whitespace);

// TODO: Should these have different names as they do not take in a zpl_file * ???
ZPL_DEF b32 zpl_file_exists(char const *filepath);
ZPL_DEF zpl_file_time zpl_file_last_write_time(char const *filepath);
ZPL_DEF b32 zpl_file_copy(char const *existing_filename, char const *new_filename, b32 fail_if_exists);
ZPL_DEF b32 zpl_file_move(char const *existing_filename, char const *new_filename);
ZPL_DEF b32 zpl_file_remove(char const *filename);

#ifndef ZPL_PATH_SEPARATOR
#if defined(ZPL_SYSTEM_WINDOWS)
#define ZPL_PATH_SEPARATOR '\\'
#else
#define ZPL_PATH_SEPARATOR '/'
#endif
#endif

ZPL_DEF b32 zpl_path_is_absolute(char const *path);
ZPL_DEF b32 zpl_path_is_relative(char const *path);
ZPL_DEF b32 zpl_path_is_root(char const *path);
ZPL_DEF char const *zpl_path_base_name(char const *path);
ZPL_DEF char const *zpl_path_extension(char const *path);
ZPL_DEF char *zpl_path_get_full_name(zpl_allocator a, char const *path);

ZPL_DEF zplFileError zpl_path_mkdir(char const *path, i32 mode);
ZPL_DEF zplFileError zpl_path_rmdir(char const *path);

// NOTE: Returns file paths terminated by newline (\n)
zpl_string zpl_path_dirlist(zpl_allocator alloc, char const *dirname, b32 recurse);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// File Handling
//
//

#if defined(ZPL_SYSTEM_WINDOWS)

zpl_internal wchar_t *zpl__alloc_utf8_to_ucs2(zpl_allocator a, char const *text, isize *w_len_) {
    wchar_t *w_text = NULL;
    isize len = 0, w_len = 0, w_len1 = 0;
    if (text == NULL) {
        if (w_len_) *w_len_ = w_len;
        return NULL;
    }
    len = zpl_strlen(text);
    if (len == 0) {
        if (w_len_) *w_len_ = w_len;
        return NULL;
    }
    w_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, cast(int) len, NULL, 0);
    if (w_len == 0) {
        if (w_len_) *w_len_ = w_len;
        return NULL;
    }
    w_text = zpl_alloc_array(a, wchar_t, w_len + 1);
    w_len1 = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, cast(int) len, w_text, cast(int) w_len);
    if (w_len1 == 0) {
        zpl_free(a, w_text);
        if (w_len_) *w_len_ = 0;
        return NULL;
    }
    w_text[w_len] = 0;
    if (w_len_) *w_len_ = w_len;
    return w_text;
}

zpl_internal ZPL_FILE_SEEK_PROC(zpl__win32_file_seek) {
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = offset;
    if (!SetFilePointerEx(fd.p, li_offset, &li_offset, whence)) { return false; }
    
    if (new_offset) *new_offset = li_offset.QuadPart;
    return true;
}

zpl_internal ZPL_FILE_READ_AT_PROC(zpl__win32_file_read) {
    zpl_unused(stop_at_newline);
    b32 result = false;
    zpl__win32_file_seek(fd, offset, ZPL_SEEK_WHENCE_BEGIN, NULL);
    DWORD size_ = cast(DWORD)(size > I32_MAX ? I32_MAX : size);
    DWORD bytes_read_;
    if (ReadFile(fd.p, buffer, size_, &bytes_read_, NULL)) {
        if (bytes_read) *bytes_read = bytes_read_;
        result = true;
    }
    
    return result;
}

zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__win32_file_write) {
    DWORD size_ = cast(DWORD)(size > I32_MAX ? I32_MAX : size);
    DWORD bytes_written_;
    zpl__win32_file_seek(fd, offset, ZPL_SEEK_WHENCE_BEGIN, NULL);
    if (WriteFile(fd.p, buffer, size_, &bytes_written_, NULL)) {
        if (bytes_written) *bytes_written = bytes_written_;
        return true;
    }
    return false;
}

zpl_internal ZPL_FILE_CLOSE_PROC(zpl__win32_file_close) { CloseHandle(fd.p); }

zpl_file_operations const zpl_default_file_operations = { zpl__win32_file_read, zpl__win32_file_write,
    zpl__win32_file_seek, zpl__win32_file_close };

zpl_no_inline ZPL_FILE_OPEN_PROC(zpl__win32_file_open) {
    DWORD desired_access;
    DWORD creation_disposition;
    void *handle;
    wchar_t *w_text;
    
    switch (mode & zpl_file_mode_modes_ev) {
        case ZPL_FILE_MODE_READ:
        desired_access = GENERIC_READ;
        creation_disposition = OPEN_EXISTING;
        break;
        case ZPL_FILE_MODE_WRITE:
        desired_access = GENERIC_WRITE;
        creation_disposition = CREATE_ALWAYS;
        break;
        case ZPL_FILE_MODE_APPEND:
        desired_access = GENERIC_WRITE;
        creation_disposition = OPEN_ALWAYS;
        break;
        case ZPL_FILE_MODE_READ | ZPL_FILE_MODE_RW:
        desired_access = GENERIC_READ | GENERIC_WRITE;
        creation_disposition = OPEN_EXISTING;
        break;
        case ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW:
        desired_access = GENERIC_READ | GENERIC_WRITE;
        creation_disposition = CREATE_ALWAYS;
        break;
        case ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW:
        desired_access = GENERIC_READ | GENERIC_WRITE;
        creation_disposition = OPEN_ALWAYS;
        break;
        default: ZPL_PANIC("Invalid file mode"); return ZPL_FILE_ERROR_INVALID;
    }
    
    w_text = zpl__alloc_utf8_to_ucs2(zpl_heap_allocator( ), filename, NULL);
    handle = CreateFileW(w_text, desired_access, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, creation_disposition,
                         FILE_ATTRIBUTE_NORMAL, NULL);
    
    zpl_free(zpl_heap_allocator( ), w_text);
    
    if (handle == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError( );
        switch (err) {
            case ERROR_FILE_NOT_FOUND: return ZPL_FILE_ERROR_NOT_EXISTS;
            case ERROR_FILE_EXISTS: return ZPL_FILE_ERROR_EXISTS;
            case ERROR_ALREADY_EXISTS: return ZPL_FILE_ERROR_EXISTS;
            case ERROR_ACCESS_DENIED: return ZPL_FILE_ERROR_PERMISSION;
        }
        return ZPL_FILE_ERROR_INVALID;
    }
    
    if (mode & ZPL_FILE_MODE_APPEND) {
        LARGE_INTEGER offset = { 0 };
        if (!SetFilePointerEx(handle, offset, NULL, ZPL_SEEK_WHENCE_END)) {
            CloseHandle(handle);
            return ZPL_FILE_ERROR_INVALID;
        }
    }
    
    fd->p = handle;
    *ops = zpl_default_file_operations;
    return ZPL_FILE_ERROR_NONE;
}

#else // POSIX
zpl_internal ZPL_FILE_SEEK_PROC(zpl__posix_file_seek) {
#if defined(ZPL_SYSTEM_OSX)
    i64 res = lseek(fd.i, offset, whence);
#else // TODO(ZaKlaus): @fixme lseek64
    i64 res = lseek(fd.i, offset, whence);
#endif
    if (res < 0) return false;
    if (new_offset) *new_offset = res;
    return true;
}

zpl_internal ZPL_FILE_READ_AT_PROC(zpl__posix_file_read) {
    zpl_unused(stop_at_newline);
    isize res = pread(fd.i, buffer, size, offset);
    if (res < 0) return false;
    if (bytes_read) *bytes_read = res;
    return true;
}

zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__posix_file_write) {
    isize res;
    i64 curr_offset = 0;
    zpl__posix_file_seek(fd, 0, ZPL_SEEK_WHENCE_CURRENT, &curr_offset);
    if (curr_offset == offset) {
        // NOTE: Writing to stdout et al. doesn't like pwrite for numerous reasons
        res = write(cast(int) fd.i, buffer, size);
    } else {
        res = pwrite(cast(int) fd.i, buffer, size, offset);
    }
    if (res < 0) return false;
    if (bytes_written) *bytes_written = res;
    return true;
}

zpl_internal ZPL_FILE_CLOSE_PROC(zpl__posix_file_close) { close(fd.i); }

zpl_file_operations const zpl_default_file_operations = { zpl__posix_file_read, zpl__posix_file_write,
    zpl__posix_file_seek, zpl__posix_file_close };

zpl_no_inline ZPL_FILE_OPEN_PROC(zpl__posix_file_open) {
    i32 os_mode;
    switch (mode & zpl_file_mode_modes_ev) {
        case ZPL_FILE_MODE_READ: os_mode = O_RDONLY; break;
        case ZPL_FILE_MODE_WRITE: os_mode = O_WRONLY | O_CREAT | O_TRUNC; break;
        case ZPL_FILE_MODE_APPEND: os_mode = O_WRONLY | O_APPEND | O_CREAT; break;
        case ZPL_FILE_MODE_READ | ZPL_FILE_MODE_RW: os_mode = O_RDWR; break;
        case ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW: os_mode = O_RDWR | O_CREAT | O_TRUNC; break;
        case ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW: os_mode = O_RDWR | O_APPEND | O_CREAT; break;
        default: ZPL_PANIC("Invalid file mode"); return ZPL_FILE_ERROR_INVALID;
    }
    
    fd->i = open(filename, os_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd->i < 0) {
        // TODO: More file errors
        return ZPL_FILE_ERROR_INVALID;
    }
    
    *ops = zpl_default_file_operations;
    return ZPL_FILE_ERROR_NONE;
}

#endif

zplFileError zpl_file_new(zpl_file *f, zpl_file_descriptor fd, zpl_file_operations ops, char const *filename) {
    zplFileError err = ZPL_FILE_ERROR_NONE;
    isize len = zpl_strlen(filename);
    
    f->ops = ops;
    f->fd = fd;
    f->filename = zpl_alloc_array(zpl_heap_allocator( ), char, len + 1);
    zpl_memcopy(cast(char *) f->filename, cast(char *) filename, len + 1);
    f->last_write_time = zpl_file_last_write_time(f->filename);
    
    return err;
}

zplFileError zpl_file_open_mode(zpl_file *f, zpl_file_mode mode, char const *filename) {
    zplFileError err;
#if defined(ZPL_SYSTEM_WINDOWS)
    err = zpl__win32_file_open(&f->fd, &f->ops, mode, filename);
#else
    err = zpl__posix_file_open(&f->fd, &f->ops, mode, filename);
#endif
    if (err == ZPL_FILE_ERROR_NONE) return zpl_file_new(f, f->fd, f->ops, filename);
    return err;
}

zplFileError zpl_file_close(zpl_file *f) {
    if (!f) return ZPL_FILE_ERROR_INVALID;
    
    if (f->filename) zpl_free(zpl_heap_allocator( ), cast(char *) f->filename);
    
#if defined(ZPL_SYSTEM_WINDOWS)
    if (f->fd.p == INVALID_HANDLE_VALUE) return ZPL_FILE_ERROR_INVALID;
#else
    if (f->fd.i < 0) return ZPL_FILE_ERROR_INVALID;
#endif
    
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.close(f->fd);
    
    return ZPL_FILE_ERROR_NONE;
}

zpl_inline b32 zpl_file_read_at_check(zpl_file *f, void *buffer, isize size, i64 offset, isize *bytes_read) {
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    return f->ops.read_at(f->fd, buffer, size, offset, bytes_read, false);
}

zpl_inline b32 zpl_file_write_at_check(zpl_file *f, void const *buffer, isize size, i64 offset, isize *bytes_written) {
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    return f->ops.write_at(f->fd, buffer, size, offset, bytes_written);
}

zpl_inline b32 zpl_file_read_at(zpl_file *f, void *buffer, isize size, i64 offset) {
    return zpl_file_read_at_check(f, buffer, size, offset, NULL);
}

zpl_inline b32 zpl_file_write_at(zpl_file *f, void const *buffer, isize size, i64 offset) {
    return zpl_file_write_at_check(f, buffer, size, offset, NULL);
}

zpl_inline i64 zpl_file_seek(zpl_file *f, i64 offset) {
    i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, offset, ZPL_SEEK_WHENCE_BEGIN, &new_offset);
    return new_offset;
}

zpl_inline i64 zpl_file_seek_to_end(zpl_file *f) {
    i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_END, &new_offset);
    return new_offset;
}

// NOTE: Skips a certain amount of bytes
zpl_inline i64 zpl_file_skip(zpl_file *f, i64 bytes) {
    i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, bytes, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
    return new_offset;
}

zpl_inline i64 zpl_file_tell(zpl_file *f) {
    i64 new_offset = 0;
    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
    return new_offset;
}

zpl_inline b32 zpl_file_read(zpl_file *f, void *buffer, isize size) {
    i64 cur_offset = zpl_file_tell(f);
    b32 result = zpl_file_read_at(f, buffer, size, zpl_file_tell(f));
    zpl_file_seek(f, cur_offset + size);
    return result;
}

zpl_inline b32 zpl_file_write(zpl_file *f, void const *buffer, isize size) {
    i64 cur_offset = zpl_file_tell(f);
    b32 result = zpl_file_write_at(f, buffer, size, zpl_file_tell(f));
    zpl_file_seek(f, cur_offset + size);
    return result;
}

zplFileError zpl_file_create(zpl_file *f, char const *filename) {
    return zpl_file_open_mode(f, ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW, filename);
}

zplFileError zpl_file_open(zpl_file *f, char const *filename) {
    return zpl_file_open_mode(f, ZPL_FILE_MODE_READ, filename);
}

char const *zpl_file_name(zpl_file *f) { return f->filename ? f->filename : ""; }

zpl_inline b32 zpl_file_has_changed(zpl_file *f) {
    b32 result = false;
    zpl_file_time last_write_time = zpl_file_last_write_time(f->filename);
    if (f->last_write_time != last_write_time) {
        result = true;
        f->last_write_time = last_write_time;
    }
    return result;
}

#ifdef ZPL_THREADING

typedef struct {
    zpl_async_file *f;
    zpl_async_file_cb *proc;
    void *data;
    isize data_size;
} zpl__async_file_ctl;

ZPL_THREAD_PROC(zpl__async_file_read_proc) {
    zpl__async_file_ctl *afops = cast(zpl__async_file_ctl *) thread->user_data;
    
    zpl_async_file *f = afops->f;
    
    i64 file_size = zpl_file_size(&f->handle);
    void *file_contents = zpl_malloc((isize)file_size);
    zpl_file_read(&f->handle, file_contents, (isize)file_size);
    
    f->size = (isize)file_size;
    f->data = file_contents;
    
    afops->proc(f);
    
    zpl_free(zpl_heap_allocator( ), afops->f);
    zpl_free(zpl_heap_allocator( ), afops);
    
    return 0;
}

ZPL_THREAD_PROC(zpl__async_file_write_proc) {
    zpl__async_file_ctl *afops = cast(zpl__async_file_ctl *) thread->user_data;
    
    zpl_async_file *f = afops->f;
    
    i64 file_size = afops->data_size;
    void *file_contents = afops->data;
    zpl_file_write(&f->handle, file_contents, (isize)file_size);
    
    f->size = (isize)file_size;
    f->data = file_contents;
    
    afops->proc(f);
    
    zpl_free(zpl_heap_allocator( ), afops->f);
    zpl_free(zpl_heap_allocator( ), afops);
    
    return 0;
}

void zpl_async_file_read(zpl_file *file, zpl_async_file_cb *proc) {
    ZPL_ASSERT(file && proc);
    
    zpl_async_file *a = (zpl_async_file *)zpl_malloc(sizeof(zpl_async_file));
    zpl_async_file a_ = { 0 };
    *a = a_;
    
    a->handle = *file;
    
    zpl_thread td = { 0 };
    zpl_thread_init(&td);
    
    zpl__async_file_ctl *afops = (zpl__async_file_ctl *)zpl_malloc(sizeof(zpl__async_file_ctl));
    zpl__async_file_ctl afops_ = { 0 };
    *afops = afops_;
    
    afops->f = a;
    afops->proc = proc;
    
    zpl_thread_start(&td, zpl__async_file_read_proc, cast(void *) afops);
}

void zpl_async_file_write(zpl_file *file, void const *buffer, isize size, zpl_async_file_cb *proc) {
    ZPL_ASSERT(file && proc && buffer);
    
    zpl_async_file *a = (zpl_async_file *)zpl_malloc(sizeof(zpl_async_file));
    zpl_async_file a_ = { 0 };
    *a = a_;
    
    a->handle = *file;
    
    zpl_thread td = { 0 };
    zpl_thread_init(&td);
    
    zpl__async_file_ctl *afops = (zpl__async_file_ctl *)zpl_malloc(sizeof(zpl__async_file_ctl));
    zpl__async_file_ctl afops_ = { 0 };
    *afops = afops_;
    
    afops->f = a;
    afops->proc = proc;
    afops->data = cast(void *) buffer;
    afops->data_size = size;
    
    zpl_thread_start(&td, zpl__async_file_write_proc, cast(void *) afops);
}

#endif // ZPL_THREADING

// TODO: Is this a bad idea?
zpl_global b32 zpl__std_file_set = false;
zpl_global zpl_file zpl__std_files[ZPL_FILE_STANDARD_COUNT] = { { 0 } };

#if defined(ZPL_SYSTEM_WINDOWS)

zpl_inline zpl_file *zpl_file_get_standard(zplFileStandardType std) {
    if (!zpl__std_file_set) {
#define ZPL__SET_STD_FILE(type, v)                                                                                     \
        zpl__std_files[type].fd.p = v;                                                                                     \
        zpl__std_files[type].ops = zpl_default_file_operations
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_INPUT, GetStdHandle(STD_INPUT_HANDLE));
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_OUTPUT, GetStdHandle(STD_OUTPUT_HANDLE));
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_ERROR, GetStdHandle(STD_ERROR_HANDLE));
#undef ZPL__SET_STD_FILE
        zpl__std_file_set = true;
    }
    return &zpl__std_files[std];
}

zpl_inline i64 zpl_file_size(zpl_file *f) {
    LARGE_INTEGER size;
    GetFileSizeEx(f->fd.p, &size);
    return size.QuadPart;
}

zplFileError zpl_file_truncate(zpl_file *f, i64 size) {
    zplFileError err = ZPL_FILE_ERROR_NONE;
    i64 prev_offset = zpl_file_tell(f);
    zpl_file_seek(f, size);
    if (!SetEndOfFile(f)) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
    zpl_file_seek(f, prev_offset);
    return err;
}

b32 zpl_file_exists(char const *name) {
    WIN32_FIND_DATAW data;
    wchar_t *w_text;
    void *handle;
    b32 found = false;
    zpl_allocator a = zpl_heap_allocator( );
    
    w_text = zpl__alloc_utf8_to_ucs2(a, name, NULL);
    if (w_text == NULL) { return false; }
    handle = FindFirstFileW(w_text, &data);
    zpl_free(a, w_text);
    found = handle != INVALID_HANDLE_VALUE;
    if (found) FindClose(handle);
    return found;
}

#else // POSIX

zpl_inline zpl_file *zpl_file_get_standard(zplFileStandardType std) {
    if (!zpl__std_file_set) {
#define ZPL__SET_STD_FILE(type, v)                                                                                     \
        zpl__std_files[type].fd.i = v;                                                                                     \
        zpl__std_files[type].ops = zpl_default_file_operations
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_INPUT, 0);
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_OUTPUT, 1);
        ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_ERROR, 2);
#undef ZPL__SET_STD_FILE
        zpl__std_file_set = true;
    }
    return &zpl__std_files[std];
}

zpl_inline i64 zpl_file_size(zpl_file *f) {
    i64 size = 0;
    i64 prev_offset = zpl_file_tell(f);
    zpl_file_seek_to_end(f);
    size = zpl_file_tell(f);
    zpl_file_seek(f, prev_offset);
    return size;
}

zpl_inline zplFileError zpl_file_truncate(zpl_file *f, i64 size) {
    zplFileError err = ZPL_FILE_ERROR_NONE;
    int i = ftruncate(f->fd.i, size);
    if (i != 0) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
    return err;
}

zpl_inline b32 zpl_file_exists(char const *name) { return access(name, F_OK) != -1; }

#endif

zplFileError zpl_file_temp(zpl_file *file) {
#if defined(ZPL_SYSTEM_EMSCRIPTEN)
    ZPL_PANIC("zpl_file_temp is not supported for emscripten");
#else
    zpl_zero_item(file);
    FILE *fd = tmpfile( );
    
    if (fd == NULL) { return ZPL_FILE_ERROR_INVALID; }
    
    file->fd.p = fd;
    file->ops = zpl_default_file_operations;
#endif
    return ZPL_FILE_ERROR_NONE;
}

#if defined(ZPL_SYSTEM_WINDOWS)
zpl_file_time zpl_file_last_write_time(char const *filepath) {
    ULARGE_INTEGER li = { 0 };
    FILETIME last_write_time = { 0 };
    WIN32_FILE_ATTRIBUTE_DATA data = { 0 };
    zpl_allocator a = zpl_heap_allocator( );
    
    wchar_t *w_text = zpl__alloc_utf8_to_ucs2(a, filepath, NULL);
    if (w_text == NULL) { return 0; }
    if (GetFileAttributesExW(w_text, GetFileExInfoStandard, &data)) last_write_time = data.ftLastWriteTime;
    
    zpl_free(a, w_text);
    
    li.LowPart = last_write_time.dwLowDateTime;
    li.HighPart = last_write_time.dwHighDateTime;
    return cast(zpl_file_time) li.QuadPart;
}

zpl_inline b32 zpl_file_copy(char const *existing_filename, char const *new_filename, b32 fail_if_exists) {
    b32 result = false;
    zpl_allocator a = zpl_heap_allocator( );
    
    wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
    if (w_old == NULL) { return false; }
    
    wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
    if (w_new != NULL) { result = CopyFileW(w_old, w_new, fail_if_exists); }
    
    zpl_free(a, w_old);
    zpl_free(a, w_new);
    return result;
}

zpl_inline b32 zpl_file_move(char const *existing_filename, char const *new_filename) {
    b32 result = false;
    zpl_allocator a = zpl_heap_allocator( );
    
    wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
    if (w_old == NULL) { return false; }
    
    wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
    if (w_new != NULL) { result = MoveFileW(w_old, w_new); }
    
    zpl_free(a, w_old);
    zpl_free(a, w_new);
    return result;
}

zpl_inline b32 zpl_file_remove(char const *filename) {
    b32 result = false;
    zpl_allocator a = zpl_heap_allocator( );
    
    wchar_t *w_filename = zpl__alloc_utf8_to_ucs2(a, filename, NULL);
    if (w_filename == NULL) { return false; }
    
    result = DeleteFileW(w_filename);
    
    zpl_free(a, w_filename);
    return result;
}

#else

zpl_file_time zpl_file_last_write_time(char const *filepath) {
    time_t result = 0;
    struct stat file_stat;
    
    if (stat(filepath, &file_stat)) result = file_stat.st_mtime;
    
    return cast(zpl_file_time) result;
}

zpl_inline b32 zpl_file_copy(char const *existing_filename, char const *new_filename, b32 fail_if_exists) {
    zpl_unused(fail_if_exists);
#if defined(ZPL_SYSTEM_OSX)
    return copyfile(existing_filename, new_filename, NULL, COPYFILE_DATA) == 0;
#else
    isize size;
    int existing_fd = open(existing_filename, O_RDONLY, 0);
    int new_fd = open(new_filename, O_WRONLY | O_CREAT, 0666);
    
    struct stat stat_existing;
    fstat(existing_fd, &stat_existing);
    
    size = sendfile(new_fd, existing_fd, 0, stat_existing.st_size);
    
    close(new_fd);
    close(existing_fd);
    
    return size == stat_existing.st_size;
#endif
}

zpl_inline b32 zpl_file_move(char const *existing_filename, char const *new_filename) {
    if (link(existing_filename, new_filename) == 0) { return (unlink(existing_filename) != -1); }
    return false;
}

zpl_inline b32 zpl_file_remove(char const *filename) {
#if defined(ZPL_SYSTEM_OSX) || defined(ZPL_SYSTEM_EMSCRIPTEN)
    return (unlink(filename) != -1);
#else
    return (remove(filename) == 0);
#endif
}

#endif

zpl_file_contents zpl_file_read_contents(zpl_allocator a, b32 zero_terminate, char const *filepath) {
    zpl_file_contents result = { 0 };
    zpl_file file = { 0 };
    
    result.allocator = a;
    
    if (zpl_file_open(&file, filepath) == ZPL_FILE_ERROR_NONE) {
        isize file_size = cast(isize) zpl_file_size(&file);
        if (file_size > 0) {
            result.data = zpl_alloc(a, zero_terminate ? file_size + 1 : file_size);
            result.size = file_size;
            zpl_file_read_at(&file, result.data, result.size, 0);
            if (zero_terminate) {
                u8 *str = cast(u8 *) result.data;
                str[file_size] = '\0';
            }
        }
        zpl_file_close(&file);
    }
    
    return result;
}

char *zpl_file_read_lines(zpl_allocator alloc, char ***lines, char const *filename, b32 strip_whitespace) {
    zpl_file f = { 0 };
    zpl_file_open(&f, filename);
    isize fsize = (isize)zpl_file_size(&f);
    
    char *contents = (char *)zpl_alloc(alloc, fsize + 1);
    zpl_file_read(&f, contents, fsize);
    contents[fsize] = 0;
    *lines = zpl_str_split_lines(alloc, contents, strip_whitespace);
    zpl_file_close(&f);
    
    return contents;
}

void zpl_file_free_contents(zpl_file_contents *fc) {
    ZPL_ASSERT_NOT_NULL(fc->data);
    zpl_free(fc->allocator, fc->data);
    fc->data = NULL;
    fc->size = 0;
}

zpl_inline b32 zpl_path_is_absolute(char const *path) {
    b32 result = false;
    ZPL_ASSERT_NOT_NULL(path);
#if defined(ZPL_SYSTEM_WINDOWS)
    result = (zpl_strlen(path) > 2) && zpl_char_is_alpha(path[0]) && (path[1] == ':' && path[2] == ZPL_PATH_SEPARATOR);
#else
    result = (zpl_strlen(path) > 0 && path[0] == ZPL_PATH_SEPARATOR);
#endif
    return result;
}

zpl_inline b32 zpl_path_is_relative(char const *path) { return !zpl_path_is_absolute(path); }

zpl_inline b32 zpl_path_is_root(char const *path) {
    b32 result = false;
    ZPL_ASSERT_NOT_NULL(path);
#if defined(ZPL_SYSTEM_WINDOWS)
    result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 3);
#else
    result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 1);
#endif
    return result;
}

zpl_inline char const *zpl_path_base_name(char const *path) {
    char const *ls;
    ZPL_ASSERT_NOT_NULL(path);
    ls = zpl_char_last_occurence(path, '/');
    return (ls == NULL) ? path : ls + 1;
}

zpl_inline char const *zpl_path_extension(char const *path) {
    char const *ld;
    ZPL_ASSERT_NOT_NULL(path);
    ld = zpl_char_last_occurence(path, '.');
    return (ld == NULL) ? NULL : ld + 1;
}

#if !defined(_WINDOWS_) && defined(ZPL_SYSTEM_WINDOWS)
ZPL_DLL_IMPORT DWORD WINAPI GetFullPathNameA(char const *lpFileName, DWORD nBufferLength, char *lpBuffer,
                                             char **lpFilePart);
ZPL_DLL_IMPORT DWORD WINAPI GetFullPathNameW(wchar_t const *lpFileName, DWORD nBufferLength, wchar_t *lpBuffer,
                                             wchar_t **lpFilePart);
#endif

char *zpl_path_get_full_name(zpl_allocator a, char const *path) {
#if defined(ZPL_SYSTEM_WINDOWS)
    wchar_t *w_path = NULL;
    wchar_t *w_fullpath = NULL;
    isize w_len = 0;
    isize new_len = 0;
    isize new_len1 = 0;
    char *new_path = 0;
    w_path = zpl__alloc_utf8_to_ucs2(zpl_heap_allocator( ), path, NULL);
    if (w_path == NULL) { return NULL; }
    w_len = GetFullPathNameW(w_path, 0, NULL, NULL);
    if (w_len == 0) { return NULL; }
    w_fullpath = zpl_alloc_array(zpl_heap_allocator( ), wchar_t, w_len + 1);
    GetFullPathNameW(w_path, cast(int) w_len, w_fullpath, NULL);
    w_fullpath[w_len] = 0;
    zpl_free(zpl_heap_allocator( ), w_path);
    
    new_len = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, w_fullpath, cast(int) w_len, NULL, 0, NULL, NULL);
    if (new_len == 0) {
        zpl_free(zpl_heap_allocator( ), w_fullpath);
        return NULL;
    }
    new_path = zpl_alloc_array(a, char, new_len1);
    new_len1 = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, w_fullpath, cast(int) w_len, new_path,
                                   cast(int) new_len, NULL, NULL);
    if (new_len1 == 0) {
        zpl_free(zpl_heap_allocator( ), w_fullpath);
        zpl_free(a, new_path);
        return NULL;
    }
    new_path[new_len] = 0;
    return new_path;
#else
    char *p, *result, *fullpath = NULL;
    isize len;
    p = realpath(path, NULL);
    fullpath = p;
    if (p == NULL) {
        // NOTE(bill): File does not exist
        fullpath = cast(char *) path;
    }
    
    len = zpl_strlen(fullpath);
    
    result = zpl_alloc_array(a, char, len + 1);
    zpl_memmove(result, fullpath, len);
    result[len] = 0;
    zpl_free(a, p);
    
    return result;
#endif
}

zplFileError zpl_path_mkdir(char const *path, i32 mode) {
    i32 error = 0;
#if defined(ZPL_SYSTEM_WINDOWS)
    error = _wmkdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const u8 *)path));
#else
    error = mkdir(path, (mode_t)mode);
#endif
    
    if (error == 0) { return ZPL_FILE_ERROR_NONE; }
    
    switch (errno) {
        case EPERM:
        case EACCES: return ZPL_FILE_ERROR_PERMISSION;
        case EEXIST: return ZPL_FILE_ERROR_EXISTS;
        case ENAMETOOLONG: return ZPL_FILE_ERROR_NAME_TOO_LONG;
    }
    
    return ZPL_FILE_ERROR_UNKNOWN;
}

zplFileError zpl_path_rmdir(char const *path) {
    i32 error = 0;
#if defined(ZPL_SYSTEM_WINDOWS)
    error = _wrmdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const u8 *)path));
#else
    error = rmdir(path);
#endif
    
    if (error == 0) { return ZPL_FILE_ERROR_NONE; }
    
    switch (errno) {
        case EPERM:
        case EACCES: return ZPL_FILE_ERROR_PERMISSION;
        case ENOENT: return ZPL_FILE_ERROR_NOT_EXISTS;
        case ENOTEMPTY: return ZPL_FILE_ERROR_NOT_EMPTY;
        case ENAMETOOLONG: return ZPL_FILE_ERROR_NAME_TOO_LONG;
    }
    
    return ZPL_FILE_ERROR_UNKNOWN;
}

void zpl__file_direntry(zpl_allocator alloc, char const *dirname, zpl_string *output, b32 recurse) {
#if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_OSX)
    DIR *d, *cd;
    struct dirent *dir;
    d = opendir(dirname);
    
    if (d) {
        while ((dir = readdir(d))) {
            if (!zpl_strncmp(dir->d_name, "..", 2)) continue;
            if (dir->d_name[0] == '.' && dir->d_name[1] == 0) continue;
            
            zpl_string dirpath = zpl_string_make(alloc, dirname);
            dirpath = zpl_string_appendc(dirpath, "/");
            dirpath = zpl_string_appendc(dirpath, dir->d_name);
            
            *output = zpl_string_appendc(*output, dirpath);
            *output = zpl_string_appendc(*output, "\n");
            
            if (recurse && (cd = opendir(dirpath)) != NULL) { zpl__file_direntry(alloc, dirpath, output, recurse); }
            zpl_string_free(dirpath);
        }
    }
#elif defined(ZPL_SYSTEM_WINDOWS)
    usize length = zpl_strlen(dirname);
    struct _wfinddata_t data;
    intptr_t findhandle;
    
    char directory[MAX_PATH] = { 0 };
    zpl_strncpy(directory, dirname, length);
    
    // keeping it native
    for (usize i = 0; i < length; i++) {
        if (directory[i] == '/') directory[i] = '\\';
    }
    
    // remove trailing slashses
    if (directory[length - 1] == '\\') { directory[length - 1] = '\0'; }
    
    // attach search parttern
    zpl_string findpath = zpl_string_make(alloc, directory);
    findpath = zpl_string_appendc(findpath, "\\");
    findpath = zpl_string_appendc(findpath, "*");
    
    findhandle = _wfindfirst((const wchar_t *)zpl_utf8_to_ucs2_buf((const u8 *)findpath), &data);
    zpl_string_free(findpath);
    
    if (findhandle != -1) {
        do {
            char *filename = (char *)zpl_ucs2_to_utf8_buf((const u16 *)data.name);
            if (!zpl_strncmp(filename, "..", 2)) continue;
            if (filename[0] == '.' && filename[1] == 0) continue;
            
            zpl_string dirpath = zpl_string_make(alloc, directory);
            dirpath = zpl_string_appendc(dirpath, "\\");
            dirpath = zpl_string_appendc(dirpath, filename);
            
            *output = zpl_string_appendc(*output, dirpath);
            *output = zpl_string_appendc(*output, "\n");
            
            if (recurse && (data.attrib & _A_SUBDIR)) { zpl__file_direntry(alloc, dirpath, output, recurse); }
            
            zpl_string_free(dirpath);
        } while (_wfindnext(findhandle, &data) != -1);
        _findclose(findhandle);
    }
#else
    // TODO: Implement other OSes
#endif
}

zpl_string zpl_path_dirlist(zpl_allocator alloc, char const *dirname, b32 recurse) {
    zpl_string buf = zpl_string_make_reserve(alloc, 4);
    zpl__file_direntry(alloc, dirname, &buf, recurse);
    return buf;
}
