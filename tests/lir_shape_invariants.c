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
    "  purpose \"lir shape fixture\"\n"
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
    "    field network bind preview.network_allowed\n"
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"bottom lir text\" }\n"
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

static int append_bytes(char *buffer, size_t buffer_len, size_t *used, const char *bytes, size_t bytes_len) {
    if (buffer == 0 || used == 0 || bytes == 0 || *used > buffer_len || bytes_len > buffer_len - *used) return 0;
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
    if (source_len != 0) *source_len = used;
    return 1;
}

static int lower_valid(latticra_l_ui_ast_result_t *ast, latticra_l_ui_semantic_result_t *semantic, latticra_lir_module_t *module) {
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), ast) == LATTICRA_STATUS_OK, "valid AST parse status");
    EXPECT_TRUE(ast->parse_result.error == LATTICRA_L_UI_PARSE_OK, "valid AST parse OK");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(ast, semantic) == LATTICRA_STATUS_OK, "valid semantic status");
    EXPECT_TRUE(semantic->error == LATTICRA_L_UI_SEMANTIC_OK, "valid semantic OK");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(ast, semantic, module) == LATTICRA_STATUS_OK, "valid LIR lower status");
    return 0;
}

static int lir_shape_accepts_semantically_valid_l_ui_fixture(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char report[LATTICRA_LIR_REPORT_MAX];
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "valid LIR lowers");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "valid LIR OK");
    EXPECT_TRUE(module.source_kind == LATTICRA_LIR_SOURCE_L_UI_CARD, "valid source kind");
    EXPECT_TRUE(module.node_count == 63u, "valid node count");
    EXPECT_TRUE(module.edge_count >= 62u, "valid edge count minimum");
    EXPECT_TRUE(module.binding_count == 24u, "valid binding count");
    EXPECT_TRUE(module.text_count == 2u, "valid text count");
    EXPECT_TRUE(latticra_lir_report(&module, report, sizeof(report)) == LATTICRA_STATUS_OK, "valid LIR report builds");
    EXPECT_TRUE(strstr(report, "LATTICRA LIR REPORT\n") != 0, "LIR report header");
    EXPECT_TRUE(strstr(report, "error=ok\n") != 0, "LIR report OK");
    return 0;
}

static int lir_shape_rejects_parser_failed_ast(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "parser failed AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "parser failed AST error");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "parser failed semantic status");
    EXPECT_TRUE(semantic.error == LATTICRA_L_UI_SEMANTIC_PARSER_FAILED, "parser failed semantic error");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "parser failed LIR lower status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_SEMANTIC_FAILED, "parser failed LIR semantic failed");
    EXPECT_TRUE(module.node_count == 0u && module.edge_count == 0u, "parser failed LIR no partial graph");
    return 0;
}

static int lir_shape_rejects_semantic_failed_ast(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), &ast) == LATTICRA_STATUS_OK, "semantic failed AST parse status");
    ast.card.field_count = 23u;
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "semantic failed validation status");
    EXPECT_TRUE(semantic.error != LATTICRA_L_UI_SEMANTIC_OK, "semantic failure detected");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "semantic failed LIR lower status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_SEMANTIC_FAILED, "semantic failed LIR error");
    EXPECT_TRUE(module.node_count == 0u && module.binding_count == 0u && module.text_count == 0u, "semantic failed no partial LIR");
    return 0;
}

static int lir_shape_preserves_card_metadata(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "card metadata lower");
    EXPECT_STR_EQ(module.module_name, "l_ui_card_module", "module name");
    EXPECT_STR_EQ(module.card_name, "NucleusPreview", "card name");
    EXPECT_STR_EQ(module.effect, "none", "effect metadata");
    EXPECT_STR_EQ(module.boundary, "preview_only", "boundary metadata");
    EXPECT_TRUE(module.source_span.start_offset == ast.card.span.start_offset, "module span start");
    EXPECT_TRUE(module.source_span.end_offset == ast.card.span.end_offset, "module span end");
    return 0;
}

