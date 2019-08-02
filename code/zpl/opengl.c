/** @file opengl.c
@brief OpenGL helpers
@defgroup opengl OpenGL helpers

 Offers OpenGL helper methods as well as basic 2D graphics and font rendering.
 
 @{
 */

#ifdef ZPL_OPENGL

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

    zpl_inline zpl_i32 zplgl_texture_format(zplgl_buffer_data_type data_type, zpl_i32 channel_count) {
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

#endif // ZPL_OPENGL

//! @}
//$$

///////////////////////////////////////////////////
///
/// OpenGL
/// 
/// 

#ifndef ZPL_GLGEN_IMPLEMENTATION
#define ZPL_GLGEN_IMPLEMENTATION  
#include "zpl_glgen.h"
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#if !defined(ZPLGL_NO_FONTS)
    #ifndef STB_RECT_PACK_IMPLEMENTATION
    #define STB_RECT_PACK_IMPLEMENTATION
    #include "stb_rect_pack.h"
    #endif

    #ifndef STB_TRUETYPE_IMPLEMENTATION
    #define STB_TRUETYPE_IMPLEMENTATION
    #include "stb_truetype.h"
    #endif
#endif


#ifdef ZPL_OPENGL

zpl_inline zplgl_color zplgl_colorf(zpl_f32 r, zpl_f32 g, zpl_f32 b, zpl_f32 a) {
    zplgl_color result;
    result.r = cast(zpl_u8)(zplgl_clamp01(r) * 255.0f);
    result.g = cast(zpl_u8)(zplgl_clamp01(g) * 255.0f);
    result.b = cast(zpl_u8)(zplgl_clamp01(b) * 255.0f);
    result.a = cast(zpl_u8)(zplgl_clamp01(a) * 255.0f);
    return result;
}

zpl_inline zplgl_color zplgl_color_opacity(zplgl_color color, zpl_f32 alpha)
{
    zplgl_color result;
    result = color;
    result.a = cast(zpl_u8)(alpha / 255.0f);
    return result;
}

zpl_u32 zplgl_make_sampler(zpl_u32 min_filter, zpl_u32 max_filter, zpl_u32 s_wrap, zpl_u32 t_wrap) {
    zpl_u32 samp;
    glGenSamplers(1, &samp);
    glSamplerParameteri(samp, GL_TEXTURE_MIN_FILTER, min_filter);
    glSamplerParameteri(samp, GL_TEXTURE_MAG_FILTER, max_filter);
    glSamplerParameteri(samp, GL_TEXTURE_WRAP_S, s_wrap);
    glSamplerParameteri(samp, GL_TEXTURE_WRAP_T, t_wrap);
    return samp;
}


////////////////////////////////////////////////////////////////
//
// Data Buffers
//
//

zpl_inline zpl_u32 zplgl__make_buffer(zpl_isize size, void const *data, zpl_i32 target, zpl_i32 usage_hint) {
    zpl_u32 buffer_handle;
    glGenBuffers(1, &buffer_handle);
    glBindBuffer(target, buffer_handle);
    glBufferData(target, size, data, usage_hint);
    return buffer_handle;
}

zpl_inline void zplgl__buffer_copy(zpl_u32 buffer_handle, zpl_i32 target, void const *data, zpl_isize size, zpl_isize offset) {
    glBindBuffer(target, buffer_handle);
    glBufferSubData(target, offset, size, data);
}

// NOTE(bill): usage_hint == (GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW)
zpl_inline zpl_u32 zplgl_make_vbo(void const *data, zpl_isize size, zpl_i32 usage_hint) {
    return zplgl__make_buffer(size, data, GL_ARRAY_BUFFER, usage_hint);
}

zpl_inline zpl_u32 zplgl_make_ebo(void const *data, zpl_isize size, zpl_i32 usage_hint) {
    return zplgl__make_buffer(size, data, GL_ELEMENT_ARRAY_BUFFER, usage_hint);
}

zpl_inline zpl_u32 zplgl_make_ssbo(void const *data, zpl_isize size, zpl_i32 ssbo_usage_hint) {
    return zplgl__make_buffer(size, data, GL_SHADER_STORAGE_BUFFER, ssbo_usage_hint);
}

zpl_inline zpl_u32 zplgl_make_vao(void) {
    zpl_u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

zpl_inline zplgl_tbo zplgl_make_tbo(zplgl_buffer_data_type data_type, zpl_i32 channel_count, void const *data, zpl_isize size, zpl_i32 usage_hint) {
    zplgl_tbo tbo;
    zpl_i32 internal_format;

    tbo.buffer_obj_handle = zplgl__make_buffer(size, data, GL_TEXTURE_BUFFER, usage_hint);

    glGenTextures(1, &tbo.buffer_handle);
    glBindTexture(GL_TEXTURE_BUFFER, tbo.buffer_handle);
    internal_format = zplgl_texture_format(data_type, channel_count);
    glTexBuffer(GL_TEXTURE_BUFFER, internal_format, tbo.buffer_obj_handle);
    return tbo;
}

zpl_inline void zplgl_vbo_copy(zpl_u32 vbo_handle, void *const data, zpl_isize size, zpl_isize offset) {
    zplgl__buffer_copy(vbo_handle, GL_ARRAY_BUFFER, data, size, offset);
}

zpl_inline void zplgl_ebo_copy(zpl_u32 ebo_handle, void *const data, zpl_isize size, zpl_isize offset) {
    zplgl__buffer_copy(ebo_handle, GL_ELEMENT_ARRAY_BUFFER, data, size, offset);
}

zpl_inline void zplgl_ssbo_copy(zpl_u32 ssbo_handle, void *const data, zpl_isize size, zpl_isize offset) {
    zplgl__buffer_copy(ssbo_handle, GL_SHADER_STORAGE_BUFFER, data, size, offset);
}

zpl_inline void zplgl_tbo_copy(zplgl_tbo tbo, void *const data, zpl_isize size, zpl_isize offset) {
    zplgl__buffer_copy(tbo.buffer_obj_handle, GL_TEXTURE_BUFFER, data, size, offset);
}

zpl_inline void zplgl_bind_vbo(zpl_u32 vbo_handle) { glBindBuffer(GL_ARRAY_BUFFER, vbo_handle); }
zpl_inline void zplgl_bind_ebo(zpl_u32 ebo_handle) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_handle); }
zpl_inline void zplgl_bind_ssbo(zpl_u32 ssbo_handle) { glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_handle); }

zpl_inline void zplgl_bind_tbo(zplgl_tbo tbo, zpl_i32 sampler_handle, zpl_i32 tex_unit) {
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(GL_TEXTURE_BUFFER, tbo.buffer_handle);
    glBindSampler(0, sampler_handle);
}

// NOTE(bill): access = GL_WRITE_ONLY, etc.
zpl_inline void * zplgl_map_vbo(zpl_u32 vbo_handle, zpl_i32 access) {
    zplgl_bind_vbo(vbo_handle);
    return glMapBuffer(GL_ARRAY_BUFFER, access);
}

zpl_inline void * zplgl_map_ebo(zpl_u32 ebo_handle, zpl_i32 access) {
    zplgl_bind_ebo(ebo_handle);
    return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, access);
}

zpl_inline void zplgl_unmap_vbo(void) { glUnmapBuffer(GL_ARRAY_BUFFER); }
zpl_inline void zplgl_unmap_ebo(void) { glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER); }



////////////////////////////////////////////////////////////////
//
// Shader
//
//


zplgl_shader_error zplgl__load_single_shader_from_file(zplgl_shader *shader, zplgl_shader_type type, char const *name) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;
    zpl_file_error ferr;
    zpl_local_persist char filepath[1024];
    zpl_snprintf(filepath, zpl_count_of(filepath), "%s%s", name, zplgl_shader_file_extensions[type]);
    ferr = zpl_file_open(&shader->files[type], filepath);

    if (ferr != ZPL_FILE_ERROR_NONE) {
        err = ZPLGL_SHADER_ERROR_UNABLE_TO_READ_FILE;
    }
    else {
        zpl_local_persist char info_log[4096];
        zpl_i64 file_size = zpl_file_size(&shader->files[type]);
        char *file_source = cast(char *)zpl_malloc(file_size + 1);

        ZPL_ASSERT_NOT_NULL(file_source);
        if (file_source) {
            zpl_i32 params;

            zpl_file_read_at(&shader->files[type], file_source, file_size, 0);
            file_source[file_size] = '\0';

            shader->shaders[type] = glCreateShader(zplgl_shader_map[type]);
            glShaderSource(shader->shaders[type], 1, &file_source, NULL);
            glCompileShader(shader->shaders[type]);
            glGetShaderiv(shader->shaders[type], GL_COMPILE_STATUS, &params);
            if (!params) {
                zpl_printf_err("Shader Source:\n%s\n", file_source);
                glGetShaderInfoLog(shader->shaders[type], zpl_size_of(info_log), NULL, info_log);
                zpl_printf_err("Shader compilation failed:\n %s\n", info_log);

                err = ZPLGL_SHADER_ERROR_SHADER_COMPILE;
            }

            zpl_mfree(file_source);
        }
        zpl_file_close(&shader->files[type]);
    }

    return err;
}

