#ifndef LATTICRA_RUNTIME_BOUNDARY_H
#define LATTICRA_RUNTIME_BOUNDARY_H

#include "latticra/lat_pipeline.h"
#include "latticra/nucleus_task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_RUNTIME_BOUNDARY_ID_MAX 64u
#define LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX 64u
#define LATTICRA_RUNTIME_BOUNDARY_REASON_MAX 128u
#define LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX 8192u
#define LATTICRA_RUNTIME_BOUNDARY_RECORD_MAX 16u

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY = 0,
    LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY = 1,
    LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY = 2,
    LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT = 3,
    LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT = 4,
    LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE = 5,
    LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE = 6,
    LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK = 7,
    LATTICRA_RUNTIME_BOUNDARY_RUNTIME_EXECUTE = 8,
    LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE = 9,
    LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE = 10,
    LATTICRA_RUNTIME_BOUNDARY_LIR_EXECUTE = 11,
    LATTICRA_RUNTIME_BOUNDARY_FILE_READ = 12,
    LATTICRA_RUNTIME_BOUNDARY_FILE_WRITE = 13,
    LATTICRA_RUNTIME_BOUNDARY_NETWORK_OPEN = 14,
    LATTICRA_RUNTIME_BOUNDARY_SERVER_INTERACTION = 15,
    LATTICRA_RUNTIME_BOUNDARY_SELF_UPDATE = 16,
    LATTICRA_RUNTIME_BOUNDARY_RECOVERY_ACTION = 17,
    LATTICRA_RUNTIME_BOUNDARY_ROLLBACK_ACTION = 18,
    LATTICRA_RUNTIME_BOUNDARY_HARDWARE_ACTION = 19,
    LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION = 20,
    LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE = 21,
    LATTICRA_RUNTIME_BOUNDARY_UNKNOWN = 22
} latticra_runtime_boundary_request_kind_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE = 0,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ = 1,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_LOCAL_MUTATION = 2,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_HOST_MUTATION = 3,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK = 4,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_HARDWARE = 5,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_BOOT = 6,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_RECOVERY = 7,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_EXTERNAL = 8,
    LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN = 9
} latticra_runtime_boundary_effect_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_MODE_DISABLED = 0,
    LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY = 1,
    LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY = 2,
    LATTICRA_RUNTIME_BOUNDARY_MODE_PREVIEW_ONLY = 3,
    LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY = 4,
    LATTICRA_RUNTIME_BOUNDARY_MODE_DENY_ALL = 5,
    LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE = 6
} latticra_runtime_boundary_mode_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT = 0,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION = 1,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION = 2,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW = 3,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY = 4,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_BLOCKED = 5,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE = 6,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_UNSUPPORTED = 7,
    LATTICRA_RUNTIME_BOUNDARY_POLICY_INTERNAL_ERROR = 8
} latticra_runtime_boundary_policy_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK = 0,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT = 1,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST = 2,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT = 3,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_REQUEST = 4,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_EFFECT = 5,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED = 6,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED = 7,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED = 8,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED = 9,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED = 10,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED = 11,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED = 12,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_BLOCKED = 13,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE = 14,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS = 15,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED = 16,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_IMPLEMENTATION_NOT_PRESENT = 17,
    LATTICRA_RUNTIME_BOUNDARY_DENIAL_INTERNAL_ERROR = 18
} latticra_runtime_boundary_denial_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED = 0,
    LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED = 1,
    LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED = 2,
    LATTICRA_RUNTIME_BOUNDARY_GATE_AVAILABLE = 3,
    LATTICRA_RUNTIME_BOUNDARY_GATE_ARMED = 4,
    LATTICRA_RUNTIME_BOUNDARY_GATE_EXECUTED = 5,
    LATTICRA_RUNTIME_BOUNDARY_GATE_FAILED = 6
} latticra_runtime_boundary_gate_state_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE = 0,
    LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REQUIRED = 1,
    LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT = 2,
    LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REJECTED = 3,
    LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_SUPPORTED = 4
} latticra_runtime_boundary_operator_confirmation_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE = 0,
    LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING = 1,
    LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED = 2,
    LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID = 3
} latticra_runtime_boundary_report_classification_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MEMORY = 0,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM = 1,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK = 2,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS = 3,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_DEVICE = 4,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_CLOCK = 5,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_RANDOMNESS = 6,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST = 7,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_EXTERNAL_CALL = 8,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PERSISTENCE = 9,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_SCHEDULER = 10,
    LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN = 11
} latticra_runtime_boundary_domain_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_AUTH_NOT_REQUESTED = 0,
    LATTICRA_RUNTIME_BOUNDARY_AUTH_REQUESTED = 1,
    LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED = 2,
    LATTICRA_RUNTIME_BOUNDARY_AUTH_UNAVAILABLE = 3,
    LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE = 4
} latticra_runtime_boundary_authorization_state_t;