static int lir_shape_preserves_rail_nodes(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "rail nodes lower");
    EXPECT_TRUE(module.nodes[0].kind == LATTICRA_LIR_NODE_MODULE, "module node kind");
    EXPECT_TRUE(module.nodes[1].kind == LATTICRA_LIR_NODE_CARD, "card node kind");
    EXPECT_TRUE(module.nodes[2].kind == LATTICRA_LIR_NODE_RAIL, "first rail kind");
    EXPECT_STR_EQ(module.nodes[2].name, "top", "first rail name");
    EXPECT_TRUE(module.nodes[10].kind == LATTICRA_LIR_NODE_RAIL, "last rail kind");
    EXPECT_STR_EQ(module.nodes[10].name, "bottom", "last rail name");
    return 0;
}

static int lir_shape_preserves_field_nodes(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "field nodes lower");
    EXPECT_TRUE(module.nodes[11].kind == LATTICRA_LIR_NODE_FIELD, "first field kind");
    EXPECT_STR_EQ(module.nodes[11].name, "origin", "first field name");
    EXPECT_STR_EQ(module.nodes[11].binding, "state.origin", "first field binding");
    EXPECT_TRUE(module.nodes[32].kind == LATTICRA_LIR_NODE_FIELD, "network field kind");
    EXPECT_STR_EQ(module.nodes[32].name, "network", "network field name");
    EXPECT_STR_EQ(module.nodes[32].binding, "preview.network_allowed", "network field binding");
    EXPECT_TRUE(module.nodes[34].kind == LATTICRA_LIR_NODE_FIELD, "last field kind");
    EXPECT_STR_EQ(module.nodes[34].name, "hardware", "last field name");
    return 0;
}

static int lir_shape_preserves_binding_nodes(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "binding nodes lower");
    EXPECT_TRUE(module.nodes[37].kind == LATTICRA_LIR_NODE_BINDING, "first binding node kind");
    EXPECT_STR_EQ(module.nodes[37].binding, "state.origin", "first binding node target");
    EXPECT_TRUE(module.bindings[0].field_node_index == 11u, "first binding field index");
    EXPECT_STR_EQ(module.bindings[0].binding_prefix, "state", "first binding prefix");
    EXPECT_TRUE(module.bindings[0].resolved_kind == LATTICRA_LIR_BINDING_STATE_VALUE, "first binding resolved kind");
    EXPECT_TRUE(module.bindings[14].resolved_kind == LATTICRA_LIR_BINDING_PREVIEW_VALUE, "preview binding resolved kind");
    EXPECT_STR_EQ(module.bindings[21].binding_target, "preview.network_allowed", "network binding target");
    EXPECT_TRUE(module.bindings[21].field_node_index == 32u, "network binding field index");
    return 0;
}

static int lir_shape_preserves_text_nodes_with_lengths(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), "A\\x00B", strlen("A\\x00B"), "top\\x00text", strlen("top\\x00text"), "bottom", strlen("bottom"), &source_len), "escaped text source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "escaped text AST status");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "escaped text semantic status");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "escaped text LIR lower status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "escaped text LIR OK");
    EXPECT_TRUE(module.nodes[35].kind == LATTICRA_LIR_NODE_TEXT, "first text node kind");
    EXPECT_TRUE(module.texts[0].text_node_index == 35u, "first text node index");
    EXPECT_TRUE(module.texts[0].value_len == ast.texts[0].value_len, "first text length preserved");
    EXPECT_TRUE(strstr(module.texts[0].escaped_value, "\\x00") != 0, "escaped text preserves NUL representation");
    return 0;
}

static int lir_shape_preserves_source_spans(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "span lower");
    EXPECT_TRUE(module.nodes[1].source_span.start_offset == ast.card.span.start_offset, "card span start");
    EXPECT_TRUE(module.nodes[2].source_span.start_offset == ast.rails[0].span.start_offset, "rail span start");
    EXPECT_TRUE(module.nodes[11].source_span.start_offset == ast.fields[0].span.start_offset, "field span start");
    EXPECT_TRUE(module.nodes[37].source_span.start_offset == ast.fields[0].binding_span.start_offset, "binding span start");
    EXPECT_TRUE(module.nodes[35].source_span.start_offset == ast.texts[0].span.start_offset, "text span start");
    return 0;
}

