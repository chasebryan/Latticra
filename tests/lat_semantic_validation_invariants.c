#include "latticra/lat_semantic.h"

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

static const char FOUNDATION_MODEL[] =
    "lat module FoundationModule {\n"
    "  state RootCell {\n"
    "    origin = \"0/0\"\n"
    "    route = \"ROOT\"\n"
    "    axis = \"ROOT\"\n"
    "    path = \"/\"\n"
    "    health = \"ok\"\n"
    "    risk = \"low\"\n"
    "    lock = \"open\"\n"
    "    host_effect = none\n"
    "    external_effect = none\n"
    "  }\n"
    "  effect PreviewOnly {\n"
    "    host = none\n"
    "    external = none\n"
    "    network = none\n"
    "    hardware = none\n"
    "  }\n"
    "  policy SafePreview {\n"
    "    require risk != \"high\"\n"
    "    require lock == \"open\"\n"
    "    ensure host_effect == none\n"
    "    ensure external_effect == none\n"
    "  }\n"
    "  transition MoveRight from RootCell {\n"
    "    require lock == \"open\"\n"
    "    effect host = none\n"
    "    effect external = none\n"
    "  }\n"
    "  assertion RootCellIsSafe {\n"
    "    require health == \"ok\"\n"
    "    require host_effect == none\n"
    "    require external_effect == none\n"
    "  }\n"
    "}\n";

static int parse_and_validate(const char *source, latticra_lat_parse_result_t *parse, latticra_lat_semantic_result_t *semantic) {
    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), parse) == LATTICRA_STATUS_OK, "parse call status OK");
    EXPECT_TRUE(latticra_lat_validate_module(parse, semantic) == LATTICRA_STATUS_OK, "semantic call status OK");
    return 0;
}

static int lat_semantic_accepts_foundation_model(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char report[LATTICRA_LAT_SEMANTIC_REPORT_MAX];
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse, &semantic) == 0, "foundation validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "foundation parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_OK, "foundation semantic OK");
    EXPECT_TRUE(semantic.semantic_valid == 1, "foundation semantic valid");
    EXPECT_TRUE(semantic.declaration_count == 5u, "foundation declaration count");
    EXPECT_TRUE(semantic.state_count == 1u, "foundation state count");
    EXPECT_TRUE(semantic.policy_count == 1u, "foundation policy count");
    EXPECT_TRUE(semantic.transition_count == 1u, "foundation transition count");
    EXPECT_TRUE(semantic.assertion_count == 1u, "foundation assertion count");
    EXPECT_TRUE(semantic.effect_count == 1u, "foundation effect count");
    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, report, sizeof(report)) == LATTICRA_STATUS_OK, "foundation report builds");
    EXPECT_TRUE(strstr(report, "LAT SEMANTIC REPORT\n") != 0, "semantic report header");
    EXPECT_TRUE(strstr(report, "error=ok\n") != 0, "semantic report OK");
    return 0;
}

static int lat_semantic_rejects_parse_error(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "parse error validates to semantic diagnostic");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION, "parse error present");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK, "semantic parse_not_ok");
    EXPECT_TRUE(semantic.semantic_valid == 0, "parse error semantic invalid");
    return 0;
}

static int lat_semantic_rejects_duplicate_declaration(void) {
    static const char source[] =
        "lat module Dup {\n"
        "  state RootCell { origin = \"0/0\" }\n"
        "  state RootCell { origin = \"1/0\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "duplicate source validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "duplicate parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION, "duplicate rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].name, "RootCell", "duplicate diagnostic name");
    return 0;
}

static int lat_semantic_rejects_unknown_transition_source(void) {
    static const char source[] =
        "lat module BadTransition {\n"
        "  transition MoveRight from MissingState {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "unknown source validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "unknown source parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE, "unknown transition source rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].name, "MissingState", "unknown source diagnostic name");
    return 0;
}

static int lat_semantic_rejects_invalid_state_field(void) {
    static const char source[] =
        "lat module BadState {\n"
        "  state RootCell { impossible = \"x\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "invalid field validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "invalid field parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD, "invalid state field rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].name, "impossible", "invalid field diagnostic name");
    return 0;
}

static int lat_semantic_rejects_invalid_policy_field_assignment(void) {
    static const char source[] =
        "lat module BadPolicy {\n"
        "  policy SafePreview { lock = \"open\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "invalid policy validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "invalid policy parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION, "policy field assignment rejected");
    return 0;
}

static int lat_semantic_rejects_invalid_effect_target(void) {
    static const char source[] =
        "lat module BadEffectTarget {\n"
        "  effect PreviewOnly { mystery = none }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "invalid effect target validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "invalid target parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET, "invalid effect target rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].name, "mystery", "invalid target diagnostic name");
    return 0;
}

