////////////////////////////////////////////////////////////////
//
// Regex
//
// Based on https://github.com/gingerBill/zpl_/blob/master/gb_regex.h
//
/* 
Supported Matching:
    ^       - Beginning of string
    $       - End of string
    .       - Match one (anything)
    |       - Branch (or)
    ()      - Capturing group
    []      - Any character included in set
    [^]     - Any character excluded from set
    +       - One or more  (greedy)
    +?      - One or more  (non-greedy)
    *       - Zero or more (greedy)
    *?      - Zero or more (non-greedy)
    ?       - Zero or once
    \XX     - Hex decimal digit (must be 2 digits)
    \meta   - Meta character
    \s      - Whitespace
    \S      - Not whitespace
    \d      - Digit
    \D      - Not digit
    \a      - Alphabetic character
    \l      - Lower case letter
    \u      - Upper case letter
    \w      - Word
    \W      - Not word
    \x      - Hex Digit
    \p      - Printable ASCII character
    --Whitespace--
    \t      - Tab
    \n      - New line
    \r      - Return carriage
    \v      - Vertical Tab
    \f      - Form feed
*/

typedef struct zpl_re {
    zpl_allocator backing;
    isize capture_count;
    char *buf;
    isize buf_len, buf_cap;
    b32 can_realloc;
} zpl_re;

typedef struct zpl_re_capture {
    char const *str;
    isize len;
} zpl_re_capture;

typedef enum zplreError {
    ZPL_RE_ERROR_NONE,
    ZPL_RE_ERROR_NO_MATCH,
    ZPL_RE_ERROR_TOO_LONG,
    ZPL_RE_ERROR_MISMATCHED_CAPTURES,
    ZPL_RE_ERROR_MISMATCHED_BLOCKS,
    ZPL_RE_ERROR_BRANCH_FAILURE,
    ZPL_RE_ERROR_INVALID_QUANTIFIER,
    ZPL_RE_ERROR_INTERNAL_FAILURE,
} zplreError;

ZPL_DEF zplreError zpl_re_compile(zpl_re *re, zpl_allocator backing, char const *pattern, isize pattern_len);
ZPL_DEF zplreError zpl_re_compile_from_buffer(zpl_re *re, char const *pattern, isize pattern_len, void *buffer, isize buffer_len);
ZPL_DEF void       zpl_re_destroy(zpl_re *re);
ZPL_DEF isize      zpl_re_capture_count(zpl_re *re);
ZPL_DEF b32        zpl_re_match(zpl_re *re, char const *str, isize str_len, zpl_re_capture *captures, isize max_capture_count);

//!!

typedef enum zplreOp {
	ZPL_RE_OP_BEGIN_CAPTURE,
	ZPL_RE_OP_END_CAPTURE,

    ZPL_RE_OP_BEGINNING_OF_LINE,
	ZPL_RE_OP_END_OF_LINE,

	ZPL_RE_OP_EXACT_MATCH,
	ZPL_RE_OP_META_MATCH,

	ZPL_RE_OP_ANY,
	ZPL_RE_OP_ANY_OF,
	ZPL_RE_OP_ANY_BUT,

	ZPL_RE_OP_ZERO_OR_MORE,
	ZPL_RE_OP_ONE_OR_MORE,
	ZPL_RE_OP_ZERO_OR_MORE_SHORTEST,
	ZPL_RE_OP_ONE_OR_MORE_SHORTEST,
	ZPL_RE_OP_ZERO_OR_ONE,

	ZPL_RE_OP_BRANCH_START,
	ZPL_RE_OP_BRANCH_END
} zplreOp;

