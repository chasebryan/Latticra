#include "latticra/seal_capability_gate.h"

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

static int capability_gate_error_valid(latticra_seal_capability_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CAPABILITY_GATE_OK:
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT:
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT:
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST:
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER:
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY:
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY:
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT:
        return 1;
    default:
        return 0;
    }
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

static int verification_receipt_strings_valid(
    const latticra_seal_verification_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return bounded_string_is(receipt->receipt_profile,
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
           text_field_valid(receipt->receipt_state,
                            LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX) &&
           verification_receipt_error_valid(receipt->error) &&
           verification_receipt_flags_valid(receipt) &&
           verification_receipt_effects_clear(receipt) &&
           text_field_valid(receipt->status,
                            LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX);
}

static int requested_label_present(const char *label) {
    return label != NULL && label[0] != '\0';
}

static const char *safe_requested_scope_for_copy(const char *requested_scope) {
    if (!requested_label_present(requested_scope)) {
        return "unspecified-scope";
    }
    if (!text_field_valid(requested_scope, LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX)) {
        return "invalid-scope";
    }
    return requested_scope;
}

const char *latticra_seal_capability_gate_error_label(
    latticra_seal_capability_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CAPABILITY_GATE_OK:
        return "ok";
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT:
        return "invalid-receipt";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY:
        return "missing-requested-capability";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    default:
        return "unknown";
    }
}

static void gate_init(latticra_seal_capability_gate_t *gate) {
    memset(gate, 0, sizeof(*gate));
    copy_literal(gate->gate_profile, sizeof(gate->gate_profile), "latticra-seal-capability-gate/0.1");
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "denied-unverified");
    gate->verified = 0u;
    gate->authority_usable = 0u;
    gate->receipt_capability_gate_allowed = 0u;
    gate->gate_allowed = 0u;
    gate->runtime_authority_granted = 0u;
    gate->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT;
    copy_literal(gate->status, sizeof(gate->status), "invalid-input");
}

latticra_status_t latticra_seal_capability_gate_from_receipt(
    const latticra_seal_verification_receipt_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_capability_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);

    if (receipt == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!verification_receipt_strings_valid(receipt)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT;
        copy_literal(out->status, sizeof(out->status), "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (receipt->error != LATTICRA_SEAL_VERIFICATION_RECEIPT_OK) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT;
        copy_literal(out->status, sizeof(out->status), "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(receipt->artifact_digest_hex,
                          LATTICRA_SEAL_VERIFICATION_RECEIPT_DIGEST_MAX)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(receipt->signer_identity_label,
                          LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(receipt->public_key_identity_label,
                          LATTICRA_SEAL_VERIFICATION_RECEIPT_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    if (!bounded_string_is(receipt->receipt_state,
                           LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX,
                           "unverified-metadata") ||
        !bounded_string_is(receipt->status,
                           LATTICRA_SEAL_VERIFICATION_RECEIPT_STATE_MAX,
                           "verification-receipt-metadata")) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT;
        copy_literal(out->status, sizeof(out->status), "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_label_present(requested_capability) ||
        !text_field_valid(requested_capability,
                          LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_label_present(requested_effect) ||
        !text_field_valid(requested_effect,
                          LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT;
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), receipt->receipt_profile);
    copy_literal(out->verification_policy_profile, sizeof(out->verification_policy_profile), receipt->verification_policy_profile);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), receipt->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), receipt->artifact_digest_hex);
    copy_literal(out->signer_identity_label, sizeof(out->signer_identity_label), receipt->signer_identity_label);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), receipt->public_key_identity_label);
    copy_literal(out->receipt_state, sizeof(out->receipt_state), receipt->receipt_state);
    copy_literal(out->verification_state, sizeof(out->verification_state), receipt->verification_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), requested_effect);
    copy_literal(
        out->requested_scope,
        sizeof(out->requested_scope),
        safe_requested_scope_for_copy(requested_scope));
    out->verified = receipt->verified;
    out->authority_usable = receipt->authority_usable;
    out->receipt_capability_gate_allowed = receipt->capability_gate_allowed;
    out->gate_allowed = 0u;
    copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unverified");
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_CAPABILITY_GATE_OK;
    copy_literal(out->status, sizeof(out->status), "capability-gate-denied-metadata");
    return LATTICRA_STATUS_OK;
}

