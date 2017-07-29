/*

ZPL - JSON parser module

License:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.
    
Warranty:
    No warranty is implied, use at your own risk.
    
Usage:
    #define ZPL_JSON_IMPLEMJSONATION exactly in ONE source file right BEFORE including the library, like:
    
    #define ZPL_JSON_IMPLEMJSONATION
    #include"zpl_json.h"
    
Credits:
    Dominik Madarasz (GitHub: zaklaus)
    
Version History:
    1.00 - Initial version
    
*/

#ifndef ZPL_INCLUDE_ZPL_JSON_H
#define ZPL_INCLUDE_ZPL_JSON_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum zpl_json_type_e {
        zpl_json_type_object_ev,
        zpl_json_type_string_ev,
        zpl_json_type_array_ev,
        zpl_json_type_integer_ev,
        zpl_json_type_real_ev,
        zpl_json_type_constant_ev
    } zpl_json_type_e;
    
    typedef enum zpl_json_constant_e {
        zpl_json_constant_null_ev,
        zpl_json_constant_false_ev,
        zpl_json_constant_true_ev,
    } zpl_json_constant_e;
    
    typedef struct zpl_json_object_t {
        zpl_allocator_t backing;
        char *name;
        u8    type;
        zpl_array_t(struct zpl_json_object_t) nodes;
        
        union {
            char *string;
            zpl_array_t(struct zpl_json_object_t) elements;
            i64   integer;
            f64   real;
            u8    constant;
        };
    } zpl_json_object_t;

    ZPL_DEF char*zpl_json_parse(zpl_json_object_t *root, usize len, char *const source, zpl_allocator_t a);
    ZPL_DEF void zpl_json_free (zpl_json_object_t *obj, char *str);
    
    ZPL_DEF char *zpl__json_parse_object(zpl_json_object_t *obj, char *base, zpl_allocator_t a);
    ZPL_DEF char *zpl__json_parse_value (zpl_json_object_t *obj, char *base, zpl_allocator_t a);
    ZPL_DEF char *zpl__json_parse_array (zpl_json_object_t *obj, char *base, zpl_allocator_t a);
    
    ZPL_DEF char *zpl__json_trim        (char *str);
    ZPL_DEF char *zpl__json_skip        (char *str, char c, b32 validate);
#ifdef __cplusplus
}
#endif 

#if defined(ZPL_JSON_IMPLEMENTATION) && !defined(ZPL_JSON_IMPLEMENTATION_DONE)
#define ZPL_JSON_IMPLEMENTATION_DONE

