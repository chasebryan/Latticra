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
    result->model_error = LATTICRA_LAT_MODEL_OK;
    result->lowering_error = LATTICRA_LAT_TO_LIR_OK;
    result->lir_error = LATTICRA_LIR_OK;
    lat_span_default(&result->span);
    result->module_name[0] = '\0';
    result->source_len = 0u;
    result->declaration_count = 0u;
    result->clause_count = 0u;
    result->model_declaration_count = 0u;
    result->model_clause_count = 0u;
    result->first_transition_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    result->parse_ok = 0;
    result->semantic_ok = 0;
    result->model_ok = 0;
    result->lowering_ok = 0;
    result->lir_ok = 0;
    result->no_effect_chain_ok = 1;
    result->evidence_level = 0u;
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
    case LATTICRA_LAT_PIPELINE_MODEL_NOT_OK: return "model_not_ok";
    case LATTICRA_LAT_PIPELINE_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_lat_pipeline_stage_label(latticra_lat_pipeline_stage_t stage) {
    switch (stage) {
    case LATTICRA_LAT_PIPELINE_STAGE_NONE: return "none";
    case LATTICRA_LAT_PIPELINE_STAGE_PARSE: return "parse";
    case LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC: return "semantic";
    case LATTICRA_LAT_PIPELINE_STAGE_MODEL: return "model";
    case LATTICRA_LAT_PIPELINE_STAGE_LOWERING: return "lowering";
    case LATTICRA_LAT_PIPELINE_STAGE_LIR: return "lir";
    case LATTICRA_LAT_PIPELINE_STAGE_EFFECT_CHECK: return "effect-check";
    case LATTICRA_LAT_PIPELINE_STAGE_REPORT: return "report";
    case LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN:
    default: return "unknown";
    }
}

