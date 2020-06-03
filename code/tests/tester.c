#define ZPL_IMPL
#include "zpl.h"

#define UNIT_MAX_CASES 16
#include "unit.h"

/* TEST CATEGORIES */
#include "cases/json.h"
#include "cases/alloc_pool.h"
#include "cases/hashing.h"

int main() {
    UNIT_CREATE("zpl");

    UNIT_CASE(json5_parser);
    UNIT_CASE(alloc_pool);
    UNIT_CASE(hashing);

    return UNIT_RUN();
}
