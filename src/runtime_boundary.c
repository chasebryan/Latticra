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
}

latticra_status_t latticra_runtime_boundary_classify(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);
    if (request == 0) {
        result->record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    result->record.request_kind = request->request_kind;
    result->record.requested_effect = request->requested_effect;
    result->record.mode = request->mode;
    result->record.operator_confirmation = request->operator_confirmation;
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
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_runtime_boundary_report(const latticra_runtime_boundary_result_t *result, char *buffer, size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(buffer, buffer_len,
        "LATTICRA RUNTIME BOUNDARY REPORT\npolicy=%s\nreason=%s\ngate=%s\n",
        latticra_runtime_boundary_policy_label(result->record.policy),
        latticra_runtime_boundary_denial_label(result->record.denial),
        latticra_runtime_boundary_gate_state_label(result->record.gate_state));
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
