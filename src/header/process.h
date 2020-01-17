/** @file process.c
@brief Process creation and manipulation methods
@defgroup process Process creation and manipulation methods

Gives you the ability to create a new process, wait for it to end or terminate it.
It also exposes standard I/O with configurable options.

@{
*/

// TODO(zaklaus): Add Linux support

typedef enum {
    ZPL_PR_OPTS_COMBINE_STD_OUTPUT  = ZPL_BIT(1),
    ZPL_PR_OPTS_INHERIT_ENV         = ZPL_BIT(2),
    ZPL_PR_OPTS_CUSTOM_ENV          = ZPL_BIT(3),
} zpl_pr_opts;

typedef struct {
    zpl_file in, out, err;
    void *f_stdin, *f_stdout, *f_stderr;
#ifdef ZPL_SYSTEM_WINDOWS
    HANDLE win32_handle;
#else
    // todo
#endif
} zpl_pr;

typedef struct {
    char *con_title;
    char *workdir;

    zpl_isize env_count;
    char **env; // format: "var=name"

    zpl_u32 posx, posy;
    zpl_u32 resx, resy;
    zpl_u32 bufx, bufy;
    zpl_u32 fill_attr;
    zpl_u32 flags;
    zpl_b32 show_window;
} zpl_pr_si;

ZPL_DEF zpl_i32 zpl_pr_create(zpl_pr *process, const char **args, zpl_isize argc, zpl_pr_si si, zpl_pr_opts options);
ZPL_DEF void    zpl_pr_destroy(zpl_pr *process);
ZPL_DEF void    zpl_pr_terminate(zpl_pr *process, zpl_i32 err_code);
ZPL_DEF zpl_i32 zpl_pr_join(zpl_pr *process);

//! @}
