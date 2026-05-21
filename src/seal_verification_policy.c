#include "latticra/seal_verification_policy.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_verification_policy_error_label(
    latticra_seal_verification_policy_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFICATION_POLICY_OK:
        return "ok";
    case LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE:
        return "invalid-signature";
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    case LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM:
        return "unsupported-algorithm";
    default:
        return "unknown";
    }
}

static void verification_policy_init(latticra_seal_verification_policy_t *policy) {
    memset(policy, 0, sizeof(*policy));
    copy_literal(
        policy->verification_policy_profile,
        sizeof(policy->verification_policy_profile),
        "latticra-seal-verification-policy/0.1");
    copy_literal(policy->trust_source, sizeof(policy->trust_source), "local-metadata-only");
    copy_literal(policy->verification_state, sizeof(policy->verification_state), "unsupported");
    policy->cryptographic_verification_supported = 0u;
    policy->cryptographic_verification_performed = 0u;
    policy->public_key_material_handling = 0u;
    policy->private_key_handling = 0u;
    policy->network_lookup_allowed = 0u;
    policy->revocation_lookup_allowed = 0u;
    policy->runtime_authority_granted = 0u;
    policy->error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT;
    copy_literal(policy->status, sizeof(policy->status), "invalid-input");
}

latticra_status_t latticra_seal_verification_policy_from_signature(
    const latticra_seal_signature_t *signature,
    const char *public_key_identity_label,
    const char *trust_source,
    latticra_seal_verification_policy_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    verification_policy_init(out);

    if (signature == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (signature->error != LATTICRA_SEAL_SIGNATURE_OK) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE;
        copy_literal(out->status, sizeof(out->status), "invalid-signature");
        return LATTICRA_STATUS_OK;
    }

    if (signature->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (signature->signer_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (signature->signature_algorithm[0] == '\0' ||
        strcmp(signature->signature_algorithm, "Ed25519-development") != 0) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM;
        copy_literal(out->status, sizeof(out->status), "unsupported-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (public_key_identity_label == NULL || public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->signature_profile, sizeof(out->signature_profile), signature->signature_profile);
    copy_literal(out->manifest_profile, sizeof(out->manifest_profile), signature->manifest_profile);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), signature->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), signature->artifact_digest_hex);
    copy_literal(out->signer_identity_label, sizeof(out->signer_identity_label), signature->signer_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), signature->signature_algorithm);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), public_key_identity_label);
    copy_literal(
        out->trust_source,
        sizeof(out->trust_source),
        trust_source != NULL && trust_source[0] != '\0' ? trust_source : "local-metadata-only");
    out->error = LATTICRA_SEAL_VERIFICATION_POLICY_OK;
    copy_literal(out->status, sizeof(out->status), "verification-policy-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_verification_policy_is_metadata_only(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return policy->cryptographic_verification_supported == 0u &&
           policy->cryptographic_verification_performed == 0u &&
           policy->public_key_material_handling == 0u &&
           policy->private_key_handling == 0u &&
           policy->network_lookup_allowed == 0u &&
           policy->revocation_lookup_allowed == 0u &&
           policy->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_verification_policy_report(
    const latticra_seal_verification_policy_t *policy,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (policy == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL VERIFICATION POLICY\n"
        "verification_policy_profile=%s\n"
        "signature_profile=%s\n"
        "manifest_profile=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "signer_identity_label=%s\n"
        "signature_algorithm=%s\n"
        "public_key_identity_label=%s\n"
        "trust_source=%s\n"
        "verification_state=%s\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "public_key_material_handling=%u\n"
        "private_key_handling=%u\n"
        "network_lookup_allowed=%u\n"
        "revocation_lookup_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        policy->verification_policy_profile,
        policy->signature_profile,
        policy->manifest_profile,
        policy->artifact_digest_algorithm,
        policy->artifact_digest_hex,
        policy->signer_identity_label,
        policy->signature_algorithm,
        policy->public_key_identity_label,
        policy->trust_source,
        policy->verification_state,
        policy->cryptographic_verification_supported,
        policy->cryptographic_verification_performed,
        policy->public_key_material_handling,
        policy->private_key_handling,
        policy->network_lookup_allowed,
        policy->revocation_lookup_allowed,
        policy->runtime_authority_granted,
        latticra_seal_verification_policy_error_label(policy->error),
        policy->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
