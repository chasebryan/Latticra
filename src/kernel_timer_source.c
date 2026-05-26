#include "latticra/kernel_timer_source.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void timer_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_timer_source_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    timer_copy(result->timer_status, sizeof(result->timer_status), "pending");
    timer_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->timer_tick_allowed = 0;
    result->timer_arm_allowed = 0;
    result->timer_disarm_allowed = 0;
    result->scheduler_tick_allowed = 0;
    result->preemption_allowed = 0;
    result->time_read_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 15u;
}

latticra_status_t latticra_kernel_timer_source_default_request(
    latticra_kernel_timer_source_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_interrupt_table_default_request(&request->interrupt_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_timer_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_timer(
    latticra_kernel_timer_source_entry_t *timer,
    size_t index,
    unsigned long timer_token,
    unsigned long irq_vector,
    unsigned long period_ns,
    const char *name,
    const char *driver_name,
    const char *device_path,
    const char *timer_class) {
    memset(timer, 0, sizeof(*timer));
    timer->timer_index = index;
    timer->timer_token = timer_token;
    timer->irq_vector = irq_vector;
    timer->period_ns = period_ns;
    timer_copy(timer->name, sizeof(timer->name), name);
    timer_copy(timer->driver_name, sizeof(timer->driver_name), driver_name);
    timer_copy(timer->device_path, sizeof(timer->device_path), device_path);
    timer_copy(timer->timer_class, sizeof(timer->timer_class), timer_class);
    timer_copy(timer->backing, sizeof(timer->backing), "interrupt-table-metadata");
    timer_copy(timer->timer_status, sizeof(timer->timer_status), "declared-metadata");
    timer_copy(timer->authority_status, sizeof(timer->authority_status),
        "timer-authority-denied");
    timer->declared = 1;
    timer->armed = 0;
    timer->running = 0;
    timer->tick_allowed = 0;
    timer->arm_allowed = 0;
    timer->disarm_allowed = 0;
    timer->scheduler_tick_allowed = 0;
    timer->preemption_allowed = 0;
    timer->time_read_allowed = 0;
    timer->hardware_effect_allowed = 0;
    timer->host_effect_allowed = 0;
    timer->no_effect = 1;
    timer->evidence_level = 15u;
}

static void fill_timers(
    latticra_kernel_timer_source_result_t *result,
    size_t requested_timer_count) {
    size_t count = requested_timer_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_TIMER_SOURCE_TIMER_MAX) {
        count = LATTICRA_KERNEL_TIMER_SOURCE_TIMER_MAX;
    }

    result->timer_count = count;
    if (count > 0u) {
        fill_timer(&result->timers[0], 0u, 0ul, 35ul, 10000000ul,
            "kernel-tick-timer-metadata", "clock-driver-metadata",
            "/dev/clock", "scheduler-tick-source");
    }
    if (count > 1u) {
        fill_timer(&result->timers[1], 1u, 1ul, 35ul, 1000000ul,
            "monotonic-time-timer-metadata", "clock-driver-metadata",
            "/dev/clock", "monotonic-time-source");
    }
    if (count > 2u) {
        fill_timer(&result->timers[2], 2u, 2ul, 34ul, 0ul,
            "entropy-poll-timer-metadata", "entropy-driver-metadata",
            "/dev/random", "entropy-poll-source");
    }
    if (count > 3u) {
        fill_timer(&result->timers[3], 3u, 3ul, 32ul, 0ul,
            "console-timeout-timer-metadata", "console-driver-metadata",
            "/dev/console", "console-timeout-source");
    }
    for (i = 4u; i < count; ++i) {
        fill_timer(&result->timers[i], i, 3000ul + (unsigned long)i,
            128ul + (unsigned long)i, 0ul, "reserved-timer-metadata",
            "reserved-driver-metadata", "/dev/reserved",
            "reserved-timer-source");
    }
}

latticra_status_t latticra_kernel_timer_source_evaluate(
    const latticra_kernel_timer_source_request_t *request,
    latticra_kernel_timer_source_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        timer_copy(result->timer_status, sizeof(result->timer_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_interrupt_table_evaluate(&request->interrupt_table_request,
        &result->interrupt_table);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        timer_copy(result->timer_status, sizeof(result->timer_status),
            "interrupt-table-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_timers(result, request->requested_timer_count);
    result->no_effect = result->interrupt_table.no_effect;
    timer_copy(result->timer_status, sizeof(result->timer_status),
        result->no_effect ? "timer-source-seed-ready" :
            "timer-source-seed-blocked");
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

latticra_status_t latticra_kernel_timer_source_report(
    const latticra_kernel_timer_source_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL TIMER SOURCE REPORT\n"
        "timer_status=%s\n"
        "policy_status=%s\n"
        "interrupt_table_status=%s\n"
        "driver_catalog_status=%s\n"
        "device_registry_status=%s\n"
        "vfs_namespace_status=%s\n"
        "ipc_table_status=%s\n"
        "syscall_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "timer_count=%lu\n"
        "no_effect=%d\n"
        "timer_tick_allowed=%d\n"
        "timer_arm_allowed=%d\n"
        "timer_disarm_allowed=%d\n"
        "scheduler_tick_allowed=%d\n"
        "preemption_allowed=%d\n"
        "time_read_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->timer_status,
        result->policy_status,
        result->interrupt_table.table_status,
        result->interrupt_table.driver_catalog.catalog_status,
        result->interrupt_table.driver_catalog.device_registry.registry_status,
        result->interrupt_table.driver_catalog.device_registry.vfs_namespace.namespace_status,
        result->interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.table_status,
        result->interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.table_status,
        result->interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        (unsigned long)result->timer_count,
        result->no_effect,
        result->timer_tick_allowed,
        result->timer_arm_allowed,
        result->timer_disarm_allowed,
        result->scheduler_tick_allowed,
        result->preemption_allowed,
        result->time_read_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->timer_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "timer[%lu].name=%s\n"
            "timer[%lu].token=%lu\n"
            "timer[%lu].irq_vector=%lu\n"
            "timer[%lu].period_ns=%lu\n"
            "timer[%lu].driver_name=%s\n"
            "timer[%lu].device_path=%s\n"
            "timer[%lu].timer_class=%s\n"
            "timer[%lu].backing=%s\n"
            "timer[%lu].timer_status=%s\n"
            "timer[%lu].authority_status=%s\n"
            "timer[%lu].declared=%d\n"
            "timer[%lu].armed=%d\n"
            "timer[%lu].running=%d\n"
            "timer[%lu].tick_allowed=%d\n"
            "timer[%lu].arm_allowed=%d\n"
            "timer[%lu].disarm_allowed=%d\n"
            "timer[%lu].scheduler_tick_allowed=%d\n"
            "timer[%lu].preemption_allowed=%d\n"
            "timer[%lu].time_read_allowed=%d\n"
            "timer[%lu].hardware_effect_allowed=%d\n"
            "timer[%lu].host_effect_allowed=%d\n"
            "timer[%lu].no_effect=%d\n",
            (unsigned long)i, result->timers[i].name,
            (unsigned long)i, result->timers[i].timer_token,
            (unsigned long)i, result->timers[i].irq_vector,
            (unsigned long)i, result->timers[i].period_ns,
            (unsigned long)i, result->timers[i].driver_name,
            (unsigned long)i, result->timers[i].device_path,
            (unsigned long)i, result->timers[i].timer_class,
            (unsigned long)i, result->timers[i].backing,
            (unsigned long)i, result->timers[i].timer_status,
            (unsigned long)i, result->timers[i].authority_status,
            (unsigned long)i, result->timers[i].declared,
            (unsigned long)i, result->timers[i].armed,
            (unsigned long)i, result->timers[i].running,
            (unsigned long)i, result->timers[i].tick_allowed,
            (unsigned long)i, result->timers[i].arm_allowed,
            (unsigned long)i, result->timers[i].disarm_allowed,
            (unsigned long)i, result->timers[i].scheduler_tick_allowed,
            (unsigned long)i, result->timers[i].preemption_allowed,
            (unsigned long)i, result->timers[i].time_read_allowed,
            (unsigned long)i, result->timers[i].hardware_effect_allowed,
            (unsigned long)i, result->timers[i].host_effect_allowed,
            (unsigned long)i, result->timers[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
