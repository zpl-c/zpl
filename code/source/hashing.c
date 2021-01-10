// file: source/hashing.c

////////////////////////////////////////////////////////////////
//
// Hashing functions
//
//

#ifdef ZPL_EDITOR
#include "../zpl.h"
#endif

ZPL_BEGIN_C_DECLS

zpl_u32 zpl_adler32(void const *data, zpl_isize len) {
    zpl_u32 const MOD_ALDER = 65521;
    zpl_u32 a = 1, b = 0;
    zpl_isize i, block_len;
    zpl_u8 const *bytes = cast(zpl_u8 const *) data;

    block_len = len % 5552;

    while (len) {
        for (i = 0; i + 7 < block_len; i += 8) {
            a += bytes[0], b += a;
            a += bytes[1], b += a;
            a += bytes[2], b += a;
            a += bytes[3], b += a;
            a += bytes[4], b += a;
            a += bytes[5], b += a;
            a += bytes[6], b += a;
            a += bytes[7], b += a;

            bytes += 8;
        }
        for (; i < block_len; i++) a += *bytes++, b += a;

        a %= MOD_ALDER, b %= MOD_ALDER;
        len -= block_len;
        block_len = 5552;
    }

    return (b << 16) | a;
}

zpl_global zpl_u32 const ZPL__CRC32_TABLE[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832,
    0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a,
    0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,
    0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab,
    0xb6662d3d, 0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01, 0x6b6b51f4,
    0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074,
    0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525,
    0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615,
    0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76,
    0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c, 0x36034af6,
    0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7,
    0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7,
    0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278,
    0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a, 0x53b39330,
    0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

zpl_u32 zpl_crc32(void const *data, zpl_isize len) {
    zpl_isize remaining;
    zpl_u32 result = ~(cast(zpl_u32) 0);
    zpl_u8 const *c = cast(zpl_u8 const *) data;
    for (remaining = len; remaining--; c++) result = (result >> 8) ^ (ZPL__CRC32_TABLE[(result ^ *c) & 0xff]);
    return ~result;
}

zpl_u32 zpl_fnv32(void const *data, zpl_isize len) {
    zpl_isize i;
    zpl_u32 h = 0x811c9dc5;
    zpl_u8 const *c = cast(zpl_u8 const *) data;

    for (i = 0; i < len; i++) h = (h * 0x01000193) ^ c[i];

    return h;
}

zpl_u64 zpl_fnv64(void const *data, zpl_isize len) {
    zpl_isize i;
    zpl_u64 h = 0xcbf29ce484222325ull;
    zpl_u8 const *c = cast(zpl_u8 const *) data;

    for (i = 0; i < len; i++) h = (h * 0x100000001b3ll) ^ c[i];

    return h;
}

zpl_u32 zpl_fnv32a(void const *data, zpl_isize len) {
    zpl_isize i;
    zpl_u32 h = 0x811c9dc5;
    zpl_u8 const *c = cast(zpl_u8 const *) data;

    for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x01000193;

    return h;
}

zpl_u64 zpl_fnv64a(void const *data, zpl_isize len) {
    zpl_isize i;
    zpl_u64 h = 0xcbf29ce484222325ull;
    zpl_u8 const *c = cast(zpl_u8 const *) data;

    for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x100000001b3ll;

    return h;
}

// base64 implementation based on https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/
//
zpl_global zpl_u8 zpl__base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/* generated table based on: */
#if 0
void zpl__base64_decode_table() {
    zpl_i32 inv[80];
    zpl_isize i;

    zpl_memset(inv, -1, zpl_size_of(inv));

    for (i=0; i < zpl_size_of(zpl__base64_chars)-1; i++) {
        inv[zpl__base64_chars[i]-43] = i;
    }
}
#endif
/* === */
zpl_global zpl_i32 zpl__base64_dec_table[] = {
    62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
    59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
    43, 44, 45, 46, 47, 48, 49, 50, 51 };

zpl_isize zpl__base64_encoded_size(zpl_isize len) {
    zpl_isize ret = len;

    if (len % 3 != 0) {
        ret += 3 - (len % 3);
    }

    ret /= 3;
    ret *= 4;

    return ret;
}

zpl_isize zpl__base64_decoded_size(void const *data) {
    zpl_isize len, ret, i;
    const zpl_u8 *s = cast(const zpl_u8 *)data;

    if (s == NULL) {
        return 0;
    }

    len = zpl_strlen(cast(const char*)s);
    ret = len / 4 * 3;

    for (i=len; i-- > 0;) {
        if (s[i] == '=') {
            ret--;
        } else {
            break;
        }
    }

    return ret;
}

zpl_b32 zpl__base64_valid_char(zpl_u8 c) {
    if (c >= '0' && c <= '9')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= 'a' && c <= 'z')
        return true;
    if (c == '+' || c == '/' || c == '=')
        return true;

    return false;
}

