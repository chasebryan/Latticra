#include "latticra/seal_manifest.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_manifest_error_label(latticra_seal_manifest_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_MANIFEST_OK:
        return "ok";
    case LATTICRA_SEAL_MANIFEST_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_MANIFEST_INVALID_MEASUREMENT:
        return "invalid-measurement";
    case LATTICRA_SEAL_MANIFEST_MISSING_DIGEST:
        return "missing-digest";
    default:
        return "unknown";
    }
}

static void manifest_init(latticra_seal_manifest_t *manifest) {
    memset(manifest, 0, sizeof(*manifest));
    copy_literal(manifest->manifest_profile, sizeof(manifest->manifest_profile), "latticra-seal-manifest/0.1");
    copy_literal(manifest->manifest_kind, sizeof(manifest->manifest_kind), "unsigned-evidence-manifest");
    copy_literal(manifest->contract_digest_algorithm, sizeof(manifest->contract_digest_algorithm), "not-computed");
    copy_literal(manifest->planned_signature_algorithm, sizeof(manifest->planned_signature_algorithm), "Ed25519-planned");
    manifest->signature_supported = 0u;
    manifest->verification_supported = 0u;
    manifest->private_key_handling = 0u;
    manifest->runtime_authority_granted = 0u;
    manifest->evidence_level = 4u;
    manifest->error = LATTICRA_SEAL_MANIFEST_INVALID_INPUT;
    copy_literal(manifest->status, sizeof(manifest->status), "invalid-input");
}

latticra_status_t latticra_seal_manifest_from_measurement(
    const latticra_seal_measurement_t *measurement,
    const char *contract_id,
    latticra_seal_manifest_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    manifest_init(out);

    if (measurement == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (measurement->error != LATTICRA_SEAL_MEASUREMENT_OK) {
        out->error = LATTICRA_SEAL_MANIFEST_INVALID_MEASUREMENT;
        copy_literal(out->status, sizeof(out->status), "invalid-measurement");
        return LATTICRA_STATUS_OK;
    }

    if (measurement->digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_MANIFEST_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->artifact_label, sizeof(out->artifact_label), measurement->artifact_label);
    out->artifact_size_bytes = measurement->artifact_size_bytes;
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), measurement->algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), measurement->digest_hex);
    copy_literal(out->measurement_profile, sizeof(out->measurement_profile), measurement->measurement_profile);
    copy_literal(out->contract_id, sizeof(out->contract_id), contract_id != NULL ? contract_id : "unspecified-contract");
    out->error = LATTICRA_SEAL_MANIFEST_OK;
    copy_literal(out->status, sizeof(out->status), "unsigned-manifest");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_manifest_is_unsigned_metadata(const latticra_seal_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->signature_supported == 0u &&
           manifest->verification_supported == 0u &&
           manifest->private_key_handling == 0u &&
           manifest->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_manifest_report(
    const latticra_seal_manifest_t *manifest,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (manifest == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL MANIFEST\n"
        "manifest_profile=%s\n"
        "manifest_kind=%s\n"
        "artifact_label=%s\n"
        "artifact_size_bytes=%lu\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "measurement_profile=%s\n"
        "contract_id=%s\n"
        "contract_digest_algorithm=%s\n"
        "contract_digest_hex=%s\n"
        "evidence_level=%u\n"
        "planned_signature_algorithm=%s\n"
        "signature_supported=%u\n"
        "verification_supported=%u\n"
        "private_key_handling=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        manifest->manifest_profile,
        manifest->manifest_kind,
        manifest->artifact_label,
        manifest->artifact_size_bytes,
        manifest->artifact_digest_algorithm,
        manifest->artifact_digest_hex,
        manifest->measurement_profile,
        manifest->contract_id,
        manifest->contract_digest_algorithm,
        manifest->contract_digest_hex,
        manifest->evidence_level,
        manifest->planned_signature_algorithm,
        manifest->signature_supported,
        manifest->verification_supported,
        manifest->private_key_handling,
        manifest->runtime_authority_granted,
        latticra_seal_manifest_error_label(manifest->error),
        manifest->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
