#ifndef LATTICRA_SEAL_RUNTIME_GATE_H
#define LATTICRA_SEAL_RUNTIME_GATE_H

#include "latticra/seal_policy_decision.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_RUNTIME_GATE_PROFILE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_GATE_ID_MAX 64u
#define LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_GATE_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_RUNTIME_GATE_OK = 0,
    LATTICRA_SEAL_RUNTIME_GATE_INVALID_INPUT = 1,
    LATTICRA_SEAL_RUNTIME_GATE_INVALID_POLICY_DECISION = 2
} latticra_seal_runtime_gate_error_t;

typedef struct {
    char runtime_enforcement_gate_profile[LATTICRA_SEAL_RUNTIME_GATE_PROFILE_MAX];
    char gate_id[LATTICRA_SEAL_RUNTIME_GATE_ID_MAX];
    char gate_version[LATTICRA_SEAL_RUNTIME_GATE_ID_MAX];
    char gate_state[LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX];
    unsigned runtime_enforcement_gate_supported;
    unsigned runtime_enforcement_supported;
    unsigned runtime_enforcement_active;
    unsigned policy_decision_input_supported;
    unsigned policy_decision_consumed;
    unsigned gate_id_present;
    unsigned gate_version_present;
    unsigned runtime_handoff_eligible;
    unsigned runtime_handoff_performed;
    unsigned allow_enforcement_supported;
    unsigned deny_enforcement_supported;
    unsigned allow_enforcement_performed;
    unsigned deny_enforcement_performed;
    unsigned effect_performed;
    unsigned default_blocked;
    unsigned operator_review_required;
    unsigned unknown_tool_blocked;
    unsigned unsigned_request_blocked;
    unsigned invalid_schema_blocked;
    unsigned stale_request_blocked;
    unsigned replayed_request_blocked;
    unsigned invalid_signature_blocked;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX];
    char decision[LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX];
    char reason[LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX];
    latticra_seal_runtime_gate_error_t error;
    char status[LATTICRA_SEAL_RUNTIME_GATE_STATE_MAX];
} latticra_seal_runtime_gate_t;

const char *latticra_seal_runtime_gate_error_label(
    latticra_seal_runtime_gate_error_t error);
latticra_status_t latticra_seal_runtime_gate_from_policy_decision(
    const latticra_seal_policy_decision_t *policy_decision,
    latticra_seal_runtime_gate_t *out);
int latticra_seal_runtime_gate_is_report_only(
    const latticra_seal_runtime_gate_t *gate);
latticra_status_t latticra_seal_runtime_gate_report(
    const latticra_seal_runtime_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
