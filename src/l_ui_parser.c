#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

static void location_default(size_t *line, size_t *column) {
    if (line != 0) {
        *line = 1u;
    }
    if (column != 0) {
        *column = 1u;
    }
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
        location_default(line, column);
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

static int find_slice_span(
    const char *source,
    size_t source_len,
    const char *needle,
    latticra_l_ui_source_span_t *span) {
    size_t index;
    if (!find_slice_index(source, source_len, needle, &index)) {
        span_default(span);
        return 0;
    }
    span_for_range(source, source_len, index, index + strlen(needle), span);
    return 1;
}

static int contains_slice(const char *source, size_t source_len, const char *needle) {
    return find_slice_index(source, source_len, needle, 0);
}

static void card_body_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *card = "card NucleusPreview {";
    size_t card_index;
    size_t body_index;

    if (find_slice_index(source, source_len, card, &card_index)) {
        body_index = card_index + strlen(card) - 1u;
        span_for_range(source, source_len, body_index, body_index, span);
        return;
    }

    span_default(span);
}

static int find_unbalanced_brace_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    size_t index;
    size_t first_open_index = 0u;
    int has_open = 0;
    int depth = 0;

    for (index = 0u; index < source_len; index++) {
        if (source[index] == '{') {
            if (depth == 0) {
                first_open_index = index;
                has_open = 1;
            }
            depth++;
        } else if (source[index] == '}') {
            if (depth == 0) {
                span_for_range(source, source_len, index, index + 1u, span);
                return 1;
            }
            depth--;
            if (depth == 0) {
                has_open = 0;
            }
        }
    }

    if (depth != 0 && has_open) {
        span_for_range(source, source_len, first_open_index, first_open_index + 1u, span);
        return 1;
    }

    span_default(span);
    return 0;
}

static int find_unterminated_string_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    size_t index;
    size_t opening_quote_index = 0u;
    int in_string = 0;
    int escaped = 0;

    for (index = 0u; index < source_len; index++) {
        char ch = source[index];
        if (escaped) {
            escaped = 0;
            continue;
        }
        if (ch == '\\') {
            escaped = 1;
            continue;
        }
        if (ch == '"') {
            if (!in_string) {
                opening_quote_index = index;
            }
            in_string = !in_string;
        }
    }

    if (in_string) {
        span_for_range(source, source_len, opening_quote_index, source_len, span);
        return 1;
    }

    span_default(span);
    return 0;
}

static void set_safe_defaults(latticra_l_ui_parse_result_t *result) {
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_PARSE_OK;
    result->line = 1u;
    result->column = 1u;
    span_default(&result->span);
    result->card_name[0] = '\0';
    result->rail_count = 0u;
    result->field_count = 0u;
    copy_literal(result->effect, sizeof(result->effect), "none");
    copy_literal(result->boundary, sizeof(result->boundary), "preview_only");
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static latticra_status_t set_error_with_span(
    latticra_l_ui_parse_result_t *result,
    latticra_l_ui_parse_error_t error,
    const latticra_l_ui_source_span_t *span) {
    set_safe_defaults(result);
    result->error = error;
    if (span != 0) {
        result->span = *span;
        result->line = span->start_line == 0u ? 1u : span->start_line;
        result->column = span->start_column == 0u ? 1u : span->start_column;
    }
    return LATTICRA_STATUS_OK;
}

static latticra_status_t set_error_at(
    latticra_l_ui_parse_result_t *result,
    latticra_l_ui_parse_error_t error,
    size_t line,
    size_t column) {
    latticra_l_ui_source_span_t span;
    span_default(&span);
    span.start_line = line == 0u ? 1u : line;
    span.start_column = column == 0u ? 1u : column;
    span.end_line = span.start_line;
    span.end_column = span.start_column;
    return set_error_with_span(result, error, &span);
}

static latticra_status_t set_error(latticra_l_ui_parse_result_t *result, latticra_l_ui_parse_error_t error) {
    return set_error_at(result, error, 1u, 1u);
}

static int has_unsupported_effect_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *effects[] = {
        "effect read",
        "effect local_mutation",
        "effect host_mutation",
        "effect network",
        "effect hardware",
        "effect boot",
        "effect recovery",
        "effect external"
    };
    size_t index;

    for (index = 0u; index < sizeof(effects) / sizeof(effects[0]); index++) {
        if (find_slice_span(source, source_len, effects[index], span)) {
            return 1;
        }
    }

    span_default(span);
    return 0;
}

