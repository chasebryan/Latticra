#include "latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void recovery_audit_review_copy(char *dst,
                                       size_t dst_len,
                                       const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_result_t
        *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    recovery_audit_review_copy(
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
        sizeof(result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status),
        "pending");
    recovery_audit_review_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_review_observation_view_allowed = 0;
    result->runtime_entry_recovery_audit_observation_view_allowed = 0;
    result->runtime_entry_recovery_closeout_observation_view_allowed = 0;
    result->runtime_entry_recovery_outcome_observation_view_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_archive_gate_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_allowed = 0;
    result->recovery_audit_review_disposition_review_closeout_observation_allowed = 0;
    result->recovery_audit_review_disposition_allowed = 0;
    result->recovery_audit_review_observation_allowed = 0;
    result->recovery_audit_review_allowed = 0;
    result->recovery_audit_observation_allowed = 0;
    result->recovery_audit_allowed = 0;
    result->recovery_closeout_observation_allowed = 0;
    result->recovery_closeout_allowed = 0;
    result->recovery_outcome_observation_allowed = 0;
    result->recovery_outcome_allowed = 0;
    result->recovery_authority_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 57u;
}

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_default_request(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request_t
        *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_default_request(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request) !=
        LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const
latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_entry_t *
recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_at(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_result_t
        *view,
    size_t index) {
    if (index < view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_count &&
        view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_views[index].declared) {
        return &view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_views[index];
    }
    return 0;
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view";
        case 1u:
            return "entropy-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view";
        case 2u:
            return "console-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view";
        case 3u:
            return "idle-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view";
        default:
            return "reserved-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view";
    }
}

static const char *fallback_process(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-process-metadata";
        case 1u:
            return "entropy-report-process-metadata";
        case 2u:
            return "console-report-process-metadata";
        case 3u:
            return "idle-process-metadata";
        default:
            return "reserved-process-metadata";
    }
}

static void deny_recovery_audit_review_authority(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_entry_t
        *entry) {
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_planned = 0;
    entry->recovery_audit_review_disposition_review_closeout_observation_planned = 0;
    entry->recovery_audit_review_disposition_planned = 0;
    entry->recovery_audit_review_observation_planned = 0;
    entry->recovery_audit_review_planned = 0;
    entry->recovery_audit_observation_planned = 0;
    entry->recovery_audit_planned = 0;
    entry->recovery_closeout_observation_planned = 0;
    entry->recovery_closeout_planned = 0;
    entry->recovery_outcome_observation_planned = 0;
    entry->recovery_outcome_planned = 0;
    entry->recovery_authority_planned = 0;
    entry->scheduler_execution_planned = 0;
    entry->context_switch_planned = 0;
    entry->run_queue_mutation_planned = 0;
    entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_review_observation_view_allowed = 0;
    entry->runtime_entry_recovery_audit_observation_view_allowed = 0;
    entry->runtime_entry_recovery_closeout_observation_view_allowed = 0;
    entry->runtime_entry_recovery_outcome_observation_view_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_allowed = 0;
    entry->recovery_audit_review_disposition_review_closeout_observation_allowed = 0;
    entry->recovery_audit_review_disposition_allowed = 0;
    entry->recovery_audit_review_observation_allowed = 0;
    entry->recovery_audit_review_allowed = 0;
    entry->recovery_audit_observation_allowed = 0;
    entry->recovery_audit_allowed = 0;
    entry->recovery_closeout_observation_allowed = 0;
    entry->recovery_closeout_allowed = 0;
    entry->recovery_outcome_observation_allowed = 0;
    entry->recovery_outcome_allowed = 0;
    entry->recovery_authority_allowed = 0;
    entry->scheduler_execution_allowed = 0;
    entry->scheduler_dispatch_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
}

