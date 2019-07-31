/** @file json.c
@brief JSON5 Parser/Writer
@defgroup json JSON5 parser/writer

Easy to use and very fast JSON5 parser that can easily load 50 megabytes of JSON content under half a second. It also contains simple JSON5 writer and acts as a good library for handling config files. The parser also supports the **Simplified JSON (SJSON)** format.

We can parse JSON5 files in two different modes:
    @n 1) Fast way (useful for raw data), which can not handle comments and might cause parsing failure if comment is present.
    @n 2) Slower way (useful for config files), which handles comments perfectly but **might** have performance impact
        on bigger JSON files. (+50MiB)
@{
*/

//! Debug mode

#ifdef ZPL_JSON_DEBUG
#define ZPL_JSON_ASSERT ZPL_ASSERT(0)
#else
#define ZPL_JSON_ASSERT
#endif

//! JSON object types
typedef enum zpl_json_type {
    ZPL_JSON_TYPE_OBJECT,
    ZPL_JSON_TYPE_STRING,
    ZPL_JSON_TYPE_MULTISTRING,
    ZPL_JSON_TYPE_ARRAY,
    ZPL_JSON_TYPE_INTEGER,
    ZPL_JSON_TYPE_REAL,
    ZPL_JSON_TYPE_CONSTANT
} zpl_json_type;

//! Field value properties
typedef enum zpl_json_props {
    ZPL_JSON_PROPS_NONE = 0,
    ZPL_JSON_PROPS_NAN = 1,
    ZPL_JSON_PROPS_NAN_NEG = 2,
    ZPL_JSON_PROPS_INFINITY = 3,
    ZPL_JSON_PROPS_INFINITY_NEG = 4,
    ZPL_JSON_PROPS_IS_EXP = 5,
    ZPL_JSON_PROPS_IS_HEX = 6,

    // Used internally so that people can fill in real numbers for JSON files they plan to write.
    ZPL_JSON_PROPS_IS_PARSED_REAL = 7,
} zpl_json_props;

//! Value constants
typedef enum zpl_json_const {
    ZPL_JSON_CONST_FALSE,
    ZPL_JSON_CONST_TRUE,
    ZPL_JSON_CONST_NULL,
} zpl_json_const;

// TODO(ZaKlaus): Error handling
//! Parser error types
typedef enum zpl_json_error {
    ZPL_JSON_ERROR_NONE,
    ZPL_JSON_ERROR_INVALID_NAME,
    ZPL_JSON_ERROR_INVALID_VALUE,
    ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL,
} zpl_json_error;

//! Field name decoration style
typedef enum zpl_json_naming_style {
    ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE,
    ZPL_JSON_NAME_STYLE_SINGLE_QUOTE,
    ZPL_JSON_NAME_STYLE_NO_QUOTES,
} zpl_json_naming_style;

//! Field value assign style
typedef enum zpl_json_assign_style {
    ZPL_JSON_ASSIGN_STYLE_COLON,
    ZPL_JSON_ASSIGN_STYLE_EQUALS,
    ZPL_JSON_ASSIGN_STYLE_LINE,
} zpl_json_assign_style;

//! Field delimiter style
typedef enum zpl_json_delim_style {
    ZPL_JSON_DELIM_STYLE_COMMA,
    ZPL_JSON_DELIM_STYLE_LINE,
    ZPL_JSON_DELIM_STYLE_NEWLINE,
} zpl_json_delim_style;

#define zpl_json_object zpl_json_object

//! JSON object definition.
typedef struct zpl_json_object {
    zpl_allocator backing;
    char *name;
    zpl_u8 type:6;
    zpl_u8 name_style:2;
    zpl_u8 props:7;
    zpl_u8 cfg_mode:1;
    zpl_u8 assign_style:4;
    zpl_u8 delim_style:4;
    zpl_u8 delim_line_width;
    
    union {
        struct zpl_json_object *nodes;  ///< zpl_array
        zpl_i64 integer;
        char *string;
        
        struct {
            zpl_f64 real;
            zpl_i32 base;
            zpl_i32 base2;
            zpl_i32 exp;
            zpl_u8 exp_neg:1;
            zpl_u8 lead_digit:1;
        };
        zpl_u8 constant;
    };
} zpl_json_object;