static int no_effect_ok(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    const latticra_lat_model_t *model_result,
    const latticra_lir_module_t *module,
    const latticra_lat_to_lir_result_t *lowering_result) {
    return parse_result != 0 && semantic_result != 0 && model_result != 0 && module != 0 && lowering_result != 0 &&
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
           model_result->no_effect == 1 &&
           model_result->execution_allowed == 0 &&
           model_result->mutation_allowed == 0 &&
           model_result->server_allowed == 0 &&
           model_result->recovery_allowed == 0 &&
           model_result->hardware_allowed == 0 &&
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

static void summarize_parse_semantic(
    size_t source_len,
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    if (parse_result == 0 || semantic_result == 0 || pipeline_result == 0) return;

    pipeline_result->source_len = source_len;
    pipeline_result->parse_error = parse_result->error;
    pipeline_result->semantic_error = semantic_result->error;
    pipeline_result->span = parse_result->module.span;
    copy_text(pipeline_result->module_name, sizeof(pipeline_result->module_name), parse_result->module.module_name);
    pipeline_result->declaration_count = parse_result->declaration_count;
    pipeline_result->clause_count = parse_result->clause_count;
    pipeline_result->semantic_valid = semantic_result->semantic_valid;
    pipeline_result->parse_ok = parse_result->error == LATTICRA_LAT_PARSE_OK;
    pipeline_result->semantic_ok = semantic_result->error == LATTICRA_LAT_SEMANTIC_OK && semantic_result->semantic_valid == 1;
    if (pipeline_result->parse_ok) pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_PARSE;
    if (pipeline_result->semantic_ok) pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC;
    pipeline_result->no_effect = parse_result->no_effect && semantic_result->no_effect;
    pipeline_result->execution_allowed = parse_result->execution_allowed || semantic_result->execution_allowed;
    pipeline_result->mutation_allowed = parse_result->mutation_allowed || semantic_result->mutation_allowed;
    pipeline_result->server_allowed = parse_result->server_allowed || semantic_result->server_allowed;
    pipeline_result->recovery_allowed = parse_result->recovery_allowed || semantic_result->recovery_allowed;
    pipeline_result->hardware_allowed = parse_result->hardware_allowed || semantic_result->hardware_allowed;
}

static void summarize_pipeline(
    size_t source_len,
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    const latticra_lat_model_t *model_result,
    const latticra_lir_module_t *module,
    const latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    if (parse_result == 0 || semantic_result == 0 || model_result == 0 || module == 0 || lowering_result == 0 || pipeline_result == 0) return;

    summarize_parse_semantic(source_len, parse_result, semantic_result, pipeline_result);
    pipeline_result->model_error = model_result->error;
    pipeline_result->model_declaration_count = model_result->declaration_count;
    pipeline_result->model_clause_count = model_result->clause_count;
    pipeline_result->first_transition_source_index = model_result->first_transition_index == LATTICRA_LAT_MODEL_NO_INDEX ?
        LATTICRA_LAT_MODEL_NO_INDEX :
        model_result->declarations[model_result->first_transition_index].source_declaration_index;
    pipeline_result->lowering_error = lowering_result->error;
    pipeline_result->lir_error = module->error;
    pipeline_result->node_count = lowering_result->node_count;
    pipeline_result->edge_count = lowering_result->edge_count;
    pipeline_result->lowering_ok = lowering_result->error == LATTICRA_LAT_TO_LIR_OK;
    pipeline_result->model_ok = model_result->error == LATTICRA_LAT_MODEL_OK;
    pipeline_result->lir_ok = module->error == LATTICRA_LIR_OK;
    if (pipeline_result->model_ok) pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_MODEL;
    if (pipeline_result->lowering_ok) pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_LOWERING;
    if (pipeline_result->lir_ok) pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_LIR;
    pipeline_result->no_effect = pipeline_result->no_effect && model_result->no_effect && module->no_effect && lowering_result->no_effect;
    pipeline_result->execution_allowed = pipeline_result->execution_allowed || model_result->execution_allowed || module->execution_allowed || lowering_result->execution_allowed;
    pipeline_result->mutation_allowed = pipeline_result->mutation_allowed || model_result->mutation_allowed || module->mutation_allowed || lowering_result->mutation_allowed;
    pipeline_result->server_allowed = pipeline_result->server_allowed || model_result->server_allowed || module->server_allowed;
    pipeline_result->recovery_allowed = pipeline_result->recovery_allowed || model_result->recovery_allowed || module->recovery_allowed;
    pipeline_result->hardware_allowed = pipeline_result->hardware_allowed || model_result->hardware_allowed || module->hardware_allowed;
    pipeline_result->no_effect_chain_ok = no_effect_ok(parse_result, semantic_result, model_result, module, lowering_result);
}

static void finalize_pipeline_report_refinement(latticra_lat_pipeline_result_t *pipeline_result) {
    if (pipeline_result == 0) return;

    pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    pipeline_result->evidence_level = 1u;

    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_NULL_ARGUMENT) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN;
        pipeline_result->evidence_level = 0u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_INTERNAL_ERROR) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN;
        pipeline_result->evidence_level = 0u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_PARSE;
        pipeline_result->evidence_level = 1u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK ||
        pipeline_result->error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC;
        pipeline_result->evidence_level = 1u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_MODEL_NOT_OK) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_MODEL;
        pipeline_result->evidence_level = 1u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_LOWERING;
        pipeline_result->evidence_level = 1u;
        return;
    }
    if (pipeline_result->error == LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION) {
        pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_EFFECT_CHECK;
        pipeline_result->evidence_level = 1u;
        return;
    }

    pipeline_result->last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_REPORT;
    pipeline_result->failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    pipeline_result->evidence_level = 2u;
}

