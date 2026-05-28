#include "latticra/seal_signature_request.h"

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

static int is_allowed_signature_request(const char *signature) {
    return bounded_string_is(signature,
                             LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX,
                             "Ed25519-development");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int envelope_error_valid(latticra_seal_report_envelope_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_REPORT_ENVELOPE_OK:
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT:
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT:
    case LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int envelope_flags_valid(const latticra_seal_report_envelope_t *envelope) {
    if (envelope == NULL) {
        return 0;
    }

    return boolean_flag_valid(envelope->crypto_graduation_gate_present) &&
           boolean_flag_valid(envelope->crypto_graduation_gate_passed) &&
           boolean_flag_valid(envelope->standard_expectations_met) &&
           boolean_flag_valid(envelope->local_verify_graduated) &&
           boolean_flag_valid(envelope->receipt_promotion_graduated) &&
           boolean_flag_valid(envelope->authority_promotion_allowed) &&
           boolean_flag_valid(envelope->report_ready) &&
           boolean_flag_valid(envelope->envelope_ready) &&
           boolean_flag_valid(envelope->signature_performed) &&
           boolean_flag_valid(envelope->handoff_performed) &&
           boolean_flag_valid(envelope->effect_performed) &&
           boolean_flag_valid(envelope->runtime_authority_granted) &&
           boolean_flag_valid(envelope->host_read_performed) &&
           boolean_flag_valid(envelope->host_write_performed) &&
           boolean_flag_valid(envelope->network_performed);
}

static int envelope_strings_valid(const latticra_seal_report_envelope_t *envelope) {
    if (envelope == NULL) {
        return 0;
    }

    return bounded_string_is(envelope->envelope_profile,
                             LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX,
                             "latticra-seal-report-envelope/0.1") &&
           text_field_terminated(envelope->report_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->handoff_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->decision_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->gate_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->receipt_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->verify_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->message_digest_algorithm,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_ALGORITHM_MAX) &&
           text_field_terminated(envelope->message_digest_hex,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_DIGEST_MAX) &&
           text_field_terminated(envelope->public_key_identity_label,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->crypto_graduation_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_terminated(envelope->assurance_baseline_profile,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX) &&
           text_field_valid(envelope->crypto_graduation_gate_state,
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX) &&
           text_field_terminated(envelope->requested_capability,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->requested_effect,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->requested_handoff,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->requested_report,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->requested_envelope,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_terminated(envelope->requested_scope,
                                 LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) &&
           text_field_valid(envelope->report_state,
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX) &&
           text_field_valid(envelope->envelope_state,
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX) &&
           text_field_valid(envelope->status,
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX) &&
           envelope_error_valid(envelope->error) &&
           envelope_flags_valid(envelope);
}

static int requested_signature_present(const char *requested_signature) {
    return requested_signature != NULL && requested_signature[0] != '\0';
}

static int request_ready_state_valid(const latticra_seal_signature_request_t *request) {
    if (request == NULL || !boolean_flag_valid(request->signature_request_ready)) {
        return 0;
    }
    if (request->signature_request_ready == 0u) {
        return request->error != LATTICRA_SEAL_SIGNATURE_REQUEST_OK &&
               text_field_valid(request->signature_request_state,
                                LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX) &&
               text_field_valid(request->status,
                                LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX);
    }

    return request->error == LATTICRA_SEAL_SIGNATURE_REQUEST_OK &&
           bounded_string_is(request->requested_signature,
                             LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX,
                             "Ed25519-development") &&
           bounded_string_is(request->signature_request_state,
                             LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX,
                             "requested-metadata-only") &&
           bounded_string_is(request->status,
                             LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX,
                             "signature-request-metadata");
}

static const char *safe_requested_signature_for_copy(
    const char *requested_signature) {
    if (!requested_signature_present(requested_signature)) {
        return NULL;
    }
    if (!text_field_valid(requested_signature,
                          LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX)) {
        return "invalid-signature";
    }
    return requested_signature;
}

const char *latticra_seal_signature_request_error_label(
    latticra_seal_signature_request_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_REQUEST_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE:
        return "invalid-envelope";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE:
        return "denied-envelope";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE:
        return "missing-requested-signature";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE:
        return "denied-unknown-signature";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void request_init(latticra_seal_signature_request_t *request) {
    memset(request, 0, sizeof(*request));
    copy_literal(
        request->signature_request_profile,
        sizeof(request->signature_request_profile),
        "latticra-seal-signature-request/0.1");
    copy_literal(
        request->signature_request_state,
        sizeof(request->signature_request_state),
        "denied-envelope");
    copy_literal(request->crypto_graduation_gate_state, sizeof(request->crypto_graduation_gate_state), "not-required");
    request->crypto_graduation_gate_present = 0u;
    request->crypto_graduation_gate_passed = 0u;
    request->standard_expectations_met = 0u;
    request->local_verify_graduated = 0u;
    request->receipt_promotion_graduated = 0u;
    request->authority_promotion_allowed = 0u;
    request->envelope_ready = 0u;
    request->signature_request_ready = 0u;
    request->signature_performed = 0u;
    request->verification_performed = 0u;
    request->private_key_handling = 0u;
    request->handoff_performed = 0u;
    request->effect_performed = 0u;
    request->runtime_authority_granted = 0u;
    request->host_read_performed = 0u;
    request->host_write_performed = 0u;
    request->network_performed = 0u;
    request->error = LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT;
    copy_literal(request->status, sizeof(request->status), "invalid-input");
}

static void copy_envelope_metadata(
    const latticra_seal_report_envelope_t *envelope,
    const char *requested_signature,
    latticra_seal_signature_request_t *out) {
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), envelope->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), envelope->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), envelope->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), envelope->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), envelope->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), envelope->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), envelope->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), envelope->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), envelope->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), envelope->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), envelope->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), envelope->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), envelope->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), envelope->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), envelope->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), envelope->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), envelope->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), envelope->requested_envelope);
    copy_literal(out->requested_signature,
                 sizeof(out->requested_signature),
                 safe_requested_signature_for_copy(requested_signature));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), envelope->requested_scope);
    out->crypto_graduation_gate_present = envelope->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = envelope->crypto_graduation_gate_passed;
    out->standard_expectations_met = envelope->standard_expectations_met;
    out->local_verify_graduated = envelope->local_verify_graduated;
    out->receipt_promotion_graduated = envelope->receipt_promotion_graduated;
    out->authority_promotion_allowed = envelope->authority_promotion_allowed;
    copy_literal(out->envelope_state, sizeof(out->envelope_state), envelope->envelope_state);
    out->envelope_ready = envelope->envelope_ready;
    out->signature_performed = envelope->signature_performed;
    out->handoff_performed = envelope->handoff_performed;
    out->effect_performed = envelope->effect_performed;
    out->runtime_authority_granted = envelope->runtime_authority_granted;
    out->host_read_performed = envelope->host_read_performed;
    out->host_write_performed = envelope->host_write_performed;
    out->network_performed = envelope->network_performed;
}

