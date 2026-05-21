#ifndef LATTICRA_SEAL_EFFECT_DECISION_H
#define LATTICRA_SEAL_EFFECT_DECISION_H

#include "latticra/seal_capability_gate.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX 64u
#define LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX 128u
#define LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX 64u
#define LATTICRA_SEAL_EFFECT_DECISION_DIGEST_MAX 65u
#define LATTICRA_SEAL_EFFECT_DECISION_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_EFFECT_DECISION_OK = 0,
    LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT = 1,
    LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE = 2,
    LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST = 3,
    LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY = 4,
    LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT = 5
} latticra_seal_effect_decision_error_t;

typedef struct {
    char decision_profile[LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX];
    char artifact_digest_algorithm[LATTICRA_SEAL_CAPABILITY_GATE_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_EFFECT_DECISION_DIGEST_MAX];
    char requested_capability[LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX];
    char gate_state[LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX];
    char decision_state[LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX];
    unsigned gate_allowed;
    unsigned effect_allowed;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    unsigned runtime_authority_granted;
    latticra_seal_effect_decision_error_t error;
    char status[LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX];
} latticra_seal_effect_decision_t;

const char *latticra_seal_effect_decision_error_label(
    latticra_seal_effect_decision_error_t error);
latticra_status_t latticra_seal_effect_decision_from_gate(
    const latticra_seal_capability_gate_t *gate,
    latticra_seal_effect_decision_t *out);
int latticra_seal_effect_decision_is_denied_metadata(
    const latticra_seal_effect_decision_t *decision);
latticra_status_t latticra_seal_effect_decision_report(
    const latticra_seal_effect_decision_t *decision,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
