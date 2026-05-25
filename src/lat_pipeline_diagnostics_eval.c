#include "latticra/lat_pipeline_diagnostics.h"

#include <stdio.h>
#include <string.h>

static void copy_text(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void diagnostic_default(latticra_lat_pipeline_diagnostic_result_t *result) {
    if (result == 0) return;
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    result->diagnostic_class = LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID;
    result->pipeline_error = LATTICRA_LAT_PIPELINE_OK;
    result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    result->semantic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID;
    result->semantic_error = LATTICRA_LAT_SEMANTIC_OK;
    result->lowering_class = LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID;
    result->lowering_error = LATTICRA_LAT_TO_LIR_OK;
    result->model_error = LATTICRA_LAT_MODEL_OK;
    result->lir_error = LATTICRA_LIR_OK;
    result->lowering_first_declaration_node_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_declaration_kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
    result->lowering_first_declaration_parse_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_declaration_first_clause_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_declaration_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_transition_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_clause_node_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->lowering_first_clause_role = LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
    result->lowering_first_clause_effect = LATTICRA_LAT_EFFECT_UNKNOWN;
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

static latticra_lat_pipeline_diagnostic_class_t class_from_lowering(
    latticra_lat_to_lir_diagnostic_class_t diagnostic_class) {
    switch (diagnostic_class) {
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_CAPACITY: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING;
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL:
    default: return LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL;
    }
}

static latticra_lat_to_lir_diagnostic_class_t lowering_class_from_error(
    latticra_lat_to_lir_error_t lowering_error,
    latticra_lir_error_t lir_error) {
    switch (lowering_error) {
    case LATTICRA_LAT_TO_LIR_OK:
        return lir_error == LATTICRA_LIR_OK ? LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID : LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR;
    case LATTICRA_LAT_TO_LIR_PARSE_NOT_OK:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE;
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK:
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC;
    case LATTICRA_LAT_TO_LIR_MODEL_NOT_OK:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL;
    case LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION:
    case LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK;
    case LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_CAPACITY;
    case LATTICRA_LAT_TO_LIR_NULL_ARGUMENT:
    case LATTICRA_LAT_TO_LIR_INTERNAL_ERROR:
    default:
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL;
    }
}

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate_with_lowering(
    const latticra_lat_pipeline_result_t *pipeline,
    const latticra_lat_semantic_result_t *semantic,
    const latticra_lat_to_lir_result_t *lowering,
    const latticra_lir_module_t *module,
    latticra_lat_pipeline_diagnostic_result_t *result) {
    latticra_lat_to_lir_diagnostic_result_t lowering_diagnostic;
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
    result->lowering_error = pipeline->lowering_error;
    result->model_error = pipeline->model_error;
    result->lir_error = pipeline->lir_error;
    result->lowering_class = lowering_class_from_error(pipeline->lowering_error, pipeline->lir_error);
    result->lowering_model_declaration_count = pipeline->model_declaration_count;
    result->lowering_model_clause_count = pipeline->model_clause_count;
    result->lowering_first_transition_source_index = pipeline->first_transition_source_index;
    result->lowering_failed = pipeline->lowering_ok == 0 && pipeline->lowering_error != LATTICRA_LAT_TO_LIR_OK;
    result->model_failed = pipeline->model_ok == 0 && pipeline->model_error != LATTICRA_LAT_MODEL_OK;
    result->lir_failed = pipeline->lir_ok == 0 && pipeline->lir_error != LATTICRA_LIR_OK;
    result->no_effect_issue = pipeline->error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION || pipeline->no_effect_chain_ok == 0;

    if (semantic != 0) {
        result->semantic_class = semantic->diagnostic_class;
        result->semantic_error = semantic->error;
        result->semantic_diagnostic_count = semantic->diagnostic_count;
        result->first_diagnostic_declaration_index = semantic->first_diagnostic_declaration_index;
        result->first_diagnostic_clause_index = semantic->first_diagnostic_clause_index;
        result->semantic_failed = semantic->error != LATTICRA_LAT_SEMANTIC_OK || semantic->semantic_valid != 1;
    }

    if (lowering != 0 &&
        latticra_lat_to_lir_diagnostics_evaluate(lowering, module, &lowering_diagnostic) == LATTICRA_STATUS_OK) {
        result->lowering_class = lowering_diagnostic.diagnostic_class;
        result->lowering_error = lowering_diagnostic.lowering_error;
        result->model_error = lowering_diagnostic.model_error;
        result->lir_error = lowering_diagnostic.lir_error;
        result->lowering_model_declaration_count = lowering_diagnostic.model_declaration_count;
        result->lowering_model_clause_count = lowering_diagnostic.model_clause_count;
        result->lowering_first_declaration_node_index = lowering_diagnostic.first_declaration_node_index;
        result->lowering_first_declaration_kind = lowering_diagnostic.first_declaration_kind;
        copy_text(result->lowering_first_declaration_name, sizeof(result->lowering_first_declaration_name), lowering_diagnostic.first_declaration_name);
        copy_text(result->lowering_first_declaration_source, sizeof(result->lowering_first_declaration_source), lowering_diagnostic.first_declaration_source);
        result->lowering_first_declaration_parse_index = lowering_diagnostic.first_declaration_parse_index;
        result->lowering_first_declaration_first_clause_index = lowering_diagnostic.first_declaration_first_clause_index;
        result->lowering_first_declaration_clause_count = lowering_diagnostic.first_declaration_clause_count;
        result->lowering_first_declaration_source_index = lowering_diagnostic.first_declaration_source_index;
        result->lowering_first_transition_source_index = lowering_diagnostic.first_transition_source_index;
        result->lowering_first_clause_node_index = lowering_diagnostic.first_clause_node_index;
        result->lowering_first_clause_role = lowering_diagnostic.first_clause_role;
        result->lowering_first_clause_effect = lowering_diagnostic.first_clause_effect;
        copy_text(result->lowering_first_clause_name, sizeof(result->lowering_first_clause_name), lowering_diagnostic.first_clause_name);
        copy_text(result->lowering_first_clause_operator, sizeof(result->lowering_first_clause_operator), lowering_diagnostic.first_clause_operator);
        copy_text(result->lowering_first_clause_value, sizeof(result->lowering_first_clause_value), lowering_diagnostic.first_clause_value);
        result->lowering_failed = lowering_diagnostic.lowering_failed;
        result->model_failed = lowering_diagnostic.model_failed;
        result->lir_failed = lowering_diagnostic.lir_failed;
        result->no_effect_issue = result->no_effect_issue || lowering_diagnostic.no_effect_issue;
        if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID ||
            result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING ||
            result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR ||
            result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL) {
            result->diagnostic_class = class_from_lowering(lowering_diagnostic.diagnostic_class);
        }
    } else if (module != 0) {
        result->lir_error = module->error;
        result->lir_failed = module->error != LATTICRA_LIR_OK;
        if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID && result->lir_failed) {
            result->diagnostic_class = LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR;
        }
    }

    if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID) result->evidence_level = 2u;
    else if (result->diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL) result->evidence_level = 0u;
    else result->evidence_level = 1u;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate(
    const latticra_lat_pipeline_result_t *pipeline,
    const latticra_lat_semantic_result_t *semantic,
    latticra_lat_pipeline_diagnostic_result_t *result) {
    return latticra_lat_pipeline_diagnostics_evaluate_with_lowering(pipeline, semantic, 0, 0, result);
}
