#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

#include "../src/l_ui_parser_ast.c"

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
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"preview-only no-live-movement no-host-effect no-external-effect\" }\n"
    "}\n";

static int escape_case(const char *input, size_t input_len, const char *expected, const char *message) {
    char output[128];
    EXPECT_TRUE(escape_report_string(input, input_len, output, sizeof(output)) == LATTICRA_STATUS_OK, message);
    EXPECT_STR_EQ(output, expected, message);
    return 0;
}

static int escape_preserves_printable_ascii(void) {
    const char input[] = "ABC xyz 123 ~!@#$%^&*()_+-=[]{}|;:',.<>/?";
    return escape_case(input, strlen(input), input, "printable ASCII should be preserved");
}

static int escape_newline_as_backslash_n(void) {
    const char input[] = "a\nb";
    return escape_case(input, strlen(input), "a\\nb", "newline escape");
}

static int escape_carriage_return_as_backslash_r(void) {
    const char input[] = "a\rb";
    return escape_case(input, strlen(input), "a\\rb", "carriage return escape");
}

static int escape_tab_as_backslash_t(void) {
    const char input[] = "a\tb";
    return escape_case(input, strlen(input), "a\\tb", "tab escape");
}

static int escape_quote_as_backslash_quote(void) {
    const char input[] = "a\"b";
    return escape_case(input, strlen(input), "a\\\"b", "quote escape");
}

static int escape_backslash_as_double_backslash(void) {
    const char input[] = "a\\b";
    return escape_case(input, strlen(input), "a\\\\b", "backslash escape");
}

static int escape_nul_as_hex_00(void) {
    const char input[] = { 'a', '\0', 'b' };
    return escape_case(input, sizeof(input), "a\\x00b", "NUL escape");
}

static int escape_control_bytes_as_uppercase_hex(void) {
    const char input[] = { 'a', 0x01, 0x1F, 'b' };
    return escape_case(input, sizeof(input), "a\\x01\\x1Fb", "control byte escape");
}

static int escape_del_as_uppercase_hex(void) {
    const char input[] = { 'a', 0x7F, 'b' };
    return escape_case(input, sizeof(input), "a\\x7Fb", "DEL escape");
}

static int escape_non_ascii_bytes_as_uppercase_hex(void) {
    const char input[] = { 'a', (char)0x80, (char)0xFF, 'b' };
    return escape_case(input, sizeof(input), "a\\x80\\xFFb", "non-ASCII escape");
}

static int escape_rejects_small_buffers(void) {
    char output[4];
    const char input[] = { (char)0xFF, (char)0xFF };
    EXPECT_TRUE(
        escape_report_string(input, sizeof(input), output, sizeof(output)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small escape buffer should be rejected");
    EXPECT_TRUE(output[0] == '\0', "small escape buffer should be cleared");
    return 0;
}

static int escape_is_deterministic(void) {
    char output_one[128];
    char output_two[128];
    const char input[] = "a\n\t\\\"\x7F";
    EXPECT_TRUE(escape_report_string(input, strlen(input), output_one, sizeof(output_one)) == LATTICRA_STATUS_OK, "first escape");
    EXPECT_TRUE(escape_report_string(input, strlen(input), output_two, sizeof(output_two)) == LATTICRA_STATUS_OK, "second escape");
    EXPECT_STR_EQ(output_one, output_two, "escaped output deterministic");
    return 0;
}

static int build_report(latticra_l_ui_ast_result_t *ast, char *report, size_t report_len) {
    if (latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), ast) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_l_ui_ast_detailed_report(ast, report, report_len) != LATTICRA_STATUS_OK) {
        return 1;
    }
    return 0;
}

static int detailed_report_contains_escaped_purpose(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "escaped purpose report builds");
    EXPECT_TRUE(
        strstr(report, "purpose_escaped=operator-visible Nucleus preview report\n") != 0,
        "escaped purpose exists");
    return 0;
}

