#include "latticra/seal_runtime_handoff_evaluation.h"

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

static int is_allowed_handoff(const char *handoff) {
    return bounded_string_is(handoff,
                             LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                             "report-only") ||
           bounded_string_is(handoff,
                             LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                             "evaluate-only");
}

static int boolean_flag_valid(unsigned value) {
    return value == 0u || value == 1u;
}

static int evaluation_error_valid(latticra_seal_runtime_handoff_evaluation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int decision_error_valid(latticra_seal_verified_effect_decision_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_INPUT:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_GATE:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_GATE:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_MISSING_REQUESTED_EFFECT:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_UNKNOWN_EFFECT:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_RUNTIME_AUTHORITY:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_NETWORK_EFFECT:
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_CRYPTO_GRADUATION_GATE:
        return 1;
    default:
        return 0;
    }
}

static int decision_flags_valid(
    const latticra_seal_verified_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return boolean_flag_valid(decision->crypto_graduation_gate_present) &&
           boolean_flag_valid(decision->crypto_graduation_gate_passed) &&
           boolean_flag_valid(decision->standard_expectations_met) &&
           boolean_flag_valid(decision->local_verify_graduated) &&
           boolean_flag_valid(decision->receipt_promotion_graduated) &&
           boolean_flag_valid(decision->authority_promotion_allowed) &&
           boolean_flag_valid(decision->verified) &&
           boolean_flag_valid(decision->authority_usable) &&
           boolean_flag_valid(decision->receipt_capability_gate_allowed) &&
           boolean_flag_valid(decision->gate_allowed) &&
           boolean_flag_valid(decision->effect_allowed) &&
           boolean_flag_valid(decision->effect_performed) &&
           boolean_flag_valid(decision->runtime_authority_granted) &&
           boolean_flag_valid(decision->host_read_performed) &&
           boolean_flag_valid(decision->host_write_performed) &&
           boolean_flag_valid(decision->network_performed);
}

static int decision_strings_valid(
    const latticra_seal_verified_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return text_field_valid(decision->decision_profile,
                            LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->gate_profile,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->receipt_profile,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->verify_profile,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->message_digest_algorithm,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_ALGORITHM_MAX) &&
           text_field_terminated(decision->message_digest_hex,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DIGEST_MAX) &&
           text_field_terminated(decision->public_key_identity_label,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->crypto_graduation_profile,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->assurance_baseline_profile,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_valid(decision->crypto_graduation_gate_state,
                            LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX) &&
           text_field_terminated(decision->requested_capability,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->requested_effect,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->requested_scope,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->gate_state,
                                 LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX) &&
           text_field_valid(decision->decision_state,
                            LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX) &&
           text_field_valid(decision->status,
                            LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX) &&
           decision_error_valid(decision->error) &&
           decision_flags_valid(decision);
}

static int requested_handoff_present(const char *requested_handoff) {
    return requested_handoff != NULL && requested_handoff[0] != '\0';
}

static int eligible_state_valid(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation) {
    if (evaluation == NULL || !boolean_flag_valid(evaluation->handoff_eligible)) {
        return 0;
    }
    if (evaluation->handoff_eligible == 0u) {
        return evaluation->error != LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK &&
               text_field_valid(evaluation->handoff_state,
                                LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX) &&
               text_field_valid(evaluation->status,
                                LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX);
    }

    return evaluation->error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK &&
           bounded_string_is(evaluation->status,
                             LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX,
                             "runtime-handoff-evaluation-metadata") &&
           ((bounded_string_is(evaluation->requested_handoff,
                               LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                               "report-only") &&
             bounded_string_is(evaluation->handoff_state,
                               LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX,
                               "eligible-report-only")) ||
            (bounded_string_is(evaluation->requested_handoff,
                               LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                               "evaluate-only") &&
             bounded_string_is(evaluation->handoff_state,
                               LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX,
                               "eligible-evaluate-only")));
}

static const char *safe_requested_handoff_for_copy(const char *requested_handoff) {
    if (!requested_handoff_present(requested_handoff)) {
        return NULL;
    }
    if (!text_field_valid(requested_handoff,
                          LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX)) {
        return "invalid-handoff";
    }
    return requested_handoff;
}

const char *latticra_seal_runtime_handoff_evaluation_error_label(
    latticra_seal_runtime_handoff_evaluation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION:
        return "invalid-decision";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION:
        return "denied-decision";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT:
        return "denied-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF:
        return "missing-requested-handoff";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF:
        return "denied-unknown-handoff";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void evaluation_init(latticra_seal_runtime_handoff_evaluation_t *evaluation) {
    memset(evaluation, 0, sizeof(*evaluation));
    copy_literal(evaluation->handoff_profile, sizeof(evaluation->handoff_profile), "latticra-seal-runtime-handoff-evaluation/0.1");
    copy_literal(evaluation->crypto_graduation_gate_state, sizeof(evaluation->crypto_graduation_gate_state), "not-required");
    copy_literal(evaluation->handoff_state, sizeof(evaluation->handoff_state), "denied-decision");
    evaluation->crypto_graduation_gate_present = 0u;
    evaluation->crypto_graduation_gate_passed = 0u;
    evaluation->standard_expectations_met = 0u;
    evaluation->local_verify_graduated = 0u;
    evaluation->receipt_promotion_graduated = 0u;
    evaluation->authority_promotion_allowed = 0u;
    evaluation->verified = 0u;
    evaluation->authority_usable = 0u;
    evaluation->receipt_capability_gate_allowed = 0u;
    evaluation->gate_allowed = 0u;
    evaluation->effect_allowed = 0u;
    evaluation->handoff_eligible = 0u;
    evaluation->handoff_performed = 0u;
    evaluation->effect_performed = 0u;
    evaluation->runtime_authority_granted = 0u;
    evaluation->host_read_performed = 0u;
    evaluation->host_write_performed = 0u;
    evaluation->network_performed = 0u;
    evaluation->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT;
    copy_literal(evaluation->status, sizeof(evaluation->status), "invalid-input");
}

static void copy_decision_metadata(
    const latticra_seal_verified_effect_decision_t *decision,
    const char *requested_handoff,
    latticra_seal_runtime_handoff_evaluation_t *out) {
    copy_literal(out->decision_profile, sizeof(out->decision_profile), decision->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), decision->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), decision->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), decision->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), decision->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), decision->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), decision->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), decision->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), decision->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), decision->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), decision->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), decision->requested_effect);
    copy_literal(out->requested_handoff,
                 sizeof(out->requested_handoff),
                 safe_requested_handoff_for_copy(requested_handoff));
    copy_literal(out->requested_scope, sizeof(out->requested_scope), decision->requested_scope);
    out->crypto_graduation_gate_present = decision->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = decision->crypto_graduation_gate_passed;
    out->standard_expectations_met = decision->standard_expectations_met;
    out->local_verify_graduated = decision->local_verify_graduated;
    out->receipt_promotion_graduated = decision->receipt_promotion_graduated;
    out->authority_promotion_allowed = decision->authority_promotion_allowed;
    out->verified = decision->verified;
    out->authority_usable = decision->authority_usable;
    out->receipt_capability_gate_allowed = decision->receipt_capability_gate_allowed;
    out->gate_allowed = decision->gate_allowed;
    copy_literal(out->gate_state, sizeof(out->gate_state), decision->gate_state);
    copy_literal(out->decision_state, sizeof(out->decision_state), decision->decision_state);
    out->effect_allowed = decision->effect_allowed;
    out->effect_performed = decision->effect_performed;
    out->runtime_authority_granted = decision->runtime_authority_granted;
    out->host_read_performed = decision->host_read_performed;
    out->host_write_performed = decision->host_write_performed;
    out->network_performed = decision->network_performed;
}