#ifdef __cplusplus
extern "C" {
#endif
    
    char *zpl_json_parse(zpl_json_object_t *root, usize len, char *const source, zpl_allocator_t a) {
        ZPL_ASSERT(root && source);
        
        char *dest = zpl_alloc(a, len+1);
        zpl_strncpy(dest, source, len);
        dest[len] = '\0';
        
        zpl_json_object_t root_ = {0};
        zpl__json_parse_object(&root_, dest, a);
        
        *root = root_;
        
        return dest;
    }
    
    void zpl_json_free(zpl_json_object_t *obj, char *str) {
        /**/ if (obj->type == zpl_json_type_array_ev) {
            for (isize i = 0; i < zpl_array_count(obj->elements); ++i) {
                zpl_json_free(obj->elements+i, 0);
            }
            
            zpl_array_free(obj->elements);
        }
        else if (obj->type == zpl_json_type_object_ev) {
            for (isize i = 0; i < zpl_array_count(obj->nodes); ++i) {
                zpl_json_free(obj->nodes+i, 0);
            }
            
            zpl_array_free(obj->nodes);
        }
        
        zpl_free(obj->backing, str);
    }
    
    char *zpl__json_parse_array(zpl_json_object_t *obj, char *base, zpl_allocator_t a) {
        ZPL_ASSERT(obj && base);
        char *p = base;
        
        obj->type = zpl_json_type_array_ev;
        zpl_array_init(obj->elements, a);
        obj->backing = a;
        
        while(*p) {
            p = zpl__json_trim(p);
            
            zpl_json_object_t elem = {0};
            p = zpl__json_parse_value(&elem, p, a);
            zpl_array_append(obj->elements, elem);
            
            if (*p == ',') {
                ++p;
                continue;
            }
            else {
                return p;
            }
        }
        return p;
    }
    
    char *zpl__json_parse_value(zpl_json_object_t *obj, char *base, zpl_allocator_t a) {
        ZPL_ASSERT(obj && base);
        char *p = base;
        char *b = base;
        char *e = base;
        
        /**/ if (*p == '"') {
            obj->type = zpl_json_type_string_ev;
            b = p+1;
            obj->string = b;
            
            e = zpl__json_skip(b, '"', false);
            *e = '\0';
            p = e+1;
        }
        else if (zpl_char_is_alpha(*p)) {
            obj->type = zpl_json_type_constant_ev;
            
            /**/ if (!zpl_strncmp(p, "true", 4)) {
                obj->constant = zpl_json_constant_true_ev;
                p += 4;
            }
            else if (!zpl_strncmp(p, "false", 5)) {
                obj->constant = zpl_json_constant_false_ev;
                p += 5;
            }
            else if (!zpl_strncmp(p, "null", 4)) {
                obj->constant = zpl_json_constant_null_ev;
                p += 4;
            }
            else {
                // TODO(ZaKlaus): Add better log
                zpl_printf("zpl_json.h: Failed to parse: '%s'!\n", p);
            }
        }
        else if (zpl_char_is_digit(*p)) {
            obj->type = zpl_json_type_integer_ev;
            
            b = p;
            e = b;
            
            isize ib = 0;
            zpl_local_persist char buf[128] = {0};
            
            while(zpl_char_is_hex_digit(*e) || *e == 'x' || *e == 'X') {
                buf[ib++] = *e++;
            }
            
            if (*e == '.') {
                obj->type = zpl_json_type_real_ev;
                
                do {
                    buf[ib++] = *e++;
                }
                while(zpl_char_is_hex_digit(*e));
            }
            
            ZPL_ASSERT(*e);
            buf[ib] = '\0';
            
            if (obj->type == zpl_json_type_integer_ev) {
                obj->integer = zpl_str_to_i64(buf, 0, 0);
            }
            else {
                obj->real = zpl_str_to_f64(buf, 0);            
            }
            
            p = e;
        }
        else if (*p == '[') {
            p = zpl__json_parse_array(obj, p+1, a);
            ++p;
        }
        else if (*p == '{') {
            p = zpl__json_parse_object(obj, p+1, a);
            ++p;
        }
        
        return p;
    }
    
    char *zpl__json_parse_object(zpl_json_object_t *obj, char *base, zpl_allocator_t a) {
        ZPL_ASSERT(obj && base);
        char *p = base;
        char *b = base;
        char *e = base;
        
        zpl_array_init(obj->nodes, a);
        obj->backing = a;
        
        while(*p) {
            zpl_json_object_t node = {0};
            p = zpl__json_trim(p);
            ZPL_ASSERT(*p == '"');
            b = ++p;
            
            node.name = b;
            
            e = zpl__json_skip(b, '"', true);
            *e = '\0';
            p = ++e;
            
            p = zpl__json_trim(p);
            
            ZPL_ASSERT(*p && *p == ':');
            
            p = zpl__json_trim(p+1);
            p = zpl__json_parse_value(&node, p, a);
            
            zpl_array_append(obj->nodes, node);
            
            p = zpl__json_trim(p);
            
            /**/ if (*p == ',') {
                ++p;
                continue;
            }
            else if (*p == '\0' || *p == '}') {
                return p;
            }
            else {
                // TODO(ZaKlaus): Add better log
                zpl_printf("zpl_json.h: Failed to parse: '%s'!\n", p);
            }
        }
        return p;
    }
    
    zpl_inline char *zpl__json_trim(char *str) {
        while (*str && zpl_char_is_space(*str)) {
            ++str;
        }
        
        return str;
    }
    
    zpl_inline b32 zpl__json_is_control_char(char c) {
        return (c == '"'  || c == '\\' || c == '/' || c == 'b' ||
                c == 'f' || c == 'n' || c == 'r'|| c == 't');
    }
    
#define jx(x) !zpl_char_is_hex_digit(str[x])
    zpl_inline b32 zpl__json_validate_name(char *str) {
        return (!(str[0] == '\\' && !zpl__json_is_control_char(str[1])) ||
                !(str[0] == '\\' && jx(1) && jx(2) && jx(3) && jx(4)) ||
                (zpl_char_is_alphanumeric(*str)) ||
                (zpl_char_is_space(*str)));
    }
#undef jx
    
    zpl_inline char *zpl__json_skip(char *str, char c, b32 validate) {
        while (*str && *str != c && (!validate || zpl__json_validate_name(str))) {
            ++str;
        }
        
        return str;
    }
    
    
#ifdef __cplusplus
}
#endif

#endif // ZPL_JSON_IMPLEMENTATION

#endif // ZPL_INCLUDE_ZPL_JSON_H