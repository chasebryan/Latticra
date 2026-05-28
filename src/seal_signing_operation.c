#include "latticra/seal_signing_operation.h"

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

static int is_allowed_signature(const char *signature) {
    return bounded_string_is(signature,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_signing_operation(const char *operation) {
    return bounded_string_is(operation,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int operation_error_valid(latticra_seal_signing_operation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNING_OPERATION_OK:
    case LATTICRA_SEAL_SIGNING_OPERATION_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int invocation_crypto_graduation_gate_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }
    if (invocation->crypto_graduation_gate_present == 0u) {
        return 1;
    }

    return invocation->crypto_graduation_gate_passed == 1u &&
           invocation->standard_expectations_met == 1u &&
           invocation->local_verify_graduated == 1u &&
           invocation->receipt_promotion_graduated == 1u &&
           invocation->authority_promotion_allowed == 0u &&
           bounded_string_is(invocation->crypto_graduation_gate_state,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "graduated-authority-neutral");
}

static int operation_crypto_graduation_gate_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }
    if (operation->crypto_graduation_gate_present == 0u) {
        return 1;
    }

    return operation->crypto_graduation_gate_passed == 1u &&
           operation->standard_expectations_met == 1u &&
           operation->local_verify_graduated == 1u &&
           operation->receipt_promotion_graduated == 1u &&
           operation->authority_promotion_allowed == 0u &&
           bounded_string_is(operation->crypto_graduation_gate_state,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "graduated-authority-neutral");
}

static int invocation_error_valid(latticra_seal_signer_invocation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNER_INVOCATION_OK:
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int invocation_flags_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }

    return boolean_flag_valid(invocation->crypto_graduation_gate_present) &&
           boolean_flag_valid(invocation->crypto_graduation_gate_passed) &&
           boolean_flag_valid(invocation->standard_expectations_met) &&
           boolean_flag_valid(invocation->local_verify_graduated) &&
           boolean_flag_valid(invocation->receipt_promotion_graduated) &&
           boolean_flag_valid(invocation->authority_promotion_allowed) &&
           boolean_flag_valid(invocation->signing_authorization_ready) &&
           boolean_flag_valid(invocation->signer_handoff_ready) &&
           boolean_flag_valid(invocation->signer_invocation_ready) &&
           boolean_flag_valid(invocation->signature_performed) &&
           boolean_flag_valid(invocation->verification_performed) &&
           boolean_flag_valid(invocation->signer_invoked) &&
           boolean_flag_valid(invocation->private_key_handling) &&
           boolean_flag_valid(invocation->key_generation_performed) &&
           boolean_flag_valid(invocation->trust_store_loaded) &&
           boolean_flag_valid(invocation->revocation_lookup_performed) &&
           boolean_flag_valid(invocation->handoff_performed) &&
           boolean_flag_valid(invocation->effect_performed) &&
           boolean_flag_valid(invocation->runtime_authority_granted) &&
           boolean_flag_valid(invocation->host_read_performed) &&
           boolean_flag_valid(invocation->host_write_performed) &&
           boolean_flag_valid(invocation->network_performed);
}

