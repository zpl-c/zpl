/** @file math.c
@brief Math operations
@defgroup math Math operations

OpenGL gamedev friendly library for math.

@{
*/



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
#define ZPL_EPSILON 1.19209290e-7f
#define ZPL_ZERO 0.0f
#define ZPL_ONE 1.0f
#define ZPL_TWO_THIRDS 0.666666666666666666666666666666666666667f

#define ZPL_TAU 6.28318530717958647692528676655900576f
#define ZPL_PI 3.14159265358979323846264338327950288f
#define ZPL_ONE_OVER_TAU 0.636619772367581343075535053490057448f
#define ZPL_ONE_OVER_PI 0.159154943091895335768883763372514362f

#define ZPL_TAU_OVER_2 3.14159265358979323846264338327950288f
#define ZPL_TAU_OVER_4 1.570796326794896619231321691639751442f
#define ZPL_TAU_OVER_8 0.785398163397448309615660845819875721f

#define ZPL_E 2.71828182845904523536f
#define ZPL_SQRT_TWO 1.41421356237309504880168872420969808f
#define ZPL_SQRT_THREE 1.73205080756887729352744634150587236f
#define ZPL_SQRT_FIVE 2.23606797749978969640917366873127623f

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

ZPL_DEF zpl_f32 zpl_half_to_float(zpl_half value);
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

ZPL_DEF void zpl_mat2_transpose(zpl_mat2 *m);
ZPL_DEF void zpl_mat2_mul(zpl_mat2 *out, zpl_mat2 *m1, zpl_mat2 *m2);
ZPL_DEF void zpl_mat2_mul_vec2(zpl_vec2 *out, zpl_mat2 *m, zpl_vec2 in);
ZPL_DEF void zpl_mat2_inverse(zpl_mat2 *out, zpl_mat2 *in);
ZPL_DEF zpl_f32 zpl_mat2_determinate(zpl_mat2 *m);

ZPL_DEF zpl_mat2 *zpl_mat2_v(zpl_vec2 m[2]);
ZPL_DEF zpl_mat2 *zpl_mat2_f(zpl_f32 m[2][2]);
ZPL_DEF zpl_float2 *zpl_float22_m(zpl_mat2 *m);
ZPL_DEF zpl_float2 *zpl_float22_v(zpl_vec2 m[2]);
ZPL_DEF zpl_float2 *zpl_float22_4(zpl_f32 m[4]);

ZPL_DEF void zpl_float22_transpose(zpl_f32 (*vec)[2]);
ZPL_DEF void zpl_float22_mul(zpl_f32 (*out)[2], zpl_f32 (*mat1)[2], zpl_f32 (*mat2)[2]);
ZPL_DEF void zpl_float22_mul_vec2(zpl_vec2 *out, zpl_f32 m[2][2], zpl_vec2 in);

ZPL_DEF void zpl_mat3_identity(zpl_mat3 *m);
ZPL_DEF void zpl_float33_identity(zpl_f32 m[3][3]);

ZPL_DEF void zpl_mat3_transpose(zpl_mat3 *m);
ZPL_DEF void zpl_mat3_mul(zpl_mat3 *out, zpl_mat3 *m1, zpl_mat3 *m2);
ZPL_DEF void zpl_mat3_mul_vec3(zpl_vec3 *out, zpl_mat3 *m, zpl_vec3 in);
ZPL_DEF void zpl_mat3_inverse(zpl_mat3 *out, zpl_mat3 *in);
ZPL_DEF zpl_f32 zpl_mat3_determinate(zpl_mat3 *m);

ZPL_DEF zpl_mat3 *zpl_mat3_v(zpl_vec3 m[3]);
ZPL_DEF zpl_mat3 *zpl_mat3_f(zpl_f32 m[3][3]);

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

ZPL_DEF void zpl_quat_axis(zpl_vec3 *axis, zpl_quat q);
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

#ifndef ZPL_MURMUR64_DEFAULT_SEED
#define ZPL_MURMUR64_DEFAULT_SEED 0x9747b28c
#endif

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Math
//

/* NOTE: To remove the need for memcpy */
static void zpl__memcpy_4byte(void *dest, void const *src, zpl_isize size) {
    zpl_isize i;
    unsigned int *d, *s;
    d = (unsigned int *)dest;
    s = (unsigned int *)src;
    for (i = 0; i < size / 4; i++) { *d++ = *s++; }
}

zpl_f32 zpl_to_radians(zpl_f32 degrees) { return degrees * ZPL_TAU / 360.0f; }
zpl_f32 zpl_to_degrees(zpl_f32 radians) { return radians * 360.0f / ZPL_TAU; }

zpl_f32 zpl_angle_diff(zpl_f32 radians_a, zpl_f32 radians_b) {
    zpl_f32 delta = zpl_mod(radians_b - radians_a, ZPL_TAU);
    delta = zpl_mod(delta + 1.5f * ZPL_TAU, ZPL_TAU);
    delta -= 0.5f * ZPL_TAU;
    return delta;
}

zpl_f32 zpl_copy_sign(zpl_f32 x, zpl_f32 y) {
    int ix, iy;
    ix = *(int *)&x;
    iy = *(int *)&y;
    
    ix &= 0x7fffffff;
    ix |= iy & 0x80000000;
    return *(zpl_f32 *)&ix;
}

zpl_f32 zpl_remainder(zpl_f32 x, zpl_f32 y) { return x - (zpl_round(x / y) * y); }

zpl_f32 zpl_mod(zpl_f32 x, zpl_f32 y) {
    zpl_f32 result;
    y = zpl_abs(y);
    result = zpl_remainder(zpl_abs(x), y);
    if (zpl_sign(result)) result += y;
    return zpl_copy_sign(result, x);
}

zpl_f64 zpl_copy_sign64(zpl_f64 x, zpl_f64 y) {
    zpl_i64 ix, iy;
    ix = *(zpl_i64 *)&x;
    iy = *(zpl_i64 *)&y;
    
    ix &= 0x7fffffffffffffff;
    ix |= iy & 0x8000000000000000;
    return *cast(zpl_f64 *) & ix;
}

zpl_f64 zpl_floor64(zpl_f64 x) { return cast(zpl_f64)((x >= 0.0) ? cast(zpl_i64) x : cast(zpl_i64)(x - 0.9999999999999999)); }
zpl_f64 zpl_ceil64(zpl_f64 x) { return cast(zpl_f64)((x < 0) ? cast(zpl_i64) x : (cast(zpl_i64) x) + 1); }
zpl_f64 zpl_round64(zpl_f64 x) { return cast(zpl_f64)((x >= 0.0) ? zpl_floor64(x + 0.5) : zpl_ceil64(x - 0.5)); }
zpl_f64 zpl_remainder64(zpl_f64 x, zpl_f64 y) { return x - (zpl_round64(x / y) * y); }
zpl_f64 zpl_abs64(zpl_f64 x) { return x < 0 ? -x : x; }
zpl_f64 zpl_sign64(zpl_f64 x) { return x < 0 ? -1.0 : +1.0; }

zpl_f64 zpl_mod64(zpl_f64 x, zpl_f64 y) {
    zpl_f64 result;
    y = zpl_abs64(y);
    result = zpl_remainder64(zpl_abs64(x), y);
    if (zpl_sign64(result)) result += y;
    return zpl_copy_sign64(result, x);
}

