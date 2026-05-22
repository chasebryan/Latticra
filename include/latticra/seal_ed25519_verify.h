#ifndef LATTICRA_SEAL_ED25519_VERIFY_H
#define LATTICRA_SEAL_ED25519_VERIFY_H

#include "latticra/seal_crypto_verify_backend.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_ED25519_VERIFY_PROFILE_MAX 64u
#define LATTICRA_SEAL_ED25519_VERIFY_LABEL_MAX 128u
#define LATTICRA_SEAL_ED25519_VERIFY_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_ED25519_VERIFY_STATE_MAX 64u
#define LATTICRA_SEAL_ED25519_VERIFY_DIGEST_MAX 65u
#define LATTICRA_SEAL_ED25519_VERIFY_REPORT_MAX 4096u
#define LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES 32u
#define LATTICRA_SEAL_ED25519_SIGNATURE_BYTES 64u
#define LATTICRA_SEAL_ED25519_MESSAGE_MAX 65536u

typedef enum {
    LATTICRA_SEAL_ED25519_VERIFY_OK = 0,
    LATTICRA_SEAL_ED25519_VERIFY_INVALID_INPUT = 1,
    LATTICRA_SEAL_ED25519_VERIFY_INVALID_BACKEND = 2,
    LATTICRA_SEAL_ED25519_VERIFY_MISSING_MESSAGE = 3,
    LATTICRA_SEAL_ED25519_VERIFY_MESSAGE_TOO_LARGE = 4,
    LATTICRA_SEAL_ED25519_VERIFY_MISSING_PUBLIC_KEY = 5,
    LATTICRA_SEAL_ED25519_VERIFY_INVALID_PUBLIC_KEY_SIZE = 6,
    LATTICRA_SEAL_ED25519_VERIFY_MISSING_SIGNATURE = 7,
    LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE_SIZE = 8,
    LATTICRA_SEAL_ED25519_VERIFY_UNSUPPORTED_ALGORITHM = 9,
    LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE = 10,
    LATTICRA_SEAL_ED25519_VERIFY_PROVIDER_FAILURE = 11
} latticra_seal_ed25519_verify_error_t;

typedef struct {
    char ed25519_verify_profile[LATTICRA_SEAL_ED25519_VERIFY_PROFILE_MAX];
    char backend_profile[LATTICRA_SEAL_ED25519_VERIFY_PROFILE_MAX];
    char verification_policy_profile[LATTICRA_SEAL_ED25519_VERIFY_PROFILE_MAX];
    char message_label[LATTICRA_SEAL_ED25519_VERIFY_LABEL_MAX];
    size_t message_size_bytes;
    char message_digest_algorithm[LATTICRA_SEAL_ED25519_VERIFY_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_ED25519_VERIFY_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_ED25519_VERIFY_LABEL_MAX];
    size_t public_key_size_bytes;
    char signature_algorithm[LATTICRA_SEAL_ED25519_VERIFY_ALGORITHM_MAX];
    size_t signature_size_bytes;
    char trust_source[LATTICRA_SEAL_ED25519_VERIFY_STATE_MAX];
    char crypto_verify_state[LATTICRA_SEAL_ED25519_VERIFY_STATE_MAX];
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned verified;
    unsigned invalid;
    unsigned authority_usable;
    unsigned capability_gate_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_ed25519_verify_error_t error;
    char status[LATTICRA_SEAL_ED25519_VERIFY_STATE_MAX];
} latticra_seal_ed25519_verify_result_t;

const char *latticra_seal_ed25519_verify_error_label(
    latticra_seal_ed25519_verify_error_t error);
latticra_status_t latticra_seal_ed25519_verify_local(
    const latticra_seal_crypto_verify_backend_t *backend,
    const char *message_label,
    const unsigned char *message,
    size_t message_len,
    const unsigned char *public_key,
    size_t public_key_len,
    const unsigned char *signature,
    size_t signature_len,
    latticra_seal_ed25519_verify_result_t *out);
int latticra_seal_ed25519_verify_result_is_authority_neutral(
    const latticra_seal_ed25519_verify_result_t *result);
latticra_status_t latticra_seal_ed25519_verify_report(
    const latticra_seal_ed25519_verify_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
