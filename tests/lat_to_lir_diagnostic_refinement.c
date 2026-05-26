#include "latticra/lat_to_lir_diagnostics.h"

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
    "}\n";

static int normalize_foundation(
    latticra_lat_parse_result_t *parse,
    latticra_lat_semantic_result_t *semantic,
    latticra_lat_model_t *model) {
    EXPECT_TRUE(latticra_lat_parse_source(FOUNDATION_MODEL, strlen(FOUNDATION_MODEL), parse) == LATTICRA_STATUS_OK, "parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(parse, semantic) == LATTICRA_STATUS_OK, "semantic status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(parse, semantic, model) == LATTICRA_STATUS_OK, "model status OK");
    EXPECT_TRUE(model->error == LATTICRA_LAT_MODEL_OK, "model OK");
    return 0;
}

static int lat_to_lir_diagnostic_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID), "valid", "valid label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE), "parse", "parse label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC), "semantic", "semantic label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL), "model", "model label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK), "effect-check", "effect label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_CAPACITY), "capacity", "capacity label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR), "lir", "lir label");
    EXPECT_STR_EQ(latticra_lat_to_lir_diagnostic_class_label(LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL), "internal", "internal label");
    return 0;
}

static int lat_to_lir_diagnostic_reports_valid_lowering(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_to_lir_diagnostic_result_t diagnostic;
    char report[LATTICRA_LAT_TO_LIR_DIAGNOSTIC_REPORT_MAX];

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "foundation normalized");
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "model lower status");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(&lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "valid diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID, "valid diagnostic class");
    EXPECT_TRUE(diagnostic.lowering_failed == 0, "valid lowering not failed");
    EXPECT_TRUE(diagnostic.model_failed == 0, "valid model not failed");
    EXPECT_TRUE(diagnostic.lir_failed == 0, "valid lir not failed");
    EXPECT_TRUE(diagnostic.model_declaration_count == 4u, "valid declaration count");
    EXPECT_TRUE(diagnostic.model_clause_count == 20u, "valid clause count");
    EXPECT_TRUE(diagnostic.first_declaration_node_index == 1u, "valid first declaration node index");
    EXPECT_TRUE(diagnostic.first_declaration_kind == LATTICRA_LAT_DECLARATION_STATE, "valid first declaration kind");
    EXPECT_STR_EQ(diagnostic.first_declaration_name, "RootCell", "valid first declaration name");
    EXPECT_STR_EQ(diagnostic.first_declaration_source, "", "valid first declaration source");
    EXPECT_TRUE(diagnostic.first_declaration_parse_index == 0u, "valid first declaration parse index");
    EXPECT_TRUE(diagnostic.first_declaration_first_clause_index == 0u, "valid first declaration clause start");
    EXPECT_TRUE(diagnostic.first_declaration_clause_count == 9u, "valid first declaration clause count");
    EXPECT_TRUE(diagnostic.first_declaration_source_index == LATTICRA_LAT_MODEL_NO_INDEX, "valid first declaration source index");
    EXPECT_TRUE(diagnostic.first_transition_source_index == 0u, "valid transition source index");
    EXPECT_TRUE(diagnostic.first_clause_node_index == 5u, "valid first clause node index");
    EXPECT_TRUE(diagnostic.first_clause_role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "valid first clause role");
    EXPECT_TRUE(diagnostic.first_clause_effect == LATTICRA_LAT_EFFECT_UNKNOWN, "valid first clause effect");
    EXPECT_STR_EQ(diagnostic.first_clause_name, "origin", "valid first clause name");
    EXPECT_STR_EQ(diagnostic.first_clause_operator, "=", "valid first clause operator");
    EXPECT_STR_EQ(diagnostic.first_clause_value, "0/0", "valid first clause value");
    EXPECT_TRUE(diagnostic.network_allowed == 0, "valid network denied");
    EXPECT_TRUE(diagnostic.evidence_level == 2u, "valid evidence level");

    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_report(&diagnostic, report, sizeof(report)) == LATTICRA_STATUS_OK, "valid diagnostic report");
    EXPECT_TRUE(strstr(report, "LAT TO LIR DIAGNOSTIC REPORT\n") != 0, "report header");
    EXPECT_TRUE(strstr(report, "diagnostic_class=valid\n") != 0, "report class");
    EXPECT_TRUE(strstr(report, "model_declaration_count=4\n") != 0, "report model count");
    EXPECT_TRUE(strstr(report, "first_declaration_node_index=1\n") != 0, "report first declaration node");
    EXPECT_TRUE(strstr(report, "first_declaration_kind=state\n") != 0, "report first declaration kind");
    EXPECT_TRUE(strstr(report, "first_declaration_name=RootCell\n") != 0, "report first declaration name");
    EXPECT_TRUE(strstr(report, "first_declaration_source=\n") != 0, "report first declaration source");
    EXPECT_TRUE(strstr(report, "first_declaration_parse_index=0\n") != 0, "report first declaration parse index");
    EXPECT_TRUE(strstr(report, "first_declaration_first_clause_index=0\n") != 0, "report first declaration clause start");
    EXPECT_TRUE(strstr(report, "first_declaration_clause_count=9\n") != 0, "report first declaration clause count");
    EXPECT_TRUE(strstr(report, "first_declaration_source_index=") != 0, "report first declaration source index");
    EXPECT_TRUE(strstr(report, "first_transition_source_index=0\n") != 0, "report transition source");
    EXPECT_TRUE(strstr(report, "first_clause_node_index=5\n") != 0, "report first clause node");
    EXPECT_TRUE(strstr(report, "first_clause_role=field\n") != 0, "report first clause role");
    EXPECT_TRUE(strstr(report, "first_clause_effect=unknown\n") != 0, "report first clause effect");
    EXPECT_TRUE(strstr(report, "first_clause_name=origin\n") != 0, "report first clause name");
    EXPECT_TRUE(strstr(report, "first_clause_operator==\n") != 0, "report first clause operator");
    EXPECT_TRUE(strstr(report, "first_clause_value=0/0\n") != 0, "report first clause value");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "report network flag");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "report evidence");
    return 0;
}