zpl_f32 zpl_quake_rsqrt(zpl_f32 a) {
    union {
        int i;
        zpl_f32 f;
    } t;
    zpl_f32 x2;
    zpl_f32 const three_halfs = 1.5f;
    
    x2 = a * 0.5f;
    t.f = a;
    t.i = 0x5f375a86 - (t.i >> 1);                /* What the fuck? */
    t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 1st iteration */
    t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 2nd iteration, this can be removed */
    
    return t.f;
}

#if defined(ZPL_NO_MATH_H)
#if defined(_MSC_VER)

zpl_f32 zpl_rsqrt(zpl_f32 a) { return _mm_cvtss_zpl_f32(_mm_rsqrt_ss(_mm_set_ss(a))); }
zpl_f32 zpl_sqrt(zpl_f32 a) { return _mm_cvtss_zpl_f32(_mm_sqrt_ss(_mm_set_ss(a))); };
zpl_f32 zpl_sin(zpl_f32 a) {
    static zpl_f32 const a0 = +1.91059300966915117e-31f;
    static zpl_f32 const a1 = +1.00086760103908896f;
    static zpl_f32 const a2 = -1.21276126894734565e-2f;
    static zpl_f32 const a3 = -1.38078780785773762e-1f;
    static zpl_f32 const a4 = -2.67353392911981221e-2f;
    static zpl_f32 const a5 = +2.08026600266304389e-2f;
    static zpl_f32 const a6 = -3.03996055049204407e-3f;
    static zpl_f32 const a7 = +1.38235642404333740e-4f;
    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
}
zpl_f32 zpl_cos(zpl_f32 a) {
    static zpl_f32 const a0 = +1.00238601909309722f;
    static zpl_f32 const a1 = -3.81919947353040024e-2f;
    static zpl_f32 const a2 = -3.94382342128062756e-1f;
    static zpl_f32 const a3 = -1.18134036025221444e-1f;
    static zpl_f32 const a4 = +1.07123798512170878e-1f;
    static zpl_f32 const a5 = -1.86637164165180873e-2f;
    static zpl_f32 const a6 = +9.90140908664079833e-4f;
    static zpl_f32 const a7 = -5.23022132118824778e-14f;
    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
}

zpl_f32 zpl_tan(zpl_f32 radians) {
    zpl_f32 rr = radians * radians;
    zpl_f32 a = 9.5168091e-03f;
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

zpl_f32 zpl_arcsin(zpl_f32 a) { return zpl_arctan2(a, zpl_sqrt((1.0f + a) * (1.0f - a))); }
zpl_f32 zpl_arccos(zpl_f32 a) { return zpl_arctan2(zpl_sqrt((1.0f + a) * (1.0 - a)), a); }

zpl_f32 zpl_arctan(zpl_f32 a) {
    zpl_f32 u = a * a;
    zpl_f32 u2 = u * u;
    zpl_f32 u3 = u2 * u;
    zpl_f32 u4 = u3 * u;
    zpl_f32 f = 1.0f + 0.33288950512027f * u - 0.08467922817644f * u2 + 0.03252232640125f * u3 - 0.00749305860992f * u4;
    return a / f;
}

zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x) {
    if (zpl_abs(x) > zpl_abs(y)) {
        zpl_f32 a = zpl_arctan(y / x);
        if (x > 0.0f)
            return a;
        else
            return y > 0.0f ? a + ZPL_TAU_OVER_2 : a - ZPL_TAU_OVER_2;
    } else {
        zpl_f32 a = zpl_arctan(x / y);
        if (x > 0.0f)
            return y > 0.0f ? ZPL_TAU_OVER_4 - a : -ZPL_TAU_OVER_4 - a;
        else
            return y > 0.0f ? ZPL_TAU_OVER_4 + a : -ZPL_TAU_OVER_4 + a;
    }
}

zpl_f32 zpl_exp(zpl_f32 a) {
    union {
        zpl_f32 f;
        int i;
    } u, v;
    u.i = (int)(6051102 * a + 1056478197);
    v.i = (int)(1056478197 - 6051102 * a);
    return u.f / v.f;
}

zpl_f32 zpl_log(zpl_f32 a) {
    union {
        zpl_f32 f;
        int i;
    } u = { a };
    return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}

zpl_f32 zpl_pow(zpl_f32 a, zpl_f32 b) {
    int flipped = 0, e;
    zpl_f32 f, r = 1.0f;
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
    return flipped ? 1.0f / r : r;
}

#else

zpl_f32 zpl_rsqrt(zpl_f32 a) { return 1.0f / __builtin_sqrt(a); }
zpl_f32 zpl_sqrt(zpl_f32 a) { return __builtin_sqrt(a); }
zpl_f32 zpl_sin(zpl_f32 radians) { return __builtin_sinf(radians); }
zpl_f32 zpl_cos(zpl_f32 radians) { return __builtin_cosf(radians); }
zpl_f32 zpl_tan(zpl_f32 radians) { return __builtin_tanf(radians); }
zpl_f32 zpl_arcsin(zpl_f32 a) { return __builtin_asinf(a); }
zpl_f32 zpl_arccos(zpl_f32 a) { return __builtin_acosf(a); }
zpl_f32 zpl_arctan(zpl_f32 a) { return __builtin_atanf(a); }
zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x) { return __builtin_atan2f(y, x); }

zpl_f32 zpl_exp(zpl_f32 x) { return __builtin_expf(x); }
zpl_f32 zpl_log(zpl_f32 x) { return __builtin_logf(x); }

// TODO: Should this be zpl_exp(y * zpl_log(x)) ???
zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y) { return __builtin_powf(x, y); }

#endif

#else
zpl_f32 zpl_rsqrt(zpl_f32 a) { return 1.0f / sqrtf(a); }
zpl_f32 zpl_sqrt(zpl_f32 a) { return sqrtf(a); };
zpl_f32 zpl_sin(zpl_f32 radians) { return sinf(radians); };
zpl_f32 zpl_cos(zpl_f32 radians) { return cosf(radians); };
zpl_f32 zpl_tan(zpl_f32 radians) { return tanf(radians); };
zpl_f32 zpl_arcsin(zpl_f32 a) { return asinf(a); };
zpl_f32 zpl_arccos(zpl_f32 a) { return acosf(a); };
zpl_f32 zpl_arctan(zpl_f32 a) { return atanf(a); };
zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x) { return atan2f(y, x); };

zpl_f32 zpl_exp(zpl_f32 x) { return expf(x); }
zpl_f32 zpl_log(zpl_f32 x) { return logf(x); }
zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y) { return powf(x, y); }
#endif

zpl_f32 zpl_exp2(zpl_f32 x) { return zpl_exp(ZPL_LOG_TWO * x); }
zpl_f32 zpl_log2(zpl_f32 x) { return zpl_log(x) / ZPL_LOG_TWO; }

zpl_f32 zpl_fast_exp(zpl_f32 x) {
    /* NOTE: Only works in the range -1 <= x <= +1 */
    zpl_f32 e = 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25f * (1.0f + x * 0.2f))));
    return e;
}

zpl_f32 zpl_fast_exp2(zpl_f32 x) { return zpl_fast_exp(ZPL_LOG_TWO * x); }

