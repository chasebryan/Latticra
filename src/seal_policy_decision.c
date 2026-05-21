#include "latticra/seal_policy_decision.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_policy_decision_error_label(
    latticra_seal_policy_decision_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_POLICY_DECISION_OK:
        return "ok";
    case LATTICRA_SEAL_POLICY_DECISION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_POLICY_DECISION_INVALID_SIGNED_REQUEST:
        return "invalid-signed-request";
    default:
        return "unknown";
    }
}

static void policy_decision_init(latticra_seal_policy_decision_t *policy_decision) {
    memset(policy_decision, 0, sizeof(*policy_decision));
    copy_literal(policy_decision->policy_decision_profile, sizeof(policy_decision->policy_decision_profile), "latticra-seal-policy-decision/0.1");
    copy_literal(policy_decision->policy_id, sizeof(policy_decision->policy_id), "unset");
    copy_literal(policy_decision->policy_version, sizeof(policy_decision->policy_version), "unset");
    copy_literal(policy_decision->requested_action, sizeof(policy_decision->requested_action), "unset");
    copy_literal(policy_decision->requested_tool, sizeof(policy_decision->requested_tool), "unset");
    policy_decision->policy_decision_supported = 0u;
    policy_decision->policy_evaluation_supported = 0u;
    policy_decision->policy_enforcement_supported = 0u;
    policy_decision->policy_id_present = 0u;
    policy_decision->policy_version_present = 0u;
    policy_decision->requested_action_present = 0u;
    policy_decision->requested_tool_present = 0u;
    policy_decision->signed_request_present = 0u;
    policy_decision->signature_valid = 0u;
    policy_decision->schema_valid = 0u;
    policy_decision->freshness_valid = 0u;
    policy_decision->replay_detected = 0u;
    copy_literal(policy_decision->default_decision, sizeof(policy_decision->default_decision), "deny");
    copy_literal(policy_decision->decision_state, sizeof(policy_decision->decision_state), "report-only");
    policy_decision->decision_allowed = 0u;
    policy_decision->decision_denied = 1u;
    policy_decision->operator_review_required = 1u;
    policy_decision->unknown_tool_denied = 1u;
    policy_decision->unsigned_request_denied = 1u;
    policy_decision->invalid_schema_denied = 1u;
    policy_decision->stale_request_denied = 1u;
    policy_decision->replayed_request_denied = 1u;
    policy_decision->invalid_signature_denied = 1u;
    policy_decision->runtime_authority_granted = 0u;
    policy_decision->host_read_performed = 0u;
    policy_decision->host_write_performed = 0u;
    policy_decision->network_performed = 0u;
    copy_literal(policy_decision->mode, sizeof(policy_decision->mode), "report-only");
    copy_literal(policy_decision->decision, sizeof(policy_decision->decision), "report-only");
    copy_literal(policy_decision->reason, sizeof(policy_decision->reason), "policy-decision-metadata-only");
    policy_decision->error = LATTICRA_SEAL_POLICY_DECISION_INVALID_INPUT;
    copy_literal(policy_decision->status, sizeof(policy_decision->status), "invalid-input");
}

