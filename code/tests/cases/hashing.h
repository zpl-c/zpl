#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif

MODULE(hashing, {
    const char test[] = "Hello World!";
    zpl_isize len = zpl_strlen(test);

    IT("calculates valid adler32", {
        zpl_u32 sum = zpl_adler32(test, len);
        EQUALS(sum, 0x1C49043E);
    });

    IT("calculates valid crc32", {
        zpl_u32 sum = zpl_crc32(test, len);
        EQUALS(sum, 0x1C291CA3);
    });

    IT("calculates valid fnv32", {
        zpl_u32 sum = zpl_fnv32(test, len);
        EQUALS(sum, 0x12a9a41c);
    });

    IT("calculates valid fnv64", {
        zpl_u64 sum = zpl_fnv64(test, len);
        EQUALS(sum, 0x8e59dd02f68c387c);
    });

    IT("calculates valid fnv32a", {
        zpl_u32 sum = zpl_fnv32a(test, len);
        EQUALS(sum, 0xb1ea4872);
    });

    IT("calculates valid fnv64a", {
        zpl_u64 sum = zpl_fnv64a(test, len);
        EQUALS(sum, 0x8c0ec8d1fb9e6e32);
    });

    IT("calculates valid murmur32", {
        zpl_u32 sum = zpl_murmur32(test, len);
        EQUALS(sum, 0xFB86EA72);
    });

    IT("calculates valid murmur64", {
        zpl_u64 sum = zpl_murmur64((zpl_u8*)test, len);
        EQUALS(sum, 0x5E778F7430BA686A);
    });

    IT("encodes base64 string", {
        zpl_u8 *enc = zpl_base64_encode(zpl_heap(), test, len);

        NEQUALS(cast(zpl_uintptr)enc, cast(zpl_uintptr)NULL);

        STREQUALS((const char*)enc, "SGVsbG8gV29ybGQh");
        zpl_mfree(enc);
    });

    IT("decodes base64 string", {
        const char enc[] = "SGVsbG8gV29ybGQh";
        zpl_u8 *dec = zpl_base64_decode(zpl_heap(), enc, zpl_strlen(enc));

        NEQUALS(cast(zpl_uintptr)dec, cast(zpl_uintptr)NULL);

        STREQUALS((const char*)dec, test);
        zpl_mfree(dec);
    });

    IT("re-encodes base64 string", {
        zpl_u8 *enc = zpl_base64_encode(zpl_heap(), test, len);
        zpl_u8 *dec = zpl_base64_decode(zpl_heap(), enc, zpl_strlen((const char*)enc));

        NEQUALS(cast(zpl_uintptr)enc, cast(zpl_uintptr)NULL);
        NEQUALS(cast(zpl_uintptr)dec, cast(zpl_uintptr)NULL);

        STREQUALS((const char*)test, (const char*)dec);
        zpl_mfree(enc);
        zpl_mfree(dec);
    });
});