zplgl_shader_error zplgl__load_single_shader_from_memory(zplgl_shader *s, zplgl_shader_type type, char const *text) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;
    zpl_i32 status;

    s->shaders[type] = glCreateShader(zplgl_shader_map[type]);
    glShaderSource(s->shaders[type], 1, &text, 0);
    glCompileShader(s->shaders[type]);

    glGetShaderiv(s->shaders[type], GL_COMPILE_STATUS, &status);
    if (!status) {
        zpl_local_persist char log_info[4096];
        zpl_i32 total_len, log_len;

        zpl_printf_err("Unable to compile shader: %s\n", text);
        glGetShaderiv(s->shaders[type], GL_INFO_LOG_LENGTH, &status);
        total_len = status;

        glGetShaderInfoLog(s->shaders[type], 4095, &log_len, log_info);
        zpl_printf_err(log_info);
        err = ZPLGL_SHADER_ERROR_SHADER_COMPILE;
    }

    return err;
}

zplgl_shader_error zplgl__link_shader(zplgl_shader *shader) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;
    zpl_i32 i, status;
    shader->program = glCreateProgram();
    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (shader->type_flags & ZPL_BIT(i))
            glAttachShader(shader->program, shader->shaders[i]);
    }

    glLinkProgram(shader->program);

    glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
    if (!status) {
        zpl_local_persist char log_info[4096];
        glGetProgramInfoLog(shader->program, zpl_size_of(log_info), NULL, log_info);
        zpl_printf_err("Shader linking failed:\n %s \n", log_info);
        err = ZPLGL_SHADER_ERROR_LINKING;
    }

    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (shader->type_flags & ZPL_BIT(i))
            glDetachShader(shader->program, shader->shaders[i]);
    }

    return err;
}



zplgl_shader_error zplgl_load_shader_from_file(zplgl_shader *shader, zpl_u32 type_bits, char const *filename) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;
    zpl_b32 loaded_shader[ZPLGL_SHADER_COUNT] = { 0 };
    zpl_i32 i;

    zpl_zero_item(shader);
    shader->type_flags = type_bits;
    zpl_strncpy(shader->base_name, filename, zpl_size_of(shader->base_name));

    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (type_bits & ZPL_BIT(i)) {
            err = zplgl__load_single_shader_from_file(shader, cast(zplgl_shader_type)i, filename);
            if (err != ZPLGL_SHADER_ERROR_NONE)
                return err;
            loaded_shader[i] = true;
        }
    }
    err = zplgl__link_shader(shader);

    return err;
}




zplgl_shader_error zplgl_load_shader_from_memory_vf(zplgl_shader *s, char const *vert_source, char const *frag_source) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;

    zpl_zero_item(s);
    s->type_flags = ZPL_BIT(ZPLGL_SHADER_VERTEX) | ZPL_BIT(ZPLGL_SHADER_FRAGMENT);

    err = zplgl__load_single_shader_from_memory(s, ZPLGL_SHADER_VERTEX, vert_source);
    if (err != ZPLGL_SHADER_ERROR_NONE) return err;
    err = zplgl__load_single_shader_from_memory(s, ZPLGL_SHADER_FRAGMENT, frag_source);
    if (err != ZPLGL_SHADER_ERROR_NONE) return err;

    err = zplgl__link_shader(s);

    return err;
}

zplgl_shader_error zplgl_load_shader_from_memory_vfg(zplgl_shader *s, char const *vert_source, char const *frag_source, char const *geom_source) {
    zplgl_shader_error err = ZPLGL_SHADER_ERROR_NONE;

    zpl_zero_item(s);
    s->type_flags = ZPL_BIT(ZPLGL_SHADER_VERTEX) | ZPL_BIT(ZPLGL_SHADER_FRAGMENT) | ZPL_BIT(ZPLGL_SHADER_GEOMETRY);

    err = zplgl__load_single_shader_from_memory(s, ZPLGL_SHADER_VERTEX, vert_source);
    if (err != ZPLGL_SHADER_ERROR_NONE) return err;
    err = zplgl__load_single_shader_from_memory(s, ZPLGL_SHADER_FRAGMENT, frag_source);
    if (err != ZPLGL_SHADER_ERROR_NONE) return err;
    err = zplgl__load_single_shader_from_memory(s, ZPLGL_SHADER_GEOMETRY, geom_source);
    if (err != ZPLGL_SHADER_ERROR_NONE) return err;

    err = zplgl__link_shader(s);

    return err;
}

zpl_inline void zplgl_destroy_shader(zplgl_shader *shader) {
    zpl_i32 i;
    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (shader->type_flags & ZPL_BIT(i)) {
            zpl_file_close(&shader->files[i]);
            glDeleteShader(shader->shaders[i]);
        }
    }

    glDeleteProgram(shader->program);

    for (i = 0; i < shader->uniform_count; i++) {
        zpl_mfree(shader->uniform_names[i]);
    }
}


zpl_inline zpl_b32 zplgl_has_shader_changed(zplgl_shader *shader) {
    zpl_i32 i;
    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (shader->type_flags & ZPL_BIT(i)) {
            if (zpl_file_has_changed(&shader->files[i])) {
                return true;
            }
        }
    }
    return false;
}


zpl_b32 zplgl_reload_shader(zplgl_shader *shader) {
    zpl_i32 i;
    for (i = 0; i < ZPLGL_SHADER_COUNT; i++) {
        if (shader->type_flags & ZPL_BIT(i)) {
            if (zplgl__load_single_shader_from_file(shader, cast(zplgl_shader_type)i, shader->base_name) != ZPLGL_SHADER_ERROR_NONE)
                return false;
        }
    }

    if (zplgl__link_shader(shader) != ZPLGL_SHADER_ERROR_NONE)
        return false;

    for (i = 0; i < shader->uniform_count; i++)
        shader->uniform_locs[i] = glGetUniformLocation(shader->program, shader->uniform_names[i]);


    return true;
}

zpl_inline void zplgl_use_shader(zplgl_shader *s) { glUseProgram(s ? s->program : 0); }

zpl_inline zpl_b32 zplgl_is_shader_in_use(zplgl_shader *s) {
    if (s) {
        zpl_i32 curr = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &curr);
        return (curr == cast(zpl_i32)s->program);
    }
    return false;
}


zpl_i32 zplgl_get_uniform(zplgl_shader *s, char const *name) {
    zpl_i32 i, loc = -1;
    for (i = 0; i < s->uniform_count; i++) {
        if (zpl_strcmp(s->uniform_names[i], name) == 0) {
            return s->uniform_locs[i];
        }
    }

    ZPL_ASSERT_MSG(s->uniform_count < ZPLGL_MAX_UNIFORM_COUNT,
        "Uniform array for shader is full");

    loc = glGetUniformLocation(s->program, name);
    s->uniform_names[s->uniform_count] = zpl_alloc_str(zpl_heap_allocator(), name);
    s->uniform_locs[s->uniform_count] = loc;
    s->uniform_count++;

    return loc;
}

zpl_i32 zplgl_get_storage_block(zplgl_shader *s, char const *name) {
    zpl_i32 i, loc = -1;
    for (i = 0; i < s->sblock_count; i++) {
        if (zpl_strcmp(s->sblock_names[i], name) == 0) {
            return s->sblock_locs[i];
        }
    }

    ZPL_ASSERT_MSG(s->sblock_count < ZPLGL_MAX_STORAGE_BLOCK_COUNT,
        "Storage block array for shader is full");

    loc = glGetProgramResourceIndex(s->program, GL_SHADER_STORAGE_BLOCK, name);
    s->sblock_names[s->sblock_count] = zpl_alloc_str(zpl_heap(), name);
    s->sblock_locs[s->sblock_count] = loc;
    s->sblock_count++;

    return loc;
}

void zplgl_bind_ssbo_storage_block(zplgl_shader *s, zpl_i32 binding_point, zpl_i32 block_index, zpl_i32 ssbo_handle) {
    glShaderStorageBlockBinding(s->program, block_index, binding_point);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ssbo_handle);
}


zpl_inline void zplgl_set_uniform_int(zplgl_shader *s, char const *name, zpl_i32 i) {
    glUniform1i(zplgl_get_uniform(s, name), i);
}

zpl_inline void zplgl_set_uniform_float(zplgl_shader *s, char const *name, zpl_f32 f) {
    glUniform1f(zplgl_get_uniform(s, name), f);
}

