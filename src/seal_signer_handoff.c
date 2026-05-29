#include "latticra/seal_signer_handoff.h"

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
                             LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_signer_handoff(const char *handoff) {
    return bounded_string_is(handoff,
                             LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int authorization_error_valid(latticra_seal_signing_authorization_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int authorization_flags_valid(
    const latticra_seal_signing_authorization_t *authorization) {
    if (authorization == NULL) {
        return 0;
    }

    return boolean_flag_valid(authorization->crypto_graduation_gate_present) &&
           boolean_flag_valid(authorization->crypto_graduation_gate_passed) &&
           boolean_flag_valid(authorization->standard_expectations_met) &&
           boolean_flag_valid(authorization->local_verify_graduated) &&
           boolean_flag_valid(authorization->receipt_promotion_graduated) &&
           boolean_flag_valid(authorization->authority_promotion_allowed) &&
           boolean_flag_valid(authorization->signature_request_ready) &&
           boolean_flag_valid(authorization->signing_authorization_ready) &&
           boolean_flag_valid(authorization->signature_performed) &&
           boolean_flag_valid(authorization->verification_performed) &&
           boolean_flag_valid(authorization->private_key_handling) &&
           boolean_flag_valid(authorization->key_generation_performed) &&
           boolean_flag_valid(authorization->trust_store_loaded) &&
           boolean_flag_valid(authorization->revocation_lookup_performed) &&
           boolean_flag_valid(authorization->handoff_performed) &&
           boolean_flag_valid(authorization->effect_performed) &&
           boolean_flag_valid(authorization->runtime_authority_granted) &&
           boolean_flag_valid(authorization->host_read_performed) &&
           boolean_flag_valid(authorization->host_write_performed) &&
           boolean_flag_valid(authorization->network_performed);
}

static int authorization_strings_valid(
    const latticra_seal_signing_authorization_t *authorization) {
    if (authorization == NULL) {
        return 0;
    }

    return bounded_string_is(authorization->signing_authorization_profile,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX,
                             "latticra-seal-signing-authorization/0.1") &&
           text_field_terminated(authorization->signature_request_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->envelope_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->report_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->handoff_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->decision_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->gate_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->receipt_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->verify_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_ALGORITHM_MAX) &&
           text_field_terminated(authorization->message_digest_hex,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_DIGEST_MAX) &&
           text_field_terminated(authorization->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->crypto_graduation_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_terminated(authorization->assurance_baseline_profile,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_PROFILE_MAX) &&
           text_field_valid(authorization->crypto_graduation_gate_state,
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX) &&
           text_field_terminated(authorization->requested_capability,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_effect,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_handoff,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_report,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_envelope,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_signature,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_signing_authorization,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_terminated(authorization->requested_scope,
                                 LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) &&
           text_field_valid(authorization->signature_request_state,
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX) &&
           text_field_valid(authorization->signing_authorization_state,
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX) &&
           bounded_string_is(authorization->mode,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(authorization->status,
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX) &&
           authorization_error_valid(authorization->error) &&
           authorization_flags_valid(authorization);
}

static int requested_signer_handoff_present(
    const char *requested_signer_handoff) {
    return requested_signer_handoff != NULL &&
           requested_signer_handoff[0] != '\0';
}

static int handoff_ready_state_valid(
    const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL || !boolean_flag_valid(handoff->signer_handoff_ready)) {
        return 0;
    }
    if (handoff->signer_handoff_ready == 0u) {
        return handoff->error != LATTICRA_SEAL_SIGNER_HANDOFF_OK &&
               text_field_valid(handoff->signer_handoff_state,
                                LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
               text_field_valid(handoff->status,
                                LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX);
    }

    return handoff->error == LATTICRA_SEAL_SIGNER_HANDOFF_OK &&
           bounded_string_is(handoff->requested_signer_handoff,
                             LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(handoff->signer_handoff_state,
                             LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                             "handoff-metadata-only") &&
           bounded_string_is(handoff->status,
                             LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                             "signer-handoff-metadata");
}

static const char *safe_requested_signer_handoff_for_copy(
    const char *requested_signer_handoff) {
    if (!requested_signer_handoff_present(requested_signer_handoff)) {
        return NULL;
    }
    if (!text_field_valid(requested_signer_handoff,
                          LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX)) {
        return "invalid-signer-handoff";
    }
    return requested_signer_handoff;
}

const char *latticra_seal_signer_handoff_error_label(
    latticra_seal_signer_handoff_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNER_HANDOFF_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION:
        return "invalid-signing-authorization";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void handoff_init(latticra_seal_signer_handoff_t *handoff) {
    memset(handoff, 0, sizeof(*handoff));
    copy_literal(
        handoff->signer_handoff_profile,
        sizeof(handoff->signer_handoff_profile),
        "latticra-seal-signer-handoff/0.1");
    copy_literal(
        handoff->signer_handoff_state,
        sizeof(handoff->signer_handoff_state),
        "denied-signing-authorization");
    copy_literal(handoff->crypto_graduation_gate_state, sizeof(handoff->crypto_graduation_gate_state), "not-required");
    handoff->crypto_graduation_gate_present = 0u;
    handoff->crypto_graduation_gate_passed = 0u;
    handoff->standard_expectations_met = 0u;
    handoff->local_verify_graduated = 0u;
    handoff->receipt_promotion_graduated = 0u;
    handoff->authority_promotion_allowed = 0u;
    copy_literal(handoff->mode, sizeof(handoff->mode), "metadata-only");
    handoff->signature_request_ready = 0u;
    handoff->signing_authorization_ready = 0u;
    handoff->signer_handoff_ready = 0u;
    handoff->signature_performed = 0u;
    handoff->verification_performed = 0u;
    handoff->signer_invoked = 0u;
    handoff->private_key_handling = 0u;
    handoff->key_generation_performed = 0u;
    handoff->trust_store_loaded = 0u;
    handoff->revocation_lookup_performed = 0u;
    handoff->handoff_performed = 0u;
    handoff->effect_performed = 0u;
    handoff->runtime_authority_granted = 0u;
    handoff->host_read_performed = 0u;
    handoff->host_write_performed = 0u;
    handoff->network_performed = 0u;
    handoff->error = LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_INPUT;
    copy_literal(handoff->status, sizeof(handoff->status), "invalid-input");
}

static void copy_authorization_metadata(
    const latticra_seal_signing_authorization_t *authorization,
    const char *requested_signer_handoff,
    latticra_seal_signer_handoff_t *out) {
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        authorization->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), authorization->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), authorization->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), authorization->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), authorization->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), authorization->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), authorization->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), authorization->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), authorization->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), authorization->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), authorization->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), authorization->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), authorization->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), authorization->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), authorization->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), authorization->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), authorization->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), authorization->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), authorization->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), authorization->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), authorization->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        authorization->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff,
                 sizeof(out->requested_signer_handoff),
                 safe_requested_signer_handoff_for_copy(requested_signer_handoff));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), authorization->requested_scope);
    out->crypto_graduation_gate_present = authorization->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = authorization->crypto_graduation_gate_passed;
    out->standard_expectations_met = authorization->standard_expectations_met;
    out->local_verify_graduated = authorization->local_verify_graduated;
    out->receipt_promotion_graduated = authorization->receipt_promotion_graduated;
    out->authority_promotion_allowed = authorization->authority_promotion_allowed;
    copy_literal(out->signature_request_state, sizeof(out->signature_request_state), authorization->signature_request_state);
    out->signature_request_ready = authorization->signature_request_ready;
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        authorization->signing_authorization_state);
    out->signing_authorization_ready = authorization->signing_authorization_ready;
    out->signature_performed = authorization->signature_performed;
    out->verification_performed = authorization->verification_performed;
    out->private_key_handling = authorization->private_key_handling;
    out->key_generation_performed = authorization->key_generation_performed;
    out->trust_store_loaded = authorization->trust_store_loaded;
    out->revocation_lookup_performed = authorization->revocation_lookup_performed;
    out->handoff_performed = authorization->handoff_performed;
    out->effect_performed = authorization->effect_performed;
    out->runtime_authority_granted = authorization->runtime_authority_granted;
    out->host_read_performed = authorization->host_read_performed;
    out->host_write_performed = authorization->host_write_performed;
    out->network_performed = authorization->network_performed;
}

