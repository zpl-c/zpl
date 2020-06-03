// file: header/hashing.h

/** @file hashing.c
@brief Hashing and Checksum Functions
@defgroup hashing Hashing and Checksum Functions

Several hashing methods used by ZPL internally but possibly useful outside of it. Contains: adler32, crc32/64, fnv32/64/a and murmur32/64

@{
*/

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

ZPL_DEF zpl_u32 zpl_adler32(void const *data, zpl_isize len);

ZPL_DEF zpl_u32 zpl_crc32(void const *data, zpl_isize len);
ZPL_DEF zpl_u64 zpl_crc64(void const *data, zpl_isize len);

// These use FNV-1 algorithm
ZPL_DEF zpl_u32 zpl_fnv32(void const *data, zpl_isize len);
ZPL_DEF zpl_u64 zpl_fnv64(void const *data, zpl_isize len);
ZPL_DEF zpl_u32 zpl_fnv32a(void const *data, zpl_isize len);
ZPL_DEF zpl_u64 zpl_fnv64a(void const *data, zpl_isize len);

ZPL_DEF zpl_u8 *zpl_base64_encode(zpl_allocator a, void const *data, zpl_isize len);
ZPL_DEF zpl_u8 *zpl_base64_decode(zpl_allocator a, void const *data, zpl_isize len);

//! Based on MurmurHash3
ZPL_DEF zpl_u32 zpl_murmur32_seed(void const *data, zpl_isize len, zpl_u32 seed);

//! Based on MurmurHash2
ZPL_DEF zpl_u64 zpl_murmur64_seed(void const *data, zpl_isize len, zpl_u64 seed);

//! Default seed of 0x9747b28c
ZPL_DEF_INLINE zpl_u32 zpl_murmur32(void const *data, zpl_isize len);

//! Default seed of 0x9747b28c
ZPL_DEF_INLINE zpl_u64 zpl_murmur64(void const *data, zpl_isize len);

//! @}

ZPL_IMPL_INLINE zpl_u32 zpl_murmur32(void const *data, zpl_isize len) { return zpl_murmur32_seed(data, len, 0x9747b28c); }
ZPL_IMPL_INLINE zpl_u64 zpl_murmur64(void const *data, zpl_isize len) { return zpl_murmur64_seed(data, len, 0x9747b28c); }

ZPL_END_C_DECLS
