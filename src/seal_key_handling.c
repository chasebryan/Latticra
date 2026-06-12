#include "latticra/seal_key_handling.h"

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
    size_t i;

    if (terminated != 1 || len == 0u) {
        return 0;
    }
    for (i = 0u; i < len; ++i) {
        if (value[i] == '\n' || value[i] == '\r') {
            return 0;
        }
    }
    return 1;
}

static int text_field_terminated(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);
    size_t i;

    if (terminated != 1) {
        return 0;
    }
    for (i = 0u; i < len; ++i) {
        if (value[i] == '\n' || value[i] == '\r') {
            return 0;
        }
    }
    return 1;
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

static int bounded_string_empty(const char *value, size_t max_len) {
    return bounded_string_is(value, max_len, "");
}

static int is_allowed_signature(const char *signature) {
    return bounded_string_is(signature,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_metadata_label(const char *label) {
    return bounded_string_is(label,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int key_handling_error_valid(latticra_seal_key_handling_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_HANDLING_OK:
    case LATTICRA_SEAL_KEY_HANDLING_INVALID_INPUT:
    case LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_MATERIAL:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
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

static int operation_crypto_graduation_gate_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }
    if (operation->crypto_graduation_gate_present == 0u) {
        return operation->crypto_graduation_gate_passed == 0u &&
               operation->standard_expectations_met == 0u &&
               operation->local_verify_graduated == 0u &&
               operation->receipt_promotion_graduated == 0u &&
               operation->authority_promotion_allowed == 0u &&
               bounded_string_empty(operation->crypto_graduation_profile,
                                    LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
               bounded_string_empty(operation->assurance_baseline_profile,
                                    LATTICRA_SEAL_SIGNING_OPERATION_PROFILE_MAX) &&
               bounded_string_is(operation->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                                 "not-required");
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

static int key_handling_crypto_graduation_gate_valid(
    const latticra_seal_key_handling_t *key_handling) {
    if (key_handling == NULL) {
        return 0;
    }
    if (key_handling->crypto_graduation_gate_present == 0u) {
        return key_handling->crypto_graduation_gate_passed == 0u &&
               key_handling->standard_expectations_met == 0u &&
               key_handling->local_verify_graduated == 0u &&
               key_handling->receipt_promotion_graduated == 0u &&
               key_handling->authority_promotion_allowed == 0u &&
               bounded_string_empty(key_handling->crypto_graduation_profile,
                                    LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
               bounded_string_empty(key_handling->assurance_baseline_profile,
                                    LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
               bounded_string_is(key_handling->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                                 "not-required");
    }

    return key_handling->crypto_graduation_gate_passed == 1u &&
           key_handling->standard_expectations_met == 1u &&
           key_handling->local_verify_graduated == 1u &&
           key_handling->receipt_promotion_graduated == 1u &&
           key_handling->authority_promotion_allowed == 0u &&
           bounded_string_is(key_handling->crypto_graduation_gate_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "graduated-authority-neutral");
}

static int operation_flags_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }

    return boolean_flag_valid(operation->signing_authorization_ready) &&
           boolean_flag_valid(operation->signer_handoff_ready) &&
           boolean_flag_valid(operation->signer_invocation_ready) &&
           boolean_flag_valid(operation->signing_operation_ready) &&
           boolean_flag_valid(operation->crypto_graduation_gate_present) &&
           boolean_flag_valid(operation->crypto_graduation_gate_passed) &&
           boolean_flag_valid(operation->standard_expectations_met) &&
           boolean_flag_valid(operation->local_verify_graduated) &&
           boolean_flag_valid(operation->receipt_promotion_graduated) &&
           boolean_flag_valid(operation->authority_promotion_allowed) &&
           boolean_flag_valid(operation->signature_performed) &&
           boolean_flag_valid(operation->verification_performed) &&
           boolean_flag_valid(operation->signer_invoked) &&
           boolean_flag_valid(operation->private_key_handling) &&
           boolean_flag_valid(operation->key_generation_performed) &&
           boolean_flag_valid(operation->trust_store_loaded) &&
           boolean_flag_valid(operation->revocation_lookup_performed) &&
           boolean_flag_valid(operation->handoff_performed) &&
           boolean_flag_valid(operation->effect_performed) &&
           boolean_flag_valid(operation->runtime_authority_granted) &&
           boolean_flag_valid(operation->host_read_performed) &&
           boolean_flag_valid(operation->host_write_performed) &&
           boolean_flag_valid(operation->network_performed);
}

static int operation_state_fields_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }

    return text_field_valid(operation->signing_authorization_state,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_valid(operation->signer_handoff_state,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_valid(operation->signer_invocation_state,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_valid(operation->signing_operation_state,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX) &&
           text_field_valid(operation->status,
                            LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX);
}

static int operation_strings_valid(
    const latticra_seal_signing_operation_t *operation) {
    if (operation == NULL) {
        return 0;
    }

    return bounded_string_is(operation->signing_operation_profile,
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
           bounded_string_is(operation->mode,
                             LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                             "metadata-only") &&
           operation_error_valid(operation->error) &&
           operation_flags_valid(operation) &&
           operation_state_fields_valid(operation);
}

static int requested_key_handling_present(const char *requested_key_handling) {
    return requested_key_handling != NULL && requested_key_handling[0] != '\0';
}

static int key_handling_ready_state_valid(
    const latticra_seal_key_handling_t *key_handling) {
    if (key_handling == NULL ||
        !boolean_flag_valid(key_handling->key_handling_ready)) {
        return 0;
    }
    if (key_handling->key_handling_ready == 0u) {
        return key_handling->error != LATTICRA_SEAL_KEY_HANDLING_OK &&
               text_field_valid(key_handling->key_handling_state,
                                LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
               text_field_valid(key_handling->status,
                                LATTICRA_SEAL_KEY_HANDLING_STATE_MAX);
    }

    return key_handling->error == LATTICRA_SEAL_KEY_HANDLING_OK &&
           key_handling->signing_authorization_ready == 1u &&
           key_handling->signer_handoff_ready == 1u &&
           key_handling->signer_invocation_ready == 1u &&
           key_handling->signing_operation_ready == 1u &&
           key_handling_crypto_graduation_gate_valid(key_handling) &&
           bounded_string_is(key_handling->requested_signature,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "Ed25519-development") &&
           bounded_string_is(key_handling->requested_signing_authorization,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(key_handling->requested_signer_handoff,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(key_handling->requested_signer_invocation,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(key_handling->requested_signing_operation,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(key_handling->requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(key_handling->signing_authorization_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "authorized-metadata-only") &&
           bounded_string_is(key_handling->signer_handoff_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "handoff-metadata-only") &&
           bounded_string_is(key_handling->signer_invocation_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "invocation-metadata-only") &&
           bounded_string_is(key_handling->signing_operation_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "operation-metadata-only") &&
           bounded_string_is(key_handling->key_handling_state,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "key-handling-metadata-only") &&
           bounded_string_is(key_handling->status,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "key-handling-metadata");
}

static const char *safe_requested_key_handling_for_copy(
    const char *requested_key_handling) {
    if (!requested_key_handling_present(requested_key_handling)) {
        return NULL;
    }
    if (!text_field_valid(requested_key_handling,
                          LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX)) {
        return "invalid-key-handling";
    }
    return requested_key_handling;
}

const char *latticra_seal_key_handling_error_label(
    latticra_seal_key_handling_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_HANDLING_OK:
        return "ok";
    case LATTICRA_SEAL_KEY_HANDLING_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION:
        return "invalid-signing-operation";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION:
        return "denied-signing-operation";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING:
        return "denied-key-handling";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_MATERIAL:
        return "denied-key-material";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE:
        return "denied-trust-store";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void key_handling_init(latticra_seal_key_handling_t *key_handling) {
    memset(key_handling, 0, sizeof(*key_handling));
    copy_literal(
        key_handling->key_handling_profile,
        sizeof(key_handling->key_handling_profile),
        "latticra-seal-key-handling/0.1");
    copy_literal(
        key_handling->key_handling_state,
        sizeof(key_handling->key_handling_state),
        "denied-signing-operation");
    copy_literal(key_handling->crypto_graduation_gate_state, sizeof(key_handling->crypto_graduation_gate_state), "not-required");
    key_handling->crypto_graduation_gate_present = 0u;
    key_handling->crypto_graduation_gate_passed = 0u;
    key_handling->standard_expectations_met = 0u;
    key_handling->local_verify_graduated = 0u;
    key_handling->receipt_promotion_graduated = 0u;
    key_handling->authority_promotion_allowed = 0u;
    copy_literal(key_handling->mode, sizeof(key_handling->mode), "metadata-only");
    key_handling->signing_authorization_ready = 0u;
    key_handling->signer_handoff_ready = 0u;
    key_handling->signer_invocation_ready = 0u;
    key_handling->signing_operation_ready = 0u;
    key_handling->key_handling_ready = 0u;
    key_handling->signature_performed = 0u;
    key_handling->verification_performed = 0u;
    key_handling->signer_invoked = 0u;
    key_handling->public_key_parsed = 0u;
    key_handling->key_material_loaded = 0u;
    key_handling->private_key_handling = 0u;
    key_handling->key_generation_performed = 0u;
    key_handling->hardware_key_used = 0u;
    key_handling->trust_store_loaded = 0u;
    key_handling->revocation_lookup_performed = 0u;
    key_handling->handoff_performed = 0u;
    key_handling->effect_performed = 0u;
    key_handling->runtime_authority_granted = 0u;
    key_handling->host_read_performed = 0u;
    key_handling->host_write_performed = 0u;
    key_handling->network_performed = 0u;
    key_handling->error = LATTICRA_SEAL_KEY_HANDLING_INVALID_INPUT;
    copy_literal(key_handling->status, sizeof(key_handling->status), "invalid-input");
}

static void copy_operation_metadata(
    const latticra_seal_signing_operation_t *operation,
    const char *requested_key_handling,
    latticra_seal_key_handling_t *out) {
    copy_literal(out->signing_operation_profile, sizeof(out->signing_operation_profile), operation->signing_operation_profile);
    copy_literal(out->signer_invocation_profile, sizeof(out->signer_invocation_profile), operation->signer_invocation_profile);
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), operation->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        operation->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), operation->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), operation->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), operation->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), operation->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), operation->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), operation->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), operation->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), operation->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), operation->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), operation->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), operation->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), operation->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), operation->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), operation->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), operation->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), operation->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), operation->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), operation->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), operation->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), operation->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        operation->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), operation->requested_signer_handoff);
    copy_literal(out->requested_signer_invocation, sizeof(out->requested_signer_invocation), operation->requested_signer_invocation);
    copy_literal(
        out->requested_signing_operation,
        sizeof(out->requested_signing_operation),
        operation->requested_signing_operation);
    copy_literal(out->requested_key_handling,
                 sizeof(out->requested_key_handling),
                 safe_requested_key_handling_for_copy(requested_key_handling));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), operation->requested_scope);
    out->crypto_graduation_gate_present = operation->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = operation->crypto_graduation_gate_passed;
    out->standard_expectations_met = operation->standard_expectations_met;
    out->local_verify_graduated = operation->local_verify_graduated;
    out->receipt_promotion_graduated = operation->receipt_promotion_graduated;
    out->authority_promotion_allowed = operation->authority_promotion_allowed;
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        operation->signing_authorization_state);
    out->signing_authorization_ready = operation->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), operation->signer_handoff_state);
    out->signer_handoff_ready = operation->signer_handoff_ready;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), operation->signer_invocation_state);
    out->signer_invocation_ready = operation->signer_invocation_ready;
    copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), operation->signing_operation_state);
    out->signing_operation_ready = operation->signing_operation_ready;
    out->signature_performed = operation->signature_performed;
    out->verification_performed = operation->verification_performed;
    out->signer_invoked = operation->signer_invoked;
    out->private_key_handling = operation->private_key_handling;
    out->key_generation_performed = operation->key_generation_performed;
    out->trust_store_loaded = operation->trust_store_loaded;
    out->revocation_lookup_performed = operation->revocation_lookup_performed;
    out->handoff_performed = operation->handoff_performed;
    out->effect_performed = operation->effect_performed;
    out->runtime_authority_granted = operation->runtime_authority_granted;
    out->host_read_performed = operation->host_read_performed;
    out->host_write_performed = operation->host_write_performed;
    out->network_performed = operation->network_performed;
}

