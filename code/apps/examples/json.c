#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JSON
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/test.json5");

    zpl_json_object root = {0};

    zpl_u8 err;
    zpl_json_parse(&root, (char *)fc.data, zpl_heap_allocator(), &err);

    zpl_json_object *replace = NULL;
    replace = zpl_ast_find(&root, "replace_me", false);

    if (replace != NULL)
    {
        zpl_printf("Field was found! Current value: %ld\nReplacing with an array!\n", (long)replace->integer);
        zpl_ast_set_arr(replace, "i_am_replaced", root.backing);

        for (size_t i = 0; i < 5; i++)
            zpl_ast_inset_int(replace, NULL, (zpl_i64)i+1);
    }

    zpl_json_object *first = zpl_ast_alloc_at(&root, 0);

    if (first) {
        zpl_ast_set_str(first, "first", "I am first!");
        first->assign_style = ZPL_AST_ASSIGN_STYLE_EQUALS;
    }

    zpl_printf("Error code: %d\n", err);
    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);
    zpl_json_free(&root);
    zpl_file_free_contents(&fc);
    return 0;
}