latticra_status_t latticra_seal_signer_handoff_from_authorization(
    const latticra_seal_signing_authorization_t *authorization,
    const char *requested_signer_handoff,
    latticra_seal_signer_handoff_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    handoff_init(out);

    if (authorization == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!authorization_strings_valid(authorization)) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION;
        copy_literal(out->signer_handoff_state,
                     sizeof(out->signer_handoff_state),
                     "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "invalid-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    copy_authorization_metadata(authorization, requested_signer_handoff, out);

    if (authorization->error != LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "invalid-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->crypto_graduation_gate_present != 0u &&
        (authorization->crypto_graduation_gate_passed != 1u ||
         authorization->standard_expectations_met != 1u ||
         authorization->local_verify_graduated != 1u ||
         authorization->receipt_promotion_graduated != 1u ||
         authorization->authority_promotion_allowed != 0u ||
         !bounded_string_is(authorization->crypto_graduation_gate_state,
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX,
                            "graduated-authority-neutral"))) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->signing_authorization_ready != 1u ||
        !bounded_string_is(authorization->signing_authorization_state,
                           LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX,
                           "authorized-metadata-only") ||
        !bounded_string_is(authorization->requested_signing_authorization,
                           LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX,
                           "metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->requested_signature[0] == '\0' ||
        !text_field_valid(authorization->requested_signature,
                          LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) ||
        !is_allowed_signature(authorization->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_signer_handoff_present(requested_signer_handoff)) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_signer_handoff,
                          LATTICRA_SEAL_SIGNER_HANDOFF_LABEL_MAX) ||
        !is_allowed_signer_handoff(requested_signer_handoff)) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->private_key_handling != 0u ||
        authorization->key_generation_performed != 0u ||
        authorization->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->revocation_lookup_performed != 0u ||
        authorization->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (authorization->signature_performed != 0u ||
        authorization->verification_performed != 0u ||
        authorization->handoff_performed != 0u ||
        authorization->effect_performed != 0u ||
        authorization->host_read_performed != 0u ||
        authorization->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT;
        copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->signer_handoff_ready = 1u;
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
    out->error = LATTICRA_SEAL_SIGNER_HANDOFF_OK;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), "handoff-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signer-handoff-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signer_handoff_is_metadata_only(
    const latticra_seal_signer_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }

    return handoff->signature_performed == 0u &&
           handoff->verification_performed == 0u &&
           handoff->signer_invoked == 0u &&
           handoff->private_key_handling == 0u &&
           handoff->key_generation_performed == 0u &&
           handoff->trust_store_loaded == 0u &&
           handoff->revocation_lookup_performed == 0u &&
           handoff->handoff_performed == 0u &&
           handoff->effect_performed == 0u &&
           handoff->runtime_authority_granted == 0u &&
           handoff->host_read_performed == 0u &&
           handoff->host_write_performed == 0u &&
           handoff->network_performed == 0u &&
           handoff_error_valid(handoff->error) &&
           boolean_flag_valid(handoff->crypto_graduation_gate_present) &&
           boolean_flag_valid(handoff->crypto_graduation_gate_passed) &&
           boolean_flag_valid(handoff->standard_expectations_met) &&
           boolean_flag_valid(handoff->local_verify_graduated) &&
           boolean_flag_valid(handoff->receipt_promotion_graduated) &&
           boolean_flag_valid(handoff->authority_promotion_allowed) &&
           boolean_flag_valid(handoff->signature_request_ready) &&
           boolean_flag_valid(handoff->signing_authorization_ready) &&
           handoff_ready_state_valid(handoff) &&
           bounded_string_is(handoff->signer_handoff_profile,
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
           text_field_valid(handoff->signature_request_state,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           text_field_valid(handoff->signing_authorization_state,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           text_field_valid(handoff->signer_handoff_state,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX) &&
           bounded_string_is(handoff->mode,
                             LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX,
                             "metadata-only") &&
           text_field_valid(handoff->status,
                            LATTICRA_SEAL_SIGNER_HANDOFF_STATE_MAX);
}

latticra_status_t latticra_seal_signer_handoff_render(
    const latticra_seal_signer_handoff_t *handoff,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (handoff == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signer_handoff_is_metadata_only(handoff)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNER HANDOFF\n"
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
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "signature_request_state=%s\n"
        "signature_request_ready=%u\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signer_handoff_state=%s\n"
        "signer_handoff_ready=%u\n"
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
        handoff->signer_handoff_profile,
        handoff->signing_authorization_profile,
        handoff->signature_request_profile,
        handoff->envelope_profile,
        handoff->report_profile,
        handoff->handoff_profile,
        handoff->decision_profile,
        handoff->gate_profile,
        handoff->receipt_profile,
        handoff->verify_profile,
        handoff->message_digest_algorithm,
        handoff->message_digest_hex,
        handoff->public_key_identity_label,
        handoff->crypto_graduation_profile,
        handoff->assurance_baseline_profile,
        handoff->crypto_graduation_gate_state,
        handoff->requested_capability,
        handoff->requested_effect,
        handoff->requested_handoff,
        handoff->requested_report,
        handoff->requested_envelope,
        handoff->requested_signature,
        handoff->requested_signing_authorization,
        handoff->requested_signer_handoff,
        handoff->requested_scope,
        handoff->crypto_graduation_gate_present,
        handoff->crypto_graduation_gate_passed,
        handoff->standard_expectations_met,
        handoff->local_verify_graduated,
        handoff->receipt_promotion_graduated,
        handoff->authority_promotion_allowed,
        handoff->signature_request_state,
        handoff->signature_request_ready,
        handoff->signing_authorization_state,
        handoff->signing_authorization_ready,
        handoff->signer_handoff_state,
        handoff->signer_handoff_ready,
        handoff->signature_performed,
        handoff->verification_performed,
        handoff->signer_invoked,
        handoff->private_key_handling,
        handoff->key_generation_performed,
        handoff->trust_store_loaded,
        handoff->revocation_lookup_performed,
        handoff->handoff_performed,
        handoff->effect_performed,
        handoff->runtime_authority_granted,
        handoff->host_read_performed,
        handoff->host_write_performed,
        handoff->network_performed,
        handoff->mode,
        latticra_seal_signer_handoff_error_label(handoff->error),
        handoff->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
