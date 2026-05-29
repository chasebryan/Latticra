#include "latticra/kernel_scheduler_selection.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void selection_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_scheduler_selection_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    selection_copy(result->selection_status,
        sizeof(result->selection_status), "pending");
    selection_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
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
    result->evidence_level = 22u;
}

latticra_status_t latticra_kernel_scheduler_selection_default_request(
    latticra_kernel_scheduler_selection_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_credit_default_request(
            &request->scheduler_credit_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_selection_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_scheduler_credit_entry_t *credit_at(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index) {
    if (index < scheduler_credit->credit_count &&
        scheduler_credit->credits[index].declared) {
        return &scheduler_credit->credits[index];
    }
    return 0;
}

static unsigned long credit_pid_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->pid_token : fallback;
}

static unsigned long credit_token_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->credit_token : fallback;
}

static unsigned long credit_decision_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->decision_token : fallback;
}

static unsigned long credit_switch_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long credit_tick_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long scheduler_credit_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->scheduler_credit_ns : fallback;
}

static unsigned long quota_credit_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->quota_credit_ns : fallback;
}

static unsigned long remaining_budget_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->remaining_budget_ns : fallback;
}

static const char *credit_process_for(
    const latticra_kernel_scheduler_credit_result_t *scheduler_credit,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_credit_entry_t *entry =
        credit_at(scheduler_credit, index);
    return entry ? entry->process_label : fallback;
}

static void fill_selection(
    latticra_kernel_scheduler_selection_entry_t *entry,
    size_t index,
    unsigned long selection_token,
    unsigned long pid_token,
    unsigned long credit_token,
    unsigned long decision_token,
    unsigned long switch_token,
    unsigned long tick_token,
    unsigned long candidate_rank,
    unsigned long scheduler_credit_ns,
    unsigned long quota_credit_ns,
    unsigned long remaining_budget_ns,
    const char *process_label,
    const char *selection_class) {
    memset(entry, 0, sizeof(*entry));
    entry->selection_index = index;
    entry->selection_token = selection_token;
    entry->pid_token = pid_token;
    entry->credit_token = credit_token;
    entry->decision_token = decision_token;
    entry->switch_token = switch_token;
    entry->tick_token = tick_token;
    entry->candidate_rank = candidate_rank;
    entry->scheduler_credit_ns = scheduler_credit_ns;
    entry->quota_credit_ns = quota_credit_ns;
    entry->remaining_budget_ns = remaining_budget_ns;
    entry->candidate_declared = 1;
    selection_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    selection_copy(entry->selection_class, sizeof(entry->selection_class),
        selection_class);
    selection_copy(entry->selection_status, sizeof(entry->selection_status),
        "declared-metadata");
    selection_copy(entry->authority_status, sizeof(entry->authority_status),
        "scheduler-selection-authority-denied");
    entry->declared = 1;
    entry->compared = 0;
    entry->selected = 0;
    entry->enqueued = 0;
    entry->dispatched = 0;
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
    entry->evidence_level = 22u;
}

