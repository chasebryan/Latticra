#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

const char *latticra_runtime_boundary_request_kind_label(latticra_runtime_boundary_request_kind_t kind) {
    switch (kind) {
    case LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY: return "parse-only";
    case LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY: return "validate-only";
    case LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY: return "classify-only";
    case LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT: return "render-report";
    case LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT: return "nucleus-task-report";
    case LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE: return "lat-validate";
    case LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE: return "lir-validate";
    case LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK: return "authority-check";
    case LATTICRA_RUNTIME_BOUNDARY_UNKNOWN: return "unknown";
    default: return "future-gated";
    }
}

const char *latticra_runtime_boundary_effect_label(latticra_runtime_boundary_effect_t effect) {
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE) return "none";
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ) return "read";
    if (effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN) return "unknown";
    return "blocked-effect";
}

const char *latticra_runtime_boundary_mode_label(latticra_runtime_boundary_mode_t mode) {
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY) return "report-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY) return "validation-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_PREVIEW_ONLY) return "preview-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY) return "classification-only";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_DENY_ALL) return "deny-all";
    if (mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE) return "future-gated";
    return "disabled";
}

const char *latticra_runtime_boundary_policy_label(latticra_runtime_boundary_policy_t policy) {
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT) return "allow-report";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION) return "allow-validation";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION) return "allow-classification";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW) return "allow-preview";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE) return "future-gated";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_BLOCKED) return "blocked";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_UNSUPPORTED) return "unsupported";
    if (policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_INTERNAL_ERROR) return "internal-error";
    return "deny";
}

const char *latticra_runtime_boundary_denial_label(latticra_runtime_boundary_denial_t denial) {
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK) return "ok";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT) return "null-argument";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST) return "unknown-request";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT) return "unknown-effect";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED) return "authority-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED) return "task-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED) return "render-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED) return "parser-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED) return "lir-failed";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS) return "non-no-effect-flags";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED) return "runtime-disabled";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED) return "operator-confirmation-not-supported";
    if (denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE) return "future-gate-required";
    return "blocked";
}

const char *latticra_runtime_boundary_gate_state_label(latticra_runtime_boundary_gate_state_t gate_state) {
    if (gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED) return "planned";
    if (gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED) return "blocked";
    return "disabled";
}

const char *latticra_runtime_boundary_operator_confirmation_label(latticra_runtime_boundary_operator_confirmation_t confirmation) {
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT) return "present";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REQUIRED) return "required";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REJECTED) return "rejected";
    if (confirmation == LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_SUPPORTED) return "not-supported";
    return "not-applicable";
}

static void seed_result(latticra_runtime_boundary_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    result->record_count = 1u;
    result->no_effect = 1;
    result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY;
    result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED;
    result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED;
    result->record.task_policy = LATTICRA_NUCLEUS_TASK_POLICY_DENY;
    result->record.task_reason = LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT;
}

static void copy_runtime_id(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    size_t n;
    n = strlen(request->runtime_id);
    if (n >= sizeof(result->record.runtime_id)) n = sizeof(result->record.runtime_id) - 1u;
    memcpy(result->record.runtime_id, request->runtime_id, n);
    result->record.runtime_id[n] = '\0';
}

static void copy_source_identity(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    size_t n;
    if (request->source_identity == 0 || request->source_identity_len == 0u) return;
    n = request->source_identity_len;
    if (n >= sizeof(result->record.source_identity)) n = sizeof(result->record.source_identity) - 1u;
    memcpy(result->record.source_identity, request->source_identity, n);
    result->record.source_identity[n] = '\0';
}

static void copy_task_flags(const latticra_nucleus_task_result_t *task, latticra_runtime_boundary_result_t *result) {
    if (task == 0) return;
    result->record.task_executed = task->record.executed;
    result->record.task_mutation_allowed = task->record.mutation_allowed;
    result->record.task_server_interaction_allowed = task->record.server_interaction_allowed;
    result->record.task_recovery_allowed = task->record.recovery_allowed;
    result->record.task_hardware_allowed = task->record.hardware_allowed;
}

static void copy_prerequisites(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (request->render != 0) {
        result->record.render_status = request->render->status;
        result->record.render_error = request->render->error;
    }
    if (request->lat != 0) {
        result->record.lat_status = request->lat->status;
        result->record.lat_error = request->lat->error;
    }
    if (request->lir != 0) {
        result->record.lir_status = request->lir->status;
        result->record.lir_error = request->lir->error;
    }
}

static int authority_flags_ok(const latticra_runtime_boundary_authority_summary_t *authority) {
    return authority != 0 && authority->status == LATTICRA_STATUS_OK && authority->no_effect == 1 && authority->execution_allowed == 0 && authority->mutation_allowed == 0 && authority->server_allowed == 0 && authority->recovery_allowed == 0 && authority->hardware_allowed == 0;
}

static int task_result_ok(const latticra_nucleus_task_result_t *task) {
    return task != 0 && task->status == LATTICRA_STATUS_OK && task->record_count > 0u && task->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_OK && task->record.executed == 0 && task->record.mutation_allowed == 0 && task->record.server_interaction_allowed == 0 && task->record.recovery_allowed == 0 && task->record.hardware_allowed == 0;
}

static int render_ok(const latticra_l_ui_render_result_t *render) {
    return render != 0 && render->status == LATTICRA_STATUS_OK && render->error == LATTICRA_L_UI_RENDER_OK;
}

static int lat_ok(const latticra_lat_parse_result_t *lat) {
    return lat != 0 && lat->status == LATTICRA_STATUS_OK && lat->error == LATTICRA_LAT_PARSE_OK;
}

