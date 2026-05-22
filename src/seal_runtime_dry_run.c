#include "latticra/seal_runtime_dry_run.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_runtime_dry_run_error_label(
    latticra_seal_runtime_dry_run_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_DRY_RUN_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION:
        return "invalid-policy-decision";
    case LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE:
        return "invalid-runtime-gate";
    default:
        return "unknown";
    }
}

static void dry_run_init(latticra_seal_runtime_dry_run_t *dry_run) {
    memset(dry_run, 0, sizeof(*dry_run));
    copy_literal(dry_run->runtime_dry_run_profile,
                 sizeof(dry_run->runtime_dry_run_profile),
                 "latticra-seal-runtime-dry-run/0.1");
    copy_literal(dry_run->request_class, sizeof(dry_run->request_class), "core-blocked-request");
    copy_literal(dry_run->policy_decision_state, sizeof(dry_run->policy_decision_state), "invalid-input");
    copy_literal(dry_run->runtime_gate_state, sizeof(dry_run->runtime_gate_state), "invalid-input");
    copy_literal(dry_run->blocked_reason, sizeof(dry_run->blocked_reason), "invalid-input");
    copy_literal(dry_run->status, sizeof(dry_run->status), "invalid-input");
    dry_run->dry_run_supported = 1u;
    dry_run->dry_run_performed = 0u;
    dry_run->input_policy_decision_present = 0u;
    dry_run->input_runtime_gate_present = 0u;
    dry_run->policy_decision_report_only = 0u;
    dry_run->runtime_gate_report_only = 0u;
    dry_run->default_action_deny = 1u;
    dry_run->would_allow = 0u;
    dry_run->would_deny = 1u;
    dry_run->would_require_operator_review = 1u;
    dry_run->would_execute_tool = 0u;
    dry_run->would_read_host = 0u;
    dry_run->would_write_host = 0u;
    dry_run->would_use_network = 0u;
    dry_run->would_grant_runtime_authority = 0u;
    dry_run->unknown_tool_denied = 1u;
    dry_run->unsigned_request_denied = 1u;
    dry_run->invalid_schema_denied = 1u;
    dry_run->stale_request_denied = 1u;
    dry_run->replayed_request_denied = 1u;
    dry_run->invalid_signature_denied = 1u;
    dry_run->report_only = 1u;
    copy_literal(dry_run->mode, sizeof(dry_run->mode), "report-only");
    dry_run->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT;
}

latticra_status_t latticra_seal_runtime_dry_run_from_policy_and_gate(
    const latticra_seal_policy_decision_t *policy_decision,
    const latticra_seal_runtime_gate_t *runtime_gate,
    latticra_seal_runtime_dry_run_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    dry_run_init(out);

    if (policy_decision == NULL || runtime_gate == NULL) {
        return LATTICRA_STATUS_OK;
    }

    out->input_policy_decision_present = 1u;
    out->input_runtime_gate_present = 1u;

    if (policy_decision->error != LATTICRA_SEAL_POLICY_DECISION_OK ||
        latticra_seal_policy_decision_is_report_only(policy_decision) != 1) {
        out->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-policy-decision");
        copy_literal(out->status, sizeof(out->status), "invalid-policy-decision");
        return LATTICRA_STATUS_OK;
    }

    if (runtime_gate->error != LATTICRA_SEAL_RUNTIME_GATE_OK ||
        latticra_seal_runtime_gate_is_report_only(runtime_gate) != 1) {
        out->policy_decision_report_only = 1u;
        copy_literal(out->policy_decision_state, sizeof(out->policy_decision_state), "report-only");
        out->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-runtime-gate");
        copy_literal(out->status, sizeof(out->status), "invalid-runtime-gate");
        return LATTICRA_STATUS_OK;
    }

    out->policy_decision_report_only = 1u;
    out->runtime_gate_report_only = 1u;
    out->dry_run_performed = 1u;
    copy_literal(out->policy_decision_state, sizeof(out->policy_decision_state), "report-only");
    copy_literal(out->runtime_gate_state, sizeof(out->runtime_gate_state), "report-only");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "default-deny-dry-run");
    copy_literal(out->status, sizeof(out->status), "runtime-dry-run-metadata");
    out->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_OK;
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_dry_run_is_report_only(
    const latticra_seal_runtime_dry_run_t *dry_run) {
    if (dry_run == NULL) {
        return 0;
    }

    return dry_run->dry_run_supported == 1u &&
           dry_run->dry_run_performed == 1u &&
           dry_run->input_policy_decision_present == 1u &&
           dry_run->input_runtime_gate_present == 1u &&
           dry_run->policy_decision_report_only == 1u &&
           dry_run->runtime_gate_report_only == 1u &&
           dry_run->default_action_deny == 1u &&
           dry_run->would_allow == 0u &&
           dry_run->would_deny == 1u &&
           dry_run->would_require_operator_review == 1u &&
           dry_run->would_execute_tool == 0u &&
           dry_run->would_read_host == 0u &&
           dry_run->would_write_host == 0u &&
           dry_run->would_use_network == 0u &&
           dry_run->would_grant_runtime_authority == 0u &&
           dry_run->unknown_tool_denied == 1u &&
           dry_run->unsigned_request_denied == 1u &&
           dry_run->invalid_schema_denied == 1u &&
           dry_run->stale_request_denied == 1u &&
           dry_run->replayed_request_denied == 1u &&
           dry_run->invalid_signature_denied == 1u &&
           dry_run->report_only == 1u &&
           strcmp(dry_run->mode, "report-only") == 0;
}

