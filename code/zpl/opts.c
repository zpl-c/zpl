/** @file opts.c
@brief CLI options processor
@defgroup cli CLI options processor

 Opts is a CLI options parser, it can parse flags, switches and arguments from command line and offers an easy way to express input errors as well as the ability to display help screen.
 
@{
 */

typedef enum {
    ZPL_OPTS_STRING,
    ZPL_OPTS_FLOAT,
    ZPL_OPTS_FLAG,
    ZPL_OPTS_INT,
} zpl_opts_types;

typedef struct {
    char const *name, *lname, *desc;
    u8 type;
    b32 met, pos;
    
    //! values
    union {
        zpl_string text;
        i64 integer;
        f64 real;
    };
} zpl_opts_entry;

typedef enum {
    ZPL_OPTS_ERR_VALUE,
    ZPL_OPTS_ERR_OPTION,
    ZPL_OPTS_ERR_EXTRA_VALUE,
    ZPL_OPTS_ERR_MISSING_VALUE,
} zpl_opts_err_type;

typedef struct {
    char *val;
    u8 type;
} zpl_opts_err;

typedef struct {
    zpl_allocator alloc;
    zpl_opts_entry *entries; ///< zpl_array
    zpl_opts_err *errors; ///< zpl_array
    zpl_opts_entry **positioned; ///< zpl_array
    char const *appname;
} zpl_opts;

//! Initializes options parser.

//! Initializes CLI options parser using specified memory allocator and provided application name.
//! @param opts Options parser to initialize.
//! @param allocator Memory allocator to use. (ex. zpl_heap())
//! @param app Application name displayed in help screen.
ZPL_DEF void zpl_opts_init(zpl_opts *opts, zpl_allocator allocator, char const *app);

//! Releases the resources used by options parser.
ZPL_DEF void zpl_opts_free(zpl_opts *opts);

//! Registers an option.

//! Registers an option with its short and long name, specifies option's type and its description.
//! @param opts Options parser to add to.
//! @param Shorter name of option. (ex. "f")
//! @param Full name of option. (ex. "foo") Note that rest of the module uses longer names to manipulate opts.
//! @param desc Description shown in the help screen.
//! @param type Option's type (see zpl_opts_types)
//! @see zpl_opts_types
ZPL_DEF void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, u8 type);

//! Registers option as positional.

//! Registers added option as positional, so that we can pass it anonymously. Arguments are expected on the command input in the same order they were registered as.
//! @param opts
//! @param name Name of already registered option.
ZPL_DEF void zpl_opts_positional_add(zpl_opts *opts, char const *name);

//! Compiles CLI arguments.

// This method takes CLI arguments as input and processes them based on rules that were set up.
//! @param opts
//! @param argc Argument count in an array.
//! @param argv Array of arguments.
ZPL_DEF b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv);

//! Prints out help screen.

//! Prints out help screen with example usage of application as well as with all the flags available.
ZPL_DEF void zpl_opts_print_help(zpl_opts *opts);

//! Prints out parsing errors.

//! Prints out possible errors caused by CLI input.
ZPL_DEF void zpl_opts_print_errors(zpl_opts *opts);

//! Fetches a string from an option.

//! @param opts
//! @param name Name of an option.
//! @param fallback Fallback string we return if option wasn't found.
ZPL_DEF zpl_string zpl_opts_string(zpl_opts *opts, char const *name, char const *fallback);

//! Fetches a real number from an option.

//! @param opts
//! @param name Name of an option.
//! @param fallback Fallback real number we return if option was not found.
ZPL_DEF f64 zpl_opts_real(zpl_opts *opts, char const *name, f64 fallback);

//! Fetches an integer number from an option.

//! @param opts
//! @param name Name of an option.
//! @param fallback Fallback integer number we return if option was not found.
ZPL_DEF i64 zpl_opts_integer(zpl_opts *opts, char const *name, i64 fallback);

//! Checks whether an option was used.

//! @param opts
//! @param name Name of an option.
ZPL_DEF b32 zpl_opts_has_arg(zpl_opts *opts, char const *name);

//! Checks whether all positionals have been passed in.
ZPL_DEF b32 zpl_opts_positionals_filled(zpl_opts *opts);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// CLI Options
//
//

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
    
    for (i32 i = 0; i < zpl_array_count(opts->entries); ++i) {
        zpl_opts_entry *e = opts->entries + i;
        if (e->type == ZPL_OPTS_STRING) { 
            zpl_string_free(e->text);
        }
    }

    zpl_array_free(opts->entries);
    zpl_array_free(opts->positioned);
    zpl_array_free(opts->errors);
}

void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, u8 type) {
    zpl_opts_entry e = { 0 };
    
    e.name = name;
    e.lname = lname;
    e.desc = desc;
    e.type = type;
    e.met = false;
    e.pos = false;
    
    zpl_array_append(opts->entries, e);
}

zpl_opts_entry *zpl__opts_find(zpl_opts *opts, char const *name, usize len, b32 longname) {
    zpl_opts_entry *e = 0;
    
    for (int i = 0; i < zpl_array_count(opts->entries); ++i) {
        e = opts->entries + i;
        char const *n = (longname ? e->lname : e->name);
        
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

b32 zpl_opts_positionals_filled(zpl_opts *opts) { return zpl_array_count(opts->positioned) == 0; }

zpl_string zpl_opts_string(zpl_opts *opts, char const *name, char const *fallback) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);
    
    return (char *)((e && e->met) ? e->text : fallback);
}

f64 zpl_opts_real(zpl_opts *opts, char const *name, f64 fallback) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);
    
    return (e && e->met) ? e->real : fallback;
}

i64 zpl_opts_integer(zpl_opts *opts, char const *name, i64 fallback) {
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
    
    for (isize i=0; i < zpl_array_count(opts->positioned); i++) {
        if (!zpl_strcmp(opts->positioned[i]->lname, t->lname)) {
            zpl_array_remove_at(opts->positioned, i);
            break;
        }
    }
}

b32 zpl_opts_has_arg(zpl_opts *opts, char const *name) {
    zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);
    
    if (e) { return e->met; }
    
    return false;
}

void zpl_opts_print_help(zpl_opts *opts) {
    zpl_printf("USAGE: %s", opts->appname);
    
    for (isize i = zpl_array_count(opts->entries); i >= 0; --i) {
        zpl_opts_entry *e = opts->entries + i;
        
        if (e->pos == (b32) true) { zpl_printf(" [%s]", e->lname); }
    }
    
    zpl_printf("\nOPTIONS:\n");
    
    for (isize i = 0; i < zpl_array_count(opts->entries); ++i) {
        zpl_opts_entry *e = opts->entries + i;
        
        zpl_printf("\t-%s, --%s: %s\n", e->name, e->lname, e->desc);
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

void zpl__opts_push_error(zpl_opts *opts, char *b, u8 errtype) {
    zpl_opts_err err = { 0 };
    err.val = b;
    err.type = errtype;
    zpl_array_append(opts->errors, err);
}

b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv) {
    b32 had_errors = false;
    for (int i = 1; i < argc; ++i) {
        char *p = argv[i];
        
        if (*p) {
            p = zpl__trim(p, false);
            if (*p == '-') {
                zpl_opts_entry *t = 0;
                b32 checkln = false;
                if (*(p + 1) == '-') {
                    checkln = true;
                    ++p;
                }
                
                char *b = p + 1, *e = b;
                
                while (zpl_char_is_alphanumeric(*e)) { ++e; }
                
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
                    
                    e = zpl__skip(e, '\0');
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
