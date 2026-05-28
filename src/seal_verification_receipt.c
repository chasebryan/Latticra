#include "latticra/seal_verification_receipt.h"

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

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int verification_receipt_error_valid(
    latticra_seal_verification_receipt_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_OK:
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT:
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY:
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST:
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER:
    case LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY:
        return 1;
    default:
        return 0;
    }
}

static int verification_policy_error_valid(
    latticra_seal_verification_policy_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFICATION_POLICY_OK:
    case LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT:
    case LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE:
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST:
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER:
    case LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY:
    case LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM:
        return 1;
    default:
        return 0;
    }
}

static int verification_policy_flags_valid(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return boolean_flag_valid(policy->cryptographic_verification_supported) &&
           boolean_flag_valid(policy->cryptographic_verification_performed) &&
           boolean_flag_valid(policy->public_key_material_handling) &&
           boolean_flag_valid(policy->private_key_handling) &&
           boolean_flag_valid(policy->network_lookup_allowed) &&
           boolean_flag_valid(policy->revocation_lookup_allowed) &&
           boolean_flag_valid(policy->runtime_authority_granted);
}

static int verification_policy_effects_clear(
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

static int verification_policy_strings_valid(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return bounded_string_is(policy->verification_policy_profile,
                             LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX,
                             "latticra-seal-verification-policy/0.1") &&
           text_field_terminated(policy->signature_profile,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX) &&
           text_field_terminated(policy->manifest_profile,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_PROFILE_MAX) &&
           text_field_terminated(policy->artifact_digest_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX) &&
           text_field_terminated(policy->artifact_digest_hex,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_DIGEST_MAX) &&
           text_field_terminated(policy->signer_identity_label,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX) &&
           text_field_terminated(policy->signature_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX) &&
           text_field_terminated(policy->public_key_identity_label,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX) &&
           text_field_valid(policy->trust_source,
                            LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX) &&
           bounded_string_is(policy->verification_state,
                             LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX,
                             "unsupported") &&
           verification_policy_error_valid(policy->error) &&
           verification_policy_flags_valid(policy) &&
           verification_policy_effects_clear(policy) &&
           text_field_valid(policy->status,
                            LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX);
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

    if (!verification_policy_strings_valid(policy)) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY;
        copy_literal(out->status, sizeof(out->status), "invalid-policy");
        return LATTICRA_STATUS_OK;
    }

    if (policy->error != LATTICRA_SEAL_VERIFICATION_POLICY_OK) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY;
        copy_literal(out->status, sizeof(out->status), "invalid-policy");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(policy->artifact_digest_hex,
                          LATTICRA_SEAL_VERIFICATION_POLICY_DIGEST_MAX)) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(policy->signer_identity_label,
                          LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(policy->public_key_identity_label,
                          LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    if (!bounded_string_is(policy->signature_algorithm,
                           LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX,
                           "Ed25519-development") ||
        !bounded_string_is(policy->status,
                           LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX,
                           "verification-policy-metadata")) {
        out->error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY;
        copy_literal(out->status, sizeof(out->status), "invalid-policy");
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

static int verification_receipt_flags_valid(
    const latticra_seal_verification_receipt_t *receipt) {
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

static int verification_receipt_effects_clear(
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

static int verification_receipt_state_valid(
    const latticra_seal_verification_receipt_t *receipt) {
    if (receipt == NULL || !verification_receipt_error_valid(receipt->error)) {
        return 0;
    }
    if (receipt->error == LATTICRA_SEAL_VERIFICATION_RECEIPT_OK) {
        return text_field_valid(receipt->artifact_digest_hex,
                                LATTICRA_SEAL_VERIFICATION_RECEIPT_DIGEST_MAX) &&
               text_field_valid(receipt->signer_identity_label,
                                LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX) &&
               text_field_valid(receipt->public_key_identity_label,
                                LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX) &&
               bounded_string_is(receipt->signature_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX,
                                 "Ed25519-development") &&
               bounded_string_is(receipt->status,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX,
                                 "verification-receipt-metadata");
    }

    return text_field_valid(receipt->status,
                            LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX);
}

static int verification_receipt_record_valid(
    const latticra_seal_verification_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return verification_receipt_effects_clear(receipt) &&
           verification_receipt_flags_valid(receipt) &&
           verification_receipt_state_valid(receipt) &&
           bounded_string_is(receipt->receipt_profile,
                             LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX,
                             "latticra-seal-verification-receipt/0.1") &&
           text_field_terminated(receipt->verification_policy_profile,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX) &&
           text_field_terminated(receipt->signature_profile,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX) &&
           text_field_terminated(receipt->manifest_profile,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_PROFILE_MAX) &&
           text_field_terminated(receipt->artifact_digest_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX) &&
           text_field_terminated(receipt->artifact_digest_hex,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_DIGEST_MAX) &&
           text_field_terminated(receipt->signer_identity_label,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX) &&
           text_field_terminated(receipt->signature_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_ALGORITHM_MAX) &&
           text_field_terminated(receipt->public_key_identity_label,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX) &&
           text_field_terminated(receipt->trust_source,
                                 LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX) &&
           bounded_string_is(receipt->verification_state,
                             LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX,
                             "unsupported") &&
           bounded_string_is(receipt->receipt_state,
                             LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX,
                             "unverified-metadata");
}

int latticra_seal_verification_receipt_is_unverified_metadata(
    const latticra_seal_verification_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return verification_receipt_record_valid(receipt);
}

latticra_status_t latticra_seal_verification_receipt_report(
    const latticra_seal_verification_receipt_t *receipt,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (receipt == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!verification_receipt_record_valid(receipt)) {
        buffer[0] = '\0';
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
