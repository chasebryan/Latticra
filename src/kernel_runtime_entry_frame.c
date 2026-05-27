#include "latticra/kernel_runtime_entry_frame.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void frame_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_runtime_entry_frame_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    frame_copy(result->frame_status, sizeof(result->frame_status), "pending");
    frame_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->runtime_entry_frame_allowed = 0;
    result->runtime_entry_admission_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->scheduler_run_entry_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->context_switch_allowed = 0;
    result->stack_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 28u;
}

latticra_status_t latticra_kernel_runtime_entry_frame_default_request(
    latticra_kernel_runtime_entry_frame_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_admission_default_request(
            &request->runtime_entry_admission_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_frame_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_admission_entry_t *admission_at(
    const latticra_kernel_runtime_entry_admission_result_t *admission,
    size_t index) {
    if (index < admission->admission_count &&
        admission->admissions[index].declared) {
        return &admission->admissions[index];
    }
    return 0;
}

static unsigned long admission_value_or(
    const latticra_kernel_runtime_entry_admission_result_t *admission,
    size_t index,
    unsigned long fallback,
    unsigned long (*reader)(
        const latticra_kernel_runtime_entry_admission_entry_t *entry)) {
    const latticra_kernel_runtime_entry_admission_entry_t *entry =
        admission_at(admission, index);
    return entry ? reader(entry) : fallback;
}

static unsigned long read_admission_token(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->admission_token;
}

static unsigned long read_run_entry_token(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->run_entry_token;
}

static unsigned long read_activation_token(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->activation_token;
}

static unsigned long read_pid_token(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->pid_token;
}

static unsigned long read_run_entry_rank(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->run_entry_rank;
}

static unsigned long read_admission_rank(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->admission_rank;
}

static unsigned long read_remaining_budget(
    const latticra_kernel_runtime_entry_admission_entry_t *entry) {
    return entry->remaining_budget_ns;
}

static const char *process_for(
    const latticra_kernel_runtime_entry_admission_result_t *admission,
    size_t index,
    const char *fallback) {
    const latticra_kernel_runtime_entry_admission_entry_t *entry =
        admission_at(admission, index);
    return entry ? entry->process_label : fallback;
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

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-runtime-entry-frame";
        case 1u:
            return "entropy-runtime-entry-frame";
        case 2u:
            return "console-runtime-entry-frame";
        case 3u:
            return "idle-runtime-entry-frame";
        default:
            return "reserved-runtime-entry-frame";
    }
}

static unsigned long fallback_frame_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 16000ul + (unsigned long)index;
}

static unsigned long fallback_admission_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 15000ul + (unsigned long)index;
}

static unsigned long fallback_run_entry_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 14000ul + (unsigned long)index;
}

static void fill_frame(
    latticra_kernel_runtime_entry_frame_entry_t *entry,
    const latticra_kernel_runtime_entry_admission_result_t *admission,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->frame_index = index;
    entry->frame_token = fallback_frame_token(index);
    entry->admission_token = admission_value_or(admission, index,
        fallback_admission_token(index), read_admission_token);
    entry->run_entry_token = admission_value_or(admission, index,
        fallback_run_entry_token(index), read_run_entry_token);
    entry->activation_token = admission_value_or(admission, index,
        13000ul + (unsigned long)index, read_activation_token);
    entry->pid_token = admission_value_or(admission, index,
        2000ul + (unsigned long)index, read_pid_token);
    entry->run_entry_rank = admission_value_or(admission, index,
        (unsigned long)index + 1ul, read_run_entry_rank);
    entry->admission_rank = admission_value_or(admission, index,
        (unsigned long)index + 1ul, read_admission_rank);
    entry->frame_rank = (unsigned long)index + 1ul;
    entry->remaining_budget_ns = admission_value_or(admission, index,
        0ul, read_remaining_budget);
    entry->admission_declared = 1;
    entry->frame_declared = 1;
    frame_copy(entry->process_label, sizeof(entry->process_label),
        process_for(admission, index, fallback_process(index)));
    frame_copy(entry->frame_class, sizeof(entry->frame_class),
        class_for(index));
    frame_copy(entry->frame_status, sizeof(entry->frame_status),
        "declared-metadata");
    frame_copy(entry->authority_status, sizeof(entry->authority_status),
        "runtime-entry-frame-authority-denied");
    entry->declared = 1;
    entry->frame_planned = 0;
    entry->frame_built = 0;
    entry->frame_installed = 0;
    entry->admitted = 0;
    entry->runtime_entry_planned = 0;
    entry->runtime_entry_entered = 0;
    entry->execution_entered = 0;
    entry->context_switch_planned = 0;
    entry->runtime_entry_frame_allowed = 0;
    entry->runtime_entry_admission_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->scheduler_run_entry_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->stack_switch_allowed = 0;
    entry->preemption_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 28u;
}

static void fill_frames(
    latticra_kernel_runtime_entry_frame_result_t *result,
    size_t requested_frame_count) {
    size_t count = requested_frame_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_MAX) {
        count = LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_MAX;
    }

    result->frame_count = count;
    for (i = 0u; i < count; ++i) {
        fill_frame(&result->frames[i], &result->runtime_entry_admission, i);
    }
}

