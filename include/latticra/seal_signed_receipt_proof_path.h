#ifndef LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_H
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_H

#include "latticra/seal_signing_operation.h"
#include "latticra/seal_verified_receipt_promotion.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MAX 65u
#define LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK = 0,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_RECEIPT = 2,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_NOT_VERIFIED = 3,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_AUTHORITY_NOT_NEUTRAL = 4,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_SIGNING_OPERATION = 5,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SIGNING_OPERATION_NOT_METADATA_ONLY = 6,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MISMATCH = 7,
    LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH = 8
} latticra_seal_signed_receipt_proof_path_error_t;

typedef struct {
    char proof_path_profile[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX];
    char signing_operation_profile[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX];
    char signer_invocation_profile[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_ALGORITHM_MAX];
    char trust_source[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
    char verification_state[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
    char receipt_state[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
    char signing_operation_state[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
    char proof_path_state[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
    unsigned local_verify_result_present;
    unsigned receipt_promotion_present;
    unsigned signing_operation_present;
    unsigned receipt_verified;
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned signing_operation_ready;
    unsigned signing_operation_metadata_only;
    unsigned digest_matches;
    unsigned public_key_matches;
    unsigned trust_root_required;
    unsigned trust_root_verified;
    unsigned revocation_required;
    unsigned revocation_checked;
    unsigned verification_only;
    unsigned proof_path_verified;
    unsigned authority_usable;
    unsigned capability_gate_allowed;
    unsigned runtime_authority_granted;
    unsigned signature_performed;
    unsigned signer_invoked;
    unsigned private_key_handling;
    unsigned key_generation_performed;
    unsigned trust_store_loaded;
    unsigned revocation_lookup_performed;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_signed_receipt_proof_path_error_t error;
    char status[LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX];
} latticra_seal_signed_receipt_proof_path_t;

const char *latticra_seal_signed_receipt_proof_path_error_label(
    latticra_seal_signed_receipt_proof_path_error_t error);
latticra_status_t latticra_seal_signed_receipt_proof_path_from_metadata(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const latticra_seal_signing_operation_t *operation,
    latticra_seal_signed_receipt_proof_path_t *out);
int latticra_seal_signed_receipt_proof_path_is_verification_only(
    const latticra_seal_signed_receipt_proof_path_t *proof_path);
latticra_status_t latticra_seal_signed_receipt_proof_path_render(
    const latticra_seal_signed_receipt_proof_path_t *proof_path,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
