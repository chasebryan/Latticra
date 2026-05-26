#include "latticra/l_ui_renderer.h"

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
    "  purpose \"render fixture\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"top render text\" }\n"
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
    "  rail bottom { text \"bottom render text\" }\n"
    "}\n";

static void authority_ok(latticra_l_ui_render_authority_summary_t *authority) {
    authority->status = LATTICRA_STATUS_OK;
    (void)snprintf(authority->status_label, sizeof(authority->status_label), "%s", "ok");
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label), "%s", "no_effect");
    (void)snprintf(authority->requested_effect_label, sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason), "%s", "none");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->network_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static int build_render(
    latticra_l_ui_render_mode_t mode,
    latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *semantic,
    latticra_lir_module_t *lir,
    latticra_l_ui_render_authority_summary_t *authority,
    latticra_l_ui_render_result_t *render) {
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), ast) == LATTICRA_STATUS_OK, "parse ast status");
    EXPECT_TRUE(ast->parse_result.error == LATTICRA_L_UI_PARSE_OK, "parse ast ok");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(ast, semantic) == LATTICRA_STATUS_OK, "semantic status");
    EXPECT_TRUE(semantic->error == LATTICRA_L_UI_SEMANTIC_OK, "semantic ok");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(ast, semantic, lir) == LATTICRA_STATUS_OK, "lir lower status");
    EXPECT_TRUE(lir->error == LATTICRA_LIR_OK, "lir ok");
    authority_ok(authority);
    request.mode = mode;
    request.ast = ast;
    request.semantic = semantic;
    request.lir = lir;
    request.authority = authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, render) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(render->error == LATTICRA_L_UI_RENDER_OK, "render ok");
    return 0;
}

static int detailed_mode_sets_explicit_metadata(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;

    EXPECT_TRUE(build_render(LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "detailed render builds");
    EXPECT_STR_EQ(render.report_classification, "detailed_report", "detailed report classification");
    EXPECT_STR_EQ(render.detail_level, "detailed", "detailed level label");
    EXPECT_STR_EQ(render.section_sequence, "HEADER,CARD,AUTHORITY,RAILS,FIELDS,TEXT,BINDINGS,LIR,SOURCE_SPANS,NO_EFFECT_FLAGS", "detailed section sequence");
    EXPECT_STR_EQ(render.no_effect_chain, "preserved", "no-effect chain label");
    EXPECT_STR_EQ(render.evidence_level, "metadata", "evidence level label");
    EXPECT_TRUE(render.detailed_report_available == 1, "detailed report available");
    EXPECT_TRUE(render.detailed_section_count == LATTICRA_L_UI_RENDER_DETAILED_SECTION_COUNT, "detailed section count");
    EXPECT_TRUE(render.section_count == LATTICRA_L_UI_RENDER_DETAILED_SECTION_COUNT, "render section count");
    EXPECT_TRUE(render.no_effect == 1, "no-effect preserved");
    EXPECT_TRUE(render.execution_allowed == 0, "execution remains denied");
    EXPECT_TRUE(render.network_allowed == 0, "network remains denied");
    return 0;
}

static int detailed_report_emits_explicit_metadata(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];

    EXPECT_TRUE(build_render(LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "detailed report render builds");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "detailed report writes");
    EXPECT_TRUE(strstr(report, "report_classification=detailed_report\n") != 0, "report classification emitted");
    EXPECT_TRUE(strstr(report, "detail_level=detailed\n") != 0, "detail level emitted");
    EXPECT_TRUE(strstr(report, "detailed_report_available=1\n") != 0, "detailed availability emitted");
    EXPECT_TRUE(strstr(report, "detailed_section_count=10\n") != 0, "detailed section count emitted");
    EXPECT_TRUE(strstr(report, "section_sequence=HEADER,CARD,AUTHORITY,RAILS,FIELDS,TEXT,BINDINGS,LIR,SOURCE_SPANS,NO_EFFECT_FLAGS\n") != 0, "section sequence emitted");
    EXPECT_TRUE(strstr(report, "no_effect_chain=preserved\n") != 0, "no-effect chain emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=metadata\n") != 0, "evidence level emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "network flag emitted");
    EXPECT_TRUE(strstr(report, "authority_network_allowed=0\n") != 0, "authority network flag emitted");
    EXPECT_TRUE(strstr(report, "authority.network_allowed=0\n") != 0, "detailed authority network flag emitted");
    EXPECT_TRUE(strstr(report, "SECTION NO_EFFECT_FLAGS\n") != 0, "no-effect section emitted");
    return 0;
}

static int summary_mode_remains_single_header_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];

    EXPECT_TRUE(build_render(LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "summary render builds");
    EXPECT_STR_EQ(render.report_classification, "summary_report", "summary report classification");
    EXPECT_STR_EQ(render.detail_level, "summary", "summary detail label");
    EXPECT_STR_EQ(render.section_sequence, "HEADER", "summary section sequence");
    EXPECT_TRUE(render.detailed_report_available == 0, "summary detailed unavailable");
    EXPECT_TRUE(render.detailed_section_count == 0u, "summary detailed section count");
    EXPECT_TRUE(render.section_count == 1u, "summary section count");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "summary report writes");
    EXPECT_TRUE(strstr(report, "report_classification=summary_report\n") != 0, "summary classification emitted");
    EXPECT_TRUE(strstr(report, "section_sequence=HEADER\n") != 0, "summary sequence emitted");
    EXPECT_TRUE(strstr(report, "SECTION CARD\n") == 0, "summary omits detailed sections");
    return 0;
}

int main(void) {
    if (detailed_mode_sets_explicit_metadata() != 0) return 1;
    if (detailed_report_emits_explicit_metadata() != 0) return 1;
    if (summary_mode_remains_single_header_report() != 0) return 1;

    puts("l_ui_rendering_detailed_report_refinement: ok");
    return 0;
}
