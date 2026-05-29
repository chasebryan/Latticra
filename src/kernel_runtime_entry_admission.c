#include "latticra/kernel_runtime_entry_admission.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void admission_copy(char *dst, size_t dst_len, const char *src) {
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
    latticra_kernel_runtime_entry_admission_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    admission_copy(result->admission_status, sizeof(result->admission_status),
        "pending");
    admission_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->scheduler_run_entry_allowed = 0;
    result->runtime_entry_admission_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->scheduler_activation_allowed = 0;
    result->scheduler_handoff_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->scheduler_selection_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->context_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->cpu_usage_write_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 27u;
}

latticra_status_t latticra_kernel_runtime_entry_admission_default_request(
    latticra_kernel_runtime_entry_admission_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_run_entry_default_request(
            &request->scheduler_run_entry_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_admission_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_scheduler_run_entry_t *run_entry_at(
    const latticra_kernel_scheduler_run_entry_result_t *scheduler_run_entry,
    size_t index) {
    if (index < scheduler_run_entry->run_entry_count &&
        scheduler_run_entry->run_entries[index].declared) {
        return &scheduler_run_entry->run_entries[index];
    }
    return 0;
}

static unsigned long value_or_entry(
    const latticra_kernel_scheduler_run_entry_result_t *scheduler_run_entry,
    size_t index,
    unsigned long fallback,
    unsigned long (*reader)(const latticra_kernel_scheduler_run_entry_t *entry)) {
    const latticra_kernel_scheduler_run_entry_t *entry =
        run_entry_at(scheduler_run_entry, index);
    return entry ? reader(entry) : fallback;
}

static unsigned long read_run_entry_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->run_entry_token;
}

static unsigned long read_activation_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->activation_token;
}

static unsigned long read_handoff_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->handoff_token;
}

static unsigned long read_dispatch_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->dispatch_token;
}

static unsigned long read_selection_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->selection_token;
}

static unsigned long read_pid_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->pid_token;
}

static unsigned long read_credit_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->credit_token;
}

static unsigned long read_decision_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->decision_token;
}

static unsigned long read_switch_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->switch_token;
}

static unsigned long read_tick_token(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->tick_token;
}

static unsigned long read_run_entry_rank(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->run_entry_rank;
}

static unsigned long read_scheduler_credit(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->scheduler_credit_ns;
}

static unsigned long read_quota_credit(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->quota_credit_ns;
}

static unsigned long read_remaining_budget(
    const latticra_kernel_scheduler_run_entry_t *entry) {
    return entry->remaining_budget_ns;
}

static const char *process_for(
    const latticra_kernel_scheduler_run_entry_result_t *scheduler_run_entry,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_run_entry_t *entry =
        run_entry_at(scheduler_run_entry, index);
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
            return "kernel-report-runtime-entry-admission";
        case 1u:
            return "entropy-runtime-entry-admission";
        case 2u:
            return "console-runtime-entry-admission";
        case 3u:
            return "idle-runtime-entry-admission";
        default:
            return "reserved-runtime-entry-admission";
    }
}

static unsigned long fallback_admission_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 15000ul + (unsigned long)index;
}

static unsigned long fallback_run_entry_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 14000ul + (unsigned long)index;
}

