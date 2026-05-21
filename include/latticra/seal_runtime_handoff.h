#ifndef LATTICRA_SEAL_RUNTIME_HANDOFF_H
#define LATTICRA_SEAL_RUNTIME_HANDOFF_H

#include "latticra/seal_effect_decision.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_RUNTIME_HANDOFF_PROFILE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_LABEL_MAX 128u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_STATE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_RUNTIME_HANDOFF_OK = 0,
    LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_INPUT = 1,
    LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_DECISION = 2,
    LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_CAPABILITY = 3,
    LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_EFFECT = 4
} latticra_seal_runtime_handoff_error_t;

typedef struct {
    char handoff_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_PROFILE_MAX];
    char requested_capability[LATTICRA_SEAL_RUNTIME_HANDOFF_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_RUNTIME_HANDOFF_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_RUNTIME_HANDOFF_LABEL_MAX];
    char decision_state[LATTICRA_SEAL_RUNTIME_HANDOFF_STATE_MAX];
    unsigned effect_allowed;
    unsigned effect_performed;
    char runtime_boundary_state[LATTICRA_SEAL_RUNTIME_HANDOFF_STATE_MAX];
    char runtime_request_label[LATTICRA_SEAL_RUNTIME_HANDOFF_LABEL_MAX];
    unsigned handoff_active;
    unsigned runtime_effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    unsigned runtime_authority_granted;
    char handoff_state[LATTICRA_SEAL_RUNTIME_HANDOFF_STATE_MAX];
    latticra_seal_runtime_handoff_error_t error;
    char status[LATTICRA_SEAL_RUNTIME_HANDOFF_STATE_MAX];
} latticra_seal_runtime_handoff_t;

const char *latticra_seal_runtime_handoff_error_label(
    latticra_seal_runtime_handoff_error_t error);
latticra_status_t latticra_seal_runtime_handoff_from_decision(
    const latticra_seal_effect_decision_t *decision,
    const char *runtime_request_label,
    latticra_seal_runtime_handoff_t *out);
int latticra_seal_runtime_handoff_is_inactive_metadata(
    const latticra_seal_runtime_handoff_t *handoff);
latticra_status_t latticra_seal_runtime_handoff_report(
    const latticra_seal_runtime_handoff_t *handoff,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
