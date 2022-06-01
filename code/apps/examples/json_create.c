#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_PARSER
#include <zpl.h>

int main(void) {
    zpl_json_object root = {0};
    root.cfg_mode = 1;
    zpl_adt_make_branch(&root, zpl_heap(), "<root>" /* unused for root object */, 0);

    zpl_random rng={0};
    zpl_random_init(&rng);

    for (size_t i = 0; i < 16000000; i++)
    {
        zpl_json_object *o = zpl_adt_alloc(&root);

        if (o) {
            zpl_adt_make_leaf(o, zpl_string_sprintf_buf(zpl_heap(), "field%lld\t", i), ZPL_ADT_TYPE_INTEGER);
            o->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            o->assign_style = ZPL_ADT_ASSIGN_STYLE_LINE;
            o->delim_style = ZPL_ADT_DELIM_STYLE_NEWLINE;

            o->integer = zpl_random_gen_u64(&rng) & i;
        }
    }

    zpl_json_write(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), &root, 0);
    zpl_json_free(&root);
    return 0;
}
