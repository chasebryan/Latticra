#include "latticra/seal_effect_decision.h"

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

static int effect_decision_error_valid(latticra_seal_effect_decision_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_EFFECT_DECISION_OK:
    case LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT:
    case LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE:
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST:
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY:
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT:
        return 1;
    default:
        return 0;
    }
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

static int capability_gate_strings_valid(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return bounded_string_is(gate->gate_profile,
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
           bounded_string_is(gate->receipt_state,
                             LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                             "unverified-metadata") &&
           bounded_string_is(gate->verification_state,
                             LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                             "unsupported") &&
           text_field_terminated(gate->requested_capability,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->requested_effect,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_terminated(gate->requested_scope,
                                 LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX) &&
           text_field_valid(gate->gate_state,
                            LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX) &&
           capability_gate_error_valid(gate->error) &&
           capability_gate_flags_valid(gate) &&
           capability_gate_effects_clear(gate) &&
           text_field_valid(gate->status,
                            LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX);
}

const char *latticra_seal_effect_decision_error_label(
    latticra_seal_effect_decision_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_EFFECT_DECISION_OK:
        return "ok";
    case LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE:
        return "invalid-gate";
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY:
        return "missing-requested-capability";
    case LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    default:
        return "unknown";
    }
}

static void decision_init(latticra_seal_effect_decision_t *decision) {
    memset(decision, 0, sizeof(*decision));
    copy_literal(decision->decision_profile, sizeof(decision->decision_profile), "latticra-seal-effect-decision/0.1");
    copy_literal(decision->decision_state, sizeof(decision->decision_state), "denied-gate");
    decision->gate_allowed = 0u;
    decision->effect_allowed = 0u;
    decision->effect_performed = 0u;
    decision->host_read_performed = 0u;
    decision->host_write_performed = 0u;
    decision->network_performed = 0u;
    decision->runtime_authority_granted = 0u;
    decision->error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT;
    copy_literal(decision->status, sizeof(decision->status), "invalid-input");
}

latticra_status_t latticra_seal_effect_decision_from_gate(
    const latticra_seal_capability_gate_t *gate,
    latticra_seal_effect_decision_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    decision_init(out);

    if (gate == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (!capability_gate_strings_valid(gate)) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE;
        copy_literal(out->status, sizeof(out->status), "invalid-gate");
        return LATTICRA_STATUS_OK;
    }

    if (gate->error != LATTICRA_SEAL_CAPABILITY_GATE_OK) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE;
        copy_literal(out->status, sizeof(out->status), "invalid-gate");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(gate->artifact_digest_hex,
                          LATTICRA_SEAL_CAPABILITY_GATE_DIGEST_MAX)) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(gate->requested_capability,
                          LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    if (!text_field_valid(gate->requested_effect,
                          LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX)) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT;
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!bounded_string_is(gate->gate_state,
                           LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                           "denied-unverified") ||
        !bounded_string_is(gate->status,
                           LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX,
                           "capability-gate-denied-metadata")) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE;
        copy_literal(out->status, sizeof(out->status), "invalid-gate");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->gate_profile, sizeof(out->gate_profile), gate->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), gate->receipt_profile);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), gate->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), gate->artifact_digest_hex);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), gate->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), gate->requested_effect);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), gate->requested_scope);
    copy_literal(out->gate_state, sizeof(out->gate_state), gate->gate_state);
    copy_literal(out->decision_state, sizeof(out->decision_state), "denied-gate");
    out->gate_allowed = gate->gate_allowed;
    out->effect_allowed = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_EFFECT_DECISION_OK;
    copy_literal(out->status, sizeof(out->status), "effect-decision-denied-metadata");
    return LATTICRA_STATUS_OK;
}

