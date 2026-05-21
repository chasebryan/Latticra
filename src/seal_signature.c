#include "latticra/seal_signature.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_signature_error_label(latticra_seal_signature_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNATURE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNATURE_INVALID_MANIFEST:
        return "invalid-manifest";
    case LATTICRA_SEAL_SIGNATURE_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_SIGNATURE_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_SIGNATURE_UNSUPPORTED_ALGORITHM:
        return "unsupported-algorithm";
    case LATTICRA_SEAL_SIGNATURE_MISSING_SIGNATURE_METADATA:
        return "missing-signature-metadata";
    default:
        return "unknown";
    }
}

static void signature_init(latticra_seal_signature_t *signature) {
    memset(signature, 0, sizeof(*signature));
    copy_literal(signature->signature_profile, sizeof(signature->signature_profile), "latticra-seal-signature/0.1");
    copy_literal(signature->signature_algorithm, sizeof(signature->signature_algorithm), "Ed25519-development");
    copy_literal(signature->signature_state, sizeof(signature->signature_state), "metadata-only");
    signature->signature_supported = 1u;
    signature->verification_supported = 0u;
    signature->private_key_handling = 0u;
    signature->network_lookup_allowed = 0u;
    signature->runtime_authority_granted = 0u;
    signature->error = LATTICRA_SEAL_SIGNATURE_INVALID_INPUT;
    copy_literal(signature->status, sizeof(signature->status), "invalid-input");
}

latticra_status_t latticra_seal_signature_from_manifest(
    const latticra_seal_manifest_t *manifest,
    const char *signer_identity_label,
    const char *signature_algorithm,
    unsigned long signature_byte_length,
    latticra_seal_signature_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    signature_init(out);

    if (manifest == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (manifest->error != LATTICRA_SEAL_MANIFEST_OK) {
        out->error = LATTICRA_SEAL_SIGNATURE_INVALID_MANIFEST;
        copy_literal(out->status, sizeof(out->status), "invalid-manifest");
        return LATTICRA_STATUS_OK;
    }

    if (manifest->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_SIGNATURE_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (signer_identity_label == NULL || signer_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_SIGNATURE_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (signature_algorithm == NULL || strcmp(signature_algorithm, "Ed25519-development") != 0) {
        out->error = LATTICRA_SEAL_SIGNATURE_UNSUPPORTED_ALGORITHM;
        copy_literal(out->status, sizeof(out->status), "unsupported-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (signature_byte_length == 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_MISSING_SIGNATURE_METADATA;
        copy_literal(out->status, sizeof(out->status), "missing-signature-metadata");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->manifest_profile, sizeof(out->manifest_profile), manifest->manifest_profile);
    copy_literal(out->manifest_kind, sizeof(out->manifest_kind), manifest->manifest_kind);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), manifest->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), manifest->artifact_digest_hex);
    copy_literal(out->signer_identity_label, sizeof(out->signer_identity_label), signer_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), signature_algorithm);
    out->signature_byte_length = signature_byte_length;
    out->error = LATTICRA_SEAL_SIGNATURE_OK;
    copy_literal(out->status, sizeof(out->status), "signature-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signature_is_metadata_only(const latticra_seal_signature_t *signature) {
    if (signature == NULL) {
        return 0;
    }

    return signature->signature_supported == 1u &&
           signature->verification_supported == 0u &&
           signature->private_key_handling == 0u &&
           signature->network_lookup_allowed == 0u &&
           signature->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_signature_report(
    const latticra_seal_signature_t *signature,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (signature == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNATURE\n"
        "signature_profile=%s\n"
        "manifest_profile=%s\n"
        "manifest_kind=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "signer_identity_label=%s\n"
        "signature_algorithm=%s\n"
        "signature_state=%s\n"
        "signature_byte_length=%lu\n"
        "signature_supported=%u\n"
        "verification_supported=%u\n"
        "private_key_handling=%u\n"
        "network_lookup_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        signature->signature_profile,
        signature->manifest_profile,
        signature->manifest_kind,
        signature->artifact_digest_algorithm,
        signature->artifact_digest_hex,
        signature->signer_identity_label,
        signature->signature_algorithm,
        signature->signature_state,
        signature->signature_byte_length,
        signature->signature_supported,
        signature->verification_supported,
        signature->private_key_handling,
        signature->network_lookup_allowed,
        signature->runtime_authority_granted,
        latticra_seal_signature_error_label(signature->error),
        signature->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
