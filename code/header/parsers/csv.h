// file: header/parsers/csv.h


ZPL_BEGIN_C_DECLS

typedef enum zpl_csv_error {
    ZPL_CSV_ERROR_NONE,
    ZPL_CSV_ERROR_INTERNAL,
    ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT,
    ZPL_CSV_ERROR_MISMATCHED_ROWS,
} zpl_csv_error;

typedef zpl_adt_node zpl_csv_object;

ZPL_DEF_INLINE zpl_u8 zpl_csv_parse(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header);
ZPL_DEF zpl_u8 zpl_csv_parse_delimiter(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header, char delim);
ZPL_DEF void zpl_csv_free(zpl_csv_object *obj);

ZPL_DEF_INLINE void zpl_csv_write(zpl_file *file, zpl_csv_object *obj);
ZPL_DEF_INLINE zpl_string zpl_csv_write_string(zpl_allocator a, zpl_csv_object *obj);
ZPL_DEF void zpl_csv_write_delimiter(zpl_file *file, zpl_csv_object *obj, char delim);
ZPL_DEF zpl_string zpl_csv_write_string_delimiter(zpl_allocator a, zpl_csv_object *obj, char delim);

/* inline */

ZPL_IMPL_INLINE zpl_u8 zpl_csv_parse(zpl_csv_object *root, char *text, zpl_allocator allocator, zpl_b32 has_header) {
    return zpl_csv_parse_delimiter(root, text, allocator, has_header, ',');
}

ZPL_IMPL_INLINE void zpl_csv_write(zpl_file *file, zpl_csv_object *obj) {
    zpl_csv_write_delimiter(file, obj, ',');
}

ZPL_IMPL_INLINE zpl_string zpl_csv_write_string(zpl_allocator a, zpl_csv_object *obj) {
    return zpl_csv_write_string_delimiter(a, obj, ',');
}


ZPL_END_C_DECLS
