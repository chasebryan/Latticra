#ifndef LATTICRA_LAT_TO_LIR_DIAGNOSTICS_H
#define LATTICRA_LAT_TO_LIR_DIAGNOSTICS_H

#include "latticra/lat_to_lir.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_TO_LIR_DIAGNOSTIC_REPORT_MAX 2048u

typedef enum {
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_VALID = 0,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_PARSE = 1,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_SEMANTIC = 2,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_MODEL = 3,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_EFFECT_CHECK = 4,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_CAPACITY = 5,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_LIR = 6,
    LATTICRA_LAT_TO_LIR_DIAGNOSTIC_INTERNAL = 7
} latticra_lat_to_lir_diagnostic_class_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_to_lir_diagnostic_class_t diagnostic_class;
    latticra_lat_to_lir_error_t lowering_error;
    latticra_lat_model_error_t model_error;
    latticra_lir_error_t lir_error;
    size_t model_declaration_count;
    size_t model_clause_count;
    size_t first_declaration_node_index;
    latticra_lat_declaration_kind_t first_declaration_kind;
    char first_declaration_name[LATTICRA_LAT_NAME_MAX];
    char first_declaration_source[LATTICRA_LAT_NAME_MAX];
    size_t first_declaration_parse_index;
    size_t first_declaration_first_clause_index;
    size_t first_declaration_clause_count;
    size_t first_declaration_source_index;
    size_t first_transition_source_index;
    size_t first_clause_node_index;
    latticra_lat_model_clause_role_t first_clause_role;
    latticra_lat_effect_t first_clause_effect;
    char first_clause_name[LATTICRA_LAT_NAME_MAX];
    char first_clause_operator[LATTICRA_LAT_NAME_MAX];
    char first_clause_value[LATTICRA_LAT_VALUE_MAX];
    size_t node_count;
    size_t edge_count;
    int lowering_failed;
    int model_failed;
    int lir_failed;
    int no_effect_issue;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    unsigned int evidence_level;
} latticra_lat_to_lir_diagnostic_result_t;

const char *latticra_lat_to_lir_diagnostic_class_label(
    latticra_lat_to_lir_diagnostic_class_t diagnostic_class);

latticra_status_t latticra_lat_to_lir_diagnostics_evaluate(
    const latticra_lat_to_lir_result_t *lowering_result,
    const latticra_lir_module_t *module,
    latticra_lat_to_lir_diagnostic_result_t *diagnostic_result);

latticra_status_t latticra_lat_to_lir_diagnostics_report(
    const latticra_lat_to_lir_diagnostic_result_t *diagnostic_result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