zpl_inline void zplgl_set_uniform_vec2(zplgl_shader *s, char const *name, zpl_f32 const *v) {
    glUniform2fv(zplgl_get_uniform(s, name), 1, v);
}

zpl_inline void zplgl_set_uniform_vec3(zplgl_shader *s, char const *name, zpl_f32 const *v) {
    glUniform3fv(zplgl_get_uniform(s, name), 1, v);
}

zpl_inline void zplgl_set_uniform_vec4(zplgl_shader *s, char const *name, zpl_f32 const *v) {
    glUniform4fv(zplgl_get_uniform(s, name), 1, v);
}

zpl_inline void zplgl_set_uniform_mat4(zplgl_shader *s, char const *name, zpl_f32 const *m) {
    zplgl_set_uniform_mat4_count(s, name, m, 1);
}

zpl_inline void zplgl_set_uniform_mat4_count(zplgl_shader *s, char const *name, zpl_f32 const *m, zpl_isize count) {
    glUniformMatrix4fv(zplgl_get_uniform(s, name), (GLsizei)count, false, m);
}


zpl_inline void zplgl_set_uniform_colour(zplgl_shader *s, char const *name, zplgl_color col) {
    zpl_f32 v[4];
    v[0] = col.r / 255.0f;
    v[1] = col.g / 255.0f;
    v[2] = col.b / 255.0f;
    v[3] = col.a / 255.0f;
    zplgl_set_uniform_vec4(s, name, v);
}



////////////////////////////////////////////////////////////////
//
// Render Buffer
//
//


zpl_b32 zplgl_init_render_buffer(zplgl_render_buffer *rb, zpl_i32 width, zpl_i32 height, zpl_i32 channel_count) {
    if ((rb->width == width) && (rb->height == height) && (rb->channel_count == channel_count)) return true;
    zplgl_destroy_render_buffer(rb);
    zpl_zero_item(rb);

    rb->width = width;
    rb->height = height;

    glEnable(GL_FRAMEBUFFER_SRGB);

    glGenFramebuffers(1, &rb->handle);
    glBindFramebuffer(GL_FRAMEBUFFER, rb->handle);

    zplgl_load_texture2d_from_memory(&rb->colour_texture, NULL, width, height, channel_count);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, rb->colour_texture.handle, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    {
        zpl_u32 draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(zpl_count_of(draw_buffers), draw_buffers);
    }

    {
        zpl_u32 status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            zpl_printf_err("Framebuffer Status: 0x%x\n", status);
            return false;
        }
    }

    return true;
}

zpl_inline void zplgl_destroy_render_buffer(zplgl_render_buffer *rb) {
    if (rb->handle)
        glDeleteFramebuffers(1, &rb->handle);

    zplgl_destroy_texture(&rb->colour_texture);
}


zpl_inline void zplgl_render_to_buffer(zplgl_render_buffer const *rb) {
    ZPL_ASSERT_NOT_NULL(rb);
    glViewport(0, 0, rb->width, rb->height);
    glBindFramebuffer(GL_FRAMEBUFFER, rb->handle);
}

