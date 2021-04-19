// file: source/opts.c

////////////////////////////////////////////////////////////////
//
// CLI Options
//
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

void zpl_opts_init(zpl_opts *opts, zpl_allocator a, char const *app) {
    zpl_opts opts_ = { 0 };
    *opts = opts_;
    opts->alloc = a;
    opts->appname = app;

    zpl_array_init(opts->entries, a);
    zpl_array_init(opts->positioned, a);
    zpl_array_init(opts->errors, a);
}

void zpl_opts_free(zpl_opts *opts) {
    for (zpl_i32 i = 0; i < zpl_array_count(opts->entries); ++i) {
        zpl_opts_entry *e = opts->entries + i;
        if (e->type == ZPL_OPTS_STRING) {
            zpl_string_free(e->text);
        }
    }

    zpl_array_free(opts->entries);
    zpl_array_free(opts->positioned);
    zpl_array_free(opts->errors);
}

void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, zpl_u8 type) {
    zpl_opts_entry e = { 0 };

    e.name = name;
    e.lname = lname;
    e.desc = desc;
    e.type = type;
    e.met = false;
    e.pos = false;

    zpl_array_append(opts->entries, e);
}

zpl_opts_entry *zpl__opts_find(zpl_opts *opts, char const *name, zpl_usize len, zpl_b32 longname) {
    zpl_opts_entry *e = 0;

    for (int i = 0; i < zpl_array_count(opts->entries); ++i) {
        e = opts->entries + i;
        char const *n = (longname ? e->lname : e->name);
        if(!n) continue;

        if (zpl_strnlen(name, len) == zpl_strlen(n) && !zpl_strncmp(n, name, len)) { return e; }
    }

    return NULL;
}

void zpl_opts_positional_add(zpl_opts *opts, char const *name) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

    if (e) {
        e->pos = true;
        zpl_array_append_at(opts->positioned, e, 0);
    }
}

zpl_b32 zpl_opts_positionals_filled(zpl_opts *opts) { return zpl_array_count(opts->positioned) == 0; }

zpl_string zpl_opts_string(zpl_opts *opts, char const *name, char const *fallback) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

    return (char *)((e && e->met) ? e->text : fallback);
}

zpl_f64 zpl_opts_real(zpl_opts *opts, char const *name, zpl_f64 fallback) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

    return (e && e->met) ? e->real : fallback;
}

zpl_i64 zpl_opts_integer(zpl_opts *opts, char const *name, zpl_i64 fallback) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

    return (e && e->met) ? e->integer : fallback;
}

void zpl__opts_set_value(zpl_opts *opts, zpl_opts_entry *t, char *b) {
    t->met = true;

    switch (t->type) {
        case ZPL_OPTS_STRING: {
            t->text = zpl_string_make(opts->alloc, b);
        } break;

        case ZPL_OPTS_FLOAT: {
            t->real = zpl_str_to_f64(b, NULL);
        } break;

        case ZPL_OPTS_INT: {
            t->integer = zpl_str_to_i64(b, NULL, 10);
        } break;
    }

    for (zpl_isize i=0; i < zpl_array_count(opts->positioned); i++) {
        if (!zpl_strcmp(opts->positioned[i]->lname, t->lname)) {
            zpl_array_remove_at(opts->positioned, i);
            break;
        }
    }
}

zpl_b32 zpl_opts_has_arg(zpl_opts *opts, char const *name) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

    if (e) { return e->met; }

    return false;
}

void zpl_opts_print_help(zpl_opts *opts) {
    zpl_printf("USAGE: %s", opts->appname);

    for (zpl_isize i = zpl_array_count(opts->entries); i >= 0; --i) {
        zpl_opts_entry *e = opts->entries + i;

        if (e->pos == (zpl_b32) true) { zpl_printf(" [%s]", e->lname); }
    }

    zpl_printf("\nOPTIONS:\n");

    for (zpl_isize i = 0; i < zpl_array_count(opts->entries); ++i) {
        zpl_opts_entry *e = opts->entries + i;

        if(e->name) {
            if(e->lname) { zpl_printf("\t-%s, --%s: %s\n", e->name, e->lname, e->desc); }
            else { zpl_printf("\t-%s: %s\n", e->name, e->desc); }
        } else { zpl_printf("\t--%s: %s\n", e->lname, e->desc); }
    }
}

