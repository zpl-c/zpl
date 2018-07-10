////////////////////////////////////////////////////////////////
//
// JSON5 Parser
//
//

#ifdef ZPL_JSON_DEBUG
#define ZPL_JSON_ASSERT ZPL_ASSERT(0)
#else
#define ZPL_JSON_ASSERT
#endif

typedef enum zpljType {
    ZPL_JSON_TYPE_OBJECT,
    ZPL_JSON_TYPE_STRING,
    ZPL_JSON_TYPE_MULTISTRING,
    ZPL_JSON_TYPE_ARRAY,
    ZPL_JSON_TYPE_INTEGER,
    ZPL_JSON_TYPE_REAL,
    ZPL_JSON_TYPE_CONSTANT
} zpljType;

typedef enum zpljProps {
    ZPL_JSON_PROPS_NONE = 0,
    ZPL_JSON_PROPS_NAN = 1,
    ZPL_JSON_PROPS_NAN_NEG = 2,
    ZPL_JSON_PROPS_INFINITY = 3,
    ZPL_JSON_PROPS_INFINITY_NEG = 4,
    ZPL_JSON_PROPS_IS_EXP = 5,
    ZPL_JSON_PROPS_IS_HEX = 6,
} zpljProps;

typedef enum zpljConst {
    ZPL_JSON_CONST_NULL,
    ZPL_JSON_CONST_FALSE,
    ZPL_JSON_CONST_TRUE,
} zpljConst;

// TODO(ZaKlaus): Error handling
typedef enum zpljError {
    ZPL_JSON_ERROR_NONE,
    ZPL_JSON_ERROR_INVALID_NAME,
    ZPL_JSON_ERROR_INVALID_VALUE,
} zpljError;

typedef enum zpljNameStyle {
    ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE,
    ZPL_JSON_NAME_STYLE_SINGLE_QUOTE,
    ZPL_JSON_NAME_STYLE_NO_QUOTES,
} zpljNameStyle;

#define zpl_json_object_t zpl_json_object
typedef struct zpl_json_object {
    zpl_allocator backing;
    u8 name_style;
    char *name;
    u8 type;
    u8 props;
    b32 cfg_mode;
    zpl_array(struct zpl_json_object) nodes;

    union {
        char *string;
        zpl_array(struct zpl_json_object) elements;
        i64 integer;
        struct {
            f64 real;
            i64 base;
            i64 base2;
            i64 exp;
            b32 exp_neg;
            b32 lead_digit;
            u8 frac;
        };
        u8 constant;
    };
} zpl_json_object;

ZPL_DEF void zpl_json_parse(zpl_json_object *root, usize len, char *const source, zpl_allocator a, b32 strip_comments,
                            u8 *err_code);
ZPL_DEF void zpl_json_write(zpl_file *f, zpl_json_object *o, isize indent);
ZPL_DEF void zpl_json_free(zpl_json_object *obj);

ZPL_DEF char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator a, u8 *err_code);
ZPL_DEF char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator a, u8 *err_code);
ZPL_DEF char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator a, u8 *err_code);

// TODO: Make it generic
#define zpl__trim zpl__json_trim
#define zpl__skip zpl__json_skip
ZPL_DEF char *zpl__json_trim(char *str);
ZPL_DEF char *zpl__json_skip(char *str, char c);
ZPL_DEF b32 zpl__json_validate_name(char *str, char *err);

//!!

////////////////////////////////////////////////////////////////
//
// JSON5 Parser
//
//

b32 zpl__json_is_control_char(char c);
char *zpl__json_trim(char *str);

