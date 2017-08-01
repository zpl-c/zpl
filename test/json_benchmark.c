//
// Requires presence of jeopardy.json file, which can be received at: https://www.reddit.com/r/datasets/comments/1uyd0t/200000_jeopardy_questions_in_a_json_file/
//
// It took 162 milliseconds to process this JSON file on my computer.
//
#define ZPL_IMPLEMENTATION
#define ZPL_JSON_IMPLEMENTATION
#include <zpl.h>
#include <zpl_json.h>

char *source = "/* this is a comment */ \"+ľščťžýáíé=\": true, \"empty\": [], \"huge\": 2.2239333e5, // Hello, new comment \n \"array\": [+1,2,-3,4,5],     \"hello\": \"world\", \"abc\": 42.67, \"children\" : { \"a\": 1, \"b\": 2 }";

#define ind(x) for (int i = 0; i < x; ++i) printf(" ");

void dump_json_contents(zpl_json_object_t *o, isize indent);

void dump_value(zpl_json_object_t *o, isize indent, b32 is_inline, b32 is_last) {
    zpl_json_object_t *node = o;
    indent+=4;
    
    if (!is_inline) {
        ind(indent);
        printf("\"%s\": ", node->name);
    }
    
    switch (node->type) {
        case zpl_json_type_string_ev: {
            printf("\"%s\"", node->string);
        }break;
        
        case zpl_json_type_array_ev: {
            printf("[");
            isize elemn = zpl_array_count(node->elements);
            for (int j = 0; j < elemn; ++j) {
                dump_value(node->elements + j, -4, true, true);
                
                if (j < elemn-1) {
                    printf(", ");
                }
            }
            printf("]");
        }break;
        
        case zpl_json_type_integer_ev: {
            printf("%ld", node->integer);
        }break;
        
        case zpl_json_type_real_ev: {
            printf("%.3f", node->real);
        }break;
        
        case zpl_json_type_object_ev: {
            dump_json_contents(node, indent);
        }break;
        
        case zpl_json_type_constant_ev: {
            /**/ if (node->constant == zpl_json_constant_true_ev) {
                printf("true");
            }
            else if (node->constant == zpl_json_constant_false_ev) {
                printf("false");
            }
            else if (node->constant == zpl_json_constant_null_ev) {
                printf("null");
            }
        }break;
    }
    
    if (!is_inline) {
        
        if (!is_last) {
            printf(",\n");
        }
        else {
            printf("\n");
        }
    }
}

void dump_json_contents(zpl_json_object_t *o, isize indent) {
    ind(indent-4);
    printf("{\n");
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
        printf("}");
    }
    else {
        printf("}\n");
    }
}

#undef ind

int main(void) {

    zpl_file_t file;
    zpl_file_open(&file, "jeopardy.json");
    //zpl_file_open(&file, "rows.json");
    //zpl_file_open(&file, "test.json");
    isize file_size = zpl_file_size(&file);
    char *content = zpl_malloc(file_size+1);
    zpl_file_read(&file, content, file_size);
    content[file_size] = 0;
    zpl_file_close(&file);
    
    zpl_json_object_t root = {0};
    char *modified = zpl_json_parse(&root, file_size, content, zpl_heap_allocator(), false);
    //char *modified = zpl_json_parse(&root, zpl_strlen(source), source, zpl_heap_allocator(), true);
    
    printf("No. of nodes: %td\n", zpl_array_count(root.nodes[0].elements));
    
    printf("Category: %s, air date: %s\nQuestion: %s\n", root.nodes[0].elements[29].nodes[0].string,
           root.nodes[0].elements[29].nodes[1].string,
           root.nodes[0].elements[29].nodes[2].string);
    
    //dump_json_contents(&root, 0);
    
    zpl_json_free(&root, modified);
    
    zpl_mfree(content);
    return 0;
}
