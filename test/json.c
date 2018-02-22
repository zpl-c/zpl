#define ZPL_IMPLEMENTATION
#define ZPLJ_IMPLEMENTATION
#include <zpl.h>
#include <zpl_json.h>


#define ind(x) for (int i = 0; i < x; ++i) zpl_printf(" ");

void dump_json_contents(zplj_object_t *o, isize indent);

void dump_value(zplj_object_t *o, isize indent, b32 is_inline, b32 is_last) {
    zplj_object_t *node = o;
    indent+=4;

    if (!is_inline) {
        ind(indent);
        switch(node->name_style) {
            case zplj_name_style_double_quote_ev: {
                zpl_printf("\"%s\": ", node->name);
            }break;

            case zplj_name_style_single_quote_ev: {
                zpl_printf("\'%s\': ", node->name);
            }break;

            case zplj_name_style_no_quotes_ev: {
                zpl_printf("%s: ", node->name);
            }break;
        }

    }

    switch (node->type) {
        case zplj_type_string_ev: {
            zpl_printf("\"%s\"", node->string);
        }break;

        case zplj_type_multistring_ev: {
            zpl_printf("`%s`", node->string);
        }break;

        case zplj_type_array_ev: {
            zpl_printf("[");
            isize elemn = zpl_array_count(node->elements);
            for (int j = 0; j < elemn; ++j) {
                dump_value(node->elements + j, -4, true, true);

                if (j < elemn-1) {
                    zpl_printf(", ");
                }
            }
            zpl_printf("]");
        }break;

        case zplj_type_integer_ev: {
            zpl_printf("%lld", node->integer);
        }break;

        case zplj_type_real_ev: {
            zpl_printf("%.3llf", node->real);
        }break;

        case zplj_type_object_ev: {
            dump_json_contents(node, indent);
        }break;

        case zplj_type_constant_ev: {
            /**/ if (node->constant == zplj_constant_true_ev) {
                zpl_printf("true");
            }
            else if (node->constant == zplj_constant_false_ev) {
                zpl_printf("false");
            }
            else if (node->constant == zplj_constant_null_ev) {
                zpl_printf("null");
            }
        }break;
    }

    if (!is_inline) {

        if (!is_last) {
            zpl_printf(",\n");
        }
        else {
            zpl_printf("\n");
        }
    }
}

void dump_json_contents(zplj_object_t *o, isize indent) {
    ind(indent-4);
    zpl_printf("{\n");
    isize cnt = zpl_array_count(o->nodes);

    for (int i = 0; i < cnt; ++i) {
        if (i < cnt-1) {
            dump_value(o->nodes + i, indent, false, false);
        }
        else {
            dump_value(o->nodes + i, indent, false, true);
        }
    }

    ind(indent);

    if (indent > 0) {
        zpl_printf("}");
    }
    else {
        zpl_printf("}\n");
    }
}

#undef ind

int main(void) {

    zpl_file_t file;
    zpl_file_open(&file, "test.json");
    isize file_size = zpl_file_size(&file);
    char *content = zpl_malloc(file_size+1);
    zpl_file_read(&file, content, file_size);
    content[file_size] = 0;
    zpl_file_close(&file);


    zplj_object_t root = {0};

    u8 err;
    zplj_parse(&root, file_size, content, zpl_heap_allocator(), true, &err);

    zpl_printf("Error code: %d\n", err);

    dump_json_contents(&root, 0);

    zplj_free(&root);

    zpl_mfree(content);
    return 0;
}