static int lir_ok(const latticra_lir_module_t *lir) {
    return lir != 0 && lir->status == LATTICRA_STATUS_OK && lir->error == LATTICRA_LIR_OK;
}

static void allow_matching_no_effect_mode(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result->record.policy != LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY || result->record.denial != LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED) return;
    if (request->requested_effect != LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE && request->requested_effect != LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ) return;

    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT) && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
        return;
    }

    if ((request->request_kind == LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE || request->request_kind == LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK) && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
        return;
    }

    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY && request->mode == LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
        result->record.allowed_effect = request->requested_effect;
    }
}

latticra_status_t latticra_runtime_boundary_classify(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);
    if (request == 0) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    copy_runtime_id(request, result);
    result->record.request_kind = request->request_kind;
    result->record.requested_effect = request->requested_effect;
    result->record.mode = request->mode;
    result->record.operator_confirmation = request->operator_confirmation;
    result->record.source_span = request->source_span;
    copy_source_identity(request, result);
    copy_prerequisites(request, result);
    if (request->authority != 0) result->record.authority = *request->authority;
    if (request->task != 0) {
        result->record.task_policy = request->task->record.policy;
        result->record.task_reason = request->task->record.denial;
        copy_task_flags(request->task, result);
    }
    if (request->authority == 0) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (!authority_flags_ok(request->authority)) {
        result->record.denial = request->authority->status == LATTICRA_STATUS_OK ? LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS : LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT && !render_ok(request->render)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE && !lat_ok(request->lat)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE && !lir_ok(request->lir)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT && !task_result_ok(request->task)) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED;
        return LATTICRA_STATUS_OK;
    }
    if (request->operator_confirmation != LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED;
    }
    if (request->requested_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT;
    }
    if (request->request_kind == LATTICRA_RUNTIME_BOUNDARY_UNKNOWN) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST;
    }
    if ((int)request->request_kind >= 8 && (int)request->request_kind <= 20) {
        result->record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE;
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE;
        result->record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED;
    }
    allow_matching_no_effect_mode(request, result);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_runtime_boundary_report(const latticra_runtime_boundary_result_t *result, char *buffer, size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(buffer, buffer_len,
        "LATTICRA RUNTIME BOUNDARY REPORT\nruntime_id=%s\nrecord_count=%lu\nrequest=%s\nrequested_effect=%s\nallowed_effect=%s\nmode=%s\npolicy=%s\nreason=%s\ngate=%s\noperator_confirmation=%s\nauthority_status=%d\nauthority_status_label=%s\nauthority_validator=%s\nauthority_requested_effect=%s\nauthority_reason=%s\nauthority_no_effect=%d\nauthority_execution_allowed=%d\nauthority_mutation_allowed=%d\nauthority_server_allowed=%d\nauthority_recovery_allowed=%d\nauthority_hardware_allowed=%d\ntask_policy=%s\ntask_reason=%s\ntask_executed=%d\ntask_mutation_allowed=%d\ntask_server_interaction_allowed=%d\ntask_recovery_allowed=%d\ntask_hardware_allowed=%d\nrender_status=%d\nrender_error=%d\nlat_status=%d\nlat_error=%d\nlir_status=%d\nlir_error=%d\nno_effect=%d\nexecution_allowed=%d\nmutation_allowed=%d\nfile_io_allowed=%d\nnetwork_allowed=%d\nserver_allowed=%d\nrecovery_allowed=%d\nrollback_allowed=%d\nhardware_allowed=%d\nboot_allowed=%d\nsource_identity=%s\nspan_start_offset=%lu\nspan_end_offset=%lu\nspan_start_line=%lu\nspan_start_column=%lu\nspan_end_line=%lu\nspan_end_column=%lu\n",
        result->record.runtime_id,
        (unsigned long)result->record_count,
        latticra_runtime_boundary_request_kind_label(result->record.request_kind),
        latticra_runtime_boundary_effect_label(result->record.requested_effect),
        latticra_runtime_boundary_effect_label(result->record.allowed_effect),
        latticra_runtime_boundary_mode_label(result->record.mode),
        latticra_runtime_boundary_policy_label(result->record.policy),
        latticra_runtime_boundary_denial_label(result->record.denial),
        latticra_runtime_boundary_gate_state_label(result->record.gate_state),
        latticra_runtime_boundary_operator_confirmation_label(result->record.operator_confirmation),
        (int)result->record.authority.status,
        result->record.authority.status_label,
        result->record.authority.validator_label,
        result->record.authority.requested_effect_label,
        result->record.authority.denial_reason,
        result->record.authority.no_effect,
        result->record.authority.execution_allowed,
        result->record.authority.mutation_allowed,
        result->record.authority.server_allowed,
        result->record.authority.recovery_allowed,
        result->record.authority.hardware_allowed,
        latticra_nucleus_task_policy_label(result->record.task_policy),
        latticra_nucleus_task_denial_label(result->record.task_reason),
        result->record.task_executed,
        result->record.task_mutation_allowed,
        result->record.task_server_interaction_allowed,
        result->record.task_recovery_allowed,
        result->record.task_hardware_allowed,
        (int)result->record.render_status,
        (int)result->record.render_error,
        (int)result->record.lat_status,
        (int)result->record.lat_error,
        (int)result->record.lir_status,
        (int)result->record.lir_error,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->server_allowed,
        result->recovery_allowed,
        result->rollback_allowed,
        result->hardware_allowed,
        result->boot_allowed,
        result->record.source_identity,
        (unsigned long)result->record.source_span.start_offset,
        (unsigned long)result->record.source_span.end_offset,
        (unsigned long)result->record.source_span.start_line,
        (unsigned long)result->record.source_span.start_column,
        (unsigned long)result->record.source_span.end_line,
        (unsigned long)result->record.source_span.end_column);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
