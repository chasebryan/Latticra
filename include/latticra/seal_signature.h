#ifndef LATTICRA_SEAL_SIGNATURE_H
#define LATTICRA_SEAL_SIGNATURE_H

#include "latticra/seal_manifest.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNATURE_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNATURE_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_SIGNATURE_OK = 0,
    LATTICRA_SEAL_SIGNATURE_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNATURE_INVALID_MANIFEST = 2,
    LATTICRA_SEAL_SIGNATURE_MISSING_DIGEST = 3,
    LATTICRA_SEAL_SIGNATURE_MISSING_SIGNER = 4,
    LATTICRA_SEAL_SIGNATURE_UNSUPPORTED_ALGORITHM = 5,
    LATTICRA_SEAL_SIGNATURE_MISSING_SIGNATURE_METADATA = 6
} latticra_seal_signature_error_t;

typedef struct {
    char signature_profile[LATTICRA_SEAL_SIGNATURE_PROFILE_MAX];
    char manifest_profile[LATTICRA_SEAL_SIGNATURE_PROFILE_MAX];
    char manifest_kind[LATTICRA_SEAL_SIGNATURE_LABEL_MAX];
    char artifact_digest_algorithm[LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_MANIFEST_DIGEST_MAX];
    char signer_identity_label[LATTICRA_SEAL_SIGNATURE_LABEL_MAX];
    char signature_algorithm[LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX];
    char signature_state[LATTICRA_SEAL_SIGNATURE_STATE_MAX];
    unsigned long signature_byte_length;
    unsigned signature_supported;
    unsigned verification_supported;
    unsigned private_key_handling;
    unsigned network_lookup_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_signature_error_t error;
    char status[LATTICRA_SEAL_SIGNATURE_STATE_MAX];
} latticra_seal_signature_t;

const char *latticra_seal_signature_error_label(latticra_seal_signature_error_t error);
latticra_status_t latticra_seal_signature_from_manifest(
    const latticra_seal_manifest_t *manifest,
    const char *signer_identity_label,
    const char *signature_algorithm,
    unsigned long signature_byte_length,
    latticra_seal_signature_t *out);
int latticra_seal_signature_is_metadata_only(const latticra_seal_signature_t *signature);
latticra_status_t latticra_seal_signature_report(
    const latticra_seal_signature_t *signature,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
