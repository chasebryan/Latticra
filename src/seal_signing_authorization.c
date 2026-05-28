#include "latticra/seal_signing_authorization.h"

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
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX,
                             "Ed25519-development");
}

static int is_allowed_authorization(const char *authorization) {
    return bounded_string_is(authorization,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX,
                             "metadata-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int request_error_valid(latticra_seal_signature_request_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_REQUEST_OK:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int request_flags_valid(const latticra_seal_signature_request_t *request) {
    if (request == NULL) {
        return 0;
    }

    return boolean_flag_valid(request->crypto_graduation_gate_present) &&
           boolean_flag_valid(request->crypto_graduation_gate_passed) &&
           boolean_flag_valid(request->standard_expectations_met) &&
           boolean_flag_valid(request->local_verify_graduated) &&
           boolean_flag_valid(request->receipt_promotion_graduated) &&
           boolean_flag_valid(request->authority_promotion_allowed) &&
           boolean_flag_valid(request->envelope_ready) &&
           boolean_flag_valid(request->signature_request_ready) &&
           boolean_flag_valid(request->signature_performed) &&
           boolean_flag_valid(request->verification_performed) &&
           boolean_flag_valid(request->private_key_handling) &&
           boolean_flag_valid(request->handoff_performed) &&
           boolean_flag_valid(request->effect_performed) &&
           boolean_flag_valid(request->runtime_authority_granted) &&
           boolean_flag_valid(request->host_read_performed) &&
           boolean_flag_valid(request->host_write_performed) &&
           boolean_flag_valid(request->network_performed);
}

static int request_strings_valid(const latticra_seal_signature_request_t *request) {
    if (request == NULL) {
        return 0;
    }

    return bounded_string_is(request->signature_request_profile,
                             LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX,
                             "latticra-seal-signature-request/0.1") &&
           text_field_terminated(request->envelope_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->report_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->handoff_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->decision_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->gate_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->receipt_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->verify_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->message_digest_algorithm,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_ALGORITHM_MAX) &&
           text_field_terminated(request->message_digest_hex,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_DIGEST_MAX) &&
           text_field_terminated(request->public_key_identity_label,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->crypto_graduation_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_terminated(request->assurance_baseline_profile,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_PROFILE_MAX) &&
           text_field_valid(request->crypto_graduation_gate_state,
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX) &&
           text_field_terminated(request->requested_capability,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_effect,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_handoff,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_report,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_envelope,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_signature,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_terminated(request->requested_scope,
                                 LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) &&
           text_field_valid(request->envelope_state,
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX) &&
           text_field_valid(request->signature_request_state,
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX) &&
           text_field_valid(request->status,
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX) &&
           request_error_valid(request->error) &&
           request_flags_valid(request);
}

static int requested_authorization_present(
    const char *requested_signing_authorization) {
    return requested_signing_authorization != NULL &&
           requested_signing_authorization[0] != '\0';
}

static int authorization_ready_state_valid(
    const latticra_seal_signing_authorization_t *authorization) {
    if (authorization == NULL ||
        !boolean_flag_valid(authorization->signing_authorization_ready)) {
        return 0;
    }
    if (authorization->signing_authorization_ready == 0u) {
        return authorization->error != LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK &&
               text_field_valid(authorization->signing_authorization_state,
                                LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX) &&
               text_field_valid(authorization->status,
                                LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX);
    }

    return authorization->error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK &&
           bounded_string_is(authorization->requested_signing_authorization,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX,
                             "metadata-only") &&
           bounded_string_is(authorization->signing_authorization_state,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX,
                             "authorized-metadata-only") &&
           bounded_string_is(authorization->status,
                             LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX,
                             "signing-authorization-metadata");
}

static const char *safe_requested_authorization_for_copy(
    const char *requested_signing_authorization) {
    if (!requested_authorization_present(requested_signing_authorization)) {
        return NULL;
    }
    if (!text_field_valid(requested_signing_authorization,
                          LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX)) {
        return "invalid-signing-authorization";
    }
    return requested_signing_authorization;
}

const char *latticra_seal_signing_authorization_error_label(
    latticra_seal_signing_authorization_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST:
        return "invalid-signature-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST:
        return "denied-signature-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST:
        return "denied-authorization-request";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void authorization_init(latticra_seal_signing_authorization_t *authorization) {
    memset(authorization, 0, sizeof(*authorization));
    copy_literal(
        authorization->signing_authorization_profile,
        sizeof(authorization->signing_authorization_profile),
        "latticra-seal-signing-authorization/0.1");
    copy_literal(
        authorization->signing_authorization_state,
        sizeof(authorization->signing_authorization_state),
        "denied-signature-request");
    copy_literal(authorization->crypto_graduation_gate_state, sizeof(authorization->crypto_graduation_gate_state), "not-required");
    authorization->crypto_graduation_gate_present = 0u;
    authorization->crypto_graduation_gate_passed = 0u;
    authorization->standard_expectations_met = 0u;
    authorization->local_verify_graduated = 0u;
    authorization->receipt_promotion_graduated = 0u;
    authorization->authority_promotion_allowed = 0u;
    copy_literal(authorization->mode, sizeof(authorization->mode), "metadata-only");
    authorization->signature_request_ready = 0u;
    authorization->signing_authorization_ready = 0u;
    authorization->signature_performed = 0u;
    authorization->verification_performed = 0u;
    authorization->private_key_handling = 0u;
    authorization->key_generation_performed = 0u;
    authorization->trust_store_loaded = 0u;
    authorization->revocation_lookup_performed = 0u;
    authorization->handoff_performed = 0u;
    authorization->effect_performed = 0u;
    authorization->runtime_authority_granted = 0u;
    authorization->host_read_performed = 0u;
    authorization->host_write_performed = 0u;
    authorization->network_performed = 0u;
    authorization->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT;
    copy_literal(authorization->status, sizeof(authorization->status), "invalid-input");
}

static void copy_request_metadata(
    const latticra_seal_signature_request_t *request,
    const char *requested_signing_authorization,
    latticra_seal_signing_authorization_t *out) {
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), request->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), request->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), request->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), request->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), request->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), request->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), request->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), request->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), request->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), request->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), request->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), request->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), request->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), request->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), request->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), request->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), request->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), request->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), request->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), request->requested_signature);
    copy_literal(out->requested_signing_authorization,
                 sizeof(out->requested_signing_authorization),
                 safe_requested_authorization_for_copy(requested_signing_authorization));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), request->requested_scope);
    out->crypto_graduation_gate_present = request->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = request->crypto_graduation_gate_passed;
    out->standard_expectations_met = request->standard_expectations_met;
    out->local_verify_graduated = request->local_verify_graduated;
    out->receipt_promotion_graduated = request->receipt_promotion_graduated;
    out->authority_promotion_allowed = request->authority_promotion_allowed;
    copy_literal(out->signature_request_state, sizeof(out->signature_request_state), request->signature_request_state);
    out->signature_request_ready = request->signature_request_ready;
    out->signature_performed = request->signature_performed;
    out->verification_performed = request->verification_performed;
    out->private_key_handling = request->private_key_handling;
    out->handoff_performed = request->handoff_performed;
    out->effect_performed = request->effect_performed;
    out->runtime_authority_granted = request->runtime_authority_granted;
    out->host_read_performed = request->host_read_performed;
    out->host_write_performed = request->host_write_performed;
    out->network_performed = request->network_performed;
}

