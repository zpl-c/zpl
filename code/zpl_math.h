/*

ZPL - Math module

License:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.
    
Warranty:
    No warranty is implied, use at your own risk.
    
Usage:
    #define ZPL_MATH_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:
    
    #define ZPL_MATH_IMPLEMENTATION
    #include"zpl_math.h"
    
Credits:
    Ginger Bill (GitHub: gingerBill)
    
Version History:
    1.00 - Initial Version
    
*/

#ifndef ZPL_MATH_INCLUDE_ZPL_MATH_H
#define ZPL_MATH_INCLUDE_ZPL_MATH_H

#include <stddef.h>

#if !defined(ZPL_MATH_NO_MATH_H)
#include <math.h>
#else
#include <intrin.h>
#endif

#ifndef ZPL_MATH_DEF
#ifdef ZPL_MATH_STATIC
#define ZPL_MATH_DEF static
#else
#define ZPL_MATH_DEF extern
#endif
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4201)
#endif

typedef union zplVec2 {
    struct { float x, y; };
    float e[2];
} zplVec2;

typedef union zplVec3 {
    struct { float x, y, z; };
    struct { float r, g, b; };
    
    zplVec2 xy;
    float e[3];
} zplVec3;

typedef union zplVec4 {
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { zplVec2 xy, zw; };
    zplVec3 xyz;
    zplVec3 rzpl;
    float e[4];
} zplVec4;

typedef union zplMat2 {
    struct { zplVec2 x, y; };
    zplVec2 col[2];
    float e[4];
} zplMat2;

typedef union zplMat3 {
    struct { zplVec3 x, y, z; };
    zplVec3 col[3];
    float e[9];
} zplMat3;

typedef union zplMat4 {
    struct { zplVec4 x, y, z, w; };
    zplVec4 col[4];
    float e[16];
} zplMat4;


typedef union zplQuat {
    struct { float x, y, z, w; };
    zplVec4 xyzw;
    zplVec3 xyz;
    float e[4];
} zplQuat;


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

typedef float zplFloat2[2];
typedef float zplFloat3[3];
typedef float zplFloat4[4];


typedef struct zplRect2 { zplVec2 pos, dim; } zplRect2;
typedef struct zplRect3 { zplVec3 pos, dim; } zplRect3;

typedef struct zplAabb2 { zplVec2 centre, half_size; } zplAabb2;
typedef struct zplAabb3 { zplVec3 centre, half_size; } zplAabb3;

#if defined(_MSC_VER)
typedef unsigned __int32 zpl_math_u32;
typedef unsigned __int64 zpl_math_u64;
#else
#if defined(ZPL_USE_STDINT)
#include <stdint.h>
typedef uint32_t zpl_math_u32;
typedef uint64_t zpl_math_u64;
#else
typedef unsigned int       zpl_math_u32;
typedef unsigned long long zpl_math_u64;
#endif
#endif

typedef short zplHalf;


#ifndef ZPL_MATH_CONSTANTS
#define ZPL_MATH_CONSTANTS
#define ZPL_MATH_EPSILON      1.19209290e-7f
#define ZPL_MATH_ZERO         0.0f
#define ZPL_MATH_ONE          1.0f
#define ZPL_MATH_TWO_THIRDS   0.666666666666666666666666666666666666667f

#define ZPL_MATH_TAU          6.28318530717958647692528676655900576f
#define ZPL_MATH_PI           3.14159265358979323846264338327950288f
#define ZPL_MATH_ONE_OVER_TAU 0.636619772367581343075535053490057448f
#define ZPL_MATH_ONE_OVER_PI  0.159154943091895335768883763372514362f

#define ZPL_MATH_TAU_OVER_2   3.14159265358979323846264338327950288f
#define ZPL_MATH_TAU_OVER_4   1.570796326794896619231321691639751442f
#define ZPL_MATH_TAU_OVER_8   0.785398163397448309615660845819875721f

#define ZPL_MATH_E            2.71828182845904523536f
#define ZPL_MATH_SQRT_TWO     1.41421356237309504880168872420969808f
#define ZPL_MATH_SQRT_THREE   1.73205080756887729352744634150587236f
#define ZPL_MATH_SQRT_FIVE    2.23606797749978969640917366873127623f

#define ZPL_MATH_LOG_TWO      0.693147180559945309417232121458176568f
#define ZPL_MATH_LOG_TEN      2.30258509299404568401799145468436421f
#endif


