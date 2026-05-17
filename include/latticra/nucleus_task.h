#ifndef LATTICRA_NUCLEUS_TASK_H
#define LATTICRA_NUCLEUS_TASK_H

#include "latticra/lat_parser.h"
#include "latticra/lir.h"
#include "latticra/l_ui_renderer.h"
#include "latticra/nucleus_preview.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_NUCLEUS_TASK_ID_MAX 64u
#define LATTICRA_NUCLEUS_TASK_LABEL_MAX 64u
#define LATTICRA_NUCLEUS_TASK_REASON_MAX 128u
#define LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_NUCLEUS_TASK_REPORT_MAX 4096u
#define LATTICRA_NUCLEUS_TASK_RECORD_MAX 16u

typedef enum {
    LATTICRA_NUCLEUS_TASK_STATE_REPORT = 0,
    LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW = 1,
    LATTICRA_NUCLEUS_TASK_RENDER_REPORT = 2,
    LATTICRA_NUCLEUS_TASK_LAT_VALIDATE = 3,
    LATTICRA_NUCLEUS_TASK_LIR_VALIDATE = 4,
    LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK = 5,
    LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION = 6,
    LATTICRA_NUCLEUS_TASK_SELF_UPDATE = 7,
    LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION = 8,
    LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION = 9,
    LATTICRA_NUCLEUS_TASK_BOOT_ACTION = 10,
    LATTICRA_NUCLEUS_TASK_UNKNOWN = 11
} latticra_nucleus_task_request_kind_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_EFFECT_NONE = 0,
    LATTICRA_NUCLEUS_TASK_EFFECT_READ = 1,
    LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION = 2,
    LATTICRA_NUCLEUS_TASK_EFFECT_HOST_MUTATION = 3,
    LATTICRA_NUCLEUS_TASK_EFFECT_NETWORK = 4,
    LATTICRA_NUCLEUS_TASK_EFFECT_HARDWARE = 5,
    LATTICRA_NUCLEUS_TASK_EFFECT_BOOT = 6,
    LATTICRA_NUCLEUS_TASK_EFFECT_RECOVERY = 7,
    LATTICRA_NUCLEUS_TASK_EFFECT_EXTERNAL = 8,
    LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN = 9
} latticra_nucleus_task_effect_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW = 0,
    LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT = 1,
    LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION = 2,
    LATTICRA_NUCLEUS_TASK_POLICY_DENY = 3,
    LATTICRA_NUCLEUS_TASK_POLICY_BLOCKED = 4,
    LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE = 5,
    LATTICRA_NUCLEUS_TASK_POLICY_UNSUPPORTED = 6,
    LATTICRA_NUCLEUS_TASK_POLICY_INTERNAL_ERROR = 7
} latticra_nucleus_task_policy_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_DENIAL_OK = 0,
    LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT = 1,
    LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST = 2,
    LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT = 3,
    LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_REQUEST = 4,
    LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT = 5,
    LATTICRA_NUCLEUS_TASK_DENIAL_PARSER_FAILED = 6,
    LATTICRA_NUCLEUS_TASK_DENIAL_SEMANTIC_FAILED = 7,
    LATTICRA_NUCLEUS_TASK_DENIAL_LIR_FAILED = 8,
    LATTICRA_NUCLEUS_TASK_DENIAL_RENDER_FAILED = 9,
    LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED = 10,
    LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED = 11,
    LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE = 12,
    LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS = 13,
    LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED = 14,
    LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT = 15,
    LATTICRA_NUCLEUS_TASK_DENIAL_INTERNAL_ERROR = 16
} latticra_nucleus_task_denial_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_GATE_DISABLED = 0,
    LATTICRA_NUCLEUS_TASK_GATE_BLOCKED = 1,
    LATTICRA_NUCLEUS_TASK_GATE_PLANNED = 2,
    LATTICRA_NUCLEUS_TASK_GATE_AVAILABLE = 3,
    LATTICRA_NUCLEUS_TASK_GATE_ARMED = 4,
    LATTICRA_NUCLEUS_TASK_GATE_EXECUTED = 5,
    LATTICRA_NUCLEUS_TASK_GATE_FAILED = 6
} latticra_nucleus_task_gate_state_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE = 0,
    LATTICRA_NUCLEUS_TASK_OPERATOR_REQUIRED = 1,
    LATTICRA_NUCLEUS_TASK_OPERATOR_PRESENT = 2,
    LATTICRA_NUCLEUS_TASK_OPERATOR_REJECTED = 3,
    LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_SUPPORTED = 4
} latticra_nucleus_task_operator_confirmation_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE = 0,
    LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_AVAILABLE = 1,
    LATTICRA_NUCLEUS_TASK_ROLLBACK_REQUIRED = 2,
    LATTICRA_NUCLEUS_TASK_ROLLBACK_READY = 3,
    LATTICRA_NUCLEUS_TASK_ROLLBACK_BLOCKED = 4
} latticra_nucleus_task_rollback_state_t;

