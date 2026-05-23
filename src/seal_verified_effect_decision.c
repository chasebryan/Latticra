#include "latticra/seal_verified_effect_decision.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_effect(const char *effect) {
    return strcmp(effect, "report-only") == 0 ||
           strcmp(effect, "evaluate-only") == 0;
}

const char *latticra_seal_verified_effect_decision_error_label(
    latticra_seal_verified_effect_decision_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK:
        return "ok";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_GATE:
        return "invalid-gate";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_GATE:
        return "denied-gate";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_UNKNOWN_EFFECT:
        return "denied-unknown-effect";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void decision_init(latticra_seal_verified_effect_decision_t *decision) {
    memset(decision, 0, sizeof(*decision));
    copy_literal(decision->decision_profile, sizeof(decision->decision_profile), "latticra-seal-verified-effect-decision/0.1");
    copy_literal(decision->decision_state, sizeof(decision->decision_state), "denied-gate");
    decision->verified = 0u;
    decision->authority_usable = 0u;
    decision->receipt_capability_gate_allowed = 0u;
    decision->gate_allowed = 0u;
    decision->effect_allowed = 0u;
    decision->effect_performed = 0u;
    decision->runtime_authority_granted = 0u;
    decision->host_read_performed = 0u;
    decision->host_write_performed = 0u;
    decision->network_performed = 0u;
    decision->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_INPUT;
    copy_literal(decision->status, sizeof(decision->status), "invalid-input");
}

static void copy_gate_metadata(
    const latticra_seal_verified_capability_gate_t *gate,
    latticra_seal_verified_effect_decision_t *out) {
    copy_literal(out->gate_profile, sizeof(out->gate_profile), gate->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), gate->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), gate->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), gate->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), gate->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), gate->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), gate->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), gate->requested_effect);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), gate->requested_scope);
    copy_literal(out->gate_state, sizeof(out->gate_state), gate->gate_state);
    out->verified = gate->verified;
    out->authority_usable = gate->authority_usable;
    out->receipt_capability_gate_allowed = gate->receipt_capability_gate_allowed;
    out->gate_allowed = gate->gate_allowed;
    out->effect_performed = gate->effect_performed;
    out->runtime_authority_granted = gate->runtime_authority_granted;
    out->host_read_performed = gate->host_read_performed;
    out->host_write_performed = gate->host_write_performed;
    out->network_performed = gate->network_performed;
}

latticra_status_t latticra_seal_verified_effect_decision_from_gate(
    const latticra_seal_verified_capability_gate_t *gate,
    latticra_seal_verified_effect_decision_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    decision_init(out);

    if (gate == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_gate_metadata(gate, out);

    if (gate->error != LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_GATE;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-gate");
        copy_literal(out->status, sizeof(out->status), "invalid-gate");
        return LATTICRA_STATUS_OK;
    }

    if (gate->gate_allowed != 1u ||
        strcmp(gate->gate_state, "allowed-metadata-only") != 0) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_GATE;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-gate");
        copy_literal(out->status, sizeof(out->status), "denied-gate");
        return LATTICRA_STATUS_OK;
    }

    if (gate->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (gate->effect_performed != 0u ||
        gate->host_read_performed != 0u ||
        gate->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (gate->network_performed != 0u) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_NETWORK_EFFECT;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (gate->requested_effect[0] == '\0') {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_MISSING_REQUESTED_EFFECT;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_effect(gate->requested_effect)) {
        out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_UNKNOWN_EFFECT;
        copy_literal(out->decision_state, sizeof(out->decision_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-effect");
        return LATTICRA_STATUS_OK;
    }

    out->effect_allowed = 1u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK;

    if (strcmp(gate->requested_effect, "report-only") == 0) {
        copy_literal(out->decision_state, sizeof(out->decision_state), "allowed-report-only");
    } else {
        copy_literal(out->decision_state, sizeof(out->decision_state), "allowed-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "verified-effect-decision-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_verified_effect_decision_is_metadata_only(
    const latticra_seal_verified_effect_decision_t *decision) {
    if (decision == NULL) {
        return 0;
    }

    return decision->effect_performed == 0u &&
           decision->runtime_authority_granted == 0u &&
           decision->host_read_performed == 0u &&
           decision->host_write_performed == 0u &&
           decision->network_performed == 0u;
}

latticra_status_t latticra_seal_verified_effect_decision_report(
    const latticra_seal_verified_effect_decision_t *decision,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (decision == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL VERIFIED EFFECT DECISION\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "decision_state=%s\n"
        "effect_allowed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        decision->decision_profile,
        decision->gate_profile,
        decision->receipt_profile,
        decision->verify_profile,
        decision->message_digest_algorithm,
        decision->message_digest_hex,
        decision->public_key_identity_label,
        decision->requested_capability,
        decision->requested_effect,
        decision->requested_scope,
        decision->verified,
        decision->authority_usable,
        decision->receipt_capability_gate_allowed,
        decision->gate_allowed,
        decision->gate_state,
        decision->decision_state,
        decision->effect_allowed,
        decision->effect_performed,
        decision->runtime_authority_granted,
        decision->host_read_performed,
        decision->host_write_performed,
        decision->network_performed,
        latticra_seal_verified_effect_decision_error_label(decision->error),
        decision->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
