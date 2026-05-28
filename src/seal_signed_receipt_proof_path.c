#include "latticra/seal_signed_receipt_proof_path.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static size_t bounded_string_len(const char *value, size_t max_len, int *terminated) {
    size_t i;

    if (terminated != NULL) {
        *terminated = 0;
    }
    if (value == NULL) {
        return 0u;
    }
    for (i = 0u; i < max_len; ++i) {
        if (value[i] == '\0') {
            if (terminated != NULL) {
                *terminated = 1;
            }
            return i;
        }
    }
    return max_len;
}

static int text_field_valid(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);

    return terminated == 1 && len > 0u;
}

static int text_field_terminated(const char *value, size_t max_len) {
    int terminated = 0;

    (void)bounded_string_len(value, max_len, &terminated);
    return terminated == 1;
}

static int bounded_string_is(const char *value, size_t max_len, const char *expected) {
    int terminated = 0;
    size_t value_len;
    size_t expected_len;

    if (value == NULL || expected == NULL) {
        return 0;
    }
    value_len = bounded_string_len(value, max_len, &terminated);
    if (terminated != 1) {
        return 0;
    }
    expected_len = strlen(expected);
    return value_len == expected_len && memcmp(value, expected, value_len) == 0;
}

static int bounded_strings_match(
    const char *left,
    size_t left_max,
    const char *right,
    size_t right_max) {
    int left_terminated = 0;
    int right_terminated = 0;
    size_t left_len;
    size_t right_len;

    left_len = bounded_string_len(left, left_max, &left_terminated);
    right_len = bounded_string_len(right, right_max, &right_terminated);
    if (left_terminated != 1 || right_terminated != 1) {
        return 0;
    }
    if (left_len == 0u || left_len != right_len) {
        return 0;
    }
    return memcmp(left, right, left_len) == 0;
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int proof_path_error_valid(latticra_seal_signed_receipt_proof_path_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_RECEIPT:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_NOT_VERIFIED:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_AUTHORITY_NOT_NEUTRAL:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_SIGNING_OPERATION:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SIGNING_OPERATION_NOT_METADATA_ONLY:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MISMATCH:
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH:
        return 1;
    default:
        return 0;
    }
}

static int receipt_strings_valid(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return bounded_string_is(receipt->receipt_profile,
                             LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX,
                             "latticra-seal-verified-receipt/0.1") &&
           text_field_valid(receipt->verify_profile,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_PROFILE_MAX) &&
           text_field_valid(receipt->message_digest_algorithm,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_ALGORITHM_MAX) &&
           text_field_valid(receipt->message_digest_hex,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_DIGEST_MAX) &&
           text_field_valid(receipt->public_key_identity_label,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_LABEL_MAX) &&
           text_field_valid(receipt->signature_algorithm,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_ALGORITHM_MAX) &&
           text_field_valid(receipt->trust_source,
                            LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX) &&
           bounded_string_is(receipt->verification_state,
                             LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX,
                             "verified") &&
           bounded_string_is(receipt->receipt_state,
                             LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX,
                             "verified") &&
           bounded_string_is(receipt->status,
                             LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_STATE_MAX,
                             "verified-receipt-metadata");
}

static int receipt_flags_valid(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return boolean_flag_valid(receipt->cryptographic_verification_supported) &&
           boolean_flag_valid(receipt->cryptographic_verification_performed) &&
           boolean_flag_valid(receipt->verified) &&
           boolean_flag_valid(receipt->invalid) &&
           boolean_flag_valid(receipt->authority_usable) &&
           boolean_flag_valid(receipt->capability_gate_allowed) &&
           boolean_flag_valid(receipt->runtime_authority_granted);
}

static int receipt_verified(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return receipt->error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK &&
           receipt->cryptographic_verification_supported == 1u &&
           receipt->cryptographic_verification_performed == 1u &&
           receipt->verified == 1u &&
           receipt->invalid == 0u;
}

static int receipt_authority_neutral(
    const latticra_seal_verified_receipt_promotion_t *receipt) {
    return latticra_seal_verified_receipt_promotion_is_authority_neutral(receipt) == 1;
}

