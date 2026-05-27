#include "latticra/kernel_scheduler_activation.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void activation_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_scheduler_activation_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    activation_copy(result->activation_status, sizeof(result->activation_status),
        "pending");
    activation_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
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
    result->evidence_level = 25u;
}

latticra_status_t latticra_kernel_scheduler_activation_default_request(
    latticra_kernel_scheduler_activation_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_handoff_default_request(
            &request->scheduler_handoff_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_activation_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_scheduler_handoff_entry_t *handoff_at(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index) {
    if (index < scheduler_handoff->handoff_count &&
        scheduler_handoff->handoffs[index].declared) {
        return &scheduler_handoff->handoffs[index];
    }
    return 0;
}

static unsigned long handoff_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->handoff_token : fallback;
}

static unsigned long dispatch_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->dispatch_token : fallback;
}

static unsigned long selection_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->selection_token : fallback;
}

static unsigned long pid_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->pid_token : fallback;
}

static unsigned long credit_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->credit_token : fallback;
}

static unsigned long decision_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->decision_token : fallback;
}

static unsigned long switch_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long tick_token_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long candidate_rank_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->candidate_rank : fallback;
}

static unsigned long dispatch_rank_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->dispatch_rank : fallback;
}

static unsigned long handoff_rank_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->handoff_rank : fallback;
}

static unsigned long scheduler_credit_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->scheduler_credit_ns : fallback;
}

static unsigned long quota_credit_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->quota_credit_ns : fallback;
}

static unsigned long remaining_budget_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->remaining_budget_ns : fallback;
}

static const char *process_for(
    const latticra_kernel_scheduler_handoff_result_t *scheduler_handoff,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_handoff_entry_t *entry =
        handoff_at(scheduler_handoff, index);
    return entry ? entry->process_label : fallback;
}

static void fill_activation(
    latticra_kernel_scheduler_activation_entry_t *entry,
    size_t index,
    unsigned long activation_token,
    unsigned long handoff_token,
    unsigned long dispatch_token,
    unsigned long selection_token,
    unsigned long pid_token,
    unsigned long credit_token,
    unsigned long decision_token,
    unsigned long switch_token,
    unsigned long tick_token,
    unsigned long candidate_rank,
    unsigned long dispatch_rank,
    unsigned long handoff_rank,
    unsigned long activation_rank,
    unsigned long scheduler_credit_ns,
    unsigned long quota_credit_ns,
    unsigned long remaining_budget_ns,
    const char *process_label,
    const char *activation_class) {
    memset(entry, 0, sizeof(*entry));
    entry->activation_index = index;
    entry->activation_token = activation_token;
    entry->handoff_token = handoff_token;
    entry->dispatch_token = dispatch_token;
    entry->selection_token = selection_token;
    entry->pid_token = pid_token;
    entry->credit_token = credit_token;
    entry->decision_token = decision_token;
    entry->switch_token = switch_token;
    entry->tick_token = tick_token;
    entry->candidate_rank = candidate_rank;
    entry->dispatch_rank = dispatch_rank;
    entry->handoff_rank = handoff_rank;
    entry->activation_rank = activation_rank;
    entry->scheduler_credit_ns = scheduler_credit_ns;
    entry->quota_credit_ns = quota_credit_ns;
    entry->remaining_budget_ns = remaining_budget_ns;
    entry->candidate_declared = 1;
    entry->dispatch_declared = 1;
    entry->handoff_declared = 1;
    entry->activation_declared = 1;
    activation_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    activation_copy(entry->activation_class, sizeof(entry->activation_class),
        activation_class);
    activation_copy(entry->activation_status, sizeof(entry->activation_status),
        "declared-metadata");
    activation_copy(entry->authority_status, sizeof(entry->authority_status),
        "scheduler-activation-authority-denied");
    entry->declared = 1;
    entry->activation_planned = 0;
    entry->handoff_planned = 0;
    entry->dispatch_planned = 0;
    entry->selected = 0;
    entry->enqueued = 0;
    entry->dequeued = 0;
    entry->dispatched = 0;
    entry->activated = 0;
    entry->context_switch_planned = 0;
    entry->execution_entered = 0;
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
    entry->evidence_level = 25u;
}