//! Parses JSON5/SJSON text.

//! This method takes text form of JSON document as a source and parses its contents into JSON object structure we can work with. It also optionally handles comments that usually appear in documents used for configuration.
//! @param root JSON object we store data to.
//! @param len Text length. (reserved)
//! @param source Text to be processed.
//! @param allocator Memory allocator to use. (ex. zpl_heap())
//! @param handle_comments Whether to handle possible comments or not. Note that if we won't handle comments in a document containing them, the parser will error out. See remark in source code.
//! @param err_code Variable we will store error code in.
ZPL_DEF void zpl_json_parse(zpl_json_object *root, zpl_usize len, char const *source, zpl_allocator allocator, zpl_b32 handle_comments,
                            zpl_u8 *err_code);

//! Exports JSON5 document into text form and outputs it into a file.

//! This method takes JSON object tree and exports it into valid JSON5 form with the support of various styles that were preserved during import or set up programatically.
//! @param file File we write text to.
//! @param obj JSON object we export data from.
//! @param indent Text indentation used during export. Use 0 for root objects.
ZPL_DEF void zpl_json_write(zpl_file *file, zpl_json_object *o, zpl_isize indent);

//! Releases used resources by a JSON object.

//! @param obj JSON object to free.
ZPL_DEF void zpl_json_free(zpl_json_object *obj);

//! Searches for a JSON node within a document by its name.

//! @param obj JSON object to search in.
//! @param name JSON node's name to search for.
//! @param deep_search Perform the search recursively.
ZPL_DEF zpl_json_object *zpl_json_find(zpl_json_object *obj, char const *name, zpl_b32 deep_search);

//! Initializes a JSON node.

//! @param obj JSON node to initialize.
//! @param backing Memory allocator to use (ex. zpl_heap())
//! @param name JSON node's name.
//! @param type JSON node's type. (See zpl_json_type)
//! @see zpl_json_type
ZPL_DEF void zpl_json_init_node(zpl_json_object *obj, zpl_allocator backing, char const *name, zpl_u8 type);

//! Adds object into JSON document at a specific index.

//! Initializes and adds a JSON object into a JSON document at a specific index.
//! @param index Index to store at.
//! @param name JSON node's name.
//! @param type JSON node's type. (See zpl_json_type)
//! @see zpl_json_type
ZPL_DEF zpl_json_object *zpl_json_add_at(zpl_json_object *obj, zpl_isize index, char const *name, zpl_u8 type);

//! Appends object into JSON document.

//! Initializes and appends a JSON object into a JSON document.
//! @param name JSON node's name.
//! @param type JSON node's type. (See zpl_json_type)
//! @see zpl_json_type
ZPL_DEF zpl_json_object *zpl_json_add(zpl_json_object *obj, char const *name, zpl_u8 type);

ZPL_DEF char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
ZPL_DEF char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
ZPL_DEF char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);

#define zpl__trim zpl_str_trim
#define zpl__skip zpl__json_skip
ZPL_DEF char *zpl__json_skip(char *str, char c);
ZPL_DEF zpl_b32 zpl__json_validate_name(char *str, char *err);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// JSON5 Parser
//
//

zpl_b32 zpl__json_is_control_char(char c);
zpl_b32 zpl__json_is_assign_char(char c);
zpl_b32 zpl__json_is_delim_char(char c);

