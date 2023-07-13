#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_PARSER
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/uri_example.txt");
    
    zpl_uri_object root = {0};
    
    zpl_u8 err;
    err = zpl_uri_parse(&root, (char *)fc.data, zpl_heap_allocator());
    
    zpl_printf("Error code: %d\n", err);
    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);
    zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root);
    zpl_uri_free(&root);
    zpl_file_free_contents(&fc);
    zpl_printf("\n");

    {
        zpl_uri_object custom = {0};
        zpl_uri_init(&custom, "http://example.com", zpl_heap_allocator());
        zpl_adt_append_str(&custom, "foo", "bar");
        zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom, 0);
        zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom);
        zpl_uri_free(&custom);
        zpl_printf("\n");
    }

    {
        zpl_uri_object custom = {0};
        zpl_uri_init(&custom, NULL, zpl_heap_allocator());
        zpl_adt_append_str(&custom, "foo", "bar");
        zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom, 0);
        zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom);
        zpl_uri_free(&custom);
        zpl_printf("\n");
    }

    {
        zpl_uri_object custom = {0};
        zpl_uri_init(&custom, NULL, zpl_heap_allocator());
        zpl_adt_append_str(&custom, "foo", "");
        zpl_adt_append_str(&custom, "foo2", NULL);
        zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom, 0);
        zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom);
        zpl_uri_free(&custom);
        zpl_printf("\n");
    }

    {
        zpl_uri_object custom = {0};
        zpl_uri_parse(&custom, "?bar=foo", zpl_heap_allocator());
        zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom, 0);
        zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom);
        zpl_uri_free(&custom);
        zpl_printf("\n");
    }

    {
        zpl_uri_object custom = {0};
        zpl_uri_parse(&custom, "?bar=&foo=", zpl_heap_allocator());
        zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom, 0);
        zpl_uri_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &custom);
        zpl_uri_free(&custom);
        zpl_printf("\n");
    }
    return 0;
}
