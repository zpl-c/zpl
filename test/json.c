#define ZPL_IMPLEMENTATION
#define ZPL_JSON_IMPLEMENTATION
#include <zpl.h>
#include <zpl_json.h>

char *source = "\"+ľščťžýáíé=\": true, \"huge\": 2.23e-2, \"array\": [1,2,3,4,5],     \"hello\": \"world\", \"abc\": 42.67, \"children\" : { \"a\": 1, \"b\": 2 }";

#define ind(x) for (int i = 0; i < x; ++i) zpl_printf(" ");

void dump_json_contents(zpl_json_object_t *o, isize indent);

void dump_value(zpl_json_object_t *o, isize indent, b32 is_inline) {
    zpl_json_object_t *node = o;
    indent+=4;
    
    if (!is_inline) {
        ind(indent);
        zpl_printf("\"%s\": ", node->name);
    }
    
    switch (node->type) {
        case zpl_json_type_string_ev: {
            zpl_printf("\"%s\"", node->string);
        }break;
        
        case zpl_json_type_array_ev: {
            zpl_printf("[");
            isize elemn = zpl_array_count(node->elements);
            for (int j = 0; j < elemn; ++j) {
                dump_value(node->elements + j, -4, true);
                
                if (j < elemn-1) {
                    zpl_printf(", ");
                }
            }
            zpl_printf("]");
        }break;
        
        case zpl_json_type_integer_ev: {
            zpl_printf("%u", node->integer);
        }break;
        
        case zpl_json_type_real_ev: {
            zpl_printf("%f", node->real);
        }break;
        
        case zpl_json_type_object_ev: {
            dump_json_contents(node, indent);
        }break;
        
        case zpl_json_type_constant_ev: {
            /**/ if (node->constant == zpl_json_constant_true_ev) {
                zpl_printf("true");
            }
            else if (node->constant == zpl_json_constant_false_ev) {
                zpl_printf("false");
            }
            else if (node->constant == zpl_json_constant_null_ev) {
                zpl_printf("null");
            }
        }break;
    }
    
    if (!is_inline) {
        zpl_printf(",\n");
    }
}

void dump_json_contents(zpl_json_object_t *o, isize indent) {
    ind(indent-4);
    zpl_printf("{\n");
    
    for (int i = 0; i < zpl_array_count(o->nodes); ++i) {
        dump_value(o->nodes + i, indent, false);
    }
    
    ind(indent);
    zpl_printf("},\n");
}

#undef ind

int main(void) {

    zpl_json_object_t root = {0};
    char *modified = zpl_json_parse(&root, zpl_strlen(source), source, zpl_heap_allocator());
    
    dump_json_contents(&root, 0);
    
    zpl_json_free(&root, modified);
    
    return 0;
}
