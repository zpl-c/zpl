// file: source/core/file_stream.c


////////////////////////////////////////////////////////////////
//
// Memory streaming
//
//

ZPL_BEGIN_C_DECLS

typedef struct {
    zpl_u8 magic;
    zpl_u8 *buf; //< zpl_array OR plain buffer if we can't write
    zpl_isize cursor;
    zpl_allocator alloc;

    zpl_file_stream_flags flags;
    zpl_isize cap;
} zpl__memory_fd;

#define ZPL__FILE_STREAM_FD_MAGIC 37

ZPL_ALWAYS_INLINE zpl_file_descriptor zpl__file_stream_fd_make(zpl__memory_fd* d) {
    zpl_file_descriptor fd = {0};
    fd.p = (void*)d;
    return fd;
}

ZPL_ALWAYS_INLINE zpl__memory_fd *zpl__file_stream_from_fd(zpl_file_descriptor fd) {
    zpl__memory_fd *d = (zpl__memory_fd*)fd.p;
    ZPL_ASSERT(d->magic == ZPL__FILE_STREAM_FD_MAGIC);
    return d;
}

void zpl_file_stream_new(zpl_file* file, zpl_allocator allocator) {
    ZPL_ASSERT_NOT_NULL(file);
    zpl__memory_fd *d = (zpl__memory_fd*)zpl_alloc(allocator, zpl_size_of(zpl__memory_fd));
    zpl_zero_item(file);
    d->magic = ZPL__FILE_STREAM_FD_MAGIC;
    d->alloc = allocator;
    d->flags = ZPL_FILE_STREAM_CLONE_WRITABLE;
    d->cap = 0;
    zpl_array_init(d->buf, allocator);
    file->ops = zpl_memory_file_operations;
    file->fd = zpl__file_stream_fd_make(d);
    file->dir = NULL;
    file->last_write_time = 0;
    file->filename = NULL;
    file->is_temp = true;
}
void zpl_file_stream_open(zpl_file* file, zpl_allocator allocator, zpl_u8 *buffer, zpl_isize size, zpl_file_stream_flags flags) {
    ZPL_ASSERT_NOT_NULL(file);
    zpl__memory_fd *d = (zpl__memory_fd*)zpl_alloc(allocator, zpl_size_of(zpl__memory_fd));
    zpl_zero_item(file);
    d->magic = ZPL__FILE_STREAM_FD_MAGIC;
    d->alloc = allocator;
    d->flags = flags;
    if (d->flags & ZPL_FILE_STREAM_CLONE_WRITABLE) {
        zpl_array_init_reserve(d->buf, allocator, size);
        zpl_memcopy(d->buf, buffer, size);
        d->cap = zpl_array_count(d->buf) = size;
    } else {
        d->buf = buffer;
        d->cap = size;
    }
    file->ops = zpl_memory_file_operations;
    file->fd = zpl__file_stream_fd_make(d);
    file->dir = NULL;
    file->last_write_time = 0;
    file->filename = NULL;
    file->is_temp = true;
}

zpl_u8 *zpl_file_stream_buf(zpl_file* file, zpl_isize *size) {
    ZPL_ASSERT_NOT_NULL(file);
    zpl__memory_fd *d = zpl__file_stream_from_fd(file->fd);
    if (size) *size = d->cap;
    return d->buf;
}

zpl_internal ZPL_FILE_SEEK_PROC(zpl__memory_file_seek) {
    zpl__memory_fd *d = zpl__file_stream_from_fd(fd);
    zpl_isize buflen = d->cap;

    if (whence == ZPL_SEEK_WHENCE_BEGIN)
        d->cursor = 0;
    else if (whence == ZPL_SEEK_WHENCE_END)
        d->cursor = buflen;

    d->cursor = zpl_max(0, zpl_clamp(d->cursor + offset, 0, buflen));
    if (new_offset) *new_offset = d->cursor;
    return true;
}

zpl_internal ZPL_FILE_READ_AT_PROC(zpl__memory_file_read) {
    zpl_unused(stop_at_newline);
    zpl__memory_fd *d = zpl__file_stream_from_fd(fd);
    zpl_memcopy(buffer, d->buf + offset, size);
    if (bytes_read) *bytes_read = size;
    return true;
}

zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__memory_file_write) {
    zpl__memory_fd *d = zpl__file_stream_from_fd(fd);
    if (!(d->flags & (ZPL_FILE_STREAM_CLONE_WRITABLE|ZPL_FILE_STREAM_WRITABLE)))
        return false;
    zpl_isize buflen = d->cap;
    zpl_isize extralen = zpl_max(0, size-(buflen-offset));
    zpl_isize rwlen = size-extralen;
    zpl_isize new_cap = buflen+extralen;
    if (d->flags & ZPL_FILE_STREAM_CLONE_WRITABLE) {
        if(zpl_array_capacity(d->buf) < new_cap) {
            zpl_array_grow(d->buf, (zpl_i64)(new_cap));
        }
    }
    zpl_memcopy(d->buf + offset, buffer, rwlen);

    if ((d->flags & ZPL_FILE_STREAM_CLONE_WRITABLE) && extralen > 0) {
        zpl_memcopy(d->buf + offset + rwlen, zpl_ptr_add_const(buffer, rwlen), extralen);
        d->cap = zpl_array_count(d->buf) = new_cap;
    } else {
        extralen = 0;
    }

    if (bytes_written) *bytes_written = (rwlen+extralen);
    return true;
}

zpl_internal ZPL_FILE_CLOSE_PROC(zpl__memory_file_close) {
    zpl__memory_fd *d = zpl__file_stream_from_fd(fd);
    zpl_allocator alloc = d->alloc;
    if (d->flags & ZPL_FILE_STREAM_CLONE_WRITABLE)
        zpl_array_free(d->buf);
    zpl_free(alloc, d);
}

zpl_file_operations const zpl_memory_file_operations = { zpl__memory_file_read, zpl__memory_file_write,
    zpl__memory_file_seek, zpl__memory_file_close };

ZPL_END_C_DECLS
