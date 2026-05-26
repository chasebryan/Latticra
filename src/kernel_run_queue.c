#include "latticra/kernel_run_queue.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void queue_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_run_queue_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    queue_copy(result->queue_status, sizeof(result->queue_status), "pending");
    queue_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->run_queue_mutation_allowed = 0;
    result->enqueue_allowed = 0;
    result->dequeue_allowed = 0;
    result->dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 17u;
}

latticra_status_t latticra_kernel_run_queue_default_request(
    latticra_kernel_run_queue_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_tick_default_request(
            &request->scheduler_tick_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_queue_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_queue(
    latticra_kernel_run_queue_entry_t *entry,
    size_t index,
    unsigned long queue_token,
    unsigned long pid_token,
    unsigned long tick_token,
    unsigned long timer_token,
    unsigned long irq_vector,
    unsigned long priority,
    unsigned long budget_ns,
    const char *scheduler_slot_label,
    const char *process_label,
    const char *queue_class) {
    memset(entry, 0, sizeof(*entry));
    entry->queue_index = index;
    entry->queue_token = queue_token;
    entry->pid_token = pid_token;
    entry->tick_token = tick_token;
    entry->timer_token = timer_token;
    entry->irq_vector = irq_vector;
    entry->priority = priority;
    entry->budget_ns = budget_ns;
    queue_copy(entry->scheduler_slot_label, sizeof(entry->scheduler_slot_label),
        scheduler_slot_label);
    queue_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    queue_copy(entry->queue_class, sizeof(entry->queue_class), queue_class);
    queue_copy(entry->queue_status, sizeof(entry->queue_status),
        "declared-metadata");
    queue_copy(entry->authority_status, sizeof(entry->authority_status),
        "run-queue-authority-denied");
    entry->declared = 1;
    entry->enqueued = 0;
    entry->dequeued = 0;
    entry->selected = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->enqueue_allowed = 0;
    entry->dequeue_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->preemption_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 17u;
}

static const latticra_kernel_scheduler_tick_entry_t *tick_at(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index) {
    if (index < scheduler_tick->tick_count &&
        scheduler_tick->ticks[index].declared) {
        return &scheduler_tick->ticks[index];
    }
    return 0;
}

static unsigned long tick_token_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long timer_token_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->timer_token : fallback;
}

static unsigned long irq_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->irq_vector : fallback;
}

static unsigned long budget_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->budget_ns : fallback;
}

static const char *slot_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->scheduler_slot_label : fallback;
}

static const char *process_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    const char *fallback) {
    const latticra_kernel_scheduler_tick_entry_t *entry =
        tick_at(scheduler_tick, index);
    return entry ? entry->process_label : fallback;
}

static void fill_queues(
    latticra_kernel_run_queue_result_t *result,
    size_t requested_queue_count) {
    size_t count = requested_queue_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUN_QUEUE_MAX) {
        count = LATTICRA_KERNEL_RUN_QUEUE_MAX;
    }

    result->queue_count = count;
    if (count > 0u) {
        fill_queue(&result->queues[0], 0u, 0ul, 1ul,
            tick_token_for(&result->scheduler_tick, 1u, 1ul),
            timer_token_for(&result->scheduler_tick, 1u, 1ul),
            irq_for(&result->scheduler_tick, 1u, 35ul),
            10ul,
            budget_for(&result->scheduler_tick, 1u, 1000000ul),
            slot_for(&result->scheduler_tick, 1u, "kernel-report-metadata"),
            process_for(&result->scheduler_tick, 1u,
                "kernel-report-process-metadata"),
            "kernel-report-run-queue-entry");
    }
    if (count > 1u) {
        fill_queue(&result->queues[1], 1u, 1ul, 2ul,
            tick_token_for(&result->scheduler_tick, 2u, 2ul),
            timer_token_for(&result->scheduler_tick, 2u, 2ul),
            irq_for(&result->scheduler_tick, 2u, 34ul),
            20ul,
            budget_for(&result->scheduler_tick, 2u, 0ul),
            slot_for(&result->scheduler_tick, 2u, "operator-report-metadata"),
            process_for(&result->scheduler_tick, 2u,
                "entropy-report-process-metadata"),
            "entropy-run-queue-entry");
    }
    if (count > 2u) {
        fill_queue(&result->queues[2], 2u, 2ul, 3ul,
            tick_token_for(&result->scheduler_tick, 3u, 3ul),
            timer_token_for(&result->scheduler_tick, 3u, 3ul),
            irq_for(&result->scheduler_tick, 3u, 32ul),
            30ul,
            budget_for(&result->scheduler_tick, 3u, 0ul),
            slot_for(&result->scheduler_tick, 3u, "operator-report-metadata"),
            process_for(&result->scheduler_tick, 3u,
                "console-report-process-metadata"),
            "console-run-queue-entry");
    }
    if (count > 3u) {
        fill_queue(&result->queues[3], 3u, 3ul, 0ul,
            tick_token_for(&result->scheduler_tick, 0u, 0ul),
            timer_token_for(&result->scheduler_tick, 0u, 0ul),
            irq_for(&result->scheduler_tick, 0u, 35ul),
            0ul,
            budget_for(&result->scheduler_tick, 0u, 10000000ul),
            slot_for(&result->scheduler_tick, 0u, "idle-metadata"),
            process_for(&result->scheduler_tick, 0u,
                "idle-process-metadata"),
            "idle-run-queue-entry");
    }
    for (i = 4u; i < count; ++i) {
        fill_queue(&result->queues[i], i, 5000ul + (unsigned long)i,
            2000ul + (unsigned long)i,
            tick_token_for(&result->scheduler_tick, i,
                4000ul + (unsigned long)i),
            timer_token_for(&result->scheduler_tick, i,
                3000ul + (unsigned long)i),
            irq_for(&result->scheduler_tick, i, 128ul + (unsigned long)i),
            0ul,
            budget_for(&result->scheduler_tick, i, 0ul),
            slot_for(&result->scheduler_tick, i, "reserved-metadata"),
            process_for(&result->scheduler_tick, i,
                "reserved-process-metadata"),
            "reserved-run-queue-entry");
    }
}

