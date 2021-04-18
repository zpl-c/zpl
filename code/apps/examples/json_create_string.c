#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JSON
#include <zpl.h>

int main(void) {
    zpl_json_object root = {0};
    zpl_ast_make_branch(&root, zpl_heap(), "<root>" /* unused for root object */, ZPL_AST_TYPE_OBJECT);

    zpl_random rng={0};
    zpl_random_init(&rng);

    for (size_t i = 0; i < 16000000; i++)
    {
        zpl_json_object *o = zpl_ast_alloc(&root);

        if (o) {
            zpl_ast_make_leaf(o, zpl_string_sprintf_buf(zpl_heap(), "field%lld\t", i), ZPL_AST_TYPE_INTEGER);
            o->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            o->assign_style = ZPL_AST_ASSIGN_STYLE_LINE;
            o->delim_style = ZPL_AST_DELIM_STYLE_NEWLINE;

            o->integer = zpl_random_gen_u64(&rng) & i;
        }
    }

    zpl_string a = zpl_json_write_string(zpl_heap(), &root, 0);
    zpl_printf("%s\n", a);
    zpl_string_free(a);
    zpl_json_free(&root);
    return 0;
}
