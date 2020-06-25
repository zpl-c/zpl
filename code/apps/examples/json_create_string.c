#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_JSON
#include <zpl.h>

int main(void) {
    zpl_json_object root = {0};
    zpl_json_init_node(&root, zpl_heap(), "<root>" /* unused for root object */, ZPL_JSON_TYPE_OBJECT);

    zpl_random rng={0};
    zpl_random_init(&rng);

    for (size_t i = 0; i < 32; i++)
    {
        zpl_json_object *o = zpl_json_add(&root, zpl_string_sprintf_buf(zpl_heap(), "field%lld", i), ZPL_JSON_TYPE_INTEGER);

        if (o) {
            o->integer = zpl_random_gen_u64(&rng) & i;
        }
    }

    zpl_string a = zpl_json_write_string(zpl_heap(), &root, 0);
    zpl_printf("%s\n", a);
    zpl_string_free(a);
    zpl_json_free(&root);
    return 0;
}