zpl_inline void zplgl_render_to_screen(zpl_i32 width, zpl_i32 height) {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


////////////////////////////////////////////////////////////////
//
// Texture
//
//


zpl_b32 zplgl_load_texture2d_from_memory(zplgl_texture *tex, void const *data, zpl_i32 width, zpl_i32 height, zpl_i32 channel_count) {
    zpl_b32 result = true;

    zpl_zero_item(tex);

    tex->width = width;
    tex->height = height;
    tex->channel_count = channel_count;
    tex->data_type = ZPLGL_BUFFER_DATA_U8;
    tex->type = ZPLGL_TEXTURE_2D;

    glGenTextures(1, &tex->handle);
    glBindTexture(GL_TEXTURE_2D, tex->handle);


    glTexImage2D(GL_TEXTURE_2D, 0,
        ZPLGL_INTERNAL_TEXTURE_FORMAT_8[channel_count - 1],
        width, height, 0,
        zplgl__texture_format[channel_count - 1],
        GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    glFinish();

    return result;
}

zpl_b32 zplgl_load_texture2d_from_file(zplgl_texture *texture, zpl_b32 flip_vertically, char const *filename, ...) {
    zpl_b32 result;
    zpl_u8 *data;
    int width, height, comp;
    char *path;

    va_list va;
    va_start(va, filename);
    path = zpl_bprintf_va(filename, va);
    va_end(va);

    stbi_set_flip_vertically_on_load(flip_vertically);
    data = stbi_load(path, &width, &height, &comp, 0);
    if (data == NULL) {
        zpl_printf_err("Failed to load image: %s\n", path);
        result = false;
    }
    else {
        result = zplgl_load_texture2d_from_memory(texture, data, width, height, comp);
        stbi_image_free(data);
    }
    return result;
}

zpl_inline zpl_b32 zplgl_init_texture2d_coloured(zplgl_texture *t, zplgl_color colour) {
    return zplgl_load_texture2d_from_memory(t, &colour.rgba, 1, 1, 4);
}


zpl_inline void zplgl_bind_texture2d(zplgl_texture const *t, zpl_u32 position, zpl_u32 sampler) {
    if (t != NULL) {
        ZPL_ASSERT(t->type == ZPLGL_TEXTURE_2D);
    }

    if (position > 31) {
        position = 31;
        zpl_printf_err("Textures can only bound to position [0 ... 31]\n");
        zpl_printf_err("Will bind to position [31]\n");
    }

    glActiveTexture(GL_TEXTURE0 + position);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t ? t->handle : 0);
    glBindSampler(position, sampler);
}

zpl_inline void zplgl_destroy_texture(zplgl_texture *t) {
    if (t->handle) {
        glDeleteTextures(1, &t->handle);
    }
}


////////////////////////////////////////////////////////////////
//
// Font
//
//

#if !defined(ZPLGL_NO_FONTS)
zpl_inline ZPL_COMPARE_PROC(zplgl__kern_pair_compare) {
    zplgl_kern_pair *kp0 = cast(zplgl_kern_pair *)a;
    zplgl_kern_pair *kp1 = cast(zplgl_kern_pair *)b;
    return kp0->packed - kp1->packed;
}


zpl_inline ZPL_COMPARE_PROC(zplgl__glyph_map_compare) {
    zplgl_glyph_mapkv_pair g0 = *cast(zplgl_glyph_mapkv_pair *)a;
    zplgl_glyph_mapkv_pair g1 = *cast(zplgl_glyph_mapkv_pair *)b;
    return g0.codepoint - g1.codepoint;
}




zpl_b32 zplgl_get_packed_font_dim(zplgl_font_cache *cache, zplgl_font_cached_ttf *ttf, zpl_i32 *width, zpl_i32 *height) {
    zpl_b32 result = true;
    stbtt_pack_context spc;
    zpl_b32 ext_w = true;
    zpl_isize sanity_counter = 0, i, j;
    *width = *height = (1 << 5);
    for (j = 0; j < cache->codepoint_count; j++) {
        cache->rect_cache[j].x = cache->rect_cache[j].y = 0;
    }

    for (;;) {
        zpl_i32 res = stbtt_PackBegin(&spc, NULL, *width, *height, 0, 1, 0);
        ZPL_ASSERT(res == 1);
        if (res != 1) {
            return false;
        }
        else {
            stbrp_context *rp_ctx;
            zpl_b32 fit = true;

            zpl_zero_array(cache->rect_cache, cache->codepoint_count);
            rp_ctx = cast(stbrp_context *)spc.pack_info;
            stbtt_PackFontRangesGatherRects(&spc, &ttf->finfo, cache->ranges, (int)cache->codepoint_count, cache->rect_cache);
            zpl_sort_array(cache->rect_cache, cache->codepoint_count, rect_height_compare);

            for (i = 0; i < cache->codepoint_count; i++) {
                stbrp__findresult fr = stbrp__skyline_pack_rectangle(rp_ctx, cache->rect_cache[i].w, cache->rect_cache[i].h);
                if (fr.prev_link) {
                    cache->rect_cache[i].x = cast(stbrp_coord)fr.x;
                    cache->rect_cache[i].y = cast(stbrp_coord)fr.y;
                }
                else {
                    int res;
                    if (ext_w) {
                        ext_w = false;
                        *width <<= 1;
                    }
                    else {
                        ext_w = true;
                        *height <<= 1;
                    }
                    fit = false;
                    for (j = 0; j < cache->codepoint_count; j++) {
                        cache->rect_cache[j].x = cache->rect_cache[j].y = 0;
                    }
                    stbtt_PackEnd(&spc);
                    res = stbtt_PackBegin(&spc, NULL, *width, *height, 0, 1, 0);
                    ZPL_ASSERT(res == 1);
                    if (res != 1) {
                        result = false;
                        goto done;
                    }
                    break;
                }
            }
            if (fit) {
                result = true;
                goto done;
            }
            if (++sanity_counter > 32) {
                result = false;
                goto done;
            }
        }
    }

done:
    stbtt_PackEnd(&spc);

    return result;
}

#if 0
void zplgl_destroy_font_cache(zplglFontCache *fc) {
    zplglFontCachedTTF *curr_ttf = fc->ttf_buffer;
    zplglFontCachedTTF *next_ttf = NULL;

    zplglFont *curr_font = fc->fonts;
    zplglFont *next_font = NULL;

    zpl_mfree(fc->font_char_list);
    zpl_mfree(fc->codepoints);
    zpl_mfree(fc->ranges);
    zpl_mfree(fc->packed_char_data);
    zpl_mfree(fc->rect_cache);

    // NOTE(bill): Free all linked listed ttfs
    while (curr_ttf) {
        zpl_mfree(curr_ttf->name);
        zpl_mfree(curr_ttf->ttf);

        next_ttf = curr_ttf->next;
        zpl_mfree(curr_ttf);
        curr_ttf = next_ttf;
    }

    // NOTE(bill): Free all linked listed fonts
    while (curr_font) {
        zpl_mfree(curr_font->ttf_filename);
        zplgl_destroy_texture(&curr_font->texture);
        zpl_mfree(curr_font->glyph_map);
        zpl_mfree(curr_font->glyphs);
        zpl_mfree(curr_font->kern_table);

        next_font = curr_font->next;
        zpl_mfree(curr_font);
        curr_font = next_font;
    }
}
#endif


zpl_inline zplgl_font * zplgl_load_font_from_file(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size) {
    zplgl_font *f = zplgl_get_font_only_from_cache(fc, ttf_filename, font_size);
    if (f) return f;
    return zplgl_cache_font(fc, ttf_filename, font_size);
}


zpl_inline zplgl_font * zplgl_get_font_only_from_cache(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size) {
    zplgl_font *f = fc->fonts;
    while (f) {
        if (f->size == font_size && zpl_strcmp(ttf_filename, f->ttf_filename) == 0) {
            return f;
        }
        f = f->next;
    }
    return NULL;
}

zplgl_font * zplgl_cache_font(zplgl_font_cache *fc, char const *ttf_filename, zpl_f32 font_size) {
    zplgl_font *f = zplgl_get_font_only_from_cache(fc, ttf_filename, font_size);
    zplgl_font_cached_ttf *ttf = NULL;
    zpl_isize i;

    if (f) { // NOTE(bill): The font is already cached
        return f;
    }

    if (!fc->fonts) {
        fc->fonts = cast(zplgl_font *)zpl_malloc(zpl_size_of(zplgl_font));
        f = fc->fonts;
    }
    else {
        f = fc->fonts;
        while (f && f->next)
            f = f->next;
        f->next = cast(zplgl_font *)zpl_malloc(zpl_size_of(zplgl_font));
        f = f->next;
    }

    if (!f) {
        zpl_printf_err("Failed to cache font\n");
        return NULL;
    }

    zpl_zero_item(f);

    // NOTE(bill): Make sure the character list file has been loaded
    if (!fc->font_char_list) {
        zpl_isize codepoint_count = 0, cpi = 0;
        fc->font_char_list = (char *)ZPLGL_FONT_CHAR_LIST;
        fc->font_char_list_count = zpl_strlen(ZPLGL_FONT_CHAR_LIST);

        for (i = 0; i < fc->font_char_list_count; i++) {
            zpl_char32 c;
            zpl_isize utf8_len = zpl_utf8_decode((zpl_u8 *)fc->font_char_list + i, fc->font_char_list_count, &c);
            i += utf8_len - 1;
            codepoint_count++;
        }

        fc->codepoint_count = codepoint_count;
        fc->ranges = cast(stbtt_pack_range *)           zpl_malloc(zpl_size_of(stbtt_pack_range)  * codepoint_count);
        fc->codepoints = cast(zpl_char32 *)             zpl_malloc(zpl_size_of(zpl_char32)        * codepoint_count);
        fc->packed_char_data = cast(stbtt_packedchar *) zpl_malloc(zpl_size_of(stbtt_packedchar)  * codepoint_count);
        fc->rect_cache = cast(stbrp_rect *)             zpl_malloc(zpl_size_of(stbrp_rect)        * codepoint_count);

        if (!fc->ranges || !fc->codepoints || !fc->packed_char_data) {
            zpl_printf_err("Unable to get memory for fonts");
        }

        for (i = 0; i < fc->font_char_list_count; i++) {
            zpl_isize utf8_len = zpl_utf8_decode((zpl_u8 *)fc->font_char_list + i, fc->font_char_list_count, fc->codepoints + cpi);
            i += utf8_len - 1;
            cpi++;
        }
        ZPL_ASSERT(cpi == fc->codepoint_count);
        for (i = 0; i < fc->codepoint_count; i++) {
            fc->ranges[i].first_unicode_codepoint_in_range = fc->codepoints[i];
            fc->ranges[i].array_of_unicode_codepoints = 0;
            fc->ranges[i].num_chars = 1;
            fc->ranges[i].chardata_for_range = fc->packed_char_data + i;
        }
    }

    {
        zplgl_font_cached_ttf **ttf_cache = &fc->ttf_buffer;

        while (*ttf_cache) {
            if (zpl_strcmp((*ttf_cache)->name, ttf_filename) == 0)
                break;
            ttf_cache = &(*ttf_cache)->next;
        }
        if (!*ttf_cache) {
            zpl_isize name_len;
            zpl_file file = {0};


            *ttf_cache = cast(zplgl_font_cached_ttf *)zpl_malloc(zpl_size_of(zplgl_font_cached_ttf));
            ZPL_ASSERT_NOT_NULL(*ttf_cache);
            (*ttf_cache)->name = NULL;
            (*ttf_cache)->ttf = NULL;
            zpl_zero_item(&(*ttf_cache)->finfo);
            (*ttf_cache)->next = NULL;

            name_len = zpl_strlen(ttf_filename);

            (*ttf_cache)->name = cast(char *)zpl_malloc(name_len + 1);
            zpl_strncpy((*ttf_cache)->name, ttf_filename, name_len);
            (*ttf_cache)->name[name_len] = '\0';

            if (zpl_file_open(&file, ttf_filename) == ZPL_FILE_ERROR_NONE) {
                zpl_i64 len = zpl_file_size(&file);
                (*ttf_cache)->ttf = cast(zpl_u8 *)zpl_malloc(len);
                ZPL_ASSERT_NOT_NULL((*ttf_cache)->ttf);

                zpl_file_read_at(&file, (*ttf_cache)->ttf, len, 0);

                zpl_file_close(&file);
            }
            else {
                ZPL_PANIC("Could not open ttf file");
            }

            stbtt_InitFont(&(*ttf_cache)->finfo, (*ttf_cache)->ttf, stbtt_GetFontOffsetForIndex((*ttf_cache)->ttf, 0));
        }
        ttf = *ttf_cache;
        ZPL_ASSERT_NOT_NULL(ttf);
    }

    // NOTE(bill): Set the range for the look up
    for (i = 0; i < fc->codepoint_count; i++)
        fc->ranges[i].font_size = font_size;

    { // NOTE(bill): Figure out smallest non-square power of 2 texture size
        zpl_i32 w, h;
        if (zplgl_get_packed_font_dim(fc, ttf, &w, &h)) {
            zpl_isize str_len, i, j;

            // NOTE(bill): Setup the font data
            f->glyph_count = fc->codepoint_count;
            f->bitmap_width = w;
            f->bitmap_height = h;
            f->size = font_size;

            str_len = zpl_strlen(ttf_filename);
            f->ttf_filename = cast(char *)zpl_malloc(str_len + 1);
            zpl_strncpy(f->ttf_filename, ttf_filename, str_len);

            f->glyph_map = cast(zplgl_glyph_mapkv_pair *)zpl_malloc(zpl_size_of(*f->glyph_map) * f->glyph_count);
            f->glyphs = cast(zplgl_glyph_info *)     zpl_malloc(zpl_size_of(*f->glyphs)    * f->glyph_count);
            if (!f->glyph_map || !f->glyphs) {
                f = NULL;
                return f;
            }
            else {
                stbtt_pack_context spc;
                zpl_u8 *px;
                zpl_i32 res;
                zpl_f32 scale;

                px = cast(zpl_u8 *)zpl_malloc(w * h);
                res = stbtt_PackBegin(&spc, px, w, h, 0, 1, NULL);
                ZPL_ASSERT(res == 1);
                res = cast(zpl_isize)stbtt_PackFontRanges(&spc, ttf->ttf, 0, fc->ranges, cast(int)fc->codepoint_count);
                ZPL_ASSERT(res == 1);
                stbtt_PackEnd(&spc);

                zplgl_load_texture2d_from_memory(&f->texture, px, w, h, 1);

                zpl_mfree(px);

                scale = stbtt_ScaleForPixelHeight(&ttf->finfo, font_size);
                stbtt_GetFontVMetrics(&ttf->finfo, &f->ascent, &f->descent, &f->line_gap);
                f->ascent = cast(zpl_i32)(cast(zpl_f32)f->ascent   * scale);
                f->descent = cast(zpl_i32)(cast(zpl_f32)f->descent  * scale);
                f->line_gap = cast(zpl_i32)(cast(zpl_f32)f->line_gap * scale);

                for (i = 0; i < f->glyph_count; i++) {
                    zplgl_glyph_info *gi = f->glyphs + i;
                    gi->s0 = cast(zpl_f32)fc->packed_char_data[i].x0;
                    gi->t0 = cast(zpl_f32)fc->packed_char_data[i].y0;
                    gi->s1 = cast(zpl_f32)fc->packed_char_data[i].x1;
                    gi->t1 = cast(zpl_f32)fc->packed_char_data[i].y1;

                    gi->xoff = cast(zpl_i16)fc->packed_char_data[i].xoff;
                    gi->yoff = cast(zpl_i16)fc->packed_char_data[i].yoff;
                    gi->xadv = fc->packed_char_data[i].xadvance;
                }

                for (i = 0; i < f->glyph_count; i++) {
                    f->glyph_map[i].codepoint = fc->codepoints[i];
                    f->glyph_map[i].index = cast(zpl_u16)i;
                }

                zpl_sort_array(f->glyph_map, f->glyph_count, zplgl__glyph_map_compare);

                { // Kerning Table
                    zpl_isize kps_count = 0;
                    for (i = 0; i < f->glyph_count; i++) {
                        for (j = 0; j < f->glyph_count; j++) {
                            zpl_i32 kern = stbtt_GetCodepointKernAdvance(&ttf->finfo, fc->codepoints[i], fc->codepoints[j]);
                            if (kern != 0)
                                kps_count++;
                        }
                    }
                    f->kern_pair_count = kps_count;
                    if (kps_count > 0) {
                        int ikp = 0;
                        f->kern_table = cast(zplgl_kern_pair *)zpl_malloc(zpl_size_of(*f->kern_table) * kps_count);
                        for (i = 0; i < f->glyph_count; i++) {
                            for (j = 0; j < f->glyph_count; j++) {
                                zpl_isize kern = stbtt_GetCodepointKernAdvance(&ttf->finfo, fc->codepoints[i], fc->codepoints[j]);
                                if (kern != 0) {
                                    zplgl_kern_pair *kp = f->kern_table + ikp++;
                                    kp->i0 = cast(zpl_u16)i;
                                    kp->i1 = cast(zpl_u16)j;
                                    kp->kern = cast(zpl_f32)kern * scale;
                                }
                            }
                        }
                        zpl_sort_array(f->kern_table, f->kern_pair_count, zplgl__kern_pair_compare);
                    }
                }
            }
        }
        else {
            ZPL_PANIC("Failure loading font");
            zpl_zero_item(&f);
        }
    }
    return f;
}


zpl_inline ZPL_COMPARE_PROC(zplgl__font_glyph_map_search_proc) {
    zplgl_glyph_mapkv_pair const *gm = cast(zplgl_glyph_mapkv_pair const *)a;
    zpl_char32 ucp = *cast(zpl_char32 const *)b;
    return cast(zpl_i32)(cast(zpl_i64)gm->codepoint - cast(zpl_i64)ucp);
}

zpl_inline zplgl_glyph_info * zplgl_get_glyph_info(zplgl_font *font, zpl_char32 codepoint, zpl_isize *out_index) {
    zpl_isize index = zpl_binary_search_array(font->glyph_map, font->glyph_count, &codepoint, zplgl__font_glyph_map_search_proc);
    if (index >= 0) {
        ZPL_ASSERT(codepoint == font->glyph_map[index].codepoint);
        if (out_index)
            *out_index = font->glyph_map[index].index;
        return font->glyphs + font->glyph_map[index].index;
    }
    return NULL;
}

zpl_inline zpl_f32 zplgl_get_font_kerning_from_glyph_indices(zplgl_font *font, zpl_isize left_index, zpl_isize right_index) {
    zpl_isize needle = (right_index << 16) | (left_index & 0xff);

    zpl_isize f = 0;
    zpl_isize l = font->kern_pair_count - 1;
    zpl_isize m = (f + l) >> 1;

    while (f <= l) {
        zpl_isize cmp = font->kern_table[m].packed - needle;
        if (cmp < 0)
            f = m + 1;
        else if (cmp > 0)
            l = m - 1;
        else
            return font->kern_table[m].kern;
        m = (f + l) >> 1;
    }
    return 0.0f;
}

void zplgl_get_string_dimensions(zplgl_font *font, char const *str, zpl_f32 *out_width, zpl_f32 *out_height) {
    zpl_isize len, char_count, i;

    zpl_f32 w = 0.0f;
    zpl_f32 h = 0.0f;
    char const *ptr = str;

    len = zpl_strlen(str);
    char_count = zpl_utf8_strnlen((zpl_u8 *)str, len);

    for (i = 0; i < char_count; i++) {
        zpl_char32 cp;
        zpl_isize byte_len, curr_index;
        zplgl_glyph_info *gi;

        byte_len = zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &cp);
        ptr += byte_len;
        gi = zplgl_get_glyph_info(font, cp, &curr_index);
        if (gi) {
            zpl_f32 kern = 0;
            if (i < char_count - 1) {
                zpl_isize next_index;
                zpl_char32 next_cp = 0;
                zplgl_glyph_info *ngi;
                zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &next_cp);
                ngi = zplgl_get_glyph_info(font, next_cp, &next_index);
                if (ngi) kern = zplgl_get_font_kerning_from_glyph_indices(font, curr_index, next_index);
            }
            w += gi->xadv + kern;
        }
    }

    if (out_width)  *out_width = w;
    if (out_height) *out_height = h;
}

