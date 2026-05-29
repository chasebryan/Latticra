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

#define EXPECT_MEM_EQ(actual, expected, len, message) \
    do { \
        if (memcmp((actual), (expected), (len)) != 0) { \
            fprintf(stderr, "FAIL: %s\n", message); \
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
    "    field network bind preview.network_allowed\n"
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

static int parse_literal_nul_source(
    const char *purpose,
    size_t purpose_len,
    const char *top_text,
    size_t top_text_len,
    latticra_l_ui_parse_result_t *result,
    char *source,
    size_t source_buffer_len,
    size_t *source_len) {
    size_t len;
    if (!make_source_binary(
            source,
            source_buffer_len,
            purpose,
            purpose_len,
            top_text,
            top_text_len,
            "bottom",
            strlen("bottom"),
            &len)) {
        return 0;
    }
    if (source_len != 0) {
        *source_len = len;
    }
    return latticra_l_ui_parse_source(source, len, result) == LATTICRA_STATUS_OK;
}

static int literal_nul_policy_rejects_purpose_literal_nul(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_parse_result_t result;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source(purpose, sizeof(purpose), "top", strlen("top"), &result, source, sizeof(source), &source_len), "purpose literal NUL parses to result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "purpose literal NUL rejected");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_rejects_text_literal_nul(void) {
    char source[4096];
    static const char text[] = { 'l', 'e', 'f', 't', '\0', 'r', 'i', 'g', 'h', 't' };
    latticra_l_ui_parse_result_t result;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source("purpose", strlen("purpose"), text, sizeof(text), &result, source, sizeof(source), &source_len), "text literal NUL parses to result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "text literal NUL rejected");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_rejects_bottom_text_literal_nul(void) {
    char source[4096];
    static const char bottom_text[] = { 'b', 'o', 't', '\0', 't', 'o', 'm' };
    latticra_l_ui_parse_result_t result;
    size_t source_len;
    EXPECT_TRUE(make_source_binary(
                    source,
                    sizeof(source),
                    "purpose",
                    strlen("purpose"),
                    "top",
                    strlen("top"),
                    bottom_text,
                    sizeof(bottom_text),
                    &source_len),
        "bottom text literal NUL source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "bottom text literal NUL parses to result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "bottom text literal NUL rejected");
    return 0;
}

static int literal_nul_policy_rejects_source_buffer_nul_outside_strings(void) {
    char source[4096];
    char *newline;
    size_t nul_index;
    size_t source_len;
    latticra_l_ui_parse_result_t result;

    EXPECT_TRUE(make_source(source, sizeof(source), "purpose", "top", "bottom", &source_len), "outside-string NUL source builds");
    newline = memchr(source, '\n', source_len);
    EXPECT_TRUE(newline != 0, "source has newline outside strings");
    nul_index = (size_t)(newline - source);
    source[nul_index] = '\0';

    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "outside-string NUL parses to result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "outside-string NUL rejected");
    EXPECT_TRUE(result.span.start_offset == nul_index, "outside-string NUL span start");
    EXPECT_TRUE(result.span.end_offset == nul_index + 1u, "outside-string NUL span end");
    EXPECT_TRUE(result.line > 0u, "outside-string NUL line one-based");
    EXPECT_TRUE(result.column > 0u, "outside-string NUL column one-based");
    return 0;
}

static int literal_nul_policy_reports_lui0023(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source(purpose, sizeof(purpose), "top", strlen("top"), &result, source, sizeof(source), &source_len), "literal NUL diagnostic source parses");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "literal NUL diagnostic maps");
    EXPECT_STR_EQ(diagnostic.code, "LUI0023", "literal NUL diagnostic code");
    EXPECT_STR_EQ(diagnostic.message, "Literal NUL bytes are not supported in AST strings.", "literal NUL diagnostic message");
    EXPECT_STR_EQ(diagnostic.hint, "Remove literal NUL bytes from the source string.", "literal NUL diagnostic hint");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_span_covers_literal_nul_byte(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source(purpose, sizeof(purpose), "top", strlen("top"), &result, source, sizeof(source), &source_len), "literal NUL span source parses");
    EXPECT_TRUE(result.span.end_offset - result.span.start_offset == 1u, "parse span covers one byte");
    EXPECT_TRUE((unsigned char)source[result.span.start_offset] == 0u, "parse span points to literal NUL byte");
    EXPECT_TRUE(result.line > 0u, "parse line one-based");
    EXPECT_TRUE(result.column > 0u, "parse column one-based");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "span diagnostic maps");
    EXPECT_TRUE(diagnostic.span.end_offset - diagnostic.span.start_offset == 1u, "diagnostic span covers one byte");
    EXPECT_TRUE((unsigned char)source[diagnostic.span.start_offset] == 0u, "diagnostic span points to literal NUL byte");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_preserves_no_effect_flags(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source(purpose, sizeof(purpose), "top", strlen("top"), &result, source, sizeof(source), &source_len), "literal NUL no-effect source parses");
    EXPECT_TRUE(result.no_effect == 1, "parse no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "parse execution denied");
    EXPECT_TRUE(result.mutation_allowed == 0, "parse mutation denied");
    EXPECT_TRUE(result.server_allowed == 0, "parse server denied");
    EXPECT_TRUE(result.network_allowed == 0, "parse network denied");
    EXPECT_TRUE(result.recovery_allowed == 0, "parse recovery denied");
    EXPECT_TRUE(result.hardware_allowed == 0, "parse hardware denied");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "literal NUL no-effect diagnostic maps");
    EXPECT_TRUE(diagnostic.no_effect == 1, "diagnostic no_effect");
    EXPECT_TRUE(diagnostic.execution_allowed == 0, "diagnostic execution denied");
    EXPECT_TRUE(diagnostic.mutation_allowed == 0, "diagnostic mutation denied");
    EXPECT_TRUE(diagnostic.server_allowed == 0, "diagnostic server denied");
    EXPECT_TRUE(diagnostic.network_allowed == 0, "diagnostic network denied");
    EXPECT_TRUE(diagnostic.recovery_allowed == 0, "diagnostic recovery denied");
    EXPECT_TRUE(diagnostic.hardware_allowed == 0, "diagnostic hardware denied");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_does_not_emit_decoded_nul_lui0022(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    size_t source_len;
    EXPECT_TRUE(parse_literal_nul_source(purpose, sizeof(purpose), "top", strlen("top"), &result, source, sizeof(source), &source_len), "literal NUL decoded-code source parses");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "literal NUL decoded-code diagnostic maps");
    EXPECT_TRUE(result.error != LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING, "literal NUL is not decoded NUL error");
    EXPECT_TRUE(strcmp(diagnostic.code, "LUI0022") != 0, "literal NUL does not emit LUI0022");
    EXPECT_STR_EQ(diagnostic.code, "LUI0023", "literal NUL emits LUI0023");
    (void)source_len;
    return 0;
}

