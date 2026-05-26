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

static int build_report(latticra_l_ui_ast_result_t *ast, char *report, size_t report_len) {
    if (latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), ast) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_l_ui_ast_detailed_report(ast, report, report_len) != LATTICRA_STATUS_OK) {
        return 1;
    }
    return 0;
}

static int index_of(const char *haystack, const char *needle, size_t *out_index) {
    const char *found = strstr(haystack, needle);
    if (found == 0) {
        return 1;
    }
    *out_index = (size_t)(found - haystack);
    return 0;
}

static int detailed_report_contains_title(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "detailed report builds");
    EXPECT_TRUE(strstr(report, "L-UI AST DETAILED REPORT\n") != 0, "detailed report title");
    return 0;
}

static int detailed_report_contains_card_section(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "card report builds");
    EXPECT_TRUE(strstr(report, "[card]\n") != 0, "card section exists");
    EXPECT_TRUE(strstr(report, "kind=card\n") != 0, "card kind exists");
    EXPECT_TRUE(strstr(report, "name=NucleusPreview\n") != 0, "card name exists");
    EXPECT_TRUE(strstr(report, "purpose=operator-visible Nucleus preview report\n") != 0, "card purpose exists");
    return 0;
}

static int detailed_report_contains_all_rails(void) {
    static const char *rails[] = {
        "name=top\n", "name=state\n", "name=trace\n", "name=safety\n", "name=gates\n",
        "name=effects\n", "name=policy\n", "name=execution\n", "name=bottom\n"
    };
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t index;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "rail report builds");
    for (index = 0u; index < sizeof(rails) / sizeof(rails[0]); index++) {
        EXPECT_TRUE(strstr(report, rails[index]) != 0, "required rail exists");
    }
    return 0;
}

static int detailed_report_contains_all_fields(void) {
    static const char *fields[] = {
        "name=origin\n", "name=route\n", "name=axis\n", "name=path\n", "name=breadcrumb\n",
        "name=trace\n", "name=health\n", "name=risk\n", "name=lock\n", "name=dark_phase\n",
        "name=safe_portal\n", "name=rollback\n", "name=host\n", "name=external\n", "name=requested\n",
        "name=request\n", "name=policy\n", "name=reason\n", "name=executed\n", "name=mutation\n",
        "name=server\n", "name=recovery\n", "name=hardware\n"
    };
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t index;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "field report builds");
    for (index = 0u; index < sizeof(fields) / sizeof(fields[0]); index++) {
        EXPECT_TRUE(strstr(report, fields[index]) != 0, "required field exists");
    }
    EXPECT_TRUE(strstr(report, "binding=preview.server_interaction_allowed\n") != 0, "server binding exists");
    return 0;
}

static int detailed_report_contains_all_text_nodes(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "text report builds");
    EXPECT_TRUE(strstr(report, "value=Latticra / Nucleus Preview / effect-bound\n") != 0, "top text exists");
    EXPECT_TRUE(strstr(report, "value=preview-only no-live-movement no-host-effect no-external-effect\n") != 0, "bottom text exists");
    return 0;
}

static int detailed_report_preserves_rail_order(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t top;
    size_t state;
    size_t bottom;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "rail order report builds");
    EXPECT_TRUE(index_of(report, "[rail 0]\nkind=rail\nname=top\n", &top) == 0, "top rail index");
    EXPECT_TRUE(index_of(report, "[rail 1]\nkind=rail\nname=state\n", &state) == 0, "state rail index");
    EXPECT_TRUE(index_of(report, "[rail 8]\nkind=rail\nname=bottom\n", &bottom) == 0, "bottom rail index");
    EXPECT_TRUE(top < state && state < bottom, "rail order preserved");
    return 0;
}

static int detailed_report_preserves_field_order(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t origin;
    size_t server;
    size_t hardware;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "field order report builds");
    EXPECT_TRUE(index_of(report, "[field 0]\nkind=field\nname=origin\n", &origin) == 0, "origin field index");
    EXPECT_TRUE(index_of(report, "[field 20]\nkind=field\nname=server\n", &server) == 0, "server field index");
    EXPECT_TRUE(index_of(report, "[field 22]\nkind=field\nname=hardware\n", &hardware) == 0, "hardware field index");
    EXPECT_TRUE(origin < server && server < hardware, "field order preserved");
    return 0;
}

static int detailed_report_preserves_text_order(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t text_zero;
    size_t text_one;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "text order report builds");
    EXPECT_TRUE(index_of(report, "[text 0]", &text_zero) == 0, "first text index");
    EXPECT_TRUE(index_of(report, "[text 1]", &text_one) == 0, "second text index");
    EXPECT_TRUE(text_zero < text_one, "text order preserved");
    return 0;
}

static int detailed_report_includes_card_span(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t card;
    size_t span;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "card span report builds");
    EXPECT_TRUE(index_of(report, "[card]", &card) == 0, "card section index");
    EXPECT_TRUE(index_of(report, "span_start_offset=", &span) == 0, "card span index");
    EXPECT_TRUE(card < span, "card span appears after card section");
    return 0;
}

