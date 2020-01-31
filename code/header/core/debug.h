// file: header/core/debug.h

/* Debugging stuff */
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

#ifndef ZPL_DEBUG_TRAP
    #if defined(_MSC_VER)
        #if _MSC_VER < 1300
            #define ZPL_DEBUG_TRAP( ) __asm int 3 /* Trap to debugger! */
        #else
            #define ZPL_DEBUG_TRAP( ) __debugbreak( )
        #endif
    #else
        #define ZPL_DEBUG_TRAP( ) __builtin_trap( )
    #endif
#endif

#ifndef ZPL_ASSERT_MSG
    #define ZPL_ASSERT_MSG(cond, msg, ...)                                                                             \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            zpl_assert_handler(#cond, __FILE__, cast(zpl_i64) __LINE__, msg, ##__VA_ARGS__);                           \
            ZPL_DEBUG_TRAP( );                                                                                         \
        }                                                                                                              \
    } while (0)
#endif

#ifndef ZPL_ASSERT
    #define ZPL_ASSERT(cond) ZPL_ASSERT_MSG(cond, NULL)
#endif

#ifndef ZPL_ASSERT_NOT_NULL
    #define ZPL_ASSERT_NOT_NULL(ptr) ZPL_ASSERT_MSG((ptr) != NULL, #ptr " must not be NULL")
#endif

// NOTE: Things that shouldn't happen with a message!
#ifndef ZPL_PANIC
    #define ZPL_PANIC(msg, ...) ZPL_ASSERT_MSG(0, msg, ##__VA_ARGS__)
#endif

#ifndef ZPL_NOT_IMPLEMENTED
    #define ZPL_NOT_IMPLEMENTED ZPL_PANIC("not implemented")
#endif

/* Functions */

ZPL_DEF void    zpl_assert_handler(char const *condition, char const *file, zpl_i32 line, char const *msg, ...);
ZPL_DEF zpl_i32 zpl_assert_crash(char const *condition);

ZPL_END_C_DECLS
