#ifndef LATTICRA_SEAL_PUBLIC_KEY_PARSING_H
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_H

#include "latticra/seal_key_material.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX 64u
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX 128u
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX 64u
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_DIGEST_MAX 65u
#define LATTICRA_SEAL_PUBLIC_KEY_PARSING_RENDER_MAX 8192u

typedef enum {
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK = 0,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_INPUT = 1,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL = 2,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL = 3,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING = 4,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION = 5,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION = 6,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF = 7,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION = 8,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM = 9,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING = 10,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY = 11,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE = 12,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_RUNTIME_AUTHORITY = 13,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT = 14,
    LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT = 15
} latticra_seal_public_key_parsing_error_t;

typedef struct {
    char public_key_parsing_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char key_material_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char key_handling_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char signing_operation_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char signer_invocation_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char signer_handoff_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char signing_authorization_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char signature_request_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char envelope_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_PUBLIC_KEY_PARSING_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_PUBLIC_KEY_PARSING_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_PUBLIC_KEY_PARSING_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_capability[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_signature[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_signing_authorization[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_signer_handoff[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_signer_invocation[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_signing_operation[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_key_handling[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_key_material[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_public_key_parsing[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_PUBLIC_KEY_PARSING_LABEL_MAX];
    char signing_authorization_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned signing_authorization_ready;
    char signer_handoff_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned signer_handoff_ready;
    char signer_invocation_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned signer_invocation_ready;
    char signing_operation_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned signing_operation_ready;
    char key_handling_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned key_handling_ready;
    char key_material_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned key_material_ready;
    char public_key_parsing_state[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    unsigned public_key_parsing_ready;
    unsigned signature_performed;
    unsigned verification_performed;
    unsigned signer_invoked;
    unsigned public_key_parsed;
    unsigned key_material_loaded;
    unsigned private_key_handling;
    unsigned key_generation_performed;
    unsigned hardware_key_used;
    unsigned trust_store_loaded;
    unsigned revocation_lookup_performed;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
    latticra_seal_public_key_parsing_error_t error;
    char status[LATTICRA_SEAL_PUBLIC_KEY_PARSING_STATE_MAX];
} latticra_seal_public_key_parsing_t;

const char *latticra_seal_public_key_parsing_error_label(
    latticra_seal_public_key_parsing_error_t error);
latticra_status_t latticra_seal_public_key_parsing_from_key_material(
    const latticra_seal_key_material_t *key_material,
    const char *requested_public_key_parsing,
    latticra_seal_public_key_parsing_t *out);
int latticra_seal_public_key_parsing_is_metadata_only(
    const latticra_seal_public_key_parsing_t *public_key_parsing);
latticra_status_t latticra_seal_public_key_parsing_render(
    const latticra_seal_public_key_parsing_t *public_key_parsing,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