zpl_u8 *zpl_base64_encode(zpl_allocator a, void const *data, zpl_isize len) {
    const zpl_u8 *s = cast(const zpl_u8*)data;
    zpl_u8 *ret = NULL;
    zpl_isize enc_len, i, j, v;

    if (data == NULL || len == 0) {
        return NULL;
    }

    enc_len = zpl__base64_encoded_size(len);
    ret = cast(zpl_u8 *)zpl_alloc(a, enc_len+1);
    ret[enc_len] = 0;

    for (i=0, j=0; i < len; i+=3, j+=4) {
        v = s[i];
        v = (i+1 < len) ? (v << 8 | s[i+1]) : (v << 8);
        v = (i+2 < len) ? (v << 8 | s[i+2]) : (v << 8);

        ret[j] = zpl__base64_chars[(v >> 18) & 0x3F];
        ret[j+1] = zpl__base64_chars[(v >> 12) & 0x3F];

        if (i+1 < len)
            ret[j+2] = zpl__base64_chars[(v >> 6) & 0x3F];

        else ret[j+2] = '=';

        if (i+2 < len)
            ret[j+3] = zpl__base64_chars[v & 0x3F];

        else ret[j+3] = '=';

    }

    return ret;
}

zpl_u8 *zpl_base64_decode(zpl_allocator a, void const *data, zpl_isize len) {
    const zpl_u8 *s = cast(const zpl_u8*)data;
    zpl_u8 *ret = NULL;
    zpl_isize alen, i, j, v;

    if (data == NULL) {
        return NULL;
    }

    alen = zpl__base64_decoded_size(s);
    ret = cast(zpl_u8 *)zpl_alloc(a, alen+1);

    ZPL_ASSERT_NOT_NULL(ret);

    ret[alen] = 0;

    for (i=0; i<len; i++) {
        if (!zpl__base64_valid_char(s[i]))
            return NULL;
    }

    for (i=0, j=0; i<len; i+=4, j+=3) {
        v = zpl__base64_dec_table[s[i]-43];
        v = (v << 6) | zpl__base64_dec_table[s[i+1]-43];
        v = (s[i+2] == '=') ? (v << 6) : ((v << 6) | zpl__base64_dec_table[s[i+2]-43]);
        v = (s[i+3] == '=') ? (v << 6) : ((v << 6) | zpl__base64_dec_table[s[i+3]-43]);

        ret[j] = (v >> 16) & 0xFF;

        if (s[i+2] != '=')
            ret[j+1] = (v >> 8) & 0xFF;

        if (s[i+3] != '=')
            ret[j+2] = v & 0xFF;
    }

    return ret;
}

zpl_u32 zpl_murmur32_seed(void const *data, zpl_isize len, zpl_u32 seed) {
    zpl_u32 const c1 = 0xcc9e2d51;
    zpl_u32 const c2 = 0x1b873593;
    zpl_u32 const r1 = 15;
    zpl_u32 const r2 = 13;
    zpl_u32 const m = 5;
    zpl_u32 const n = 0xe6546b64;

    zpl_isize i, nblocks = len / 4;
    zpl_u32 hash = seed, k1 = 0;
    zpl_u32 const *blocks = cast(zpl_u32 const *) data;
    zpl_u8 const *tail = cast(zpl_u8 const *)(data) + nblocks * 4;

    for (i = 0; i < nblocks; i++) {
        zpl_u32 k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    switch (len & 3) {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1:
        k1 ^= tail[0];

        k1 *= c1;
        k1 = (k1 << r1) | (k1 >> (32 - r1));
        k1 *= c2;
        hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

zpl_u64 zpl_murmur64_seed(void const *data_, zpl_isize len, zpl_u64 seed) {
    zpl_u64 const m = 0xc6a4a7935bd1e995ULL;
    zpl_i32 const r = 47;

    zpl_u64 h = seed ^ (len * m);

    zpl_u64 const *data = cast(zpl_u64 const *) data_;
    zpl_u8 const *data2 = cast(zpl_u8 const *) data_;
    zpl_u64 const *end = data + (len / 8);

    while (data != end) {
        zpl_u64 k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    switch (len & 7) {
        case 7: h ^= cast(zpl_u64)(data2[6]) << 48;
        case 6: h ^= cast(zpl_u64)(data2[5]) << 40;
        case 5: h ^= cast(zpl_u64)(data2[4]) << 32;
        case 4: h ^= cast(zpl_u64)(data2[3]) << 24;
        case 3: h ^= cast(zpl_u64)(data2[2]) << 16;
        case 2: h ^= cast(zpl_u64)(data2[1]) << 8;
        case 1: h ^= cast(zpl_u64)(data2[0]); 
                h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

ZPL_END_C_DECLS
