#include "latticra/seal_operator_receipt_report.h"

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

const char *latticra_seal_operator_receipt_report_error_label(
    latticra_seal_operator_receipt_report_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK:
        return "ok";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA:
        return "missing-capability-metadata";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION:
        return "missing-policy-decision";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS:
        return "missing-request-freshness";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST:
        return "missing-signed-request";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN:
        return "missing-runtime-dry-run";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE:
        return "non-report-only-source";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT:
        return "source-would-allow-effect";
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

static void receipt_init(latticra_seal_operator_receipt_report_t *receipt) {
    memset(receipt, 0, sizeof(*receipt));
    copy_literal(receipt->operator_receipt_profile,
                 sizeof(receipt->operator_receipt_profile),
                 "latticra-seal-operator-receipt-report/0.1");
    copy_literal(receipt->receipt_mode, sizeof(receipt->receipt_mode), "report-only");
    copy_literal(receipt->receipt_status, sizeof(receipt->receipt_status), "invalid-source-denied");
    copy_literal(receipt->capability_name, sizeof(receipt->capability_name), "unknown");
    copy_literal(receipt->policy_decision_state, sizeof(receipt->policy_decision_state), "missing");
    copy_literal(receipt->request_freshness_state, sizeof(receipt->request_freshness_state), "missing");
    copy_literal(receipt->signed_request_state, sizeof(receipt->signed_request_state), "missing");
    copy_literal(receipt->runtime_dry_run_state, sizeof(receipt->runtime_dry_run_state), "missing");
    receipt->default_action_deny = 1u;
    receipt->would_allow = 0u;
    receipt->would_deny = 1u;
    receipt->would_require_operator_review = 1u;
    receipt->would_execute_tool = 0u;
    receipt->would_read_host = 0u;
    receipt->would_write_host = 0u;
    receipt->would_use_network = 0u;
    receipt->would_grant_runtime_authority = 0u;
    receipt->unknown_tool_denied = 1u;
    receipt->unsigned_request_denied = 1u;
    receipt->invalid_schema_denied = 1u;
    receipt->stale_request_denied = 1u;
    receipt->replayed_request_denied = 1u;
    receipt->invalid_signature_denied = 1u;
    copy_literal(receipt->blocked_reason, sizeof(receipt->blocked_reason), "invalid-source-denied");
    receipt->receipt_complete = 0u;
    receipt->receipt_invalid = 1u;
    receipt->report_only = 1u;
    receipt->runtime_authority_granted = 0u;
    receipt->effect_performed = 0u;
    receipt->host_read_performed = 0u;
    receipt->host_write_performed = 0u;
    receipt->network_performed = 0u;
    receipt->error = LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT;
}

static void receipt_mark_error(latticra_seal_operator_receipt_report_t *receipt,
                               latticra_seal_operator_receipt_report_error_t error,
                               const char *blocked_reason) {
    receipt->error = error;
    receipt->receipt_complete = 0u;
    receipt->receipt_invalid = 1u;
    copy_literal(receipt->receipt_status, sizeof(receipt->receipt_status), "invalid-source-denied");
    copy_literal(receipt->blocked_reason, sizeof(receipt->blocked_reason), blocked_reason);
}

static int capability_source_report_only(
    const latticra_seal_capability_metadata_result_t *capability) {
    return capability != NULL &&
           capability->error == LATTICRA_SEAL_CAPABILITY_METADATA_OK &&
           capability->capability_lookup_performed == 1u &&
           capability->capability_requires_guarded_allowlist == 1u &&
           capability->capability_requires_policy_decision == 1u &&
           capability->capability_requires_runtime_gate == 1u &&
           capability->capability_requires_runtime_dry_run == 1u &&
           capability->capability_requires_operator_review == 1u &&
           capability->capability_grants_authority == 0u &&
           capability->capability_executes_tool == 0u &&
           capability->capability_reads_host == 0u &&
           capability->capability_writes_host == 0u &&
           capability->capability_uses_network == 0u &&
           capability->default_action_deny == 1u &&
           capability->would_allow == 0u &&
           capability->would_deny == 1u &&
           capability->would_require_operator_review == 1u &&
           capability->report_only == 1u &&
           bounded_string_is(capability->mode,
                             LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX,
                             "report-only");
}

static int policy_source_report_only(const latticra_seal_policy_decision_t *policy) {
    return policy != NULL &&
           policy->error == LATTICRA_SEAL_POLICY_DECISION_OK &&
           policy->policy_decision_supported == 0u &&
           policy->policy_evaluation_supported == 0u &&
           policy->policy_enforcement_supported == 0u &&
           policy->policy_id_present == 0u &&
           policy->policy_version_present == 0u &&
           policy->requested_action_present == 0u &&
           policy->requested_tool_present == 0u &&
           policy->signed_request_present == 0u &&
           policy->signature_valid == 0u &&
           policy->schema_valid == 0u &&
           policy->freshness_valid == 0u &&
           policy->replay_detected == 0u &&
           policy->decision_allowed == 0u &&
           policy->decision_denied == 1u &&
           policy->operator_review_required == 1u &&
           policy->unknown_tool_denied == 1u &&
           policy->unsigned_request_denied == 1u &&
           policy->invalid_schema_denied == 1u &&
           policy->stale_request_denied == 1u &&
           policy->replayed_request_denied == 1u &&
           policy->invalid_signature_denied == 1u &&
           policy->runtime_authority_granted == 0u &&
           policy->host_read_performed == 0u &&
           policy->host_write_performed == 0u &&
           policy->network_performed == 0u &&
           bounded_string_is(policy->decision_state,
                             LATTICRA_SEAL_POLICY_DECISION_STATE_MAX,
                             "report-only") &&
           bounded_string_is(policy->mode,
                             LATTICRA_SEAL_POLICY_DECISION_STATE_MAX,
                             "report-only") &&
           bounded_string_is(policy->decision,
                             LATTICRA_SEAL_POLICY_DECISION_STATE_MAX,
                             "report-only");
}

static int freshness_source_report_only(
    const latticra_seal_request_freshness_t *freshness) {
    return freshness != NULL &&
           freshness->error == LATTICRA_SEAL_REQUEST_FRESHNESS_OK &&
           freshness->request_freshness_supported == 0u &&
           freshness->request_freshness_validation_supported == 0u &&
           freshness->replay_protection_supported == 0u &&
           freshness->request_id_present == 0u &&
           freshness->caller_id_present == 0u &&
           freshness->tool_id_present == 0u &&
           freshness->request_timestamp_present == 0u &&
           freshness->request_expiration_present == 0u &&
           freshness->nonce_present == 0u &&
           freshness->context_hash_present == 0u &&
           freshness->parameter_hash_present == 0u &&
           freshness->freshness_valid == 0u &&
           freshness->replay_detected == 0u &&
           freshness->runtime_authority_granted == 0u &&
           freshness->host_read_performed == 0u &&
           freshness->host_write_performed == 0u &&
           freshness->network_performed == 0u &&
           bounded_string_is(freshness->mode,
                             LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX,
                             "report-only") &&
           bounded_string_is(freshness->decision,
                             LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX,
                             "report-only");
}

static int signed_request_source_report_only(
    const latticra_seal_signed_request_t *signed_request) {
    return signed_request != NULL &&
           signed_request->error == LATTICRA_SEAL_SIGNED_REQUEST_OK &&
           signed_request->signed_request_supported == 0u &&
           signed_request->signature_generation_supported == 0u &&
           signed_request->signature_verification_supported == 0u &&
           signed_request->signature_present == 0u &&
           signed_request->signature_valid == 0u &&
           signed_request->signature_algorithm_declared == 0u &&
           signed_request->signing_key_id_present == 0u &&
           signed_request->signature_hash_present == 0u &&
           signed_request->signed_request_id_present == 0u &&
           signed_request->identity_binding_declared == 0u &&
           signed_request->context_binding_declared == 0u &&
           signed_request->parameter_binding_declared == 0u &&
           signed_request->freshness_binding_declared == 0u &&
           signed_request->policy_binding_declared == 0u &&
           signed_request->trust_store_supported == 0u &&
           signed_request->revocation_lookup_supported == 0u &&
           signed_request->runtime_authority_granted == 0u &&
           signed_request->host_read_performed == 0u &&
           signed_request->host_write_performed == 0u &&
           signed_request->network_performed == 0u &&
           bounded_string_is(signed_request->mode,
                             LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX,
                             "report-only") &&
           bounded_string_is(signed_request->decision,
                             LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX,
                             "report-only");
}

static int dry_run_source_report_only(const latticra_seal_runtime_dry_run_t *dry_run) {
    return dry_run != NULL &&
           dry_run->error == LATTICRA_SEAL_RUNTIME_DRY_RUN_OK &&
           dry_run->dry_run_supported == 1u &&
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
           bounded_string_is(dry_run->mode,
                             LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX,
                             "report-only");
}

static int source_strings_valid(
    const latticra_seal_operator_receipt_report_sources_t *sources) {
    return sources != NULL &&
           text_field_valid(sources->capability_metadata->capability_name,
                            LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX) &&
           text_field_valid(sources->capability_metadata->blocked_reason,
                            LATTICRA_SEAL_CAPABILITY_METADATA_REASON_MAX) &&
           text_field_valid(sources->policy_decision->decision_state,
                            LATTICRA_SEAL_POLICY_DECISION_STATE_MAX) &&
           text_field_valid(sources->request_freshness->decision,
                            LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX) &&
           text_field_valid(sources->signed_request->decision,
                            LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX) &&
           text_field_valid(sources->runtime_dry_run->mode,
                            LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX);
}

static int source_would_allow_effect(
    const latticra_seal_operator_receipt_report_sources_t *sources) {
    return sources->capability_metadata->would_allow != 0u ||
           sources->capability_metadata->capability_grants_authority != 0u ||
           sources->capability_metadata->capability_executes_tool != 0u ||
           sources->capability_metadata->capability_reads_host != 0u ||
           sources->capability_metadata->capability_writes_host != 0u ||
           sources->capability_metadata->capability_uses_network != 0u ||
           sources->policy_decision->decision_allowed != 0u ||
           sources->policy_decision->runtime_authority_granted != 0u ||
           sources->policy_decision->host_read_performed != 0u ||
           sources->policy_decision->host_write_performed != 0u ||
           sources->policy_decision->network_performed != 0u ||
           sources->request_freshness->runtime_authority_granted != 0u ||
           sources->request_freshness->host_read_performed != 0u ||
           sources->request_freshness->host_write_performed != 0u ||
           sources->request_freshness->network_performed != 0u ||
           sources->signed_request->runtime_authority_granted != 0u ||
           sources->signed_request->host_read_performed != 0u ||
           sources->signed_request->host_write_performed != 0u ||
           sources->signed_request->network_performed != 0u ||
           sources->runtime_dry_run->would_allow != 0u ||
           sources->runtime_dry_run->would_execute_tool != 0u ||
           sources->runtime_dry_run->would_read_host != 0u ||
           sources->runtime_dry_run->would_write_host != 0u ||
           sources->runtime_dry_run->would_use_network != 0u ||
           sources->runtime_dry_run->would_grant_runtime_authority != 0u;
}

static int sources_report_only(
    const latticra_seal_operator_receipt_report_sources_t *sources) {
    return capability_source_report_only(sources->capability_metadata) &&
           policy_source_report_only(sources->policy_decision) &&
           freshness_source_report_only(sources->request_freshness) &&
           signed_request_source_report_only(sources->signed_request) &&
           dry_run_source_report_only(sources->runtime_dry_run);
}

latticra_status_t latticra_seal_operator_receipt_report_from_sources(
    const latticra_seal_operator_receipt_report_sources_t *sources,
    latticra_seal_operator_receipt_report_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    receipt_init(out);
    if (sources == NULL) {
        return LATTICRA_STATUS_OK;
    }

    out->source_capability_metadata_present = sources->capability_metadata != NULL ? 1u : 0u;
    out->source_policy_decision_present = sources->policy_decision != NULL ? 1u : 0u;
    out->source_request_freshness_present = sources->request_freshness != NULL ? 1u : 0u;
    out->source_signed_request_present = sources->signed_request != NULL ? 1u : 0u;
    out->source_runtime_dry_run_present = sources->runtime_dry_run != NULL ? 1u : 0u;

    if (sources->capability_metadata == NULL) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA,
                           "missing-capability-metadata");
        return LATTICRA_STATUS_OK;
    }
    if (sources->policy_decision == NULL) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION,
                           "missing-policy-decision");
        return LATTICRA_STATUS_OK;
    }
    if (sources->request_freshness == NULL) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS,
                           "missing-request-freshness");
        return LATTICRA_STATUS_OK;
    }
    if (sources->signed_request == NULL) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST,
                           "missing-signed-request");
        return LATTICRA_STATUS_OK;
    }
    if (sources->runtime_dry_run == NULL) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN,
                           "missing-runtime-dry-run");
        return LATTICRA_STATUS_OK;
    }

    if (source_would_allow_effect(sources)) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT,
                           "source-would-allow-effect-denied");
        return LATTICRA_STATUS_OK;
    }
    if (!source_strings_valid(sources) || !sources_report_only(sources)) {
        receipt_mark_error(out,
                           LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE,
                           "non-report-only-source-denied");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->capability_name,
                 sizeof(out->capability_name),
                 sources->capability_metadata->capability_name);
    copy_literal(out->policy_decision_state,
                 sizeof(out->policy_decision_state),
                 sources->policy_decision->decision_state);
    copy_literal(out->request_freshness_state,
                 sizeof(out->request_freshness_state),
                 sources->request_freshness->decision);
    copy_literal(out->signed_request_state,
                 sizeof(out->signed_request_state),
                 sources->signed_request->decision);
    copy_literal(out->runtime_dry_run_state,
                 sizeof(out->runtime_dry_run_state),
                 sources->runtime_dry_run->mode);

    out->capability_known = sources->capability_metadata->capability_known;
    out->capability_candidate = sources->capability_metadata->capability_candidate;
    out->source_denial_reason_present = 1u;
    out->default_action_deny = 1u;
    out->would_allow = 0u;
    out->would_deny = 1u;
    out->would_require_operator_review = 1u;
    out->would_execute_tool = 0u;
    out->would_read_host = 0u;
    out->would_write_host = 0u;
    out->would_use_network = 0u;
    out->would_grant_runtime_authority = 0u;
    out->unknown_tool_denied = 1u;
    out->unsigned_request_denied = 1u;
    out->invalid_schema_denied = 1u;
    out->stale_request_denied = 1u;
    out->replayed_request_denied = 1u;
    out->invalid_signature_denied = 1u;
    copy_literal(out->blocked_reason,
                 sizeof(out->blocked_reason),
                 sources->capability_metadata->blocked_reason);
    out->receipt_complete = 1u;
    out->receipt_invalid = 0u;
    out->report_only = 1u;
    out->runtime_authority_granted = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    copy_literal(out->receipt_status, sizeof(out->receipt_status), "denied-report-only");
    out->error = LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK;
    return LATTICRA_STATUS_OK;
}

