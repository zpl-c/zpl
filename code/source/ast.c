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
