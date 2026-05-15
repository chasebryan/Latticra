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
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"preview-only no-live-movement no-host-effect no-external-effect\" }\n"
    "}\n";

static int parse_valid(latticra_l_ui_ast_result_t *ast) {
    return latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), ast) == LATTICRA_STATUS_OK;
}

static int valid_fixture_builds_ast_summary(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "valid AST parse should succeed");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "valid AST parse error");
    EXPECT_STR_EQ(ast.card.name, "NucleusPreview", "AST card name");
    EXPECT_TRUE(ast.rail_count == 9u, "AST rail count");
    EXPECT_TRUE(ast.field_count == 23u, "AST field count");
    EXPECT_TRUE(ast.text_count == 2u, "AST text count");
    return 0;
}

static int ast_card_name_is_nucleus_preview(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST card parse should succeed");
    EXPECT_STR_EQ(ast.card.name, "NucleusPreview", "AST card name stable");
    EXPECT_STR_EQ(ast.card.purpose, "operator-visible Nucleus preview report", "AST purpose stable");
    return 0;
}

static int ast_counts_match_fixture(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST count parse should succeed");
    EXPECT_TRUE(ast.card.rail_count == 9u, "card rail count");
    EXPECT_TRUE(ast.card.field_count == 23u, "card field count");
    EXPECT_TRUE(ast.card.text_count == 2u, "card text count");
    EXPECT_TRUE(ast.rail_count == ast.card.rail_count, "top rail count matches card");
    EXPECT_TRUE(ast.field_count == ast.card.field_count, "top field count matches card");
    EXPECT_TRUE(ast.text_count == ast.card.text_count, "top text count matches card");
    return 0;
}

static int ast_preserves_effect_none(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST effect parse should succeed");
    EXPECT_STR_EQ(ast.card.effect, "none", "AST effect");
    return 0;
}

static int ast_preserves_boundary_preview_only(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST boundary parse should succeed");
    EXPECT_STR_EQ(ast.card.boundary, "preview_only", "AST boundary");
    return 0;
}

static int ast_contains_required_rails(void) {
    static const char *expected[] = {
        "top", "state", "trace", "safety", "gates", "effects", "policy", "execution", "bottom"
    };
    latticra_l_ui_ast_result_t ast;
    size_t index;
    EXPECT_TRUE(parse_valid(&ast), "AST rail parse should succeed");
    for (index = 0u; index < sizeof(expected) / sizeof(expected[0]); index++) {
        EXPECT_STR_EQ(ast.rails[index].name, expected[index], "AST required rail");
        EXPECT_TRUE(ast.rails[index].span.start_line > 0u, "rail span start line");
        EXPECT_TRUE(ast.rails[index].span.end_offset >= ast.rails[index].span.start_offset, "rail span offsets");
    }
    return 0;
}

static int ast_contains_required_fields(void) {
    static const char *expected_names[] = {
        "origin", "route", "axis", "path", "breadcrumb", "trace", "health", "risk", "lock",
        "dark_phase", "safe_portal", "rollback", "host", "external", "requested", "request",
        "policy", "reason", "executed", "mutation", "server", "recovery", "hardware"
    };
    static const char *expected_bindings[] = {
        "state.origin", "state.route", "state.axis", "state.path", "state.breadcrumb", "state.trace",
        "state.health", "state.risk", "state.lock", "state.dark_phase", "state.safe_portal",
        "state.rollback", "state.host_effect", "state.external_effect", "preview.requested_effect",
        "preview.request", "preview.policy", "preview.reason", "preview.executed",
        "preview.mutation_allowed", "preview.server_interaction_allowed", "preview.recovery_allowed",
        "preview.hardware_allowed"
    };
    latticra_l_ui_ast_result_t ast;
    size_t index;
    EXPECT_TRUE(parse_valid(&ast), "AST field parse should succeed");
    for (index = 0u; index < sizeof(expected_names) / sizeof(expected_names[0]); index++) {
        EXPECT_STR_EQ(ast.fields[index].name, expected_names[index], "AST field name");
        EXPECT_STR_EQ(ast.fields[index].binding, expected_bindings[index], "AST field binding");
    }
    return 0;
}

