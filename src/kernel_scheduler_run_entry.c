#include "latticra/kernel_scheduler_run_entry.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void run_entry_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_scheduler_run_entry_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    run_entry_copy(result->run_entry_status, sizeof(result->run_entry_status),
        "pending");
    run_entry_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->scheduler_run_entry_allowed = 0;
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
    result->runtime_entry_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 26u;
}

latticra_status_t latticra_kernel_scheduler_run_entry_default_request(
    latticra_kernel_scheduler_run_entry_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_activation_default_request(
            &request->scheduler_activation_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_run_entry_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_scheduler_activation_entry_t *activation_at(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index) {
    if (index < scheduler_activation->activation_count &&
        scheduler_activation->activations[index].declared) {
        return &scheduler_activation->activations[index];
    }
    return 0;
}

static unsigned long activation_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->activation_token : fallback;
}

static unsigned long handoff_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->handoff_token : fallback;
}

static unsigned long dispatch_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->dispatch_token : fallback;
}

static unsigned long selection_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->selection_token : fallback;
}

static unsigned long pid_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->pid_token : fallback;
}

static unsigned long credit_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->credit_token : fallback;
}

static unsigned long decision_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->decision_token : fallback;
}

static unsigned long switch_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long tick_token_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long candidate_rank_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->candidate_rank : fallback;
}

static unsigned long dispatch_rank_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->dispatch_rank : fallback;
}

static unsigned long handoff_rank_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->handoff_rank : fallback;
}

static unsigned long activation_rank_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->activation_rank : fallback;
}

static unsigned long scheduler_credit_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->scheduler_credit_ns : fallback;
}

static unsigned long quota_credit_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->quota_credit_ns : fallback;
}

static unsigned long remaining_budget_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->remaining_budget_ns : fallback;
}

static const char *process_for(
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_activation_entry_t *entry =
        activation_at(scheduler_activation, index);
    return entry ? entry->process_label : fallback;
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-scheduler-run-entry";
        case 1u:
            return "entropy-scheduler-run-entry";
        case 2u:
            return "console-scheduler-run-entry";
        case 3u:
            return "idle-scheduler-run-entry";
        default:
            return "reserved-scheduler-run-entry";
    }
}

static unsigned long fallback_run_entry_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 14000ul + (unsigned long)index;
}

static unsigned long fallback_activation_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 13000ul + (unsigned long)index;
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

static void fill_run_entry(
    latticra_kernel_scheduler_run_entry_t *entry,
    const latticra_kernel_scheduler_activation_result_t *scheduler_activation,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->run_entry_index = index;
    entry->run_entry_token = fallback_run_entry_token(index);
    entry->activation_token = activation_token_for(scheduler_activation, index,
        fallback_activation_token(index));
    entry->handoff_token = handoff_token_for(scheduler_activation, index,
        12000ul + (unsigned long)index);
    entry->dispatch_token = dispatch_token_for(scheduler_activation, index,
        11000ul + (unsigned long)index);
    entry->selection_token = selection_token_for(scheduler_activation, index,
        10000ul + (unsigned long)index);
    entry->pid_token = pid_token_for(scheduler_activation, index,
        2000ul + (unsigned long)index);
    entry->credit_token = credit_token_for(scheduler_activation, index,
        9000ul + (unsigned long)index);
    entry->decision_token = decision_token_for(scheduler_activation, index,
        8000ul + (unsigned long)index);
    entry->switch_token = switch_token_for(scheduler_activation, index,
        6000ul + (unsigned long)index);
    entry->tick_token = tick_token_for(scheduler_activation, index,
        4000ul + (unsigned long)index);
    entry->candidate_rank = candidate_rank_for(scheduler_activation, index,
        (unsigned long)index + 1ul);
    entry->dispatch_rank = dispatch_rank_for(scheduler_activation, index,
        (unsigned long)index + 1ul);
    entry->handoff_rank = handoff_rank_for(scheduler_activation, index,
        (unsigned long)index + 1ul);
    entry->activation_rank = activation_rank_for(scheduler_activation, index,
        (unsigned long)index + 1ul);
    entry->run_entry_rank = (unsigned long)index + 1ul;
    entry->scheduler_credit_ns = scheduler_credit_for(scheduler_activation,
        index, 0ul);
    entry->quota_credit_ns = quota_credit_for(scheduler_activation, index, 0ul);
    entry->remaining_budget_ns = remaining_budget_for(scheduler_activation,
        index, 0ul);
    entry->candidate_declared = 1;
    entry->dispatch_declared = 1;
    entry->handoff_declared = 1;
    entry->activation_declared = 1;
    entry->run_entry_declared = 1;
    run_entry_copy(entry->process_label, sizeof(entry->process_label),
        process_for(scheduler_activation, index, fallback_process(index)));
    run_entry_copy(entry->run_entry_class, sizeof(entry->run_entry_class),
        class_for(index));
    run_entry_copy(entry->run_entry_status, sizeof(entry->run_entry_status),
        "declared-metadata");
    run_entry_copy(entry->authority_status, sizeof(entry->authority_status),
        "scheduler-run-entry-authority-denied");
    entry->declared = 1;
    entry->activation_planned = 0;
    entry->run_entry_planned = 0;
    entry->run_entry_prepared = 0;
    entry->handoff_planned = 0;
    entry->dispatch_planned = 0;
    entry->selected = 0;
    entry->enqueued = 0;
    entry->dequeued = 0;
    entry->dispatched = 0;
    entry->activated = 0;
    entry->context_switch_planned = 0;
    entry->execution_entered = 0;
    entry->scheduler_run_entry_allowed = 0;
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
    entry->runtime_entry_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 26u;
}

