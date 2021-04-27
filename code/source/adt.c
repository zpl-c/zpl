// file: source/adt.c

zpl_u8 zpl_adt_make_branch(zpl_adt_node *node, zpl_allocator backing, char const *name, zpl_u8 type) {
    ZPL_ASSERT(type == ZPL_ADT_TYPE_OBJECT || type == ZPL_ADT_TYPE_ARRAY);
    zpl_zero_item(node);
    node->type = type;
    node->name = name;
    zpl_array_init(node->nodes, backing);
    return 0;
}

zpl_u8 zpl_adt_destroy_branch(zpl_adt_node *node) {
    ZPL_ASSERT_NOT_NULL(node);
    if ((node->type == ZPL_ADT_TYPE_OBJECT || node->type == ZPL_ADT_TYPE_ARRAY) && node->nodes) {
        for (zpl_isize i = 0; i < zpl_array_count(node->nodes); ++i) { zpl_adt_destroy_branch(node->nodes + i); }

        zpl_array_free(node->nodes);
    }
    return 0;
}

zpl_u8 zpl_adt_make_leaf(zpl_adt_node *node, char const *name, zpl_u8 type) {
    ZPL_ASSERT(type != ZPL_ADT_TYPE_OBJECT && type != ZPL_ADT_TYPE_ARRAY);
    zpl_zero_item(node);
    node->type = type;
    node->name = name;
    return 0;
}

zpl_adt_node *zpl_adt_find(zpl_adt_node *node, char const *name, zpl_b32 deep_search) {
    if (node->type != ZPL_ADT_TYPE_OBJECT) {
        return NULL;
    }

    for (zpl_isize i = 0; i < zpl_array_count(node->nodes); i++) {
        if (!zpl_strcmp(node->nodes[i].name, name)) {
            return (node->nodes + i);
        }
    }

    if (deep_search) {
        for (zpl_isize i = 0; i < zpl_array_count(node->nodes); i++) {
            zpl_adt_node *res = zpl_adt_find(node->nodes + i, name, deep_search);

            if (res != NULL)
                return res;
        }
    }

    return NULL;
}

zpl_adt_node *zpl_adt_alloc_at(zpl_adt_node *parent, zpl_isize index) {
    if (!parent || (parent->type != ZPL_ADT_TYPE_OBJECT && parent->type != ZPL_ADT_TYPE_ARRAY)) {
        return NULL;
    }

    if (!parent->nodes)
        return NULL;

    if (index < 0 || index > zpl_array_count(parent->nodes))
        return NULL;

    zpl_adt_node o = {0};
    zpl_array_append_at(parent->nodes, o, index);

    return parent->nodes + index;
}

zpl_adt_node *zpl_adt_alloc(zpl_adt_node *parent) {
    if (!parent || (parent->type != ZPL_ADT_TYPE_OBJECT && parent->type != ZPL_ADT_TYPE_ARRAY)) {
        return NULL;
    }

    if (!parent->nodes)
        return NULL;

    return zpl_adt_alloc_at(parent, zpl_array_count(parent->nodes));
}


void zpl_adt_set_obj(zpl_adt_node *obj, char const *name, zpl_allocator backing) {
    zpl_adt_make_branch(obj, backing, name, ZPL_ADT_TYPE_OBJECT);
}
void zpl_adt_set_arr(zpl_adt_node *obj, char const *name, zpl_allocator backing) {
    zpl_adt_make_branch(obj, backing, name, ZPL_ADT_TYPE_ARRAY);
}
void zpl_adt_set_str(zpl_adt_node *obj, char const *name, char const *value) {
    zpl_adt_make_leaf(obj, name, ZPL_ADT_TYPE_STRING);
    obj->string = value;
}
void zpl_adt_set_flt(zpl_adt_node *obj, char const *name, zpl_f64 value) {
    zpl_adt_make_leaf(obj, name, ZPL_ADT_TYPE_REAL);
    obj->real = value;
}
void zpl_adt_set_int(zpl_adt_node *obj, char const *name, zpl_i64 value) {
    zpl_adt_make_leaf(obj, name, ZPL_ADT_TYPE_INTEGER);
    obj->integer = value;
}