zpl_f32 zpl_round(zpl_f32 x) { return (float)((x >= 0.0f) ? zpl_floor(x + 0.5f) : zpl_ceil(x - 0.5f)); }
zpl_f32 zpl_floor(zpl_f32 x) { return (float)((x >= 0.0f) ? (int)x : (int)(x - 0.9999999999999999f)); }
zpl_f32 zpl_ceil(zpl_f32 x) { return (float)((x < 0) ? (int)x : ((int)x) + 1); }

zpl_f32 zpl_half_to_float(zpl_half value) {
    union {
        unsigned int i;
        zpl_f32 f;
    } result;
    int s = (value >> 15) & 0x001;
    int e = (value >> 10) & 0x01f;
    int m = value & 0x3ff;
    
    if (e == 0) {
        if (m == 0) {
            /* Plus or minus zero */
            result.i = (unsigned int)(s << 31);
            return result.f;
        } else {
            /* Denormalized number */
            while (!(m & 0x00000400)) {
                m <<= 1;
                e -= 1;
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

zpl_half zpl_float_to_half(zpl_f32 value) {
    union {
        unsigned int i;
        zpl_f32 f;
    } v;
    int i, s, e, m;
    
    v.f = value;
    i = (int)v.i;
    
    s = (i >> 16) & 0x00008000;
    e = ((i >> 23) & 0x000000ff) - (127 - 15);
    m = i & 0x007fffff;
    
    if (e <= 0) {
        if (e < -10) return (zpl_half)s;
        m = (m | 0x00800000) >> (1 - e);
        
        if (m & 0x00001000) m += 0x00002000;
        
        return (zpl_half)(s | (m >> 13));
    } else if (e == 0xff - (127 - 15)) {
        if (m == 0) {
            return (zpl_half)(s | 0x7c00); /* NOTE: infinity */
        } else {
            /* NOTE: NAN */
            m >>= 13;
            return (zpl_half)(s | 0x7c00 | m | (m == 0));
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
            zpl_f32 volatile f = 1e12f;
            int j;
            for (j = 0; j < 10; j++) f *= f; /* NOTE: Cause overflow */
            
            return (zpl_half)(s | 0x7c00);
        }
        
        return (zpl_half)(s | (e << 10) | (m >> 13));
    }
}

#define ZPL_VEC2_2OP(a, c, post)                                                                                       \
\
a->x = c.x post;                                                                                                   \
\
a->y = c.y post;

#define ZPL_VEC2_3OP(a, b, op, c, post)                                                                                \
\
a->x = b.x op c.x post;                                                                                            \
\
a->y = b.y op c.y post;

#define ZPL_VEC3_2OP(a, c, post)                                                                                       \
\
a->x = c.x post;                                                                                                   \
\
a->y = c.y post;                                                                                                   \
\
a->z = c.z post;

#define ZPL_VEC3_3OP(a, b, op, c, post)                                                                                \
\
a->x = b.x op c.x post;                                                                                            \
\
a->y = b.y op c.y post;                                                                                            \
\
a->z = b.z op c.z post;

#define ZPL_VEC4_2OP(a, c, post)                                                                                       \
\
a->x = c.x post;                                                                                                   \
\
a->y = c.y post;                                                                                                   \
\
a->z = c.z post;                                                                                                   \
\
a->w = c.w post;

#define ZPL_VEC4_3OP(a, b, op, c, post)                                                                                \
\
a->x = b.x op c.x post;                                                                                            \
\
a->y = b.y op c.y post;                                                                                            \
\
a->z = b.z op c.z post;                                                                                            \
\
a->w = b.w op c.w post;

zpl_vec2 zpl_vec2f_zero(void) {
    zpl_vec2 v = { 0, 0 };
    return v;
}
zpl_vec2 zpl_vec2f(zpl_f32 x, zpl_f32 y) {
    zpl_vec2 v;
    v.x = x;
    v.y = y;
    return v;
}
zpl_vec2 zpl_vec2fv(zpl_f32 x[2]) {
    zpl_vec2 v;
    v.x = x[0];
    v.y = x[1];
    return v;
}

zpl_vec3 zpl_vec3f_zero(void) {
    zpl_vec3 v = { 0, 0, 0 };
    return v;
}
zpl_vec3 zpl_vec3f(zpl_f32 x, zpl_f32 y, zpl_f32 z) {
    zpl_vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
zpl_vec3 zpl_vec3fv(zpl_f32 x[3]) {
    zpl_vec3 v;
    v.x = x[0];
    v.y = x[1];
    v.z = x[2];
    return v;
}

zpl_vec4 zpl_vec4f_zero(void) {
    zpl_vec4 v = { 0, 0, 0, 0 };
    return v;
}
zpl_vec4 zpl_vec4f(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w) {
    zpl_vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}
zpl_vec4 zpl_vec4fv(zpl_f32 x[4]) {
    zpl_vec4 v;
    v.x = x[0];
    v.y = x[1];
    v.z = x[2];
    v.w = x[3];
    return v;
}

void zpl_vec2_add(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1) { ZPL_VEC2_3OP(d, v0, +, v1, +0); }
void zpl_vec2_sub(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1) { ZPL_VEC2_3OP(d, v0, -, v1, +0); }
void zpl_vec2_mul(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s) { ZPL_VEC2_2OP(d, v, *s); }
void zpl_vec2_div(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s) { ZPL_VEC2_2OP(d, v, / s); }

void zpl_vec3_add(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) { ZPL_VEC3_3OP(d, v0, +, v1, +0); }
void zpl_vec3_sub(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) { ZPL_VEC3_3OP(d, v0, -, v1, +0); }
void zpl_vec3_mul(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s) { ZPL_VEC3_2OP(d, v, *s); }
void zpl_vec3_div(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s) { ZPL_VEC3_2OP(d, v, / s); }

void zpl_vec4_add(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1) { ZPL_VEC4_3OP(d, v0, +, v1, +0); }
void zpl_vec4_sub(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1) { ZPL_VEC4_3OP(d, v0, -, v1, +0); }
void zpl_vec4_mul(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s) { ZPL_VEC4_2OP(d, v, *s); }
void zpl_vec4_div(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s) { ZPL_VEC4_2OP(d, v, / s); }

void zpl_vec2_addeq(zpl_vec2 *d, zpl_vec2 v) { ZPL_VEC2_3OP(d, (*d), +, v, +0); }
void zpl_vec2_subeq(zpl_vec2 *d, zpl_vec2 v) { ZPL_VEC2_3OP(d, (*d), -, v, +0); }
void zpl_vec2_muleq(zpl_vec2 *d, zpl_f32 s) { ZPL_VEC2_2OP(d, (*d), *s); }
void zpl_vec2_diveq(zpl_vec2 *d, zpl_f32 s) { ZPL_VEC2_2OP(d, (*d), / s); }

void zpl_vec3_addeq(zpl_vec3 *d, zpl_vec3 v) { ZPL_VEC3_3OP(d, (*d), +, v, +0); }
void zpl_vec3_subeq(zpl_vec3 *d, zpl_vec3 v) { ZPL_VEC3_3OP(d, (*d), -, v, +0); }
void zpl_vec3_muleq(zpl_vec3 *d, zpl_f32 s) { ZPL_VEC3_2OP(d, (*d), *s); }
void zpl_vec3_diveq(zpl_vec3 *d, zpl_f32 s) { ZPL_VEC3_2OP(d, (*d), / s); }

void zpl_vec4_addeq(zpl_vec4 *d, zpl_vec4 v) { ZPL_VEC4_3OP(d, (*d), +, v, +0); }
void zpl_vec4_subeq(zpl_vec4 *d, zpl_vec4 v) { ZPL_VEC4_3OP(d, (*d), -, v, +0); }
void zpl_vec4_muleq(zpl_vec4 *d, zpl_f32 s) { ZPL_VEC4_2OP(d, (*d), *s); }
void zpl_vec4_diveq(zpl_vec4 *d, zpl_f32 s) { ZPL_VEC4_2OP(d, (*d), / s); }

#undef ZPL_VEC2_2OP
#undef ZPL_VEC2_3OP
#undef ZPL_VEC3_3OP
#undef ZPL_VEC3_2OP
#undef ZPL_VEC4_2OP
#undef ZPL_VEC4_3OP

zpl_f32 zpl_vec2_dot(zpl_vec2 v0, zpl_vec2 v1) { return v0.x * v1.x + v0.y * v1.y; }
zpl_f32 zpl_vec3_dot(zpl_vec3 v0, zpl_vec3 v1) { return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; }
zpl_f32 zpl_vec4_dot(zpl_vec4 v0, zpl_vec4 v1) { return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w; }

void zpl_vec2_cross(zpl_f32 *d, zpl_vec2 v0, zpl_vec2 v1) { *d = v0.x * v1.y - v1.x * v0.y; }
void zpl_vec3_cross(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) {
    d->x = v0.y * v1.z - v0.z * v1.y;
    d->y = v0.z * v1.x - v0.x * v1.z;
    d->z = v0.x * v1.y - v0.y * v1.x;
}

zpl_f32 zpl_vec2_mag2(zpl_vec2 v) { return zpl_vec2_dot(v, v); }
zpl_f32 zpl_vec3_mag2(zpl_vec3 v) { return zpl_vec3_dot(v, v); }
zpl_f32 zpl_vec4_mag2(zpl_vec4 v) { return zpl_vec4_dot(v, v); }

/* TODO: Create custom sqrt function */
zpl_f32 zpl_vec2_mag(zpl_vec2 v) { return zpl_sqrt(zpl_vec2_dot(v, v)); }
zpl_f32 zpl_vec3_mag(zpl_vec3 v) { return zpl_sqrt(zpl_vec3_dot(v, v)); }
zpl_f32 zpl_vec4_mag(zpl_vec4 v) { return zpl_sqrt(zpl_vec4_dot(v, v)); }

void zpl_vec2_norm(zpl_vec2 *d, zpl_vec2 v) {
    zpl_f32 inv_mag = zpl_rsqrt(zpl_vec2_dot(v, v));
    zpl_vec2_mul(d, v, inv_mag);
}
void zpl_vec3_norm(zpl_vec3 *d, zpl_vec3 v) {
    zpl_f32 mag = zpl_vec3_mag(v);
    zpl_vec3_div(d, v, mag);
}
void zpl_vec4_norm(zpl_vec4 *d, zpl_vec4 v) {
    zpl_f32 mag = zpl_vec4_mag(v);
    zpl_vec4_div(d, v, mag);
}

void zpl_vec2_norm0(zpl_vec2 *d, zpl_vec2 v) {
    zpl_f32 mag = zpl_vec2_mag(v);
    if (mag > 0)
        zpl_vec2_div(d, v, mag);
    else
        *d = zpl_vec2f_zero( );
}
void zpl_vec3_norm0(zpl_vec3 *d, zpl_vec3 v) {
    zpl_f32 mag = zpl_vec3_mag(v);
    if (mag > 0)
        zpl_vec3_div(d, v, mag);
    else
        *d = zpl_vec3f_zero( );
}
void zpl_vec4_norm0(zpl_vec4 *d, zpl_vec4 v) {
    zpl_f32 mag = zpl_vec4_mag(v);
    if (mag > 0)
        zpl_vec4_div(d, v, mag);
    else
        *d = zpl_vec4f_zero( );
}

void zpl_vec2_reflect(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n) {
    zpl_vec2 b = n;
    zpl_vec2_muleq(&b, 2.0f * zpl_vec2_dot(n, i));
    zpl_vec2_sub(d, i, b);
}

void zpl_vec3_reflect(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n) {
    zpl_vec3 b = n;
    zpl_vec3_muleq(&b, 2.0f * zpl_vec3_dot(n, i));
    zpl_vec3_sub(d, i, b);
}

void zpl_vec2_refract(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n, zpl_f32 eta) {
    zpl_vec2 a, b;
    zpl_f32 dv, k;
    
    dv = zpl_vec2_dot(n, i);
    k = 1.0f - eta * eta * (1.0f - dv * dv);
    zpl_vec2_mul(&a, i, eta);
    zpl_vec2_mul(&b, n, eta * dv * zpl_sqrt(k));
    zpl_vec2_sub(d, a, b);
    zpl_vec2_muleq(d, (float)(k >= 0.0f));
}

void zpl_vec3_refract(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n, zpl_f32 eta) {
    zpl_vec3 a, b;
    zpl_f32 dv, k;
    
    dv = zpl_vec3_dot(n, i);
    k = 1.0f - eta * eta * (1.0f - dv * dv);
    zpl_vec3_mul(&a, i, eta);
    zpl_vec3_mul(&b, n, eta * dv * zpl_sqrt(k));
    zpl_vec3_sub(d, a, b);
    zpl_vec3_muleq(d, (float)(k >= 0.0f));
}

zpl_f32 zpl_vec2_aspect_ratio(zpl_vec2 v) { return (v.y < 0.0001f) ? 0.0f : v.x / v.y; }

void zpl_mat2_transpose(zpl_mat2 *m) { zpl_float22_transpose(zpl_float22_m(m)); }
void zpl_mat2_identity(zpl_mat2 *m) { zpl_float22_identity(zpl_float22_m(m)); }
void zpl_mat2_mul(zpl_mat2 *out, zpl_mat2 *m1, zpl_mat2 *m2) {
    zpl_float22_mul(zpl_float22_m(out), zpl_float22_m(m1), zpl_float22_m(m2));
}

void zpl_float22_identity(zpl_f32 m[2][2]) {
    m[0][0] = 1;
    m[0][1] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
}

void zpl_mat2_mul_vec2(zpl_vec2 *out, zpl_mat2 *m, zpl_vec2 in) { zpl_float22_mul_vec2(out, zpl_float22_m(m), in); }

zpl_mat2 *zpl_mat2_v(zpl_vec2 m[2]) { return (zpl_mat2 *)m; }
zpl_mat2 *zpl_mat2_f(zpl_f32 m[2][2]) { return (zpl_mat2 *)m; }

zpl_float2 *zpl_float22_m(zpl_mat2 *m) { return (zpl_float2 *)m; }
zpl_float2 *zpl_float22_v(zpl_vec2 m[2]) { return (zpl_float2 *)m; }
zpl_float2 *zpl_float22_4(zpl_f32 m[4]) { return (zpl_float2 *)m; }

void zpl_float22_transpose(zpl_f32 (*vec)[2]) {
    int i, j;
    for (j = 0; j < 2; j++) {
        for (i = j + 1; i < 2; i++) {
            zpl_f32 t = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = t;
        }
    }
}

void zpl_float22_mul(zpl_f32 (*out)[2], zpl_f32 (*mat1)[2], zpl_f32 (*mat2)[2]) {
    int i, j;
    zpl_f32 temp1[2][2], temp2[2][2];
    if (mat1 == out) {
        zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
        mat1 = temp1;
    }
    if (mat2 == out) {
        zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
        mat2 = temp2;
    }
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++) { out[j][i] = mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1]; }
    }
}

void zpl_float22_mul_vec2(zpl_vec2 *out, zpl_f32 m[2][2], zpl_vec2 v) {
    out->x = m[0][0] * v.x + m[0][1] * v.y;
    out->y = m[1][0] * v.x + m[1][1] * v.y;
}

zpl_f32 zpl_mat2_determinate(zpl_mat2 *m) {
    zpl_float2 *e = zpl_float22_m(m);
    return e[0][0] * e[1][1] - e[1][0] * e[0][1];
}

void zpl_mat2_inverse(zpl_mat2 *out, zpl_mat2 *in) {
    zpl_float2 *o = zpl_float22_m(out);
    zpl_float2 *i = zpl_float22_m(in);
    
    zpl_f32 ood = 1.0f / zpl_mat2_determinate(in);
    
    o[0][0] = +i[1][1] * ood;
    o[0][1] = -i[0][1] * ood;
    o[1][0] = -i[1][0] * ood;
    o[1][1] = +i[0][0] * ood;
}

void zpl_mat3_transpose(zpl_mat3 *m) { zpl_float33_transpose(zpl_float33_m(m)); }
void zpl_mat3_identity(zpl_mat3 *m) { zpl_float33_identity(zpl_float33_m(m)); }
void zpl_mat3_mul(zpl_mat3 *out, zpl_mat3 *m1, zpl_mat3 *m2) {
    zpl_float33_mul(zpl_float33_m(out), zpl_float33_m(m1), zpl_float33_m(m2));
}

void zpl_float33_identity(zpl_f32 m[3][3]) {
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
}

void zpl_mat3_mul_vec3(zpl_vec3 *out, zpl_mat3 *m, zpl_vec3 in) { zpl_float33_mul_vec3(out, zpl_float33_m(m), in); }

zpl_mat3 *zpl_mat3_v(zpl_vec3 m[3]) { return (zpl_mat3 *)m; }
zpl_mat3 *zpl_mat3_f(zpl_f32 m[3][3]) { return (zpl_mat3 *)m; }

zpl_float3 *zpl_float33_m(zpl_mat3 *m) { return (zpl_float3 *)m; }
zpl_float3 *zpl_float33_v(zpl_vec3 m[3]) { return (zpl_float3 *)m; }
zpl_float3 *zpl_float33_9(zpl_f32 m[9]) { return (zpl_float3 *)m; }

void zpl_float33_transpose(zpl_f32 (*vec)[3]) {
    int i, j;
    for (j = 0; j < 3; j++) {
        for (i = j + 1; i < 3; i++) {
            zpl_f32 t = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = t;
        }
    }
}

void zpl_float33_mul(zpl_f32 (*out)[3], zpl_f32 (*mat1)[3], zpl_f32 (*mat2)[3]) {
    int i, j;
    zpl_f32 temp1[3][3], temp2[3][3];
    if (mat1 == out) {
        zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
        mat1 = temp1;
    }
    if (mat2 == out) {
        zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
        mat2 = temp2;
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            out[j][i] = mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1] + mat1[2][i] * mat2[j][2];
        }
    }
}

