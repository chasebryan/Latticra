#include "latticra/seal_crypto_graduation_gate.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_hex_char(char value) {
    return (value >= '0' && value <= '9') ||
           (value >= 'a' && value <= 'f') ||
           (value >= 'A' && value <= 'F');
}

static int is_sha256_hex_digest(const char *digest) {
    size_t i;

    if (digest == NULL || strlen(digest) != 64u) {
        return 0;
    }

    for (i = 0u; i < 64u; ++i) {
        if (!is_hex_char(digest[i])) {
            return 0;
        }
    }

    return 1;
}

const char *latticra_seal_crypto_graduation_gate_error_label(
    latticra_seal_crypto_graduation_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK:
        return "ok";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_VERIFY_RESULT:
        return "missing-verify-result";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_RECEIPT:
        return "missing-receipt";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_VERIFY_RESULT:
        return "invalid-verify-result";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_RECEIPT:
        return "invalid-receipt";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_UNSUPPORTED_ALGORITHM:
        return "unsupported-algorithm";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_MESSAGE_DIGEST:
        return "missing-message-digest";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_MESSAGE_DIGEST:
        return "invalid-message-digest";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_KEY_OR_SIGNATURE_SIZE:
        return "invalid-key-or-signature-size";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_AUTHORITY_NOT_NEUTRAL:
        return "authority-not-neutral";
    case LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

static void gate_init(latticra_seal_crypto_graduation_gate_t *gate) {
    memset(gate, 0, sizeof(*gate));
    copy_literal(
        gate->crypto_graduation_profile,
        sizeof(gate->crypto_graduation_profile),
        "latticra-seal-crypto-graduation-gate/0.1");
    copy_literal(
        gate->assurance_baseline_profile,
        sizeof(gate->assurance_baseline_profile),
        "latticra-cryptographic-assurance-key-management/0.1");
    copy_literal(gate->message_digest_algorithm, sizeof(gate->message_digest_algorithm), "SHA-256");
    copy_literal(gate->signature_algorithm, sizeof(gate->signature_algorithm), "Ed25519-development");
    copy_literal(gate->verification_state, sizeof(gate->verification_state), "invalid");
    copy_literal(gate->receipt_state, sizeof(gate->receipt_state), "invalid");
    gate->provider_backed_verification_required = 1u;
    gate->deterministic_test_vector_required = 1u;
    gate->negative_test_vector_required = 1u;
    gate->rfc8032_test_vector_tracked = 1u;
    gate->fips_186_5_signature_standard_tracked = 1u;
    gate->fips_180_4_digest_standard_tracked = 1u;
    gate->fips_140_3_claim_gate_required = 1u;
    gate->sp_800_57_key_management_required = 1u;
    gate->sp_800_131a_transition_review_required = 1u;
    gate->fips_204_ml_dsa_planning_tracked = 1u;
    gate->fips_205_slh_dsa_planning_tracked = 1u;
    gate->production_crypto_claim_allowed = 0u;
    gate->fips_claim_allowed = 0u;
    gate->signing_authority_granted = 0u;
    gate->key_generation_allowed = 0u;
    gate->key_storage_allowed = 0u;
    gate->revocation_lookup_allowed = 0u;
    gate->network_lookup_allowed = 0u;
    gate->authority_usable = 0u;
    gate->authority_promotion_allowed = 0u;
    gate->capability_gate_allowed = 0u;
    gate->runtime_authority_granted = 0u;
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "blocked");
    copy_literal(gate->blocked_reason, sizeof(gate->blocked_reason), "invalid-input");
    gate->error = LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_INPUT;
    copy_literal(gate->status, sizeof(gate->status), "invalid-input");
}

static latticra_status_t gate_fail(
    latticra_seal_crypto_graduation_gate_t *gate,
    latticra_seal_crypto_graduation_gate_error_t error,
    const char *blocked_reason) {
    gate->local_verify_graduated = 0u;
    gate->receipt_promotion_graduated = 0u;
    gate->standard_expectations_met = 0u;
    gate->authority_usable = 0u;
    gate->authority_promotion_allowed = 0u;
    gate->capability_gate_allowed = 0u;
    gate->runtime_authority_granted = 0u;
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "blocked");
    copy_literal(gate->blocked_reason, sizeof(gate->blocked_reason), blocked_reason);
    gate->error = error;
    copy_literal(
        gate->status,
        sizeof(gate->status),
        latticra_seal_crypto_graduation_gate_error_label(error));
    return LATTICRA_STATUS_OK;
}

