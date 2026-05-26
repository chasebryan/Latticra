#include "latticra/kernel_context_switch.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void switch_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_context_switch_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    switch_copy(result->switch_status, sizeof(result->switch_status), "pending");
    switch_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->context_switch_allowed = 0;
    result->register_save_allowed = 0;
    result->register_restore_allowed = 0;
    result->stack_switch_allowed = 0;
    result->address_space_switch_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 18u;
}

latticra_status_t latticra_kernel_context_switch_default_request(
    latticra_kernel_context_switch_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_run_queue_default_request(&request->run_queue_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_switch_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_switch(
    latticra_kernel_context_switch_entry_t *entry,
    size_t index,
    unsigned long switch_token,
    unsigned long from_pid_token,
    unsigned long to_pid_token,
    unsigned long queue_token,
    unsigned long tick_token,
    unsigned long priority,
    const char *from_process_label,
    const char *to_process_label,
    const char *scheduler_slot_label,
    const char *switch_class) {
    memset(entry, 0, sizeof(*entry));
    entry->switch_index = index;
    entry->switch_token = switch_token;
    entry->from_pid_token = from_pid_token;
    entry->to_pid_token = to_pid_token;
    entry->queue_token = queue_token;
    entry->tick_token = tick_token;
    entry->priority = priority;
    switch_copy(entry->from_process_label, sizeof(entry->from_process_label),
        from_process_label);
    switch_copy(entry->to_process_label, sizeof(entry->to_process_label),
        to_process_label);
    switch_copy(entry->scheduler_slot_label, sizeof(entry->scheduler_slot_label),
        scheduler_slot_label);
    switch_copy(entry->switch_class, sizeof(entry->switch_class), switch_class);
    switch_copy(entry->switch_status, sizeof(entry->switch_status),
        "declared-metadata");
    switch_copy(entry->authority_status, sizeof(entry->authority_status),
        "context-switch-authority-denied");
    entry->declared = 1;
    entry->prepared = 0;
    entry->selected = 0;
    entry->committed = 0;
    entry->context_switch_allowed = 0;
    entry->register_save_allowed = 0;
    entry->register_restore_allowed = 0;
    entry->stack_switch_allowed = 0;
    entry->address_space_switch_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->preemption_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 18u;
}

static const latticra_kernel_run_queue_entry_t *queue_at(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index) {
    if (index < run_queue->queue_count && run_queue->queues[index].declared) {
        return &run_queue->queues[index];
    }
    return 0;
}

static const char *queue_process_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    const char *fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->process_label : fallback;
}

static const char *queue_slot_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    const char *fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->scheduler_slot_label : fallback;
}

static unsigned long queue_pid_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->pid_token : fallback;
}

static unsigned long queue_token_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->queue_token : fallback;
}

static unsigned long tick_token_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->tick_token : fallback;
}

static unsigned long priority_for(
    const latticra_kernel_run_queue_result_t *run_queue,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_run_queue_entry_t *queue = queue_at(run_queue, index);
    return queue ? queue->priority : fallback;
}

