#include "latticra/lat_to_lir_diagnostics.h"

#include <stdio.h>

static void diagnostic_default(latticra_lat_to_lir_diagnostic_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->diagnostic_class = LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID;
    result->lowering_error = LATTICRA_LAT_TO_LIR_OK;
    result->model_error = LATTICRA_LAT_MODEL_OK;
    result->lir_error = LATTICRA_LIR_OK;
    result->model_declaration_count = 0u;
    result->model_clause_count = 0u;
    result->first_transition_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->lowering_failed = 0;
    result->model_failed = 0;
    result->lir_failed = 0;
    result->no_effect_issue = 0;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->evidence_level = 0u;
}

const char *latticra_lat_to_lir_diagnostic_class_label(
    latticra_lat_to_lir_diagnostic_class_t diagnostic_class) {
    switch (diagnostic_class) {
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID: return "valid";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE: return "parse";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC: return "semantic";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL: return "model";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK: return "effect-check";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_CAPACITY: return "capacity";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR: return "lir";
    case LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL:
    default: return "internal";
    }
}

static latticra_lat_to_lir_diagnostic_class_t class_from_lowering(
    const latticra_lat_to_lir_result_t *lowering,
    const latticra_lir_module_t *module) {
    if (lowering == 0) return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL;
    if (lowering->status != LATTICRA_STATUS_OK && lowering->error == LATTICRA_LAT_TO_LIR_OK) {
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL;
    }
    switch (lowering->error) {
    case LATTICRA_LAT_TO_LIR_OK:
        if (module != 0 && module->error != LATTICRA_LIR_OK) return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR;
        return LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID;
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

latticra_status_t latticra_lat_to_lir_diagnostics_evaluate(
    const latticra_lat_to_lir_result_t *lowering,
    const latticra_lir_module_t *module,
    latticra_lat_to_lir_diagnostic_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    diagnostic_default(result);
    if (lowering == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        result->diagnostic_class = LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL;
        result->evidence_level = 0u;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result->status = lowering->status;
    result->lowering_error = lowering->error;
    result->model_error = lowering->model_error;
    result->model_declaration_count = lowering->model_declaration_count;
    result->model_clause_count = lowering->model_clause_count;
    result->first_transition_source_index = lowering->first_transition_source_index;
    result->node_count = lowering->node_count;
    result->edge_count = lowering->edge_count;
    result->lowering_failed = lowering->error != LATTICRA_LAT_TO_LIR_OK;
    result->model_failed = lowering->model_error != LATTICRA_LAT_MODEL_OK ||
        lowering->error == LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
    result->no_effect = lowering->no_effect;
    result->execution_allowed = lowering->execution_allowed;
    result->mutation_allowed = lowering->mutation_allowed;
    result->no_effect_issue = lowering->error == LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION ||
        lowering->no_effect != 1 ||
        lowering->execution_allowed != 0 ||
        lowering->mutation_allowed != 0;

    if (module != 0) {
        result->lir_error = module->error;
        result->lir_failed = module->error != LATTICRA_LIR_OK;
    }

    result->diagnostic_class = class_from_lowering(lowering, module);
    if (result->diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID) result->evidence_level = 2u;
    else if (result->diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL) result->evidence_level = 0u;
    else result->evidence_level = 1u;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_to_lir_diagnostics_report(
    const latticra_lat_to_lir_diagnostic_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(
        buffer,
        buffer_len,
        "LAT TO LIR DIAGNOSTIC REPORT\n"
        "status=%d\n"
        "diagnostic_class=%s\n"
        "lowering_error=%s\n"
        "model_error=%s\n"
        "lir_error=%s\n"
        "model_declaration_count=%zu\n"
        "model_clause_count=%zu\n"
        "first_transition_source_index=%zu\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "lowering_failed=%d\n"
        "model_failed=%d\n"
        "lir_failed=%d\n"
        "no_effect_issue=%d\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "evidence_level=%u\n",
        (int)result->status,
        latticra_lat_to_lir_diagnostic_class_label(result->diagnostic_class),
        latticra_lat_to_lir_error_label(result->lowering_error),
        latticra_lat_model_error_label(result->model_error),
        latticra_lir_error_label(result->lir_error),
        result->model_declaration_count,
        result->model_clause_count,
        result->first_transition_source_index,
        result->node_count,
        result->edge_count,
        result->lowering_failed,
        result->model_failed,
        result->lir_failed,
        result->no_effect_issue,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->evidence_level);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
