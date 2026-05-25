#include "latticra/lat_pipeline_diagnostics.h"

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

static int run_pipeline(const char *source,
                        latticra_lat_parse_result_t *parse,
                        latticra_lat_semantic_result_t *semantic,
                        latticra_lir_module_t *module,
                        latticra_lat_to_lir_result_t *lowering,
                        latticra_lat_pipeline_result_t *pipeline) {
    EXPECT_TRUE(latticra_lat_pipeline_run_source(source, strlen(source), parse, semantic, module, lowering, pipeline) == LATTICRA_STATUS_OK, "pipeline status ok");
    return 0;
}

static int lat_pipeline_diagnostic_integration_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID), "valid", "valid label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE), "parse", "parse label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC), "semantic", "semantic label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING), "lowering", "lowering label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR), "lir", "lir label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK), "effect-check", "effect check label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL), "internal", "internal label");
    EXPECT_STR_EQ(latticra_lat_pipeline_diagnostic_class_label(LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL), "model", "model label");
    return 0;
}

static int lat_pipeline_diagnostic_integration_reports_valid_pipeline(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    latticra_lat_pipeline_diagnostic_result_t diagnostic;
    char report[LATTICRA_LAT_PIPELINE_DIAGNOSTIC_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(VALID_SOURCE, &parse, &semantic, &module, &lowering, &pipeline) == 0, "valid pipeline run");
    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_evaluate_with_lowering(&pipeline, &semantic, &lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "valid diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID, "valid diagnostic class");
    EXPECT_TRUE(diagnostic.semantic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID, "valid semantic class");
    EXPECT_TRUE(diagnostic.lowering_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID, "valid lowering class");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_OK, "valid lowering error");
    EXPECT_TRUE(diagnostic.model_error == LATTICRA_LAT_MODEL_OK, "valid model error");
    EXPECT_TRUE(diagnostic.lir_error == LATTICRA_LIR_OK, "valid lir error");
    EXPECT_TRUE(diagnostic.lowering_model_declaration_count == 4u, "valid lowering model declaration count");
    EXPECT_TRUE(diagnostic.lowering_model_clause_count == 20u, "valid lowering model clause count");
    EXPECT_TRUE(diagnostic.lowering_first_transition_source_index == 0u, "valid lowering transition source");
    EXPECT_TRUE(diagnostic.pipeline_failed == 0, "valid pipeline not failed");
    EXPECT_TRUE(diagnostic.semantic_failed == 0, "valid semantic not failed");
    EXPECT_TRUE(diagnostic.lowering_failed == 0, "valid lowering not failed");
    EXPECT_TRUE(diagnostic.model_failed == 0, "valid model not failed");
    EXPECT_TRUE(diagnostic.lir_failed == 0, "valid lir not failed");
    EXPECT_TRUE(diagnostic.evidence_level == 2u, "valid evidence level");

    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_report(&diagnostic, report, sizeof(report)) == LATTICRA_STATUS_OK, "valid diagnostic report");
    EXPECT_TRUE(strstr(report, "diagnostic_class=valid\n") != 0, "valid report class");
    EXPECT_TRUE(strstr(report, "semantic_class=valid\n") != 0, "valid semantic report class");
    EXPECT_TRUE(strstr(report, "lowering_class=valid\n") != 0, "valid lowering report class");
    EXPECT_TRUE(strstr(report, "lowering_model_declaration_count=4\n") != 0, "valid lowering count report");
    EXPECT_TRUE(strstr(report, "lowering_first_transition_source_index=0\n") != 0, "valid transition report");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "valid evidence report");
    return 0;
}

static int lat_pipeline_diagnostic_integration_reports_parse_failure(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    latticra_lat_pipeline_diagnostic_result_t diagnostic;

    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "parse failure pipeline run");
    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_evaluate_with_lowering(&pipeline, &semantic, &lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "parse diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE, "parse diagnostic class");
    EXPECT_TRUE(diagnostic.semantic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE, "parse semantic class");
    EXPECT_TRUE(diagnostic.lowering_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE, "parse lowering class");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_PARSE_NOT_OK, "parse lowering error");
    EXPECT_TRUE(diagnostic.model_error == LATTICRA_LAT_MODEL_PARSE_NOT_OK, "parse model error");
    EXPECT_TRUE(diagnostic.pipeline_failed == 1, "parse pipeline failed");
    EXPECT_TRUE(diagnostic.semantic_failed == 1, "parse semantic failed");
    EXPECT_TRUE(diagnostic.lowering_failed == 1, "parse lowering failed");
    EXPECT_TRUE(diagnostic.model_failed == 1, "parse model failed");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "parse evidence level");
    return 0;
}

