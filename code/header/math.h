// file: header/math.h

/** @file math.c
@brief Math operations
@defgroup math Math operations

OpenGL gamedev friendly library for math.

@{
*/
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

typedef union zpl_vec2 {
    struct {
        zpl_f32 x, y;
    };
    zpl_f32 e[2];
} zpl_vec2;

typedef union zpl_vec3 {
    struct {
        zpl_f32 x, y, z;
    };
    struct {
        zpl_f32 r, g, b;
    };

    zpl_vec2 xy;
    zpl_f32 e[3];
} zpl_vec3;

typedef union zpl_vec4 {
    struct {
        zpl_f32 x, y, z, w;
    };
    struct {
        zpl_f32 r, g, b, a;
    };
    struct {
        zpl_vec2 xy, zw;
    };
    zpl_vec3 xyz;
    zpl_vec3 rgb;
    zpl_f32 e[4];
} zpl_vec4;

typedef union zpl_mat2 {
    struct {
        zpl_vec2 x, y;
    };
    zpl_vec2 col[2];
    zpl_f32 e[4];
} zpl_mat2;

typedef union zpl_mat3 {
    struct {
        zpl_vec3 x, y, z;
    };
    zpl_vec3 col[3];
    zpl_f32 e[9];
} zpl_mat3;

typedef union zpl_mat4 {
    struct {
        zpl_vec4 x, y, z, w;
    };
    zpl_vec4 col[4];
    zpl_f32 e[16];
} zpl_mat4;

typedef union zpl_quat {
    struct {
        zpl_f32 x, y, z, w;
    };
    zpl_vec4 xyzw;
    zpl_vec3 xyz;
    zpl_f32 e[4];
} zpl_quat;

typedef zpl_f32 zpl_float2[2];
typedef zpl_f32 zpl_float3[3];
typedef zpl_f32 zpl_float4[4];

typedef struct zpl_rect2 {
    zpl_vec2 pos, dim;
} zpl_rect2;
typedef struct zpl_rect3 {
    zpl_vec3 pos, dim;
} zpl_rect3;

typedef struct zpl_aabb2 {
    zpl_vec2 centre, half_size;
} zpl_aabb2;
typedef struct zpl_aabb3 {
    zpl_vec3 centre, half_size;
} zpl_aabb3;

typedef short zpl_half;

#ifndef ZPL_CONSTANTS
#define ZPL_CONSTANTS
#define ZPL_EPSILON    1.19209290e-7f
#define ZPL_ZERO       0.0f
#define ZPL_ONE        1.0f
#define ZPL_TWO_THIRDS 0.666666666666666666666666666666666666667f

#define ZPL_TAU          6.28318530717958647692528676655900576f
#define ZPL_PI           3.14159265358979323846264338327950288f
#define ZPL_ONE_OVER_TAU 0.636619772367581343075535053490057448f
#define ZPL_ONE_OVER_PI  0.159154943091895335768883763372514362f

#define ZPL_TAU_OVER_2 3.14159265358979323846264338327950288f
#define ZPL_TAU_OVER_4 1.570796326794896619231321691639751442f
#define ZPL_TAU_OVER_8 0.785398163397448309615660845819875721f

#define ZPL_E          2.71828182845904523536f
#define ZPL_SQRT_TWO   1.41421356237309504880168872420969808f
#define ZPL_SQRT_THREE 1.73205080756887729352744634150587236f
#define ZPL_SQRT_FIVE  2.23606797749978969640917366873127623f

#define ZPL_LOG_TWO 0.693147180559945309417232121458176568f
#define ZPL_LOG_TEN 2.30258509299404568401799145468436421f
#endif // ZPL_CONSTANTS

#ifndef zpl_square
#define zpl_square(x) ((x) * (x))
#endif

#ifndef zpl_cube
#define zpl_cube(x) ((x) * (x) * (x))
#endif

#ifndef zpl_sign
#define zpl_sign(x) ((x) >= 0 ? 1 : -1)
#endif

ZPL_DEF zpl_f32 zpl_to_radians(zpl_f32 degrees);
ZPL_DEF zpl_f32 zpl_to_degrees(zpl_f32 radians);

/* NOTE: Because to interpolate angles */
ZPL_DEF zpl_f32 zpl_angle_diff(zpl_f32 radians_a, zpl_f32 radians_b);

