#ifndef LATTICRA_SEAL_SIGNING_OPERATION_H
#define LATTICRA_SEAL_SIGNING_OPERATION_H

#include "latticra/seal_signer_invocation.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNING_OPERATION_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNING_OPERATION_DIGEST_MAX 65u
#define LATTICRA_SEAL_SIGNING_OPERATION_RENDER_MAX 4096u

typedef enum {
    LATTICRA_SEAL_SIGNING_OPERATION_OK = 0,
    LATTICRA_SEAL_SIGNING_OPERATION_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION = 2,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION = 3,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF = 4,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION = 5,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM = 6,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION = 7,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY = 8,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_RUNTIME_AUTHORITY = 9,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT = 10,
    LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT = 11
} latticra_seal_signing_operation_error_t;

typedef struct {
    char signing_operation_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char signer_invocation_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char signer_handoff_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char signing_authorization_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char signature_request_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char envelope_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_SIGNING_OPERATION_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_SIGNING_OPERATION_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_capability[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_signature[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_signing_authorization[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_signer_handoff[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_signer_invocation[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_signing_operation[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];
    char signing_authorization_state[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
    unsigned signing_authorization_ready;
    char signer_handoff_state[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
    unsigned signer_handoff_ready;
    char signer_invocation_state[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
    unsigned signer_invocation_ready;
    char signing_operation_state[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
    unsigned signing_operation_ready;
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
    char mode[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
    latticra_seal_signing_operation_error_t error;
    char status[LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX];
} latticra_seal_signing_operation_t;

const char *latticra_seal_signing_operation_error_label(
    latticra_seal_signing_operation_error_t error);
latticra_status_t latticra_seal_signing_operation_from_invocation(
    const latticra_seal_signer_invocation_t *invocation,
    const char *requested_signing_operation,
    latticra_seal_signing_operation_t *out);
int latticra_seal_signing_operation_is_metadata_only(
    const latticra_seal_signing_operation_t *operation);
latticra_status_t latticra_seal_signing_operation_render(
    const latticra_seal_signing_operation_t *operation,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
