#ifndef LATTICRA_LAT_MODEL_H
#define LATTICRA_LAT_MODEL_H

#include "latticra/lat_semantic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_MODEL_REPORT_MAX 4096u
#define LATTICRA_LAT_MODEL_NO_INDEX ((size_t)-1)

typedef enum {
    LATTICRA_LAT_MODEL_OK = 0,
    LATTICRA_LAT_MODEL_NULL_ARGUMENT = 1,
    LATTICRA_LAT_MODEL_PARSE_NOT_OK = 2,
    LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK = 3,
    LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID = 4,
    LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION = 5,
    LATTICRA_LAT_MODEL_CAPACITY_EXCEEDED = 6,
    LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION = 7,
    LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE = 8,
    LATTICRA_LAT_MODEL_INTERNAL_ERROR = 9
} latticra_lat_model_error_t;

typedef enum {
    LATTICRA_LAT_MODEL_CLAUSE_FIELD = 0,
    LATTICRA_LAT_MODEL_CLAUSE_REQUIRE = 1,
    LATTICRA_LAT_MODEL_CLAUSE_ENSURE = 2,
    LATTICRA_LAT_MODEL_CLAUSE_EFFECT = 3,
    LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN = 4
} latticra_lat_model_clause_role_t;

typedef struct {
    latticra_lat_declaration_kind_t kind;
    char name[LATTICRA_LAT_NAME_MAX];
    char source_name[LATTICRA_LAT_NAME_MAX];
    size_t parse_declaration_index;
    size_t first_clause_index;
    size_t clause_count;
    size_t source_declaration_index;
    latticra_lat_source_span_t span;
} latticra_lat_model_declaration_t;

typedef struct {
    latticra_lat_model_clause_role_t role;
    latticra_lat_declaration_kind_t owner_kind;
    size_t owner_declaration_index;
    char name[LATTICRA_LAT_NAME_MAX];
    char operator_text[LATTICRA_LAT_NAME_MAX];
    char value[LATTICRA_LAT_VALUE_MAX];
    latticra_lat_effect_t effect;
    latticra_lat_source_span_t span;
} latticra_lat_model_clause_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_model_error_t error;
    latticra_lat_source_span_t span;
    char module_name[LATTICRA_LAT_NAME_MAX];
    latticra_lat_model_declaration_t declarations[LATTICRA_LAT_DECLARATION_MAX];
    latticra_lat_model_clause_t clauses[LATTICRA_LAT_CLAUSE_MAX];
    size_t state_indices[LATTICRA_LAT_DECLARATION_MAX];
    size_t policy_indices[LATTICRA_LAT_DECLARATION_MAX];
    size_t transition_indices[LATTICRA_LAT_DECLARATION_MAX];
    size_t assertion_indices[LATTICRA_LAT_DECLARATION_MAX];
    size_t effect_indices[LATTICRA_LAT_DECLARATION_MAX];
    size_t declaration_count;
    size_t clause_count;
    size_t state_count;
    size_t policy_count;
    size_t transition_count;
    size_t assertion_count;
    size_t effect_count;
    size_t first_state_index;
    size_t first_policy_index;
    size_t first_transition_index;
    size_t first_assertion_index;
    size_t first_effect_index;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_lat_model_t;

const char *latticra_lat_model_error_label(latticra_lat_model_error_t error);
const char *latticra_lat_model_clause_role_label(latticra_lat_model_clause_role_t role);

latticra_status_t latticra_lat_model_normalize_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_model_t *model);

latticra_status_t latticra_lat_model_report(
    const latticra_lat_model_t *model,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