latticra_status_t latticra_kernel_run_queue_evaluate(
    const latticra_kernel_run_queue_request_t *request,
    latticra_kernel_run_queue_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        queue_copy(result->queue_status, sizeof(result->queue_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_tick_evaluate(
        &request->scheduler_tick_request,
        &result->scheduler_tick);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        queue_copy(result->queue_status, sizeof(result->queue_status),
            "scheduler-tick-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_queues(result, request->requested_queue_count);
    result->no_effect = result->scheduler_tick.no_effect;
    queue_copy(result->queue_status, sizeof(result->queue_status),
        result->no_effect ? "run-queue-seed-ready" :
            "run-queue-seed-blocked");
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

latticra_status_t latticra_kernel_run_queue_report(
    const latticra_kernel_run_queue_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUN QUEUE REPORT\n"
        "queue_status=%s\n"
        "policy_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "queue_count=%lu\n"
        "no_effect=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "enqueue_allowed=%d\n"
        "dequeue_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->queue_status,
        result->policy_status,
        result->scheduler_tick.tick_status,
        result->scheduler_tick.timer_source.timer_status,
        (unsigned long)result->queue_count,
        result->no_effect,
        result->run_queue_mutation_allowed,
        result->enqueue_allowed,
        result->dequeue_allowed,
        result->dispatch_allowed,
        result->context_switch_allowed,
        result->preemption_allowed,
        result->time_accounting_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->queue_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "queue[%lu].process_label=%s\n"
            "queue[%lu].scheduler_slot_label=%s\n"
            "queue[%lu].queue_token=%lu\n"
            "queue[%lu].pid_token=%lu\n"
            "queue[%lu].tick_token=%lu\n"
            "queue[%lu].timer_token=%lu\n"
            "queue[%lu].irq_vector=%lu\n"
            "queue[%lu].priority=%lu\n"
            "queue[%lu].budget_ns=%lu\n"
            "queue[%lu].queue_class=%s\n"
            "queue[%lu].queue_status=%s\n"
            "queue[%lu].authority_status=%s\n"
            "queue[%lu].declared=%d\n"
            "queue[%lu].enqueued=%d\n"
            "queue[%lu].dequeued=%d\n"
            "queue[%lu].selected=%d\n"
            "queue[%lu].run_queue_mutation_allowed=%d\n"
            "queue[%lu].enqueue_allowed=%d\n"
            "queue[%lu].dequeue_allowed=%d\n"
            "queue[%lu].dispatch_allowed=%d\n"
            "queue[%lu].context_switch_allowed=%d\n"
            "queue[%lu].preemption_allowed=%d\n"
            "queue[%lu].time_accounting_allowed=%d\n"
            "queue[%lu].process_wake_allowed=%d\n"
            "queue[%lu].hardware_effect_allowed=%d\n"
            "queue[%lu].host_effect_allowed=%d\n"
            "queue[%lu].no_effect=%d\n",
            (unsigned long)i, result->queues[i].process_label,
            (unsigned long)i, result->queues[i].scheduler_slot_label,
            (unsigned long)i, result->queues[i].queue_token,
            (unsigned long)i, result->queues[i].pid_token,
            (unsigned long)i, result->queues[i].tick_token,
            (unsigned long)i, result->queues[i].timer_token,
            (unsigned long)i, result->queues[i].irq_vector,
            (unsigned long)i, result->queues[i].priority,
            (unsigned long)i, result->queues[i].budget_ns,
            (unsigned long)i, result->queues[i].queue_class,
            (unsigned long)i, result->queues[i].queue_status,
            (unsigned long)i, result->queues[i].authority_status,
            (unsigned long)i, result->queues[i].declared,
            (unsigned long)i, result->queues[i].enqueued,
            (unsigned long)i, result->queues[i].dequeued,
            (unsigned long)i, result->queues[i].selected,
            (unsigned long)i, result->queues[i].run_queue_mutation_allowed,
            (unsigned long)i, result->queues[i].enqueue_allowed,
            (unsigned long)i, result->queues[i].dequeue_allowed,
            (unsigned long)i, result->queues[i].dispatch_allowed,
            (unsigned long)i, result->queues[i].context_switch_allowed,
            (unsigned long)i, result->queues[i].preemption_allowed,
            (unsigned long)i, result->queues[i].time_accounting_allowed,
            (unsigned long)i, result->queues[i].process_wake_allowed,
            (unsigned long)i, result->queues[i].hardware_effect_allowed,
            (unsigned long)i, result->queues[i].host_effect_allowed,
            (unsigned long)i, result->queues[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