static int receipt_error_valid(latticra_seal_operator_receipt_report_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT:
    case LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_BUFFER_TOO_SMALL:
        return 1;
    default:
        return 0;
    }
}

static int receipt_text_fields_valid(
    const latticra_seal_operator_receipt_report_t *receipt) {
    return receipt != NULL &&
           bounded_string_is(receipt->operator_receipt_profile,
                             LATTICRA_SEAL_OPERATOR_RECEIPT_PROFILE_MAX,
                             "latticra-seal-operator-receipt-report/0.1") &&
           bounded_string_is(receipt->receipt_mode,
                             LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                             "report-only") &&
           (bounded_string_is(receipt->receipt_status,
                              LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                              "denied-report-only") ||
            bounded_string_is(receipt->receipt_status,
                              LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                              "invalid-source-denied")) &&
           text_field_valid(receipt->capability_name,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_CAPABILITY_MAX) &&
           text_field_valid(receipt->policy_decision_state,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX) &&
           text_field_valid(receipt->request_freshness_state,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX) &&
           text_field_valid(receipt->signed_request_state,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX) &&
           text_field_valid(receipt->runtime_dry_run_state,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX) &&
           text_field_valid(receipt->blocked_reason,
                            LATTICRA_SEAL_OPERATOR_RECEIPT_REASON_MAX);
}

