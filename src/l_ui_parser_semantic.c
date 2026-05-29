#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void span_default(latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static const char *expected_rail_name(size_t index) {
    static const char *rails[] = {
        "top", "state", "trace", "safety", "gates", "effects", "policy", "execution", "bottom"
    };
    if (index >= sizeof(rails) / sizeof(rails[0])) return "";
    return rails[index];
}

static size_t expected_rail_field_count(size_t index) {
    static const size_t counts[] = { 0u, 4u, 2u, 4u, 2u, 3u, 3u, 6u, 0u };
    if (index >= sizeof(counts) / sizeof(counts[0])) return 0u;
    return counts[index];
}

static size_t expected_rail_text_count(size_t index) {
    static const size_t counts[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u };
    if (index >= sizeof(counts) / sizeof(counts[0])) return 0u;
    return counts[index];
}

static size_t expected_rail_first_field_index(size_t index) {
    static const size_t indices[] = { 0u, 0u, 4u, 6u, 10u, 12u, 15u, 18u, 24u };
    if (index >= sizeof(indices) / sizeof(indices[0])) return 0u;
    return indices[index];
}

static size_t expected_rail_first_text_index(size_t index) {
    static const size_t indices[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u };
    if (index >= sizeof(indices) / sizeof(indices[0])) return 0u;
    return indices[index];
}

static const char *expected_field_name(size_t index) {
    static const char *names[] = {
        "origin", "route", "axis", "path", "breadcrumb", "trace", "health", "risk", "lock",
        "dark_phase", "safe_portal", "rollback", "host", "external", "requested", "request",
        "policy", "reason", "executed", "mutation", "server", "network", "recovery", "hardware"
    };
    if (index >= sizeof(names) / sizeof(names[0])) return "";
    return names[index];
}

static const char *expected_binding(size_t index) {
    static const char *bindings[] = {
        "state.origin", "state.route", "state.axis", "state.path", "state.breadcrumb", "state.trace",
        "state.health", "state.risk", "state.lock", "state.dark_phase", "state.safe_portal",
        "state.rollback", "state.host_effect", "state.external_effect", "preview.requested_effect",
        "preview.request", "preview.policy", "preview.reason", "preview.executed", "preview.mutation_allowed",
        "preview.server_interaction_allowed", "preview.network_allowed", "preview.recovery_allowed",
        "preview.hardware_allowed"
    };
    if (index >= sizeof(bindings) / sizeof(bindings[0])) return "";
    return bindings[index];
}

static int starts_with_allowed_binding_prefix(const char *binding) {
    if (binding == 0) return 0;
    return strncmp(binding, "state.", strlen("state.")) == 0 ||
           strncmp(binding, "preview.", strlen("preview.")) == 0;
}

