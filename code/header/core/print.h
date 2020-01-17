/** @file print.c
@brief Printing methods
@defgroup print Printing methods

Various printing methods.
@{
*/

ZPL_DEF zpl_isize zpl_printf(char const *fmt, ...) ZPL_PRINTF_FORMAT(1, 2);
ZPL_DEF zpl_isize zpl_printf_va(char const *fmt, va_list va);
ZPL_DEF zpl_isize zpl_printf_err(char const *fmt, ...) ZPL_PRINTF_FORMAT(1, 2);
ZPL_DEF zpl_isize zpl_printf_err_va(char const *fmt, va_list va);
ZPL_DEF zpl_isize zpl_fprintf(zpl_file *f, char const *fmt, ...) ZPL_PRINTF_FORMAT(2, 3);
ZPL_DEF zpl_isize zpl_fprintf_va(zpl_file *f, char const *fmt, va_list va);

// NOTE: A locally persisting buffer is used internally
ZPL_DEF char *zpl_bprintf(char const *fmt, ...) ZPL_PRINTF_FORMAT(1, 2);

// NOTE: A locally persisting buffer is used internally
ZPL_DEF char *zpl_bprintf_va(char const *fmt, va_list va);

ZPL_DEF zpl_isize zpl_snprintf(char *str, zpl_isize n, char const *fmt, ...) ZPL_PRINTF_FORMAT(3, 4);
ZPL_DEF zpl_isize zpl_snprintf_va(char *str, zpl_isize n, char const *fmt, va_list va);
