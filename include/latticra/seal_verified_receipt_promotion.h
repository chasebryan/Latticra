#ifndef LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_H
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_H

#include "latticra/seal_ed25519_verify.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX 64u
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_LABEL_MAX 128u
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX 64u
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_DIGEST_MAX 65u
#define LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK = 0,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_INPUT = 1,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_RESULT = 2,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_UNSUPPORTED_VERIFICATION = 3,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_VERIFICATION_NOT_PERFORMED = 4,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_NOT_VERIFIED = 5,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_STATE = 6,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_MESSAGE_DIGEST = 7,
    LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_PUBLIC_KEY_IDENTITY = 8
} latticra_seal_verified_receipt_promotion_error_t;

typedef struct {
    char receipt_profile[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX];
    char backend_profile[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX];
    char verification_policy_profile[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX];
    char message_label[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_LABEL_MAX];
    size_t message_size_bytes;
    char message_digest_algorithm[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_ALGORITHM_MAX];
    char trust_source[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX];
    char verification_state[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX];
    char receipt_state[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX];
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned verified;
    unsigned invalid;
    unsigned authority_usable;
    unsigned capability_gate_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_verified_receipt_promotion_error_t error;
    char status[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX];
} latticra_seal_verified_receipt_promotion_t;

const char *latticra_seal_verified_receipt_promotion_error_label(
    latticra_seal_verified_receipt_promotion_error_t error);
latticra_status_t latticra_seal_verified_receipt_promotion_from_ed25519_result(
    const latticra_seal_ed25519_verify_result_t *verify_result,
    latticra_seal_verified_receipt_promotion_t *out);
int latticra_seal_verified_receipt_promotion_is_authority_neutral(
    const latticra_seal_verified_receipt_promotion_t *receipt);
latticra_status_t latticra_seal_verified_receipt_promotion_report(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