void zpl_float33_mul_vec3(zpl_vec3 *out, zpl_f32 m[3][3], zpl_vec3 v) {
    out->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
    out->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
    out->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
}

zpl_f32 zpl_mat3_determinate(zpl_mat3 *m) {
    zpl_float3 *e = zpl_float33_m(m);
    zpl_f32 d = +e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) - e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]) +
        e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
    return d;
}

void zpl_mat3_inverse(zpl_mat3 *out, zpl_mat3 *in) {
    zpl_float3 *o = zpl_float33_m(out);
    zpl_float3 *i = zpl_float33_m(in);
    
    zpl_f32 ood = 1.0f / zpl_mat3_determinate(in);
    
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

void zpl_mat4_transpose(zpl_mat4 *m) { zpl_float44_transpose(zpl_float44_m(m)); }
void zpl_mat4_identity(zpl_mat4 *m) { zpl_float44_identity(zpl_float44_m(m)); }
void zpl_mat4_mul(zpl_mat4 *out, zpl_mat4 *m1, zpl_mat4 *m2) {
    zpl_float44_mul(zpl_float44_m(out), zpl_float44_m(m1), zpl_float44_m(m2));
}

void zpl_float44_identity(zpl_f32 m[4][4]) {
    m[0][0] = 1;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = 1;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}

void zpl_mat4_mul_vec4(zpl_vec4 *out, zpl_mat4 *m, zpl_vec4 in) { zpl_float44_mul_vec4(out, zpl_float44_m(m), in); }

zpl_mat4 *zpl_mat4_v(zpl_vec4 m[4]) { return (zpl_mat4 *)m; }
zpl_mat4 *zpl_mat4_f(zpl_f32 m[4][4]) { return (zpl_mat4 *)m; }

zpl_float4 *zpl_float44_m(zpl_mat4 *m) { return (zpl_float4 *)m; }
zpl_float4 *zpl_float44_v(zpl_vec4 m[4]) { return (zpl_float4 *)m; }
zpl_float4 *zpl_float44_16(zpl_f32 m[16]) { return (zpl_float4 *)m; }

void zpl_float44_transpose(zpl_f32 (*vec)[4]) {
    zpl_f32 tmp;
    tmp = vec[1][0];
    vec[1][0] = vec[0][1];
    vec[0][1] = tmp;
    tmp = vec[2][0];
    vec[2][0] = vec[0][2];
    vec[0][2] = tmp;
    tmp = vec[3][0];
    vec[3][0] = vec[0][3];
    vec[0][3] = tmp;
    tmp = vec[2][1];
    vec[2][1] = vec[1][2];
    vec[1][2] = tmp;
    tmp = vec[3][1];
    vec[3][1] = vec[1][3];
    vec[1][3] = tmp;
    tmp = vec[3][2];
    vec[3][2] = vec[2][3];
    vec[2][3] = tmp;
}

void zpl_float44_mul(zpl_f32 (*out)[4], zpl_f32 (*mat1)[4], zpl_f32 (*mat2)[4]) {
    int i, j;
    zpl_f32 temp1[4][4], temp2[4][4];
    if (mat1 == out) {
        zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
        mat1 = temp1;
    }
    if (mat2 == out) {
        zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
        mat2 = temp2;
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            out[j][i] =
                mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1] + mat1[2][i] * mat2[j][2] + mat1[3][i] * mat2[j][3];
        }
    }
}

