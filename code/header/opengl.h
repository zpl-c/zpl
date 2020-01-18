/** @file opengl.c
@brief OpenGL helpers
@defgroup opengl OpenGL helpers

 Offers OpenGL helper methods as well as basic 2D graphics and font rendering.

 @{
 */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#ifndef ZPL_GLGEN_IMPLEMENTATION
#include "zpl_glgen.h"
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#if !defined(ZPLGL_NO_FONTS)
    #ifndef STB_RECT_PACK_IMPLEMENTATION
    #include "stb_rect_pack.h"
    #endif

    #ifndef STB_TRUETYPE_IMPLEMENTATION
    #include "stb_truetype.h"
    #endif
#endif

#define zplgl_lerp(x, y, t) zpl_lerp(x, y, t)
#define zplgl_sin(x)        zpl_sin(x)
#define zplgl_cos(x)        zpl_cos(x)
#define zplgl_abs(x)        zpl_abs(x)
#define zplgl_min(x, y)     zpl_min(x, y)
#define zplgl_max(x, y)     zpl_max(x, y)
#define zplgl_round(x)      zpl_round(x)

#define zplgl_clamp(x, lower, upper) zplgl_min(zplgl_max((x), (lower)), (upper))
#define zplgl_clamp01(x) zplgl_clamp(x, 0, 1)

    ////////////////////////////////////////////////////////////////
    //
    // Color Type
    //

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4201)
#endif

    typedef union zplgl_color {
        zpl_u32    rgba; // NOTE(bill): 0xaabbggrr in little endian
        struct     { zpl_u8 r, g, b, a; };
        zpl_u8     e[4];
    } zplgl_color;
    ZPL_STATIC_ASSERT(zpl_size_of(zplgl_color) == zpl_size_of(zpl_u32));

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


    ZPL_DEF zplgl_color zplgl_colorf(zpl_f32 r, zpl_f32 g, zpl_f32 b, zpl_f32 a);
    ZPL_DEF zplgl_color zplgl_color_opacity(zplgl_color color, zpl_f32 alpha);

    zpl_global zplgl_color const zplgl_color_white = { 0xffffffff };
    zpl_global zplgl_color const zplgl_color_grey = { 0xff808080 };
    zpl_global zplgl_color const zplgl_color_black = { 0xff000000 };

    zpl_global zplgl_color const zplgl_color_red = { 0xff0000ff };
    zpl_global zplgl_color const zplgl_color_orange = { 0xff0099ff };
    zpl_global zplgl_color const zplgl_color_yellow = { 0xff00ffff };
    zpl_global zplgl_color const zplgl_color_green = { 0xff00ff00 };
    zpl_global zplgl_color const zplgl_color_cyan = { 0xffffff00 };
    zpl_global zplgl_color const zplgl_color_blue = { 0xffff0000 };
    zpl_global zplgl_color const zplgl_color_violet = { 0xffff007f };
    zpl_global zplgl_color const zplgl_color_magenta = { 0xffff00ff };


    ////////////////////////////////////////////////////////////////
    //
    // Generic Stuff
    //
    //


#ifndef ZPLGL_VERT_PTR_AA_GENERIC
#define ZPLGL_VERT_PTR_AA_GENERIC
    // NOTE(bill) The "default" is just the f32 version
#define zplgl_vert_ptr_aa(index, element_count, Type, var_name) \
    zplgl_vert_ptr_aa_f32(index, element_count, Type, var_name)

#define zplgl_vert_ptr_aa_f32(index, element_count, Type, var_name) do {  \
    glVertexAttribPointer(index,                                         \
                          element_count,                                 \
                          GL_FLOAT,                                      \
                          false,                                         \
                          zpl_size_of(Type),                              \
                          (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                    \
} while (0)

#define zplgl_vert_ptr_aa_f32b(index, element_count) do {  \
    glVertexAttribPointer(index,                                         \
                          element_count,                                 \
                          GL_FLOAT,                                      \
                          false,                                         \
                          0,                                             \
                          (void const *)0); \
    glEnableVertexAttribArray(index);                                    \
} while (0)

