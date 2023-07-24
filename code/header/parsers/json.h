// file: header/parsers/json.h


ZPL_BEGIN_C_DECLS

typedef enum zpl_json_error {
    ZPL_JSON_ERROR_NONE,
    ZPL_JSON_ERROR_INTERNAL,
    ZPL_JSON_ERROR_INVALID_NAME,
    ZPL_JSON_ERROR_INVALID_VALUE,
    ZPL_JSON_ERROR_INVALID_ASSIGNMENT,
    ZPL_JSON_ERROR_UNKNOWN_KEYWORD,
    ZPL_JSON_ERROR_ARRAY_LEFT_OPEN,
    ZPL_JSON_ERROR_OBJECT_END_PAIR_MISMATCHED,
    ZPL_JSON_ERROR_OUT_OF_MEMORY,
} zpl_json_error;

typedef enum zpl_json_indent_style {
    ZPL_JSON_INDENT_STYLE_COMPACT = -1000,
} zpl_json_indent_style;

typedef zpl_adt_node zpl_json_object;

ZPL_DEF zpl_u8 zpl_json_parse(zpl_json_object *root, char *text, zpl_allocator allocator);
ZPL_DEF void zpl_json_free(zpl_json_object *obj);
ZPL_DEF zpl_b8 zpl_json_write(zpl_file *file, zpl_json_object *obj, zpl_isize indent);
ZPL_DEF zpl_string zpl_json_write_string(zpl_allocator a, zpl_json_object *obj, zpl_isize indent);

ZPL_END_C_DECLS
