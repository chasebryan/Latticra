#include "latticra/lat_parser.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void span_default(latticra_lat_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void result_default(latticra_lat_parse_result_t *result) {
    size_t index;
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_LAT_PARSE_OK;
    span_default(&result->span);
    result->module.module_name[0] = '\0';
    span_default(&result->module.span);
    result->module.declaration_count = 0u;
    result->module.state_count = 0u;
    result->module.policy_count = 0u;
    result->module.transition_count = 0u;
    result->module.assertion_count = 0u;
    result->module.effect_count = 0u;
    for (index = 0u; index < LATTICRA_LAT_DECLARATION_MAX; index++) {
        result->declarations[index].kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
        result->declarations[index].name[0] = '\0';
        result->declarations[index].source_name[0] = '\0';
        span_default(&result->declarations[index].span);
        result->declarations[index].first_clause_index = 0u;
        result->declarations[index].clause_count = 0u;
    }
    for (index = 0u; index < LATTICRA_LAT_CLAUSE_MAX; index++) {
        result->clauses[index].keyword[0] = '\0';
        result->clauses[index].left[0] = '\0';
        result->clauses[index].operator_text[0] = '\0';
        result->clauses[index].right[0] = '\0';
        result->clauses[index].effect = LATTICRA_LAT_EFFECT_UNKNOWN;
        span_default(&result->clauses[index].span);
    }
    result->declaration_count = 0u;
    result->clause_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