typedef enum zplreCode {
	ZPL_RE_CODE_NULL              = 0x0000,
	ZPL_RE_CODE_WHITESPACE        = 0x0100,
	ZPL_RE_CODE_NOT_WHITESPACE    = 0x0200,
	ZPL_RE_CODE_DIGIT             = 0x0300,
	ZPL_RE_CODE_NOT_DIGIT         = 0x0400,
	ZPL_RE_CODE_ALPHA             = 0x0500,
	ZPL_RE_CODE_LOWER             = 0x0600,
	ZPL_RE_CODE_UPPER             = 0x0700,
	ZPL_RE_CODE_WORD              = 0x0800,
	ZPL_RE_CODE_NOT_WORD          = 0x0900,

	ZPL_RE_CODE_XDIGIT            = 0x0a00,
	ZPL_RE_CODE_PRINTABLE         = 0x0b00,
} zplreCode;

typedef struct {
    isize op, offset;
} zpl_re_ctx;

enum {
    ZPL_RE__NO_MATCH = -1,
    ZPL_RE__INTERNAL_FAILURE = -2,
};

static char const ZPL_RE__META_CHARS[] = "^$()[].*+?|\\";
static char const ZPL_RE__WHITESPACE[] = " \r\t\n\v\f";
#define ZPL_RE__LITERAL(str) (str), zpl_size_of(str)-1

static zpl_re_ctx zpl_re__exec_single(zpl_re *re, isize op, char const *str, isize str_len, isize offset, zpl_re_capture *captures, isize max_capture_count);
static zpl_re_ctx zpl_re__exec(zpl_re *re, isize op, char const *str, isize str_len, isize offset, zpl_re_capture *captures, isize max_capture_count);

static zpl_re_ctx zpl_re__ctx_no_match(isize op) {
    zpl_re_ctx c;
    c.op = op;
    c.offset = ZPL_RE__NO_MATCH;
    return c;
}

static zpl_re_ctx zpl_re__ctx_internal_failure(isize op) {
    zpl_re_ctx c;
    c.op = op;
    c.offset = ZPL_RE__INTERNAL_FAILURE;
    return c;
}

static u8 zpl_re__hex(char const *s) {
    return ((zpl_char_to_hex_digit(*s) << 4) & 0xf0) | (zpl_char_to_hex_digit(*(s+1)) & 0x0f);
}

static isize zpl_re__strfind(char const *s, isize len, char c, isize offset) {
    if (offset < len) {
        char const *found = (char const *)zpl_memchr(s+offset, c, len-offset);
        if (found)
            return found - s;
    }

    return -1;
}

static b32 zpl_re__match_escape(char c, int code) {
	switch (code) {
	case ZPL_RE_CODE_NULL:           return c == 0;
	case ZPL_RE_CODE_WHITESPACE:     return zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__WHITESPACE), c, 0) >= 0;
	case ZPL_RE_CODE_NOT_WHITESPACE: return zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__WHITESPACE), c, 0) < 0;
	case ZPL_RE_CODE_DIGIT:          return (c >= '0' && c <= '9');
	case ZPL_RE_CODE_NOT_DIGIT:      return !(c >= '0' && c <= '9');
	case ZPL_RE_CODE_ALPHA:          return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	case ZPL_RE_CODE_LOWER:          return (c >= 'a' && c <= 'z');
	case ZPL_RE_CODE_UPPER:          return (c >= 'A' && c <= 'Z');

	/* TODO(bill): Make better? */
	case ZPL_RE_CODE_WORD:           return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_';
	case ZPL_RE_CODE_NOT_WORD:       return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');

	/* TODO(bill): Maybe replace with between tests? */
	case ZPL_RE_CODE_XDIGIT:         return zpl_re__strfind(ZPL_RE__LITERAL("0123456789ABCDEFabcdef"), c, 0) >= 0;
	case ZPL_RE_CODE_PRINTABLE:      return c >= 0x20 && c <= 0x7e;
	default: break;
	}

	return 0;
}

