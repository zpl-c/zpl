#define ZPL_IMPL
#include "zpl.h"

#define UNIT_MAX_MODULES 16
#include "unit.h"

/* TEST CATEGORIES */
#include "cases/json.h"
#include "cases/csv.h"
#include "cases/alloc_pool.h"
#include "cases/hashing.h"
#include "cases/time.h"
#include "cases/stream.h"
#include "cases/print.h"

int main() {
    UNIT_CREATE("zpl");

    UNIT_MODULE(alloc_pool);
    UNIT_MODULE(hashing);
    UNIT_MODULE(time);
    UNIT_MODULE(stream);
    UNIT_MODULE(print);
    UNIT_MODULE(json5_parser);
    UNIT_MODULE(csv_parser);

    return UNIT_RUN();
}