static void fill_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_entry_t
        *entry,
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_result_t
        *view,
    size_t index) {
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_entry_t
        *archive_gate_review_view =
            recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_at(view, index);

    memset(entry, 0, sizeof(*entry));
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_index = index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_token =
        index < 4u ? (unsigned long)index : 45000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_token =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_token :
        44000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_token =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_token :
        43000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_token =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_token :
        42000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_observation_view_token =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_observation_view_token :
        41000ul + (unsigned long)index;
    entry->recovery_audit_review_observation_view_token = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_observation_view_token :
        38000ul + (unsigned long)index;
    entry->recovery_audit_observation_view_token = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_observation_view_token :
        37000ul + (unsigned long)index;
    entry->recovery_closeout_observation_view_token = archive_gate_review_view ?
        archive_gate_review_view->recovery_closeout_observation_view_token :
        36000ul + (unsigned long)index;
    entry->recovery_outcome_observation_view_token = archive_gate_review_view ?
        archive_gate_review_view->recovery_outcome_observation_view_token :
        35000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_slot =
        24576ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_slot :
        23552ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_slot :
        22528ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_observation_slot :
        21504ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_observation_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_observation_slot :
        20480ul + (unsigned long)index;
    entry->recovery_audit_review_observation_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_observation_slot :
        17408ul + (unsigned long)index;
    entry->recovery_audit_observation_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_observation_slot :
        16384ul + (unsigned long)index;
    entry->recovery_closeout_observation_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_closeout_observation_slot :
        15360ul + (unsigned long)index;
    entry->recovery_outcome_observation_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_outcome_observation_slot :
        14336ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_slot = 45ul;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_slot :
        44ul;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_review_slot :
        43ul;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_slot =
        archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_archive_gate_slot :
        42ul;
    entry->recovery_audit_review_disposition_review_closeout_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_review_closeout_slot : 41ul;
    entry->recovery_audit_review_disposition_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_disposition_slot : 39ul;
    entry->recovery_audit_review_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_audit_review_slot : 38ul;
    entry->recovery_audit_slot = archive_gate_review_view ? archive_gate_review_view->recovery_audit_slot :
        37ul;
    entry->recovery_closeout_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_closeout_slot : 36ul;
    entry->recovery_outcome_slot = archive_gate_review_view ?
        archive_gate_review_view->recovery_outcome_slot : 35ul;
    entry->pid_token = archive_gate_review_view ? archive_gate_review_view->pid_token :
        4000ul + (unsigned long)index;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_observation_view_declared = 1;
    entry->recovery_audit_review_observation_view_declared = 1;
    entry->recovery_audit_observation_view_declared = 1;
    entry->recovery_closeout_observation_view_declared = 1;
    entry->recovery_outcome_observation_view_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_archive_gate_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_declared = 1;
    entry->recovery_audit_review_disposition_review_closeout_observation_declared = 1;
    entry->recovery_audit_review_disposition_declared = 1;
    entry->recovery_audit_review_observation_declared = 1;
    entry->recovery_audit_review_declared = 1;
    entry->recovery_audit_observation_declared = 1;
    entry->recovery_audit_declared = 1;
    entry->recovery_closeout_observation_declared = 1;
    entry->recovery_closeout_declared = 1;
    entry->recovery_outcome_observation_declared = 1;
    entry->recovery_outcome_declared = 1;
    entry->recovery_authority_observation_declared = 1;
    recovery_audit_review_copy(entry->process_label,
        sizeof(entry->process_label),
        archive_gate_review_view ? archive_gate_review_view->process_label : fallback_process(index));
    recovery_audit_review_copy(
        entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_class,
        sizeof(entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_class),
        class_for(index));
    recovery_audit_review_copy(
        entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
        sizeof(entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status),
        "declared-metadata");
    recovery_audit_review_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-authority-denied");
    entry->declared = 1;
    entry->no_effect = 1;
    entry->evidence_level = 57u;
    deny_recovery_audit_review_authority(entry);
}

