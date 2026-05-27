#ifndef LATTICRA_SEAL_SIGNING_AUTHORIZATION_H
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_H

#include "latticra/seal_signature_request.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_DIGEST_MAX 65u
#define LATTICRA_SEAL_SIGNING_AUTHORIZATION_RENDER_MAX 8192u

typedef enum {
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK = 0,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST = 2,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST = 3,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM = 4,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST = 5,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY = 6,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY = 7,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT = 8,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT = 9,
    LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE = 10
} latticra_seal_signing_authorization_error_t;

typedef struct {
    char signing_authorization_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char signature_request_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char envelope_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_SIGNING_AUTHORIZATION_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_SIGNING_AUTHORIZATION_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char crypto_graduation_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char assurance_baseline_profile[LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX];
    char crypto_graduation_gate_state[LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX];
    char requested_capability[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_signature[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_signing_authorization[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];
    unsigned crypto_graduation_gate_present;
    unsigned crypto_graduation_gate_passed;
    unsigned standard_expectations_met;
    unsigned local_verify_graduated;
    unsigned receipt_promotion_graduated;
    unsigned authority_promotion_allowed;
    char signature_request_state[LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX];
    unsigned signature_request_ready;
    char signing_authorization_state[LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX];
    unsigned signing_authorization_ready;
    unsigned signature_performed;
    unsigned verification_performed;
    unsigned private_key_handling;
    unsigned key_generation_performed;
    unsigned trust_store_loaded;
    unsigned revocation_lookup_performed;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX];
    latticra_seal_signing_authorization_error_t error;
    char status[LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX];
} latticra_seal_signing_authorization_t;

const char *latticra_seal_signing_authorization_error_label(
    latticra_seal_signing_authorization_error_t error);
latticra_status_t latticra_seal_signing_authorization_from_request(
    const latticra_seal_signature_request_t *request,
    const char *requested_signing_authorization,
    latticra_seal_signing_authorization_t *out);
int latticra_seal_signing_authorization_is_metadata_only(
    const latticra_seal_signing_authorization_t *authorization);
latticra_status_t latticra_seal_signing_authorization_render(
    const latticra_seal_signing_authorization_t *authorization,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