ZPL_DEF zpl_f32 zpl_copy_sign(zpl_f32 x, zpl_f32 y);
ZPL_DEF zpl_f32 zpl_remainder(zpl_f32 x, zpl_f32 y);
ZPL_DEF zpl_f32 zpl_mod(zpl_f32 x, zpl_f32 y);
ZPL_DEF zpl_f64 zpl_copy_sign64(zpl_f64 x, zpl_f64 y);
ZPL_DEF zpl_f64 zpl_floor64(zpl_f64 x);
ZPL_DEF zpl_f64 zpl_ceil64(zpl_f64 x);
ZPL_DEF zpl_f64 zpl_round64(zpl_f64 x);
ZPL_DEF zpl_f64 zpl_remainder64(zpl_f64 x, zpl_f64 y);
ZPL_DEF zpl_f64 zpl_abs64(zpl_f64 x);
ZPL_DEF zpl_f64 zpl_sign64(zpl_f64 x);
ZPL_DEF zpl_f64 zpl_mod64(zpl_f64 x, zpl_f64 y);
ZPL_DEF zpl_f32 zpl_sqrt(zpl_f32 a);
ZPL_DEF zpl_f32 zpl_rsqrt(zpl_f32 a);
ZPL_DEF zpl_f32 zpl_quake_rsqrt(zpl_f32 a); /* NOTE: It's probably better to use 1.0f/zpl_sqrt(a)
                                     * And for simd, there is usually isqrt functions too!
                                     */
ZPL_DEF zpl_f32 zpl_sin(zpl_f32 radians);
ZPL_DEF zpl_f32 zpl_cos(zpl_f32 radians);
ZPL_DEF zpl_f32 zpl_tan(zpl_f32 radians);
ZPL_DEF zpl_f32 zpl_arcsin(zpl_f32 a);
ZPL_DEF zpl_f32 zpl_arccos(zpl_f32 a);
ZPL_DEF zpl_f32 zpl_arctan(zpl_f32 a);
ZPL_DEF zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x);