static void fill_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_views(
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_result_t
        *result,
    size_t requested_count) {
    size_t count = requested_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count >
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_MAX) {
        count =
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_MAX;
    }

    result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view(
            &result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_views[i],
            &result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view,
            i);
    }
}

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_evaluate(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_request_t
        *request,
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_result_t
        *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        recovery_audit_review_copy(
            result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
            sizeof(result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status =
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_evaluate(
            &request->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_request,
            &result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        result->no_effect = 0;
        recovery_audit_review_copy(
            result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
            sizeof(result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status),
            "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-not-ready");
        return status;
    }

    fill_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_views(result,
        request->requested_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count);
    result->no_effect =
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.no_effect;
    recovery_audit_review_copy(
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
        sizeof(result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status),
        result->no_effect ?
            "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-seed-ready" :
            "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-seed-blocked");
    return result->status;
}

static latticra_status_t append_text(char *buffer,
                                     size_t buffer_len,
                                     size_t *used,
                                     const char *fmt,
                                     ...) {
    int written;
    va_list args;
    if (*used >= buffer_len) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    va_start(args, fmt);
    written = vsnprintf(buffer + *used, buffer_len - *used, fmt, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    *used += (size_t)written;
    return LATTICRA_STATUS_OK;
}

static latticra_status_t append_entry_int(char *buffer,
                                          size_t buffer_len,
                                          size_t *used,
                                          size_t index,
                                          const char *field,
                                          int value) {
    return append_text(buffer, buffer_len, used,
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].%s=%d\n",
        (unsigned long)index, field, value);
}

static latticra_status_t append_entry_ulong(char *buffer,
                                            size_t buffer_len,
                                            size_t *used,
                                            size_t index,
                                            const char *field,
                                            unsigned long value) {
    return append_text(buffer, buffer_len, used,
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].%s=%lu\n",
        (unsigned long)index, field, value);
}

static latticra_status_t append_entry_string(char *buffer,
                                             size_t buffer_len,
                                             size_t *used,
                                             size_t index,
                                             const char *field,
                                             const char *value) {
    return append_text(buffer, buffer_len, used,
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].%s=%s\n",
        (unsigned long)index, field, value);
}

latticra_status_t
latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_report(
    const
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_result_t
        *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY RECOVERY AUDIT REVIEW DISPOSITION REVIEW CLOSEOUT ARCHIVE GATE REVIEW DISPOSITION CLOSEOUT OBSERVATION VIEW REPORT\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_status=%s\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_status=%s\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=%s\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_status=%s\n"
        "runtime_entry_recovery_audit_review_observation_view_status=%s\n"
        "runtime_entry_recovery_audit_observation_view_status=%s\n"
        "runtime_entry_recovery_closeout_observation_view_status=%s\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_review_observation_view_allowed=%d\n"
        "runtime_entry_recovery_audit_observation_view_allowed=%d\n"
        "runtime_entry_recovery_closeout_observation_view_allowed=%d\n"
        "runtime_entry_recovery_outcome_observation_view_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_archive_gate_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_allowed=%d\n"
        "recovery_audit_review_disposition_review_closeout_observation_allowed=%d\n"
        "recovery_audit_review_disposition_allowed=%d\n"
        "recovery_audit_review_observation_allowed=%d\n"
        "recovery_audit_review_allowed=%d\n"
        "recovery_audit_observation_allowed=%d\n"
        "recovery_audit_allowed=%d\n"
        "recovery_closeout_observation_allowed=%d\n"
        "recovery_closeout_allowed=%d\n"
        "recovery_outcome_observation_allowed=%d\n"
        "recovery_outcome_allowed=%d\n"
        "recovery_authority_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "scheduler_dispatch_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status,
        result->policy_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            recovery_audit_review_disposition_review_closeout_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view.
            recovery_audit_review_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view.
            runtime_entry_recovery_audit_observation_view.
            recovery_audit_observation_view_status,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view.
            runtime_entry_recovery_audit_observation_view.
            runtime_entry_recovery_closeout_observation_view.
            recovery_closeout_observation_view_status,
        (unsigned long)result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count,
        result->no_effect,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed,
        result->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed,
        result->runtime_entry_recovery_audit_review_observation_view_allowed,
        result->runtime_entry_recovery_audit_observation_view_allowed,
        result->runtime_entry_recovery_closeout_observation_view_allowed,
        result->runtime_entry_recovery_outcome_observation_view_allowed,
        result->runtime_entry_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed,
        result->recovery_audit_review_disposition_review_closeout_archive_gate_allowed,
        result->recovery_audit_review_disposition_review_closeout_allowed,
        result->recovery_audit_review_disposition_review_closeout_observation_allowed,
        result->recovery_audit_review_disposition_allowed,
        result->recovery_audit_review_observation_allowed,
        result->recovery_audit_review_allowed,
        result->recovery_audit_observation_allowed,
        result->recovery_audit_allowed,
        result->recovery_closeout_observation_allowed,
        result->recovery_closeout_allowed,
        result->recovery_outcome_observation_allowed,
        result->recovery_outcome_allowed,
        result->recovery_authority_allowed,
        result->scheduler_execution_allowed,
        result->scheduler_dispatch_allowed,
        result->context_switch_allowed,
        result->run_queue_mutation_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count; ++i) {
        const
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_entry_t
            *entry = &result->recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_views[i];

#define APPEND_ENTRY_STRING(field) \
    do { \
        status = append_entry_string(buffer, buffer_len, &used, i, #field, \
            entry->field); \
        if (status != LATTICRA_STATUS_OK) return status; \
    } while (0)
        APPEND_ENTRY_STRING(process_label);
        APPEND_ENTRY_STRING(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_class);
#undef APPEND_ENTRY_STRING

#define APPEND_ENTRY_ULONG(field) \
    do { \
        status = append_entry_ulong(buffer, buffer_len, &used, i, #field, \
            entry->field); \
        if (status != LATTICRA_STATUS_OK) return status; \
    } while (0)
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_closeout_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_outcome_observation_view_token);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_observation_slot);
        APPEND_ENTRY_ULONG(recovery_closeout_observation_slot);
        APPEND_ENTRY_ULONG(recovery_outcome_observation_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_review_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_archive_gate_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_review_closeout_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_disposition_slot);
        APPEND_ENTRY_ULONG(recovery_audit_review_slot);
        APPEND_ENTRY_ULONG(recovery_audit_slot);
        APPEND_ENTRY_ULONG(recovery_closeout_slot);
        APPEND_ENTRY_ULONG(recovery_outcome_slot);