static zpl_re_ctx zpl_re__consume(zpl_re *re, isize op, char const *str, isize str_len, isize offset, zpl_re_capture *captures, isize max_capture_count, b32 is_greedy)
{
    zpl_re_ctx c, best_c, next_c;

    c.op = op;
    c.offset = offset;

    best_c.op = ZPL_RE__NO_MATCH;
    best_c.offset = offset;
    
    for (;;) {
        c = zpl_re__exec_single(re, op, str, str_len, c.offset, 0, 0);
        if (c.offset > str_len || c.offset == -1) break;
        if (c.op >= re->buf_len) return c;

        next_c = zpl_re__exec(re, c.op, str, str_len, c.offset, captures, max_capture_count);
        if (next_c.offset <= str_len) {
            if (captures)
                zpl_re__exec(re, c.op, str, str_len, c.offset, captures, max_capture_count);
            
            best_c = next_c;
            if (!is_greedy) break;
        }

        if (best_c.op > re->buf_len)
            best_c.op = c.op;

    }

    return best_c;
}

static zpl_re_ctx zpl_re__exec_single(zpl_re *re, isize op, char const *str, isize str_len, isize offset, zpl_re_capture *captures, isize max_capture_count) {
    zpl_re_ctx ctx;
    isize buffer_len;
    isize match_len;
    isize next_op;
    isize skip;

    switch (re->buf[op++]) {
        case ZPL_RE_OP_BEGIN_CAPTURE: {
            u8 capture = re->buf[op++];
            if (captures && (capture < max_capture_count))
                captures[capture].str = str + offset;
        } break;

        case ZPL_RE_OP_END_CAPTURE: {
            u8 capture = re->buf[op++];
            if (captures && (capture < max_capture_count))
                captures[capture].len = (str + offset) - captures[capture].str;
        } break;

        case ZPL_RE_OP_BEGINNING_OF_LINE: {
            if (offset != 0)
                return zpl_re__ctx_no_match(op);
        } break;

        case ZPL_RE_OP_END_OF_LINE: {
            if (offset != str_len)
                return zpl_re__ctx_no_match(op);
        } break;

        case ZPL_RE_OP_BRANCH_START: {
            skip = re->buf[op++];
            ctx = zpl_re__exec(re, op, str, str_len, offset, captures, max_capture_count);
            if (ctx.offset <= str_len) {
                offset = ctx.offset;
                op = ctx.op;
            } else {
                ctx = zpl_re__exec(re, op + skip, str, str_len, offset, captures, max_capture_count);
                offset = ctx.offset;
                op = ctx.op;
            }
        } break;

        case ZPL_RE_OP_BRANCH_END: {
            skip = re->buf[op++];
            op += skip;
        } break;

        case ZPL_RE_OP_ANY: {
            if (offset < str_len) {
                offset++;
                break;
            }
            return zpl_re__ctx_no_match(op);
        } break;

        case ZPL_RE_OP_ANY_OF: {
            isize i;
            char cin = str[offset];
            buffer_len = re->buf[op++];

            if (offset >= str_len)
                return zpl_re__ctx_no_match(op + buffer_len);

            for (i = 0; i < buffer_len; i++) {
                char cmatch = (char)re->buf[op+i];
                if (!cmatch) {
                    i++;
                    if (zpl_re__match_escape(cin, re->buf[op+i] << 8))
                        break;
                } else if (cin == cmatch) {
                    break;
                }
            }

            if (i == buffer_len)
                return zpl_re__ctx_no_match(op + buffer_len);

            offset++;
            op += buffer_len;
        } break;

        case ZPL_RE_OP_ANY_BUT: {
            isize i;
            char cin = str[offset];
            buffer_len = re->buf[op++];

            if (offset >= str_len)
                return zpl_re__ctx_no_match(op + buffer_len);

            for (i = 0; i < buffer_len; i++) {
                char cmatch = (char)re->buf[op + i];
                if (!cmatch) {
                    i++;
                    if (zpl_re__match_escape(cin, re->buf[op+i] << 8))
                        return zpl_re__ctx_no_match(op + buffer_len);
                } else if (cin == cmatch) {
                    return zpl_re__ctx_no_match(op + buffer_len);
                }
            }

            offset++;
            op += buffer_len;
        } break;

        case ZPL_RE_OP_EXACT_MATCH: {
            match_len = re->buf[op++];
            
            if ((match_len > (str_len - offset)) ||
                zpl_strncmp(str+offset, (const char*)re->buf + op, match_len) != 0)
                return zpl_re__ctx_no_match(op + match_len);

            op += match_len;
            offset += match_len;
        } break;

        case ZPL_RE_OP_META_MATCH: {
            char cin = (char)re->buf[op++];
            char cmatch = str[offset++];
            
            if (!cin) {
                if (zpl_re__match_escape(cmatch, re->buf[op++] << 8))
                    break;
            }
            else if (cin == cmatch) break;

            return zpl_re__ctx_no_match(op);
        } break;

        case ZPL_RE_OP_ZERO_OR_MORE: {
            ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 1);
            offset = ctx.offset;
            op = ctx.op;
        } break;

        case ZPL_RE_OP_ONE_OR_MORE: {
            ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);
            
            if (ctx.offset > str_len)
                return ctx;
                
            ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 1);
            offset = ctx.offset;
            op = ctx.op;
        } break;

        case ZPL_RE_OP_ZERO_OR_MORE_SHORTEST: {
            ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 0);
            offset = ctx.offset;
            op = ctx.op;
        } break;
        
        case ZPL_RE_OP_ONE_OR_MORE_SHORTEST: {
            ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);
            
            if (ctx.offset > str_len)
                return ctx;
                
            ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 0);
            offset = ctx.offset;
            op = ctx.op;
        } break;

        case ZPL_RE_OP_ZERO_OR_ONE: {
            ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);

            if (ctx.offset <= str_len) {
                zpl_re_ctx possible_ctx = zpl_re__exec(re, ctx.op, str, str_len, ctx.offset, captures, max_capture_count);

                if (possible_ctx.offset <= str_len) {
                    op = possible_ctx.op;
                    offset = possible_ctx.offset;
                    break;
                }
            }

            next_op = ctx.op;
            ctx = zpl_re__exec(re, next_op, str, str_len, offset, captures, max_capture_count);

            if (ctx.offset <= str_len) {
                op = ctx.op;
                offset = ctx.offset;
                break;
            }
            return zpl_re__ctx_no_match(op);
        } break;

        default: {
            return zpl_re__ctx_internal_failure(op);
        } break;
    }

    ctx.op = op;
    ctx.offset = offset;

    return ctx;
}

