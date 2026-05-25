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

static const char COMMENTED_FOUNDATION_MODEL[] =
    "// pipeline comment one\n"
    "lat module FoundationModule { // module comment\n"
    "  // state comment\n"
    "  state RootCell {\n"
    "    origin = \"0/0\" // origin comment\n"
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
    EXPECT_TRUE(latticra_lat_pipeline_run_source(source, strlen(source), parse, semantic, module, lowering, pipeline) == LATTICRA_STATUS_OK, "pipeline status OK");
    return 0;
}

static int lat_pipeline_accepts_foundation_model(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "foundation pipeline run");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "parse ok");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_OK, "semantic ok");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_OK, "lowering ok");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "lir ok");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_OK, "pipeline ok");
    EXPECT_TRUE(pipeline.model_error == LATTICRA_LAT_MODEL_OK, "pipeline model ok");
    EXPECT_TRUE(pipeline.model_ok == 1, "pipeline model ok flag");
    return 0;
}

static int lat_pipeline_exposes_normalized_model(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    EXPECT_TRUE(latticra_lat_pipeline_run_source_with_model(FOUNDATION_MODEL, strlen(FOUNDATION_MODEL), &parse, &semantic, &model, &module, &lowering, &pipeline) == LATTICRA_STATUS_OK, "model pipeline status OK");
    EXPECT_TRUE(model.error == LATTICRA_LAT_MODEL_OK, "model result ok");
    EXPECT_TRUE(model.declaration_count == 5u, "model declaration count");
    EXPECT_TRUE(model.clause_count == 23u, "model clause count");
    EXPECT_TRUE(model.declarations[model.transition_indices[0]].source_declaration_index == 0u, "model transition source resolved");
    EXPECT_TRUE(lowering.model_error == LATTICRA_LAT_MODEL_OK, "lowering model ok");
    EXPECT_TRUE(lowering.model_declaration_count == 5u, "lowering model declaration count");
    EXPECT_TRUE(lowering.model_clause_count == 23u, "lowering model clause count");
    EXPECT_TRUE(lowering.first_transition_source_index == 0u, "lowering transition source index");
    EXPECT_TRUE(pipeline.model_declaration_count == 5u, "pipeline model declaration count");
    EXPECT_TRUE(pipeline.model_clause_count == 23u, "pipeline model clause count");
    EXPECT_TRUE(pipeline.first_declaration_node_index == 1u, "pipeline first declaration node index");
    EXPECT_TRUE(pipeline.first_declaration_kind == LATTICRA_LAT_DECLARATION_STATE, "pipeline first declaration kind");
    EXPECT_STR_EQ(pipeline.first_declaration_name, "RootCell", "pipeline first declaration name");
    EXPECT_STR_EQ(pipeline.first_declaration_source, "", "pipeline first declaration source");
    EXPECT_TRUE(pipeline.first_declaration_parse_index == 0u, "pipeline first declaration parse index");
    EXPECT_TRUE(pipeline.first_declaration_first_clause_index == 0u, "pipeline first declaration clause start");
    EXPECT_TRUE(pipeline.first_declaration_clause_count == 9u, "pipeline first declaration clause count");
    EXPECT_TRUE(pipeline.first_declaration_source_index == LATTICRA_LAT_MODEL_NO_INDEX, "pipeline first declaration source index");
    EXPECT_TRUE(pipeline.first_transition_source_index == 0u, "pipeline transition source index");
    EXPECT_TRUE(pipeline.first_clause_node_index == 6u, "pipeline first clause node index");
    EXPECT_TRUE(pipeline.first_clause_role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "pipeline first clause role");
    EXPECT_TRUE(pipeline.first_clause_effect == LATTICRA_LAT_EFFECT_UNKNOWN, "pipeline first clause effect");
    EXPECT_STR_EQ(pipeline.first_clause_name, "origin", "pipeline first clause name");
    EXPECT_STR_EQ(pipeline.first_clause_operator, "=", "pipeline first clause operator");
    EXPECT_STR_EQ(pipeline.first_clause_value, "0/0", "pipeline first clause value");
    return 0;
}

static int lat_pipeline_preserves_counts(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "count pipeline run");
    EXPECT_TRUE(pipeline.declaration_count == 5u, "declaration count");
    EXPECT_TRUE(pipeline.clause_count == 23u, "clause count");
    EXPECT_TRUE(pipeline.model_declaration_count == 5u, "model declaration count");
    EXPECT_TRUE(pipeline.model_clause_count == 23u, "model clause count");
    EXPECT_TRUE(pipeline.node_count == 29u, "node count");
    EXPECT_TRUE(pipeline.edge_count == 29u, "edge count");
    EXPECT_STR_EQ(pipeline.module_name, "FoundationModule", "module name");
    return 0;
}

