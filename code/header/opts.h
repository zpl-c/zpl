/** @file opts.c
@brief CLI options processor
@defgroup cli CLI options processor

 Opts is a CLI options parser, it can parse flags, switches and arguments from command line
 and offers an easy way to express input errors as well as the ability to display help screen.

@{
 */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

typedef enum {
    ZPL_OPTS_STRING,
    ZPL_OPTS_FLOAT,
    ZPL_OPTS_FLAG,
    ZPL_OPTS_INT,
} zpl_opts_types;

typedef struct {
    char const *name, *lname, *desc;
    zpl_u8 type;
    zpl_b32 met, pos;

    //! values
    union {
        zpl_string text;
        zpl_i64 integer;
        zpl_f64 real;
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
    zpl_u8 type;
} zpl_opts_err;

typedef struct {
    zpl_allocator    alloc;
    zpl_opts_entry  *entries;   ///< zpl_array
    zpl_opts_err    *errors;    ///< zpl_array
    zpl_opts_entry **positioned; ///< zpl_array
    char const      *appname;
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
//! @param lname Shorter name of option. (ex. "f")
//! @param name Full name of option. (ex. "foo") Note that rest of the module uses longer names to manipulate opts.
//! @param desc Description shown in the help screen.
//! @param type Option's type (see zpl_opts_types)
//! @see zpl_opts_types
ZPL_DEF void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, zpl_u8 type);

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
ZPL_DEF zpl_b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv);

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
ZPL_DEF zpl_f64 zpl_opts_real(zpl_opts *opts, char const *name, zpl_f64 fallback);

//! Fetches an integer number from an option.

//! @param opts
//! @param name Name of an option.
//! @param fallback Fallback integer number we return if option was not found.
ZPL_DEF zpl_i64 zpl_opts_integer(zpl_opts *opts, char const *name, zpl_i64 fallback);

//! Checks whether an option was used.

//! @param opts
//! @param name Name of an option.
ZPL_DEF zpl_b32 zpl_opts_has_arg(zpl_opts *opts, char const *name);

//! Checks whether all positionals have been passed in.
ZPL_DEF zpl_b32 zpl_opts_positionals_filled(zpl_opts *opts);

//! @}