static int lat_pipeline_diagnostic_integration_reports_semantic_failure(void) {
    static const char source[] =
        "lat module BadRequirement {\n"
        "  policy SafePreview { require impossible == \"open\" }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    latticra_lat_pipeline_result_t pipeline;
    latticra_lat_pipeline_diagnostic_result_t diagnostic;
    char report[LATTICRA_LAT_PIPELINE_DIAGNOSTIC_REPORT_MAX];

    EXPECT_TRUE(run_pipeline(source, &parse, &semantic, &module, &lowering, &pipeline) == 0, "semantic failure pipeline run");
    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_evaluate_with_lowering(&pipeline, &semantic, &lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "semantic diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC, "semantic diagnostic class");
    EXPECT_TRUE(diagnostic.semantic_class == LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT, "semantic requirement class");
    EXPECT_TRUE(diagnostic.lowering_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC, "semantic lowering class");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK, "semantic lowering error");
    EXPECT_TRUE(diagnostic.semantic_error == LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT, "semantic error copied");
    EXPECT_TRUE(diagnostic.semantic_diagnostic_count == 1u, "semantic diagnostic count copied");
    EXPECT_TRUE(diagnostic.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC, "failed stage semantic");
    EXPECT_TRUE(diagnostic.first_diagnostic_declaration_index == 0u, "first declaration index copied");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "semantic evidence level");

    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_report(&diagnostic, report, sizeof(report)) == LATTICRA_STATUS_OK, "semantic diagnostic report");
    EXPECT_TRUE(strstr(report, "diagnostic_class=semantic\n") != 0, "semantic report class");
    EXPECT_TRUE(strstr(report, "semantic_class=requirement\n") != 0, "semantic class report");
    EXPECT_TRUE(strstr(report, "lowering_class=semantic\n") != 0, "semantic lowering class report");
    EXPECT_TRUE(strstr(report, "semantic_diagnostic_count=1\n") != 0, "semantic count report");
    return 0;
}

static int lat_pipeline_diagnostic_integration_reports_model_failure(void) {
    latticra_lat_pipeline_result_t pipeline;
    latticra_lat_to_lir_result_t lowering;
    latticra_lir_module_t module;
    latticra_lat_pipeline_diagnostic_result_t diagnostic;

    memset(&pipeline, 0, sizeof(pipeline));
    memset(&lowering, 0, sizeof(lowering));
    memset(&module, 0, sizeof(module));
    pipeline.status = LATTICRA_STATUS_OK;
    pipeline.error = LATTICRA_LAT_PIPELINE_MODEL_NOT_OK;
    pipeline.failed_stage = LATTICRA_LAT_PIPELINE_STAGE_MODEL;
    pipeline.model_error = LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION;
    pipeline.lowering_error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
    pipeline.lir_error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
    pipeline.no_effect_chain_ok = 1;
    lowering.status = LATTICRA_STATUS_OK;
    lowering.error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
    lowering.model_error = LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION;
    lowering.first_transition_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    lowering.no_effect = 1;
    module.error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;

    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_evaluate_with_lowering(&pipeline, 0, &lowering, &module, &diagnostic) == LATTICRA_STATUS_OK, "model diagnostic evaluate");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL, "model diagnostic class");
    EXPECT_TRUE(diagnostic.lowering_class == LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL, "model lowering class");
    EXPECT_TRUE(diagnostic.model_error == LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION, "model error copied");
    EXPECT_TRUE(diagnostic.lowering_error == LATTICRA_LAT_TO_LIR_MODEL_NOT_OK, "model lowering error copied");
    EXPECT_TRUE(diagnostic.lir_error == LATTICRA_LIR_UNSUPPORTED_NODE_KIND, "model lir error copied");
    EXPECT_TRUE(diagnostic.failed_stage == LATTICRA_LAT_PIPELINE_STAGE_MODEL, "model failed stage");
    EXPECT_TRUE(diagnostic.pipeline_failed == 1, "model pipeline failed");
    EXPECT_TRUE(diagnostic.model_failed == 1, "model failed flag");
    EXPECT_TRUE(diagnostic.lir_failed == 1, "model lir failed flag");
    EXPECT_TRUE(diagnostic.evidence_level == 1u, "model evidence level");
    return 0;
}

static int lat_pipeline_diagnostic_integration_reports_null_pipeline(void) {
    latticra_lat_pipeline_diagnostic_result_t diagnostic;

    EXPECT_TRUE(latticra_lat_pipeline_diagnostics_evaluate(0, 0, &diagnostic) == LATTICRA_STATUS_NULL_ARGUMENT, "null pipeline diagnostic status");
    EXPECT_TRUE(diagnostic.diagnostic_class == LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL, "null pipeline internal class");
    EXPECT_TRUE(diagnostic.evidence_level == 0u, "null pipeline evidence level");
    return 0;
}

int main(void) {
    if (lat_pipeline_diagnostic_integration_labels_are_stable() != 0) return 1;
    if (lat_pipeline_diagnostic_integration_reports_valid_pipeline() != 0) return 1;
    if (lat_pipeline_diagnostic_integration_reports_parse_failure() != 0) return 1;
    if (lat_pipeline_diagnostic_integration_reports_semantic_failure() != 0) return 1;
    if (lat_pipeline_diagnostic_integration_reports_model_failure() != 0) return 1;
    if (lat_pipeline_diagnostic_integration_reports_null_pipeline() != 0) return 1;

    puts("lat_pipeline_diagnostic_integration_refinement: ok");
    return 0;
}
