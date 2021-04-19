// file: source/parsers/csv.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#ifdef ZPL_CSV_DEBUG
#define ZPL_CSV_ASSERT(msg) ZPL_PANIC(msg)
#else
#define ZPL_CSV_ASSERT(msg)
#endif


ZPL_BEGIN_C_DECLS

zpl_u8 zpl_csv_parse_delimiter(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header, char delim) {
    zpl_csv_error err = ZPL_CSV_ERROR_NONE;
    ZPL_ASSERT_NOT_NULL(root);
    ZPL_ASSERT_NOT_NULL(text);
    zpl_zero_item(root);
    zpl_ast_make_branch(root, allocator, NULL, has_header ? ZPL_AST_TYPE_OBJECT : ZPL_AST_TYPE_ARRAY);
    char *p = text, *b = p, *e = p;
    zpl_isize colc = 0, total_colc = 0;

    do {
        char d = 0;
        p = zpl_str_trim(p, false);
        if (*p == 0) break;
        zpl_ast_node row_item = {0};
        row_item.type = ZPL_AST_TYPE_STRING;

        if (*p == '"') {
            p = b = e = p+1;
            row_item.string = b;
            do {
                e = zpl_str_skip(e, '"');
                if (*(e+1) == '"') {
                    e += 2;
                }
                else break;
            } while (*e);
            if (*e == 0) {
                ZPL_CSV_ASSERT("unmatched quoted string");
                err = ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT;
                return err;
            }
            *e = 0;
            p = zpl_str_trim(e+1, true);
            d = *p;
        }
        else {
            b = e = p;
            row_item.string = b;
            row_item.name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            do {
                e++;
            } while (*e != delim && *e != '\n' && *e);
            if (*e) {
                p = zpl_str_trim(e, true);
                while (zpl_char_is_space(*(e-1))) { e--; }
                d = *p;
                *e = 0;
            }
        }

        if (colc >= zpl_array_count(root->nodes)) {
            zpl_ast_inset_arr(root, NULL);
        }

        zpl_array_append(root->nodes[colc].nodes, row_item);

        if (d == delim) {
            colc++;
            p++;
        }
        else if (d == '\n' || d == 0) {
            if (total_colc < colc) total_colc = colc;
            else if (total_colc != colc) {
                ZPL_CSV_ASSERT("mismatched rows");
                err = ZPL_CSV_ERROR_MISMATCHED_ROWS;
                return err;
            }
            colc = 0;
            p++;
        }
    } while(*p);

    if (zpl_array_count(root->nodes) == 0) {
        ZPL_CSV_ASSERT("unexpected end of input. stream is empty.");
        err = ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT;
        return err;
    }

    /* consider first row as a header. */
    if (has_header) {
        for (zpl_isize i = 0; i < zpl_array_count(root->nodes); i++) {
            zpl_csv_object *col = root->nodes + i;
            zpl_csv_object *hdr = col->nodes;
            col->name = hdr->string;
            zpl_array_remove_at(col->nodes, 0);
        }
    }

    return err;
}
void zpl_csv_free(zpl_csv_object *obj) {
    zpl_ast_destroy_branch(obj);
}

void zpl__csv_write_record(zpl_file *file, char const* text, zpl_u8 name_style) {
    switch (name_style) {
        case ZPL_AST_NAME_STYLE_DOUBLE_QUOTE: {
            zpl_fprintf(file, "\"%s\"", text);
        } break;

        case ZPL_AST_NAME_STYLE_NO_QUOTES: {
            zpl_fprintf(file, "%s", text);
        } break;
    }
}

void zpl_csv_write_delimiter(zpl_file *file, zpl_csv_object *obj, char delimiter) {
    ZPL_ASSERT_NOT_NULL(file);
    ZPL_ASSERT_NOT_NULL(obj);
    ZPL_ASSERT(obj->nodes);
    zpl_isize cols = zpl_array_count(obj->nodes);
    if (cols == 0) return;

    zpl_isize rows = zpl_array_count(obj->nodes[0].nodes);
    if (rows == 0) return;

    zpl_b32 has_headers = obj->nodes[0].name != NULL;

    if (has_headers) {
        for (zpl_isize i = 0; i < cols; i++) {
            zpl__csv_write_record(file, obj->nodes[i].name, obj->nodes[i].name_style);
            if (i+1 != cols) {
                zpl_fprintf(file, ",");
            }
        }
        zpl_fprintf(file, "\n");
    }

    for (zpl_isize r = 0; r < rows; r++) {
        for (zpl_isize i = 0; i < cols; i++) {
            zpl__csv_write_record(file, obj->nodes[i].nodes[r].string, obj->nodes[i].nodes[r].name_style);
            if (i+1 != cols) {
                zpl_fprintf(file, ",");
            }
        }
        zpl_fprintf(file, "\n");
    }
}

zpl_string zpl_csv_write_string_delimiter(zpl_allocator a, zpl_csv_object *obj, char delimiter) {
    zpl_file tmp;
    zpl_file_stream_new(&tmp, a);
    zpl_csv_write_delimiter(&tmp, obj, delimiter);
    zpl_isize fsize;
    zpl_u8* buf = zpl_file_stream_buf(&tmp, &fsize);
    zpl_string output = zpl_string_make_length(a, (char *)buf, fsize+1);
    zpl_file_close(&tmp);
    return output;
}

ZPL_END_C_DECLS