zpl_f32 zplgl_get_sub_string_width(zplgl_font *font, char const *str, zpl_isize char_count) {
    zpl_isize i, len;
    zpl_f32 w = 0;
    char const *ptr = str;
    len = zpl_strlen(str);
    for (i = 0; i < char_count; i++) {
        if (*ptr == 0) {
            break;
        }
        else {
            zpl_char32 cp;
            zpl_isize byte_len, curr_index;
            zpl_f32 kern = 0;
            zplgl_glyph_info *gi;

            byte_len = zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &cp);
            ptr += byte_len;
            if (ptr - str > char_count)
                break;

            gi = zplgl_get_glyph_info(font, cp, &curr_index);
            if (i < char_count - 1) {
                zpl_isize next_index;
                zpl_char32 next_cp = 0;
                zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &next_cp);
                zplgl_get_glyph_info(font, next_cp, &next_index);
                kern = zplgl_get_font_kerning_from_glyph_indices(font, curr_index, next_index);
            }
            w += gi->xadv + kern;
        }

    }
    return w;
}

zpl_i32 zplgl_get_wrapped_line_count(zplgl_font *font, char const *str, zpl_isize max_len, zpl_isize max_width) {
    zpl_isize i, str_len, char_count, line_count = 1;
    zpl_f32 w = 0;
    char const *ptr = str;

    str_len = zpl_strnlen(str, max_len);
    char_count = zpl_utf8_strnlen((zpl_u8 *)str, str_len);

    for (i = 0; i < char_count; i++) {
        zpl_char32 cp;
        zpl_isize byte_len, curr_index;
        zplgl_glyph_info *gi;
        zpl_f32 kern = 0;

        byte_len = zpl_utf8_decode((zpl_u8 *)ptr, str_len - (ptr - str), &cp);
        ptr += byte_len;
        // NOTE(bill): Check calculation here
        if (ptr - str >= max_len - 6)
            break;

        gi = zplgl_get_glyph_info(font, cp, &curr_index);
        if (gi) {
            if (w + gi->xadv >= cast(zpl_f32)max_width) {
                line_count++;
                w = 0.0f;
            }
        }

        if (i < char_count - 1) {
            zpl_char32 next_cp;
            zpl_isize next_index;
            zpl_utf8_decode((zpl_u8 *)ptr, str_len - (ptr - str), &next_cp);

            zplgl_get_glyph_info(font, next_cp, &next_index);
            kern = zplgl_get_font_kerning_from_glyph_indices(font, curr_index, next_index);
        }

        if (gi) {
            w += gi->xadv + kern;
        }
    }

    return cast(zpl_i32)line_count;
}