static void fill_run_entries(
    latticra_kernel_scheduler_run_entry_result_t *result,
    size_t requested_run_entry_count) {
    size_t count = requested_run_entry_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_MAX) {
        count = LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_MAX;
    }

    result->run_entry_count = count;
    for (i = 0u; i < count; ++i) {
        fill_run_entry(&result->run_entries[i],
            &result->scheduler_activation, i);
    }
}

latticra_status_t latticra_kernel_scheduler_run_entry_evaluate(
    const latticra_kernel_scheduler_run_entry_request_t *request,
    latticra_kernel_scheduler_run_entry_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        run_entry_copy(result->run_entry_status,
            sizeof(result->run_entry_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_activation_evaluate(
        &request->scheduler_activation_request, &result->scheduler_activation);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        run_entry_copy(result->run_entry_status,
            sizeof(result->run_entry_status), "scheduler-activation-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_run_entries(result, request->requested_run_entry_count);
    result->no_effect = result->scheduler_activation.no_effect;
    run_entry_copy(result->run_entry_status, sizeof(result->run_entry_status),
        result->no_effect ? "scheduler-run-entry-seed-ready" :
            "scheduler-run-entry-seed-blocked");
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

latticra_status_t latticra_kernel_scheduler_run_entry_report(
    const latticra_kernel_scheduler_run_entry_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER RUN ENTRY REPORT\n"
        "run_entry_status=%s\n"
        "policy_status=%s\n"
        "scheduler_activation_status=%s\n"
        "scheduler_handoff_status=%s\n"
        "scheduler_dispatch_status=%s\n"
        "scheduler_selection_status=%s\n"
        "scheduler_credit_status=%s\n"
        "preemption_status=%s\n"
        "time_accounting_status=%s\n"
        "context_switch_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "run_entry_count=%lu\n"
        "no_effect=%d\n"
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
        "runtime_entry_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->run_entry_status,
        result->policy_status,
        result->scheduler_activation.activation_status,
        result->scheduler_activation.scheduler_handoff.handoff_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            dispatch_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.selection_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.credit_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.preemption_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.time_accounting.
            accounting_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.time_accounting.
            context_switch.switch_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.time_accounting.
            context_switch.run_queue.queue_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.time_accounting.
            context_switch.run_queue.scheduler_tick.tick_status,
        result->scheduler_activation.scheduler_handoff.scheduler_dispatch.
            scheduler_selection.scheduler_credit.preemption.time_accounting.
            context_switch.run_queue.scheduler_tick.timer_source.timer_status,
        (unsigned long)result->run_entry_count,
        result->no_effect,
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
        result->runtime_entry_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->run_entry_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "run_entry[%lu].process_label=%s\n"
            "run_entry[%lu].run_entry_token=%lu\n"
            "run_entry[%lu].activation_token=%lu\n"
            "run_entry[%lu].handoff_token=%lu\n"
            "run_entry[%lu].dispatch_token=%lu\n"
            "run_entry[%lu].selection_token=%lu\n"
            "run_entry[%lu].pid_token=%lu\n"
            "run_entry[%lu].activation_rank=%lu\n"
            "run_entry[%lu].run_entry_rank=%lu\n"
            "run_entry[%lu].scheduler_credit_ns=%lu\n"
            "run_entry[%lu].remaining_budget_ns=%lu\n"
            "run_entry[%lu].activation_declared=%d\n"
            "run_entry[%lu].run_entry_declared=%d\n"
            "run_entry[%lu].run_entry_class=%s\n"
            "run_entry[%lu].run_entry_status=%s\n"
            "run_entry[%lu].authority_status=%s\n"
            "run_entry[%lu].activation_planned=%d\n"
            "run_entry[%lu].run_entry_planned=%d\n"
            "run_entry[%lu].run_entry_prepared=%d\n"
            "run_entry[%lu].activated=%d\n"
            "run_entry[%lu].execution_entered=%d\n"
            "run_entry[%lu].context_switch_planned=%d\n"
            "run_entry[%lu].scheduler_run_entry_allowed=%d\n"
            "run_entry[%lu].scheduler_activation_allowed=%d\n"
            "run_entry[%lu].scheduler_handoff_allowed=%d\n"
            "run_entry[%lu].dispatch_allowed=%d\n"
            "run_entry[%lu].run_queue_mutation_allowed=%d\n"
            "run_entry[%lu].context_switch_allowed=%d\n"
            "run_entry[%lu].runtime_entry_allowed=%d\n"
            "run_entry[%lu].hardware_effect_allowed=%d\n"
            "run_entry[%lu].host_effect_allowed=%d\n"
            "run_entry[%lu].no_effect=%d\n",
            (unsigned long)i, result->run_entries[i].process_label,
            (unsigned long)i, result->run_entries[i].run_entry_token,
            (unsigned long)i, result->run_entries[i].activation_token,
            (unsigned long)i, result->run_entries[i].handoff_token,
            (unsigned long)i, result->run_entries[i].dispatch_token,
            (unsigned long)i, result->run_entries[i].selection_token,
            (unsigned long)i, result->run_entries[i].pid_token,
            (unsigned long)i, result->run_entries[i].activation_rank,
            (unsigned long)i, result->run_entries[i].run_entry_rank,
            (unsigned long)i, result->run_entries[i].scheduler_credit_ns,
            (unsigned long)i, result->run_entries[i].remaining_budget_ns,
            (unsigned long)i, result->run_entries[i].activation_declared,
            (unsigned long)i, result->run_entries[i].run_entry_declared,
            (unsigned long)i, result->run_entries[i].run_entry_class,
            (unsigned long)i, result->run_entries[i].run_entry_status,
            (unsigned long)i, result->run_entries[i].authority_status,
            (unsigned long)i, result->run_entries[i].activation_planned,
            (unsigned long)i, result->run_entries[i].run_entry_planned,
            (unsigned long)i, result->run_entries[i].run_entry_prepared,
            (unsigned long)i, result->run_entries[i].activated,
            (unsigned long)i, result->run_entries[i].execution_entered,
            (unsigned long)i, result->run_entries[i].context_switch_planned,
            (unsigned long)i, result->run_entries[i].scheduler_run_entry_allowed,
            (unsigned long)i,
            result->run_entries[i].scheduler_activation_allowed,
            (unsigned long)i, result->run_entries[i].scheduler_handoff_allowed,
            (unsigned long)i, result->run_entries[i].dispatch_allowed,
            (unsigned long)i, result->run_entries[i].run_queue_mutation_allowed,
            (unsigned long)i, result->run_entries[i].context_switch_allowed,
            (unsigned long)i, result->run_entries[i].runtime_entry_allowed,
            (unsigned long)i, result->run_entries[i].hardware_effect_allowed,
            (unsigned long)i, result->run_entries[i].host_effect_allowed,
            (unsigned long)i, result->run_entries[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
