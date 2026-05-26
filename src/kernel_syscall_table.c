#include "latticra/kernel_syscall_table.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void syscall_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_syscall_table_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    syscall_copy(result->table_status, sizeof(result->table_status), "pending");
    syscall_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->syscall_dispatch_allowed = 0;
    result->host_effect_allowed = 0;
    result->mutation_allowed = 0;
    result->file_io_allowed = 0;
    result->network_allowed = 0;
    result->evidence_level = 9u;
}

latticra_status_t latticra_kernel_syscall_table_default_request(
    latticra_kernel_syscall_table_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_process_table_default_request(&request->process_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_call_count = 8u;
    return LATTICRA_STATUS_OK;
}

static void fill_call(
    latticra_kernel_syscall_table_entry_t *call,
    size_t index,
    unsigned long call_number,
    const char *name,
    const char *domain,
    const char *authority_status) {
    memset(call, 0, sizeof(*call));
    call->call_index = index;
    call->call_number = call_number;
    syscall_copy(call->name, sizeof(call->name), name);
    syscall_copy(call->domain, sizeof(call->domain), domain);
    syscall_copy(call->dispatch_status, sizeof(call->dispatch_status),
        "dispatch-denied");
    syscall_copy(call->authority_status, sizeof(call->authority_status),
        authority_status);
    call->declared = 1;
    call->implemented = 0;
    call->dispatch_allowed = 0;
    call->host_effect_allowed = 0;
    call->network_allowed = 0;
    call->no_effect = 1;
    call->evidence_level = 9u;
}

static void fill_calls(
    latticra_kernel_syscall_table_result_t *result,
    size_t requested_call_count) {
    size_t count = requested_call_count;
    size_t i;
    if (count == 0u) count = 8u;
    if (count > LATTICRA_KERNEL_SYSCALL_TABLE_CALL_MAX) {
        count = LATTICRA_KERNEL_SYSCALL_TABLE_CALL_MAX;
    }

    result->call_count = count;
    if (count > 0u) {
        fill_call(&result->calls[0], 0u, 0ul, "yield", "scheduler",
            "context-switch-denied");
    }
    if (count > 1u) {
        fill_call(&result->calls[1], 1u, 1ul, "spawn_process", "process",
            "spawn-denied");
    }
    if (count > 2u) {
        fill_call(&result->calls[2], 2u, 2ul, "send_signal", "process",
            "signal-denied");
    }
    if (count > 3u) {
        fill_call(&result->calls[3], 3u, 3ul, "map_memory", "memory",
            "address-space-mutation-denied");
    }
    if (count > 4u) {
        fill_call(&result->calls[4], 4u, 4ul, "open_file", "filesystem",
            "file-io-denied");
    }
    if (count > 5u) {
        fill_call(&result->calls[5], 5u, 5ul, "read_file", "filesystem",
            "file-io-denied");
    }
    if (count > 6u) {
        fill_call(&result->calls[6], 6u, 6ul, "open_device", "device",
            "device-io-denied");
    }
    if (count > 7u) {
        fill_call(&result->calls[7], 7u, 7ul, "network_send", "network",
            "network-io-denied");
    }
    for (i = 8u; i < count; ++i) {
        fill_call(&result->calls[i], i, 1000ul + (unsigned long)i,
            "reserved_syscall", "reserved", "reserved-denied");
    }
}

latticra_status_t latticra_kernel_syscall_table_evaluate(
    const latticra_kernel_syscall_table_request_t *request,
    latticra_kernel_syscall_table_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        syscall_copy(result->table_status, sizeof(result->table_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_process_table_evaluate(&request->process_table_request,
        &result->process_table);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        syscall_copy(result->table_status, sizeof(result->table_status),
            "process-table-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_calls(result, request->requested_call_count);
    result->no_effect = result->process_table.no_effect;
    syscall_copy(result->table_status, sizeof(result->table_status),
        result->no_effect ? "syscall-table-seed-ready" : "syscall-table-seed-blocked");
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

latticra_status_t latticra_kernel_syscall_table_report(
    const latticra_kernel_syscall_table_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SYSCALL TABLE REPORT\n"
        "table_status=%s\n"
        "policy_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "call_count=%lu\n"
        "no_effect=%d\n"
        "syscall_dispatch_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "mutation_allowed=%d\n"
        "file_io_allowed=%d\n"
        "network_allowed=%d\n"
        "evidence_level=%u\n",
        result->table_status,
        result->policy_status,
        result->process_table.table_status,
        result->process_table.memory_map.map_status,
        (unsigned long)result->call_count,
        result->no_effect,
        result->syscall_dispatch_allowed,
        result->host_effect_allowed,
        result->mutation_allowed,
        result->file_io_allowed,
        result->network_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->call_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "call[%lu].name=%s\n"
            "call[%lu].number=%lu\n"
            "call[%lu].domain=%s\n"
            "call[%lu].dispatch_status=%s\n"
            "call[%lu].authority_status=%s\n"
            "call[%lu].declared=%d\n"
            "call[%lu].implemented=%d\n"
            "call[%lu].dispatch_allowed=%d\n"
            "call[%lu].host_effect_allowed=%d\n"
            "call[%lu].network_allowed=%d\n"
            "call[%lu].no_effect=%d\n",
            (unsigned long)i, result->calls[i].name,
            (unsigned long)i, result->calls[i].call_number,
            (unsigned long)i, result->calls[i].domain,
            (unsigned long)i, result->calls[i].dispatch_status,
            (unsigned long)i, result->calls[i].authority_status,
            (unsigned long)i, result->calls[i].declared,
            (unsigned long)i, result->calls[i].implemented,
            (unsigned long)i, result->calls[i].dispatch_allowed,
            (unsigned long)i, result->calls[i].host_effect_allowed,
            (unsigned long)i, result->calls[i].network_allowed,
            (unsigned long)i, result->calls[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
