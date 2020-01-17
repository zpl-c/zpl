#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

typedef struct zpl_random {
    zpl_u32 offsets[8];
    zpl_u32 value;
} zpl_random;

// NOTE: Generates from numerous sources to produce a decent pseudo-random seed
ZPL_DEF void      zpl_random_init(zpl_random *r);
ZPL_DEF zpl_u32   zpl_random_gen_u32(zpl_random *r);
ZPL_DEF zpl_u32   zpl_random_gen_u32_unique(zpl_random *r);
ZPL_DEF zpl_u64   zpl_random_gen_u64(zpl_random *r); // NOTE: (zpl_random_gen_u32() << 32) | zpl_random_gen_u32()
ZPL_DEF zpl_isize zpl_random_gen_isize(zpl_random *r);
ZPL_DEF zpl_i64   zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc);
ZPL_DEF zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc);
ZPL_DEF zpl_f64   zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc);
