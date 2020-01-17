/** @file regex.c
@brief Regular expressions parser.
@defgroup regex Regex processor

Port of gb_regex with several bugfixes applied. This is a simple regex library and is fast to perform.

Supported Matching:
    @n ^       - Beginning of string
    @n $       - End of string
    @n .       - Match one (anything)
    @n |       - Branch (or)
    @n ()      - Capturing group
    @n []      - Any character included in set
    @n [^]     - Any character excluded from set
    @n +       - One or more  (greedy)
    @n +?      - One or more  (non-greedy)
    @n *       - Zero or more (greedy)
    @n *?      - Zero or more (non-greedy)
    @n ?       - Zero or once
    @n [BACKSLASH]XX     - Hex decimal digit (must be 2 digits)
    @n [BACKSLASH]meta   - Meta character
    @n [BACKSLASH]s      - Whitespace
    @n [BACKSLASH]S      - Not whitespace
    @n [BACKSLASH]d      - Digit
    @n [BACKSLASH]D      - Not digit
    @n [BACKSLASH]a      - Alphabetic character
    @n [BACKSLASH]l      - Lower case letter
    @n [BACKSLASH]u      - Upper case letter
    @n [BACKSLASH]w      - Word
    @n [BACKSLASH]W      - Not word
    @n [BACKSLASH]x      - Hex Digit
    @n [BACKSLASH]p      - Printable ASCII character
    @n --Whitespace--
    @n [BACKSLASH]t      - Tab
    @n [BACKSLASH]n      - New line
    @n [BACKSLASH]r      - Return carriage
    @n [BACKSLASH]v      - Vertical Tab
    @n [BACKSLASH]f      - Form feed

    @{
*/
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

typedef struct zpl_re {
    zpl_allocator backing;
    zpl_isize capture_count;
    char *buf;
    zpl_isize buf_len, buf_cap;
    zpl_b32 can_realloc;
} zpl_re;

typedef struct zpl_re_capture {
    char const *str;
    zpl_isize len;
} zpl_re_capture;

#define zplRegexError zpl_regex_error
typedef enum zpl_regex_error {
    ZPL_RE_ERROR_NONE,
    ZPL_RE_ERROR_NO_MATCH,
    ZPL_RE_ERROR_TOO_LONG,
    ZPL_RE_ERROR_MISMATCHED_CAPTURES,
    ZPL_RE_ERROR_MISMATCHED_BLOCKS,
    ZPL_RE_ERROR_BRANCH_FAILURE,
    ZPL_RE_ERROR_INVALID_QUANTIFIER,
    ZPL_RE_ERROR_INTERNAL_FAILURE,
} zpl_regex_error;

//! Compile regex pattern.
ZPL_DEF zpl_regex_error zpl_re_compile(zpl_re *re, zpl_allocator backing, char const *pattern, zpl_isize pattern_len);

//! Compile regex pattern using a buffer.
ZPL_DEF zpl_regex_error zpl_re_compile_from_buffer(zpl_re *re, char const *pattern, zpl_isize pattern_len, void *buffer, zpl_isize buffer_len);

//! Destroy regex object.
ZPL_DEF void            zpl_re_destroy(zpl_re *re);

//! Retrieve number of retrievable captures.
ZPL_DEF zpl_isize       zpl_re_capture_count(zpl_re *re);

//! Match input string and output captures of the occurence.
ZPL_DEF zpl_b32         zpl_re_match(zpl_re *re, char const *str, zpl_isize str_len, zpl_re_capture *captures, zpl_isize max_capture_count, zpl_isize *offset);

//! Match all occurences in an input string and output them into captures. Array of captures is allocated on the heap and needs to be freed afterwards.
ZPL_DEF zpl_b32         zpl_re_match_all(zpl_re *re, char const *str, zpl_isize str_len, zpl_isize max_capture_count, zpl_re_capture **out_captures);