static int receipt_no_effect_contract_valid(
    const latticra_seal_operator_receipt_report_t *receipt) {
    return receipt != NULL &&
           receipt->default_action_deny == 1u &&
           receipt->would_allow == 0u &&
           receipt->would_deny == 1u &&
           receipt->would_require_operator_review == 1u &&
           receipt->would_execute_tool == 0u &&
           receipt->would_read_host == 0u &&
           receipt->would_write_host == 0u &&
           receipt->would_use_network == 0u &&
           receipt->would_grant_runtime_authority == 0u &&
           receipt->report_only == 1u &&
           receipt->runtime_authority_granted == 0u &&
           receipt->effect_performed == 0u &&
           receipt->host_read_performed == 0u &&
           receipt->host_write_performed == 0u &&
           receipt->network_performed == 0u;
}

static int receipt_completion_contract_valid(
    const latticra_seal_operator_receipt_report_t *receipt) {
    if (receipt == NULL || !receipt_error_valid(receipt->error)) {
        return 0;
    }
    if (receipt->error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK) {
        return receipt->receipt_complete == 1u &&
               receipt->receipt_invalid == 0u &&
               receipt->source_denial_reason_present == 1u &&
               bounded_string_is(receipt->receipt_status,
                                 LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                                 "denied-report-only");
    }
    return receipt->receipt_complete == 0u &&
           receipt->receipt_invalid == 1u &&
           bounded_string_is(receipt->receipt_status,
                             LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                             "invalid-source-denied");
}