latticra_status_t latticra_seal_runtime_dry_run_report(
    const latticra_seal_runtime_dry_run_t *dry_run,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (dry_run == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME DRY RUN\n"
        "runtime_dry_run_profile=%s\n"
        "request_class=%s\n"
        "policy_decision_state=%s\n"
        "runtime_gate_state=%s\n"
        "blocked_reason=%s\n"
        "dry_run_supported=%u\n"
        "dry_run_performed=%u\n"
        "input_policy_decision_present=%u\n"
        "input_runtime_gate_present=%u\n"
        "policy_decision_report_only=%u\n"
        "runtime_gate_report_only=%u\n"
        "default_action_deny=%u\n"
        "would_allow=%u\n"
        "would_deny=%u\n"
        "would_require_operator_review=%u\n"
        "would_execute_tool=%u\n"
        "would_read_host=%u\n"
        "would_write_host=%u\n"
        "would_use_network=%u\n"
        "would_grant_runtime_authority=%u\n"
        "unknown_tool_denied=%u\n"
        "unsigned_request_denied=%u\n"
        "invalid_schema_denied=%u\n"
        "stale_request_denied=%u\n"
        "replayed_request_denied=%u\n"
        "invalid_signature_denied=%u\n"
        "report_only=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        dry_run->runtime_dry_run_profile,
        dry_run->request_class,
        dry_run->policy_decision_state,
        dry_run->runtime_gate_state,
        dry_run->blocked_reason,
        dry_run->dry_run_supported,
        dry_run->dry_run_performed,
        dry_run->input_policy_decision_present,
        dry_run->input_runtime_gate_present,
        dry_run->policy_decision_report_only,
        dry_run->runtime_gate_report_only,
        dry_run->default_action_deny,
        dry_run->would_allow,
        dry_run->would_deny,
        dry_run->would_require_operator_review,
        dry_run->would_execute_tool,
        dry_run->would_read_host,
        dry_run->would_write_host,
        dry_run->would_use_network,
        dry_run->would_grant_runtime_authority,
        dry_run->unknown_tool_denied,
        dry_run->unsigned_request_denied,
        dry_run->invalid_schema_denied,
        dry_run->stale_request_denied,
        dry_run->replayed_request_denied,
        dry_run->invalid_signature_denied,
        dry_run->report_only,
        dry_run->mode,
        latticra_seal_runtime_dry_run_error_label(dry_run->error),
        dry_run->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
