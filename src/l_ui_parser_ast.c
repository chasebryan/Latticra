#include "latticra/l_ui_parser.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LATTICRA_L_UI_AST_ESCAPED_PURPOSE_MAX ((LATTICRA_L_UI_AST_PURPOSE_MAX * 4u) + 1u)
#define LATTICRA_L_UI_AST_ESCAPED_TEXT_MAX ((LATTICRA_L_UI_AST_PURPOSE_MAX * 4u) + 1u)

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source);
}

static void copy_bytes_compat(char *destination, size_t destination_len, const char *source, size_t source_len) {
    if (destination == 0 || destination_len == 0u) return;
    destination[0] = '\0';
    if (source == 0) return;
    if (source_len >= destination_len) return;
    (void)memcpy(destination, source, source_len);
    destination[source_len] = '\0';
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
        if (line != 0) *line = 1u;
        if (column != 0) *column = 1u;
        return;
    }
    if (target_index > source_len) target_index = source_len;
    while (index < target_index) {
        if (source[index] == '\r') {
            if (index + 1u < source_len && source[index + 1u] == '\n') index += 2u;
            else index += 1u;
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
    if (line != 0) *line = current_line;
    if (column != 0) *column = current_column;
}

static void span_for_range(
    const char *source,
    size_t source_len,
    size_t start_offset,
    size_t end_offset,
    latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    if (start_offset > source_len) start_offset = source_len;
    if (end_offset > source_len) end_offset = source_len;
    if (end_offset < start_offset) end_offset = start_offset;
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
    if (source == 0 || needle == 0) return 0;
    needle_len = strlen(needle);
    if (needle_len == 0u) {
        if (out_index != 0) *out_index = 0u;
        return 1;
    }
    if (source_len < needle_len) return 0;
    for (index = 0u; index <= source_len - needle_len; index++) {
        if (memcmp(source + index, needle, needle_len) == 0) {
            if (out_index != 0) *out_index = index;
            return 1;
        }
    }
    return 0;
}

static int find_slice_index_from(
    const char *source,
    size_t source_len,
    const char *needle,
    size_t start_index,
    size_t *out_index) {
    size_t needle_len;
    size_t index;
    if (source == 0 || needle == 0 || start_index > source_len) return 0;
    needle_len = strlen(needle);
    if (needle_len == 0u) {
        if (out_index != 0) *out_index = start_index;
        return 1;
    }
    if (source_len < needle_len || start_index > source_len - needle_len) return 0;
    for (index = start_index; index <= source_len - needle_len; index++) {
        if (memcmp(source + index, needle, needle_len) == 0) {
            if (out_index != 0) *out_index = index;
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
    while (end < source_len && source[end] != '}') end++;
    if (end < source_len) end++;
    span_for_range(source, source_len, start, end, span);
}

static int is_upper_hex_digit(unsigned char byte) {
    return (byte >= (unsigned char)'0' && byte <= (unsigned char)'9') ||
           (byte >= (unsigned char)'A' && byte <= (unsigned char)'F');
}

static unsigned char upper_hex_value(unsigned char byte) {
    if (byte >= (unsigned char)'0' && byte <= (unsigned char)'9') return (unsigned char)(byte - (unsigned char)'0');
    return (unsigned char)(10u + (byte - (unsigned char)'A'));
}

static latticra_status_t append_decoded_byte(
    char *destination,
    size_t destination_len,
    size_t *output_index,
    unsigned char byte) {
    if (destination == 0 || output_index == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (*output_index + 1u >= destination_len) {
        if (destination_len > 0u) destination[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    destination[*output_index] = (char)byte;
    *output_index += 1u;
    return LATTICRA_STATUS_OK;
}

static latticra_status_t decode_l_ui_string_literal_value(
    const char *source,
    size_t start_offset,
    size_t end_offset,
    char *destination,
    size_t destination_len,
    size_t *decoded_len) {
    size_t input_index;
    size_t output_index = 0u;

    if (decoded_len != 0) *decoded_len = 0u;
    if (source == 0 || destination == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (destination_len == 0u || end_offset < start_offset) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    destination[0] = '\0';
    input_index = start_offset;
    while (input_index < end_offset) {
        unsigned char byte = (unsigned char)source[input_index];
        unsigned char decoded;
        latticra_status_t status;

        if (byte == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        if (byte != (unsigned char)'\\') {
            status = append_decoded_byte(destination, destination_len, &output_index, byte);
            if (status != LATTICRA_STATUS_OK) return status;
            input_index += 1u;
            continue;
        }
        if (input_index + 1u >= end_offset) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

        byte = (unsigned char)source[input_index + 1u];
        if (byte == (unsigned char)'\\') {
            decoded = (unsigned char)'\\';
            input_index += 2u;
        } else if (byte == (unsigned char)'"') {
            decoded = (unsigned char)'"';
            input_index += 2u;
        } else if (byte == (unsigned char)'n') {
            decoded = (unsigned char)'\n';
            input_index += 2u;
        } else if (byte == (unsigned char)'r') {
            decoded = (unsigned char)'\r';
            input_index += 2u;
        } else if (byte == (unsigned char)'t') {
            decoded = (unsigned char)'\t';
            input_index += 2u;
        } else if (byte == (unsigned char)'x') {
            unsigned char high;
            unsigned char low;
            if (input_index + 3u >= end_offset) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            high = (unsigned char)source[input_index + 2u];
            low = (unsigned char)source[input_index + 3u];
            if (!is_upper_hex_digit(high) || !is_upper_hex_digit(low)) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            decoded = (unsigned char)((upper_hex_value(high) << 4u) | upper_hex_value(low));
            input_index += 4u;
        } else {
            return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        }
        status = append_decoded_byte(destination, destination_len, &output_index, decoded);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    destination[output_index] = '\0';
    if (decoded_len != 0) *decoded_len = output_index;
    return LATTICRA_STATUS_OK;
}

static latticra_status_t extract_decoded_quoted_value_after_token(
    const char *source,
    size_t source_len,
    const char *token,
    size_t occurrence,
    char *destination,
    size_t destination_len,
    size_t *decoded_len,
    latticra_l_ui_source_span_t *value_span) {
    size_t token_len;
    size_t search_index = 0u;
    size_t found_index = 0u;
    size_t found_count = 0u;
    size_t quote_index;
    size_t value_start;
    size_t value_end;
    int found_token = 0;
    int escaped = 0;

    if (source == 0 || token == 0 || destination == 0 || value_span == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    destination[0] = '\0';
    if (decoded_len != 0) *decoded_len = 0u;
    span_default(value_span);
    token_len = strlen(token);

    while (find_slice_index_from(source, source_len, token, search_index, &found_index)) {
        if (found_count == occurrence) {
            found_token = 1;
            break;
        }
        found_count++;
        search_index = found_index + token_len;
    }
    if (!found_token) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    quote_index = found_index + token_len;
    while (quote_index < source_len && (source[quote_index] == ' ' || source[quote_index] == '\t')) quote_index++;
    if (quote_index >= source_len || source[quote_index] != '"') return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    value_start = quote_index + 1u;
    value_end = value_start;
    while (value_end < source_len) {
        char ch = source[value_end];
        if (escaped) {
            escaped = 0;
            value_end++;
            continue;
        }
        if (ch == '\\') {
            escaped = 1;
            value_end++;
            continue;
        }
        if (ch == '"') {
            latticra_status_t status = decode_l_ui_string_literal_value(
                source,
                value_start,
                value_end,
                destination,
                destination_len,
                decoded_len);
            if (status != LATTICRA_STATUS_OK) return status;
            span_for_range(source, source_len, value_start, value_end, value_span);
            return LATTICRA_STATUS_OK;
        }
        value_end++;
    }
    return LATTICRA_STATUS_BUFFER_TOO_SMALL;
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
    ast->parse_result.network_allowed = 0;
    ast->parse_result.recovery_allowed = 0;
    ast->parse_result.hardware_allowed = 0;

    ast->card.name[0] = '\0';
    ast->card.purpose[0] = '\0';
    ast->card.purpose_len = 0u;
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
        ast->texts[index].value_len = 0u;
        span_default(&ast->texts[index].span);
    }
    ast->rail_count = 0u;
    ast->field_count = 0u;
    ast->text_count = 0u;
    ast->no_effect = 1;
    ast->execution_allowed = 0;
    ast->mutation_allowed = 0;
    ast->server_allowed = 0;
    ast->network_allowed = 0;
    ast->recovery_allowed = 0;
    ast->hardware_allowed = 0;
}

const char *latticra_l_ui_ast_node_kind_label(latticra_l_ui_ast_node_kind_t kind) {
    switch (kind) {
    case LATTICRA_L_UI_AST_NODE_CARD: return "card";
    case LATTICRA_L_UI_AST_NODE_RAIL: return "rail";
    case LATTICRA_L_UI_AST_NODE_FIELD: return "field";
    case LATTICRA_L_UI_AST_NODE_TEXT: return "text";
    case LATTICRA_L_UI_AST_NODE_BINDING: return "binding";
    case LATTICRA_L_UI_AST_NODE_UNKNOWN:
    default: return "unknown";
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
    size_t value_len,
    const latticra_l_ui_source_span_t *span) {
    copy_bytes_compat(ast->texts[index].value, sizeof(ast->texts[index].value), value, value_len);
    ast->texts[index].value_len = value_len;
    ast->texts[index].span = *span;
}

static latticra_status_t ast_internal_error(
    latticra_l_ui_ast_result_t *ast,
    const latticra_l_ui_parse_result_t *parse_result) {
    ast_default(ast);
    ast->parse_result = *parse_result;
    ast->parse_result.error = LATTICRA_L_UI_PARSE_INTERNAL_ERROR;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_parse_ast(
    const char *source,
    size_t source_len,
    latticra_l_ui_ast_result_t *ast) {
    latticra_status_t status;
    latticra_l_ui_parse_result_t parse_result;
    latticra_l_ui_source_span_t purpose_span;
    latticra_l_ui_source_span_t top_text_span;
    latticra_l_ui_source_span_t bottom_text_span;
    char extracted_purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
    char extracted_top_text[LATTICRA_L_UI_AST_PURPOSE_MAX];
    char extracted_bottom_text[LATTICRA_L_UI_AST_PURPOSE_MAX];
    size_t extracted_purpose_len = 0u;
    size_t extracted_top_text_len = 0u;
    size_t extracted_bottom_text_len = 0u;
    static const char *field_names[] = {
        "origin", "route", "axis", "path", "breadcrumb", "trace", "health", "risk", "lock",
        "dark_phase", "safe_portal", "rollback", "host", "external", "requested", "request",
        "policy", "reason", "executed", "mutation", "server", "recovery", "hardware"
    };
    static const char *bindings[] = {
        "state.origin", "state.route", "state.axis", "state.path", "state.breadcrumb", "state.trace",
        "state.health", "state.risk", "state.lock", "state.dark_phase", "state.safe_portal",
        "state.rollback", "state.host_effect", "state.external_effect", "preview.requested_effect",
        "preview.request", "preview.policy", "preview.reason", "preview.executed", "preview.mutation_allowed",
        "preview.server_interaction_allowed", "preview.recovery_allowed", "preview.hardware_allowed"
    };
    size_t index;

    if (source == 0 || ast == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    ast_default(ast);
    status = latticra_l_ui_parse_source(source, source_len, &parse_result);
    if (status != LATTICRA_STATUS_OK) return status;
    ast->parse_result = parse_result;
    if (parse_result.error != LATTICRA_L_UI_PARSE_OK) return LATTICRA_STATUS_OK;
    if (LATTICRA_L_UI_AST_RAIL_MAX < 9u || LATTICRA_L_UI_AST_FIELD_MAX < 23u || LATTICRA_L_UI_AST_TEXT_MAX < 2u) {
        return ast_internal_error(ast, &parse_result);
    }

    status = extract_decoded_quoted_value_after_token(
        source, source_len, "purpose ", 0u, extracted_purpose, sizeof(extracted_purpose), &extracted_purpose_len, &purpose_span);
    if (status != LATTICRA_STATUS_OK) return ast_internal_error(ast, &parse_result);
    status = extract_decoded_quoted_value_after_token(
        source, source_len, "text ", 0u, extracted_top_text, sizeof(extracted_top_text), &extracted_top_text_len, &top_text_span);
    if (status != LATTICRA_STATUS_OK) return ast_internal_error(ast, &parse_result);
    status = extract_decoded_quoted_value_after_token(
        source, source_len, "text ", 1u, extracted_bottom_text, sizeof(extracted_bottom_text), &extracted_bottom_text_len, &bottom_text_span);
    if (status != LATTICRA_STATUS_OK) return ast_internal_error(ast, &parse_result);

    copy_literal(ast->card.name, sizeof(ast->card.name), "NucleusPreview");
    copy_bytes_compat(ast->card.purpose, sizeof(ast->card.purpose), extracted_purpose, extracted_purpose_len);
    ast->card.purpose_len = extracted_purpose_len;
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

    for (index = 0u; index < 23u; index++) fill_field(ast, index, field_names[index], bindings[index], source, source_len);
    fill_text(ast, 0u, extracted_top_text, extracted_top_text_len, &top_text_span);
    fill_text(ast, 1u, extracted_bottom_text, extracted_bottom_text_len, &bottom_text_span);

    ast->rail_count = 9u;
    ast->field_count = 23u;
    ast->text_count = 2u;
    ast->no_effect = 1;
    ast->execution_allowed = 0;
    ast->mutation_allowed = 0;
    ast->server_allowed = 0;
    ast->network_allowed = 0;
    ast->recovery_allowed = 0;
    ast->hardware_allowed = 0;
    (void)purpose_span;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_ast_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (ast == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
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
        "network_allowed=%d\n"
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
        ast->network_allowed,
        ast->recovery_allowed,
        ast->hardware_allowed);
    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

static latticra_status_t append_text(char *buffer, size_t buffer_len, size_t *used, const char *format, ...) {
    va_list args;
    int written;
    size_t remaining;
    if (buffer == 0 || used == 0 || format == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (*used >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    remaining = buffer_len - *used;
    va_start(args, format);
    written = vsnprintf(buffer + *used, remaining, format, args);
    va_end(args);
    if (written < 0 || (size_t)written >= remaining) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    *used += (size_t)written;
    return LATTICRA_STATUS_OK;
}

static latticra_status_t escape_report_bytes(
    const char *input,
    size_t input_len,
    char *output,
    size_t output_len) {
    static const char hex[] = "0123456789ABCDEF";
    size_t input_index;
    size_t output_index = 0u;
    if (input == 0 || output == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (output_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    for (input_index = 0u; input_index < input_len; input_index++) {
        unsigned char byte = (unsigned char)input[input_index];
        const char *short_escape = 0;
        char hex_escape[4];
        size_t needed;

        if (byte == '\n') short_escape = "\\n";
        else if (byte == '\r') short_escape = "\\r";
        else if (byte == '\t') short_escape = "\\t";
        else if (byte == '"') short_escape = "\\\"";
        else if (byte == '\\') short_escape = "\\\\";

        if (short_escape != 0) {
            needed = strlen(short_escape);
            if (output_index + needed >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            (void)memcpy(output + output_index, short_escape, needed);
            output_index += needed;
        } else if (byte >= 0x20u && byte <= 0x7Eu) {
            if (output_index + 1u >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            output[output_index] = (char)byte;
            output_index++;
        } else {
            hex_escape[0] = '\\';
            hex_escape[1] = 'x';
            hex_escape[2] = hex[(byte >> 4u) & 0x0Fu];
            hex_escape[3] = hex[byte & 0x0Fu];
            if (output_index + sizeof(hex_escape) >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            (void)memcpy(output + output_index, hex_escape, sizeof(hex_escape));
            output_index += sizeof(hex_escape);
        }
    }
    output[output_index] = '\0';
    return LATTICRA_STATUS_OK;
}

static latticra_status_t append_span_fields(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const char *prefix,
    const latticra_l_ui_source_span_t *span) {
    const char *safe_prefix = prefix == 0 ? "" : prefix;
    latticra_status_t status;
    status = append_text(buffer, buffer_len, used, "%sspan_start_offset=%zu\n", safe_prefix, span->start_offset);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "%sspan_end_offset=%zu\n", safe_prefix, span->end_offset);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "%sspan_start_line=%zu\n", safe_prefix, span->start_line);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "%sspan_start_column=%zu\n", safe_prefix, span->start_column);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "%sspan_end_line=%zu\n", safe_prefix, span->end_line);
    if (status != LATTICRA_STATUS_OK) return status;
    return append_text(buffer, buffer_len, used, "%sspan_end_column=%zu\n", safe_prefix, span->end_column);
}

static latticra_status_t append_failed_parse_report(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const latticra_l_ui_ast_result_t *ast) {
    latticra_status_t status;
    status = append_text(buffer, buffer_len, used, "L-UI AST DETAILED REPORT\n");
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "parse_error=%s\n", latticra_l_ui_parse_error_label(ast->parse_result.error));
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "rail_count=0\nfield_count=0\ntext_count=0\n");
    if (status != LATTICRA_STATUS_OK) return status;
    return append_text(
        buffer,
        buffer_len,
        used,
        "no_effect=%d\nexecution_allowed=%d\nmutation_allowed=%d\nserver_allowed=%d\nnetwork_allowed=%d\nrecovery_allowed=%d\nhardware_allowed=%d\n",
        ast->no_effect,
        ast->execution_allowed,
        ast->mutation_allowed,
        ast->server_allowed,
        ast->network_allowed,
        ast->recovery_allowed,
        ast->hardware_allowed);
}

static latticra_status_t append_card_section(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const latticra_l_ui_ast_result_t *ast) {
    latticra_status_t status;
    char escaped_purpose[LATTICRA_L_UI_AST_ESCAPED_PURPOSE_MAX];
    status = escape_report_bytes(ast->card.purpose, ast->card.purpose_len, escaped_purpose, sizeof(escaped_purpose));
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "[card]\nkind=card\n");
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(
        buffer,
        buffer_len,
        used,
        "name=%s\npurpose=%s\npurpose_len=%zu\npurpose_escaped=%s\neffect=%s\nboundary=%s\nrail_count=%zu\nfield_count=%zu\ntext_count=%zu\n",
        ast->card.name,
        ast->card.purpose,
        ast->card.purpose_len,
        escaped_purpose,
        ast->card.effect,
        ast->card.boundary,
        ast->card.rail_count,
        ast->card.field_count,
        ast->card.text_count);
    if (status != LATTICRA_STATUS_OK) return status;
    return append_span_fields(buffer, buffer_len, used, "", &ast->card.span);
}

static latticra_status_t append_rail_section(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const latticra_l_ui_ast_result_t *ast,
    size_t index) {
    const latticra_l_ui_ast_rail_t *rail = &ast->rails[index];
    latticra_status_t status;
    status = append_text(buffer, buffer_len, used, "[rail %zu]\nkind=rail\n", index);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(
        buffer,
        buffer_len,
        used,
        "name=%s\nfirst_field_index=%zu\nfield_count=%zu\nfirst_text_index=%zu\ntext_count=%zu\n",
        rail->name,
        rail->first_field_index,
        rail->field_count,
        rail->first_text_index,
        rail->text_count);
    if (status != LATTICRA_STATUS_OK) return status;
    return append_span_fields(buffer, buffer_len, used, "", &rail->span);
}

static latticra_status_t append_field_section(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const latticra_l_ui_ast_result_t *ast,
    size_t index) {
    const latticra_l_ui_ast_field_t *field = &ast->fields[index];
    latticra_status_t status;
    status = append_text(buffer, buffer_len, used, "[field %zu]\nkind=field\n", index);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "name=%s\nbinding=%s\n", field->name, field->binding);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_span_fields(buffer, buffer_len, used, "", &field->span);
    if (status != LATTICRA_STATUS_OK) return status;
    return append_span_fields(buffer, buffer_len, used, "binding_", &field->binding_span);
}

static latticra_status_t append_text_section(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const latticra_l_ui_ast_result_t *ast,
    size_t index) {
    const latticra_l_ui_ast_text_t *text = &ast->texts[index];
    latticra_status_t status;
    char escaped_text[LATTICRA_L_UI_AST_ESCAPED_TEXT_MAX];
    status = escape_report_bytes(text->value, text->value_len, escaped_text, sizeof(escaped_text));
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_text(buffer, buffer_len, used, "[text %zu]\nkind=text\nvalue=%s\nvalue_len=%zu\nvalue_escaped=%s\n", index, text->value, text->value_len, escaped_text);
    if (status != LATTICRA_STATUS_OK) return status;
    return append_span_fields(buffer, buffer_len, used, "", &text->span);
}

latticra_status_t latticra_l_ui_ast_detailed_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len) {
    latticra_status_t status;
    size_t used = 0u;
    size_t index;
    if (ast == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (ast->parse_result.error != LATTICRA_L_UI_PARSE_OK) return append_failed_parse_report(buffer, buffer_len, &used, ast);

    status = append_text(
        buffer,
        buffer_len,
        &used,
        "L-UI AST DETAILED REPORT\ncard=%s\npurpose=%s\neffect=%s\nboundary=%s\nrail_count=%zu\nfield_count=%zu\ntext_count=%zu\nno_effect=%d\nexecution_allowed=%d\nmutation_allowed=%d\nserver_allowed=%d\nnetwork_allowed=%d\nrecovery_allowed=%d\nhardware_allowed=%d\n",
        ast->card.name,
        ast->card.purpose,
        ast->card.effect,
        ast->card.boundary,
        ast->rail_count,
        ast->field_count,
        ast->text_count,
        ast->no_effect,
        ast->execution_allowed,
        ast->mutation_allowed,
        ast->server_allowed,
        ast->network_allowed,
        ast->recovery_allowed,
        ast->hardware_allowed);
    if (status != LATTICRA_STATUS_OK) return status;
    status = append_card_section(buffer, buffer_len, &used, ast);
    if (status != LATTICRA_STATUS_OK) return status;
    for (index = 0u; index < ast->rail_count; index++) {
        status = append_rail_section(buffer, buffer_len, &used, ast, index);
        if (status != LATTICRA_STATUS_OK) return status;
    }
    for (index = 0u; index < ast->field_count; index++) {
        status = append_field_section(buffer, buffer_len, &used, ast, index);
        if (status != LATTICRA_STATUS_OK) return status;
    }
    for (index = 0u; index < ast->text_count; index++) {
        status = append_text_section(buffer, buffer_len, &used, ast, index);
        if (status != LATTICRA_STATUS_OK) return status;
    }
    return LATTICRA_STATUS_OK;
}
