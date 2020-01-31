// file: source/process.c

////////////////////////////////////////////////////////////////
//
// Process creation and manipulation methods
//
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

static ZPL_ALWAYS_INLINE void zpl__pr_close_file_handle(zpl_file *f) {
    ZPL_ASSERT_NOT_NULL(f);
    f->fd.p  = NULL;
}

static ZPL_ALWAYS_INLINE void zpl__pr_close_file_handles(zpl_pr *process) {
    ZPL_ASSERT_NOT_NULL(process);

    zpl__pr_close_file_handle(&process->in);
    zpl__pr_close_file_handle(&process->out);
    zpl__pr_close_file_handle(&process->err);

    process->f_stdin = process->f_stdout = process->f_stderr = NULL;

#ifdef ZPL_SYSTEM_WINDOWS
    process->win32_handle = NULL;
#else
    ZPL_NOT_IMPLEMENTED;
#endif
}

enum {
    ZPL_PR_HANDLE_MODE_READ,
    ZPL_PR_HANDLE_MODE_WRITE,
    ZPL_PR_HANDLE_MODES,
};

void *zpl__pr_open_handle(zpl_u8 type, const char *mode, void **handle) {
#ifdef ZPL_SYSTEM_WINDOWS
    void *pipes[ZPL_PR_HANDLE_MODES];
    zpl_i32 fd;

    const zpl_u32 flag_inherit      = 0x00000001;
    SECURITY_ATTRIBUTES sa         = {zpl_size_of(sa), 0, 1};

    if (!CreatePipe(&pipes[0], &pipes[1], cast(LPSECURITY_ATTRIBUTES)&sa, 0)) {
        return NULL;
    }

    if (!SetHandleInformation(pipes[type], flag_inherit, 0)) {
        return NULL;
    }

    fd = _open_osfhandle(cast(zpl_intptr)pipes[type], 0);

    if (fd != -1) {
        *handle = pipes[1-type];
        return _fdopen(fd, mode);
    }

    return NULL;
#else
    ZPL_NOT_IMPLEMENTED;
    return NULL;
#endif
}

zpl_i32 zpl_pr_create(zpl_pr *process, const char **args, zpl_isize argc, zpl_pr_si si, zpl_pr_opts options) {
    ZPL_ASSERT_NOT_NULL(process);
    zpl_zero_item(process);

#ifdef ZPL_SYSTEM_WINDOWS
    zpl_string cli, env;
    zpl_b32 c_env=false;
    STARTUPINFOW psi = {0};
    PROCESS_INFORMATION pi = {0};
    zpl_i32 err_code = 0;
    zpl_allocator a = zpl_heap();
    const zpl_u32 use_std_handles   = 0x00000100;

    psi.cb = zpl_size_of(psi);
    psi.dwFlags = use_std_handles | si.flags;

    if (options & ZPL_PR_OPTS_CUSTOM_ENV) {
        env = zpl_string_join(zpl_heap(), cast(const char**)si.env, si.env_count, "\0\0");
        env = zpl_string_appendc(env, "\0");
        c_env = true;
    }
    else if (!(options & ZPL_PR_OPTS_INHERIT_ENV)) {
        env = (zpl_string)"\0\0\0\0";
    } else {
        env = (zpl_string)NULL;
    }

    process->f_stdin  = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_WRITE, "wb", &psi.hStdInput);
    process->f_stdout = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_READ, "rb", &psi.hStdOutput);

    if (options & ZPL_PR_OPTS_COMBINE_STD_OUTPUT) {
        process->f_stderr = process->f_stdout;
        psi.hStdError = psi.hStdOutput;
    } else {
        process->f_stderr = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_READ, "rb", &psi.hStdError);
    }

    cli = zpl_string_join(zpl_heap(), args, argc, " ");

    psi.dwX = si.posx;
    psi.dwY = si.posy;
    psi.dwXSize = si.resx;
    psi.dwYSize = si.resy;
    psi.dwXCountChars = si.bufx;
    psi.dwYCountChars = si.bufy;
    psi.dwFillAttribute = si.fill_attr;
    psi.wShowWindow = si.show_window;

    wchar_t *w_cli = zpl__alloc_utf8_to_ucs2(a, cli, NULL);
    wchar_t *w_workdir = zpl__alloc_utf8_to_ucs2(a, si.workdir, NULL);

    if (!CreateProcessW(
        NULL,
        w_cli,
        NULL,
        NULL,
        1,
        0,
        env,
        w_workdir,
        cast(LPSTARTUPINFOW)&psi,
        cast(LPPROCESS_INFORMATION)&pi
    )) {
        err_code = -1;
        goto pr_free_data;
    }

    process->win32_handle = pi.hProcess;
    CloseHandle(pi.hThread);

    zpl_file_connect_handle(&process->in, process->f_stdin);
    zpl_file_connect_handle(&process->out, process->f_stdout);
    zpl_file_connect_handle(&process->err, process->f_stderr);

pr_free_data:
    zpl_string_free(cli);
    zpl_free(a, w_cli);
    zpl_free(a, w_workdir);

    if (c_env)
            zpl_string_free(env);

    return err_code;

#else
    ZPL_NOT_IMPLEMENTED;
    return -1;
#endif
}


zpl_i32 zpl_pr_join(zpl_pr *process) {
    zpl_i32 ret_code;

    ZPL_ASSERT_NOT_NULL(process);

#ifdef ZPL_SYSTEM_WINDOWS
    if (process->f_stdin) {
        fclose(cast(FILE *)process->f_stdin);
    }

    WaitForSingleObject(process->win32_handle, INFINITE);

    if (!GetExitCodeProcess(process->win32_handle, cast(LPDWORD)&ret_code)) {
        zpl_pr_destroy(process);
        return -1;
    }

    zpl_pr_destroy(process);

    return ret_code;
#else
    ZPL_NOT_IMPLEMENTED;
    ret_code = -1;
    return ret_code;
#endif
}

void zpl_pr_destroy(zpl_pr *process) {
    ZPL_ASSERT_NOT_NULL(process);

#ifdef ZPL_SYSTEM_WINDOWS
    if (process->f_stdin) {
        fclose(cast(FILE *)process->f_stdin);
    }

    fclose(cast(FILE *)process->f_stdout);

    if (process->f_stderr != process->f_stdout) {
        fclose(cast(FILE *)process->f_stderr);
    }

    CloseHandle(process->win32_handle);

    zpl__pr_close_file_handles(process);
#else
    ZPL_NOT_IMPLEMENTED;
#endif
}

void zpl_pr_terminate(zpl_pr *process, zpl_i32 err_code) {
    ZPL_ASSERT_NOT_NULL(process);

#ifdef ZPL_SYSTEM_WINDOWS
    TerminateProcess(process->win32_handle, cast(UINT)err_code);
    zpl_pr_destroy(process);
#else
    ZPL_NOT_IMPLEMENTED;
#endif
}

ZPL_END_C_DECLS