void zpl_opts_print_errors(zpl_opts *opts) {
    for (int i = 0; i < zpl_array_count(opts->errors); ++i) {
        zpl_opts_err *err = (opts->errors + i);

        zpl_printf("ERROR: ");

        switch (err->type) {
            case ZPL_OPTS_ERR_OPTION: zpl_printf("Invalid option \"%s\"", err->val); break;

            case ZPL_OPTS_ERR_VALUE: zpl_printf("Invalid value \"%s\"", err->val); break;

            case ZPL_OPTS_ERR_MISSING_VALUE: zpl_printf("Missing value for option \"%s\"", err->val); break;

            case ZPL_OPTS_ERR_EXTRA_VALUE: zpl_printf("Extra value for option \"%s\"", err->val); break;
        }

        zpl_printf("\n");
    }
}

void zpl__opts_push_error(zpl_opts *opts, char *b, zpl_u8 errtype) {
    zpl_opts_err err = { 0 };
    err.val = b;
    err.type = errtype;
    zpl_array_append(opts->errors, err);
}

zpl_b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv) {
    zpl_b32 had_errors = false;
    for (int i = 1; i < argc; ++i) {
        char *p = argv[i];

        if (*p) {
            p = cast(char *)zpl_str_trim(p, false);
            if (*p == '-') {
                zpl_opts_entry *t = 0;
                zpl_b32 checkln = false;
                if (*(p + 1) == '-') {
                    checkln = true;
                    ++p;
                }

                char *b = p + 1, *e = b;

                while (zpl_char_is_alphanumeric(*e) || *e == '-' || *e == '_') { ++e; }

                t = zpl__opts_find(opts, b, (e - b), checkln);

                if (t) {
                    char *ob = b;
                    b = e;

                    /**/ if (*e == '=') {
                        if (t->type == ZPL_OPTS_FLAG) {
                            *e = '\0';
                            zpl__opts_push_error(opts, ob, ZPL_OPTS_ERR_EXTRA_VALUE);
                            had_errors = true;
                            continue;
                        }

                        b = e = e + 1;
                    } else if (*e == '\0') {
                        char *sp = argv[i+1];

                        if (sp && *sp != '-' && (zpl_array_count(opts->positioned) < 1  || t->type != ZPL_OPTS_FLAG)) {
                            if (t->type == ZPL_OPTS_FLAG) {
                                zpl__opts_push_error(opts, b, ZPL_OPTS_ERR_EXTRA_VALUE);
                                had_errors = true;
                                continue;
                            }

                            p = sp;
                            b = e = sp;
                            ++i;
                        } else {
                            if (t->type != ZPL_OPTS_FLAG) {
                                zpl__opts_push_error(opts, ob, ZPL_OPTS_ERR_MISSING_VALUE);
                                had_errors = true;
                                continue;
                            }
                            t->met = true;
                            continue;
                        }
                    }

                    e = cast(char *)zpl_str_control_skip(e, '\0');
                    zpl__opts_set_value(opts, t, b);
                } else {
                    zpl__opts_push_error(opts, b, ZPL_OPTS_ERR_OPTION);
                    had_errors = true;
                }
            } else if (zpl_array_count(opts->positioned)) {
                zpl_opts_entry *l = zpl_array_back(opts->positioned);
                zpl_array_pop(opts->positioned);
                zpl__opts_set_value(opts, l, p);
            } else {
                zpl__opts_push_error(opts, p, ZPL_OPTS_ERR_VALUE);
                had_errors = true;
            }
        }
    }
    return !had_errors;
}

ZPL_END_C_DECLS
