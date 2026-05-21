#include "latticra/seal_verification_receipt.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_verification_receipt_error_label(
    latticra_seal_verification_receipt_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_OK:
        return "ok";
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY:
        return "invalid-policy";
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    default:
        return "unknown";
    }
}

static void receipt_init(latticra_seal_verification_receipt_t *receipt) {
    memset(receipt, 0, sizeof(*receipt));
    copy_literal(receipt->receipt_profile, sizeof(receipt->receipt_profile), "latticra-seal-verification-receipt/0.1");
    copy_literal(receipt->verification_state, sizeof(receipt->verification_state), "unsupported");
    copy_literal(receipt->receipt_state, sizeof(receipt->receipt_state), "unverified-metadata");
    receipt->cryptographic_verification_supported = 0u;
    receipt->cryptographic_verification_performed = 0u;
    receipt->verified = 0u;
    receipt->invalid = 0u;
    receipt->authority_usable = 0u;
    receipt->capability_gate_allowed = 0u;
    receipt->runtime_authority_granted = 0u;
    receipt->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT;
    copy_literal(receipt->status, sizeof(receipt->status), "invalid-input");
}

latticra_status_t latticra_seal_verification_receipt_from_policy(
    const latticra_seal_verification_policy_t *policy,
    latticra_seal_verification_receipt_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    receipt_init(out);

    if (policy == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (policy->error != LATTICRA_SEAL_VERIFICATION_POLICY_OK) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY;
        copy_literal(out->status, sizeof(out->status), "invalid-policy");
        return LATTICRA_STATUS_OK;
    }

    if (policy->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (policy->signer_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (policy->public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
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
    copy_literal(out->verification_state, sizeof(out->verification_state), policy->verification_state);
    out->cryptographic_verification_supported = policy->cryptographic_verification_supported;
    out->cryptographic_verification_performed = policy->cryptographic_verification_performed;
    out->verified = 0u;
    out->invalid = 0u;
    out->authority_usable = 0u;
    out->capability_gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_OK;
    copy_literal(out->status, sizeof(out->status), "verification-receipt-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_verification_receipt_is_unverified_metadata(
    const latticra_seal_verification_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return receipt->cryptographic_verification_supported == 0u &&
           receipt->cryptographic_verification_performed == 0u &&
           receipt->verified == 0u &&
           receipt->invalid == 0u &&
           receipt->authority_usable == 0u &&
           receipt->capability_gate_allowed == 0u &&
           receipt->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_verification_receipt_report(
    const latticra_seal_verification_receipt_t *receipt,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (receipt == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL VERIFICATION RECEIPT\n"
        "receipt_profile=%s\n"
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
        "receipt_state=%s\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "verified=%u\n"
        "invalid=%u\n"
        "authority_usable=%u\n"
        "capability_gate_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        receipt->receipt_profile,
        receipt->verification_policy_profile,
        receipt->signature_profile,
        receipt->manifest_profile,
        receipt->artifact_digest_algorithm,
        receipt->artifact_digest_hex,
        receipt->signer_identity_label,
        receipt->signature_algorithm,
        receipt->public_key_identity_label,
        receipt->trust_source,
        receipt->verification_state,
        receipt->receipt_state,
        receipt->cryptographic_verification_supported,
        receipt->cryptographic_verification_performed,
        receipt->verified,
        receipt->invalid,
        receipt->authority_usable,
        receipt->capability_gate_allowed,
        receipt->runtime_authority_granted,
        latticra_seal_verification_receipt_error_label(receipt->error),
        receipt->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
