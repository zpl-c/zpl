// file: header/ast.h
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef enum zpl_ast_type {
    ZPL_AST_TYPE_UNINITIALISED, /* node was not initialised, this is a programming error! */
    ZPL_AST_TYPE_ARRAY,
    ZPL_AST_TYPE_OBJECT,
    ZPL_AST_TYPE_STRING,
    ZPL_AST_TYPE_MULTISTRING,
    ZPL_AST_TYPE_INTEGER,
    ZPL_AST_TYPE_REAL,
    ZPL_AST_TYPE_CONSTANT
} zpl_ast_type;

typedef enum zpl_ast_props {
    ZPL_AST_PROPS_NONE,
    ZPL_AST_PROPS_NAN,
    ZPL_AST_PROPS_NAN_NEG,
    ZPL_AST_PROPS_INFINITY,
    ZPL_AST_PROPS_INFINITY_NEG,
    ZPL_AST_PROPS_IS_EXP,
    ZPL_AST_PROPS_IS_HEX,

    // Used internally so that people can fill in real numbers they plan to write.
    ZPL_AST_PROPS_IS_PARSED_REAL,
} zpl_ast_props;

typedef enum zpl_ast_const {
    ZPL_AST_CONST_FALSE,
    ZPL_AST_CONST_TRUE,
    ZPL_AST_CONST_NULL,
} zpl_ast_const;

typedef enum zpl_ast_naming_style {
    ZPL_AST_NAME_STYLE_DOUBLE_QUOTE,
    ZPL_AST_NAME_STYLE_SINGLE_QUOTE,
    ZPL_AST_NAME_STYLE_NO_QUOTES,
} zpl_ast_naming_style;

typedef enum zpl_ast_assign_style {
    ZPL_AST_ASSIGN_STYLE_COLON,
    ZPL_AST_ASSIGN_STYLE_EQUALS,
    ZPL_AST_ASSIGN_STYLE_LINE,
} zpl_ast_assign_style;

typedef enum zpl_ast_delim_style {
    ZPL_AST_DELIM_STYLE_COMMA,
    ZPL_AST_DELIM_STYLE_LINE,
    ZPL_AST_DELIM_STYLE_NEWLINE,
} zpl_ast_delim_style;

typedef struct zpl_ast_node {
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
            struct zpl_ast_node *nodes;  ///< zpl_array
        };
        zpl_i64 integer;
        char const *string;

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
} zpl_ast_node;

ZPL_DEF zpl_u8 zpl_ast_make_branch(zpl_ast_node *node, zpl_allocator backing, char const *name, zpl_u8 type);
ZPL_DEF zpl_u8 zpl_ast_destroy_branch(zpl_ast_node *node);

ZPL_DEF zpl_u8 zpl_ast_make_leaf(zpl_ast_node *node, char const *name, zpl_u8 type);

ZPL_DEF zpl_ast_node *zpl_ast_find(zpl_ast_node *node, char const *name, zpl_b32 deep_search);

ZPL_DEF zpl_ast_node *zpl_ast_alloc_at(zpl_ast_node *parent, zpl_isize index);
ZPL_DEF zpl_ast_node *zpl_ast_alloc(zpl_ast_node *parent);

ZPL_DEF void zpl_ast_set_obj(zpl_ast_node *obj, char const *name, zpl_allocator backing);
ZPL_DEF void zpl_ast_set_arr(zpl_ast_node *obj, char const *name, zpl_allocator backing);
ZPL_DEF void zpl_ast_set_str(zpl_ast_node *obj, char const *name, char const *value);
ZPL_DEF void zpl_ast_set_flt(zpl_ast_node *obj, char const *name, zpl_f64 value);
ZPL_DEF void zpl_ast_set_int(zpl_ast_node *obj, char const *name, zpl_i64 value);

ZPL_DEF zpl_ast_node *zpl_ast_inset_obj(zpl_ast_node *parent, char const *name);
ZPL_DEF zpl_ast_node *zpl_ast_inset_arr(zpl_ast_node *parent, char const *name);
ZPL_DEF zpl_ast_node *zpl_ast_inset_str(zpl_ast_node *parent, char const *name, char const *value);
ZPL_DEF zpl_ast_node *zpl_ast_inset_flt(zpl_ast_node *parent, char const *name, zpl_f64 value);
ZPL_DEF zpl_ast_node *zpl_ast_inset_int(zpl_ast_node *parent, char const *name, zpl_i64 value);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define zpl_ast_inset(parent, name, value) _Generic((value), \
                                                              char*: zpl_ast_inset_str, \
                                                              char const*: zpl_ast_inset_str, \
                                                              zpl_f64: zpl_ast_inset_flt, \
                                                              default: zpl_ast_inset_int)(parent, name, value)
#define zpl_ast_set(obj, name, value) _Generic((value), \
                                                              char*: zpl_ast_set_str, \
                                                              char const*: zpl_ast_set_str, \
                                                              zpl_f64: zpl_ast_set_flt, \
                                                              default: zpl_ast_set_int)(obj, name, value)
#endif

/* parser helpers */

ZPL_DEF char *zpl_ast_parse_number(zpl_ast_node *node, char* base);
ZPL_DEF void zpl_ast_str_to_flt(zpl_ast_node *node);

ZPL_END_C_DECLS
