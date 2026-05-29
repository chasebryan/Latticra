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

static const char VALID_SOURCE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"semantic validation fixture\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"top semantic text\" }\n"
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
    "  rail bottom { text \"bottom semantic text\" }\n"
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

static int parse_valid_ast(latticra_l_ui_ast_result_t *ast) {
    EXPECT_TRUE(latticra_l_ui_parse_ast(VALID_SOURCE, strlen(VALID_SOURCE), ast) == LATTICRA_STATUS_OK, "valid AST parse status");
    EXPECT_TRUE(ast->parse_result.error == LATTICRA_L_UI_PARSE_OK, "valid AST parse OK");
    return 0;
}

static int validate_ast(const latticra_l_ui_ast_result_t *ast, latticra_l_ui_semantic_result_t *result) {
    EXPECT_TRUE(latticra_l_ui_validate_semantics(ast, result) == LATTICRA_STATUS_OK, "semantic validation status");
    return 0;
}

static int semantic_validation_accepts_current_fixture(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    char report[LATTICRA_L_UI_SEMANTIC_REPORT_MAX];
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "valid fixture parses");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "valid fixture validates");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_OK, "valid fixture semantic OK");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(result.error), "ok", "semantic OK label");
    EXPECT_TRUE(result.rail_count == 9u, "semantic rail count");
    EXPECT_TRUE(result.field_count == 24u, "semantic field count");
    EXPECT_TRUE(result.text_count == 2u, "semantic text count");
    EXPECT_TRUE(latticra_l_ui_semantic_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "semantic report status");
    EXPECT_TRUE(strstr(report, "L-UI SEMANTIC VALIDATION RESULT\n") != 0, "semantic report header");
    EXPECT_TRUE(strstr(report, "error=ok\n") != 0, "semantic report OK");
    return 0;
}

static int semantic_validation_rejects_duplicate_rail(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "duplicate rail base parses");
    snprintf(ast.rails[1].name, sizeof(ast.rails[1].name), "%s", "top");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "duplicate rail validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL, "duplicate rail error");
    EXPECT_STR_EQ(result.rail_name, "top", "duplicate rail name copied");
    return 0;
}

static int semantic_validation_rejects_missing_required_rail(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "missing rail base parses");
    snprintf(ast.rails[1].name, sizeof(ast.rails[1].name), "%s", "missing_state");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "missing rail validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL, "missing required rail error");
    return 0;
}

static int semantic_validation_rejects_duplicate_field(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "duplicate field base parses");
    snprintf(ast.fields[1].name, sizeof(ast.fields[1].name), "%s", "origin");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "duplicate field validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD, "duplicate field error");
    EXPECT_STR_EQ(result.field_name, "origin", "duplicate field name copied");
    return 0;
}

static int semantic_validation_rejects_field_rail_mismatch(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "field rail mismatch base parses");
    ast.rails[1].first_field_index = 1u;
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "field rail mismatch validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH, "field rail mismatch error");
    return 0;
}

static int semantic_validation_rejects_binding_field_mismatch(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "binding mismatch base parses");
    snprintf(ast.fields[0].binding, sizeof(ast.fields[0].binding), "%s", "state.route");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "binding mismatch validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH, "binding mismatch error");
    EXPECT_STR_EQ(result.binding, "state.route", "binding mismatch copied");
    return 0;
}

static int semantic_validation_rejects_unsupported_binding_target(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "unsupported binding base parses");
    snprintf(ast.fields[0].binding, sizeof(ast.fields[0].binding), "%s", "host.origin");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "unsupported binding validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET, "unsupported binding error");
    EXPECT_STR_EQ(result.binding, "host.origin", "unsupported binding copied");
    return 0;
}

static int semantic_validation_rejects_text_rail_mismatch(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "text mismatch base parses");
    ast.rails[0].text_count = 0u;
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "text mismatch validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH, "text rail mismatch error");
    return 0;
}

static int semantic_validation_rejects_card_count_mismatch(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "card mismatch base parses");
    ast.card.field_count = 23u;
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "card mismatch validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH, "card count mismatch error");
    return 0;
}

static int semantic_validation_skips_when_parser_failed(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parser AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "parser failed as expected");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "parser failed semantic result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_PARSER_FAILED, "parser failed semantic error");
    EXPECT_TRUE(result.parser_error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "parser error preserved");
    EXPECT_TRUE(result.rail_count == 0u && result.field_count == 0u && result.text_count == 0u, "parser failed counts zero");
    return 0;
}

static int semantic_validation_reports_source_spans(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "span base parses");
    snprintf(ast.fields[0].binding, sizeof(ast.fields[0].binding), "%s", "state.route");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "span semantic result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH, "span binding mismatch");
    EXPECT_TRUE(result.span.start_offset == ast.fields[0].binding_span.start_offset, "binding span start preserved");
    EXPECT_TRUE(result.span.end_offset == ast.fields[0].binding_span.end_offset, "binding span end preserved");
    return 0;
}

