#include <dirent.h>

#if !defined(ZPL_SYSTEM_MACOS) && !defined(ZPL_SYSTEM_FREEBSD)
    #include <sys/sendfile.h>
#endif

#if defined(ZPL_SYSTEM_WINDOWS)
    zpl_file_time zpl_fs_last_write_time(char const *filepath) {
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

    zpl_b32 zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists) {
        zpl_b32 result = false;
        zpl_allocator a = zpl_heap_allocator( );

        wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
        if (w_old == NULL) { return false; }

        wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
        if (w_new != NULL) { result = CopyFileW(w_old, w_new, fail_if_exists); }

        zpl_free(a, w_old);
        zpl_free(a, w_new);
        return result;
    }

    zpl_b32 zpl_fs_move(char const *existing_filename, char const *new_filename) {
        zpl_b32 result = false;
        zpl_allocator a = zpl_heap_allocator( );

        wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
        if (w_old == NULL) { return false; }

        wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
        if (w_new != NULL) { result = MoveFileW(w_old, w_new); }

        zpl_free(a, w_old);
        zpl_free(a, w_new);
        return result;
    }

    zpl_b32 zpl_fs_remove(char const *filename) {
        zpl_b32 result = false;
        zpl_allocator a = zpl_heap_allocator( );

        wchar_t *w_filename = zpl__alloc_utf8_to_ucs2(a, filename, NULL);
        if (w_filename == NULL) { return false; }

        result = DeleteFileW(w_filename);

        zpl_free(a, w_filename);
        return result;
    }

#else

    zpl_file_time zpl_fs_last_write_time(char const *filepath) {
        time_t result = 0;
        struct stat file_stat;

        if (stat(filepath, &file_stat)) result = file_stat.st_mtime;

        return cast(zpl_file_time) result;
    }

    zpl_b32 zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists) {
        zpl_unused(fail_if_exists);
    #if defined(ZPL_SYSTEM_OSX)
        return copyfile(existing_filename, new_filename, NULL, COPYFILE_DATA) == 0;
    #else
        zpl_isize size;
        int existing_fd = open(existing_filename, O_RDONLY, 0);
        int new_fd = open(new_filename, O_WRONLY | O_CREAT, 0666);

        struct stat stat_existing;
        fstat(existing_fd, &stat_existing);

    #if defined(ZPL_SYSTEM_FREEBSD)
        size = sendfile(new_fd, existing_fd, 0, stat_existing.st_size, NULL, 0, 0);
    #else
        size = sendfile(new_fd, existing_fd, 0, stat_existing.st_size);
    #endif

        close(new_fd);
        close(existing_fd);

        return size == stat_existing.st_size;
    #endif
    }

    zpl_b32 zpl_fs_move(char const *existing_filename, char const *new_filename) {
        if (link(existing_filename, new_filename) == 0) { return (unlink(existing_filename) != -1); }
        return false;
    }

    zpl_b32 zpl_fs_remove(char const *filename) {
    #if defined(ZPL_SYSTEM_OSX) || defined(ZPL_SYSTEM_EMSCRIPTEN)
        return (unlink(filename) != -1);
    #else
        return (remove(filename) == 0);
    #endif
    }

#endif

char *zpl_path_get_full_name(zpl_allocator a, char const *path) {
#if defined(ZPL_SYSTEM_WINDOWS)
    wchar_t *w_path = NULL;
    wchar_t *w_fullpath = NULL;
    zpl_isize w_len = 0;
    zpl_isize new_len = 0;
    zpl_isize new_len1 = 0;
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
    zpl_isize len;
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

zpl_file_error zpl_path_mkdir(char const *path, zpl_i32 mode) {
    zpl_i32 error = 0;
#if defined(ZPL_SYSTEM_WINDOWS)
    error = _wmkdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));
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

zpl_file_error zpl_path_rmdir(char const *path) {
    zpl_i32 error = 0;
#if defined(ZPL_SYSTEM_WINDOWS)
    error = _wrmdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));
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

