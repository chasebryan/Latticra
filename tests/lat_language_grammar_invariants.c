#include "latticra/lat_parser.h"

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

static const char MINIMAL_MODULE[] =
    "lat module RootModule {\n"
    "  state RootCell {\n"
    "    origin = \"0/0\"\n"
    "    route = \"ROOT\"\n"
    "    axis = \"ROOT\"\n"
    "    path = \"/\"\n"
    "    host_effect = none\n"
    "    external_effect = none\n"
    "  }\n"
    "}\n";

static int parse_source(const char *source, size_t source_len, latticra_lat_parse_result_t *result) {
    EXPECT_TRUE(latticra_lat_parse_source(source, source_len, result) == LATTICRA_STATUS_OK, "Lat parse status OK");
    return 0;
}

static int lat_grammar_accepts_minimal_module(void) {
    latticra_lat_parse_result_t result;
    char report[LATTICRA_LAT_REPORT_MAX];
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "minimal module parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "minimal module parse OK");
    EXPECT_STR_EQ(result.module.module_name, "RootModule", "minimal module name");
    EXPECT_TRUE(result.declaration_count == 1u, "minimal declaration count");
    EXPECT_TRUE(result.module.state_count == 1u, "minimal state count");
    EXPECT_TRUE(result.clause_count == 6u, "minimal clause count");
    EXPECT_TRUE(latticra_lat_parse_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "minimal report builds");
    EXPECT_TRUE(strstr(report, "LAT GRAMMAR REPORT\n") != 0, "minimal report header");
    EXPECT_TRUE(strstr(report, "error=ok\n") != 0, "minimal report OK");
    EXPECT_TRUE(strstr(report, "first_declaration_index=0\n") != 0, "minimal first declaration index report");
    EXPECT_TRUE(strstr(report, "first_declaration_kind=state\n") != 0, "minimal first declaration kind report");
    EXPECT_TRUE(strstr(report, "first_declaration_name=RootCell\n") != 0, "minimal first declaration name report");
    EXPECT_TRUE(strstr(report, "first_declaration_first_clause_index=0\n") != 0, "minimal first declaration first clause report");
    EXPECT_TRUE(strstr(report, "first_declaration_clause_count=6\n") != 0, "minimal first declaration clause count report");
    EXPECT_TRUE(strstr(report, "first_clause_index=0\n") != 0, "minimal first clause index report");
    EXPECT_TRUE(strstr(report, "first_clause_keyword=field\n") != 0, "minimal first clause keyword report");
    EXPECT_TRUE(strstr(report, "first_clause_left=origin\n") != 0, "minimal first clause left report");
    EXPECT_TRUE(strstr(report, "first_clause_operator==\n") != 0, "minimal first clause operator report");
    EXPECT_TRUE(strstr(report, "first_clause_right=0/0\n") != 0, "minimal first clause right report");
    EXPECT_TRUE(strstr(report, "first_clause_effect=unknown\n") != 0, "minimal first clause effect report");
    return 0;
}

static int lat_grammar_accepts_state_declaration(void) {
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "state declaration parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "state declaration OK");
    EXPECT_TRUE(result.declarations[0].kind == LATTICRA_LAT_DECLARATION_STATE, "state declaration kind");
    EXPECT_STR_EQ(result.declarations[0].name, "RootCell", "state declaration name");
    EXPECT_STR_EQ(result.clauses[0].keyword, "field", "state clause keyword");
    EXPECT_STR_EQ(result.clauses[0].left, "origin", "state first field left");
    EXPECT_STR_EQ(result.clauses[0].right, "0/0", "state first field right");
    return 0;
}

static int lat_grammar_accepts_policy_declaration(void) {
    static const char source[] =
        "lat module PolicyModule {\n"
        "  policy SafePreview {\n"
        "    require risk != \"high\"\n"
        "    require lock == \"open\"\n"
        "    ensure host_effect == none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "policy declaration parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "policy declaration OK");
    EXPECT_TRUE(result.module.policy_count == 1u, "policy count");
    EXPECT_TRUE(result.declarations[0].kind == LATTICRA_LAT_DECLARATION_POLICY, "policy kind");
    EXPECT_STR_EQ(result.clauses[0].keyword, "require", "policy first clause keyword");
    EXPECT_STR_EQ(result.clauses[2].keyword, "ensure", "policy ensure keyword");
    return 0;
}

