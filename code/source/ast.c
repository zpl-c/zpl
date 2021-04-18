// file: source/ast.c

zpl_u8 zpl_ast_make_branch(zpl_ast_node *node, zpl_allocator backing, char *name, zpl_u8 type) {
    ZPL_ASSERT(type == ZPL_AST_TYPE_OBJECT || type == ZPL_AST_TYPE_ARRAY);
    zpl_zero_item(node);
    node->type = type;
    node->name = name;
    node->backing = backing;
    zpl_array_init(node->nodes, backing);
    return 0;
}

zpl_u8 zpl_ast_destroy_branch(zpl_ast_node *node) {
    ZPL_ASSERT_NOT_NULL(node);
    if ((node->type == ZPL_AST_TYPE_OBJECT || node->type == ZPL_AST_TYPE_ARRAY) && node->nodes) {
        for (zpl_isize i = 0; i < zpl_array_count(node->nodes); ++i) { zpl_ast_destroy_branch(node->nodes + i); }

        zpl_array_free(node->nodes);
    }
    return 0;
}

zpl_u8 zpl_ast_make_leaf(zpl_ast_node *node, char *name, zpl_u8 type) {
    ZPL_ASSERT(type != ZPL_AST_TYPE_OBJECT && type != ZPL_AST_TYPE_ARRAY);
    zpl_zero_item(node);
    node->type = type;
    node->name = name;
    return 0;
}

zpl_ast_node *zpl_ast_find(zpl_ast_node *node, char *name, zpl_b32 deep_search) {
    if (node->type != ZPL_AST_TYPE_OBJECT) {
        return NULL;
    }

    for (zpl_isize i = 0; i < zpl_array_count(node->nodes); i++) {
        if (!zpl_strcmp(node->nodes[i].name, name)) {
            return (node->nodes + i);
        }
    }

    if (deep_search) {
        for (zpl_isize i = 0; i < zpl_array_count(node->nodes); i++) {
            zpl_ast_node *res = zpl_ast_find(node->nodes + i, name, deep_search);

            if (res != NULL)
                return res;
        }
    }

    return NULL;
}

zpl_ast_node *zpl_ast_alloc_at(zpl_ast_node *parent, zpl_isize index) {
    if (!parent || (parent->type != ZPL_AST_TYPE_OBJECT && parent->type != ZPL_AST_TYPE_ARRAY)) {
        return NULL;
    }

    if (!parent->nodes)
        return NULL;

    if (index < 0 || index > zpl_array_count(parent->nodes))
        return NULL;

    zpl_ast_node o = {0};
    zpl_array_append_at(parent->nodes, o, index);

    return parent->nodes + index;
}

zpl_ast_node *zpl_ast_alloc(zpl_ast_node *parent) {
    if (!parent || (parent->type != ZPL_AST_TYPE_OBJECT && parent->type != ZPL_AST_TYPE_ARRAY)) {
        return NULL;
    }

    if (!parent->nodes)
        return NULL;

    return zpl_ast_alloc_at(parent, zpl_array_count(parent->nodes));
}


void zpl_ast_set_obj(zpl_ast_node *obj, char *name, zpl_allocator backing) {
    zpl_ast_make_branch(obj, backing, name, ZPL_AST_TYPE_OBJECT);
}
void zpl_ast_set_arr(zpl_ast_node *obj, char *name, zpl_allocator backing) {
    zpl_ast_make_branch(obj, backing, name, ZPL_AST_TYPE_ARRAY);
}
void zpl_ast_set_str(zpl_ast_node *obj, char *name, char const *value) {
    zpl_ast_make_leaf(obj, name, ZPL_AST_TYPE_STRING);
    obj->string = value;
}
void zpl_ast_set_flt(zpl_ast_node *obj, char *name, zpl_f64 value) {
    zpl_ast_make_leaf(obj, name, ZPL_AST_TYPE_REAL);
    obj->real = value;
}
void zpl_ast_set_int(zpl_ast_node *obj, char *name, zpl_i64 value) {
    zpl_ast_make_leaf(obj, name, ZPL_AST_TYPE_INTEGER);
    obj->integer = value;
}

zpl_ast_node *zpl_ast_inset_obj(zpl_ast_node *parent, char *name) {
    zpl_ast_node *o = zpl_ast_alloc(parent);
    zpl_ast_set_obj(o, name, parent->backing);
    return o;
}
zpl_ast_node *zpl_ast_inset_arr(zpl_ast_node *parent, char *name) {
    zpl_ast_node *o = zpl_ast_alloc(parent);
    zpl_ast_set_arr(o, name, parent->backing);
    return o;
}
zpl_ast_node *zpl_ast_inset_str(zpl_ast_node *parent, char *name, char const *value) {
    zpl_ast_node *o = zpl_ast_alloc(parent);
    zpl_ast_set_str(o, name, value);
    return o;
}
zpl_ast_node *zpl_ast_inset_flt(zpl_ast_node *parent, char *name, zpl_f64 value) {
    zpl_ast_node *o = zpl_ast_alloc(parent);
    zpl_ast_set_flt(o, name, value);
    return o;
}
zpl_ast_node *zpl_ast_inset_int(zpl_ast_node *parent, char *name, zpl_i64 value) {
    zpl_ast_node *o = zpl_ast_alloc(parent);
    zpl_ast_set_int(o, name, value);
    return o;
}