static int has_forbidden_marker_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *markers[] = {
        "execute ",
        "host_mutation",
        "effect network",
        "effect hardware",
        "effect boot",
        "effect recovery",
        "self_update",
        "server call",
        "server_interaction {"
    };
    size_t index;

    for (index = 0u; index < sizeof(markers) / sizeof(markers[0]); index++) {
        if (find_slice_span(source, source_len, markers[index], span)) {
            return 1;
        }
    }

    span_default(span);
    return 0;
}

static int find_unknown_binding_prefix_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *prefixes[] = {
        " bind host.",
        " bind network.",
        " bind hardware.",
        " bind server."
    };
    size_t index;
    size_t found_index;
    size_t target_start;
    size_t target_len;

    for (index = 0u; index < sizeof(prefixes) / sizeof(prefixes[0]); index++) {
        if (find_slice_index(source, source_len, prefixes[index], &found_index)) {
            target_start = found_index + strlen(" bind ");
            target_len = strlen(prefixes[index]) - strlen(" bind ");
            span_for_range(source, source_len, target_start, target_start + target_len, span);
            return 1;
        }
    }

    span_default(span);
    return 0;
}

static latticra_l_ui_parse_error_t validate_required_rails_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *rails[] = {
        "rail top {",
        "rail state {",
        "rail trace {",
        "rail safety {",
        "rail gates {",
        "rail effects {",
        "rail policy {",
        "rail execution {",
        "rail bottom {"
    };
    size_t index;

    for (index = 0u; index < sizeof(rails) / sizeof(rails[0]); index++) {
        if (!contains_slice(source, source_len, rails[index])) {
            card_body_span(source, source_len, span);
            return LATTICRA_L_UI_PARSE_MISSING_RAIL;
        }
    }

    span_default(span);
    return LATTICRA_L_UI_PARSE_OK;
}

static latticra_l_ui_parse_error_t validate_required_bindings_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span) {
    const char *bindings[] = {
        "field origin bind state.origin",
        "field route bind state.route",
        "field axis bind state.axis",
        "field path bind state.path",
        "field breadcrumb bind state.breadcrumb",
        "field trace bind state.trace",
        "field health bind state.health",
        "field risk bind state.risk",
        "field lock bind state.lock",
        "field dark_phase bind state.dark_phase",
        "field safe_portal bind state.safe_portal",
        "field rollback bind state.rollback",
        "field host bind state.host_effect",
        "field external bind state.external_effect",
        "field requested bind preview.requested_effect",
        "field request bind preview.request",
        "field policy bind preview.policy",
        "field reason bind preview.reason",
        "field executed bind preview.executed",
        "field mutation bind preview.mutation_allowed",
        "field server bind preview.server_interaction_allowed",
        "field recovery bind preview.recovery_allowed",
        "field hardware bind preview.hardware_allowed"
    };
    size_t index;

    for (index = 0u; index < sizeof(bindings) / sizeof(bindings[0]); index++) {
        if (!contains_slice(source, source_len, bindings[index])) {
            card_body_span(source, source_len, span);
            return LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING;
        }
    }

    span_default(span);
    return LATTICRA_L_UI_PARSE_OK;
}

const char *latticra_l_ui_parse_error_label(latticra_l_ui_parse_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_PARSE_OK:
        return "ok";
    case LATTICRA_L_UI_PARSE_NULL_ARGUMENT:
        return "null_argument";
    case LATTICRA_L_UI_PARSE_EMPTY_SOURCE:
        return "empty_source";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION:
        return "unsupported_version";
    case LATTICRA_L_UI_PARSE_MISSING_CARD:
        return "missing_card";
    case LATTICRA_L_UI_PARSE_MISSING_PURPOSE:
        return "missing_purpose";
    case LATTICRA_L_UI_PARSE_MISSING_EFFECT:
        return "missing_effect";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT:
        return "unsupported_effect";
    case LATTICRA_L_UI_PARSE_MISSING_BOUNDARY:
        return "missing_boundary";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY:
        return "unsupported_boundary";
    case LATTICRA_L_UI_PARSE_MISSING_RAIL:
        return "missing_rail";
    case LATTICRA_L_UI_PARSE_UNKNOWN_RAIL:
        return "unknown_rail";
    case LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX:
        return "unknown_binding_prefix";
    case LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING:
        return "missing_required_binding";
    case LATTICRA_L_UI_PARSE_UNTERMINATED_STRING:
        return "unterminated_string";
    case LATTICRA_L_UI_PARSE_UNBALANCED_BRACE:
        return "unbalanced_brace";
    case LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER:
        return "forbidden_behavior_marker";
    case LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE:
        return "source_too_large";
    case LATTICRA_L_UI_PARSE_INTERNAL_ERROR:
    default:
        return "internal_error";
    }
}

