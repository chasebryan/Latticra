#include "latticra/kernel_scheduler_tick.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void tick_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_scheduler_tick_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    tick_copy(result->tick_status, sizeof(result->tick_status), "pending");
    tick_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->timer_tick_allowed = 0;
    result->scheduler_tick_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->context_switch_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 16u;
}

latticra_status_t latticra_kernel_scheduler_tick_default_request(
    latticra_kernel_scheduler_tick_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_timer_source_default_request(&request->timer_source_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_tick_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_tick(
    latticra_kernel_scheduler_tick_entry_t *tick,
    size_t index,
    unsigned long tick_token,
    unsigned long timer_token,
    unsigned long irq_vector,
    unsigned long budget_ns,
    const char *timer_name,
    const char *scheduler_slot_label,
    const char *process_label,
    const char *tick_class) {
    memset(tick, 0, sizeof(*tick));
    tick->tick_index = index;
    tick->tick_token = tick_token;
    tick->timer_token = timer_token;
    tick->irq_vector = irq_vector;
    tick->budget_ns = budget_ns;
    tick_copy(tick->timer_name, sizeof(tick->timer_name), timer_name);
    tick_copy(tick->scheduler_slot_label, sizeof(tick->scheduler_slot_label),
        scheduler_slot_label);
    tick_copy(tick->process_label, sizeof(tick->process_label), process_label);
    tick_copy(tick->tick_class, sizeof(tick->tick_class), tick_class);
    tick_copy(tick->tick_status, sizeof(tick->tick_status), "declared-metadata");
    tick_copy(tick->authority_status, sizeof(tick->authority_status),
        "scheduler-tick-authority-denied");
    tick->declared = 1;
    tick->pending = 0;
    tick->dispatched = 0;
    tick->timer_tick_allowed = 0;
    tick->scheduler_tick_allowed = 0;
    tick->run_queue_mutation_allowed = 0;
    tick->context_switch_allowed = 0;
    tick->preemption_allowed = 0;
    tick->time_accounting_allowed = 0;
    tick->time_read_allowed = 0;
    tick->process_wake_allowed = 0;
    tick->hardware_effect_allowed = 0;
    tick->host_effect_allowed = 0;
    tick->no_effect = 1;
    tick->evidence_level = 16u;
}

static const char *timer_name_for(
    const latticra_kernel_timer_source_result_t *timer_source,
    size_t index,
    const char *fallback) {
    if (index < timer_source->timer_count && timer_source->timers[index].declared) {
        return timer_source->timers[index].name;
    }
    return fallback;
}

static unsigned long timer_token_for(
    const latticra_kernel_timer_source_result_t *timer_source,
    size_t index,
    unsigned long fallback) {
    if (index < timer_source->timer_count && timer_source->timers[index].declared) {
        return timer_source->timers[index].timer_token;
    }
    return fallback;
}

static unsigned long irq_for(
    const latticra_kernel_timer_source_result_t *timer_source,
    size_t index,
    unsigned long fallback) {
    if (index < timer_source->timer_count && timer_source->timers[index].declared) {
        return timer_source->timers[index].irq_vector;
    }
    return fallback;
}

static unsigned long budget_for(
    const latticra_kernel_timer_source_result_t *timer_source,
    size_t index,
    unsigned long fallback) {
    if (index < timer_source->timer_count && timer_source->timers[index].declared) {
        return timer_source->timers[index].period_ns;
    }
    return fallback;
}

static void fill_ticks(
    latticra_kernel_scheduler_tick_result_t *result,
    size_t requested_tick_count) {
    size_t count = requested_tick_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_SCHEDULER_TICK_MAX) {
        count = LATTICRA_KERNEL_SCHEDULER_TICK_MAX;
    }

    result->tick_count = count;
    if (count > 0u) {
        fill_tick(&result->ticks[0], 0u, 0ul,
            timer_token_for(&result->timer_source, 0u, 0ul),
            irq_for(&result->timer_source, 0u, 35ul),
            budget_for(&result->timer_source, 0u, 10000000ul),
            timer_name_for(&result->timer_source, 0u, "kernel-tick-timer-metadata"),
            "idle-metadata", "idle-process-metadata", "scheduler-clock-tick");
    }
    if (count > 1u) {
        fill_tick(&result->ticks[1], 1u, 1ul,
            timer_token_for(&result->timer_source, 1u, 1ul),
            irq_for(&result->timer_source, 1u, 35ul),
            budget_for(&result->timer_source, 1u, 1000000ul),
            timer_name_for(&result->timer_source, 1u, "monotonic-time-timer-metadata"),
            "kernel-report-metadata", "kernel-report-process-metadata",
            "time-accounting-sample");
    }
    if (count > 2u) {
        fill_tick(&result->ticks[2], 2u, 2ul,
            timer_token_for(&result->timer_source, 2u, 2ul),
            irq_for(&result->timer_source, 2u, 34ul),
            budget_for(&result->timer_source, 2u, 0ul),
            timer_name_for(&result->timer_source, 2u, "entropy-poll-timer-metadata"),
            "operator-report-metadata", "entropy-report-process-metadata",
            "entropy-wakeup-window");
    }
    if (count > 3u) {
        fill_tick(&result->ticks[3], 3u, 3ul,
            timer_token_for(&result->timer_source, 3u, 3ul),
            irq_for(&result->timer_source, 3u, 32ul),
            budget_for(&result->timer_source, 3u, 0ul),
            timer_name_for(&result->timer_source, 3u, "console-timeout-timer-metadata"),
            "operator-report-metadata", "console-report-process-metadata",
            "console-timeout-window");
    }
    for (i = 4u; i < count; ++i) {
        fill_tick(&result->ticks[i], i, 4000ul + (unsigned long)i,
            timer_token_for(&result->timer_source, i, 3000ul + (unsigned long)i),
            irq_for(&result->timer_source, i, 128ul + (unsigned long)i),
            budget_for(&result->timer_source, i, 0ul),
            timer_name_for(&result->timer_source, i, "reserved-timer-metadata"),
            "reserved-metadata", "reserved-process-metadata",
            "reserved-scheduler-tick");
    }
}

latticra_status_t latticra_kernel_scheduler_tick_evaluate(
    const latticra_kernel_scheduler_tick_request_t *request,
    latticra_kernel_scheduler_tick_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        tick_copy(result->tick_status, sizeof(result->tick_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_timer_source_evaluate(&request->timer_source_request,
        &result->timer_source);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        tick_copy(result->tick_status, sizeof(result->tick_status),
            "timer-source-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_ticks(result, request->requested_tick_count);
    result->no_effect = result->timer_source.no_effect;
    tick_copy(result->tick_status, sizeof(result->tick_status),
        result->no_effect ? "scheduler-tick-seed-ready" :
            "scheduler-tick-seed-blocked");
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

latticra_status_t latticra_kernel_scheduler_tick_report(
    const latticra_kernel_scheduler_tick_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER TICK REPORT\n"
        "tick_status=%s\n"
        "policy_status=%s\n"
        "timer_source_status=%s\n"
        "interrupt_table_status=%s\n"
        "driver_catalog_status=%s\n"
        "device_registry_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "scheduler_status=%s\n"
        "tick_count=%lu\n"
        "no_effect=%d\n"
        "timer_tick_allowed=%d\n"
        "scheduler_tick_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->tick_status,
        result->policy_status,
        result->timer_source.timer_status,
        result->timer_source.interrupt_table.table_status,
        result->timer_source.interrupt_table.driver_catalog.catalog_status,
        result->timer_source.interrupt_table.driver_catalog.device_registry.registry_status,
        result->timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        result->timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.scheduler.scheduler_status,
        (unsigned long)result->tick_count,
        result->no_effect,
        result->timer_tick_allowed,
        result->scheduler_tick_allowed,
        result->run_queue_mutation_allowed,
        result->context_switch_allowed,
        result->preemption_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->tick_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "tick[%lu].timer_name=%s\n"
            "tick[%lu].timer_token=%lu\n"
            "tick[%lu].irq_vector=%lu\n"
            "tick[%lu].budget_ns=%lu\n"
            "tick[%lu].scheduler_slot_label=%s\n"
            "tick[%lu].process_label=%s\n"
            "tick[%lu].tick_class=%s\n"
            "tick[%lu].tick_status=%s\n"
            "tick[%lu].authority_status=%s\n"
            "tick[%lu].declared=%d\n"
            "tick[%lu].pending=%d\n"
            "tick[%lu].dispatched=%d\n"
            "tick[%lu].timer_tick_allowed=%d\n"
            "tick[%lu].scheduler_tick_allowed=%d\n"
            "tick[%lu].run_queue_mutation_allowed=%d\n"
            "tick[%lu].context_switch_allowed=%d\n"
            "tick[%lu].preemption_allowed=%d\n"
            "tick[%lu].time_accounting_allowed=%d\n"
            "tick[%lu].time_read_allowed=%d\n"
            "tick[%lu].process_wake_allowed=%d\n"
            "tick[%lu].hardware_effect_allowed=%d\n"
            "tick[%lu].host_effect_allowed=%d\n"
            "tick[%lu].no_effect=%d\n",
            (unsigned long)i, result->ticks[i].timer_name,
            (unsigned long)i, result->ticks[i].timer_token,
            (unsigned long)i, result->ticks[i].irq_vector,
            (unsigned long)i, result->ticks[i].budget_ns,
            (unsigned long)i, result->ticks[i].scheduler_slot_label,
            (unsigned long)i, result->ticks[i].process_label,
            (unsigned long)i, result->ticks[i].tick_class,
            (unsigned long)i, result->ticks[i].tick_status,
            (unsigned long)i, result->ticks[i].authority_status,
            (unsigned long)i, result->ticks[i].declared,
            (unsigned long)i, result->ticks[i].pending,
            (unsigned long)i, result->ticks[i].dispatched,
            (unsigned long)i, result->ticks[i].timer_tick_allowed,
            (unsigned long)i, result->ticks[i].scheduler_tick_allowed,
            (unsigned long)i, result->ticks[i].run_queue_mutation_allowed,
            (unsigned long)i, result->ticks[i].context_switch_allowed,
            (unsigned long)i, result->ticks[i].preemption_allowed,
            (unsigned long)i, result->ticks[i].time_accounting_allowed,
            (unsigned long)i, result->ticks[i].time_read_allowed,
            (unsigned long)i, result->ticks[i].process_wake_allowed,
            (unsigned long)i, result->ticks[i].hardware_effect_allowed,
            (unsigned long)i, result->ticks[i].host_effect_allowed,
            (unsigned long)i, result->ticks[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
