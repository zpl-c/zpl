// file: source/dll.c


#if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
#    include <dlfcn.h>
#endif

ZPL_BEGIN_C_DECLS

////////////////////////////////////////////////////////////////
//
// DLL Handling
//
//

#if defined(ZPL_SYSTEM_WINDOWS)
    zpl_dll_handle zpl_dll_load(char const *filepath) {
        return cast(zpl_dll_handle) LoadLibraryA(filepath);
    }

    void zpl_dll_unload(zpl_dll_handle dll) {
        FreeLibrary(cast(HMODULE) dll);
    }

    zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
        return cast(zpl_dll_proc) GetProcAddress(cast(HMODULE) dll, proc_name);
    }

#else // POSIX

    zpl_dll_handle zpl_dll_load(char const *filepath) {
        return cast(zpl_dll_handle) dlopen(filepath, RTLD_LAZY | RTLD_GLOBAL);
    }

    void zpl_dll_unload(zpl_dll_handle dll) {
        dlclose(dll);
    }

    zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
        return cast(zpl_dll_proc) dlsym(dll, proc_name);
    }

#endif

ZPL_END_C_DECLS