zpl_inline zpl_f32 zplgl_get_string_width(zplgl_font *font, char const *str, zpl_isize max_len) {
    zpl_isize len = zpl_strnlen(str, max_len);
    zpl_isize char_count = zpl_utf8_strnlen((zpl_u8 *)str, len);
    return zplgl_get_sub_string_width(font, str, char_count);
}

#endif


////////////////////////////////////////////////////////////////
//
// Basic State
//
//

#if !defined(ZPLGL_NO_BASIC_STATE)


void zplgl_bs_init(zplgl_basic_state *bs, zpl_i32 window_width, zpl_i32 window_height) {
    zpl_isize i;

    zplgl_bs_set_resolution(bs, window_width, window_height);
    glGenVertexArrays(1, &bs->vao);
    glBindVertexArray(bs->vao);

    bs->vbo = zplgl_make_vbo(NULL, zpl_size_of(zplgl_basic_vertex) * ZPLGL_BS_MAX_VERTEX_COUNT, GL_DYNAMIC_DRAW);

    for (i = 0; i < ZPLGL_BS_MAX_INDEX_COUNT / 6; i++) {
        bs->indices[i * 6 + 0] = cast(zpl_u16)(i * 4 + 0);
        bs->indices[i * 6 + 1] = cast(zpl_u16)(i * 4 + 1);
        bs->indices[i * 6 + 2] = cast(zpl_u16)(i * 4 + 2);
        bs->indices[i * 6 + 3] = cast(zpl_u16)(i * 4 + 2);
        bs->indices[i * 6 + 4] = cast(zpl_u16)(i * 4 + 3);
        bs->indices[i * 6 + 5] = cast(zpl_u16)(i * 4 + 0);
    }
    bs->ebo = zplgl_make_ebo(bs->indices, zpl_size_of(zpl_u16) * ZPLGL_BS_MAX_INDEX_COUNT, GL_STATIC_DRAW);

    bs->nearest_sampler = zplgl_make_sampler(GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    bs->linear_sampler = zplgl_make_sampler(GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    bs->mipmap_sampler = zplgl_make_sampler(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

    zplgl_load_shader_from_memory_vf(&bs->ortho_tex_shader,
        ZPL_MULTILINE(#version 420 core\n
        
        layout (location = 0) in vec4 a_position;
        layout (location = 1) in vec2 a_tex_coord;

        uniform mat4 u_ortho_mat;

        out vec2 v_tex_coord;

        void main(void) {
            gl_Position = u_ortho_mat * a_position;
            v_tex_coord = a_tex_coord;
        }),

        ZPL_MULTILINE(#version 420 core\n

        precision mediump float;

        in vec2 v_tex_coord;
        layout (binding = 0) uniform sampler2D u_tex;

        out vec4 o_colour;
        
        void main(void) {
            o_colour = texture2D(u_tex, v_tex_coord);
        })
    );

    zplgl_load_shader_from_memory_vf(&bs->ortho_col_shader,
        ZPL_MULTILINE(#version 420 core\n

        precision mediump float;
        
        layout (location = 0) in vec4 a_position;
        
        uniform mat4 u_ortho_mat;
        
        void main(void) {
            gl_Position = u_ortho_mat * a_position;
        }),

        ZPL_MULTILINE(#version 420 core\n
        
        uniform vec4 u_colour;
        
        out vec4 o_colour;
        
        void main(void) {
            o_colour = u_colour;
        })
    );


#if !defined(ZPLGL_NO_FONTS)
    zplgl_load_shader_from_memory_vf(&bs->font_shader,
        ZPL_MULTILINE(#version 420 core\n
        
        layout (location = 0) in vec4 a_position;
        layout (location = 1) in vec2 a_tex_coord;
        
        uniform mat4 u_ortho_mat;
        
        out vec2 v_tex_coord;
        
        void main(void) {
            gl_Position = u_ortho_mat * a_position;
            v_tex_coord = a_tex_coord;
        }),

        ZPL_MULTILINE(#version 420 core\n
        
        in vec2 v_tex_coord;
        
        uniform vec4 u_colour;
        
        layout (binding = 0) uniform sampler2D u_tex;
        
        out vec4 o_colour;
        
        void main(void) {
            o_colour = u_colour * texture2D(u_tex, v_tex_coord).r;
        })
    );

    glGenVertexArrays(1, &bs->font_vao);
    glBindVertexArray(bs->font_vao);

    bs->font_vbo = zplgl_make_vbo(NULL, zpl_size_of(zplgl_basic_vertex) * ZPLGL_MAX_RENDER_STRING_LENGTH * 4, GL_DYNAMIC_DRAW);

    for (i = 0; i < ZPLGL_MAX_RENDER_STRING_LENGTH; i++) {
        bs->font_indices[i * 6 + 0] = cast(zpl_u16)(i * 4 + 0);
        bs->font_indices[i * 6 + 1] = cast(zpl_u16)(i * 4 + 1);
        bs->font_indices[i * 6 + 2] = cast(zpl_u16)(i * 4 + 2);
        bs->font_indices[i * 6 + 3] = cast(zpl_u16)(i * 4 + 2);
        bs->font_indices[i * 6 + 4] = cast(zpl_u16)(i * 4 + 3);
        bs->font_indices[i * 6 + 5] = cast(zpl_u16)(i * 4 + 0);
    }
    bs->font_ebo = zplgl_make_ebo(bs->font_indices, zpl_size_of(zpl_u16) * ZPLGL_MAX_RENDER_STRING_LENGTH * 6, GL_STATIC_DRAW);

    bs->font_samplers[0] = zplgl_make_sampler(GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    bs->font_samplers[1] = zplgl_make_sampler(GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    bs->text_params[ZPLGL_TEXTPARAM_MAXWIDTH].val_i32 = 0;
    bs->text_params[ZPLGL_TEXTPARAM_JUSTIFY].val_i32 = ZPLGL_JUSTIFY_LEFT;
    bs->text_params[ZPLGL_TEXTPARAM_TEXTURE_FILTER].val_i32 = 0;
#endif
}

zpl_inline void zplgl_bs_set_resolution(zplgl_basic_state *bs, zpl_i32 window_width, zpl_i32 window_height) {
    zpl_f32 left = 0.0f;
    zpl_f32 right = cast(zpl_f32)window_width;
    zpl_f32 bottom = 0.0f;
    zpl_f32 top = cast(zpl_f32)window_height;
    zpl_f32 znear = 0.0f;
    zpl_f32 zfar = 1.0f;

    bs->width = window_width;
    bs->height = window_height;

    bs->ortho_mat[0] = 2.0f / (right - left);
    bs->ortho_mat[1] = 0.0f;
    bs->ortho_mat[2] = 0.0f;
    bs->ortho_mat[3] = 0.0f;

    bs->ortho_mat[4] = 0.0f;
    bs->ortho_mat[5] = 2.0f / (top - bottom);
    bs->ortho_mat[6] = 0.0f;
    bs->ortho_mat[7] = 0.0f;

    bs->ortho_mat[8] = 0.0f;
    bs->ortho_mat[9] = 0.0f;
    bs->ortho_mat[10] = -2.0f / (zfar - znear);
    bs->ortho_mat[11] = 0.0f;

    bs->ortho_mat[12] = -(right + left) / (right - left);
    bs->ortho_mat[13] = -(top + bottom) / (top - bottom);
    bs->ortho_mat[14] = -(zfar + znear) / (zfar - znear);
    bs->ortho_mat[15] = 1.0f;
}

zpl_inline void zplgl_bs_begin(zplgl_basic_state *bs) {
    glBindVertexArray(bs->vao);
    glDisable(GL_SCISSOR_TEST);
}

zpl_inline void zplgl_bs_end(zplgl_basic_state *bs) {
    glBindVertexArray(0);
}

void zplgl_bs_draw_textured_rect(zplgl_basic_state *bs, zplgl_texture *tex, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_b32 v_up) {
    bs->vertices[0].x = x;
    bs->vertices[0].y = y;
    bs->vertices[0].u = 0.0f;
    bs->vertices[0].v = v_up ? 0.0f : 1.0f;

    bs->vertices[1].x = x + w;
    bs->vertices[1].y = y;
    bs->vertices[1].u = 1.0f;
    bs->vertices[1].v = v_up ? 0.0f : 1.0f;

    bs->vertices[2].x = x + w;
    bs->vertices[2].y = y + h;
    bs->vertices[2].u = 1.0f;
    bs->vertices[2].v = v_up ? 1.0f : 0.0f;

    bs->vertices[3].x = x;
    bs->vertices[3].y = y + h;
    bs->vertices[3].u = 0.0f;
    bs->vertices[3].v = v_up ? 1.0f : 0.0f;

    zplgl_use_shader(&bs->ortho_tex_shader);
    zplgl_set_uniform_mat4(&bs->ortho_tex_shader, "u_ortho_mat", bs->ortho_mat);
    zplgl_bind_texture2d(tex, 0, bs->mipmap_sampler);

    zplgl_vbo_copy(bs->vbo, bs->vertices, 4 * zpl_size_of(bs->vertices[0]), 0);

    zplgl_vert_ptr_aa(0, 2, zplgl_basic_vertex, x);
    zplgl_vert_ptr_aa(1, 2, zplgl_basic_vertex, u);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bs->ebo);

    glEnable(GL_BLEND);
    glBlendEquationi(0, GL_FUNC_ADD);
    glBlendFunci(0, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

zpl_inline void zplgl_bs_draw_rect(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zplgl_color col) {
    zplgl_bs_draw_quad(bs,
        x, y,
        x + w, y,
        x + w, y + h,
        x, y + h,
        col);
}

zpl_inline void zplgl_bs_draw_rect_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zplgl_color col, zpl_f32 thickness) {
    zplgl_bs_draw_quad_outline(bs,
        x, y,
        x + w, y,
        x + w, y + h,
        x, y + h,
        col,
        thickness);
}


zpl_internal void zplgl__bs_setup_ortho_colour_state(zplgl_basic_state *bs, zpl_isize vertex_count, zplgl_color col) {

    zplgl_use_shader(&bs->ortho_col_shader);
    zplgl_set_uniform_mat4(&bs->ortho_col_shader, "u_ortho_mat", bs->ortho_mat);
    zplgl_set_uniform_colour(&bs->ortho_col_shader, "u_colour", col);

    zplgl_vbo_copy(bs->vbo, bs->vertices, vertex_count*zpl_size_of(bs->vertices[0]), 0);
    zplgl_vert_ptr_aa(0, 2, zplgl_basic_vertex, x);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bs->ebo);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

zpl_inline void zplgl_bs_draw_quad(zplgl_basic_state *bs,
    zpl_f32 x0, zpl_f32 y0,
    zpl_f32 x1, zpl_f32 y1,
    zpl_f32 x2, zpl_f32 y2,
    zpl_f32 x3, zpl_f32 y3,
    zplgl_color col) {
    bs->vertices[0].x = x0;
    bs->vertices[0].y = y0;

    bs->vertices[1].x = x1;
    bs->vertices[1].y = y1;

    bs->vertices[2].x = x2;
    bs->vertices[2].y = y2;

    bs->vertices[3].x = x3;
    bs->vertices[3].y = y3;

    zplgl__bs_setup_ortho_colour_state(bs, 4, col);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

zpl_inline void zplgl_bs_draw_quad_outline(zplgl_basic_state *bs,
    zpl_f32 x0, zpl_f32 y0,
    zpl_f32 x1, zpl_f32 y1,
    zpl_f32 x2, zpl_f32 y2,
    zpl_f32 x3, zpl_f32 y3,
    zplgl_color col, zpl_f32 thickness) {
    bs->vertices[0].x = x0;
    bs->vertices[0].y = y0;

    bs->vertices[1].x = x1;
    bs->vertices[1].y = y1;

    bs->vertices[2].x = x2;
    bs->vertices[2].y = y2;

    bs->vertices[3].x = x3;
    bs->vertices[3].y = y3;

    zplgl__bs_setup_ortho_colour_state(bs, 4, col);
    glLineWidth(thickness);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

zpl_inline void zplgl_bs_draw_line(zplgl_basic_state *bs, zpl_f32 x0, zpl_f32 y0, zpl_f32 x1, zpl_f32 y1, zplgl_color col, zpl_f32 thickness) {
    bs->vertices[0].x = x0;
    bs->vertices[0].y = y0;

    bs->vertices[1].x = x1;
    bs->vertices[1].y = y1;

    zplgl__bs_setup_ortho_colour_state(bs, 2, col);
    glLineWidth(thickness);
    glDrawArrays(GL_LINES, 0, 2);
}

zpl_inline void zplgl_bs_draw_elliptical_arc(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius_a, zpl_f32 radius_b,
    zpl_f32 min_angle, zpl_f32 max_angle, zplgl_color col) {
    zpl_isize i;

    bs->vertices[0].x = x;
    bs->vertices[0].y = y;

    for (i = 0; i < 31; i++) {
        zpl_f32 t = cast(zpl_f32)i / 30.0f;
        zpl_f32 a = zplgl_lerp(min_angle, max_angle, t);
        zpl_f32 c = zplgl_cos(a);
        zpl_f32 s = zplgl_sin(a);
        bs->vertices[i + 1].x = x + c * radius_a;
        bs->vertices[i + 1].y = y + s * radius_b;
    }

    zplgl__bs_setup_ortho_colour_state(bs, 32, col);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
}

zpl_inline void zplgl_bs_draw_elliptical_arc_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius_a, zpl_f32 radius_b,
    zpl_f32 min_angle, zpl_f32 max_angle, zplgl_color col, zpl_f32 thickness) {
    zpl_isize i;

    for (i = 0; i < 32; i++) {
        zpl_f32 t = cast(zpl_f32)i / 31.0f;
        zpl_f32 a = zplgl_lerp(min_angle, max_angle, t);
        zpl_f32 c = zplgl_cos(a);
        zpl_f32 s = zplgl_sin(a);
        bs->vertices[i + 1].x = x + c * radius_a;
        bs->vertices[i + 1].y = y + s * radius_b;
    }

    zplgl__bs_setup_ortho_colour_state(bs, 32, col);
    glLineWidth(thickness);
    glDrawArrays(GL_LINES, 0, 32);
}



zpl_inline void zplgl_bs_draw_circle(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius, zplgl_color col) {
    zplgl_bs_draw_elliptical_arc(bs, x, y, radius, radius, 0, ZPL_TAU, col);
}

zpl_inline void zplgl_bs_draw_circle_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 radius, zplgl_color col, zpl_f32 thickness) {
    zplgl_bs_draw_elliptical_arc_outline(bs, x, y, radius, radius, 0, ZPL_TAU, col, thickness);
}

void zplgl_bs_draw_rounded_rect_corners(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_u32 corners) {
    if ((2.0f*roundness > zplgl_abs(w)) ||
        (2.0f*roundness > zplgl_abs(h))) {
        roundness = 0.5f*zplgl_min(zplgl_abs(w), zplgl_abs(h));
    }

    if (roundness == 0 || corners == 0) {
        zplgl_bs_draw_rect(bs, x, y, w, h, col);
    }
    else {
        zpl_isize i, vc = 0;

        bs->vertices[vc].x = x + 0.5f*w;
        bs->vertices[vc].y = y + 0.5f*h;
        vc++;

        if (corners & 1) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.5f*ZPL_TAU, 0.75f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + roundness + c * roundness;
                bs->vertices[vc].y = y + roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y;
            vc++;
        }

        if (corners & 2) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.75f*ZPL_TAU, 1.00f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + w - roundness + c * roundness;
                bs->vertices[vc].y = y + roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x + w;
            bs->vertices[vc].y = y;
            vc++;
        }


        if (corners & 4) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.00f*ZPL_TAU, 0.25f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + w - roundness + c * roundness;
                bs->vertices[vc].y = y + h - roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x + w;
            bs->vertices[vc].y = y + h;
            vc++;
        }

        if (corners & 8) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.25f*ZPL_TAU, 0.50f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + roundness + c * roundness;
                bs->vertices[vc].y = y + h - roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y + h;
            vc++;
        }

        if (corners & 1) {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y + roundness;
        }
        else {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y;
        }
        vc++;

        zplgl__bs_setup_ortho_colour_state(bs, vc, col);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)vc);
    }
}

