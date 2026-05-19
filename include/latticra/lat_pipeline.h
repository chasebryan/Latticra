#ifndef LATTICRA_LAT_PIPELINE_H
#define LATTICRA_LAT_PIPELINE_H

#include "latticra/lat_to_lir.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_PIPELINE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_LAT_PIPELINE_OK = 0,
    LATTICRA_LAT_PIPELINE_NULL_ARGUMENT = 1,
    LATTICRA_LAT_PIPELINE_PARSE_NOT_OK = 2,
    LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK = 3,
    LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID = 4,
    LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK = 5,
    LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION = 6,
    LATTICRA_LAT_PIPELINE_INTERNAL_ERROR = 7
} latticra_lat_pipeline_error_t;

typedef enum {
    LATTICRA_LAT_PIPELINE_STAGE_NONE = 0,
    LATTICRA_LAT_PIPELINE_STAGE_PARSE = 1,
    LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC = 2,
    LATTICRA_LAT_PIPELINE_STAGE_LOWERING = 3,
    LATTICRA_LAT_PIPELINE_STAGE_LIR = 4,
    LATTICRA_LAT_PIPELINE_STAGE_EFFECT_CHECK = 5,
    LATTICRA_LAT_PIPELINE_STAGE_REPORT = 6,
    LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN = 7
} latticra_lat_pipeline_stage_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_pipeline_error_t error;
    latticra_lat_parse_error_t parse_error;
    latticra_lat_semantic_error_t semantic_error;
    latticra_lat_to_lir_error_t lowering_error;
    latticra_lir_error_t lir_error;
    latticra_lat_source_span_t span;
    char module_name[LATTICRA_LAT_NAME_MAX];
    size_t source_len;
    size_t declaration_count;
    size_t clause_count;
    size_t node_count;
    size_t edge_count;
    latticra_lat_pipeline_stage_t last_completed_stage;
    latticra_lat_pipeline_stage_t failed_stage;
    int parse_ok;
    int semantic_ok;
    int lowering_ok;
    int lir_ok;
    int no_effect_chain_ok;
    unsigned int evidence_level;
    int semantic_valid;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_lat_pipeline_result_t;

const char *latticra_lat_pipeline_error_label(latticra_lat_pipeline_error_t error);
const char *latticra_lat_pipeline_stage_label(latticra_lat_pipeline_stage_t stage);

latticra_status_t latticra_lat_pipeline_run_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result);

latticra_status_t latticra_lat_pipeline_report(
    const latticra_lat_pipeline_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