static int receipt_render_contract_valid(
    const latticra_seal_operator_receipt_report_t *receipt) {
    return receipt_text_fields_valid(receipt) &&
           receipt_no_effect_contract_valid(receipt) &&
           receipt_completion_contract_valid(receipt);
}

int latticra_seal_operator_receipt_report_is_report_only(
    const latticra_seal_operator_receipt_report_t *receipt) {
    if (receipt == NULL || !receipt_render_contract_valid(receipt)) {
        return 0;
    }

    return receipt->source_capability_metadata_present == 1u &&
           receipt->source_policy_decision_present == 1u &&
           receipt->source_request_freshness_present == 1u &&
           receipt->source_signed_request_present == 1u &&
           receipt->source_runtime_dry_run_present == 1u &&
           receipt->source_denial_reason_present == 1u &&
           receipt->capability_known == 1u &&
           receipt->capability_candidate == 1u &&
           receipt->default_action_deny == 1u &&
           receipt->would_allow == 0u &&
           receipt->would_deny == 1u &&
           receipt->would_require_operator_review == 1u &&
           receipt->would_execute_tool == 0u &&
           receipt->would_read_host == 0u &&
           receipt->would_write_host == 0u &&
           receipt->would_use_network == 0u &&
           receipt->would_grant_runtime_authority == 0u &&
           receipt->receipt_complete == 1u &&
           receipt->receipt_invalid == 0u &&
           receipt->report_only == 1u &&
           receipt->runtime_authority_granted == 0u &&
           receipt->effect_performed == 0u &&
           receipt->host_read_performed == 0u &&
           receipt->host_write_performed == 0u &&
           receipt->network_performed == 0u &&
           bounded_string_is(receipt->receipt_mode,
                             LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                             "report-only") &&
           bounded_string_is(receipt->receipt_status,
                             LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX,
                             "denied-report-only") &&
           receipt->error == LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK;
}