#if defined(__cplusplus)
extern "C" {
#endif
    
#ifndef zpl_clamp
#define zpl_clamp(x, lower, upper) (zpl_min(zpl_max(x, (lower)), (upper)))
#endif
#ifndef zpl_clamp01
#define zpl_clamp01(x) zpl_clamp(x, 0, 1)
#endif
    
#ifndef zpl_square
#define zpl_square(x) ((x)*(x))
#endif
    
#ifndef zpl_cube
#define zpl_cube(x) ((x)*(x)*(x))
#endif
    
#ifndef zpl_abs
#define zpl_abs(x) ((x) > 0 ? (x) : -(x))
#endif
    
#ifndef zpl_sign
#define zpl_sign(x) ((x) >= 0 ? 1 : -1)
#endif
    
    
    ZPL_MATH_DEF float zpl_to_radians(float degrees);
    ZPL_MATH_DEF float zpl_to_degrees(float radians);
    
    /* NOTE: Because to interpolate angles */
    ZPL_MATH_DEF float zpl_angle_diff(float radians_a, float radians_b);
    
#ifndef zpl_min
#define zpl_min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef zpl_max
#define zpl_max(a, b) ((a) > (b) ? (a) : (b))
#endif
    
#ifndef zpl_min3
#define zpl_min3(a, b, c) zpl_min(zpl_min(a, b), c)
#endif
    
#ifndef zpl_max3
#define zpl_max3(a, b, c) zpl_max(zpl_max(a, b), c)
#endif
    
    
    ZPL_MATH_DEF float zpl_copy_sign  (float x, float y);
    ZPL_MATH_DEF float zpl_remainder  (float x, float y);
    ZPL_MATH_DEF float zpl_mod        (float x, float y);
    ZPL_MATH_DEF float zpl_sqrt       (float a);
    ZPL_MATH_DEF float zpl_rsqrt      (float a);
    ZPL_MATH_DEF float zpl_quake_rsqrt(float a); /* NOTE: It's probably better to use 1.0f/zpl_sqrt(a)
* And for simd, there is usually isqrt functions too!
*/
    ZPL_MATH_DEF float zpl_sin    (float radians);
    ZPL_MATH_DEF float zpl_cos    (float radians);
    ZPL_MATH_DEF float zpl_tan    (float radians);
    ZPL_MATH_DEF float zpl_arcsin (float a);
    ZPL_MATH_DEF float zpl_arccos (float a);
    ZPL_MATH_DEF float zpl_arctan (float a);
    ZPL_MATH_DEF float zpl_arctan2(float y, float x);
    
    ZPL_MATH_DEF float zpl_exp      (float x);
    ZPL_MATH_DEF float zpl_exp2     (float x);
    ZPL_MATH_DEF float zpl_log      (float x);
    ZPL_MATH_DEF float zpl_log2     (float x);
    ZPL_MATH_DEF float zpl_fast_exp (float x);  /* NOTE: Only valid from -1 <= x <= +1 */
    ZPL_MATH_DEF float zpl_fast_exp2(float x); /* NOTE: Only valid from -1 <= x <= +1 */
    ZPL_MATH_DEF float zpl_pow      (float x, float y); /* x^y */
    
    ZPL_MATH_DEF float zpl_round(float x);
    ZPL_MATH_DEF float zpl_floor(float x);
    ZPL_MATH_DEF float zpl_ceil (float x);
    
    ZPL_MATH_DEF float  zpl_half_to_float(zplHalf value);
    ZPL_MATH_DEF zplHalf zpl_float_to_half(float value);
    
    
    ZPL_MATH_DEF zplVec2 zpl_vec2_zero(void);
    ZPL_MATH_DEF zplVec2 zpl_vec2     (float x, float y);
    ZPL_MATH_DEF zplVec2 zpl_vec2v    (float x[2]);
    
    ZPL_MATH_DEF zplVec3 zpl_vec3_zero(void);
    ZPL_MATH_DEF zplVec3 zpl_vec3     (float x, float y, float z);
    ZPL_MATH_DEF zplVec3 zpl_vec3v    (float x[3]);
    
    ZPL_MATH_DEF zplVec4 zpl_vec4_zero(void);
    ZPL_MATH_DEF zplVec4 zpl_vec4     (float x, float y, float z, float w);
    ZPL_MATH_DEF zplVec4 zpl_vec4v    (float x[4]);
    
    
    ZPL_MATH_DEF void zpl_vec2_add(zplVec2 *d, zplVec2 v0, zplVec2 v1);
    ZPL_MATH_DEF void zpl_vec2_sub(zplVec2 *d, zplVec2 v0, zplVec2 v1);
    ZPL_MATH_DEF void zpl_vec2_mul(zplVec2 *d, zplVec2 v,  float s);
    ZPL_MATH_DEF void zpl_vec2_div(zplVec2 *d, zplVec2 v,  float s);
    
    ZPL_MATH_DEF void zpl_vec3_add(zplVec3 *d, zplVec3 v0, zplVec3 v1);
    ZPL_MATH_DEF void zpl_vec3_sub(zplVec3 *d, zplVec3 v0, zplVec3 v1);
    ZPL_MATH_DEF void zpl_vec3_mul(zplVec3 *d, zplVec3 v,  float s);
    ZPL_MATH_DEF void zpl_vec3_div(zplVec3 *d, zplVec3 v,  float s);
    
    ZPL_MATH_DEF void zpl_vec4_add(zplVec4 *d, zplVec4 v0, zplVec4 v1);
    ZPL_MATH_DEF void zpl_vec4_sub(zplVec4 *d, zplVec4 v0, zplVec4 v1);
    ZPL_MATH_DEF void zpl_vec4_mul(zplVec4 *d, zplVec4 v,  float s);
    ZPL_MATH_DEF void zpl_vec4_div(zplVec4 *d, zplVec4 v,  float s);
    
    ZPL_MATH_DEF void zpl_vec2_addeq(zplVec2 *d, zplVec2 v);
    ZPL_MATH_DEF void zpl_vec2_subeq(zplVec2 *d, zplVec2 v);
    ZPL_MATH_DEF void zpl_vec2_muleq(zplVec2 *d, float s);
    ZPL_MATH_DEF void zpl_vec2_diveq(zplVec2 *d, float s);
    
    ZPL_MATH_DEF void zpl_vec3_addeq(zplVec3 *d, zplVec3 v);
    ZPL_MATH_DEF void zpl_vec3_subeq(zplVec3 *d, zplVec3 v);
    ZPL_MATH_DEF void zpl_vec3_muleq(zplVec3 *d, float s);
    ZPL_MATH_DEF void zpl_vec3_diveq(zplVec3 *d, float s);
    
    ZPL_MATH_DEF void zpl_vec4_addeq(zplVec4 *d, zplVec4 v);
    ZPL_MATH_DEF void zpl_vec4_subeq(zplVec4 *d, zplVec4 v);
    ZPL_MATH_DEF void zpl_vec4_muleq(zplVec4 *d, float s);
    ZPL_MATH_DEF void zpl_vec4_diveq(zplVec4 *d, float s);
    
    ZPL_MATH_DEF float zpl_vec2_dot(zplVec2 v0, zplVec2 v1);
    ZPL_MATH_DEF float zpl_vec3_dot(zplVec3 v0, zplVec3 v1);
    ZPL_MATH_DEF float zpl_vec4_dot(zplVec4 v0, zplVec4 v1);
    
    ZPL_MATH_DEF void zpl_vec2_cross(float *d, zplVec2 v0, zplVec2 v1);
    ZPL_MATH_DEF void zpl_vec3_cross(zplVec3 *d, zplVec3 v0, zplVec3 v1);
    
    ZPL_MATH_DEF float zpl_vec2_mag2(zplVec2 v);
    ZPL_MATH_DEF float zpl_vec3_mag2(zplVec3 v);
    ZPL_MATH_DEF float zpl_vec4_mag2(zplVec4 v);
    
    ZPL_MATH_DEF float zpl_vec2_mag(zplVec2 v);
    ZPL_MATH_DEF float zpl_vec3_mag(zplVec3 v);
    ZPL_MATH_DEF float zpl_vec4_mag(zplVec4 v);
    
    ZPL_MATH_DEF void zpl_vec2_norm(zplVec2 *d, zplVec2 v);
    ZPL_MATH_DEF void zpl_vec3_norm(zplVec3 *d, zplVec3 v);
    ZPL_MATH_DEF void zpl_vec4_norm(zplVec4 *d, zplVec4 v);
    
    ZPL_MATH_DEF void zpl_vec2_norm0(zplVec2 *d, zplVec2 v);
    ZPL_MATH_DEF void zpl_vec3_norm0(zplVec3 *d, zplVec3 v);
    ZPL_MATH_DEF void zpl_vec4_norm0(zplVec4 *d, zplVec4 v);
    
    ZPL_MATH_DEF void zpl_vec2_reflect(zplVec2 *d, zplVec2 i, zplVec2 n);
    ZPL_MATH_DEF void zpl_vec3_reflect(zplVec3 *d, zplVec3 i, zplVec3 n);
    ZPL_MATH_DEF void zpl_vec2_refract(zplVec2 *d, zplVec2 i, zplVec2 n, float eta);
    ZPL_MATH_DEF void zpl_vec3_refract(zplVec3 *d, zplVec3 i, zplVec3 n, float eta);
    
    ZPL_MATH_DEF float zpl_vec2_aspect_ratio(zplVec2 v);
    
    
    ZPL_MATH_DEF void zpl_mat2_identity   (zplMat2 *m);
    ZPL_MATH_DEF void zpl_float22_identity(float m[2][2]);
    
    ZPL_MATH_DEF void  zpl_mat2_transpose  (zplMat2 *m);
    ZPL_MATH_DEF void  zpl_mat2_mul        (zplMat2 *out, zplMat2 *m1, zplMat2 *m2);
    ZPL_MATH_DEF void  zpl_mat2_mul_vec2   (zplVec2 *out, zplMat2 *m, zplVec2 in);
    ZPL_MATH_DEF void  zpl_mat2_inverse    (zplMat2 *out, zplMat2 *in);
    ZPL_MATH_DEF float zpl_mat2_determinate(zplMat2 *m);
    
    ZPL_MATH_DEF zplMat2 *zpl_mat2_v(zplVec2 m[2]);
    ZPL_MATH_DEF zplMat2 *zpl_mat2_f(float m[2][2]);
    ZPL_MATH_DEF zplFloat2 *zpl_float22_m(zplMat2 *m);
    ZPL_MATH_DEF zplFloat2 *zpl_float22_v(zplVec2 m[2]);
    ZPL_MATH_DEF zplFloat2 *zpl_float22_4(float m[4]);
    
    ZPL_MATH_DEF void zpl_float22_transpose(float (*vec)[2]);
    ZPL_MATH_DEF void zpl_float22_mul      (float (*out)[2], float (*mat1)[2], float (*mat2)[2]);
    ZPL_MATH_DEF void zpl_float22_mul_vec2 (zplVec2 *out, float m[2][2], zplVec2 in);
    
    
    ZPL_MATH_DEF void zpl_mat3_identity   (zplMat3 *m);
    ZPL_MATH_DEF void zpl_float33_identity(float m[3][3]);
    
    ZPL_MATH_DEF void  zpl_mat3_transpose  (zplMat3 *m);
    ZPL_MATH_DEF void  zpl_mat3_mul        (zplMat3 *out, zplMat3 *m1, zplMat3 *m2);
    ZPL_MATH_DEF void  zpl_mat3_mul_vec3   (zplVec3 *out, zplMat3 *m, zplVec3 in);
    ZPL_MATH_DEF void  zpl_mat3_inverse    (zplMat3 *out, zplMat3 *in);
    ZPL_MATH_DEF float zpl_mat3_determinate(zplMat3 *m);
    
    
    ZPL_MATH_DEF zplMat3 *zpl_mat3_v(zplVec3 m[3]);
    ZPL_MATH_DEF zplMat3 *zpl_mat3_f(float m[3][3]);
    
    ZPL_MATH_DEF zplFloat3 *zpl_float33_m(zplMat3 *m);
    ZPL_MATH_DEF zplFloat3 *zpl_float33_v(zplVec3 m[3]);
    ZPL_MATH_DEF zplFloat3 *zpl_float33_9(float m[9]);
    
    ZPL_MATH_DEF void zpl_float33_transpose(float (*vec)[3]);
    ZPL_MATH_DEF void zpl_float33_mul      (float (*out)[3], float (*mat1)[3], float (*mat2)[3]);
    ZPL_MATH_DEF void zpl_float33_mul_vec3 (zplVec3 *out, float m[3][3], zplVec3 in);
    
    ZPL_MATH_DEF void zpl_mat4_identity   (zplMat4 *m);
    ZPL_MATH_DEF void zpl_float44_identity(float m[4][4]);
    
    ZPL_MATH_DEF void  zpl_mat4_transpose  (zplMat4 *m);
    ZPL_MATH_DEF void  zpl_mat4_mul        (zplMat4 *out, zplMat4 *m1, zplMat4 *m2);
    ZPL_MATH_DEF void  zpl_mat4_mul_vec4   (zplVec4 *out, zplMat4 *m, zplVec4 in);
    ZPL_MATH_DEF void  zpl_mat4_inverse    (zplMat4 *out, zplMat4 *in);
    
    ZPL_MATH_DEF zplMat4 *zpl_mat4_v(zplVec4 m[4]);
    ZPL_MATH_DEF zplMat4 *zpl_mat4_f(float m[4][4]);
    
    ZPL_MATH_DEF zplFloat4 *zpl_float44_m (zplMat4 *m);
    ZPL_MATH_DEF zplFloat4 *zpl_float44_v (zplVec4 m[4]);
    ZPL_MATH_DEF zplFloat4 *zpl_float44_16(float m[16]);
    
    ZPL_MATH_DEF void zpl_float44_transpose(float (*vec)[4]);
    ZPL_MATH_DEF void zpl_float44_mul      (float (*out)[4], float (*mat1)[4], float (*mat2)[4]);
    ZPL_MATH_DEF void zpl_float44_mul_vec4 (zplVec4 *out, float m[4][4], zplVec4 in);
    
    
    ZPL_MATH_DEF void zpl_mat4_translate           (zplMat4 *out, zplVec3 v);
    ZPL_MATH_DEF void zpl_mat4_rotate              (zplMat4 *out, zplVec3 v, float angle_radians);
    ZPL_MATH_DEF void zpl_mat4_scale               (zplMat4 *out, zplVec3 v);
    ZPL_MATH_DEF void zpl_mat4_scalef              (zplMat4 *out, float s);
    ZPL_MATH_DEF void zpl_mat4_ortho2d             (zplMat4 *out, float left, float right, float bottom, float top);
    ZPL_MATH_DEF void zpl_mat4_ortho3d             (zplMat4 *out, float left, float right, float bottom, float top, float z_near, float z_far);
    ZPL_MATH_DEF void zpl_mat4_perspective         (zplMat4 *out, float fovy, float aspect, float z_near, float z_far);
    ZPL_MATH_DEF void zpl_mat4_infinite_perspective(zplMat4 *out, float fovy, float aspect, float z_near);
    
    ZPL_MATH_DEF void zpl_mat4_look_at(zplMat4 *out, zplVec3 eye, zplVec3 centre, zplVec3 up);
    
    
    
    ZPL_MATH_DEF zplQuat zpl_quat             (float x, float y, float z, float w);
    ZPL_MATH_DEF zplQuat zpl_quatv            (float e[4]);
    ZPL_MATH_DEF zplQuat zpl_quat_axis_angle  (zplVec3 axis, float angle_radians);
    ZPL_MATH_DEF zplQuat zpl_quat_euler_angles(float pitch, float yaw, float roll);
    ZPL_MATH_DEF zplQuat zpl_quat_identity    (void);
    
    ZPL_MATH_DEF void zpl_quat_add(zplQuat *d, zplQuat q0, zplQuat q1);
    ZPL_MATH_DEF void zpl_quat_sub(zplQuat *d, zplQuat q0, zplQuat q1);
    ZPL_MATH_DEF void zpl_quat_mul(zplQuat *d, zplQuat q0, zplQuat q1);
    ZPL_MATH_DEF void zpl_quat_div(zplQuat *d, zplQuat q0, zplQuat q1);
    
    ZPL_MATH_DEF void zpl_quat_mulf(zplQuat *d, zplQuat q, float s);
    ZPL_MATH_DEF void zpl_quat_divf(zplQuat *d, zplQuat q, float s);
    
    
    ZPL_MATH_DEF void zpl_quat_addeq(zplQuat *d, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_subeq(zplQuat *d, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_muleq(zplQuat *d, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_diveq(zplQuat *d, zplQuat q);
    
    
    ZPL_MATH_DEF void zpl_quat_muleqf(zplQuat *d, float s);
    ZPL_MATH_DEF void zpl_quat_diveqf(zplQuat *d, float s);
    
    
    
    
    ZPL_MATH_DEF float zpl_quat_dot(zplQuat q0, zplQuat q1);
    ZPL_MATH_DEF float zpl_quat_mag(zplQuat q);
    
    ZPL_MATH_DEF void zpl_quat_norm   (zplQuat *d, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_conj   (zplQuat *d, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_inverse(zplQuat *d, zplQuat q);
    
    ZPL_MATH_DEF void  zpl_quat_axis (zplVec3 *axis, zplQuat q);
    ZPL_MATH_DEF float zpl_quat_angle(zplQuat q);
    
    ZPL_MATH_DEF float zpl_quat_pitch(zplQuat q);
    ZPL_MATH_DEF float zpl_quat_yaw  (zplQuat q);
    ZPL_MATH_DEF float zpl_quat_roll (zplQuat q);
    
    /* NOTE: Rotate v by q */
    ZPL_MATH_DEF void zpl_quat_rotate_vec3(zplVec3 *d, zplQuat q, zplVec3 v);
    ZPL_MATH_DEF void zpl_mat4_from_quat  (zplMat4 *out, zplQuat q);
    ZPL_MATH_DEF void zpl_quat_from_mat4  (zplQuat *out, zplMat4 *m);
    
    
    
    /* Interpolations */
    ZPL_MATH_DEF float zpl_lerp         (float a, float b, float t);
    ZPL_MATH_DEF float zpl_unlerp       (float t, float a, float b);
    ZPL_MATH_DEF float zpl_smooth_step  (float a, float b, float t);
    ZPL_MATH_DEF float zpl_smoother_step(float a, float b, float t);
    
    ZPL_MATH_DEF void zpl_vec2_lerp(zplVec2 *d, zplVec2 a, zplVec2 b, float t);
    ZPL_MATH_DEF void zpl_vec3_lerp(zplVec3 *d, zplVec3 a, zplVec3 b, float t);
    ZPL_MATH_DEF void zpl_vec4_lerp(zplVec4 *d, zplVec4 a, zplVec4 b, float t);
    
    ZPL_MATH_DEF void zpl_quat_lerp (zplQuat *d, zplQuat a, zplQuat b, float t);
    ZPL_MATH_DEF void zpl_quat_nlerp(zplQuat *d, zplQuat a, zplQuat b, float t);
    ZPL_MATH_DEF void zpl_quat_slerp(zplQuat *d, zplQuat a, zplQuat b, float t);
    ZPL_MATH_DEF void zpl_quat_nquad(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t);
    ZPL_MATH_DEF void zpl_quat_squad(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t);
    ZPL_MATH_DEF void zpl_quat_slerp_approx(zplQuat *d, zplQuat a, zplQuat b, float t);
    ZPL_MATH_DEF void zpl_quat_squad_approx(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t);
    
    
    /* Rects */
    ZPL_MATH_DEF zplRect2 zpl_rect2(zplVec2 pos, zplVec2 dim);
    ZPL_MATH_DEF zplRect3 zpl_rect3(zplVec3 pos, zplVec3 dim);
    
    ZPL_MATH_DEF int zpl_rect2_contains           (zplRect2 a, float x, float y);
    ZPL_MATH_DEF int zpl_rect2_contains_vec2      (zplRect2 a, zplVec2 p);
    ZPL_MATH_DEF int zpl_rect2_intersects         (zplRect2 a, zplRect2 b);
    ZPL_MATH_DEF int zpl_rect2_intersection_result(zplRect2 a, zplRect2 b, zplRect2 *intersection);
    
    
#ifndef	ZPL_MURMUR64_DEFAULT_SEED
#define ZPL_MURMUR64_DEFAULT_SEED 0x9747b28c
#endif
    /* Hashing */
    ZPL_MATH_DEF zpl_math_u64 zpl_hash_murmur64(void const *key, size_t num_bytes, zpl_math_u64 seed);
    
    /* Random */
    /* TODO: Use a generator for the random numbers */
    ZPL_MATH_DEF float zpl_random_range_float(float min_inc, float max_inc);
    ZPL_MATH_DEF int   zpl_random_range_int  (int min_inc, int max_inc);
    ZPL_MATH_DEF float zpl_random01          (void);
    
    
    
#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)

/* TODO: How should I apply ZPL_MATH_DEF to these operator overloads? */

inline bool operator==(zplVec2 a, zplVec2 b) { return (a.x == b.x) && (a.y == b.y); }
inline bool operator!=(zplVec2 a, zplVec2 b) { return !operator==(a, b); }

inline zplVec2 operator+(zplVec2 a) { return a; }
inline zplVec2 operator-(zplVec2 a) { zplVec2 r = {-a.x, -a.y}; return r; }

inline zplVec2 operator+(zplVec2 a, zplVec2 b) { zplVec2 r; zpl_vec2_add(&r, a, b); return r; }
inline zplVec2 operator-(zplVec2 a, zplVec2 b) { zplVec2 r; zpl_vec2_sub(&r, a, b); return r; }

inline zplVec2 operator*(zplVec2 a, float scalar) { zplVec2 r; zpl_vec2_mul(&r, a, scalar); return r; }
inline zplVec2 operator*(float scalar, zplVec2 a) { return operator*(a, scalar); }

inline zplVec2 operator/(zplVec2 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zplVec2 operator*(zplVec2 a, zplVec2 b) { zplVec2 r = {a.x*b.x, a.y*b.y}; return r; }
inline zplVec2 operator/(zplVec2 a, zplVec2 b) { zplVec2 r = {a.x/b.x, a.y/b.y}; return r; }

inline zplVec2 &operator+=(zplVec2 &a, zplVec2 b)       { return (a = a + b); }
inline zplVec2 &operator-=(zplVec2 &a, zplVec2 b)       { return (a = a - b); }
inline zplVec2 &operator*=(zplVec2 &a, float scalar) { return (a = a * scalar); }
inline zplVec2 &operator/=(zplVec2 &a, float scalar) { return (a = a / scalar); }


inline bool operator==(zplVec3 a, zplVec3 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
inline bool operator!=(zplVec3 a, zplVec3 b) { return !operator==(a, b); }

inline zplVec3 operator+(zplVec3 a) { return a; }
inline zplVec3 operator-(zplVec3 a) { zplVec3 r = {-a.x, -a.y, -a.z}; return r; }

inline zplVec3 operator+(zplVec3 a, zplVec3 b) { zplVec3 r; zpl_vec3_add(&r, a, b); return r; }
inline zplVec3 operator-(zplVec3 a, zplVec3 b) { zplVec3 r; zpl_vec3_sub(&r, a, b); return r; }

inline zplVec3 operator*(zplVec3 a, float scalar) { zplVec3 r; zpl_vec3_mul(&r, a, scalar); return r; }
inline zplVec3 operator*(float scalar, zplVec3 a) { return operator*(a, scalar); }

inline zplVec3 operator/(zplVec3 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zplVec3 operator*(zplVec3 a, zplVec3 b) { zplVec3 r = {a.x*b.x, a.y*b.y, a.z*b.z}; return r; }
inline zplVec3 operator/(zplVec3 a, zplVec3 b) { zplVec3 r = {a.x/b.x, a.y/b.y, a.z/b.z}; return r; }

inline zplVec3 &operator+=(zplVec3 &a, zplVec3 b)       { return (a = a + b); }
inline zplVec3 &operator-=(zplVec3 &a, zplVec3 b)       { return (a = a - b); }
inline zplVec3 &operator*=(zplVec3 &a, float scalar) { return (a = a * scalar); }
inline zplVec3 &operator/=(zplVec3 &a, float scalar) { return (a = a / scalar); }


inline bool operator==(zplVec4 a, zplVec4 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w); }
inline bool operator!=(zplVec4 a, zplVec4 b) { return !operator==(a, b); }

inline zplVec4 operator+(zplVec4 a) { return a; }
inline zplVec4 operator-(zplVec4 a) { zplVec4 r = {-a.x, -a.y, -a.z, -a.w}; return r; }

inline zplVec4 operator+(zplVec4 a, zplVec4 b) { zplVec4 r; zpl_vec4_add(&r, a, b); return r; }
inline zplVec4 operator-(zplVec4 a, zplVec4 b) { zplVec4 r; zpl_vec4_sub(&r, a, b); return r; }

inline zplVec4 operator*(zplVec4 a, float scalar) { zplVec4 r; zpl_vec4_mul(&r, a, scalar); return r; }
inline zplVec4 operator*(float scalar, zplVec4 a) { return operator*(a, scalar); }

inline zplVec4 operator/(zplVec4 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zplVec4 operator*(zplVec4 a, zplVec4 b) { zplVec4 r = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return r; }
inline zplVec4 operator/(zplVec4 a, zplVec4 b) { zplVec4 r = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return r; }

inline zplVec4 &operator+=(zplVec4 &a, zplVec4 b)       { return (a = a + b); }
inline zplVec4 &operator-=(zplVec4 &a, zplVec4 b)       { return (a = a - b); }
inline zplVec4 &operator*=(zplVec4 &a, float scalar) { return (a = a * scalar); }
inline zplVec4 &operator/=(zplVec4 &a, float scalar) { return (a = a / scalar); }


inline zplMat2 operator+(zplMat2 const &a, zplMat2 const &b) {
    int i, j;
    zplMat2 r = {0};
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++)
            r.e[2*j+i] = a.e[2*j+i] + b.e[2*j+i];
    }
    return r;
}

inline zplMat2 operator-(zplMat2 const &a, zplMat2 const &b) {
    int i, j;
    zplMat2 r = {0};
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++)
            r.e[2*j+i] = a.e[2*j+i] - b.e[2*j+i];
    }
    return r;
}

inline zplMat2 operator*(zplMat2 const &a, zplMat2 const &b) { zplMat2 r; zpl_mat2_mul(&r, (zplMat2 *)&a, (zplMat2 *)&b); return r; }
inline zplVec2 operator*(zplMat2 const &a, zplVec2 v) { zplVec2 r; zpl_mat2_mul_vec2(&r, (zplMat2 *)&a, v); return r; }
inline zplMat2 operator*(zplMat2 const &a, float scalar) {
    zplMat2 r = {0};
    int i;
    for (i = 0; i < 2*2; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zplMat2 operator*(float scalar, zplMat2 const &a) { return operator*(a, scalar); }
inline zplMat2 operator/(zplMat2 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zplMat2& operator+=(zplMat2& a, zplMat2 const &b) { return (a = a + b); }
inline zplMat2& operator-=(zplMat2& a, zplMat2 const &b) { return (a = a - b); }
inline zplMat2& operator*=(zplMat2& a, zplMat2 const &b) { return (a = a * b); }



inline zplMat3 operator+(zplMat3 const &a, zplMat3 const &b) {
    int i, j;
    zplMat3 r = {0};
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++)
            r.e[3*j+i] = a.e[3*j+i] + b.e[3*j+i];
    }
    return r;
}

inline zplMat3 operator-(zplMat3 const &a, zplMat3 const &b) {
    int i, j;
    zplMat3 r = {0};
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++)
            r.e[3*j+i] = a.e[3*j+i] - b.e[3*j+i];
    }
    return r;
}

inline zplMat3 operator*(zplMat3 const &a, zplMat3 const &b) { zplMat3 r; zpl_mat3_mul(&r, (zplMat3 *)&a, (zplMat3 *)&b); return r; }
inline zplVec3 operator*(zplMat3 const &a, zplVec3 v) { zplVec3 r; zpl_mat3_mul_vec3(&r, (zplMat3 *)&a, v); return r; } inline zplMat3 operator*(zplMat3 const &a, float scalar) {
    zplMat3 r = {0};
    int i;
    for (i = 0; i < 3*3; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zplMat3 operator*(float scalar, zplMat3 const &a) { return operator*(a, scalar); }
inline zplMat3 operator/(zplMat3 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zplMat3& operator+=(zplMat3& a, zplMat3 const &b) { return (a = a + b); }
inline zplMat3& operator-=(zplMat3& a, zplMat3 const &b) { return (a = a - b); }
inline zplMat3& operator*=(zplMat3& a, zplMat3 const &b) { return (a = a * b); }



inline zplMat4 operator+(zplMat4 const &a, zplMat4 const &b) {
    int i, j;
    zplMat4 r = {0};
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++)
            r.e[4*j+i] = a.e[4*j+i] + b.e[4*j+i];
    }
    return r;
}

inline zplMat4 operator-(zplMat4 const &a, zplMat4 const &b) {
    int i, j;
    zplMat4 r = {0};
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++)
            r.e[4*j+i] = a.e[4*j+i] - b.e[4*j+i];
    }
    return r;
}

inline zplMat4 operator*(zplMat4 const &a, zplMat4 const &b) { zplMat4 r; zpl_mat4_mul(&r, (zplMat4 *)&a, (zplMat4 *)&b); return r; }
inline zplVec4 operator*(zplMat4 const &a, zplVec4 v) { zplVec4 r; zpl_mat4_mul_vec4(&r, (zplMat4 *)&a, v); return r; }
inline zplMat4 operator*(zplMat4 const &a, float scalar) {
    zplMat4 r = {0};
    int i;
    for (i = 0; i < 4*4; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zplMat4 operator*(float scalar, zplMat4 const &a) { return operator*(a, scalar); }
inline zplMat4 operator/(zplMat4 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zplMat4& operator+=(zplMat4 &a, zplMat4 const &b) { return (a = a + b); }
inline zplMat4& operator-=(zplMat4 &a, zplMat4 const &b) { return (a = a - b); }
inline zplMat4& operator*=(zplMat4 &a, zplMat4 const &b) { return (a = a * b); }



inline bool operator==(zplQuat a, zplQuat b) { return a.xyzw == b.xyzw; }
inline bool operator!=(zplQuat a, zplQuat b) { return !operator==(a, b); }

inline zplQuat operator+(zplQuat q) { return q; }
inline zplQuat operator-(zplQuat q) { return zpl_quat(-q.x, -q.y, -q.z, -q.w); }

inline zplQuat operator+(zplQuat a, zplQuat b) { zplQuat r; zpl_quat_add(&r, a, b); return r; }
inline zplQuat operator-(zplQuat a, zplQuat b) { zplQuat r; zpl_quat_sub(&r, a, b); return r; }

inline zplQuat operator*(zplQuat a, zplQuat b)  { zplQuat r; zpl_quat_mul(&r, a, b); return r; }
inline zplQuat operator*(zplQuat q, float s) { zplQuat r; zpl_quat_mulf(&r, q, s); return r; }
inline zplQuat operator*(float s, zplQuat q) { return operator*(q, s); }
inline zplQuat operator/(zplQuat q, float s) { zplQuat r; zpl_quat_divf(&r, q, s); return r; }

inline zplQuat &operator+=(zplQuat &a, zplQuat b) { zpl_quat_addeq(&a, b); return a; }
inline zplQuat &operator-=(zplQuat &a, zplQuat b) { zpl_quat_subeq(&a, b); return a; }
inline zplQuat &operator*=(zplQuat &a, zplQuat b) { zpl_quat_muleq(&a, b); return a; }
inline zplQuat &operator/=(zplQuat &a, zplQuat b) { zpl_quat_diveq(&a, b); return a; }

inline zplQuat &operator*=(zplQuat &a, float b) { zpl_quat_muleqf(&a, b); return a; }
inline zplQuat &operator/=(zplQuat &a, float b) { zpl_quat_diveqf(&a, b); return a; }

/* Rotate v by a */
inline zplVec3 operator*(zplQuat q, zplVec3 v) { zplVec3 r; zpl_quat_rotate_vec3(&r, q, v); return r; }

#endif




#endif /* ZPL_MATH_INCLUDE_ZPL_MATH_H */

/****************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Implementation
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 ****************************************************************/

#if defined(ZPL_MATH_IMPLEMENTATION) && !defined(ZPL_MATH_IMPLEMENTATION_DONE)
#define ZPL_MATH_IMPLEMENTATION_DONE

#if (defined(__GCC__) || defined(__GNUC__)) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wmissing-braces"
#elif __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif


/* NOTE: To remove the need for memcpy */
static void zpl__memcpy_4byte(void *dest, void const *src, size_t size) {
    size_t i;
    unsigned int *d, *s;
    d = (unsigned int *)dest;
    s = (unsigned int *)src;
    for (i = 0; i < size/4; i++) {
        *d++ = *s++;
    }
}


float zpl_to_radians(float degrees) { return degrees * ZPL_MATH_TAU / 360.0f; }
float zpl_to_degrees(float radians) { return radians * 360.0f / ZPL_MATH_TAU; }

float zpl_angle_diff(float radians_a, float radians_b) {
    float delta = zpl_mod(radians_b-radians_a, ZPL_MATH_TAU);
    delta = zpl_mod(delta + 1.5f*ZPL_MATH_TAU, ZPL_MATH_TAU);
    delta -= 0.5f*ZPL_MATH_TAU;
    return delta;
}

float zpl_copy_sign(float x, float y) {
    int ix, iy;
    ix = *(int *)&x;
    iy = *(int *)&y;
    
    ix &= 0x7fffffff;
    ix |= iy & 0x80000000;
    return *(float *)&ix;
}

float zpl_remainder(float x, float y) {
    return x - (zpl_round(x/y)*y);
}

float zpl_mod(float x, float y) {
    float result;
    y = zpl_abs(y);
    result = zpl_remainder(zpl_abs(x), y);
    if (zpl_sign(result)) result += y;
    return zpl_copy_sign(result, x);
}


float zpl_quake_rsqrt(float a) {
    union {
        int i;
        float f;
    } t;
    float x2;
    float const three_halfs = 1.5f;
    
    x2 = a * 0.5f;
    t.f = a;
    t.i = 0x5f375a86 - (t.i >> 1);                /* What the fuck? */
    t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 1st iteration */
    t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 2nd iteration, this can be removed */
    
    return t.f;
}


#if defined(ZPL_MATH_NO_MATH_H)
#if defined(_MSC_VER)

float zpl_rsqrt(float a) { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(a))); }
float zpl_sqrt(float a)  { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(a))); };
float
zpl_sin(float a)
{
    static float const a0 = +1.91059300966915117e-31f;
    static float const a1 = +1.00086760103908896f;
    static float const a2 = -1.21276126894734565e-2f;
    static float const a3 = -1.38078780785773762e-1f;
    static float const a4 = -2.67353392911981221e-2f;
    static float const a5 = +2.08026600266304389e-2f;
    static float const a6 = -3.03996055049204407e-3f;
    static float const a7 = +1.38235642404333740e-4f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}
float
zpl_cos(float a)
{
    static float const a0 = +1.00238601909309722f;
    static float const a1 = -3.81919947353040024e-2f;
    static float const a2 = -3.94382342128062756e-1f;
    static float const a3 = -1.18134036025221444e-1f;
    static float const a4 = +1.07123798512170878e-1f;
    static float const a5 = -1.86637164165180873e-2f;
    static float const a6 = +9.90140908664079833e-4f;
    static float const a7 = -5.23022132118824778e-14f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}

float
zpl_tan(float radians)
{
    float rr = radians*radians;
    float a = 9.5168091e-03f;
    a *= rr;
    a += 2.900525e-03f;
    a *= rr;
    a += 2.45650893e-02f;
    a *= rr;
    a += 5.33740603e-02f;
    a *= rr;
    a += 1.333923995e-01f;
    a *= rr;
    a += 3.333314036e-01f;
    a *= rr;
    a += 1.0f;
    a *= radians;
    return a;
}

float zpl_arcsin(float a) { return zpl_arctan2(a, zpl_sqrt((1.0f + a) * (1.0f - a))); }
float zpl_arccos(float a) { return zpl_arctan2(zpl_sqrt((1.0f + a) * (1.0 - a)), a); }

float
zpl_arctan(float a)
{
    float u  = a*a;
    float u2 = u*u;
    float u3 = u2*u;
    float u4 = u3*u;
    float f  = 1.0f+0.33288950512027f*u-0.08467922817644f*u2+0.03252232640125f*u3-0.00749305860992f*u4;
    return a/f;
}

float
zpl_arctan2(float y, float x)
{
    if (zpl_abs(x) > zpl_abs(y)) {
        float a = zpl_arctan(y/x);
        if (x > 0.0f)
            return a;
        else
            return y > 0.0f ? a+ZPL_MATH_TAU_OVER_2:a-ZPL_MATH_TAU_OVER_2;
    } else {
        float a = zpl_arctan(x/y);
        if (x > 0.0f)
            return y > 0.0f ? ZPL_MATH_TAU_OVER_4-a:-ZPL_MATH_TAU_OVER_4-a;
        else
            return y > 0.0f ? ZPL_MATH_TAU_OVER_4+a:-ZPL_MATH_TAU_OVER_4+a;
    }
}

float
zpl_exp(float a)
{
    union { float f; int i; } u, v;
    u.i = (int)(6051102 * a + 1056478197);
    v.i = (int)(1056478197 - 6051102 * a);
    return u.f / v.f;
}

float
zpl_log(float a)
{
    union { float f; int i; } u = {a};
    return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}

float
zpl_pow(float a, float b)
{
    int flipped = 0, e;
    float f, r = 1.0f;
    if (b < 0) {
        flipped = 1;
        b = -b;
    }
    
    e = (int)b;
    f = zpl_exp(b - e);
    
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    
    r *= f;
    return flipped ? 1.0f/r : r;
}

#else

float zpl_rsqrt(float a)            { return 1.0f/__builtin_sqrt(a); }
float zpl_sqrt(float a)             { return __builtin_sqrt(a); }
float zpl_sin(float radians)        { return __builtin_sinf(radians); }
float zpl_cos(float radians)        { return __builtin_cosf(radians); }
float zpl_tan(float radians)        { return __builtin_tanf(radians); }
float zpl_arcsin(float a)           { return __builtin_asinf(a); }
float zpl_arccos(float a)           { return __builtin_acosf(a); }
float zpl_arctan(float a)           { return __builtin_atanf(a); }
float zpl_arctan2(float y, float x) { return __builtin_atan2f(y, x); }


float zpl_exp(float x)  { return __builtin_expf(x); }
float zpl_log(float x)  { return __builtin_logf(x); }

// TODO: Should this be zpl_exp(y * zpl_log(x)) ???
float zpl_pow(float x, float y) { return __builtin_powf(x, y); }

#endif

#else
float zpl_rsqrt(float a)            { return 1.0f/sqrtf(a); }
float zpl_sqrt(float a)             { return sqrtf(a); };
float zpl_sin(float radians)        { return sinf(radians); };
float zpl_cos(float radians)        { return cosf(radians); };
float zpl_tan(float radians)        { return tanf(radians); };
float zpl_arcsin(float a)           { return asinf(a); };
float zpl_arccos(float a)           { return acosf(a); };
float zpl_arctan(float a)           { return atanf(a); };
float zpl_arctan2(float y, float x) { return atan2f(y, x); };

float zpl_exp(float x)          { return expf(x); }
float zpl_log(float x)          { return logf(x); }
float zpl_pow(float x, float y) { return powf(x, y); }
#endif

float zpl_exp2(float x) { return zpl_exp(ZPL_MATH_LOG_TWO * x); }
float zpl_log2(float x) { return zpl_log(x) / ZPL_MATH_LOG_TWO; }


float zpl_fast_exp(float x) {
    /* NOTE: Only works in the range -1 <= x <= +1 */
    float e = 1.0f + x*(1.0f + x*0.5f*(1.0f + x*0.3333333333f*(1.0f + x*0.25f*(1.0f + x*0.2f))));
    return e;
}

float zpl_fast_exp2(float x) { return zpl_fast_exp(ZPL_MATH_LOG_TWO * x); }



float zpl_round(float x) { return (float)((x >= 0.0f) ? zpl_floor(x + 0.5f) : zpl_ceil(x - 0.5f)); }
float zpl_floor(float x) { return (float)((x >= 0.0f) ? (int)x : (int)(x-0.9999999999999999f)); }
float zpl_ceil(float x)  { return (float)((x < 0) ? (int)x : ((int)x)+1); }





float zpl_half_to_float(zplHalf value) {
    union { unsigned int i; float f; } result;
    int s = (value >> 15) & 0x001;
    int e = (value >> 10) & 0x01f;
    int m =  value        & 0x3ff;
    
    if (e == 0) {
        if (m == 0) {
            /* Plus or minus zero */
            result.i = (unsigned int)(s << 31);
            return result.f;
        } else {
            /* Denormalized number */
            while (!(m & 0x00000400)) {
                m <<= 1;
                e -=  1;
            }
            
            e += 1;
            m &= ~0x00000400;
        }
    } else if (e == 31) {
        if (m == 0) {
            /* Positive or negative infinity */
            result.i = (unsigned int)((s << 31) | 0x7f800000);
            return result.f;
        } else {
            /* Nan */
            result.i = (unsigned int)((s << 31) | 0x7f800000 | (m << 13));
            return result.f;
        }
    }
    
    e = e + (127 - 15);
    m = m << 13;
    
    result.i = (unsigned int)((s << 31) | (e << 23) | m);
    return result.f;
}

zplHalf zpl_float_to_half(float value) {
    union { unsigned int i; float f; } v;
    int i, s, e, m;
    
    v.f = value;
    i = (int)v.i;
    
    s =  (i >> 16) & 0x00008000;
    e = ((i >> 23) & 0x000000ff) - (127 - 15);
    m =   i        & 0x007fffff;
    
    
    if (e <= 0) {
        if (e < -10) return (zplHalf)s;
        m = (m | 0x00800000) >> (1 - e);
        
        if (m & 0x00001000)
            m += 0x00002000;
        
        return (zplHalf)(s | (m >> 13));
    } else if (e == 0xff - (127 - 15)) {
        if (m == 0) {
            return (zplHalf)(s | 0x7c00); /* NOTE: infinity */
        } else {
            /* NOTE: NAN */
            m >>= 13;
            return (zplHalf)(s | 0x7c00 | m | (m == 0));
        }
    } else {
        if (m & 0x00001000) {
            m += 0x00002000;
            if (m & 0x00800000) {
                m = 0;
                e += 1;
            }
        }
        
        if (e > 30) {
            float volatile f = 1e12f;
            int j;
            for (j = 0; j < 10; j++)
                f *= f; /* NOTE: Cause overflow */
            
            return (zplHalf)(s | 0x7c00);
        }
        
        return (zplHalf)(s | (e << 10) | (m >> 13));
    }
}







#define ZPL_VEC2_2OP(a,c,post)  \
a->x =        c.x post;    \
a->y =        c.y post;

#define ZPL_VEC2_3OP(a,b,op,c,post) \
a->x = b.x op c.x post;        \
a->y = b.y op c.y post;

#define ZPL_VEC3_2OP(a,c,post) \
a->x =        c.x post;   \
a->y =        c.y post;   \
a->z =        c.z post;

#define ZPL_VEC3_3OP(a,b,op,c,post) \
a->x = b.x op c.x post;        \
a->y = b.y op c.y post;        \
a->z = b.z op c.z post;

#define ZPL_VEC4_2OP(a,c,post) \
a->x =        c.x post;   \
a->y =        c.y post;   \
a->z =        c.z post;   \
a->w =        c.w post;

#define ZPL_VEC4_3OP(a,b,op,c,post) \
a->x = b.x op c.x post;        \
a->y = b.y op c.y post;        \
a->z = b.z op c.z post;        \
a->w = b.w op c.w post;


zplVec2 zpl_vec2_zero(void)        { zplVec2 v = {0, 0};                return v; }
zplVec2 zpl_vec2(float x, float y) { zplVec2 v; v.x = x;    v.y = y;    return v; }
zplVec2 zpl_vec2v(float x[2])      { zplVec2 v; v.x = x[0]; v.y = x[1]; return v; }

zplVec3 zpl_vec3_zero(void)                 { zplVec3 v = {0, 0, 0};                         return v; }
zplVec3 zpl_vec3(float x, float y, float z) { zplVec3 v; v.x = x; v.y = y; v.z = z;          return v; }
zplVec3 zpl_vec3v(float x[3])               { zplVec3 v; v.x = x[0]; v.y = x[1]; v.z = x[2]; return v; }

zplVec4 zpl_vec4_zero(void)                          { zplVec4 v = {0, 0, 0, 0};                                  return v; }
zplVec4 zpl_vec4(float x, float y, float z, float w) { zplVec4 v; v.x = x; v.y = y; v.z = z; v.w = w;             return v; }
zplVec4 zpl_vec4v(float x[4])                        { zplVec4 v; v.x = x[0]; v.y = x[1]; v.z = x[2]; v.w = x[3]; return v; }


void zpl_vec2_add(zplVec2 *d, zplVec2 v0, zplVec2 v1) { ZPL_VEC2_3OP(d,v0,+,v1,+0); }
void zpl_vec2_sub(zplVec2 *d, zplVec2 v0, zplVec2 v1) { ZPL_VEC2_3OP(d,v0,-,v1,+0); }
void zpl_vec2_mul(zplVec2 *d, zplVec2 v,  float s)   { ZPL_VEC2_2OP(d,v,* s);      }
void zpl_vec2_div(zplVec2 *d, zplVec2 v,  float s)   { ZPL_VEC2_2OP(d,v,/ s);      }

void zpl_vec3_add(zplVec3 *d, zplVec3 v0, zplVec3 v1) { ZPL_VEC3_3OP(d,v0,+,v1,+0); }
void zpl_vec3_sub(zplVec3 *d, zplVec3 v0, zplVec3 v1) { ZPL_VEC3_3OP(d,v0,-,v1,+0); }
void zpl_vec3_mul(zplVec3 *d, zplVec3 v,  float s)   { ZPL_VEC3_2OP(d,v,* s);      }
void zpl_vec3_div(zplVec3 *d, zplVec3 v,  float s)   { ZPL_VEC3_2OP(d,v,/ s);      }

void zpl_vec4_add(zplVec4 *d, zplVec4 v0, zplVec4 v1) { ZPL_VEC4_3OP(d,v0,+,v1,+0); }
void zpl_vec4_sub(zplVec4 *d, zplVec4 v0, zplVec4 v1) { ZPL_VEC4_3OP(d,v0,-,v1,+0); }
void zpl_vec4_mul(zplVec4 *d, zplVec4 v,  float s)   { ZPL_VEC4_2OP(d,v,* s);      }
void zpl_vec4_div(zplVec4 *d, zplVec4 v,  float s)   { ZPL_VEC4_2OP(d,v,/ s);      }


void zpl_vec2_addeq(zplVec2 *d, zplVec2 v) { ZPL_VEC2_3OP(d,(*d),+,v,+0); }
void zpl_vec2_subeq(zplVec2 *d, zplVec2 v) { ZPL_VEC2_3OP(d,(*d),-,v,+0); }
void zpl_vec2_muleq(zplVec2 *d, float s)  { ZPL_VEC2_2OP(d,(*d),* s);    }
void zpl_vec2_diveq(zplVec2 *d, float s)  { ZPL_VEC2_2OP(d,(*d),/ s);    }

void zpl_vec3_addeq(zplVec3 *d, zplVec3 v) { ZPL_VEC3_3OP(d,(*d),+,v,+0); }
void zpl_vec3_subeq(zplVec3 *d, zplVec3 v) { ZPL_VEC3_3OP(d,(*d),-,v,+0); }
void zpl_vec3_muleq(zplVec3 *d, float s)  { ZPL_VEC3_2OP(d,(*d),* s);    }
void zpl_vec3_diveq(zplVec3 *d, float s)  { ZPL_VEC3_2OP(d,(*d),/ s);    }

void zpl_vec4_addeq(zplVec4 *d, zplVec4 v) { ZPL_VEC4_3OP(d,(*d),+,v,+0); }
void zpl_vec4_subeq(zplVec4 *d, zplVec4 v) { ZPL_VEC4_3OP(d,(*d),-,v,+0); }
void zpl_vec4_muleq(zplVec4 *d, float s)  { ZPL_VEC4_2OP(d,(*d),* s);    }
void zpl_vec4_diveq(zplVec4 *d, float s)  { ZPL_VEC4_2OP(d,(*d),/ s);    }


#undef ZPL_VEC2_2OP
#undef ZPL_VEC2_3OP
#undef ZPL_VEC3_3OP
#undef ZPL_VEC3_2OP
#undef ZPL_VEC4_2OP
#undef ZPL_VEC4_3OP




float zpl_vec2_dot(zplVec2 v0, zplVec2 v1) { return v0.x*v1.x + v0.y*v1.y; }
float zpl_vec3_dot(zplVec3 v0, zplVec3 v1) { return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z; }
float zpl_vec4_dot(zplVec4 v0, zplVec4 v1) { return v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w; }

void zpl_vec2_cross(float *d, zplVec2 v0, zplVec2 v1) { *d = v0.x*v1.y - v1.x*v0.y; }
void zpl_vec3_cross(zplVec3 *d, zplVec3 v0, zplVec3 v1)  { d->x = v0.y*v1.z - v0.z*v1.y;
    d->y = v0.z*v1.x - v0.x*v1.z;
    d->z = v0.x*v1.y - v0.y*v1.x; }

float zpl_vec2_mag2(zplVec2 v) { return zpl_vec2_dot(v, v); }
float zpl_vec3_mag2(zplVec3 v) { return zpl_vec3_dot(v, v); }
float zpl_vec4_mag2(zplVec4 v) { return zpl_vec4_dot(v, v); }

/* TODO: Create custom sqrt function */
float zpl_vec2_mag(zplVec2 v) { return zpl_sqrt(zpl_vec2_dot(v, v)); }
float zpl_vec3_mag(zplVec3 v) { return zpl_sqrt(zpl_vec3_dot(v, v)); }
float zpl_vec4_mag(zplVec4 v) { return zpl_sqrt(zpl_vec4_dot(v, v)); }

void zpl_vec2_norm(zplVec2 *d, zplVec2 v) {
    float inv_mag = zpl_rsqrt(zpl_vec2_dot(v, v));
    zpl_vec2_mul(d, v, inv_mag);
}
void zpl_vec3_norm(zplVec3 *d, zplVec3 v) {
    float mag = zpl_vec3_mag(v);
    zpl_vec3_div(d, v, mag);
}
void zpl_vec4_norm(zplVec4 *d, zplVec4 v) {
    float mag = zpl_vec4_mag(v);
    zpl_vec4_div(d, v, mag);
}

void zpl_vec2_norm0(zplVec2 *d, zplVec2 v) {
    float mag = zpl_vec2_mag(v);
    if (mag > 0)
        zpl_vec2_div(d, v, mag);
    else
        *d = zpl_vec2_zero();
}
void zpl_vec3_norm0(zplVec3 *d, zplVec3 v) {
    float mag = zpl_vec3_mag(v);
    if (mag > 0)
        zpl_vec3_div(d, v, mag);
    else
        *d = zpl_vec3_zero();
}
void zpl_vec4_norm0(zplVec4 *d, zplVec4 v) {
    float mag = zpl_vec4_mag(v);
    if (mag > 0)
        zpl_vec4_div(d, v, mag);
    else
        *d = zpl_vec4_zero();
}


void zpl_vec2_reflect(zplVec2 *d, zplVec2 i, zplVec2 n) {
    zplVec2 b = n;
    zpl_vec2_muleq(&b, 2.0f*zpl_vec2_dot(n, i));
    zpl_vec2_sub(d, i, b);
}

void zpl_vec3_reflect(zplVec3 *d, zplVec3 i, zplVec3 n) {
    zplVec3 b = n;
    zpl_vec3_muleq(&b, 2.0f*zpl_vec3_dot(n, i));
    zpl_vec3_sub(d, i, b);
}

void zpl_vec2_refract(zplVec2 *d, zplVec2 i, zplVec2 n, float eta) {
    zplVec2 a, b;
    float dv, k;
    
    dv = zpl_vec2_dot(n, i);
    k = 1.0f - eta*eta * (1.0f - dv*dv);
    zpl_vec2_mul(&a, i, eta);
    zpl_vec2_mul(&b, n, eta*dv*zpl_sqrt(k));
    zpl_vec2_sub(d, a, b);
    zpl_vec2_muleq(d, (float)(k >= 0.0f));
}

void zpl_vec3_refract(zplVec3 *d, zplVec3 i, zplVec3 n, float eta) {
    zplVec3 a, b;
    float dv, k;
    
    dv = zpl_vec3_dot(n, i);
    k = 1.0f - eta*eta * (1.0f - dv*dv);
    zpl_vec3_mul(&a, i, eta);
    zpl_vec3_mul(&b, n, eta*dv*zpl_sqrt(k));
    zpl_vec3_sub(d, a, b);
    zpl_vec3_muleq(d, (float)(k >= 0.0f));
}





float zpl_vec2_aspect_ratio(zplVec2 v) { return (v.y < 0.0001f) ? 0.0f : v.x/v.y; }





void zpl_mat2_transpose(zplMat2 *m) { zpl_float22_transpose(zpl_float22_m(m)); }
void zpl_mat2_identity(zplMat2 *m)  { zpl_float22_identity(zpl_float22_m(m));  }
void zpl_mat2_mul(zplMat2 *out, zplMat2 *m1, zplMat2 *m2) { zpl_float22_mul(zpl_float22_m(out), zpl_float22_m(m1), zpl_float22_m(m2)); }

void zpl_float22_identity(float m[2][2]) {
    m[0][0] = 1; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = 1;
}

void zpl_mat2_mul_vec2(zplVec2 *out, zplMat2 *m, zplVec2 in) { zpl_float22_mul_vec2(out, zpl_float22_m(m), in); }

zplMat2 *zpl_mat2_v(zplVec2 m[2])   { return (zplMat2 *)m; }
zplMat2 *zpl_mat2_f(float m[2][2]) { return (zplMat2 *)m; }

zplFloat2 *zpl_float22_m(zplMat2 *m)   { return (zplFloat2 *)m; }
zplFloat2 *zpl_float22_v(zplVec2 m[2]) { return (zplFloat2 *)m; }
zplFloat2 *zpl_float22_4(float m[4])  { return (zplFloat2 *)m; }

void zpl_float22_transpose(float (*vec)[2]) {
    int i, j;
    for (j = 0; j < 2; j++) {
        for (i = j + 1; i < 2; i++) {
            float t = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = t;
        }
    }
}



void zpl_float22_mul(float (*out)[2], float (*mat1)[2], float (*mat2)[2]) {
    int i, j;
    float temp1[2][2], temp2[2][2];
    if (mat1 == out) { zpl__memcpy_4byte(temp1, mat1, sizeof(temp1)); mat1 = temp1; }
    if (mat2 == out) { zpl__memcpy_4byte(temp2, mat2, sizeof(temp2)); mat2 = temp2; }
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++) {
            out[j][i] = mat1[0][i]*mat2[j][0]
                + mat1[1][i]*mat2[j][1];
        }
    }
}