static int lat_grammar_accepts_transition_declaration(void) {
    static const char source[] =
        "lat module TransitionModule {\n"
        "  transition MoveRight from RootCell {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "    effect external = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "transition declaration parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "transition declaration OK");
    EXPECT_TRUE(result.module.transition_count == 1u, "transition count");
    EXPECT_TRUE(result.declarations[0].kind == LATTICRA_LAT_DECLARATION_TRANSITION, "transition kind");
    EXPECT_STR_EQ(result.declarations[0].name, "MoveRight", "transition name");
    EXPECT_STR_EQ(result.declarations[0].source_name, "RootCell", "transition source state");
    EXPECT_TRUE(result.clauses[1].effect == LATTICRA_LAT_EFFECT_NONE, "transition effect metadata");
    return 0;
}

static int lat_grammar_accepts_assertion_declaration(void) {
    static const char source[] =
        "lat module AssertionModule {\n"
        "  assertion RootCellIsSafe {\n"
        "    require health == \"ok\"\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "assertion declaration parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "assertion declaration OK");
    EXPECT_TRUE(result.module.assertion_count == 1u, "assertion count");
    EXPECT_TRUE(result.declarations[0].kind == LATTICRA_LAT_DECLARATION_ASSERTION, "assertion kind");
    EXPECT_STR_EQ(result.declarations[0].name, "RootCellIsSafe", "assertion name");
    return 0;
}

static int lat_grammar_accepts_effect_declaration(void) {
    static const char source[] =
        "lat module EffectModule {\n"
        "  effect PreviewOnly {\n"
        "    host = none\n"
        "    external = none\n"
        "    network = none\n"
        "    hardware = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "effect declaration parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "effect declaration OK");
    EXPECT_TRUE(result.module.effect_count == 1u, "effect count");
    EXPECT_TRUE(result.declarations[0].kind == LATTICRA_LAT_DECLARATION_EFFECT, "effect declaration kind");
    EXPECT_TRUE(result.clauses[0].effect == LATTICRA_LAT_EFFECT_NONE, "effect clause metadata");
    return 0;
}

static int lat_grammar_accepts_line_comments(void) {
    static const char source[] =
        "// exec spawn socket are inert in comments\n"
        "lat module CommentModule { // module opener\n"
        "  // state declaration lead-in\n"
        "  state RootCell {\n"
        "    origin = \"0/0\" // first field comment\n"
        "    route = \"//not-comment\"\n"
        "    // before declaration close\n"
        "  }\n"
        "  // before module close\n"
        "}\n";
    latticra_lat_parse_result_t result;
    char report[LATTICRA_LAT_REPORT_MAX];

    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "commented source parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "commented source OK");
    EXPECT_STR_EQ(result.module.module_name, "CommentModule", "commented module name");
    EXPECT_TRUE(result.declaration_count == 1u, "commented declaration count");
    EXPECT_TRUE(result.clause_count == 2u, "commented clause count");
    EXPECT_TRUE(result.comment_count == 6u, "comment count");
    EXPECT_TRUE(result.first_comment_span.start_line == 1u, "first comment start line");
    EXPECT_TRUE(result.first_comment_span.start_column == 1u, "first comment start column");
    EXPECT_TRUE(result.first_comment_span.end_column > result.first_comment_span.start_column, "first comment width");
    EXPECT_STR_EQ(result.clauses[1].right, "//not-comment", "string slash slash preserved");
    EXPECT_TRUE(result.no_effect == 1, "comments preserve no-effect");
    EXPECT_TRUE(result.execution_allowed == 0, "comments do not allow execution");

    EXPECT_TRUE(latticra_lat_parse_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "comment report builds");
    EXPECT_TRUE(strstr(report, "comment_count=6\n") != 0, "comment count report");
    EXPECT_TRUE(strstr(report, "first_comment_start_line=1\n") != 0, "comment start line report");
    EXPECT_TRUE(strstr(report, "first_comment_start_column=1\n") != 0, "comment start column report");
    EXPECT_TRUE(strstr(report, "first_clause_right=0/0\n") != 0, "first clause remains stable");
    return 0;
}

static int lat_grammar_rejects_block_comments(void) {
    static const char source[] =
        "// line comment before unsupported block\n"
        "lat module BadBlock {\n"
        "  /* block comments are not accepted in Lat-Core */\n"
        "  state RootCell {\n"
        "    origin = \"0/0\"\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;
    char report[LATTICRA_LAT_REPORT_MAX];

    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "block comment source parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT, "block comment rejected");
    EXPECT_TRUE(result.comment_count == 1u, "line comment before block counted");
    EXPECT_TRUE(result.span.start_line == 3u, "block comment error line");
    EXPECT_TRUE(result.execution_allowed == 0, "block comments do not allow execution");
    EXPECT_TRUE(result.no_effect == 1, "block comments preserve no-effect");

    EXPECT_TRUE(latticra_lat_parse_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "block comment report builds");
    EXPECT_TRUE(strstr(report, "error=unsupported_block_comment\n") != 0, "block comment error report");
    EXPECT_TRUE(strstr(report, "comment_count=1\n") != 0, "block comment line comment count report");
    return 0;
}

