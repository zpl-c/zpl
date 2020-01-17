zpl_string zpl_string_make_reserve(zpl_allocator a, zpl_isize capacity) {
    zpl_isize header_size = zpl_size_of(zpl_string_header);
    void *ptr = zpl_alloc(a, header_size + capacity + 1);

    zpl_string str;
    zpl_string_header *header;

    if (ptr == NULL) return NULL;
    zpl_zero_size(ptr, header_size + capacity + 1);

    str = cast(char *) ptr + header_size;
    header = ZPL_STRING_HEADER(str);
    header->allocator = a;
    header->length = 0;
    header->capacity = capacity;
    str[capacity] = '\0';

    return str;
}


zpl_string zpl_string_make_length(zpl_allocator a, void const *init_str, zpl_isize num_bytes) {
    zpl_isize header_size = zpl_size_of(zpl_string_header);
    void *ptr = zpl_alloc(a, header_size + num_bytes + 1);

    zpl_string str;
    zpl_string_header *header;

    if (ptr == NULL) return NULL;
    if (!init_str) zpl_zero_size(ptr, header_size + num_bytes + 1);

    str = cast(char *) ptr + header_size;
    header = ZPL_STRING_HEADER(str);
    header->allocator = a;
    header->length = num_bytes;
    header->capacity = num_bytes;
    if (num_bytes && init_str) zpl_memcopy(str, init_str, num_bytes);
    str[num_bytes] = '\0';

    return str;
}

zpl_string zpl_string_sprintf_buf(zpl_allocator a, const char *fmt, ...) {
    zpl_local_persist char buf[4096] = { 0 };
    va_list va;
    va_start(va, fmt);
    zpl_snprintf_va(buf, 4096, fmt, va);
    va_end(va);

    return zpl_string_make(a, buf);
}

zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, zpl_isize num_bytes, const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    zpl_snprintf_va(buf, num_bytes, fmt, va);
    va_end(va);

    return zpl_string_make(a, buf);
}

zpl_string zpl_string_append_length(zpl_string str, void const *other, zpl_isize other_len) {
    if (other_len > 0) {
        zpl_isize curr_len = zpl_string_length(str);

        str = zpl_string_make_space_for(str, other_len);
        if (str == NULL) return NULL;

        zpl_memcopy(str + curr_len, other, other_len);
        str[curr_len + other_len] = '\0';
        zpl__set_string_length(str, curr_len + other_len);
    }
    return str;
}

ZPL_ALWAYS_INLINE zpl_string zpl_string_appendc(zpl_string str, const char *other) {
    return zpl_string_append_length(str, other, zpl_strlen(other));
}

ZPL_ALWAYS_INLINE zpl_string zpl_string_join(zpl_allocator a, const char **parts, zpl_isize count, const char *glue) {
    zpl_string ret;
    zpl_isize i;

    ret = zpl_string_make(a, NULL);

    for (i=0; i<count; ++i) {
        ret = zpl_string_appendc(ret, parts[i]);

        if ((i+1) < count) {
            ret = zpl_string_appendc(ret, glue);
        }
    }

    return ret;
}

zpl_string zpl_string_set(zpl_string str, const char *cstr) {
    zpl_isize len = zpl_strlen(cstr);
    if (zpl_string_capacity(str) < len) {
        str = zpl_string_make_space_for(str, len - zpl_string_length(str));
        if (str == NULL) return NULL;
    }

    zpl_memcopy(str, cstr, len);
    str[len] = '\0';
    zpl__set_string_length(str, len);

    return str;
}

zpl_string zpl_string_make_space_for(zpl_string str, zpl_isize add_len) {
    zpl_isize available = zpl_string_available_space(str);

    // NOTE: Return if there is enough space left
    if (available >= add_len) {
        return str;
    } else {
        zpl_isize new_len, old_size, new_size;
        void *ptr, *new_ptr;
        zpl_allocator a = ZPL_STRING_HEADER(str)->allocator;
        zpl_string_header *header;

        new_len = zpl_string_length(str) + add_len;
        ptr = ZPL_STRING_HEADER(str);
        old_size = zpl_size_of(zpl_string_header) + zpl_string_length(str) + 1;
        new_size = zpl_size_of(zpl_string_header) + new_len + 1;

        new_ptr = zpl_resize(a, ptr, old_size, new_size);
        if (new_ptr == NULL) return NULL;

        header = cast(zpl_string_header *) new_ptr;
        header->allocator = a;

        str = cast(zpl_string)(header + 1);
        zpl__set_string_capacity(str, new_len);

        return str;
    }
}

zpl_isize zpl_string_allocation_size(zpl_string const str) {
    zpl_isize cap = zpl_string_capacity(str);
    return zpl_size_of(zpl_string_header) + cap;
}

zpl_b32 zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs) {
    zpl_isize lhs_len, rhs_len, i;
    lhs_len = zpl_string_length(lhs);
    rhs_len = zpl_string_length(rhs);
    if (lhs_len != rhs_len) return false;

    for (i = 0; i < lhs_len; i++) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

zpl_string zpl_string_trim(zpl_string str, const char *cut_set) {
    char *start, *end, *start_pos, *end_pos;
    zpl_isize len;

    start_pos = start = str;
    end_pos = end = str + zpl_string_length(str) - 1;

    while (start_pos <= end && zpl_char_first_occurence(cut_set, *start_pos)) start_pos++;
    while (end_pos > start_pos && zpl_char_first_occurence(cut_set, *end_pos)) end_pos--;

    len = cast(zpl_isize)((start_pos > end_pos) ? 0 : ((end_pos - start_pos) + 1));

    if (str != start_pos) zpl_memmove(str, start_pos, len);
    str[len] = '\0';

    zpl__set_string_length(str, len);

    return str;
}

zpl_string zpl_string_append_rune(zpl_string str, zpl_rune r) {
    if (r >= 0) {
        zpl_u8 buf[8] = { 0 };
        zpl_isize len = zpl_utf8_encode_rune(buf, r);
        return zpl_string_append_length(str, buf, len);
    }

    return str;
}

zpl_string zpl_string_append_fmt(zpl_string str, const char *fmt, ...) {
    zpl_isize res;
    char buf[4096] = { 0 };
    va_list va;
    va_start(va, fmt);
    res = zpl_snprintf_va(buf, zpl_count_of(buf) - 1, fmt, va) - 1;
    va_end(va);
    return zpl_string_append_length(str, buf, res);
}
