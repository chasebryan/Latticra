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

static int lat_semantic_diagnostic_class_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID), "valid", "valid class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE), "parse", "parse class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_DECLARATION), "declaration", "declaration class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REFERENCE), "reference", "reference class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT), "requirement", "requirement class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT), "effect", "effect class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_NO_EFFECT), "no-effect", "no-effect class");
    EXPECT_STR_EQ(latticra_lat_semantic_diagnostic_class_label(LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL), "internal", "internal class");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_valid_class(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char report[LATTICRA_LAT_SEMANTIC_REPORT_MAX];

    EXPECT_TRUE(parse_and_validate(FOUNDATION_MODEL, &parse, &semantic) == 0, "valid semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_OK, "valid semantic ok");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID, "valid diagnostic class");
    EXPECT_TRUE(semantic.parse_diagnostic_count == 0u, "valid parse diagnostic count");
    EXPECT_TRUE(semantic.declaration_diagnostic_count == 0u, "valid declaration diagnostic count");
    EXPECT_TRUE(semantic.effect_diagnostic_count == 0u, "valid effect diagnostic count");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 0u, "valid first declaration index default");

    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, report, sizeof(report)) == LATTICRA_STATUS_OK, "valid semantic report");
    EXPECT_TRUE(strstr(report, "diagnostic_class=valid\n") != 0, "valid report class");
    EXPECT_TRUE(strstr(report, "parse_diagnostic_count=0\n") != 0, "valid parse count report");
    EXPECT_TRUE(strstr(report, "effect_diagnostic_count=0\n") != 0, "valid effect count report");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_parse_class(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char report[LATTICRA_LAT_SEMANTIC_REPORT_MAX];

    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "parse diagnostic semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK, "parse diagnostic error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE, "parse diagnostic class");
    EXPECT_TRUE(semantic.parse_diagnostic_count == 1u, "parse diagnostic count");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 0u, "parse first declaration index");
    EXPECT_TRUE(semantic.first_diagnostic_clause_index == 0u, "parse first clause index");

    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, report, sizeof(report)) == LATTICRA_STATUS_OK, "parse semantic report");
    EXPECT_TRUE(strstr(report, "diagnostic_class=parse\n") != 0, "parse class report");
    EXPECT_TRUE(strstr(report, "parse_diagnostic_count=1\n") != 0, "parse count report");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_declaration_class(void) {
    static const char source[] =
        "lat module Dup {\n"
        "  state RootCell { origin = \"0/0\" }\n"
        "  state RootCell { origin = \"1/0\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;

    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "declaration diagnostic semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION, "duplicate declaration error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_DECLARATION, "declaration diagnostic class");
    EXPECT_TRUE(semantic.declaration_diagnostic_count == 1u, "declaration diagnostic count");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 1u, "duplicate first declaration index");
    EXPECT_TRUE(semantic.first_diagnostic_clause_index == 0u, "duplicate first clause index");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_reference_class(void) {
    static const char source[] =
        "lat module BadTransition {\n"
        "  transition MoveRight from MissingState {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;

    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "reference diagnostic semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE, "reference diagnostic error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REFERENCE, "reference diagnostic class");
    EXPECT_TRUE(semantic.reference_diagnostic_count == 2u, "reference diagnostic count preserves per-clause source checks");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 0u, "reference first declaration index");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_requirement_class(void) {
    static const char source[] =
        "lat module BadRequirement {\n"
        "  policy SafePreview { require impossible == \"open\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;

    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "requirement diagnostic semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT, "requirement diagnostic error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT, "requirement diagnostic class");
    EXPECT_TRUE(semantic.requirement_diagnostic_count == 1u, "requirement diagnostic count");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 0u, "requirement first declaration index");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_effect_class(void) {
    static const char source[] =
        "lat module GateNeeded {\n"
        "  effect PreviewOnly { network = network }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    char report[LATTICRA_LAT_SEMANTIC_REPORT_MAX];

    EXPECT_TRUE(parse_and_validate(source, &parse, &semantic) == 0, "effect diagnostic semantic run");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE, "effect diagnostic error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT, "effect diagnostic class");
    EXPECT_TRUE(semantic.effect_diagnostic_count == 1u, "effect diagnostic count");
    EXPECT_TRUE(semantic.first_diagnostic_declaration_index == 0u, "effect first declaration index");

    EXPECT_TRUE(latticra_lat_semantic_report(&semantic, report, sizeof(report)) == LATTICRA_STATUS_OK, "effect semantic report");
    EXPECT_TRUE(strstr(report, "diagnostic_class=effect\n") != 0, "effect class report");
    EXPECT_TRUE(strstr(report, "effect_diagnostic_count=1\n") != 0, "effect count report");
    EXPECT_TRUE(strstr(report, "first_diagnostic_declaration_index=0\n") != 0, "first declaration index report");
    return 0;
}

static int lat_semantic_diagnostics_refinement_reports_internal_null_argument(void) {
    latticra_lat_semantic_result_t semantic;

    EXPECT_TRUE(latticra_lat_validate_module(0, &semantic) == LATTICRA_STATUS_NULL_ARGUMENT, "null parse semantic status");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT, "null semantic error");
    EXPECT_TRUE(semantic.diagnostic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL, "null internal class");
    EXPECT_TRUE(semantic.internal_diagnostic_count == 1u, "null internal diagnostic count");
    EXPECT_TRUE(semantic.diagnostic_count == 0u, "null diagnostic records remain zero");
    return 0;
}

int main(void) {
    if (lat_semantic_diagnostic_class_labels_are_stable() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_valid_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_parse_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_declaration_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_reference_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_requirement_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_effect_class() != 0) return 1;
    if (lat_semantic_diagnostics_refinement_reports_internal_null_argument() != 0) return 1;

    puts("lat_semantic_diagnostics_refinement: ok");
    return 0;
}
