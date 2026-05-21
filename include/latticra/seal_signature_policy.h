#ifndef LATTICRA_SEAL_SIGNATURE_POLICY_H
#define LATTICRA_SEAL_SIGNATURE_POLICY_H

#include "latticra/seal_manifest.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNATURE_POLICY_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_POLICY_LABEL_MAX 128u
#define LATTICRA_SEAL_SIGNATURE_POLICY_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_SIGNATURE_POLICY_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNATURE_POLICY_REPORT_MAX 2048u

typedef enum {
    LATTICRA_SEAL_SIGNATURE_POLICY_OK = 0,
    LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_MANIFEST = 2
} latticra_seal_signature_policy_error_t;

typedef struct {
    char policy_profile[LATTICRA_SEAL_SIGNATURE_POLICY_PROFILE_MAX];
    char manifest_profile[LATTICRA_SEAL_SIGNATURE_POLICY_PROFILE_MAX];
    char manifest_kind[LATTICRA_SEAL_SIGNATURE_POLICY_LABEL_MAX];
    char planned_signature_algorithm[LATTICRA_SEAL_SIGNATURE_POLICY_ALGORITHM_MAX];
    char post_quantum_algorithm_planned[LATTICRA_SEAL_SIGNATURE_POLICY_ALGORITHM_MAX];
    char conservative_root_algorithm_planned[LATTICRA_SEAL_SIGNATURE_POLICY_ALGORITHM_MAX];
    char signature_state[LATTICRA_SEAL_SIGNATURE_POLICY_STATE_MAX];
    unsigned signature_supported;
    unsigned verification_supported;
    unsigned public_key_metadata_supported;
    unsigned private_key_handling;
    unsigned network_lookup_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_signature_policy_error_t error;
    char status[LATTICRA_SEAL_SIGNATURE_POLICY_STATE_MAX];
} latticra_seal_signature_policy_t;

const char *latticra_seal_signature_policy_error_label(latticra_seal_signature_policy_error_t error);
latticra_status_t latticra_seal_signature_policy_from_manifest(
    const latticra_seal_manifest_t *manifest,
    latticra_seal_signature_policy_t *out);
int latticra_seal_signature_policy_is_metadata_only(
    const latticra_seal_signature_policy_t *policy);
latticra_status_t latticra_seal_signature_policy_report(
    const latticra_seal_signature_policy_t *policy,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
