

#define ZPL_IMPLEMENTATION
#include "zpl.h"

int
main(void) {
    
    // NOTE(ZaKlaus): Create stack buffer region
    isize stack_size = zpl_kilobytes(16);
    void *stack_buf = zpl_malloc(stack_size);
    
    // NOTE(ZaKlaus): Create stack memory allocator
    zplStackMemory stack = {0};
    zpl_stack_memory_init(&stack, stack_buf, stack_size);
    
    zplAllocator stack_alloc = zpl_stack_allocator(&stack);
    
    // NOTE(ZaKlaus): Create array container
    zplArray(u32) arr;
    zpl_array_init(arr, stack_alloc);
    
    // NOTE(ZaKlaus): Push 5 elements
    for (i32 i = 0; i < 5; ++i) {
        zpl_array_append(arr, i*2);
    }
    
    // NOTE(ZaKlaus): List them
    zpl_printf("Before removal:\n");
    for (i32 i = 0; i < 5; ++i) {
        zpl_printf("Value: %lld\n", arr[i]);
    }
    
    // NOTE(ZaKlaus): Pop 2 values
    zpl_array_pop(arr);
    zpl_array_pop(arr);

    // NOTE(ZaKlaus): List them again
    zpl_printf("\nAfter removal:\n");
    for (i32 i = 0; i < 3; ++i) {
        zpl_printf("Value: %lld\n", arr[i]);
    }
    
    // NOTE(ZaKlaus): Clear the array out
    zpl_array_clear(arr);
    
    // NOTE(ZaKlaus): Release used resources
    zpl_mfree(stack_buf);
    return 0;
}