latticra_status_t latticra_seal_signature_request_from_envelope(
    const latticra_seal_report_envelope_t *envelope,
    const char *requested_signature,
    latticra_seal_signature_request_t *out) {
    int envelope_report_ready;
    int envelope_evaluate_ready;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    request_init(out);

    if (envelope == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!envelope_strings_valid(envelope)) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "invalid-envelope");
        return LATTICRA_STATUS_OK;
    }

    copy_envelope_metadata(envelope, requested_signature, out);

    if (envelope->error != LATTICRA_SEAL_REPORT_ENVELOPE_OK) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "invalid-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->crypto_graduation_gate_present != 0u &&
        (envelope->crypto_graduation_gate_passed != 1u ||
         envelope->standard_expectations_met != 1u ||
         envelope->local_verify_graduated != 1u ||
         envelope->receipt_promotion_graduated != 1u ||
         envelope->authority_promotion_allowed != 0u ||
         !bounded_string_is(envelope->crypto_graduation_gate_state,
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                            "graduated-authority-neutral"))) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->envelope_ready != 1u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    envelope_report_ready = bounded_string_is(envelope->envelope_state,
                                              LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                                              "sealed-report-only");
    envelope_evaluate_ready = bounded_string_is(envelope->envelope_state,
                                                LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                                                "sealed-evaluate-only");
    if (!envelope_report_ready && !envelope_evaluate_ready) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->signature_performed != 0u ||
        envelope->handoff_performed != 0u ||
        envelope->effect_performed != 0u ||
        envelope->host_read_performed != 0u ||
        envelope->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_signature_present(requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signature");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_signature,
                          LATTICRA_SEAL_SIGNATURE_REQUEST_LABEL_MAX) ||
        !is_allowed_signature_request(requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-signature");
        return LATTICRA_STATUS_OK;
    }

    out->signature_request_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->private_key_handling = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_OK;
    copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "requested-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signature-request-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signature_request_is_metadata_only(
    const latticra_seal_signature_request_t *request) {
    if (request == NULL) {
        return 0;
    }

    return request->signature_performed == 0u &&
           request->verification_performed == 0u &&
           request->private_key_handling == 0u &&
           request->handoff_performed == 0u &&
           request->effect_performed == 0u &&
           request->runtime_authority_granted == 0u &&
           request->host_read_performed == 0u &&
           request->host_write_performed == 0u &&
           request->network_performed == 0u &&
           request_error_valid(request->error) &&
           boolean_flag_valid(request->crypto_graduation_gate_present) &&
           boolean_flag_valid(request->crypto_graduation_gate_passed) &&
           boolean_flag_valid(request->standard_expectations_met) &&
           boolean_flag_valid(request->local_verify_graduated) &&
           boolean_flag_valid(request->receipt_promotion_graduated) &&
           boolean_flag_valid(request->authority_promotion_allowed) &&
           boolean_flag_valid(request->envelope_ready) &&
           request_ready_state_valid(request) &&
           bounded_string_is(request->signature_request_profile,
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
                            LATTICRA_SEAL_SIGNATURE_REQUEST_STATE_MAX);
}