static zpl_re_ctx zpl_re__exec(zpl_re *re, isize op, char const *str, isize str_len, isize offset, zpl_re_capture *captures, isize max_capture_count) {
    zpl_re_ctx c;
    c.op = op;
    c.offset = offset;

    while (c.op < re->buf_len) {
        c = zpl_re__exec_single(re, c.op, str, str_len, c.offset, captures, max_capture_count);

        if (c.offset > str_len)
            break;
    }

    return c;
}

static zplreError zpl_re__emit_ops(zpl_re *re, isize op_count, ...) {
    va_list va;

    if (re->buf_len + op_count > re->buf_cap) {
        if (!re->can_realloc) {
            return ZPL_RE_ERROR_TOO_LONG;
        }
        else {
            isize new_cap = (re->buf_cap*2) + op_count;
            re->buf = (char *)zpl_resize(re->backing, re->buf, re->buf_cap, new_cap);
            re->buf_cap = new_cap;
        }
    }

    va_start(va, op_count);
    for (isize i = 0; i < op_count; i++)
    {
        i32 v = va_arg(va, i32);
        if (v > 256)
            return ZPL_RE_ERROR_TOO_LONG;
        re->buf[re->buf_len++] = (char)v;
    }
    va_end(va);
    
    return ZPL_RE_ERROR_NONE;
}

static zplreError zpl_re__emit_ops_buffer(zpl_re *re, isize op_count, char const *buffer) {
    if (re->buf_len + op_count > re->buf_cap) {
        if (!re->can_realloc) {
            return ZPL_RE_ERROR_TOO_LONG;
        }
        else {
            isize new_cap = (re->buf_cap*2) + op_count;
            re->buf = (char *)zpl_resize(re->backing, re->buf, re->buf_cap, new_cap);
            re->buf_cap = new_cap;
        }
    }

    for (isize i = 0; i < op_count; i++)
    {
        re->buf[re->buf_len++] = buffer[i];
    }
    
    return ZPL_RE_ERROR_NONE;
}