static int lat_pipeline_exposes_comment_metadata(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char report[LATTICRA_LAT_PIPELINE_REPORT_MAX];
    EXPECT_TRUE(run_pipeline(COMMENTED_FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "comment metadata pipeline run");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "comment metadata parse ok");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_OK, "comment metadata pipeline ok");
    EXPECT_TRUE(pipeline.comment_count == 4u, "pipeline comment count");
    EXPECT_TRUE(pipeline.first_comment_span.start_line == 1u, "pipeline first comment line");
    EXPECT_TRUE(pipeline.first_comment_span.start_column == 1u, "pipeline first comment column");
    EXPECT_TRUE(pipeline.no_effect == 1, "comment metadata no-effect");
    EXPECT_TRUE(pipeline.execution_allowed == 0, "comment metadata execution denied");
    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, report, sizeof(report)) == LATTICRA_STATUS_OK, "comment metadata report");
    EXPECT_TRUE(strstr(report, "error=ok\n") != 0, "comment report ok");
    EXPECT_TRUE(strstr(report, "comment_count=4\n") != 0, "comment count in report");
    EXPECT_TRUE(strstr(report, "first_comment_start_line=1\n") != 0, "first comment line in report");
    EXPECT_TRUE(strstr(report, "first_comment_start_column=1\n") != 0, "first comment column in report");
    return 0;
}

static int lat_pipeline_preserves_parse_failure_comment_metadata(void) {
    static const char source[] =
        "// preserved before unsupported block\n"
        "lat module Bad {\n"
        "  /* block comments are not supported */\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char report[LATTICRA_LAT_PIPELINE_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "parse failure comment pipeline run");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT, "parse failure comment unsupported block");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK, "parse failure comment pipeline error");
    EXPECT_TRUE(pipeline.parse_error == LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT, "parse failure comment parse error copied");
    EXPECT_TRUE(pipeline.comment_count == 1u, "parse failure comment count");
    EXPECT_TRUE(pipeline.first_comment_span.start_line == 1u, "parse failure comment line");
    EXPECT_TRUE(pipeline.first_comment_span.start_column == 1u, "parse failure comment column");
    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, report, sizeof(report)) == LATTICRA_STATUS_OK, "parse failure comment report");
    EXPECT_TRUE(strstr(report, "error=parse_not_ok\n") != 0, "parse failure comment report error");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_block_comment\n") != 0, "parse failure comment report parse error");
    EXPECT_TRUE(strstr(report, "comment_count=1\n") != 0, "parse failure comment report count");
    EXPECT_TRUE(strstr(report, "first_comment_start_line=1\n") != 0, "parse failure comment report line");
    EXPECT_TRUE(strstr(report, "first_comment_start_column=1\n") != 0, "parse failure comment report column");
    return 0;
}

static int lat_pipeline_rejects_parse_failure(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "parse failure pipeline run");
    EXPECT_TRUE(parse.error != LATTICRA_LAT_PARSE_OK, "parse failed");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK, "pipeline parse failure");
    EXPECT_TRUE(pipeline.model_error == LATTICRA_LAT_MODEL_PARSE_NOT_OK, "model parse failure");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_PARSE_NOT_OK, "lowering parse failure");
    return 0;
}

static int lat_pipeline_rejects_semantic_failure(void) {
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
    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "semantic failure pipeline run");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "parse ok before semantic failure");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE, "semantic failure captured");
    EXPECT_TRUE(pipeline.error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK, "pipeline semantic failure");
    EXPECT_TRUE(pipeline.model_error == LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK, "model semantic failure");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK, "lowering semantic failure");
    return 0;
}

static int lat_pipeline_preserves_no_effect_flags(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "flags pipeline run");
    EXPECT_TRUE(pipeline.no_effect == 1, "pipeline no-effect");
    EXPECT_TRUE(pipeline.execution_allowed == 0, "pipeline execution flag");
    EXPECT_TRUE(pipeline.mutation_allowed == 0, "pipeline mutation flag");
    EXPECT_TRUE(pipeline.server_allowed == 0, "pipeline server flag");
    EXPECT_TRUE(pipeline.recovery_allowed == 0, "pipeline recovery flag");
    EXPECT_TRUE(pipeline.hardware_allowed == 0, "pipeline hardware flag");
    return 0;
}