static int request_is_key_material(const char *requested_key_handling) {
    return bounded_string_is(requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "parse-public-key") ||
           bounded_string_is(requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "load-key-material");
}

static int request_is_private_key(const char *requested_key_handling) {
    return bounded_string_is(requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "handle-private-key") ||
           bounded_string_is(requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "generate-key") ||
           bounded_string_is(requested_key_handling,
                             LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                             "use-hardware-key");
}

latticra_status_t latticra_seal_key_handling_from_operation(
    const latticra_seal_signing_operation_t *operation,
    const char *requested_key_handling,
    latticra_seal_key_handling_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    key_handling_init(out);

    if (operation == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!operation_strings_valid(operation)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION;
        copy_literal(out->key_handling_state,
                     sizeof(out->key_handling_state),
                     "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "invalid-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    copy_operation_metadata(operation, requested_key_handling, out);

    if (operation->error != LATTICRA_SEAL_SIGNING_OPERATION_OK) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "invalid-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (!operation_crypto_graduation_gate_valid(operation)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (operation->signing_operation_ready != 1u ||
        !bounded_string_is(operation->signing_operation_state,
                           LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                           "operation-metadata-only") ||
        !bounded_string_is(operation->requested_signing_operation,
                           LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "denied-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (operation->signer_invocation_ready != 1u ||
        !bounded_string_is(operation->signer_invocation_state,
                           LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                           "invocation-metadata-only") ||
        !bounded_string_is(operation->requested_signer_invocation,
                           LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (operation->signer_handoff_ready != 1u ||
        !bounded_string_is(operation->signer_handoff_state,
                           LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                           "handoff-metadata-only") ||
        !bounded_string_is(operation->requested_signer_handoff,
                           LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (operation->signing_authorization_ready != 1u ||
        !bounded_string_is(operation->signing_authorization_state,
                           LATTICRA_SEAL_SIGNING_OPERATION_STATE_MAX,
                           "authorized-metadata-only") ||
        !bounded_string_is(operation->requested_signing_authorization,
                           LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (operation->requested_signature[0] == '\0' ||
        !text_field_valid(operation->requested_signature,
                          LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX) ||
        !is_allowed_signature(operation->requested_signature)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_key_handling_present(requested_key_handling)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-key-handling");
        copy_literal(out->status, sizeof(out->status), "missing-requested-key-handling");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_key_material(requested_key_handling)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_MATERIAL;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_private_key(requested_key_handling)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (bounded_string_is(requested_key_handling,
                          LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                          "load-trust-store")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (bounded_string_is(requested_key_handling,
                          LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX,
                          "revocation-lookup")) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_metadata_label(requested_key_handling)) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-key-handling");
        copy_literal(out->status, sizeof(out->status), "denied-key-handling");
        return LATTICRA_STATUS_OK;
    }

    if (operation->private_key_handling != 0u ||
        operation->key_generation_performed != 0u) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (operation->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (operation->revocation_lookup_performed != 0u ||
        operation->network_performed != 0u) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (operation->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (operation->signature_performed != 0u ||
        operation->verification_performed != 0u ||
        operation->signer_invoked != 0u ||
        operation->handoff_performed != 0u ||
        operation->effect_performed != 0u ||
        operation->host_read_performed != 0u ||
        operation->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT;
        copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->key_handling_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->signer_invoked = 0u;
    out->public_key_parsed = 0u;
    out->key_material_loaded = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->hardware_key_used = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_KEY_HANDLING_OK;
    copy_literal(out->key_handling_state, sizeof(out->key_handling_state), "key-handling-metadata-only");
    copy_literal(out->status, sizeof(out->status), "key-handling-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_key_handling_is_metadata_only(
    const latticra_seal_key_handling_t *key_handling) {
    if (key_handling == NULL) {
        return 0;
    }

    return key_handling->signature_performed == 0u &&
           key_handling->verification_performed == 0u &&
           key_handling->signer_invoked == 0u &&
           key_handling->public_key_parsed == 0u &&
           key_handling->key_material_loaded == 0u &&
           key_handling->private_key_handling == 0u &&
           key_handling->key_generation_performed == 0u &&
           key_handling->hardware_key_used == 0u &&
           key_handling->trust_store_loaded == 0u &&
           key_handling->revocation_lookup_performed == 0u &&
           key_handling->handoff_performed == 0u &&
           key_handling->effect_performed == 0u &&
           key_handling->runtime_authority_granted == 0u &&
           key_handling->host_read_performed == 0u &&
           key_handling->host_write_performed == 0u &&
           key_handling->network_performed == 0u &&
           key_handling_error_valid(key_handling->error) &&
           boolean_flag_valid(key_handling->crypto_graduation_gate_present) &&
           boolean_flag_valid(key_handling->crypto_graduation_gate_passed) &&
           boolean_flag_valid(key_handling->standard_expectations_met) &&
           boolean_flag_valid(key_handling->local_verify_graduated) &&
           boolean_flag_valid(key_handling->receipt_promotion_graduated) &&
           boolean_flag_valid(key_handling->authority_promotion_allowed) &&
           boolean_flag_valid(key_handling->signing_authorization_ready) &&
           boolean_flag_valid(key_handling->signer_handoff_ready) &&
           boolean_flag_valid(key_handling->signer_invocation_ready) &&
           boolean_flag_valid(key_handling->signing_operation_ready) &&
           key_handling_ready_state_valid(key_handling) &&
           bounded_string_is(key_handling->key_handling_profile,
                             LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX,
                             "latticra-seal-key-handling/0.1") &&
           text_field_terminated(key_handling->signing_operation_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->signer_invocation_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->signer_handoff_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->signing_authorization_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->signature_request_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->envelope_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->report_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->handoff_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->decision_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->gate_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->receipt_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->verify_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->message_digest_algorithm,
                                 LATTICRA_SEAL_KEY_HANDLING_ALGORITHM_MAX) &&
           text_field_terminated(key_handling->message_digest_hex,
                                 LATTICRA_SEAL_KEY_HANDLING_DIGEST_MAX) &&
           text_field_terminated(key_handling->public_key_identity_label,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->crypto_graduation_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->assurance_baseline_profile,
                                 LATTICRA_SEAL_KEY_HANDLING_PROFILE_MAX) &&
           text_field_terminated(key_handling->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           key_handling_crypto_graduation_gate_valid(key_handling) &&
           text_field_terminated(key_handling->requested_capability,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_effect,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_handoff,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_report,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_envelope,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_signature,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_signing_authorization,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_signer_handoff,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_signer_invocation,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_signing_operation,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_key_handling,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->requested_scope,
                                 LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX) &&
           text_field_terminated(key_handling->signing_authorization_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           text_field_terminated(key_handling->signer_handoff_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           text_field_terminated(key_handling->signer_invocation_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           text_field_terminated(key_handling->signing_operation_state,
                                 LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           text_field_valid(key_handling->key_handling_state,
                            LATTICRA_SEAL_KEY_HANDLING_STATE_MAX) &&
           bounded_string_is(key_handling->mode,
                             LATTICRA_SEAL_KEY_HANDLING_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(key_handling->status,
                            LATTICRA_SEAL_KEY_HANDLING_STATE_MAX);
}

latticra_status_t latticra_seal_key_handling_render(
    const latticra_seal_key_handling_t *key_handling,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (key_handling == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_key_handling_is_metadata_only(key_handling)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL KEY HANDLING\n"
        "key_handling_profile=%s\n"
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
        "requested_key_handling=%s\n"
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
        "key_handling_state=%s\n"
        "key_handling_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "public_key_parsed=%u\n"
        "key_material_loaded=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "hardware_key_used=%u\n"
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
        key_handling->key_handling_profile,
        key_handling->signing_operation_profile,
        key_handling->signer_invocation_profile,
        key_handling->signer_handoff_profile,
        key_handling->signing_authorization_profile,
        key_handling->signature_request_profile,
        key_handling->envelope_profile,
        key_handling->report_profile,
        key_handling->handoff_profile,
        key_handling->decision_profile,
        key_handling->gate_profile,
        key_handling->receipt_profile,
        key_handling->verify_profile,
        key_handling->message_digest_algorithm,
        key_handling->message_digest_hex,
        key_handling->public_key_identity_label,
        key_handling->crypto_graduation_profile,
        key_handling->assurance_baseline_profile,
        key_handling->crypto_graduation_gate_state,
        key_handling->requested_capability,
        key_handling->requested_effect,
        key_handling->requested_handoff,
        key_handling->requested_report,
        key_handling->requested_envelope,
        key_handling->requested_signature,
        key_handling->requested_signing_authorization,
        key_handling->requested_signer_handoff,
        key_handling->requested_signer_invocation,
        key_handling->requested_signing_operation,
        key_handling->requested_key_handling,
        key_handling->requested_scope,
        key_handling->crypto_graduation_gate_present,
        key_handling->crypto_graduation_gate_passed,
        key_handling->standard_expectations_met,
        key_handling->local_verify_graduated,
        key_handling->receipt_promotion_graduated,
        key_handling->authority_promotion_allowed,
        key_handling->signing_authorization_state,
        key_handling->signing_authorization_ready,
        key_handling->signer_handoff_state,
        key_handling->signer_handoff_ready,
        key_handling->signer_invocation_state,
        key_handling->signer_invocation_ready,
        key_handling->signing_operation_state,
        key_handling->signing_operation_ready,
        key_handling->key_handling_state,
        key_handling->key_handling_ready,
        key_handling->signature_performed,
        key_handling->verification_performed,
        key_handling->signer_invoked,
        key_handling->public_key_parsed,
        key_handling->key_material_loaded,
        key_handling->private_key_handling,
        key_handling->key_generation_performed,
        key_handling->hardware_key_used,
        key_handling->trust_store_loaded,
        key_handling->revocation_lookup_performed,
        key_handling->handoff_performed,
        key_handling->effect_performed,
        key_handling->runtime_authority_granted,
        key_handling->host_read_performed,
        key_handling->host_write_performed,
        key_handling->network_performed,
        key_handling->mode,
        latticra_seal_key_handling_error_label(key_handling->error),
        key_handling->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