latticra_status_t latticra_seal_runtime_handoff_evaluation_from_decision(
    const latticra_seal_verified_effect_decision_t *decision,
    const char *requested_handoff,
    latticra_seal_runtime_handoff_evaluation_t *out) {
    int decision_report;
    int decision_evaluate;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    evaluation_init(out);

    if (decision == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!decision_strings_valid(decision)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
        copy_literal(out->status, sizeof(out->status), "invalid-decision");
        return LATTICRA_STATUS_OK;
    }

    copy_decision_metadata(decision, requested_handoff, out);

    if (decision->error != LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
        copy_literal(out->status, sizeof(out->status), "invalid-decision");
        return LATTICRA_STATUS_OK;
    }

    if (decision->crypto_graduation_gate_present != 0u &&
        (decision->crypto_graduation_gate_passed != 1u ||
         decision->standard_expectations_met != 1u ||
         decision->local_verify_graduated != 1u ||
         decision->receipt_promotion_graduated != 1u ||
         decision->authority_promotion_allowed != 0u ||
         !bounded_string_is(decision->crypto_graduation_gate_state,
                            LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX,
                            "graduated-authority-neutral"))) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (decision->effect_allowed != 1u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-effect");
        return LATTICRA_STATUS_OK;
    }

    decision_report = bounded_string_is(decision->decision_state,
                                        LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX,
                                        "allowed-report-only");
    decision_evaluate = bounded_string_is(decision->decision_state,
                                          LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_STATE_MAX,
                                          "allowed-evaluate-only");
    if (!decision_report && !decision_evaluate) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
        copy_literal(out->status, sizeof(out->status), "denied-decision");
        return LATTICRA_STATUS_OK;
    }

    if (decision->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (decision->effect_performed != 0u ||
        decision->host_read_performed != 0u ||
        decision->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (decision->network_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!requested_handoff_present(requested_handoff)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "missing-requested-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(requested_handoff,
                          LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) ||
        !is_allowed_handoff(requested_handoff)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-handoff");
        return LATTICRA_STATUS_OK;
    }

    if ((decision_report &&
         !bounded_string_is(requested_handoff,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                            "report-only")) ||
        (decision_evaluate &&
         !bounded_string_is(requested_handoff,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                            "evaluate-only"))) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-effect");
        return LATTICRA_STATUS_OK;
    }

    out->handoff_eligible = 1u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK;

    if (bounded_string_is(requested_handoff,
                          LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX,
                          "report-only")) {
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "eligible-report-only");
    } else {
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "eligible-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "runtime-handoff-evaluation-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_handoff_evaluation_is_metadata_only(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation) {
    if (evaluation == NULL) {
        return 0;
    }

    return evaluation->handoff_performed == 0u &&
           evaluation->effect_performed == 0u &&
           evaluation->runtime_authority_granted == 0u &&
           evaluation->host_read_performed == 0u &&
           evaluation->host_write_performed == 0u &&
           evaluation->network_performed == 0u &&
           evaluation_error_valid(evaluation->error) &&
           boolean_flag_valid(evaluation->crypto_graduation_gate_present) &&
           boolean_flag_valid(evaluation->crypto_graduation_gate_passed) &&
           boolean_flag_valid(evaluation->standard_expectations_met) &&
           boolean_flag_valid(evaluation->local_verify_graduated) &&
           boolean_flag_valid(evaluation->receipt_promotion_graduated) &&
           boolean_flag_valid(evaluation->authority_promotion_allowed) &&
           boolean_flag_valid(evaluation->verified) &&
           boolean_flag_valid(evaluation->authority_usable) &&
           boolean_flag_valid(evaluation->receipt_capability_gate_allowed) &&
           boolean_flag_valid(evaluation->gate_allowed) &&
           boolean_flag_valid(evaluation->effect_allowed) &&
           eligible_state_valid(evaluation) &&
           bounded_string_is(evaluation->handoff_profile,
                             LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX,
                             "latticra-seal-runtime-handoff-evaluation/0.1") &&
           text_field_terminated(evaluation->decision_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_terminated(evaluation->gate_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_terminated(evaluation->receipt_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_terminated(evaluation->verify_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_terminated(evaluation->message_digest_algorithm,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_ALGORITHM_MAX) &&
           text_field_terminated(evaluation->message_digest_hex,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DIGEST_MAX) &&
           text_field_terminated(evaluation->public_key_identity_label,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) &&
           text_field_terminated(evaluation->crypto_graduation_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_terminated(evaluation->assurance_baseline_profile,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_PROFILE_MAX) &&
           text_field_valid(evaluation->crypto_graduation_gate_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX) &&
           text_field_terminated(evaluation->requested_capability,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) &&
           text_field_terminated(evaluation->requested_effect,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) &&
           text_field_terminated(evaluation->requested_handoff,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) &&
           text_field_terminated(evaluation->requested_scope,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_LABEL_MAX) &&
           text_field_terminated(evaluation->gate_state,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX) &&
           text_field_terminated(evaluation->decision_state,
                                 LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX) &&
           text_field_valid(evaluation->handoff_state,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX) &&
           text_field_valid(evaluation->status,
                            LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_STATE_MAX);
}

latticra_status_t latticra_seal_runtime_handoff_evaluation_report(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evaluation == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_runtime_handoff_evaluation_is_metadata_only(evaluation)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME HANDOFF EVALUATION\n"
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
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "decision_state=%s\n"
        "effect_allowed=%u\n"
        "handoff_state=%s\n"
        "handoff_eligible=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        evaluation->handoff_profile,
        evaluation->decision_profile,
        evaluation->gate_profile,
        evaluation->receipt_profile,
        evaluation->verify_profile,
        evaluation->message_digest_algorithm,
        evaluation->message_digest_hex,
        evaluation->public_key_identity_label,
        evaluation->crypto_graduation_profile,
        evaluation->assurance_baseline_profile,
        evaluation->crypto_graduation_gate_state,
        evaluation->requested_capability,
        evaluation->requested_effect,
        evaluation->requested_handoff,
        evaluation->requested_scope,
        evaluation->crypto_graduation_gate_present,
        evaluation->crypto_graduation_gate_passed,
        evaluation->standard_expectations_met,
        evaluation->local_verify_graduated,
        evaluation->receipt_promotion_graduated,
        evaluation->authority_promotion_allowed,
        evaluation->verified,
        evaluation->authority_usable,
        evaluation->receipt_capability_gate_allowed,
        evaluation->gate_allowed,
        evaluation->gate_state,
        evaluation->decision_state,
        evaluation->effect_allowed,
        evaluation->handoff_state,
        evaluation->handoff_eligible,
        evaluation->handoff_performed,
        evaluation->effect_performed,
        evaluation->runtime_authority_granted,
        evaluation->host_read_performed,
        evaluation->host_write_performed,
        evaluation->network_performed,
        latticra_seal_runtime_handoff_evaluation_error_label(evaluation->error),
        evaluation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
