#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", message, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

static const char SOURCE_PREFIX[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"";

static const char SOURCE_MIDDLE[] =
    "\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"";

static const char SOURCE_AFTER_TOP_TEXT[] =
    "\" }\n"
    "  rail state {\n"
    "    field origin bind state.origin\n"
    "    field route bind state.route\n"
    "    field axis bind state.axis\n"
    "    field path bind state.path\n"
    "  }\n"
    "  rail trace {\n"
    "    field breadcrumb bind state.breadcrumb\n"
    "    field trace bind state.trace\n"
    "  }\n"
    "  rail safety {\n"
    "    field health bind state.health\n"
    "    field risk bind state.risk\n"
    "    field lock bind state.lock\n"
    "    field dark_phase bind state.dark_phase\n"
    "  }\n"
    "  rail gates {\n"
    "    field safe_portal bind state.safe_portal\n"
    "    field rollback bind state.rollback\n"
    "  }\n"
    "  rail effects {\n"
    "    field host bind state.host_effect\n"
    "    field external bind state.external_effect\n"
    "    field requested bind preview.requested_effect\n"
    "  }\n"
    "  rail policy {\n"
    "    field request bind preview.request\n"
    "    field policy bind preview.policy\n"
    "    field reason bind preview.reason\n"
    "  }\n"
    "  rail execution {\n"
    "    field executed bind preview.executed\n"
    "    field mutation bind preview.mutation_allowed\n"
    "    field server bind preview.server_interaction_allowed\n"
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"";

static const char SOURCE_SUFFIX[] =
    "\" }\n"
    "}\n";

static int append_bytes(char *buffer, size_t buffer_len, size_t *used, const char *bytes, size_t bytes_len) {
    if (buffer == 0 || used == 0 || bytes == 0 || *used > buffer_len || bytes_len > buffer_len - *used) {
        return 0;
    }
    memcpy(buffer + *used, bytes, bytes_len);
    *used += bytes_len;
    return 1;
}

static int make_source_binary(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    size_t purpose_len,
    const char *top_text,
    size_t top_text_len,
    const char *bottom_text,
    size_t bottom_text_len,
    size_t *source_len) {
    size_t used = 0u;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_PREFIX, sizeof(SOURCE_PREFIX) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, purpose, purpose_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_MIDDLE, sizeof(SOURCE_MIDDLE) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, top_text, top_text_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_AFTER_TOP_TEXT, sizeof(SOURCE_AFTER_TOP_TEXT) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, bottom_text, bottom_text_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_SUFFIX, sizeof(SOURCE_SUFFIX) - 1u)) return 0;
    if (used >= buffer_len) return 0;
    buffer[used] = '\0';
    if (source_len != 0) {
        *source_len = used;
    }
    return 1;
}

static int make_source(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    const char *top_text,
    const char *bottom_text,
    size_t *source_len) {
    return make_source_binary(
        buffer,
        buffer_len,
        purpose,
        strlen(purpose),
        top_text,
        strlen(top_text),
        bottom_text,
        strlen(bottom_text),
        source_len);
}

static int expect_escape_diagnostic_for_source(
    const char *source,
    size_t source_len,
    latticra_l_ui_parse_error_t expected_error,
    const char *expected_code,
    const char *expected_message,
    const char *expected_hint) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "parse status");
    EXPECT_TRUE(result.error == expected_error, "parse error");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "diagnostic status");
    EXPECT_TRUE(diagnostic.severity == LATTICRA_L_UI_DIAGNOSTIC_ERROR, "diagnostic severity");
    EXPECT_STR_EQ(diagnostic.code, expected_code, "diagnostic code");
    EXPECT_STR_EQ(diagnostic.message, expected_message, "diagnostic message");
    EXPECT_STR_EQ(diagnostic.hint, expected_hint, "diagnostic hint");
    EXPECT_TRUE(diagnostic.line > 0u, "diagnostic line one-based");
    EXPECT_TRUE(diagnostic.column > 0u, "diagnostic column one-based");
    EXPECT_TRUE(diagnostic.no_effect == 1, "diagnostic no_effect");
    EXPECT_TRUE(diagnostic.execution_allowed == 0, "diagnostic execution");
    EXPECT_TRUE(diagnostic.mutation_allowed == 0, "diagnostic mutation");
    EXPECT_TRUE(diagnostic.server_allowed == 0, "diagnostic server");
    EXPECT_TRUE(diagnostic.recovery_allowed == 0, "diagnostic recovery");
    EXPECT_TRUE(diagnostic.hardware_allowed == 0, "diagnostic hardware");
    return 0;
}