static int lat_semantic_rejects_invalid_effect_value(void) {
    static const char source[] =
        "lat module BadEffectValue {\n"
        "  effect PreviewOnly { host = maybe }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "invalid effect value validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "invalid value parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE, "invalid effect value rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].detail, "maybe", "invalid value diagnostic detail");
    return 0;
}

static int lat_semantic_rejects_effect_requiring_gate(void) {
    static const char source[] =
        "lat module GateNeeded {\n"
        "  effect PreviewOnly { network = network }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "gated effect validates");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "gated effect parse OK");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE, "non-none effect rejected");
    EXPECT_STR_EQ(semantic.diagnostics[0].detail, "network", "gated effect diagnostic detail");
    return 0;
}

static int lat_semantic_preserves_no_effect_flags(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse, &semantic) == 0, "no-effect validates");
    EXPECT_TRUE(semantic.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(semantic.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(semantic.mutation_allowed == 0, "mutation denied");
    EXPECT_TRUE(semantic.server_allowed == 0, "server denied");
    EXPECT_TRUE(semantic.network_allowed == 0, "network denied");
    EXPECT_TRUE(semantic.recovery_allowed == 0, "recovery denied");
    EXPECT_TRUE(semantic.hardware_allowed == 0, "hardware denied");
    return 0;
}

static int lat_semantic_reports_are_deterministic(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char one[LATTICRA_LAT_SEMANTIC_REPORT_MAX];
    char two[LATTICRA_LAT_SEMANTIC_REPORT_MAX];
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse, &semantic) == 0, "report validates");
    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, one, sizeof(one)) == LATTICRA_STATUS_OK, "first semantic report builds");
    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, two, sizeof(two)) == LATTICRA_STATUS_OK, "second semantic report builds");
    EXPECT_STR_EQ(one, two, "semantic report deterministic");
    return 0;
}

static int lat_semantic_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char tiny[8];
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse, &semantic) == 0, "small report validates");
    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small semantic report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small semantic report clears buffer");
    return 0;
}

static int lat_semantic_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_OK), "ok", "ok semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK), "parse_not_ok", "parse semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION), "duplicate_declaration", "duplicate semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE), "unknown_transition_source", "source semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET), "invalid_effect_target", "target semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE), "effect_requires_gate", "gate semantic label");
    EXPECT_STR_EQ(latticra_lat_semantic_error_label(LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR), "internal_error", "internal semantic label");
    return 0;
}

static int lat_semantic_is_deterministic(void) {
    latticra_lat_parse_result_t parse_one;
    latticra_lat_parse_result_t parse_two;
    latticra_lat_semantic_result_t semantic_one;
    latticra_lat_semantic_result_t semantic_two;
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse_one, &semantic_one) == 0, "first semantic deterministic parse");
    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse_two, &semantic_two) == 0, "second semantic deterministic parse");
    EXPECT_TRUE(semantic_one.error == semantic_two.error, "deterministic semantic error");
    EXPECT_TRUE(semantic_one.diagnostic_count == semantic_two.diagnostic_count, "deterministic semantic diagnostics");
    EXPECT_TRUE(semantic_one.declaration_count == semantic_two.declaration_count, "deterministic semantic declarations");
    EXPECT_STR_EQ(semantic_one.module_name, semantic_two.module_name, "deterministic semantic module");
    EXPECT_TRUE(semantic_one.span.end_offset == semantic_two.span.end_offset, "deterministic semantic span");
    return 0;
}

int main(void) {
    if (lat_semantic_accepts_foundation_model() != 0) return 1;
    if (lat_semantic_rejects_parse_error() != 0) return 1;
    if (lat_semantic_rejects_duplicate_declaration() != 0) return 1;
    if (lat_semantic_rejects_unknown_transition_source() != 0) return 1;
    if (lat_semantic_rejects_invalid_state_field() != 0) return 1;
    if (lat_semantic_rejects_invalid_policy_field_assignment() != 0) return 1;
    if (lat_semantic_rejects_invalid_effect_target() != 0) return 1;
    if (lat_semantic_rejects_invalid_effect_value() != 0) return 1;
    if (lat_semantic_rejects_effect_requiring_gate() != 0) return 1;
    if (lat_semantic_preserves_no_effect_flags() != 0) return 1;
    if (lat_semantic_reports_are_deterministic() != 0) return 1;
    if (lat_semantic_report_rejects_small_buffer() != 0) return 1;
    if (lat_semantic_error_labels_are_stable() != 0) return 1;
    if (lat_semantic_is_deterministic() != 0) return 1;

    puts("lat_semantic_validation_invariants: ok");
    return 0;
}
