// file: header/adt.h

ZPL_BEGIN_C_DECLS

typedef enum zpl_adt_type {
    ZPL_ADT_TYPE_UNINITIALISED, /* node was not initialised, this is a programming error! */
    ZPL_ADT_TYPE_ARRAY,
    ZPL_ADT_TYPE_OBJECT,
    ZPL_ADT_TYPE_STRING,
    ZPL_ADT_TYPE_MULTISTRING,
    ZPL_ADT_TYPE_INTEGER,
    ZPL_ADT_TYPE_REAL,
} zpl_adt_type;

typedef enum zpl_adt_props {
    ZPL_ADT_PROPS_NONE,
    ZPL_ADT_PROPS_NAN,
    ZPL_ADT_PROPS_NAN_NEG,
    ZPL_ADT_PROPS_INFINITY,
    ZPL_ADT_PROPS_INFINITY_NEG,
    ZPL_ADT_PROPS_FALSE,
    ZPL_ADT_PROPS_TRUE,
    ZPL_ADT_PROPS_NULL,
    ZPL_ADT_PROPS_IS_EXP,
    ZPL_ADT_PROPS_IS_HEX,

    // Used internally so that people can fill in real numbers they plan to write.
    ZPL_ADT_PROPS_IS_PARSED_REAL,
} zpl_adt_props;

typedef enum zpl_adt_naming_style {
    ZPL_ADT_NAME_STYLE_DOUBLE_QUOTE,
    ZPL_ADT_NAME_STYLE_SINGLE_QUOTE,
    ZPL_ADT_NAME_STYLE_NO_QUOTES,
} zpl_adt_naming_style;

typedef enum zpl_adt_assign_style {
    ZPL_ADT_ASSIGN_STYLE_COLON,
    ZPL_ADT_ASSIGN_STYLE_EQUALS,
    ZPL_ADT_ASSIGN_STYLE_LINE,
} zpl_adt_assign_style;

typedef enum zpl_adt_delim_style {
    ZPL_ADT_DELIM_STYLE_COMMA,
    ZPL_ADT_DELIM_STYLE_LINE,
    ZPL_ADT_DELIM_STYLE_NEWLINE,
} zpl_adt_delim_style;

typedef enum zpl_adt_error {
    ZPL_ADT_ERROR_NONE,
    ZPL_ADT_ERROR_INTERNAL,
    ZPL_ADT_ERROR_ALREADY_CONVERTED,
    ZPL_ADT_ERROR_INVALID_TYPE,
    ZPL_ADT_ERROR_OUT_OF_MEMORY,
} zpl_adt_error;

typedef struct zpl_adt_node {
    char const *name;
    struct zpl_adt_node *parent;

    /* properties */
    zpl_u8 type        :4;
    zpl_u8 props       :4;
#ifndef ZPL_PARSER_DISABLE_ANALYSIS
    zpl_u8 cfg_mode    :1;
    zpl_u8 name_style  :2;
    zpl_u8 assign_style:2;
    zpl_u8 delim_style :2;
    zpl_u8 delim_line_width :4;
    zpl_u8 assign_line_width:4;
#endif

    /* adt data */
    union {
        char const *string;
        struct zpl_adt_node *nodes;  ///< zpl_array
        struct {
            union {
                zpl_f64 real;
                zpl_i64 integer;
            };

#ifndef ZPL_PARSER_DISABLE_ANALYSIS
            /* number analysis */
            zpl_i32 base;
            zpl_i32 base2;
            zpl_u8 base2_offset:4;
            zpl_i8 exp         :4;
            zpl_u8 neg_zero  :1;
            zpl_u8 lead_digit:1;
#endif
        };
    };
} zpl_adt_node;

/* ADT NODE LIMITS
    * delimiter and assignment segment width is limited to 128 whitespace symbols each.
    * real number limits decimal position to 128 places.
    * real number exponent is limited to 64 digits.
 */

/**
 * @brief Initialise an ADT object or array
 *
 * @param node
 * @param backing Memory allocator used for descendants
 * @param name Node's name
 * @param is_array
 * @return error code
 */
ZPL_DEF zpl_u8 zpl_adt_make_branch(zpl_adt_node *node, zpl_allocator backing, char const *name, zpl_b32 is_array);

/**
 * @brief Destroy an ADT branch and its descendants
 *
 * @param node
 * @return error code
 */
ZPL_DEF zpl_u8 zpl_adt_destroy_branch(zpl_adt_node *node);

/**
 * @brief Initialise an ADT leaf
 *
 * @param node
 * @param name Node's name
 * @param type Node's type (use zpl_adt_make_branch for container nodes)
 * @return error code
 */