void zpl_json_parse(zpl_json_object *root, zpl_usize len, char const *source, zpl_allocator a, zpl_b32 handle_comments,
                    zpl_u8 *err_code) {
    
    if (!root || !source)
    {
        ZPL_JSON_ASSERT;
        if (err_code) *err_code = ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL;
        return;
    }
    
    zpl_unused(len);
    
    char *dest = (char *)source;
    
    if (handle_comments) {
        zpl_b32 is_lit = false;
        char lit_c = '\0';
        char *p = dest;
        char *b = dest;
        zpl_isize l = 0;
        
        while (*p) {
            if (!is_lit) {
                if ((*p == '"' || *p == '\'')) {
                    lit_c = *p;
                    is_lit = true;
                    ++p;
                    continue;
                }
            } else {
                if (*p == '\\' && *(p + 1) && *(p + 1) == lit_c) {
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
    
    dest = zpl_str_trim(dest, false);
    
    if (*dest != '{' && *dest != '[') { root_.cfg_mode = true; }
    
    char *endp = zpl__json_parse_object(&root_, dest, a, err_code);
    
    if (!root_.cfg_mode && endp == NULL)
    {
        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
    }
    
    *root = root_;
}

#define zpl___ind(x)                                                                                                   \
for (int i = 0; i < x; ++i) zpl_fprintf(f, " ");

void zpl__json_write_value(zpl_file *f, zpl_json_object *o, zpl_json_object *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last);

void zpl_json_write(zpl_file *f, zpl_json_object *o, zpl_isize indent) {
    if (!o)
        return;
    
    zpl___ind(indent - 4);
    if (!o->cfg_mode)
        zpl_fprintf(f, "{\n");
    else {
        indent -= 4;
    }
    
    if (o->nodes)
    {
        zpl_isize cnt = zpl_array_count(o->nodes);
        
        for (int i = 0; i < cnt; ++i) {
            if (i < cnt - 1) {
                zpl__json_write_value(f, o->nodes + i, o, indent, false, false);
            } else {
                zpl__json_write_value(f, o->nodes + i, o, indent, false, true);
            }
        }
    }
    
    zpl___ind(indent);
    
    if (indent > 0) {
        zpl_fprintf(f, "}");
    } else {
        if (!o->cfg_mode) zpl_fprintf(f, "}\n");
    }
}

void zpl__json_write_value(zpl_file *f, zpl_json_object *o, zpl_json_object *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last) {
    zpl_json_object *node = o;
    indent += 4;
    
    if (!is_inline) {
        zpl___ind(indent);
        switch (node->name_style) {
            case ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE: {
                zpl_fprintf(f, "\"%s\"", node->name);
            } break;
            
            case ZPL_JSON_NAME_STYLE_SINGLE_QUOTE: {
                zpl_fprintf(f, "\'%s\'", node->name);
            } break;
            
            case ZPL_JSON_NAME_STYLE_NO_QUOTES: {
                zpl_fprintf(f, "%s", node->name);
            } break;
        }
        
        if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_COLON)
            zpl_fprintf(f, ": ");
        else {
            if (o->name_style != ZPL_JSON_NAME_STYLE_NO_QUOTES)
                zpl___ind(1);
            
            if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_EQUALS)
                zpl_fprintf(f, "= ");
            else if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_LINE)
                zpl_fprintf(f, "| ");    
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
            zpl_isize elemn = zpl_array_count(node->nodes);
            for (int j = 0; j < elemn; ++j) {
                if ((node->nodes + j)->type == ZPL_JSON_TYPE_OBJECT || (node->nodes + j)->type == ZPL_JSON_TYPE_ARRAY) {
                    zpl__json_write_value(f, node->nodes + j, o, 0, true, true);
                } else {
                    zpl__json_write_value(f, node->nodes + j, o, -4, true, true);
                }
                
                if (j < elemn - 1) { zpl_fprintf(f, ", "); }
            }
            zpl_fprintf(f, "]");
        } break;
        
        case ZPL_JSON_TYPE_INTEGER: {
            if (node->props == ZPL_JSON_PROPS_IS_HEX) {
                zpl_fprintf(f, "0x%llx", (long long)node->integer);
            } else {
                zpl_fprintf(f, "%lld", (long long)node->integer);
            }
        } break;
        
        case ZPL_JSON_TYPE_REAL: {
            if (node->props == ZPL_JSON_PROPS_NAN) {
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
            } else if (node->props == ZPL_JSON_PROPS_IS_PARSED_REAL) {
                if (!node->lead_digit)
                    zpl_fprintf(f, ".%lld", (long long)node->base2);
                else
                    zpl_fprintf(f, "%lld.%lld", (long long)node->base, (long long)node->base2);
            } else {
                zpl_fprintf(f, "%llf", node->real);
            }
        } break;
        
        case ZPL_JSON_TYPE_OBJECT: {
            zpl_json_write(f, node, indent);
        } break;
        
        case ZPL_JSON_TYPE_CONSTANT: {
            if (node->constant == ZPL_JSON_CONST_TRUE) {
                zpl_fprintf(f, "true");
            } else if (node->constant == ZPL_JSON_CONST_FALSE) {
                zpl_fprintf(f, "false");
            } else if (node->constant == ZPL_JSON_CONST_NULL) {
                zpl_fprintf(f, "null");
            }
        } break;
    }
    
    if (!is_inline) {
        
        if (o->delim_style != ZPL_JSON_DELIM_STYLE_COMMA)
        {
            if (o->delim_style == ZPL_JSON_DELIM_STYLE_NEWLINE)
                zpl_fprintf(f, "\n");
            else if (o->delim_style == ZPL_JSON_DELIM_STYLE_LINE)
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
#undef zpl___ind

void zpl_json_free(zpl_json_object *obj) {
    if ((obj->type == ZPL_JSON_TYPE_OBJECT || obj->type == ZPL_JSON_TYPE_ARRAY) && obj->nodes) {
        for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); ++i) { zpl_json_free(obj->nodes + i); }
        
        zpl_array_free(obj->nodes);
    }
}

char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    
    obj->type = ZPL_JSON_TYPE_ARRAY;
    zpl_array_init(obj->nodes, a);
    obj->backing = a;
    
    while (*p) {
        p = zpl_str_trim(p, false);
        
        zpl_json_object elem = { 0 };
        elem.backing = a;
        p = zpl__json_parse_value(&elem, p, a, err_code);
        
        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }
        
        zpl_array_append(obj->nodes, elem);
        
        p = zpl_str_trim(p, false);
        
        if (*p == ',') {
            ++p;
            continue;
        } else {
            return p;
        }
    }
    return p;
}

