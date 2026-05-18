#include "latticra/lat_pipeline.h"

#include <stdio.h>
#include <string.h>

static void copy_text(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void lat_span_default(latticra_lat_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void pipeline_result_default(latticra_lat_pipeline_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_LAT_PIPELINE_OK;
    result->parse_error = LATTICRA_LAT_PARSE_OK;
    result->semantic_error = LATTICRA_LAT_SEMANTIC_OK;
    result->lowering_error = LATTICRA_LAT_TO_LIR_OK;
    result->lir_error = LATTICRA_LIR_OK;
    lat_span_default(&result->span);
    result->module_name[0] = '\0';
    result->source_len = 0u;
    result->declaration_count = 0u;
    result->clause_count = 0u;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->semantic_valid = 0;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

const char *latticra_lat_pipeline_error_label(latticra_lat_pipeline_error_t error) {
    switch (error) {
    case LATTICRA_LAT_PIPELINE_OK: return "ok";
    case LATTICRA_LAT_PIPELINE_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LAT_PIPELINE_PARSE_NOT_OK: return "parse_not_ok";
    case LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK: return "semantic_not_ok";
    case LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID: return "semantic_not_valid";
    case LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK: return "lowering_not_ok";
    case LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION: return "no_effect_violation";
    case LATTICRA_LAT_PIPELINE_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

static int no_effect_ok(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    const latticra_lir_module_t *module,
    const latticra_lat_to_lir_result_t *lowering_result) {
    return parse_result != 0 && semantic_result != 0 && module != 0 && lowering_result != 0 &&
           parse_result->no_effect == 1 &&
           parse_result->execution_allowed == 0 &&
           parse_result->mutation_allowed == 0 &&
           parse_result->server_allowed == 0 &&
           parse_result->recovery_allowed == 0 &&
           parse_result->hardware_allowed == 0 &&
           semantic_result->no_effect == 1 &&
           semantic_result->execution_allowed == 0 &&
           semantic_result->mutation_allowed == 0 &&
           semantic_result->server_allowed == 0 &&
           semantic_result->recovery_allowed == 0 &&
           semantic_result->hardware_allowed == 0 &&
           module->no_effect == 1 &&
           module->execution_allowed == 0 &&
           module->mutation_allowed == 0 &&
           module->server_allowed == 0 &&
           module->recovery_allowed == 0 &&
           module->hardware_allowed == 0 &&
           lowering_result->no_effect == 1 &&
           lowering_result->execution_allowed == 0 &&
           lowering_result->mutation_allowed == 0;
}

static void summarize_pipeline(
    size_t source_len,
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    const latticra_lir_module_t *module,
    const latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    if (parse_result == 0 || semantic_result == 0 || module == 0 || lowering_result == 0 || pipeline_result == 0) return;

    pipeline_result->source_len = source_len;
    pipeline_result->parse_error = parse_result->error;
    pipeline_result->semantic_error = semantic_result->error;
    pipeline_result->lowering_error = lowering_result->error;
    pipeline_result->lir_error = module->error;
    pipeline_result->span = parse_result->module.span;
    copy_text(pipeline_result->module_name, sizeof(pipeline_result->module_name), parse_result->module.module_name);
    pipeline_result->declaration_count = parse_result->declaration_count;
    pipeline_result->clause_count = parse_result->clause_count;
    pipeline_result->node_count = lowering_result->node_count;
    pipeline_result->edge_count = lowering_result->edge_count;
    pipeline_result->semantic_valid = semantic_result->semantic_valid;
    pipeline_result->no_effect = parse_result->no_effect && semantic_result->no_effect && module->no_effect && lowering_result->no_effect;
    pipeline_result->execution_allowed = parse_result->execution_allowed || semantic_result->execution_allowed || module->execution_allowed || lowering_result->execution_allowed;
    pipeline_result->mutation_allowed = parse_result->mutation_allowed || semantic_result->mutation_allowed || module->mutation_allowed || lowering_result->mutation_allowed;
    pipeline_result->server_allowed = parse_result->server_allowed || semantic_result->server_allowed || module->server_allowed;
    pipeline_result->recovery_allowed = parse_result->recovery_allowed || semantic_result->recovery_allowed || module->recovery_allowed;
    pipeline_result->hardware_allowed = parse_result->hardware_allowed || semantic_result->hardware_allowed || module->hardware_allowed;
}

latticra_status_t latticra_lat_pipeline_run_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    latticra_status_t parse_status;
    latticra_status_t semantic_status;
    latticra_status_t lowering_status;

    if (source == 0 || parse_result == 0 || semantic_result == 0 || module == 0 || lowering_result == 0 || pipeline_result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    pipeline_result_default(pipeline_result);

    parse_status = latticra_lat_parse_source(source, source_len, parse_result);
    if (parse_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = parse_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        pipeline_result->source_len = source_len;
        return parse_status;
    }

    semantic_status = latticra_lat_validate_module(parse_result, semantic_result);
    if (semantic_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = semantic_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        summarize_pipeline(source_len, parse_result, semantic_result, module, lowering_result, pipeline_result);
        return semantic_status;
    }

    lowering_status = latticra_lir_lower_lat_module(parse_result, semantic_result, module, lowering_result);
    if (lowering_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = lowering_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        summarize_pipeline(source_len, parse_result, semantic_result, module, lowering_result, pipeline_result);
        return lowering_status;
    }

    summarize_pipeline(source_len, parse_result, semantic_result, module, lowering_result, pipeline_result);

    if (parse_result->error != LATTICRA_LAT_PARSE_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_PARSE_NOT_OK;
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->error != LATTICRA_LAT_SEMANTIC_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK;
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->semantic_valid != 1) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID;
        return LATTICRA_STATUS_OK;
    }
    if (lowering_result->error != LATTICRA_LAT_TO_LIR_OK || module->error != LATTICRA_LIR_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK;
        return LATTICRA_STATUS_OK;
    }
    if (!no_effect_ok(parse_result, semantic_result, module, lowering_result)) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION;
        return LATTICRA_STATUS_OK;
    }

    pipeline_result->error = LATTICRA_LAT_PIPELINE_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_pipeline_report(
    const latticra_lat_pipeline_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    written = snprintf(
        buffer,
        buffer_len,
        "LAT PIPELINE REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "parse_error=%s\n"
        "semantic_error=%s\n"
        "lowering_error=%s\n"
        "lir_error=%s\n"
        "module=%s\n"
        "source_len=%zu\n"
        "semantic_valid=%d\n"
        "declaration_count=%zu\n"
        "clause_count=%zu\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)result->status,
        latticra_lat_pipeline_error_label(result->error),
        latticra_lat_parse_error_label(result->parse_error),
        latticra_lat_semantic_error_label(result->semantic_error),
        latticra_lat_to_lir_error_label(result->lowering_error),
        latticra_lir_error_label(result->lir_error),
        result->module_name,
        result->source_len,
        result->semantic_valid,
        result->declaration_count,
        result->clause_count,
        result->node_count,
        result->edge_count,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->server_allowed,
        result->recovery_allowed,
        result->hardware_allowed,
        result->span.start_offset,
        result->span.end_offset,
        result->span.start_line,
        result->span.start_column,
        result->span.end_line,
        result->span.end_column);
    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
