#include "latticra/lat_pipeline.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int lat_pipeline_records_null_source(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;

    EXPECT_TRUE(latticra_lat_pipeline_run_source(0, 7u, &parse, &semantic, &module, &lowering, &pipeline) == LATTICRA_STATUS_NULL_ARGUMENT, "null source rejected");
    EXPECT_TRUE(pipeline.status == LATTICRA_STATUS_NULL_ARGUMENT, "null source status recorded");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_NULL_ARGUMENT, "null source error recorded");
    EXPECT_TRUE(pipeline.source_len == 7u, "null source length recorded");
    EXPECT_TRUE(strcmp(latticra_lat_pipeline_error_label(pipeline.error), "null_argument") == 0, "null source label recorded");
    return 0;
}

static int lat_pipeline_rejects_null_result(void) {
    static const char source[] = "lat module Empty { }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;

    EXPECT_TRUE(latticra_lat_pipeline_run_source(source, strlen(source), &parse, &semantic, &module, &lowering, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null result rejected");
    return 0;
}

int main(void) {
    if (lat_pipeline_records_null_source() != 0) return 1;
    if (lat_pipeline_rejects_null_result() != 0) return 1;

    puts("lat_pipeline_hardening_invariants: ok");
    return 0;
}
