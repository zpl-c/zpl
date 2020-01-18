/*
	This file provides C++ math extensions for the math module.
	Make sure ZPL is included first before including this file.
*/

#if defined(__cplusplus)
inline bool operator==(zpl_vec2 a, zpl_vec2 b) { return (a.x == b.x) && (a.y == b.y); }
inline bool operator!=(zpl_vec2 a, zpl_vec2 b) { return !operator==(a, b); }

inline zpl_vec2 operator+(zpl_vec2 a) { return a; }
inline zpl_vec2 operator-(zpl_vec2 a) { zpl_vec2 r = {-a.x, -a.y}; return r; }

inline zpl_vec2 operator+(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_add(&r, a, b); return r; }
inline zpl_vec2 operator-(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_sub(&r, a, b); return r; }

inline zpl_vec2 operator*(zpl_vec2 a, float scalar) { zpl_vec2 r; zpl_vec2_mul(&r, a, scalar); return r; }
inline zpl_vec2 operator*(float scalar, zpl_vec2 a) { return operator*(a, scalar); }

inline zpl_vec2 operator/(zpl_vec2 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zpl_vec2 operator*(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x*b.x, a.y*b.y}; return r; }
inline zpl_vec2 operator/(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x/b.x, a.y/b.y}; return r; }

inline zpl_vec2 &operator+=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a + b); }
inline zpl_vec2 &operator-=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a - b); }
inline zpl_vec2 &operator*=(zpl_vec2 &a, float scalar) { return (a = a * scalar); }
inline zpl_vec2 &operator/=(zpl_vec2 &a, float scalar) { return (a = a / scalar); }


inline bool operator==(zpl_vec3 a, zpl_vec3 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
inline bool operator!=(zpl_vec3 a, zpl_vec3 b) { return !operator==(a, b); }

inline zpl_vec3 operator+(zpl_vec3 a) { return a; }
inline zpl_vec3 operator-(zpl_vec3 a) { zpl_vec3 r = {-a.x, -a.y, -a.z}; return r; }

inline zpl_vec3 operator+(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_add(&r, a, b); return r; }
inline zpl_vec3 operator-(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_sub(&r, a, b); return r; }

inline zpl_vec3 operator*(zpl_vec3 a, float scalar) { zpl_vec3 r; zpl_vec3_mul(&r, a, scalar); return r; }
inline zpl_vec3 operator*(float scalar, zpl_vec3 a) { return operator*(a, scalar); }

inline zpl_vec3 operator/(zpl_vec3 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zpl_vec3 operator*(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x*b.x, a.y*b.y, a.z*b.z}; return r; }
inline zpl_vec3 operator/(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x/b.x, a.y/b.y, a.z/b.z}; return r; }

inline zpl_vec3 &operator+=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a + b); }
inline zpl_vec3 &operator-=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a - b); }
inline zpl_vec3 &operator*=(zpl_vec3 &a, float scalar) { return (a = a * scalar); }
inline zpl_vec3 &operator/=(zpl_vec3 &a, float scalar) { return (a = a / scalar); }


inline bool operator==(zpl_vec4 a, zpl_vec4 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w); }
inline bool operator!=(zpl_vec4 a, zpl_vec4 b) { return !operator==(a, b); }

inline zpl_vec4 operator+(zpl_vec4 a) { return a; }
inline zpl_vec4 operator-(zpl_vec4 a) { zpl_vec4 r = {-a.x, -a.y, -a.z, -a.w}; return r; }

inline zpl_vec4 operator+(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_add(&r, a, b); return r; }
inline zpl_vec4 operator-(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_sub(&r, a, b); return r; }

inline zpl_vec4 operator*(zpl_vec4 a, float scalar) { zpl_vec4 r; zpl_vec4_mul(&r, a, scalar); return r; }
inline zpl_vec4 operator*(float scalar, zpl_vec4 a) { return operator*(a, scalar); }

inline zpl_vec4 operator/(zpl_vec4 a, float scalar) { return operator*(a, 1.0f/scalar); }

/* Hadamard Product */
inline zpl_vec4 operator*(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return r; }
inline zpl_vec4 operator/(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return r; }

inline zpl_vec4 &operator+=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a + b); }
inline zpl_vec4 &operator-=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a - b); }
inline zpl_vec4 &operator*=(zpl_vec4 &a, float scalar) { return (a = a * scalar); }
inline zpl_vec4 &operator/=(zpl_vec4 &a, float scalar) { return (a = a / scalar); }


inline zpl_mat2 operator+(zpl_mat2 const &a, zpl_mat2 const &b) {
    int i, j;
    zpl_mat2 r = {0};
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++)
            r.e[2*j+i] = a.e[2*j+i] + b.e[2*j+i];
    }
    return r;
}

inline zpl_mat2 operator-(zpl_mat2 const &a, zpl_mat2 const &b) {
    int i, j;
    zpl_mat2 r = {0};
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++)
            r.e[2*j+i] = a.e[2*j+i] - b.e[2*j+i];
    }
    return r;
}

inline zpl_mat2 operator*(zpl_mat2 const &a, zpl_mat2 const &b) { zpl_mat2 r; zpl_mat2_mul(&r, (zpl_mat2 *)&a, (zpl_mat2 *)&b); return r; }
inline zpl_vec2 operator*(zpl_mat2 const &a, zpl_vec2 v) { zpl_vec2 r; zpl_mat2_mul_vec2(&r, (zpl_mat2 *)&a, v); return r; }
inline zpl_mat2 operator*(zpl_mat2 const &a, float scalar) {
    zpl_mat2 r = {0};
    int i;
    for (i = 0; i < 2*2; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zpl_mat2 operator*(float scalar, zpl_mat2 const &a) { return operator*(a, scalar); }
inline zpl_mat2 operator/(zpl_mat2 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zpl_mat2& operator+=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a + b); }
inline zpl_mat2& operator-=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a - b); }
inline zpl_mat2& operator*=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a * b); }