static int expect_escape_diagnostic_for_purpose(
    const char *purpose,
    latticra_l_ui_parse_error_t expected_error,
    const char *expected_code,
    const char *expected_message,
    const char *expected_hint) {
    char source[8192];
    size_t source_len;
    EXPECT_TRUE(make_source(source, sizeof(source), purpose, "top", "bottom", &source_len), "source builds");
    return expect_escape_diagnostic_for_source(
        source,
        source_len,
        expected_error,
        expected_code,
        expected_message,
        expected_hint);
}

static int string_escape_diagnostic_rejects_unknown_escape_lui0019(void) {
    return expect_escape_diagnostic_for_purpose(
        "bad\\a",
        LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE,
        "LUI0019",
        "String literal escape is not supported.",
        "Use only \134\134, \134\042, \134n, \134r, \134t, or uppercase \134xNN escapes.");
}

static int string_escape_diagnostic_rejects_lowercase_hex_lui0020(void) {
    return expect_escape_diagnostic_for_purpose(
        "bad\\x0a",
        LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE,
        "LUI0020",
        "Hex string escape must use exactly two uppercase hexadecimal digits.",
        "Use exactly two uppercase hex digits, such as \x0A or \x7F.");
}

static int string_escape_diagnostic_rejects_short_hex_lui0020(void) {
    return expect_escape_diagnostic_for_purpose(
        "bad\\x0",
        LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE,
        "LUI0020",
        "Hex string escape must use exactly two uppercase hexadecimal digits.",
        "Use exactly two uppercase hex digits, such as \x0A or \x7F.");
}

static int string_escape_diagnostic_rejects_invalid_hex_lui0020(void) {
    return expect_escape_diagnostic_for_purpose(
        "bad\\xGG",
        LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE,
        "LUI0020",
        "Hex string escape must use exactly two uppercase hexadecimal digits.",
        "Use exactly two uppercase hex digits, such as \x0A or \x7F.");
}

static int string_escape_diagnostic_rejects_unterminated_escape_lui0021(void) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;

    result.status = LATTICRA_STATUS_OK;
    result.error = LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE;
    result.line = 3u;
    result.column = 15u;
    result.span.start_offset = 0u;
    result.span.end_offset = 1u;
    result.span.start_line = 3u;
    result.span.start_column = 15u;
    result.span.end_line = 3u;
    result.span.end_column = 16u;
    result.card_name[0] = '\0';
    result.rail_count = 0u;
    result.field_count = 0u;
    result.effect[0] = '\0';
    result.boundary[0] = '\0';
    result.no_effect = 1;
    result.execution_allowed = 0;
    result.mutation_allowed = 0;
    result.server_allowed = 0;
    result.recovery_allowed = 0;
    result.hardware_allowed = 0;

    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "unterminated diagnostic status");
    EXPECT_TRUE(diagnostic.severity == LATTICRA_L_UI_DIAGNOSTIC_ERROR, "unterminated severity");
    EXPECT_STR_EQ(diagnostic.code, "LUI0021", "unterminated code");
    EXPECT_STR_EQ(diagnostic.message, "String literal escape is not terminated.", "unterminated message");
    EXPECT_STR_EQ(diagnostic.hint, "Complete the escape sequence or remove the trailing backslash.", "unterminated hint");
    return 0;
}

static int string_escape_diagnostic_rejects_decoded_nul_lui0022(void) {
    return expect_escape_diagnostic_for_purpose(
        "bad\\x00",
        LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING,
        "LUI0022",
        "Decoded NUL bytes are not supported in AST strings.",
        "Avoid \x00 until length-carrying AST strings exist.");
}

static int string_escape_diagnostic_rejects_literal_nul_lui0023(void) {
    char source[8192];
    static const char purpose[] = { 'b', 'a', 'd', '\0', 'n', 'u', 'l' };
    size_t source_len;
    EXPECT_TRUE(make_source_binary(
                    source,
                    sizeof(source),
                    purpose,
                    sizeof(purpose),
                    "top",
                    strlen("top"),
                    "bottom",
                    strlen("bottom"),
                    &source_len),
                "literal NUL source builds");
    return expect_escape_diagnostic_for_source(
        source,
        source_len,
        LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING,
        "LUI0023",
        "Literal NUL bytes are not supported in AST strings.",
        "Remove literal NUL bytes from the source string.");
}

static int fill_repeated(char *buffer, size_t len, char value) {
    size_t index;
    if (len == 0u) {
        return 0;
    }
    for (index = 0u; index + 1u < len; index++) {
        buffer[index] = value;
    }
    buffer[len - 1u] = '\0';
    return 1;
}

static int string_escape_diagnostic_rejects_oversized_decoded_output_lui0024(void) {
    char long_value[LATTICRA_L_UI_AST_PURPOSE_MAX + 1u];
    EXPECT_TRUE(fill_repeated(long_value, sizeof(long_value), 'x'), "long value builds");
    return expect_escape_diagnostic_for_purpose(
        long_value,
        LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE,
        "LUI0024",
        "Decoded string value exceeds the supported AST storage limit.",
        "Shorten the decoded purpose or text value.");
}