ZPL_DEF zpl_f32 zpl_exp(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_exp2(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_log(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_log2(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_fast_exp(zpl_f32 x);   /* NOTE: Only valid from -1 <= x <= +1 */
ZPL_DEF zpl_f32 zpl_fast_exp2(zpl_f32 x);  /* NOTE: Only valid from -1 <= x <= +1 */
ZPL_DEF zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y); /* x^y */

ZPL_DEF zpl_f32 zpl_round(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_floor(zpl_f32 x);
ZPL_DEF zpl_f32 zpl_ceil(zpl_f32 x);

ZPL_DEF zpl_f32  zpl_half_to_float(zpl_half value);
ZPL_DEF zpl_half zpl_float_to_half(zpl_f32 value);

ZPL_DEF zpl_vec2 zpl_vec2f_zero(void);
ZPL_DEF zpl_vec2 zpl_vec2f(zpl_f32 x, zpl_f32 y);
ZPL_DEF zpl_vec2 zpl_vec2fv(zpl_f32 x[2]);

ZPL_DEF zpl_vec3 zpl_vec3f_zero(void);
ZPL_DEF zpl_vec3 zpl_vec3f(zpl_f32 x, zpl_f32 y, zpl_f32 z);
ZPL_DEF zpl_vec3 zpl_vec3fv(zpl_f32 x[3]);

ZPL_DEF zpl_vec4 zpl_vec4f_zero(void);
ZPL_DEF zpl_vec4 zpl_vec4f(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w);
ZPL_DEF zpl_vec4 zpl_vec4fv(zpl_f32 x[4]);

ZPL_DEF void zpl_vec2_add(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1);
ZPL_DEF void zpl_vec2_sub(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1);
ZPL_DEF void zpl_vec2_mul(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s);
ZPL_DEF void zpl_vec2_div(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s);

ZPL_DEF void zpl_vec3_add(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);
ZPL_DEF void zpl_vec3_sub(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);
ZPL_DEF void zpl_vec3_mul(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s);
ZPL_DEF void zpl_vec3_div(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s);

ZPL_DEF void zpl_vec4_add(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1);
ZPL_DEF void zpl_vec4_sub(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1);
ZPL_DEF void zpl_vec4_mul(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s);
ZPL_DEF void zpl_vec4_div(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s);

ZPL_DEF void zpl_vec2_addeq(zpl_vec2 *d, zpl_vec2 v);
ZPL_DEF void zpl_vec2_subeq(zpl_vec2 *d, zpl_vec2 v);
ZPL_DEF void zpl_vec2_muleq(zpl_vec2 *d, zpl_f32 s);
ZPL_DEF void zpl_vec2_diveq(zpl_vec2 *d, zpl_f32 s);

ZPL_DEF void zpl_vec3_addeq(zpl_vec3 *d, zpl_vec3 v);
ZPL_DEF void zpl_vec3_subeq(zpl_vec3 *d, zpl_vec3 v);
ZPL_DEF void zpl_vec3_muleq(zpl_vec3 *d, zpl_f32 s);
ZPL_DEF void zpl_vec3_diveq(zpl_vec3 *d, zpl_f32 s);

ZPL_DEF void zpl_vec4_addeq(zpl_vec4 *d, zpl_vec4 v);
ZPL_DEF void zpl_vec4_subeq(zpl_vec4 *d, zpl_vec4 v);
ZPL_DEF void zpl_vec4_muleq(zpl_vec4 *d, zpl_f32 s);
ZPL_DEF void zpl_vec4_diveq(zpl_vec4 *d, zpl_f32 s);

ZPL_DEF zpl_f32 zpl_vec2_dot(zpl_vec2 v0, zpl_vec2 v1);
ZPL_DEF zpl_f32 zpl_vec3_dot(zpl_vec3 v0, zpl_vec3 v1);
ZPL_DEF zpl_f32 zpl_vec4_dot(zpl_vec4 v0, zpl_vec4 v1);

ZPL_DEF void zpl_vec2_cross(zpl_f32 *d, zpl_vec2 v0, zpl_vec2 v1);
ZPL_DEF void zpl_vec3_cross(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);

ZPL_DEF zpl_f32 zpl_vec2_mag2(zpl_vec2 v);
ZPL_DEF zpl_f32 zpl_vec3_mag2(zpl_vec3 v);
ZPL_DEF zpl_f32 zpl_vec4_mag2(zpl_vec4 v);

ZPL_DEF zpl_f32 zpl_vec2_mag(zpl_vec2 v);
ZPL_DEF zpl_f32 zpl_vec3_mag(zpl_vec3 v);
ZPL_DEF zpl_f32 zpl_vec4_mag(zpl_vec4 v);

ZPL_DEF void zpl_vec2_norm(zpl_vec2 *d, zpl_vec2 v);
ZPL_DEF void zpl_vec3_norm(zpl_vec3 *d, zpl_vec3 v);
ZPL_DEF void zpl_vec4_norm(zpl_vec4 *d, zpl_vec4 v);

ZPL_DEF void zpl_vec2_norm0(zpl_vec2 *d, zpl_vec2 v);
ZPL_DEF void zpl_vec3_norm0(zpl_vec3 *d, zpl_vec3 v);
ZPL_DEF void zpl_vec4_norm0(zpl_vec4 *d, zpl_vec4 v);

ZPL_DEF void zpl_vec2_reflect(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n);
ZPL_DEF void zpl_vec3_reflect(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n);
ZPL_DEF void zpl_vec2_refract(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n, zpl_f32 eta);
ZPL_DEF void zpl_vec3_refract(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n, zpl_f32 eta);

ZPL_DEF zpl_f32 zpl_vec2_aspect_ratio(zpl_vec2 v);

ZPL_DEF void zpl_mat2_identity(zpl_mat2 *m);
ZPL_DEF void zpl_float22_identity(zpl_f32 m[2][2]);

ZPL_DEF void    zpl_mat2_transpose(zpl_mat2 *m);
ZPL_DEF void    zpl_mat2_mul(zpl_mat2 *out, zpl_mat2 *m1, zpl_mat2 *m2);
ZPL_DEF void    zpl_mat2_mul_vec2(zpl_vec2 *out, zpl_mat2 *m, zpl_vec2 in);
ZPL_DEF void    zpl_mat2_inverse(zpl_mat2 *out, zpl_mat2 *in);
ZPL_DEF zpl_f32 zpl_mat2_determinate(zpl_mat2 *m);

ZPL_DEF zpl_mat2   *zpl_mat2_v(zpl_vec2 m[2]);
ZPL_DEF zpl_mat2   *zpl_mat2_f(zpl_f32 m[2][2]);
ZPL_DEF zpl_float2 *zpl_float22_m(zpl_mat2 *m);
ZPL_DEF zpl_float2 *zpl_float22_v(zpl_vec2 m[2]);
ZPL_DEF zpl_float2 *zpl_float22_4(zpl_f32 m[4]);

ZPL_DEF void zpl_float22_transpose(zpl_f32 (*vec)[2]);
ZPL_DEF void zpl_float22_mul(zpl_f32 (*out)[2], zpl_f32 (*mat1)[2], zpl_f32 (*mat2)[2]);
ZPL_DEF void zpl_float22_mul_vec2(zpl_vec2 *out, zpl_f32 m[2][2], zpl_vec2 in);

ZPL_DEF void zpl_mat3_identity(zpl_mat3 *m);
ZPL_DEF void zpl_float33_identity(zpl_f32 m[3][3]);

ZPL_DEF void    zpl_mat3_transpose(zpl_mat3 *m);
ZPL_DEF void    zpl_mat3_mul(zpl_mat3 *out, zpl_mat3 *m1, zpl_mat3 *m2);
ZPL_DEF void    zpl_mat3_mul_vec3(zpl_vec3 *out, zpl_mat3 *m, zpl_vec3 in);
ZPL_DEF void    zpl_mat3_inverse(zpl_mat3 *out, zpl_mat3 *in);
ZPL_DEF zpl_f32 zpl_mat3_determinate(zpl_mat3 *m);

ZPL_DEF zpl_mat3   *zpl_mat3_v(zpl_vec3 m[3]);
ZPL_DEF zpl_mat3   *zpl_mat3_f(zpl_f32 m[3][3]);

ZPL_DEF zpl_float3 *zpl_float33_m(zpl_mat3 *m);
ZPL_DEF zpl_float3 *zpl_float33_v(zpl_vec3 m[3]);
ZPL_DEF zpl_float3 *zpl_float33_9(zpl_f32 m[9]);

ZPL_DEF void zpl_float33_transpose(zpl_f32 (*vec)[3]);
ZPL_DEF void zpl_float33_mul(zpl_f32 (*out)[3], zpl_f32 (*mat1)[3], zpl_f32 (*mat2)[3]);
ZPL_DEF void zpl_float33_mul_vec3(zpl_vec3 *out, zpl_f32 m[3][3], zpl_vec3 in);

ZPL_DEF void zpl_mat4_identity(zpl_mat4 *m);
ZPL_DEF void zpl_float44_identity(zpl_f32 m[4][4]);

ZPL_DEF void zpl_mat4_transpose(zpl_mat4 *m);
ZPL_DEF void zpl_mat4_mul(zpl_mat4 *out, zpl_mat4 *m1, zpl_mat4 *m2);
ZPL_DEF void zpl_mat4_mul_vec4(zpl_vec4 *out, zpl_mat4 *m, zpl_vec4 in);
ZPL_DEF void zpl_mat4_inverse(zpl_mat4 *out, zpl_mat4 *in);

ZPL_DEF zpl_mat4 *zpl_mat4_v(zpl_vec4 m[4]);
ZPL_DEF zpl_mat4 *zpl_mat4_f(zpl_f32 m[4][4]);

ZPL_DEF zpl_float4 *zpl_float44_m(zpl_mat4 *m);
ZPL_DEF zpl_float4 *zpl_float44_v(zpl_vec4 m[4]);
ZPL_DEF zpl_float4 *zpl_float44_16(zpl_f32 m[16]);

ZPL_DEF void zpl_float44_transpose(zpl_f32 (*vec)[4]);
ZPL_DEF void zpl_float44_mul(zpl_f32 (*out)[4], zpl_f32 (*mat1)[4], zpl_f32 (*mat2)[4]);
ZPL_DEF void zpl_float44_mul_vec4(zpl_vec4 *out, zpl_f32 m[4][4], zpl_vec4 in);

ZPL_DEF void zpl_mat4_translate(zpl_mat4 *out, zpl_vec3 v);
ZPL_DEF void zpl_mat4_rotate(zpl_mat4 *out, zpl_vec3 v, zpl_f32 angle_radians);
ZPL_DEF void zpl_mat4_scale(zpl_mat4 *out, zpl_vec3 v);
ZPL_DEF void zpl_mat4_scalef(zpl_mat4 *out, zpl_f32 s);
ZPL_DEF void zpl_mat4_ortho2d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top);
ZPL_DEF void zpl_mat4_ortho3d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far);
ZPL_DEF void zpl_mat4_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far);
ZPL_DEF void zpl_mat4_infinite_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near);