latticra_status_t latticra_seal_operator_receipt_report_render(
    const latticra_seal_operator_receipt_report_t *receipt,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (receipt == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!receipt_render_contract_valid(receipt)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL OPERATOR RECEIPT REPORT\n"
        "operator_receipt_profile=%s\n"
        "receipt_mode=%s\n"
        "receipt_status=%s\n"
        "source_capability_metadata_present=%u\n"
        "source_policy_decision_present=%u\n"
        "source_request_freshness_present=%u\n"
        "source_signed_request_present=%u\n"
        "source_runtime_dry_run_present=%u\n"
        "source_denial_reason_present=%u\n"
        "capability_name=%s\n"
        "capability_known=%u\n"
        "capability_candidate=%u\n"
        "policy_decision_state=%s\n"
        "request_freshness_state=%s\n"
        "signed_request_state=%s\n"
        "runtime_dry_run_state=%s\n"
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
        "blocked_reason=%s\n"
        "receipt_complete=%u\n"
        "receipt_invalid=%u\n"
        "report_only=%u\n"
        "runtime_authority_granted=%u\n"
        "effect_performed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n",
        receipt->operator_receipt_profile,
        receipt->receipt_mode,
        receipt->receipt_status,
        receipt->source_capability_metadata_present,
        receipt->source_policy_decision_present,
        receipt->source_request_freshness_present,
        receipt->source_signed_request_present,
        receipt->source_runtime_dry_run_present,
        receipt->source_denial_reason_present,
        receipt->capability_name,
        receipt->capability_known,
        receipt->capability_candidate,
        receipt->policy_decision_state,
        receipt->request_freshness_state,
        receipt->signed_request_state,
        receipt->runtime_dry_run_state,
        receipt->default_action_deny,
        receipt->would_allow,
        receipt->would_deny,
        receipt->would_require_operator_review,
        receipt->would_execute_tool,
        receipt->would_read_host,
        receipt->would_write_host,
        receipt->would_use_network,
        receipt->would_grant_runtime_authority,
        receipt->unknown_tool_denied,
        receipt->unsigned_request_denied,
        receipt->invalid_schema_denied,
        receipt->stale_request_denied,
        receipt->replayed_request_denied,
        receipt->invalid_signature_denied,
        receipt->blocked_reason,
        receipt->receipt_complete,
        receipt->receipt_invalid,
        receipt->report_only,
        receipt->runtime_authority_granted,
        receipt->effect_performed,
        receipt->host_read_performed,
        receipt->host_write_performed,
        receipt->network_performed,
        latticra_seal_operator_receipt_report_error_label(receipt->error));

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