const char *latticra_seal_signed_receipt_proof_path_error_label(
    latticra_seal_signed_receipt_proof_path_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_RECEIPT:
        return "invalid-receipt";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_NOT_VERIFIED:
        return "receipt-not-verified";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_AUTHORITY_NOT_NEUTRAL:
        return "receipt-authority-not-neutral";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_SIGNING_OPERATION:
        return "invalid-signing-operation";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SIGNING_OPERATION_NOT_METADATA_ONLY:
        return "signing-operation-not-metadata-only";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MISMATCH:
        return "digest-mismatch";
    case LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH:
        return "public-key-mismatch";
    default:
        return "unknown";
    }
}

static void proof_path_init(latticra_seal_signed_receipt_proof_path_t *proof_path) {
    memset(proof_path, 0, sizeof(*proof_path));
    copy_literal(proof_path->proof_path_profile,
                 sizeof(proof_path->proof_path_profile),
                 "latticra-seal-signed-receipt-proof-path/0.1");
    copy_literal(proof_path->proof_path_state,
                 sizeof(proof_path->proof_path_state),
                 "invalid-input");
    proof_path->trust_root_required = 1u;
    proof_path->revocation_required = 1u;
    proof_path->error = LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_INPUT;
    copy_literal(proof_path->status, sizeof(proof_path->status), "invalid-input");
}

static void deny(
    latticra_seal_signed_receipt_proof_path_t *proof_path,
    latticra_seal_signed_receipt_proof_path_error_t error,
    const char *state) {
    proof_path->error = error;
    copy_literal(proof_path->proof_path_state, sizeof(proof_path->proof_path_state), state);
    copy_literal(proof_path->status, sizeof(proof_path->status), state);
}

static void copy_metadata(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const latticra_seal_signing_operation_t *operation,
    latticra_seal_signed_receipt_proof_path_t *out) {
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), receipt->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), receipt->verify_profile);
    copy_literal(out->signing_operation_profile,
                 sizeof(out->signing_operation_profile),
                 operation->signing_operation_profile);
    copy_literal(out->signer_invocation_profile,
                 sizeof(out->signer_invocation_profile),
                 operation->signer_invocation_profile);
    copy_literal(out->message_digest_algorithm,
                 sizeof(out->message_digest_algorithm),
                 receipt->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), receipt->message_digest_hex);
    copy_literal(out->public_key_identity_label,
                 sizeof(out->public_key_identity_label),
                 receipt->public_key_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), receipt->signature_algorithm);
    copy_literal(out->trust_source, sizeof(out->trust_source), receipt->trust_source);
    copy_literal(out->verification_state, sizeof(out->verification_state), receipt->verification_state);
    copy_literal(out->receipt_state, sizeof(out->receipt_state), receipt->receipt_state);
    copy_literal(out->signing_operation_state,
                 sizeof(out->signing_operation_state),
                 operation->signing_operation_state);
    out->local_verify_result_present = 1u;
    out->receipt_promotion_present = 1u;
    out->signing_operation_present = 1u;
    out->receipt_verified = receipt->verified;
    out->cryptographic_verification_supported = receipt->cryptographic_verification_supported;
    out->cryptographic_verification_performed = receipt->cryptographic_verification_performed;
    out->signing_operation_ready = operation->signing_operation_ready;
    out->signing_operation_metadata_only = 1u;
    out->digest_matches = 1u;
    out->public_key_matches = 1u;
    out->trust_root_required = 1u;
    out->trust_root_verified = 0u;
    out->revocation_required = 1u;
    out->revocation_checked = 0u;
    out->verification_only = 1u;
    out->proof_path_verified = 0u;
    out->authority_usable = 0u;
    out->capability_gate_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->signature_performed = 0u;
    out->signer_invoked = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
}