ZPL_DEF zpl_u8 zpl_adt_make_leaf(zpl_adt_node *node, char const *name, zpl_u8 type);


/**
 * @brief Fetch a node using provided URI string.
 *
 * This method uses a basic syntax to fetch a node from the ADT. The following features are available
 * to retrieve the data:
 *
 * - "a/b/c" navigates through objects "a" and "b" to get to "c"
 * - "arr/[foo=123]/bar" iterates over "arr" to find any object with param "foo" that matches the value "123", then gets its field called "bar"
 * - "arr/3" retrieves the 4th element in "arr"
 * - "arr/[apple]" retrieves the first element of value "apple" in "arr"
 *
 * @param node ADT node
 * @param uri Locator string as described above
 * @return zpl_adt_node*
 *
 * @see code/apps/examples/json_get.c
 */
ZPL_DEF zpl_adt_node *zpl_adt_query(zpl_adt_node *node, char const *uri);

/**
 * @brief Find a field node within an object by the given name.
 *
 * @param node
 * @param name
 * @param deep_search Perform search recursively
 * @return zpl_adt_node * node
 */
ZPL_DEF zpl_adt_node *zpl_adt_find(zpl_adt_node *node, char const *name, zpl_b32 deep_search);

/**
 * @brief Allocate an unitialised node within a container at a specified index.
 *
 * @param parent
 * @param index
 * @return zpl_adt_node * node
 */
ZPL_DEF zpl_adt_node *zpl_adt_alloc_at(zpl_adt_node *parent, zpl_isize index);

/**
 * @brief Allocate an unitialised node within a container.
 *
 * @param parent
 * @return zpl_adt_node * node
 */
ZPL_DEF zpl_adt_node *zpl_adt_alloc(zpl_adt_node *parent);

/**
 * @brief Move an existing node to a new container at a specified index.
 *
 * @param node
 * @param new_parent
 * @param index
 * @return zpl_adt_node * node
 */
ZPL_DEF zpl_adt_node *zpl_adt_move_node_at(zpl_adt_node *node, zpl_adt_node *new_parent, zpl_isize index);

/**
 * @brief Move an existing node to a new container.
 *
 * @param node
 * @param new_parent
 * @return zpl_adt_node * node
 */
ZPL_DEF zpl_adt_node *zpl_adt_move_node(zpl_adt_node *node, zpl_adt_node *new_parent);

/**
 * @brief Swap two nodes.
 *
 * @param node
 * @param other_node
 * @return
 */
ZPL_DEF void zpl_adt_swap_nodes(zpl_adt_node *node, zpl_adt_node *other_node);

/**
 * @brief Remove node from container.
 *
 * @param node
 * @return
 */
ZPL_DEF void zpl_adt_remove_node(zpl_adt_node *node);

/**
 * @brief Initialise a node as an object
 *
 * @param obj
 * @param name
 * @param backing
 * @return
 */
ZPL_DEF zpl_b8 zpl_adt_set_obj(zpl_adt_node *obj, char const *name, zpl_allocator backing);

/**
 * @brief Initialise a node as an array
 *
 * @param obj
 * @param name
 * @param backing
 * @return
 */
ZPL_DEF zpl_b8 zpl_adt_set_arr(zpl_adt_node *obj, char const *name, zpl_allocator backing);

/**
 * @brief Initialise a node as a string
 *
 * @param obj
 * @param name
 * @param value
 * @return
 */
ZPL_DEF zpl_b8 zpl_adt_set_str(zpl_adt_node *obj, char const *name, char const *value);

/**
 * @brief Initialise a node as a float
 *
 * @param obj
 * @param name
 * @param value
 * @return
 */
ZPL_DEF zpl_b8 zpl_adt_set_flt(zpl_adt_node *obj, char const *name, zpl_f64 value);

/**
 * @brief Initialise a node as a signed integer
 *
 * @param obj
 * @param name
 * @param value
 * @return
 */
ZPL_DEF zpl_b8 zpl_adt_set_int(zpl_adt_node *obj, char const *name, zpl_i64 value);

/**
 * @brief Append a new node to a container as an object
 *
 * @param parent
 * @param name
 * @return*
 */
ZPL_DEF zpl_adt_node *zpl_adt_append_obj(zpl_adt_node *parent, char const *name);

/**
 * @brief Append a new node to a container as an array
 *
 * @param parent
 * @param name
 * @return*
 */
ZPL_DEF zpl_adt_node *zpl_adt_append_arr(zpl_adt_node *parent, char const *name);

/**
 * @brief Append a new node to a container as a string
 *
 * @param parent
 * @param name
 * @param value
 * @return*
 */
