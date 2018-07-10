////////////////////////////////////////////////////////////////
//
// Hashing and Checksum Functions
//
//

ZPL_EXTERN u32 zpl_adler32(void const *data, isize len);

ZPL_EXTERN u32 zpl_crc32(void const *data, isize len);
ZPL_EXTERN u64 zpl_crc64(void const *data, isize len);

ZPL_EXTERN u32 zpl_fnv32(void const *data, isize len);
ZPL_EXTERN u64 zpl_fnv64(void const *data, isize len);
ZPL_EXTERN u32 zpl_fnv32a(void const *data, isize len);
ZPL_EXTERN u64 zpl_fnv64a(void const *data, isize len);

// NOTE: Default seed of 0x9747b28c
// NOTE: I prefer using murmur64 for most hashes
ZPL_EXTERN u32 zpl_murmur32(void const *data, isize len);
ZPL_EXTERN u64 zpl_murmur64(void const *data, isize len);

ZPL_EXTERN u32 zpl_murmur32_seed(void const *data, isize len, u32 seed);
ZPL_EXTERN u64 zpl_murmur64_seed(void const *data, isize len, u64 seed);

//!!

////////////////////////////////////////////////////////////////
//
// Hashing functions
//
//

u32 zpl_adler32(void const *data, isize len) {
    u32 const MOD_ALDER = 65521;
    u32 a = 1, b = 0;
    isize i, block_len;
    u8 const *bytes = cast(u8 const *) data;

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

zpl_global u32 const zpl__CRC32_TABLE[256] = {
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

zpl_global u64 const zpl__CRC64_TABLE[256] = {
    0x0000000000000000ull, 0x42f0e1eba9ea3693ull, 0x85e1c3d753d46d26ull, 0xc711223cfa3e5bb5ull, 0x493366450e42ecdfull,
    0x0bc387aea7a8da4cull, 0xccd2a5925d9681f9ull, 0x8e224479f47cb76aull, 0x9266cc8a1c85d9beull, 0xd0962d61b56fef2dull,
    0x17870f5d4f51b498ull, 0x5577eeb6e6bb820bull, 0xdb55aacf12c73561ull, 0x99a54b24bb2d03f2ull, 0x5eb4691841135847ull,
    0x1c4488f3e8f96ed4ull, 0x663d78ff90e185efull, 0x24cd9914390bb37cull, 0xe3dcbb28c335e8c9ull, 0xa12c5ac36adfde5aull,
    0x2f0e1eba9ea36930ull, 0x6dfeff5137495fa3ull, 0xaaefdd6dcd770416ull, 0xe81f3c86649d3285ull, 0xf45bb4758c645c51ull,
    0xb6ab559e258e6ac2ull, 0x71ba77a2dfb03177ull, 0x334a9649765a07e4ull, 0xbd68d2308226b08eull, 0xff9833db2bcc861dull,
    0x388911e7d1f2dda8ull, 0x7a79f00c7818eb3bull, 0xcc7af1ff21c30bdeull, 0x8e8a101488293d4dull, 0x499b3228721766f8ull,
    0x0b6bd3c3dbfd506bull, 0x854997ba2f81e701ull, 0xc7b97651866bd192ull, 0x00a8546d7c558a27ull, 0x4258b586d5bfbcb4ull,
    0x5e1c3d753d46d260ull, 0x1cecdc9e94ace4f3ull, 0xdbfdfea26e92bf46ull, 0x990d1f49c77889d5ull, 0x172f5b3033043ebfull,
    0x55dfbadb9aee082cull, 0x92ce98e760d05399ull, 0xd03e790cc93a650aull, 0xaa478900b1228e31ull, 0xe8b768eb18c8b8a2ull,
    0x2fa64ad7e2f6e317ull, 0x6d56ab3c4b1cd584ull, 0xe374ef45bf6062eeull, 0xa1840eae168a547dull, 0x66952c92ecb40fc8ull,
    0x2465cd79455e395bull, 0x3821458aada7578full, 0x7ad1a461044d611cull, 0xbdc0865dfe733aa9ull, 0xff3067b657990c3aull,
    0x711223cfa3e5bb50ull, 0x33e2c2240a0f8dc3ull, 0xf4f3e018f031d676ull, 0xb60301f359dbe0e5ull, 0xda050215ea6c212full,
    0x98f5e3fe438617bcull, 0x5fe4c1c2b9b84c09ull, 0x1d14202910527a9aull, 0x93366450e42ecdf0ull, 0xd1c685bb4dc4fb63ull,
    0x16d7a787b7faa0d6ull, 0x5427466c1e109645ull, 0x4863ce9ff6e9f891ull, 0x0a932f745f03ce02ull, 0xcd820d48a53d95b7ull,
    0x8f72eca30cd7a324ull, 0x0150a8daf8ab144eull, 0x43a04931514122ddull, 0x84b16b0dab7f7968ull, 0xc6418ae602954ffbull,
    0xbc387aea7a8da4c0ull, 0xfec89b01d3679253ull, 0x39d9b93d2959c9e6ull, 0x7b2958d680b3ff75ull, 0xf50b1caf74cf481full,
    0xb7fbfd44dd257e8cull, 0x70eadf78271b2539ull, 0x321a3e938ef113aaull, 0x2e5eb66066087d7eull, 0x6cae578bcfe24bedull,
    0xabbf75b735dc1058ull, 0xe94f945c9c3626cbull, 0x676dd025684a91a1ull, 0x259d31cec1a0a732ull, 0xe28c13f23b9efc87ull,
    0xa07cf2199274ca14ull, 0x167ff3eacbaf2af1ull, 0x548f120162451c62ull, 0x939e303d987b47d7ull, 0xd16ed1d631917144ull,
    0x5f4c95afc5edc62eull, 0x1dbc74446c07f0bdull, 0xdaad56789639ab08ull, 0x985db7933fd39d9bull, 0x84193f60d72af34full,
    0xc6e9de8b7ec0c5dcull, 0x01f8fcb784fe9e69ull, 0x43081d5c2d14a8faull, 0xcd2a5925d9681f90ull, 0x8fdab8ce70822903ull,
    0x48cb9af28abc72b6ull, 0x0a3b7b1923564425ull, 0x70428b155b4eaf1eull, 0x32b26afef2a4998dull, 0xf5a348c2089ac238ull,
    0xb753a929a170f4abull, 0x3971ed50550c43c1ull, 0x7b810cbbfce67552ull, 0xbc902e8706d82ee7ull, 0xfe60cf6caf321874ull,
    0xe224479f47cb76a0ull, 0xa0d4a674ee214033ull, 0x67c58448141f1b86ull, 0x253565a3bdf52d15ull, 0xab1721da49899a7full,
    0xe9e7c031e063acecull, 0x2ef6e20d1a5df759ull, 0x6c0603e6b3b7c1caull, 0xf6fae5c07d3274cdull, 0xb40a042bd4d8425eull,
    0x731b26172ee619ebull, 0x31ebc7fc870c2f78ull, 0xbfc9838573709812ull, 0xfd39626eda9aae81ull, 0x3a28405220a4f534ull,
    0x78d8a1b9894ec3a7ull, 0x649c294a61b7ad73ull, 0x266cc8a1c85d9be0ull, 0xe17dea9d3263c055ull, 0xa38d0b769b89f6c6ull,
    0x2daf4f0f6ff541acull, 0x6f5faee4c61f773full, 0xa84e8cd83c212c8aull, 0xeabe6d3395cb1a19ull, 0x90c79d3fedd3f122ull,
    0xd2377cd44439c7b1ull, 0x15265ee8be079c04ull, 0x57d6bf0317edaa97ull, 0xd9f4fb7ae3911dfdull, 0x9b041a914a7b2b6eull,
    0x5c1538adb04570dbull, 0x1ee5d94619af4648ull, 0x02a151b5f156289cull, 0x4051b05e58bc1e0full, 0x87409262a28245baull,
    0xc5b073890b687329ull, 0x4b9237f0ff14c443ull, 0x0962d61b56fef2d0ull, 0xce73f427acc0a965ull, 0x8c8315cc052a9ff6ull,
    0x3a80143f5cf17f13ull, 0x7870f5d4f51b4980ull, 0xbf61d7e80f251235ull, 0xfd913603a6cf24a6ull, 0x73b3727a52b393ccull,
    0x31439391fb59a55full, 0xf652b1ad0167feeaull, 0xb4a25046a88dc879ull, 0xa8e6d8b54074a6adull, 0xea16395ee99e903eull,
    0x2d071b6213a0cb8bull, 0x6ff7fa89ba4afd18ull, 0xe1d5bef04e364a72ull, 0xa3255f1be7dc7ce1ull, 0x64347d271de22754ull,
    0x26c49cccb40811c7ull, 0x5cbd6cc0cc10fafcull, 0x1e4d8d2b65facc6full, 0xd95caf179fc497daull, 0x9bac4efc362ea149ull,
    0x158e0a85c2521623ull, 0x577eeb6e6bb820b0ull, 0x906fc95291867b05ull, 0xd29f28b9386c4d96ull, 0xcedba04ad0952342ull,
    0x8c2b41a1797f15d1ull, 0x4b3a639d83414e64ull, 0x09ca82762aab78f7ull, 0x87e8c60fded7cf9dull, 0xc51827e4773df90eull,
    0x020905d88d03a2bbull, 0x40f9e43324e99428ull, 0x2cffe7d5975e55e2ull, 0x6e0f063e3eb46371ull, 0xa91e2402c48a38c4ull,
    0xebeec5e96d600e57ull, 0x65cc8190991cb93dull, 0x273c607b30f68faeull, 0xe02d4247cac8d41bull, 0xa2dda3ac6322e288ull,
    0xbe992b5f8bdb8c5cull, 0xfc69cab42231bacfull, 0x3b78e888d80fe17aull, 0x7988096371e5d7e9ull, 0xf7aa4d1a85996083ull,
    0xb55aacf12c735610ull, 0x724b8ecdd64d0da5ull, 0x30bb6f267fa73b36ull, 0x4ac29f2a07bfd00dull, 0x08327ec1ae55e69eull,
    0xcf235cfd546bbd2bull, 0x8dd3bd16fd818bb8ull, 0x03f1f96f09fd3cd2ull, 0x41011884a0170a41ull, 0x86103ab85a2951f4ull,
    0xc4e0db53f3c36767ull, 0xd8a453a01b3a09b3ull, 0x9a54b24bb2d03f20ull, 0x5d45907748ee6495ull, 0x1fb5719ce1045206ull,
    0x919735e51578e56cull, 0xd367d40ebc92d3ffull, 0x1476f63246ac884aull, 0x568617d9ef46bed9ull, 0xe085162ab69d5e3cull,
    0xa275f7c11f7768afull, 0x6564d5fde549331aull, 0x279434164ca30589ull, 0xa9b6706fb8dfb2e3ull, 0xeb46918411358470ull,
    0x2c57b3b8eb0bdfc5ull, 0x6ea7525342e1e956ull, 0x72e3daa0aa188782ull, 0x30133b4b03f2b111ull, 0xf7021977f9cceaa4ull,
    0xb5f2f89c5026dc37ull, 0x3bd0bce5a45a6b5dull, 0x79205d0e0db05dceull, 0xbe317f32f78e067bull, 0xfcc19ed95e6430e8ull,
    0x86b86ed5267cdbd3ull, 0xc4488f3e8f96ed40ull, 0x0359ad0275a8b6f5ull, 0x41a94ce9dc428066ull, 0xcf8b0890283e370cull,
    0x8d7be97b81d4019full, 0x4a6acb477bea5a2aull, 0x089a2aacd2006cb9ull, 0x14dea25f3af9026dull, 0x562e43b4931334feull,
    0x913f6188692d6f4bull, 0xd3cf8063c0c759d8ull, 0x5dedc41a34bbeeb2ull, 0x1f1d25f19d51d821ull, 0xd80c07cd676f8394ull,
    0x9afce626ce85b507ull,
};

u32 zpl_crc32(void const *data, isize len) {
    isize remaining;
    u32 result = ~(cast(u32) 0);
    u8 const *c = cast(u8 const *) data;
    for (remaining = len; remaining--; c++) result = (result >> 8) ^ (zpl__CRC32_TABLE[(result ^ *c) & 0xff]);
    return ~result;
}

u64 zpl_crc64(void const *data, isize len) {
    isize remaining;
    u64 result = ~(cast(u64) 0);
    u8 const *c = cast(u8 const *) data;
    for (remaining = len; remaining--; c++) result = (result >> 8) ^ (zpl__CRC64_TABLE[(result ^ *c) & 0xff]);
    return ~result;
}

u32 zpl_fnv32(void const *data, isize len) {
    isize i;
    u32 h = 0x811c9dc5;
    u8 const *c = cast(u8 const *) data;

    for (i = 0; i < len; i++) h = (h * 0x01000193) ^ c[i];

    return h;
}

u64 zpl_fnv64(void const *data, isize len) {
    isize i;
    u64 h = 0xcbf29ce484222325ull;
    u8 const *c = cast(u8 const *) data;

    for (i = 0; i < len; i++) h = (h * 0x100000001b3ll) ^ c[i];

    return h;
}

u32 zpl_fnv32a(void const *data, isize len) {
    isize i;
    u32 h = 0x811c9dc5;
    u8 const *c = cast(u8 const *) data;

    for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x01000193;

    return h;
}

u64 zpl_fnv64a(void const *data, isize len) {
    isize i;
    u64 h = 0xcbf29ce484222325ull;
    u8 const *c = cast(u8 const *) data;

    for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x100000001b3ll;

    return h;
}

zpl_inline u32 zpl_murmur32(void const *data, isize len) { return zpl_murmur32_seed(data, len, 0x9747b28c); }
zpl_inline u64 zpl_murmur64(void const *data, isize len) { return zpl_murmur64_seed(data, len, 0x9747b28c); }

u32 zpl_murmur32_seed(void const *data, isize len, u32 seed) {
    u32 const c1 = 0xcc9e2d51;
    u32 const c2 = 0x1b873593;
    u32 const r1 = 15;
    u32 const r2 = 13;
    u32 const m = 5;
    u32 const n = 0xe6546b64;

    isize i, nblocks = len / 4;
    u32 hash = seed, k1 = 0;
    u32 const *blocks = cast(u32 const *) data;
    u8 const *tail = cast(u8 const *)(data) + nblocks * 4;

    for (i = 0; i < nblocks; i++) {
        u32 k = blocks[i];
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

u64 zpl_murmur64_seed(void const *data_, isize len, u64 seed) {
#if defined(ZPL_ARCH_64_BIT)
    u64 const m = 0xc6a4a7935bd1e995ULL;
    i32 const r = 47;

    u64 h = seed ^ (len * m);

    u64 const *data = cast(u64 const *) data_;
    u8 const *data2 = cast(u8 const *) data_;
    u64 const *end = data + (len / 8);

    while (data != end) {
        u64 k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    switch (len & 7) {
    case 7: h ^= cast(u64)(data2[6]) << 48;
    case 6: h ^= cast(u64)(data2[5]) << 40;
    case 5: h ^= cast(u64)(data2[4]) << 32;
    case 4: h ^= cast(u64)(data2[3]) << 24;
    case 3: h ^= cast(u64)(data2[2]) << 16;
    case 2: h ^= cast(u64)(data2[1]) << 8;
    case 1: h ^= cast(u64)(data2[0]); h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
#else
    u64 h;
    u32 const m = 0x5bd1e995;
    i32 const r = 24;

    u32 h1 = cast(u32)(seed) ^ cast(u32)(len);
    u32 h2 = cast(u32)(seed >> 32);

    u32 const *data = cast(u32 const *) data_;

    while (len >= 8) {
        u32 k1, k2;
        k1 = *data++;
        k1 *= m;
        k1 ^= k1 >> r;
        k1 *= m;
        h1 *= m;
        h1 ^= k1;
        len -= 4;

        k2 = *data++;
        k2 *= m;
        k2 ^= k2 >> r;
        k2 *= m;
        h2 *= m;
        h2 ^= k2;
        len -= 4;
    }

    if (len >= 4) {
        u32 k1 = *data++;
        k1 *= m;
        k1 ^= k1 >> r;
        k1 *= m;
        h1 *= m;
        h1 ^= k1;
        len -= 4;
    }

    switch (len) {
    case 3: h2 ^= (cast(u8 const *) data)[2] << 16;
    case 2: h2 ^= (cast(u8 const *) data)[1] << 8;
    case 1: h2 ^= (cast(u8 const *) data)[0] << 0; h2 *= m;
    };

    h1 ^= h2 >> 18;
    h1 *= m;
    h2 ^= h1 >> 22;
    h2 *= m;
    h1 ^= h2 >> 17;
    h1 *= m;
    h2 ^= h1 >> 19;
    h2 *= m;

    h = h1;
    h = (h << 32) | h2;

    return h;
#endif
}