void zpl_json_parse(zpl_json_object *root, usize len, char *const source, zpl_allocator_t a, b32 strip_comments,
                    u8 *err_code) {
    ZPL_ASSERT(root && source);
    zpl_unused(len);

    char *dest = source;

    if (strip_comments) {
        b32 is_lit = false;
        char lit_c = '\0';
        char *p = dest;
        char *b = dest;
        isize l = 0;

        while (*p) {
            if (!is_lit) {
                if ((*p == '"' || *p == '\'')) {
                    lit_c = *p;
                    is_lit = true;
                    ++p;
                    continue;
                }
            } else {
                /**/ if (*p == '\\' && *(p + 1) && *(p + 1) == lit_c) {
                    p += 2;
                    continue;
                } else if (*p == lit_c) {
                    is_lit = false;
                    ++p;
                    continue;
                }
            }

            if (!is_lit) {
                // NOTE(ZaKlaus): block comment
                if (p[0] == '/' && p[1] == '*') {
                    b = p;
                    l = 2;
                    p += 2;

                    while (p[0] != '*' && p[1] != '/') {
                        ++p;
                        ++l;
                    }
                    p += 2;
                    l += 2;
                    zpl_memset(b, ' ', l);
                }

                // NOTE(ZaKlaus): inline comment
                if (p[0] == '/' && p[1] == '/') {
                    b = p;
                    l = 2;
                    p += 2;

                    while (p[0] != '\n') {
                        ++p;
                        ++l;
                    }
                    ++l;
                    zpl_memset(b, ' ', l);
                }
            }

            ++p;
        }
    }

    if (err_code) *err_code = ZPL_JSON_ERROR_NONE;
    zpl_json_object root_ = { 0 };

    dest = zpl__json_trim(dest);

    if (*dest != '{' || *dest != '[') { root_.cfg_mode = true; }

    zpl__json_parse_object(&root_, dest, a, err_code);

    *root = root_;
}

#define zpl___ind(x)                                                                                                   \
    for (int i = 0; i < x; ++i) zpl_fprintf(f, " ");

void zpl__json_write_value(zpl_file *f, zpl_json_object_t *o, isize indent, b32 is_inline, b32 is_last);

void zpl_json_write(zpl_file *f, zpl_json_object *o, isize indent) {
    zpl___ind(indent - 4);
    if (!o->cfg_mode)
        zpl_fprintf(f, "{\n");
    else {
        indent -= 4;
    }
    isize cnt = zpl_array_count(o->nodes);

    for (int i = 0; i < cnt; ++i) {
        if (i < cnt - 1) {
            zpl__json_write_value(f, o->nodes + i, indent, false, false);
        } else {
            zpl__json_write_value(f, o->nodes + i, indent, false, true);
        }
    }

    zpl___ind(indent);

    if (indent > 0) {
        zpl_fprintf(f, "}");
    } else {
        if (!o->cfg_mode) zpl_fprintf(f, "}\n");
    }
}

void zpl__json_write_value(zpl_file *f, zpl_json_object_t *o, isize indent, b32 is_inline, b32 is_last) {
    zpl_json_object_t *node = o;
    indent += 4;

    if (!is_inline) {
        zpl___ind(indent);
        switch (node->name_style) {
        case ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE: {
            zpl_fprintf(f, "\"%s\": ", node->name);
        } break;

        case ZPL_JSON_NAME_STYLE_SINGLE_QUOTE: {
            zpl_fprintf(f, "\'%s\': ", node->name);
        } break;

        case ZPL_JSON_NAME_STYLE_NO_QUOTES: {
            zpl_fprintf(f, "%s: ", node->name);
        } break;
        }
    }

    switch (node->type) {
    case ZPL_JSON_TYPE_STRING: {
        zpl_fprintf(f, "\"%s\"", node->string);
    } break;

    case ZPL_JSON_TYPE_MULTISTRING: {
        zpl_fprintf(f, "`%s`", node->string);
    } break;

    case ZPL_JSON_TYPE_ARRAY: {
        zpl_fprintf(f, "[");
        isize elemn = zpl_array_count(node->elements);
        for (int j = 0; j < elemn; ++j) {
            zpl__json_write_value(f, node->elements + j, -4, true, true);

            if (j < elemn - 1) { zpl_fprintf(f, ", "); }
        }
        zpl_fprintf(f, "]");
    } break;

    case ZPL_JSON_TYPE_INTEGER: {
        /**/ if (node->props == ZPL_JSON_PROPS_IS_HEX) {
            zpl_fprintf(f, "0x%llx", (long long)node->integer);
        } else {
            zpl_fprintf(f, "%lld", (long long)node->integer);
        }
    } break;

    case ZPL_JSON_TYPE_REAL: {
        /**/ if (node->props == ZPL_JSON_PROPS_NAN) {
            zpl_fprintf(f, "NaN");
        } else if (node->props == ZPL_JSON_PROPS_NAN_NEG) {
            zpl_fprintf(f, "-NaN");
        } else if (node->props == ZPL_JSON_PROPS_INFINITY) {
            zpl_fprintf(f, "Infinity");
        } else if (node->props == ZPL_JSON_PROPS_INFINITY_NEG) {
            zpl_fprintf(f, "-Infinity");
        } else if (node->props == ZPL_JSON_PROPS_IS_EXP) {
            zpl_fprintf(f, "%lld.%llde%c%lld", (long long)node->base, (long long)node->base2, node->exp_neg ? '-' : '+',
                        (long long)node->exp);
        } else {
            if (!node->lead_digit)
                zpl_fprintf(f, ".%lld", (long long)node->base2);
            else
                zpl_fprintf(f, "%lld.%lld", (long long)node->base, (long long)node->base2);
        }
    } break;

    case ZPL_JSON_TYPE_OBJECT: {
        zpl_json_write(f, node, indent);
    } break;

    case ZPL_JSON_TYPE_CONSTANT: {
        /**/ if (node->constant == ZPL_JSON_CONST_TRUE) {
            zpl_fprintf(f, "true");
        } else if (node->constant == ZPL_JSON_CONST_FALSE) {
            zpl_fprintf(f, "false");
        } else if (node->constant == ZPL_JSON_CONST_NULL) {
            zpl_fprintf(f, "null");
        }
    } break;
    }

    if (!is_inline) {

        if (!is_last) {
            zpl_fprintf(f, ",\n");
        } else {
            zpl_fprintf(f, "\n");
        }
    }
}
#undef zpl___ind