static int lat_grammar_preserves_block_comment_markers_in_strings(void) {
    static const char source[] =
        "lat module StringBlockMarker {\n"
        "  state RootCell {\n"
        "    route = \"/*not-comment*/\"\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t result;

    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "string block marker source parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "string block marker OK");
    EXPECT_STR_EQ(result.clauses[0].right, "/*not-comment*/", "block marker string preserved");
    EXPECT_TRUE(result.comment_count == 0u, "string block marker not counted as comment");
    return 0;
}

static int lat_grammar_rejects_plain_l_extension_claim(void) {
    static const char source[] = "l module RootModule { }\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "plain l source parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM, "plain l rejected");
    return 0;
}

static int lat_grammar_rejects_unknown_keyword(void) {
    static const char source[] = "lat module RootModule { unknown Thing { } }\n";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "unknown keyword parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION, "unknown declaration rejected");
    return 0;
}

static int lat_grammar_rejects_unterminated_string(void) {
    static const char source[] = "lat module RootModule { state RootCell { origin = \"abc } }";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "unterminated string parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_UNTERMINATED_STRING, "unterminated string rejected");
    return 0;
}

static int lat_grammar_rejects_invalid_escape(void) {
    static const char source[] = "lat module RootModule { state RootCell { origin = \"a\\q\" } }";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "invalid escape parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE, "invalid escape rejected");
    return 0;
}

static int lat_grammar_rejects_literal_source_nul(void) {
    static const char source[] = { 'l', 'a', 't', ' ', 'm', 'o', 'd', 'u', 'l', 'e', ' ', 'R', '\0', ' ', '{', '}', '\n' };
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, sizeof(source), &result) == 0, "literal NUL parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING, "literal NUL rejected");
    return 0;
}

static int lat_grammar_reports_source_spans(void) {
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "span source parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "span source OK");
    EXPECT_TRUE(result.span.end_offset > result.span.start_offset, "module span offsets");
    EXPECT_TRUE(result.declarations[0].span.end_offset > result.declarations[0].span.start_offset, "declaration span offsets");
    EXPECT_TRUE(result.clauses[0].span.end_offset > result.clauses[0].span.start_offset, "clause span offsets");
    EXPECT_TRUE(result.span.start_line >= 1u, "module span line");
    return 0;
}

static int lat_grammar_preserves_no_effect_flags(void) {
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "no-effect source parses");
    EXPECT_TRUE(result.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(result.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation denied");
    EXPECT_TRUE(result.server_allowed == 0, "server denied");
    EXPECT_TRUE(result.network_allowed == 0, "network denied");
    EXPECT_TRUE(result.recovery_allowed == 0, "recovery denied");
    EXPECT_TRUE(result.hardware_allowed == 0, "hardware denied");
    return 0;
}

static int lat_grammar_report_is_deterministic(void) {
    latticra_lat_parse_result_t result;
    char one[LATTICRA_LAT_REPORT_MAX];
    char two[LATTICRA_LAT_REPORT_MAX];
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "report source parses");
    EXPECT_TRUE(latticra_lat_parse_report(&result, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report builds");
    EXPECT_TRUE(latticra_lat_parse_report(&result, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report builds");
    EXPECT_STR_EQ(one, two, "report deterministic");
    EXPECT_TRUE(strstr(one, "network_allowed=0\n") != 0, "report network denied");
    return 0;
}

static int lat_grammar_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t result;
    char tiny[8];
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "small report source parses");
    EXPECT_TRUE(latticra_lat_parse_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small report clears buffer");
    return 0;
}

static int lat_grammar_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_OK), "ok", "ok label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_NULL_ARGUMENT), "null_argument", "null label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_EMPTY_SOURCE), "empty_source", "empty label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE), "source_too_large", "large label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM), "unsupported_extension_claim", "extension label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_MISSING_MODULE), "missing_module", "module label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE), "invalid_string_escape", "escape label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING), "literal_nul_in_string", "nul label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT), "unsupported_block_comment", "block comment label");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_INTERNAL_ERROR), "internal_error", "internal label");
    return 0;
}

