#define ZPL_IMPL
#include "zpl.h"

#include "unit.h"

/* TEST CATEGORIES */
#include "cases/json.h"

int main() {
    UNIT_CREATE("zpl");

    UNIT_CASE(json5_parser);

    return UNIT_RUN();
}
