// file: header/json.h

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#ifdef ZPL_JSON_DEBUG
#define ZPL_JSON_ASSERT ZPL_ASSERT(0)
#else
#define ZPL_JSON_ASSERT
#endif

typedef enum zpl_json_error {
    ZPL_JSON_ERROR_NONE,
    ZPL_JSON_ERROR_INVALID_NAME,
    ZPL_JSON_ERROR_INVALID_VALUE,
    ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL,
} zpl_json_error;

typedef zpl_ast_node zpl_json_object;

ZPL_DEF void zpl_json_parse(zpl_json_object *root, char *source, zpl_allocator allocator, zpl_u8 *err_code);
ZPL_DEF void zpl_json_free(zpl_json_object *obj);
ZPL_DEF void zpl_json_write(zpl_file *file, zpl_json_object *obj, zpl_isize indent);
ZPL_DEF zpl_string zpl_json_write_string(zpl_allocator a, zpl_json_object *obj, zpl_isize indent);

ZPL_DEF void zpl_json_str_to_flt(zpl_json_object *obj);

//! @}

ZPL_END_C_DECLS
