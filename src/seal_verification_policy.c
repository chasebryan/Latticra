#include "latticra/seal_verification_policy.h"

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

static int signature_error_valid(latticra_seal_signature_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_OK:
    case LATTICRA_SEAL_SIGNATURE_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNATURE_INVALID_MANIFEST:
    case LATTICRA_SEAL_SIGNATURE_MISSING_DIGEST:
    case LATTICRA_SEAL_SIGNATURE_MISSING_SIGNER:
    case LATTICRA_SEAL_SIGNATURE_UNSUPPORTED_ALGORITHM:
    case LATTICRA_SEAL_SIGNATURE_MISSING_SIGNATURE_METADATA:
        return 1;
    default:
        return 0;
    }
}

static int signature_flags_valid(const latticra_seal_signature_t *signature) {
    if (signature == NULL) {
        return 0;
    }

    return boolean_flag_valid(signature->signature_supported) &&
           boolean_flag_valid(signature->verification_supported) &&
           boolean_flag_valid(signature->private_key_handling) &&
           boolean_flag_valid(signature->network_lookup_allowed) &&
           boolean_flag_valid(signature->runtime_authority_granted);
}

static int signature_strings_valid(const latticra_seal_signature_t *signature) {
    if (signature == NULL) {
        return 0;
    }

    return bounded_string_is(signature->signature_profile,
                             LATTICRA_SEAL_SIGNATURE_PROFILE_MAX,
                             "latticra-seal-signature/0.1") &&
           text_field_terminated(signature->manifest_profile,
                                 LATTICRA_SEAL_SIGNATURE_PROFILE_MAX) &&
           text_field_terminated(signature->manifest_kind,
                                 LATTICRA_SEAL_SIGNATURE_LABEL_MAX) &&
           text_field_terminated(signature->artifact_digest_algorithm,
                                 LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX) &&
           text_field_terminated(signature->artifact_digest_hex,
                                 LATTICRA_SEAL_MANIFEST_DIGEST_MAX) &&
           text_field_terminated(signature->signer_identity_label,
                                 LATTICRA_SEAL_SIGNATURE_LABEL_MAX) &&
           text_field_terminated(signature->signature_algorithm,
                                 LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX) &&
           bounded_string_is(signature->signature_state,
                             LATTICRA_SEAL_SIGNATURE_STATE_MAX,
                             "metadata-only") &&
           signature_error_valid(signature->error) &&
           signature_flags_valid(signature) &&
           text_field_valid(signature->status,
                            LATTICRA_SEAL_SIGNATURE_STATE_MAX);
}

static int public_key_identity_present(const char *public_key_identity_label) {
    return public_key_identity_label != NULL && public_key_identity_label[0] != '\0';
}

static const char *safe_trust_source_for_copy(const char *trust_source) {
    if (trust_source == NULL || trust_source[0] == '\0') {
        return "local-metadata-only";
    }
    if (!text_field_valid(trust_source,
                          LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX)) {
        return "invalid-trust-source";
    }
    return trust_source;
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

    if (!signature_strings_valid(signature)) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE;
        copy_literal(out->status, sizeof(out->status), "invalid-signature");
        return LATTICRA_STATUS_OK;
    }

    if (signature->error != LATTICRA_SEAL_SIGNATURE_OK) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE;
        copy_literal(out->status, sizeof(out->status), "invalid-signature");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(signature->artifact_digest_hex,
                          LATTICRA_SEAL_MANIFEST_DIGEST_MAX)) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(signature->signer_identity_label,
                          LATTICRA_SEAL_SIGNATURE_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (!bounded_string_is(signature->signature_algorithm,
                           LATTICRA_SEAL_SIGNATURE_ALGORITHM_MAX,
                           "Ed25519-development")) {
        out->error = LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM;
        copy_literal(out->status, sizeof(out->status), "unsupported-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!public_key_identity_present(public_key_identity_label) ||
        !text_field_valid(public_key_identity_label,
                          LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX)) {
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
        safe_trust_source_for_copy(trust_source));
    out->error = LATTICRA_SEAL_VERIFICATION_POLICY_OK;
    copy_literal(out->status, sizeof(out->status), "verification-policy-metadata");
    return LATTICRA_STATUS_OK;
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

static int verification_policy_state_valid(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL || !verification_policy_error_valid(policy->error)) {
        return 0;
    }
    if (policy->error == LATTICRA_SEAL_VERIFICATION_POLICY_OK) {
        return bounded_string_is(policy->signature_algorithm,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_ALGORITHM_MAX,
                                 "Ed25519-development") &&
               text_field_valid(policy->artifact_digest_hex,
                                LATTICRA_SEAL_VERIFICATION_POLICY_DIGEST_MAX) &&
               text_field_valid(policy->signer_identity_label,
                                LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX) &&
               text_field_valid(policy->public_key_identity_label,
                                LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX) &&
               bounded_string_is(policy->status,
                                 LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX,
                                 "verification-policy-metadata");
    }

    return text_field_valid(policy->status,
                            LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX);
}

static int verification_policy_record_valid(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return verification_policy_effects_clear(policy) &&
           verification_policy_flags_valid(policy) &&
           verification_policy_state_valid(policy) &&
           bounded_string_is(policy->verification_policy_profile,
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
                             "unsupported");
}

int latticra_seal_verification_policy_is_metadata_only(
    const latticra_seal_verification_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return verification_policy_record_valid(policy);
}

latticra_status_t latticra_seal_verification_policy_report(
    const latticra_seal_verification_policy_t *policy,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (policy == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!verification_policy_record_valid(policy)) {
        buffer[0] = '\0';
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