static void fill_switches(
    latticra_kernel_context_switch_result_t *result,
    size_t requested_switch_count) {
    size_t count = requested_switch_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_CONTEXT_SWITCH_MAX) {
        count = LATTICRA_KERNEL_CONTEXT_SWITCH_MAX;
    }

    result->switch_count = count;
    if (count > 0u) {
        fill_switch(&result->switches[0], 0u, 0ul,
            queue_pid_for(&result->run_queue, 0u, 0ul),
            queue_pid_for(&result->run_queue, 1u, 1ul),
            queue_token_for(&result->run_queue, 1u, 1ul),
            tick_token_for(&result->run_queue, 1u, 1ul),
            priority_for(&result->run_queue, 1u, 10ul),
            queue_process_for(&result->run_queue, 0u, "idle-process-metadata"),
            queue_process_for(&result->run_queue, 1u,
                "kernel-report-process-metadata"),
            queue_slot_for(&result->run_queue, 1u, "kernel-report-metadata"),
            "idle-to-kernel-report-context-switch");
    }
    if (count > 1u) {
        fill_switch(&result->switches[1], 1u, 1ul,
            queue_pid_for(&result->run_queue, 1u, 1ul),
            queue_pid_for(&result->run_queue, 2u, 2ul),
            queue_token_for(&result->run_queue, 2u, 2ul),
            tick_token_for(&result->run_queue, 2u, 2ul),
            priority_for(&result->run_queue, 2u, 20ul),
            queue_process_for(&result->run_queue, 1u,
                "kernel-report-process-metadata"),
            queue_process_for(&result->run_queue, 2u,
                "entropy-report-process-metadata"),
            queue_slot_for(&result->run_queue, 2u, "operator-report-metadata"),
            "kernel-report-to-entropy-context-switch");
    }
    if (count > 2u) {
        fill_switch(&result->switches[2], 2u, 2ul,
            queue_pid_for(&result->run_queue, 2u, 2ul),
            queue_pid_for(&result->run_queue, 3u, 3ul),
            queue_token_for(&result->run_queue, 3u, 3ul),
            tick_token_for(&result->run_queue, 3u, 3ul),
            priority_for(&result->run_queue, 3u, 30ul),
            queue_process_for(&result->run_queue, 2u,
                "entropy-report-process-metadata"),
            queue_process_for(&result->run_queue, 3u,
                "console-report-process-metadata"),
            queue_slot_for(&result->run_queue, 3u, "operator-report-metadata"),
            "entropy-to-console-context-switch");
    }
    if (count > 3u) {
        fill_switch(&result->switches[3], 3u, 3ul,
            queue_pid_for(&result->run_queue, 3u, 3ul),
            queue_pid_for(&result->run_queue, 0u, 0ul),
            queue_token_for(&result->run_queue, 0u, 0ul),
            tick_token_for(&result->run_queue, 0u, 0ul),
            priority_for(&result->run_queue, 0u, 0ul),
            queue_process_for(&result->run_queue, 3u,
                "console-report-process-metadata"),
            queue_process_for(&result->run_queue, 0u, "idle-process-metadata"),
            queue_slot_for(&result->run_queue, 0u, "idle-metadata"),
            "console-to-idle-context-switch");
    }
    for (i = 4u; i < count; ++i) {
        fill_switch(&result->switches[i], i, 6000ul + (unsigned long)i,
            1000ul + (unsigned long)i,
            2000ul + (unsigned long)i,
            queue_token_for(&result->run_queue, i, 5000ul + (unsigned long)i),
            tick_token_for(&result->run_queue, i, 4000ul + (unsigned long)i),
            priority_for(&result->run_queue, i, 100ul),
            "reserved-current-process-metadata",
            queue_process_for(&result->run_queue, i, "reserved-process-metadata"),
            queue_slot_for(&result->run_queue, i, "reserved-metadata"),
            "reserved-context-switch");
    }
}

