#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "../data/test.json5");

    zpl_json_object root = {0};

    u8 err;
    zpl_json_parse(&root, fc.size, (char *const)fc.data, zpl_heap_allocator(), true, &err);

    zpl_json_object *replace = NULL;
    replace = zpl_json_find(&root, "replace_me", false);

    if (replace != NULL)
    {
        zpl_printf("Field was found! Current value: %ld\nReplacing with an array!\n", replace->integer);

        replace->type = ZPL_JSON_TYPE_ARRAY;
        zpl_array_init(replace->nodes, replace->backing);

        for (size_t i = 0; i < 5; i++)
        {
            zpl_json_object *o = zpl_json_add(replace, NULL, ZPL_JSON_TYPE_INTEGER);

            if (o) {
                o->integer = (i64)i+1;
            }
        }

        replace->name = "i_am_replaced ";
    }

    zpl_json_object *first = zpl_json_add_at(&root, 0, "first", ZPL_JSON_TYPE_STRING);

    if (first)
    {
        first->string = "I am first!";
        first->assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
    }
    

    zpl_printf("Error code: %d\n", err);

    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);

    zpl_json_free(&root);

    zpl_file_free_contents(&fc);
    return 0;
}