const char *latticra_l_ui_semantic_error_label(latticra_l_ui_semantic_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_SEMANTIC_OK: return "ok";
    case LATTICRA_L_UI_SEMANTIC_PARSER_FAILED: return "parser_failed";
    case LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL: return "duplicate_rail";
    case LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL: return "missing_required_rail";
    case LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD: return "duplicate_field";
    case LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH: return "field_rail_mismatch";
    case LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH: return "binding_field_mismatch";
    case LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET: return "unsupported_binding_target";
    case LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH: return "text_rail_mismatch";
    case LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH: return "card_count_mismatch";
    case LATTICRA_L_UI_SEMANTIC_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

static void semantic_default(latticra_l_ui_semantic_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_SEMANTIC_OK;
    result->parser_error = LATTICRA_L_UI_PARSE_OK;
    span_default(&result->span);
    result->rail_index = 0u;
    result->field_index = 0u;
    result->text_index = 0u;
    result->card_name[0] = '\0';
    result->rail_name[0] = '\0';
    result->field_name[0] = '\0';
    result->binding[0] = '\0';
    result->rail_count = 0u;
    result->field_count = 0u;
    result->text_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->network_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static void copy_ast_summary(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result) {
    if (ast == 0 || result == 0) return;
    copy_literal(result->card_name, sizeof(result->card_name), ast->card.name);
    result->rail_count = ast->rail_count;
    result->field_count = ast->field_count;
    result->text_count = ast->text_count;
    result->no_effect = ast->no_effect;
    result->execution_allowed = ast->execution_allowed;
    result->mutation_allowed = ast->mutation_allowed;
    result->server_allowed = ast->server_allowed;
    result->network_allowed = ast->network_allowed;
    result->recovery_allowed = ast->recovery_allowed;
    result->hardware_allowed = ast->hardware_allowed;
}

static latticra_status_t set_semantic_error(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result,
    latticra_l_ui_semantic_error_t error,
    size_t rail_index,
    size_t field_index,
    size_t text_index,
    const latticra_l_ui_source_span_t *span) {
    result->error = error;
    result->rail_index = rail_index;
    result->field_index = field_index;
    result->text_index = text_index;
    if (span != 0) result->span = *span;
    if (rail_index < ast->rail_count) copy_literal(result->rail_name, sizeof(result->rail_name), ast->rails[rail_index].name);
    if (field_index < ast->field_count) {
        copy_literal(result->field_name, sizeof(result->field_name), ast->fields[field_index].name);
        copy_literal(result->binding, sizeof(result->binding), ast->fields[field_index].binding);
    }
    return LATTICRA_STATUS_OK;
}

static latticra_status_t parser_failed_result(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result) {
    result->error = LATTICRA_L_UI_SEMANTIC_PARSER_FAILED;
    result->parser_error = ast->parse_result.error;
    result->span = ast->parse_result.span;
    result->rail_count = 0u;
    result->field_count = 0u;
    result->text_count = 0u;
    return LATTICRA_STATUS_OK;
}

static latticra_status_t check_duplicate_rails(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result) {
    size_t index;
    size_t other;
    for (index = 0u; index < ast->rail_count; index++) {
        for (other = index + 1u; other < ast->rail_count; other++) {
            if (ast->rails[index].name[0] != '\0' && strcmp(ast->rails[index].name, ast->rails[other].name) == 0) {
                return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL, other, 0u, 0u, &ast->rails[other].span);
            }
        }
    }
    return LATTICRA_STATUS_OK;
}

static latticra_status_t check_duplicate_fields(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result) {
    size_t index;
    size_t other;
    for (index = 0u; index < ast->field_count; index++) {
        for (other = index + 1u; other < ast->field_count; other++) {
            if (ast->fields[index].name[0] != '\0' && strcmp(ast->fields[index].name, ast->fields[other].name) == 0) {
                return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD, 0u, other, 0u, &ast->fields[other].span);
            }
        }
    }
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_validate_semantics(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result) {
    size_t index;
    latticra_status_t status;

    if (ast == 0 || result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    semantic_default(result);
    copy_ast_summary(ast, result);
    result->parser_error = ast->parse_result.error;

    if (ast->parse_result.error != LATTICRA_L_UI_PARSE_OK) return parser_failed_result(ast, result);

    if (strcmp(ast->card.name, "NucleusPreview") != 0 ||
        strcmp(ast->card.effect, "none") != 0 ||
        strcmp(ast->card.boundary, "preview_only") != 0 ||
        ast->rail_count != 9u || ast->field_count != 24u || ast->text_count != 2u ||
        ast->card.rail_count != ast->rail_count || ast->card.field_count != ast->field_count ||
        ast->card.text_count != ast->text_count) {
        return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH, 0u, 0u, 0u, &ast->card.span);
    }

    if (ast->no_effect != 1 || ast->execution_allowed != 0 || ast->mutation_allowed != 0 ||
        ast->server_allowed != 0 || ast->network_allowed != 0 ||
        ast->recovery_allowed != 0 || ast->hardware_allowed != 0) {
        return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH, 0u, 0u, 0u, &ast->card.span);
    }

    status = check_duplicate_rails(ast, result);
    if (result->error != LATTICRA_L_UI_SEMANTIC_OK) return status;
    status = check_duplicate_fields(ast, result);
    if (result->error != LATTICRA_L_UI_SEMANTIC_OK) return status;

    for (index = 0u; index < 9u; index++) {
        const latticra_l_ui_ast_rail_t *rail = &ast->rails[index];
        if (rail->name[0] == '\0' || strcmp(rail->name, expected_rail_name(index)) != 0) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL, index, 0u, 0u, &rail->span);
        }
        if (rail->first_field_index != expected_rail_first_field_index(index) ||
            rail->field_count != expected_rail_field_count(index)) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH, index, rail->first_field_index, rail->first_text_index, &rail->span);
        }
        if (rail->first_text_index != expected_rail_first_text_index(index) ||
            rail->text_count != expected_rail_text_count(index)) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH, index, rail->first_field_index, rail->first_text_index, &rail->span);
        }
    }

    for (index = 0u; index < 24u; index++) {
        const latticra_l_ui_ast_field_t *field = &ast->fields[index];
        if (field->name[0] == '\0' || strcmp(field->name, expected_field_name(index)) != 0) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH, 0u, index, 0u, &field->span);
        }
        if (!starts_with_allowed_binding_prefix(field->binding)) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET, 0u, index, 0u, &field->binding_span);
        }
        if (strcmp(field->binding, expected_binding(index)) != 0) {
            return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH, 0u, index, 0u, &field->binding_span);
        }
    }

    if (ast->rails[0].first_text_index != 0u || ast->rails[0].text_count != 1u ||
        ast->rails[8].first_text_index != 1u || ast->rails[8].text_count != 1u ||
        ast->texts[0].value_len == 0u || ast->texts[1].value_len == 0u) {
        return set_semantic_error(ast, result, LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH, 0u, 0u, 0u, &ast->texts[0].span);
    }

    result->error = LATTICRA_L_UI_SEMANTIC_OK;
    result->parser_error = LATTICRA_L_UI_PARSE_OK;
    result->span = ast->card.span;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_semantic_report(
    const latticra_l_ui_semantic_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    written = snprintf(
        buffer,
        buffer_len,
        "L-UI SEMANTIC VALIDATION RESULT\n"
        "status=%d\n"
        "error=%s\n"
        "parser_error=%s\n"
        "card=%s\n"
        "rail=%s\n"
        "field=%s\n"
        "binding=%s\n"
        "rail_index=%zu\n"
        "field_index=%zu\n"
        "text_index=%zu\n"
        "rail_count=%zu\n"
        "field_count=%zu\n"
        "text_count=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "network_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)result->status,
        latticra_l_ui_semantic_error_label(result->error),
        latticra_l_ui_parse_error_label(result->parser_error),
        result->card_name,
        result->rail_name,
        result->field_name,
        result->binding,
        result->rail_index,
        result->field_index,
        result->text_index,
        result->rail_count,
        result->field_count,
        result->text_count,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->server_allowed,
        result->network_allowed,
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