static void copy_verify_metadata(
    const latticra_seal_ed25519_verify_result_t *verify_result,
    latticra_seal_crypto_graduation_gate_t *gate) {
    copy_literal(gate->verify_profile, sizeof(gate->verify_profile), verify_result->ed25519_verify_profile);
    copy_literal(gate->backend_profile, sizeof(gate->backend_profile), verify_result->backend_profile);
    copy_literal(
        gate->verification_policy_profile,
        sizeof(gate->verification_policy_profile),
        verify_result->verification_policy_profile);
    copy_literal(gate->message_label, sizeof(gate->message_label), verify_result->message_label);
    gate->message_size_bytes = verify_result->message_size_bytes;
    copy_literal(
        gate->message_digest_algorithm,
        sizeof(gate->message_digest_algorithm),
        verify_result->message_digest_algorithm);
    copy_literal(gate->message_digest_hex, sizeof(gate->message_digest_hex), verify_result->message_digest_hex);
    copy_literal(
        gate->public_key_identity_label,
        sizeof(gate->public_key_identity_label),
        verify_result->public_key_identity_label);
    gate->public_key_size_bytes = verify_result->public_key_size_bytes;
    copy_literal(gate->signature_algorithm, sizeof(gate->signature_algorithm), verify_result->signature_algorithm);
    gate->signature_size_bytes = verify_result->signature_size_bytes;
    copy_literal(gate->verification_state, sizeof(gate->verification_state), verify_result->crypto_verify_state);
    gate->cryptographic_verification_supported = verify_result->cryptographic_verification_supported;
    gate->cryptographic_verification_performed = verify_result->cryptographic_verification_performed;
    gate->verified = verify_result->verified;
    gate->invalid = verify_result->invalid;
}

static void copy_receipt_metadata(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    latticra_seal_crypto_graduation_gate_t *gate) {
    copy_literal(gate->receipt_profile, sizeof(gate->receipt_profile), receipt->receipt_profile);
    copy_literal(gate->receipt_state, sizeof(gate->receipt_state), receipt->receipt_state);
}

static int verify_result_authority_neutral(
    const latticra_seal_ed25519_verify_result_t *verify_result) {
    return verify_result->authority_usable == 0u &&
           verify_result->capability_gate_allowed == 0u &&
           verify_result->runtime_authority_granted == 0u;
}