static int zpl_re__encode_escape(char code) {
	switch (code) {
	default:   break; /* NOTE(bill): It's a normal character */

	/* TODO(bill): Are there anymore? */
	case 't':  return '\t';
	case 'n':  return '\n';
	case 'r':  return '\r';
	case 'f':  return '\f';
	case 'v':  return '\v';

	case '0':  return ZPL_RE_CODE_NULL;

	case 's':  return ZPL_RE_CODE_WHITESPACE;
	case 'S':  return ZPL_RE_CODE_NOT_WHITESPACE;

	case 'd':  return ZPL_RE_CODE_DIGIT;
	case 'D':  return ZPL_RE_CODE_NOT_DIGIT;

	case 'a':  return ZPL_RE_CODE_ALPHA;
	case 'l':  return ZPL_RE_CODE_LOWER;
	case 'u':  return ZPL_RE_CODE_UPPER;

	case 'w':  return ZPL_RE_CODE_WORD;
	case 'W':  return ZPL_RE_CODE_NOT_WORD;

	case 'x':  return ZPL_RE_CODE_XDIGIT;
	case 'p':  return ZPL_RE_CODE_PRINTABLE;
	}
	return code;
}

static zplreError zpl_re__parse_group(zpl_re *re, char const *pattern, isize len, isize offset, isize *new_offset) {
    zplreError err = ZPL_RE_ERROR_NONE;
    unsigned char buffer[256] = {0};
    isize buffer_len = 0, buffer_cap = zpl_size_of(buffer);
    b32 closed = 0;
    zplreOp op = ZPL_RE_OP_ANY_OF;

    if (pattern[offset] == '^') {
        offset++;
        op = ZPL_RE_OP_ANY_BUT;
    }

    while(!closed &&
            err == ZPL_RE_ERROR_NONE &&
            offset < len)
    {
        if (pattern[offset] == ']') {
            err = zpl_re__emit_ops(re, 2, (i32)op, (i32)buffer_len);
            if (err) break;

            err = zpl_re__emit_ops_buffer(re, buffer_len, buffer);
            if (buffer && err) break;
            offset++;
            closed = 1;
            break;
        }

        if (buffer_len >= buffer_cap)
            return ZPL_RE_ERROR_TOO_LONG;

        if (pattern[offset] == '\\') {
            offset++;

            if ((offset + 1 < len) && zpl_char_is_hex_digit(*(pattern+offset))) {
                buffer[buffer_len++] = zpl_re__hex((pattern+offset));
                offset++;
            }
            else if (offset < len) {
                i32 code = zpl_re__encode_escape(pattern[offset]);

                if (!code || code > 0xff) {
                    buffer[buffer_len++] = 0;

                    if (buffer_len >= buffer_cap)
                        return ZPL_RE_ERROR_TOO_LONG;
                    
                    buffer[buffer_len++] = (code >> 8) & 0xff;
                }
                else {
                    buffer[buffer_len++] = code & 0xff;
                }
            }
        }
        else {
            buffer[buffer_len++] = (unsigned char)pattern[offset];
        }

        offset++;
    }

    if (err) return err;
    if (!closed) return ZPL_RE_ERROR_MISMATCHED_BLOCKS;
    if (new_offset) *new_offset = offset;
    return ZPL_RE_ERROR_NONE;
}

static zplreError zpl_re__compile_quantifier(zpl_re *re, isize last_buf_len, unsigned char quantifier) {
    zplreError err;
    isize move_size;

    if ((re->buf[last_buf_len] == ZPL_RE_OP_EXACT_MATCH) &&
        (re->buf[last_buf_len+1] > 1)) 
    {    
        unsigned char last_char = re->buf[re->buf_len-1];

        re->buf[last_buf_len+1]--;
        re->buf_len--;
        err = zpl_re__emit_ops(re, 4, (i32)quantifier, (i32)ZPL_RE_OP_EXACT_MATCH, 1, (i32)last_char);
        if (err) return err;
        return ZPL_RE_ERROR_NONE;
    }

    move_size = re->buf_len - last_buf_len + 1;

    err = zpl_re__emit_ops(re, 1, 0);
    if (err) return err;

    zpl_memmove(re->buf+last_buf_len+1, re->buf+last_buf_len, move_size);
    re->buf[last_buf_len] = quantifier;

    return ZPL_RE_ERROR_NONE;
}

