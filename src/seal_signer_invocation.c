#include "latticra/seal_signer_invocation.h"

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

static int bounded_string_empty(const char *value, size_t max_len) {
    return bounded_string_is(value, max_len, "");
}

static int is_allowed_signature(const char *signature) {
    return bounded_string_is(signature,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_signer_invocation(const char *invocation) {
    return bounded_string_is(invocation,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int handoff_error_valid(latticra_seal_signer_handoff_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNER_HANDOFF_OK:
    case LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int handoff_flags_valid(const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }

    return boolean_flag_valid(handoff->crypto_graduation_gate_present) &&
           boolean_flag_valid(handoff->crypto_graduation_gate_passed) &&
           boolean_flag_valid(handoff->standard_expectations_met) &&
           boolean_flag_valid(handoff->local_verify_graduated) &&
           boolean_flag_valid(handoff->receipt_promotion_graduated) &&
           boolean_flag_valid(handoff->authority_promotion_allowed) &&
           boolean_flag_valid(handoff->signature_request_ready) &&
           boolean_flag_valid(handoff->signing_authorization_ready) &&
           boolean_flag_valid(handoff->signer_handoff_ready) &&
           boolean_flag_valid(handoff->signature_performed) &&
           boolean_flag_valid(handoff->verification_performed) &&
           boolean_flag_valid(handoff->signer_invoked) &&
           boolean_flag_valid(handoff->private_key_handling) &&
           boolean_flag_valid(handoff->key_generation_performed) &&
           boolean_flag_valid(handoff->trust_store_loaded) &&
           boolean_flag_valid(handoff->revocation_lookup_performed) &&
           boolean_flag_valid(handoff->handoff_performed) &&
           boolean_flag_valid(handoff->effect_performed) &&
           boolean_flag_valid(handoff->runtime_authority_granted) &&
           boolean_flag_valid(handoff->host_read_performed) &&
           boolean_flag_valid(handoff->host_write_performed) &&
           boolean_flag_valid(handoff->network_performed);
}

static int handoff_crypto_graduation_gate_valid(
    const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }
    if (handoff->crypto_graduation_gate_present == 0u) {
        return handoff->crypto_graduation_gate_passed == 0u &&
               handoff->standard_expectations_met == 0u &&
               handoff->local_verify_graduated == 0u &&
               handoff->receipt_promotion_graduated == 0u &&
               handoff->authority_promotion_allowed == 0u &&
               bounded_string_empty(handoff->crypto_graduation_profile,
                                    LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
               bounded_string_empty(handoff->assurance_baseline_profile,
                                    LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
               bounded_string_is(handoff->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                                 "not-required");
    }

    return handoff->crypto_graduation_gate_passed == 1u &&
           handoff->standard_expectations_met == 1u &&
           handoff->local_verify_graduated == 1u &&
           handoff->receipt_promotion_graduated == 1u &&
           handoff->authority_promotion_allowed == 0u &&
           bounded_string_is(handoff->crypto_graduation_gate_state,
                             LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                             "graduated-authority-neutral");
}

static int handoff_ready_state_valid(
    const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }

    return text_field_valid(handoff->signer_handoff_state,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           text_field_valid(handoff->status,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX);
}

static int handoff_strings_valid(
    const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }

    return bounded_string_is(handoff->signer_handoff_profile,
                             LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX,
                             "latticra-seal-signer-handoff/0.1") &&
           text_field_terminated(handoff->signing_authorization_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->signature_request_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->envelope_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->report_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->handoff_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->decision_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->gate_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->receipt_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->verify_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_ALGORITHM_MAX) &&
           text_field_terminated(handoff->message_digest_hex,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_DIGEST_MAX) &&
           text_field_terminated(handoff->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->crypto_graduation_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_terminated(handoff->assurance_baseline_profile,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_PROFILE_MAX) &&
           text_field_valid(handoff->crypto_graduation_gate_state,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           text_field_terminated(handoff->requested_capability,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_effect,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_handoff,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_report,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_envelope,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_signature,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_signing_authorization,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_signer_handoff,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->requested_scope,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) &&
           text_field_terminated(handoff->signature_request_state,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           text_field_terminated(handoff->signing_authorization_state,
                                 LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           bounded_string_is(handoff->mode,
                             LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                             "metadata-only") &&
           handoff_error_valid(handoff->error) &&
           handoff_flags_valid(handoff) &&
           handoff_ready_state_valid(handoff);
}

static int requested_signer_invocation_present(
    const char *requested_signer_invocation) {
    return requested_signer_invocation != NULL &&
           requested_signer_invocation[0] != '\0';
}

static int invocation_crypto_graduation_gate_valid(
    const latticra_seal_signer_invocation_t *invocation);

static int invocation_ready_state_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL ||
        !boolean_flag_valid(invocation->signer_invocation_ready)) {
        return 0;
    }
    if (invocation->signer_invocation_ready == 0u) {
        return invocation->error != LATTICRA_SEAL_SIGNER_INVOCATION_OK &&
               text_field_valid(invocation->signer_invocation_state,
                                LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
               text_field_valid(invocation->status,
                                LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX);
    }

    return invocation->error == LATTICRA_SEAL_SIGNER_INVOCATION_OK &&
           invocation->signing_authorization_ready == 1u &&
           invocation->signer_handoff_ready == 1u &&
           invocation_crypto_graduation_gate_valid(invocation) &&
           bounded_string_is(invocation->requested_signature,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "Ed25519-development") &&
           bounded_string_is(invocation->requested_signing_authorization,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(invocation->requested_signer_handoff,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(invocation->requested_signer_invocation,
                             LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(invocation->signing_authorization_state,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "authorized-metadata-only") &&
           bounded_string_is(invocation->signer_handoff_state,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "handoff-metadata-only") &&
           bounded_string_is(invocation->signer_invocation_state,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "invocation-metadata-only") &&
           bounded_string_is(invocation->status,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "signer-invocation-metadata");
}

static int invocation_crypto_graduation_gate_valid(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }
    if (invocation->crypto_graduation_gate_present == 0u) {
        return invocation->crypto_graduation_gate_passed == 0u &&
               invocation->standard_expectations_met == 0u &&
               invocation->local_verify_graduated == 0u &&
               invocation->receipt_promotion_graduated == 0u &&
               invocation->authority_promotion_allowed == 0u &&
               bounded_string_empty(invocation->crypto_graduation_profile,
                                    LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
               bounded_string_empty(invocation->assurance_baseline_profile,
                                    LATTICRA_SEAL_SIGNER_INVOCATION_PROFILE_MAX) &&
               bounded_string_is(invocation->crypto_graduation_gate_state,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                                 "not-required");
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

static const char *safe_requested_signer_invocation_for_copy(
    const char *requested_signer_invocation) {
    if (!requested_signer_invocation_present(requested_signer_invocation)) {
        return NULL;
    }
    if (!text_field_valid(requested_signer_invocation,
                          LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX)) {
        return "invalid-signer-invocation";
    }
    return requested_signer_invocation;
}

const char *latticra_seal_signer_invocation_error_label(
    latticra_seal_signer_invocation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNER_INVOCATION_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF:
        return "invalid-signer-handoff";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void invocation_init(latticra_seal_signer_invocation_t *invocation) {
    memset(invocation, 0, sizeof(*invocation));
    copy_literal(
        invocation->signer_invocation_profile,
        sizeof(invocation->signer_invocation_profile),
        "latticra-seal-signer-invocation/0.1");
    copy_literal(
        invocation->signer_invocation_state,
        sizeof(invocation->signer_invocation_state),
        "denied-signer-handoff");
    copy_literal(invocation->crypto_graduation_gate_state, sizeof(invocation->crypto_graduation_gate_state), "not-required");
    invocation->crypto_graduation_gate_present = 0u;
    invocation->crypto_graduation_gate_passed = 0u;
    invocation->standard_expectations_met = 0u;
    invocation->local_verify_graduated = 0u;
    invocation->receipt_promotion_graduated = 0u;
    invocation->authority_promotion_allowed = 0u;
    copy_literal(invocation->mode, sizeof(invocation->mode), "metadata-only");
    invocation->signing_authorization_ready = 0u;
    invocation->signer_handoff_ready = 0u;
    invocation->signer_invocation_ready = 0u;
    invocation->signature_performed = 0u;
    invocation->verification_performed = 0u;
    invocation->signer_invoked = 0u;
    invocation->private_key_handling = 0u;
    invocation->key_generation_performed = 0u;
    invocation->trust_store_loaded = 0u;
    invocation->revocation_lookup_performed = 0u;
    invocation->handoff_performed = 0u;
    invocation->effect_performed = 0u;
    invocation->runtime_authority_granted = 0u;
    invocation->host_read_performed = 0u;
    invocation->host_write_performed = 0u;
    invocation->network_performed = 0u;
    invocation->error = LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT;
    copy_literal(invocation->status, sizeof(invocation->status), "invalid-input");
}

static void copy_handoff_metadata(
    const latticra_seal_signer_handoff_t *handoff,
    const char *requested_signer_invocation,
    latticra_seal_signer_invocation_t *out) {
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), handoff->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        handoff->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), handoff->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), handoff->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), handoff->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), handoff->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), handoff->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), handoff->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), handoff->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), handoff->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), handoff->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), handoff->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), handoff->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), handoff->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), handoff->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), handoff->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), handoff->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), handoff->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), handoff->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), handoff->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), handoff->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), handoff->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        handoff->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), handoff->requested_signer_handoff);
    copy_literal(
        out->requested_signer_invocation,
        sizeof(out->requested_signer_invocation),
        safe_requested_signer_invocation_for_copy(requested_signer_invocation));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), handoff->requested_scope);
    out->crypto_graduation_gate_present = handoff->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = handoff->crypto_graduation_gate_passed;
    out->standard_expectations_met = handoff->standard_expectations_met;
    out->local_verify_graduated = handoff->local_verify_graduated;
    out->receipt_promotion_graduated = handoff->receipt_promotion_graduated;
    out->authority_promotion_allowed = handoff->authority_promotion_allowed;
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        handoff->signing_authorization_state);
    out->signing_authorization_ready = handoff->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), handoff->signer_handoff_state);
    out->signer_handoff_ready = handoff->signer_handoff_ready;
    out->signature_performed = handoff->signature_performed;
    out->verification_performed = handoff->verification_performed;
    out->signer_invoked = handoff->signer_invoked;
    out->private_key_handling = handoff->private_key_handling;
    out->key_generation_performed = handoff->key_generation_performed;
    out->trust_store_loaded = handoff->trust_store_loaded;
    out->revocation_lookup_performed = handoff->revocation_lookup_performed;
    out->handoff_performed = handoff->handoff_performed;
    out->effect_performed = handoff->effect_performed;
    out->runtime_authority_granted = handoff->runtime_authority_granted;
    out->host_read_performed = handoff->host_read_performed;
    out->host_write_performed = handoff->host_write_performed;
    out->network_performed = handoff->network_performed;
}