void zpl__file_direntry(zpl_allocator alloc, char const *dirname, zpl_string *output, zpl_b32 recurse) {
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
    zpl_usize length = zpl_strlen(dirname);
    struct _wfinddata_t data;
    zpl_intptr findhandle;

    char directory[MAX_PATH] = { 0 };
    zpl_strncpy(directory, dirname, length);

    // keeping it native
    for (zpl_usize i = 0; i < length; i++) {
        if (directory[i] == '/') directory[i] = '\\';
    }

    // remove trailing slashses
    if (directory[length - 1] == '\\') { directory[length - 1] = '\0'; }

    // attach search parttern
    zpl_string findpath = zpl_string_make(alloc, directory);
    findpath = zpl_string_appendc(findpath, "\\");
    findpath = zpl_string_appendc(findpath, "*");

    findhandle = _wfindfirst((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)findpath), &data);
    zpl_string_free(findpath);

    if (findhandle != -1) {
        do {
            char *filename = (char *)zpl_ucs2_to_utf8_buf((const zpl_u16 *)data.name);
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

zpl_string zpl_path_dirlist(zpl_allocator alloc, char const *dirname, zpl_b32 recurse) {
    zpl_string buf = zpl_string_make_reserve(alloc, 4);
    zpl__file_direntry(alloc, dirname, &buf, recurse);
    return buf;
}

void zpl_dirinfo_init(zpl_dir_info *dir, char const *path) {
    ZPL_ASSERT_NOT_NULL(dir);

    zpl_dir_info dir_ = {0};
    *dir = dir_;
    dir->fullpath = (char const*)zpl_malloc(zpl_strlen(path));
    zpl_strcpy((char *)dir->fullpath, path);


    zpl_string dirlist = zpl_path_dirlist(zpl_heap(), path, false);
    char **files=zpl_str_split_lines(zpl_heap(), dirlist, false);
    dir->filenames = files;
    dir->buf = dirlist;

    zpl_array_init(dir->entries, zpl_heap());

    for (zpl_i32 i=0; i<zpl_array_count(files); ++i) {
        zpl_dir_entry entry = {0};
        entry.filename = files[i];
        entry.type = zpl_fs_get_type(entry.filename);

        zpl_array_append(dir->entries, entry);
    }
}

zpl_internal void zpl__dirinfo_free_entry(zpl_dir_entry *entry) {
    if (entry->dir_info) {
        zpl_dirinfo_free(entry->dir_info);
        zpl_mfree(entry->dir_info);
        entry->dir_info = NULL;
    }
}

void zpl_dirinfo_free(zpl_dir_info *dir) {
    ZPL_ASSERT_NOT_NULL(dir);

    for (zpl_isize i = 0; i < zpl_array_count(dir->entries); ++i) {
        zpl__dirinfo_free_entry(dir->entries + i);
    }

    zpl_array_free(dir->entries);
    zpl_array_free(dir->filenames);
    zpl_string_free(dir->buf);
    zpl_mfree((void *)dir->fullpath);
}


zpl_u8 zpl_fs_get_type(char const *path) {
#ifdef ZPL_SYSTEM_WINDOWS
    DWORD attrs = GetFileAttributesW((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));

    if (attrs == INVALID_FILE_ATTRIBUTES) {
        return ZPL_DIR_TYPE_UNKNOWN;
    }

    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        return ZPL_DIR_TYPE_FOLDER;
    }
    else {
        return ZPL_DIR_TYPE_FILE;
    }

#else
    struct stat s;
    if( stat(path,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            return ZPL_DIR_TYPE_FOLDER;
        }
        else
        {
            return ZPL_DIR_TYPE_FILE;
        }
    }
#endif

    return ZPL_DIR_TYPE_UNKNOWN;
}

void zpl_dirinfo_step(zpl_dir_entry *entry) {
    if (entry->dir_info) {
        zpl__dirinfo_free_entry(entry);
    }

    entry->dir_info = (zpl_dir_info *)zpl_malloc(sizeof(zpl_dir_info));
    zpl_dir_info dir_ = {0};
    *entry->dir_info = dir_;

    zpl_local_persist char buf[128] = {0};
    char const *path = entry->filename;

    if (entry->type != ZPL_DIR_TYPE_FOLDER) {
        zpl_path_fix_slashes((char *)path);
        char const* slash = zpl_char_last_occurence(path, ZPL_PATH_SEPARATOR);
        zpl_strncpy(buf, path, slash-path);
        path = buf;
    }

    zpl_dirinfo_init(entry->dir_info, path);
}

void zpl_file_dirinfo_refresh(zpl_file *file) {
    if (file->dir) {
        zpl__dirinfo_free_entry(file->dir);
        zpl_mfree(file->dir);
        file->dir = NULL;
    }

    file->dir = (zpl_dir_entry *)zpl_malloc(sizeof(zpl_dir_entry));
    zpl_dir_entry dir_ = {0};
    *file->dir = dir_;
    file->dir->filename = file->filename;
    file->dir->type = ZPL_DIR_TYPE_FILE;

    zpl_dirinfo_step(file->dir);
}

void zpl_path_fix_slashes(char *path) {
#ifdef ZPL_SYSTEM_WINDOWS
    char *p = path;

    while (*p != '\0') {
        if (*p == '/')
            *p = '\\';

        ++p;
    }
#endif
}
