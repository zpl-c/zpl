#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_MATH
#include <zpl.h>

int main(void) {
    zpl_vec3 myvec = zpl_vec3f(10.0f, 5.0f, 0.0f);

    myvec *= 5.0f;

    ZPL_ASSERT(myvec.x == 50.0f);
    ZPL_ASSERT(myvec.y == 25.0f);
    ZPL_ASSERT(myvec.z == 0.0f);

    zpl_printf("result vec: %f %f %f\n", myvec.x, myvec.y, myvec.z);

    return 0;
}
