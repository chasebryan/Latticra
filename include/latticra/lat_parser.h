#ifndef LATTICRA_LAT_PARSER_H
#define LATTICRA_LAT_PARSER_H

#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LAT_SOURCE_MAX 65536u
#define LATTICRA_LAT_NAME_MAX 64u
#define LATTICRA_LAT_VALUE_MAX 128u
#define LATTICRA_LAT_DECLARATION_MAX 64u
#define LATTICRA_LAT_CLAUSE_MAX 128u
#define LATTICRA_LAT_REPORT_MAX 4096u

typedef enum {
    LATTICRA_LAT_PARSE_OK = 0,
    LATTICRA_LAT_PARSE_NULL_ARGUMENT = 1,
    LATTICRA_LAT_PARSE_EMPTY_SOURCE = 2,
    LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE = 3,
    LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM = 4,
    LATTICRA_LAT_PARSE_MISSING_MODULE = 5,
    LATTICRA_LAT_PARSE_INVALID_MODULE_NAME = 6,
    LATTICRA_LAT_PARSE_UNBALANCED_BRACE = 7,
    LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION = 8,
    LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME = 9,
    LATTICRA_LAT_PARSE_UNTERMINATED_STRING = 10,
    LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE = 11,
    LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE = 12,
    LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING = 13,
    LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED = 14,
    LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER = 15,
    LATTICRA_LAT_PARSE_INTERNAL_ERROR = 16,
    LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT = 17,
    LATTICRA_LAT_PARSE_TRAILING_CONTENT = 18
} latticra_lat_parse_error_t;

typedef enum {
    LATTICRA_LAT_DECLARATION_STATE = 0,
    LATTICRA_LAT_DECLARATION_POLICY = 1,
    LATTICRA_LAT_DECLARATION_TRANSITION = 2,
    LATTICRA_LAT_DECLARATION_ASSERTION = 3,
    LATTICRA_LAT_DECLARATION_EFFECT = 4,
    LATTICRA_LAT_DECLARATION_UNKNOWN = 5
} latticra_lat_declaration_kind_t;

typedef enum {
    LATTICRA_LAT_EFFECT_NONE = 0,
    LATTICRA_LAT_EFFECT_READ = 1,
    LATTICRA_LAT_EFFECT_LOCAL_MUTATION = 2,
    LATTICRA_LAT_EFFECT_HOST_MUTATION = 3,
    LATTICRA_LAT_EFFECT_NETWORK = 4,
    LATTICRA_LAT_EFFECT_HARDWARE = 5,
    LATTICRA_LAT_EFFECT_BOOT = 6,
    LATTICRA_LAT_EFFECT_RECOVERY = 7,
    LATTICRA_LAT_EFFECT_EXTERNAL = 8,
    LATTICRA_LAT_EFFECT_UNKNOWN = 9
} latticra_lat_effect_t;

typedef struct {
    size_t start_offset;
    size_t end_offset;
    size_t start_line;
    size_t start_column;
    size_t end_line;
    size_t end_column;
} latticra_lat_source_span_t;

typedef struct {
    char module_name[LATTICRA_LAT_NAME_MAX];
    latticra_lat_source_span_t span;
    size_t declaration_count;
    size_t state_count;
    size_t policy_count;
    size_t transition_count;
    size_t assertion_count;
    size_t effect_count;
} latticra_lat_ast_module_t;

typedef struct {
    latticra_lat_declaration_kind_t kind;
    char name[LATTICRA_LAT_NAME_MAX];
    char source_name[LATTICRA_LAT_NAME_MAX];
    latticra_lat_source_span_t span;
    size_t first_clause_index;
    size_t clause_count;
} latticra_lat_ast_declaration_t;

typedef struct {
    char keyword[LATTICRA_LAT_NAME_MAX];
    char left[LATTICRA_LAT_NAME_MAX];
    char operator_text[LATTICRA_LAT_NAME_MAX];
    char right[LATTICRA_LAT_VALUE_MAX];
    latticra_lat_effect_t effect;
    latticra_lat_source_span_t span;
} latticra_lat_ast_clause_t;

typedef struct {
    latticra_status_t status;
    latticra_lat_parse_error_t error;
    latticra_lat_source_span_t span;
    latticra_lat_ast_module_t module;
    latticra_lat_ast_declaration_t declarations[LATTICRA_LAT_DECLARATION_MAX];
    latticra_lat_ast_clause_t clauses[LATTICRA_LAT_CLAUSE_MAX];
    size_t declaration_count;
    size_t clause_count;
    size_t comment_count;
    latticra_lat_source_span_t first_comment_span;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int network_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_lat_parse_result_t;

const char *latticra_lat_parse_error_label(latticra_lat_parse_error_t error);
const char *latticra_lat_declaration_kind_label(latticra_lat_declaration_kind_t kind);
const char *latticra_lat_effect_label(latticra_lat_effect_t effect);

latticra_status_t latticra_lat_parse_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *result);

latticra_status_t latticra_lat_parse_report(
    const latticra_lat_parse_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
