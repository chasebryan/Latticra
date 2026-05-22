#ifndef LATTICRA_SEAL_RUNTIME_DRY_RUN_H
#define LATTICRA_SEAL_RUNTIME_DRY_RUN_H

#include "latticra/seal_runtime_gate.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_RUNTIME_DRY_RUN_PROFILE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_DRY_RUN_REASON_MAX 96u
#define LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_RUNTIME_DRY_RUN_OK = 0,
    LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT = 1,
    LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION = 2,
    LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE = 3
} latticra_seal_runtime_dry_run_error_t;

typedef struct {
    char runtime_dry_run_profile[LATTICRA_SEAL_RUNTIME_DRY_RUN_PROFILE_MAX];
    char request_class[LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX];
    char policy_decision_state[LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX];
    char runtime_gate_state[LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_RUNTIME_DRY_RUN_REASON_MAX];
    char status[LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX];
    unsigned dry_run_supported;
    unsigned dry_run_performed;
    unsigned input_policy_decision_present;
    unsigned input_runtime_gate_present;
    unsigned policy_decision_report_only;
    unsigned runtime_gate_report_only;
    unsigned default_action_deny;
    unsigned would_allow;
    unsigned would_deny;
    unsigned would_require_operator_review;
    unsigned would_execute_tool;
    unsigned would_read_host;
    unsigned would_write_host;
    unsigned would_use_network;
    unsigned would_grant_runtime_authority;
    unsigned unknown_tool_denied;
    unsigned unsigned_request_denied;
    unsigned invalid_schema_denied;
    unsigned stale_request_denied;
    unsigned replayed_request_denied;
    unsigned invalid_signature_denied;
    unsigned report_only;
    char mode[LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX];
    latticra_seal_runtime_dry_run_error_t error;
} latticra_seal_runtime_dry_run_t;

const char *latticra_seal_runtime_dry_run_error_label(
    latticra_seal_runtime_dry_run_error_t error);
latticra_status_t latticra_seal_runtime_dry_run_from_policy_and_gate(
    const latticra_seal_policy_decision_t *policy_decision,
    const latticra_seal_runtime_gate_t *runtime_gate,
    latticra_seal_runtime_dry_run_t *out);
int latticra_seal_runtime_dry_run_is_report_only(
    const latticra_seal_runtime_dry_run_t *dry_run);
latticra_status_t latticra_seal_runtime_dry_run_report(
    const latticra_seal_runtime_dry_run_t *dry_run,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