#define zplgl_vert_ptr_aa_u8(index, element_count, Type, var_name) do {   \
    glVertexAttribPointer(index,                                         \
                          element_count,                                 \
                          GL_UNSIGNED_BYTE,                              \
                          false,                                         \
                          zpl_size_of(Type),                              \
                          (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                    \
} while (0)

#define zplgl_vert_ptr_aa_u8n(index, element_count, Type, var_name) do {  \
    glVertexAttribPointer(index,                                         \
                          element_count,                                 \
                          GL_UNSIGNED_BYTE,                              \
                          true,                                          \
                          zpl_size_of(Type),                              \
                          (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                    \
} while (0)

#define zplgl_vert_ptr_aa_u32(index, element_count, Type, var_name) do {   \
    glVertexAttribIPointer(index,                                         \
                           element_count,                                 \
                           GL_UNSIGNED_INT,                               \
                           zpl_size_of(Type),                              \
                           (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                     \
} while (0)

#define zplgl_vert_ptr_aa_u16(index, element_count, Type, var_name) do {   \
    glVertexAttribIPointer(index,                                         \
                           element_count,                                 \
                           GL_UNSIGNED_SHORT,                             \
                           zpl_size_of(Type),                              \
                           (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                     \
} while (0)

#define zplgl_vert_ptr_aa_u16n(index, element_count, Type, var_name) do { \
    glVertexAttribPointer(index,                                         \
                          element_count,                                 \
                          GL_UNSIGNED_SHORT,                             \
                          true,                                          \
                          zpl_size_of(Type),                              \
                          (void const *)(zpl_offset_of(Type, var_name))); \
    glEnableVertexAttribArray(index);                                    \
} while (0)

#endif

    ZPL_DEF zpl_u32 zplgl_make_sampler(zpl_u32 min_filter, zpl_u32 max_filter, zpl_u32 s_wrap, zpl_u32 t_wrap);

    ////////////////////////////////////////////////////////////////
    //
    // Data Buffers
    //
    //


    typedef enum zplgl_buffer_data_type {
        ZPLGL_BUFFER_DATA_U8 = GL_UNSIGNED_BYTE,
        ZPLGL_BUFFER_DATA_I8 = GL_BYTE,

        ZPLGL_BUFFER_DATA_U16 = GL_UNSIGNED_SHORT,
        ZPLGL_BUFFER_DATA_I16 = GL_SHORT,
        ZPLGL_BUFFER_DATA_F16 = GL_HALF_FLOAT,

        ZPLGL_BUFFER_DATA_U32 = GL_UNSIGNED_INT,
        ZPLGL_BUFFER_DATA_I32 = GL_INT,
        ZPLGL_BUFFER_DATA_F32 = GL_FLOAT,

        ZPLGL_BUFFER_DATA_F8, // NOTE(bill): This is not a "real" OpenGL type but it is needed for internal format enums
    } zplgl_buffer_data_type;


    // NOTE(bill) index+1 = channels count
#if defined(ZPLGL_USE_SRGB_TEXTURE_FORMAT)
    zpl_i32 const zplgl__texture_format[4] = { GL_RED, GL_RG, GL_SRGB8, GL_SRGB8_ALPHA8 };
#else
    zpl_i32 const zplgl__texture_format[4] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
#endif

    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_8[4] = { GL_R8,   GL_RG8,   GL_RGB8,      GL_RGBA8 };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_16[4] = { GL_R16,  GL_RG16,  GL_RGB16,  GL_RGBA16 };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_32[4] = { GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_U8[4] = { GL_R8UI, GL_RG8UI, GL_RGB8UI, GL_RGB8UI };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_I8[4] = { GL_R8I,  GL_RG8I,  GL_RGB8I,  GL_RGB8I };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_F8[4] = { GL_R8,   GL_RG8,   GL_RGB8,   GL_RGB8 };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_U16[4] = { GL_R16UI, GL_RG16UI, GL_RGB16UI, GL_RGB16UI };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_I16[4] = { GL_R16I,  GL_RG16I,  GL_RGB16I,  GL_RGB16I };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_F16[4] = { GL_R16F,  GL_RG16F,  GL_RGB16F,  GL_RGB16F };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_U32[4] = { GL_R32UI, GL_RG32UI, GL_RGB32UI, GL_RGBA32UI };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_I32[4] = { GL_R32I,  GL_RG32I,  GL_RGB32I,  GL_RGBA32I };
    zpl_i32 const ZPLGL_INTERNAL_TEXTURE_FORMAT_F32[4] = { GL_R32F,  GL_RG32F,  GL_RGB32F,  GL_RGBA32F };

    ZPL_IMPL_INLINE zpl_i32 zplgl_texture_format(zplgl_buffer_data_type data_type, zpl_i32 channel_count) {
        ZPL_ASSERT(zpl_is_between(channel_count, 1, 4));
        switch (data_type) {
        case ZPLGL_BUFFER_DATA_U8:  return ZPLGL_INTERNAL_TEXTURE_FORMAT_U8[channel_count - 1];
        case ZPLGL_BUFFER_DATA_I8:  return ZPLGL_INTERNAL_TEXTURE_FORMAT_I8[channel_count - 1];
        case ZPLGL_BUFFER_DATA_F8:  return ZPLGL_INTERNAL_TEXTURE_FORMAT_F8[channel_count - 1];
        case ZPLGL_BUFFER_DATA_U16: return ZPLGL_INTERNAL_TEXTURE_FORMAT_U16[channel_count - 1];
        case ZPLGL_BUFFER_DATA_I16: return ZPLGL_INTERNAL_TEXTURE_FORMAT_I16[channel_count - 1];
        case ZPLGL_BUFFER_DATA_F16: return ZPLGL_INTERNAL_TEXTURE_FORMAT_F16[channel_count - 1];
        case ZPLGL_BUFFER_DATA_U32: return ZPLGL_INTERNAL_TEXTURE_FORMAT_U32[channel_count - 1];
        case ZPLGL_BUFFER_DATA_I32: return ZPLGL_INTERNAL_TEXTURE_FORMAT_I32[channel_count - 1];
        case ZPLGL_BUFFER_DATA_F32: return ZPLGL_INTERNAL_TEXTURE_FORMAT_F32[channel_count - 1];
        }
        return ZPLGL_INTERNAL_TEXTURE_FORMAT_F32[4 - 1];
    }

    typedef struct zplgl_tbo {
        zpl_u32 buffer_obj_handle;
        zpl_u32 buffer_handle;
    } zplgl_tbo;

    // NOTE(bill): usage_hint == (GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW)
    // NOTE(zaklaus): ssbo_usage_hint == (GL_DYNAMIC_COPY, ...)
    ZPL_DEF zpl_u32 zplgl_make_vbo(void const *data, zpl_isize size, zpl_i32 usage_hint);
    ZPL_DEF zpl_u32 zplgl_make_ebo(void const *data, zpl_isize size, zpl_i32 usage_hint);
    ZPL_DEF zpl_u32 zplgl_make_ssbo(void const *data, zpl_isize size, zpl_i32 ssbo_usage_hint);
    ZPL_DEF zpl_u32 zplgl_make_vao(void);

    ZPL_DEF zplgl_tbo zplgl_make_tbo(zplgl_buffer_data_type data_type, zpl_i32 channel_count, void const *data, zpl_isize size, zpl_i32 usage_hint);

    ZPL_DEF void zplgl_vbo_copy(zpl_u32 vbo_handle, void *const data, zpl_isize size, zpl_isize offset);
    ZPL_DEF void zplgl_ebo_copy(zpl_u32 ebo_handle, void *const data, zpl_isize size, zpl_isize offset);
    ZPL_DEF void zplgl_ssbo_copy(zpl_u32 ssbo_handle, void *const data, zpl_isize size, zpl_isize offset);
    ZPL_DEF void zplgl_tbo_copy(zplgl_tbo tbo, void *const data, zpl_isize size, zpl_isize offset);



    ZPL_DEF void zplgl_bind_vbo(zpl_u32 vbo_handle);
    ZPL_DEF void zplgl_bind_ebo(zpl_u32 ebo_handle);
    ZPL_DEF void zplgl_bind_ssbo(zpl_u32 ssbo_handle);
    ZPL_DEF void zplgl_bind_tbo(zplgl_tbo tbo, zpl_i32 sampler_handle, zpl_i32 tex_unit);

    // NOTE(bill): access = GL_WRITE_ONLY, etc.
    ZPL_DEF void *zplgl_map_vbo(zpl_u32 vbo_handle, zpl_i32 access);
    ZPL_DEF void *zplgl_map_ebo(zpl_u32 ebo_handle, zpl_i32 access);
    ZPL_DEF void *zplgl_map_ssbo(zpl_u32 ssbo_handle, zpl_i32 access);
    ZPL_DEF void zplgl_unmap_vbo(void);
    ZPL_DEF void zplgl_unmap_ebo(void);



    ////////////////////////////////////////////////////////////////
    //
    // Shader
    //
    //

    typedef enum zplgl_shader_type {
        ZPLGL_SHADER_VERTEX,
        ZPLGL_SHADER_FRAGMENT,
        ZPLGL_SHADER_GEOMETRY,

        ZPLGL_SHADER_COUNT,
    } zplgl_shader_type;

    zpl_i32 const zplgl_shader_map[ZPLGL_SHADER_COUNT] = {
        GL_VERTEX_SHADER,   /* zplglShader_Vertex   */
        GL_FRAGMENT_SHADER, /* zplglShader_Fragment */
        GL_GEOMETRY_SHADER, /* zplglShader_Geometry */
    };

    typedef enum zplgl_shader_error {
        ZPLGL_SHADER_ERROR_NONE,
        ZPLGL_SHADER_ERROR_SHADER_COMPILE,
        ZPLGL_SHADER_ERROR_LINKING,
        ZPLGL_SHADER_ERROR_UNABLE_TO_READ_FILE,

        ZPLGL_SHADER_ERROR_COUNT,
    } zplgl_shader_error;

#ifndef ZPLGL_MAX_UNIFORM_COUNT
#define ZPLGL_MAX_UNIFORM_COUNT 32
#endif

#ifndef ZPLGL_MAX_STORAGE_BLOCK_COUNT
#define ZPLGL_MAX_STORAGE_BLOCK_COUNT 32
#endif

    typedef struct zplgl_shader {
        zpl_u32 shaders[ZPLGL_SHADER_COUNT];
        zpl_u32 program;

        zpl_i32   uniform_locs[ZPLGL_MAX_UNIFORM_COUNT];
        char *uniform_names[ZPLGL_MAX_UNIFORM_COUNT];
        zpl_i32   uniform_count;

        zpl_i32   sblock_locs[ZPLGL_MAX_STORAGE_BLOCK_COUNT];
        char *sblock_names[ZPLGL_MAX_STORAGE_BLOCK_COUNT];
        zpl_i32   sblock_count;

        zpl_u32   type_flags;

        zpl_file files[ZPLGL_SHADER_COUNT];

        char base_name[64];
    } zplgl_shader;



#ifndef ZPLGL_SHADER_FILE_EXTENSIONS_DEFINED
#define ZPLGL_SHADER_FILE_EXTENSIONS_DEFINED
    zpl_global char const *zplgl_shader_file_extensions[ZPLGL_SHADER_COUNT] = { ".vs", ".fs", ".gs" };
#endif


    ZPL_DEF zplgl_shader_error zplgl_load_shader_from_file(zplgl_shader *s, zpl_u32 type_bits, char const *filename);
    ZPL_DEF zplgl_shader_error zplgl_load_shader_from_memory_vf(zplgl_shader *s, char const *vert_source, char const *frag_source);
    ZPL_DEF zplgl_shader_error zplgl_load_shader_from_memory_vfg(zplgl_shader *s, char const *vert_source, char const *frag_source, char const *geom_source);

    ZPL_DEF void zplgl_destroy_shader(zplgl_shader *shader);
    ZPL_DEF zpl_b32  zplgl_has_shader_changed(zplgl_shader *shader);
    ZPL_DEF zpl_b32  zplgl_reload_shader(zplgl_shader *shader); // TODO(bill): Return an error code?
    ZPL_DEF void zplgl_use_shader(zplgl_shader *shader);
    ZPL_DEF zpl_b32  zplgl_is_shader_in_use(zplgl_shader *shader);

    ZPL_DEF zpl_i32 zplgl_get_uniform(zplgl_shader *shader, char const *name);
    ZPL_DEF zpl_i32 zplgl_get_storage_block(zplgl_shader *s, char const *name);
    ZPL_DEF void zplgl_bind_ssbo_storage_block(zplgl_shader *s, zpl_i32 binding_point, zpl_i32 block_index, zpl_i32 ssbo_handle);

    ZPL_DEF void zplgl_set_uniform_int(zplgl_shader *s, char const *name, zpl_i32 i);
    ZPL_DEF void zplgl_set_uniform_float(zplgl_shader *s, char const *name, zpl_f32 f);
    ZPL_DEF void zplgl_set_uniform_vec2(zplgl_shader *s, char const *name, zpl_f32 const *v);
    ZPL_DEF void zplgl_set_uniform_vec3(zplgl_shader *s, char const *name, zpl_f32 const *v);
    ZPL_DEF void zplgl_set_uniform_vec4(zplgl_shader *s, char const *name, zpl_f32 const *v);
    ZPL_DEF void zplgl_set_uniform_mat4(zplgl_shader *s, char const *name, zpl_f32 const *m);
    ZPL_DEF void zplgl_set_uniform_mat4_count(zplgl_shader *s, char const *name, zpl_f32 const *m, zpl_isize count);
    ZPL_DEF void zplgl_set_uniform_colour(zplgl_shader *s, char const *name, zplgl_color col);


    ////////////////////////////////////////////////////////////////
    //
    // Texture
    //
    //

    typedef enum zplgl_texture_type {
        ZPLGL_TEXTURE_2D,
        ZPLGL_TEXTURE_CUBEMAP,

        ZPLGL_TEXTURE_COUNT,
    } zplgl_texture_type;

    zpl_global zpl_i32 const ZPLGL_TEXTURE_TYPE[ZPLGL_TEXTURE_COUNT] = {
        GL_TEXTURE_2D,       /* zplglgTexture_2D */
        GL_TEXTURE_CUBE_MAP, /* zplglgTexture_CubeMap */
    };


    typedef struct zplgl_texture {
        zpl_i32 width, height, channel_count;
        zplgl_buffer_data_type data_type;
        zplgl_texture_type type;
        zpl_u32 handle;
    } zplgl_texture;

    ZPL_DEF zpl_b32  zplgl_load_texture2d_from_file(zplgl_texture *texture, zpl_b32 flip_vertically, char const *filename, ...);
    ZPL_DEF zpl_b32  zplgl_load_texture2d_from_memory(zplgl_texture *texture, void const *data, zpl_i32 width, zpl_i32 height, zpl_i32 channel_count);
    ZPL_DEF zpl_b32  zplgl_init_texture2d_coloured(zplgl_texture *texture, zplgl_color colour);
    ZPL_DEF void zplgl_destroy_texture(zplgl_texture *texture);

    ZPL_DEF void zplgl_bind_texture2d(zplgl_texture const *texture, zpl_u32 position, zpl_u32 sampler);





    ////////////////////////////////////////////////////////////////
    //
    // Render Buffer
    //
    //

    // TODO(bill): Record depth and stencil and numerous colour attachments

    typedef struct zplgl_render_buffer {
        zpl_i32 width, height;
        zpl_i32 channel_count;
        zpl_u32 handle;

        zplgl_texture colour_texture;
    } zplgl_render_buffer;

#define ZPLGL_MAX_RENDER_COLOUR_BUFFERS 16
    zpl_global zpl_u32 const zplglColourBufferAttachments[ZPLGL_MAX_RENDER_COLOUR_BUFFERS] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4,
        GL_COLOR_ATTACHMENT5,
        GL_COLOR_ATTACHMENT6,
        GL_COLOR_ATTACHMENT7,
        GL_COLOR_ATTACHMENT8,
        GL_COLOR_ATTACHMENT9,
        GL_COLOR_ATTACHMENT10,
        GL_COLOR_ATTACHMENT11,
        GL_COLOR_ATTACHMENT12,
        GL_COLOR_ATTACHMENT13,
        GL_COLOR_ATTACHMENT14,
        GL_COLOR_ATTACHMENT15,
    };


    ZPL_DEF zpl_b32  zplgl_init_render_buffer(zplgl_render_buffer *rb, zpl_i32 width, zpl_i32 height, zpl_i32 channel_count);
    ZPL_DEF void zplgl_destroy_render_buffer(zplgl_render_buffer *rb);
    ZPL_DEF void zplgl_render_to_buffer(zplgl_render_buffer const *rb);
    ZPL_DEF void zplgl_render_to_screen(zpl_i32 width, zpl_i32 height);


    ////////////////////////////////////////////////////////////////
    //
    // Font Stuff
    //
    //

#if !defined(ZPLGL_NO_FONTS)

    typedef struct zplgl_glyph_mapkv_pair {
        zpl_char32 codepoint;
        zpl_u16    index;
    } zplgl_glyph_mapkv_pair;

    typedef struct zplgl_glyph_info {
        zpl_f32 s0, t0, s1, t1;
        zpl_i16 xoff, yoff;
        zpl_f32 xadv;
    } zplgl_glyph_info;

    typedef struct zplgl_kern_pair {
        union {
            zpl_i32 packed;
            struct { zpl_u16 i0, i1; };
        };
        zpl_f32 kern;
    } zplgl_kern_pair;

    typedef enum zplgl_justify_type {
        ZPLGL_JUSTIFY_LEFT,
        ZPLGL_JUSTIFY_CENTER,
        ZPLGL_JUSTIFY_RIGHT,
    } zplgl_justify_type;

    typedef enum zplgl_textparam_type {
        ZPLGL_TEXTPARAM_INVALID,
        ZPLGL_TEXTPARAM_MAXWIDTH,
        ZPLGL_TEXTPARAM_JUSTIFY,
        ZPLGL_TEXTPARAM_TEXTURE_FILTER,

        ZPLGL_TEXTPARAM_COUNT,
    } zplgl_textparam_type;

    typedef struct zplgl_textparam {
        zplgl_textparam_type type;
        union {
            zpl_f32 val_f32;
            zpl_i32 val_i32;
        };
    } zplgl_textparam;

    typedef struct zplgl_font {
        zpl_isize glyph_count;
        zpl_isize kern_pair_count;
        zpl_i32 bitmap_width, bitmap_height;
        zpl_f32 size;
        zpl_i32 ascent, descent, line_gap;
        char *ttf_filename;
        zplgl_texture texture;

        zplgl_glyph_mapkv_pair *glyph_map;
        zplgl_glyph_info *     glyphs;
        zplgl_kern_pair *      kern_table;

        struct zplgl_font *next; // NOTE(bill): Allow as linked list
    } zplgl_font;

    typedef struct zplgl_font_cached_ttf {
        char *                    name;
        zpl_u8 *                      ttf;
        stbtt_fontinfo            finfo;
        struct zplgl_font_cached_ttf *next;
    } zplgl_font_cached_ttf;

    typedef struct zplgl_font_cache {
        zpl_isize font_char_list_count;
        char *font_char_list;

        zpl_isize   codepoint_count;
        zpl_char32 *codepoints;

        stbtt_pack_range *ranges;
        stbtt_packedchar *packed_char_data;
        stbrp_rect *      rect_cache;

        zplgl_font_cached_ttf *ttf_buffer;
        zplgl_font *         fonts;
    } zplgl_font_cache;


#if 0
    ZPL_DEF void zplgl_destroy_font_cache(zplglFontCache *fc);
#endif

    // NOTE(bill): zplgl_load_font_from_file will load from file if it is not found
    ZPL_DEF zplgl_font *zplgl_load_font_from_file(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size);
    ZPL_DEF zplgl_font *zplgl_get_font_only_from_cache(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size);
    ZPL_DEF zplgl_font *zplgl_cache_font(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size);


    ZPL_DEF zpl_b32            zplgl_get_packed_font_dim(zplgl_font_cache *cache, zplgl_font_cached_ttf *ttf, zpl_i32 *width, zpl_i32 *height);
    ZPL_DEF zplgl_glyph_info  *zplgl_get_glyph_info(zplgl_font *font, zpl_char32 codepoint, zpl_isize *out_index);
    ZPL_DEF zpl_f32            zplgl_get_font_kerning_from_glyph_indices(zplgl_font *font, zpl_isize left_index, zpl_isize right_index);
    ZPL_DEF void               zplgl_get_string_dimensions(zplgl_font *font, char const *str, zpl_f32 *out_width, zpl_f32 *out_height);
    ZPL_DEF zpl_f32            zplgl_get_sub_string_width(zplgl_font *font, char const *str, zpl_isize char_count);
    ZPL_DEF zpl_i32            zplgl_get_wrapped_line_count(zplgl_font *font, char const *str, zpl_isize max_len, zpl_isize max_width);
    ZPL_DEF zpl_f32            zplgl_get_string_width(zplgl_font *font, char const *str, zpl_isize max_len);


#endif

    ////////////////////////////////////////////////////////////////
    //
    // Basic State
    //
    //

#if !defined(ZPLGL_NO_BASIC_STATE)

#ifndef ZPLGL_BS_MAX_VERTEX_COUNT
#define ZPLGL_BS_MAX_VERTEX_COUNT 32
#endif

#ifndef ZPLGL_BS_MAX_INDEX_COUNT
#define ZPLGL_BS_MAX_INDEX_COUNT 6
#endif


#if !defined(ZPLGL_NO_FONTS)

  #ifndef ZPLGL_MAX_RENDER_STRING_LENGTH
  #define ZPLGL_MAX_RENDER_STRING_LENGTH 4096
  #endif

  #ifndef ZPLGL_TEXTPARAM_STACK_SIZE
  #define ZPLGL_TEXTPARAM_STACK_SIZE 128
  #endif

  #ifndef ZPLGL_FONT_CHAR_LIST
  #define ZPLGL_FONT_CHAR_LIST \
      "ĀāăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğĠġĢģĤĥĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽľŁł"\
      "ŃńŅņņŇňŉŊŋŌōōŎŏŐőŒœŕŖŗŘřŚśŜŝŞşŠšŢţŤťŨũŪūŬŭŮůŰűŲųŴŵŶŷŸŹźŻżŽža!ö"\
      "\"#$%%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"\
      "ŠšŒœŸÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõøùúûüýþÿ®™£"\
      "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"\
      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"\
      " \t\r\n"
  #endif

  #ifndef ZPLGL_PT_TO_PX_SCALE
  #define ZPLGL_PT_TO_PX_SCALE (96.0f / 72.0f)
  #endif

  #ifndef ZPLGL_TAB_CHARACTER_WIDTH
  #define ZPLGL_TAB_CHARACTER_WIDTH 4
  #endif

#endif

    typedef struct zplgl_basic_vertex {
        zpl_f32 x, y;
        zpl_f32 u, v;
    } zplgl_basic_vertex;

    typedef struct zplgl_basic_state {
        zplgl_basic_vertex vertices[ZPLGL_BS_MAX_VERTEX_COUNT];
        zpl_u16 indices[ZPLGL_BS_MAX_INDEX_COUNT];

        zpl_u32 vao, vbo, ebo;
        zpl_u32 nearest_sampler;
        zpl_u32 linear_sampler;
        zpl_u32 mipmap_sampler;
        zplgl_shader ortho_tex_shader;
        zplgl_shader ortho_col_shader;

        zpl_f32 ortho_mat[16];
        zpl_i32 width, height;

#if !defined(ZPLGL_NO_FONTS)
        zplgl_font_cache    font_cache;
        zplgl_shader        font_shader;
        zplgl_basic_vertex  font_vertices[ZPLGL_MAX_RENDER_STRING_LENGTH * 4];
        zpl_u16             font_indices[ZPLGL_MAX_RENDER_STRING_LENGTH * 6];
        zpl_u32             font_vao, font_vbo, font_ebo;
        char                font_text_buffer[ZPLGL_MAX_RENDER_STRING_LENGTH * 4]; // NOTE(bill): Maximum of 4 bytes per char for utf-8
        zpl_u32             font_samplers[2];

        zplgl_textparam text_param_stack[ZPLGL_TEXTPARAM_STACK_SIZE];
        zpl_isize         text_param_stack_count;
        zplgl_textparam text_params[ZPLGL_TEXTPARAM_COUNT];
#endif
    } zplgl_basic_state;

    ZPL_DEF void zplgl_bs_init(zplgl_basic_state *bs, zpl_i32 window_width, zpl_i32 window_height);
    ZPL_DEF void zplgl_bs_set_resolution(zplgl_basic_state *bs, zpl_i32 window_width, zpl_i32 window_height);
    ZPL_DEF void zplgl_bs_begin(zplgl_basic_state *bs);
    ZPL_DEF void zplgl_bs_end(zplgl_basic_state *bs);

    ZPL_DEF void zplgl_bs_draw_textured_rect(zplgl_basic_state *bs, zplgl_texture *tex, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_b32 v_up);
    ZPL_DEF void zplgl_bs_draw_rect(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zplgl_color col);
    ZPL_DEF void zplgl_bs_draw_rect_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zplgl_color col, zpl_f32 thickness);
    ZPL_DEF void zplgl_bs_draw_quad(zplgl_basic_state *bs,
        zpl_f32 x0, zpl_f32 y0,
        zpl_f32 x1, zpl_f32 y1,
        zpl_f32 x2, zpl_f32 y2,
        zpl_f32 x3, zpl_f32 y3,
        zplgl_color col);
    ZPL_DEF void zplgl_bs_draw_quad_outline(zplgl_basic_state *bs,
        zpl_f32 x0, zpl_f32 y0,
        zpl_f32 x1, zpl_f32 y1,
        zpl_f32 x2, zpl_f32 y2,
        zpl_f32 x3, zpl_f32 y3,
        zplgl_color col, zpl_f32 thickness);

    ZPL_DEF void zplgl_bs_draw_line(zplgl_basic_state *bs, zpl_f32 x0, zpl_f32 y0, zpl_f32 x1, zpl_f32 y1, zplgl_color col, zpl_f32 thickness);

    ZPL_DEF void zplgl_bs_draw_elliptical_arc(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius_a, zpl_f32 radius_b, zpl_f32 min_angle, zpl_f32 max_angle, zplgl_color col);
    ZPL_DEF void zplgl_bs_draw_elliptical_arc_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius_a, zpl_f32 radius_b,
        zpl_f32 min_angle, zpl_f32 max_angle, zplgl_color col, zpl_f32 thickness);

    ZPL_DEF void zplgl_bs_draw_circle(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius, zplgl_color col);
    ZPL_DEF void zplgl_bs_draw_circle_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius, zplgl_color col, zpl_f32 thickness);


    // Corners Flags:
    // 1 - Bottom Left
    // 2 - Bottom Right
    // 4 - Top    Right
    // 8 - Top    Left
    // NOTE(bill): Apple, please don't sue me!
    ZPL_DEF void zplgl_bs_draw_rounded_rect_corners(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_u32 corners);
    ZPL_DEF void zplgl_bs_draw_rounded_rect(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col);

    ZPL_DEF void zplgl_bs_draw_rounded_rect_corners_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_f32 thickness, zpl_u32 corners);
    ZPL_DEF void zplgl_bs_draw_rounded_rect_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_f32 thickness);


#if !defined(ZPLGL_NO_FONTS)
    ZPL_DEF zpl_isize zplgl_bs_draw_substring(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *str, zpl_isize len);
    ZPL_DEF zpl_isize zplgl_bs_draw_string(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *fmt, ...);
    ZPL_DEF zpl_isize zplgl_bs_draw_string_va(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *fmt, va_list va);
#endif

#endif // !defined(ZPL_NO_BASIC_STATE)

//! @}