latticra_status_t latticra_lat_pipeline_run_source_with_model(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_model_t *model_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    latticra_status_t parse_status;
    latticra_status_t semantic_status;
    latticra_status_t model_status;
    latticra_status_t lowering_status;

    if (source == 0 || parse_result == 0 || semantic_result == 0 || model_result == 0 || module == 0 || lowering_result == 0 || pipeline_result == 0) {
        if (pipeline_result != 0) {
            pipeline_result_default(pipeline_result);
            pipeline_result->status = LATTICRA_STATUS_NULL_ARGUMENT;
            pipeline_result->error = LATTICRA_LAT_PIPELINE_NULL_ARGUMENT;
            pipeline_result->source_len = source_len;
            finalize_pipeline_report_refinement(pipeline_result);
        }
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    pipeline_result_default(pipeline_result);

    parse_status = latticra_lat_parse_source(source, source_len, parse_result);
    if (parse_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = parse_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        pipeline_result->source_len = source_len;
        finalize_pipeline_report_refinement(pipeline_result);
        return parse_status;
    }

    semantic_status = latticra_lat_validate_module(parse_result, semantic_result);
    if (semantic_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = semantic_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        summarize_parse_semantic(source_len, parse_result, semantic_result, pipeline_result);
        finalize_pipeline_report_refinement(pipeline_result);
        return semantic_status;
    }

    model_status = latticra_lat_model_normalize_module(parse_result, semantic_result, model_result);
    if (model_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = model_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        summarize_parse_semantic(source_len, parse_result, semantic_result, pipeline_result);
        finalize_pipeline_report_refinement(pipeline_result);
        return model_status;
    }

    lowering_status = latticra_lir_lower_lat_module(parse_result, semantic_result, module, lowering_result);
    if (lowering_status != LATTICRA_STATUS_OK) {
        pipeline_result->status = lowering_status;
        pipeline_result->error = LATTICRA_LAT_PIPELINE_INTERNAL_ERROR;
        summarize_parse_semantic(source_len, parse_result, semantic_result, pipeline_result);
        finalize_pipeline_report_refinement(pipeline_result);
        return lowering_status;
    }

    summarize_pipeline(source_len, parse_result, semantic_result, model_result, module, lowering_result, pipeline_result);

    if (parse_result->error != LATTICRA_LAT_PARSE_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_PARSE_NOT_OK;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->error == LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION ||
        model_result->error == LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION ||
        lowering_result->error == LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION ||
        !no_effect_ok(parse_result, semantic_result, model_result, module, lowering_result)) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION;
        pipeline_result->no_effect_chain_ok = 0;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->error != LATTICRA_LAT_SEMANTIC_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->semantic_valid != 1) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }
    if (model_result->error != LATTICRA_LAT_MODEL_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_MODEL_NOT_OK;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }
    if (lowering_result->error != LATTICRA_LAT_TO_LIR_OK || module->error != LATTICRA_LIR_OK) {
        pipeline_result->error = LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK;
        finalize_pipeline_report_refinement(pipeline_result);
        return LATTICRA_STATUS_OK;
    }

    pipeline_result->error = LATTICRA_LAT_PIPELINE_OK;
    pipeline_result->parse_ok = 1;
    pipeline_result->semantic_ok = 1;
    pipeline_result->model_ok = 1;
    pipeline_result->lowering_ok = 1;
    pipeline_result->lir_ok = 1;
    pipeline_result->no_effect_chain_ok = 1;
    finalize_pipeline_report_refinement(pipeline_result);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_pipeline_run_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result) {
    latticra_lat_model_t model_result;
    return latticra_lat_pipeline_run_source_with_model(
        source,
        source_len,
        parse_result,
        semantic_result,
        &model_result,
        module,
        lowering_result,
        pipeline_result);
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
        "model_error=%s\n"
        "lowering_error=%s\n"
        "lir_error=%s\n"
        "module=%s\n"
        "source_len=%zu\n"
        "semantic_valid=%d\n"
        "declaration_count=%zu\n"
        "clause_count=%zu\n"
        "model_declaration_count=%zu\n"
        "model_clause_count=%zu\n"
        "first_transition_source_index=%zu\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "last_completed_stage=%s\n"
        "failed_stage=%s\n"
        "parse_ok=%d\n"
        "semantic_ok=%d\n"
        "model_ok=%d\n"
        "lowering_ok=%d\n"
        "lir_ok=%d\n"
        "no_effect_chain_ok=%d\n"
        "evidence_level=%u\n"
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
        latticra_lat_model_error_label(result->model_error),
        latticra_lat_to_lir_error_label(result->lowering_error),
        latticra_lir_error_label(result->lir_error),
        result->module_name,
        result->source_len,
        result->semantic_valid,
        result->declaration_count,
        result->clause_count,
        result->model_declaration_count,
        result->model_clause_count,
        result->first_transition_source_index,
        result->node_count,
        result->edge_count,
        latticra_lat_pipeline_stage_label(result->last_completed_stage),
        latticra_lat_pipeline_stage_label(result->failed_stage),
        result->parse_ok,
        result->semantic_ok,
        result->model_ok,
        result->lowering_ok,
        result->lir_ok,
        result->no_effect_chain_ok,
        result->evidence_level,
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
