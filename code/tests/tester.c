#define ZPL_IMPL
#define ZPL_HEAP_ANALYSIS
#include "zpl.h"

#define UNIT_MAX_MODULES 16
#include "unit.h"

/* TEST CATEGORIES */
#include "cases/json.h"
#include "cases/csv.h"
#include "cases/uri.h"
#include "cases/alloc_pool.h"
#include "cases/hashing.h"
#include "cases/memory.h"
#include "cases/table.h"
#include "cases/time.h"
#include "cases/stream.h"
#include "cases/print.h"
#include "cases/adt.h"

int main() {
    zpl_heap_stats_init();
    UNIT_CREATE("zpl");

    UNIT_MODULE(alloc_pool);
    UNIT_MODULE(hashing);
    UNIT_MODULE(time);
    UNIT_MODULE(stream);
    UNIT_MODULE(memory);
    UNIT_MODULE(table);
    UNIT_MODULE(print);
    UNIT_MODULE(json5_parser);
    UNIT_MODULE(csv_parser);
    UNIT_MODULE(uri_parser);
    UNIT_MODULE(adt);

    int32_t ret_code = UNIT_RUN();
    zpl_heap_stats_check();
    return ret_code;
}
