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
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_RENDER_OK;
    result->mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    result->card_name[0] = '\0';
    result->effect[0] = '\0';
    result->boundary[0] = '\0';
    result->rail_count = 0u;
    result->field_count = 0u;
    result->text_count = 0u;
    result->binding_count = 0u;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->section_count = 0u;
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

static latticra_status_t set_error(
    latticra_l_ui_render_result_t *result,
    latticra_l_ui_render_error_t error) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result->status = LATTICRA_STATUS_OK;
    result->error = error;
    return LATTICRA_STATUS_OK;
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

    if (!copy_checked(result->card_name, sizeof(result->card_name), request->ast->card.name) ||
        !copy_checked(result->effect, sizeof(result->effect), request->ast->card.effect) ||
        !copy_checked(result->boundary, sizeof(result->boundary), request->ast->card.boundary) ||
        !copy_checked(result->authority.status_label, sizeof(result->authority.status_label), request->authority->status_label) ||
        !copy_checked(result->authority.validator_label, sizeof(result->authority.validator_label), request->authority->validator_label) ||
        !copy_checked(result->authority.requested_effect_label, sizeof(result->authority.requested_effect_label), request->authority->requested_effect_label) ||
        !copy_checked(result->authority.denial_reason, sizeof(result->authority.denial_reason), request->authority->denial_reason)) {
        return set_error(result, LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED);
    }

    result->rail_count = request->ast->rail_count;
    result->field_count = request->ast->field_count;
    result->text_count = request->ast->text_count;
    result->binding_count = request->lir->binding_count;
    result->node_count = request->lir->node_count;
    result->edge_count = request->lir->edge_count;
    result->section_count = request->mode == LATTICRA_L_UI_RENDER_MODE_DETAILED ? 10u : 1u;
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
           appendf(buffer, buffer_len, used, "rails.count=%lu\n", (unsigned long)result->rail_count) &&
           appendf(buffer, buffer_len, used, "SECTION FIELDS\n") &&
           appendf(buffer, buffer_len, used, "fields.count=%lu\n", (unsigned long)result->field_count) &&
           appendf(buffer, buffer_len, used, "SECTION TEXT\n") &&
           appendf(buffer, buffer_len, used, "text.count=%lu\n", (unsigned long)result->text_count) &&
           appendf(buffer, buffer_len, used, "SECTION BINDINGS\n") &&
           appendf(buffer, buffer_len, used, "bindings.count=%lu\n", (unsigned long)result->binding_count) &&
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
