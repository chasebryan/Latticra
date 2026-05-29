#ifndef LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_H
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_H

#include "latticra/seal_verified_effect_decision.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX 128u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DIGEST_MAX 65u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK = 0,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT = 1,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION = 2,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION = 3,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT = 4,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF = 5,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF = 6,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY = 7,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT = 8,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT = 9,
    LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE = 10
} latticra_seal_runtime_handoff_evaluation_error_t;

typedef struct {
    char handoff_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX];
    char crypto_graduation_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char assurance_baseline_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX];
    char crypto_graduation_gate_state[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX];
    char requested_capability[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX];
    unsigned crypto_graduation_gate_present;
    unsigned crypto_graduation_gate_passed;
    unsigned standard_expectations_met;
    unsigned local_verify_graduated;
    unsigned receipt_promotion_graduated;
    unsigned authority_promotion_allowed;
    unsigned verified;
    unsigned authority_usable;
    unsigned receipt_capability_gate_allowed;
    unsigned gate_allowed;
    char gate_state[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX];
    char decision_state[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX];
    unsigned effect_allowed;
    char handoff_state[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX];
    unsigned handoff_eligible;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_runtime_handoff_evaluation_error_t error;
    char status[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX];
} latticra_seal_runtime_handoff_evaluation_t;

const char *latticra_seal_runtime_handoff_evaluation_error_label(
    latticra_seal_runtime_handoff_evaluation_error_t error);
latticra_status_t latticra_seal_runtime_handoff_evaluation_from_decision(
    const latticra_seal_verified_effect_decision_t *decision,
    const char *requested_handoff,
    latticra_seal_runtime_handoff_evaluation_t *out);
int latticra_seal_runtime_handoff_evaluation_is_metadata_only(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation);
latticra_status_t latticra_seal_runtime_handoff_evaluation_report(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