latticra_status_t latticra_kernel_runtime_entry_frame_evaluate(
    const latticra_kernel_runtime_entry_frame_request_t *request,
    latticra_kernel_runtime_entry_frame_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        frame_copy(result->frame_status, sizeof(result->frame_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_admission_evaluate(
        &request->runtime_entry_admission_request,
        &result->runtime_entry_admission);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        frame_copy(result->frame_status, sizeof(result->frame_status),
            "runtime-entry-admission-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_frames(result, request->requested_frame_count);
    result->no_effect = result->runtime_entry_admission.no_effect;
    frame_copy(result->frame_status, sizeof(result->frame_status),
        result->no_effect ? "runtime-entry-frame-seed-ready" :
            "runtime-entry-frame-seed-blocked");
    return result->status;
}

static latticra_status_t append_text(
    char *buffer,
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

latticra_status_t latticra_kernel_runtime_entry_frame_report(
    const latticra_kernel_runtime_entry_frame_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY FRAME REPORT\n"
        "frame_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_admission_status=%s\n"
        "scheduler_run_entry_status=%s\n"
        "frame_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_frame_allowed=%d\n"
        "runtime_entry_admission_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "scheduler_run_entry_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "stack_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->frame_status,
        result->policy_status,
        result->runtime_entry_admission.admission_status,
        result->runtime_entry_admission.scheduler_run_entry.run_entry_status,
        (unsigned long)result->frame_count,
        result->no_effect,
        result->runtime_entry_frame_allowed,
        result->runtime_entry_admission_allowed,
        result->runtime_entry_allowed,
        result->scheduler_run_entry_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->context_switch_allowed,
        result->stack_switch_allowed,
        result->preemption_allowed,
        result->scheduler_credit_update_allowed,
        result->quota_update_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->frame_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "frame[%lu].process_label=%s\n"
            "frame[%lu].frame_token=%lu\n"
            "frame[%lu].admission_token=%lu\n"
            "frame[%lu].run_entry_token=%lu\n"
            "frame[%lu].activation_token=%lu\n"
            "frame[%lu].pid_token=%lu\n"
            "frame[%lu].run_entry_rank=%lu\n"
            "frame[%lu].admission_rank=%lu\n"
            "frame[%lu].frame_rank=%lu\n"
            "frame[%lu].remaining_budget_ns=%lu\n"
            "frame[%lu].admission_declared=%d\n"
            "frame[%lu].frame_declared=%d\n"
            "frame[%lu].declared=%d\n"
            "frame[%lu].frame_class=%s\n"
            "frame[%lu].frame_status=%s\n"
            "frame[%lu].authority_status=%s\n"
            "frame[%lu].frame_planned=%d\n"
            "frame[%lu].frame_built=%d\n"
            "frame[%lu].frame_installed=%d\n"
            "frame[%lu].admitted=%d\n"
            "frame[%lu].runtime_entry_planned=%d\n"
            "frame[%lu].runtime_entry_entered=%d\n"
            "frame[%lu].execution_entered=%d\n"
            "frame[%lu].context_switch_planned=%d\n"
            "frame[%lu].runtime_entry_frame_allowed=%d\n"
            "frame[%lu].runtime_entry_admission_allowed=%d\n"
            "frame[%lu].runtime_entry_allowed=%d\n"
            "frame[%lu].scheduler_run_entry_allowed=%d\n"
            "frame[%lu].dispatch_allowed=%d\n"
            "frame[%lu].run_queue_mutation_allowed=%d\n"
            "frame[%lu].context_switch_allowed=%d\n"
            "frame[%lu].stack_switch_allowed=%d\n"
            "frame[%lu].hardware_effect_allowed=%d\n"
            "frame[%lu].host_effect_allowed=%d\n"
            "frame[%lu].no_effect=%d\n",
            (unsigned long)i, result->frames[i].process_label,
            (unsigned long)i, result->frames[i].frame_token,
            (unsigned long)i, result->frames[i].admission_token,
            (unsigned long)i, result->frames[i].run_entry_token,
            (unsigned long)i, result->frames[i].activation_token,
            (unsigned long)i, result->frames[i].pid_token,
            (unsigned long)i, result->frames[i].run_entry_rank,
            (unsigned long)i, result->frames[i].admission_rank,
            (unsigned long)i, result->frames[i].frame_rank,
            (unsigned long)i, result->frames[i].remaining_budget_ns,
            (unsigned long)i, result->frames[i].admission_declared,
            (unsigned long)i, result->frames[i].frame_declared,
            (unsigned long)i, result->frames[i].declared,
            (unsigned long)i, result->frames[i].frame_class,
            (unsigned long)i, result->frames[i].frame_status,
            (unsigned long)i, result->frames[i].authority_status,
            (unsigned long)i, result->frames[i].frame_planned,
            (unsigned long)i, result->frames[i].frame_built,
            (unsigned long)i, result->frames[i].frame_installed,
            (unsigned long)i, result->frames[i].admitted,
            (unsigned long)i, result->frames[i].runtime_entry_planned,
            (unsigned long)i, result->frames[i].runtime_entry_entered,
            (unsigned long)i, result->frames[i].execution_entered,
            (unsigned long)i, result->frames[i].context_switch_planned,
            (unsigned long)i, result->frames[i].runtime_entry_frame_allowed,
            (unsigned long)i,
            result->frames[i].runtime_entry_admission_allowed,
            (unsigned long)i, result->frames[i].runtime_entry_allowed,
            (unsigned long)i, result->frames[i].scheduler_run_entry_allowed,
            (unsigned long)i, result->frames[i].dispatch_allowed,
            (unsigned long)i, result->frames[i].run_queue_mutation_allowed,
            (unsigned long)i, result->frames[i].context_switch_allowed,
            (unsigned long)i, result->frames[i].stack_switch_allowed,
            (unsigned long)i, result->frames[i].hardware_effect_allowed,
            (unsigned long)i, result->frames[i].host_effect_allowed,
            (unsigned long)i, result->frames[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