static int receipt_authority_neutral(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    return receipt->authority_usable == 0u &&
           receipt->capability_gate_allowed == 0u &&
           receipt->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_crypto_graduation_gate_from_verified_receipt(
    const latticra_seal_ed25519_verify_result_t *verify_result,
    const latticra_seal_verified_receipt_promotion_t *receipt,
    latticra_seal_crypto_graduation_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);

    if (verify_result == NULL) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_VERIFY_RESULT,
            "missing-verify-result");
    }

    out->verify_result_present = 1u;
    copy_verify_metadata(verify_result, out);

    if (receipt == NULL) {
        return gate_fail(out, LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_RECEIPT, "missing-receipt");
    }

    out->receipt_present = 1u;
    copy_receipt_metadata(receipt, out);

    if (verify_result->error != LATTICRA_SEAL_ED25519_VERIFY_OK ||
        verify_result->verified != 1u ||
        verify_result->invalid != 0u ||
        strcmp(verify_result->crypto_verify_state, "verified") != 0 ||
        verify_result->cryptographic_verification_supported != 1u ||
        verify_result->cryptographic_verification_performed != 1u) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_VERIFY_RESULT,
            "invalid-verify-result");
    }

    if (receipt->error != LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK ||
        receipt->verified != 1u ||
        receipt->invalid != 0u ||
        strcmp(receipt->verification_state, "verified") != 0 ||
        strcmp(receipt->receipt_state, "verified") != 0 ||
        receipt->cryptographic_verification_supported != 1u ||
        receipt->cryptographic_verification_performed != 1u) {
        return gate_fail(out, LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_RECEIPT, "invalid-receipt");
    }

    if (strcmp(verify_result->signature_algorithm, "Ed25519-development") != 0 ||
        strcmp(receipt->signature_algorithm, "Ed25519-development") != 0) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_UNSUPPORTED_ALGORITHM,
            "unsupported-algorithm");
    }

    if (strcmp(verify_result->message_digest_algorithm, "SHA-256") != 0 ||
        strcmp(receipt->message_digest_algorithm, "SHA-256") != 0) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_MESSAGE_DIGEST,
            "invalid-message-digest-algorithm");
    }

    if (verify_result->message_digest_hex[0] == '\0' || receipt->message_digest_hex[0] == '\0') {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_MESSAGE_DIGEST,
            "missing-message-digest");
    }

    if (!is_sha256_hex_digest(verify_result->message_digest_hex) ||
        !is_sha256_hex_digest(receipt->message_digest_hex) ||
        strcmp(verify_result->message_digest_hex, receipt->message_digest_hex) != 0) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_MESSAGE_DIGEST,
            "invalid-message-digest");
    }

    if (verify_result->public_key_identity_label[0] == '\0' ||
        receipt->public_key_identity_label[0] == '\0' ||
        strcmp(verify_result->public_key_identity_label, receipt->public_key_identity_label) != 0) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_PUBLIC_KEY_IDENTITY,
            "missing-public-key-identity");
    }

    if (verify_result->public_key_size_bytes != LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES ||
        verify_result->signature_size_bytes != LATTICRA_SEAL_ED25519_SIGNATURE_BYTES) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_KEY_OR_SIGNATURE_SIZE,
            "invalid-key-or-signature-size");
    }

    if (!verify_result_authority_neutral(verify_result) || !receipt_authority_neutral(receipt)) {
        return gate_fail(
            out,
            LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_AUTHORITY_NOT_NEUTRAL,
            "authority-not-neutral");
    }

    out->local_verify_graduated = 1u;
    out->receipt_promotion_graduated = 1u;
    out->standard_expectations_met = 1u;
    out->cryptographic_verification_supported = 1u;
    out->cryptographic_verification_performed = 1u;
    out->verified = 1u;
    out->invalid = 0u;
    out->authority_usable = 0u;
    out->authority_promotion_allowed = 0u;
    out->capability_gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->gate_state, sizeof(out->gate_state), "graduated-authority-neutral");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "authority-remains-denied");
    out->error = LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK;
    copy_literal(out->status, sizeof(out->status), "crypto-graduation-gate-passed");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_crypto_graduation_gate_is_authority_neutral(
    const latticra_seal_crypto_graduation_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->signing_authority_granted == 0u &&
           gate->key_generation_allowed == 0u &&
           gate->key_storage_allowed == 0u &&
           gate->revocation_lookup_allowed == 0u &&
           gate->network_lookup_allowed == 0u &&
           gate->authority_usable == 0u &&
           gate->authority_promotion_allowed == 0u &&
           gate->capability_gate_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_crypto_graduation_gate_report(
    const latticra_seal_crypto_graduation_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL CRYPTO GRADUATION GATE\n"
        "crypto_graduation_profile=%s\n"
        "assurance_baseline_profile=%s\n"
        "verify_profile=%s\n"
        "receipt_profile=%s\n"
        "backend_profile=%s\n"
        "verification_policy_profile=%s\n"
        "message_label=%s\n"
        "message_size_bytes=%zu\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "public_key_size_bytes=%zu\n"
        "signature_algorithm=%s\n"
        "signature_size_bytes=%zu\n"
        "verification_state=%s\n"
        "receipt_state=%s\n"
        "verify_result_present=%u\n"
        "receipt_present=%u\n"
        "provider_backed_verification_required=%u\n"
        "deterministic_test_vector_required=%u\n"
        "negative_test_vector_required=%u\n"
        "rfc8032_test_vector_tracked=%u\n"
        "fips_186_5_signature_standard_tracked=%u\n"
        "fips_180_4_digest_standard_tracked=%u\n"
        "fips_140_3_claim_gate_required=%u\n"
        "sp_800_57_key_management_required=%u\n"
        "sp_800_131a_transition_review_required=%u\n"
        "fips_204_ml_dsa_planning_tracked=%u\n"
        "fips_205_slh_dsa_planning_tracked=%u\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "verified=%u\n"
        "invalid=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "standard_expectations_met=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "signing_authority_granted=%u\n"
        "key_generation_allowed=%u\n"
        "key_storage_allowed=%u\n"
        "revocation_lookup_allowed=%u\n"
        "network_lookup_allowed=%u\n"
        "authority_usable=%u\n"
        "authority_promotion_allowed=%u\n"
        "capability_gate_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "gate_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->crypto_graduation_profile,
        gate->assurance_baseline_profile,
        gate->verify_profile,
        gate->receipt_profile,
        gate->backend_profile,
        gate->verification_policy_profile,
        gate->message_label,
        gate->message_size_bytes,
        gate->message_digest_algorithm,
        gate->message_digest_hex,
        gate->public_key_identity_label,
        gate->public_key_size_bytes,
        gate->signature_algorithm,
        gate->signature_size_bytes,
        gate->verification_state,
        gate->receipt_state,
        gate->verify_result_present,
        gate->receipt_present,
        gate->provider_backed_verification_required,
        gate->deterministic_test_vector_required,
        gate->negative_test_vector_required,
        gate->rfc8032_test_vector_tracked,
        gate->fips_186_5_signature_standard_tracked,
        gate->fips_180_4_digest_standard_tracked,
        gate->fips_140_3_claim_gate_required,
        gate->sp_800_57_key_management_required,
        gate->sp_800_131a_transition_review_required,
        gate->fips_204_ml_dsa_planning_tracked,
        gate->fips_205_slh_dsa_planning_tracked,
        gate->cryptographic_verification_supported,
        gate->cryptographic_verification_performed,
        gate->verified,
        gate->invalid,
        gate->local_verify_graduated,
        gate->receipt_promotion_graduated,
        gate->standard_expectations_met,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->signing_authority_granted,
        gate->key_generation_allowed,
        gate->key_storage_allowed,
        gate->revocation_lookup_allowed,
        gate->network_lookup_allowed,
        gate->authority_usable,
        gate->authority_promotion_allowed,
        gate->capability_gate_allowed,
        gate->runtime_authority_granted,
        gate->gate_state,
        gate->blocked_reason,
        latticra_seal_crypto_graduation_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