static zplreError zpl_re__parse(zpl_re *re, char const *pattern, isize len, isize offset, isize level, isize *new_offset) {
    zplreError err = ZPL_RE_ERROR_NONE;
    isize last_buf_len = re->buf_len;
    isize branch_begin = re->buf_len;
    isize branch_op = -1;

    while (offset < len) {
        switch (pattern[offset++]) {
            case '^': {
                err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_BEGINNING_OF_LINE);
                if (err) return err;
            } break;

            case '$': {
                err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_END_OF_LINE);
                if (err) return err;
            } break;

            case '(': {
                isize capture = re->capture_count++;
                last_buf_len = re->buf_len;
                err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_BEGIN_CAPTURE, (i32)capture);
                if (err) return err;

                err = zpl_re__parse(re, pattern, len, offset, level+1, &offset);

                if ((offset > len) || (pattern[offset-1] != ')'))
                    return ZPL_RE_ERROR_MISMATCHED_CAPTURES;

                err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_END_CAPTURE, (i32)capture);
                if (err) return err;
            } break;

            case ')': {
                if (branch_op != -1)
                    re->buf[branch_op + 1] = (unsigned char)(re->buf_len - (branch_op+2));

                if (level == 0)
                    return ZPL_RE_ERROR_MISMATCHED_CAPTURES;
                
                if (new_offset) *new_offset = offset;
                return ZPL_RE_ERROR_NONE;
            } break;

            case '[': {
                last_buf_len = re->buf_len;
                err = zpl_re__parse_group(re, pattern, len, offset, &offset);
                if (offset > len)
                    return err;
            } break;

            /* NOTE(bill): Branching magic! */
            case '|': {
                if (branch_begin >= re->buf_len) {
                    return ZPL_RE_ERROR_BRANCH_FAILURE;
                } else {
                    isize size = re->buf_len - branch_begin;
                    err = zpl_re__emit_ops(re, 4, 0, 0, ZPL_RE_OP_BRANCH_END, 0);
                    if (err) return err;

                    zpl_memmove(re->buf + branch_begin + 2, re->buf + branch_begin, size);
                    re->buf[branch_begin] = ZPL_RE_OP_BRANCH_START;
                    re->buf[branch_begin+1] = (size+2) & 0xff;
                    branch_op = re->buf_len-2;
                }
            } break;

            case '.': {
                last_buf_len = re->buf_len;
                err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_ANY);
                if (err) return err;
            } break;

            case '*':
            case '+':
            {
                unsigned char quantifier = ZPL_RE_OP_ONE_OR_MORE;
                if (pattern[offset-1] == '*')
                    quantifier = ZPL_RE_OP_ZERO_OR_MORE;

                if (last_buf_len >= re->buf_len)
                    return ZPL_RE_ERROR_INVALID_QUANTIFIER;
                if ((re->buf[last_buf_len] < ZPL_RE_OP_EXACT_MATCH) ||
                        (re->buf[last_buf_len] > ZPL_RE_OP_ANY_BUT))
                    return ZPL_RE_ERROR_INVALID_QUANTIFIER;

                if ((offset < len) && (pattern[offset] == '?')) {
                    quantifier = ZPL_RE_OP_ONE_OR_MORE_SHORTEST;
                    if (quantifier == ZPL_RE_OP_ZERO_OR_MORE)
                        quantifier = ZPL_RE_OP_ZERO_OR_MORE_SHORTEST;
                    offset++;
                }

                err = zpl_re__compile_quantifier(re, last_buf_len, quantifier);
                if (err) return err;
            } break;

            case '?': {
                if (last_buf_len >= re->buf_len)
                    return ZPL_RE_ERROR_INVALID_QUANTIFIER;
                if ((re->buf[last_buf_len] < ZPL_RE_OP_EXACT_MATCH) ||
                        (re->buf[last_buf_len] > ZPL_RE_OP_ANY_BUT))
                    return ZPL_RE_ERROR_INVALID_QUANTIFIER;

                err = zpl_re__compile_quantifier(re, last_buf_len,
                                            (unsigned char)ZPL_RE_OP_ZERO_OR_ONE);
                if (err) return err;
            } break;

            case '\\': {
                last_buf_len = re->buf_len;
                if ((offset+1 < len) && zpl_char_is_hex_digit(*(pattern+offset))) {
                    unsigned char hex_value = zpl_re__hex((pattern+offset));
                    offset += 2;
                    err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_META_MATCH, (int)hex_value);
                    if (err) return err;
                } else if (offset < len) {
                    int code = zpl_re__encode_escape(pattern[offset++]);
                    if (!code || (code > 0xff)) {
                        err = zpl_re__emit_ops(re, 3, ZPL_RE_OP_META_MATCH, 0, (int)((code >> 8) & 0xff));
                        if (err) return err;
                    } else {
                        err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_META_MATCH, (int)code);
                        if (err) return err;
                    }
                }
            } break;

            /* NOTE(bill): Exact match */
            default: {
                char const *match_start;
                isize size = 0;
                offset--;
                match_start = pattern+offset;
                while ((offset < len) &&
                        (zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__META_CHARS), pattern[offset], 0) < 0)) {
                    size++, offset++;
                }

                last_buf_len = re->buf_len;
                err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_EXACT_MATCH, (int)size);
                if (err) return err;
                err = zpl_re__emit_ops_buffer(re, size, (unsigned char const *)match_start);
                if (err) return err;
            } break;
        }
    }

    if (new_offset) *new_offset = offset;
    return ZPL_RE_ERROR_NONE;
}