char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;
    
    if (*p == '"' || *p == '\'') {
        char c = *p;
        obj->type = ZPL_JSON_TYPE_STRING;
        b = p + 1;
        e = b;
        obj->string = b;
        
        while (*e) {
            if (*e == '\\' && *(e + 1) == c) {
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
            if (*e == '\\' && *(e + 1) == '`') {
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
        
        if (!zpl_strncmp(p, "true", 4)) {
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
        
        zpl_isize ib = 0;
        char buf[16] = { 0 };
        
        if (*e == '+')
            ++e;
        else if (*e == '-') {
            buf[ib++] = *e++;
        }
        
        if (*e == '.') {
            obj->type = ZPL_JSON_TYPE_REAL;
            obj->props = ZPL_JSON_PROPS_IS_PARSED_REAL;
            buf[ib++] = '0';
            obj->lead_digit = false;
            
            do {
                buf[ib++] = *e;
            } while (zpl_char_is_digit(*++e));
        } else {
            if (*e == '0' && (*(e + 1) == 'x' || *(e + 1) == 'X')) { obj->props = ZPL_JSON_PROPS_IS_HEX; }
            while (zpl_char_is_hex_digit(*e) || *e == 'x' || *e == 'X') { buf[ib++] = *e++; }
            
            if (*e == '.') {
                obj->type = ZPL_JSON_TYPE_REAL;
                obj->lead_digit = true;
                zpl_u32 step = 0;
                
                do {
                    buf[ib++] = *e;
                    ++step;
                } while (zpl_char_is_digit(*++e));
                
                if (step < 2) { buf[ib++] = '0'; }
            }
        }
        
        zpl_i32 exp = 0;
        zpl_f32 eb = 10;
        char expbuf[6] = { 0 };
        zpl_isize expi = 0;
        
        if (*e == 'e' || *e == 'E') {
            ++e;
            if (*e == '+' || *e == '-' || zpl_char_is_digit(*e)) {
                if (*e == '-') { eb = 0.1f; }
                
                if (!zpl_char_is_digit(*e)) { ++e; }
                
                while (zpl_char_is_digit(*e)) { expbuf[expi++] = *e++; }
            }
            
            exp = (zpl_i32)zpl_str_to_i64(expbuf, NULL, 10);
        }
        
        if (obj->type == ZPL_JSON_TYPE_INTEGER) {
            obj->integer = zpl_str_to_i64(buf, 0, 0);
            
            while (exp-- > 0) { obj->integer *= (zpl_i64)eb; }
        } else {
            obj->real = zpl_str_to_f64(buf, 0);
            
            char *q = buf, *qp = q, *qp2 = q;
            while (*qp != '.') ++qp;
            *qp = '\0';
            qp2 = qp + 1;
            
            obj->base = (zpl_i32)zpl_str_to_i64(q, 0, 0);
            obj->base2 = (zpl_i32)zpl_str_to_i64(qp2, 0, 0);
            
            if (exp) {
                obj->exp = exp;
                obj->exp_neg = !(eb == 10.f);
                obj->props = ZPL_JSON_PROPS_IS_EXP;
            }
            
            while (exp-- > 0) { obj->real *= eb; }
        }
        p = e;
    } else if (*p == '[') {
        p = zpl_str_trim(p + 1, false);
        if (*p == ']') return p;
        p = zpl__json_parse_array(obj, p, a, err_code);
        
        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }
        
        ++p;
    } else if (*p == '{') {
        p = zpl_str_trim(p + 1, false);
        p = zpl__json_parse_object(obj, p, a, err_code);
        
        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }
        
        ++p;
    }
    
    return p;
}

char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
    ZPL_ASSERT(obj && base);
    char *p = base;
    char *b = base;
    char *e = base;
    
    zpl_array_init(obj->nodes, a);
    obj->backing = a;
    
    p = zpl_str_trim(p, false);
    zpl_b32 starts_with_brace = false;
    zpl_b32 starts_with_bracket = false;
    if (*p == '{') { ++p; starts_with_brace = true; }
    
    while (*p) {
        zpl_json_object node = { 0 };
        p = zpl_str_trim(p, false);
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
            p = zpl_str_trim(p, false);
            
            if (*p && !zpl__json_is_assign_char(*p)) {
                ZPL_JSON_ASSERT;
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                return NULL;
            }
        } 
        else {
            if (*p == '[') {
                starts_with_bracket = true;
                if (node.name) *node.name = '\0';
                p = zpl__json_parse_value(&node, p, a, err_code);
                goto l_parsed;
            } 
            else if (zpl_char_is_alpha(*p) || *p == '_' || *p == '$') {
                b = p;
                e = b;
                
                do {
                    ++e;
                } while (*e && (zpl_char_is_alphanumeric(*e) || *e == '_') && !zpl_char_is_space(*e) && !zpl__json_is_assign_char(*e));

                if (zpl_char_is_space(*e)) {
                    // NOTE(zaklaus): We know this is where the node name ends, cut it here
                    *e = '\0';
                    ++e;
                }
                
                if (zpl__json_is_assign_char(*e)) {
                    p = e;
                    
                    if (*e == '=')
                        node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                    else if (*e == '|')
                        node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
                } 
                else {
                    while (*e) {
                        if (*e && (!zpl_char_is_space(*e) || zpl__json_is_assign_char(*e))) 
                        { 
                            if (*e == '=')
                                node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                            else if (*e == '|')
                                node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
                            
                            break; 
                        }
                        ++e;
                    }
                    
                    e = zpl_str_trim(e, false);
                    p = e;
                    
                    if (*p && !zpl__json_is_assign_char(*p)) {
                        ZPL_JSON_ASSERT;
                        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                        return NULL;
                    }
                    else
                    {
                        if (*p == '=')
                            node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                        else if (*p == '|')
                            node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
                    }
                }
                
                *e = '\0';
                node.name = b;
                node.name_style = ZPL_JSON_NAME_STYLE_NO_QUOTES;
            }
        }
        
        char errc;
        if (node.name && !zpl__json_validate_name(node.name, &errc)) {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
            return NULL;
        }
        
        p = zpl_str_trim(p + 1, false);
        p = zpl__json_parse_value(&node, p, a, err_code);
        node.backing = obj->backing;
        
        if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }
        
        l_parsed:
        
        zpl_array_append(obj->nodes, node);
        
        char *wp = p;
        p = zpl_str_trim(p, true);
        zpl_u8 wl = cast(zpl_u8)(p-wp);
        
        if (zpl__json_is_delim_char(*p)) {
            zpl_json_object *n = zpl_array_end(obj->nodes);
            
            if (*p == '\n')
                n->delim_style = ZPL_JSON_DELIM_STYLE_NEWLINE;
            else if (*p == '|') {
                n->delim_style = ZPL_JSON_DELIM_STYLE_LINE;
                n->delim_line_width = wl;
            }
            
            if (*p == '\0')
                return NULL;
            
            p = zpl_str_trim(p + 1, false);
            if (*p == '\0' || *p == '}')
                return p;
            else
                continue;
        } else if (*p == '\0' || *p == '}' || *p == ']') {
            if (starts_with_brace && *p != '}')
            {
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                return NULL;
            }
            
            if (starts_with_bracket && *p != ']')
            {
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                return NULL;
            }
            
            return p;
        } else {
            ZPL_JSON_ASSERT;
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return NULL;
        }
    }
    return p;
}

