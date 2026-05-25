#ifndef LATTICRA_LAT_PIPELINE_DIAGNOSTICS_H
#define LATTICRA_LAT_PIPELINE_DIAGNOSTICS_H

#include "latticra/lat_pipeline.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_PIPELINE_DIAGNOSTIC_REPORT_MAX 2048u

typedef enum {
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID = 0,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE = 1,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC = 2,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING = 3,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR = 4,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK = 5,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL = 6,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL = 7
} latticra_lat_pipeline_diagnostic_class_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_pipeline_diagnostic_class_t diagnostic_class;
    latticra_lat_pipeline_error_t pipeline_error;
    latticra_lat_pipeline_stage_t failed_stage;
    latticra_lat_semantic_diagnostic_class_t semantic_class;
    latticra_lat_semantic_error_t semantic_error;
    size_t semantic_diagnostic_count;
    size_t first_diagnostic_declaration_index;
    size_t first_diagnostic_clause_index;
    int pipeline_failed;
    int semantic_failed;
    int no_effect_issue;
    unsigned int evidence_level;
} latticra_lat_pipeline_diagnostic_result_t;

const char *latticra_lat_pipeline_diagnostic_class_label(
    latticra_lat_pipeline_diagnostic_class_t diagnostic_class);

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate(
    const latticra_lat_pipeline_result_t *pipeline_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_pipeline_diagnostic_result_t *diagnostic_result);

latticra_status_t latticra_lat_pipeline_diagnostics_report(
    const latticra_lat_pipeline_diagnostic_result_t *diagnostic_result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
