// file: header/core/print.h

/** @file print.c
@brief Printing methods
@defgroup print Printing methods

Various printing methods.
@{
*/
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#ifndef ZPL_PRINTF_MAXLEN
#define ZPL_PRINTF_MAXLEN 4096
#endif

ZPL_DEF zpl_isize zpl_printf(char const *fmt, ...);
ZPL_DEF zpl_isize zpl_printf_va(char const *fmt, va_list va);
ZPL_DEF zpl_isize zpl_printf_err(char const *fmt, ...);
ZPL_DEF zpl_isize zpl_printf_err_va(char const *fmt, va_list va);
ZPL_DEF zpl_isize zpl_fprintf(zpl_file *f, char const *fmt, ...);
ZPL_DEF zpl_isize zpl_fprintf_va(zpl_file *f, char const *fmt, va_list va);

// NOTE: A locally persisting buffer is used internally
ZPL_DEF char *zpl_bprintf(char const *fmt, ...);

// NOTE: A locally persisting buffer is used internally
ZPL_DEF char *zpl_bprintf_va(char const *fmt, va_list va);

ZPL_DEF zpl_isize zpl_asprintf(zpl_allocator allocator, char **buffer, char const *fmt, ...);
ZPL_DEF zpl_isize zpl_asprintf_va(zpl_allocator allocator, char **buffer, char const *fmt, va_list va);

ZPL_DEF zpl_isize zpl_snprintf(char *str, zpl_isize n, char const *fmt, ...);
ZPL_DEF zpl_isize zpl_snprintf_va(char *str, zpl_isize n, char const *fmt, va_list va);

ZPL_END_C_DECLS