latticra_status_t latticra_seal_signing_authorization_from_request(
    const latticra_seal_signature_request_t *request,
    const char *requested_signing_authorization,
    latticra_seal_signing_authorization_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    authorization_init(out);

    if (request == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!request_strings_valid(request)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST;
        copy_literal(out->signing_authorization_state,
                     sizeof(out->signing_authorization_state),
                     "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "invalid-signature-request");
        return LATTICRA_STATUS_OK;
    }

    copy_request_metadata(request, requested_signing_authorization, out);

    if (request->error != LATTICRA_SEAL_SIGNATURE_REQUEST_OK) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "invalid-signature-request");
        return LATTICRA_STATUS_OK;
    }

    if (request->crypto_graduation_gate_present != 0u &&
        (request->crypto_graduation_gate_passed != 1u ||
         request->standard_expectations_met != 1u ||
         request->local_verify_graduated != 1u ||
         request->receipt_promotion_graduated != 1u ||
         request->authority_promotion_allowed != 0u ||
         !bounded_string_is(request->crypto_graduation_gate_state,
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX,
                            "graduated-authority-neutral"))) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (request->signature_request_ready != 1u ||
        !bounded_string_is(request->signature_request_state,
                           LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX,
                           "requested-metadata-only")) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "denied-signature-request");
        return LATTICRA_STATUS_OK;
    }

    if (request->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (request->private_key_handling != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (request->signature_performed != 0u ||
        request->verification_performed != 0u ||
        request->handoff_performed != 0u ||
        request->effect_performed != 0u ||
        request->host_read_performed != 0u ||
        request->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (request->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (request->requested_signature[0] == '\0' ||
        !text_field_valid(request->requested_signature,
                          LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) ||
        !is_allowed_signature(request->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_authorization_present(requested_signing_authorization)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-authorization-request");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_signing_authorization,
                          LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX) ||
        !is_allowed_authorization(requested_signing_authorization)) {
        out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST;
        copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "denied-authorization-request");
        copy_literal(out->status, sizeof(out->status), "denied-authorization-request");
        return LATTICRA_STATUS_OK;
    }

    out->signing_authorization_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
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
    out->error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK;
    copy_literal(out->signing_authorization_state, sizeof(out->signing_authorization_state), "authorized-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signing-authorization-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signing_authorization_is_metadata_only(
    const latticra_seal_signing_authorization_t *authorization) {
    if (authorization == NULL) {
        return 0;
    }

    return authorization->signature_performed == 0u &&
           authorization->verification_performed == 0u &&
           authorization->private_key_handling == 0u &&
           authorization->key_generation_performed == 0u &&
           authorization->trust_store_loaded == 0u &&
           authorization->revocation_lookup_performed == 0u &&
           authorization->handoff_performed == 0u &&
           authorization->effect_performed == 0u &&
           authorization->runtime_authority_granted == 0u &&
           authorization->host_read_performed == 0u &&
           authorization->host_write_performed == 0u &&
           authorization->network_performed == 0u &&
           authorization_error_valid(authorization->error) &&
           boolean_flag_valid(authorization->crypto_graduation_gate_present) &&
           boolean_flag_valid(authorization->crypto_graduation_gate_passed) &&
           boolean_flag_valid(authorization->standard_expectations_met) &&
           boolean_flag_valid(authorization->local_verify_graduated) &&
           boolean_flag_valid(authorization->receipt_promotion_graduated) &&
           boolean_flag_valid(authorization->authority_promotion_allowed) &&
           boolean_flag_valid(authorization->signature_request_ready) &&
           authorization_ready_state_valid(authorization) &&
           bounded_string_is(authorization->signing_authorization_profile,
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
                            LATTICRA_SEAL_SIGNING_AUTHORIZATION_STATE_MAX);
}

latticra_status_t latticra_seal_signing_authorization_render(
    const latticra_seal_signing_authorization_t *authorization,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (authorization == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signing_authorization_is_metadata_only(authorization)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNING AUTHORIZATION\n"
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
        "signature_performed=%u\n"
        "verification_performed=%u\n"
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
        authorization->signing_authorization_profile,
        authorization->signature_request_profile,
        authorization->envelope_profile,
        authorization->report_profile,
        authorization->handoff_profile,
        authorization->decision_profile,
        authorization->gate_profile,
        authorization->receipt_profile,
        authorization->verify_profile,
        authorization->message_digest_algorithm,
        authorization->message_digest_hex,
        authorization->public_key_identity_label,
        authorization->crypto_graduation_profile,
        authorization->assurance_baseline_profile,
        authorization->crypto_graduation_gate_state,
        authorization->requested_capability,
        authorization->requested_effect,
        authorization->requested_handoff,
        authorization->requested_report,
        authorization->requested_envelope,
        authorization->requested_signature,
        authorization->requested_signing_authorization,
        authorization->requested_scope,
        authorization->crypto_graduation_gate_present,
        authorization->crypto_graduation_gate_passed,
        authorization->standard_expectations_met,
        authorization->local_verify_graduated,
        authorization->receipt_promotion_graduated,
        authorization->authority_promotion_allowed,
        authorization->signature_request_state,
        authorization->signature_request_ready,
        authorization->signing_authorization_state,
        authorization->signing_authorization_ready,
        authorization->signature_performed,
        authorization->verification_performed,
        authorization->private_key_handling,
        authorization->key_generation_performed,
        authorization->trust_store_loaded,
        authorization->revocation_lookup_performed,
        authorization->handoff_performed,
        authorization->effect_performed,
        authorization->runtime_authority_granted,
        authorization->host_read_performed,
        authorization->host_write_performed,
        authorization->network_performed,
        authorization->mode,
        latticra_seal_signing_authorization_error_label(authorization->error),
        authorization->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
