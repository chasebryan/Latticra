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

static const char VALID_FIXTURE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"operator-visible Nucleus preview report\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"Latticra / Nucleus Preview / effect-bound\" }\n"
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
    "  rail bottom { text \"preview-only no-live-movement no-host-effect no-external-effect\" }\n"
    "}\n";

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

static int make_source(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    const char *top_text,
    const char *bottom_text) {
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
    return written >= 0 && (size_t)written < buffer_len;
}

static int parse_valid(latticra_l_ui_ast_result_t *ast) {
    return latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), ast) == LATTICRA_STATUS_OK &&
           ast->parse_result.error == LATTICRA_L_UI_PARSE_OK;
}

static int source_backed_purpose_matches_fixture_source(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "fixture AST should parse");
    EXPECT_STR_EQ(ast.card.purpose, "operator-visible Nucleus preview report", "source-backed purpose");
    return 0;
}

static int source_backed_top_text_matches_fixture_source(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "fixture AST should parse");
    EXPECT_STR_EQ(ast.texts[0].value, "Latticra / Nucleus Preview / effect-bound", "source-backed top text");
    return 0;
}

static int source_backed_bottom_text_matches_fixture_source(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "fixture AST should parse");
    EXPECT_STR_EQ(ast.texts[1].value, "preview-only no-live-movement no-host-effect no-external-effect", "source-backed bottom text");
    return 0;
}

static int source_backed_text_values_are_copied(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "custom purpose", "custom top", "custom bottom"), "custom source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "custom AST parse status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "custom AST parse error");
    EXPECT_STR_EQ(ast.card.purpose, "custom purpose", "custom purpose copied");
    EXPECT_STR_EQ(ast.texts[0].value, "custom top", "custom top copied");
    EXPECT_STR_EQ(ast.texts[1].value, "custom bottom", "custom bottom copied");
    return 0;
}

static int source_backed_text_does_not_retain_source_pointers(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "copy purpose", "copy top", "copy bottom"), "copy source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "copy AST parse status");
    memset(source, 'x', sizeof(source));
    EXPECT_STR_EQ(ast.card.purpose, "copy purpose", "purpose should be copied");
    EXPECT_STR_EQ(ast.texts[0].value, "copy top", "top text should be copied");
    EXPECT_STR_EQ(ast.texts[1].value, "copy bottom", "bottom text should be copied");
    return 0;
}

static int source_backed_text_excludes_quotes(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "quoted purpose", "quoted top", "quoted bottom"), "quoted source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "quoted AST parse status");
    EXPECT_TRUE(strchr(ast.card.purpose, '"') == 0, "purpose excludes quotes");
    EXPECT_TRUE(strchr(ast.texts[0].value, '"') == 0, "top text excludes quotes");
    EXPECT_TRUE(strchr(ast.texts[1].value, '"') == 0, "bottom text excludes quotes");
    return 0;
}

static int source_backed_text_preserves_ast_counts(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "count purpose", "count top", "count bottom"), "count source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "count AST parse status");
    EXPECT_TRUE(ast.rail_count == 9u, "rail count preserved");
    EXPECT_TRUE(ast.field_count == 24u, "field count preserved");
    EXPECT_TRUE(ast.text_count == 2u, "text count preserved");
    return 0;
}

static int source_backed_text_preserves_no_effect_flags(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "flag purpose", "flag top", "flag bottom"), "flag source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "flag AST parse status");
    EXPECT_TRUE(ast.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(ast.execution_allowed == 0, "execution flag preserved");
    EXPECT_TRUE(ast.mutation_allowed == 0, "mutation flag preserved");
    EXPECT_TRUE(ast.server_allowed == 0, "server flag preserved");
    EXPECT_TRUE(ast.network_allowed == 0, "network flag preserved");
    EXPECT_TRUE(ast.recovery_allowed == 0, "recovery flag preserved");
    EXPECT_TRUE(ast.hardware_allowed == 0, "hardware flag preserved");
    return 0;
}

static int source_backed_text_updates_detailed_report_literals(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "report purpose", "report top", "report bottom"), "report source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "report AST parse status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "detailed report status");
    EXPECT_TRUE(strstr(report, "purpose=report purpose\n") != 0, "report purpose literal updated");
    EXPECT_TRUE(strstr(report, "value=report top\n") != 0, "report top literal updated");
    EXPECT_TRUE(strstr(report, "value=report bottom\n") != 0, "report bottom literal updated");
    return 0;
}

