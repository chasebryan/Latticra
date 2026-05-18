#ifndef LATTICRA_LAT_SEMANTIC_H
#define LATTICRA_LAT_SEMANTIC_H

#include "latticra/lat_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX 32u
#define LATTICRA_LAT_SEMANTIC_REPORT_MAX 4096u

typedef enum {
    LATTICRA_LAT_SEMANTIC_OK = 0,
    LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT = 1,
    LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK = 2,
    LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION = 3,
    LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE = 4,
    LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD = 5,
    LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT = 6,
    LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET = 7,
    LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE = 8,
    LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE = 9,
    LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION = 10,
    LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION = 11,
    LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION = 12,
    LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED = 13,
    LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR = 14
} latticra_lat_semantic_error_t;

typedef struct {
    latticra_lat_semantic_error_t error;
    latticra_lat_source_span_t span;
    size_t declaration_index;
    size_t clause_index;
    char name[LATTICRA_LAT_NAME_MAX];
    char detail[LATTICRA_LAT_VALUE_MAX];
} latticra_lat_semantic_diagnostic_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_semantic_error_t error;
    latticra_lat_source_span_t span;
    char module_name[LATTICRA_LAT_NAME_MAX];
    int semantic_valid;
    size_t diagnostic_count;
    latticra_lat_semantic_diagnostic_t diagnostics[LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX];
    size_t declaration_count;
    size_t state_count;
    size_t policy_count;
    size_t transition_count;
    size_t assertion_count;
    size_t effect_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_lat_semantic_result_t;

const char *latticra_lat_semantic_error_label(latticra_lat_semantic_error_t error);

latticra_status_t latticra_lat_validate_module(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result);

latticra_status_t latticra_lat_semantic_report(
    const latticra_lat_semantic_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
