#include "latticra/seal_runtime_gate.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_runtime_gate_error_label(
    latticra_seal_runtime_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_GATE_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_GATE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_GATE_INVALID_POLICY_DECISION:
        return "invalid-policy-decision";
    default:
        return "unknown";
    }
}

static void gate_init(latticra_seal_runtime_gate_t *gate) {
    memset(gate, 0, sizeof(*gate));
    copy_literal(gate->runtime_enforcement_gate_profile, sizeof(gate->runtime_enforcement_gate_profile), "latticra-seal-runtime-enforcement-gate/0.1");
    copy_literal(gate->gate_id, sizeof(gate->gate_id), "unset");
    copy_literal(gate->gate_version, sizeof(gate->gate_version), "unset");
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "report-only");
    gate->runtime_enforcement_gate_supported = 0u;
    gate->runtime_enforcement_supported = 0u;
    gate->runtime_enforcement_active = 0u;
    gate->policy_decision_input_supported = 0u;
    gate->policy_decision_consumed = 0u;
    gate->gate_id_present = 0u;
    gate->gate_version_present = 0u;
    gate->runtime_handoff_eligible = 0u;
    gate->runtime_handoff_performed = 0u;
    gate->allow_enforcement_supported = 0u;
    gate->deny_enforcement_supported = 0u;
    gate->allow_enforcement_performed = 0u;
    gate->deny_enforcement_performed = 0u;
    gate->effect_performed = 0u;
    gate->default_blocked = 1u;
    gate->operator_review_required = 1u;
    gate->unknown_tool_blocked = 1u;
    gate->unsigned_request_blocked = 1u;
    gate->invalid_schema_blocked = 1u;
    gate->stale_request_blocked = 1u;
    gate->replayed_request_blocked = 1u;
    gate->invalid_signature_blocked = 1u;
    gate->runtime_authority_granted = 0u;
    gate->host_read_performed = 0u;
    gate->host_write_performed = 0u;
    gate->network_performed = 0u;
    copy_literal(gate->mode, sizeof(gate->mode), "report-only");
    copy_literal(gate->decision, sizeof(gate->decision), "report-only");
    copy_literal(gate->reason, sizeof(gate->reason), "runtime-gate-metadata-only");
    gate->error = LATTICRA_SEAL_RUNTIME_GATE_INVALID_INPUT;
    copy_literal(gate->status, sizeof(gate->status), "invalid-input");
}

latticra_status_t latticra_seal_runtime_gate_from_policy_decision(
    const latticra_seal_policy_decision_t *policy_decision,
    latticra_seal_runtime_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);

    if (policy_decision == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (policy_decision->error != LATTICRA_SEAL_POLICY_DECISION_OK ||
        latticra_seal_policy_decision_is_report_only(policy_decision) != 1) {
        out->error = LATTICRA_SEAL_RUNTIME_GATE_INVALID_POLICY_DECISION;
        copy_literal(out->reason, sizeof(out->reason), "invalid-policy-decision");
        copy_literal(out->status, sizeof(out->status), "invalid-policy-decision");
        return LATTICRA_STATUS_OK;
    }

    out->runtime_authority_granted = policy_decision->runtime_authority_granted;
    out->host_read_performed = policy_decision->host_read_performed;
    out->host_write_performed = policy_decision->host_write_performed;
    out->network_performed = policy_decision->network_performed;
    out->error = LATTICRA_SEAL_RUNTIME_GATE_OK;
    copy_literal(out->status, sizeof(out->status), "runtime-gate-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_gate_is_report_only(
    const latticra_seal_runtime_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->runtime_enforcement_gate_supported == 0u &&
           gate->runtime_enforcement_supported == 0u &&
           gate->runtime_enforcement_active == 0u &&
           gate->policy_decision_input_supported == 0u &&
           gate->policy_decision_consumed == 0u &&
           gate->gate_id_present == 0u &&
           gate->gate_version_present == 0u &&
           gate->runtime_handoff_eligible == 0u &&
           gate->runtime_handoff_performed == 0u &&
           gate->allow_enforcement_supported == 0u &&
           gate->deny_enforcement_supported == 0u &&
           gate->allow_enforcement_performed == 0u &&
           gate->deny_enforcement_performed == 0u &&
           gate->effect_performed == 0u &&
           gate->default_blocked == 1u &&
           gate->operator_review_required == 1u &&
           gate->unknown_tool_blocked == 1u &&
           gate->unsigned_request_blocked == 1u &&
           gate->invalid_schema_blocked == 1u &&
           gate->stale_request_blocked == 1u &&
           gate->replayed_request_blocked == 1u &&
           gate->invalid_signature_blocked == 1u &&
           gate->runtime_authority_granted == 0u &&
           gate->host_read_performed == 0u &&
           gate->host_write_performed == 0u &&
           gate->network_performed == 0u;
}

latticra_status_t latticra_seal_runtime_gate_report(
    const latticra_seal_runtime_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME GATE\n"
        "runtime_enforcement_gate_profile=%s\n"
        "gate_id=%s\n"
        "gate_version=%s\n"
        "gate_state=%s\n"
        "runtime_enforcement_gate_supported=%u\n"
        "runtime_enforcement_supported=%u\n"
        "runtime_enforcement_active=%u\n"
        "policy_decision_input_supported=%u\n"
        "policy_decision_consumed=%u\n"
        "gate_id_present=%u\n"
        "gate_version_present=%u\n"
        "runtime_handoff_eligible=%u\n"
        "runtime_handoff_performed=%u\n"
        "allow_enforcement_supported=%u\n"
        "deny_enforcement_supported=%u\n"
        "allow_enforcement_performed=%u\n"
        "deny_enforcement_performed=%u\n"
        "effect_performed=%u\n"
        "default_blocked=%u\n"
        "operator_review_required=%u\n"
        "unknown_tool_blocked=%u\n"
        "unsigned_request_blocked=%u\n"
        "invalid_schema_blocked=%u\n"
        "stale_request_blocked=%u\n"
        "replayed_request_blocked=%u\n"
        "invalid_signature_blocked=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->runtime_enforcement_gate_profile,
        gate->gate_id,
        gate->gate_version,
        gate->gate_state,
        gate->runtime_enforcement_gate_supported,
        gate->runtime_enforcement_supported,
        gate->runtime_enforcement_active,
        gate->policy_decision_input_supported,
        gate->policy_decision_consumed,
        gate->gate_id_present,
        gate->gate_version_present,
        gate->runtime_handoff_eligible,
        gate->runtime_handoff_performed,
        gate->allow_enforcement_supported,
        gate->deny_enforcement_supported,
        gate->allow_enforcement_performed,
        gate->deny_enforcement_performed,
        gate->effect_performed,
        gate->default_blocked,
        gate->operator_review_required,
        gate->unknown_tool_blocked,
        gate->unsigned_request_blocked,
        gate->invalid_schema_blocked,
        gate->stale_request_blocked,
        gate->replayed_request_blocked,
        gate->invalid_signature_blocked,
        gate->runtime_authority_granted,
        gate->host_read_performed,
        gate->host_write_performed,
        gate->network_performed,
        gate->mode,
        gate->decision,
        gate->reason,
        latticra_seal_runtime_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