static int effect_decision_flags_valid(
    const latticra_seal_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return boolean_flag_valid(decision->gate_allowed) &&
           boolean_flag_valid(decision->effect_allowed) &&
           boolean_flag_valid(decision->effect_performed) &&
           boolean_flag_valid(decision->host_read_performed) &&
           boolean_flag_valid(decision->host_write_performed) &&
           boolean_flag_valid(decision->network_performed) &&
           boolean_flag_valid(decision->runtime_authority_granted);
}

static int effect_decision_effects_clear(
    const latticra_seal_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return decision->gate_allowed == 0u &&
           decision->effect_allowed == 0u &&
           decision->effect_performed == 0u &&
           decision->host_read_performed == 0u &&
           decision->host_write_performed == 0u &&
           decision->network_performed == 0u &&
           decision->runtime_authority_granted == 0u;
}

static int effect_decision_state_valid(
    const latticra_seal_effect_decision_t *decision) {
    if (decision == NULL || !effect_decision_error_valid(decision->error)) {
        return 0;
    }
    if (decision->error == LATTICRA_SEAL_EFFECT_DECISION_OK) {
        return text_field_valid(decision->artifact_digest_hex,
                                LATTICRA_SEAL_EFFECT_DECISION_DIGEST_MAX) &&
               text_field_valid(decision->requested_capability,
                                LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX) &&
               text_field_valid(decision->requested_effect,
                                LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX) &&
               bounded_string_is(decision->gate_state,
                                 LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX,
                                 "denied-unverified") &&
               bounded_string_is(decision->decision_state,
                                 LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX,
                                 "denied-gate") &&
               bounded_string_is(decision->status,
                                 LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX,
                                 "effect-decision-denied-metadata");
    }

    return text_field_valid(decision->status,
                            LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX);
}

static int effect_decision_record_valid(
    const latticra_seal_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return effect_decision_effects_clear(decision) &&
           effect_decision_flags_valid(decision) &&
           effect_decision_state_valid(decision) &&
           bounded_string_is(decision->decision_profile,
                             LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX,
                             "latticra-seal-effect-decision/0.1") &&
           text_field_terminated(decision->gate_profile,
                                 LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->receipt_profile,
                                 LATTICRA_SEAL_EFFECT_DECISION_PROFILE_MAX) &&
           text_field_terminated(decision->artifact_digest_algorithm,
                                 LATTICRA_SEAL_CAPABILITY_GATE_ALGORITHM_MAX) &&
           text_field_terminated(decision->artifact_digest_hex,
                                 LATTICRA_SEAL_EFFECT_DECISION_DIGEST_MAX) &&
           text_field_terminated(decision->requested_capability,
                                 LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->requested_effect,
                                 LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX) &&
           text_field_terminated(decision->requested_scope,
                                 LATTICRA_SEAL_EFFECT_DECISION_LABEL_MAX) &&
           text_field_valid(decision->gate_state,
                            LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX) &&
           text_field_valid(decision->decision_state,
                            LATTICRA_SEAL_EFFECT_DECISION_STATE_MAX);
}

int latticra_seal_effect_decision_is_denied_metadata(
    const latticra_seal_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return effect_decision_record_valid(decision);
}

latticra_status_t latticra_seal_effect_decision_report(
    const latticra_seal_effect_decision_t *decision,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (decision == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!effect_decision_record_valid(decision)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL EFFECT DECISION\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "gate_state=%s\n"
        "decision_state=%s\n"
        "gate_allowed=%u\n"
        "effect_allowed=%u\n"
        "effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        decision->decision_profile,
        decision->gate_profile,
        decision->receipt_profile,
        decision->artifact_digest_algorithm,
        decision->artifact_digest_hex,
        decision->requested_capability,
        decision->requested_effect,
        decision->requested_scope,
        decision->gate_state,
        decision->decision_state,
        decision->gate_allowed,
        decision->effect_allowed,
        decision->effect_performed,
        decision->host_read_performed,
        decision->host_write_performed,
        decision->network_performed,
        decision->runtime_authority_granted,
        latticra_seal_effect_decision_error_label(decision->error),
        decision->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