ZPL_DEF void zpl_mat4_look_at(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up);

ZPL_DEF zpl_quat zpl_quatf(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w);
ZPL_DEF zpl_quat zpl_quatfv(zpl_f32 e[4]);
ZPL_DEF zpl_quat zpl_quat_axis_angle(zpl_vec3 axis, zpl_f32 angle_radians);
ZPL_DEF zpl_quat zpl_quat_euler_angles(zpl_f32 pitch, zpl_f32 yaw, zpl_f32 roll);
ZPL_DEF zpl_quat zpl_quat_identity(void);

ZPL_DEF void zpl_quat_add(zpl_quat *d, zpl_quat q0, zpl_quat q1);
ZPL_DEF void zpl_quat_sub(zpl_quat *d, zpl_quat q0, zpl_quat q1);
ZPL_DEF void zpl_quat_mul(zpl_quat *d, zpl_quat q0, zpl_quat q1);
ZPL_DEF void zpl_quat_div(zpl_quat *d, zpl_quat q0, zpl_quat q1);

ZPL_DEF void zpl_quat_mulf(zpl_quat *d, zpl_quat q, zpl_f32 s);
ZPL_DEF void zpl_quat_divf(zpl_quat *d, zpl_quat q, zpl_f32 s);

ZPL_DEF void zpl_quat_addeq(zpl_quat *d, zpl_quat q);
ZPL_DEF void zpl_quat_subeq(zpl_quat *d, zpl_quat q);
ZPL_DEF void zpl_quat_muleq(zpl_quat *d, zpl_quat q);
ZPL_DEF void zpl_quat_diveq(zpl_quat *d, zpl_quat q);

