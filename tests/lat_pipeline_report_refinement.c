#include "latticra/lat_pipeline.h"

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

static int run_pipeline(
    const char *source,
    latticra_lat_parse_result_t *parse,
    latticra_lat_semantic_result_t *semantic,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering,
    latticra_lat_pipeline_result_t *pipeline) {
    EXPECT_TRUE(latticra_lat_pipeline_run_source(source, strlen(source), parse, semantic, module, lowering, pipeline) == LATTICRA_STATUS_OK, "pipeline run status OK");
    return 0;
}

static int lat_pipeline_report_refinement_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_NONE), "none", "none stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_PARSE), "parse", "parse stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC), "semantic", "semantic stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_MODEL), "model", "model stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_LOWERING), "lowering", "lowering stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_LIR), "lir", "lir stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_EFFECT_CHECK), "effect-check", "effect-check stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_REPORT), "report", "report stage label");
    EXPECT_STR_EQ(latticra_lat_pipeline_stage_label(LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN), "unknown", "unknown stage label");
    return 0;
}

static int lat_pipeline_report_refinement_reports_success_stage_summary(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char report[LATTICRA_LAT_PIPELINE_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "success pipeline run");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_OK, "pipeline ok");
    EXPECT_TRUE(pipeline.last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_REPORT, "last stage report");
    EXPECT_TRUE(pipeline.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_NONE, "failed stage none");
    EXPECT_TRUE(pipeline.parse_ok == 1, "parse ok flag");
    EXPECT_TRUE(pipeline.semantic_ok == 1, "semantic ok flag");
    EXPECT_TRUE(pipeline.model_ok == 1, "model ok flag");
    EXPECT_TRUE(pipeline.lowering_ok == 1, "lowering ok flag");
    EXPECT_TRUE(pipeline.lir_ok == 1, "lir ok flag");
    EXPECT_TRUE(pipeline.first_declaration_node_index == 1u, "first declaration node index");
    EXPECT_TRUE(pipeline.first_declaration_kind == LATTICRA_LAT_DECLARATION_STATE, "first declaration kind");
    EXPECT_STR_EQ(pipeline.first_declaration_name, "RootCell", "first declaration name");
    EXPECT_STR_EQ(pipeline.first_declaration_source, "", "first declaration source");
    EXPECT_TRUE(pipeline.first_declaration_parse_index == 0u, "first declaration parse index");
    EXPECT_TRUE(pipeline.first_declaration_first_clause_index == 0u, "first declaration clause start");
    EXPECT_TRUE(pipeline.first_declaration_clause_count == 9u, "first declaration clause count");
    EXPECT_TRUE(pipeline.first_declaration_source_index == LATTICRA_LAT_MODEL_NO_INDEX, "first declaration source index");
    EXPECT_TRUE(pipeline.first_clause_node_index == 6u, "first clause node index");
    EXPECT_TRUE(pipeline.first_clause_role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "first clause role");
    EXPECT_TRUE(pipeline.first_clause_effect == LATTICRA_LAT_EFFECT_UNKNOWN, "first clause effect");
    EXPECT_STR_EQ(pipeline.first_clause_name, "origin", "first clause name");
    EXPECT_STR_EQ(pipeline.first_clause_operator, "=", "first clause operator");
    EXPECT_STR_EQ(pipeline.first_clause_value, "0/0", "first clause value");
    EXPECT_TRUE(pipeline.no_effect_chain_ok == 1, "no-effect chain ok");
    EXPECT_TRUE(pipeline.evidence_level == 2u, "success evidence level two");

    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, report, sizeof(report)) == LATTICRA_STATUS_OK, "success report ok");
    EXPECT_TRUE(strstr(report, "last_completed_stage=report\n") != 0, "last completed report field");
    EXPECT_TRUE(strstr(report, "failed_stage=none\n") != 0, "failed none report field");
    EXPECT_TRUE(strstr(report, "parse_ok=1\n") != 0, "parse ok report field");
    EXPECT_TRUE(strstr(report, "semantic_ok=1\n") != 0, "semantic ok report field");
    EXPECT_TRUE(strstr(report, "model_ok=1\n") != 0, "model ok report field");
    EXPECT_TRUE(strstr(report, "model_error=ok\n") != 0, "model error report field");
    EXPECT_TRUE(strstr(report, "first_declaration_node_index=1\n") != 0, "first declaration node report field");
    EXPECT_TRUE(strstr(report, "first_declaration_kind=state\n") != 0, "first declaration kind report field");
    EXPECT_TRUE(strstr(report, "first_declaration_name=RootCell\n") != 0, "first declaration name report field");
    EXPECT_TRUE(strstr(report, "first_declaration_source=\n") != 0, "first declaration source report field");
    EXPECT_TRUE(strstr(report, "first_declaration_parse_index=0\n") != 0, "first declaration parse index report field");
    EXPECT_TRUE(strstr(report, "first_declaration_first_clause_index=0\n") != 0, "first declaration clause start report field");
    EXPECT_TRUE(strstr(report, "first_declaration_clause_count=9\n") != 0, "first declaration clause count report field");
    EXPECT_TRUE(strstr(report, "first_declaration_source_index=") != 0, "first declaration source index report field");
    EXPECT_TRUE(strstr(report, "first_transition_source_index=0\n") != 0, "transition source report field");
    EXPECT_TRUE(strstr(report, "first_clause_node_index=6\n") != 0, "first clause node report field");
    EXPECT_TRUE(strstr(report, "first_clause_role=field\n") != 0, "first clause role report field");
    EXPECT_TRUE(strstr(report, "first_clause_effect=unknown\n") != 0, "first clause effect report field");
    EXPECT_TRUE(strstr(report, "first_clause_name=origin\n") != 0, "first clause name report field");
    EXPECT_TRUE(strstr(report, "first_clause_operator==\n") != 0, "first clause operator report field");
    EXPECT_TRUE(strstr(report, "first_clause_value=0/0\n") != 0, "first clause value report field");
    EXPECT_TRUE(strstr(report, "lowering_ok=1\n") != 0, "lowering ok report field");
    EXPECT_TRUE(strstr(report, "lir_ok=1\n") != 0, "lir ok report field");
    EXPECT_TRUE(strstr(report, "no_effect_chain_ok=1\n") != 0, "no-effect chain report field");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "evidence level report field");
    return 0;
}

