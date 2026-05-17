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
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"bottom render text\" }\n"
    "}\n";

static const char ESCAPED_NUL_SOURCE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"render fixture\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"top\\x00render\" }\n"
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
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static int build_render_from_source(
    const char *source,
    latticra_l_ui_render_mode_t mode,
    latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *semantic,
    latticra_lir_module_t *lir,
    latticra_l_ui_render_authority_summary_t *authority,
    latticra_l_ui_render_result_t *render) {
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), ast) == LATTICRA_STATUS_OK, "parse ast status");
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
    return 0;
}

static int l_ui_rendering_accepts_semantically_valid_l_ui_fixture(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "valid render builds");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_OK, "render ok");
    EXPECT_STR_EQ(render.card_name, "NucleusPreview", "render card name");
    EXPECT_TRUE(render.rail_count == 9u, "render rail count");
    EXPECT_TRUE(render.field_count == 23u, "render field count");
    EXPECT_TRUE(render.text_count == 2u, "render text count");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "render report builds");
    EXPECT_TRUE(strstr(report, "LATTICRA L-UI RENDER REPORT\n") != 0, "render report header");
    return 0;
}

static int l_ui_rendering_requires_semantic_success(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "base render builds");
    semantic.error = LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD;
    request.mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    request.ast = &ast;
    request.semantic = &semantic;
    request.lir = &lir;
    request.authority = &authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, &render) == LATTICRA_STATUS_OK, "semantic failed render returns status ok");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_SEMANTIC_FAILED, "semantic failure rejected");
    return 0;
}

static int l_ui_rendering_requires_lir_success(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "base render builds");
    lir.error = LATTICRA_LIR_SEMANTIC_FAILED;
    request.mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    request.ast = &ast;
    request.semantic = &semantic;
    request.lir = &lir;
    request.authority = &authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, &render) == LATTICRA_STATUS_OK, "lir failed render returns status ok");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_LIR_FAILED, "lir failure rejected");
    return 0;
}

static int l_ui_rendering_requires_authority_success(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "base render builds");
    authority.status = LATTICRA_STATUS_BUFFER_TOO_SMALL;
    request.mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    request.ast = &ast;
    request.semantic = &semantic;
    request.lir = &lir;
    request.authority = &authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, &render) == LATTICRA_STATUS_OK, "authority failed render returns status ok");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_AUTHORITY_FAILED, "authority failure rejected");
    return 0;
}

static int l_ui_rendering_rejects_non_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "base render builds");
    authority.mutation_allowed = 1;
    request.mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    request.ast = &ast;
    request.semantic = &semantic;
    request.lir = &lir;
    request.authority = &authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, &render) == LATTICRA_STATUS_OK, "non-no-effect render returns status ok");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_AUTHORITY_FAILED, "non-no-effect rejected");
    return 0;
}

static int l_ui_rendering_preserves_card_metadata(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "card metadata render builds");
    EXPECT_STR_EQ(render.card_name, ast.card.name, "card name preserved");
    EXPECT_STR_EQ(render.effect, "none", "effect preserved");
    EXPECT_STR_EQ(render.boundary, "preview_only", "boundary preserved");
    EXPECT_TRUE(render.span.start_offset == ast.card.span.start_offset, "card span start preserved");
    return 0;
}

static int l_ui_rendering_preserves_rail_order(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "rail render builds");
    EXPECT_STR_EQ(render.rail_names[0], "top", "first rail name");
    EXPECT_STR_EQ(render.rail_names[8], "bottom", "last rail name");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "rail report builds");
    EXPECT_TRUE(strstr(report, "rail[0].name=top\n") != 0, "rail report first rail");
    EXPECT_TRUE(strstr(report, "rail[8].name=bottom\n") != 0, "rail report last rail");
    return 0;
}