static void fill_selections(
    latticra_kernel_scheduler_selection_result_t *result,
    size_t requested_selection_count) {
    size_t count = requested_selection_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_SCHEDULER_SELECTION_MAX) {
        count = LATTICRA_KERNEL_SCHEDULER_SELECTION_MAX;
    }

    result->selection_count = count;
    if (count > 0u) {
        fill_selection(&result->selections[0], 0u, 0ul,
            credit_pid_for(&result->scheduler_credit, 0u, 1ul),
            credit_token_for(&result->scheduler_credit, 0u, 0ul),
            credit_decision_for(&result->scheduler_credit, 0u, 0ul),
            credit_switch_for(&result->scheduler_credit, 0u, 0ul),
            credit_tick_for(&result->scheduler_credit, 0u, 1ul),
            1ul,
            scheduler_credit_for(&result->scheduler_credit, 0u, 10000000ul),
            quota_credit_for(&result->scheduler_credit, 0u, 10000000ul),
            remaining_budget_for(&result->scheduler_credit, 0u, 10000000ul),
            credit_process_for(&result->scheduler_credit, 0u,
                "kernel-report-process-metadata"),
            "kernel-report-scheduler-selection");
    }
    if (count > 1u) {
        fill_selection(&result->selections[1], 1u, 1ul,
            credit_pid_for(&result->scheduler_credit, 1u, 2ul),
            credit_token_for(&result->scheduler_credit, 1u, 1ul),
            credit_decision_for(&result->scheduler_credit, 1u, 1ul),
            credit_switch_for(&result->scheduler_credit, 1u, 1ul),
            credit_tick_for(&result->scheduler_credit, 1u, 2ul),
            2ul,
            scheduler_credit_for(&result->scheduler_credit, 1u, 1000000ul),
            quota_credit_for(&result->scheduler_credit, 1u, 1000000ul),
            remaining_budget_for(&result->scheduler_credit, 1u, 1000000ul),
            credit_process_for(&result->scheduler_credit, 1u,
                "entropy-report-process-metadata"),
            "entropy-scheduler-selection");
    }
    if (count > 2u) {
        fill_selection(&result->selections[2], 2u, 2ul,
            credit_pid_for(&result->scheduler_credit, 2u, 3ul),
            credit_token_for(&result->scheduler_credit, 2u, 2ul),
            credit_decision_for(&result->scheduler_credit, 2u, 2ul),
            credit_switch_for(&result->scheduler_credit, 2u, 2ul),
            credit_tick_for(&result->scheduler_credit, 2u, 3ul),
            3ul,
            scheduler_credit_for(&result->scheduler_credit, 2u, 0ul),
            quota_credit_for(&result->scheduler_credit, 2u, 0ul),
            remaining_budget_for(&result->scheduler_credit, 2u, 0ul),
            credit_process_for(&result->scheduler_credit, 2u,
                "console-report-process-metadata"),
            "console-scheduler-selection");
    }
    if (count > 3u) {
        fill_selection(&result->selections[3], 3u, 3ul,
            credit_pid_for(&result->scheduler_credit, 3u, 0ul),
            credit_token_for(&result->scheduler_credit, 3u, 3ul),
            credit_decision_for(&result->scheduler_credit, 3u, 3ul),
            credit_switch_for(&result->scheduler_credit, 3u, 3ul),
            credit_tick_for(&result->scheduler_credit, 3u, 0ul),
            4ul,
            scheduler_credit_for(&result->scheduler_credit, 3u, 0ul),
            quota_credit_for(&result->scheduler_credit, 3u, 0ul),
            remaining_budget_for(&result->scheduler_credit, 3u, 0ul),
            credit_process_for(&result->scheduler_credit, 3u,
                "idle-process-metadata"),
            "idle-scheduler-selection");
    }
    for (i = 4u; i < count; ++i) {
        fill_selection(&result->selections[i], i, 10000ul + (unsigned long)i,
            credit_pid_for(&result->scheduler_credit, i,
                2000ul + (unsigned long)i),
            credit_token_for(&result->scheduler_credit, i,
                9000ul + (unsigned long)i),
            credit_decision_for(&result->scheduler_credit, i,
                8000ul + (unsigned long)i),
            credit_switch_for(&result->scheduler_credit, i,
                6000ul + (unsigned long)i),
            credit_tick_for(&result->scheduler_credit, i,
                4000ul + (unsigned long)i),
            (unsigned long)i + 1ul,
            scheduler_credit_for(&result->scheduler_credit, i, 0ul),
            quota_credit_for(&result->scheduler_credit, i, 0ul),
            remaining_budget_for(&result->scheduler_credit, i, 0ul),
            credit_process_for(&result->scheduler_credit, i,
                "reserved-process-metadata"),
            "reserved-scheduler-selection");
    }
}