zpl_adt_node *zpl_adt_move_node_at(zpl_adt_node *node, zpl_adt_node *old_parent, zpl_adt_node *new_parent, zpl_isize index) {
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT_NOT_NULL(old_parent);
    ZPL_ASSERT_NOT_NULL(new_parent);
    ZPL_ASSERT(new_parent->type == ZPL_ADT_TYPE_ARRAY || new_parent->type == ZPL_ADT_TYPE_OBJECT);
    ZPL_ASSERT(node >= old_parent->nodes);
    ZPL_ASSERT(node <= zpl_array_end(old_parent->nodes));
    ZPL_ASSERT(index >= 0 && index <= zpl_array_count(new_parent->nodes));
    zpl_adt_node *new_node = zpl_adt_alloc_at(new_parent, index);
    *new_node = *node;
    zpl_adt_remove_node(node, old_parent);
    return new_node;
}

zpl_adt_node *zpl_adt_move_node(zpl_adt_node *node, zpl_adt_node *old_parent, zpl_adt_node *new_parent) {
    ZPL_ASSERT_NOT_NULL(new_parent);
    ZPL_ASSERT(new_parent->type == ZPL_ADT_TYPE_ARRAY || new_parent->type == ZPL_ADT_TYPE_OBJECT);
    return zpl_adt_move_node_at(node, old_parent, new_parent, zpl_array_count(new_parent->nodes));
}

void zpl_adt_swap_nodes(zpl_adt_node *node, zpl_adt_node *other_node, zpl_adt_node *parent) {
    zpl_adt_swap_nodes_between_parents(node, other_node, parent, parent);
}

void zpl_adt_swap_nodes_between_parents(zpl_adt_node *node, zpl_adt_node *other_node, zpl_adt_node *parent, zpl_adt_node *other_parent) {
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT_NOT_NULL(other_node);
    ZPL_ASSERT_NOT_NULL(parent);
    ZPL_ASSERT_NOT_NULL(other_parent);
    ZPL_ASSERT(node >= parent->nodes && node <= zpl_array_end(parent->nodes));
    ZPL_ASSERT(other_node >= other_parent->nodes && other_node <= zpl_array_end(other_parent->nodes));
    zpl_isize index = (zpl_pointer_diff(parent->nodes, node) / zpl_size_of(zpl_adt_node));
    zpl_isize index2 = (zpl_pointer_diff(other_parent->nodes, other_node) / zpl_size_of(zpl_adt_node));
    zpl_adt_node temp = parent->nodes[index];
    parent->nodes[index] = other_parent->nodes[index2];
    other_parent->nodes[index2] = temp;
}

void zpl_adt_remove_node(zpl_adt_node *node, zpl_adt_node *parent) {
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT_NOT_NULL(parent);
    ZPL_ASSERT(node >= parent->nodes);
    ZPL_ASSERT(node <= zpl_array_end(parent->nodes));
    zpl_isize index = (zpl_pointer_diff(parent->nodes, node) / zpl_size_of(zpl_adt_node));
    zpl_array_remove_at(parent->nodes, index);
}


zpl_adt_node *zpl_adt_inset_obj(zpl_adt_node *parent, char const *name) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_obj(o, name, ZPL_ARRAY_HEADER(parent->nodes)->allocator);
    return o;
}
zpl_adt_node *zpl_adt_inset_arr(zpl_adt_node *parent, char const *name) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_arr(o, name, ZPL_ARRAY_HEADER(parent->nodes)->allocator);
    return o;
}
zpl_adt_node *zpl_adt_inset_str(zpl_adt_node *parent, char const *name, char const *value) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_str(o, name, value);
    return o;
}
zpl_adt_node *zpl_adt_inset_flt(zpl_adt_node *parent, char const *name, zpl_f64 value) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_flt(o, name, value);
    return o;
}
zpl_adt_node *zpl_adt_inset_int(zpl_adt_node *parent, char const *name, zpl_i64 value) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_int(o, name, value);
    return o;
}

