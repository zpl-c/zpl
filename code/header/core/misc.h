// file: header/core/misc.h

/** @file misc.c
@brief Various other stuff
@defgroup misc Various other stuff

 Methods that don't belong anywhere but are still very useful in many occasions.

 @{
 */

ZPL_BEGIN_C_DECLS

ZPL_DEF void zpl_yield(void);

//! Returns allocated buffer
ZPL_DEF const char *zpl_get_env(const char *name);
ZPL_DEF const char *zpl_get_env_buf(const char *name);
ZPL_DEF zpl_string  zpl_get_env_str(const char *name);
ZPL_DEF void        zpl_set_env(const char *name, const char *value);
ZPL_DEF void        zpl_unset_env(const char *name);

ZPL_DEF zpl_u32    zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer);
ZPL_DEF zpl_string zpl_system_command_str(const char *command, zpl_allocator backing);

ZPL_DEF_INLINE zpl_u16 zpl_endian_swap16(zpl_u16 i);
ZPL_DEF_INLINE zpl_u32 zpl_endian_swap32(zpl_u32 i);
ZPL_DEF_INLINE zpl_u64 zpl_endian_swap64(zpl_u64 i);

ZPL_DEF_INLINE zpl_isize zpl_count_set_bits(zpl_u64 mask);

//! @}
//$$

ZPL_IMPL_INLINE zpl_u16 zpl_endian_swap16(zpl_u16 i) {
    return (i>>8) | (i<<8);
}

ZPL_IMPL_INLINE zpl_u32 zpl_endian_swap32(zpl_u32 i) {
    return (i>>24) |(i<<24) |
        ((i&0x00ff0000u)>>8)  | ((i&0x0000ff00u)<<8);
}

ZPL_IMPL_INLINE zpl_u64 zpl_endian_swap64(zpl_u64 i) {
    return (i>>56) | (i<<56) |
        ((i&0x00ff000000000000ull)>>40) | ((i&0x000000000000ff00ull)<<40) |
        ((i&0x0000ff0000000000ull)>>24) | ((i&0x0000000000ff0000ull)<<24) |
        ((i&0x000000ff00000000ull)>>8)  | ((i&0x00000000ff000000ull)<<8);
}

ZPL_IMPL_INLINE zpl_i32 zpl_next_pow2(zpl_i32 x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

ZPL_IMPL_INLINE void zpl_bit_set(zpl_u32* x, zpl_u32 bit) { *x = *x | (1 << bit); }
ZPL_IMPL_INLINE zpl_b8 zpl_bit_get(zpl_u32 x, zpl_u32 bit) { return (x & (1 << bit)); }
ZPL_IMPL_INLINE void zpl_bit_reset(zpl_u32* x, zpl_u32 bit) { *x = *x & ~(1 << bit); }

ZPL_IMPL_INLINE zpl_isize zpl_count_set_bits(zpl_u64 mask) {
    zpl_isize count = 0;
    while (mask) {
        count += (mask & 1);
        mask >>= 1;
    }
    return count;
}

ZPL_END_C_DECLS