static int l_ui_rendering_preserves_field_bindings(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "field render builds");
    EXPECT_STR_EQ(render.field_names[0], "origin", "field name preserved");
    EXPECT_STR_EQ(render.field_bindings[0], "state.origin", "field binding preserved");
    EXPECT_STR_EQ(render.field_binding_prefixes[0], "state", "field binding prefix preserved");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "field report builds");
    EXPECT_TRUE(strstr(report, "field[0].binding=state.origin\n") != 0, "field report binding");
    return 0;
}

static int l_ui_rendering_preserves_text_lengths(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "text render builds");
    EXPECT_TRUE(render.text_value_lens[0] == lir.texts[0].value_len, "text length preserved");
    EXPECT_STR_EQ(render.text_escaped_values[0], lir.texts[0].escaped_value, "escaped text preserved");
    return 0;
}

static int l_ui_rendering_preserves_escaped_x00_visibility(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(ESCAPED_NUL_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "escaped NUL render builds");
    EXPECT_TRUE(strstr(render.text_escaped_values[0], "\\x00") != 0, "escaped NUL stored visibly");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "escaped NUL report builds");
    EXPECT_TRUE(strstr(report, "\\x00") != 0, "escaped NUL report visible");
    return 0;
}

static int l_ui_rendering_preserves_source_spans(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "span render builds");
    EXPECT_TRUE(render.rail_spans[0].start_offset == ast.rails[0].span.start_offset, "rail span preserved");
    EXPECT_TRUE(render.field_spans[0].start_offset == ast.fields[0].span.start_offset, "field span preserved");
    EXPECT_TRUE(render.field_binding_spans[0].start_offset == ast.fields[0].binding_span.start_offset, "binding span preserved");
    EXPECT_TRUE(render.text_spans[0].start_offset == lir.texts[0].source_span.start_offset, "text span preserved");
    return 0;
}

static int l_ui_rendering_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "flags render builds");
    EXPECT_TRUE(render.no_effect == 1, "render no_effect preserved");
    EXPECT_TRUE(render.execution_allowed == 0, "render execution denied");
    EXPECT_TRUE(render.mutation_allowed == 0, "render mutation denied");
    EXPECT_TRUE(render.server_allowed == 0, "render server denied");
    EXPECT_TRUE(render.recovery_allowed == 0, "render recovery denied");
    EXPECT_TRUE(render.hardware_allowed == 0, "render hardware denied");
    return 0;
}

static int l_ui_rendering_report_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char one[LATTICRA_L_UI_RENDER_REPORT_MAX];
    char two[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "deterministic render builds");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report builds");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report builds");
    EXPECT_STR_EQ(one, two, "render report deterministic");
    return 0;
}

static int l_ui_rendering_report_rejects_small_buffer(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char tiny[8];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "small buffer render builds");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    return 0;
}

static int l_ui_rendering_rejects_unsupported_mode(void) {
    latticra_l_ui_render_request_t request;
    latticra_l_ui_render_result_t render;
    request.mode = (latticra_l_ui_render_mode_t)99;
    request.ast = 0;
    request.semantic = 0;
    request.lir = 0;
    request.authority = 0;
    EXPECT_TRUE(latticra_l_ui_render(&request, &render) == LATTICRA_STATUS_OK, "unsupported mode returns status ok");
    EXPECT_TRUE(render.error == LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE, "unsupported mode rejected");
    return 0;
}

static int l_ui_rendering_does_not_change_ast_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char before[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    char after[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "ast report render builds");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, before, sizeof(before)) == LATTICRA_STATUS_OK, "before AST report builds");
    EXPECT_TRUE(latticra_l_ui_render(&((latticra_l_ui_render_request_t){ LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority }), &render) == LATTICRA_STATUS_OK, "render reruns");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, after, sizeof(after)) == LATTICRA_STATUS_OK, "after AST report builds");
    EXPECT_STR_EQ(after, before, "render does not mutate AST report");
    return 0;
}

