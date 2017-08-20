#define ZPL_IMPLEMENTATION
#include <zpl.h>

ZPL_ASYNC_FILE_CB(test_read_finished) {
    // NOTE(ZaKlaus): Print first 64 characters
    zpl_printf("Size: %d\n\n%*.s", file->size, 64, cast(char *)file->data);
}

int main() {
    zpl_file_t test_file = {0};
    
    zpl_file_open(&test_file, "../include/zpl.h");
    {
        zpl_async_file_read(&test_file, test_read_finished);
        zpl_printf("We should read at this moment!\n");
    }
    zpl_file_close(&test_file);
    
    zpl_sleep_ms(4000);
    
    return 0;
}