// file: header/parsers/uri.h


ZPL_BEGIN_C_DECLS

typedef zpl_adt_node zpl_uri_object;

typedef enum zpl_uri_error {
    ZPL_URI_ERROR_NONE,
    ZPL_URI_ERROR_INTERNAL,
} zpl_uri_error;

ZPL_DEF zpl_u8 zpl_uri_init(zpl_adt_node *root, char *origin, zpl_allocator a);
ZPL_DEF zpl_u8 zpl_uri_parse(zpl_adt_node *root, char *text, zpl_allocator a);
ZPL_DEF void zpl_uri_write(zpl_file *f, zpl_adt_node *obj);
ZPL_DEF zpl_string zpl_uri_write_string(zpl_allocator a, zpl_adt_node *obj);
ZPL_DEF void zpl_uri_free(zpl_adt_node *obj);

ZPL_END_C_DECLS

