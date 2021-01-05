// file: header/core/file_stream.h

/** @file file_stream.c
@brief File stream
@defgroup fileio File stream

File streaming operations on memory.

@{
*/
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef enum {
    /* Allows us to write to the buffer directly. Beware: you can not append a new data! */
    ZPL_FILE_STREAM_WRITABLE = ZPL_BIT(0),

    /* Clones the input buffer so you can write (zpl_file_write*) data into it. */
    /* Since we work with a clone, the buffer size can dynamically grow as well. */
    ZPL_FILE_STREAM_CLONE_WRITABLE = ZPL_BIT(1),
} zpl_file_stream_flags;

/**
 * Opens a new memory stream
 * @param file
 * @param allocator
 */
ZPL_DEF void zpl_file_stream_new(zpl_file* file, zpl_allocator allocator);

/**
 * Opens a memory stream over an existing buffer
 * @param  file
 * @param  allocator
 * @param  buffer   Memory to create stream from
 * @param  size     Buffer's size
 * @param  flags
 */
ZPL_DEF void zpl_file_stream_open(zpl_file* file, zpl_allocator allocator, zpl_u8 *buffer, zpl_isize size, zpl_file_stream_flags flags);

extern zpl_file_operations const zpl_memory_file_operations;

//! @}

ZPL_END_C_DECLS