latticra_status_t latticra_seal_signed_receipt_proof_path_from_metadata(
    const latticra_seal_verified_receipt_promotion_t *receipt,
    const latticra_seal_signing_operation_t *operation,
    latticra_seal_signed_receipt_proof_path_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    proof_path_init(out);

    if (receipt == NULL || operation == NULL) {
        return LATTICRA_STATUS_OK;
    }
    if (!receipt_strings_valid(receipt) || !receipt_flags_valid(receipt)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_RECEIPT,
             "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }
    if (!receipt_verified(receipt)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_NOT_VERIFIED,
             "receipt-not-verified");
        return LATTICRA_STATUS_OK;
    }
    if (!receipt_authority_neutral(receipt)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_RECEIPT_AUTHORITY_NOT_NEUTRAL,
             "receipt-authority-not-neutral");
        return LATTICRA_STATUS_OK;
    }
    if (!latticra_seal_signing_operation_is_metadata_only(operation)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SIGNING_OPERATION_NOT_METADATA_ONLY,
             "signing-operation-not-metadata-only");
        return LATTICRA_STATUS_OK;
    }
    if (operation->error != LATTICRA_SEAL_SIGNING_OPERATION_OK ||
        operation->signing_operation_ready != 1u) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_INVALID_SIGNING_OPERATION,
             "invalid-signing-operation");
        return LATTICRA_STATUS_OK;
    }
    if (!bounded_strings_match(receipt->message_digest_hex,
                               LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_DIGEST_MAX,
                               operation->message_digest_hex,
                               LATTICRA_SEAL_SIGNING_OPERATION_DIGEST_MAX)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MISMATCH,
             "digest-mismatch");
        return LATTICRA_STATUS_OK;
    }
    if (!bounded_strings_match(receipt->public_key_identity_label,
                               LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_LABEL_MAX,
                               operation->public_key_identity_label,
                               LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX)) {
        deny(out,
             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PUBLIC_KEY_MISMATCH,
             "public-key-mismatch");
        return LATTICRA_STATUS_OK;
    }

    copy_metadata(receipt, operation, out);
    out->error = LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK;
    copy_literal(out->proof_path_state,
                 sizeof(out->proof_path_state),
                 "verification-only");
    copy_literal(out->status,
                 sizeof(out->status),
                 "signed-receipt-proof-path-verification-only");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signed_receipt_proof_path_is_verification_only(
    const latticra_seal_signed_receipt_proof_path_t *proof_path) {
    if (proof_path == NULL) {
        return 0;
    }

    return proof_path_error_valid(proof_path->error) &&
           proof_path->error == LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_OK &&
           bounded_string_is(proof_path->proof_path_profile,
                             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX,
                             "latticra-seal-signed-receipt-proof-path/0.1") &&
           text_field_terminated(proof_path->receipt_profile,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX) &&
           text_field_terminated(proof_path->verify_profile,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX) &&
           text_field_terminated(proof_path->signing_operation_profile,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX) &&
           text_field_terminated(proof_path->signer_invocation_profile,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_PROFILE_MAX) &&
           text_field_terminated(proof_path->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_ALGORITHM_MAX) &&
           text_field_terminated(proof_path->message_digest_hex,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_DIGEST_MAX) &&
           text_field_terminated(proof_path->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_LABEL_MAX) &&
           text_field_terminated(proof_path->signature_algorithm,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_ALGORITHM_MAX) &&
           text_field_terminated(proof_path->trust_source,
                                 LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX) &&
           bounded_string_is(proof_path->proof_path_state,
                             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX,
                             "verification-only") &&
           bounded_string_is(proof_path->status,
                             LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_STATE_MAX,
                             "signed-receipt-proof-path-verification-only") &&
           proof_path->local_verify_result_present == 1u &&
           proof_path->receipt_promotion_present == 1u &&
           proof_path->signing_operation_present == 1u &&
           proof_path->receipt_verified == 1u &&
           proof_path->cryptographic_verification_supported == 1u &&
           proof_path->cryptographic_verification_performed == 1u &&
           proof_path->signing_operation_ready == 1u &&
           proof_path->signing_operation_metadata_only == 1u &&
           proof_path->digest_matches == 1u &&
           proof_path->public_key_matches == 1u &&
           proof_path->trust_root_required == 1u &&
           proof_path->trust_root_verified == 0u &&
           proof_path->revocation_required == 1u &&
           proof_path->revocation_checked == 0u &&
           proof_path->verification_only == 1u &&
           proof_path->proof_path_verified == 0u &&
           proof_path->authority_usable == 0u &&
           proof_path->capability_gate_allowed == 0u &&
           proof_path->runtime_authority_granted == 0u &&
           proof_path->signature_performed == 0u &&
           proof_path->signer_invoked == 0u &&
           proof_path->private_key_handling == 0u &&
           proof_path->key_generation_performed == 0u &&
           proof_path->trust_store_loaded == 0u &&
           proof_path->revocation_lookup_performed == 0u &&
           proof_path->handoff_performed == 0u &&
           proof_path->effect_performed == 0u &&
           proof_path->host_read_performed == 0u &&
           proof_path->host_write_performed == 0u &&
           proof_path->network_performed == 0u;
}

