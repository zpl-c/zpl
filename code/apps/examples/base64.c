#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_HASHING
#include "zpl.h"

int main(void)
{
    char buf[] = "Hello World";
    zpl_u8 *enc = zpl_base64_encode(zpl_heap(), buf, zpl_strlen((const char*)buf));
    zpl_u8 *dec = zpl_base64_decode(zpl_heap(), enc, zpl_strlen((const char*)enc));

    ZPL_ASSERT_NOT_NULL(enc);
    ZPL_ASSERT_NOT_NULL(dec);

    ZPL_ASSERT_MSG((!zpl_strcmp((const char*)buf, (const char*)dec)), "%s == %s\n", buf, dec);

    zpl_printf("Output:\n%s is %s\n", enc, dec);
    
    zpl_mfree(enc);
    zpl_mfree(dec);aa
    
    return 0;
}