static int l_ui_rendering_does_not_change_lir_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char before[LATTICRA_LIR_REPORT_MAX];
    char after[LATTICRA_LIR_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "lir report render builds");
    EXPECT_TRUE(latticra_lir_report(&lir, before, sizeof(before)) == LATTICRA_STATUS_OK, "before LIR report builds");
    EXPECT_TRUE(latticra_l_ui_render(&((latticra_l_ui_render_request_t){ LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority }), &render) == LATTICRA_STATUS_OK, "render reruns");
    EXPECT_TRUE(latticra_lir_report(&lir, after, sizeof(after)) == LATTICRA_STATUS_OK, "after LIR report builds");
    EXPECT_STR_EQ(after, before, "render does not mutate LIR report");
    return 0;
}

static int l_ui_rendering_does_not_execute_bindings(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_L_UI_RENDER_REPORT_MAX];
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_DETAILED, &ast, &semantic, &lir, &authority, &render) == 0, "binding render builds");
    EXPECT_TRUE(latticra_l_ui_render_report(&render, report, sizeof(report)) == LATTICRA_STATUS_OK, "binding report builds");
    EXPECT_TRUE(strstr(report, "binding[0].target=state.origin\n") != 0, "binding remains symbolic");
    EXPECT_TRUE(strstr(report, "origin=") == 0, "binding not evaluated as host state");
    return 0;
}

static int l_ui_rendering_does_not_call_nucleus_execution(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &render) == 0, "nucleus render builds");
    EXPECT_TRUE(render.execution_allowed == 0, "render does not allow execution");
    EXPECT_TRUE(render.mutation_allowed == 0, "render does not allow mutation");
    return 0;
}

static int l_ui_rendering_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t lir;
    latticra_l_ui_render_authority_summary_t authority;
    latticra_l_ui_render_result_t one;
    latticra_l_ui_render_result_t two;
    latticra_l_ui_render_request_t request;
    EXPECT_TRUE(build_render_from_source(VALID_SOURCE, LATTICRA_L_UI_RENDER_MODE_SUMMARY, &ast, &semantic, &lir, &authority, &one) == 0, "deterministic base builds");
    request.mode = LATTICRA_L_UI_RENDER_MODE_SUMMARY;
    request.ast = &ast;
    request.semantic = &semantic;
    request.lir = &lir;
    request.authority = &authority;
    EXPECT_TRUE(latticra_l_ui_render(&request, &two) == LATTICRA_STATUS_OK, "second deterministic render builds");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.rail_count == two.rail_count, "deterministic rail count");
    EXPECT_STR_EQ(one.card_name, two.card_name, "deterministic card name");
    return 0;
}

int main(void) {
    if (l_ui_rendering_accepts_semantically_valid_l_ui_fixture() != 0) return 1;
    if (l_ui_rendering_requires_semantic_success() != 0) return 1;
    if (l_ui_rendering_requires_lir_success() != 0) return 1;
    if (l_ui_rendering_requires_authority_success() != 0) return 1;
    if (l_ui_rendering_rejects_non_no_effect_flags() != 0) return 1;
    if (l_ui_rendering_preserves_card_metadata() != 0) return 1;
    if (l_ui_rendering_preserves_rail_order() != 0) return 1;
    if (l_ui_rendering_preserves_field_bindings() != 0) return 1;
    if (l_ui_rendering_preserves_text_lengths() != 0) return 1;
    if (l_ui_rendering_preserves_escaped_x00_visibility() != 0) return 1;
    if (l_ui_rendering_preserves_source_spans() != 0) return 1;
    if (l_ui_rendering_preserves_no_effect_flags() != 0) return 1;
    if (l_ui_rendering_report_is_deterministic() != 0) return 1;
    if (l_ui_rendering_report_rejects_small_buffer() != 0) return 1;
    if (l_ui_rendering_rejects_unsupported_mode() != 0) return 1;
    if (l_ui_rendering_does_not_change_ast_report() != 0) return 1;
    if (l_ui_rendering_does_not_change_lir_report() != 0) return 1;
    if (l_ui_rendering_does_not_execute_bindings() != 0) return 1;
    if (l_ui_rendering_does_not_call_nucleus_execution() != 0) return 1;
    if (l_ui_rendering_is_deterministic() != 0) return 1;

    puts("l_ui_rendering_invariants: ok");
    return 0;
}