latticra_status_t latticra_seal_policy_decision_from_signed_request(
    const latticra_seal_signed_request_t *signed_request,
    latticra_seal_policy_decision_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    policy_decision_init(out);

    if (signed_request == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (signed_request->error != LATTICRA_SEAL_SIGNED_REQUEST_OK ||
        latticra_seal_signed_request_is_report_only(signed_request) != 1) {
        out->error = LATTICRA_SEAL_POLICY_DECISION_INVALID_SIGNED_REQUEST;
        copy_literal(out->reason, sizeof(out->reason), "invalid-signed-request");
        copy_literal(out->status, sizeof(out->status), "invalid-signed-request");
        return LATTICRA_STATUS_OK;
    }

    out->runtime_authority_granted = signed_request->runtime_authority_granted;
    out->host_read_performed = signed_request->host_read_performed;
    out->host_write_performed = signed_request->host_write_performed;
    out->network_performed = signed_request->network_performed;
    out->error = LATTICRA_SEAL_POLICY_DECISION_OK;
    copy_literal(out->status, sizeof(out->status), "policy-decision-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_policy_decision_is_report_only(
    const latticra_seal_policy_decision_t *policy_decision) {
    if (policy_decision == NULL) {
        return 0;
    }

    return policy_decision->policy_decision_supported == 0u &&
           policy_decision->policy_evaluation_supported == 0u &&
           policy_decision->policy_enforcement_supported == 0u &&
           policy_decision->policy_id_present == 0u &&
           policy_decision->policy_version_present == 0u &&
           policy_decision->requested_action_present == 0u &&
           policy_decision->requested_tool_present == 0u &&
           policy_decision->signed_request_present == 0u &&
           policy_decision->signature_valid == 0u &&
           policy_decision->schema_valid == 0u &&
           policy_decision->freshness_valid == 0u &&
           policy_decision->replay_detected == 0u &&
           policy_decision->decision_allowed == 0u &&
           policy_decision->decision_denied == 1u &&
           policy_decision->operator_review_required == 1u &&
           policy_decision->unknown_tool_denied == 1u &&
           policy_decision->unsigned_request_denied == 1u &&
           policy_decision->invalid_schema_denied == 1u &&
           policy_decision->stale_request_denied == 1u &&
           policy_decision->replayed_request_denied == 1u &&
           policy_decision->invalid_signature_denied == 1u &&
           policy_decision->runtime_authority_granted == 0u &&
           policy_decision->host_read_performed == 0u &&
           policy_decision->host_write_performed == 0u &&
           policy_decision->network_performed == 0u;
}

latticra_status_t latticra_seal_policy_decision_report(
    const latticra_seal_policy_decision_t *policy_decision,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (policy_decision == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL POLICY DECISION\n"
        "policy_decision_profile=%s\n"
        "policy_id=%s\n"
        "policy_version=%s\n"
        "requested_action=%s\n"
        "requested_tool=%s\n"
        "policy_decision_supported=%u\n"
        "policy_evaluation_supported=%u\n"
        "policy_enforcement_supported=%u\n"
        "policy_id_present=%u\n"
        "policy_version_present=%u\n"
        "requested_action_present=%u\n"
        "requested_tool_present=%u\n"
        "signed_request_present=%u\n"
        "signature_valid=%u\n"
        "schema_valid=%u\n"
        "freshness_valid=%u\n"
        "replay_detected=%u\n"
        "default_decision=%s\n"
        "decision_state=%s\n"
        "decision_allowed=%u\n"
        "decision_denied=%u\n"
        "operator_review_required=%u\n"
        "unknown_tool_denied=%u\n"
        "unsigned_request_denied=%u\n"
        "invalid_schema_denied=%u\n"
        "stale_request_denied=%u\n"
        "replayed_request_denied=%u\n"
        "invalid_signature_denied=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        policy_decision->policy_decision_profile,
        policy_decision->policy_id,
        policy_decision->policy_version,
        policy_decision->requested_action,
        policy_decision->requested_tool,
        policy_decision->policy_decision_supported,
        policy_decision->policy_evaluation_supported,
        policy_decision->policy_enforcement_supported,
        policy_decision->policy_id_present,
        policy_decision->policy_version_present,
        policy_decision->requested_action_present,
        policy_decision->requested_tool_present,
        policy_decision->signed_request_present,
        policy_decision->signature_valid,
        policy_decision->schema_valid,
        policy_decision->freshness_valid,
        policy_decision->replay_detected,
        policy_decision->default_decision,
        policy_decision->decision_state,
        policy_decision->decision_allowed,
        policy_decision->decision_denied,
        policy_decision->operator_review_required,
        policy_decision->unknown_tool_denied,
        policy_decision->unsigned_request_denied,
        policy_decision->invalid_schema_denied,
        policy_decision->stale_request_denied,
        policy_decision->replayed_request_denied,
        policy_decision->invalid_signature_denied,
        policy_decision->runtime_authority_granted,
        policy_decision->host_read_performed,
        policy_decision->host_write_performed,
        policy_decision->network_performed,
        policy_decision->mode,
        policy_decision->decision,
        policy_decision->reason,
        latticra_seal_policy_decision_error_label(policy_decision->error),
        policy_decision->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