const char *latticra_lat_parse_error_label(latticra_lat_parse_error_t error) {
    switch (error) {
    case LATTICRA_LAT_PARSE_OK: return "ok";
    case LATTICRA_LAT_PARSE_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LAT_PARSE_EMPTY_SOURCE: return "empty_source";
    case LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE: return "source_too_large";
    case LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM: return "unsupported_extension_claim";
    case LATTICRA_LAT_PARSE_MISSING_MODULE: return "missing_module";
    case LATTICRA_LAT_PARSE_INVALID_MODULE_NAME: return "invalid_module_name";
    case LATTICRA_LAT_PARSE_UNBALANCED_BRACE: return "unbalanced_brace";
    case LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION: return "unknown_declaration";
    case LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME: return "invalid_declaration_name";
    case LATTICRA_LAT_PARSE_UNTERMINATED_STRING: return "unterminated_string";
    case LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE: return "invalid_string_escape";
    case LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE: return "invalid_hex_escape";
    case LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING: return "literal_nul_in_string";
    case LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER: return "forbidden_behavior_marker";
    case LATTICRA_LAT_PARSE_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_lat_declaration_kind_label(latticra_lat_declaration_kind_t kind) {
    switch (kind) {
    case LATTICRA_LAT_DECLARATION_STATE: return "state";
    case LATTICRA_LAT_DECLARATION_POLICY: return "policy";
    case LATTICRA_LAT_DECLARATION_TRANSITION: return "transition";
    case LATTICRA_LAT_DECLARATION_ASSERTION: return "assertion";
    case LATTICRA_LAT_DECLARATION_EFFECT: return "effect";
    case LATTICRA_LAT_DECLARATION_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_lat_effect_label(latticra_lat_effect_t effect) {
    switch (effect) {
    case LATTICRA_LAT_EFFECT_NONE: return "none";
    case LATTICRA_LAT_EFFECT_READ: return "read";
    case LATTICRA_LAT_EFFECT_LOCAL_MUTATION: return "local_mutation";
    case LATTICRA_LAT_EFFECT_HOST_MUTATION: return "host_mutation";
    case LATTICRA_LAT_EFFECT_NETWORK: return "network";
    case LATTICRA_LAT_EFFECT_HARDWARE: return "hardware";
    case LATTICRA_LAT_EFFECT_BOOT: return "boot";
    case LATTICRA_LAT_EFFECT_RECOVERY: return "recovery";
    case LATTICRA_LAT_EFFECT_EXTERNAL: return "external";
    case LATTICRA_LAT_EFFECT_UNKNOWN:
    default: return "unknown";
    }
}

typedef struct {
    const char *source;
    size_t source_len;
    size_t offset;
    size_t line;
    size_t column;
} lat_cursor_t;

static int cursor_at_end(const lat_cursor_t *cursor) {
    return cursor == 0 || cursor->offset >= cursor->source_len;
}

static char cursor_peek(const lat_cursor_t *cursor) {
    if (cursor_at_end(cursor)) return '\0';
    return cursor->source[cursor->offset];
}

static char cursor_peek_next(const lat_cursor_t *cursor) {
    if (cursor == 0 || cursor->offset + 1u >= cursor->source_len) return '\0';
    return cursor->source[cursor->offset + 1u];
}

static void cursor_advance(lat_cursor_t *cursor) {
    char ch;
    if (cursor_at_end(cursor)) return;
    ch = cursor->source[cursor->offset];
    cursor->offset += 1u;
    if (ch == '\n') {
        cursor->line += 1u;
        cursor->column = 1u;
    } else {
        cursor->column += 1u;
    }
}

static latticra_lat_source_span_t span_start(const lat_cursor_t *cursor) {
    latticra_lat_source_span_t span;
    span.start_offset = cursor == 0 ? 0u : cursor->offset;
    span.end_offset = cursor == 0 ? 0u : cursor->offset;
    span.start_line = cursor == 0 ? 1u : cursor->line;
    span.start_column = cursor == 0 ? 1u : cursor->column;
    span.end_line = span.start_line;
    span.end_column = span.start_column;
    return span;
}

static void span_finish(latticra_lat_source_span_t *span, const lat_cursor_t *cursor) {
    if (span == 0 || cursor == 0) return;
    span->end_offset = cursor->offset;
    span->end_line = cursor->line;
    span->end_column = cursor->column;
}

static int is_ident_start(char ch) {
    return isalpha((unsigned char)ch) || ch == '_';
}

static int is_ident_continue(char ch) {
    return isalnum((unsigned char)ch) || ch == '_';
}

static void skip_ws_and_comments(lat_cursor_t *cursor) {
    int again = 1;
    while (!cursor_at_end(cursor) && again) {
        again = 0;
        while (!cursor_at_end(cursor) && isspace((unsigned char)cursor_peek(cursor))) cursor_advance(cursor);
        if (!cursor_at_end(cursor) && cursor_peek(cursor) == '/' && cursor_peek_next(cursor) == '/') {
            while (!cursor_at_end(cursor) && cursor_peek(cursor) != '\n') cursor_advance(cursor);
            again = 1;
        }
    }
}

static int read_identifier(lat_cursor_t *cursor, char *buffer, size_t buffer_len, latticra_lat_source_span_t *span) {
    size_t used = 0u;
    if (cursor == 0 || buffer == 0 || buffer_len == 0u) return 0;
    buffer[0] = '\0';
    skip_ws_and_comments(cursor);
    if (span != 0) *span = span_start(cursor);
    if (!is_ident_start(cursor_peek(cursor))) return 0;
    while (!cursor_at_end(cursor) && is_ident_continue(cursor_peek(cursor))) {
        if (used + 1u >= buffer_len) return 0;
        buffer[used] = cursor_peek(cursor);
        used += 1u;
        cursor_advance(cursor);
    }
    buffer[used] = '\0';
    if (span != 0) span_finish(span, cursor);
    return 1;
}

static int match_keyword(lat_cursor_t *cursor, const char *keyword) {
    char buffer[LATTICRA_LAT_NAME_MAX];
    lat_cursor_t copy;
    if (cursor == 0 || keyword == 0) return 0;
    copy = *cursor;
    if (!read_identifier(&copy, buffer, sizeof(buffer), 0)) return 0;
    if (strcmp(buffer, keyword) != 0) return 0;
    *cursor = copy;
    return 1;
}

static int consume_char(lat_cursor_t *cursor, char expected) {
    skip_ws_and_comments(cursor);
    if (cursor_peek(cursor) != expected) return 0;
    cursor_advance(cursor);
    return 1;
}

static int is_hex_digit(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

static latticra_lat_parse_error_t read_string(
    lat_cursor_t *cursor,
    char *buffer,
    size_t buffer_len,
    latticra_lat_source_span_t *span) {
    size_t used = 0u;
    if (cursor == 0 || buffer == 0 || buffer_len == 0u) return LATTICRA_LAT_PARSE_INTERNAL_ERROR;
    buffer[0] = '\0';
    skip_ws_and_comments(cursor);
    if (span != 0) *span = span_start(cursor);
    if (cursor_peek(cursor) != '"') return LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE;
    cursor_advance(cursor);
    while (!cursor_at_end(cursor)) {
        char ch = cursor_peek(cursor);
        if (ch == '\0') return LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING;
        if (ch == '"') {
            cursor_advance(cursor);
            buffer[used] = '\0';
            if (span != 0) span_finish(span, cursor);
            return LATTICRA_LAT_PARSE_OK;
        }
        if (ch == '\n' || ch == '\r') return LATTICRA_LAT_PARSE_UNTERMINATED_STRING;
        if (used + 1u >= buffer_len) return LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED;
        if (ch == '\\') {
            cursor_advance(cursor);
            if (cursor_at_end(cursor)) return LATTICRA_LAT_PARSE_UNTERMINATED_STRING;
            ch = cursor_peek(cursor);
            if (ch == '\\' || ch == '"' || ch == 'n' || ch == 'r' || ch == 't') {
                buffer[used] = ch == 'n' ? '\n' : ch == 'r' ? '\r' : ch == 't' ? '\t' : ch;
                used += 1u;
                cursor_advance(cursor);
            } else if (ch == 'x') {
                cursor_advance(cursor);
                if (!is_hex_digit(cursor_peek(cursor)) || !is_hex_digit(cursor_peek_next(cursor))) {
                    return LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE;
                }
                if (cursor_peek(cursor) == '0' && cursor_peek_next(cursor) == '0') {
                    return LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE;
                }
                cursor_advance(cursor);
                cursor_advance(cursor);
                buffer[used] = '?';
                used += 1u;
            } else {
                return LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE;
            }
        } else {
            buffer[used] = ch;
            used += 1u;
            cursor_advance(cursor);
        }
    }
    return LATTICRA_LAT_PARSE_UNTERMINATED_STRING;
}

static int read_integer(lat_cursor_t *cursor, char *buffer, size_t buffer_len, latticra_lat_source_span_t *span) {
    size_t used = 0u;
    if (cursor == 0 || buffer == 0 || buffer_len == 0u) return 0;
    buffer[0] = '\0';
    skip_ws_and_comments(cursor);
    if (span != 0) *span = span_start(cursor);
    if (!isdigit((unsigned char)cursor_peek(cursor))) return 0;
    while (!cursor_at_end(cursor) && isdigit((unsigned char)cursor_peek(cursor))) {
        if (used + 1u >= buffer_len) return 0;
        buffer[used] = cursor_peek(cursor);
        used += 1u;
        cursor_advance(cursor);
    }
    buffer[used] = '\0';
    if (span != 0) span_finish(span, cursor);
    return 1;
}

static int read_value(
    lat_cursor_t *cursor,
    char *buffer,
    size_t buffer_len,
    latticra_lat_source_span_t *span,
    latticra_lat_parse_error_t *error) {
    if (error != 0) *error = LATTICRA_LAT_PARSE_OK;
    skip_ws_and_comments(cursor);
    if (cursor_peek(cursor) == '"') {
        latticra_lat_parse_error_t string_error = read_string(cursor, buffer, buffer_len, span);
        if (error != 0) *error = string_error;
        return string_error == LATTICRA_LAT_PARSE_OK;
    }
    if (isdigit((unsigned char)cursor_peek(cursor))) return read_integer(cursor, buffer, buffer_len, span);
    if (read_identifier(cursor, buffer, buffer_len, span)) return 1;
    if (error != 0) *error = LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
    return 0;
}

static latticra_lat_effect_t effect_from_label(const char *label) {
    if (label == 0) return LATTICRA_LAT_EFFECT_UNKNOWN;
    if (strcmp(label, "none") == 0) return LATTICRA_LAT_EFFECT_NONE;
    if (strcmp(label, "read") == 0) return LATTICRA_LAT_EFFECT_READ;
    if (strcmp(label, "local_mutation") == 0) return LATTICRA_LAT_EFFECT_LOCAL_MUTATION;
    if (strcmp(label, "host_mutation") == 0) return LATTICRA_LAT_EFFECT_HOST_MUTATION;
    if (strcmp(label, "network") == 0) return LATTICRA_LAT_EFFECT_NETWORK;
    if (strcmp(label, "hardware") == 0) return LATTICRA_LAT_EFFECT_HARDWARE;
    if (strcmp(label, "boot") == 0) return LATTICRA_LAT_EFFECT_BOOT;
    if (strcmp(label, "recovery") == 0) return LATTICRA_LAT_EFFECT_RECOVERY;
    if (strcmp(label, "external") == 0) return LATTICRA_LAT_EFFECT_EXTERNAL;
    return LATTICRA_LAT_EFFECT_UNKNOWN;
}

static latticra_lat_declaration_kind_t declaration_kind_from_label(const char *label) {
    if (label == 0) return LATTICRA_LAT_DECLARATION_UNKNOWN;
    if (strcmp(label, "state") == 0) return LATTICRA_LAT_DECLARATION_STATE;
    if (strcmp(label, "policy") == 0) return LATTICRA_LAT_DECLARATION_POLICY;
    if (strcmp(label, "transition") == 0) return LATTICRA_LAT_DECLARATION_TRANSITION;
    if (strcmp(label, "assertion") == 0) return LATTICRA_LAT_DECLARATION_ASSERTION;
    if (strcmp(label, "effect") == 0) return LATTICRA_LAT_DECLARATION_EFFECT;
    return LATTICRA_LAT_DECLARATION_UNKNOWN;
}

static int append_clause(
    latticra_lat_parse_result_t *result,
    const char *keyword,
    const char *left,
    const char *operator_text,
    const char *right,
    const latticra_lat_source_span_t *span) {
    latticra_lat_ast_clause_t *clause;
    if (result == 0 || result->clause_count >= LATTICRA_LAT_CLAUSE_MAX) return 0;
    clause = &result->clauses[result->clause_count];
    copy_literal(clause->keyword, sizeof(clause->keyword), keyword);
    copy_literal(clause->left, sizeof(clause->left), left);
    copy_literal(clause->operator_text, sizeof(clause->operator_text), operator_text);
    copy_literal(clause->right, sizeof(clause->right), right);
    clause->effect = effect_from_label(right);
    if (span != 0) clause->span = *span;
    result->clause_count += 1u;
    return 1;
}

static int read_operator(lat_cursor_t *cursor, char *buffer, size_t buffer_len) {
    char first;
    if (cursor == 0 || buffer == 0 || buffer_len < 3u) return 0;
    skip_ws_and_comments(cursor);
    first = cursor_peek(cursor);
    if ((first == '=' || first == '!' || first == '<' || first == '>') && cursor_peek_next(cursor) == '=') {
        buffer[0] = first;
        buffer[1] = '=';
        buffer[2] = '\0';
        cursor_advance(cursor);
        cursor_advance(cursor);
        return 1;
    }
    if (first == '<' || first == '>') {
        buffer[0] = first;
        buffer[1] = '\0';
        cursor_advance(cursor);
        return 1;
    }
    return 0;
}

static latticra_lat_parse_error_t parse_clause(
    lat_cursor_t *cursor,
    latticra_lat_parse_result_t *result,
    latticra_lat_ast_declaration_t *declaration) {
    char keyword[LATTICRA_LAT_NAME_MAX];
    char left[LATTICRA_LAT_NAME_MAX];
    char operator_text[LATTICRA_LAT_NAME_MAX];
    char right[LATTICRA_LAT_VALUE_MAX];
    latticra_lat_source_span_t span;
    latticra_lat_source_span_t value_span;
    latticra_lat_parse_error_t value_error = LATTICRA_LAT_PARSE_OK;

    span = span_start(cursor);
    if (!read_identifier(cursor, keyword, sizeof(keyword), &span)) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;

    if (strcmp(keyword, "require") == 0 || strcmp(keyword, "ensure") == 0) {
        if (!read_identifier(cursor, left, sizeof(left), 0)) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
        if (!read_operator(cursor, operator_text, sizeof(operator_text))) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
        if (!read_value(cursor, right, sizeof(right), &value_span, &value_error)) return value_error;
    } else if (strcmp(keyword, "effect") == 0) {
        if (!read_identifier(cursor, left, sizeof(left), 0)) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
        if (!consume_char(cursor, '=')) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
        copy_literal(operator_text, sizeof(operator_text), "=");
        if (!read_value(cursor, right, sizeof(right), &value_span, &value_error)) return value_error;
    } else {
        copy_literal(left, sizeof(left), keyword);
        if (!consume_char(cursor, '=')) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
        copy_literal(keyword, sizeof(keyword), "field");
        copy_literal(operator_text, sizeof(operator_text), "=");
        if (!read_value(cursor, right, sizeof(right), &value_span, &value_error)) return value_error;
    }

    span_finish(&span, cursor);
    if (!append_clause(result, keyword, left, operator_text, right, &span)) return LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED;
    if (declaration != 0) declaration->clause_count += 1u;
    return LATTICRA_LAT_PARSE_OK;
}

static void count_declaration(latticra_lat_parse_result_t *result, latticra_lat_declaration_kind_t kind) {
    if (result == 0) return;
    if (kind == LATTICRA_LAT_DECLARATION_STATE) result->module.state_count += 1u;
    else if (kind == LATTICRA_LAT_DECLARATION_POLICY) result->module.policy_count += 1u;
    else if (kind == LATTICRA_LAT_DECLARATION_TRANSITION) result->module.transition_count += 1u;
    else if (kind == LATTICRA_LAT_DECLARATION_ASSERTION) result->module.assertion_count += 1u;
    else if (kind == LATTICRA_LAT_DECLARATION_EFFECT) result->module.effect_count += 1u;
}

static latticra_lat_parse_error_t parse_declaration(lat_cursor_t *cursor, latticra_lat_parse_result_t *result) {
    char kind_label[LATTICRA_LAT_NAME_MAX];
    latticra_lat_declaration_kind_t kind;
    latticra_lat_ast_declaration_t *declaration;
    size_t declaration_index;
    latticra_lat_source_span_t kind_span;

    if (!read_identifier(cursor, kind_label, sizeof(kind_label), &kind_span)) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
    kind = declaration_kind_from_label(kind_label);
    if (kind == LATTICRA_LAT_DECLARATION_UNKNOWN) return LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION;
    if (result->declaration_count >= LATTICRA_LAT_DECLARATION_MAX) return LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED;

    declaration_index = result->declaration_count;
    declaration = &result->declarations[declaration_index];
    declaration->kind = kind;
    declaration->span = kind_span;
    declaration->first_clause_index = result->clause_count;
    declaration->clause_count = 0u;
    if (!read_identifier(cursor, declaration->name, sizeof(declaration->name), 0)) return LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME;
    if (kind == LATTICRA_LAT_DECLARATION_TRANSITION) {
        if (!match_keyword(cursor, "from")) return LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME;
        if (!read_identifier(cursor, declaration->source_name, sizeof(declaration->source_name), 0)) return LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME;
    }
    if (!consume_char(cursor, '{')) return LATTICRA_LAT_PARSE_UNBALANCED_BRACE;
    while (!cursor_at_end(cursor)) {
        latticra_lat_parse_error_t clause_error;
        skip_ws_and_comments(cursor);
        if (cursor_peek(cursor) == '}') {
            cursor_advance(cursor);
            span_finish(&declaration->span, cursor);
            result->declaration_count += 1u;
            result->module.declaration_count += 1u;
            count_declaration(result, kind);
            return LATTICRA_LAT_PARSE_OK;
        }
        clause_error = parse_clause(cursor, result, declaration);
        if (clause_error != LATTICRA_LAT_PARSE_OK) return clause_error;
    }
    return LATTICRA_LAT_PARSE_UNBALANCED_BRACE;
}

static int marker_boundary(const char *source, size_t source_len, size_t start, size_t len) {
    int before_ok = start == 0u || !is_ident_continue(source[start - 1u]);
    int after_ok = start + len >= source_len || !is_ident_continue(source[start + len]);
    return before_ok && after_ok;
}

static int contains_forbidden_marker_outside_comment(const char *source, size_t source_len) {
    static const char *markers[] = { "exec", "spawn", "syscall", "socket", "open_file", "write_file", "hardware_write" };
    size_t index = 0u;
    int in_line_comment = 0;
    while (index < source_len) {
        size_t marker_index;
        char ch = source[index];
        if (in_line_comment) {
            if (ch == '\n') in_line_comment = 0;
            index += 1u;
            continue;
        }
        if (ch == '/' && index + 1u < source_len && source[index + 1u] == '/') {
            in_line_comment = 1;
            index += 2u;
            continue;
        }
        for (marker_index = 0u; marker_index < sizeof(markers) / sizeof(markers[0]); marker_index++) {
            size_t len = strlen(markers[marker_index]);
            if (index + len <= source_len && strncmp(source + index, markers[marker_index], len) == 0 && marker_boundary(source, source_len, index, len)) return 1;
        }
        index += 1u;
    }
    return 0;
}

static int source_contains_literal_nul(const char *source, size_t source_len) {
    size_t index;
    for (index = 0u; index < source_len; index++) {
        if (source[index] == '\0') return 1;
    }
    return 0;
}

static latticra_lat_parse_error_t set_error(latticra_lat_parse_result_t *result, latticra_lat_parse_error_t error, const lat_cursor_t *cursor) {
    result->status = LATTICRA_STATUS_OK;
    result->error = error;
    if (cursor != 0) {
        result->span = span_start(cursor);
    }
    return error;
}

latticra_status_t latticra_lat_parse_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *result) {
    lat_cursor_t cursor;
    latticra_lat_parse_error_t error;
    latticra_lat_source_span_t module_span;

    if (source == 0 || result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result_default(result);
    if (source_len == 0u) {
        result->error = LATTICRA_LAT_PARSE_EMPTY_SOURCE;
        return LATTICRA_STATUS_OK;
    }
    if (source_len > LATTICRA_LAT_SOURCE_MAX) {
        result->error = LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE;
        return LATTICRA_STATUS_OK;
    }
    if (source_contains_literal_nul(source, source_len)) {
        result->error = LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING;
        return LATTICRA_STATUS_OK;
    }
    if (contains_forbidden_marker_outside_comment(source, source_len)) {
        result->error = LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER;
        return LATTICRA_STATUS_OK;
    }

    cursor.source = source;
    cursor.source_len = source_len;
    cursor.offset = 0u;
    cursor.line = 1u;
    cursor.column = 1u;
    module_span = span_start(&cursor);

    if (match_keyword(&cursor, "l")) {
        set_error(result, LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM, &cursor);
        return LATTICRA_STATUS_OK;
    }
    if (!match_keyword(&cursor, "lat")) {
        set_error(result, LATTICRA_LAT_PARSE_MISSING_MODULE, &cursor);
        return LATTICRA_STATUS_OK;
    }
    if (!match_keyword(&cursor, "module")) {
        set_error(result, LATTICRA_LAT_PARSE_MISSING_MODULE, &cursor);
        return LATTICRA_STATUS_OK;
    }
    result->module.span = module_span;
    if (!read_identifier(&cursor, result->module.module_name, sizeof(result->module.module_name), 0)) {
        set_error(result, LATTICRA_LAT_PARSE_INVALID_MODULE_NAME, &cursor);
        return LATTICRA_STATUS_OK;
    }
    if (!consume_char(&cursor, '{')) {
        set_error(result, LATTICRA_LAT_PARSE_UNBALANCED_BRACE, &cursor);
        return LATTICRA_STATUS_OK;
    }
    while (!cursor_at_end(&cursor)) {
        skip_ws_and_comments(&cursor);
        if (cursor_peek(&cursor) == '}') {
            cursor_advance(&cursor);
            span_finish(&result->module.span, &cursor);
            result->span = result->module.span;
            result->error = LATTICRA_LAT_PARSE_OK;
            return LATTICRA_STATUS_OK;
        }
        error = parse_declaration(&cursor, result);
        if (error != LATTICRA_LAT_PARSE_OK) {
            set_error(result, error, &cursor);
            return LATTICRA_STATUS_OK;
        }
    }
    set_error(result, LATTICRA_LAT_PARSE_UNBALANCED_BRACE, &cursor);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_parse_report(
    const latticra_lat_parse_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    written = snprintf(
        buffer,
        buffer_len,
        "LAT GRAMMAR REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "module=%s\n"
        "declaration_count=%zu\n"
        "state_count=%zu\n"
        "policy_count=%zu\n"
        "transition_count=%zu\n"
        "assertion_count=%zu\n"
        "effect_count=%zu\n"
        "clause_count=%zu\n"
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
        latticra_lat_parse_error_label(result->error),
        result->module.module_name,
        result->declaration_count,
        result->module.state_count,
        result->module.policy_count,
        result->module.transition_count,
        result->module.assertion_count,
        result->module.effect_count,
        result->clause_count,
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
