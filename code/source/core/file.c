// file: source/core/file.c


////////////////////////////////////////////////////////////////
//
// File Handling
//
//
#include <sys/stat.h>

#ifdef ZPL_SYSTEM_MACOS
#    include <copyfile.h>
#endif

#ifdef ZPL_SYSTEM_CYGWIN
#   include <windows.h>
#endif

#if defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_COMPILER_GCC)
#include <io.h>
#endif

ZPL_BEGIN_C_DECLS

#if defined(ZPL_SYSTEM_WINDOWS) || defined (ZPL_SYSTEM_CYGWIN)

    zpl_internal wchar_t *zpl__alloc_utf8_to_ucs2(zpl_allocator a, char const *text, zpl_isize *w_len_) {
        wchar_t *w_text = NULL;
        zpl_isize len = 0, w_len = 0, w_len1 = 0;
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
        zpl_b32 result = false;
        zpl__win32_file_seek(fd, offset, ZPL_SEEK_WHENCE_BEGIN, NULL);
        DWORD size_ = cast(DWORD)(size > ZPL_I32_MAX ? ZPL_I32_MAX : size);
        DWORD bytes_read_;
        if (ReadFile(fd.p, buffer, size_, &bytes_read_, NULL)) {
            if (bytes_read) *bytes_read = bytes_read_;
            result = true;
        }

        return result;
    }

    zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__win32_file_write) {
        DWORD size_ = cast(DWORD)(size > ZPL_I32_MAX ? ZPL_I32_MAX : size);
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

    ZPL_NEVER_INLINE ZPL_FILE_OPEN_PROC(zpl__win32_file_open) {
        DWORD desired_access;
        DWORD creation_disposition;
        void *handle;
        wchar_t *w_text;

        switch (mode & ZPL_FILE_MODES) {
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
#    include <fcntl.h>

    zpl_internal ZPL_FILE_SEEK_PROC(zpl__posix_file_seek) {
#    if defined(ZPL_SYSTEM_OSX)
        zpl_i64 res = lseek(fd.i, offset, whence);
#    else // TODO(ZaKlaus): @fixme lseek64
        zpl_i64 res = lseek(fd.i, offset, whence);
#    endif
        if (res < 0) return false;
        if (new_offset) *new_offset = res;
        return true;
    }

    zpl_internal ZPL_FILE_READ_AT_PROC(zpl__posix_file_read) {
        zpl_unused(stop_at_newline);
        zpl_isize res = pread(fd.i, buffer, size, offset);
        if (res < 0) return false;
        if (bytes_read) *bytes_read = res;
        return true;
    }

    zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__posix_file_write) {
        zpl_isize res;
        zpl_i64 curr_offset = 0;
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

    ZPL_NEVER_INLINE ZPL_FILE_OPEN_PROC(zpl__posix_file_open) {
        zpl_i32 os_mode;
        switch (mode & ZPL_FILE_MODES) {
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

zpl_file_error zpl_file_new(zpl_file *f, zpl_file_descriptor fd, zpl_file_operations ops, char const *filename) {
    zpl_file_error err = ZPL_FILE_ERROR_NONE;
    zpl_isize len = zpl_strlen(filename);

    f->ops = ops;
    f->fd = fd;
    f->dir = NULL;
    f->last_write_time = 0;
    f->filename = zpl_alloc_array(zpl_heap_allocator( ), char, len + 1);
    zpl_memcopy(cast(char *) f->filename, cast(char *) filename, len + 1);

    return err;
}

zpl_file_error zpl_file_open_mode(zpl_file *f, zpl_file_mode mode, char const *filename) {
    zpl_file file_ = {0};
    *f = file_;
    zpl_file_error err;
#if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)
    err = zpl__win32_file_open(&f->fd, &f->ops, mode, filename);
#else
    err = zpl__posix_file_open(&f->fd, &f->ops, mode, filename);
#endif
    if (err == ZPL_FILE_ERROR_NONE) return zpl_file_new(f, f->fd, f->ops, filename);
    return err;
}

zpl_internal void zpl__dirinfo_free_entry(zpl_dir_entry *entry);

zpl_file_error zpl_file_close(zpl_file *f) {
    if (!f) return ZPL_FILE_ERROR_INVALID;

    if (f->filename) zpl_free(zpl_heap_allocator( ), cast(char *) f->filename);

#if defined(ZPL_SYSTEM_WINDOWS)
    if (f->fd.p == INVALID_HANDLE_VALUE) return ZPL_FILE_ERROR_INVALID;
#else
    if (f->fd.i < 0) return ZPL_FILE_ERROR_INVALID;
#endif
    
    if (f->is_temp)
    {
        f->ops.close(f->fd);
        return ZPL_FILE_ERROR_NONE;
    }

    if (!f->ops.read_at) f->ops = zpl_default_file_operations;
    f->ops.close(f->fd);

    if (f->dir) {
        zpl__dirinfo_free_entry(f->dir);
        zpl_mfree(f->dir);
        f->dir = NULL;
    }

    return ZPL_FILE_ERROR_NONE;
}


zpl_file_error zpl_file_create(zpl_file *f, char const *filename) {
    return zpl_file_open_mode(f, ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW, filename);
}

zpl_file_error zpl_file_open(zpl_file *f, char const *filename) {
    return zpl_file_open_mode(f, ZPL_FILE_MODE_READ, filename);
}

char const *zpl_file_name(zpl_file *f) { return f->filename ? f->filename : ""; }

zpl_b32 zpl_file_has_changed(zpl_file *f) {
    if (f->is_temp)
        return false;
    zpl_b32 result = false;
    zpl_file_time last_write_time = zpl_fs_last_write_time(f->filename);
    if (f->last_write_time != last_write_time) {
        result = true;
        f->last_write_time = last_write_time;
    }
    return result;
}

// TODO: Is this a bad idea?
zpl_global zpl_b32 zpl__std_file_set = false;
zpl_global zpl_file zpl__std_files[ZPL_FILE_STANDARD_COUNT] = { { 0 } };

#if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)

zpl_file *zpl_file_get_standard(zpl_file_standard_type std) {
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

void zpl_file_connect_handle(zpl_file *file, void *handle) {
    ZPL_ASSERT_NOT_NULL(file);
    ZPL_ASSERT_NOT_NULL(handle);

    if (file->is_temp)
        return;

    zpl_zero_item(file);

    file->fd.p = handle;
    file->ops = zpl_default_file_operations;
}

zpl_file_error zpl_file_truncate(zpl_file *f, zpl_i64 size) {
    zpl_file_error err = ZPL_FILE_ERROR_NONE;
    zpl_i64 prev_offset = zpl_file_tell(f);
    zpl_file_seek(f, size);
    if (!SetEndOfFile(f)) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
    zpl_file_seek(f, prev_offset);
    return err;
}

zpl_b32 zpl_fs_exists(char const *name) {
    WIN32_FIND_DATAW data;
    wchar_t *w_text;
    void *handle;
    zpl_b32 found = false;
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

zpl_file *zpl_file_get_standard(zpl_file_standard_type std) {
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

zpl_file_error zpl_file_truncate(zpl_file *f, zpl_i64 size) {
    zpl_file_error err = ZPL_FILE_ERROR_NONE;
    int i = ftruncate(f->fd.i, size);
    if (i != 0) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
    return err;
}

zpl_b32 zpl_fs_exists(char const *name) { return access(name, F_OK) != -1; }

#endif

zpl_i64 zpl_file_size(zpl_file *f) {
    zpl_i64 size = 0;
    zpl_i64 prev_offset = zpl_file_tell(f);
    zpl_file_seek_to_end(f);
    size = zpl_file_tell(f);
    zpl_file_seek(f, prev_offset);
    return size;
}

zpl_file_error zpl_file_temp(zpl_file *file) {
    zpl_zero_item(file);
    FILE *fd = NULL;

#if (defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_SYSTEM_TINYC)) && !defined(ZPL_COMPILER_GCC)
    errno_t errcode = tmpfile_s(&fd);

    if (errcode != 0) {
        fd = NULL;
    }
#else
    fd = tmpfile();
#endif

    if (fd == NULL) { return ZPL_FILE_ERROR_INVALID; }

#if defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_COMPILER_GCC)
    file->fd.i = _get_osfhandle(_fileno(fd));
#else 
    file->fd.i = fileno(fd);
#endif
    file->ops = zpl_default_file_operations;
    file->is_temp = true;
    return ZPL_FILE_ERROR_NONE;
}

zpl_file_contents zpl_file_read_contents(zpl_allocator a, zpl_b32 zero_terminate, char const *filepath) {
    zpl_file_contents result = { 0 };
    zpl_file file = { 0 };

    result.allocator = a;

    zpl_u8 entry_type = zpl_fs_get_type(filepath);

    /* ignore folders */
    if (entry_type == ZPL_DIR_TYPE_FOLDER) {
        return result;
    }

    if (zpl_file_open(&file, filepath) == ZPL_FILE_ERROR_NONE) {
        zpl_isize file_size = cast(zpl_isize) zpl_file_size(&file);
        if (file_size > 0) {
            result.data = zpl_alloc(a, zero_terminate ? file_size + 1 : file_size);
            result.size = file_size;
            zpl_file_read_at(&file, result.data, result.size, 0);
            if (zero_terminate) {
                zpl_u8 *str = cast(zpl_u8 *) result.data;
                str[file_size] = '\0';
            }
        }
        zpl_file_close(&file);
    }

    return result;
}

void zpl_file_free_contents(zpl_file_contents *fc) {
    ZPL_ASSERT_NOT_NULL(fc->data);
    zpl_free(fc->allocator, fc->data);
    fc->data = NULL;
    fc->size = 0;
}

zpl_b32 zpl_file_write_contents(char const* filepath, void const* buffer, zpl_isize size, zpl_file_error* err) {
    zpl_file f = { 0 };
    zpl_file_error open_err;
    zpl_b32 write_ok;
    open_err = zpl_file_open_mode(&f, ZPL_FILE_MODE_WRITE, filepath);

    if (open_err != ZPL_FILE_ERROR_NONE)
    {
        if (err)
            *err = open_err;

        return false;
    }

    write_ok = zpl_file_write(&f, buffer, size);
    zpl_file_close(&f);
    return write_ok;
}

char *zpl_file_read_lines(zpl_allocator alloc, zpl_array(char *)*lines, char const *filename, zpl_b32 strip_whitespace) {
    zpl_file f = { 0 };
    zpl_file_open(&f, filename);
    zpl_isize fsize = (zpl_isize)zpl_file_size(&f);

    char *contents = (char *)zpl_alloc(alloc, fsize + 1);
    zpl_file_read(&f, contents, fsize);
    contents[fsize] = 0;
    *lines = zpl_str_split_lines(alloc, contents, strip_whitespace);
    zpl_file_close(&f);

    return contents;
}

#if !defined(_WINDOWS_) && defined(ZPL_SYSTEM_WINDOWS)
    ZPL_IMPORT DWORD WINAPI GetFullPathNameA(char const *lpFileName, DWORD nBufferLength, char *lpBuffer, char **lpFilePart);
    ZPL_IMPORT DWORD WINAPI GetFullPathNameW(wchar_t const *lpFileName, DWORD nBufferLength, wchar_t *lpBuffer, wchar_t **lpFilePart);
#endif

ZPL_END_C_DECLS