static int invocation_state_fields_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }

    return text_field_valid(invocation->signing_authorization_state,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_valid(invocation->signer_handoff_state,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_valid(invocation->signer_invocation_state,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_valid(invocation->status,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX);
}

static int invocation_strings_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }

    return bounded_string_is(invocation->signer_invocation_profile,
                             LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX,
                             "latticra-seal-signer-invocation/0.1") &&
           text_field_terminated(invocation->signer_handoff_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->signing_authorization_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->signature_request_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->envelope_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->report_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->handoff_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->decision_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->gate_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->receipt_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->verify_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_ALGORITHM_MAX) &&
           text_field_terminated(invocation->message_digest_hex,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_DIGEST_MAX) &&
           text_field_terminated(invocation->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->crypto_graduation_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->assurance_baseline_profile,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
           text_field_terminated(invocation->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_terminated(invocation->requested_capability,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_effect,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_handoff,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_report,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_envelope,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_signature,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_signing_authorization,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_signer_handoff,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_signer_invocation,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           text_field_terminated(invocation->requested_scope,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) &&
           bounded_string_is(invocation->mode,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "metadata-only") &&
           invocation_error_valid(invocation->error) &&
           invocation_flags_valid(invocation) &&
           invocation_state_fields_valid(invocation);
}

static int requested_signing_operation_present(
    const char *requested_signing_operation) {
    return requested_signing_operation != NULL &&
           requested_signing_operation[0] != '\0';
}

static int operation_ready_state_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL ||
        !boolean_flag_valid(operation->signing_operation_ready)) {
        return 0;
    }
    if (operation->signing_operation_ready == 0u) {
        return operation->error != LATTICRA_SEAL_SIGNING_OPERATION_OK &&
               text_field_valid(operation->signing_operation_state,
                                LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
               text_field_valid(operation->status,
                                LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX);
    }

    return operation->error == LATTICRA_SEAL_SIGNING_OPERATION_OK &&
           operation->signing_authorization_ready == 1u &&
           operation->signer_handoff_ready == 1u &&
           operation->signer_invocation_ready == 1u &&
           operation_crypto_graduation_gate_valid(operation) &&
           bounded_string_is(operation->requested_signature,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "Ed25519-development") &&
           bounded_string_is(operation->requested_signing_authorization,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(operation->requested_signer_handoff,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(operation->requested_signer_invocation,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(operation->requested_signing_operation,
                             LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(operation->signing_authorization_state,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "authorized-metadata-only") &&
           bounded_string_is(operation->signer_handoff_state,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "handoff-metadata-only") &&
           bounded_string_is(operation->signer_invocation_state,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "invocation-metadata-only") &&
           bounded_string_is(operation->signing_operation_state,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "operation-metadata-only") &&
           bounded_string_is(operation->status,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "signing-operation-metadata");
}

static const char *safe_requested_signing_operation_for_copy(
    const char *requested_signing_operation) {
    if (!requested_signing_operation_present(requested_signing_operation)) {
        return NULL;
    }
    if (!text_field_valid(requested_signing_operation,
                          LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX)) {
        return "invalid-signing-operation";
    }
    return requested_signing_operation;
}

const char *latticra_seal_signing_operation_error_label(
    latticra_seal_signing_operation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNING_OPERATION_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNING_OPERATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION:
        return "invalid-signer-invocation";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION:
        return "denied-signing-operation";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNING_OPERATION_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void operation_init(latticra_seal_signing_operation_t *operation) {
    memset(operation, 0, sizeof(*operation));
    copy_literal(
        operation->signing_operation_profile,
        sizeof(operation->signing_operation_profile),
        "latticra-seal-signing-operation/0.1");
    copy_literal(
        operation->signing_operation_state,
        sizeof(operation->signing_operation_state),
        "denied-signer-invocation");
    copy_literal(operation->crypto_graduation_gate_state, sizeof(operation->crypto_graduation_gate_state), "not-required");
    operation->crypto_graduation_gate_present = 0u;
    operation->crypto_graduation_gate_passed = 0u;
    operation->standard_expectations_met = 0u;
    operation->local_verify_graduated = 0u;
    operation->receipt_promotion_graduated = 0u;
    operation->authority_promotion_allowed = 0u;
    copy_literal(operation->mode, sizeof(operation->mode), "metadata-only");
    operation->signing_authorization_ready = 0u;
    operation->signer_handoff_ready = 0u;
    operation->signer_invocation_ready = 0u;
    operation->signing_operation_ready = 0u;
    operation->signature_performed = 0u;
    operation->verification_performed = 0u;
    operation->signer_invoked = 0u;
    operation->private_key_handling = 0u;
    operation->key_generation_performed = 0u;
    operation->trust_store_loaded = 0u;
    operation->revocation_lookup_performed = 0u;
    operation->handoff_performed = 0u;
    operation->effect_performed = 0u;
    operation->runtime_authority_granted = 0u;
    operation->host_read_performed = 0u;
    operation->host_write_performed = 0u;
    operation->network_performed = 0u;
    operation->error = LATTICRA_SEAL_SIGNING_OPERATION_INVALID_INPUT;
    copy_literal(operation->status, sizeof(operation->status), "invalid-input");
}

static void copy_invocation_metadata(
    const latticra_seal_signer_invocation_t *invocation,
    const char *requested_signing_operation,
    latticra_seal_signing_operation_t *out) {
    copy_literal(out->signer_invocation_profile, sizeof(out->signer_invocation_profile), invocation->signer_invocation_profile);
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), invocation->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        invocation->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), invocation->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), invocation->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), invocation->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), invocation->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), invocation->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), invocation->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), invocation->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), invocation->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), invocation->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), invocation->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), invocation->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), invocation->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), invocation->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), invocation->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), invocation->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), invocation->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), invocation->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), invocation->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), invocation->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), invocation->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        invocation->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), invocation->requested_signer_handoff);
    copy_literal(out->requested_signer_invocation, sizeof(out->requested_signer_invocation), invocation->requested_signer_invocation);
    copy_literal(
        out->requested_signing_operation,
        sizeof(out->requested_signing_operation),
        safe_requested_signing_operation_for_copy(requested_signing_operation));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), invocation->requested_scope);
    out->crypto_graduation_gate_present = invocation->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = invocation->crypto_graduation_gate_passed;
    out->standard_expectations_met = invocation->standard_expectations_met;
    out->local_verify_graduated = invocation->local_verify_graduated;
    out->receipt_promotion_graduated = invocation->receipt_promotion_graduated;
    out->authority_promotion_allowed = invocation->authority_promotion_allowed;
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        invocation->signing_authorization_state);
    out->signing_authorization_ready = invocation->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), invocation->signer_handoff_state);
    out->signer_handoff_ready = invocation->signer_handoff_ready;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), invocation->signer_invocation_state);
    out->signer_invocation_ready = invocation->signer_invocation_ready;
    out->signature_performed = invocation->signature_performed;
    out->verification_performed = invocation->verification_performed;
    out->signer_invoked = invocation->signer_invoked;
    out->private_key_handling = invocation->private_key_handling;
    out->key_generation_performed = invocation->key_generation_performed;
    out->trust_store_loaded = invocation->trust_store_loaded;
    out->revocation_lookup_performed = invocation->revocation_lookup_performed;
    out->handoff_performed = invocation->handoff_performed;
    out->effect_performed = invocation->effect_performed;
    out->runtime_authority_granted = invocation->runtime_authority_granted;
    out->host_read_performed = invocation->host_read_performed;
    out->host_write_performed = invocation->host_write_performed;
    out->network_performed = invocation->network_performed;
}