static void fill_activations(
    latticra_kernel_scheduler_activation_result_t *result,
    size_t requested_activation_count) {
    size_t count = requested_activation_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_SCHEDULER_ACTIVATION_MAX) {
        count = LATTICRA_KERNEL_SCHEDULER_ACTIVATION_MAX;
    }

    result->activation_count = count;
    if (count > 0u) {
        fill_activation(&result->activations[0], 0u, 0ul,
            handoff_token_for(&result->scheduler_handoff, 0u, 0ul),
            dispatch_token_for(&result->scheduler_handoff, 0u, 0ul),
            selection_token_for(&result->scheduler_handoff, 0u, 0ul),
            pid_token_for(&result->scheduler_handoff, 0u, 1ul),
            credit_token_for(&result->scheduler_handoff, 0u, 0ul),
            decision_token_for(&result->scheduler_handoff, 0u, 0ul),
            switch_token_for(&result->scheduler_handoff, 0u, 0ul),
            tick_token_for(&result->scheduler_handoff, 0u, 1ul),
            candidate_rank_for(&result->scheduler_handoff, 0u, 1ul),
            dispatch_rank_for(&result->scheduler_handoff, 0u, 1ul),
            handoff_rank_for(&result->scheduler_handoff, 0u, 1ul), 1ul,
            scheduler_credit_for(&result->scheduler_handoff, 0u, 10000000ul),
            quota_credit_for(&result->scheduler_handoff, 0u, 10000000ul),
            remaining_budget_for(&result->scheduler_handoff, 0u, 10000000ul),
            process_for(&result->scheduler_handoff, 0u,
                "kernel-report-process-metadata"),
            "kernel-report-scheduler-activation");
    }
    if (count > 1u) {
        fill_activation(&result->activations[1], 1u, 1ul,
            handoff_token_for(&result->scheduler_handoff, 1u, 1ul),
            dispatch_token_for(&result->scheduler_handoff, 1u, 1ul),
            selection_token_for(&result->scheduler_handoff, 1u, 1ul),
            pid_token_for(&result->scheduler_handoff, 1u, 2ul),
            credit_token_for(&result->scheduler_handoff, 1u, 1ul),
            decision_token_for(&result->scheduler_handoff, 1u, 1ul),
            switch_token_for(&result->scheduler_handoff, 1u, 1ul),
            tick_token_for(&result->scheduler_handoff, 1u, 2ul),
            candidate_rank_for(&result->scheduler_handoff, 1u, 2ul),
            dispatch_rank_for(&result->scheduler_handoff, 1u, 2ul),
            handoff_rank_for(&result->scheduler_handoff, 1u, 2ul), 2ul,
            scheduler_credit_for(&result->scheduler_handoff, 1u, 1000000ul),
            quota_credit_for(&result->scheduler_handoff, 1u, 1000000ul),
            remaining_budget_for(&result->scheduler_handoff, 1u, 1000000ul),
            process_for(&result->scheduler_handoff, 1u,
                "entropy-report-process-metadata"),
            "entropy-scheduler-activation");
    }
    if (count > 2u) {
        fill_activation(&result->activations[2], 2u, 2ul,
            handoff_token_for(&result->scheduler_handoff, 2u, 2ul),
            dispatch_token_for(&result->scheduler_handoff, 2u, 2ul),
            selection_token_for(&result->scheduler_handoff, 2u, 2ul),
            pid_token_for(&result->scheduler_handoff, 2u, 3ul),
            credit_token_for(&result->scheduler_handoff, 2u, 2ul),
            decision_token_for(&result->scheduler_handoff, 2u, 2ul),
            switch_token_for(&result->scheduler_handoff, 2u, 2ul),
            tick_token_for(&result->scheduler_handoff, 2u, 3ul),
            candidate_rank_for(&result->scheduler_handoff, 2u, 3ul),
            dispatch_rank_for(&result->scheduler_handoff, 2u, 3ul),
            handoff_rank_for(&result->scheduler_handoff, 2u, 3ul), 3ul,
            scheduler_credit_for(&result->scheduler_handoff, 2u, 0ul),
            quota_credit_for(&result->scheduler_handoff, 2u, 0ul),
            remaining_budget_for(&result->scheduler_handoff, 2u, 0ul),
            process_for(&result->scheduler_handoff, 2u,
                "console-report-process-metadata"),
            "console-scheduler-activation");
    }
    if (count > 3u) {
        fill_activation(&result->activations[3], 3u, 3ul,
            handoff_token_for(&result->scheduler_handoff, 3u, 3ul),
            dispatch_token_for(&result->scheduler_handoff, 3u, 3ul),
            selection_token_for(&result->scheduler_handoff, 3u, 3ul),
            pid_token_for(&result->scheduler_handoff, 3u, 0ul),
            credit_token_for(&result->scheduler_handoff, 3u, 3ul),
            decision_token_for(&result->scheduler_handoff, 3u, 3ul),
            switch_token_for(&result->scheduler_handoff, 3u, 3ul),
            tick_token_for(&result->scheduler_handoff, 3u, 0ul),
            candidate_rank_for(&result->scheduler_handoff, 3u, 4ul),
            dispatch_rank_for(&result->scheduler_handoff, 3u, 4ul),
            handoff_rank_for(&result->scheduler_handoff, 3u, 4ul), 4ul,
            scheduler_credit_for(&result->scheduler_handoff, 3u, 0ul),
            quota_credit_for(&result->scheduler_handoff, 3u, 0ul),
            remaining_budget_for(&result->scheduler_handoff, 3u, 0ul),
            process_for(&result->scheduler_handoff, 3u,
                "idle-process-metadata"),
            "idle-scheduler-activation");
    }
    for (i = 4u; i < count; ++i) {
        fill_activation(&result->activations[i], i, 13000ul + (unsigned long)i,
            handoff_token_for(&result->scheduler_handoff, i,
                12000ul + (unsigned long)i),
            dispatch_token_for(&result->scheduler_handoff, i,
                11000ul + (unsigned long)i),
            selection_token_for(&result->scheduler_handoff, i,
                10000ul + (unsigned long)i),
            pid_token_for(&result->scheduler_handoff, i,
                2000ul + (unsigned long)i),
            credit_token_for(&result->scheduler_handoff, i,
                9000ul + (unsigned long)i),
            decision_token_for(&result->scheduler_handoff, i,
                8000ul + (unsigned long)i),
            switch_token_for(&result->scheduler_handoff, i,
                6000ul + (unsigned long)i),
            tick_token_for(&result->scheduler_handoff, i,
                4000ul + (unsigned long)i),
            candidate_rank_for(&result->scheduler_handoff, i,
                (unsigned long)i + 1ul),
            dispatch_rank_for(&result->scheduler_handoff, i,
                (unsigned long)i + 1ul),
            handoff_rank_for(&result->scheduler_handoff, i,
                (unsigned long)i + 1ul),
            (unsigned long)i + 1ul,
            scheduler_credit_for(&result->scheduler_handoff, i, 0ul),
            quota_credit_for(&result->scheduler_handoff, i, 0ul),
            remaining_budget_for(&result->scheduler_handoff, i, 0ul),
            process_for(&result->scheduler_handoff, i,
                "reserved-process-metadata"),
            "reserved-scheduler-activation");
    }
}

