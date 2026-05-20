#include "latticra/l_ui_renderer.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void span_default(latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void authority_default(latticra_l_ui_render_authority_summary_t *authority) {
    if (authority == 0) return;
    authority->status = LATTICRA_STATUS_OK;
    authority->status_label[0] = '\0';
    authority->validator_label[0] = '\0';
    authority->requested_effect_label[0] = '\0';
    authority->denial_reason[0] = '\0';
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static void result_default(latticra_l_ui_render_result_t *result) {
    size_t index;
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_RENDER_OK;
    result->mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    result->card_name[0] = '\0';
    result->effect[0] = '\0';
    result->boundary[0] = '\0';
    for (index = 0u; index < LATTICRA_L_UI_AST_RAIL_MAX; index++) {
        result->rail_names[index][0] = '\0';
        result->rail_field_counts[index] = 0u;
        result->rail_text_counts[index] = 0u;
        span_default(&result->rail_spans[index]);
    }
    for (index = 0u; index < LATTICRA_L_UI_AST_FIELD_MAX; index++) {
        result->field_names[index][0] = '\0';
        result->field_bindings[index][0] = '\0';
        result->field_binding_prefixes[index][0] = '\0';
        span_default(&result->field_spans[index]);
        span_default(&result->field_binding_spans[index]);
    }
    for (index = 0u; index < LATTICRA_L_UI_AST_TEXT_MAX; index++) {
        result->text_value_lens[index] = 0u;
        result->text_escaped_values[index][0] = '\0';
        span_default(&result->text_spans[index]);
    }
    result->rail_count = 0u;
    result->field_count = 0u;
    result->text_count = 0u;
    result->binding_count = 0u;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->section_count = 0u;
    result->report_classification[0] = '\0';
    result->detail_level[0] = '\0';
    result->section_sequence[0] = '\0';
    result->no_effect_chain[0] = '\0';
    result->evidence_level[0] = '\0';
    result->detailed_report_available = 0;
    result->detailed_section_count = 0u;
    span_default(&result->span);
    authority_default(&result->authority);
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static int copy_checked(char *destination, size_t destination_len, const char *source) {
    size_t source_len;
    if (destination == 0 || destination_len == 0u) return 0;
    destination[0] = '\0';
    if (source == 0) return 1;
    source_len = strlen(source);
    if (source_len >= destination_len) return 0;
    (void)memcpy(destination, source, source_len + 1u);
    return 1;
}

static int copy_binding_prefix(char *destination, size_t destination_len, const char *binding) {
    const char *dot;
    size_t len;
    if (destination == 0 || destination_len == 0u) return 0;
    destination[0] = '\0';
    if (binding == 0) return 1;
    dot = strchr(binding, '.');
    len = dot == 0 ? strlen(binding) : (size_t)(dot - binding);
    if (len >= destination_len) return 0;
    (void)memcpy(destination, binding, len);
    destination[len] = '\0';
    return 1;
}

static int no_effect_flags_ok(
    int no_effect,
    int execution_allowed,
    int mutation_allowed,
    int server_allowed,
    int recovery_allowed,
    int hardware_allowed) {
    return no_effect == 1 &&
           execution_allowed == 0 &&
           mutation_allowed == 0 &&
           server_allowed == 0 &&
           recovery_allowed == 0 &&
           hardware_allowed == 0;
}

static int authority_ok(const latticra_l_ui_render_authority_summary_t *authority) {
    if (authority == 0) return 0;
    return authority->status == LATTICRA_STATUS_OK &&
           no_effect_flags_ok(authority->no_effect,
                              authority->execution_allowed,
                              authority->mutation_allowed,
                              authority->server_allowed,
                              authority->recovery_allowed,
                              authority->hardware_allowed);
}

static int mode_is_supported(latticra_l_ui_render_mode_t mode) {
    return mode == LATTICRA_L_UI_RENDER_MODE_SUMMARY ||
           mode == LATTICRA_L_UI_RENDER_MODE_DETAILED ||
           mode == LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY ||
           mode == LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY;
}

const char *latticra_l_ui_render_error_label(latticra_l_ui_render_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_RENDER_OK: return "ok";
    case LATTICRA_L_UI_RENDER_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_L_UI_RENDER_INVALID_INPUT: return "invalid_input";
    case LATTICRA_L_UI_RENDER_PARSER_FAILED: return "parser_failed";
    case LATTICRA_L_UI_RENDER_SEMANTIC_FAILED: return "semantic_failed";
    case LATTICRA_L_UI_RENDER_LIR_FAILED: return "lir_failed";
    case LATTICRA_L_UI_RENDER_AUTHORITY_FAILED: return "authority_failed";
    case LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE: return "unsupported_render_mode";
    case LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT: return "unsupported_effect";
    case LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY: return "unsupported_boundary";
    case LATTICRA_L_UI_RENDER_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_l_ui_render_mode_label(latticra_l_ui_render_mode_t mode) {
    switch (mode) {
    case LATTICRA_L_UI_RENDER_MODE_SUMMARY: return "summary";
    case LATTICRA_L_UI_RENDER_MODE_DETAILED: return "detailed";
    case LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY: return "diagnostics_only";
    case LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY: return "authority_only";
    default: return "unknown";
    }
}

static const char *report_classification_label(latticra_l_ui_render_mode_t mode) {
    switch (mode) {
    case LATTICRA_L_UI_RENDER_MODE_SUMMARY: return "summary_report";
    case LATTICRA_L_UI_RENDER_MODE_DETAILED: return "detailed_report";
    case LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY: return "diagnostics_report";
    case LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY: return "authority_report";
    default: return "unknown_report";
    }
}

static const char *section_sequence_label(latticra_l_ui_render_mode_t mode) {
    if (mode == LATTICRA_L_UI_RENDER_MODE_DETAILED) {
        return "HEADER,CARD,AUTHORITY,RAILS,FIELDS,TEXT,BINDINGS,LIR,SOURCE_SPANS,NO_EFFECT_FLAGS";
    }
    return "HEADER";
}

static latticra_status_t set_error(
    latticra_l_ui_render_result_t *result,
    latticra_l_ui_render_error_t error) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result->status = LATTICRA_STATUS_OK;
    result->error = error;
    return LATTICRA_STATUS_OK;
}

static int copy_snapshot_metadata(
    const latticra_l_ui_render_request_t *request,
    latticra_l_ui_render_result_t *result) {
    size_t index;

    for (index = 0u; index < request->ast->rail_count; index++) {
        if (!copy_checked(result->rail_names[index],
                          sizeof(result->rail_names[index]),
                          request->ast->rails[index].name)) return 0;
        result->rail_field_counts[index] = request->ast->rails[index].field_count;
        result->rail_text_counts[index] = request->ast->rails[index].text_count;
        result->rail_spans[index] = request->ast->rails[index].span;
    }

    for (index = 0u; index < request->ast->field_count; index++) {
        if (!copy_checked(result->field_names[index],
                          sizeof(result->field_names[index]),
                          request->ast->fields[index].name) ||
            !copy_checked(result->field_bindings[index],
                          sizeof(result->field_bindings[index]),
                          request->ast->fields[index].binding) ||
            !copy_binding_prefix(result->field_binding_prefixes[index],
                                 sizeof(result->field_binding_prefixes[index]),
                                 request->ast->fields[index].binding)) {
            return 0;
        }
        result->field_spans[index] = request->ast->fields[index].span;
        result->field_binding_spans[index] = request->ast->fields[index].binding_span;
    }

    for (index = 0u; index < request->lir->text_count; index++) {
        result->text_value_lens[index] = request->lir->texts[index].value_len;
        if (!copy_checked(result->text_escaped_values[index],
                          sizeof(result->text_escaped_values[index]),
                          request->lir->texts[index].escaped_value)) return 0;
        result->text_spans[index] = request->lir->texts[index].source_span;
    }

    return 1;
}

latticra_status_t latticra_l_ui_render(
    const latticra_l_ui_render_request_t *request,
    latticra_l_ui_render_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result_default(result);

    if (request == 0) {
        result->error = LATTICRA_L_UI_RENDER_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result->mode = request->mode;

    if (!mode_is_supported(request->mode)) {
        return set_error(result, LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE);
    }

    if (request->ast == 0 || request->semantic == 0 ||
        request->lir == 0 || request->authority == 0) {
        return set_error(result, LATTICRA_L_UI_RENDER_NULL_ARGUMENT);
    }

    if (request->ast->parse_result.error != LATTICRA_L_UI_PARSE_OK) {
        return set_error(result, LATTICRA_L_UI_RENDER_PARSER_FAILED);
    }

    if (request->semantic->status != LATTICRA_STATUS_OK ||
        request->semantic->error != LATTICRA_L_UI_SEMANTIC_OK ||
        request->semantic->parser_error != LATTICRA_L_UI_PARSE_OK) {
        return set_error(result, LATTICRA_L_UI_RENDER_SEMANTIC_FAILED);
    }

    if (request->lir->status != LATTICRA_STATUS_OK ||
        request->lir->error != LATTICRA_LIR_OK) {
        return set_error(result, LATTICRA_L_UI_RENDER_LIR_FAILED);
    }

    if (!authority_ok(request->authority)) {
        return set_error(result, LATTICRA_L_UI_RENDER_AUTHORITY_FAILED);
    }

    if (!no_effect_flags_ok(request->ast->no_effect,
                            request->ast->execution_allowed,
                            request->ast->mutation_allowed,
                            request->ast->server_allowed,
                            request->ast->recovery_allowed,
                            request->ast->hardware_allowed) ||
        !no_effect_flags_ok(request->semantic->no_effect,
                            request->semantic->execution_allowed,
                            request->semantic->mutation_allowed,
                            request->semantic->server_allowed,
                            request->semantic->recovery_allowed,
                            request->semantic->hardware_allowed) ||
        !no_effect_flags_ok(request->lir->no_effect,
                            request->lir->execution_allowed,
                            request->lir->mutation_allowed,
                            request->lir->server_allowed,
                            request->lir->recovery_allowed,
                            request->lir->hardware_allowed)) {
        return set_error(result, LATTICRA_L_UI_RENDER_AUTHORITY_FAILED);
    }

    if (strcmp(request->ast->card.effect, "none") != 0 ||
        strcmp(request->lir->effect, "none") != 0) {
        return set_error(result, LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT);
    }

    if (strcmp(request->ast->card.boundary, "preview_only") != 0 ||
        strcmp(request->lir->boundary, "preview_only") != 0) {
        return set_error(result, LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY);
    }

    if (request->ast->rail_count > LATTICRA_L_UI_AST_RAIL_MAX ||
        request->ast->field_count > LATTICRA_L_UI_AST_FIELD_MAX ||
        request->lir->text_count > LATTICRA_L_UI_AST_TEXT_MAX) {
        return set_error(result, LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED);
    }

    if (!copy_checked(result->card_name, sizeof(result->card_name), request->ast->card.name) ||
        !copy_checked(result->effect, sizeof(result->effect), request->ast->card.effect) ||
        !copy_checked(result->boundary, sizeof(result->boundary), request->ast->card.boundary) ||
        !copy_checked(result->authority.status_label, sizeof(result->authority.status_label), request->authority->status_label) ||
        !copy_checked(result->authority.validator_label, sizeof(result->authority.validator_label), request->authority->validator_label) ||
        !copy_checked(result->authority.requested_effect_label, sizeof(result->authority.requested_effect_label), request->authority->requested_effect_label) ||
        !copy_checked(result->authority.denial_reason, sizeof(result->authority.denial_reason), request->authority->denial_reason) ||
        !copy_checked(result->report_classification, sizeof(result->report_classification), report_classification_label(request->mode)) ||
        !copy_checked(result->detail_level, sizeof(result->detail_level), latticra_l_ui_render_mode_label(request->mode)) ||
        !copy_checked(result->section_sequence, sizeof(result->section_sequence), section_sequence_label(request->mode)) ||
        !copy_checked(result->no_effect_chain, sizeof(result->no_effect_chain), "preserved") ||
        !copy_checked(result->evidence_level, sizeof(result->evidence_level), "metadata")) {
        return set_error(result, LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED);
    }

    result->rail_count = request->ast->rail_count;
    result->field_count = request->ast->field_count;
    result->text_count = request->lir->text_count;
    result->binding_count = request->lir->binding_count;
    result->node_count = request->lir->node_count;
    result->edge_count = request->lir->edge_count;
    result->section_count = request->mode == LATTICRA_L_UI_RENDER_MODE_DETAILED ? LATTICRA_L_UI_RENDER_DETAILED_SECTION_COUNT : 1u;
    result->detailed_report_available = request->mode == LATTICRA_L_UI_RENDER_MODE_DETAILED ? 1 : 0;
    result->detailed_section_count = result->detailed_report_available ? LATTICRA_L_UI_RENDER_DETAILED_SECTION_COUNT : 0u;
    result->span = request->ast->card.span;
    result->authority.status = request->authority->status;
    result->authority.no_effect = request->authority->no_effect;
    result->authority.execution_allowed = request->authority->execution_allowed;
    result->authority.mutation_allowed = request->authority->mutation_allowed;
    result->authority.server_allowed = request->authority->server_allowed;
    result->authority.recovery_allowed = request->authority->recovery_allowed;
    result->authority.hardware_allowed = request->authority->hardware_allowed;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;

    if (!copy_snapshot_metadata(request, result)) {
        return set_error(result, LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED);
    }

    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_RENDER_OK;
    return LATTICRA_STATUS_OK;
}

static int appendf(char *buffer, size_t buffer_len, size_t *used, const char *format, ...) {
    int written;
    va_list args;
    if (buffer == 0 || used == 0 || format == 0 || *used >= buffer_len) return 0;
    va_start(args, format);
    written = vsnprintf(buffer + *used, buffer_len - *used, format, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) return 0;
    *used += (size_t)written;
    return 1;
}

static void clear_buffer(char *buffer, size_t buffer_len) {
    if (buffer != 0 && buffer_len > 0u) buffer[0] = '\0';
}

static int append_header(const latticra_l_ui_render_result_t *result, char *buffer, size_t buffer_len, size_t *used) {
    return appendf(buffer, buffer_len, used, "LATTICRA L-UI RENDER REPORT\n") &&
           appendf(buffer, buffer_len, used, "status=%d\n", (int)result->status) &&
           appendf(buffer, buffer_len, used, "error=%s\n", latticra_l_ui_render_error_label(result->error)) &&
           appendf(buffer, buffer_len, used, "mode=%s\n", latticra_l_ui_render_mode_label(result->mode)) &&
           appendf(buffer, buffer_len, used, "report_classification=%s\n", result->report_classification) &&
           appendf(buffer, buffer_len, used, "detail_level=%s\n", result->detail_level) &&
           appendf(buffer, buffer_len, used, "detailed_report_available=%d\n", result->detailed_report_available) &&
           appendf(buffer, buffer_len, used, "detailed_section_count=%lu\n", (unsigned long)result->detailed_section_count) &&
           appendf(buffer, buffer_len, used, "section_sequence=%s\n", result->section_sequence) &&
           appendf(buffer, buffer_len, used, "no_effect_chain=%s\n", result->no_effect_chain) &&
           appendf(buffer, buffer_len, used, "evidence_level=%s\n", result->evidence_level) &&
           appendf(buffer, buffer_len, used, "card=%s\n", result->card_name) &&
           appendf(buffer, buffer_len, used, "effect=%s\n", result->effect) &&
           appendf(buffer, buffer_len, used, "boundary=%s\n", result->boundary) &&
           appendf(buffer, buffer_len, used, "rail_count=%lu\n", (unsigned long)result->rail_count) &&
           appendf(buffer, buffer_len, used, "field_count=%lu\n", (unsigned long)result->field_count) &&
           appendf(buffer, buffer_len, used, "text_count=%lu\n", (unsigned long)result->text_count) &&
           appendf(buffer, buffer_len, used, "binding_count=%lu\n", (unsigned long)result->binding_count) &&
           appendf(buffer, buffer_len, used, "node_count=%lu\n", (unsigned long)result->node_count) &&
           appendf(buffer, buffer_len, used, "edge_count=%lu\n", (unsigned long)result->edge_count) &&
           appendf(buffer, buffer_len, used, "section_count=%lu\n", (unsigned long)result->section_count) &&
           appendf(buffer, buffer_len, used, "no_effect=%d\n", result->no_effect) &&
           appendf(buffer, buffer_len, used, "execution_allowed=%d\n", result->execution_allowed) &&
           appendf(buffer, buffer_len, used, "mutation_allowed=%d\n", result->mutation_allowed) &&
           appendf(buffer, buffer_len, used, "server_allowed=%d\n", result->server_allowed) &&
           appendf(buffer, buffer_len, used, "recovery_allowed=%d\n", result->recovery_allowed) &&
           appendf(buffer, buffer_len, used, "hardware_allowed=%d\n", result->hardware_allowed) &&
           appendf(buffer, buffer_len, used, "authority_status=%s\n", result->authority.status_label) &&
           appendf(buffer, buffer_len, used, "authority_validator=%s\n", result->authority.validator_label) &&
           appendf(buffer, buffer_len, used, "authority_requested_effect=%s\n", result->authority.requested_effect_label) &&
           appendf(buffer, buffer_len, used, "authority_denial_reason=%s\n", result->authority.denial_reason) &&
           appendf(buffer, buffer_len, used, "span_start_offset=%lu\n", (unsigned long)result->span.start_offset) &&
           appendf(buffer, buffer_len, used, "span_end_offset=%lu\n", (unsigned long)result->span.end_offset) &&
           appendf(buffer, buffer_len, used, "span_start_line=%lu\n", (unsigned long)result->span.start_line) &&
           appendf(buffer, buffer_len, used, "span_start_column=%lu\n", (unsigned long)result->span.start_column) &&
           appendf(buffer, buffer_len, used, "span_end_line=%lu\n", (unsigned long)result->span.end_line) &&
           appendf(buffer, buffer_len, used, "span_end_column=%lu\n", (unsigned long)result->span.end_column);
}

static int append_rails(const latticra_l_ui_render_result_t *result, char *buffer, size_t buffer_len, size_t *used) {
    size_t index;
    for (index = 0u; index < result->rail_count; index++) {
        if (!appendf(buffer, buffer_len, used, "rail[%lu].name=%s\n", (unsigned long)index, result->rail_names[index]) ||
            !appendf(buffer, buffer_len, used, "rail[%lu].field_count=%lu\n", (unsigned long)index, (unsigned long)result->rail_field_counts[index]) ||
            !appendf(buffer, buffer_len, used, "rail[%lu].text_count=%lu\n", (unsigned long)index, (unsigned long)result->rail_text_counts[index]) ||
            !appendf(buffer, buffer_len, used, "rail[%lu].span_start_offset=%lu\n", (unsigned long)index, (unsigned long)result->rail_spans[index].start_offset) ||
            !appendf(buffer, buffer_len, used, "rail[%lu].span_end_offset=%lu\n", (unsigned long)index, (unsigned long)result->rail_spans[index].end_offset)) return 0;
    }
    return 1;
}

static int append_fields(const latticra_l_ui_render_result_t *result, char *buffer, size_t buffer_len, size_t *used) {
    size_t index;
    for (index = 0u; index < result->field_count; index++) {
        if (!appendf(buffer, buffer_len, used, "field[%lu].name=%s\n", (unsigned long)index, result->field_names[index]) ||
            !appendf(buffer, buffer_len, used, "field[%lu].binding=%s\n", (unsigned long)index, result->field_bindings[index]) ||
            !appendf(buffer, buffer_len, used, "field[%lu].binding_prefix=%s\n", (unsigned long)index, result->field_binding_prefixes[index]) ||
            !appendf(buffer, buffer_len, used, "field[%lu].span_start_offset=%lu\n", (unsigned long)index, (unsigned long)result->field_spans[index].start_offset) ||
            !appendf(buffer, buffer_len, used, "field[%lu].binding_span_start_offset=%lu\n", (unsigned long)index, (unsigned long)result->field_binding_spans[index].start_offset)) return 0;
    }
    return 1;
}

static int append_texts(const latticra_l_ui_render_result_t *result, char *buffer, size_t buffer_len, size_t *used) {
    size_t index;
    for (index = 0u; index < result->text_count; index++) {
        if (!appendf(buffer, buffer_len, used, "text[%lu].value_len=%lu\n", (unsigned long)index, (unsigned long)result->text_value_lens[index]) ||
            !appendf(buffer, buffer_len, used, "text[%lu].escaped_value=%s\n", (unsigned long)index, result->text_escaped_values[index]) ||
            !appendf(buffer, buffer_len, used, "text[%lu].span_start_offset=%lu\n", (unsigned long)index, (unsigned long)result->text_spans[index].start_offset) ||
            !appendf(buffer, buffer_len, used, "text[%lu].span_end_offset=%lu\n", (unsigned long)index, (unsigned long)result->text_spans[index].end_offset)) return 0;
    }
    return 1;
}

static int append_bindings(const latticra_l_ui_render_result_t *result, char *buffer, size_t buffer_len, size_t *used) {
    size_t index;
    size_t limit = result->binding_count < result->field_count ? result->binding_count : result->field_count;
    for (index = 0u; index < limit; index++) {
        if (!appendf(buffer, buffer_len, used, "binding[%lu].target=%s\n", (unsigned long)index, result->field_bindings[index]) ||
            !appendf(buffer, buffer_len, used, "binding[%lu].prefix=%s\n", (unsigned long)index, result->field_binding_prefixes[index])) return 0;
    }
    return 1;
}

static int append_detailed(
    const latticra_l_ui_render_result_t *result,
    char *buffer,
    size_t buffer_len,
    size_t *used) {
    return appendf(buffer, buffer_len, used, "SECTION HEADER\n") &&
           appendf(buffer, buffer_len, used, "SECTION CARD\n") &&
           appendf(buffer, buffer_len, used, "card.name=%s\n", result->card_name) &&
           appendf(buffer, buffer_len, used, "SECTION AUTHORITY\n") &&
           appendf(buffer, buffer_len, used, "authority.status=%s\n", result->authority.status_label) &&
           appendf(buffer, buffer_len, used, "authority.validator=%s\n", result->authority.validator_label) &&
           appendf(buffer, buffer_len, used, "authority.requested_effect=%s\n", result->authority.requested_effect_label) &&
           appendf(buffer, buffer_len, used, "SECTION RAILS\n") &&
           append_rails(result, buffer, buffer_len, used) &&
           appendf(buffer, buffer_len, used, "SECTION FIELDS\n") &&
           append_fields(result, buffer, buffer_len, used) &&
           appendf(buffer, buffer_len, used, "SECTION TEXT\n") &&
           append_texts(result, buffer, buffer_len, used) &&
           appendf(buffer, buffer_len, used, "SECTION BINDINGS\n") &&
           append_bindings(result, buffer, buffer_len, used) &&
           appendf(buffer, buffer_len, used, "SECTION LIR\n") &&
           appendf(buffer, buffer_len, used, "lir.node_count=%lu\n", (unsigned long)result->node_count) &&
           appendf(buffer, buffer_len, used, "lir.edge_count=%lu\n", (unsigned long)result->edge_count) &&
           appendf(buffer, buffer_len, used, "SECTION SOURCE_SPANS\n") &&
           appendf(buffer, buffer_len, used, "source_span.start_offset=%lu\n", (unsigned long)result->span.start_offset) &&
           appendf(buffer, buffer_len, used, "source_span.end_offset=%lu\n", (unsigned long)result->span.end_offset) &&
           appendf(buffer, buffer_len, used, "SECTION NO_EFFECT_FLAGS\n") &&
           appendf(buffer, buffer_len, used, "no_effect=%d\n", result->no_effect) &&
           appendf(buffer, buffer_len, used, "execution_allowed=%d\n", result->execution_allowed) &&
           appendf(buffer, buffer_len, used, "mutation_allowed=%d\n", result->mutation_allowed) &&
           appendf(buffer, buffer_len, used, "server_allowed=%d\n", result->server_allowed) &&
           appendf(buffer, buffer_len, used, "recovery_allowed=%d\n", result->recovery_allowed) &&
           appendf(buffer, buffer_len, used, "hardware_allowed=%d\n", result->hardware_allowed);
}

latticra_status_t latticra_l_ui_render_report(
    const latticra_l_ui_render_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    clear_buffer(buffer, buffer_len);

    if (!append_header(result, buffer, buffer_len, &used)) {
        clear_buffer(buffer, buffer_len);
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    if (result->mode == LATTICRA_L_UI_RENDER_MODE_DETAILED) {
        if (!append_detailed(result, buffer, buffer_len, &used)) {
            clear_buffer(buffer, buffer_len);
            return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        }
    }

    return LATTICRA_STATUS_OK;
}