ZPL_DEF void zpl_quat_muleqf(zpl_quat *d, zpl_f32 s);
ZPL_DEF void zpl_quat_diveqf(zpl_quat *d, zpl_f32 s);

ZPL_DEF zpl_f32 zpl_quat_dot(zpl_quat q0, zpl_quat q1);
ZPL_DEF zpl_f32 zpl_quat_mag(zpl_quat q);

ZPL_DEF void zpl_quat_norm(zpl_quat *d, zpl_quat q);
ZPL_DEF void zpl_quat_conj(zpl_quat *d, zpl_quat q);
ZPL_DEF void zpl_quat_inverse(zpl_quat *d, zpl_quat q);

ZPL_DEF void    zpl_quat_axis(zpl_vec3 *axis, zpl_quat q);
ZPL_DEF zpl_f32 zpl_quat_angle(zpl_quat q);

ZPL_DEF zpl_f32 zpl_quat_pitch(zpl_quat q);
ZPL_DEF zpl_f32 zpl_quat_yaw(zpl_quat q);
ZPL_DEF zpl_f32 zpl_quat_roll(zpl_quat q);

/* NOTE: Rotate v by q */
ZPL_DEF void zpl_quat_rotate_vec3(zpl_vec3 *d, zpl_quat q, zpl_vec3 v);
ZPL_DEF void zpl_mat4_from_quat(zpl_mat4 *out, zpl_quat q);
ZPL_DEF void zpl_quat_from_mat4(zpl_quat *out, zpl_mat4 *m);

/* Interpolations */
ZPL_DEF zpl_f32 zpl_lerp(zpl_f32 a, zpl_f32 b, zpl_f32 t);
ZPL_DEF zpl_f32 zpl_unlerp(zpl_f32 t, zpl_f32 a, zpl_f32 b);
ZPL_DEF zpl_f32 zpl_smooth_step(zpl_f32 a, zpl_f32 b, zpl_f32 t);
ZPL_DEF zpl_f32 zpl_smoother_step(zpl_f32 a, zpl_f32 b, zpl_f32 t);

ZPL_DEF void zpl_vec2_lerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 b, zpl_f32 t);
ZPL_DEF void zpl_vec3_lerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 b, zpl_f32 t);
ZPL_DEF void zpl_vec4_lerp(zpl_vec4 *d, zpl_vec4 a, zpl_vec4 b, zpl_f32 t);

ZPL_DEF void zpl_vec2_cslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t);
ZPL_DEF void zpl_vec3_cslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t);
ZPL_DEF void zpl_vec2_dcslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t);
ZPL_DEF void zpl_vec3_dcslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t);