static int detailed_report_includes_rail_spans(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t rail;
    size_t span;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "rail span report builds");
    EXPECT_TRUE(index_of(report, "[rail 0]", &rail) == 0, "rail section index");
    EXPECT_TRUE(index_of(report + rail, "span_start_offset=", &span) == 0, "rail span index");
    return 0;
}

static int detailed_report_includes_field_spans(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t field;
    size_t span;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "field span report builds");
    EXPECT_TRUE(index_of(report, "[field 0]", &field) == 0, "field section index");
    EXPECT_TRUE(index_of(report + field, "span_start_offset=", &span) == 0, "field span index");
    return 0;
}

static int detailed_report_includes_binding_spans(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "binding span report builds");
    EXPECT_TRUE(strstr(report, "binding_span_start_offset=") != 0, "binding span start exists");
    EXPECT_TRUE(strstr(report, "binding_span_end_column=") != 0, "binding span end exists");
    return 0;
}

static int detailed_report_includes_text_spans(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    size_t text;
    size_t span;
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "text span report builds");
    EXPECT_TRUE(index_of(report, "[text 0]", &text) == 0, "text section index");
    EXPECT_TRUE(index_of(report + text, "span_start_offset=", &span) == 0, "text span index");
    return 0;
}

static int detailed_report_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "no-effect report builds");
    EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0, "no_effect in report");
    EXPECT_TRUE(strstr(report, "execution_allowed=0\n") != 0, "execution flag in report");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0\n") != 0, "mutation flag in report");
    EXPECT_TRUE(strstr(report, "server_allowed=0\n") != 0, "server flag in report");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "network flag in report");
    EXPECT_TRUE(strstr(report, "recovery_allowed=0\n") != 0, "recovery flag in report");
    EXPECT_TRUE(strstr(report, "hardware_allowed=0\n") != 0, "hardware flag in report");
    return 0;
}

static int detailed_report_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    char report_one[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    char report_two[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), &ast) == LATTICRA_STATUS_OK, "determinism parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report_one, sizeof(report_one)) == LATTICRA_STATUS_OK, "first detail report");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report_two, sizeof(report_two)) == LATTICRA_STATUS_OK, "second detail report");
    EXPECT_TRUE(strcmp(report_one, report_two) == 0, "detailed report deterministic");
    return 0;
}

static int detailed_report_rejects_bad_arguments(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), &ast) == LATTICRA_STATUS_OK, "bad arg parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL AST rejected");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL buffer rejected");
    return 0;
}

static int detailed_report_rejects_small_buffers(void) {
    latticra_l_ui_ast_result_t ast;
    char small[8];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), &ast) == LATTICRA_STATUS_OK, "small buffer parse");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer rejected");
    return 0;
}

static int detailed_report_omits_unused_capacity_slots(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_report(&ast, report, sizeof(report)) == 0, "capacity report builds");
    EXPECT_TRUE(strstr(report, "[rail 9]") == 0, "unused rail omitted");
    EXPECT_TRUE(strstr(report, "[field 23]") == 0, "unused field omitted");
    EXPECT_TRUE(strstr(report, "[text 2]") == 0, "unused text omitted");
    return 0;
}

static int detailed_report_handles_failed_parse(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed parse detail report");
    EXPECT_TRUE(strstr(report, "L-UI AST DETAILED REPORT\n") != 0, "failed report title");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed parse error label");
    EXPECT_TRUE(strstr(report, "rail_count=0\n") != 0, "failed rail count");
    EXPECT_TRUE(strstr(report, "field_count=0\n") != 0, "failed field count");
    EXPECT_TRUE(strstr(report, "text_count=0\n") != 0, "failed text count");
    return 0;
}

int main(void) {
    if (detailed_report_contains_title() != 0) return 1;
    if (detailed_report_contains_card_section() != 0) return 1;
    if (detailed_report_contains_all_rails() != 0) return 1;
    if (detailed_report_contains_all_fields() != 0) return 1;
    if (detailed_report_contains_all_text_nodes() != 0) return 1;
    if (detailed_report_preserves_rail_order() != 0) return 1;
    if (detailed_report_preserves_field_order() != 0) return 1;
    if (detailed_report_preserves_text_order() != 0) return 1;
    if (detailed_report_includes_card_span() != 0) return 1;
    if (detailed_report_includes_rail_spans() != 0) return 1;
    if (detailed_report_includes_field_spans() != 0) return 1;
    if (detailed_report_includes_binding_spans() != 0) return 1;
    if (detailed_report_includes_text_spans() != 0) return 1;
    if (detailed_report_preserves_no_effect_flags() != 0) return 1;
    if (detailed_report_is_deterministic() != 0) return 1;
    if (detailed_report_rejects_bad_arguments() != 0) return 1;
    if (detailed_report_rejects_small_buffers() != 0) return 1;
    if (detailed_report_omits_unused_capacity_slots() != 0) return 1;
    if (detailed_report_handles_failed_parse() != 0) return 1;

    puts("l_ui_parser_ast_detailed_report_invariants: ok");
    return 0;
}