latticra_status_t latticra_kernel_scheduler_activation_evaluate(
    const latticra_kernel_scheduler_activation_request_t *request,
    latticra_kernel_scheduler_activation_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        activation_copy(result->activation_status,
            sizeof(result->activation_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_handoff_evaluate(
        &request->scheduler_handoff_request, &result->scheduler_handoff);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        activation_copy(result->activation_status,
            sizeof(result->activation_status), "scheduler-handoff-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_activations(result, request->requested_activation_count);
    result->no_effect = result->scheduler_handoff.no_effect;
    activation_copy(result->activation_status, sizeof(result->activation_status),
        result->no_effect ? "scheduler-activation-seed-ready" :
            "scheduler-activation-seed-blocked");
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

latticra_status_t latticra_kernel_scheduler_activation_report(
    const latticra_kernel_scheduler_activation_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER ACTIVATION REPORT\n"
        "activation_status=%s\n"
        "policy_status=%s\n"
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
        "activation_count=%lu\n"
        "no_effect=%d\n"
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
        result->activation_status,
        result->policy_status,
        result->scheduler_handoff.handoff_status,
        result->scheduler_handoff.scheduler_dispatch.dispatch_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            selection_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.credit_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.preemption_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.time_accounting.accounting_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.time_accounting.context_switch.
            switch_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.time_accounting.context_switch.
            run_queue.queue_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.time_accounting.context_switch.
            run_queue.scheduler_tick.tick_status,
        result->scheduler_handoff.scheduler_dispatch.scheduler_selection.
            scheduler_credit.preemption.time_accounting.context_switch.
            run_queue.scheduler_tick.timer_source.timer_status,
        (unsigned long)result->activation_count,
        result->no_effect,
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

    for (i = 0u; i < result->activation_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "activation[%lu].process_label=%s\n"
            "activation[%lu].activation_token=%lu\n"
            "activation[%lu].handoff_token=%lu\n"
            "activation[%lu].dispatch_token=%lu\n"
            "activation[%lu].selection_token=%lu\n"
            "activation[%lu].pid_token=%lu\n"
            "activation[%lu].activation_rank=%lu\n"
            "activation[%lu].scheduler_credit_ns=%lu\n"
            "activation[%lu].remaining_budget_ns=%lu\n"
            "activation[%lu].activation_declared=%d\n"
            "activation[%lu].activation_class=%s\n"
            "activation[%lu].activation_status=%s\n"
            "activation[%lu].authority_status=%s\n"
            "activation[%lu].activation_planned=%d\n"
            "activation[%lu].activated=%d\n"
            "activation[%lu].execution_entered=%d\n"
            "activation[%lu].context_switch_planned=%d\n"
            "activation[%lu].scheduler_activation_allowed=%d\n"
            "activation[%lu].scheduler_handoff_allowed=%d\n"
            "activation[%lu].dispatch_allowed=%d\n"
            "activation[%lu].run_queue_mutation_allowed=%d\n"
            "activation[%lu].context_switch_allowed=%d\n"
            "activation[%lu].runtime_entry_allowed=%d\n"
            "activation[%lu].hardware_effect_allowed=%d\n"
            "activation[%lu].host_effect_allowed=%d\n"
            "activation[%lu].no_effect=%d\n",
            (unsigned long)i, result->activations[i].process_label,
            (unsigned long)i, result->activations[i].activation_token,
            (unsigned long)i, result->activations[i].handoff_token,
            (unsigned long)i, result->activations[i].dispatch_token,
            (unsigned long)i, result->activations[i].selection_token,
            (unsigned long)i, result->activations[i].pid_token,
            (unsigned long)i, result->activations[i].activation_rank,
            (unsigned long)i, result->activations[i].scheduler_credit_ns,
            (unsigned long)i, result->activations[i].remaining_budget_ns,
            (unsigned long)i, result->activations[i].activation_declared,
            (unsigned long)i, result->activations[i].activation_class,
            (unsigned long)i, result->activations[i].activation_status,
            (unsigned long)i, result->activations[i].authority_status,
            (unsigned long)i, result->activations[i].activation_planned,
            (unsigned long)i, result->activations[i].activated,
            (unsigned long)i, result->activations[i].execution_entered,
            (unsigned long)i, result->activations[i].context_switch_planned,
            (unsigned long)i,
            result->activations[i].scheduler_activation_allowed,
            (unsigned long)i, result->activations[i].scheduler_handoff_allowed,
            (unsigned long)i, result->activations[i].dispatch_allowed,
            (unsigned long)i, result->activations[i].run_queue_mutation_allowed,
            (unsigned long)i, result->activations[i].context_switch_allowed,
            (unsigned long)i, result->activations[i].runtime_entry_allowed,
            (unsigned long)i, result->activations[i].hardware_effect_allowed,
            (unsigned long)i, result->activations[i].host_effect_allowed,
            (unsigned long)i, result->activations[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
