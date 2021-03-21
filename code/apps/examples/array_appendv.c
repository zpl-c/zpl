#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#include <zpl.h>

zpl_i32 nums[] = { 1,2,3,4,5 };
zpl_i32 xtra[] = { 9,9,8 };

void display_arr(zpl_i32 *arr) {
    for (zpl_isize i = 0; i < zpl_array_count(arr); i++) {
        zpl_printf("%d, ", arr[i]);
    }
    zpl_printf("%s", "\n");
}

int main() {
    zpl_i32 *arr = NULL;
    zpl_array_init(arr, zpl_heap());
    zpl_array_appendv(arr, nums, zpl_count_of(nums));
    display_arr(arr);

    zpl_array_appendv_at(arr, xtra, zpl_count_of(xtra), 1);
    display_arr(arr);

    zpl_array_fill(arr, 1, 6, 5);
    display_arr(arr);

    zpl_array_free(arr);
    return 0;
}
