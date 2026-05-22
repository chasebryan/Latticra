#include "latticra/seal_verified_receipt_promotion.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_verified_receipt_promotion_error_label(
    latticra_seal_verified_receipt_promotion_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK:
        return "ok";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_RESULT:
        return "invalid-verify-result";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_UNSUPPORTED_VERIFICATION:
        return "unsupported-verification";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_VERIFICATION_NOT_PERFORMED:
        return "verification-not-performed";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_NOT_VERIFIED:
        return "not-verified";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_STATE:
        return "invalid-verify-state";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_MESSAGE_DIGEST:
        return "missing-message-digest";
    case LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    default:
        return "unknown";
    }
}

static void receipt_init(latticra_seal_verified_receipt_promotion_t *receipt) {
    memset(receipt, 0, sizeof(*receipt));
    copy_literal(receipt->receipt_profile, sizeof(receipt->receipt_profile), "latticra-seal-verified-receipt/0.1");
    copy_literal(receipt->verification_state, sizeof(receipt->verification_state), "invalid");
    copy_literal(receipt->receipt_state, sizeof(receipt->receipt_state), "invalid");
    receipt->cryptographic_verification_supported = 0u;
    receipt->cryptographic_verification_performed = 0u;
    receipt->verified = 0u;
    receipt->invalid = 1u;
    receipt->authority_usable = 0u;
    receipt->capability_gate_allowed = 0u;
    receipt->runtime_authority_granted = 0u;
    receipt->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_INPUT;
    copy_literal(receipt->status, sizeof(receipt->status), "invalid-input");
}

latticra_status_t latticra_seal_verified_receipt_promotion_from_ed25519_result(
    const latticra_seal_ed25519_verify_result_t *verify_result,
    latticra_seal_verified_receipt_promotion_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    receipt_init(out);

    if (verify_result == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->error != LATTICRA_SEAL_ED25519_VERIFY_OK) {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_RESULT;
        copy_literal(out->status, sizeof(out->status), "invalid-verify-result");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->cryptographic_verification_supported != 1u) {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_UNSUPPORTED_VERIFICATION;
        copy_literal(out->status, sizeof(out->status), "unsupported-verification");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->cryptographic_verification_performed != 1u) {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_VERIFICATION_NOT_PERFORMED;
        copy_literal(out->status, sizeof(out->status), "verification-not-performed");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->verified != 1u || verify_result->invalid != 0u) {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_NOT_VERIFIED;
        copy_literal(out->status, sizeof(out->status), "not-verified");
        return LATTICRA_STATUS_OK;
    }

    if (strcmp(verify_result->crypto_verify_state, "verified") != 0) {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_STATE;
        copy_literal(out->status, sizeof(out->status), "invalid-verify-state");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->message_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_MESSAGE_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-message-digest");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result->public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->verify_profile, sizeof(out->verify_profile), verify_result->ed25519_verify_profile);
    copy_literal(out->backend_profile, sizeof(out->backend_profile), verify_result->backend_profile);
    copy_literal(out->verification_policy_profile, sizeof(out->verification_policy_profile), verify_result->verification_policy_profile);
    copy_literal(out->message_label, sizeof(out->message_label), verify_result->message_label);
    out->message_size_bytes = verify_result->message_size_bytes;
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), verify_result->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), verify_result->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), verify_result->public_key_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), verify_result->signature_algorithm);
    copy_literal(out->trust_source, sizeof(out->trust_source), verify_result->trust_source);
    copy_literal(out->verification_state, sizeof(out->verification_state), "verified");
    copy_literal(out->receipt_state, sizeof(out->receipt_state), "verified");
    out->cryptographic_verification_supported = 1u;
    out->cryptographic_verification_performed = 1u;
    out->verified = 1u;
    out->invalid = 0u;
    out->authority_usable = 0u;
    out->capability_gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK;
    copy_literal(out->status, sizeof(out->status), "verified-receipt-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_verified_receipt_promotion_is_authority_neutral(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return receipt->authority_usable == 0u &&
           receipt->capability_gate_allowed == 0u &&
           receipt->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_verified_receipt_promotion_report(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (receipt == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL VERIFIED RECEIPT PROMOTION\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "backend_profile=%s\n"
        "verification_policy_profile=%s\n"
        "message_label=%s\n"
        "message_size_bytes=%zu\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "signature_algorithm=%s\n"
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
        receipt->verify_profile,
        receipt->backend_profile,
        receipt->verification_policy_profile,
        receipt->message_label,
        receipt->message_size_bytes,
        receipt->message_digest_algorithm,
        receipt->message_digest_hex,
        receipt->public_key_identity_label,
        receipt->signature_algorithm,
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
        latticra_seal_verified_receipt_promotion_error_label(receipt->error),
        receipt->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
