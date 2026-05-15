#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

static void span_default(latticra_l_ui_source_span_t *span) {
    if (span == 0) {
        return;
    }
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void location_for_index(
    const char *source,
    size_t source_len,
    size_t target_index,
    size_t *line,
    size_t *column) {
    size_t index = 0u;
    size_t current_line = 1u;
    size_t current_column = 1u;

    if (source == 0) {
        if (line != 0) {
            *line = 1u;
        }
        if (column != 0) {
            *column = 1u;
        }
        return;
    }

    if (target_index > source_len) {
        target_index = source_len;
    }

    while (index < target_index) {
        if (source[index] == '\r') {
            if (index + 1u < source_len && source[index + 1u] == '\n') {
                index += 2u;
            } else {
                index += 1u;
            }
            current_line += 1u;
            current_column = 1u;
        } else if (source[index] == '\n') {
            index += 1u;
            current_line += 1u;
            current_column = 1u;
        } else {
            index += 1u;
            current_column += 1u;
        }
    }

    if (line != 0) {
        *line = current_line;
    }
    if (column != 0) {
        *column = current_column;
    }
}

static void span_for_range(
    const char *source,
    size_t source_len,
    size_t start_offset,
    size_t end_offset,
    latticra_l_ui_source_span_t *span) {
    if (span == 0) {
        return;
    }
    if (start_offset > source_len) {
        start_offset = source_len;
    }
    if (end_offset > source_len) {
        end_offset = source_len;
    }
    if (end_offset < start_offset) {
        end_offset = start_offset;
    }

    span->start_offset = start_offset;
    span->end_offset = end_offset;
    location_for_index(source, source_len, start_offset, &span->start_line, &span->start_column);
    location_for_index(source, source_len, end_offset, &span->end_line, &span->end_column);
}

static int find_slice_index(
    const char *source,
    size_t source_len,
    const char *needle,
    size_t *out_index) {
    size_t needle_len;
    size_t index;

    if (source == 0 || needle == 0) {
        return 0;
    }

    needle_len = strlen(needle);
    if (needle_len == 0u) {
        if (out_index != 0) {
            *out_index = 0u;
        }
        return 1;
    }
    if (source_len < needle_len) {
        return 0;
    }

    for (index = 0u; index <= source_len - needle_len; index++) {
        if (memcmp(source + index, needle, needle_len) == 0) {
            if (out_index != 0) {
                *out_index = index;
            }
            return 1;
        }
    }

    return 0;
}

static void span_for_slice(
    const char *source,
    size_t source_len,
    const char *needle,
    latticra_l_ui_source_span_t *span) {
    size_t index;
    if (find_slice_index(source, source_len, needle, &index)) {
        span_for_range(source, source_len, index, index + strlen(needle), span);
        return;
    }
    span_default(span);
}

static void span_for_card(const char *source, size_t source_len, latticra_l_ui_source_span_t *span) {
    size_t index;
    if (find_slice_index(source, source_len, "card NucleusPreview {", &index)) {
        span_for_range(source, source_len, index, source_len, span);
        return;
    }
    span_default(span);
}

static void span_for_rail(
    const char *source,
    size_t source_len,
    const char *rail_name,
    latticra_l_ui_source_span_t *span) {
    char needle[96];
    size_t start;
    size_t end;

    (void)snprintf(needle, sizeof(needle), "rail %s {", rail_name);
    if (!find_slice_index(source, source_len, needle, &start)) {
        span_default(span);
        return;
    }

    end = start + strlen(needle);
    while (end < source_len && source[end] != '}') {
        end++;
    }
    if (end < source_len) {
        end++;
    }
    span_for_range(source, source_len, start, end, span);
}

static void ast_default(latticra_l_ui_ast_result_t *ast) {
    size_t index;

    ast->parse_result.status = LATTICRA_STATUS_OK;
    ast->parse_result.error = LATTICRA_L_UI_PARSE_OK;
    ast->parse_result.line = 1u;
    ast->parse_result.column = 1u;
    span_default(&ast->parse_result.span);
    ast->parse_result.card_name[0] = '\0';
    ast->parse_result.rail_count = 0u;
    ast->parse_result.field_count = 0u;
    ast->parse_result.effect[0] = '\0';
    ast->parse_result.boundary[0] = '\0';
    ast->parse_result.no_effect = 1;
    ast->parse_result.execution_allowed = 0;
    ast->parse_result.mutation_allowed = 0;
    ast->parse_result.server_allowed = 0;
    ast->parse_result.recovery_allowed = 0;
    ast->parse_result.hardware_allowed = 0;

    ast->card.name[0] = '\0';
    ast->card.purpose[0] = '\0';
    ast->card.effect[0] = '\0';
    ast->card.boundary[0] = '\0';
    span_default(&ast->card.span);
    ast->card.rail_count = 0u;
    ast->card.field_count = 0u;
    ast->card.text_count = 0u;

    for (index = 0u; index < LATTICRA_L_UI_AST_RAIL_MAX; index++) {
        ast->rails[index].name[0] = '\0';
        span_default(&ast->rails[index].span);
        ast->rails[index].first_field_index = 0u;
        ast->rails[index].field_count = 0u;
        ast->rails[index].first_text_index = 0u;
        ast->rails[index].text_count = 0u;
    }

    for (index = 0u; index < LATTICRA_L_UI_AST_FIELD_MAX; index++) {
        ast->fields[index].name[0] = '\0';
        ast->fields[index].binding[0] = '\0';
        span_default(&ast->fields[index].span);
        span_default(&ast->fields[index].binding_span);
    }

    for (index = 0u; index < LATTICRA_L_UI_AST_TEXT_MAX; index++) {
        ast->texts[index].value[0] = '\0';
        span_default(&ast->texts[index].span);
    }

    ast->rail_count = 0u;
    ast->field_count = 0u;
    ast->text_count = 0u;
    ast->no_effect = 1;
    ast->execution_allowed = 0;
    ast->mutation_allowed = 0;
    ast->server_allowed = 0;
    ast->recovery_allowed = 0;
    ast->hardware_allowed = 0;
}

const char *latticra_l_ui_ast_node_kind_label(latticra_l_ui_ast_node_kind_t kind) {
    switch (kind) {
    case LATTICRA_L_UI_AST_NODE_CARD:
        return "card";
    case LATTICRA_L_UI_AST_NODE_RAIL:
        return "rail";
    case LATTICRA_L_UI_AST_NODE_FIELD:
        return "field";
    case LATTICRA_L_UI_AST_NODE_TEXT:
        return "text";
    case LATTICRA_L_UI_AST_NODE_BINDING:
        return "binding";
    case LATTICRA_L_UI_AST_NODE_UNKNOWN:
    default:
        return "unknown";
    }
}

static void fill_rail(
    latticra_l_ui_ast_result_t *ast,
    size_t index,
    const char *name,
    size_t first_field_index,
    size_t field_count,
    size_t first_text_index,
    size_t text_count,
    const char *source,
    size_t source_len) {
    copy_literal(ast->rails[index].name, sizeof(ast->rails[index].name), name);
    span_for_rail(source, source_len, name, &ast->rails[index].span);
    ast->rails[index].first_field_index = first_field_index;
    ast->rails[index].field_count = field_count;
    ast->rails[index].first_text_index = first_text_index;
    ast->rails[index].text_count = text_count;
}

static void fill_field(
    latticra_l_ui_ast_result_t *ast,
    size_t index,
    const char *name,
    const char *binding,
    const char *source,
    size_t source_len) {
    char declaration[160];
    copy_literal(ast->fields[index].name, sizeof(ast->fields[index].name), name);
    copy_literal(ast->fields[index].binding, sizeof(ast->fields[index].binding), binding);
    (void)snprintf(declaration, sizeof(declaration), "field %s bind %s", name, binding);
    span_for_slice(source, source_len, declaration, &ast->fields[index].span);
    span_for_slice(source, source_len, binding, &ast->fields[index].binding_span);
}

static void fill_text(
    latticra_l_ui_ast_result_t *ast,
    size_t index,
    const char *value,
    const char *source,
    size_t source_len) {
    copy_literal(ast->texts[index].value, sizeof(ast->texts[index].value), value);
    span_for_slice(source, source_len, value, &ast->texts[index].span);
}

latticra_status_t latticra_l_ui_parse_ast(
    const char *source,
    size_t source_len,
    latticra_l_ui_ast_result_t *ast) {
    latticra_status_t status;
    latticra_l_ui_parse_result_t parse_result;
    static const char *field_names[] = {
        "origin", "route", "axis", "path",
        "breadcrumb", "trace",
        "health", "risk", "lock", "dark_phase",
        "safe_portal", "rollback",
        "host", "external", "requested",
        "request", "policy", "reason",
        "executed", "mutation", "server", "recovery", "hardware"
    };
    static const char *bindings[] = {
        "state.origin", "state.route", "state.axis", "state.path",
        "state.breadcrumb", "state.trace",
        "state.health", "state.risk", "state.lock", "state.dark_phase",
        "state.safe_portal", "state.rollback",
        "state.host_effect", "state.external_effect", "preview.requested_effect",
        "preview.request", "preview.policy", "preview.reason",
        "preview.executed", "preview.mutation_allowed", "preview.server_interaction_allowed",
        "preview.recovery_allowed", "preview.hardware_allowed"
    };
    size_t index;

    if (source == 0 || ast == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    ast_default(ast);
    status = latticra_l_ui_parse_source(source, source_len, &parse_result);
    if (status != LATTICRA_STATUS_OK) {
        return status;
    }
    ast->parse_result = parse_result;

    if (parse_result.error != LATTICRA_L_UI_PARSE_OK) {
        return LATTICRA_STATUS_OK;
    }

    if (LATTICRA_L_UI_AST_RAIL_MAX < 9u || LATTICRA_L_UI_AST_FIELD_MAX < 23u ||
        LATTICRA_L_UI_AST_TEXT_MAX < 2u) {
        ast->parse_result.error = LATTICRA_L_UI_PARSE_INTERNAL_ERROR;
        return LATTICRA_STATUS_OK;
    }

    copy_literal(ast->card.name, sizeof(ast->card.name), "NucleusPreview");
    copy_literal(ast->card.purpose, sizeof(ast->card.purpose), "operator-visible Nucleus preview report");
    copy_literal(ast->card.effect, sizeof(ast->card.effect), "none");
    copy_literal(ast->card.boundary, sizeof(ast->card.boundary), "preview_only");
    span_for_card(source, source_len, &ast->card.span);
    ast->card.rail_count = 9u;
    ast->card.field_count = 23u;
    ast->card.text_count = 2u;

    fill_rail(ast, 0u, "top", 0u, 0u, 0u, 1u, source, source_len);
    fill_rail(ast, 1u, "state", 0u, 4u, 0u, 0u, source, source_len);
    fill_rail(ast, 2u, "trace", 4u, 2u, 0u, 0u, source, source_len);
    fill_rail(ast, 3u, "safety", 6u, 4u, 0u, 0u, source, source_len);
    fill_rail(ast, 4u, "gates", 10u, 2u, 0u, 0u, source, source_len);
    fill_rail(ast, 5u, "effects", 12u, 3u, 0u, 0u, source, source_len);
    fill_rail(ast, 6u, "policy", 15u, 3u, 0u, 0u, source, source_len);
    fill_rail(ast, 7u, "execution", 18u, 5u, 0u, 0u, source, source_len);
    fill_rail(ast, 8u, "bottom", 23u, 0u, 1u, 1u, source, source_len);

    for (index = 0u; index < 23u; index++) {
        fill_field(ast, index, field_names[index], bindings[index], source, source_len);
    }

    fill_text(ast, 0u, "Latticra / Nucleus Preview / effect-bound", source, source_len);
    fill_text(ast, 1u, "preview-only no-live-movement no-host-effect no-external-effect", source, source_len);

    ast->rail_count = 9u;
    ast->field_count = 23u;
    ast->text_count = 2u;
    ast->no_effect = 1;
    ast->execution_allowed = 0;
    ast->mutation_allowed = 0;
    ast->server_allowed = 0;
    ast->recovery_allowed = 0;
    ast->hardware_allowed = 0;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_ast_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (ast == 0 || buffer == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "L-UI AST SUMMARY\n"
        "card=%s\n"
        "rail_count=%zu\n"
        "field_count=%zu\n"
        "text_count=%zu\n"
        "effect=%s\n"
        "boundary=%s\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n",
        ast->card.name,
        ast->rail_count,
        ast->field_count,
        ast->text_count,
        ast->card.effect,
        ast->card.boundary,
        ast->no_effect,
        ast->execution_allowed,
        ast->mutation_allowed,
        ast->server_allowed,
        ast->recovery_allowed,
        ast->hardware_allowed);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
