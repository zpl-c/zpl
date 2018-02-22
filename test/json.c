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
            case ZPLJ_NAME_STYLE_DOUBLE_QUOTE: {
                zpl_printf("\"%s\": ", node->name);
            }break;

            case ZPLJ_NAME_STYLE_SINGLE_QUOTE: {
                zpl_printf("\'%s\': ", node->name);
            }break;

            case ZPLJ_NAME_STYLE_NO_QUOTES: {
                zpl_printf("%s: ", node->name);
            }break;
        }

    }

    switch (node->type) {
        case ZPLJ_TYPE_STRING: {
            zpl_printf("\"%s\"", node->string);
        }break;

        case ZPLJ_TYPE_MULTISTRING: {
            zpl_printf("`%s`", node->string);
        }break;

        case ZPLJ_TYPE_ARRAY: {
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

        case ZPLJ_TYPE_INTEGER: {
            zpl_printf("%ld", node->integer);
        }break;

        case ZPLJ_TYPE_REAL: {
            /**/ if (node->props & ZPLJ_PROPS_NAN) {
                zpl_printf("NAN");
            }
            else if (node->props & ZPLJ_PROPS_INFINITY) {
                zpl_printf("INFINITY");
            }
            else {
                zpl_printf("%.3lf", node->real);
            }
        }break;

        case ZPLJ_TYPE_OBJECT: {
            dump_json_contents(node, indent);
        }break;

        case ZPLJ_TYPE_CONSTANT: {
            /**/ if (node->constant == ZPLJ_CONST_TRUE) {
                zpl_printf("true");
            }
            else if (node->constant == ZPLJ_CONST_FALSE) {
                zpl_printf("false");
            }
            else if (node->constant == ZPLJ_CONST_NULL) {
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
    zpl_file_open(&file, "../data/test.json5");
    isize file_size = zpl_file_size(&file);
    char *content = (char *)zpl_malloc(file_size+1);
    zpl_file_read(&file, content, file_size);
    content[file_size] = 0;
    zpl_file_close(&file);


    zplj_object_t root = {};

    u8 err;
    zplj_parse(&root, file_size, content, zpl_heap_allocator(), true, &err);

    zpl_printf("Error code: %d\n", err);

    dump_json_contents(&root, 0);

    zplj_free(&root);

    zpl_mfree(content);
    return 0;
}
