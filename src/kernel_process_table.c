#include "latticra/kernel_process_table.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void process_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_process_table_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    process_copy(result->table_status, sizeof(result->table_status), "pending");
    process_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->process_spawn_allowed = 0;
    result->context_switch_allowed = 0;
    result->signal_delivery_allowed = 0;
    result->address_space_mutation_allowed = 0;
    result->evidence_level = 8u;
}

latticra_status_t latticra_kernel_process_table_default_request(
    latticra_kernel_process_table_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_memory_map_default_request(&request->memory_map_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_process_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_process(
    latticra_kernel_process_table_entry_t *process,
    size_t index,
    unsigned long pid_token,
    const char *label,
    const char *scheduler_slot_label,
    const char *memory_region_label) {
    memset(process, 0, sizeof(*process));
    process->process_index = index;
    process->pid_token = pid_token;
    process_copy(process->label, sizeof(process->label), label);
    process_copy(process->lifecycle_status, sizeof(process->lifecycle_status),
        "declared-metadata");
    process_copy(process->authority_status, sizeof(process->authority_status),
        "spawn-denied");
    process_copy(process->scheduler_slot_label, sizeof(process->scheduler_slot_label),
        scheduler_slot_label);
    process_copy(process->memory_region_label, sizeof(process->memory_region_label),
        memory_region_label);
    process->declared = 1;
    process->runnable = 0;
    process->scheduled = 0;
    process->spawned = 0;
    process->no_effect = 1;
    process->evidence_level = 8u;
}

static void fill_processes(
    latticra_kernel_process_table_result_t *result,
    size_t requested_process_count) {
    size_t count = requested_process_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_PROCESS_TABLE_PROCESS_MAX) {
        count = LATTICRA_KERNEL_PROCESS_TABLE_PROCESS_MAX;
    }

    result->process_count = count;
    if (count > 0u) {
        fill_process(&result->processes[0], 0u, 0ul, "idle-process-metadata",
            "idle-metadata", "kernel-stack-metadata");
    }
    if (count > 1u) {
        fill_process(&result->processes[1], 1u, 1ul, "kernel-report-process-metadata",
            "kernel-report-metadata", "kernel-report-metadata");
    }
    if (count > 2u) {
        fill_process(&result->processes[2], 2u, 2ul, "operator-report-process-metadata",
            "operator-report-metadata", "kernel-report-metadata");
    }
    if (count > 3u) {
        fill_process(&result->processes[3], 3u, 3ul, "supervisor-process-metadata",
            "reserved-metadata", "kernel-data-metadata");
    }
    for (i = 4u; i < count; ++i) {
        fill_process(&result->processes[i], i, 1000ul + (unsigned long)i,
            "reserved-process-metadata", "reserved-metadata",
            "reserved-memory-metadata");
    }
}

latticra_status_t latticra_kernel_process_table_evaluate(
    const latticra_kernel_process_table_request_t *request,
    latticra_kernel_process_table_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        process_copy(result->table_status, sizeof(result->table_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_memory_map_evaluate(&request->memory_map_request,
        &result->memory_map);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        process_copy(result->table_status, sizeof(result->table_status),
            "memory-map-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_processes(result, request->requested_process_count);
    result->no_effect = result->memory_map.no_effect;
    process_copy(result->table_status, sizeof(result->table_status),
        result->no_effect ? "process-table-seed-ready" : "process-table-seed-blocked");
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

latticra_status_t latticra_kernel_process_table_report(
    const latticra_kernel_process_table_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL PROCESS TABLE REPORT\n"
        "table_status=%s\n"
        "policy_status=%s\n"
        "memory_map_status=%s\n"
        "scheduler_status=%s\n"
        "process_count=%lu\n"
        "no_effect=%d\n"
        "process_spawn_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "signal_delivery_allowed=%d\n"
        "address_space_mutation_allowed=%d\n"
        "evidence_level=%u\n",
        result->table_status,
        result->policy_status,
        result->memory_map.map_status,
        result->memory_map.scheduler.scheduler_status,
        (unsigned long)result->process_count,
        result->no_effect,
        result->process_spawn_allowed,
        result->context_switch_allowed,
        result->signal_delivery_allowed,
        result->address_space_mutation_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->process_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "process[%lu].label=%s\n"
            "process[%lu].pid_token=%lu\n"
            "process[%lu].lifecycle_status=%s\n"
            "process[%lu].authority_status=%s\n"
            "process[%lu].scheduler_slot_label=%s\n"
            "process[%lu].memory_region_label=%s\n"
            "process[%lu].declared=%d\n"
            "process[%lu].runnable=%d\n"
            "process[%lu].scheduled=%d\n"
            "process[%lu].spawned=%d\n"
            "process[%lu].no_effect=%d\n",
            (unsigned long)i, result->processes[i].label,
            (unsigned long)i, result->processes[i].pid_token,
            (unsigned long)i, result->processes[i].lifecycle_status,
            (unsigned long)i, result->processes[i].authority_status,
            (unsigned long)i, result->processes[i].scheduler_slot_label,
            (unsigned long)i, result->processes[i].memory_region_label,
            (unsigned long)i, result->processes[i].declared,
            (unsigned long)i, result->processes[i].runnable,
            (unsigned long)i, result->processes[i].scheduled,
            (unsigned long)i, result->processes[i].spawned,
            (unsigned long)i, result->processes[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
