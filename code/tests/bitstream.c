#define ZPL_IMPLEMENTATION
#include "zpl.h"

int main() {
    // NOTE(inlife): create and allocate a bitstream
    // with size of 100 bytes
    zpl_bs_t bsp;
    zpl_bs_init(bsp, zpl_heap_allocator(), 100);

    // NOTE(inlife): write a typed values
    // (values will be automatically casted)
    zpl_bs_write_f64(bsp, 0.444548254);
    zpl_bs_write_i32(bsp, -42230);
    zpl_bs_write_u32(bsp, 32);

    // NOTE(inlife): read a typed value
    i32 boo = zpl_bs_read_i32(bsp);

    // NOTE(inlife): read a data from a particular place
    i32 foo = zpl_bs_read_i32_at(bsp, 4 + 8);

    // NOTE(inlife): write a data into particular place
    zpl_bs_write_f32_at(bsp, 24.23232, 4);

    // NOTE(inlife): helper methods
    zpl_bs_size(bsp); // get actual written size of the bitstream
    zpl_bs_capacity(bsp); // get allocated capacity
    zpl_bs_read_pos(bsp);
    zpl_bs_write_pos(bsp);

    // NOTE(inlife): free the resources
    zpl_bs_free(bsp);

    return 0;
}
