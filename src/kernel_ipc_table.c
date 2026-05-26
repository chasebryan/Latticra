#include "latticra/kernel_ipc_table.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void ipc_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_ipc_table_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    ipc_copy(result->table_status, sizeof(result->table_status), "pending");
    ipc_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->ipc_send_allowed = 0;
    result->ipc_receive_allowed = 0;
    result->queue_mutation_allowed = 0;
    result->endpoint_bind_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 10u;
}

latticra_status_t latticra_kernel_ipc_table_default_request(
    latticra_kernel_ipc_table_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_syscall_table_default_request(&request->syscall_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_port_count = 5u;
    return LATTICRA_STATUS_OK;
}

static void fill_port(
    latticra_kernel_ipc_table_entry_t *port,
    size_t index,
    unsigned long port_token,
    const char *label,
    const char *domain,
    const char *authority_status) {
    memset(port, 0, sizeof(*port));
    port->port_index = index;
    port->port_token = port_token;
    ipc_copy(port->label, sizeof(port->label), label);
    ipc_copy(port->domain, sizeof(port->domain), domain);
    ipc_copy(port->endpoint_status, sizeof(port->endpoint_status), "declared-metadata");
    ipc_copy(port->authority_status, sizeof(port->authority_status), authority_status);
    port->declared = 1;
    port->bound = 0;
    port->send_allowed = 0;
    port->receive_allowed = 0;
    port->queue_mutation_allowed = 0;
    port->host_effect_allowed = 0;
    port->no_effect = 1;
    port->evidence_level = 10u;
}

static void fill_ports(
    latticra_kernel_ipc_table_result_t *result,
    size_t requested_port_count) {
    size_t count = requested_port_count;
    size_t i;
    if (count == 0u) count = 5u;
    if (count > LATTICRA_KERNEL_IPC_TABLE_PORT_MAX) {
        count = LATTICRA_KERNEL_IPC_TABLE_PORT_MAX;
    }

    result->port_count = count;
    if (count > 0u) {
        fill_port(&result->ports[0], 0u, 0ul, "kernel-control-port-metadata",
            "control", "ipc-send-denied");
    }
    if (count > 1u) {
        fill_port(&result->ports[1], 1u, 1ul, "process-report-port-metadata",
            "process", "ipc-receive-denied");
    }
    if (count > 2u) {
        fill_port(&result->ports[2], 2u, 2ul, "filesystem-request-port-metadata",
            "filesystem", "ipc-queue-denied");
    }
    if (count > 3u) {
        fill_port(&result->ports[3], 3u, 3ul, "device-event-port-metadata",
            "device", "ipc-endpoint-bind-denied");
    }
    if (count > 4u) {
        fill_port(&result->ports[4], 4u, 4ul, "network-event-port-metadata",
            "network", "ipc-host-effect-denied");
    }
    for (i = 5u; i < count; ++i) {
        fill_port(&result->ports[i], i, 1000ul + (unsigned long)i,
            "reserved-ipc-port-metadata", "reserved", "reserved-denied");
    }
}

latticra_status_t latticra_kernel_ipc_table_evaluate(
    const latticra_kernel_ipc_table_request_t *request,
    latticra_kernel_ipc_table_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        ipc_copy(result->table_status, sizeof(result->table_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_syscall_table_evaluate(&request->syscall_table_request,
        &result->syscall_table);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        ipc_copy(result->table_status, sizeof(result->table_status),
            "syscall-table-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_ports(result, request->requested_port_count);
    result->no_effect = result->syscall_table.no_effect;
    ipc_copy(result->table_status, sizeof(result->table_status),
        result->no_effect ? "ipc-table-seed-ready" : "ipc-table-seed-blocked");
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

latticra_status_t latticra_kernel_ipc_table_report(
    const latticra_kernel_ipc_table_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL IPC TABLE REPORT\n"
        "table_status=%s\n"
        "policy_status=%s\n"
        "syscall_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "port_count=%lu\n"
        "no_effect=%d\n"
        "ipc_send_allowed=%d\n"
        "ipc_receive_allowed=%d\n"
        "queue_mutation_allowed=%d\n"
        "endpoint_bind_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->table_status,
        result->policy_status,
        result->syscall_table.table_status,
        result->syscall_table.process_table.table_status,
        result->syscall_table.process_table.memory_map.map_status,
        (unsigned long)result->port_count,
        result->no_effect,
        result->ipc_send_allowed,
        result->ipc_receive_allowed,
        result->queue_mutation_allowed,
        result->endpoint_bind_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->port_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "port[%lu].label=%s\n"
            "port[%lu].token=%lu\n"
            "port[%lu].domain=%s\n"
            "port[%lu].endpoint_status=%s\n"
            "port[%lu].authority_status=%s\n"
            "port[%lu].declared=%d\n"
            "port[%lu].bound=%d\n"
            "port[%lu].send_allowed=%d\n"
            "port[%lu].receive_allowed=%d\n"
            "port[%lu].queue_mutation_allowed=%d\n"
            "port[%lu].host_effect_allowed=%d\n"
            "port[%lu].no_effect=%d\n",
            (unsigned long)i, result->ports[i].label,
            (unsigned long)i, result->ports[i].port_token,
            (unsigned long)i, result->ports[i].domain,
            (unsigned long)i, result->ports[i].endpoint_status,
            (unsigned long)i, result->ports[i].authority_status,
            (unsigned long)i, result->ports[i].declared,
            (unsigned long)i, result->ports[i].bound,
            (unsigned long)i, result->ports[i].send_allowed,
            (unsigned long)i, result->ports[i].receive_allowed,
            (unsigned long)i, result->ports[i].queue_mutation_allowed,
            (unsigned long)i, result->ports[i].host_effect_allowed,
            (unsigned long)i, result->ports[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