static void fill_admission(
    latticra_kernel_runtime_entry_admission_entry_t *entry,
    const latticra_kernel_scheduler_run_entry_result_t *scheduler_run_entry,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->admission_index = index;
    entry->admission_token = fallback_admission_token(index);
    entry->run_entry_token = value_or_entry(scheduler_run_entry, index,
        fallback_run_entry_token(index), read_run_entry_token);
    entry->activation_token = value_or_entry(scheduler_run_entry, index,
        13000ul + (unsigned long)index, read_activation_token);
    entry->handoff_token = value_or_entry(scheduler_run_entry, index,
        12000ul + (unsigned long)index, read_handoff_token);
    entry->dispatch_token = value_or_entry(scheduler_run_entry, index,
        11000ul + (unsigned long)index, read_dispatch_token);
    entry->selection_token = value_or_entry(scheduler_run_entry, index,
        10000ul + (unsigned long)index, read_selection_token);
    entry->pid_token = value_or_entry(scheduler_run_entry, index,
        2000ul + (unsigned long)index, read_pid_token);
    entry->credit_token = value_or_entry(scheduler_run_entry, index,
        9000ul + (unsigned long)index, read_credit_token);
    entry->decision_token = value_or_entry(scheduler_run_entry, index,
        8000ul + (unsigned long)index, read_decision_token);
    entry->switch_token = value_or_entry(scheduler_run_entry, index,
        6000ul + (unsigned long)index, read_switch_token);
    entry->tick_token = value_or_entry(scheduler_run_entry, index,
        4000ul + (unsigned long)index, read_tick_token);
    entry->run_entry_rank = value_or_entry(scheduler_run_entry, index,
        (unsigned long)index + 1ul, read_run_entry_rank);
    entry->admission_rank = (unsigned long)index + 1ul;
    entry->scheduler_credit_ns = value_or_entry(scheduler_run_entry, index,
        0ul, read_scheduler_credit);
    entry->quota_credit_ns = value_or_entry(scheduler_run_entry, index,
        0ul, read_quota_credit);
    entry->remaining_budget_ns = value_or_entry(scheduler_run_entry, index,
        0ul, read_remaining_budget);
    entry->run_entry_declared = 1;
    entry->admission_declared = 1;
    admission_copy(entry->process_label, sizeof(entry->process_label),
        process_for(scheduler_run_entry, index, fallback_process(index)));
    admission_copy(entry->admission_class, sizeof(entry->admission_class),
        class_for(index));
    admission_copy(entry->admission_status, sizeof(entry->admission_status),
        "declared-metadata");
    admission_copy(entry->authority_status, sizeof(entry->authority_status),
        "runtime-entry-admission-authority-denied");
    entry->declared = 1;
    entry->admission_planned = 0;
    entry->admitted = 0;
    entry->runtime_entry_planned = 0;
    entry->runtime_entry_entered = 0;
    entry->execution_entered = 0;
    entry->context_switch_planned = 0;
    entry->scheduler_run_entry_allowed = 0;
    entry->runtime_entry_admission_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->scheduler_activation_allowed = 0;
    entry->scheduler_handoff_allowed = 0;
    entry->scheduler_dispatch_allowed = 0;
    entry->scheduler_selection_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->preemption_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->cpu_usage_write_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 27u;
}

static void fill_admissions(
    latticra_kernel_runtime_entry_admission_result_t *result,
    size_t requested_admission_count) {
    size_t count = requested_admission_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_MAX) {
        count = LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_MAX;
    }

    result->admission_count = count;
    for (i = 0u; i < count; ++i) {
        fill_admission(&result->admissions[i], &result->scheduler_run_entry, i);
    }
}

