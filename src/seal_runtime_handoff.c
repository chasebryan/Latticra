#include "latticra/seal_runtime_handoff.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_runtime_handoff_error_label(
    latticra_seal_runtime_handoff_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_DECISION:
        return "invalid-decision";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_CAPABILITY:
        return "missing-requested-capability";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    default:
        return "unknown";
    }
}

static void handoff_init(latticra_seal_runtime_handoff_t *handoff) {
    memset(handoff, 0, sizeof(*handoff));
    copy_literal(handoff->handoff_profile, sizeof(handoff->handoff_profile), "latticra-seal-runtime-handoff/0.1");
    copy_literal(handoff->runtime_boundary_state, sizeof(handoff->runtime_boundary_state), "disabled");
    copy_literal(handoff->handoff_state, sizeof(handoff->handoff_state), "denied-decision");
    handoff->effect_allowed = 0u;
    handoff->effect_performed = 0u;
    handoff->handoff_active = 0u;
    handoff->runtime_effect_performed = 0u;
    handoff->host_read_performed = 0u;
    handoff->host_write_performed = 0u;
    handoff->network_performed = 0u;
    handoff->runtime_authority_granted = 0u;
    handoff->error = LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_INPUT;
    copy_literal(handoff->status, sizeof(handoff->status), "invalid-input");
}

latticra_status_t latticra_seal_runtime_handoff_from_decision(
    const latticra_seal_effect_decision_t *decision,
    const char *runtime_request_label,
    latticra_seal_runtime_handoff_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    handoff_init(out);

    if (decision == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (decision->error != LATTICRA_SEAL_EFFECT_DECISION_OK) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_DECISION;
        copy_literal(out->status, sizeof(out->status), "invalid-decision");
        return LATTICRA_STATUS_OK;
    }

    if (decision->requested_capability[0] == '\0') {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    if (decision->requested_effect[0] == '\0') {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_EFFECT;
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->decision_profile, sizeof(out->decision_profile), decision->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), decision->gate_profile);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), decision->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), decision->requested_effect);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), decision->requested_scope);
    copy_literal(out->decision_state, sizeof(out->decision_state), decision->decision_state);
    out->effect_allowed = decision->effect_allowed;
    out->effect_performed = decision->effect_performed;
    copy_literal(out->runtime_boundary_state, sizeof(out->runtime_boundary_state), "disabled");
    copy_literal(
        out->runtime_request_label,
        sizeof(out->runtime_request_label),
        runtime_request_label != NULL && runtime_request_label[0] != '\0' ? runtime_request_label : "no-runtime-request");
    out->handoff_active = 0u;
    out->runtime_effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
    out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_OK;
    copy_literal(out->status, sizeof(out->status), "runtime-handoff-inactive-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_handoff_is_inactive_metadata(
    const latticra_seal_runtime_handoff_t *handoff) {
    if (handoff == NULL) {
        return 0;
    }

    return handoff->effect_allowed == 0u &&
           handoff->effect_performed == 0u &&
           handoff->handoff_active == 0u &&
           handoff->runtime_effect_performed == 0u &&
           handoff->host_read_performed == 0u &&
           handoff->host_write_performed == 0u &&
           handoff->network_performed == 0u &&
           handoff->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_runtime_handoff_report(
    const latticra_seal_runtime_handoff_t *handoff,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (handoff == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME HANDOFF\n"
        "handoff_profile=%s\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "decision_state=%s\n"
        "effect_allowed=%u\n"
        "effect_performed=%u\n"
        "runtime_boundary_state=%s\n"
        "runtime_request_label=%s\n"
        "handoff_active=%u\n"
        "runtime_effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "handoff_state=%s\n"
        "error=%s\n"
        "status=%s\n",
        handoff->handoff_profile,
        handoff->decision_profile,
        handoff->gate_profile,
        handoff->requested_capability,
        handoff->requested_effect,
        handoff->requested_scope,
        handoff->decision_state,
        handoff->effect_allowed,
        handoff->effect_performed,
        handoff->runtime_boundary_state,
        handoff->runtime_request_label,
        handoff->handoff_active,
        handoff->runtime_effect_performed,
        handoff->host_read_performed,
        handoff->host_write_performed,
        handoff->network_performed,
        handoff->runtime_authority_granted,
        handoff->handoff_state,
        latticra_seal_runtime_handoff_error_label(handoff->error),
        handoff->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