static int literal_nul_policy_does_not_materialize_partial_ast(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), purpose, sizeof(purpose), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "literal NUL AST source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL AST call succeeds");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL AST parse error");
    EXPECT_TRUE(ast.rail_count == 0u, "no AST rails materialized");
    EXPECT_TRUE(ast.field_count == 0u, "no AST fields materialized");
    EXPECT_TRUE(ast.text_count == 0u, "no AST text materialized");
    EXPECT_TRUE(ast.card.rail_count == 0u, "no card rail count");
    EXPECT_TRUE(ast.card.field_count == 0u, "no card field count");
    EXPECT_TRUE(ast.card.text_count == 0u, "no card text count");
    EXPECT_TRUE(ast.card.purpose_len == 0u, "no purpose bytes materialized");
    EXPECT_TRUE(ast.texts[0].value_len == 0u, "no text bytes materialized");
    return 0;
}

static int literal_nul_policy_does_not_change_escaped_x00_acceptance(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    static const char expected_purpose[] = { 'A', '\0', 'B' };
    static const char expected_text[] = { 'l', 'e', 'f', 't', '\0', 'r', 'i', 'g', 'h', 't' };
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\x00B", "left\\x00right", "bottom", &source_len), "escaped x00 source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "escaped x00 AST call succeeds");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "escaped x00 remains accepted");
    EXPECT_TRUE(ast.card.purpose_len == sizeof(expected_purpose), "escaped x00 purpose length");
    EXPECT_TRUE(ast.texts[0].value_len == sizeof(expected_text), "escaped x00 text length");
    EXPECT_MEM_EQ(ast.card.purpose, expected_purpose, sizeof(expected_purpose), "escaped x00 purpose bytes");
    EXPECT_MEM_EQ(ast.texts[0].value, expected_text, sizeof(expected_text), "escaped x00 text bytes");
    return 0;
}

