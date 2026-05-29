#ifndef LATTICRA_SEAL_STATUS_ROLLUP_H
#define LATTICRA_SEAL_STATUS_ROLLUP_H

#include "latticra/seal_runtime_handoff.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_STATUS_ROLLUP_PROFILE_MAX 64u
#define LATTICRA_SEAL_STATUS_ROLLUP_STATE_MAX 64u
#define LATTICRA_SEAL_STATUS_ROLLUP_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_STATUS_ROLLUP_OK = 0,
    LATTICRA_SEAL_STATUS_ROLLUP_INVALID_INPUT = 1,
    LATTICRA_SEAL_STATUS_ROLLUP_INVALID_HANDOFF = 2
} latticra_seal_status_rollup_error_t;

typedef struct {
    char rollup_profile[LATTICRA_SEAL_STATUS_ROLLUP_PROFILE_MAX];
    unsigned report_present;
    unsigned measurement_present;
    unsigned manifest_present;
    unsigned signature_policy_present;
    unsigned signature_metadata_present;
    unsigned verification_policy_present;
    unsigned verification_receipt_present;
    unsigned capability_gate_present;
    unsigned effect_decision_present;
    unsigned runtime_handoff_present;
    unsigned cryptographic_verification_supported;
    unsigned verified;
    unsigned capability_gate_allowed;
    unsigned effect_allowed;
    unsigned handoff_active;
    char runtime_boundary_state[LATTICRA_SEAL_STATUS_ROLLUP_STATE_MAX];
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char rollup_state[LATTICRA_SEAL_STATUS_ROLLUP_STATE_MAX];
    latticra_seal_status_rollup_error_t error;
    char status[LATTICRA_SEAL_STATUS_ROLLUP_STATE_MAX];

    /* Q-Seal / Post-Quantum posture (report-only planning surface) */
    unsigned q_seal_post_quantum_profile_planned;
    unsigned post_quantum_signature_support_planned;      /* ML-DSA etc. */
    unsigned post_quantum_key_establishment_planned;      /* ML-KEM etc. */
} latticra_seal_status_rollup_t;

const char *latticra_seal_status_rollup_error_label(
    latticra_seal_status_rollup_error_t error);
latticra_status_t latticra_seal_status_rollup_from_handoff(
    const latticra_seal_runtime_handoff_t *handoff,
    latticra_seal_status_rollup_t *out);
int latticra_seal_status_rollup_is_metadata_only(
    const latticra_seal_status_rollup_t *rollup);
latticra_status_t latticra_seal_status_rollup_report(
    const latticra_seal_status_rollup_t *rollup,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
