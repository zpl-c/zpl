#define ZPL_IMPL
#include "zpl.h"

#include "unit.h"

/* TEST CATEGORIES */
#include "cases/json.h"
#include "cases/alloc_pool.h"

int main() {
    UNIT_CREATE("zpl");

    UNIT_CASE(json5_parser);
    UNIT_CASE(alloc_pool);

    return UNIT_RUN();
}