#undef APPEND_ENTRY_ULONG

#define APPEND_ENTRY_INT(field) \
    do { \
        status = append_entry_int(buffer, buffer_len, &used, i, #field, \
            entry->field); \
        if (status != LATTICRA_STATUS_OK) return status; \
    } while (0)
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_declared);
        APPEND_ENTRY_INT(recovery_audit_review_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_review_declared);
        APPEND_ENTRY_INT(recovery_audit_observation_declared);
        APPEND_ENTRY_INT(recovery_audit_declared);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_observation_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_planned);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_observation_planned);
        APPEND_ENTRY_INT(recovery_audit_review_observation_planned);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_review_observation_view_allowed);
        APPEND_ENTRY_INT(runtime_entry_recovery_audit_observation_view_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_archive_gate_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_review_closeout_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_disposition_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_review_allowed);
        APPEND_ENTRY_INT(recovery_audit_observation_allowed);
        APPEND_ENTRY_INT(recovery_audit_allowed);
        APPEND_ENTRY_INT(no_effect);
#undef APPEND_ENTRY_INT

#if 0
        status = append_text(buffer, buffer_len, &used,
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_observation_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_observation_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_observation_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_observation_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_declared=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_observation_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_observation_planned=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_observation_planned=%d\n",
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_observation_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_declared,
            (unsigned long)i,
            entry->recovery_audit_review_observation_declared,
            (unsigned long)i, entry->recovery_audit_review_declared,
            (unsigned long)i, entry->recovery_audit_observation_declared,
            (unsigned long)i, entry->recovery_audit_declared,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_planned,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_planned,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_planned,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_planned,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_planned,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_observation_planned,
            (unsigned long)i,
            entry->recovery_audit_review_observation_planned);
        if (status != LATTICRA_STATUS_OK) return status;

        status = append_text(buffer, buffer_len, &used,
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].runtime_entry_recovery_audit_review_observation_view_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].runtime_entry_recovery_audit_observation_view_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_archive_gate_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_review_closeout_observation_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_disposition_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_observation_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_review_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_observation_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].recovery_audit_allowed=%d\n"
            "recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view[%lu].no_effect=%d\n",
            (unsigned long)i,
            entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed,
            (unsigned long)i,
            entry->runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed,
            (unsigned long)i,
            entry->runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed,
            (unsigned long)i,
            entry->runtime_entry_recovery_audit_review_observation_view_allowed,
            (unsigned long)i,
            entry->runtime_entry_recovery_audit_observation_view_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_archive_gate_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_review_closeout_observation_allowed,
            (unsigned long)i,
            entry->recovery_audit_review_disposition_allowed,
            (unsigned long)i, entry->recovery_audit_review_observation_allowed,
            (unsigned long)i, entry->recovery_audit_review_allowed,
            (unsigned long)i, entry->recovery_audit_observation_allowed,
            (unsigned long)i, entry->recovery_audit_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
#endif
    }

    return LATTICRA_STATUS_OK;
}
