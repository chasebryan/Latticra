#include "latticra/lat_pipeline_diagnostics.h"

#include <string.h>

static void diagnostic_default(latticra_lat_pipeline_diagnostic_result_t *result) {
    if (result == 0) return;
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    result->diagnostic_class = LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID;
    result->pipeline_error = LATTICRA_LAT_PIPELINE_OK;
    result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    result->semantic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID;
    result->semantic_error = LATTICRA_LAT_SEMANTIC_OK;
    result->evidence_level = 0u;
}

static latticra_lat_pipeline_diagnostic_class_t class_from_pipeline(
    const latticra_lat_pipeline_result_t *pipeline) {
    if (pipeline == 0) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_OK) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK ||
        pipeline->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_MODEL_NOT_OK) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING;
    if (pipeline->error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION) return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK;
    return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL;
}

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate(
    const latticra_lat_pipeline_result_t *pipeline,
    const latticra_lat_semantic_result_t *semantic,
    latticra_lat_pipeline_diagnostic_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    diagnostic_default(result);
    if (pipeline == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        result->diagnostic_class = LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL;
        result->evidence_level = 0u;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result->pipeline_error = pipeline->error;
    result->failed_stage = pipeline->failed_stage;
    result->pipeline_failed = pipeline->error != LATTICRA_LAT_PIPELINE_OK;
    result->diagnostic_class = class_from_pipeline(pipeline);
    result->no_effect_issue = pipeline->error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION || pipeline->no_effect_chain_ok == 0;

    if (semantic != 0) {
        result->semantic_class = semantic->diagnostic_class;
        result->semantic_error = semantic->error;
        result->semantic_diagnostic_count = semantic->diagnostic_count;
        result->first_diagnostic_declaration_index = semantic->first_diagnostic_declaration_index;
        result->first_diagnostic_clause_index = semantic->first_diagnostic_clause_index;
        result->semantic_failed = semantic->error != LATTICRA_LAT_SEMANTIC_OK || semantic->semantic_valid != 1;
    }

    if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID) result->evidence_level = 2u;
    else if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL) result->evidence_level = 0u;
    else result->evidence_level = 1u;

    return LATTICRA_STATUS_OK;
}