/* parser helpers */

char *zpl_adt_parse_number(zpl_adt_node *node, char* base) {
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT_NOT_NULL(base);
    char *p = base, *e = p;

    /* skip false positives and special cases */
    if (!!zpl_strchr("eE", *p) || (!!zpl_strchr(".+-", *p) && !zpl_char_is_hex_digit(*(p+1)) && *(p+1) != '.')) {
        return ++base;
    }

    node->type = ZPL_ADT_TYPE_INTEGER;
    node->neg_zero = false;

    zpl_isize ib = 0;
    char buf[48] = { 0 };

    if (*e == '+')
        ++e;
    else if (*e == '-') {
        buf[ib++] = *e++;
    }

    if (*e == '.') {
        node->type = ZPL_ADT_TYPE_REAL;
        node->props = ZPL_ADT_PROPS_IS_PARSED_REAL;
        node->lead_digit = false;
        buf[ib++] = '0';
        do {
            buf[ib++] = *e;
        } while (zpl_char_is_digit(*++e));
    } else {
        if (!zpl_strncmp(e, "0x", 2) || !zpl_strncmp(e, "0X", 2)) { node->props = ZPL_ADT_PROPS_IS_HEX; }
        while (zpl_char_is_hex_digit(*e) || zpl_char_to_lower(*e) == 'x') { buf[ib++] = *e++; }

        if (*e == '.') {
            node->type = ZPL_ADT_TYPE_REAL;
            node->lead_digit = true;
            zpl_u32 step = 0;

            do {
                buf[ib++] = *e;
                ++step;
            } while (zpl_char_is_digit(*++e));

            if (step < 2) { buf[ib++] = '0'; }
        }
    }

    zpl_u8 exp = 0;
    zpl_f32 eb = 10;
    char expbuf[6] = { 0 };
    zpl_isize expi = 0;

    if (!!zpl_strchr("eE", *e)) {
        ++e;
        if (*e == '+' || *e == '-' || zpl_char_is_digit(*e)) {
            if (*e == '-') { eb = 0.1f; }
            if (!zpl_char_is_digit(*e)) { ++e; }
            while (zpl_char_is_digit(*e)) { expbuf[expi++] = *e++; }
        }

        exp = (zpl_u8)zpl_str_to_i64(expbuf, NULL, 10);
    }

    if (node->type == ZPL_ADT_TYPE_INTEGER) {
        node->integer = zpl_str_to_i64(buf, 0, 0);
        /* special case: negative zero */
        if (node->integer == 0 && buf[0] == '-') {
            node->neg_zero = true;
        }
        while (exp-- > 0) { node->integer *= (zpl_i64)eb; }
    } else {
        node->real = zpl_str_to_f64(buf, 0);

        char *q = buf, *base_str = q, *base_str2 = q;
        base_str = cast(char *)zpl_str_skip(base_str, '.');
        *base_str = '\0';
        base_str2 = base_str + 1;
        char *base_str_off = base_str2;
        while (*base_str_off++ == '0') node->base2_offset++;

        node->base = (zpl_i32)zpl_str_to_i64(q, 0, 0);
        node->base2 = (zpl_i32)zpl_str_to_i64(base_str2, 0, 0);

        if (exp) {
            node->exp = exp;
            node->exp_neg = !(eb == 10.f);
            node->props = ZPL_ADT_PROPS_IS_EXP;
        }

        /* special case: negative zero */
        if (node->base == 0 && buf[0] == '-') {
            node->neg_zero = true;
        }

        while (exp-- > 0) { node->real *= eb; }
    }
    return e;
}

