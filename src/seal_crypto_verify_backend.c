#include "latticra/seal_crypto_verify_backend.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_crypto_verify_backend_error_label(
    latticra_seal_crypto_verify_backend_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK:
        return "ok";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_POLICY:
        return "invalid-policy";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    case LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_UNSUPPORTED_ALGORITHM:
        return "unsupported-algorithm";
    default:
        return "unknown";
    }
}

static void backend_init(latticra_seal_crypto_verify_backend_t *backend) {
    memset(backend, 0, sizeof(*backend));
    copy_literal(backend->backend_profile, sizeof(backend->backend_profile), "latticra-seal-crypto-verify-backend/0.1");
    copy_literal(backend->crypto_verify_state, sizeof(backend->crypto_verify_state), "unsupported");
    backend->cryptographic_verification_supported = 0u;
    backend->cryptographic_verification_performed = 0u;
    backend->verified = 0u;
    backend->invalid = 0u;
    backend->authority_usable = 0u;
    backend->capability_gate_allowed = 0u;
    backend->runtime_authority_granted = 0u;
    backend->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_INPUT;
    copy_literal(backend->status, sizeof(backend->status), "invalid-input");
}

latticra_status_t latticra_seal_crypto_verify_backend_from_policy(
    const latticra_seal_verification_policy_t *policy,
    latticra_seal_crypto_verify_backend_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    backend_init(out);

    if (policy == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (policy->error != LATTICRA_SEAL_VERIFICATION_POLICY_OK) {
        out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_POLICY;
        copy_literal(out->status, sizeof(out->status), "invalid-policy");
        return LATTICRA_STATUS_OK;
    }

    if (policy->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (policy->signer_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (policy->public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    if (strcmp(policy->signature_algorithm, "Ed25519-development") != 0) {
        out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_UNSUPPORTED_ALGORITHM;
        copy_literal(out->status, sizeof(out->status), "unsupported-algorithm");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->verification_policy_profile, sizeof(out->verification_policy_profile), policy->verification_policy_profile);
    copy_literal(out->signature_profile, sizeof(out->signature_profile), policy->signature_profile);
    copy_literal(out->manifest_profile, sizeof(out->manifest_profile), policy->manifest_profile);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), policy->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), policy->artifact_digest_hex);
    copy_literal(out->signer_identity_label, sizeof(out->signer_identity_label), policy->signer_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), policy->signature_algorithm);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), policy->public_key_identity_label);
    copy_literal(out->trust_source, sizeof(out->trust_source), policy->trust_source);
    copy_literal(out->crypto_verify_state, sizeof(out->crypto_verify_state), "ready-local-ed25519");
    out->cryptographic_verification_supported = 1u;
    out->cryptographic_verification_performed = 0u;
    out->verified = 0u;
    out->invalid = 0u;
    out->authority_usable = 0u;
    out->capability_gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK;
    copy_literal(out->status, sizeof(out->status), "crypto-verify-backend-ready");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_crypto_verify_backend_is_metadata_only(
    const latticra_seal_crypto_verify_backend_t *backend) {
    if (backend == NULL) {
        return 0;
    }

    return backend->cryptographic_verification_supported == 0u &&
           backend->cryptographic_verification_performed == 0u &&
           backend->verified == 0u &&
           backend->invalid == 0u &&
           backend->authority_usable == 0u &&
           backend->capability_gate_allowed == 0u &&
           backend->runtime_authority_granted == 0u;
}

int latticra_seal_crypto_verify_backend_is_authority_neutral(
    const latticra_seal_crypto_verify_backend_t *backend) {
    if (backend == NULL) {
        return 0;
    }

    return backend->authority_usable == 0u &&
           backend->capability_gate_allowed == 0u &&
           backend->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_crypto_verify_backend_report(
    const latticra_seal_crypto_verify_backend_t *backend,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (backend == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL CRYPTO VERIFY BACKEND\n"
        "backend_profile=%s\n"
        "verification_policy_profile=%s\n"
        "signature_profile=%s\n"
        "manifest_profile=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "signer_identity_label=%s\n"
        "signature_algorithm=%s\n"
        "public_key_identity_label=%s\n"
        "trust_source=%s\n"
        "crypto_verify_state=%s\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "verified=%u\n"
        "invalid=%u\n"
        "authority_usable=%u\n"
        "capability_gate_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        backend->backend_profile,
        backend->verification_policy_profile,
        backend->signature_profile,
        backend->manifest_profile,
        backend->artifact_digest_algorithm,
        backend->artifact_digest_hex,
        backend->signer_identity_label,
        backend->signature_algorithm,
        backend->public_key_identity_label,
        backend->trust_source,
        backend->crypto_verify_state,
        backend->cryptographic_verification_supported,
        backend->cryptographic_verification_performed,
        backend->verified,
        backend->invalid,
        backend->authority_usable,
        backend->capability_gate_allowed,
        backend->runtime_authority_granted,
        latticra_seal_crypto_verify_backend_error_label(backend->error),
        backend->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