zpl_inline void zplgl_bs_draw_rounded_rect(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col) {
    zplgl_bs_draw_rounded_rect_corners(bs, x, y, w, h, roundness, col, 1 | 2 | 4 | 8);
}


void zplgl_bs_draw_rounded_rect_corners_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_f32 thickness, zpl_u32 corners) {
    if ((2.0f*roundness > zplgl_abs(w)) ||
        (2.0f*roundness > zplgl_abs(h))) {
        roundness = 0.5f*zplgl_min(zplgl_abs(w), zplgl_abs(h));
    }

    if (roundness == 0 || corners == 0) {
        zplgl_bs_draw_rect_outline(bs, x, y, w, h, col, thickness);
    }
    else {
        zpl_isize i, vc = 0;

        if (corners & 1) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.5f*ZPL_TAU, 0.75f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + roundness + c * roundness;
                bs->vertices[vc].y = y + roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y;
            vc++;
        }

        if (corners & 2) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.75f*ZPL_TAU, 1.00f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + w - roundness + c * roundness;
                bs->vertices[vc].y = y + roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x + w;
            bs->vertices[vc].y = y;
            vc++;
        }


        if (corners & 4) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.00f*ZPL_TAU, 0.25f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + w - roundness + c * roundness;
                bs->vertices[vc].y = y + h - roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x + w;
            bs->vertices[vc].y = y + h;
            vc++;
        }

        if (corners & 8) {
            for (i = 0; i < 6; i++) {
                zpl_f32 t = cast(zpl_f32)i / 5.0f;
                zpl_f32 a = zplgl_lerp(0.25f*ZPL_TAU, 0.50f*ZPL_TAU, t);
                zpl_f32 c = zplgl_cos(a);
                zpl_f32 s = zplgl_sin(a);
                bs->vertices[vc].x = x + roundness + c * roundness;
                bs->vertices[vc].y = y + h - roundness + s * roundness;
                vc++;
            }
        }
        else {
            bs->vertices[vc].x = x;
            bs->vertices[vc].y = y + h;
            vc++;
        }

        zplgl__bs_setup_ortho_colour_state(bs, vc, col);
        glLineWidth(thickness);
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)vc);
    }
}