inline zpl_mat3 operator+(zpl_mat3 const &a, zpl_mat3 const &b) {
    int i, j;
    zpl_mat3 r = {0};
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++)
            r.e[3*j+i] = a.e[3*j+i] + b.e[3*j+i];
    }
    return r;
}

inline zpl_mat3 operator-(zpl_mat3 const &a, zpl_mat3 const &b) {
    int i, j;
    zpl_mat3 r = {0};
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++)
            r.e[3*j+i] = a.e[3*j+i] - b.e[3*j+i];
    }
    return r;
}

inline zpl_mat3 operator*(zpl_mat3 const &a, zpl_mat3 const &b) { zpl_mat3 r; zpl_mat3_mul(&r, (zpl_mat3 *)&a, (zpl_mat3 *)&b); return r; }
inline zpl_vec3 operator*(zpl_mat3 const &a, zpl_vec3 v) { zpl_vec3 r; zpl_mat3_mul_vec3(&r, (zpl_mat3 *)&a, v); return r; } inline zpl_mat3 operator*(zpl_mat3 const &a, float scalar) {
    zpl_mat3 r = {0};
    int i;
    for (i = 0; i < 3*3; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zpl_mat3 operator*(float scalar, zpl_mat3 const &a) { return operator*(a, scalar); }
inline zpl_mat3 operator/(zpl_mat3 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zpl_mat3& operator+=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a + b); }
inline zpl_mat3& operator-=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a - b); }
inline zpl_mat3& operator*=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a * b); }



inline zpl_mat4 operator+(zpl_mat4 const &a, zpl_mat4 const &b) {
    int i, j;
    zpl_mat4 r = {0};
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++)
            r.e[4*j+i] = a.e[4*j+i] + b.e[4*j+i];
    }
    return r;
}

inline zpl_mat4 operator-(zpl_mat4 const &a, zpl_mat4 const &b) {
    int i, j;
    zpl_mat4 r = {0};
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++)
            r.e[4*j+i] = a.e[4*j+i] - b.e[4*j+i];
    }
    return r;
}

inline zpl_mat4 operator*(zpl_mat4 const &a, zpl_mat4 const &b) { zpl_mat4 r; zpl_mat4_mul(&r, (zpl_mat4 *)&a, (zpl_mat4 *)&b); return r; }
inline zpl_vec4 operator*(zpl_mat4 const &a, zpl_vec4 v) { zpl_vec4 r; zpl_mat4_mul_vec4(&r, (zpl_mat4 *)&a, v); return r; }
inline zpl_mat4 operator*(zpl_mat4 const &a, float scalar) {
    zpl_mat4 r = {0};
    int i;
    for (i = 0; i < 4*4; i++) r.e[i] = a.e[i] * scalar;
    return r;
}
inline zpl_mat4 operator*(float scalar, zpl_mat4 const &a) { return operator*(a, scalar); }
inline zpl_mat4 operator/(zpl_mat4 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

inline zpl_mat4& operator+=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a + b); }
inline zpl_mat4& operator-=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a - b); }
inline zpl_mat4& operator*=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a * b); }



inline bool operator==(zpl_quat a, zpl_quat b) { return a.xyzw == b.xyzw; }
inline bool operator!=(zpl_quat a, zpl_quat b) { return !operator==(a, b); }

inline zpl_quat operator+(zpl_quat q) { return q; }
inline zpl_quat operator-(zpl_quat q) { return zpl_quatf(-q.x, -q.y, -q.z, -q.w); }

inline zpl_quat operator+(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_add(&r, a, b); return r; }
inline zpl_quat operator-(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_sub(&r, a, b); return r; }

inline zpl_quat operator*(zpl_quat a, zpl_quat b)  { zpl_quat r; zpl_quat_mul(&r, a, b); return r; }
inline zpl_quat operator*(zpl_quat q, float s) { zpl_quat r; zpl_quat_mulf(&r, q, s); return r; }
inline zpl_quat operator*(float s, zpl_quat q) { return operator*(q, s); }
inline zpl_quat operator/(zpl_quat q, float s) { zpl_quat r; zpl_quat_divf(&r, q, s); return r; }

inline zpl_quat &operator+=(zpl_quat &a, zpl_quat b) { zpl_quat_addeq(&a, b); return a; }
inline zpl_quat &operator-=(zpl_quat &a, zpl_quat b) { zpl_quat_subeq(&a, b); return a; }
inline zpl_quat &operator*=(zpl_quat &a, zpl_quat b) { zpl_quat_muleq(&a, b); return a; }
inline zpl_quat &operator/=(zpl_quat &a, zpl_quat b) { zpl_quat_diveq(&a, b); return a; }

inline zpl_quat &operator*=(zpl_quat &a, float b) { zpl_quat_muleqf(&a, b); return a; }
inline zpl_quat &operator/=(zpl_quat &a, float b) { zpl_quat_diveqf(&a, b); return a; }

/* Rotate v by a */
inline zpl_vec3 operator*(zpl_quat q, zpl_vec3 v) { zpl_vec3 r; zpl_quat_rotate_vec3(&r, q, v); return r; }

#endif