latticra_status_t latticra_seal_signature_request_render(
    const latticra_seal_signature_request_t *request,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (request == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_signature_request_is_metadata_only(request)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNATURE REQUEST\n"
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
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "envelope_state=%s\n"
        "envelope_ready=%u\n"
        "signature_request_state=%s\n"
        "signature_request_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "private_key_handling=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        request->signature_request_profile,
        request->envelope_profile,
        request->report_profile,
        request->handoff_profile,
        request->decision_profile,
        request->gate_profile,
        request->receipt_profile,
        request->verify_profile,
        request->message_digest_algorithm,
        request->message_digest_hex,
        request->public_key_identity_label,
        request->crypto_graduation_profile,
        request->assurance_baseline_profile,
        request->crypto_graduation_gate_state,
        request->requested_capability,
        request->requested_effect,
        request->requested_handoff,
        request->requested_report,
        request->requested_envelope,
        request->requested_signature,
        request->requested_scope,
        request->crypto_graduation_gate_present,
        request->crypto_graduation_gate_passed,
        request->standard_expectations_met,
        request->local_verify_graduated,
        request->receipt_promotion_graduated,
        request->authority_promotion_allowed,
        request->envelope_state,
        request->envelope_ready,
        request->signature_request_state,
        request->signature_request_ready,
        request->signature_performed,
        request->verification_performed,
        request->private_key_handling,
        request->handoff_performed,
        request->effect_performed,
        request->runtime_authority_granted,
        request->host_read_performed,
        request->host_write_performed,
        request->network_performed,
        latticra_seal_signature_request_error_label(request->error),
        request->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
