#include "latticra/nucleus_task.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void default_span(latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void default_authority(latticra_nucleus_task_authority_summary_t *authority) {
    if (authority == 0) return;
    authority->status = LATTICRA_STATUS_OK;
    authority->status_label[0] = '\0';
    authority->validator_label[0] = '\0';
    authority->requested_effect_label[0] = '\0';
    authority->denial_reason[0] = '\0';
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->network_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static void default_record(latticra_nucleus_task_record_t *record) {
    if (record == 0) return;
    record->task_id[0] = '\0';
    record->request_kind = LATTICRA_NUCLEUS_TASK_UNKNOWN;
    record->requested_effect = LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN;
    record->allowed_effect = LATTICRA_NUCLEUS_TASK_EFFECT_NONE;
    record->policy = LATTICRA_NUCLEUS_TASK_POLICY_DENY;
    record->denial = LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT;
    record->gate_state = LATTICRA_NUCLEUS_TASK_GATE_DISABLED;
    record->operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    record->rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    record->report_classification = LATTICRA_NUCLEUS_TASK_REPORT_DENIED;
    record->task_domain = LATTICRA_NUCLEUS_TASK_DOMAIN_UNKNOWN;
    record->authorization_state = LATTICRA_NUCLEUS_TASK_AUTH_DENIED;
    record->prerequisites_satisfied = 0;
    record->no_effect_chain_ok = 1;
    record->report_alignment[0] = '\0';
    record->no_effect_policy[0] = '\0';
    record->representation_gate[0] = '\0';
    record->execution_status[0] = '\0';
    record->effect_status[0] = '\0';
    record->runtime_status[0] = '\0';
    default_authority(&record->authority);
    record->source_identity[0] = '\0';
    default_span(&record->source_span);
    record->executed = 0;
    record->mutation_allowed = 0;
    record->server_interaction_allowed = 0;
    record->network_allowed = 0;
    record->recovery_allowed = 0;
    record->hardware_allowed = 0;
    record->evidence_level = 0u;
}

