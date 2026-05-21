#ifndef LATTICRA_SEAL_VERIFICATION_RECEIPT_H
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_H

#include "latticra/seal_verification_policy.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX 64u
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX 128u
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX 64u
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_DIGEST_MAX 65u
#define LATTICRA_SEAL_VERIFICATION_RECEIPT_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_VERIFICATION_RECEIPT_OK = 0,
    LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT = 1,
    LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY = 2,
    LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST = 3,
    LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER = 4,
    LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY = 5
} latticra_seal_verification_receipt_error_t;

typedef struct {
    char receipt_profile[LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX];
    char verification_policy_profile[LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX];
    char signature_profile[LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX];
    char manifest_profile[LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX];
    char artifact_digest_algorithm[LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_VERIFICATION_RECEIPT_DIGEST_MAX];
    char signer_identity_label[LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX];
    char public_key_identity_label[LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX];
    char trust_source[LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX];
    char verification_state[LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX];
    char receipt_state[LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX];
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned verified;
    unsigned invalid;
    unsigned authority_usable;
    unsigned capability_gate_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_verification_receipt_error_t error;
    char status[LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX];
} latticra_seal_verification_receipt_t;

const char *latticra_seal_verification_receipt_error_label(
    latticra_seal_verification_receipt_error_t error);
latticra_status_t latticra_seal_verification_receipt_from_policy(
    const latticra_seal_verification_policy_t *policy,
    latticra_seal_verification_receipt_t *out);
int latticra_seal_verification_receipt_is_unverified_metadata(
    const latticra_seal_verification_receipt_t *receipt);
latticra_status_t latticra_seal_verification_receipt_report(
    const latticra_seal_verification_receipt_t *receipt,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