static int lat_to_lir_diagnostic_reports_parse_failure(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_to_lir_diagnostic_result_t diagnostic;

    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "bad parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "bad semantic status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(&parse, &semantic, &model) == LATTICRA_STATUS_OK, "bad model status OK");
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "bad lower status OK");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(&lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "parse diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE, "parse diagnostic class");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_PARSE_NOT_OK, "parse lowering error");
    EXPECT_TRUE(diagnostic.model_error == LATTICRA_LAT_MODEL_PARSE_NOT_OK, "parse model error");
    EXPECT_TRUE(diagnostic.lowering_failed == 1, "parse lowering failed");
    EXPECT_TRUE(diagnostic.model_failed == 1, "parse model failed");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "parse evidence level");
    return 0;
}

static int lat_to_lir_diagnostic_reports_model_failure(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_to_lir_diagnostic_result_t diagnostic;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "model failure normalized");
    model.declarations[0].kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "model failure lower status");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(&lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "model diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL, "model diagnostic class");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_MODEL_NOT_OK, "model lowering error");
    EXPECT_TRUE(diagnostic.model_failed == 1, "model failed flag");
    EXPECT_TRUE(diagnostic.lir_failed == 1, "model lir failed flag");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "model evidence level");
    return 0;
}

static int lat_to_lir_diagnostic_reports_no_effect_issue(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_to_lir_diagnostic_result_t diagnostic;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "effect issue normalized");
    model.no_effect = 0;
    model.execution_allowed = 1;
    model.network_allowed = 1;
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "effect lower status");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(&lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "effect diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK, "effect diagnostic class");
    EXPECT_TRUE(diagnostic.no_effect_issue == 1, "effect issue flag");
    EXPECT_TRUE(diagnostic.no_effect == 0, "effect no-effect copied");
    EXPECT_TRUE(diagnostic.execution_allowed == 1, "effect execution copied");
    EXPECT_TRUE(diagnostic.network_allowed == 1, "effect network copied");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "effect evidence level");
    return 0;
}

static int lat_to_lir_diagnostic_reports_null_lowering(void) {
    latticra_lat_to_lir_diagnostic_result_t diagnostic;
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(0, 0, &diagnostic) == LATTICRA_STATUS_NULL_ARGUMENT, "null lowering diagnostic status");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL, "null lowering internal class");
    EXPECT_TRUE(diagnostic.evidence_level == 0u, "null lowering evidence");
    return 0;
}

static int lat_to_lir_diagnostic_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_to_lir_diagnostic_result_t diagnostic;
    char tiny[8];

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "small report normalized");
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "small report lower");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_evaluate(&lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "small report evaluate");
    EXPECT_TRUE(latticra_lat_to_lir_diagnostics_report(&diagnostic, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small report cleared");
    return 0;
}

int main(void) {
    if (lat_to_lir_diagnostic_labels_are_stable() != 0) return 1;
    if (lat_to_lir_diagnostic_reports_valid_lowering() != 0) return 1;
    if (lat_to_lir_diagnostic_reports_parse_failure() != 0) return 1;
    if (lat_to_lir_diagnostic_reports_model_failure() != 0) return 1;
    if (lat_to_lir_diagnostic_reports_no_effect_issue() != 0) return 1;
    if (lat_to_lir_diagnostic_reports_null_lowering() != 0) return 1;
    if (lat_to_lir_diagnostic_report_rejects_small_buffer() != 0) return 1;

    puts("lat_to_lir_diagnostic_refinement: ok");
    return 0;
}
