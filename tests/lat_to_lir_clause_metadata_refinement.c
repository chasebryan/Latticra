#include "latticra/lat_to_lir.h"

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

static size_t clause_node_index(const latticra_lat_model_t *model, size_t clause_index) {
    return 1u + model->declaration_count + clause_index;
}

static int lower_foundation(
    latticra_lat_parse_result_t *parse,
    latticra_lat_semantic_result_t *semantic,
    latticra_lat_model_t *model,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering) {
    EXPECT_TRUE(latticra_lat_parse_source(FOUNDATION_MODEL, strlen(FOUNDATION_MODEL), parse) == LATTICRA_STATUS_OK, "parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(parse, semantic) == LATTICRA_STATUS_OK, "semantic status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(parse, semantic, model) == LATTICRA_STATUS_OK, "model status OK");
    EXPECT_TRUE(latticra_lir_lower_lat_model(model, module, lowering) == LATTICRA_STATUS_OK, "lowering status OK");
    EXPECT_TRUE(model->error == LATTICRA_LAT_MODEL_OK, "model OK");
    EXPECT_TRUE(lowering->error == LATTICRA_LAT_TO_LIR_OK, "lowering OK");
    EXPECT_TRUE(module->error == LATTICRA_LIR_OK, "LIR OK");
    return 0;
}

static int clause_metadata_preserves_field_operator(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    char report[LATTICRA_LAT_TO_LIR_REPORT_MAX];
    size_t state_index;
    size_t clause_index;
    size_t node_index;

    EXPECT_TRUE(lower_foundation(&parse, &semantic, &model, &module, &lowering) == 0, "foundation lowered");
    state_index = model.state_indices[0];
    clause_index = model.declarations[state_index].first_clause_index;
    node_index = clause_node_index(&model, clause_index);

    EXPECT_TRUE(module.nodes[node_index].kind == LATTICRA_LIR_NODE_FIELD, "state field node kind");
    EXPECT_STR_EQ(module.nodes[node_index].name, "origin", "state field name");
    EXPECT_STR_EQ(module.nodes[node_index].operator_text, "=", "state field operator");
    EXPECT_STR_EQ(module.nodes[node_index].value, "0/0", "state field value");
    EXPECT_STR_EQ(module.nodes[node_index].binding, "field", "state field role");

    EXPECT_TRUE(lowering.first_clause_node_index == node_index, "first clause node index");
    EXPECT_TRUE(lowering.first_clause_role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "first clause role");
    EXPECT_TRUE(lowering.first_clause_effect == LATTICRA_LAT_EFFECT_UNKNOWN, "first clause effect");
    EXPECT_STR_EQ(lowering.first_clause_name, "origin", "first clause name");
    EXPECT_STR_EQ(lowering.first_clause_operator, "=", "first clause operator");
    EXPECT_STR_EQ(lowering.first_clause_value, "0/0", "first clause value");

    EXPECT_TRUE(latticra_lat_to_lir_report(&lowering, report, sizeof(report)) == LATTICRA_STATUS_OK, "lowering report");
    EXPECT_TRUE(strstr(report, "first_clause_node_index=6\n") != 0, "report first clause node");
    EXPECT_TRUE(strstr(report, "first_clause_role=field\n") != 0, "report first clause role");
    EXPECT_TRUE(strstr(report, "first_clause_effect=unknown\n") != 0, "report first clause effect");
    EXPECT_TRUE(strstr(report, "first_clause_name=origin\n") != 0, "report first clause name");
    EXPECT_TRUE(strstr(report, "first_clause_operator==\n") != 0, "report first clause operator");
    EXPECT_TRUE(strstr(report, "first_clause_value=0/0\n") != 0, "report first clause value");
    return 0;
}

static int clause_metadata_preserves_requirement_operator(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    size_t policy_index;
    size_t clause_index;
    size_t node_index;

    EXPECT_TRUE(lower_foundation(&parse, &semantic, &model, &module, &lowering) == 0, "foundation lowered");
    policy_index = model.policy_indices[0];
    clause_index = model.declarations[policy_index].first_clause_index;
    node_index = clause_node_index(&model, clause_index);

    EXPECT_TRUE(module.nodes[node_index].kind == LATTICRA_LIR_NODE_LAT_REQUIREMENT, "requirement node kind");
    EXPECT_STR_EQ(module.nodes[node_index].name, "risk", "requirement name");
    EXPECT_STR_EQ(module.nodes[node_index].operator_text, "!=", "requirement operator");
    EXPECT_STR_EQ(module.nodes[node_index].value, "high", "requirement value");
    EXPECT_STR_EQ(module.nodes[node_index].binding, "require", "requirement role");
    return 0;
}