latticra_status_t latticra_kernel_scheduler_selection_evaluate(
    const latticra_kernel_scheduler_selection_request_t *request,
    latticra_kernel_scheduler_selection_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        selection_copy(result->selection_status,
            sizeof(result->selection_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_credit_evaluate(
        &request->scheduler_credit_request, &result->scheduler_credit);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        selection_copy(result->selection_status,
            sizeof(result->selection_status), "scheduler-credit-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_selections(result, request->requested_selection_count);
    result->no_effect = result->scheduler_credit.no_effect;
    selection_copy(result->selection_status, sizeof(result->selection_status),
        result->no_effect ? "scheduler-selection-seed-ready" :
            "scheduler-selection-seed-blocked");
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

latticra_status_t latticra_kernel_scheduler_selection_report(
    const latticra_kernel_scheduler_selection_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER SELECTION REPORT\n"
        "selection_status=%s\n"
        "policy_status=%s\n"
        "scheduler_credit_status=%s\n"
        "preemption_status=%s\n"
        "time_accounting_status=%s\n"
        "context_switch_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "selection_count=%lu\n"
        "no_effect=%d\n"
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
        result->selection_status,
        result->policy_status,
        result->scheduler_credit.credit_status,
        result->scheduler_credit.preemption.preemption_status,
        result->scheduler_credit.preemption.time_accounting.accounting_status,
        result->scheduler_credit.preemption.time_accounting.context_switch.switch_status,
        result->scheduler_credit.preemption.time_accounting.context_switch.run_queue.queue_status,
        result->scheduler_credit.preemption.time_accounting.context_switch.run_queue.scheduler_tick.tick_status,
        result->scheduler_credit.preemption.time_accounting.context_switch.run_queue.scheduler_tick.timer_source.timer_status,
        (unsigned long)result->selection_count,
        result->no_effect,
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

    for (i = 0u; i < result->selection_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "selection[%lu].process_label=%s\n"
            "selection[%lu].selection_token=%lu\n"
            "selection[%lu].pid_token=%lu\n"
            "selection[%lu].credit_token=%lu\n"
            "selection[%lu].decision_token=%lu\n"
            "selection[%lu].switch_token=%lu\n"
            "selection[%lu].tick_token=%lu\n"
            "selection[%lu].candidate_rank=%lu\n"
            "selection[%lu].scheduler_credit_ns=%lu\n"
            "selection[%lu].quota_credit_ns=%lu\n"
            "selection[%lu].remaining_budget_ns=%lu\n"
            "selection[%lu].candidate_declared=%d\n"
            "selection[%lu].selection_class=%s\n"
            "selection[%lu].selection_status=%s\n"
            "selection[%lu].authority_status=%s\n"
            "selection[%lu].declared=%d\n"
            "selection[%lu].compared=%d\n"
            "selection[%lu].selected=%d\n"
            "selection[%lu].enqueued=%d\n"
            "selection[%lu].dispatched=%d\n"
            "selection[%lu].scheduler_selection_allowed=%d\n"
            "selection[%lu].dispatch_allowed=%d\n"
            "selection[%lu].run_queue_mutation_allowed=%d\n"
            "selection[%lu].context_switch_allowed=%d\n"
            "selection[%lu].preemption_allowed=%d\n"
            "selection[%lu].scheduler_credit_update_allowed=%d\n"
            "selection[%lu].quota_update_allowed=%d\n"
            "selection[%lu].cpu_usage_write_allowed=%d\n"
            "selection[%lu].time_accounting_allowed=%d\n"
            "selection[%lu].time_read_allowed=%d\n"
            "selection[%lu].process_wake_allowed=%d\n"
            "selection[%lu].hardware_effect_allowed=%d\n"
            "selection[%lu].host_effect_allowed=%d\n"
            "selection[%lu].no_effect=%d\n",
            (unsigned long)i, result->selections[i].process_label,
            (unsigned long)i, result->selections[i].selection_token,
            (unsigned long)i, result->selections[i].pid_token,
            (unsigned long)i, result->selections[i].credit_token,
            (unsigned long)i, result->selections[i].decision_token,
            (unsigned long)i, result->selections[i].switch_token,
            (unsigned long)i, result->selections[i].tick_token,
            (unsigned long)i, result->selections[i].candidate_rank,
            (unsigned long)i, result->selections[i].scheduler_credit_ns,
            (unsigned long)i, result->selections[i].quota_credit_ns,
            (unsigned long)i, result->selections[i].remaining_budget_ns,
            (unsigned long)i, result->selections[i].candidate_declared,
            (unsigned long)i, result->selections[i].selection_class,
            (unsigned long)i, result->selections[i].selection_status,
            (unsigned long)i, result->selections[i].authority_status,
            (unsigned long)i, result->selections[i].declared,
            (unsigned long)i, result->selections[i].compared,
            (unsigned long)i, result->selections[i].selected,
            (unsigned long)i, result->selections[i].enqueued,
            (unsigned long)i, result->selections[i].dispatched,
            (unsigned long)i, result->selections[i].scheduler_selection_allowed,
            (unsigned long)i, result->selections[i].dispatch_allowed,
            (unsigned long)i, result->selections[i].run_queue_mutation_allowed,
            (unsigned long)i, result->selections[i].context_switch_allowed,
            (unsigned long)i, result->selections[i].preemption_allowed,
            (unsigned long)i, result->selections[i].scheduler_credit_update_allowed,
            (unsigned long)i, result->selections[i].quota_update_allowed,
            (unsigned long)i, result->selections[i].cpu_usage_write_allowed,
            (unsigned long)i, result->selections[i].time_accounting_allowed,
            (unsigned long)i, result->selections[i].time_read_allowed,
            (unsigned long)i, result->selections[i].process_wake_allowed,
            (unsigned long)i, result->selections[i].hardware_effect_allowed,
            (unsigned long)i, result->selections[i].host_effect_allowed,
            (unsigned long)i, result->selections[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