void zpl_float22_mul_vec2(zplVec2 *out, float m[2][2], zplVec2 v) {
    out->x = m[0][0]*v.x + m[0][1]*v.y;
    out->y = m[1][0]*v.x + m[1][1]*v.y;
}

float zpl_mat2_determinate(zplMat2 *m) {
    zplFloat2 *e = zpl_float22_m(m);
    return e[0][0]*e[1][1] - e[1][0]*e[0][1];
}

void zpl_mat2_inverse(zplMat2 *out, zplMat2 *in) {
    zplFloat2 *o = zpl_float22_m(out);
    zplFloat2 *i = zpl_float22_m(in);
    
    float ood = 1.0f / zpl_mat2_determinate(in);
    
    o[0][0] = +i[1][1] * ood;
    o[0][1] = -i[0][1] * ood;
    o[1][0] = -i[1][0] * ood;
    o[1][1] = +i[0][0] * ood;
}






void zpl_mat3_transpose(zplMat3 *m) { zpl_float33_transpose(zpl_float33_m(m)); }
void zpl_mat3_identity(zplMat3 *m)  { zpl_float33_identity(zpl_float33_m(m));  }
void zpl_mat3_mul(zplMat3 *out, zplMat3 *m1, zplMat3 *m2) { zpl_float33_mul(zpl_float33_m(out), zpl_float33_m(m1), zpl_float33_m(m2)); }

