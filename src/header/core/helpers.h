/* Various macro based helpers */

#ifndef cast
    #define cast(Type) (Type)
#endif

#ifndef zpl_size_of
    #define zpl_size_of(x) (zpl_isize)(sizeof(x))
#endif

#ifndef zpl_count_of
    #define zpl_count_of(x) ((zpl_size_of(x) / zpl_size_of(0 [x])) / ((zpl_isize)(!(zpl_size_of(x) % zpl_size_of(0 [x])))))
#endif

#ifndef zpl_offset_of
#ifdef _MSC_VER
    #define zpl_offset_of(Type, element) ((zpl_isize) & (((Type *)0)->element))
#else
    #define zpl_offset_of(Type, element) __builtin_offsetof(Type, element)
#endif
#endif

#if defined(__cplusplus)
    #ifndef zpl_align_of
        #if __cplusplus >= 201103L
            #define zpl_align_of(Type) (zpl_isize)alignof(Type)
        #else
            extern "C++" {
                template <typename T> struct zpl_alignment_trick {
                    char c;
                    T member;
                };
            }
            #define zpl_align_of(Type) zpl_offset_of(zpl_alignment_trick<Type>, member)
        #endif
    #endif
#else
    #ifndef zpl_align_of
        #define zpl_align_of(Type) \
        zpl_offset_of(             \
        struct {                   \
            char c;                \
            Type member;           \
        },                         \
        member)
    #endif
#endif

#ifndef zpl_swap
    #define zpl_swap(Type, a, b) \
    do {                         \
        Type tmp = (a);          \
        (a) = (b);               \
        (b) = tmp;               \
    } while (0)
#endif



#ifndef zpl_global
    #define zpl_global static        // Global variables
#endif

#ifndef zpl_internal
    #define zpl_internal static      // Internal linkage
#endif

#ifndef zpl_local_persist
    #define zpl_local_persist static // Local Persisting variables
#endif

#ifndef zpl_unused
    #if defined(_MSC_VER)
        #define zpl_unused(x) (__pragma(warning(suppress : 4100))(x))
    #elif defined(__GCC__)
        #define zpl_unused(x) __attribute__((__unused__))(x)
    #else
        #define zpl_unused(x) ((void)(zpl_size_of(x)))
    #endif
#endif


#ifndef ZPL_JOIN_MACROS
    #define ZPL_JOIN_MACROS

    #define ZPL_JOIN2 ZPL_CONCAT
    #define ZPL_JOIN3(a, b, c) ZPL_JOIN2(ZPL_JOIN2(a, b), c)
    #define ZPL_JOIN4(a, b, c, d) ZPL_JOIN2(ZPL_JOIN2(ZPL_JOIN2(a, b), c), d)
#endif

#ifndef ZPL_BIT
    #define ZPL_BIT(x) (1 << (x))
#endif

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

#ifndef zpl_clamp
    #define zpl_clamp(x, lower, upper) zpl_min(zpl_max((x), (lower)), (upper))
#endif

#ifndef zpl_clamp01
    #define zpl_clamp01(x) zpl_clamp((x), 0, 1)
#endif

#ifndef zpl_is_between
    #define zpl_is_between(x, lower, upper) (((lower) <= (x)) && ((x) <= (upper)))
#endif

#ifndef zpl_abs
    #define zpl_abs(x) ((x) < 0 ? -(x) : (x))
#endif

#ifndef hard_cast
    #define hard_cast(type) *cast(type) &
#endif

// WARN(ZaKlaus): Supported only on GCC via GNU extensions!!!
#ifndef zpl_lambda
    #define zpl_lambda(b_) ({ b_ _; })
#endif

#ifndef zpl_when
    #define zpl_when(init, type, name) \
    type name = init;                  \
    if (name)
#endif

/* NOTE: Very useful bit setting */
#ifndef ZPL_MASK_SET
    #define ZPL_MASK_SET(var, set, mask) \
    do {                                 \
        if (set)                         \
        (var) |= (mask);                 \
        else                             \
        (var) &= ~(mask);                \
    } while (0)
#endif

// Multiline string literals in C99!
#ifndef ZPL_MULTILINE
    #define ZPL_MULTILINE(...) #__VA_ARGS__
#endif