static int capability_gate_flags_valid(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return boolean_flag_valid(gate->verified) &&
           boolean_flag_valid(gate->authority_usable) &&
           boolean_flag_valid(gate->receipt_capability_gate_allowed) &&
           boolean_flag_valid(gate->gate_allowed) &&
           boolean_flag_valid(gate->runtime_authority_granted);
}

static int capability_gate_effects_clear(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->verified == 0u &&
           gate->authority_usable == 0u &&
           gate->receipt_capability_gate_allowed == 0u &&
           gate->gate_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

static int capability_gate_state_valid(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL || !capability_gate_error_valid(gate->error)) {
        return 0;
    }
    if (gate->error == LATTICRA_SEAL_CAPABILITY_GATE_OK) {
        return text_field_valid(gate->artifact_digest_hex,
                                LATTICRA_SEAL_CAPABILITY_GATE_DIGEST_MAX) &&
               text_field_valid(gate->signer_identity_label,
                                LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
               text_field_valid(gate->public_key_identity_label,
                                LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
               text_field_valid(gate->requested_capability,
                                LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
               text_field_valid(gate->requested_effect,
                                LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
               bounded_string_is(gate->receipt_state,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                                 "unverified-metadata") &&
               bounded_string_is(gate->verification_state,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                                 "unsupported") &&
               bounded_string_is(gate->gate_state,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                                 "denied-unverified") &&
               bounded_string_is(gate->status,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                                 "capability-gate-denied-metadata");
    }

    return text_field_valid(gate->status, LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX);
}

static int capability_gate_record_valid(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return capability_gate_effects_clear(gate) &&
           capability_gate_flags_valid(gate) &&
           capability_gate_state_valid(gate) &&
           bounded_string_is(gate->gate_profile,
                             LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX,
                             "latticra-seal-capability-gate/0.1") &&
           text_field_terminated(gate->receipt_profile,
                                 LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX) &&
           text_field_terminated(gate->verification_policy_profile,
                                 LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX) &&
           text_field_terminated(gate->artifact_digest_algorithm,
                                 LATTICRA_SEAL_CAPABILITY_GATE_ALGORITHM_MAX) &&
           text_field_terminated(gate->artifact_digest_hex,
                                 LATTICRA_SEAL_CAPABILITY_GATE_DIGEST_MAX) &&
           text_field_terminated(gate->signer_identity_label,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->public_key_identity_label,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->receipt_state,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX) &&
           text_field_terminated(gate->verification_state,
                                 LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX) &&
           text_field_terminated(gate->requested_capability,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->requested_effect,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->requested_scope,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_valid(gate->gate_state,
                            LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX);
}

int latticra_seal_capability_gate_is_denied_metadata(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return capability_gate_record_valid(gate);
}

latticra_status_t latticra_seal_capability_gate_report(
    const latticra_seal_capability_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!capability_gate_record_valid(gate)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL CAPABILITY GATE\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verification_policy_profile=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "signer_identity_label=%s\n"
        "public_key_identity_label=%s\n"
        "receipt_state=%s\n"
        "verification_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        gate->gate_profile,
        gate->receipt_profile,
        gate->verification_policy_profile,
        gate->artifact_digest_algorithm,
        gate->artifact_digest_hex,
        gate->signer_identity_label,
        gate->public_key_identity_label,
        gate->receipt_state,
        gate->verification_state,
        gate->requested_capability,
        gate->requested_effect,
        gate->requested_scope,
        gate->verified,
        gate->authority_usable,
        gate->receipt_capability_gate_allowed,
        gate->gate_allowed,
        gate->gate_state,
        gate->runtime_authority_granted,
        latticra_seal_capability_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