static int lat_grammar_kind_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_declaration_kind_label(LATTICRA_LAT_DECLARATION_STATE), "state", "state kind label");
    EXPECT_STR_EQ(latticra_lat_declaration_kind_label(LATTICRA_LAT_DECLARATION_POLICY), "policy", "policy kind label");
    EXPECT_STR_EQ(latticra_lat_declaration_kind_label(LATTICRA_LAT_DECLARATION_TRANSITION), "transition", "transition kind label");
    EXPECT_STR_EQ(latticra_lat_declaration_kind_label(LATTICRA_LAT_DECLARATION_ASSERTION), "assertion", "assertion kind label");
    EXPECT_STR_EQ(latticra_lat_declaration_kind_label(LATTICRA_LAT_DECLARATION_EFFECT), "effect", "effect kind label");
    EXPECT_STR_EQ(latticra_lat_effect_label(LATTICRA_LAT_EFFECT_NONE), "none", "none effect label");
    EXPECT_STR_EQ(latticra_lat_effect_label(LATTICRA_LAT_EFFECT_NETWORK), "network", "network effect label");
    EXPECT_STR_EQ(latticra_lat_effect_label(LATTICRA_LAT_EFFECT_EXTERNAL), "external", "external effect label");
    return 0;
}

static int lat_grammar_does_not_lower_to_lir(void) {
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &result) == 0, "no LIR source parses");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_OK, "no LIR parse OK");
    EXPECT_TRUE(result.no_effect == 1, "no LIR no_effect");
    EXPECT_TRUE(result.declaration_count == 1u, "no LIR only Lat AST metadata");
    return 0;
}

static int lat_grammar_does_not_execute_declarations(void) {
    static const char source[] = "lat module Bad { state S { exec = none } }";
    latticra_lat_parse_result_t result;
    EXPECT_TRUE(parse_source(source, strlen(source), &result) == 0, "execution marker parses to error");
    EXPECT_TRUE(result.error == LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER, "execution marker rejected");
    EXPECT_TRUE(result.execution_allowed == 0, "execution remains denied");
    return 0;
}

static int lat_grammar_is_deterministic(void) {
    latticra_lat_parse_result_t one;
    latticra_lat_parse_result_t two;
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &one) == 0, "first deterministic parse");
    EXPECT_TRUE(parse_source(MINIMAL_MODULE, strlen(MINIMAL_MODULE), &two) == 0, "second deterministic parse");
    EXPECT_TRUE(one.error == two.error, "deterministic error");
    EXPECT_TRUE(one.declaration_count == two.declaration_count, "deterministic declarations");
    EXPECT_TRUE(one.clause_count == two.clause_count, "deterministic clauses");
    EXPECT_STR_EQ(one.module.module_name, two.module.module_name, "deterministic module name");
    EXPECT_TRUE(one.span.end_offset == two.span.end_offset, "deterministic span end");
    return 0;
}

int main(void) {
    if (lat_grammar_accepts_minimal_module() != 0) return 1;
    if (lat_grammar_accepts_state_declaration() != 0) return 1;
    if (lat_grammar_accepts_policy_declaration() != 0) return 1;
    if (lat_grammar_accepts_transition_declaration() != 0) return 1;
    if (lat_grammar_accepts_assertion_declaration() != 0) return 1;
    if (lat_grammar_accepts_effect_declaration() != 0) return 1;
    if (lat_grammar_accepts_line_comments() != 0) return 1;
    if (lat_grammar_rejects_block_comments() != 0) return 1;
    if (lat_grammar_preserves_block_comment_markers_in_strings() != 0) return 1;
    if (lat_grammar_rejects_plain_l_extension_claim() != 0) return 1;
    if (lat_grammar_rejects_unknown_keyword() != 0) return 1;
    if (lat_grammar_rejects_unterminated_string() != 0) return 1;
    if (lat_grammar_rejects_invalid_escape() != 0) return 1;
    if (lat_grammar_rejects_literal_source_nul() != 0) return 1;
    if (lat_grammar_reports_source_spans() != 0) return 1;
    if (lat_grammar_preserves_no_effect_flags() != 0) return 1;
    if (lat_grammar_report_is_deterministic() != 0) return 1;
    if (lat_grammar_report_rejects_small_buffer() != 0) return 1;
    if (lat_grammar_error_labels_are_stable() != 0) return 1;
    if (lat_grammar_kind_labels_are_stable() != 0) return 1;
    if (lat_grammar_does_not_lower_to_lir() != 0) return 1;
    if (lat_grammar_does_not_execute_declarations() != 0) return 1;
    if (lat_grammar_is_deterministic() != 0) return 1;

    puts("lat_language_grammar_invariants: ok");
    return 0;
}
