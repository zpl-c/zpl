// file: header/json.h

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
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

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
    ZPL_JSON_PROPS_NONE         = 0,
    ZPL_JSON_PROPS_NAN          = 1,
    ZPL_JSON_PROPS_NAN_NEG      = 2,
    ZPL_JSON_PROPS_INFINITY     = 3,
    ZPL_JSON_PROPS_INFINITY_NEG = 4,
    ZPL_JSON_PROPS_IS_EXP       = 5,
    ZPL_JSON_PROPS_IS_HEX       = 6,

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
    zpl_u8 type        :6;
    zpl_u8 name_style  :2;
    zpl_u8 props       :7;
    zpl_u8 cfg_mode    :1;
    zpl_u8 assign_style:4;
    zpl_u8 delim_style :4;
    zpl_u8 delim_line_width;

    union {
        struct zpl_json_object *nodes;  ///< zpl_array
        zpl_i64 integer;
        char *string;

        struct {
            zpl_f64 real;
            zpl_i32 base;
            zpl_i32 base2;
            zpl_i32 base2_offset;
            zpl_i32 exp;
            zpl_u8 exp_neg   :1;
            zpl_u8 lead_digit:1;
        };
        zpl_u8 constant;
    };
} zpl_json_object;

//! Parses JSON5/SJSON text.

//! This method takes text form of JSON document as a source and parses its contents into JSON object structure we can work with. It also optionally handles comments that usually appear in documents used for configuration.
//! @param root JSON object we store data to.
//! @param len Text length. (reserved)
//! @param source Text to be processed. This string will be modified during the process!
//! @param allocator Memory allocator to use. (ex. zpl_heap())
//! @param handle_comments Whether to handle possible comments or not. Note that if we won't handle comments in a document containing them, the parser will error out. See remark in source code.
//! @param err_code Variable we will store error code in.
ZPL_DEF void zpl_json_parse(zpl_json_object *root, zpl_usize len, char *source, zpl_allocator allocator, zpl_b32 handle_comments,
                            zpl_u8 *err_code);

//! Exports JSON5 document into text form and outputs it into a file.

//! This method takes JSON object tree and exports it into valid JSON5 form with the support of various styles that were preserved during import or set up programatically.
//! @param file File we write text to.
//! @param obj JSON object we export data from.
//! @param indent Text indentation used during export. Use 0 for root objects.
ZPL_DEF void zpl_json_write(zpl_file *file, zpl_json_object *obj, zpl_isize indent);

//! Exports JSON5 document into text form and returns a zpl_string

//! This method takes JSON object tree and exports it into valid JSON5 form with the support of various styles that were preserved during import or set up programatically.
//! @param obj JSON object we export data from.
//! @param indent Text indentation used during export. Use 0 for root objects.
//! @return zpl_string
ZPL_DEF zpl_string zpl_json_write_string(zpl_allocator a, zpl_json_object *obj, zpl_isize indent);

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
//! @param obj Root node to add to.
//! @param index Index to store at.
//! @param name JSON node's name.
//! @param type JSON node's type. (See zpl_json_type)
//! @see zpl_json_type
ZPL_DEF zpl_json_object *zpl_json_add_at(zpl_json_object *obj, zpl_isize index, char const *name, zpl_u8 type);

//! Appends object into JSON document.

//! Initializes and appends a JSON object into a JSON document.
//! @param obj Root node to add to.
//! @param name JSON node's name.
//! @param type JSON node's type. (See zpl_json_type)
//! @see zpl_json_type
ZPL_DEF zpl_json_object *zpl_json_add(zpl_json_object *obj, char const *name, zpl_u8 type);

//! @}

ZPL_END_C_DECLS