void zpl_float33_identity(float m[3][3]) {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
}

void zpl_mat3_mul_vec3(zplVec3 *out, zplMat3 *m, zplVec3 in) { zpl_float33_mul_vec3(out, zpl_float33_m(m), in); }

zplMat3 *zpl_mat3_v(zplVec3 m[3])   { return (zplMat3 *)m; }
zplMat3 *zpl_mat3_f(float m[3][3]) { return (zplMat3 *)m; }

zplFloat3 *zpl_float33_m(zplMat3 *m)   { return (zplFloat3 *)m; }
zplFloat3 *zpl_float33_v(zplVec3 m[3]) { return (zplFloat3 *)m; }
zplFloat3 *zpl_float33_16(float m[9]) { return (zplFloat3 *)m; }

void zpl_float33_transpose(float (*vec)[3]) {
    int i, j;
    for (j = 0; j < 3; j++) {
        for (i = j + 1; i < 3; i++) {
            float t = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = t;
        }
    }
}

void zpl_float33_mul(float (*out)[3], float (*mat1)[3], float (*mat2)[3]) {
    int i, j;
    float temp1[3][3], temp2[3][3];
    if (mat1 == out) { zpl__memcpy_4byte(temp1, mat1, sizeof(temp1)); mat1 = temp1; }
    if (mat2 == out) { zpl__memcpy_4byte(temp2, mat2, sizeof(temp2)); mat2 = temp2; }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            out[j][i] = mat1[0][i]*mat2[j][0]
                + mat1[1][i]*mat2[j][1]
                + mat1[2][i]*mat2[j][2];
        }
    }
}

