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

typedef struct zpl_adt_node {
    char const *name;
    zpl_u8 type        :6;
    zpl_u8 name_style  :2;
    zpl_u8 props       :7;
    zpl_u8 cfg_mode    :1;
    zpl_u8 assign_style:4;
    zpl_u8 delim_style :4;
    zpl_u8 delim_line_width;
    zpl_u8 assign_line_width;
    void *user_data;
    zpl_i64 user_index;

    union {
        struct {
            zpl_allocator backing;
            struct zpl_adt_node *nodes;  ///< zpl_array
        };
        char const *string;
        struct {
            union {
                zpl_f64 real;
                zpl_i64 integer;
            };

            /* number analysis */
            zpl_i32 base;
            zpl_i32 base2;
            zpl_i32 base2_offset;
            zpl_i32 exp;
            zpl_u8 neg_zero  :1;
            zpl_u8 exp_neg   :1;
            zpl_u8 lead_digit:1;
        };
    };
} zpl_adt_node;

ZPL_DEF zpl_u8 zpl_adt_make_branch(zpl_adt_node *node, zpl_allocator backing, char const *name, zpl_u8 type);
ZPL_DEF zpl_u8 zpl_adt_destroy_branch(zpl_adt_node *node);

ZPL_DEF zpl_u8 zpl_adt_make_leaf(zpl_adt_node *node, char const *name, zpl_u8 type);

ZPL_DEF zpl_adt_node *zpl_adt_find(zpl_adt_node *node, char const *name, zpl_b32 deep_search);

ZPL_DEF zpl_adt_node *zpl_adt_alloc_at(zpl_adt_node *parent, zpl_isize index);
ZPL_DEF zpl_adt_node *zpl_adt_alloc(zpl_adt_node *parent);

ZPL_DEF void zpl_adt_set_obj(zpl_adt_node *obj, char const *name, zpl_allocator backing);
ZPL_DEF void zpl_adt_set_arr(zpl_adt_node *obj, char const *name, zpl_allocator backing);
ZPL_DEF void zpl_adt_set_str(zpl_adt_node *obj, char const *name, char const *value);
ZPL_DEF void zpl_adt_set_flt(zpl_adt_node *obj, char const *name, zpl_f64 value);
ZPL_DEF void zpl_adt_set_int(zpl_adt_node *obj, char const *name, zpl_i64 value);

ZPL_DEF zpl_adt_node *zpl_adt_inset_obj(zpl_adt_node *parent, char const *name);
ZPL_DEF zpl_adt_node *zpl_adt_inset_arr(zpl_adt_node *parent, char const *name);
ZPL_DEF zpl_adt_node *zpl_adt_inset_str(zpl_adt_node *parent, char const *name, char const *value);
ZPL_DEF zpl_adt_node *zpl_adt_inset_flt(zpl_adt_node *parent, char const *name, zpl_f64 value);
ZPL_DEF zpl_adt_node *zpl_adt_inset_int(zpl_adt_node *parent, char const *name, zpl_i64 value);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define zpl_adt_inset(parent, name, value) _Generic((value), \
                                                              char*: zpl_adt_inset_str, \
                                                              char const*: zpl_adt_inset_str, \
                                                              zpl_f64: zpl_adt_inset_flt, \
                                                              default: zpl_adt_inset_int)(parent, name, value)
#define zpl_adt_set(obj, name, value) _Generic((value), \
                                                              char*: zpl_adt_set_str, \
                                                              char const*: zpl_adt_set_str, \
                                                              zpl_f64: zpl_adt_set_flt, \
                                                              default: zpl_adt_set_int)(obj, name, value)
#endif

/* parser helpers */

ZPL_DEF char *zpl_adt_parse_number(zpl_adt_node *node, char* base);
ZPL_DEF void zpl_adt_str_to_number(zpl_adt_node *node);
ZPL_DEF void zpl_adt_print_number(zpl_file *file, zpl_adt_node *node);
ZPL_DEF void zpl_adt_print_string(zpl_file *file, zpl_adt_node *node, char const* escaped_chars, char escape_symbol);

/* deprecated */

ZPL_DEPRECATED_FOR(13.3.0, zpl_adt_str_to_number)
ZPL_IMPL_INLINE void zpl_adt_str_to_flt(zpl_adt_node *node) {
    zpl_adt_str_to_number(node);
}

ZPL_END_C_DECLS