latticra_status_t latticra_kernel_context_switch_evaluate(
    const latticra_kernel_context_switch_request_t *request,
    latticra_kernel_context_switch_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        switch_copy(result->switch_status, sizeof(result->switch_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_run_queue_evaluate(&request->run_queue_request,
        &result->run_queue);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        switch_copy(result->switch_status, sizeof(result->switch_status),
            "run-queue-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_switches(result, request->requested_switch_count);
    result->no_effect = result->run_queue.no_effect;
    switch_copy(result->switch_status, sizeof(result->switch_status),
        result->no_effect ? "context-switch-seed-ready" :
            "context-switch-seed-blocked");
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

latticra_status_t latticra_kernel_context_switch_report(
    const latticra_kernel_context_switch_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL CONTEXT SWITCH REPORT\n"
        "switch_status=%s\n"
        "policy_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "interrupt_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "scheduler_status=%s\n"
        "switch_count=%lu\n"
        "no_effect=%d\n"
        "context_switch_allowed=%d\n"
        "register_save_allowed=%d\n"
        "register_restore_allowed=%d\n"
        "stack_switch_allowed=%d\n"
        "address_space_switch_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "preemption_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->switch_status,
        result->policy_status,
        result->run_queue.queue_status,
        result->run_queue.scheduler_tick.tick_status,
        result->run_queue.scheduler_tick.timer_source.timer_status,
        result->run_queue.scheduler_tick.timer_source.interrupt_table.table_status,
        result->run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        result->run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.scheduler.scheduler_status,
        (unsigned long)result->switch_count,
        result->no_effect,
        result->context_switch_allowed,
        result->register_save_allowed,
        result->register_restore_allowed,
        result->stack_switch_allowed,
        result->address_space_switch_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->preemption_allowed,
        result->time_accounting_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->switch_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "switch[%lu].from_process_label=%s\n"
            "switch[%lu].to_process_label=%s\n"
            "switch[%lu].switch_token=%lu\n"
            "switch[%lu].from_pid_token=%lu\n"
            "switch[%lu].to_pid_token=%lu\n"
            "switch[%lu].queue_token=%lu\n"
            "switch[%lu].tick_token=%lu\n"
            "switch[%lu].priority=%lu\n"
            "switch[%lu].scheduler_slot_label=%s\n"
            "switch[%lu].switch_class=%s\n"
            "switch[%lu].switch_status=%s\n"
            "switch[%lu].authority_status=%s\n"
            "switch[%lu].declared=%d\n"
            "switch[%lu].prepared=%d\n"
            "switch[%lu].selected=%d\n"
            "switch[%lu].committed=%d\n"
            "switch[%lu].context_switch_allowed=%d\n"
            "switch[%lu].register_save_allowed=%d\n"
            "switch[%lu].register_restore_allowed=%d\n"
            "switch[%lu].stack_switch_allowed=%d\n"
            "switch[%lu].address_space_switch_allowed=%d\n"
            "switch[%lu].dispatch_allowed=%d\n"
            "switch[%lu].run_queue_mutation_allowed=%d\n"
            "switch[%lu].preemption_allowed=%d\n"
            "switch[%lu].time_accounting_allowed=%d\n"
            "switch[%lu].process_wake_allowed=%d\n"
            "switch[%lu].hardware_effect_allowed=%d\n"
            "switch[%lu].host_effect_allowed=%d\n"
            "switch[%lu].no_effect=%d\n",
            (unsigned long)i, result->switches[i].from_process_label,
            (unsigned long)i, result->switches[i].to_process_label,
            (unsigned long)i, result->switches[i].switch_token,
            (unsigned long)i, result->switches[i].from_pid_token,
            (unsigned long)i, result->switches[i].to_pid_token,
            (unsigned long)i, result->switches[i].queue_token,
            (unsigned long)i, result->switches[i].tick_token,
            (unsigned long)i, result->switches[i].priority,
            (unsigned long)i, result->switches[i].scheduler_slot_label,
            (unsigned long)i, result->switches[i].switch_class,
            (unsigned long)i, result->switches[i].switch_status,
            (unsigned long)i, result->switches[i].authority_status,
            (unsigned long)i, result->switches[i].declared,
            (unsigned long)i, result->switches[i].prepared,
            (unsigned long)i, result->switches[i].selected,
            (unsigned long)i, result->switches[i].committed,
            (unsigned long)i, result->switches[i].context_switch_allowed,
            (unsigned long)i, result->switches[i].register_save_allowed,
            (unsigned long)i, result->switches[i].register_restore_allowed,
            (unsigned long)i, result->switches[i].stack_switch_allowed,
            (unsigned long)i, result->switches[i].address_space_switch_allowed,
            (unsigned long)i, result->switches[i].dispatch_allowed,
            (unsigned long)i, result->switches[i].run_queue_mutation_allowed,
            (unsigned long)i, result->switches[i].preemption_allowed,
            (unsigned long)i, result->switches[i].time_accounting_allowed,
            (unsigned long)i, result->switches[i].process_wake_allowed,
            (unsigned long)i, result->switches[i].hardware_effect_allowed,
            (unsigned long)i, result->switches[i].host_effect_allowed,
            (unsigned long)i, result->switches[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
