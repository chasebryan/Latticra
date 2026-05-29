#ifndef LATTICRA_SEAL_SIGNATURE_REQUEST_H
#define LATTICRA_SEAL_SIGNATURE_REQUEST_H

#include "latticra/seal_report_envelope.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNATURE_REQUEST_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_REQUEST_DIGEST_MAX 65u
#define LATTICRA_SEAL_SIGNATURE_REQUEST_RENDER_MAX 8192u

typedef enum {
    LATTICRA_SEAL_SIGNATURE_REQUEST_OK = 0,
    LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE = 2,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE = 3,
    LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE = 4,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE = 5,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY = 6,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT = 7,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT = 8,
    LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE = 9
} latticra_seal_signature_request_error_t;

typedef struct {
    char signature_request_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char envelope_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_SIGNATURE_REQUEST_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_SIGNATURE_REQUEST_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char crypto_graduation_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char assurance_baseline_profile[LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX];
    char crypto_graduation_gate_state[LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX];
    char requested_capability[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_signature[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX];
    unsigned crypto_graduation_gate_present;
    unsigned crypto_graduation_gate_passed;
    unsigned standard_expectations_met;
    unsigned local_verify_graduated;
    unsigned receipt_promotion_graduated;
    unsigned authority_promotion_allowed;
    char envelope_state[LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX];
    unsigned envelope_ready;
    char signature_request_state[LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX];
    unsigned signature_request_ready;
    unsigned signature_performed;
    unsigned verification_performed;
    unsigned private_key_handling;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_signature_request_error_t error;
    char status[LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX];
} latticra_seal_signature_request_t;

const char *latticra_seal_signature_request_error_label(
    latticra_seal_signature_request_error_t error);
latticra_status_t latticra_seal_signature_request_from_envelope(
    const latticra_seal_report_envelope_t *envelope,
    const char *requested_signature,
    latticra_seal_signature_request_t *out);
int latticra_seal_signature_request_is_metadata_only(
    const latticra_seal_signature_request_t *request);
latticra_status_t latticra_seal_signature_request_render(
    const latticra_seal_signature_request_t *request,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