void zpl_float33_mul_vec3(zplVec3 *out, float m[3][3], zplVec3 v) {
    out->x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z;
    out->y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z;
    out->z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z;
}



float zpl_mat3_determinate(zplMat3 *m) {
    zplFloat3 *e = zpl_float33_m(m);
    float d = +e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1])
        -e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0])
        +e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
    return d;
}

void zpl_mat3_inverse(zplMat3 *out, zplMat3 *in) {
    zplFloat3 *o = zpl_float33_m(out);
    zplFloat3 *i = zpl_float33_m(in);
    
    float ood = 1.0f / zpl_mat3_determinate(in);
    
    o[0][0] = +(i[1][1] * i[2][2] - i[2][1] * i[1][2]) * ood;
    o[0][1] = -(i[1][0] * i[2][2] - i[2][0] * i[1][2]) * ood;
    o[0][2] = +(i[1][0] * i[2][1] - i[2][0] * i[1][1]) * ood;
    o[1][0] = -(i[0][1] * i[2][2] - i[2][1] * i[0][2]) * ood;
    o[1][1] = +(i[0][0] * i[2][2] - i[2][0] * i[0][2]) * ood;
    o[1][2] = -(i[0][0] * i[2][1] - i[2][0] * i[0][1]) * ood;
    o[2][0] = +(i[0][1] * i[1][2] - i[1][1] * i[0][2]) * ood;
    o[2][1] = -(i[0][0] * i[1][2] - i[1][0] * i[0][2]) * ood;
    o[2][2] = +(i[0][0] * i[1][1] - i[1][0] * i[0][1]) * ood;
}