void zpl_float44_mul_vec4(zpl_vec4 *out, zpl_f32 m[4][4], zpl_vec4 v) {
    out->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w;
    out->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w;
    out->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w;
    out->w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w;
}

void zpl_mat4_inverse(zpl_mat4 *out, zpl_mat4 *in) {
    zpl_float4 *o = zpl_float44_m(out);
    zpl_float4 *m = zpl_float44_m(in);
    
    zpl_f32 ood;
    
    zpl_f32 sf00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    zpl_f32 sf01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    zpl_f32 sf02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    zpl_f32 sf03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    zpl_f32 sf04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    zpl_f32 sf05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    zpl_f32 sf06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    zpl_f32 sf07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    zpl_f32 sf08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    zpl_f32 sf09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    zpl_f32 sf10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    zpl_f32 sf11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    zpl_f32 sf12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    zpl_f32 sf13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    zpl_f32 sf14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    zpl_f32 sf15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    zpl_f32 sf16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
    zpl_f32 sf17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    zpl_f32 sf18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
    
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
    
    ood = 1.0f / (m[0][0] * o[0][0] + m[0][1] * o[1][0] + m[0][2] * o[2][0] + m[0][3] * o[3][0]);
    
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

void zpl_mat4_translate(zpl_mat4 *out, zpl_vec3 v) {
    zpl_mat4_identity(out);
    out->col[3].xyz = v;
    out->col[3].w = 1;
}

void zpl_mat4_rotate(zpl_mat4 *out, zpl_vec3 v, zpl_f32 angle_radians) {
    zpl_f32 c, s;
    zpl_vec3 axis, t;
    zpl_float4 *rot;
    
    c = zpl_cos(angle_radians);
    s = zpl_sin(angle_radians);
    
    zpl_vec3_norm(&axis, v);
    zpl_vec3_mul(&t, axis, 1.0f - c);
    
    zpl_mat4_identity(out);
    rot = zpl_float44_m(out);
    
    rot[0][0] = c + t.x * axis.x;
    rot[0][1] = 0 + t.x * axis.y + s * axis.z;
    rot[0][2] = 0 + t.x * axis.z - s * axis.y;
    rot[0][3] = 0;
    
    rot[1][0] = 0 + t.y * axis.x - s * axis.z;
    rot[1][1] = c + t.y * axis.y;
    rot[1][2] = 0 + t.y * axis.z + s * axis.x;
    rot[1][3] = 0;
    
    rot[2][0] = 0 + t.z * axis.x + s * axis.y;
    rot[2][1] = 0 + t.z * axis.y - s * axis.x;
    rot[2][2] = c + t.z * axis.z;
    rot[2][3] = 0;
}

void zpl_mat4_scale(zpl_mat4 *out, zpl_vec3 v) {
    zpl_mat4_identity(out);
    out->e[0] = v.x;
    out->e[5] = v.y;
    out->e[10] = v.z;
}

void zpl_mat4_scalef(zpl_mat4 *out, zpl_f32 s) {
    zpl_mat4_identity(out);
    out->e[0] = s;
    out->e[5] = s;
    out->e[10] = s;
}

void zpl_mat4_ortho2d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top) {
    zpl_float4 *m;
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = 2.0f / (right - left);
    m[1][1] = 2.0f / (top - bottom);
    m[2][2] = -1.0f;
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
}

