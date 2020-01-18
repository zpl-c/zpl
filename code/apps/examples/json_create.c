#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/test.json5");

    zpl_json_object root = {0};
    root.cfg_mode = 1;
    zpl_json_init_node(&root, zpl_heap(), "<root>" /* unused for root object */, ZPL_JSON_TYPE_OBJECT);

    zpl_random rng={0};
    zpl_random_init(&rng);

    for (size_t i = 0; i < 16000000; i++)
    {
        zpl_json_object *o = zpl_json_add(&root, zpl_string_sprintf_buf(zpl_heap(), "field%lld\t", i), ZPL_JSON_TYPE_INTEGER);

        if (o) {
            o->name_style = ZPL_JSON_NAME_STYLE_NO_QUOTES;
            o->assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
            o->delim_style = ZPL_JSON_DELIM_STYLE_NEWLINE;

            o->integer = zpl_random_gen_u64(&rng) & i;
        }
    }

    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);

    zpl_json_free(&root);

    zpl_file_free_contents(&fc);
    return 0;
}
