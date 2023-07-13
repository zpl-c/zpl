// file: source/parsers/uri.c

ZPL_BEGIN_C_DECLS

void zpl__uri_decode_str(char *text) {
    char buf[ZPL_PRINTF_MAXLEN] = {0}, *p = buf;
    char *tp = text;
    
    char ch = -1;
    while (*tp) {
        ch = *tp++;
        
        if (ch != '%') {
            if (ch == '+') {
                *(p++) = ' ';
            } else {
                *(p++) = ch;
            }
        } else {
            char hex[3] = {0};
            hex[0] = tp[0];
            hex[1] = tp[1];
            char b = (char)zpl_str_to_i64(hex, NULL, 16);
            *(p++) = b;
            tp += 2;
        }
    }
    
    zpl_strcpy(text, buf);
    text[p-buf] = 0;
}

zpl_u8 zpl_uri_init(zpl_adt_node *root, char *origin, zpl_allocator a) {
    zpl_u8 err_code = ZPL_URI_ERROR_NONE;
    ZPL_ASSERT_NOT_NULL(root);
    zpl_zero_item(root);
    zpl_adt_set_obj(root, NULL, a);
    if (origin)
        zpl_adt_append_str(root, "__zpl_origin__", origin);
    return err_code;
}

zpl_u8 zpl_uri_parse(zpl_adt_node *root, char *text, zpl_allocator a) {
    zpl_u8 err_code = ZPL_URI_ERROR_NONE;
    ZPL_ASSERT_NOT_NULL(root);
    ZPL_ASSERT_NOT_NULL(text);
    zpl_zero_item(root);
    text = (char *)zpl_str_trim(text, false);
    
    zpl_adt_set_obj(root, NULL, a);
    
    char *p = text, *b = p;

    if (*p == 0) {
        return err_code;
    }
    
    // NOTE(zaklaus): grab URI origin
    if (*p != '?') {
        while (*p && *p != '?' && !zpl_char_is_space(*p)) {++p;}
        char c = *p;
        *p = 0;

        zpl_adt_append_str(root, "__zpl_origin__", b);
        
        if (!c) {
            // NOTE(zaklaus): URI has no query params, bail
            return err_code;
        }
    }
    
    b = ++p;
    
    // NOTE(zaklaus): extract query params
    while (*p && !zpl_char_is_space(*p)) {
        // NOTE(zaklaus): get param name
        b = p;
        while (*p && (*p != '&' && *p != '?' && *p != '=' && !zpl_char_is_space(*p))) { ++p; }
        char c = *p;
        *p = 0;
        
        char *field_name = b;
        char *field_value = "";
        zpl__uri_decode_str(field_name);
        
        if (c == '=') {
            // NOTE(zaklaus): read param value
            ++p;
            b = p;
            while (*p && (*p != '&' && *p != '?' && !zpl_char_is_space(*p))) { ++p; }
            c = *p;
            *p = 0;
            
            field_value = b;
            zpl__uri_decode_str(field_value);
            zpl_adt_node *obj = zpl_adt_append_str(root, field_name, field_value);
            zpl_adt_str_to_number_strict(obj);
        } else {
            zpl_adt_node *obj = zpl_adt_append_flt(root, field_name, 1);
            obj->props = ZPL_ADT_PROPS_TRUE;
        }
        
        
        if (!c) {
            break;
        }
        
        ++p;
    }
    
    return err_code;
}

zpl_adt_error zpl__uri_print_str(zpl_file *file, const char *text) {
    ZPL_ASSERT_NOT_NULL(file);
    
    if (!text) {
        return ZPL_ADT_ERROR_NONE;
    }
    
    const char *p = text;
    char buf[10] = {0};
    zpl_u8 ch;
    
    while (*p) {
        ch = (zpl_u8) *p++;
        if (ch == ' ') {
            zpl_fprintf(file, "%s", "+");
        } else if (zpl_char_is_alphanumeric(ch) || zpl_strchr("-_.~", ch)) {
            zpl_fprintf(file, "%c", ch);
        } else {
            zpl_snprintf(buf, zpl_size_of(buf), "%02X", ch);
            zpl_fprintf(file, "%c%s", '%', buf);
        }
    }
    
    return ZPL_ADT_ERROR_NONE;
}

void zpl_uri_write(zpl_file *f, zpl_adt_node *obj) {
    ZPL_ASSERT_NOT_NULL(f);
    ZPL_ASSERT_NOT_NULL(obj);
    ZPL_ASSERT(obj->type == ZPL_ADT_TYPE_OBJECT);
    
    zpl_adt_node *origin = NULL;
    
    // NOTE(zaklaus): write URI origin if available
    {
        origin = zpl_adt_query(obj, "__zpl_origin__");
        if (origin) {
            zpl_fprintf(f, origin->string);
        }
    }
    
	// NOTE(zaklaus): write params
	if (zpl_array_count(obj->nodes) > 0)
    	zpl_fprintf(f, "%s", "?");
    
    for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); i++) {
        zpl_adt_node *n = (obj->nodes+i);
        if (origin == n) continue;
        
        zpl__uri_print_str(f, n->name);

        if (n->type == ZPL_ADT_TYPE_STRING) {
            zpl_fprintf(f, "%c", '=');
            zpl__uri_print_str(f, n->string);
        } else if (n->type == ZPL_ADT_TYPE_INTEGER || n->type == ZPL_ADT_TYPE_REAL) {
           if (n->props != ZPL_ADT_PROPS_TRUE) {
                zpl_fprintf(f, "%c", '=');
                // TODO: ensure the output is URI-encoded
                zpl_adt_print_number(f, n);
           } 
        }
        
        if (i+1 < zpl_array_count(obj->nodes)) {
            zpl_fprintf(f, "%s", "&");
        }
    }
}

void zpl_uri_free(zpl_adt_node *obj) {
    zpl_adt_destroy_branch(obj);
}

zpl_string zpl_uri_write_string(zpl_allocator a, zpl_adt_node *obj) {
    zpl_file tmp;
    zpl_file_stream_new(&tmp, a);
    zpl_uri_write(&tmp, obj);
    zpl_isize fsize;
    zpl_u8* buf = zpl_file_stream_buf(&tmp, &fsize);
    zpl_string output = zpl_string_make_length(a, (char *)buf, fsize);
    zpl_file_close(&tmp);
    return output;
}

ZPL_END_C_DECLS