latticra_status_t latticra_kernel_runtime_entry_admission_evaluate(
    const latticra_kernel_runtime_entry_admission_request_t *request,
    latticra_kernel_runtime_entry_admission_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        admission_copy(result->admission_status,
            sizeof(result->admission_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_run_entry_evaluate(
        &request->scheduler_run_entry_request, &result->scheduler_run_entry);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        admission_copy(result->admission_status,
            sizeof(result->admission_status), "scheduler-run-entry-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_admissions(result, request->requested_admission_count);
    result->no_effect = result->scheduler_run_entry.no_effect;
    admission_copy(result->admission_status, sizeof(result->admission_status),
        result->no_effect ? "runtime-entry-admission-seed-ready" :
            "runtime-entry-admission-seed-blocked");
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

latticra_status_t latticra_kernel_runtime_entry_admission_report(
    const latticra_kernel_runtime_entry_admission_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY ADMISSION REPORT\n"
        "admission_status=%s\n"
        "policy_status=%s\n"
        "scheduler_run_entry_status=%s\n"
        "scheduler_activation_status=%s\n"
        "scheduler_handoff_status=%s\n"
        "scheduler_dispatch_status=%s\n"
        "scheduler_selection_status=%s\n"
        "admission_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_admission_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "scheduler_run_entry_allowed=%d\n"
        "scheduler_activation_allowed=%d\n"
        "scheduler_handoff_allowed=%d\n"
        "scheduler_dispatch_allowed=%d\n"
        "scheduler_selection_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "cpu_usage_write_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->admission_status,
        result->policy_status,
        result->scheduler_run_entry.run_entry_status,
        result->scheduler_run_entry.scheduler_activation.activation_status,
        result->scheduler_run_entry.scheduler_activation.scheduler_handoff.
            handoff_status,
        result->scheduler_run_entry.scheduler_activation.scheduler_handoff.
            scheduler_dispatch.dispatch_status,
        result->scheduler_run_entry.scheduler_activation.scheduler_handoff.
            scheduler_dispatch.scheduler_selection.selection_status,
        (unsigned long)result->admission_count,
        result->no_effect,
        result->runtime_entry_admission_allowed,
        result->runtime_entry_allowed,
        result->scheduler_run_entry_allowed,
        result->scheduler_activation_allowed,
        result->scheduler_handoff_allowed,
        result->scheduler_dispatch_allowed,
        result->scheduler_selection_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->context_switch_allowed,
        result->preemption_allowed,
        result->scheduler_credit_update_allowed,
        result->quota_update_allowed,
        result->cpu_usage_write_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->admission_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "admission[%lu].process_label=%s\n"
            "admission[%lu].admission_token=%lu\n"
            "admission[%lu].run_entry_token=%lu\n"
            "admission[%lu].activation_token=%lu\n"
            "admission[%lu].pid_token=%lu\n"
            "admission[%lu].run_entry_rank=%lu\n"
            "admission[%lu].admission_rank=%lu\n"
            "admission[%lu].remaining_budget_ns=%lu\n"
            "admission[%lu].run_entry_declared=%d\n"
            "admission[%lu].admission_declared=%d\n"
            "admission[%lu].admission_class=%s\n"
            "admission[%lu].admission_status=%s\n"
            "admission[%lu].authority_status=%s\n"
            "admission[%lu].admission_planned=%d\n"
            "admission[%lu].admitted=%d\n"
            "admission[%lu].runtime_entry_planned=%d\n"
            "admission[%lu].runtime_entry_entered=%d\n"
            "admission[%lu].execution_entered=%d\n"
            "admission[%lu].context_switch_planned=%d\n"
            "admission[%lu].runtime_entry_admission_allowed=%d\n"
            "admission[%lu].runtime_entry_allowed=%d\n"
            "admission[%lu].scheduler_run_entry_allowed=%d\n"
            "admission[%lu].dispatch_allowed=%d\n"
            "admission[%lu].run_queue_mutation_allowed=%d\n"
            "admission[%lu].context_switch_allowed=%d\n"
            "admission[%lu].hardware_effect_allowed=%d\n"
            "admission[%lu].host_effect_allowed=%d\n"
            "admission[%lu].no_effect=%d\n",
            (unsigned long)i, result->admissions[i].process_label,
            (unsigned long)i, result->admissions[i].admission_token,
            (unsigned long)i, result->admissions[i].run_entry_token,
            (unsigned long)i, result->admissions[i].activation_token,
            (unsigned long)i, result->admissions[i].pid_token,
            (unsigned long)i, result->admissions[i].run_entry_rank,
            (unsigned long)i, result->admissions[i].admission_rank,
            (unsigned long)i, result->admissions[i].remaining_budget_ns,
            (unsigned long)i, result->admissions[i].run_entry_declared,
            (unsigned long)i, result->admissions[i].admission_declared,
            (unsigned long)i, result->admissions[i].admission_class,
            (unsigned long)i, result->admissions[i].admission_status,
            (unsigned long)i, result->admissions[i].authority_status,
            (unsigned long)i, result->admissions[i].admission_planned,
            (unsigned long)i, result->admissions[i].admitted,
            (unsigned long)i, result->admissions[i].runtime_entry_planned,
            (unsigned long)i, result->admissions[i].runtime_entry_entered,
            (unsigned long)i, result->admissions[i].execution_entered,
            (unsigned long)i, result->admissions[i].context_switch_planned,
            (unsigned long)i,
            result->admissions[i].runtime_entry_admission_allowed,
            (unsigned long)i, result->admissions[i].runtime_entry_allowed,
            (unsigned long)i, result->admissions[i].scheduler_run_entry_allowed,
            (unsigned long)i, result->admissions[i].dispatch_allowed,
            (unsigned long)i, result->admissions[i].run_queue_mutation_allowed,
            (unsigned long)i, result->admissions[i].context_switch_allowed,
            (unsigned long)i, result->admissions[i].hardware_effect_allowed,
            (unsigned long)i, result->admissions[i].host_effect_allowed,
            (unsigned long)i, result->admissions[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