static int detailed_report_contains_escaped_text_values(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "escaped text report builds");
    EXPECT_TRUE(
        strstr(report, "value_escaped=Latticra / Nucleus Preview / effect-bound\n") != 0,
        "first escaped text exists");
    EXPECT_TRUE(
        strstr(report, "value_escaped=preview-only no-live-movement no-host-effect no-external-effect\n") != 0,
        "second escaped text exists");
    return 0;
}

static int detailed_report_escaped_fields_are_additive(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "additive escaped report builds");
    EXPECT_TRUE(strstr(report, "purpose=operator-visible Nucleus preview report\n") != 0, "literal purpose remains");
    EXPECT_TRUE(strstr(report, "purpose_escaped=operator-visible Nucleus preview report\n") != 0, "escaped purpose added");
    EXPECT_TRUE(strstr(report, "value=Latticra / Nucleus Preview / effect-bound\n") != 0, "literal text remains");
    EXPECT_TRUE(strstr(report, "value_escaped=Latticra / Nucleus Preview / effect-bound\n") != 0, "escaped text added");
    return 0;
}

static int detailed_report_escapes_mutated_values(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), &ast) == LATTICRA_STATUS_OK, "mutated value AST builds");
    (void)snprintf(ast.card.purpose, sizeof(ast.card.purpose), "line\nquote\"slash\\tab\t");
    (void)snprintf(ast.texts[0].value, sizeof(ast.texts[0].value), "text\r\nnext");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "mutated report builds");
    EXPECT_TRUE(strstr(report, "purpose_escaped=line\\nquote\\\"slash\\\\tab\\t\n") != 0, "mutated purpose escaped");
    EXPECT_TRUE(strstr(report, "value_escaped=text\\r\\nnext\n") != 0, "mutated text escaped");
    return 0;
}

static int detailed_report_escape_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "no-effect escape report builds");
    EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0, "no_effect remains");
    EXPECT_TRUE(strstr(report, "execution_allowed=0\n") != 0, "execution remains denied");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0\n") != 0, "mutation remains denied");
    EXPECT_TRUE(strstr(report, "server_allowed=0\n") != 0, "server remains denied");
    EXPECT_TRUE(strstr(report, "recovery_allowed=0\n") != 0, "recovery remains denied");
    EXPECT_TRUE(strstr(report, "hardware_allowed=0\n") != 0, "hardware remains denied");
    return 0;
}

static int detailed_report_escape_does_not_change_failed_parse_report(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed AST parse result maps");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed detailed report builds");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed report error stays");
    EXPECT_TRUE(strstr(report, "purpose_escaped=") == 0, "failed report has no escaped purpose");
    EXPECT_TRUE(strstr(report, "value_escaped=") == 0, "failed report has no escaped text");
    return 0;
}

int main(void) {
    if (escape_preserves_printable_ascii() != 0) return 1;
    if (escape_newline_as_backslash_n() != 0) return 1;
    if (escape_carriage_return_as_backslash_r() != 0) return 1;
    if (escape_tab_as_backslash_t() != 0) return 1;
    if (escape_quote_as_backslash_quote() != 0) return 1;
    if (escape_backslash_as_double_backslash() != 0) return 1;
    if (escape_nul_as_hex_00() != 0) return 1;
    if (escape_control_bytes_as_uppercase_hex() != 0) return 1;
    if (escape_del_as_uppercase_hex() != 0) return 1;
    if (escape_non_ascii_bytes_as_uppercase_hex() != 0) return 1;
    if (escape_rejects_small_buffers() != 0) return 1;
    if (escape_is_deterministic() != 0) return 1;
    if (detailed_report_contains_escaped_purpose() != 0) return 1;
    if (detailed_report_contains_escaped_text_values() != 0) return 1;
    if (detailed_report_escaped_fields_are_additive() != 0) return 1;
    if (detailed_report_escapes_mutated_values() != 0) return 1;
    if (detailed_report_escape_preserves_no_effect_flags() != 0) return 1;
    if (detailed_report_escape_does_not_change_failed_parse_report() != 0) return 1;

    puts("l_ui_ast_escaped_string_report_invariants: ok");
    return 0;
}
