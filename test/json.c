#define ZPL_IMPLEMENTATION
#include <zpl.h>

#define ind(x) for (int i = 0; i < x; ++i) zpl_printf(" ");

void dump_json_contents(zpl_json_object_t *o, isize indent);

void dump_value(zpl_json_object_t *o, isize indent, b32 is_inline, b32 is_last) {
    zpl_json_object_t *node = o;
    indent+=4;

    if (!is_inline) {
        ind(indent);
        switch(node->name_style) {
            case ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE: {
                zpl_printf("\"%s\": ", node->name);
            }break;

            case ZPL_JSON_NAME_STYLE_SINGLE_QUOTE: {
                zpl_printf("\'%s\': ", node->name);
            }break;

            case ZPL_JSON_NAME_STYLE_NO_QUOTES: {
                zpl_printf("%s: ", node->name);
            }break;
        }

    }

    switch (node->type) {
        case ZPL_JSON_TYPE_STRING: {
            zpl_printf("\"%s\"", node->string);
        }break;

        case ZPL_JSON_TYPE_MULTISTRING: {
            zpl_printf("`%s`", node->string);
        }break;

        case ZPL_JSON_TYPE_ARRAY: {
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

        case ZPL_JSON_TYPE_INTEGER: {
            zpl_printf("%ld", node->integer);
        }break;

        case ZPL_JSON_TYPE_REAL: {
            /**/ if (node->props == ZPL_JSON_PROPS_NAN) {
                zpl_printf("NaN");
            }
            else if (node->props == ZPL_JSON_PROPS_NAN_NEG) {
                zpl_printf("-NaN");
            }
            else if (node->props == ZPL_JSON_PROPS_INFINITY) {
                zpl_printf("Infinity");
            }
            else if (node->props == ZPL_JSON_PROPS_INFINITY_NEG) {
                zpl_printf("-Infinity");
            }
            else if (node->props == ZPL_JSON_PROPS_IS_EXP) {
                zpl_printf("%ld.%lde%c%ld", node->base, node->base2, node->exp_neg ? '-' : '+', node->exp);
            }
            else {
                if (node->frac == 0) {
                    zpl_printf("%.1lf", node->real);
                }
                else {
                    zpl_printf("%.*lf", node->frac, node->real);
                }
            }
        }break;

        case ZPL_JSON_TYPE_OBJECT: {
            dump_json_contents(node, indent);
        }break;

        case ZPL_JSON_TYPE_CONSTANT: {
            /**/ if (node->constant == ZPL_JSON_CONST_TRUE) {
                zpl_printf("true");
            }
            else if (node->constant == ZPL_JSON_CONST_FALSE) {
                zpl_printf("false");
            }
            else if (node->constant == ZPL_JSON_CONST_NULL) {
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

void dump_json_contents(zpl_json_object_t *o, isize indent) {
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
    zpl_file_open(&file, "../data/test.json5");
    isize file_size = zpl_file_size(&file);
    char *content = (char *)zpl_malloc(file_size+1);
    zpl_file_read(&file, content, file_size);
    content[file_size] = 0;
    zpl_file_close(&file);


    zpl_json_object root = {0};

    u8 err;
    zpl_json_parse(&root, file_size, content, zpl_heap_allocator(), true, &err);

    zpl_printf("Error code: %d\n", err);

    dump_json_contents(&root, 0);

    zpl_json_free(&root);

    zpl_mfree(content);
    return 0;
}
