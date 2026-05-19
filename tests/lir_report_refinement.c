#include "latticra/lir.h"

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

static const char VALID_SOURCE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"lir report refinement fixture\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"top lir text\" }\n"
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
    "  rail bottom { text \"bottom lir text\" }\n"
    "}\n";

static int lower_valid(latticra_l_ui_ast_result_t *ast, latticra_l_ui_semantic_result_t *semantic, latticra_lir_module_t *module) {
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), ast) == LATTICRA_STATUS_OK, "valid AST parse status");
    EXPECT_TRUE(ast->parse_result.error == LATTICRA_L_UI_PARSE_OK, "valid AST parse OK");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(ast, semantic) == LATTICRA_STATUS_OK, "valid semantic status");
    EXPECT_TRUE(semantic->error == LATTICRA_L_UI_SEMANTIC_OK, "valid semantic OK");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(ast, semantic, module) == LATTICRA_STATUS_OK, "valid LIR lower status");
    return 0;
}

static int lir_report_refinement_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lir_report_classification_label(LATTICRA_LIR_REPORT_EMPTY), "empty", "empty classification label");
    EXPECT_STR_EQ(latticra_lir_report_classification_label(LATTICRA_LIR_REPORT_MATERIALIZED), "materialized", "materialized classification label");
    EXPECT_STR_EQ(latticra_lir_report_classification_label(LATTICRA_LIR_REPORT_REJECTED), "rejected", "rejected classification label");
    EXPECT_STR_EQ(latticra_lir_report_classification_label(LATTICRA_LIR_REPORT_INVALID), "invalid", "invalid classification label");
    EXPECT_STR_EQ(latticra_lir_shape_kind_label(LATTICRA_LIR_SHAPE_UNKNOWN), "unknown", "unknown shape label");
    EXPECT_STR_EQ(latticra_lir_shape_kind_label(LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH), "l-ui-card-graph", "l-ui shape label");
    EXPECT_STR_EQ(latticra_lir_shape_kind_label(LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH), "lat-module-graph", "lat shape label");
    EXPECT_STR_EQ(latticra_lir_shape_kind_label(LATTICRA_LIR_SHAPE_INTERNAL_FIXTURE_GRAPH), "internal-fixture-graph", "fixture shape label");
    return 0;
}

static int lir_report_refinement_reports_materialized_l_ui_shape(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char report[LATTICRA_LIR_REPORT_MAX];

    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "materialized lower");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "materialized lir ok");
    EXPECT_TRUE(module.report_classification == LATTICRA_LIR_REPORT_MATERIALIZED, "materialized classification");
    EXPECT_TRUE(module.shape_kind == LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH, "l-ui graph shape");
    EXPECT_TRUE(module.contains_edge_count == 35u, "contains edge count");
    EXPECT_TRUE(module.binds_edge_count == 23u, "binds edge count");
    EXPECT_TRUE(module.annotates_edge_count == 2u, "annotates edge count");
    EXPECT_TRUE(module.orders_before_edge_count == 0u, "orders edge count");
    EXPECT_TRUE(module.transitions_from_edge_count == 0u, "transition edge count");
    EXPECT_TRUE(module.no_effect_chain_ok == 1, "no-effect chain ok");
    EXPECT_TRUE(module.evidence_level == 2u, "materialized evidence level");

    EXPECT_TRUE(latticra_lir_report(&module, report, sizeof(report)) == LATTICRA_STATUS_OK, "materialized report");
    EXPECT_TRUE(strstr(report, "report_classification=materialized\n") != 0, "classification report field");
    EXPECT_TRUE(strstr(report, "shape_kind=l-ui-card-graph\n") != 0, "shape report field");
    EXPECT_TRUE(strstr(report, "contains_edge_count=35\n") != 0, "contains count report field");
    EXPECT_TRUE(strstr(report, "binds_edge_count=23\n") != 0, "binds count report field");
    EXPECT_TRUE(strstr(report, "annotates_edge_count=2\n") != 0, "annotates count report field");
    EXPECT_TRUE(strstr(report, "no_effect_chain_ok=1\n") != 0, "no-effect chain report field");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "evidence report field");
    return 0;
}

static int lir_report_refinement_reports_semantic_rejection(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char report[LATTICRA_LIR_REPORT_MAX];

    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "parser failed AST status");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "parser failed semantic status");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "semantic rejection lower");
    EXPECT_TRUE(module.error == LATTICRA_LIR_SEMANTIC_FAILED, "semantic rejection error");
    EXPECT_TRUE(module.report_classification == LATTICRA_LIR_REPORT_REJECTED, "semantic rejection classification");
    EXPECT_TRUE(module.shape_kind == LATTICRA_LIR_SHAPE_UNKNOWN, "semantic rejection unknown shape");
    EXPECT_TRUE(module.node_count == 0u, "semantic rejection no nodes");
    EXPECT_TRUE(module.evidence_level == 1u, "semantic rejection evidence level");

    EXPECT_TRUE(latticra_lir_report(&module, report, sizeof(report)) == LATTICRA_STATUS_OK, "semantic rejection report");
    EXPECT_TRUE(strstr(report, "report_classification=rejected\n") != 0, "rejected report field");
    EXPECT_TRUE(strstr(report, "shape_kind=unknown\n") != 0, "unknown shape report field");
    EXPECT_TRUE(strstr(report, "evidence_level=1\n") != 0, "rejected evidence field");
    return 0;
}

static int lir_report_refinement_report_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char one[LATTICRA_LIR_REPORT_MAX];
    char two[LATTICRA_LIR_REPORT_MAX];

    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "deterministic lower");
    EXPECT_TRUE(latticra_lir_report(&module, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report");
    EXPECT_TRUE(latticra_lir_report(&module, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report");
    EXPECT_STR_EQ(one, two, "LIR report deterministic");
    return 0;
}

int main(void) {
    if (lir_report_refinement_labels_are_stable() != 0) return 1;
    if (lir_report_refinement_reports_materialized_l_ui_shape() != 0) return 1;
    if (lir_report_refinement_reports_semantic_rejection() != 0) return 1;
    if (lir_report_refinement_report_is_deterministic() != 0) return 1;

    puts("lir_report_refinement: ok");
    return 0;
}
