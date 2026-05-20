#include "latticra/system_bootstrap.h"

#include <stdio.h>
#include <string.h>

static void sb_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static latticra_l_ui_source_span_t sb_span(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 0u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 1u;
    return span;
}

static void sb_nucleus_authority(latticra_nucleus_task_authority_summary_t *authority) {
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    sb_copy(authority->status_label, sizeof(authority->status_label), "ok");
    sb_copy(authority->validator_label, sizeof(authority->validator_label), "system-bootstrap");
    sb_copy(authority->requested_effect_label, sizeof(authority->requested_effect_label), "none");
    sb_copy(authority->denial_reason, sizeof(authority->denial_reason), "ok");
    authority->no_effect = 1;
}

static void sb_boundary_authority(latticra_runtime_boundary_authority_summary_t *authority) {
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    sb_copy(authority->status_label, sizeof(authority->status_label), "ok");
    sb_copy(authority->validator_label, sizeof(authority->validator_label), "system-bootstrap");
    sb_copy(authority->requested_effect_label, sizeof(authority->requested_effect_label), "none");
    sb_copy(authority->denial_reason, sizeof(authority->denial_reason), "ok");
    authority->no_effect = 1;
}

latticra_status_t latticra_system_bootstrap_default_request(latticra_system_bootstrap_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    sb_copy(request->bootstrap_id, sizeof(request->bootstrap_id), "latticra-system-bootstrap");
    request->source_identity = "system-bootstrap-default";
    request->source_identity_len = strlen("system-bootstrap-default");
    request->source_span = sb_span();
    return LATTICRA_STATUS_OK;
}

static void sb_seed(const latticra_system_bootstrap_request_t *request, latticra_system_bootstrap_result_t *result) {
    size_t n;
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    sb_copy(result->phase, sizeof(result->phase), "startup-report");
    sb_copy(result->system_status, sizeof(result->system_status), "pending");
    sb_copy(result->effect_boundary, sizeof(result->effect_boundary), "no-effect");
    sb_copy(result->runtime_entry_status, sizeof(result->runtime_entry_status), "not-entered");
    result->source_span = sb_span();
    result->no_effect = 1;
    result->evidence_level = 3u;

    if (request == 0) return;
    sb_copy(result->bootstrap_id, sizeof(result->bootstrap_id), request->bootstrap_id);
    if (request->source_identity != 0 && request->source_identity_len > 0u) {
        n = request->source_identity_len;
        if (n >= sizeof(result->source_identity)) n = sizeof(result->source_identity) - 1u;
        memcpy(result->source_identity, request->source_identity, n);
        result->source_identity[n] = '\0';
    }
    result->source_span = request->source_span;
}

static latticra_status_t sb_classify_task(const latticra_system_bootstrap_request_t *request, latticra_system_bootstrap_result_t *result) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t task_request;
    latticra_status_t status;

    sb_nucleus_authority(&authority);
    memset(&preview, 0, sizeof(preview));
    status = latticra_nucleus_classify_preview(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE, &preview);
    if (status != LATTICRA_STATUS_OK) return status;

    memset(&task_request, 0, sizeof(task_request));
    sb_copy(task_request.task_id, sizeof(task_request.task_id), result->bootstrap_id);
    task_request.request_kind = LATTICRA_NUCLEUS_TASK_STATE_REPORT;
    task_request.requested_effect = LATTICRA_NUCLEUS_TASK_EFFECT_NONE;
    task_request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    task_request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    task_request.authority = &authority;
    task_request.preview = &preview;
    task_request.source_identity = request->source_identity;
    task_request.source_identity_len = request->source_identity_len;
    task_request.source_span = request->source_span;

    return latticra_nucleus_task_classify(&task_request, &result->nucleus_task);
}

static latticra_status_t sb_classify_boundary(const latticra_system_bootstrap_request_t *request, latticra_system_bootstrap_result_t *result) {
    latticra_runtime_boundary_authority_summary_t authority;
    latticra_runtime_boundary_request_t runtime_request;

    sb_boundary_authority(&authority);
    memset(&runtime_request, 0, sizeof(runtime_request));
    sb_copy(runtime_request.runtime_id, sizeof(runtime_request.runtime_id), result->bootstrap_id);
    runtime_request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT;
    runtime_request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    runtime_request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    runtime_request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    runtime_request.authority = &authority;
    runtime_request.task = &result->nucleus_task;
    runtime_request.source_identity = request->source_identity;
    runtime_request.source_identity_len = request->source_identity_len;
    runtime_request.source_span = request->source_span;

    return latticra_runtime_boundary_classify(&runtime_request, &result->runtime_boundary);
}

latticra_status_t latticra_system_bootstrap_run(const latticra_system_bootstrap_request_t *request, latticra_system_bootstrap_result_t *result) {
    latticra_status_t status;
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    sb_seed(request, result);
    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        sb_copy(result->system_status, sizeof(result->system_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = sb_classify_task(request, result);
    if (status != LATTICRA_STATUS_OK) return status;
    status = sb_classify_boundary(request, result);
    if (status != LATTICRA_STATUS_OK) return status;

    result->no_effect = result->nucleus_task.no_effect && result->runtime_boundary.no_effect;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->file_io_allowed = 0;
    result->network_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
    sb_copy(result->system_status, sizeof(result->system_status), result->no_effect ? "startup-report-ready" : "startup-report-blocked");
    return result->status;
}

latticra_status_t latticra_system_bootstrap_report(const latticra_system_bootstrap_result_t *result, char *buffer, size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(buffer, buffer_len,
        "LATTICRA SYSTEM BOOTSTRAP REPORT\n"
        "bootstrap_id=%s\n"
        "phase=%s\n"
        "system_status=%s\n"
        "effect_boundary=%s\n"
        "runtime_entry_status=%s\n"
        "evidence_level=%u\n"
        "nucleus_policy=%s\n"
        "nucleus_reason=%s\n"
        "nucleus_runtime_status=%s\n"
        "runtime_policy=%s\n"
        "runtime_reason=%s\n"
        "runtime_classification=%s\n"
        "runtime_policy_matrix_cell=%s\n"
        "no_effect=%d\n"
        "source_identity=%s\n",
        result->bootstrap_id,
        result->phase,
        result->system_status,
        result->effect_boundary,
        result->runtime_entry_status,
        result->evidence_level,
        latticra_nucleus_task_policy_label(result->nucleus_task.record.policy),
        latticra_nucleus_task_denial_label(result->nucleus_task.record.denial),
        result->nucleus_task.record.runtime_status,
        latticra_runtime_boundary_policy_label(result->runtime_boundary.record.policy),
        latticra_runtime_boundary_denial_label(result->runtime_boundary.record.denial),
        latticra_runtime_boundary_report_classification_label(result->runtime_boundary.record.report_classification),
        latticra_runtime_boundary_policy_matrix_cell_label(result->runtime_boundary.record.policy_matrix_cell),
        result->no_effect,
        result->source_identity);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
