#define ZPL_IMPLEMENTATION
#include "zpl.h"

int main(void)
{
    char buf[] = "Hello World";
    zpl_u8 *enc = zpl_base64_encode(zpl_heap(), buf, zpl_strlen(buf));
    zpl_u8 *dec = zpl_base64_decode(zpl_heap(), enc, zpl_strlen(enc));

    ZPL_ASSERT_NOT_NULL(enc);
    ZPL_ASSERT_NOT_NULL(dec);

    ZPL_ASSERT_MSG((!zpl_strcmp(buf, dec)), "%s == %s\n", buf, dec);

    zpl_printf("Output:\n%s is %s\n", enc, dec);
    return 0;
}