void zpl_adt_print_number(zpl_file *file, zpl_adt_node *node) {
    ZPL_ASSERT_NOT_NULL(file);
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT(node->type == ZPL_ADT_TYPE_INTEGER || node->type == ZPL_ADT_TYPE_REAL);

    if (node->neg_zero) {
        zpl_fprintf(file, "-");
    }

    switch (node->type) {
        case ZPL_ADT_TYPE_INTEGER: {
            if (node->props == ZPL_ADT_PROPS_IS_HEX) {
                zpl_fprintf(file, "0x%llx", (long long)node->integer);
            } else {
                zpl_fprintf(file, "%lld", (long long)node->integer);
            }
        } break;

        case ZPL_ADT_TYPE_REAL: {
            if (node->props == ZPL_ADT_PROPS_NAN) {
                zpl_fprintf(file, "NaN");
            } else if (node->props == ZPL_ADT_PROPS_NAN_NEG) {
                zpl_fprintf(file, "-NaN");
            } else if (node->props == ZPL_ADT_PROPS_INFINITY) {
                zpl_fprintf(file, "Infinity");
            } else if (node->props == ZPL_ADT_PROPS_INFINITY_NEG) {
                zpl_fprintf(file, "-Infinity");
            } else if (node->props == ZPL_ADT_PROPS_TRUE) {
                zpl_fprintf(file, "true");
            } else if (node->props == ZPL_ADT_PROPS_FALSE) {
                zpl_fprintf(file, "false");
            } else if (node->props == ZPL_ADT_PROPS_NULL) {
                zpl_fprintf(file, "null");
            } else if (node->props == ZPL_ADT_PROPS_IS_EXP) {
                zpl_fprintf(file, "%lld.%0*d%llde%c%lld", (long long)node->base, node->base2_offset, 0, (long long)node->base2, node->exp_neg ? '-' : '+',
                            (long long)node->exp);
            } else if (node->props == ZPL_ADT_PROPS_IS_PARSED_REAL) {
                if (!node->lead_digit)
                    zpl_fprintf(file, ".%0*d%lld", node->base2_offset, 0, (long long)node->base2);
                else
                    zpl_fprintf(file, "%lld.%0*d%lld", (long long int)node->base2_offset, 0, (int)node->base, (long long)node->base2);
            } else {
                zpl_fprintf(file, "%f", node->real);
            }
        } break;
    }
}

void zpl_adt_print_string(zpl_file *file, zpl_adt_node *node, char const* escaped_chars, char escape_symbol) {
    ZPL_ASSERT_NOT_NULL(file);
    ZPL_ASSERT_NOT_NULL(node);
    ZPL_ASSERT_NOT_NULL(escaped_chars);
    ZPL_ASSERT(node->type == ZPL_ADT_TYPE_STRING || node->type == ZPL_ADT_TYPE_MULTISTRING);

    /* escape string */
    char const* p = node->string, *b = p;
    do {
        p = zpl_str_skip_any(p, escaped_chars);
        zpl_fprintf(file, "%.*s", zpl_ptr_diff(b, p), b);
        if (*p && !!zpl_strchr(escaped_chars, *p)) {
            zpl_fprintf(file, "%c%c", escape_symbol, *p);
            p++;
        }
        b = p;
    } while (*p);
}

void zpl_adt_str_to_number(zpl_adt_node *node) {
    ZPL_ASSERT(node);

    if (node->type == ZPL_ADT_TYPE_REAL || node->type == ZPL_ADT_TYPE_INTEGER) return; /* this is already converted/parsed */
    ZPL_ASSERT(node->type == ZPL_ADT_TYPE_STRING || node->type == ZPL_ADT_TYPE_MULTISTRING);
    zpl_adt_parse_number(node, (char *)node->string);
}
