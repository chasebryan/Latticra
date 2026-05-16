#ifndef LATTICRA_LIR_H
#define LATTICRA_LIR_H

#include "latticra/l_ui_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_LIR_NAME_MAX 64u
#define LATTICRA_LIR_VALUE_MAX 128u
#define LATTICRA_LIR_BINDING_MAX 96u
#define LATTICRA_LIR_NODE_MAX 96u
#define LATTICRA_LIR_EDGE_MAX 128u
#define LATTICRA_LIR_BINDING_REF_MAX 32u
#define LATTICRA_LIR_TEXT_MAX 16u
#define LATTICRA_LIR_REPORT_MAX 8192u

typedef enum {
    LATTICRA_LIR_SOURCE_UNKNOWN = 0,
    LATTICRA_LIR_SOURCE_L_UI_CARD = 1,
    LATTICRA_LIR_SOURCE_LAT_MODULE = 2,
    LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE = 3
} latticra_lir_source_kind_t;

typedef enum {
    LATTICRA_LIR_NODE_MODULE = 0,
    LATTICRA_LIR_NODE_CARD = 1,
    LATTICRA_LIR_NODE_RAIL = 2,
    LATTICRA_LIR_NODE_FIELD = 3,
    LATTICRA_LIR_NODE_TEXT = 4,
    LATTICRA_LIR_NODE_BINDING = 5,
    LATTICRA_LIR_NODE_EFFECT = 6,
    LATTICRA_LIR_NODE_BOUNDARY = 7,
    LATTICRA_LIR_NODE_UNKNOWN = 8
} latticra_lir_node_kind_t;

typedef enum {
    LATTICRA_LIR_EDGE_CONTAINS = 0,
    LATTICRA_LIR_EDGE_BINDS = 1,
    LATTICRA_LIR_EDGE_ANNOTATES = 2,
    LATTICRA_LIR_EDGE_ORDERS_BEFORE = 3,
    LATTICRA_LIR_EDGE_UNKNOWN = 4
} latticra_lir_edge_kind_t;

typedef enum {
    LATTICRA_LIR_BINDING_STATE_VALUE = 0,
    LATTICRA_LIR_BINDING_PREVIEW_VALUE = 1,
    LATTICRA_LIR_BINDING_UNSUPPORTED = 2
} latticra_lir_resolved_binding_kind_t;

typedef enum {
    LATTICRA_LIR_OK = 0,
    LATTICRA_LIR_NULL_ARGUMENT = 1,
    LATTICRA_LIR_SEMANTIC_FAILED = 2,
    LATTICRA_LIR_CAPACITY_EXCEEDED = 3,
    LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND = 4,
    LATTICRA_LIR_UNSUPPORTED_NODE_KIND = 5,
    LATTICRA_LIR_UNSUPPORTED_EFFECT = 6,
    LATTICRA_LIR_UNSUPPORTED_BOUNDARY = 7,
    LATTICRA_LIR_INTERNAL_ERROR = 8
} latticra_lir_error_t;

typedef struct {
    latticra_lir_node_kind_t kind;
    char name[LATTICRA_LIR_NAME_MAX];
    char value[LATTICRA_LIR_VALUE_MAX];
    char binding[LATTICRA_LIR_BINDING_MAX];
    latticra_l_ui_source_span_t source_span;
    size_t parent_index;
    size_t first_child_index;
    size_t child_count;
    unsigned int flags;
} latticra_lir_node_t;

typedef struct {
    size_t from_index;
    size_t to_index;
    latticra_lir_edge_kind_t edge_kind;
    latticra_l_ui_source_span_t source_span;
} latticra_lir_edge_t;

typedef struct {
    size_t field_node_index;
    char binding_target[LATTICRA_LIR_BINDING_MAX];
    char binding_prefix[LATTICRA_LIR_NAME_MAX];
    latticra_l_ui_source_span_t source_span;
    latticra_lir_resolved_binding_kind_t resolved_kind;
} latticra_lir_binding_ref_t;

typedef struct {
    size_t text_node_index;
    char value[LATTICRA_LIR_VALUE_MAX];
    size_t value_len;
    char escaped_value[LATTICRA_LIR_VALUE_MAX];
    latticra_l_ui_source_span_t source_span;
} latticra_lir_text_ref_t;

typedef struct {
    latticra_status_t status;
    latticra_lir_error_t error;
    latticra_lir_source_kind_t source_kind;
    char module_name[LATTICRA_LIR_NAME_MAX];
    char card_name[LATTICRA_LIR_NAME_MAX];
    char effect[LATTICRA_LIR_NAME_MAX];
    char boundary[LATTICRA_LIR_NAME_MAX];
    latticra_l_ui_source_span_t source_span;
    latticra_lir_node_t nodes[LATTICRA_LIR_NODE_MAX];
    latticra_lir_edge_t edges[LATTICRA_LIR_EDGE_MAX];
    latticra_lir_binding_ref_t bindings[LATTICRA_LIR_BINDING_REF_MAX];
    latticra_lir_text_ref_t texts[LATTICRA_LIR_TEXT_MAX];
    size_t node_count;
    size_t edge_count;
    size_t binding_count;
    size_t text_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_lir_module_t;

const char *latticra_lir_error_label(latticra_lir_error_t error);
const char *latticra_lir_source_kind_label(latticra_lir_source_kind_t kind);
const char *latticra_lir_node_kind_label(latticra_lir_node_kind_t kind);
const char *latticra_lir_edge_kind_label(latticra_lir_edge_kind_t kind);
const char *latticra_lir_resolved_binding_kind_label(latticra_lir_resolved_binding_kind_t kind);

latticra_status_t latticra_lir_lower_l_ui_ast(
    const latticra_l_ui_ast_result_t *ast,
    const latticra_l_ui_semantic_result_t *semantic,
    latticra_lir_module_t *module);

latticra_status_t latticra_lir_report(
    const latticra_lir_module_t *module,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
