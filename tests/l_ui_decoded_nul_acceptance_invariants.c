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

static int decoded_nul_accepts_purpose_x00(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("A\\x00B", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "purpose x00 parse");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "purpose x00 accepted");
    (void)source_len;
    return 0;
}

static int decoded_nul_accepts_text_x00(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose", "left\\x00right", "bottom", &ast, source, sizeof(source), &source_len) == 0, "text x00 parse");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "text x00 accepted");
    (void)source_len;
    return 0;
}

static int decoded_nul_counts_purpose_len(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    static const char expected[] = { 'A', '\0', 'B' };
    EXPECT_TRUE(parse_values("A\\x00B", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "purpose len x00 parse");
    EXPECT_TRUE(ast.card.purpose_len == sizeof(expected), "purpose_len counts decoded NUL");
    EXPECT_MEM_EQ(ast.card.purpose, expected, sizeof(expected), "purpose bytes include decoded NUL");
    (void)source_len;
    return 0;
}

static int decoded_nul_counts_text_value_len(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    static const char expected[] = { 'l', 'e', 'f', 't', '\0', 'r', 'i', 'g', 'h', 't' };
    EXPECT_TRUE(parse_values("purpose", "left\\x00right", "bottom", &ast, source, sizeof(source), &source_len) == 0, "text len x00 parse");
    EXPECT_TRUE(ast.texts[0].value_len == sizeof(expected), "value_len counts decoded NUL");
    EXPECT_MEM_EQ(ast.texts[0].value, expected, sizeof(expected), "text bytes include decoded NUL");
    (void)source_len;
    return 0;
}

static int decoded_nul_preserves_c_string_prefix_compatibility(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("A\\x00B", "left\\x00right", "bottom", &ast, source, sizeof(source), &source_len) == 0, "C-string prefix parse");
    EXPECT_TRUE(strlen(ast.card.purpose) == 1u, "purpose C-string prefix length");
    EXPECT_TRUE(strlen(ast.texts[0].value) == 4u, "text C-string prefix length");
    EXPECT_TRUE(ast.card.purpose_len == 3u, "purpose explicit length differs from strlen");
    EXPECT_TRUE(ast.texts[0].value_len == 10u, "text explicit length differs from strlen");
    (void)source_len;
    return 0;
}

static int decoded_nul_reports_purpose_escaped_x00(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("A\\x00B", "top", "bottom", &ast, source, sizeof(source), &source_len) == 0, "purpose report parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "purpose report status");
    EXPECT_TRUE(strstr(report, "purpose_len=3\n") != 0, "purpose_len report");
    EXPECT_TRUE(strstr(report, "purpose_escaped=A\\x00B\n") != 0, "purpose escaped x00 report");
    (void)source_len;
    return 0;
}

static int decoded_nul_reports_text_value_escaped_x00(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("purpose", "left\\x00right", "bottom", &ast, source, sizeof(source), &source_len) == 0, "text report parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "text report status");
    EXPECT_TRUE(strstr(report, "value_len=10\n") != 0, "value_len report");
    EXPECT_TRUE(strstr(report, "value_escaped=left\\x00right\n") != 0, "value escaped x00 report");
    (void)source_len;
    return 0;
}

static int decoded_nul_does_not_emit_lui0022_for_x00(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\x00B", "top", "bottom", &source_len), "parse source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "parse source status");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "x00 no longer emits decoded_nul_in_string");
    return 0;
}

static int decoded_nul_still_rejects_literal_nul_lui0023(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
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
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL still rejected");
    return 0;
}

static int decoded_nul_still_rejects_lowercase_hex_lui0020(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\x0aB", "top", "bottom", &source_len), "lowercase source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "lowercase parse status");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE, "lowercase hex still rejected");
    return 0;
}

static int decoded_nul_still_rejects_unknown_escape_lui0019(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\aB", "top", "bottom", &source_len), "unknown source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "unknown parse status");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE, "unknown escape still rejected");
    return 0;
}

