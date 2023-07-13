#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_PARSER
#include <zpl.h>

typedef zpl_adt_node zpl_uri_object;

typedef enum zpl_uri_error {
    ZPL_URI_ERROR_NONE,
    ZPL_URI_ERROR_INTERNAL,
} zpl_uri_error;

zpl_u8 zpl_uri_parse(zpl_adt_node* root, char *text, zpl_allocator a) {
    zpl_u8 err_code = ZPL_URI_ERROR_NONE;
    ZPL_ASSERT_NOT_NULL(root);
    ZPL_ASSERT_NOT_NULL(text);
    zpl_zero_item(root);
    text = zpl_str_trim(text, true);
}

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/uri_example.txt");
    
    zpl_uri_object root = {0};
    
    zpl_u8 err;
    err = zpl_json_parse(&root, (char *)fc.data, zpl_heap_allocator());
    
    zpl_json_object *replace = NULL;
    replace = zpl_adt_find(&root, "replace_me", false);
    
    if (replace != NULL)
    {
        zpl_printf("Field was found! Current value: %ld\nReplacing with an array!\n", (long)replace->integer);
        zpl_adt_set_arr(replace, "i_am_replaced", zpl_heap());
        
        for (size_t i = 0; i < 5; i++)
            zpl_adt_append_int(replace, NULL, (zpl_i64)i+1);
    }
    
    zpl_json_object *first = zpl_adt_alloc_at(&root, 0);
    
    if (first) {
        zpl_adt_set_str(first, "first", "I am first!");
        first->assign_style = ZPL_ADT_ASSIGN_STYLE_EQUALS;
    }
    
    zpl_printf("Error code: %d\n", err);
    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);
    zpl_json_free(&root);
    zpl_file_free_contents(&fc);
    return 0;
}