void zpl_mat4_transpose(zplMat4 *m) { zpl_float44_transpose(zpl_float44_m(m)); }
void zpl_mat4_identity(zplMat4 *m)  { zpl_float44_identity(zpl_float44_m(m));  }
void zpl_mat4_mul(zplMat4 *out, zplMat4 *m1, zplMat4 *m2) { zpl_float44_mul(zpl_float44_m(out), zpl_float44_m(m1), zpl_float44_m(m2)); }

void zpl_float44_identity(float m[4][4]) {
    m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

void zpl_mat4_mul_vec4(zplVec4 *out, zplMat4 *m, zplVec4 in) {
    zpl_float44_mul_vec4(out, zpl_float44_m(m), in);
}

zplMat4 *zpl_mat4_v(zplVec4 m[4])   { return (zplMat4 *)m; }
zplMat4 *zpl_mat4_f(float m[4][4]) { return (zplMat4 *)m; }

zplFloat4 *zpl_float44_m(zplMat4 *m)    { return (zplFloat4 *)m; }
zplFloat4 *zpl_float44_v(zplVec4 m[4])  { return (zplFloat4 *)m; }
zplFloat4 *zpl_float44_16(float m[16]) { return (zplFloat4 *)m; }

void zpl_float44_transpose(float (*vec)[4]) {
    float tmp;
    tmp = vec[1][0]; vec[1][0] = vec[0][1]; vec[0][1] = tmp;
    tmp = vec[2][0]; vec[2][0] = vec[0][2]; vec[0][2] = tmp;
    tmp = vec[3][0]; vec[3][0] = vec[0][3]; vec[0][3] = tmp;
    tmp = vec[2][1]; vec[2][1] = vec[1][2]; vec[1][2] = tmp;
    tmp = vec[3][1]; vec[3][1] = vec[1][3]; vec[1][3] = tmp;
    tmp = vec[3][2]; vec[3][2] = vec[2][3]; vec[2][3] = tmp;
}

void zpl_float44_mul(float (*out)[4], float (*mat1)[4], float (*mat2)[4]) {
    int i, j;
    float temp1[4][4], temp2[4][4];
    if (mat1 == out) { zpl__memcpy_4byte(temp1, mat1, sizeof(temp1)); mat1 = temp1; }
    if (mat2 == out) { zpl__memcpy_4byte(temp2, mat2, sizeof(temp2)); mat2 = temp2; }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            out[j][i] = mat1[0][i]*mat2[j][0]
                + mat1[1][i]*mat2[j][1]
                + mat1[2][i]*mat2[j][2]
                + mat1[3][i]*mat2[j][3];
        }
    }
}

void zpl_float44_mul_vec4(zplVec4 *out, float m[4][4], zplVec4 v) {
    out->x = m[0][0]*v.x + m[1][0]*v.y + m[2][0]*v.z + m[3][0]*v.w;
    out->y = m[0][1]*v.x + m[1][1]*v.y + m[2][1]*v.z + m[3][1]*v.w;
    out->z = m[0][2]*v.x + m[1][2]*v.y + m[2][2]*v.z + m[3][2]*v.w;
    out->w = m[0][3]*v.x + m[1][3]*v.y + m[2][3]*v.z + m[3][3]*v.w;
}

void zpl_mat4_inverse(zplMat4 *out, zplMat4 *in) {
    zplFloat4 *o = zpl_float44_m(out);
    zplFloat4 *m = zpl_float44_m(in);
    
    float ood;
    //float tmp;
    
    float sf00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    float sf01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    float sf02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    float sf03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    float sf04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    float sf05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    float sf06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    float sf07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    float sf08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    float sf09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    float sf10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    float sf11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    float sf12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    float sf13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    float sf14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    float sf15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    float sf16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
    float sf17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    float sf18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
    
    o[0][0] = +(m[1][1] * sf00 - m[1][2] * sf01 + m[1][3] * sf02);
    o[1][0] = -(m[1][0] * sf00 - m[1][2] * sf03 + m[1][3] * sf04);
    o[2][0] = +(m[1][0] * sf01 - m[1][1] * sf03 + m[1][3] * sf05);
    o[3][0] = -(m[1][0] * sf02 - m[1][1] * sf04 + m[1][2] * sf05);
    
    o[0][1] = -(m[0][1] * sf00 - m[0][2] * sf01 + m[0][3] * sf02);
    o[1][1] = +(m[0][0] * sf00 - m[0][2] * sf03 + m[0][3] * sf04);
    o[2][1] = -(m[0][0] * sf01 - m[0][1] * sf03 + m[0][3] * sf05);
    o[3][1] = +(m[0][0] * sf02 - m[0][1] * sf04 + m[0][2] * sf05);
    
    o[0][2] = +(m[0][1] * sf06 - m[0][2] * sf07 + m[0][3] * sf08);
    o[1][2] = -(m[0][0] * sf06 - m[0][2] * sf09 + m[0][3] * sf10);
    o[2][2] = +(m[0][0] * sf11 - m[0][1] * sf09 + m[0][3] * sf12);
    o[3][2] = -(m[0][0] * sf08 - m[0][1] * sf10 + m[0][2] * sf12);
    
    o[0][3] = -(m[0][1] * sf13 - m[0][2] * sf14 + m[0][3] * sf15);
    o[1][3] = +(m[0][0] * sf13 - m[0][2] * sf16 + m[0][3] * sf17);
    o[2][3] = -(m[0][0] * sf14 - m[0][1] * sf16 + m[0][3] * sf18);
    o[3][3] = +(m[0][0] * sf15 - m[0][1] * sf17 + m[0][2] * sf18);
    
    ood = 1.0f / (m[0][0] * o[0][0] +
                  m[0][1] * o[1][0] +
                  m[0][2] * o[2][0] +
                  m[0][3] * o[3][0]);
    
    o[0][0] *= ood;
    o[0][1] *= ood;
    o[0][2] *= ood;
    o[0][3] *= ood;
    o[1][0] *= ood;
    o[1][1] *= ood;
    o[1][2] *= ood;
    o[1][3] *= ood;
    o[2][0] *= ood;
    o[2][1] *= ood;
    o[2][2] *= ood;
    o[2][3] *= ood;
    o[3][0] *= ood;
    o[3][1] *= ood;
    o[3][2] *= ood;
    o[3][3] *= ood;
}







void zpl_mat4_translate(zplMat4 *out, zplVec3 v) {
    zpl_mat4_identity(out);
    out->col[3].xyz = v;
    out->col[3].w  = 1;
}