static int ast_contains_text_nodes(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST text parse should succeed");
    EXPECT_STR_EQ(ast.texts[0].value, "Latticra / Nucleus Preview / effect-bound", "AST top text");
    EXPECT_STR_EQ(
        ast.texts[1].value,
        "preview-only no-live-movement no-host-effect no-external-effect",
        "AST bottom text");
    return 0;
}

static int ast_nodes_have_source_spans(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST span parse should succeed");
    EXPECT_TRUE(ast.card.span.end_offset > ast.card.span.start_offset, "card span populated");
    EXPECT_TRUE(ast.rails[0].span.end_offset > ast.rails[0].span.start_offset, "rail span populated");
    EXPECT_TRUE(ast.fields[0].span.end_offset > ast.fields[0].span.start_offset, "field span populated");
    EXPECT_TRUE(ast.texts[0].span.end_offset > ast.texts[0].span.start_offset, "text span populated");
    return 0;
}

static int ast_bindings_have_binding_spans(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST binding span parse should succeed");
    EXPECT_TRUE(ast.fields[0].binding_span.end_offset > ast.fields[0].binding_span.start_offset, "binding span populated");
    EXPECT_TRUE(ast.fields[0].binding_span.start_line > 0u, "binding span line");
    return 0;
}

static int ast_rejects_failed_parse(void) {
    latticra_l_ui_ast_result_t ast;
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "failed parse AST error");
    EXPECT_TRUE(ast.rail_count == 0u, "failed parse rail count");
    EXPECT_TRUE(ast.field_count == 0u, "failed parse field count");
    EXPECT_TRUE(ast.text_count == 0u, "failed parse text count");
    return 0;
}

static int ast_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST no-effect parse should succeed");
    EXPECT_TRUE(ast.no_effect == 1, "AST no_effect");
    EXPECT_TRUE(ast.execution_allowed == 0, "AST execution flag");
    EXPECT_TRUE(ast.mutation_allowed == 0, "AST mutation flag");
    EXPECT_TRUE(ast.server_allowed == 0, "AST server flag");
    EXPECT_TRUE(ast.recovery_allowed == 0, "AST recovery flag");
    EXPECT_TRUE(ast.hardware_allowed == 0, "AST hardware flag");
    return 0;
}

static int ast_report_contains_required_fields(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_REPORT_MAX];
    EXPECT_TRUE(parse_valid(&ast), "AST report parse should succeed");
    EXPECT_TRUE(latticra_l_ui_ast_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "AST report render");
    EXPECT_TRUE(strstr(report, "L-UI AST SUMMARY") != 0, "AST report title");
    EXPECT_TRUE(strstr(report, "card=NucleusPreview") != 0, "AST report card");
    EXPECT_TRUE(strstr(report, "rail_count=9") != 0, "AST report rail count");
    EXPECT_TRUE(strstr(report, "field_count=23") != 0, "AST report field count");
    EXPECT_TRUE(strstr(report, "text_count=2") != 0, "AST report text count");
    EXPECT_TRUE(strstr(report, "effect=none") != 0, "AST report effect");
    EXPECT_TRUE(strstr(report, "boundary=preview_only") != 0, "AST report boundary");
    EXPECT_TRUE(strstr(report, "no_effect=1") != 0, "AST report no effect");
    return 0;
}

static int ast_report_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast_one;
    latticra_l_ui_ast_result_t ast_two;
    char report_one[LATTICRA_L_UI_AST_REPORT_MAX];
    char report_two[LATTICRA_L_UI_AST_REPORT_MAX];
    EXPECT_TRUE(parse_valid(&ast_one), "first AST report parse should succeed");
    EXPECT_TRUE(parse_valid(&ast_two), "second AST report parse should succeed");
    EXPECT_TRUE(latticra_l_ui_ast_report(&ast_one, report_one, sizeof(report_one)) == LATTICRA_STATUS_OK, "first AST report");
    EXPECT_TRUE(latticra_l_ui_ast_report(&ast_two, report_two, sizeof(report_two)) == LATTICRA_STATUS_OK, "second AST report");
    EXPECT_TRUE(strcmp(report_one, report_two) == 0, "AST report deterministic");
    return 0;
}