static int lir_shape_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "flags lower");
    EXPECT_TRUE(module.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(module.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(module.mutation_allowed == 0, "mutation denied");
    EXPECT_TRUE(module.server_allowed == 0, "server denied");
    EXPECT_TRUE(module.network_allowed == 0, "network denied");
    EXPECT_TRUE(module.recovery_allowed == 0, "recovery denied");
    EXPECT_TRUE(module.hardware_allowed == 0, "hardware denied");
    return 0;
}

static int lir_shape_rejects_semantic_network_flag(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), &ast) == LATTICRA_STATUS_OK, "network LIR AST parse status");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "network LIR semantic status");
    semantic.network_allowed = 1;
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "network LIR lower status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_SEMANTIC_FAILED, "network LIR semantic failed");
    EXPECT_TRUE(module.network_allowed == 0, "rejected LIR keeps network denied");
    return 0;
}

static int lir_shape_report_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char one[LATTICRA_LIR_REPORT_MAX];
    char two[LATTICRA_LIR_REPORT_MAX];
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "report deterministic lower");
    EXPECT_TRUE(latticra_lir_report(&module, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report builds");
    EXPECT_TRUE(latticra_lir_report(&module, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report builds");
    EXPECT_STR_EQ(one, two, "LIR report deterministic");
    return 0;
}

static int lir_shape_report_rejects_small_buffer(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char tiny[8];
    EXPECT_TRUE(lower_valid(&ast, &semantic, &module) == 0, "small report lower");
    EXPECT_TRUE(latticra_lir_report(&module, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small LIR report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small LIR report clears buffer");
    return 0;
}

static int lir_shape_does_not_change_ast_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char before[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    char after[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), &ast) == LATTICRA_STATUS_OK, "ast report base parses");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, before, sizeof(before)) == LATTICRA_STATUS_OK, "before AST report builds");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "ast report semantic validates");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "ast report LIR lowers");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, after, sizeof(after)) == LATTICRA_STATUS_OK, "after AST report builds");
    EXPECT_STR_EQ(after, before, "LIR does not mutate AST report");
    return 0;
}

static int lir_shape_does_not_change_semantic_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    char before[LATTICRA_L_UI_SEMANTIC_REPORT_MAX];
    char after[LATTICRA_L_UI_SEMANTIC_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), &ast) == LATTICRA_STATUS_OK, "semantic report base parses");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "semantic report validates");
    EXPECT_TRUE(latticra_l_ui_semantic_report(&semantic, before, sizeof(before)) == LATTICRA_STATUS_OK, "before semantic report builds");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "semantic report LIR lowers");
    EXPECT_TRUE(latticra_l_ui_semantic_report(&semantic, after, sizeof(after)) == LATTICRA_STATUS_OK, "after semantic report builds");
    EXPECT_STR_EQ(after, before, "LIR does not mutate semantic report");
    return 0;
}

static int lir_shape_does_not_change_escaped_x00_acceptance(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), "A\\x00B", strlen("A\\x00B"), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "escaped x00 source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "escaped x00 AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "escaped x00 still accepted");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "escaped x00 semantic status");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "escaped x00 LIR status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "escaped x00 LIR OK");
    return 0;
}

static int lir_shape_does_not_change_literal_nul_rejection(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t module;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), purpose, sizeof(purpose), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "literal NUL source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL still rejected");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "literal NUL semantic status");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &module) == LATTICRA_STATUS_OK, "literal NUL LIR status");
    EXPECT_TRUE(module.error == LATTICRA_LIR_SEMANTIC_FAILED, "literal NUL no LIR materialization");
    return 0;
}

static int lir_shape_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_OK), "ok", "LIR OK label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_NULL_ARGUMENT), "null_argument", "LIR null label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_SEMANTIC_FAILED), "semantic_failed", "LIR semantic failed label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_CAPACITY_EXCEEDED), "capacity_exceeded", "LIR capacity label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND), "unsupported_source_kind", "LIR source label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_UNSUPPORTED_NODE_KIND), "unsupported_node_kind", "LIR node label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_UNSUPPORTED_EFFECT), "unsupported_effect", "LIR effect label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_UNSUPPORTED_BOUNDARY), "unsupported_boundary", "LIR boundary label");
    EXPECT_STR_EQ(latticra_lir_error_label(LATTICRA_LIR_INTERNAL_ERROR), "internal_error", "LIR internal label");
    return 0;
}