static int lat_pipeline_report_refinement_reports_parse_failure_stage(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char report[LATTICRA_LAT_PIPELINE_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "parse failure pipeline run");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK, "parse failure pipeline error");
    EXPECT_TRUE(pipeline.parse_ok == 0, "parse ok false");
    EXPECT_TRUE(pipeline.model_ok == 0, "parse failure model false");
    EXPECT_TRUE(pipeline.model_error == LATTICRA_LAT_MODEL_PARSE_NOT_OK, "parse failure model error");
    EXPECT_TRUE(pipeline.last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_NONE, "parse failure completed none");
    EXPECT_TRUE(pipeline.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_PARSE, "parse failed stage");
    EXPECT_TRUE(pipeline.evidence_level == 1u, "parse failure evidence level one");

    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, report, sizeof(report)) == LATTICRA_STATUS_OK, "parse failure report ok");
    EXPECT_TRUE(strstr(report, "last_completed_stage=none\n") != 0, "parse failure last stage report");
    EXPECT_TRUE(strstr(report, "failed_stage=parse\n") != 0, "parse failed stage report");
    EXPECT_TRUE(strstr(report, "parse_ok=0\n") != 0, "parse ok false report");
    EXPECT_TRUE(strstr(report, "model_ok=0\n") != 0, "parse model false report");
    EXPECT_TRUE(strstr(report, "model_error=parse_not_ok\n") != 0, "parse model error report");
    EXPECT_TRUE(strstr(report, "evidence_level=1\n") != 0, "parse evidence level report");
    return 0;
}

static int lat_pipeline_report_refinement_reports_semantic_failure_stage(void) {
    static const char source[] =
        "lat module BadTransition {\n"
        "  transition MoveRight from MissingState {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char report[LATTICRA_LAT_PIPELINE_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "semantic failure pipeline run");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK, "semantic failure pipeline error");
    EXPECT_TRUE(pipeline.parse_ok == 1, "semantic failure parse ok");
    EXPECT_TRUE(pipeline.semantic_ok == 0, "semantic ok false");
    EXPECT_TRUE(pipeline.model_ok == 0, "semantic failure model false");
    EXPECT_TRUE(pipeline.model_error == LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK, "semantic failure model error");
    EXPECT_TRUE(pipeline.last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_PARSE, "semantic failure completed parse");
    EXPECT_TRUE(pipeline.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC, "semantic failed stage");
    EXPECT_TRUE(pipeline.evidence_level == 1u, "semantic failure evidence level one");

    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, report, sizeof(report)) == LATTICRA_STATUS_OK, "semantic failure report ok");
    EXPECT_TRUE(strstr(report, "last_completed_stage=parse\n") != 0, "semantic failure last stage report");
    EXPECT_TRUE(strstr(report, "failed_stage=semantic\n") != 0, "semantic failed stage report");
    EXPECT_TRUE(strstr(report, "parse_ok=1\n") != 0, "semantic failure parse ok report");
    EXPECT_TRUE(strstr(report, "semantic_ok=0\n") != 0, "semantic false report");
    EXPECT_TRUE(strstr(report, "model_ok=0\n") != 0, "semantic model false report");
    EXPECT_TRUE(strstr(report, "model_error=semantic_not_ok\n") != 0, "semantic model error report");
    return 0;
}

static int lat_pipeline_report_refinement_null_result_sets_unknown_stage(void) {
    latticra_lat_pipeline_result_t pipeline;

    EXPECT_TRUE(latticra_lat_pipeline_run_source(0, 10u, 0, 0, 0, 0, &pipeline) == LATTICRA_STATUS_NULL_ARGUMENT, "null pipeline returns null argument");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_NULL_ARGUMENT, "null pipeline error");
    EXPECT_TRUE(pipeline.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_UNKNOWN, "null pipeline unknown failed stage");
    EXPECT_TRUE(pipeline.evidence_level == 0u, "null pipeline evidence zero");
    return 0;
}

int main(void) {
    if (lat_pipeline_report_refinement_labels_are_stable() != 0) return 1;
    if (lat_pipeline_report_refinement_reports_success_stage_summary() != 0) return 1;
    if (lat_pipeline_report_refinement_reports_parse_failure_stage() != 0) return 1;
    if (lat_pipeline_report_refinement_reports_semantic_failure_stage() != 0) return 1;
    if (lat_pipeline_report_refinement_null_result_sets_unknown_stage() != 0) return 1;

    puts("lat_pipeline_report_refinement: ok");
    return 0;
}
