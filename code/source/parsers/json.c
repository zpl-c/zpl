// file: source/parsers/json.c

////////////////////////////////////////////////////////////////
//
// JSON5 Parser
//
//

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#ifdef ZPL_JSON_DEBUG
#define ZPL_JSON_ASSERT ZPL_ASSERT(0)
#else
#define ZPL_JSON_ASSERT
#endif

#include <math.h> /* needed for INFINITY and NAN */

ZPL_BEGIN_C_DECLS

char *zpl__json_parse_object(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
char *zpl__json_parse_array(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
char *zpl__json_parse_value(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
char *zpl__json_trim(char *base, zpl_b32 skip_newline);
void zpl__json_write_value(zpl_file *f, zpl_ast_node *o, zpl_ast_node *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last);
#define zpl___ind(x) if (x > 0) zpl_fprintf(f, "%*r", x, ' ');

zpl_u8 zpl_json_parse(zpl_ast_node *root, char *source, zpl_allocator a) {
    zpl_u8 err_code = ZPL_JSON_ERROR_NONE;

    if (!root || !source) {
        ZPL_JSON_ASSERT;
        err_code = ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL;
        return err_code;
    }

    char *dest = (char *)source;

    zpl_ast_node root_ = { 0 };

    dest = zpl__json_trim(dest, false);

    if (!zpl_strchr("{[", *dest)) { root_.cfg_mode = true; }
    if (*dest == '[') {  root_.type = ZPL_AST_TYPE_ARRAY; }

    char *endp = NULL;

    endp = zpl__json_parse_object(&root_, dest, a, &err_code);

    if (!root_.cfg_mode && endp == NULL) {
        err_code = ZPL_JSON_ERROR_INVALID_VALUE;
    }

    *root = root_;
    return err_code;
}

void zpl_json_free(zpl_ast_node *obj) {
    zpl_ast_destroy_branch(obj);
}

void zpl_json_write(zpl_file *f, zpl_ast_node *o, zpl_isize indent) {
    if (!o)
        return;

    zpl___ind(indent - 4);
    if (!o->cfg_mode)
        zpl_fprintf(f, "{\n");
    else {
        indent -= 4;
    }

    if (o->nodes) {
        zpl_isize cnt = zpl_array_count(o->nodes);

        for (int i = 0; i < cnt; ++i) {
            zpl__json_write_value(f, o->nodes + i, o, indent, false, !(i < cnt - 1));
        }
    }

    zpl___ind(indent);

    if (indent > 0) {
        zpl_fprintf(f, "}");
    } else {
        if (!o->cfg_mode) zpl_fprintf(f, "}\n");
    }
}

zpl_string zpl_json_write_string(zpl_allocator a, zpl_ast_node *obj, zpl_isize indent) {
    zpl_file tmp;
    zpl_file_stream_new(&tmp, a);
    zpl_json_write(&tmp, obj, indent);
    zpl_isize fsize;
    zpl_u8* buf = zpl_file_stream_buf(&tmp, &fsize);
    zpl_string output = zpl_string_make_length(a, (char *)buf, fsize+1);
    zpl_file_close(&tmp);
    return output;
}

/* private */

static ZPL_ALWAYS_INLINE zpl_b32 zpl__json_is_assign_char(char c) { return !!zpl_strchr(":=|", c); }
static ZPL_ALWAYS_INLINE zpl_b32 zpl__json_is_delim_char(char c) { return !!zpl_strchr(",|\n", c); }

#define jx(x) !zpl_char_is_hex_digit(str[x])
ZPL_ALWAYS_INLINE zpl_b32 zpl__json_validate_name(char const *str, char *err) {
    while (*str) {
        if ((str[0] == '\\' && !zpl_char_is_control(str[1])) &&
            (str[0] == '\\' && jx(1) && jx(2) && jx(3) && jx(4))) {
            if (err) *err = *str;
            return false;
        }

        ++str;
    }

    return true;
}
#undef jx

void zpl__json_write_value(zpl_file *f, zpl_ast_node *o, zpl_ast_node *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last) {
    zpl_ast_node *node = o;
    indent += 4;

    if (!is_inline) {
        zpl___ind(indent);
        switch (node->name_style) {
            case ZPL_AST_NAME_STYLE_DOUBLE_QUOTE: {
                zpl_fprintf(f, "\"%s\"", node->name);
            } break;

            case ZPL_AST_NAME_STYLE_SINGLE_QUOTE: {
                zpl_fprintf(f, "\'%s\'", node->name);
            } break;

            case ZPL_AST_NAME_STYLE_NO_QUOTES: {
                zpl_fprintf(f, "%s", node->name);
            } break;
        }

        if (o->assign_style == ZPL_AST_ASSIGN_STYLE_COLON)
            zpl_fprintf(f, ": ");
        else {
            zpl___ind(zpl_max(o->assign_line_width, 1));

            if (o->assign_style == ZPL_AST_ASSIGN_STYLE_EQUALS)
                zpl_fprintf(f, "= ");
            else if (o->assign_style == ZPL_AST_ASSIGN_STYLE_LINE) {
                zpl_fprintf(f, "| ");
            }
        }

    }

    switch (node->type) {
        case ZPL_AST_TYPE_STRING: {
            zpl_fprintf(f, "\"%s\"", node->string);
        } break;

        case ZPL_AST_TYPE_MULTISTRING: {
            zpl_fprintf(f, "`%s`", node->string);
        } break;

        case ZPL_AST_TYPE_ARRAY: {
            zpl_fprintf(f, "[");
            zpl_isize elemn = zpl_array_count(node->nodes);
            for (int j = 0; j < elemn; ++j) {
                if ((node->nodes + j)->type == ZPL_AST_TYPE_OBJECT || (node->nodes + j)->type == ZPL_AST_TYPE_ARRAY) {
                    zpl__json_write_value(f, node->nodes + j, o, 0, true, true);
                } else {
                    zpl__json_write_value(f, node->nodes + j, o, -4, true, true);
                }

                if (j < elemn - 1) { zpl_fprintf(f, ", "); }
            }
            zpl_fprintf(f, "]");
        } break;

        case ZPL_AST_TYPE_INTEGER: {
            if (node->props == ZPL_AST_PROPS_IS_HEX) {
                zpl_fprintf(f, "0x%llx", (long long)node->integer);
            } else {
                zpl_fprintf(f, "%lld", (long long)node->integer);
            }
        } break;

        case ZPL_AST_TYPE_REAL: {
            if (node->props == ZPL_AST_PROPS_NAN) {
                zpl_fprintf(f, "NaN");
            } else if (node->props == ZPL_AST_PROPS_NAN_NEG) {
                zpl_fprintf(f, "-NaN");
            } else if (node->props == ZPL_AST_PROPS_INFINITY) {
                zpl_fprintf(f, "Infinity");
            } else if (node->props == ZPL_AST_PROPS_INFINITY_NEG) {
                zpl_fprintf(f, "-Infinity");
            } else if (node->props == ZPL_AST_PROPS_IS_EXP) {
                zpl_fprintf(f, "%lld.%0*d%llde%c%lld", (long long)node->base, node->base2_offset, 0, (long long)node->base2, node->exp_neg ? '-' : '+',
                            (long long)node->exp);
            } else if (node->props == ZPL_AST_PROPS_IS_PARSED_REAL) {
                if (!node->lead_digit)
                    zpl_fprintf(f, ".%0*d%lld", node->base2_offset, 0, (long long)node->base2);
                else
                    zpl_fprintf(f, "%lld.%0*d%lld", (long long int)node->base2_offset, 0, (int)node->base, (long long)node->base2);
            } else {
                zpl_fprintf(f, "%f", node->real);
            }
        } break;

        case ZPL_AST_TYPE_OBJECT: {
            zpl_json_write(f, node, indent);
        } break;

        case ZPL_AST_TYPE_CONSTANT: {
            if (node->constant == ZPL_AST_CONST_TRUE) {
                zpl_fprintf(f, "true");
            } else if (node->constant == ZPL_AST_CONST_FALSE) {
                zpl_fprintf(f, "false");
            } else if (node->constant == ZPL_AST_CONST_NULL) {
                zpl_fprintf(f, "null");
            }
        } break;
    }

    if (!is_inline) {

        if (o->delim_style != ZPL_AST_DELIM_STYLE_COMMA)
        {
            if (o->delim_style == ZPL_AST_DELIM_STYLE_NEWLINE)
                zpl_fprintf(f, "\n");
            else if (o->delim_style == ZPL_AST_DELIM_STYLE_LINE)
            {
                zpl___ind(o->delim_line_width);
                zpl_fprintf(f, "|\n");
            }
        }
        else
        {
            if (!is_last) {
                zpl_fprintf(f, ",\n");
            } else {
                zpl_fprintf(f, "\n");
            }
        }
    }
}

char *zpl__json_parse_array(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;

    obj->type = ZPL_AST_TYPE_ARRAY;
    zpl_array_init(obj->nodes, a);
    obj->backing = a;

    while (*p) {
        p = zpl__json_trim(p, false);

        if (p && *p == ']') {
            return p;
        }

        zpl_ast_node elem = { 0 };
        elem.backing = a;
        p = zpl__json_parse_value(&elem, p, a, err_code);

        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

        zpl_array_append(obj->nodes, elem);

        p = zpl__json_trim(p, false);

        if (*p == ',') {
            ++p;
            continue;
        } else {
            if (*p != ']') {
                if (err_code) { *err_code = ZPL_JSON_ERROR_INVALID_VALUE; }
            }
            return p;
        }
    }

    if (err_code) { *err_code = ZPL_JSON_ERROR_INVALID_VALUE; }
    return p;
}

char *zpl__json_parse_value(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;

    if (!!zpl_strchr("`\"'", *p)) {
        char c = *p;
        obj->type = ZPL_AST_TYPE_STRING;
        b = p + 1;
        e = p;
        obj->string = b;

        do {
            ++e;
            e = zpl_str_skip(e, c);
        } while (*(e-1) == '\\');

        if (c == '`') obj->type = ZPL_AST_TYPE_MULTISTRING;

        *e = '\0';
        p = e + 1;
    } else if (zpl_char_is_alpha(*p) || (*p == '-' && !zpl_char_is_digit(*(p + 1)))) {
        obj->type = ZPL_AST_TYPE_CONSTANT;

        if (zpl_str_has_prefix(p, "true")) {
            obj->constant = ZPL_AST_CONST_TRUE;
            p += 4;
        } else if (zpl_str_has_prefix(p, "false")) {
            obj->constant = ZPL_AST_CONST_FALSE;
            p += 5;
        } else if (zpl_str_has_prefix(p, "null")) {
            obj->constant = ZPL_AST_CONST_NULL;
            p += 4;
        } else if (zpl_str_has_prefix(p, "Infinity")) {
            obj->type = ZPL_AST_TYPE_REAL;
            obj->real = INFINITY;
            obj->props = ZPL_AST_PROPS_INFINITY;
            p += 8;
        } else if (zpl_str_has_prefix(p, "-Infinity")) {
            obj->type = ZPL_AST_TYPE_REAL;
            obj->real = -INFINITY;
            obj->props = ZPL_AST_PROPS_INFINITY_NEG;
            p += 9;
        } else if (zpl_str_has_prefix(p, "NaN")) {
            obj->type = ZPL_AST_TYPE_REAL;
            obj->real = NAN;
            obj->props = ZPL_AST_PROPS_NAN;
            p += 3;
        } else if (zpl_str_has_prefix(p, "-NaN")) {
            obj->type = ZPL_AST_TYPE_REAL;
            obj->real = -NAN;
            obj->props = ZPL_AST_PROPS_NAN_NEG;
            p += 4;
        } else {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return NULL;
        }
    } else if (zpl_char_is_digit(*p) || *p == '+' || *p == '-' || *p == '.') {
        p = zpl_ast_parse_number(obj, p);
    } else if (!!zpl_strchr("[{", *p)) {
        p = zpl__json_parse_object(obj, p, a, err_code);
        ++p;
    }

    return p;
}

char *zpl__json_parse_object(zpl_ast_node *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;

    zpl_array_init(obj->nodes, a);
    obj->backing = a;

    p = zpl__json_trim(p, false);
    /**/ if (*p == '{') { ++p; obj->type = ZPL_AST_TYPE_OBJECT; }
    else if (*p == '[') {
        ++p;
        obj->type = ZPL_AST_TYPE_ARRAY;
        return zpl__json_parse_array(obj, p, a, err_code);
    }

    while (*p) {
        zpl_ast_node node = { 0 };
        p = zpl__json_trim(p, false);
        if (*p == '}' && obj->type == ZPL_AST_TYPE_OBJECT) return p;
        if (*p == ']' && obj->type == ZPL_AST_TYPE_ARRAY) return p;

        if (*p == ']' && obj->type == ZPL_AST_TYPE_OBJECT)  {
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return p;
        }
        if (*p == '}' && obj->type == ZPL_AST_TYPE_ARRAY)   {
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return p;
        }

        if (*p == '"' || *p == '\'' || zpl_char_is_alpha(*p) || *p == '_' || *p == '$') {
            if (*p == '"' || *p == '\'') {
                if (*p == '"') {
                    node.name_style = ZPL_AST_NAME_STYLE_DOUBLE_QUOTE;
                } else if (*p == '\'') {
                    node.name_style = ZPL_AST_NAME_STYLE_SINGLE_QUOTE;
                }

                char c = *p;
                b = ++p;
                e = zpl_str_control_skip(b, c);
                node.name = b;
                *e = '\0';
                ++e;
            }
            else {
                b = p;
                e = b;

                do {
                    ++e;
                } while (*e && (zpl_char_is_alphanumeric(*e) || *e == '_') && !zpl_char_is_space(*e) && !zpl__json_is_assign_char(*e));

                node.name = b;
                node.name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            }

            char *assign_p = e;
            p = zpl__json_trim(e, false);
            node.assign_line_width = cast(zpl_u8)(p-assign_p);

            if (*p && !zpl__json_is_assign_char(*p)) {
                ZPL_JSON_ASSERT;
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                return NULL;
            }
            else
            {
                if (*p == '=')
                    node.assign_style = ZPL_AST_ASSIGN_STYLE_EQUALS;
                else if (*p == '|')
                    node.assign_style = ZPL_AST_ASSIGN_STYLE_LINE;
                else node.assign_style = ZPL_AST_ASSIGN_STYLE_COLON;
            }

            if (node.name_style == ZPL_AST_NAME_STYLE_NO_QUOTES && *e)
                *e = '\0';
        }

        if (node.name && !zpl__json_validate_name(node.name, NULL)) {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
            return NULL;
        }

        p = zpl__json_trim(p + 1, false);
        p = zpl__json_parse_value(&node, p, a, err_code);
        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

        zpl_array_append(obj->nodes, node);

        char *end_p = p;
        p = zpl__json_trim(p, true);

        if (zpl__json_is_delim_char(*p)) {
            zpl_ast_node *n = zpl_array_end(obj->nodes);
            n->delim_style = ZPL_AST_DELIM_STYLE_COMMA;

            if (*p == '\n')
                n->delim_style = ZPL_AST_DELIM_STYLE_NEWLINE;
            else if (*p == '|') {
                n->delim_style = ZPL_AST_DELIM_STYLE_LINE;
                n->delim_line_width = cast(zpl_u8)(p-end_p);
            }
            ++p;
        }
    }
    if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
    return p;
}

char *zpl__json_trim(char *base, zpl_b32 skip_newline) {
    char *p = base;
    do {
        if (!zpl_strncmp(p, "//", 2)) {
            const char *e = zpl_str_skip(p, '\n');
            p += (e-p)+1;
        }
        else if (!zpl_strncmp(p, "/*", 2)) {
            const char *e = zpl_str_skip(p+2, '*');
            if (*e && *(e+1) == '/') {
                e+=2; /* advance past end comment block */
                p += (e-p)+1;
            }
            else ++p;
        }
        else if (*p == '\n' && skip_newline) {
            return p;
        }
        else if (*p == '\0' || !zpl_char_is_space(*p)) {
            return p;
        }
        else ++p;
    } while (*p);
    return p;
}

#undef zpl___ind

ZPL_END_C_DECLS
