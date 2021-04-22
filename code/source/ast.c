// file: source/ast.c

zpl_u8 zpl_adt_make_branch(zpl_adt_node *node, zpl_allocator backing, char const *name, zpl_u8 type) {
    ZPL_ASSERT(type == ZPL_ADT_TYPE_OBJECT || type == ZPL_ADT_TYPE_ARRAY);
    zpl_zero_item(node);
    node->type = type;
    node->name = name;
    node->backing = backing;
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

zpl_adt_node *zpl_adt_inset_obj(zpl_adt_node *parent, char const *name) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_obj(o, name, parent->backing);
    return o;
}
zpl_adt_node *zpl_adt_inset_arr(zpl_adt_node *parent, char const *name) {
    zpl_adt_node *o = zpl_adt_alloc(parent);
    zpl_adt_set_arr(o, name, parent->backing);
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
    node->type = ZPL_ADT_TYPE_INTEGER;

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

    zpl_i32 exp = 0;
    zpl_f32 eb = 10;
    char expbuf[6] = { 0 };
    zpl_isize expi = 0;

    if (zpl_char_to_lower(*e) == 'e') {
        ++e;
        if (*e == '+' || *e == '-' || zpl_char_is_digit(*e)) {
            if (*e == '-') { eb = 0.1f; }
            if (!zpl_char_is_digit(*e)) { ++e; }
            while (zpl_char_is_digit(*e)) { expbuf[expi++] = *e++; }
        }

        exp = (zpl_i32)zpl_str_to_i64(expbuf, NULL, 10);
    }

    if (node->type == ZPL_ADT_TYPE_INTEGER) {
        node->integer = zpl_str_to_i64(buf, 0, 0);
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

        while (exp-- > 0) { node->real *= eb; }
    }
    return e;
}

void zpl_adt_str_to_flt(zpl_adt_node *node) {
    ZPL_ASSERT(node);

    if (node->type == ZPL_ADT_TYPE_REAL) return; /* this is already converted/parsed */
    ZPL_ASSERT(node->type == ZPL_ADT_TYPE_STRING || node->type == ZPL_ADT_TYPE_MULTISTRING);
    zpl_adt_parse_number(node, (char *)node->string);
}
