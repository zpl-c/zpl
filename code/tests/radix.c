

#define ZPL_IMPLEMENTATION
#include "zpl.h"

int
main(void) {
   
    
    u32 nums[4096*8] = {0};
    u32 temp[4096*8] = {0};
    
    zplRandom r; zpl_random_init(&r);
    for (int i = 0; i < 4096*8; ++i) {
        nums[i] = zpl_random_gen_u32_unique(&r);
    }
    
    zpl_printf("First 30 numbers...\nBefore: ");
    for (int i = 0; i < 90; ++i) {
        zpl_printf("%lld, ", nums[i]);
    }
    
    zpl_radix_sort_u32(nums, temp, 4096*8);
    
    zpl_printf("\n\nAfter: ");
    for (int i = 0; i < 90; ++i) {
        zpl_printf("%lld, ", nums[i]);
    }    
    
    return 0;
}