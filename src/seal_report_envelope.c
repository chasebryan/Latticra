#include "latticra/seal_report_envelope.h"

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

static int is_allowed_envelope(const char *envelope) {
    return bounded_string_is(envelope,
                             LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                             "report-only") ||
           bounded_string_is(envelope,
                             LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                             "evaluate-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
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

static int report_error_valid(latticra_seal_runtime_handoff_report_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_EVALUATION:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_EVALUATION:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_REPORT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_UNKNOWN_REPORT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int report_flags_valid(const latticra_seal_runtime_handoff_report_t *report) {
    if (report == NULL) {
        return 0;
    }

    return boolean_flag_valid(report->crypto_graduation_gate_present) &&
           boolean_flag_valid(report->crypto_graduation_gate_passed) &&
           boolean_flag_valid(report->standard_expectations_met) &&
           boolean_flag_valid(report->local_verify_graduated) &&
           boolean_flag_valid(report->receipt_promotion_graduated) &&
           boolean_flag_valid(report->authority_promotion_allowed) &&
           boolean_flag_valid(report->verified) &&
           boolean_flag_valid(report->authority_usable) &&
           boolean_flag_valid(report->receipt_capability_gate_allowed) &&
           boolean_flag_valid(report->gate_allowed) &&
           boolean_flag_valid(report->effect_allowed) &&
           boolean_flag_valid(report->handoff_eligible) &&
           boolean_flag_valid(report->report_ready) &&
           boolean_flag_valid(report->handoff_performed) &&
           boolean_flag_valid(report->effect_performed) &&
           boolean_flag_valid(report->runtime_authority_granted) &&
           boolean_flag_valid(report->host_read_performed) &&
           boolean_flag_valid(report->host_write_performed) &&
           boolean_flag_valid(report->network_performed);
}

static int report_strings_valid(const latticra_seal_runtime_handoff_report_t *report) {
    if (report == NULL) {
        return 0;
    }

    return bounded_string_is(report->report_profile,
                             LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX,
                             "latticra-seal-runtime-handoff-report/0.1") &&
           text_field_terminated(report->handoff_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->decision_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->gate_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->receipt_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->verify_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->message_digest_algorithm,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_ALGORITHM_MAX) &&
           text_field_terminated(report->message_digest_hex,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DIGEST_MAX) &&
           text_field_terminated(report->public_key_identity_label,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->crypto_graduation_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_terminated(report->assurance_baseline_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_PROFILE_MAX) &&
           text_field_valid(report->crypto_graduation_gate_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           text_field_terminated(report->requested_capability,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->requested_effect,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->requested_handoff,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->requested_report,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->requested_scope,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_LABEL_MAX) &&
           text_field_terminated(report->gate_state,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           text_field_terminated(report->decision_state,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           text_field_valid(report->handoff_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           text_field_valid(report->report_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           text_field_valid(report->status,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX) &&
           report_error_valid(report->error) &&
           report_flags_valid(report);
}

static int requested_envelope_present(const char *requested_envelope) {
    return requested_envelope != NULL && requested_envelope[0] != '\0';
}

static int envelope_ready_state_valid(const latticra_seal_report_envelope_t *envelope) {
    if (envelope == NULL || !boolean_flag_valid(envelope->envelope_ready)) {
        return 0;
    }
    if (envelope->envelope_ready == 0u) {
        return envelope->error != LATTICRA_SEAL_REPORT_ENVELOPE_OK &&
               text_field_valid(envelope->envelope_state,
                                LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX) &&
               text_field_valid(envelope->status,
                                LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX);
    }

    return envelope->error == LATTICRA_SEAL_REPORT_ENVELOPE_OK &&
           bounded_string_is(envelope->status,
                             LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                             "sealed-report-envelope-metadata") &&
           ((bounded_string_is(envelope->requested_envelope,
                               LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                               "report-only") &&
             bounded_string_is(envelope->envelope_state,
                               LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                               "sealed-report-only")) ||
            (bounded_string_is(envelope->requested_envelope,
                               LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                               "evaluate-only") &&
             bounded_string_is(envelope->envelope_state,
                               LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX,
                               "sealed-evaluate-only")));
}

static const char *safe_requested_envelope_for_copy(
    const char *requested_envelope) {
    if (!requested_envelope_present(requested_envelope)) {
        return NULL;
    }
    if (!text_field_valid(requested_envelope,
                          LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX)) {
        return "invalid-envelope";
    }
    return requested_envelope;
}

const char *latticra_seal_report_envelope_error_label(
    latticra_seal_report_envelope_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_REPORT_ENVELOPE_OK:
        return "ok";
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT:
        return "invalid-report";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT:
        return "denied-report";
    case LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE:
        return "missing-requested-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE:
        return "denied-unknown-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE:
        return "denied-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void envelope_init(latticra_seal_report_envelope_t *envelope) {
    memset(envelope, 0, sizeof(*envelope));
    copy_literal(envelope->envelope_profile, sizeof(envelope->envelope_profile), "latticra-seal-report-envelope/0.1");
    copy_literal(envelope->crypto_graduation_gate_state, sizeof(envelope->crypto_graduation_gate_state), "not-required");
    copy_literal(envelope->envelope_state, sizeof(envelope->envelope_state), "denied-report");
    envelope->crypto_graduation_gate_present = 0u;
    envelope->crypto_graduation_gate_passed = 0u;
    envelope->standard_expectations_met = 0u;
    envelope->local_verify_graduated = 0u;
    envelope->receipt_promotion_graduated = 0u;
    envelope->authority_promotion_allowed = 0u;
    envelope->report_ready = 0u;
    envelope->envelope_ready = 0u;
    envelope->signature_performed = 0u;
    envelope->handoff_performed = 0u;
    envelope->effect_performed = 0u;
    envelope->runtime_authority_granted = 0u;
    envelope->host_read_performed = 0u;
    envelope->host_write_performed = 0u;
    envelope->network_performed = 0u;
    envelope->error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT;
    copy_literal(envelope->status, sizeof(envelope->status), "invalid-input");
}

static void copy_report_metadata(
    const latticra_seal_runtime_handoff_report_t *report,
    const char *requested_envelope,
    latticra_seal_report_envelope_t *out) {
    copy_literal(out->report_profile, sizeof(out->report_profile), report->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), report->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), report->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), report->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), report->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), report->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), report->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), report->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), report->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), report->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), report->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), report->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), report->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), report->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), report->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), report->requested_report);
    copy_literal(out->requested_envelope,
                 sizeof(out->requested_envelope),
                 safe_requested_envelope_for_copy(requested_envelope));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), report->requested_scope);
    out->crypto_graduation_gate_present = report->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = report->crypto_graduation_gate_passed;
    out->standard_expectations_met = report->standard_expectations_met;
    out->local_verify_graduated = report->local_verify_graduated;
    out->receipt_promotion_graduated = report->receipt_promotion_graduated;
    out->authority_promotion_allowed = report->authority_promotion_allowed;
    copy_literal(out->report_state, sizeof(out->report_state), report->report_state);
    out->report_ready = report->report_ready;
    out->handoff_performed = report->handoff_performed;
    out->effect_performed = report->effect_performed;
    out->runtime_authority_granted = report->runtime_authority_granted;
    out->host_read_performed = report->host_read_performed;
    out->host_write_performed = report->host_write_performed;
    out->network_performed = report->network_performed;
}