zpl_json_object *zpl_json_find(zpl_json_object *obj, char const *name, zpl_b32 deep_search)
{
    if (obj->type != ZPL_JSON_TYPE_OBJECT)
    {
        return NULL;
    }
    
    for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); i++)
    {            
        if (!zpl_strcmp(obj->nodes[i].name, name))
        {
            return (obj->nodes + i);
        }
    }
    
    if (deep_search)
    {
        for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); i++)
        {
            zpl_json_object *res = zpl_json_find(obj->nodes + i, name, deep_search);
            
            if (res != NULL)
                return res;
        }
    }
    
    return NULL;
}

void zpl_json_init_node(zpl_json_object *obj, zpl_allocator backing, char const *name, zpl_u8 type)
{
    obj->name = (char *)name;
    obj->type = type;
    obj->backing = backing;
    
    if (type == ZPL_JSON_TYPE_ARRAY || type == ZPL_JSON_TYPE_OBJECT)
    {
        zpl_array_init(obj->nodes, backing);
    }
}

zpl_json_object *zpl_json_add_at(zpl_json_object *obj, zpl_isize index, char const *name, zpl_u8 type)
{
    if (!obj || (obj->type != ZPL_JSON_TYPE_OBJECT && obj->type != ZPL_JSON_TYPE_ARRAY))
    {
        return NULL;
    }
    
    if (!obj->nodes)
        return NULL;
    
    if (index < 0 || index > zpl_array_count(obj->nodes))
        return NULL;
    
    zpl_json_object o = {0};
    zpl_json_init_node(&o, obj->backing, name, type);
    
    zpl_array_append_at(obj->nodes, o, index);
    
    return obj->nodes + index;
}

zpl_json_object *zpl_json_add(zpl_json_object *obj, char const *name, zpl_u8 type)
{
    if (!obj || (obj->type != ZPL_JSON_TYPE_OBJECT && obj->type != ZPL_JSON_TYPE_ARRAY))
    {
        return NULL;
    }
    
    if (!obj->nodes)
        return NULL;
    
    return zpl_json_add_at(obj, zpl_array_count(obj->nodes), name, type);
}

zpl_inline zpl_b32 zpl__json_is_control_char(char c) {
    return !!zpl_strchr("\"\\/bfnrt", c);
}

zpl_inline zpl_b32 zpl__json_is_special_char(char c) { return !!zpl_strchr("<>:/", c); }
zpl_inline zpl_b32 zpl__json_is_assign_char(char c) { return !!zpl_strchr(":=|", c); }
zpl_inline zpl_b32 zpl__json_is_delim_char(char c) { return !!zpl_strchr(",|\n", c); }

#define jx(x) !zpl_char_is_hex_digit(str[x])
zpl_inline zpl_b32 zpl__json_validate_name(char *str, char *err) {
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