static void default_result(latticra_nucleus_task_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    default_record(&result->record);
    result->record_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->network_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static int copy_checked(char *destination, size_t destination_len, const char *source) {
    size_t source_len;
    if (destination == 0 || destination_len == 0u) return 0;
    destination[0] = '\0';
    if (source == 0) return 1;
    source_len = strlen(source);
    if (source_len >= destination_len) return 0;
    (void)memcpy(destination, source, source_len + 1u);
    return 1;
}

static int copy_n(char *destination, size_t destination_len, const char *source, size_t source_len) {
    if (destination == 0 || destination_len == 0u) return 0;
    destination[0] = '\0';
    if (source == 0 || source_len == 0u) return 1;
    if (source_len >= destination_len) return 0;
    (void)memcpy(destination, source, source_len);
    destination[source_len] = '\0';
    return 1;
}

static int no_effect_flags_ok(int no_effect,
                              int execution_allowed,
                              int mutation_allowed,
                              int server_allowed,
                              int network_allowed,
                              int recovery_allowed,
                              int hardware_allowed) {
    return no_effect == 1 && execution_allowed == 0 && mutation_allowed == 0 &&
           server_allowed == 0 && network_allowed == 0 &&
           recovery_allowed == 0 && hardware_allowed == 0;
}

static int authority_ok(const latticra_nucleus_task_authority_summary_t *authority) {
    if (authority == 0) return 0;
    return authority->status == LATTICRA_STATUS_OK &&
           no_effect_flags_ok(authority->no_effect,
                              authority->execution_allowed,
                              authority->mutation_allowed,
                              authority->server_allowed,
                              authority->network_allowed,
                              authority->recovery_allowed,
                              authority->hardware_allowed);
}

static latticra_nucleus_task_effect_t effect_from_preview(latticra_effect_t effect) {
    switch (effect) {
    case LATTICRA_EFFECT_NONE: return LATTICRA_NUCLEUS_TASK_EFFECT_NONE;
    case LATTICRA_EFFECT_READ: return LATTICRA_NUCLEUS_TASK_EFFECT_READ;
    case LATTICRA_EFFECT_LOCAL_MUTATION: return LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION;
    case LATTICRA_EFFECT_HOST_MUTATION: return LATTICRA_NUCLEUS_TASK_EFFECT_HOST_MUTATION;
    case LATTICRA_EFFECT_NETWORK: return LATTICRA_NUCLEUS_TASK_EFFECT_NETWORK;
    case LATTICRA_EFFECT_HARDWARE: return LATTICRA_NUCLEUS_TASK_EFFECT_HARDWARE;
    case LATTICRA_EFFECT_BOOT: return LATTICRA_NUCLEUS_TASK_EFFECT_BOOT;
    case LATTICRA_EFFECT_RECOVERY: return LATTICRA_NUCLEUS_TASK_EFFECT_RECOVERY;
    case LATTICRA_EFFECT_EXTERNAL: return LATTICRA_NUCLEUS_TASK_EFFECT_EXTERNAL;
    default: return LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN;
    }
}

const char *latticra_nucleus_task_request_kind_label(latticra_nucleus_task_request_kind_t kind) {
    switch (kind) {
    case LATTICRA_NUCLEUS_TASK_STATE_REPORT: return "state-report";
    case LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW: return "transition-preview";
    case LATTICRA_NUCLEUS_TASK_RENDER_REPORT: return "render-report";
    case LATTICRA_NUCLEUS_TASK_LAT_VALIDATE: return "lat-validate";
    case LATTICRA_NUCLEUS_TASK_LIR_VALIDATE: return "lir-validate";
    case LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK: return "authority-check";
    case LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION: return "server-interaction";
    case LATTICRA_NUCLEUS_TASK_SELF_UPDATE: return "self-update";
    case LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION: return "recovery-action";
    case LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION: return "hardware-action";
    case LATTICRA_NUCLEUS_TASK_BOOT_ACTION: return "boot-action";
    case LATTICRA_NUCLEUS_TASK_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_nucleus_task_effect_label(latticra_nucleus_task_effect_t effect) {
    switch (effect) {
    case LATTICRA_NUCLEUS_TASK_EFFECT_NONE: return "none";
    case LATTICRA_NUCLEUS_TASK_EFFECT_READ: return "read";
    case LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION: return "local_mutation";
    case LATTICRA_NUCLEUS_TASK_EFFECT_HOST_MUTATION: return "host_mutation";
    case LATTICRA_NUCLEUS_TASK_EFFECT_NETWORK: return "network";
    case LATTICRA_NUCLEUS_TASK_EFFECT_HARDWARE: return "hardware";
    case LATTICRA_NUCLEUS_TASK_EFFECT_BOOT: return "boot";
    case LATTICRA_NUCLEUS_TASK_EFFECT_RECOVERY: return "recovery";
    case LATTICRA_NUCLEUS_TASK_EFFECT_EXTERNAL: return "external";
    case LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_nucleus_task_policy_label(latticra_nucleus_task_policy_t policy) {
    switch (policy) {
    case LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW: return "allow-preview";
    case LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT: return "allow-report";
    case LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION: return "allow-validation";
    case LATTICRA_NUCLEUS_TASK_POLICY_DENY: return "deny";
    case LATTICRA_NUCLEUS_TASK_POLICY_BLOCKED: return "blocked";
    case LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE: return "requires-future-gate";
    case LATTICRA_NUCLEUS_TASK_POLICY_UNSUPPORTED: return "unsupported";
    case LATTICRA_NUCLEUS_TASK_POLICY_INTERNAL_ERROR:
    default: return "internal-error";
    }
}

const char *latticra_nucleus_task_denial_label(latticra_nucleus_task_denial_t denial) {
    switch (denial) {
    case LATTICRA_NUCLEUS_TASK_DENIAL_OK: return "ok";
    case LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT: return "null-argument";
    case LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST: return "unknown-request";
    case LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT: return "unknown-effect";
    case LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_REQUEST: return "unsupported-request";
    case LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT: return "unsupported-effect";
    case LATTICRA_NUCLEUS_TASK_DENIAL_PARSER_FAILED: return "parser-failed";
    case LATTICRA_NUCLEUS_TASK_DENIAL_SEMANTIC_FAILED: return "semantic-failed";
    case LATTICRA_NUCLEUS_TASK_DENIAL_LIR_FAILED: return "lir-failed";
    case LATTICRA_NUCLEUS_TASK_DENIAL_RENDER_FAILED: return "render-failed";
    case LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED: return "authority-failed";
    case LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED: return "effect-blocked";
    case LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE: return "effect-requires-future-gate";
    case LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS: return "non-no-effect-flags";
    case LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED: return "operator-confirmation-not-supported";
    case LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT: return "implementation-not-present";
    case LATTICRA_NUCLEUS_TASK_DENIAL_INTERNAL_ERROR:
    default: return "internal-error";
    }
}

const char *latticra_nucleus_task_gate_state_label(latticra_nucleus_task_gate_state_t gate_state) {
    switch (gate_state) {
    case LATTICRA_NUCLEUS_TASK_GATE_DISABLED: return "disabled";
    case LATTICRA_NUCLEUS_TASK_GATE_BLOCKED: return "blocked";
    case LATTICRA_NUCLEUS_TASK_GATE_PLANNED: return "planned";
    case LATTICRA_NUCLEUS_TASK_GATE_AVAILABLE: return "available";
    case LATTICRA_NUCLEUS_TASK_GATE_ARMED: return "armed";
    case LATTICRA_NUCLEUS_TASK_GATE_EXECUTED: return "executed";
    case LATTICRA_NUCLEUS_TASK_GATE_FAILED:
    default: return "failed";
    }
}

const char *latticra_nucleus_task_operator_confirmation_label(latticra_nucleus_task_operator_confirmation_t confirmation) {
    switch (confirmation) {
    case LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE: return "not-applicable";
    case LATTICRA_NUCLEUS_TASK_OPERATOR_REQUIRED: return "required";
    case LATTICRA_NUCLEUS_TASK_OPERATOR_PRESENT: return "present";
    case LATTICRA_NUCLEUS_TASK_OPERATOR_REJECTED: return "rejected";
    case LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_SUPPORTED:
    default: return "not-supported";
    }
}

const char *latticra_nucleus_task_rollback_state_label(latticra_nucleus_task_rollback_state_t rollback_state) {
    switch (rollback_state) {
    case LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE: return "not-applicable";
    case LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_AVAILABLE: return "not-available";
    case LATTICRA_NUCLEUS_TASK_ROLLBACK_REQUIRED: return "required";
    case LATTICRA_NUCLEUS_TASK_ROLLBACK_READY: return "ready";
    case LATTICRA_NUCLEUS_TASK_ROLLBACK_BLOCKED:
    default: return "blocked";
    }
}

const char *latticra_nucleus_task_report_classification_label(latticra_nucleus_task_report_classification_t classification) {
    switch (classification) {
    case LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED: return "accepted";
    case LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED: return "future-gated";
    case LATTICRA_NUCLEUS_TASK_REPORT_DENIED: return "denied";
    case LATTICRA_NUCLEUS_TASK_REPORT_INVALID:
    default: return "invalid";
    }
}

const char *latticra_nucleus_task_domain_label(latticra_nucleus_task_domain_t domain) {
    switch (domain) {
    case LATTICRA_NUCLEUS_TASK_DOMAIN_STATE: return "state";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_TRANSITION: return "transition";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_RENDER: return "render";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_LAT: return "lat";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_LIR: return "lir";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_AUTHORITY: return "authority";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_SERVER: return "server";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_UPDATE: return "update";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_RECOVERY: return "recovery";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_HARDWARE: return "hardware";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_BOOT: return "boot";
    case LATTICRA_NUCLEUS_TASK_DOMAIN_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_nucleus_task_authorization_state_label(latticra_nucleus_task_authorization_state_t state) {
    switch (state) {
    case LATTICRA_NUCLEUS_TASK_AUTH_NOT_REQUESTED: return "not-requested";
    case LATTICRA_NUCLEUS_TASK_AUTH_CHECKED: return "checked";
    case LATTICRA_NUCLEUS_TASK_AUTH_DENIED: return "denied";
    case LATTICRA_NUCLEUS_TASK_AUTH_RESERVED_FOR_FUTURE: return "reserved-for-future";
    case LATTICRA_NUCLEUS_TASK_AUTH_UNAVAILABLE:
    default: return "unavailable";
    }
}

static int task_kind_is_future_gated(latticra_nucleus_task_request_kind_t kind) {
    return kind == LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION ||
           kind == LATTICRA_NUCLEUS_TASK_SELF_UPDATE ||
           kind == LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION ||
           kind == LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION ||
           kind == LATTICRA_NUCLEUS_TASK_BOOT_ACTION;
}

static latticra_nucleus_task_domain_t task_domain_for_kind(latticra_nucleus_task_request_kind_t kind) {
    switch (kind) {
    case LATTICRA_NUCLEUS_TASK_STATE_REPORT: return LATTICRA_NUCLEUS_TASK_DOMAIN_STATE;
    case LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW: return LATTICRA_NUCLEUS_TASK_DOMAIN_TRANSITION;
    case LATTICRA_NUCLEUS_TASK_RENDER_REPORT: return LATTICRA_NUCLEUS_TASK_DOMAIN_RENDER;
    case LATTICRA_NUCLEUS_TASK_LAT_VALIDATE: return LATTICRA_NUCLEUS_TASK_DOMAIN_LAT;
    case LATTICRA_NUCLEUS_TASK_LIR_VALIDATE: return LATTICRA_NUCLEUS_TASK_DOMAIN_LIR;
    case LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK: return LATTICRA_NUCLEUS_TASK_DOMAIN_AUTHORITY;
    case LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION: return LATTICRA_NUCLEUS_TASK_DOMAIN_SERVER;
    case LATTICRA_NUCLEUS_TASK_SELF_UPDATE: return LATTICRA_NUCLEUS_TASK_DOMAIN_UPDATE;
    case LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION: return LATTICRA_NUCLEUS_TASK_DOMAIN_RECOVERY;
    case LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION: return LATTICRA_NUCLEUS_TASK_DOMAIN_HARDWARE;
    case LATTICRA_NUCLEUS_TASK_BOOT_ACTION: return LATTICRA_NUCLEUS_TASK_DOMAIN_BOOT;
    case LATTICRA_NUCLEUS_TASK_UNKNOWN:
    default: return LATTICRA_NUCLEUS_TASK_DOMAIN_UNKNOWN;
    }
}

static int result_no_effect_chain_ok(const latticra_nucleus_task_result_t *result) {
    if (result == 0) return 0;
    return no_effect_flags_ok(result->no_effect,
                              result->execution_allowed,
                              result->mutation_allowed,
                              result->server_allowed,
                              result->network_allowed,
                              result->recovery_allowed,
                              result->hardware_allowed) &&
           result->record.executed == 0 &&
           result->record.mutation_allowed == 0 &&
           result->record.server_interaction_allowed == 0 &&
           result->record.network_allowed == 0 &&
           result->record.recovery_allowed == 0 &&
           result->record.hardware_allowed == 0;
}

static void apply_no_effect_report_alignment(latticra_nucleus_task_result_t *result) {
    if (result == 0) return;
    (void)copy_checked(result->record.report_alignment,
                       sizeof(result->record.report_alignment),
                       "no-effect-report-alignment");
    (void)copy_checked(result->record.no_effect_policy,
                       sizeof(result->record.no_effect_policy),
                       result->record.no_effect_chain_ok == 1 ? "preserved" : "violated");
    (void)copy_checked(result->record.representation_gate,
                       sizeof(result->record.representation_gate),
                       "language-representation-reviewed");
    (void)copy_checked(result->record.execution_status,
                       sizeof(result->record.execution_status),
                       "not-executed");
    (void)copy_checked(result->record.effect_status,
                       sizeof(result->record.effect_status),
                       "report-only");
    (void)copy_checked(result->record.runtime_status,
                       sizeof(result->record.runtime_status),
                       "not-entered");
}

static void finalize_task_report_refinement(latticra_nucleus_task_result_t *result) {
    if (result == 0) return;

    result->record.task_domain = task_domain_for_kind(result->record.request_kind);
    result->record.no_effect_chain_ok = result_no_effect_chain_ok(result);
    result->record.prerequisites_satisfied = result->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_OK ? 1 : 0;
    apply_no_effect_report_alignment(result);

    if (result->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT ||
        result->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST ||
        result->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT) {
        result->record.report_classification = LATTICRA_NUCLEUS_TASK_REPORT_INVALID;
        result->record.authorization_state = LATTICRA_NUCLEUS_TASK_AUTH_UNAVAILABLE;
        result->record.evidence_level = 0u;
        return;
    }

    if (result->record.policy == LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE ||
        task_kind_is_future_gated(result->record.request_kind)) {
        result->record.report_classification = LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED;
        result->record.authorization_state = LATTICRA_NUCLEUS_TASK_AUTH_RESERVED_FOR_FUTURE;
        result->record.evidence_level = 1u;
        return;
    }

    if (result->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_OK) {
        result->record.report_classification = LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED;
        result->record.authorization_state = result->record.request_kind == LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK ?
            LATTICRA_NUCLEUS_TASK_AUTH_CHECKED : LATTICRA_NUCLEUS_TASK_AUTH_NOT_REQUESTED;
        result->record.evidence_level = 2u;
        return;
    }

    result->record.report_classification = LATTICRA_NUCLEUS_TASK_REPORT_DENIED;
    result->record.authorization_state = LATTICRA_NUCLEUS_TASK_AUTH_DENIED;
    result->record.evidence_level = 1u;
}

static void copy_authority(latticra_nucleus_task_authority_summary_t *destination,
                           const latticra_nucleus_task_authority_summary_t *source) {
    if (destination == 0) return;
    default_authority(destination);
    if (source == 0) return;
    destination->status = source->status;
    (void)copy_checked(destination->status_label, sizeof(destination->status_label), source->status_label);
    (void)copy_checked(destination->validator_label, sizeof(destination->validator_label), source->validator_label);
    (void)copy_checked(destination->requested_effect_label, sizeof(destination->requested_effect_label), source->requested_effect_label);
    (void)copy_checked(destination->denial_reason, sizeof(destination->denial_reason), source->denial_reason);
    destination->no_effect = source->no_effect;
    destination->execution_allowed = source->execution_allowed;
    destination->mutation_allowed = source->mutation_allowed;
    destination->server_allowed = source->server_allowed;
    destination->network_allowed = source->network_allowed;
    destination->recovery_allowed = source->recovery_allowed;
    destination->hardware_allowed = source->hardware_allowed;
}

static void fill_record_defaults(const latticra_nucleus_task_request_t *request,
                                 latticra_nucleus_task_result_t *result) {
    if (result == 0) return;
    default_result(result);
    result->record_count = 1u;
    if (request == 0) return;
    (void)copy_checked(result->record.task_id, sizeof(result->record.task_id), request->task_id);
    result->record.request_kind = request->request_kind;
    result->record.requested_effect = request->requested_effect;
    result->record.operator_confirmation = request->operator_confirmation;
    result->record.rollback_state = request->rollback_state;
    copy_authority(&result->record.authority, request->authority);
    (void)copy_n(result->record.source_identity,
                 sizeof(result->record.source_identity),
                 request->source_identity,
                 request->source_identity_len);
    result->record.source_span = request->source_span;
    result->record.executed = 0;
    result->record.mutation_allowed = 0;
    result->record.server_interaction_allowed = 0;
    result->record.network_allowed = 0;
    result->record.recovery_allowed = 0;
    result->record.hardware_allowed = 0;
    result->record.evidence_level = 1u;
}

static void set_denial(latticra_nucleus_task_result_t *result,
                       latticra_nucleus_task_policy_t policy,
                       latticra_nucleus_task_denial_t denial,
                       latticra_nucleus_task_gate_state_t gate_state) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->record.policy = policy;
    result->record.denial = denial;
    result->record.gate_state = gate_state;
    result->record.allowed_effect = LATTICRA_NUCLEUS_TASK_EFFECT_NONE;
    result->record.executed = 0;
    result->record.mutation_allowed = 0;
    result->record.server_interaction_allowed = 0;
    result->record.network_allowed = 0;
    result->record.recovery_allowed = 0;
    result->record.hardware_allowed = 0;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->network_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
    finalize_task_report_refinement(result);
}

static void set_allowed(latticra_nucleus_task_result_t *result,
                        latticra_nucleus_task_policy_t policy,
                        latticra_nucleus_task_effect_t allowed_effect) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->record.policy = policy;
    result->record.denial = LATTICRA_NUCLEUS_TASK_DENIAL_OK;
    result->record.gate_state = LATTICRA_NUCLEUS_TASK_GATE_DISABLED;
    result->record.allowed_effect = allowed_effect;
    result->record.executed = 0;
    result->record.mutation_allowed = 0;
    result->record.server_interaction_allowed = 0;
    result->record.network_allowed = 0;
    result->record.recovery_allowed = 0;
    result->record.hardware_allowed = 0;
    finalize_task_report_refinement(result);
}

static int effect_is_preview_eligible(latticra_nucleus_task_effect_t effect) {
    return effect == LATTICRA_NUCLEUS_TASK_EFFECT_NONE || effect == LATTICRA_NUCLEUS_TASK_EFFECT_READ;
}

static int preview_allows(const latticra_nucleus_preview_t *preview,
                          latticra_request_kind_t expected_kind,
                          latticra_nucleus_task_effect_t requested_effect) {
    if (preview == 0) return 0;
    return preview->request_kind == expected_kind &&
           effect_from_preview(preview->requested_effect) == requested_effect &&
           preview->policy_result == LATTICRA_POLICY_ALLOW_PREVIEW &&
           preview->executed == 0 &&
           preview->mutation_allowed == 0 &&
           preview->server_interaction_allowed == 0 &&
           preview->network_allowed == 0 &&
           preview->recovery_allowed == 0 &&
           preview->hardware_allowed == 0;
}

latticra_status_t latticra_nucleus_task_classify(const latticra_nucleus_task_request_t *request,
                                                 latticra_nucleus_task_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    fill_record_defaults(request, result);

    if (request == 0) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (request->source_identity_len >= LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_INTERNAL_ERROR,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (request->authority == 0) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (!authority_ok(request->authority)) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   request->authority->status == LATTICRA_STATUS_OK ? LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS : LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (request->operator_confirmation != LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (request->request_kind == LATTICRA_NUCLEUS_TASK_UNKNOWN) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (request->requested_effect == LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    if (!effect_is_preview_eligible(request->requested_effect)) {
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }

    switch (request->request_kind) {
    case LATTICRA_NUCLEUS_TASK_STATE_REPORT:
        if (!preview_allows(request->preview, LATTICRA_REQUEST_STATE_REPORT, request->requested_effect)) {
            set_denial(result,
                       LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                       LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED,
                       LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        } else {
            set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, request->requested_effect);
        }
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW:
        if (!preview_allows(request->preview, LATTICRA_REQUEST_TRANSITION_PREVIEW, request->requested_effect)) {
            set_denial(result,
                       LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                       LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED,
                       LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        } else {
            set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW, request->requested_effect);
        }
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_RENDER_REPORT:
        if (request->render == 0 || request->render->status != LATTICRA_STATUS_OK || request->render->error != LATTICRA_L_UI_RENDER_OK) {
            set_denial(result,
                       LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                       LATTICRA_NUCLEUS_TASK_DENIAL_RENDER_FAILED,
                       LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        } else {
            set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, request->requested_effect);
        }
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_LAT_VALIDATE:
        if (request->lat == 0 || request->lat->status != LATTICRA_STATUS_OK || request->lat->error != LATTICRA_LAT_PARSE_OK) {
            set_denial(result,
                       LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                       LATTICRA_NUCLEUS_TASK_DENIAL_PARSER_FAILED,
                       LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        } else {
            set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION, request->requested_effect);
        }
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_LIR_VALIDATE:
        if (request->lir == 0 || request->lir->status != LATTICRA_STATUS_OK || request->lir->error != LATTICRA_LIR_OK) {
            set_denial(result,
                       LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                       LATTICRA_NUCLEUS_TASK_DENIAL_LIR_FAILED,
                       LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        } else {
            set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION, request->requested_effect);
        }
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK:
        set_allowed(result, LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION, request->requested_effect);
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION:
    case LATTICRA_NUCLEUS_TASK_SELF_UPDATE:
    case LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION:
    case LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION:
    case LATTICRA_NUCLEUS_TASK_BOOT_ACTION:
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE,
                   LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE,
                   LATTICRA_NUCLEUS_TASK_GATE_PLANNED);
        return LATTICRA_STATUS_OK;
    case LATTICRA_NUCLEUS_TASK_UNKNOWN:
    default:
        set_denial(result,
                   LATTICRA_NUCLEUS_TASK_POLICY_DENY,
                   LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST,
                   LATTICRA_NUCLEUS_TASK_GATE_BLOCKED);
        return LATTICRA_STATUS_OK;
    }
}

static int appendf(char *buffer, size_t buffer_len, size_t *used, const char *format, ...) {
    int written;
    va_list args;
    if (buffer == 0 || used == 0 || format == 0 || *used >= buffer_len) return 0;
    va_start(args, format);
    written = vsnprintf(buffer + *used, buffer_len - *used, format, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) return 0;
    *used += (size_t)written;
    return 1;
}

static void clear_buffer(char *buffer, size_t buffer_len) {
    if (buffer != 0 && buffer_len > 0u) buffer[0] = '\0';
}

latticra_status_t latticra_nucleus_task_report(const latticra_nucleus_task_result_t *result,
                                               char *buffer,
                                               size_t buffer_len) {
    size_t used = 0u;
    const latticra_nucleus_task_record_t *record;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    clear_buffer(buffer, buffer_len);
    record = &result->record;

    if (!appendf(buffer, buffer_len, &used, "LATTICRA NUCLEUS TASK REPORT\n") ||
        !appendf(buffer, buffer_len, &used, "status=%d\n", (int)result->status) ||
        !appendf(buffer, buffer_len, &used, "task_id=%s\n", record->task_id) ||
        !appendf(buffer, buffer_len, &used, "request=%s\n", latticra_nucleus_task_request_kind_label(record->request_kind)) ||
        !appendf(buffer, buffer_len, &used, "requested_effect=%s\n", latticra_nucleus_task_effect_label(record->requested_effect)) ||
        !appendf(buffer, buffer_len, &used, "allowed_effect=%s\n", latticra_nucleus_task_effect_label(record->allowed_effect)) ||
        !appendf(buffer, buffer_len, &used, "policy=%s\n", latticra_nucleus_task_policy_label(record->policy)) ||
        !appendf(buffer, buffer_len, &used, "reason=%s\n", latticra_nucleus_task_denial_label(record->denial)) ||
        !appendf(buffer, buffer_len, &used, "report_classification=%s\n", latticra_nucleus_task_report_classification_label(record->report_classification)) ||
        !appendf(buffer, buffer_len, &used, "task_domain=%s\n", latticra_nucleus_task_domain_label(record->task_domain)) ||
        !appendf(buffer, buffer_len, &used, "authorization_state=%s\n", latticra_nucleus_task_authorization_state_label(record->authorization_state)) ||
        !appendf(buffer, buffer_len, &used, "prerequisites_satisfied=%d\n", record->prerequisites_satisfied) ||
        !appendf(buffer, buffer_len, &used, "no_effect_chain_ok=%d\n", record->no_effect_chain_ok) ||
        !appendf(buffer, buffer_len, &used, "report_alignment=%s\n", record->report_alignment) ||
        !appendf(buffer, buffer_len, &used, "no_effect_policy=%s\n", record->no_effect_policy) ||
        !appendf(buffer, buffer_len, &used, "representation_gate=%s\n", record->representation_gate) ||
        !appendf(buffer, buffer_len, &used, "execution_status=%s\n", record->execution_status) ||
        !appendf(buffer, buffer_len, &used, "effect_status=%s\n", record->effect_status) ||
        !appendf(buffer, buffer_len, &used, "runtime_status=%s\n", record->runtime_status) ||
        !appendf(buffer, buffer_len, &used, "authority_status=%s\n", record->authority.status_label) ||
        !appendf(buffer, buffer_len, &used, "authority_validator=%s\n", record->authority.validator_label) ||
        !appendf(buffer, buffer_len, &used, "authority_reason=%s\n", record->authority.denial_reason) ||
        !appendf(buffer, buffer_len, &used, "gate_state=%s\n", latticra_nucleus_task_gate_state_label(record->gate_state)) ||
        !appendf(buffer, buffer_len, &used, "operator_confirmation=%s\n", latticra_nucleus_task_operator_confirmation_label(record->operator_confirmation)) ||
        !appendf(buffer, buffer_len, &used, "executed=%d\n", record->executed) ||
        !appendf(buffer, buffer_len, &used, "mutation_allowed=%d\n", record->mutation_allowed) ||
        !appendf(buffer, buffer_len, &used, "server_interaction_allowed=%d\n", record->server_interaction_allowed) ||
        !appendf(buffer, buffer_len, &used, "network_allowed=%d\n", record->network_allowed) ||
        !appendf(buffer, buffer_len, &used, "recovery_allowed=%d\n", record->recovery_allowed) ||
        !appendf(buffer, buffer_len, &used, "hardware_allowed=%d\n", record->hardware_allowed) ||
        !appendf(buffer, buffer_len, &used, "rollback_state=%s\n", latticra_nucleus_task_rollback_state_label(record->rollback_state)) ||
        !appendf(buffer, buffer_len, &used, "evidence_level=%u\n", record->evidence_level) ||
        !appendf(buffer, buffer_len, &used, "source_identity=%s\n", record->source_identity) ||
        !appendf(buffer, buffer_len, &used, "span_start_offset=%lu\n", (unsigned long)record->source_span.start_offset) ||
        !appendf(buffer, buffer_len, &used, "span_end_offset=%lu\n", (unsigned long)record->source_span.end_offset)) {
        clear_buffer(buffer, buffer_len);
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