latticra_status_t latticra_seal_report_envelope_from_report(
    const latticra_seal_runtime_handoff_report_t *report,
    const char *requested_envelope,
    latticra_seal_report_envelope_t *out) {
    int report_only_ready;
    int evaluate_only_ready;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    envelope_init(out);

    if (report == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!report_strings_valid(report)) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "invalid-report");
        return LATTICRA_STATUS_OK;
    }

    copy_report_metadata(report, requested_envelope, out);

    if (report->error != LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "invalid-report");
        return LATTICRA_STATUS_OK;
    }

    if (report->crypto_graduation_gate_present != 0u &&
        (report->crypto_graduation_gate_passed != 1u ||
         report->standard_expectations_met != 1u ||
         report->local_verify_graduated != 1u ||
         report->receipt_promotion_graduated != 1u ||
         report->authority_promotion_allowed != 0u ||
         !bounded_string_is(report->crypto_graduation_gate_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX,
                            "graduated-authority-neutral"))) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (report->report_ready != 1u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-report");
        return LATTICRA_STATUS_OK;
    }

    report_only_ready = bounded_string_is(report->report_state,
                                          LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX,
                                          "ready-report-only");
    evaluate_only_ready = bounded_string_is(report->report_state,
                                            LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_STATE_MAX,
                                            "ready-evaluate-only");
    if (!report_only_ready && !evaluate_only_ready) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-report");
        return LATTICRA_STATUS_OK;
    }

    if (report->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (report->handoff_performed != 0u ||
        report->effect_performed != 0u ||
        report->host_read_performed != 0u ||
        report->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (report->network_performed != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_envelope_present(requested_envelope)) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "missing-requested-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_envelope,
                          LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX) ||
        !is_allowed_envelope(requested_envelope)) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-envelope");
        return LATTICRA_STATUS_OK;
    }

    if ((report_only_ready &&
         !bounded_string_is(requested_envelope,
                            LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                            "report-only")) ||
        (evaluate_only_ready &&
         !bounded_string_is(requested_envelope,
                            LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                            "evaluate-only"))) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    out->envelope_ready = 1u;
    out->signature_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_REPORT_ENVELOPE_OK;

    if (bounded_string_is(requested_envelope,
                          LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX,
                          "report-only")) {
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "sealed-report-only");
    } else {
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "sealed-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "sealed-report-envelope-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_report_envelope_is_metadata_only(
    const latticra_seal_report_envelope_t *envelope) {
    if (envelope == NULL) {
        return 0;
    }

    return envelope->signature_performed == 0u &&
           envelope->handoff_performed == 0u &&
           envelope->effect_performed == 0u &&
           envelope->runtime_authority_granted == 0u &&
           envelope->host_read_performed == 0u &&
           envelope->host_write_performed == 0u &&
           envelope->network_performed == 0u &&
           envelope_error_valid(envelope->error) &&
           boolean_flag_valid(envelope->crypto_graduation_gate_present) &&
           boolean_flag_valid(envelope->crypto_graduation_gate_passed) &&
           boolean_flag_valid(envelope->standard_expectations_met) &&
           boolean_flag_valid(envelope->local_verify_graduated) &&
           boolean_flag_valid(envelope->receipt_promotion_graduated) &&
           boolean_flag_valid(envelope->authority_promotion_allowed) &&
           boolean_flag_valid(envelope->report_ready) &&
           envelope_ready_state_valid(envelope) &&
           bounded_string_is(envelope->envelope_profile,
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
                            LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX);
}

latticra_status_t latticra_seal_report_envelope_render(
    const latticra_seal_report_envelope_t *envelope,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (envelope == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_report_envelope_is_metadata_only(envelope)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL REPORT ENVELOPE\n"
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
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "report_state=%s\n"
        "report_ready=%u\n"
        "envelope_state=%s\n"
        "envelope_ready=%u\n"
        "signature_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        envelope->envelope_profile,
        envelope->report_profile,
        envelope->handoff_profile,
        envelope->decision_profile,
        envelope->gate_profile,
        envelope->receipt_profile,
        envelope->verify_profile,
        envelope->message_digest_algorithm,
        envelope->message_digest_hex,
        envelope->public_key_identity_label,
        envelope->crypto_graduation_profile,
        envelope->assurance_baseline_profile,
        envelope->crypto_graduation_gate_state,
        envelope->requested_capability,
        envelope->requested_effect,
        envelope->requested_handoff,
        envelope->requested_report,
        envelope->requested_envelope,
        envelope->requested_scope,
        envelope->crypto_graduation_gate_present,
        envelope->crypto_graduation_gate_passed,
        envelope->standard_expectations_met,
        envelope->local_verify_graduated,
        envelope->receipt_promotion_graduated,
        envelope->authority_promotion_allowed,
        envelope->report_state,
        envelope->report_ready,
        envelope->envelope_state,
        envelope->envelope_ready,
        envelope->signature_performed,
        envelope->handoff_performed,
        envelope->effect_performed,
        envelope->runtime_authority_granted,
        envelope->host_read_performed,
        envelope->host_write_performed,
        envelope->network_performed,
        latticra_seal_report_envelope_error_label(envelope->error),
        envelope->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