void zpl_mat4_ortho3d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far) {
    zpl_float4 *m;
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = +2.0f / (right - left);
    m[1][1] = +2.0f / (top - bottom);
    m[2][2] = -2.0f / (z_far - z_near);
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
    m[3][2] = -(z_far + z_near) / (z_far - z_near);
}

void zpl_mat4_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far) {
    zpl_f32 tan_half_fovy = zpl_tan(0.5f * fovy);
    zpl_mat4 zero_mat = { 0 };
    zpl_float4 *m = zpl_float44_m(out);
    *out = zero_mat;
    
    m[0][0] = 1.0f / (aspect * tan_half_fovy);
    m[1][1] = 1.0f / (tan_half_fovy);
    m[2][2] = -(z_far + z_near) / (z_far - z_near);
    m[2][3] = -1.0f;
    m[3][2] = -2.0f * z_far * z_near / (z_far - z_near);
}

void zpl_mat4_infinite_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near) {
    zpl_f32 range = zpl_tan(0.5f * fovy) * z_near;
    zpl_f32 left = -range * aspect;
    zpl_f32 right = range * aspect;
    zpl_f32 bottom = -range;
    zpl_f32 top = range;
    zpl_mat4 zero_mat = { 0 };
    zpl_float4 *m = zpl_float44_m(out);
    *out = zero_mat;
    
    m[0][0] = (2.0f * z_near) / (right - left);
    m[1][1] = (2.0f * z_near) / (top - bottom);
    m[2][2] = -1.0f;
    m[2][3] = -1.0f;
    m[3][2] = -2.0f * z_near;
}

void zpl_mat4_look_at(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up) {
    zpl_vec3 f, s, u;
    zpl_float4 *m;
    
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
    
    m[3][0] = -zpl_vec3_dot(s, eye);
    m[3][1] = -zpl_vec3_dot(u, eye);
    m[3][2] = +zpl_vec3_dot(f, eye);
}

zpl_quat zpl_quatf(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w) {
    zpl_quat q;
    q.x = x;
    q.y = y;
    q.z = z;
    q.w = w;
    return q;
}
zpl_quat zpl_quatfv(zpl_f32 e[4]) {
    zpl_quat q;
    q.x = e[0];
    q.y = e[1];
    q.z = e[2];
    q.w = e[3];
    return q;
}

zpl_quat zpl_quat_axis_angle(zpl_vec3 axis, zpl_f32 angle_radians) {
    zpl_quat q;
    zpl_vec3_norm(&q.xyz, axis);
    zpl_vec3_muleq(&q.xyz, zpl_sin(0.5f * angle_radians));
    q.w = zpl_cos(0.5f * angle_radians);
    return q;
}

zpl_quat zpl_quat_euler_angles(zpl_f32 pitch, zpl_f32 yaw, zpl_f32 roll) {
    /* TODO: Do without multiplication, i.e. make it faster */
    zpl_quat q, p, y, r;
    p = zpl_quat_axis_angle(zpl_vec3f(1, 0, 0), pitch);
    y = zpl_quat_axis_angle(zpl_vec3f(0, 1, 0), yaw);
    r = zpl_quat_axis_angle(zpl_vec3f(0, 0, 1), roll);
    
    zpl_quat_mul(&q, y, p);
    zpl_quat_muleq(&q, r);
    
    return q;
}

zpl_quat zpl_quat_identity(void) {
    zpl_quat q = { 0, 0, 0, 1 };
    return q;
}

void zpl_quat_add(zpl_quat *d, zpl_quat q0, zpl_quat q1) { zpl_vec4_add(&d->xyzw, q0.xyzw, q1.xyzw); }
void zpl_quat_sub(zpl_quat *d, zpl_quat q0, zpl_quat q1) { zpl_vec4_sub(&d->xyzw, q0.xyzw, q1.xyzw); }

void zpl_quat_mul(zpl_quat *d, zpl_quat q0, zpl_quat q1) {
    d->x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
    d->y = q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x;
    d->z = q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w;
    d->w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
}

void zpl_quat_div(zpl_quat *d, zpl_quat q0, zpl_quat q1) {
    zpl_quat iq1;
    zpl_quat_inverse(&iq1, q1);
    zpl_quat_mul(d, q0, iq1);
}

void zpl_quat_mulf(zpl_quat *d, zpl_quat q0, zpl_f32 s) { zpl_vec4_mul(&d->xyzw, q0.xyzw, s); }
void zpl_quat_divf(zpl_quat *d, zpl_quat q0, zpl_f32 s) { zpl_vec4_div(&d->xyzw, q0.xyzw, s); }