static int lir_shape_kind_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lir_source_kind_label(LATTICRA_LIR_SOURCE_L_UI_CARD), "l_ui_card", "source kind label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_MODULE), "module", "module kind label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_BINDING), "binding", "binding kind label");
    EXPECT_STR_EQ(latticra_lir_edge_kind_label(LATTICRA_LIR_EDGE_CONTAINS), "contains", "contains label");
    EXPECT_STR_EQ(latticra_lir_edge_kind_label(LATTICRA_LIR_EDGE_ORDERS_BEFORE), "orders_before", "orders_before label");
    EXPECT_STR_EQ(latticra_lir_resolved_binding_kind_label(LATTICRA_LIR_BINDING_STATE_VALUE), "state_value", "state binding label");
    EXPECT_STR_EQ(latticra_lir_resolved_binding_kind_label(LATTICRA_LIR_BINDING_PREVIEW_VALUE), "preview_value", "preview binding label");
    EXPECT_STR_EQ(latticra_lir_resolved_binding_kind_label(LATTICRA_LIR_BINDING_UNSUPPORTED), "unsupported", "unsupported binding label");
    return 0;
}

static int lir_shape_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t semantic;
    latticra_lir_module_t one;
    latticra_lir_module_t two;
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), &ast) == LATTICRA_STATUS_OK, "deterministic base parses");
    EXPECT_TRUE(latticra_l_ui_validate_semantics(&ast, &semantic) == LATTICRA_STATUS_OK, "deterministic semantic validates");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &one) == LATTICRA_STATUS_OK, "first LIR lower");
    EXPECT_TRUE(latticra_lir_lower_l_ui_ast(&ast, &semantic, &two) == LATTICRA_STATUS_OK, "second LIR lower");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.node_count == two.node_count, "deterministic node count");
    EXPECT_TRUE(one.edge_count == two.edge_count, "deterministic edge count");
    EXPECT_TRUE(one.binding_count == two.binding_count, "deterministic binding count");
    EXPECT_TRUE(one.text_count == two.text_count, "deterministic text count");
    EXPECT_STR_EQ(one.card_name, two.card_name, "deterministic card");
    return 0;
}

int main(void) {
    if (lir_shape_accepts_semantically_valid_l_ui_fixture() != 0) return 1;
    if (lir_shape_rejects_parser_failed_ast() != 0) return 1;
    if (lir_shape_rejects_semantic_failed_ast() != 0) return 1;
    if (lir_shape_preserves_card_metadata() != 0) return 1;
    if (lir_shape_preserves_rail_nodes() != 0) return 1;
    if (lir_shape_preserves_field_nodes() != 0) return 1;
    if (lir_shape_preserves_binding_nodes() != 0) return 1;
    if (lir_shape_preserves_text_nodes_with_lengths() != 0) return 1;
    if (lir_shape_preserves_source_spans() != 0) return 1;
    if (lir_shape_preserves_no_effect_flags() != 0) return 1;
    if (lir_shape_rejects_semantic_network_flag() != 0) return 1;
    if (lir_shape_report_is_deterministic() != 0) return 1;
    if (lir_shape_report_rejects_small_buffer() != 0) return 1;
    if (lir_shape_does_not_change_ast_report() != 0) return 1;
    if (lir_shape_does_not_change_semantic_report() != 0) return 1;
    if (lir_shape_does_not_change_escaped_x00_acceptance() != 0) return 1;
    if (lir_shape_does_not_change_literal_nul_rejection() != 0) return 1;
    if (lir_shape_error_labels_are_stable() != 0) return 1;
    if (lir_shape_kind_labels_are_stable() != 0) return 1;
    if (lir_shape_is_deterministic() != 0) return 1;

    puts("lir_shape_invariants: ok");
    return 0;
}
