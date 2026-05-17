#ifndef LATTICRA_L_UI_RENDERER_H
#define LATTICRA_L_UI_RENDERER_H

#include "latticra/lir.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_L_UI_RENDER_LABEL_MAX 64u
#define LATTICRA_L_UI_RENDER_REASON_MAX 128u
#define LATTICRA_L_UI_RENDER_REPORT_MAX 16384u
#define LATTICRA_L_UI_RENDER_LINE_MAX 512u
#define LATTICRA_L_UI_RENDER_SECTION_MAX 16u
#define LATTICRA_L_UI_RENDER_AUTHORITY_REPORT_MAX 4096u

typedef enum {
    LATTICRA_L_UI_RENDER_OK = 0,
    LATTICRA_L_UI_RENDER_NULL_ARGUMENT = 1,
    LATTICRA_L_UI_RENDER_INVALID_INPUT = 2,
    LATTICRA_L_UI_RENDER_PARSER_FAILED = 3,
    LATTICRA_L_UI_RENDER_SEMANTIC_FAILED = 4,
    LATTICRA_L_UI_RENDER_LIR_FAILED = 5,
    LATTICRA_L_UI_RENDER_AUTHORITY_FAILED = 6,
    LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED = 7,
    LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE = 8,
    LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT = 9,
    LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY = 10,
    LATTICRA_L_UI_RENDER_INTERNAL_ERROR = 11
} latticra_l_ui_render_error_t;

typedef enum {
    LATTICRA_L_UI_RENDER_MODE_SUMMARY = 0,
    LATTICRA_L_UI_RENDER_MODE_DETAILED = 1,
    LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY = 2,
    LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY = 3
} latticra_l_ui_render_mode_t;

typedef struct {
    latticra_status_t status;
    char status_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
    char validator_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
    char requested_effect_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
    char denial_reason[LATTICRA_L_UI_RENDER_REASON_MAX];
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_render_authority_summary_t;

typedef struct {
    latticra_l_ui_render_mode_t mode;
    const latticra_l_ui_ast_result_t *ast;
    const latticra_l_ui_semantic_result_t *semantic;
    const latticra_lir_module_t *lir;
    const latticra_l_ui_render_authority_summary_t *authority;
} latticra_l_ui_render_request_t;

typedef struct {
    latticra_status_t status;
    latticra_l_ui_render_error_t error;
    latticra_l_ui_render_mode_t mode;
    char card_name[LATTICRA_L_UI_RENDER_LABEL_MAX];
    char effect[LATTICRA_L_UI_RENDER_LABEL_MAX];
    char boundary[LATTICRA_L_UI_RENDER_LABEL_MAX];
    size_t rail_count;
    size_t field_count;
    size_t text_count;
    size_t binding_count;
    size_t node_count;
    size_t edge_count;
    size_t section_count;
    latticra_l_ui_source_span_t span;
    latticra_l_ui_render_authority_summary_t authority;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_render_result_t;

const char *latticra_l_ui_render_error_label(latticra_l_ui_render_error_t error);
const char *latticra_l_ui_render_mode_label(latticra_l_ui_render_mode_t mode);

latticra_status_t latticra_l_ui_render(
    const latticra_l_ui_render_request_t *request,
    latticra_l_ui_render_result_t *result);

latticra_status_t latticra_l_ui_render_report(
    const latticra_l_ui_render_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