void zpl_quat_addeq(zpl_quat *d, zpl_quat q) { zpl_vec4_addeq(&d->xyzw, q.xyzw); }
void zpl_quat_subeq(zpl_quat *d, zpl_quat q) { zpl_vec4_subeq(&d->xyzw, q.xyzw); }
void zpl_quat_muleq(zpl_quat *d, zpl_quat q) { zpl_quat_mul(d, *d, q); }
void zpl_quat_diveq(zpl_quat *d, zpl_quat q) { zpl_quat_div(d, *d, q); }

void zpl_quat_muleqf(zpl_quat *d, zpl_f32 s) { zpl_vec4_muleq(&d->xyzw, s); }
void zpl_quat_diveqf(zpl_quat *d, zpl_f32 s) { zpl_vec4_diveq(&d->xyzw, s); }

zpl_f32 zpl_quat_dot(zpl_quat q0, zpl_quat q1) {
    zpl_f32 r = zpl_vec3_dot(q0.xyz, q1.xyz) + q0.w * q1.w;
    return r;
}
zpl_f32 zpl_quat_mag(zpl_quat q) {
    zpl_f32 r = zpl_sqrt(zpl_quat_dot(q, q));
    return r;
}

void zpl_quat_norm(zpl_quat *d, zpl_quat q) { zpl_quat_divf(d, q, zpl_quat_mag(q)); }
void zpl_quat_conj(zpl_quat *d, zpl_quat q) {
    d->xyz = zpl_vec3f(-q.x, -q.y, -q.z);
    d->w = q.w;
}
void zpl_quat_inverse(zpl_quat *d, zpl_quat q) {
    zpl_quat_conj(d, q);
    zpl_quat_diveqf(d, zpl_quat_dot(q, q));
}

void zpl_quat_axis(zpl_vec3 *axis, zpl_quat q) {
    zpl_quat n;
    zpl_quat_norm(&n, q);
    zpl_vec3_div(axis, n.xyz, zpl_sin(zpl_arccos(q.w)));
}

zpl_f32 zpl_quat_angle(zpl_quat q) {
    zpl_f32 mag = zpl_quat_mag(q);
    zpl_f32 c = q.w * (1.0f / mag);
    zpl_f32 angle = 2.0f * zpl_arccos(c);
    return angle;
}

zpl_f32 zpl_quat_roll(zpl_quat q) {
    return zpl_arctan2(2.0f * q.x * q.y + q.z * q.w, q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z);
}
zpl_f32 zpl_quat_pitch(zpl_quat q) {
    return zpl_arctan2(2.0f * q.y * q.z + q.w * q.x, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
}
zpl_f32 zpl_quat_yaw(zpl_quat q) { return zpl_arcsin(-2.0f * (q.x * q.z - q.w * q.y)); }

void zpl_quat_rotate_vec3(zpl_vec3 *d, zpl_quat q, zpl_vec3 v) {
    /* zpl_vec3 t = 2.0f * cross(q.xyz, v);
     * *d = q.w*t + v + cross(q.xyz, t);
     */
    zpl_vec3 t, p;
    zpl_vec3_cross(&t, q.xyz, v);
    zpl_vec3_muleq(&t, 2.0f);
    
    zpl_vec3_cross(&p, q.xyz, t);
    
    zpl_vec3_mul(d, t, q.w);
    zpl_vec3_addeq(d, v);
    zpl_vec3_addeq(d, p);
}

void zpl_mat4_from_quat(zpl_mat4 *out, zpl_quat q) {
    zpl_float4 *m;
    zpl_quat a;
    zpl_f32 xx, yy, zz, xy, xz, yz, wx, wy, wz;
    
    zpl_quat_norm(&a, q);
    xx = a.x * a.x;
    yy = a.y * a.y;
    zz = a.z * a.z;
    xy = a.x * a.y;
    xz = a.x * a.z;
    yz = a.y * a.z;
    wx = a.w * a.x;
    wy = a.w * a.y;
    wz = a.w * a.z;
    
    zpl_mat4_identity(out);
    m = zpl_float44_m(out);
    
    m[0][0] = 1.0f - 2.0f * (yy + zz);
    m[0][1] = 2.0f * (xy + wz);
    m[0][2] = 2.0f * (xz - wy);
    
    m[1][0] = 2.0f * (xy - wz);
    m[1][1] = 1.0f - 2.0f * (xx + zz);
    m[1][2] = 2.0f * (yz + wx);
    
    m[2][0] = 2.0f * (xz + wy);
    m[2][1] = 2.0f * (yz - wx);
    m[2][2] = 1.0f - 2.0f * (xx + yy);
}

void zpl_quat_from_mat4(zpl_quat *out, zpl_mat4 *mat) {
    zpl_float4 *m;
    zpl_f32 four_x_squared_minus_1, four_y_squared_minus_1, four_z_squared_minus_1, four_w_squared_minus_1,
    four_biggest_squared_minus_1;
    int biggest_index = 0;
    zpl_f32 biggest_value, mult;
    
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

zpl_f32 zpl_lerp(zpl_f32 a, zpl_f32 b, zpl_f32 t) { return a * (1.0f - t) + b * t; }
zpl_f32 zpl_unlerp(zpl_f32 t, zpl_f32 a, zpl_f32 b) { return (t - a) / (b - a); }
zpl_f32 zpl_smooth_step(zpl_f32 a, zpl_f32 b, zpl_f32 t) {
    zpl_f32 x = (t - a) / (b - a);
    return x * x * (3.0f - 2.0f * x);
}
zpl_f32 zpl_smoother_step(zpl_f32 a, zpl_f32 b, zpl_f32 t) {
    zpl_f32 x = (t - a) / (b - a);
    return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}

#define ZPL_VEC_LERPN(N, d, a, b, t)                                                                                   \
\
zpl_vec##N db;                                                                                                 \
\
zpl_vec##N##_sub(&db, b, a);                                                                                       \
\
zpl_vec##N##_muleq(&db, t);                                                                                        \
\
zpl_vec##N##_add(d, a, db)
void zpl_vec2_lerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 b, zpl_f32 t) { ZPL_VEC_LERPN(2, d, a, b, t); }
void zpl_vec3_lerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 b, zpl_f32 t) { ZPL_VEC_LERPN(3, d, a, b, t); }
void zpl_vec4_lerp(zpl_vec4 *d, zpl_vec4 a, zpl_vec4 b, zpl_f32 t) { ZPL_VEC_LERPN(4, d, a, b, t); }

#undef ZPL_VEC_LERPN

void zpl_vec2_cslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t) {
    zpl_f32 t2 = t * t;
    zpl_f32 ti = (t - 1);
    zpl_f32 ti2 = ti * ti;
    
    zpl_f32 h00 = (1 + 2 * t) * ti2;
    zpl_f32 h10 = t * ti2;
    zpl_f32 h01 = t2 * (3 - 2 * t);
    zpl_f32 h11 = t2 * ti;
    
    d->x = h00 * a.x + h10 * v0.x + h01 * b.x + h11 * v1.x;
    d->y = h00 * a.y + h10 * v0.y + h01 * b.y + h11 * v1.y;
}

