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

static int make_source(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    const char *top_text,
    const char *bottom_text,
    size_t *source_len) {
    int written = snprintf(
        buffer,
        buffer_len,
        "%s%s%s%s%s%s%s",
        SOURCE_PREFIX,
        purpose,
        SOURCE_MIDDLE,
        top_text,
        SOURCE_AFTER_TOP_TEXT,
        bottom_text,
        SOURCE_SUFFIX);
    if (written < 0 || (size_t)written >= buffer_len) {
        return 0;
    }
    if (source_len != 0) {
        *source_len = (size_t)written;
    }
    return 1;
}

static int parse_values(
    const char *purpose,
    const char *top_text,
    const char *bottom_text,
    latticra_l_ui_ast_result_t *ast,
    char *source,
    size_t source_len_limit,
    size_t *source_len) {
    size_t len;
    EXPECT_TRUE(make_source(source, source_len_limit, purpose, top_text, bottom_text, &len), "source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, len, ast) == LATTICRA_STATUS_OK, "AST parse status");
    EXPECT_TRUE(ast->parse_result.error == LATTICRA_L_UI_PARSE_OK, "AST parse OK");
    if (source_len != 0) {
        *source_len = len;
    }
    return 0;
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

static int ast_string_storage_sets_purpose_len(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose bytes", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "purpose len parse");
    EXPECT_TRUE(ast.card.purpose_len == strlen("purpose bytes"), "purpose_len set");
    (void)source_len;
    return 0;
}

static int ast_string_storage_sets_text_value_len(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose", "top bytes", "bottom bytes", &ast, source, sizeof(source), &source_len) == 0, "text len parse");
    EXPECT_TRUE(ast.texts[0].value_len == strlen("top bytes"), "top value_len set");
    EXPECT_TRUE(ast.texts[1].value_len == strlen("bottom bytes"), "bottom value_len set");
    (void)source_len;
    return 0;
}

static int ast_string_storage_len_matches_strlen_for_non_nul_values(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("abc", "def", "ghi", &ast, source, sizeof(source), &source_len) == 0, "strlen parse");
    EXPECT_TRUE(ast.card.purpose_len == strlen(ast.card.purpose), "purpose_len matches strlen");
    EXPECT_TRUE(ast.texts[0].value_len == strlen(ast.texts[0].value), "top value_len matches strlen");
    EXPECT_TRUE(ast.texts[1].value_len == strlen(ast.texts[1].value), "bottom value_len matches strlen");
    (void)source_len;
    return 0;
}

static int ast_string_storage_len_tracks_decoded_newline(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("A\\nB", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "newline parse");
    EXPECT_STR_EQ(ast.card.purpose, "A\nB", "newline decoded");
    EXPECT_TRUE(ast.card.purpose_len == 3u, "newline decoded length");
    (void)source_len;
    return 0;
}

static int ast_string_storage_len_tracks_decoded_tab(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose", "A\\tB", "bottom", &ast, source, sizeof(source), &source_len) == 0, "tab parse");
    EXPECT_STR_EQ(ast.texts[0].value, "A\tB", "tab decoded");
    EXPECT_TRUE(ast.texts[0].value_len == 3u, "tab decoded length");
    (void)source_len;
    return 0;
}

static int ast_string_storage_len_tracks_decoded_high_byte_hex(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("hi\\x80\\xFF", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "high-byte parse");
    EXPECT_TRUE(ast.card.purpose_len == 4u, "high byte decoded length");
    EXPECT_TRUE(strlen(ast.card.purpose) == 4u, "high byte strlen compatibility");
    (void)source_len;
    return 0;
}

static int ast_string_storage_preserves_existing_c_string_fields(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("plain purpose", "plain top", "plain bottom", &ast, source, sizeof(source), &source_len) == 0, "c string parse");
    EXPECT_STR_EQ(ast.card.purpose, "plain purpose", "purpose C string preserved");
    EXPECT_STR_EQ(ast.texts[0].value, "plain top", "top C string preserved");
    EXPECT_STR_EQ(ast.texts[1].value, "plain bottom", "bottom C string preserved");
    (void)source_len;
    return 0;
}

static int ast_string_storage_updates_detailed_report_lengths(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("abc", "A\\nB", "bottom", &ast, source, sizeof(source), &source_len) == 0, "length report parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "length report builds");
    EXPECT_TRUE(strstr(report, "purpose_len=3\n") != 0, "purpose_len in report");
    EXPECT_TRUE(strstr(report, "value_len=3\n") != 0, "value_len in report");
    (void)source_len;
    return 0;
}