static int source_backed_text_updates_detailed_report_escaped_fields(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "escape purpose", "escape top", "escape bottom"), "escaped report source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "escaped report AST parse status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "escaped detailed report status");
    EXPECT_TRUE(strstr(report, "purpose_escaped=escape purpose\n") != 0, "report purpose escaped updated");
    EXPECT_TRUE(strstr(report, "value_escaped=escape top\n") != 0, "report top escaped updated");
    EXPECT_TRUE(strstr(report, "value_escaped=escape bottom\n") != 0, "report bottom escaped updated");
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

static int source_backed_text_rejects_or_classifies_oversized_purpose(void) {
    char source[8192];
    char long_value[LATTICRA_L_UI_AST_PURPOSE_MAX + 1u];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(fill_repeated(long_value, sizeof(long_value), 'p'), "long purpose builds");
    EXPECT_TRUE(make_source(source, sizeof(source), long_value, "small top", "small bottom"), "oversized purpose source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "oversized purpose AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE, "oversized purpose classified too large");
    EXPECT_TRUE(ast.rail_count == 0u && ast.field_count == 0u && ast.text_count == 0u, "oversized purpose no partial AST");
    return 0;
}

static int source_backed_text_rejects_or_classifies_oversized_text(void) {
    char source[8192];
    char long_value[LATTICRA_L_UI_AST_PURPOSE_MAX + 1u];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(fill_repeated(long_value, sizeof(long_value), 't'), "long text builds");
    EXPECT_TRUE(make_source(source, sizeof(source), "small purpose", long_value, "small bottom"), "oversized text source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "oversized text AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE, "oversized text classified too large");
    EXPECT_TRUE(ast.rail_count == 0u && ast.field_count == 0u && ast.text_count == 0u, "oversized text no partial AST");
    return 0;
}

static int source_backed_text_does_not_change_failed_parse_report(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed parse report status");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed parse report unchanged");
    EXPECT_TRUE(strstr(report, "purpose=") == 0, "failed parse has no source-backed purpose");
    EXPECT_TRUE(strstr(report, "value=") == 0, "failed parse has no source-backed value");
    return 0;
}

static int source_backed_text_is_deterministic(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast_one;
    latticra_l_ui_ast_result_t ast_two;
    EXPECT_TRUE(make_source(source, sizeof(source), "det purpose", "det top", "det bottom"), "det source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast_one) == LATTICRA_STATUS_OK, "first deterministic parse");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast_two) == LATTICRA_STATUS_OK, "second deterministic parse");
    EXPECT_STR_EQ(ast_one.card.purpose, ast_two.card.purpose, "deterministic purpose");
    EXPECT_STR_EQ(ast_one.texts[0].value, ast_two.texts[0].value, "deterministic top text");
    EXPECT_STR_EQ(ast_one.texts[1].value, ast_two.texts[1].value, "deterministic bottom text");
    return 0;
}

static int source_backed_text_decodes_accepted_string_escapes(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), "raw\\ntext", "raw\\ttext", "raw\\\"quote"), "accepted escape source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "accepted escape AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "accepted escape AST parse OK");
    EXPECT_STR_EQ(ast.card.purpose, "raw\ntext", "purpose escape decoded");
    EXPECT_STR_EQ(ast.texts[0].value, "raw\ttext", "top text escape decoded");
    EXPECT_STR_EQ(ast.texts[1].value, "raw\"quote", "bottom text escaped quote decoded");
    return 0;
}

int main(void) {
    if (source_backed_purpose_matches_fixture_source() != 0) return 1;
    if (source_backed_top_text_matches_fixture_source() != 0) return 1;
    if (source_backed_bottom_text_matches_fixture_source() != 0) return 1;
    if (source_backed_text_values_are_copied() != 0) return 1;
    if (source_backed_text_does_not_retain_source_pointers() != 0) return 1;
    if (source_backed_text_excludes_quotes() != 0) return 1;
    if (source_backed_text_preserves_ast_counts() != 0) return 1;
    if (source_backed_text_preserves_no_effect_flags() != 0) return 1;
    if (source_backed_text_updates_detailed_report_literals() != 0) return 1;
    if (source_backed_text_updates_detailed_report_escaped_fields() != 0) return 1;
    if (source_backed_text_rejects_or_classifies_oversized_purpose() != 0) return 1;
    if (source_backed_text_rejects_or_classifies_oversized_text() != 0) return 1;
    if (source_backed_text_does_not_change_failed_parse_report() != 0) return 1;
    if (source_backed_text_is_deterministic() != 0) return 1;
    if (source_backed_text_decodes_accepted_string_escapes() != 0) return 1;

    puts("l_ui_ast_source_backed_text_invariants: ok");
    return 0;
}