void zpl_vec3_cslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t) {
    zpl_f32 t2 = t * t;
    zpl_f32 ti = (t - 1);
    zpl_f32 ti2 = ti * ti;
    
    zpl_f32 h00 = (1 + 2 * t) * ti2;
    zpl_f32 h10 = t * ti2;
    zpl_f32 h01 = t2 * (3 - 2 * t);
    zpl_f32 h11 = t2 * ti;
    
    d->x = h00 * a.x + h10 * v0.x + h01 * b.x + h11 * v1.x;
    d->y = h00 * a.y + h10 * v0.y + h01 * b.y + h11 * v1.y;
    d->z = h00 * a.z + h10 * v0.z + h01 * b.z + h11 * v1.z;
}

void zpl_vec2_dcslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t) {
    zpl_f32 t2 = t * t;
    
    zpl_f32 dh00 = 6 * t2 - 6 * t;
    zpl_f32 dh10 = 3 * t2 - 4 * t + 1;
    zpl_f32 dh01 = -6 * t2 + 6 * t;
    zpl_f32 dh11 = 3 * t2 - 2 * t;
    
    d->x = dh00 * a.x + dh10 * v0.x + dh01 * b.x + dh11 * v1.x;
    d->y = dh00 * a.y + dh10 * v0.y + dh01 * b.y + dh11 * v1.y;
}

void zpl_vec3_dcslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t) {
    zpl_f32 t2 = t * t;
    
    zpl_f32 dh00 = 6 * t2 - 6 * t;
    zpl_f32 dh10 = 3 * t2 - 4 * t + 1;
    zpl_f32 dh01 = -6 * t2 + 6 * t;
    zpl_f32 dh11 = 3 * t2 - 2 * t;
    
    d->x = dh00 * a.x + dh10 * v0.x + dh01 * b.x + dh11 * v1.x;
    d->y = dh00 * a.y + dh10 * v0.y + dh01 * b.y + dh11 * v1.y;
    d->z = dh00 * a.z + dh10 * v0.z + dh01 * b.z + dh11 * v1.z;
}

void zpl_quat_lerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) { zpl_vec4_lerp(&d->xyzw, a.xyzw, b.xyzw, t); }
void zpl_quat_nlerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
    zpl_quat_lerp(d, a, b, t);
    zpl_quat_norm(d, *d);
}

void zpl_quat_slerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
    zpl_quat x, y, z;
    zpl_f32 cos_theta, angle;
    zpl_f32 s1, s0, is;
    
    z = b;
    cos_theta = zpl_quat_dot(a, b);
    
    if (cos_theta < 0.0f) {
        z = zpl_quatf(-b.x, -b.y, -b.z, -b.w);
        cos_theta = -cos_theta;
    }
    
    if (cos_theta > 1.0f) {
        /* NOTE: Use lerp not nlerp as it's not a real angle or they are not normalized */
        zpl_quat_lerp(d, a, b, t);
    }
    
    angle = zpl_arccos(cos_theta);
    
    s1 = zpl_sin((1.0f - t) * angle);
    s0 = zpl_sin(t * angle);
    is = 1.0f / zpl_sin(angle);
    zpl_quat_mulf(&x, a, s1);
    zpl_quat_mulf(&y, z, s0);
    zpl_quat_add(d, x, y);
    zpl_quat_muleqf(d, is);
}

void zpl_quat_slerp_approx(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
    /* NOTE: Derived by taylor expanding the geometric interpolation equation
     *             Even works okay for nearly anti-parallel versors!!!
     */
    /* NOTE: Extra interations cannot be used as they require angle^4 which is not worth it to approximate */
    zpl_f32 tp = t + (1.0f - zpl_quat_dot(a, b)) / 3.0f * t * (-2.0f * t * t + 3.0f * t - 1.0f);
    zpl_quat_nlerp(d, a, b, tp);
}

void zpl_quat_nquad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
    zpl_quat x, y;
    zpl_quat_nlerp(&x, p, q, t);
    zpl_quat_nlerp(&y, a, b, t);
    zpl_quat_nlerp(d, x, y, 2.0f * t * (1.0f - t));
}

void zpl_quat_squad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
    zpl_quat x, y;
    zpl_quat_slerp(&x, p, q, t);
    zpl_quat_slerp(&y, a, b, t);
    zpl_quat_slerp(d, x, y, 2.0f * t * (1.0f - t));
}

void zpl_quat_squad_approx(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
    zpl_quat x, y;
    zpl_quat_slerp_approx(&x, p, q, t);
    zpl_quat_slerp_approx(&y, a, b, t);
    zpl_quat_slerp_approx(d, x, y, 2.0f * t * (1.0f - t));
}

zpl_rect2 zpl_rect2f(zpl_vec2 pos, zpl_vec2 dim) {
    zpl_rect2 r;
    r.pos = pos;
    r.dim = dim;
    return r;
}

zpl_rect3 zpl_rect3f(zpl_vec3 pos, zpl_vec3 dim) {
    zpl_rect3 r;
    r.pos = pos;
    r.dim = dim;
    return r;
}

int zpl_rect2_contains(zpl_rect2 a, zpl_f32 x, zpl_f32 y) {
    zpl_f32 min_x = zpl_min(a.pos.x, a.pos.x + a.dim.x);
    zpl_f32 max_x = zpl_max(a.pos.x, a.pos.x + a.dim.x);
    zpl_f32 min_y = zpl_min(a.pos.y, a.pos.y + a.dim.y);
    zpl_f32 max_y = zpl_max(a.pos.y, a.pos.y + a.dim.y);
    int result = (x >= min_x) & (x < max_x) & (y >= min_y) & (y < max_y);
    return result;
}

int zpl_rect2_contains_vec2(zpl_rect2 a, zpl_vec2 p) { return zpl_rect2_contains(a, p.x, p.y); }

int zpl_rect2_intersects(zpl_rect2 a, zpl_rect2 b) {
    zpl_rect2 r = { 0 };
    return zpl_rect2_intersection_result(a, b, &r);
}

int zpl_rect2_intersection_result(zpl_rect2 a, zpl_rect2 b, zpl_rect2 *intersection) {
    zpl_f32 a_min_x = zpl_min(a.pos.x, a.pos.x + a.dim.x);
    zpl_f32 a_max_x = zpl_max(a.pos.x, a.pos.x + a.dim.x);
    zpl_f32 a_min_y = zpl_min(a.pos.y, a.pos.y + a.dim.y);
    zpl_f32 a_max_y = zpl_max(a.pos.y, a.pos.y + a.dim.y);
    
    zpl_f32 b_min_x = zpl_min(b.pos.x, b.pos.x + b.dim.x);
    zpl_f32 b_max_x = zpl_max(b.pos.x, b.pos.x + b.dim.x);
    zpl_f32 b_min_y = zpl_min(b.pos.y, b.pos.y + b.dim.y);
    zpl_f32 b_max_y = zpl_max(b.pos.y, b.pos.y + b.dim.y);
    
    zpl_f32 x0 = zpl_max(a_min_x, b_min_x);
    zpl_f32 y0 = zpl_max(a_min_y, b_min_y);
    zpl_f32 x1 = zpl_min(a_max_x, b_max_x);
    zpl_f32 y1 = zpl_min(a_max_y, b_max_y);
    
    if ((x0 < x1) && (y0 < y1)) {
        zpl_rect2 r = zpl_rect2f(zpl_vec2f(x0, y0), zpl_vec2f(x1 - x0, y1 - y0));
        *intersection = r;
        return 1;
    } else {
        zpl_rect2 r = { 0 };
        *intersection = r;
        return 0;
    }
}