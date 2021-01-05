#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif

MODULE(stream, {
    const char test[] = "Hello World!";
    zpl_isize len = zpl_strlen(test);
    zpl_file f;

    IT("can read data from the stream", {
        char buf[80] = {0};
        zpl_file_stream_open(&f, zpl_heap(), cast(zpl_u8*) test, len, 0);
        zpl_file_read(&f, buf, len);
        zpl_file_close(&f);
        STREQUALS(buf, test);
    });

    IT("can append data to the stream", {
        const char hello2yello[] = "Yello";
        zpl_file_stream_open(&f, zpl_heap(), cast(zpl_u8*) test, len, ZPL_FILE_STREAM_CLONE_WRITABLE);
        zpl_file_write_at(&f, hello2yello, zpl_strlen(hello2yello), 0);
        zpl_file_close(&f);
        STREQUALS((char*)zpl_file_stream_buf(&f, 0), "Yello World!");
    });

    IT("can create a new memory stream", {
        const char message[] = "Ryan started the fire!";
        zpl_isize msglen = zpl_strlen(message);
        zpl_file_stream_new(&f, zpl_heap());
        zpl_file_write(&f, message, msglen);
        zpl_file_close(&f);
        STREQUALS((char*)zpl_file_stream_buf(&f, 0), message);
    });

    IT("can overwrite an existing buffer directly", {
        zpl_string hello = zpl_string_make(zpl_heap(), "hello");
        const char olleh[] = "!dlrow olleH";
        const zpl_isize wordlen = zpl_strlen(hello);
        zpl_file_stream_open(&f, zpl_heap(), cast(zpl_u8*) hello, wordlen, ZPL_FILE_STREAM_WRITABLE);
        zpl_file_write_at(&f, olleh, zpl_strlen(olleh), 0);
        zpl_file_close(&f);
        zpl_string_free(hello);
        STRCEQUALS((char*)zpl_file_stream_buf(&f, 0), olleh, wordlen);
    });
});
