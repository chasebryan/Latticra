#ifndef LATTICRA_L_UI_PARSER_H
#define LATTICRA_L_UI_PARSER_H

#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_L_UI_SOURCE_MAX 65536u
#define LATTICRA_L_UI_CARD_NAME_MAX 64u
#define LATTICRA_L_UI_LABEL_MAX 32u
#define LATTICRA_L_UI_PARSE_REPORT_MAX 768u
#define LATTICRA_L_UI_DIAGNOSTIC_CODE_MAX 16u
#define LATTICRA_L_UI_DIAGNOSTIC_MESSAGE_MAX 128u
#define LATTICRA_L_UI_DIAGNOSTIC_HINT_MAX 128u
#define LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX 1024u

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
    LATTICRA_L_UI_PARSE_INTERNAL_ERROR = 18
} latticra_l_ui_parse_error_t;

typedef enum {
    LATTICRA_L_UI_DIAGNOSTIC_OK = 0,
    LATTICRA_L_UI_DIAGNOSTIC_ERROR = 1,
    LATTICRA_L_UI_DIAGNOSTIC_INTERNAL = 2
} latticra_l_ui_diagnostic_severity_t;

typedef struct {
    latticra_status_t status;
    latticra_l_ui_parse_error_t error;
    size_t line;
    size_t column;
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
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_diagnostic_t;

const char *latticra_l_ui_parse_error_label(latticra_l_ui_parse_error_t error);
const char *latticra_l_ui_diagnostic_severity_label(
    latticra_l_ui_diagnostic_severity_t severity);

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

#ifdef __cplusplus
}
#endif

#endif