static int string_escape_diagnostic_reports_source_span(void) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "bad\\a", "top", "bottom", &source_len), "span source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "span parse status");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE, "span parse error");
    EXPECT_TRUE(result.span.end_offset - result.span.start_offset == 2u, "span covers escape bytes");
    EXPECT_TRUE(memcmp(source + result.span.start_offset, "\\a", 2u) == 0, "span bytes match escape");
    return 0;
}

static int string_escape_diagnostic_reports_line_column(void) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "bad\\a", "top", "bottom", &source_len), "line source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "line parse status");
    EXPECT_TRUE(result.line == 3u, "escape diagnostic line");
    EXPECT_TRUE(result.column == 15u, "escape diagnostic column");
    return 0;
}

static int string_escape_diagnostic_preserves_no_effect_flags(void) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "bad\\a", "top", "bottom", &source_len), "flag source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "flag parse status");
    EXPECT_TRUE(result.no_effect == 1, "no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "hardware flag");
    return 0;
}

static int string_escape_diagnostic_does_not_change_accepted_escape_decoding(void) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "ok\\nvalue", "top\\tvalue", "bottom\\x41", &source_len), "accepted source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "accepted AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "accepted AST parse OK");
    EXPECT_STR_EQ(ast.card.purpose, "ok\nvalue", "accepted purpose decode");
    EXPECT_STR_EQ(ast.texts[0].value, "top\tvalue", "accepted top decode");
    EXPECT_STR_EQ(ast.texts[1].value, "bottomA", "accepted bottom decode");
    return 0;
}

static int string_escape_diagnostic_does_not_change_existing_error_codes(void) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    EXPECT_TRUE(latticra_l_ui_parse_source("", 0u, &result) == LATTICRA_STATUS_OK, "empty parse status");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "empty diagnostic status");
    EXPECT_STR_EQ(diagnostic.code, "LUI0002", "existing empty-source code stable");
    return 0;
}

static int string_escape_diagnostic_uses_failed_parse_ast_report(void) {
    char source[8192];
    size_t source_len;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "bad\\a", "top", "bottom", &source_len), "failed AST source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "failed AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE, "failed AST parse error");
    EXPECT_TRUE(ast.rail_count == 0u && ast.field_count == 0u && ast.text_count == 0u, "failed AST no nodes");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed AST report status");
    EXPECT_TRUE(strstr(report, "parse_error=invalid_string_escape\n") != 0, "failed AST report parse error");
    EXPECT_TRUE(strstr(report, "purpose=") == 0, "failed AST report no purpose section");
    return 0;
}

static int string_escape_diagnostic_is_deterministic(void) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_parse_result_t one;
    latticra_l_ui_parse_result_t two;
    EXPECT_TRUE(make_source(source, sizeof(source), "bad\\a", "top", "bottom", &source_len), "det source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &one) == LATTICRA_STATUS_OK, "first parse status");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &two) == LATTICRA_STATUS_OK, "second parse status");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.line == two.line, "deterministic line");
    EXPECT_TRUE(one.column == two.column, "deterministic column");
    EXPECT_TRUE(one.span.start_offset == two.span.start_offset, "deterministic span start");
    EXPECT_TRUE(one.span.end_offset == two.span.end_offset, "deterministic span end");
    return 0;
}

int main(void) {
    if (string_escape_diagnostic_rejects_unknown_escape_lui0019() != 0) return 1;
    if (string_escape_diagnostic_rejects_lowercase_hex_lui0020() != 0) return 1;
    if (string_escape_diagnostic_rejects_short_hex_lui0020() != 0) return 1;
    if (string_escape_diagnostic_rejects_invalid_hex_lui0020() != 0) return 1;
    if (string_escape_diagnostic_rejects_unterminated_escape_lui0021() != 0) return 1;
    if (string_escape_diagnostic_rejects_decoded_nul_lui0022() != 0) return 1;
    if (string_escape_diagnostic_rejects_literal_nul_lui0023() != 0) return 1;
    if (string_escape_diagnostic_rejects_oversized_decoded_output_lui0024() != 0) return 1;
    if (string_escape_diagnostic_reports_source_span() != 0) return 1;
    if (string_escape_diagnostic_reports_line_column() != 0) return 1;
    if (string_escape_diagnostic_preserves_no_effect_flags() != 0) return 1;
    if (string_escape_diagnostic_does_not_change_accepted_escape_decoding() != 0) return 1;
    if (string_escape_diagnostic_does_not_change_existing_error_codes() != 0) return 1;
    if (string_escape_diagnostic_uses_failed_parse_ast_report() != 0) return 1;
    if (string_escape_diagnostic_is_deterministic() != 0) return 1;

    puts("l_ui_parser_string_escape_diagnostics_invariants: ok");
    return 0;
}