static int clause_metadata_preserves_effect_operator_and_effect_label(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    size_t transition_index;
    size_t clause_index;
    size_t node_index;

    EXPECT_TRUE(lower_foundation(&parse, &semantic, &model, &module, &lowering) == 0, "foundation lowered");
    transition_index = model.transition_indices[0];
    clause_index = model.declarations[transition_index].first_clause_index + 1u;
    node_index = clause_node_index(&model, clause_index);

    EXPECT_TRUE(model.clauses[clause_index].effect == LATTICRA_LAT_EFFECT_NONE, "effect clause effect enum");
    EXPECT_TRUE(module.nodes[node_index].kind == LATTICRA_LIR_NODE_EFFECT, "effect node kind");
    EXPECT_STR_EQ(module.nodes[node_index].name, "host", "effect target");
    EXPECT_STR_EQ(module.nodes[node_index].operator_text, "=", "effect operator");
    EXPECT_STR_EQ(module.nodes[node_index].value, "none", "effect value");
    EXPECT_STR_EQ(module.nodes[node_index].binding, "effect", "effect role");
    return 0;
}

static int lat_parser_rejects_trailing_content(void) {
    static const char source[] =
        "lat module Tight {\n"
        "  state RootCell { origin = \"0/0\" }\n"
        "}\n"
        "lat module Extra { }\n";
    latticra_lat_parse_result_t parse;

    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "trailing parse call");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_TRAILING_CONTENT, "trailing content rejected");
    EXPECT_STR_EQ(latticra_lat_parse_error_label(parse.error), "trailing_content", "trailing label");
    return 0;
}

static int lat_reports_escape_clause_values(void) {
    static const char source[] =
        "lat module EscapedReport {\n"
        "  state RootCell {\n"
        "    origin = \"0/0\\nnetwork_allowed=1\"\n"
        "    route = \"ROOT\"\n"
        "    axis = \"ROOT\"\n"
        "    path = \"/\"\n"
        "    health = \"ok\"\n"
        "    risk = \"low\"\n"
        "    lock = \"open\"\n"
        "    host_effect = none\n"
        "    external_effect = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    char parse_report[LATTICRA_LAT_REPORT_MAX];
    char lowering_report[LATTICRA_LAT_TO_LIR_REPORT_MAX];

    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "escaped parse call");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "escaped parse ok");
    EXPECT_TRUE(latticra_lat_parse_report(&parse, parse_report, sizeof(parse_report)) == LATTICRA_STATUS_OK, "escaped parse report");
    EXPECT_TRUE(strstr(parse_report, "first_clause_right=0/0\\nnetwork_allowed=1\n") != 0, "parse report escaped");
    EXPECT_TRUE(strstr(parse_report, "first_clause_right=0/0\nnetwork_allowed=1\n") == 0, "parse report cannot forge line");

    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "escaped semantic status");
    EXPECT_TRUE(latticra_lat_model_normalize_module(&parse, &semantic, &model) == LATTICRA_STATUS_OK, "escaped model status");
    EXPECT_TRUE(latticra_lir_lower_lat_model(&model, &module, &lowering) == LATTICRA_STATUS_OK, "escaped lowering status");
    EXPECT_TRUE(latticra_lat_to_lir_report(&lowering, lowering_report, sizeof(lowering_report)) == LATTICRA_STATUS_OK, "escaped lowering report");
    EXPECT_TRUE(strstr(lowering_report, "first_clause_value=0/0\\nnetwork_allowed=1\n") != 0, "lowering report escaped");
    EXPECT_TRUE(strstr(lowering_report, "first_clause_value=0/0\nnetwork_allowed=1\n") == 0, "lowering report cannot forge line");
    return 0;
}

int main(void) {
    if (clause_metadata_preserves_field_operator() != 0) return 1;
    if (clause_metadata_preserves_requirement_operator() != 0) return 1;
    if (clause_metadata_preserves_effect_operator_and_effect_label() != 0) return 1;
    if (lat_parser_rejects_trailing_content() != 0) return 1;
    if (lat_reports_escape_clause_values() != 0) return 1;

    puts("lat_to_lir_clause_metadata_refinement: ok");
    return 0;
}