static int decoded_nul_preserves_source_spans(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    static const char top_text[] = "left\\x00right";
    EXPECT_TRUE(parse_values("purpose", top_text, "bottom", &ast, source, sizeof(source), &source_len) == 0, "span parse");
    EXPECT_TRUE(ast.texts[0].span.end_offset - ast.texts[0].span.start_offset == strlen(top_text), "span remains source byte length");
    EXPECT_TRUE(ast.texts[0].value_len == 10u, "decoded length counts one NUL byte");
    (void)source_len;
    return 0;
}

static int decoded_nul_preserves_no_effect_flags(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_values("A\\x00B", "left\\x00right", "bottom", &ast, source, sizeof(source), &source_len) == 0, "flag parse");
    EXPECT_TRUE(ast.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(ast.execution_allowed == 0, "execution preserved");
    EXPECT_TRUE(ast.mutation_allowed == 0, "mutation preserved");
    EXPECT_TRUE(ast.server_allowed == 0, "server preserved");
    EXPECT_TRUE(ast.network_allowed == 0, "network preserved");
    EXPECT_TRUE(ast.recovery_allowed == 0, "recovery preserved");
    EXPECT_TRUE(ast.hardware_allowed == 0, "hardware preserved");
    (void)source_len;
    return 0;
}

static int decoded_nul_does_not_change_failed_parse_report(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed report status");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed parse report unchanged");
    EXPECT_TRUE(strstr(report, "purpose_escaped=") == 0, "failed report no purpose escaped");
    EXPECT_TRUE(strstr(report, "value_escaped=") == 0, "failed report no value escaped");
    return 0;
}

static int decoded_nul_is_deterministic(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t one;
    latticra_l_ui_ast_result_t two;
    EXPECT_TRUE(make_source(source, sizeof(source), "A\\x00B", "left\\x00right", "bottom", &source_len), "det source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &one) == LATTICRA_STATUS_OK, "first parse status");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &two) == LATTICRA_STATUS_OK, "second parse status");
    EXPECT_TRUE(one.card.purpose_len == two.card.purpose_len, "purpose_len deterministic");
    EXPECT_TRUE(one.texts[0].value_len == two.texts[0].value_len, "value_len deterministic");
    EXPECT_MEM_EQ(one.card.purpose, two.card.purpose, one.card.purpose_len, "purpose bytes deterministic");
    EXPECT_MEM_EQ(one.texts[0].value, two.texts[0].value, one.texts[0].value_len, "text bytes deterministic");
    return 0;
}

int main(void) {
    if (decoded_nul_accepts_purpose_x00() != 0) return 1;
    if (decoded_nul_accepts_text_x00() != 0) return 1;
    if (decoded_nul_counts_purpose_len() != 0) return 1;
    if (decoded_nul_counts_text_value_len() != 0) return 1;
    if (decoded_nul_preserves_c_string_prefix_compatibility() != 0) return 1;
    if (decoded_nul_reports_purpose_escaped_x00() != 0) return 1;
    if (decoded_nul_reports_text_value_escaped_x00() != 0) return 1;
    if (decoded_nul_does_not_emit_lui0022_for_x00() != 0) return 1;
    if (decoded_nul_still_rejects_literal_nul_lui0023() != 0) return 1;
    if (decoded_nul_still_rejects_lowercase_hex_lui0020() != 0) return 1;
    if (decoded_nul_still_rejects_unknown_escape_lui0019() != 0) return 1;
    if (decoded_nul_preserves_source_spans() != 0) return 1;
    if (decoded_nul_preserves_no_effect_flags() != 0) return 1;
    if (decoded_nul_does_not_change_failed_parse_report() != 0) return 1;
    if (decoded_nul_is_deterministic() != 0) return 1;

    puts("l_ui_decoded_nul_acceptance_invariants: ok");
    return 0;
}