void zpl_mat4_rotate(zplMat4 *out, zplVec3 v, float angle_radians) {
    float c, s;
    zplVec3 axis, t;
    zplFloat4 *rot;
    
    c = zpl_cos(angle_radians);
    s = zpl_sin(angle_radians);
    
    zpl_vec3_norm(&axis, v);
    zpl_vec3_mul(&t, axis, 1.0f-c);
    
    zpl_mat4_identity(out);
    rot = zpl_float44_m(out);
    
    rot[0][0] = c + t.x*axis.x;
    rot[0][1] = 0 + t.x*axis.y + s*axis.z;
    rot[0][2] = 0 + t.x*axis.z - s*axis.y;
    rot[0][3] = 0;
    
    rot[1][0] = 0 + t.y*axis.x - s*axis.z;
    rot[1][1] = c + t.y*axis.y;
    rot[1][2] = 0 + t.y*axis.z + s*axis.x;
    rot[1][3] = 0;
    
    rot[2][0] = 0 + t.z*axis.x + s*axis.y;
    rot[2][1] = 0 + t.z*axis.y - s*axis.x;
    rot[2][2] = c + t.z*axis.z;
    rot[2][3] = 0;
}

void zpl_mat4_scale(zplMat4 *out, zplVec3 v) {
    zpl_mat4_identity(out);
    out->e[0]  = v.x;
    out->e[5]  = v.y;
    out->e[10] = v.z;
}

void zpl_mat4_scalef(zplMat4 *out, float s) {
    zpl_mat4_identity(out);
    out->e[0]  = s;
    out->e[5]  = s;
    out->e[10] = s;
}


void zpl_mat4_ortho2d(zplMat4 *out, float left, float right, float bottom, float top) {
    zplFloat4 *m;
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = 2.0f / (right - left);
    m[1][1] = 2.0f / (top - bottom);
    m[2][2] = -1.0f;
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
}

void zpl_mat4_ortho3d(zplMat4 *out, float left, float right, float bottom, float top, float z_near, float z_far) {
    zplFloat4 *m;
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = +2.0f / (right - left);
    m[1][1] = +2.0f / (top - bottom);
    m[2][2] = -2.0f / (z_far - z_near);
    m[3][0] = -(right + left)   / (right - left);
    m[3][1] = -(top   + bottom) / (top   - bottom);
    m[3][2] = -(z_far + z_near) / (z_far - z_near);
}


void zpl_mat4_perspective(zplMat4 *out, float fovy, float aspect, float z_near, float z_far) {
    float tan_half_fovy = zpl_tan(0.5f * fovy);
    zplMat4 zero_mat = {0};
    zplFloat4 *m = zpl_float44_m(out);
    *out = zero_mat;
    
    m[0][0] = 1.0f / (aspect*tan_half_fovy);
    m[1][1] = 1.0f / (tan_half_fovy);
    m[2][2] = -(z_far + z_near) / (z_far - z_near);
    m[2][3] = -1.0f;
    m[3][2] = -2.0f*z_far*z_near / (z_far - z_near);
}

void zpl_mat4_infinite_perspective(zplMat4 *out, float fovy, float aspect, float z_near) {
    float range  = zpl_tan(0.5f * fovy) * z_near;
    float left   = -range * aspect;
    float right  =  range * aspect;
    float bottom = -range;
    float top    =  range;
    zplMat4 zero_mat = {0};
    zplFloat4 *m = zpl_float44_m(out);
    *out = zero_mat;
    
    m[0][0] = (2.0f*z_near) / (right - left);
    m[1][1] = (2.0f*z_near) / (top   - bottom);
    m[2][2] = -1.0f;
    m[2][3] = -1.0f;
    m[3][2] = -2.0f*z_near;
}

void zpl_mat4_look_at(zplMat4 *out, zplVec3 eye, zplVec3 centre, zplVec3 up) {
    zplVec3 f, s, u;
    zplFloat4 *m;
    
    zpl_vec3_sub(&f, centre, eye);
    zpl_vec3_norm(&f, f);
    
    zpl_vec3_cross(&s, f, up);
    zpl_vec3_norm(&s, s);
    
    zpl_vec3_cross(&u, s, f);
    
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = +s.x;
    m[1][0] = +s.y;
    m[2][0] = +s.z;
    
    m[0][1] = +u.x;
    m[1][1] = +u.y;
    m[2][1] = +u.z;
    
    m[0][2] = -f.x;
    m[1][2] = -f.y;
    m[2][2] = -f.z;
    
    m[3][0] = zpl_vec3_dot(s, eye);
    m[3][1] = zpl_vec3_dot(u, eye);
    m[3][2] = zpl_vec3_dot(f, eye);
}












zplQuat zpl_quat(float x, float y, float z, float w) { zplQuat q; q.x = x; q.y = y; q.z = z; q.w = w; return q; }
zplQuat zpl_quatv(float e[4]) { zplQuat q; q.x = e[0]; q.y = e[1]; q.z = e[2]; q.w = e[3]; return q; }

zplQuat zpl_quat_axis_angle(zplVec3 axis, float angle_radians) {
    zplQuat q;
    zpl_vec3_norm(&q.xyz, axis);
    zpl_vec3_muleq(&q.xyz, zpl_sin(0.5f*angle_radians));
    q.w = zpl_cos(0.5f*angle_radians);
    return q;
}

zplQuat zpl_quat_euler_angles(float pitch, float yaw, float roll) {
    /* TODO: Do without multiplication, i.e. make it faster */
    zplQuat q, p, y, r;
    p = zpl_quat_axis_angle(zpl_vec3(1, 0, 0), pitch);
    y = zpl_quat_axis_angle(zpl_vec3(0, 1, 0), yaw);
    r = zpl_quat_axis_angle(zpl_vec3(0, 0, 1), roll);
    
    zpl_quat_mul(&q, y, p);
    zpl_quat_muleq(&q, r);
    
    return q;
}

zplQuat zpl_quat_identity(void) { zplQuat q = {0, 0, 0, 1}; return q; }


void zpl_quat_add(zplQuat *d, zplQuat q0, zplQuat q1) { zpl_vec4_add(&d->xyzw, q0.xyzw, q1.xyzw); }
void zpl_quat_sub(zplQuat *d, zplQuat q0, zplQuat q1) { zpl_vec4_sub(&d->xyzw, q0.xyzw, q1.xyzw); }

void zpl_quat_mul(zplQuat *d, zplQuat q0, zplQuat q1) {
    d->x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
    d->y = q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x;
    d->z = q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w;
    d->w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
}

void zpl_quat_div(zplQuat *d, zplQuat q0, zplQuat q1){ zplQuat iq1; zpl_quat_inverse(&iq1, q1); zpl_quat_mul(d, q0, iq1); }

void zpl_quat_mulf(zplQuat *d, zplQuat q0, float s) { zpl_vec4_mul(&d->xyzw, q0.xyzw, s); }
void zpl_quat_divf(zplQuat *d, zplQuat q0, float s) { zpl_vec4_div(&d->xyzw, q0.xyzw, s); }


void zpl_quat_addeq(zplQuat *d, zplQuat q) { zpl_vec4_addeq(&d->xyzw, q.xyzw); }
void zpl_quat_subeq(zplQuat *d, zplQuat q) { zpl_vec4_subeq(&d->xyzw, q.xyzw); }
void zpl_quat_muleq(zplQuat *d, zplQuat q) { zpl_quat_mul(d, *d, q); }
void zpl_quat_diveq(zplQuat *d, zplQuat q) { zpl_quat_div(d, *d, q); }


void zpl_quat_muleqf(zplQuat *d, float s) { zpl_vec4_muleq(&d->xyzw, s); }
void zpl_quat_diveqf(zplQuat *d, float s) { zpl_vec4_diveq(&d->xyzw, s); }

float zpl_quat_dot(zplQuat q0, zplQuat q1) { float r = zpl_vec3_dot(q0.xyz, q1.xyz) + q0.w*q1.w; return r; }
float zpl_quat_mag(zplQuat q)           { float r = zpl_sqrt(zpl_quat_dot(q, q)); return r; }

void zpl_quat_norm(zplQuat *d, zplQuat q)    { zpl_quat_divf(d, q, zpl_quat_mag(q)); }
void zpl_quat_conj(zplQuat *d, zplQuat q)    { d->xyz = zpl_vec3(-q.x, -q.y, -q.z); d->w = q.w; }
void zpl_quat_inverse(zplQuat *d, zplQuat q) { zpl_quat_conj(d, q); zpl_quat_diveqf(d, zpl_quat_dot(q, q)); }


void zpl_quat_axis(zplVec3 *axis, zplQuat q) {
    zplQuat n; zpl_quat_norm(&n, q);
    zpl_vec3_div(axis, n.xyz, zpl_sin(zpl_arccos(q.w)));
}

float zpl_quat_angle(zplQuat q) {
    float mag = zpl_quat_mag(q);
    float c = q.w * (1.0f/mag);
    float angle = 2.0f*zpl_arccos(c);
    return angle;
}


float zpl_quat_roll(zplQuat q)  { return zpl_arctan2(2.0f*q.x*q.y + q.z*q.w, q.x*q.x + q.w*q.w - q.y*q.y - q.z*q.z); }
float zpl_quat_pitch(zplQuat q) { return zpl_arctan2(2.0f*q.y*q.z + q.w*q.x, q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z); }
float zpl_quat_yaw(zplQuat q)   { return zpl_arcsin(-2.0f*(q.x*q.z - q.w*q.y)); }

void zpl_quat_rotate_vec3(zplVec3 *d, zplQuat q, zplVec3 v) {
    /* zplVec3 t = 2.0f * cross(q.xyz, v);
     * *d = q.w*t + v + cross(q.xyz, t);
     */
    zplVec3 t, p;
    zpl_vec3_cross(&t, q.xyz, v);
    zpl_vec3_muleq(&t, 2.0f);
    
    zpl_vec3_cross(&p, q.xyz, t);
    
    zpl_vec3_mul(d, t, q.w);
    zpl_vec3_addeq(d, v);
    zpl_vec3_addeq(d, p);
}


void zpl_mat4_from_quat(zplMat4 *out, zplQuat q) {
    zplFloat4 *m;
    zplQuat a;
    float xx, yy, zz,
    xy, xz, yz,
    wx, wy, wz;
    
    zpl_quat_norm(&a, q);
    xx = a.x*a.x; yy = a.y*a.y; zz = a.z*a.z;
    xy = a.x*a.y; xz = a.x*a.z; yz = a.y*a.z;
    wx = a.w*a.x; wy = a.w*a.y; wz = a.w*a.z;
    
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = 1.0f - 2.0f*(yy + zz);
    m[0][1] =        2.0f*(xy + wz);
    m[0][2] =        2.0f*(xz - wy);
    
    m[1][0] =        2.0f*(xy - wz);
    m[1][1] = 1.0f - 2.0f*(xx + zz);
    m[1][2] =        2.0f*(yz + wx);
    
    m[2][0] =        2.0f*(xz + wy);
    m[2][1] =        2.0f*(yz - wx);
    m[2][2] = 1.0f - 2.0f*(xx + yy);
}

void zpl_quat_from_mat4(zplQuat *out, zplMat4 *mat) {
    zplFloat4 *m;
    float four_x_squared_minus_1, four_y_squared_minus_1,
    four_z_squared_minus_1, four_w_squared_minus_1,
    four_biggest_squared_minus_1;
    int biggest_index = 0;
    float biggest_value, mult;
    
    m = zpl_float44_m(mat);
    
    four_x_squared_minus_1 = m[0][0] - m[1][1] - m[2][2];
    four_y_squared_minus_1 = m[1][1] - m[0][0] - m[2][2];
    four_z_squared_minus_1 = m[2][2] - m[0][0] - m[1][1];
    four_w_squared_minus_1 = m[0][0] + m[1][1] + m[2][2];
    
    four_biggest_squared_minus_1 = four_w_squared_minus_1;
    if (four_x_squared_minus_1 > four_biggest_squared_minus_1) {
        four_biggest_squared_minus_1 = four_x_squared_minus_1;
        biggest_index = 1;
    }
    if (four_y_squared_minus_1 > four_biggest_squared_minus_1) {
        four_biggest_squared_minus_1 = four_y_squared_minus_1;
        biggest_index = 2;
    }
    if (four_z_squared_minus_1 > four_biggest_squared_minus_1) {
        four_biggest_squared_minus_1 = four_z_squared_minus_1;
        biggest_index = 3;
    }
    
    biggest_value = zpl_sqrt(four_biggest_squared_minus_1 + 1.0f) * 0.5f;
    mult = 0.25f / biggest_value;
    
    switch (biggest_index) {
        case 0:
        out->w = biggest_value;
        out->x = (m[1][2] - m[2][1]) * mult;
        out->y = (m[2][0] - m[0][2]) * mult;
        out->z = (m[0][1] - m[1][0]) * mult;
        break;
        case 1:
        out->w = (m[1][2] - m[2][1]) * mult;
        out->x = biggest_value;
        out->y = (m[0][1] + m[1][0]) * mult;
        out->z = (m[2][0] + m[0][2]) * mult;
        break;
        case 2:
        out->w = (m[2][0] - m[0][2]) * mult;
        out->x = (m[0][1] + m[1][0]) * mult;
        out->y = biggest_value;
        out->z = (m[1][2] + m[2][1]) * mult;
        break;
        case 3:
        out->w = (m[0][1] - m[1][0]) * mult;
        out->x = (m[2][0] + m[0][2]) * mult;
        out->y = (m[1][2] + m[2][1]) * mult;
        out->z = biggest_value;
        break;
        default:
        /* NOTE: This shouldn't fucking happen!!! */
        break;
    }
    
}






