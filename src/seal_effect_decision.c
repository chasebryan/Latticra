#include "latticra/seal_effect_decision.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
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

    if (gate->error != LATTICRA_SEAL_CAPABILITY_GATE_OK) {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE;
        copy_literal(out->status, sizeof(out->status), "invalid-gate");
        return LATTICRA_STATUS_OK;
    }

    if (gate->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (gate->requested_capability[0] == '\0') {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    if (gate->requested_effect[0] == '\0') {
        out->error = LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT;
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
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

int latticra_seal_effect_decision_is_denied_metadata(
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

latticra_status_t latticra_seal_effect_decision_report(
    const latticra_seal_effect_decision_t *decision,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (decision == NULL || buffer == NULL) {
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