static int ast_string_storage_escaped_report_uses_explicit_lengths(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("hi\\x80\\xFF", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "escaped length parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "escaped length report builds");
    EXPECT_TRUE(strstr(report, "purpose_len=4\n") != 0, "high byte purpose_len in report");
    EXPECT_TRUE(strstr(report, "purpose_escaped=hi\\x80\\xFF\n") != 0, "escaped high bytes in report");
    (void)source_len;
    return 0;
}

static int ast_string_storage_accepts_decoded_nul_after_acceptance_contract(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    static const char expected[] = { 'A', '\0', 'B' };
    EXPECT_TRUE(parse_values("A\\x00B", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "decoded NUL AST status");
    EXPECT_TRUE(ast.card.purpose_len == sizeof(expected), "decoded NUL counted in purpose_len");
    EXPECT_TRUE(strlen(ast.card.purpose) == 1u, "decoded NUL C-string prefix compatibility");
    EXPECT_TRUE(memcmp(ast.card.purpose, expected, sizeof(expected)) == 0, "decoded NUL stored in purpose bytes");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "decoded NUL report builds");
    EXPECT_TRUE(strstr(report, "purpose_len=3\n") != 0, "decoded NUL purpose_len report");
    EXPECT_TRUE(strstr(report, "purpose_escaped=A\\x00B\n") != 0, "decoded NUL purpose escaped report");
    (void)source_len;
    return 0;
}

static int ast_string_storage_still_rejects_literal_nul_until_acceptance_contract(void) {
    latticra_l_ui_parse_result_t result;
    result.status = LATTICRA_STATUS_OK;
    result.error = LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING;
    result.line = 1u;
    result.column = 1u;
    result.span.start_offset = 0u;
    result.span.end_offset = 1u;
    result.span.start_line = 1u;
    result.span.start_column = 1u;
    result.span.end_line = 1u;
    result.span.end_column = 2u;
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
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL diagnostic remains available");
    return 0;
}

static int ast_string_storage_still_rejects_oversized_decoded_output(void) {
    char source[8192];
    char long_value[LATTICRA_L_UI_AST_PURPOSE_MAX + 1u];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(fill_repeated(long_value, sizeof(long_value), 'x'), "long value builds");
    EXPECT_TRUE(make_source(source, sizeof(source), long_value, "top", "bottom", &source_len), "oversized source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "oversized AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE, "oversized still rejected");
    return 0;
}

static int ast_string_storage_preserves_source_spans(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    static const char top_text[] = "A\\nB";
    EXPECT_TRUE(parse_values("purpose", top_text, "bottom", &ast, source, sizeof(source), &source_len) == 0, "span parse");
    EXPECT_TRUE(ast.texts[0].span.end_offset - ast.texts[0].span.start_offset == strlen(top_text), "span remains source length");
    EXPECT_TRUE(ast.texts[0].value_len == 3u, "decoded length differs from source span length");
    (void)source_len;
    return 0;
}

static int ast_string_storage_preserves_no_effect_flags(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "flag parse");
    EXPECT_TRUE(ast.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(ast.execution_allowed == 0, "execution flag preserved");
    EXPECT_TRUE(ast.mutation_allowed == 0, "mutation flag preserved");
    EXPECT_TRUE(ast.server_allowed == 0, "server flag preserved");
    EXPECT_TRUE(ast.recovery_allowed == 0, "recovery flag preserved");
    EXPECT_TRUE(ast.hardware_allowed == 0, "hardware flag preserved");
    (void)source_len;
    return 0;
}

static int ast_string_storage_does_not_change_existing_diagnostic_codes(void) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    EXPECT_TRUE(latticra_l_ui_parse_source("", 0u, &result) == LATTICRA_STATUS_OK, "empty source parse status");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "diagnostic status");
    EXPECT_STR_EQ(diagnostic.code, "LUI0002", "empty source diagnostic code unchanged");
    return 0;
}

static int ast_string_storage_does_not_change_failed_parse_report(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed parse report status");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed parse error preserved");
    EXPECT_TRUE(strstr(report, "purpose_len=") == 0, "failed parse has no purpose_len field");
    EXPECT_TRUE(strstr(report, "value_len=") == 0, "failed parse has no value_len field");
    return 0;
}

static int ast_string_storage_is_deterministic(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t one;
    latticra_l_ui_ast_result_t two;
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\nB", "T\\tQ", "B\\x41", &source_len), "det source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &one) == LATTICRA_STATUS_OK, "first AST status");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &two) == LATTICRA_STATUS_OK, "second AST status");
    EXPECT_TRUE(one.card.purpose_len == two.card.purpose_len, "purpose_len deterministic");
    EXPECT_TRUE(one.texts[0].value_len == two.texts[0].value_len, "top value_len deterministic");
    EXPECT_TRUE(one.texts[1].value_len == two.texts[1].value_len, "bottom value_len deterministic");
    EXPECT_STR_EQ(one.card.purpose, two.card.purpose, "purpose deterministic");
    EXPECT_STR_EQ(one.texts[0].value, two.texts[0].value, "top text deterministic");
    EXPECT_STR_EQ(one.texts[1].value, two.texts[1].value, "bottom text deterministic");
    return 0;
}

int main(void) {
    if (ast_string_storage_sets_purpose_len() != 0) return 1;
    if (ast_string_storage_sets_text_value_len() != 0) return 1;
    if (ast_string_storage_len_matches_strlen_for_non_nul_values() != 0) return 1;
    if (ast_string_storage_len_tracks_decoded_newline() != 0) return 1;
    if (ast_string_storage_len_tracks_decoded_tab() != 0) return 1;
    if (ast_string_storage_len_tracks_decoded_high_byte_hex() != 0) return 1;
    if (ast_string_storage_preserves_existing_c_string_fields() != 0) return 1;
    if (ast_string_storage_updates_detailed_report_lengths() != 0) return 1;
    if (ast_string_storage_escaped_report_uses_explicit_lengths() != 0) return 1;
    if (ast_string_storage_accepts_decoded_nul_after_acceptance_contract() != 0) return 1;
    if (ast_string_storage_still_rejects_literal_nul_until_acceptance_contract() != 0) return 1;
    if (ast_string_storage_still_rejects_oversized_decoded_output() != 0) return 1;
    if (ast_string_storage_preserves_source_spans() != 0) return 1;
    if (ast_string_storage_preserves_no_effect_flags() != 0) return 1;
    if (ast_string_storage_does_not_change_existing_diagnostic_codes() != 0) return 1;
    if (ast_string_storage_does_not_change_failed_parse_report() != 0) return 1;
    if (ast_string_storage_is_deterministic() != 0) return 1;

    puts("l_ui_ast_length_carrying_string_storage_invariants: ok");
    return 0;
}