latticra_status_t latticra_seal_signing_operation_from_invocation(
    const latticra_seal_signer_invocation_t *invocation,
    const char *requested_signing_operation,
    latticra_seal_signing_operation_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    operation_init(out);

    if (invocation == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!invocation_strings_valid(invocation)) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION;
        copy_literal(out->signing_operation_state,
                     sizeof(out->signing_operation_state),
                     "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "invalid-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    copy_invocation_metadata(invocation, requested_signing_operation, out);

    if (invocation->error != LATTICRA_SEAL_SIGNER_INVOCATION_OK) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "invalid-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (!invocation_crypto_graduation_gate_valid(invocation)) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->signer_invocation_ready != 1u ||
        !bounded_string_is(invocation->signer_invocation_state,
                           LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                           "invocation-metadata-only") ||
        !bounded_string_is(invocation->requested_signer_invocation,
                           LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->signer_handoff_ready != 1u ||
        !bounded_string_is(invocation->signer_handoff_state,
                           LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                           "handoff-metadata-only") ||
        !bounded_string_is(invocation->requested_signer_handoff,
                           LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->signing_authorization_ready != 1u ||
        !bounded_string_is(invocation->signing_authorization_state,
                           LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                           "authorized-metadata-only") ||
        !bounded_string_is(invocation->requested_signing_authorization,
                           LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->requested_signature[0] == '\0' ||
        !text_field_valid(invocation->requested_signature,
                          LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) ||
        !is_allowed_signature(invocation->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_signing_operation_present(requested_signing_operation)) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_signing_operation,
                          LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) ||
        !is_allowed_signing_operation(requested_signing_operation)) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "denied-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->private_key_handling != 0u ||
        invocation->key_generation_performed != 0u ||
        invocation->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->revocation_lookup_performed != 0u ||
        invocation->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (invocation->signature_performed != 0u ||
        invocation->verification_performed != 0u ||
        invocation->signer_invoked != 0u ||
        invocation->handoff_performed != 0u ||
        invocation->effect_performed != 0u ||
        invocation->host_read_performed != 0u ||
        invocation->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT;
        copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->signing_operation_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->signer_invoked = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_SIGNING_OPERATION_OK;
    copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), "operation-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signing-operation-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signing_operation_is_metadata_only(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }

    return operation->signature_performed == 0u &&
           operation->verification_performed == 0u &&
           operation->signer_invoked == 0u &&
           operation->private_key_handling == 0u &&
           operation->key_generation_performed == 0u &&
           operation->trust_store_loaded == 0u &&
           operation->revocation_lookup_performed == 0u &&
           operation->handoff_performed == 0u &&
           operation->effect_performed == 0u &&
           operation->runtime_authority_granted == 0u &&
           operation->host_read_performed == 0u &&
           operation->host_write_performed == 0u &&
           operation->network_performed == 0u &&
           operation_error_valid(operation->error) &&
           boolean_flag_valid(operation->crypto_graduation_gate_present) &&
           boolean_flag_valid(operation->crypto_graduation_gate_passed) &&
           boolean_flag_valid(operation->standard_expectations_met) &&
           boolean_flag_valid(operation->local_verify_graduated) &&
           boolean_flag_valid(operation->receipt_promotion_graduated) &&
           boolean_flag_valid(operation->authority_promotion_allowed) &&
           boolean_flag_valid(operation->signing_authorization_ready) &&
           boolean_flag_valid(operation->signer_handoff_ready) &&
           boolean_flag_valid(operation->signer_invocation_ready) &&
           operation_ready_state_valid(operation) &&
           bounded_string_is(operation->signing_operation_profile,
                             LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX,
                             "latticra-seal-signing-operation/0.1") &&
           text_field_terminated(operation->signer_invocation_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->signer_handoff_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->signing_authorization_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->signature_request_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->envelope_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->report_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->handoff_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->decision_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->gate_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->receipt_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->verify_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNING_OPERATION_ALGORITHM_MAX) &&
           text_field_terminated(operation->message_digest_hex,
                                 LATTICRA_SEAL_SIGNING_OPERATION_DIGEST_MAX) &&
           text_field_terminated(operation->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->crypto_graduation_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->assurance_baseline_profile,
                                 LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
           text_field_terminated(operation->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           operation_crypto_graduation_gate_valid(operation) &&
           text_field_terminated(operation->requested_capability,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_effect,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_handoff,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_report,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_envelope,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_signature,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_signing_authorization,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_signer_handoff,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_signer_invocation,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_signing_operation,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->requested_scope,
                                 LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) &&
           text_field_terminated(operation->signing_authorization_state,
                                 LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_terminated(operation->signer_handoff_state,
                                 LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_terminated(operation->signer_invocation_state,
                                 LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_valid(operation->signing_operation_state,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           bounded_string_is(operation->mode,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(operation->status,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX);
}

latticra_status_t latticra_seal_signing_operation_render(
    const latticra_seal_signing_operation_t *operation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (operation == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signing_operation_is_metadata_only(operation)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNING OPERATION\n"
        "signing_operation_profile=%s\n"
        "signer_invocation_profile=%s\n"
        "signer_handoff_profile=%s\n"
        "signing_authorization_profile=%s\n"
        "signature_request_profile=%s\n"
        "envelope_profile=%s\n"
        "report_profile=%s\n"
        "handoff_profile=%s\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "crypto_graduation_profile=%s\n"
        "assurance_baseline_profile=%s\n"
        "crypto_graduation_gate_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_handoff=%s\n"
        "requested_report=%s\n"
        "requested_envelope=%s\n"
        "requested_signature=%s\n"
        "requested_signing_authorization=%s\n"
        "requested_signer_handoff=%s\n"
        "requested_signer_invocation=%s\n"
        "requested_signing_operation=%s\n"
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signer_handoff_state=%s\n"
        "signer_handoff_ready=%u\n"
        "signer_invocation_state=%s\n"
        "signer_invocation_ready=%u\n"
        "signing_operation_state=%s\n"
        "signing_operation_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "trust_store_loaded=%u\n"
        "revocation_lookup_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        operation->signing_operation_profile,
        operation->signer_invocation_profile,
        operation->signer_handoff_profile,
        operation->signing_authorization_profile,
        operation->signature_request_profile,
        operation->envelope_profile,
        operation->report_profile,
        operation->handoff_profile,
        operation->decision_profile,
        operation->gate_profile,
        operation->receipt_profile,
        operation->verify_profile,
        operation->message_digest_algorithm,
        operation->message_digest_hex,
        operation->public_key_identity_label,
        operation->crypto_graduation_profile,
        operation->assurance_baseline_profile,
        operation->crypto_graduation_gate_state,
        operation->requested_capability,
        operation->requested_effect,
        operation->requested_handoff,
        operation->requested_report,
        operation->requested_envelope,
        operation->requested_signature,
        operation->requested_signing_authorization,
        operation->requested_signer_handoff,
        operation->requested_signer_invocation,
        operation->requested_signing_operation,
        operation->requested_scope,
        operation->crypto_graduation_gate_present,
        operation->crypto_graduation_gate_passed,
        operation->standard_expectations_met,
        operation->local_verify_graduated,
        operation->receipt_promotion_graduated,
        operation->authority_promotion_allowed,
        operation->signing_authorization_state,
        operation->signing_authorization_ready,
        operation->signer_handoff_state,
        operation->signer_handoff_ready,
        operation->signer_invocation_state,
        operation->signer_invocation_ready,
        operation->signing_operation_state,
        operation->signing_operation_ready,
        operation->signature_performed,
        operation->verification_performed,
        operation->signer_invoked,
        operation->private_key_handling,
        operation->key_generation_performed,
        operation->trust_store_loaded,
        operation->revocation_lookup_performed,
        operation->handoff_performed,
        operation->effect_performed,
        operation->runtime_authority_granted,
        operation->host_read_performed,
        operation->host_write_performed,
        operation->network_performed,
        operation->mode,
        latticra_seal_signing_operation_error_label(operation->error),
        operation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