static int literal_nul_policy_does_not_change_failed_parse_report(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    static const char purpose[] = { 'A', '\0', 'B' };
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), purpose, sizeof(purpose), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "literal NUL failed report source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL failed report AST call succeeds");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "literal NUL failed report builds");
    EXPECT_TRUE(strstr(report, "parse_error=literal_nul_in_string\n") != 0, "failed report parse error");
    EXPECT_TRUE(strstr(report, "rail_count=0\n") != 0, "failed report rail count");
    EXPECT_TRUE(strstr(report, "field_count=0\n") != 0, "failed report field count");
    EXPECT_TRUE(strstr(report, "text_count=0\n") != 0, "failed report text count");
    EXPECT_TRUE(strstr(report, "purpose_escaped=") == 0, "failed report has no purpose escaped field");
    EXPECT_TRUE(strstr(report, "value_escaped=") == 0, "failed report has no value escaped field");
    return 0;
}

static int literal_nul_policy_is_deterministic(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    size_t source_len;
    latticra_l_ui_parse_result_t one;
    latticra_l_ui_parse_result_t two;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), purpose, sizeof(purpose), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "literal NUL deterministic source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &one) == LATTICRA_STATUS_OK, "first literal NUL parse succeeds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &two) == LATTICRA_STATUS_OK, "second literal NUL parse succeeds");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.line == two.line, "deterministic line");
    EXPECT_TRUE(one.column == two.column, "deterministic column");
    EXPECT_TRUE(one.span.start_offset == two.span.start_offset, "deterministic span start");
    EXPECT_TRUE(one.span.end_offset == two.span.end_offset, "deterministic span end");
    return 0;
}

int main(void) {
    if (literal_nul_policy_rejects_purpose_literal_nul() != 0) return 1;
    if (literal_nul_policy_rejects_text_literal_nul() != 0) return 1;
    if (literal_nul_policy_rejects_bottom_text_literal_nul() != 0) return 1;
    if (literal_nul_policy_rejects_source_buffer_nul_outside_strings() != 0) return 1;
    if (literal_nul_policy_reports_lui0023() != 0) return 1;
    if (literal_nul_policy_span_covers_literal_nul_byte() != 0) return 1;
    if (literal_nul_policy_preserves_no_effect_flags() != 0) return 1;
    if (literal_nul_policy_does_not_emit_decoded_nul_lui0022() != 0) return 1;
    if (literal_nul_policy_does_not_materialize_partial_ast() != 0) return 1;
    if (literal_nul_policy_does_not_change_escaped_x00_acceptance() != 0) return 1;
    if (literal_nul_policy_does_not_change_failed_parse_report() != 0) return 1;
    if (literal_nul_policy_is_deterministic() != 0) return 1;

    puts("l_ui_source_buffer_literal_nul_policy_invariants: ok");
    return 0;
}
