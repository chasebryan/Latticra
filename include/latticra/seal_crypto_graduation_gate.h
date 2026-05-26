#ifndef LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_H
#define LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_H

#include "latticra/seal_verified_receipt_promotion.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX 64u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_LABEL_MAX 128u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_STATE_MAX 64u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_REASON_MAX 128u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_DIGEST_MAX 65u
#define LATTICRA_SEAL_CRYPTO_GRADUATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK = 0,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_INPUT = 1,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_VERIFY_RESULT = 2,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_RECEIPT = 3,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_VERIFY_RESULT = 4,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_RECEIPT = 5,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_UNSUPPORTED_ALGORITHM = 6,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_MESSAGE_DIGEST = 7,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_MESSAGE_DIGEST = 8,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_PUBLIC_KEY_IDENTITY = 9,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_KEY_OR_SIGNATURE_SIZE = 10,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_AUTHORITY_NOT_NEUTRAL = 11,
    LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_BUFFER_TOO_SMALL = 12
} latticra_seal_crypto_graduation_gate_error_t;

typedef struct {
    char crypto_graduation_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char assurance_baseline_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char backend_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char verification_policy_profile[LATTICRA_SEAL_CRYPTO_GRADUATION_PROFILE_MAX];
    char message_label[LATTICRA_SEAL_CRYPTO_GRADUATION_LABEL_MAX];
    size_t message_size_bytes;
    char message_digest_algorithm[LATTICRA_SEAL_CRYPTO_GRADUATION_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_CRYPTO_GRADUATION_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_CRYPTO_GRADUATION_LABEL_MAX];
    size_t public_key_size_bytes;
    char signature_algorithm[LATTICRA_SEAL_CRYPTO_GRADUATION_ALGORITHM_MAX];
    size_t signature_size_bytes;
    char verification_state[LATTICRA_SEAL_CRYPTO_GRADUATION_STATE_MAX];
    char receipt_state[LATTICRA_SEAL_CRYPTO_GRADUATION_STATE_MAX];
    unsigned verify_result_present;
    unsigned receipt_present;
    unsigned provider_backed_verification_required;
    unsigned deterministic_test_vector_required;
    unsigned negative_test_vector_required;
    unsigned rfc8032_test_vector_tracked;
    unsigned fips_186_5_signature_standard_tracked;
    unsigned fips_180_4_digest_standard_tracked;
    unsigned fips_140_3_claim_gate_required;
    unsigned sp_800_57_key_management_required;
    unsigned sp_800_131a_transition_review_required;
    unsigned fips_204_ml_dsa_planning_tracked;
    unsigned fips_205_slh_dsa_planning_tracked;
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned verified;
    unsigned invalid;
    unsigned local_verify_graduated;
    unsigned receipt_promotion_graduated;
    unsigned standard_expectations_met;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned signing_authority_granted;
    unsigned key_generation_allowed;
    unsigned key_storage_allowed;
    unsigned revocation_lookup_allowed;
    unsigned network_lookup_allowed;
    unsigned authority_usable;
    unsigned authority_promotion_allowed;
    unsigned capability_gate_allowed;
    unsigned runtime_authority_granted;
    char gate_state[LATTICRA_SEAL_CRYPTO_GRADUATION_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_CRYPTO_GRADUATION_REASON_MAX];
    latticra_seal_crypto_graduation_gate_error_t error;
    char status[LATTICRA_SEAL_CRYPTO_GRADUATION_STATE_MAX];
} latticra_seal_crypto_graduation_gate_t;

const char *latticra_seal_crypto_graduation_gate_error_label(
    latticra_seal_crypto_graduation_gate_error_t error);
latticra_status_t latticra_seal_crypto_graduation_gate_from_verified_receipt(
    const latticra_seal_ed25519_verify_result_t *verify_result,
    const latticra_seal_verified_receipt_promotion_t *receipt,
    latticra_seal_crypto_graduation_gate_t *out);
int latticra_seal_crypto_graduation_gate_is_authority_neutral(
    const latticra_seal_crypto_graduation_gate_t *gate);
latticra_status_t latticra_seal_crypto_graduation_gate_report(
    const latticra_seal_crypto_graduation_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