zpl_inline void zplgl_bs_draw_rounded_rect_outline(zplgl_basic_state *bs, zpl_f32 x, zpl_f32 y, zpl_f32 w, zpl_f32 h, zpl_f32 roundness, zplgl_color col, zpl_f32 thickness) {
    zplgl_bs_draw_rounded_rect_corners_outline(bs, x, y, w, h, roundness, col, thickness, 1 | 2 | 4 | 8);
}




#if !defined(ZPLGL_NO_FONTS)


zpl_isize zplgl_bs_draw_substring(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *str, zpl_isize len) {
    zpl_isize char_count = zpl_utf8_strnlen((zpl_u8 *)str, len);
    zpl_isize line_count = 0;
    if (char_count > 0) {
        char const *ptr = str;

        zpl_f32 sf = 1.0f / cast(zpl_f32)font->bitmap_width;
        zpl_f32 tf = 1.0f / cast(zpl_f32)font->bitmap_height;

        zpl_f32 ox, oy;
        zpl_f32 px, py;

        zpl_isize glyph_count = 0, i;
        zpl_f32 font_height = font->size;
        zpl_i32 max_width = bs->text_params[ZPLGL_TEXTPARAM_MAXWIDTH].val_i32;

        zplgl_justify_type justify = cast(zplgl_justify_type)bs->text_params[ZPLGL_TEXTPARAM_JUSTIFY].val_i32;
        if (justify == ZPLGL_JUSTIFY_CENTER) {
            zpl_f32 width;
            zplgl_get_string_dimensions(font, ptr, &width, NULL);
            x = zplgl_round(x - width * 0.5f);
        }
        else if (justify == ZPLGL_JUSTIFY_RIGHT) {
            zpl_f32 width;
            zplgl_get_string_dimensions(font, ptr, &width, NULL);
            x = zplgl_round(x - width);
        }

        line_count = 1;

        ox = x;
        oy = y;
        px = ox;
        py = oy;

        for (i = 0; i < char_count; i++) {
            zpl_char32 cp;
            zpl_isize byte_len, curr_index, draw_this_glyph_count = 1, j;
            zplgl_glyph_info *gi;

            byte_len = zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &cp);
            ptr += byte_len;
            if (ptr - str > len)
                break;

            if (cp == '\t') {
                draw_this_glyph_count = ZPLGL_TAB_CHARACTER_WIDTH;
                cp = ' '; // TODO(bill): Set tab to be space
            }


            gi = zplgl_get_glyph_info(font, cp, &curr_index);
            if (!gi) {
                gi = zplgl_get_glyph_info(font, '?', &curr_index);
            }

            if (gi) {
                for (j = 0; j < draw_this_glyph_count; j++) {
                    zpl_f32 s0, t0, s1, t1;
                    zpl_f32 x0, y0, x1, y1;
                    zpl_f32 kern = 0.0f;


                    if (cp == '\r' || cp == '\n' ||
                        (max_width > 0 && px - ox + gi->xadv >= cast(zpl_f32)max_width)) {
                        px = ox;

                        py -= font_height;
                        line_count += 2;

                        if (cp == '\r' || cp == '\n') {
                            if (cp == '\r' && ptr[1] == '\n')
                                ptr++;
                            continue;
                        }
                    }

                    s0 = cast(zpl_f32)gi->s0 * sf;
                    t0 = cast(zpl_f32)gi->t0 * tf;
                    s1 = cast(zpl_f32)gi->s1 * sf;
                    t1 = cast(zpl_f32)gi->t1 * tf;

                    x0 = px + gi->xoff;
                    y0 = py - gi->yoff;
                    x1 = x0 + (gi->s1 - gi->s0);
                    y1 = y0 + (gi->t0 - gi->t1);

                    bs->font_vertices[glyph_count * 4 + 0].x = x0;
                    bs->font_vertices[glyph_count * 4 + 0].y = y0;
                    bs->font_vertices[glyph_count * 4 + 0].u = s0;
                    bs->font_vertices[glyph_count * 4 + 0].v = t0;

                    bs->font_vertices[glyph_count * 4 + 1].x = x1;
                    bs->font_vertices[glyph_count * 4 + 1].y = y0;
                    bs->font_vertices[glyph_count * 4 + 1].u = s1;
                    bs->font_vertices[glyph_count * 4 + 1].v = t0;

                    bs->font_vertices[glyph_count * 4 + 2].x = x1;
                    bs->font_vertices[glyph_count * 4 + 2].y = y1;
                    bs->font_vertices[glyph_count * 4 + 2].u = s1;
                    bs->font_vertices[glyph_count * 4 + 2].v = t1;

                    bs->font_vertices[glyph_count * 4 + 3].x = x0;
                    bs->font_vertices[glyph_count * 4 + 3].y = y1;
                    bs->font_vertices[glyph_count * 4 + 3].u = s0;
                    bs->font_vertices[glyph_count * 4 + 3].v = t1;

                    glyph_count++;

                    if (i < char_count - 1) {
                        zpl_isize next_index;
                        zpl_char32 next_cp = 0;
                        zplgl_glyph_info *ngi;

                        zpl_utf8_decode((zpl_u8 *)ptr, len - (ptr - str), &next_cp);
                        ngi = zplgl_get_glyph_info(font, next_cp, &next_index);
                        if (ngi) {
                            kern = zplgl_get_font_kerning_from_glyph_indices(font, curr_index, next_index);
                        }
                    }

                    px += gi->xadv + kern;
                }
            }
        }


        if (glyph_count > 0) {
            zpl_isize sampler_index = 0;

            zplgl_use_shader(&bs->font_shader);
            zplgl_set_uniform_mat4(&bs->font_shader, "u_ortho_mat", bs->ortho_mat);
            zplgl_set_uniform_colour(&bs->font_shader, "u_colour", col);
            ZPL_ASSERT(bs->text_params[ZPLGL_TEXTPARAM_TEXTURE_FILTER].val_i32 < zpl_count_of(bs->font_samplers));
            if (bs->text_params[ZPLGL_TEXTPARAM_TEXTURE_FILTER].val_i32 < zpl_count_of(bs->font_samplers))
                sampler_index = bs->text_params[ZPLGL_TEXTPARAM_TEXTURE_FILTER].val_i32;

            zplgl_bind_texture2d(&font->texture, 0, bs->font_samplers[sampler_index]);
            zplgl_vbo_copy(bs->font_vbo, bs->font_vertices, zpl_size_of(bs->font_vertices[0]) * glyph_count * 4, 0);

            zplgl_vert_ptr_aa(0, 2, zplgl_basic_vertex, x);
            zplgl_vert_ptr_aa(1, 2, zplgl_basic_vertex, u);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bs->font_ebo);

            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            glDrawElements(GL_TRIANGLES, (GLsizei)(glyph_count * 6), GL_UNSIGNED_SHORT, NULL);

        }
    }
    return line_count;
}

zpl_isize zplgl_bs_draw_string(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *fmt, ...) {
    zpl_isize len;
    va_list va;
    va_start(va, fmt);
    len = zplgl_bs_draw_string_va(bs, font, x, y, col, fmt, va);
    va_end(va);
    return len;
}

zpl_inline zpl_isize zplgl_bs_draw_string_va(zplgl_basic_state *bs, zplgl_font *font, zpl_f32 x, zpl_f32 y, zplgl_color col, char const *fmt, va_list va) {
    zpl_isize len = zpl_snprintf_va(bs->font_text_buffer, zpl_size_of(bs->font_text_buffer),
        fmt, va);
    zpl_isize char_count = zpl_utf8_strnlen((zpl_u8 *)bs->font_text_buffer, len);
    if (char_count <= 0)
        return 0;
    return zplgl_bs_draw_substring(bs, font, x, y, col, bs->font_text_buffer, len);
}

#endif // !defined(ZPLGL_NO_FONTS)
#endif // !defined(ZPLGL_NO_BASIC_STATE)

#endif // ZPL_OPENGL
