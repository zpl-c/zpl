#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_PARSER
#include <zpl.h>

int main(void) {
    zpl_file_contents fc;
    fc = zpl_file_read_contents(zpl_heap(), true, "misc/data/glsl_diffuse.json5");

    zpl_json_object root = {0};

    zpl_u8 err;
    err = zpl_json_parse(&root, (char *)fc.data, zpl_heap_allocator());
    zpl_printf("Error code: %d\n", err);

    zpl_json_object *nested_node_variant = zpl_adt_get(&root, "layer1/layer2/layer3");
    ZPL_ASSERT_NOT_NULL(nested_node_variant);
    ZPL_ASSERT(nested_node_variant->integer == 42);

    zpl_json_object *def_value_node = zpl_adt_get(&root, "uniforms/[name=distort]/layout/[pos=y]/default_value");
    ZPL_ASSERT_NOT_NULL(def_value_node);

    zpl_json_object *num_42_node = zpl_adt_get(&root, "numbers/[value=42]");
    ZPL_ASSERT_NOT_NULL(num_42_node);

    zpl_json_object *arr_idx_node = zpl_adt_get(&root, "array/3");
    ZPL_ASSERT_NOT_NULL(arr_idx_node);
    ZPL_ASSERT(arr_idx_node->integer == 4);

    zpl_json_object *arr_val_node = zpl_adt_get(&root, "array/[4]");
    ZPL_ASSERT_NOT_NULL(arr_val_node);

    zpl_json_free(&root);
    zpl_file_free_contents(&fc);
    return 0;
}