float zpl_lerp         (float a, float b, float t) { return a*(1.0f-t) + b*t; }
float zpl_unlerp       (float t, float a, float b) { return (t-a)/(b-a); }
float zpl_smooth_step  (float a, float b, float t) { float x = (t - a)/(b - a); return x*x*(3.0f - 2.0f*x); }
float zpl_smoother_step(float a, float b, float t) { float x = (t - a)/(b - a); return x*x*x*(x*(6.0f*x - 15.0f) + 10.0f); }


#define ZPL_VEC_LERPN(N, d, a, b, t) \
zplVec##N db; \
zpl_vec##N##_sub(&db, b, a); \
zpl_vec##N##_muleq(&db, t); \
zpl_vec##N##_add(d, a, db)
void zpl_vec2_lerp(zplVec2 *d, zplVec2 a, zplVec2 b, float t) { ZPL_VEC_LERPN(2, d, a, b, t); }
void zpl_vec3_lerp(zplVec3 *d, zplVec3 a, zplVec3 b, float t) { ZPL_VEC_LERPN(3, d, a, b, t); }
void zpl_vec4_lerp(zplVec4 *d, zplVec4 a, zplVec4 b, float t) { ZPL_VEC_LERPN(4, d, a, b, t); }

#undef ZPL_VEC_LERPN

void zpl_quat_lerp(zplQuat *d, zplQuat a, zplQuat b, float t)  { zpl_vec4_lerp(&d->xyzw, a.xyzw, b.xyzw, t); }
void zpl_quat_nlerp(zplQuat *d, zplQuat a, zplQuat b, float t) { zpl_quat_lerp(d, a, b, t); zpl_quat_norm(d, *d); }

void zpl_quat_slerp(zplQuat *d, zplQuat a, zplQuat b, float t) {
    zplQuat x, y, z;
    float cos_theta, angle;
    float s1, s0, is;
    
    z = b;
    cos_theta = zpl_quat_dot(a, b);
    
    if (cos_theta < 0.0f) {
        z = zpl_quat(-b.x, -b.y, -b.z, -b.w);
        cos_theta = -cos_theta;
    }
    
    if (cos_theta > 1.0f) {
        /* NOTE: Use lerp not nlerp as it's not a real angle or they are not normalized */
        zpl_quat_lerp(d, a, b, t);
    }
    
    angle = zpl_arccos(cos_theta);
    
    s1 = zpl_sin(1.0f - t*angle);
    s0 = zpl_sin(t*angle);
    is = 1.0f/zpl_sin(angle);
    zpl_quat_mulf(&x, z, s1);
    zpl_quat_mulf(&y, z, s0);
    zpl_quat_add(d, x, y);
    zpl_quat_muleqf(d, is);
}

void zpl_quat_slerp_approx(zplQuat *d, zplQuat a, zplQuat b, float t) {
    /* NOTE: Derived by taylor expanding the geometric interpolation equation
     *             Even works okay for nearly anti-parallel versors!!!
     */
    /* NOTE: Extra interations cannot be used as they require angle^4 which is not worth it to approximate */
    float tp = t + (1.0f - zpl_quat_dot(a, b))/3.0f * t*(-2.0f*t*t + 3.0f*t - 1.0f);
    zpl_quat_nlerp(d, a, b, tp);
}

void zpl_quat_nquad(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t) {
    zplQuat x, y;
    zpl_quat_nlerp(&x, p, q, t);
    zpl_quat_nlerp(&y, a, b, t);
    zpl_quat_nlerp(d, x, y, 2.0f*t*(1.0f-t));
}

void zpl_quat_squad(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t) {
    zplQuat x, y;
    zpl_quat_slerp(&x, p, q, t);
    zpl_quat_slerp(&y, a, b, t);
    zpl_quat_slerp(d, x, y, 2.0f*t*(1.0f-t));
}

void zpl_quat_squad_approx(zplQuat *d, zplQuat p, zplQuat a, zplQuat b, zplQuat q, float t) {
    zplQuat x, y;
    zpl_quat_slerp_approx(&x, p, q, t);
    zpl_quat_slerp_approx(&y, a, b, t);
    zpl_quat_slerp_approx(d, x, y, 2.0f*t*(1.0f-t));
}






zplRect2 zpl_rect2(zplVec2 pos, zplVec2 dim) {
    zplRect2 r;
    r.pos = pos;
    r.dim = dim;
    return r;
}

zplRect3 zpl_rect3(zplVec3 pos, zplVec3 dim) {
    zplRect3 r;
    r.pos = pos;
    r.dim = dim;
    return r;
}

int zpl_rect2_contains(zplRect2 a, float x, float y) {
    float min_x = zpl_min(a.pos.x, a.pos.x+a.dim.x);
    float max_x = zpl_max(a.pos.x, a.pos.x+a.dim.x);
    float min_y = zpl_min(a.pos.y, a.pos.y+a.dim.y);
    float max_y = zpl_max(a.pos.y, a.pos.y+a.dim.y);
    int result = (x >= min_x) & (x < max_x) & (y >= min_y) & (y < max_y);
    return result;
}

int zpl_rect2_contains_vec2(zplRect2 a, zplVec2 p) { return zpl_rect2_contains(a, p.x, p.y); }

int zpl_rect2_intersects(zplRect2 a, zplRect2 b) {
    zplRect2 r = {0};
    return zpl_rect2_intersection_result(a, b, &r);
}

int zpl_rect2_intersection_result(zplRect2 a, zplRect2 b, zplRect2 *intersection) {
    float a_min_x = zpl_min(a.pos.x, a.pos.x+a.dim.x);
    float a_max_x = zpl_max(a.pos.x, a.pos.x+a.dim.x);
    float a_min_y = zpl_min(a.pos.y, a.pos.y+a.dim.y);
    float a_max_y = zpl_max(a.pos.y, a.pos.y+a.dim.y);
    
    float b_min_x = zpl_min(b.pos.x, b.pos.x+b.dim.x);
    float b_max_x = zpl_max(b.pos.x, b.pos.x+b.dim.x);
    float b_min_y = zpl_min(b.pos.y, b.pos.y+b.dim.y);
    float b_max_y = zpl_max(b.pos.y, b.pos.y+b.dim.y);
    
    float x0 = zpl_max(a_min_x, b_min_x);
    float y0 = zpl_max(a_min_y, b_min_y);
    float x1 = zpl_min(a_max_x, b_max_x);
    float y1 = zpl_min(a_max_y, b_max_y);
    
    if ((x0 < x1) && (y0 < y1)) {
        zplRect2 r = zpl_rect2(zpl_vec2(x0, y0), zpl_vec2(x1-x0, y1-y0));
        *intersection = r;
        return 1;
    } else {
        zplRect2 r = {0};
        *intersection = r;
        return 0;
    }
}


#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
zpl_math_u64 zpl_hash_murmur64(void const *key, size_t num_bytes, zpl_math_u64 seed) {
    zpl_math_u64 const m = 0xc6a4a7935bd1e995ULL;
    zpl_math_u64 const r = 47;
    
    zpl_math_u64 h = seed ^ (num_bytes * m);
    
    zpl_math_u64 *data = (zpl_math_u64 *)(key);
    zpl_math_u64 *end = data + (num_bytes / 8);
    unsigned char *data2;
    
    while (data != end) {
        zpl_math_u64 k = *data++;
        k *= m;
        k ^= k >> r;
        k *= m;
        h ^= k;
        h *= m;
    }
    
    data2 = (unsigned char *)data;
    
    switch (num_bytes & 7) {
        case 7: h ^= (zpl_math_u64)data2[6] << 48;
        case 6: h ^= (zpl_math_u64)data2[5] << 40;
        case 5: h ^= (zpl_math_u64)data2[4] << 32;
        case 4: h ^= (zpl_math_u64)data2[3] << 24;
        case 3: h ^= (zpl_math_u64)data2[2] << 16;
        case 2: h ^= (zpl_math_u64)data2[1] << 8;
        case 1: h ^= (zpl_math_u64)data2[0];
        h *= m;
    };
    
    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    
    return h;
}
#else
zpl_math_u64 zpl_hash_murmur64(void const *key, size_t num_bytes, zpl_math_u64 seed) {
    zpl_math_u32 const m = 0x5bd1e995;
    zpl_math_u32 const r = 24;
    
    zpl_math_u64 h  = 0;
    zpl_math_u32 h1 = (zpl_math_u32)seed ^ (zpl_math_u32)num_bytes;
    zpl_math_u32 h2 = (zpl_math_u32)((zpl_math_u64)seed >> 32);
    
    zpl_math_u32 *data = (zpl_math_u32 *)key;
    
    
    while (num_bytes >= 8) {
        zpl_math_u32 k1, k2;
        k1 = *data++;
        k1 *= m;
        k1 ^= k1 >> r;
        k1 *= m;
        h1 *= m;
        h1 ^= k1;
        num_bytes -= 4;
        
        k2 = *data++;
        k2 *= m;
        k2 ^= k2 >> r;
        k2 *= m;
        h2 *= m;
        h2 ^= k2;
        num_bytes -= 4;
    }
    
    if (num_bytes >= 4) {
        zpl_math_u32 k1 = *data++;
        k1 *= m;
        k1 ^= k1 >> r;
        k1 *= m;
        h1 *= m;
        h1 ^= k1;
        num_bytes -= 4;
    }
    
    switch (num_bytes) {
        zpl_math_u32 a, b, c;
        case 3: c = data[2]; h2 ^= c << 16;
        case 2: b = data[1]; h2 ^= b <<  8;
        case 1: a = data[0]; h2 ^= a <<  0;
        h2 *= m;
    };
    
    h1 ^= h2 >> 18;
    h1 *= m;
    h2 ^= h1 >> 22;
    h2 *= m;
    h1 ^= h2 >> 17;
    h1 *= m;
    h2 ^= h1 >> 19;
    h2 *= m;
    
    h = (zpl_math_u64)(h << 32) | (zpl_math_u64)h2;
    
    return h;
}
#endif


/* TODO: Make better random number generators */
float zpl_random_range_float(float min_inc, float max_inc) {
    int int_result = zpl_random_range_int(0, 2147483646); /* Prevent integer overflow */
    float result = int_result/(float)2147483646;
    result *= max_inc - min_inc;
    result += min_inc;
    return result;
}

int zpl_random_range_int(int min_inc, int max_inc) {
    static unsigned int random_value = 0xdeadbeef; /* Random Value */
    unsigned int diff, result;
    random_value = random_value * 2147001325 + 715136305; /* BCPL generator */
    diff = max_inc - min_inc + 1;
    result = random_value % diff;
    result += min_inc;
    
    return result;
}

float zpl_random01(void) {
    return zpl_random_range_float(0.0f, 1.0f);
}

#if defined(__GCC__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif



#endif /* ZPL_MATH_IMPLEMENTATION */
