#ifndef LATTICRA_SEAL_SIGNER_HANDOFF_H
#define LATTICRA_SEAL_SIGNER_HANDOFF_H

#include "latticra/seal_signing_authorization.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNER_HANDOFF_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNER_HANDOFF_DIGEST_MAX 65u
#define LATTICRA_SEAL_SIGNER_HANDOFF_RENDER_MAX 4096u

typedef enum {
    LATTICRA_SEAL_SIGNER_HANDOFF_OK = 0,
    LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION = 2,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION = 3,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM = 4,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF = 5,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY = 6,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_RUNTIME_AUTHORITY = 7,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT = 8,
    LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT = 9
} latticra_seal_signer_handoff_error_t;

typedef struct {
    char signer_handoff_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char signing_authorization_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char signature_request_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char envelope_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_SIGNER_HANDOFF_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_SIGNER_HANDOFF_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_capability[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_signature[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_signing_authorization[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_signer_handoff[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX];
    char signature_request_state[LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX];
    unsigned signature_request_ready;
    char signing_authorization_state[LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX];
    unsigned signing_authorization_ready;
    char signer_handoff_state[LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX];
    unsigned signer_handoff_ready;
    unsigned signature_performed;
    unsigned verification_performed;
    unsigned signer_invoked;
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
    char mode[LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX];
    latticra_seal_signer_handoff_error_t error;
    char status[LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX];
} latticra_seal_signer_handoff_t;

const char *latticra_seal_signer_handoff_error_label(
    latticra_seal_signer_handoff_error_t error);
latticra_status_t latticra_seal_signer_handoff_from_authorization(
    const latticra_seal_signing_authorization_t *authorization,
    const char *requested_signer_handoff,
    latticra_seal_signer_handoff_t *out);
int latticra_seal_signer_handoff_is_metadata_only(
    const latticra_seal_signer_handoff_t *handoff);
latticra_status_t latticra_seal_signer_handoff_render(
    const latticra_seal_signer_handoff_t *handoff,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