latticra_status_t latticra_seal_signed_receipt_proof_path_render(
    const latticra_seal_signed_receipt_proof_path_t *proof_path,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (proof_path == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signed_receipt_proof_path_is_verification_only(proof_path)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNED RECEIPT PROOF PATH\n"
        "proof_path_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "signing_operation_profile=%s\n"
        "signer_invocation_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "signature_algorithm=%s\n"
        "trust_source=%s\n"
        "verification_state=%s\n"
        "receipt_state=%s\n"
        "signing_operation_state=%s\n"
        "proof_path_state=%s\n"
        "local_verify_result_present=%u\n"
        "receipt_promotion_present=%u\n"
        "signing_operation_present=%u\n"
        "receipt_verified=%u\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "signing_operation_ready=%u\n"
        "signing_operation_metadata_only=%u\n"
        "digest_matches=%u\n"
        "public_key_matches=%u\n"
        "trust_root_required=%u\n"
        "trust_root_verified=%u\n"
        "revocation_required=%u\n"
        "revocation_checked=%u\n"
        "verification_only=%u\n"
        "proof_path_verified=%u\n"
        "authority_usable=%u\n"
        "capability_gate_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "signature_performed=%u\n"
        "signer_invoked=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "trust_store_loaded=%u\n"
        "revocation_lookup_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        proof_path->proof_path_profile,
        proof_path->receipt_profile,
        proof_path->verify_profile,
        proof_path->signing_operation_profile,
        proof_path->signer_invocation_profile,
        proof_path->message_digest_algorithm,
        proof_path->message_digest_hex,
        proof_path->public_key_identity_label,
        proof_path->signature_algorithm,
        proof_path->trust_source,
        proof_path->verification_state,
        proof_path->receipt_state,
        proof_path->signing_operation_state,
        proof_path->proof_path_state,
        proof_path->local_verify_result_present,
        proof_path->receipt_promotion_present,
        proof_path->signing_operation_present,
        proof_path->receipt_verified,
        proof_path->cryptographic_verification_supported,
        proof_path->cryptographic_verification_performed,
        proof_path->signing_operation_ready,
        proof_path->signing_operation_metadata_only,
        proof_path->digest_matches,
        proof_path->public_key_matches,
        proof_path->trust_root_required,
        proof_path->trust_root_verified,
        proof_path->revocation_required,
        proof_path->revocation_checked,
        proof_path->verification_only,
        proof_path->proof_path_verified,
        proof_path->authority_usable,
        proof_path->capability_gate_allowed,
        proof_path->runtime_authority_granted,
        proof_path->signature_performed,
        proof_path->signer_invoked,
        proof_path->private_key_handling,
        proof_path->key_generation_performed,
        proof_path->trust_store_loaded,
        proof_path->revocation_lookup_performed,
        proof_path->handoff_performed,
        proof_path->effect_performed,
        proof_path->host_read_performed,
        proof_path->host_write_performed,
        proof_path->network_performed,
        latticra_seal_signed_receipt_proof_path_error_label(proof_path->error),
        proof_path->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
