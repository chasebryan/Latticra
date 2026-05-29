#ifndef LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_H
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_H

#include "latticra/seal_runtime_handoff_evaluation.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX 128u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX 64u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DIGEST_MAX 65u
#define LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_RENDER_MAX 8192u

typedef enum {
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK = 0,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT = 1,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_EVALUATION = 2,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_EVALUATION = 3,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF = 4,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_REPORT = 5,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT = 6,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_UNKNOWN_REPORT = 7,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_RUNTIME_AUTHORITY = 8,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT = 9,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_NETWORK_EFFECT = 10,
    LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE = 11
} latticra_seal_runtime_handoff_report_error_t;

typedef struct {
    char report_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
    char crypto_graduation_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char assurance_baseline_profile[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX];
    char crypto_graduation_gate_state[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
    char requested_capability[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX];
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
    char gate_state[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
    char decision_state[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
    unsigned effect_allowed;
    char handoff_state[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
    unsigned handoff_eligible;
    char report_state[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
    unsigned report_ready;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_runtime_handoff_report_error_t error;
    char status[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX];
} latticra_seal_runtime_handoff_report_t;

const char *latticra_seal_runtime_handoff_report_error_label(
    latticra_seal_runtime_handoff_report_error_t error);
latticra_status_t latticra_seal_runtime_handoff_report_from_evaluation(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    const char *requested_report,
    latticra_seal_runtime_handoff_report_t *out);
int latticra_seal_runtime_handoff_report_is_metadata_only(
    const latticra_seal_runtime_handoff_report_t *report);
latticra_status_t latticra_seal_runtime_handoff_report_render(
    const latticra_seal_runtime_handoff_report_t *report,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
