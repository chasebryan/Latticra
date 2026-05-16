#ifndef LATTICRA_L_UI_PARSER_H
#define LATTICRA_L_UI_PARSER_H

#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_L_UI_SOURCE_MAX 65536u
#define LATTICRA_L_UI_CARD_NAME_MAX 64u
#define LATTICRA_L_UI_LABEL_MAX 32u
#define LATTICRA_L_UI_PARSE_REPORT_MAX 1024u
#define LATTICRA_L_UI_DIAGNOSTIC_CODE_MAX 16u
#define LATTICRA_L_UI_DIAGNOSTIC_MESSAGE_MAX 128u
#define LATTICRA_L_UI_DIAGNOSTIC_HINT_MAX 128u
#define LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX 1280u
#define LATTICRA_L_UI_AST_RAIL_MAX 16u
#define LATTICRA_L_UI_AST_FIELD_MAX 64u
#define LATTICRA_L_UI_AST_TEXT_MAX 16u
#define LATTICRA_L_UI_AST_LABEL_MAX 64u
#define LATTICRA_L_UI_AST_BINDING_MAX 96u
#define LATTICRA_L_UI_AST_PURPOSE_MAX 128u
#define LATTICRA_L_UI_AST_REPORT_MAX 2048u
#define LATTICRA_L_UI_AST_DETAILED_REPORT_MAX 16384u
#define LATTICRA_L_UI_SEMANTIC_REPORT_MAX 2048u

typedef enum {
    LATTICRA_L_UI_PARSE_OK = 0,
    LATTICRA_L_UI_PARSE_NULL_ARGUMENT = 1,
    LATTICRA_L_UI_PARSE_EMPTY_SOURCE = 2,
    LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION = 3,
    LATTICRA_L_UI_PARSE_MISSING_CARD = 4,
    LATTICRA_L_UI_PARSE_MISSING_PURPOSE = 5,
    LATTICRA_L_UI_PARSE_MISSING_EFFECT = 6,
    LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT = 7,
    LATTICRA_L_UI_PARSE_MISSING_BOUNDARY = 8,
    LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY = 9,
    LATTICRA_L_UI_PARSE_MISSING_RAIL = 10,
    LATTICRA_L_UI_PARSE_UNKNOWN_RAIL = 11,
    LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX = 12,
    LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING = 13,
    LATTICRA_L_UI_PARSE_UNTERMINATED_STRING = 14,
    LATTICRA_L_UI_PARSE_UNBALANCED_BRACE = 15,
    LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER = 16,
    LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE = 17,
    LATTICRA_L_UI_PARSE_INTERNAL_ERROR = 18,
    LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE = 19,
    LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE = 20,
    LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE = 21,
    LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING = 22,
    LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING = 23,
    LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE = 24
} latticra_l_ui_parse_error_t;

typedef enum {
    LATTICRA_L_UI_SEMANTIC_OK = 0,
    LATTICRA_L_UI_SEMANTIC_PARSER_FAILED = 1,
    LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL = 2,
    LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL = 3,
    LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD = 4,
    LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH = 5,
    LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH = 6,
    LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET = 7,
    LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH = 8,
    LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH = 9,
    LATTICRA_L_UI_SEMANTIC_INTERNAL_ERROR = 10
} latticra_l_ui_semantic_error_t;

typedef enum {
    LATTICRA_L_UI_DIAGNOSTIC_OK = 0,
    LATTICRA_L_UI_DIAGNOSTIC_ERROR = 1,
    LATTICRA_L_UI_DIAGNOSTIC_INTERNAL = 2
} latticra_l_ui_diagnostic_severity_t;

typedef enum {
    LATTICRA_L_UI_AST_NODE_CARD = 0,
    LATTICRA_L_UI_AST_NODE_RAIL = 1,
    LATTICRA_L_UI_AST_NODE_FIELD = 2,
    LATTICRA_L_UI_AST_NODE_TEXT = 3,
    LATTICRA_L_UI_AST_NODE_BINDING = 4,
    LATTICRA_L_UI_AST_NODE_UNKNOWN = 5
} latticra_l_ui_ast_node_kind_t;

typedef struct {
    size_t start_offset;
    size_t end_offset;
    size_t start_line;
    size_t start_column;
    size_t end_line;
    size_t end_column;
} latticra_l_ui_source_span_t;

