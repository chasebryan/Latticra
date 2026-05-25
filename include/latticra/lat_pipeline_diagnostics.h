#ifndef LATTICRA_LAT_PIPELINE_DIAGNOSTICS_H
#define LATTICRA_LAT_PIPELINE_DIAGNOSTICS_H

#include "latticra/lat_pipeline.h"
#include "latticra/lat_to_lir_diagnostics.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_PIPELINE_DIAGNOSTIC_REPORT_MAX 4096u

typedef enum {
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_VALID = 0,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_PARSE = 1,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC = 2,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LOWERING = 3,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_LIR = 4,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_EFFECT_CHECK = 5,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_INTERNAL = 6,
    LATTICRA_LAT_PIPELINE_DIAGNOSTIC_MODEL = 7
} latticra_lat_pipeline_diagnostic_class_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_pipeline_diagnostic_class_t diagnostic_class;
    latticra_lat_pipeline_error_t pipeline_error;
    latticra_lat_pipeline_stage_t failed_stage;
    latticra_lat_semantic_diagnostic_class_t semantic_class;
    latticra_lat_semantic_error_t semantic_error;
    latticra_lat_to_lir_diagnostic_class_t lowering_class;
    latticra_lat_to_lir_error_t lowering_error;
    latticra_lat_model_error_t model_error;
    latticra_lir_error_t lir_error;
    size_t semantic_diagnostic_count;
    size_t first_diagnostic_declaration_index;
    size_t first_diagnostic_clause_index;
    size_t lowering_model_declaration_count;
    size_t lowering_model_clause_count;
    size_t lowering_first_declaration_node_index;
    latticra_lat_declaration_kind_t lowering_first_declaration_kind;
    char lowering_first_declaration_name[LATTICRA_LAT_NAME_MAX];
    char lowering_first_declaration_source[LATTICRA_LAT_NAME_MAX];
    size_t lowering_first_declaration_parse_index;
    size_t lowering_first_declaration_first_clause_index;
    size_t lowering_first_declaration_clause_count;
    size_t lowering_first_declaration_source_index;
    size_t lowering_first_transition_source_index;
    size_t lowering_first_clause_node_index;
    latticra_lat_model_clause_role_t lowering_first_clause_role;
    latticra_lat_effect_t lowering_first_clause_effect;
    char lowering_first_clause_name[LATTICRA_LAT_NAME_MAX];
    char lowering_first_clause_operator[LATTICRA_LAT_NAME_MAX];
    char lowering_first_clause_value[LATTICRA_LAT_VALUE_MAX];
    int pipeline_failed;
    int semantic_failed;
    int lowering_failed;
    int model_failed;
    int lir_failed;
    int no_effect_issue;
    unsigned int evidence_level;
} latticra_lat_pipeline_diagnostic_result_t;

const char *latticra_lat_pipeline_diagnostic_class_label(
    latticra_lat_pipeline_diagnostic_class_t diagnostic_class);

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate(
    const latticra_lat_pipeline_result_t *pipeline_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_pipeline_diagnostic_result_t *diagnostic_result);

latticra_status_t latticra_lat_pipeline_diagnostics_evaluate_with_lowering(
    const latticra_lat_pipeline_result_t *pipeline_result,
    const latticra_lat_semantic_result_t *semantic_result,
    const latticra_lat_to_lir_result_t *lowering_result,
    const latticra_lir_module_t *module,
    latticra_lat_pipeline_diagnostic_result_t *diagnostic_result);

latticra_status_t latticra_lat_pipeline_diagnostics_report(
    const latticra_lat_pipeline_diagnostic_result_t *diagnostic_result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