static int semantic_validation_preserves_no_effect_flags(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "flag base parses");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "flag semantic result");
    EXPECT_TRUE(result.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(result.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation denied");
    EXPECT_TRUE(result.server_allowed == 0, "server denied");
    EXPECT_TRUE(result.network_allowed == 0, "network denied");
    EXPECT_TRUE(result.recovery_allowed == 0, "recovery denied");
    EXPECT_TRUE(result.hardware_allowed == 0, "hardware denied");
    return 0;
}

static int semantic_validation_rejects_network_flag(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "network flag base parses");
    ast.network_allowed = 1;
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "network flag validates to error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH, "network flag rejected");
    return 0;
}

static int semantic_validation_does_not_change_ast_report(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    char before[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    char after[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "report base parses");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, before, sizeof(before)) == LATTICRA_STATUS_OK, "before report builds");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "report semantic result");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, after, sizeof(after)) == LATTICRA_STATUS_OK, "after report builds");
    EXPECT_STR_EQ(after, before, "semantic validation does not mutate AST report");
    return 0;
}

static int semantic_validation_does_not_change_escaped_x00_acceptance(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), "A\\x00B", strlen("A\\x00B"), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "escaped x00 source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "escaped x00 AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_OK, "escaped x00 parse OK");
    EXPECT_TRUE(ast.card.purpose_len == 3u, "escaped x00 purpose length");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "escaped x00 semantic result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_OK, "escaped x00 semantic OK");
    return 0;
}

static int semantic_validation_does_not_change_literal_nul_rejection(void) {
    char source[4096];
    static const char purpose[] = { 'A', '\0', 'B' };
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    EXPECT_TRUE(make_source_binary(source, sizeof(source), purpose, sizeof(purpose), "top", strlen("top"), "bottom", strlen("bottom"), &source_len), "literal NUL source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL still rejected");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "literal NUL semantic result");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_SEMANTIC_PARSER_FAILED, "literal NUL semantic parser failed");
    EXPECT_TRUE(result.parser_error == LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING, "literal NUL parser error preserved");
    return 0;
}

static int semantic_validation_is_deterministic(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t one;
    latticra_l_ui_semantic_result_t two;
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "determinism base parses");
    EXPECT_TRUE(validate_ast(&ast, &one) == 0, "first semantic result");
    EXPECT_TRUE(validate_ast(&ast, &two) == 0, "second semantic result");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.rail_count == two.rail_count, "deterministic rail count");
    EXPECT_TRUE(one.field_count == two.field_count, "deterministic field count");
    EXPECT_TRUE(one.text_count == two.text_count, "deterministic text count");
    EXPECT_TRUE(one.span.start_offset == two.span.start_offset, "deterministic span start");
    EXPECT_TRUE(one.span.end_offset == two.span.end_offset, "deterministic span end");
    return 0;
}

static int semantic_validation_report_rejects_small_buffer(void) {
    latticra_l_ui_ast_result_t ast;
    latticra_l_ui_semantic_result_t result;
    char tiny[8];
    EXPECT_TRUE(parse_valid_ast(&ast) == 0, "small report base parses");
    EXPECT_TRUE(validate_ast(&ast, &result) == 0, "small report semantic result");
    EXPECT_TRUE(latticra_l_ui_semantic_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small report clears buffer");
    return 0;
}

static int semantic_validation_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_OK), "ok", "ok label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_PARSER_FAILED), "parser_failed", "parser failed label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL), "duplicate_rail", "duplicate rail label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL), "missing_required_rail", "missing rail label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD), "duplicate_field", "duplicate field label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH), "field_rail_mismatch", "field rail mismatch label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH), "binding_field_mismatch", "binding mismatch label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET), "unsupported_binding_target", "unsupported binding label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH), "text_rail_mismatch", "text mismatch label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH), "card_count_mismatch", "card count label");
    EXPECT_STR_EQ(latticra_l_ui_semantic_error_label(LATTICRA_L_UI_SEMANTIC_INTERNAL_ERROR), "internal_error", "internal error label");
    return 0;
}

int main(void) {
    if (semantic_validation_accepts_current_fixture() != 0) return 1;
    if (semantic_validation_rejects_duplicate_rail() != 0) return 1;
    if (semantic_validation_rejects_missing_required_rail() != 0) return 1;
    if (semantic_validation_rejects_duplicate_field() != 0) return 1;
    if (semantic_validation_rejects_field_rail_mismatch() != 0) return 1;
    if (semantic_validation_rejects_binding_field_mismatch() != 0) return 1;
    if (semantic_validation_rejects_unsupported_binding_target() != 0) return 1;
    if (semantic_validation_rejects_text_rail_mismatch() != 0) return 1;
    if (semantic_validation_rejects_card_count_mismatch() != 0) return 1;
    if (semantic_validation_skips_when_parser_failed() != 0) return 1;
    if (semantic_validation_reports_source_spans() != 0) return 1;
    if (semantic_validation_preserves_no_effect_flags() != 0) return 1;
    if (semantic_validation_rejects_network_flag() != 0) return 1;
    if (semantic_validation_does_not_change_ast_report() != 0) return 1;
    if (semantic_validation_does_not_change_escaped_x00_acceptance() != 0) return 1;
    if (semantic_validation_does_not_change_literal_nul_rejection() != 0) return 1;
    if (semantic_validation_is_deterministic() != 0) return 1;
    if (semantic_validation_report_rejects_small_buffer() != 0) return 1;
    if (semantic_validation_error_labels_are_stable() != 0) return 1;

    puts("l_ui_semantic_validation_invariants: ok");
    return 0;
}