static int ast_capacity_limits_are_enforced(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST capacity parse should succeed");
    EXPECT_TRUE(ast.rail_count <= LATTICRA_L_UI_AST_RAIL_MAX, "rail capacity");
    EXPECT_TRUE(ast.field_count <= LATTICRA_L_UI_AST_FIELD_MAX, "field capacity");
    EXPECT_TRUE(ast.text_count <= LATTICRA_L_UI_AST_TEXT_MAX, "text capacity");
    return 0;
}

static int ast_does_not_retain_source_pointers(void) {
    char source[sizeof(VALID_FIXTURE)];
    latticra_l_ui_ast_result_t ast;
    (void)snprintf(source, sizeof(source), "%s", VALID_FIXTURE);
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "AST copy parse");
    memset(source, 'x', sizeof(source));
    EXPECT_STR_EQ(ast.card.name, "NucleusPreview", "AST card name copied");
    EXPECT_STR_EQ(ast.fields[0].binding, "state.origin", "AST binding copied");
    EXPECT_STR_EQ(ast.texts[0].value, "Latticra / Nucleus Preview / effect-bound", "AST text copied");
    return 0;
}

static int ast_labels_are_stable(void) {
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(parse_valid(&ast), "AST labels parse should succeed");
    EXPECT_STR_EQ(ast.rails[1].name, "state", "rail label stable");
    EXPECT_STR_EQ(ast.fields[20].name, "server", "field label stable");
    EXPECT_STR_EQ(ast.fields[20].binding, "preview.server_interaction_allowed", "binding label stable");
    return 0;
}

static int ast_node_kind_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_CARD), "card", "card kind");
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_RAIL), "rail", "rail kind");
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_FIELD), "field", "field kind");
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_TEXT), "text", "text kind");
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_BINDING), "binding", "binding kind");
    EXPECT_STR_EQ(latticra_l_ui_ast_node_kind_label(LATTICRA_L_UI_AST_NODE_UNKNOWN), "unknown", "unknown kind");
    return 0;
}

static int ast_bad_arguments_are_rejected(void) {
    latticra_l_ui_ast_result_t ast;
    char report[LATTICRA_L_UI_AST_REPORT_MAX];
    char small[8];
    EXPECT_TRUE(latticra_l_ui_parse_ast(0, 1u, &ast) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL AST source");
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_FIXTURE, strlen(VALID_FIXTURE), 0) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL AST result");
    EXPECT_TRUE(parse_valid(&ast), "AST bad report parse should succeed");
    EXPECT_TRUE(latticra_l_ui_ast_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL AST report input");
    EXPECT_TRUE(latticra_l_ui_ast_report(&ast, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT, "NULL AST report buffer");
    EXPECT_TRUE(latticra_l_ui_ast_report(&ast, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small AST report buffer");
    return 0;
}

int main(void) {
    if (valid_fixture_builds_ast_summary() != 0) return 1;
    if (ast_card_name_is_nucleus_preview() != 0) return 1;
    if (ast_counts_match_fixture() != 0) return 1;
    if (ast_preserves_effect_none() != 0) return 1;
    if (ast_preserves_boundary_preview_only() != 0) return 1;
    if (ast_contains_required_rails() != 0) return 1;
    if (ast_contains_required_fields() != 0) return 1;
    if (ast_contains_text_nodes() != 0) return 1;
    if (ast_nodes_have_source_spans() != 0) return 1;
    if (ast_bindings_have_binding_spans() != 0) return 1;
    if (ast_rejects_failed_parse() != 0) return 1;
    if (ast_preserves_no_effect_flags() != 0) return 1;
    if (ast_report_contains_required_fields() != 0) return 1;
    if (ast_report_is_deterministic() != 0) return 1;
    if (ast_capacity_limits_are_enforced() != 0) return 1;
    if (ast_does_not_retain_source_pointers() != 0) return 1;
    if (ast_labels_are_stable() != 0) return 1;
    if (ast_node_kind_labels_are_stable() != 0) return 1;
    if (ast_bad_arguments_are_rejected() != 0) return 1;

    puts("l_ui_parser_ast_invariants: ok");
    return 0;
}