void zpl_json_free(zpl_json_object *obj) {
    /**/ if (obj->type == ZPL_JSON_TYPE_ARRAY && obj->elements) {
        for (isize i = 0; i < zpl_array_count(obj->elements); ++i) { zpl_json_free(obj->elements + i); }

        zpl_array_free(obj->elements);
    } else if (obj->type == ZPL_JSON_TYPE_OBJECT && obj->nodes) {
        for (isize i = 0; i < zpl_array_count(obj->nodes); ++i) { zpl_json_free(obj->nodes + i); }

        zpl_array_free(obj->nodes);
    }
}

char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator_t a, u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;

    obj->type = ZPL_JSON_TYPE_ARRAY;
    zpl_array_init(obj->elements, a);
    obj->backing = a;

    while (*p) {
        p = zpl__json_trim(p);

        zpl_json_object elem = { 0 };
        p = zpl__json_parse_value(&elem, p, a, err_code);

        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

        zpl_array_append(obj->elements, elem);

        p = zpl__json_trim(p);

        if (*p == ',') {
            ++p;
            continue;
        } else {
            return p;
        }
    }
    return p;
}

char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator_t a, u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;

    /**/ if (*p == '"' || *p == '\'') {
        char c = *p;
        obj->type = ZPL_JSON_TYPE_STRING;
        b = p + 1;
        e = b;
        obj->string = b;

        while (*e) {
            /**/ if (*e == '\\' && *(e + 1) == c) {
                e += 2;
                continue;
            } else if (*e == '\\' && (*(e + 1) == '\r' || *(e + 1) == '\n')) {
                *e = ' ';
                e++;
                continue;
            } else if (*e == c) {
                break;
            }
            ++e;
        }

        *e = '\0';
        p = e + 1;
    } else if (*p == '`') {
        obj->type = ZPL_JSON_TYPE_MULTISTRING;
        b = p + 1;
        e = b;
        obj->string = b;

        while (*e) {
            /**/ if (*e == '\\' && *(e + 1) == '`') {
                e += 2;
                continue;
            } else if (*e == '`') {
                break;
            }
            ++e;
        }

        *e = '\0';
        p = e + 1;
    } else if (zpl_char_is_alpha(*p) || (*p == '-' && !zpl_char_is_digit(*(p + 1)))) {
        obj->type = ZPL_JSON_TYPE_CONSTANT;

        /**/ if (!zpl_strncmp(p, "true", 4)) {
            obj->constant = ZPL_JSON_CONST_TRUE;
            p += 4;
        } else if (!zpl_strncmp(p, "false", 5)) {
            obj->constant = ZPL_JSON_CONST_FALSE;
            p += 5;
        } else if (!zpl_strncmp(p, "null", 4)) {
            obj->constant = ZPL_JSON_CONST_NULL;
            p += 4;
        } else if (!zpl_strncmp(p, "Infinity", 8)) {
            obj->type = ZPL_JSON_TYPE_REAL;
            obj->real = INFINITY;
            obj->props = ZPL_JSON_PROPS_INFINITY;
            p += 8;
        } else if (!zpl_strncmp(p, "-Infinity", 9)) {
            obj->type = ZPL_JSON_TYPE_REAL;
            obj->real = -INFINITY;
            obj->props = ZPL_JSON_PROPS_INFINITY_NEG;
            p += 9;
        } else if (!zpl_strncmp(p, "NaN", 3)) {
            obj->type = ZPL_JSON_TYPE_REAL;
            obj->real = NAN;
            obj->props = ZPL_JSON_PROPS_NAN;
            p += 3;
        } else if (!zpl_strncmp(p, "-NaN", 4)) {
            obj->type = ZPL_JSON_TYPE_REAL;
            obj->real = -NAN;
            obj->props = ZPL_JSON_PROPS_NAN_NEG;
            p += 4;
        } else {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return NULL;
        }
    } else if (zpl_char_is_digit(*p) || *p == '+' || *p == '-' || *p == '.') {
        obj->type = ZPL_JSON_TYPE_INTEGER;

        b = p;
        e = b;

        isize ib = 0;
        u8 frac = 0;
        char buf[16] = { 0 };

        /**/ if (*e == '+')
            ++e;
        else if (*e == '-') {
            buf[ib++] = *e++;
        }

        if (*e == '.') {
            obj->type = ZPL_JSON_TYPE_REAL;
            buf[ib++] = '0';
            obj->lead_digit = false;

            do {
                buf[ib++] = *e;
                ++frac;
            } while (zpl_char_is_digit(*++e));
        } else {
            if (*e == '0' && (*(e + 1) == 'x' || *(e + 1) == 'X')) { obj->props = ZPL_JSON_PROPS_IS_HEX; }
            while (zpl_char_is_hex_digit(*e) || *e == 'x' || *e == 'X') { buf[ib++] = *e++; }

            if (*e == '.') {
                obj->type = ZPL_JSON_TYPE_REAL;
                obj->lead_digit = true;
                u32 step = 0;

                do {
                    buf[ib++] = *e;
                    ++step;
                    ++frac;
                } while (zpl_char_is_digit(*++e));

                if (step < 2) { buf[ib++] = '0'; }
            }
        }

        i64 exp = 0;
        f32 eb = 10;
        char expbuf[6] = { 0 };
        isize expi = 0;

        if (*e == 'e' || *e == 'E') {
            ++e;
            if (*e == '+' || *e == '-' || zpl_char_is_digit(*e)) {
                if (*e == '-') { eb = 0.1f; }

                if (!zpl_char_is_digit(*e)) { ++e; }

                while (zpl_char_is_digit(*e)) { expbuf[expi++] = *e++; }
            }

            exp = zpl_str_to_i64(expbuf, NULL, 10);
        }

        if (*e == '\0') {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
        }

        if (obj->type == ZPL_JSON_TYPE_INTEGER) {
            obj->integer = zpl_str_to_i64(buf, 0, 0);

            while (--exp > 0) { obj->integer *= (i64)eb; }
        } else {
            obj->real = zpl_str_to_f64(buf, 0);
            obj->frac = frac - 1;

            isize qs = zpl_strlen(buf) + 1;
            char *q = (char *)zpl_malloc(qs), *qp = q, *qp2 = q;
            zpl_memcopy(q, buf, qs);
            while (*qp != '.') ++qp;
            *qp = '\0';
            qp2 = qp + 1;

            obj->base = zpl_str_to_i64(q, 0, 0);
            obj->base2 = zpl_str_to_i64(qp2, 0, 0);

            if (exp) {
                obj->exp = exp;
                obj->exp_neg = !(eb == 10.f);
                obj->props = ZPL_JSON_PROPS_IS_EXP;
            }

            while (--exp > 0) { obj->real *= eb; }
        }
        p = e;
    } else if (*p == '[') {
        p = zpl__json_trim(p + 1);
        if (*p == ']') return p;
        p = zpl__json_parse_array(obj, p, a, err_code);

        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

        ++p;
    } else if (*p == '{') {
        p = zpl__json_trim(p + 1);
        p = zpl__json_parse_object(obj, p, a, err_code);

        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

        ++p;
    }

    return p;
}

