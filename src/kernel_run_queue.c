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
    queue_copy(result->policy_status, sizeof(result->policy_status), "report-only");
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
    if (latticra_kernel_scheduler_tick_default_request(&request->scheduler_tick_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_queue_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_queue(
    latticra_kernel_run_queue_entry_t *queue,
    size_t index,
    unsigned long queue_token,
    unsigned long pid_token,
    unsigned long tick_token,
    unsigned long priority,
    const char *process_label,
    const char *scheduler_slot_label,
    const char *queue_class) {
    memset(queue, 0, sizeof(*queue));
    queue->queue_index = index;
    queue->queue_token = queue_token;
    queue->pid_token = pid_token;
    queue->tick_token = tick_token;
    queue->priority = priority;
    queue_copy(queue->process_label, sizeof(queue->process_label), process_label);
    queue_copy(queue->scheduler_slot_label, sizeof(queue->scheduler_slot_label),
        scheduler_slot_label);
    queue_copy(queue->queue_class, sizeof(queue->queue_class), queue_class);
    queue_copy(queue->queue_status, sizeof(queue->queue_status), "declared-metadata");
    queue_copy(queue->authority_status, sizeof(queue->authority_status),
        "run-queue-authority-denied");
    queue->declared = 1;
    queue->enqueued = 0;
    queue->dequeued = 0;
    queue->selected = 0;
    queue->run_queue_mutation_allowed = 0;
    queue->enqueue_allowed = 0;
    queue->dequeue_allowed = 0;
    queue->dispatch_allowed = 0;
    queue->context_switch_allowed = 0;
    queue->preemption_allowed = 0;
    queue->time_accounting_allowed = 0;
    queue->process_wake_allowed = 0;
    queue->hardware_effect_allowed = 0;
    queue->host_effect_allowed = 0;
    queue->no_effect = 1;
    queue->evidence_level = 17u;
}

static const char *tick_process_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    const char *fallback) {
    if (index < scheduler_tick->tick_count && scheduler_tick->ticks[index].declared) {
        return scheduler_tick->ticks[index].process_label;
    }
    return fallback;
}

static const char *tick_slot_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    const char *fallback) {
    if (index < scheduler_tick->tick_count && scheduler_tick->ticks[index].declared) {
        return scheduler_tick->ticks[index].scheduler_slot_label;
    }
    return fallback;
}

static unsigned long tick_token_for(
    const latticra_kernel_scheduler_tick_result_t *scheduler_tick,
    size_t index,
    unsigned long fallback) {
    if (index < scheduler_tick->tick_count && scheduler_tick->ticks[index].declared) {
        return scheduler_tick->ticks[index].tick_token;
    }
    return fallback;
}

static void fill_queues(
    latticra_kernel_run_queue_result_t *result,
    size_t requested_queue_count) {
    size_t count = requested_queue_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUN_QUEUE_ENTRY_MAX) {
        count = LATTICRA_KERNEL_RUN_QUEUE_ENTRY_MAX;
    }

    result->queue_count = count;
    if (count > 0u) {
        fill_queue(&result->queues[0], 0u, 0ul, 0ul,
            tick_token_for(&result->scheduler_tick, 0u, 0ul),
            0ul,
            tick_process_for(&result->scheduler_tick, 0u, "idle-process-metadata"),
            tick_slot_for(&result->scheduler_tick, 0u, "idle-metadata"),
            "idle-run-queue");
    }
    if (count > 1u) {
        fill_queue(&result->queues[1], 1u, 1ul, 1ul,
            tick_token_for(&result->scheduler_tick, 1u, 1ul),
            10ul,
            tick_process_for(&result->scheduler_tick, 1u,
                "kernel-report-process-metadata"),
            tick_slot_for(&result->scheduler_tick, 1u, "kernel-report-metadata"),
            "kernel-report-run-queue");
    }
    if (count > 2u) {
        fill_queue(&result->queues[2], 2u, 2ul, 2ul,
            tick_token_for(&result->scheduler_tick, 2u, 2ul),
            20ul,
            tick_process_for(&result->scheduler_tick, 2u,
                "entropy-report-process-metadata"),
            tick_slot_for(&result->scheduler_tick, 2u, "operator-report-metadata"),
            "entropy-run-queue");
    }
    if (count > 3u) {
        fill_queue(&result->queues[3], 3u, 3ul, 3ul,
            tick_token_for(&result->scheduler_tick, 3u, 3ul),
            30ul,
            tick_process_for(&result->scheduler_tick, 3u,
                "console-report-process-metadata"),
            tick_slot_for(&result->scheduler_tick, 3u, "operator-report-metadata"),
            "console-run-queue");
    }
    for (i = 4u; i < count; ++i) {
        fill_queue(&result->queues[i], i, 5000ul + (unsigned long)i,
            1000ul + (unsigned long)i,
            tick_token_for(&result->scheduler_tick, i, 4000ul + (unsigned long)i),
            100ul,
            tick_process_for(&result->scheduler_tick, i, "reserved-process-metadata"),
            tick_slot_for(&result->scheduler_tick, i, "reserved-metadata"),
            "reserved-run-queue");
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
        queue_copy(result->queue_status, sizeof(result->queue_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_tick_evaluate(&request->scheduler_tick_request,
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
        result->no_effect ? "run-queue-seed-ready" : "run-queue-seed-blocked");
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
        "interrupt_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "scheduler_status=%s\n"
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
        result->scheduler_tick.timer_source.interrupt_table.table_status,
        result->scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        result->scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.scheduler.scheduler_status,
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
            "queue[%lu].queue_token=%lu\n"
            "queue[%lu].pid_token=%lu\n"
            "queue[%lu].tick_token=%lu\n"
            "queue[%lu].priority=%lu\n"
            "queue[%lu].scheduler_slot_label=%s\n"
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
            (unsigned long)i, result->queues[i].queue_token,
            (unsigned long)i, result->queues[i].pid_token,
            (unsigned long)i, result->queues[i].tick_token,
            (unsigned long)i, result->queues[i].priority,
            (unsigned long)i, result->queues[i].scheduler_slot_label,
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