ZPL_DEF void zpl_quat_lerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
ZPL_DEF void zpl_quat_nlerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
ZPL_DEF void zpl_quat_slerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
ZPL_DEF void zpl_quat_nquad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);
ZPL_DEF void zpl_quat_squad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);
ZPL_DEF void zpl_quat_slerp_approx(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
ZPL_DEF void zpl_quat_squad_approx(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);

/* Rects */
ZPL_DEF zpl_rect2 zpl_rect2f(zpl_vec2 pos, zpl_vec2 dim);
ZPL_DEF zpl_rect3 zpl_rect3f(zpl_vec3 pos, zpl_vec3 dim);

ZPL_DEF int zpl_rect2_contains(zpl_rect2 a, zpl_f32 x, zpl_f32 y);
ZPL_DEF int zpl_rect2_contains_vec2(zpl_rect2 a, zpl_vec2 p);
ZPL_DEF int zpl_rect2_intersects(zpl_rect2 a, zpl_rect2 b);
ZPL_DEF int zpl_rect2_intersection_result(zpl_rect2 a, zpl_rect2 b, zpl_rect2 *intersection);

//! @}
ZPL_END_C_DECLS
#if defined(__cplusplus)
    ZPL_INLINE bool operator==(zpl_vec2 a, zpl_vec2 b) { return (a.x == b.x) && (a.y == b.y); }
    ZPL_INLINE bool operator!=(zpl_vec2 a, zpl_vec2 b) { return !operator==(a, b); }

    ZPL_INLINE zpl_vec2 operator+(zpl_vec2 a) { return a; }
    ZPL_INLINE zpl_vec2 operator-(zpl_vec2 a) { zpl_vec2 r = {-a.x, -a.y}; return r; }

    ZPL_INLINE zpl_vec2 operator+(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_add(&r, a, b); return r; }
    ZPL_INLINE zpl_vec2 operator-(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_sub(&r, a, b); return r; }

    ZPL_INLINE zpl_vec2 operator*(zpl_vec2 a, float scalar) { zpl_vec2 r; zpl_vec2_mul(&r, a, scalar); return r; }
    ZPL_INLINE zpl_vec2 operator*(float scalar, zpl_vec2 a) { return operator*(a, scalar); }

    ZPL_INLINE zpl_vec2 operator/(zpl_vec2 a, float scalar) { return operator*(a, 1.0f/scalar); }

    /* Hadamard Product */
    ZPL_INLINE zpl_vec2 operator*(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x*b.x, a.y*b.y}; return r; }
    ZPL_INLINE zpl_vec2 operator/(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x/b.x, a.y/b.y}; return r; }

    ZPL_INLINE zpl_vec2 &operator+=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a + b); }
    ZPL_INLINE zpl_vec2 &operator-=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a - b); }
    ZPL_INLINE zpl_vec2 &operator*=(zpl_vec2 &a, float scalar) { return (a = a * scalar); }
    ZPL_INLINE zpl_vec2 &operator/=(zpl_vec2 &a, float scalar) { return (a = a / scalar); }


    ZPL_INLINE bool operator==(zpl_vec3 a, zpl_vec3 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
    ZPL_INLINE bool operator!=(zpl_vec3 a, zpl_vec3 b) { return !operator==(a, b); }

    ZPL_INLINE zpl_vec3 operator+(zpl_vec3 a) { return a; }
    ZPL_INLINE zpl_vec3 operator-(zpl_vec3 a) { zpl_vec3 r = {-a.x, -a.y, -a.z}; return r; }

    ZPL_INLINE zpl_vec3 operator+(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_add(&r, a, b); return r; }
    ZPL_INLINE zpl_vec3 operator-(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_sub(&r, a, b); return r; }

    ZPL_INLINE zpl_vec3 operator*(zpl_vec3 a, float scalar) { zpl_vec3 r; zpl_vec3_mul(&r, a, scalar); return r; }
    ZPL_INLINE zpl_vec3 operator*(float scalar, zpl_vec3 a) { return operator*(a, scalar); }

    ZPL_INLINE zpl_vec3 operator/(zpl_vec3 a, float scalar) { return operator*(a, 1.0f/scalar); }

    /* Hadamard Product */
    ZPL_INLINE zpl_vec3 operator*(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x*b.x, a.y*b.y, a.z*b.z}; return r; }
    ZPL_INLINE zpl_vec3 operator/(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x/b.x, a.y/b.y, a.z/b.z}; return r; }

    ZPL_INLINE zpl_vec3 &operator+=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a + b); }
    ZPL_INLINE zpl_vec3 &operator-=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a - b); }
    ZPL_INLINE zpl_vec3 &operator*=(zpl_vec3 &a, float scalar) { return (a = a * scalar); }
    ZPL_INLINE zpl_vec3 &operator/=(zpl_vec3 &a, float scalar) { return (a = a / scalar); }


    ZPL_INLINE bool operator==(zpl_vec4 a, zpl_vec4 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w); }
    ZPL_INLINE bool operator!=(zpl_vec4 a, zpl_vec4 b) { return !operator==(a, b); }

    ZPL_INLINE zpl_vec4 operator+(zpl_vec4 a) { return a; }
    ZPL_INLINE zpl_vec4 operator-(zpl_vec4 a) { zpl_vec4 r = {-a.x, -a.y, -a.z, -a.w}; return r; }

    ZPL_INLINE zpl_vec4 operator+(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_add(&r, a, b); return r; }
    ZPL_INLINE zpl_vec4 operator-(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_sub(&r, a, b); return r; }

    ZPL_INLINE zpl_vec4 operator*(zpl_vec4 a, float scalar) { zpl_vec4 r; zpl_vec4_mul(&r, a, scalar); return r; }
    ZPL_INLINE zpl_vec4 operator*(float scalar, zpl_vec4 a) { return operator*(a, scalar); }

    ZPL_INLINE zpl_vec4 operator/(zpl_vec4 a, float scalar) { return operator*(a, 1.0f/scalar); }

    /* Hadamard Product */
    ZPL_INLINE zpl_vec4 operator*(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return r; }
    ZPL_INLINE zpl_vec4 operator/(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return r; }

    ZPL_INLINE zpl_vec4 &operator+=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a + b); }
    ZPL_INLINE zpl_vec4 &operator-=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a - b); }
    ZPL_INLINE zpl_vec4 &operator*=(zpl_vec4 &a, float scalar) { return (a = a * scalar); }
    ZPL_INLINE zpl_vec4 &operator/=(zpl_vec4 &a, float scalar) { return (a = a / scalar); }


    ZPL_INLINE zpl_mat2 operator+(zpl_mat2 const &a, zpl_mat2 const &b) {
        int i, j;
        zpl_mat2 r = {0};
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 2; i++)
                r.e[2*j+i] = a.e[2*j+i] + b.e[2*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat2 operator-(zpl_mat2 const &a, zpl_mat2 const &b) {
        int i, j;
        zpl_mat2 r = {0};
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 2; i++)
                r.e[2*j+i] = a.e[2*j+i] - b.e[2*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat2 operator*(zpl_mat2 const &a, zpl_mat2 const &b) { zpl_mat2 r; zpl_mat2_mul(&r, (zpl_mat2 *)&a, (zpl_mat2 *)&b); return r; }
    ZPL_INLINE zpl_vec2 operator*(zpl_mat2 const &a, zpl_vec2 v) { zpl_vec2 r; zpl_mat2_mul_vec2(&r, (zpl_mat2 *)&a, v); return r; }
    ZPL_INLINE zpl_mat2 operator*(zpl_mat2 const &a, float scalar) {
        zpl_mat2 r = {0};
        int i;
        for (i = 0; i < 2*2; i++) r.e[i] = a.e[i] * scalar;
        return r;
    }
    ZPL_INLINE zpl_mat2 operator*(float scalar, zpl_mat2 const &a) { return operator*(a, scalar); }
    ZPL_INLINE zpl_mat2 operator/(zpl_mat2 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

    ZPL_INLINE zpl_mat2& operator+=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a + b); }
    ZPL_INLINE zpl_mat2& operator-=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a - b); }
    ZPL_INLINE zpl_mat2& operator*=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a * b); }



    ZPL_INLINE zpl_mat3 operator+(zpl_mat3 const &a, zpl_mat3 const &b) {
        int i, j;
        zpl_mat3 r = {0};
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 3; i++)
                r.e[3*j+i] = a.e[3*j+i] + b.e[3*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat3 operator-(zpl_mat3 const &a, zpl_mat3 const &b) {
        int i, j;
        zpl_mat3 r = {0};
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 3; i++)
                r.e[3*j+i] = a.e[3*j+i] - b.e[3*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat3 operator*(zpl_mat3 const &a, zpl_mat3 const &b) { zpl_mat3 r; zpl_mat3_mul(&r, (zpl_mat3 *)&a, (zpl_mat3 *)&b); return r; }
    ZPL_INLINE zpl_vec3 operator*(zpl_mat3 const &a, zpl_vec3 v) { zpl_vec3 r; zpl_mat3_mul_vec3(&r, (zpl_mat3 *)&a, v); return r; }
    ZPL_INLINE zpl_mat3 operator*(zpl_mat3 const &a, float scalar) {
        zpl_mat3 r = {0};
        int i;
        for (i = 0; i < 3*3; i++) r.e[i] = a.e[i] * scalar;
        return r;
    }
    ZPL_INLINE zpl_mat3 operator*(float scalar, zpl_mat3 const &a) { return operator*(a, scalar); }
    ZPL_INLINE zpl_mat3 operator/(zpl_mat3 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

    ZPL_INLINE zpl_mat3& operator+=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a + b); }
    ZPL_INLINE zpl_mat3& operator-=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a - b); }
    ZPL_INLINE zpl_mat3& operator*=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a * b); }



    ZPL_INLINE zpl_mat4 operator+(zpl_mat4 const &a, zpl_mat4 const &b) {
        int i, j;
        zpl_mat4 r = {0};
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++)
                r.e[4*j+i] = a.e[4*j+i] + b.e[4*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat4 operator-(zpl_mat4 const &a, zpl_mat4 const &b) {
        int i, j;
        zpl_mat4 r = {0};
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++)
                r.e[4*j+i] = a.e[4*j+i] - b.e[4*j+i];
        }
        return r;
    }

    ZPL_INLINE zpl_mat4 operator*(zpl_mat4 const &a, zpl_mat4 const &b) { zpl_mat4 r; zpl_mat4_mul(&r, (zpl_mat4 *)&a, (zpl_mat4 *)&b); return r; }
    ZPL_INLINE zpl_vec4 operator*(zpl_mat4 const &a, zpl_vec4 v) { zpl_vec4 r; zpl_mat4_mul_vec4(&r, (zpl_mat4 *)&a, v); return r; }
    ZPL_INLINE zpl_mat4 operator*(zpl_mat4 const &a, float scalar) {
        zpl_mat4 r = {0};
        int i;
        for (i = 0; i < 4*4; i++) r.e[i] = a.e[i] * scalar;
        return r;
    }
    ZPL_INLINE zpl_mat4 operator*(float scalar, zpl_mat4 const &a) { return operator*(a, scalar); }
    ZPL_INLINE zpl_mat4 operator/(zpl_mat4 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

    ZPL_INLINE zpl_mat4& operator+=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a + b); }
    ZPL_INLINE zpl_mat4& operator-=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a - b); }
    ZPL_INLINE zpl_mat4& operator*=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a * b); }



    ZPL_INLINE bool operator==(zpl_quat a, zpl_quat b) { return a.xyzw == b.xyzw; }
    ZPL_INLINE bool operator!=(zpl_quat a, zpl_quat b) { return !operator==(a, b); }

    ZPL_INLINE zpl_quat operator+(zpl_quat q) { return q; }
    ZPL_INLINE zpl_quat operator-(zpl_quat q) { return zpl_quatf(-q.x, -q.y, -q.z, -q.w); }

    ZPL_INLINE zpl_quat operator+(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_add(&r, a, b); return r; }
    ZPL_INLINE zpl_quat operator-(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_sub(&r, a, b); return r; }

    ZPL_INLINE zpl_quat operator*(zpl_quat a, zpl_quat b)  { zpl_quat r; zpl_quat_mul(&r, a, b); return r; }
    ZPL_INLINE zpl_quat operator*(zpl_quat q, float s) { zpl_quat r; zpl_quat_mulf(&r, q, s); return r; }
    ZPL_INLINE zpl_quat operator*(float s, zpl_quat q) { return operator*(q, s); }
    ZPL_INLINE zpl_quat operator/(zpl_quat q, float s) { zpl_quat r; zpl_quat_divf(&r, q, s); return r; }

    ZPL_INLINE zpl_quat &operator+=(zpl_quat &a, zpl_quat b) { zpl_quat_addeq(&a, b); return a; }
    ZPL_INLINE zpl_quat &operator-=(zpl_quat &a, zpl_quat b) { zpl_quat_subeq(&a, b); return a; }
    ZPL_INLINE zpl_quat &operator*=(zpl_quat &a, zpl_quat b) { zpl_quat_muleq(&a, b); return a; }
    ZPL_INLINE zpl_quat &operator/=(zpl_quat &a, zpl_quat b) { zpl_quat_diveq(&a, b); return a; }

    ZPL_INLINE zpl_quat &operator*=(zpl_quat &a, float b) { zpl_quat_muleqf(&a, b); return a; }
    ZPL_INLINE zpl_quat &operator/=(zpl_quat &a, float b) { zpl_quat_diveqf(&a, b); return a; }

    /* Rotate v by a */
    ZPL_INLINE zpl_vec3 operator*(zpl_quat q, zpl_vec3 v) { zpl_vec3 r; zpl_quat_rotate_vec3(&r, q, v); return r; }
#endif