typedef enum {
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_REPORT = 0,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION = 1,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_CLASSIFICATION = 2,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION = 3,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT = 4,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED = 5,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID = 6,
    LATTICRA_RUNTIME_BOUNDARY_MATRIX_UNSUPPORTED = 7
} latticra_runtime_boundary_policy_matrix_cell_t;

typedef struct {
    latticra_status_t status;
    char status_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
    char validator_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
    char requested_effect_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
    char denial_reason[LATTICRA_RUNTIME_BOUNDARY_REASON_MAX];
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int network_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_runtime_boundary_authority_summary_t;

typedef struct {
    char runtime_id[LATTICRA_RUNTIME_BOUNDARY_ID_MAX];
    latticra_runtime_boundary_request_kind_t request_kind;
    latticra_runtime_boundary_effect_t requested_effect;
    latticra_runtime_boundary_mode_t mode;
    latticra_runtime_boundary_operator_confirmation_t operator_confirmation;
    const latticra_runtime_boundary_authority_summary_t *authority;
    const latticra_nucleus_task_result_t *task;
    const latticra_l_ui_render_result_t *render;
    const latticra_lir_module_t *lir;
    const latticra_lat_parse_result_t *lat;
    const latticra_lat_pipeline_result_t *lat_pipeline;
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_runtime_boundary_request_t;

typedef struct {
    char runtime_id[LATTICRA_RUNTIME_BOUNDARY_ID_MAX];
    latticra_runtime_boundary_request_kind_t request_kind;
    latticra_runtime_boundary_effect_t requested_effect;
    latticra_runtime_boundary_effect_t allowed_effect;
    latticra_runtime_boundary_mode_t mode;
    latticra_runtime_boundary_policy_t policy;
    latticra_runtime_boundary_denial_t denial;
    latticra_runtime_boundary_gate_state_t gate_state;
    latticra_runtime_boundary_operator_confirmation_t operator_confirmation;
    latticra_runtime_boundary_report_classification_t report_classification;
    latticra_runtime_boundary_domain_t boundary_domain;
    latticra_runtime_boundary_authorization_state_t authorization_state;
    latticra_runtime_boundary_policy_matrix_cell_t policy_matrix_cell;
    int matrix_effect_allowed;
    int matrix_mode_allowed;
    int matrix_requires_authority;
    int matrix_requires_future_gate;
    latticra_runtime_boundary_authority_summary_t authority;
    latticra_nucleus_task_policy_t task_policy;
    latticra_nucleus_task_denial_t task_reason;
    int task_executed;
    int task_mutation_allowed;
    int task_server_interaction_allowed;
    int task_network_allowed;
    int task_recovery_allowed;
    int task_hardware_allowed;
    latticra_status_t render_status;
    latticra_l_ui_render_error_t render_error;
    latticra_status_t lat_status;
    latticra_lat_parse_error_t lat_error;
    latticra_status_t lir_status;
    latticra_lir_error_t lir_error;
    latticra_status_t lat_pipeline_status;
    latticra_lat_pipeline_error_t lat_pipeline_error;
    latticra_lat_parse_error_t lat_pipeline_parse_error;
    latticra_lat_source_span_t lat_pipeline_span;
    latticra_lat_semantic_error_t lat_pipeline_semantic_error;
    latticra_lat_model_error_t lat_pipeline_model_error;
    latticra_lat_to_lir_error_t lat_pipeline_lowering_error;
    latticra_lir_error_t lat_pipeline_lir_error;
    latticra_lat_pipeline_stage_t lat_pipeline_last_completed_stage;
    latticra_lat_pipeline_stage_t lat_pipeline_failed_stage;
    int lat_pipeline_parse_ok;
    int lat_pipeline_semantic_ok;
    int lat_pipeline_model_ok;
    int lat_pipeline_lowering_ok;
    int lat_pipeline_lir_ok;
    int lat_pipeline_no_effect_chain_ok;
    unsigned int lat_pipeline_evidence_level;
    int lat_pipeline_semantic_valid;
    char lat_pipeline_module_name[LATTICRA_LAT_NAME_MAX];
    size_t lat_pipeline_source_len;
    size_t lat_pipeline_declaration_count;
    size_t lat_pipeline_clause_count;
    size_t lat_pipeline_model_declaration_count;
    size_t lat_pipeline_model_clause_count;
    size_t lat_pipeline_first_declaration_node_index;
    latticra_lat_declaration_kind_t lat_pipeline_first_declaration_kind;
    char lat_pipeline_first_declaration_name[LATTICRA_LAT_NAME_MAX];
    char lat_pipeline_first_declaration_source[LATTICRA_LAT_NAME_MAX];
    size_t lat_pipeline_first_declaration_parse_index;
    size_t lat_pipeline_first_declaration_first_clause_index;
    size_t lat_pipeline_first_declaration_clause_count;
    size_t lat_pipeline_first_declaration_source_index;
    size_t lat_pipeline_first_transition_source_index;
    size_t lat_pipeline_first_clause_node_index;
    latticra_lat_model_clause_role_t lat_pipeline_first_clause_role;
    latticra_lat_effect_t lat_pipeline_first_clause_effect;
    char lat_pipeline_first_clause_name[LATTICRA_LAT_NAME_MAX];
    char lat_pipeline_first_clause_operator[LATTICRA_LAT_NAME_MAX];
    char lat_pipeline_first_clause_value[LATTICRA_LAT_VALUE_MAX];
    size_t lat_pipeline_node_count;
    size_t lat_pipeline_edge_count;
    size_t lat_pipeline_comment_count;
    latticra_lat_source_span_t lat_pipeline_first_comment_span;
    latticra_lir_source_kind_t lat_lir_source_kind;
    char lat_lir_module_name[LATTICRA_LIR_NAME_MAX];
    latticra_lir_report_classification_t lat_lir_report_classification;
    latticra_lir_shape_kind_t lat_lir_shape_kind;
    latticra_l_ui_source_span_t lat_lir_source_span;
    size_t lat_lir_module_node_count;
    size_t lat_lir_module_edge_count;
    size_t lat_lir_binding_count;
    size_t lat_lir_text_count;
    size_t lat_lir_lat_state_node_count;
    size_t lat_lir_lat_policy_node_count;
    size_t lat_lir_lat_transition_node_count;
    size_t lat_lir_lat_assertion_node_count;
    size_t lat_lir_lat_requirement_node_count;
    size_t lat_lir_lat_effect_declaration_node_count;
    int lat_lir_has_first_lat_node;
    size_t lat_lir_first_lat_node_index;
    latticra_lir_node_kind_t lat_lir_first_lat_node_kind;
    char lat_lir_first_lat_node_name[LATTICRA_LIR_NAME_MAX];
    char lat_lir_first_lat_node_value[LATTICRA_LIR_VALUE_MAX];
    char lat_lir_first_lat_node_operator[LATTICRA_LIR_NAME_MAX];
    char lat_lir_first_lat_node_binding[LATTICRA_LIR_BINDING_MAX];
    latticra_l_ui_source_span_t lat_lir_first_lat_node_span;
    int lat_lir_no_effect_chain_ok;
    unsigned int lat_lir_evidence_level;
    int lat_lir_no_effect;
    int lat_lir_execution_allowed;
    int lat_lir_mutation_allowed;
    int lat_lir_server_allowed;
    int lat_lir_network_allowed;
    int lat_lir_recovery_allowed;
    int lat_lir_hardware_allowed;
    size_t lat_lir_contains_edge_count;
    size_t lat_lir_binds_edge_count;
    size_t lat_lir_annotates_edge_count;
    size_t lat_lir_orders_before_edge_count;
    size_t lat_lir_transition_edge_count;
    int lat_lir_has_first_edge;
    size_t lat_lir_first_edge_index;
    size_t lat_lir_first_edge_from_index;
    size_t lat_lir_first_edge_to_index;
    latticra_lir_edge_kind_t lat_lir_first_edge_kind;
    int lat_lir_has_lat_state_nodes;
    int lat_lir_has_lat_transition_nodes;
    int lat_lir_has_transition_source_edges;
    char source_identity[LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
    int executed;
    int mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    int server_interaction_allowed;
    int recovery_allowed;
    int rollback_allowed;
    int hardware_allowed;
    int boot_allowed;
    unsigned int evidence_level;
} latticra_runtime_boundary_record_t;

typedef struct {
    latticra_status_t status;
    latticra_runtime_boundary_record_t record;
    size_t record_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    int server_allowed;
    int recovery_allowed;
    int rollback_allowed;
    int hardware_allowed;
    int boot_allowed;
} latticra_runtime_boundary_result_t;

const char *latticra_runtime_boundary_request_kind_label(latticra_runtime_boundary_request_kind_t kind);
const char *latticra_runtime_boundary_effect_label(latticra_runtime_boundary_effect_t effect);
const char *latticra_runtime_boundary_mode_label(latticra_runtime_boundary_mode_t mode);
const char *latticra_runtime_boundary_policy_label(latticra_runtime_boundary_policy_t policy);
const char *latticra_runtime_boundary_denial_label(latticra_runtime_boundary_denial_t denial);
const char *latticra_runtime_boundary_gate_state_label(latticra_runtime_boundary_gate_state_t gate_state);
const char *latticra_runtime_boundary_operator_confirmation_label(latticra_runtime_boundary_operator_confirmation_t confirmation);
const char *latticra_runtime_boundary_report_classification_label(latticra_runtime_boundary_report_classification_t classification);
const char *latticra_runtime_boundary_domain_label(latticra_runtime_boundary_domain_t domain);
const char *latticra_runtime_boundary_authorization_state_label(latticra_runtime_boundary_authorization_state_t state);
const char *latticra_runtime_boundary_policy_matrix_cell_label(latticra_runtime_boundary_policy_matrix_cell_t cell);

latticra_status_t latticra_runtime_boundary_classify(
    const latticra_runtime_boundary_request_t *request,
    latticra_runtime_boundary_result_t *result);

latticra_status_t latticra_runtime_boundary_report(
    const latticra_runtime_boundary_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