static int lat_pipeline_report_is_deterministic(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char one[LATTICRA_LAT_PIPELINE_REPORT_MAX];
    char two[LATTICRA_LAT_PIPELINE_REPORT_MAX];
    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "report pipeline run");
    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report");
    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report");
    EXPECT_STR_EQ(one, two, "report deterministic");
    EXPECT_TRUE(strstr(one, "LAT PIPELINE REPORT\n") != 0, "report header");
    EXPECT_TRUE(strstr(one, "error=ok\n") != 0, "report ok");
    EXPECT_TRUE(strstr(one, "model_error=ok\n") != 0, "model ok in report");
    EXPECT_TRUE(strstr(one, "comment_count=0\n") != 0, "comment count in report");
    EXPECT_TRUE(strstr(one, "model_declaration_count=5\n") != 0, "model count in report");
    EXPECT_TRUE(strstr(one, "first_declaration_node_index=1\n") != 0, "first declaration node in report");
    EXPECT_TRUE(strstr(one, "first_declaration_kind=state\n") != 0, "first declaration kind in report");
    EXPECT_TRUE(strstr(one, "first_declaration_name=RootCell\n") != 0, "first declaration name in report");
    EXPECT_TRUE(strstr(one, "first_declaration_source=\n") != 0, "first declaration source in report");
    EXPECT_TRUE(strstr(one, "first_declaration_parse_index=0\n") != 0, "first declaration parse index in report");
    EXPECT_TRUE(strstr(one, "first_declaration_first_clause_index=0\n") != 0, "first declaration clause start in report");
    EXPECT_TRUE(strstr(one, "first_declaration_clause_count=9\n") != 0, "first declaration clause count in report");
    EXPECT_TRUE(strstr(one, "first_declaration_source_index=") != 0, "first declaration source index in report");
    EXPECT_TRUE(strstr(one, "first_clause_node_index=6\n") != 0, "first clause node in report");
    EXPECT_TRUE(strstr(one, "first_clause_role=field\n") != 0, "first clause role in report");
    EXPECT_TRUE(strstr(one, "first_clause_effect=unknown\n") != 0, "first clause effect in report");
    EXPECT_TRUE(strstr(one, "first_clause_name=origin\n") != 0, "first clause name in report");
    EXPECT_TRUE(strstr(one, "first_clause_operator==\n") != 0, "first clause operator in report");
    EXPECT_TRUE(strstr(one, "first_clause_value=0/0\n") != 0, "first clause value in report");
    EXPECT_TRUE(strstr(one, "lowering_error=ok\n") != 0, "lowering ok in report");
    return 0;
}

static int lat_pipeline_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    char tiny[8];
    EXPECT_TRUE(run_pipeline(FOUNDATION_MODEL, &parse, &semantic, &module, &lowering, &pipeline) == 0, "small report pipeline run");
    EXPECT_TRUE(latticra_lat_pipeline_report(&pipeline, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small report cleared");
    return 0;
}

static int lat_pipeline_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_OK), "ok", "ok label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_NULL_ARGUMENT), "null_argument", "null label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_PARSE_NOT_OK), "parse_not_ok", "parse label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK), "semantic_not_ok", "semantic label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID), "semantic_not_valid", "semantic valid label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_MODEL_NOT_OK), "model_not_ok", "model label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK), "lowering_not_ok", "lowering label");
    EXPECT_STR_EQ(latticra_lat_pipeline_error_label(LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION), "no_effect_violation", "flags label");
    return 0;
}

int main(void) {
    if (lat_pipeline_accepts_foundation_model() != 0) return 1;
    if (lat_pipeline_exposes_normalized_model() != 0) return 1;
    if (lat_pipeline_preserves_counts() != 0) return 1;
    if (lat_pipeline_exposes_comment_metadata() != 0) return 1;
    if (lat_pipeline_preserves_parse_failure_comment_metadata() != 0) return 1;
    if (lat_pipeline_rejects_parse_failure() != 0) return 1;
    if (lat_pipeline_rejects_semantic_failure() != 0) return 1;
    if (lat_pipeline_preserves_no_effect_flags() != 0) return 1;
    if (lat_pipeline_report_is_deterministic() != 0) return 1;
    if (lat_pipeline_report_rejects_small_buffer() != 0) return 1;
    if (lat_pipeline_error_labels_are_stable() != 0) return 1;

    puts("lat_pipeline_invariants: ok");
    return 0;
}