ZPL_DEF zpl_adt_node *zpl_adt_append_str(zpl_adt_node *parent, char const *name, char const *value);

/**
 * @brief Append a new node to a container as a float
 *
 * @param parent
 * @param name
 * @param value
 * @return*
 */
ZPL_DEF zpl_adt_node *zpl_adt_append_flt(zpl_adt_node *parent, char const *name, zpl_f64 value);

/**
 * @brief Append a new node to a container as a signed integer
 *
 * @param parent
 * @param name
 * @param value
 * @return*
 */
ZPL_DEF zpl_adt_node *zpl_adt_append_int(zpl_adt_node *parent, char const *name, zpl_i64 value);

/* parser helpers */

/**
 * @brief Parses a text and stores the result into an unitialised node.
 *
 * @param node
 * @param base
 * @return*
 */
ZPL_DEF char         *zpl_adt_parse_number(zpl_adt_node *node, char* base);

/**
 * @brief Parses a text and stores the result into an unitialised node.
 * This function expects the entire input to be a number.
 *
 * @param node
 * @param base
 * @return*
 */
ZPL_DEF char         *zpl_adt_parse_number_strict(zpl_adt_node *node, char* base_str);

/**
 * @brief Parses and converts an existing string node into a number.
 *
 * @param node
 * @return
 */
ZPL_DEF zpl_adt_error zpl_adt_str_to_number(zpl_adt_node *node);

/**
 * @brief Parses and converts an existing string node into a number.
 * This function expects the entire input to be a number.
 *
 * @param node
 * @return
 */
ZPL_DEF zpl_adt_error zpl_adt_str_to_number_strict(zpl_adt_node *node);

/**
 * @brief Prints a number into a file stream.
 *
 * The provided file handle can also be a memory mapped stream.
 *
 * @see zpl_file_stream_new
 * @param file
 * @param node
 * @return
 */
ZPL_DEF zpl_adt_error zpl_adt_print_number(zpl_file *file, zpl_adt_node *node);

/**
 * @brief Prints a string into a file stream.
 *
 * The provided file handle can also be a memory mapped stream.
 *
 * @see zpl_file_stream_new
 * @param file
 * @param node
 * @param escaped_chars
 * @param escape_symbol
 * @return
 */
ZPL_DEF zpl_adt_error zpl_adt_print_string(zpl_file *file, zpl_adt_node *node, char const *escaped_chars, char const *escape_symbol);

/* extensions */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define zpl_adt_append(parent, name, value) _Generic((value), \
                                                              char*: zpl_adt_append_str, \
                                                              char const*: zpl_adt_append_str, \
                                                              zpl_f64: zpl_adt_append_flt, \
                                                              default: zpl_adt_append_int)(parent, name, value)
#define zpl_adt_set(obj, name, value) _Generic((value), \
                                                              char*: zpl_adt_set_str, \
                                                              char const*: zpl_adt_set_str, \
                                                              zpl_f64: zpl_adt_set_flt, \
                                                              default: zpl_adt_set_int)(obj, name, value)
#endif

/* deprecated */

ZPL_DEPRECATED_FOR(18.0.0, zpl_adt_query)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_get(zpl_adt_node *node, char const *uri) {
    return zpl_adt_query(node, uri);
}

ZPL_DEPRECATED_FOR(13.3.0, zpl_adt_str_to_number)
ZPL_IMPL_INLINE void zpl_adt_str_to_flt(zpl_adt_node *node) {
    (void)zpl_adt_str_to_number(node);
}

ZPL_DEPRECATED_FOR(17.0.0, zpl_adt_append_obj)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_inset_obj(zpl_adt_node *parent, char const *name) {
    return zpl_adt_append_obj(parent, name);
}

ZPL_DEPRECATED_FOR(17.0.0, zpl_adt_append_arr)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_inset_arr(zpl_adt_node *parent, char const *name) {
    return zpl_adt_append_arr(parent, name);
}

ZPL_DEPRECATED_FOR(17.0.0, zpl_adt_append_str)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_inset_str(zpl_adt_node *parent, char const *name, char const *value) {
    return zpl_adt_append_str(parent, name, value);
}

ZPL_DEPRECATED_FOR(17.0.0, zpl_adt_append_flt)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_inset_flt(zpl_adt_node *parent, char const *name, zpl_f64 value) {
    return zpl_adt_append_flt(parent, name, value);
}

ZPL_DEPRECATED_FOR(17.0.0, zpl_adt_append_int)
ZPL_IMPL_INLINE zpl_adt_node *zpl_adt_inset_int(zpl_adt_node *parent, char const *name, zpl_i64 value) {
    return zpl_adt_append_int(parent, name, value);
}

ZPL_END_C_DECLS