typedef struct {
    latticra_status_t status;
    latticra_l_ui_parse_error_t error;
    size_t line;
    size_t column;
    latticra_l_ui_source_span_t span;
    char card_name[LATTICRA_L_UI_CARD_NAME_MAX];
    size_t rail_count;
    size_t field_count;
    char effect[LATTICRA_L_UI_LABEL_MAX];
    char boundary[LATTICRA_L_UI_LABEL_MAX];
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_parse_result_t;

typedef struct {
    latticra_l_ui_diagnostic_severity_t severity;
    char code[LATTICRA_L_UI_DIAGNOSTIC_CODE_MAX];
    char message[LATTICRA_L_UI_DIAGNOSTIC_MESSAGE_MAX];
    char hint[LATTICRA_L_UI_DIAGNOSTIC_HINT_MAX];
    size_t line;
    size_t column;
    latticra_l_ui_source_span_t span;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_diagnostic_t;

typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    char purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
    size_t purpose_len;
    char effect[LATTICRA_L_UI_LABEL_MAX];
    char boundary[LATTICRA_L_UI_LABEL_MAX];
    latticra_l_ui_source_span_t span;
    size_t rail_count;
    size_t field_count;
    size_t text_count;
} latticra_l_ui_ast_card_t;

typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    latticra_l_ui_source_span_t span;
    size_t first_field_index;
    size_t field_count;
    size_t first_text_index;
    size_t text_count;
} latticra_l_ui_ast_rail_t;

typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    char binding[LATTICRA_L_UI_AST_BINDING_MAX];
    latticra_l_ui_source_span_t span;
    latticra_l_ui_source_span_t binding_span;
} latticra_l_ui_ast_field_t;

typedef struct {
    char value[LATTICRA_L_UI_AST_PURPOSE_MAX];
    size_t value_len;
    latticra_l_ui_source_span_t span;
} latticra_l_ui_ast_text_t;

typedef struct {
    latticra_l_ui_parse_result_t parse_result;
    latticra_l_ui_ast_card_t card;
    latticra_l_ui_ast_rail_t rails[LATTICRA_L_UI_AST_RAIL_MAX];
    latticra_l_ui_ast_field_t fields[LATTICRA_L_UI_AST_FIELD_MAX];
    latticra_l_ui_ast_text_t texts[LATTICRA_L_UI_AST_TEXT_MAX];
    size_t rail_count;
    size_t field_count;
    size_t text_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_ast_result_t;

typedef struct {
    latticra_status_t status;
    latticra_l_ui_semantic_error_t error;
    latticra_l_ui_parse_error_t parser_error;
    latticra_l_ui_source_span_t span;
    size_t rail_index;
    size_t field_index;
    size_t text_index;
    char card_name[LATTICRA_L_UI_AST_LABEL_MAX];
    char rail_name[LATTICRA_L_UI_AST_LABEL_MAX];
    char field_name[LATTICRA_L_UI_AST_LABEL_MAX];
    char binding[LATTICRA_L_UI_AST_BINDING_MAX];
    size_t rail_count;
    size_t field_count;
    size_t text_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_semantic_result_t;

const char *latticra_l_ui_parse_error_label(latticra_l_ui_parse_error_t error);
const char *latticra_l_ui_semantic_error_label(latticra_l_ui_semantic_error_t error);
const char *latticra_l_ui_diagnostic_severity_label(
    latticra_l_ui_diagnostic_severity_t severity);
const char *latticra_l_ui_ast_node_kind_label(latticra_l_ui_ast_node_kind_t kind);

latticra_status_t latticra_l_ui_parse_source(
    const char *source,
    size_t source_len,
    latticra_l_ui_parse_result_t *result);

latticra_status_t latticra_l_ui_parse_result_report(
    const latticra_l_ui_parse_result_t *result,
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_l_ui_diagnostic_from_parse_result(
    const latticra_l_ui_parse_result_t *parse_result,
    latticra_l_ui_diagnostic_t *diagnostic);

latticra_status_t latticra_l_ui_diagnostic_report(
    const latticra_l_ui_diagnostic_t *diagnostic,
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_l_ui_parse_ast(
    const char *source,
    size_t source_len,
    latticra_l_ui_ast_result_t *ast);

latticra_status_t latticra_l_ui_ast_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_l_ui_ast_detailed_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_l_ui_validate_semantics(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result);

latticra_status_t latticra_l_ui_semantic_report(
    const latticra_l_ui_semantic_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