char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator_t a, u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;

    zpl_array_init(obj->nodes, a);
    obj->backing = a;

    p = zpl__json_trim(p);
    if (*p == '{') { ++p; }

    while (*p) {
        zpl_json_object node = { 0 };
        p = zpl__json_trim(p);
        if (*p == '}') return p;

        if (*p == '"' || *p == '\'') {
            if (*p == '"') {
                node.name_style = ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE;
            } else {
                node.name_style = ZPL_JSON_NAME_STYLE_SINGLE_QUOTE;
            }

            char c = *p;
            b = ++p;
            e = zpl__json_skip(b, c);
            node.name = b;
            *e = '\0';

            p = ++e;
            p = zpl__json_trim(p);

            if (*p && *p != ':') {
                ZPL_JSON_ASSERT;
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                return NULL;
            }
        } else {
            /**/ if (*p == '[') {
                if (node.name) *node.name = '\0';
                p = zpl__json_parse_value(&node, p, a, err_code);
                goto l_parsed;
            } else if (zpl_char_is_alpha(*p) || *p == '_' || *p == '$') {
                b = p;
                e = b;

                do {
                    ++e;
                } while (*e && (zpl_char_is_alphanumeric(*e) || *e == '_') && !zpl_char_is_space(*e) && *e != ':');

                if (*e == ':') {
                    p = e;
                } else {
                    while (*e) {
                        if (*e && (!zpl_char_is_space(*e) || *e == ':')) { break; }
                        ++e;
                    }
                    e = zpl__json_trim(e);
                    p = e;

                    if (*p && *p != ':') {
                        ZPL_JSON_ASSERT;
                        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                        return NULL;
                    }
                }

                *e = '\0';
                node.name = b;
                node.name_style = ZPL_JSON_NAME_STYLE_NO_QUOTES;
            }
        }

        char errc;
        if (!zpl__json_validate_name(node.name, &errc)) {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
            return NULL;
        }

        p = zpl__json_trim(p + 1);
        p = zpl__json_parse_value(&node, p, a, err_code);

        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

    l_parsed:

        zpl_array_append(obj->nodes, node);

        p = zpl__json_trim(p);

        /**/ if (*p == ',') {
            p = zpl__json_trim(p + 1);
            /**/ if (*p == '\0' || *p == '}')
                return p;
            else
                continue;
        } else if (*p == '\0' || *p == '}') {
            return p;
        } else {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return NULL;
        }
    }
    return p;
}

zpl_inline char *zpl__json_trim(char *str) {
    while (*str && zpl_char_is_space(*str)) { ++str; }

    return str;
}

zpl_inline b32 zpl__json_is_control_char(char c) {
    return (c == '"' || c == '\\' || c == '/' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't');
}

zpl_inline b32 zpl__json_is_special_char(char c) { return (c == '<' || c == '>' || c == ':' || c == '/'); }

#define jx(x) !zpl_char_is_hex_digit(str[x])
zpl_inline b32 zpl__json_validate_name(char *str, char *err) {
    while (*str) {
        if ((str[0] == '\\' && !zpl__json_is_control_char(str[1])) &&
            (str[0] == '\\' && jx(1) && jx(2) && jx(3) && jx(4))) {
            *err = *str;
            return false;
        }

        ++str;
    }

    return true;
}
#undef jx

zpl_inline char *zpl__json_skip(char *str, char c) {
    while ((*str && *str != c) || (*(str - 1) == '\\' && *str == c && zpl__json_is_control_char(c))) { ++str; }

    return str;
}
