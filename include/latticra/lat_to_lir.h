#ifndef LATTICRA_LAT_TO_LIR_H
#define LATTICRA_LAT_TO_LIR_H

#include "latticra/lat_model.h"
#include "latticra/lir.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_TO_LIR_REPORT_MAX 4096u

typedef enum {
    LATTICRA_LAT_TO_LIR_OK = 0,
    LATTICRA_LAT_TO_LIR_NULL_ARGUMENT = 1,
    LATTICRA_LAT_TO_LIR_PARSE_NOT_OK = 2,
    LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK = 3,
    LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID = 4,
    LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION = 5,
    LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED = 6,
    LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT = 7,
    LATTICRA_LAT_TO_LIR_INTERNAL_ERROR = 8,
    LATTICRA_LAT_TO_LIR_MODEL_NOT_OK = 9
} latticra_lat_to_lir_error_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_to_lir_error_t error;
    latticra_lat_model_error_t model_error;
    latticra_lat_source_span_t span;
    char module_name[LATTICRA_LAT_NAME_MAX];
    size_t declaration_count;
    size_t clause_count;
    size_t model_declaration_count;
    size_t model_clause_count;
    size_t first_transition_source_index;
    size_t node_count;
    size_t edge_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
} latticra_lat_to_lir_result_t;

const char *latticra_lat_to_lir_error_label(latticra_lat_to_lir_error_t error);

latticra_status_t latticra_lir_lower_lat_model(
    const latticra_lat_model_t *model,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result);

latticra_status_t latticra_lir_lower_lat_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result);

latticra_status_t latticra_lat_to_lir_report(
    const latticra_lat_to_lir_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
