/** @file dll.c
@brief DLL Handling
@defgroup dll DLL handling

@{
*/

typedef void *zpl_dll_handle;
typedef void (*zpl_dll_proc)(void);

ZPL_DEF zpl_dll_handle zpl_dll_load(char const *filepath);
ZPL_DEF void           zpl_dll_unload(zpl_dll_handle dll);
ZPL_DEF zpl_dll_proc   zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// DLL Handling
//
//

#if defined(ZPL_SYSTEM_WINDOWS)

zpl_dll_handle zpl_dll_load(char const *filepath) { return cast(zpl_dll_handle) LoadLibraryA(filepath); }
zpl_inline void zpl_dll_unload(zpl_dll_handle dll) { FreeLibrary(cast(HMODULE) dll); }
zpl_inline zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
    return cast(zpl_dll_proc) GetProcAddress(cast(HMODULE) dll, proc_name);
}

#else // POSIX

zpl_dll_handle zpl_dll_load(char const *filepath) {
    return cast(zpl_dll_handle) dlopen(filepath, RTLD_LAZY | RTLD_GLOBAL);
}

zpl_inline void zpl_dll_unload(zpl_dll_handle dll) { dlclose(dll); }
zpl_inline zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
    return cast(zpl_dll_proc) dlsym(dll, proc_name);
}

#endif
