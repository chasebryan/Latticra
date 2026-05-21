#ifndef LATTICRA_SEAL_VERIFICATION_POLICY_H
#define LATTICRA_SEAL_VERIFICATION_POLICY_H

#include "latticra/seal_signature.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX 64u
#define LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX 128u
#define LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX 64u
#define LATTICRA_SEAL_VERIFICATION_POLICY_DIGEST_MAX 65u
#define LATTICRA_SEAL_VERIFICATION_POLICY_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_VERIFICATION_POLICY_OK = 0,
    LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT = 1,
    LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE = 2,
    LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST = 3,
    LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER = 4,
    LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY = 5,
    LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM = 6
} latticra_seal_verification_policy_error_t;

typedef struct {
    char verification_policy_profile[LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX];
    char signature_profile[LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX];
    char manifest_profile[LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX];
    char artifact_digest_algorithm[LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_VERIFICATION_POLICY_DIGEST_MAX];
    char signer_identity_label[LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX];
    char public_key_identity_label[LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX];
    char trust_source[LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX];
    char verification_state[LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX];
    unsigned cryptographic_verification_supported;
    unsigned cryptographic_verification_performed;
    unsigned public_key_material_handling;
    unsigned private_key_handling;
    unsigned network_lookup_allowed;
    unsigned revocation_lookup_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_verification_policy_error_t error;
    char status[LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX];
} latticra_seal_verification_policy_t;

const char *latticra_seal_verification_policy_error_label(
    latticra_seal_verification_policy_error_t error);
latticra_status_t latticra_seal_verification_policy_from_signature(
    const latticra_seal_signature_t *signature,
    const char *public_key_identity_label,
    const char *trust_source,
    latticra_seal_verification_policy_t *out);
int latticra_seal_verification_policy_is_metadata_only(
    const latticra_seal_verification_policy_t *policy);
latticra_status_t latticra_seal_verification_policy_report(
    const latticra_seal_verification_policy_t *policy,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