latticra_status_t latticra_seal_signer_invocation_from_handoff(
    const latticra_seal_signer_handoff_t *handoff,
    const char *requested_signer_invocation,
    latticra_seal_signer_invocation_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    invocation_init(out);

    if (handoff == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!handoff_strings_valid(handoff)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF;
        copy_literal(out->signer_invocation_state,
                     sizeof(out->signer_invocation_state),
                     "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "invalid-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    copy_handoff_metadata(handoff, requested_signer_invocation, out);

    if (handoff->error != LATTICRA_SEAL_SIGNER_HANDOFF_OK) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "invalid-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (!handoff_crypto_graduation_gate_valid(handoff)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signer_handoff_ready != 1u ||
        !bounded_string_is(handoff->signer_handoff_state,
                           LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                           "handoff-metadata-only") ||
        !bounded_string_is(handoff->requested_signer_handoff,
                           LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signing_authorization_ready != 1u ||
        !bounded_string_is(handoff->signing_authorization_state,
                           LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                           "authorized-metadata-only") ||
        !bounded_string_is(handoff->requested_signing_authorization,
                           LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->requested_signature[0] == '\0' ||
        !text_field_valid(handoff->requested_signature,
                          LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) ||
        !is_allowed_signature(handoff->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_signer_invocation_present(requested_signer_invocation)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_signer_invocation,
                          LATTICRA_SEAL_SIGNER_INVOCATION_LABEL_MAX) ||
        !is_allowed_signer_invocation(requested_signer_invocation)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->private_key_handling != 0u ||
        handoff->key_generation_performed != 0u ||
        handoff->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->revocation_lookup_performed != 0u ||
        handoff->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signature_performed != 0u ||
        handoff->verification_performed != 0u ||
        handoff->signer_invoked != 0u ||
        handoff->handoff_performed != 0u ||
        handoff->effect_performed != 0u ||
        handoff->host_read_performed != 0u ||
        handoff->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->signer_invocation_ready = 1u;
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
    out->error = LATTICRA_SEAL_SIGNER_INVOCATION_OK;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "invocation-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signer-invocation-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signer_invocation_is_metadata_only(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }

    return invocation->signature_performed == 0u &&
           invocation->verification_performed == 0u &&
           invocation->signer_invoked == 0u &&
           invocation->private_key_handling == 0u &&
           invocation->key_generation_performed == 0u &&
           invocation->trust_store_loaded == 0u &&
           invocation->revocation_lookup_performed == 0u &&
           invocation->handoff_performed == 0u &&
           invocation->effect_performed == 0u &&
           invocation->runtime_authority_granted == 0u &&
           invocation->host_read_performed == 0u &&
           invocation->host_write_performed == 0u &&
           invocation->network_performed == 0u &&
           invocation_error_valid(invocation->error) &&
           boolean_flag_valid(invocation->crypto_graduation_gate_present) &&
           boolean_flag_valid(invocation->crypto_graduation_gate_passed) &&
           boolean_flag_valid(invocation->standard_expectations_met) &&
           boolean_flag_valid(invocation->local_verify_graduated) &&
           boolean_flag_valid(invocation->receipt_promotion_graduated) &&
           boolean_flag_valid(invocation->authority_promotion_allowed) &&
           boolean_flag_valid(invocation->signing_authorization_ready) &&
           boolean_flag_valid(invocation->signer_handoff_ready) &&
           invocation_crypto_graduation_gate_valid(invocation) &&
           invocation_ready_state_valid(invocation) &&
           bounded_string_is(invocation->signer_invocation_profile,
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
           text_field_valid(invocation->crypto_graduation_gate_state,
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
           text_field_terminated(invocation->signing_authorization_state,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_terminated(invocation->signer_handoff_state,
                                 LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           text_field_valid(invocation->signer_invocation_state,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX) &&
           bounded_string_is(invocation->mode,
                             LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(invocation->status,
                            LATTICRA_SEAL_SIGNER_INVOCATION_STATE_MAX);
}

latticra_status_t latticra_seal_signer_invocation_render(
    const latticra_seal_signer_invocation_t *invocation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (invocation == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signer_invocation_is_metadata_only(invocation)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNER INVOCATION\n"
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
        invocation->signer_invocation_profile,
        invocation->signer_handoff_profile,
        invocation->signing_authorization_profile,
        invocation->signature_request_profile,
        invocation->envelope_profile,
        invocation->report_profile,
        invocation->handoff_profile,
        invocation->decision_profile,
        invocation->gate_profile,
        invocation->receipt_profile,
        invocation->verify_profile,
        invocation->message_digest_algorithm,
        invocation->message_digest_hex,
        invocation->public_key_identity_label,
        invocation->crypto_graduation_profile,
        invocation->assurance_baseline_profile,
        invocation->crypto_graduation_gate_state,
        invocation->requested_capability,
        invocation->requested_effect,
        invocation->requested_handoff,
        invocation->requested_report,
        invocation->requested_envelope,
        invocation->requested_signature,
        invocation->requested_signing_authorization,
        invocation->requested_signer_handoff,
        invocation->requested_signer_invocation,
        invocation->requested_scope,
        invocation->crypto_graduation_gate_present,
        invocation->crypto_graduation_gate_passed,
        invocation->standard_expectations_met,
        invocation->local_verify_graduated,
        invocation->receipt_promotion_graduated,
        invocation->authority_promotion_allowed,
        invocation->signing_authorization_state,
        invocation->signing_authorization_ready,
        invocation->signer_handoff_state,
        invocation->signer_handoff_ready,
        invocation->signer_invocation_state,
        invocation->signer_invocation_ready,
        invocation->signature_performed,
        invocation->verification_performed,
        invocation->signer_invoked,
        invocation->private_key_handling,
        invocation->key_generation_performed,
        invocation->trust_store_loaded,
        invocation->revocation_lookup_performed,
        invocation->handoff_performed,
        invocation->effect_performed,
        invocation->runtime_authority_granted,
        invocation->host_read_performed,
        invocation->host_write_performed,
        invocation->network_performed,
        invocation->mode,
        latticra_seal_signer_invocation_error_label(invocation->error),
        invocation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
