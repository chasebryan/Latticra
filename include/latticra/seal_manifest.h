#ifndef LATTICRA_SEAL_MANIFEST_H
#define LATTICRA_SEAL_MANIFEST_H

#include "latticra/seal_measurement.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_MANIFEST_PROFILE_MAX 64u
#define LATTICRA_SEAL_MANIFEST_KIND_MAX 64u
#define LATTICRA_SEAL_MANIFEST_LABEL_MAX 128u
#define LATTICRA_SEAL_MANIFEST_DIGEST_MAX 65u
#define LATTICRA_SEAL_MANIFEST_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_MANIFEST_STATUS_MAX 64u
#define LATTICRA_SEAL_MANIFEST_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_MANIFEST_OK = 0,
    LATTICRA_SEAL_MANIFEST_INVALID_INPUT = 1,
    LATTICRA_SEAL_MANIFEST_INVALID_MEASUREMENT = 2,
    LATTICRA_SEAL_MANIFEST_MISSING_DIGEST = 3
} latticra_seal_manifest_error_t;

typedef struct {
    char manifest_profile[LATTICRA_SEAL_MANIFEST_PROFILE_MAX];
    char manifest_kind[LATTICRA_SEAL_MANIFEST_KIND_MAX];
    char artifact_label[LATTICRA_SEAL_MANIFEST_LABEL_MAX];
    unsigned long artifact_size_bytes;
    char artifact_digest_algorithm[LATTICRA_SEAL_MANIFEST_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_MANIFEST_DIGEST_MAX];
    char measurement_profile[LATTICRA_SEAL_MANIFEST_PROFILE_MAX];
    char contract_id[LATTICRA_SEAL_MANIFEST_LABEL_MAX];
    char contract_digest_algorithm[LATTICRA_SEAL_MANIFEST_ALGORITHM_MAX];
    char contract_digest_hex[LATTICRA_SEAL_MANIFEST_DIGEST_MAX];
    unsigned evidence_level;
    char planned_signature_algorithm[LATTICRA_SEAL_MANIFEST_ALGORITHM_MAX];
    unsigned signature_supported;
    unsigned verification_supported;
    unsigned private_key_handling;
    unsigned runtime_authority_granted;
    latticra_seal_manifest_error_t error;
    char status[LATTICRA_SEAL_MANIFEST_STATUS_MAX];
} latticra_seal_manifest_t;

const char *latticra_seal_manifest_error_label(latticra_seal_manifest_error_t error);
latticra_status_t latticra_seal_manifest_from_measurement(
    const latticra_seal_measurement_t *measurement,
    const char *contract_id,
    latticra_seal_manifest_t *out);
int latticra_seal_manifest_is_unsigned_metadata(const latticra_seal_manifest_t *manifest);
latticra_status_t latticra_seal_manifest_report(
    const latticra_seal_manifest_t *manifest,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