zplreError zpl_re_compile_from_buffer(zpl_re *re, char const *pattern, isize pattern_len, void *buffer, isize buffer_len) {
    zplreError err;
    re->capture_count = 0;
    re->buf = (unsigned char *)buffer;
    re->buf_len = 0;
    re->buf_cap = re->buf_len;
    re->can_realloc = 0;

    err = zpl_re__parse(re, pattern, pattern_len, 0, 0, 0);
    return err;
}

zplreError zpl_re_compile(zpl_re *re, zpl_allocator backing, char const *pattern, isize pattern_len) {
    zplreError err;
    isize cap = pattern_len+128;
    isize offset = 0;

    re->backing = backing;
    re->capture_count = 0;
    re->buf = (unsigned char *)zpl_alloc(backing, cap);
    re->buf_len = 0;
    re->buf_cap = cap;
    re->can_realloc = 1;

    err = zpl_re__parse(re, pattern, pattern_len, 0, 0, &offset);

    if (offset != pattern_len)
        zpl_free(backing, re->buf);

    return err;
}

isize zpl_re_capture_count(zpl_re *re) { return re->capture_count; }

b32 zpl_re_match(zpl_re *re, char const *str, isize len, zpl_re_capture *captures, isize max_capture_count) {
	if (re && re->buf_len > 0) {
		if (re->buf[0] == ZPL_RE_OP_BEGINNING_OF_LINE) {
			zpl_re_ctx c = zpl_re__exec(re, 0, str, len, 0, captures, max_capture_count);
			if (c.offset >= 0 && c.offset <= len)   return 1;
			if (c.offset == ZPL_RE__INTERNAL_FAILURE) return 0;
		} else {
			isize i;
			for (i = 0; i < len; i++) {
				zpl_re_ctx c = zpl_re__exec(re, 0, str, len, i, captures, max_capture_count);
				if (c.offset >= 0 && c.offset <= len)   return 1;
				if (c.offset == ZPL_RE__INTERNAL_FAILURE) return 0;
			}
		}
		return 0;
	}
	return 1;
}
