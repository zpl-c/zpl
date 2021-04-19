// file: header/parsers/csv.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef enum zpl_csv_error {
    ZPL_CSV_ERROR_NONE,
    ZPL_CSV_ERROR_INTERNAL,
    ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT,
    ZPL_CSV_ERROR_MISMATCHED_ROWS,
} zpl_csv_error;

typedef zpl_ast_node zpl_csv_object;

ZPL_DEF zpl_u8 zpl_csv_parse(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header);
ZPL_DEF zpl_u8 zpl_csv_parse_delimiter(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header, char delim);
ZPL_DEF void zpl_csv_free(zpl_csv_object *obj);

ZPL_DEF void zpl_csv_write(zpl_file *file, zpl_csv_object *obj);
ZPL_DEF zpl_string zpl_csv_write_string(zpl_allocator a, zpl_csv_object *obj);
ZPL_DEF void zpl_csv_write_delimiter(zpl_file *file, zpl_csv_object *obj, char delim);
ZPL_DEF zpl_string zpl_csv_write_string_delimiter(zpl_allocator a, zpl_csv_object *obj, char delim);

ZPL_END_C_DECLS