typedef struct {
    latticra_status_t status;
    char status_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
    char validator_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
    char requested_effect_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
    char denial_reason[LATTICRA_NUCLEUS_TASK_REASON_MAX];
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_nucleus_task_authority_summary_t;

typedef struct {
    char task_id[LATTICRA_NUCLEUS_TASK_ID_MAX];
    latticra_nucleus_task_request_kind_t request_kind;
    latticra_nucleus_task_effect_t requested_effect;
    latticra_nucleus_task_operator_confirmation_t operator_confirmation;
    latticra_nucleus_task_rollback_state_t rollback_state;
    const latticra_nucleus_task_authority_summary_t *authority;
    const latticra_nucleus_preview_t *preview;
    const latticra_l_ui_render_result_t *render;
    const latticra_lir_module_t *lir;
    const latticra_lat_parse_result_t *lat;
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_nucleus_task_request_t;

typedef struct {
    char task_id[LATTICRA_NUCLEUS_TASK_ID_MAX];
    latticra_nucleus_task_request_kind_t request_kind;
    latticra_nucleus_task_effect_t requested_effect;
    latticra_nucleus_task_effect_t allowed_effect;
    latticra_nucleus_task_policy_t policy;
    latticra_nucleus_task_denial_t denial;
    latticra_nucleus_task_gate_state_t gate_state;
    latticra_nucleus_task_operator_confirmation_t operator_confirmation;
    latticra_nucleus_task_rollback_state_t rollback_state;
    latticra_nucleus_task_authority_summary_t authority;
    char source_identity[LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
    int executed;
    int mutation_allowed;
    int server_interaction_allowed;
    int recovery_allowed;
    int hardware_allowed;
    unsigned int evidence_level;
} latticra_nucleus_task_record_t;

typedef struct {
    latticra_status_t status;
    latticra_nucleus_task_record_t record;
    size_t record_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_nucleus_task_result_t;

const char *latticra_nucleus_task_request_kind_label(latticra_nucleus_task_request_kind_t kind);
const char *latticra_nucleus_task_effect_label(latticra_nucleus_task_effect_t effect);
const char *latticra_nucleus_task_policy_label(latticra_nucleus_task_policy_t policy);
const char *latticra_nucleus_task_denial_label(latticra_nucleus_task_denial_t denial);
const char *latticra_nucleus_task_gate_state_label(latticra_nucleus_task_gate_state_t gate_state);
const char *latticra_nucleus_task_operator_confirmation_label(latticra_nucleus_task_operator_confirmation_t confirmation);
const char *latticra_nucleus_task_rollback_state_label(latticra_nucleus_task_rollback_state_t rollback_state);

latticra_status_t latticra_nucleus_task_classify(
    const latticra_nucleus_task_request_t *request,
    latticra_nucleus_task_result_t *result);

latticra_status_t latticra_nucleus_task_report(
    const latticra_nucleus_task_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