latticra_status_t latticra_l_ui_parse_source(
    const char *source,
    size_t source_len,
    latticra_l_ui_parse_result_t *result) {
    latticra_l_ui_parse_error_t rail_error;
    latticra_l_ui_parse_error_t binding_error;
    latticra_l_ui_source_span_t span;

    if (source == 0 || result == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    set_safe_defaults(result);
    span_default(&span);

    if (source_len == 0u) {
        return set_error(result, LATTICRA_L_UI_PARSE_EMPTY_SOURCE);
    }

    if (source_len > LATTICRA_L_UI_SOURCE_MAX) {
        return set_error(result, LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE);
    }

    if (find_unterminated_string_span(source, source_len, &span)) {
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNTERMINATED_STRING, &span);
    }

    if (find_unbalanced_brace_span(source, source_len, &span)) {
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, &span);
    }

    if (!contains_slice(source, source_len, "lui 0.1")) {
        if (!find_slice_span(source, source_len, "lui", &span)) {
            span_default(&span);
        }
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION, &span);
    }

    if (!contains_slice(source, source_len, "card NucleusPreview {")) {
        return set_error(result, LATTICRA_L_UI_PARSE_MISSING_CARD);
    }

    if (!contains_slice(source, source_len, "purpose ")) {
        card_body_span(source, source_len, &span);
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_MISSING_PURPOSE, &span);
    }

    if (!contains_slice(source, source_len, "effect ")) {
        card_body_span(source, source_len, &span);
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_MISSING_EFFECT, &span);
    }

    if (has_unsupported_effect_span(source, source_len, &span)) {
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &span);
    }

    if (!contains_slice(source, source_len, "effect none")) {
        if (!find_slice_span(source, source_len, "effect ", &span)) {
            span_default(&span);
        }
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &span);
    }

    if (!contains_slice(source, source_len, "boundary ")) {
        card_body_span(source, source_len, &span);
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_MISSING_BOUNDARY, &span);
    }

    if (!contains_slice(source, source_len, "boundary preview_only")) {
        find_slice_span(source, source_len, "boundary ", &span);
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY, &span);
    }

    if (has_forbidden_marker_span(source, source_len, &span)) {
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER, &span);
    }

    rail_error = validate_required_rails_span(source, source_len, &span);
    if (rail_error != LATTICRA_L_UI_PARSE_OK) {
        return set_error_with_span(result, rail_error, &span);
    }

    if (find_unknown_binding_prefix_span(source, source_len, &span)) {
        return set_error_with_span(result, LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX, &span);
    }

    binding_error = validate_required_bindings_span(source, source_len, &span);
    if (binding_error != LATTICRA_L_UI_PARSE_OK) {
        return set_error_with_span(result, binding_error, &span);
    }

    copy_literal(result->card_name, sizeof(result->card_name), "NucleusPreview");
    copy_literal(result->effect, sizeof(result->effect), "none");
    copy_literal(result->boundary, sizeof(result->boundary), "preview_only");
    result->rail_count = 9u;
    result->field_count = 23u;
    result->error = LATTICRA_L_UI_PARSE_OK;
    result->line = 1u;
    result->column = 1u;
    span_default(&result->span);

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_parse_result_report(
    const latticra_l_ui_parse_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == 0 || buffer == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "L-UI PARSE RESULT\n"
        "status=%d\n"
        "error=%s\n"
        "line=%zu\n"
        "column=%zu\n"
        "card_name=%s\n"
        "rail_count=%zu\n"
        "field_count=%zu\n"
        "effect=%s\n"
        "boundary=%s\n"
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
        latticra_l_ui_parse_error_label(result->error),
        result->line,
        result->column,
        result->card_name,
        result->rail_count,
        result->field_count,
        result->effect,
        result->boundary,
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
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
