#include "latticra/kernel_interrupt_table.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void interrupt_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_interrupt_table_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    interrupt_copy(result->table_status, sizeof(result->table_status), "pending");
    interrupt_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->interrupt_mask_allowed = 0;
    result->interrupt_unmask_allowed = 0;
    result->interrupt_dispatch_allowed = 0;
    result->interrupt_ack_allowed = 0;
    result->dma_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 14u;
}

latticra_status_t latticra_kernel_interrupt_table_default_request(
    latticra_kernel_interrupt_table_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_driver_catalog_default_request(&request->driver_catalog_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_route_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_route(
    latticra_kernel_interrupt_table_entry_t *route,
    size_t index,
    unsigned long irq_vector,
    const char *driver_name,
    const char *device_path,
    const char *route_class) {
    memset(route, 0, sizeof(*route));
    route->route_index = index;
    route->irq_vector = irq_vector;
    interrupt_copy(route->driver_name, sizeof(route->driver_name), driver_name);
    interrupt_copy(route->device_path, sizeof(route->device_path), device_path);
    interrupt_copy(route->route_class, sizeof(route->route_class), route_class);
    interrupt_copy(route->backing, sizeof(route->backing), "driver-catalog-metadata");
    interrupt_copy(route->table_status, sizeof(route->table_status),
        "declared-metadata");
    interrupt_copy(route->authority_status, sizeof(route->authority_status),
        "interrupt-authority-denied");
    route->declared = 1;
    route->connected = 0;
    route->enabled = 0;
    route->mask_allowed = 0;
    route->unmask_allowed = 0;
    route->dispatch_allowed = 0;
    route->ack_allowed = 0;
    route->dma_allowed = 0;
    route->hardware_effect_allowed = 0;
    route->host_effect_allowed = 0;
    route->no_effect = 1;
    route->evidence_level = 14u;
}

static void fill_routes(
    latticra_kernel_interrupt_table_result_t *result,
    size_t requested_route_count) {
    size_t count = requested_route_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_INTERRUPT_TABLE_ROUTE_MAX) {
        count = LATTICRA_KERNEL_INTERRUPT_TABLE_ROUTE_MAX;
    }

    result->route_count = count;
    if (count > 0u) {
        fill_route(&result->routes[0], 0u, 32ul, "console-driver-metadata",
            "/dev/console", "console-interrupt");
    }
    if (count > 1u) {
        fill_route(&result->routes[1], 1u, 33ul, "root-block-driver-metadata",
            "/dev/root", "block-interrupt");
    }
    if (count > 2u) {
        fill_route(&result->routes[2], 2u, 34ul, "entropy-driver-metadata",
            "/dev/random", "entropy-interrupt");
    }
    if (count > 3u) {
        fill_route(&result->routes[3], 3u, 35ul, "clock-driver-metadata",
            "/dev/clock", "timer-interrupt");
    }
    for (i = 4u; i < count; ++i) {
        fill_route(&result->routes[i], i, 128ul + (unsigned long)i,
            "reserved-driver-metadata", "/dev/reserved",
            "reserved-interrupt");
    }
}

latticra_status_t latticra_kernel_interrupt_table_evaluate(
    const latticra_kernel_interrupt_table_request_t *request,
    latticra_kernel_interrupt_table_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        interrupt_copy(result->table_status, sizeof(result->table_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_driver_catalog_evaluate(&request->driver_catalog_request,
        &result->driver_catalog);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        interrupt_copy(result->table_status, sizeof(result->table_status),
            "driver-catalog-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_routes(result, request->requested_route_count);
    result->no_effect = result->driver_catalog.no_effect;
    interrupt_copy(result->table_status, sizeof(result->table_status),
        result->no_effect ? "interrupt-table-seed-ready" :
            "interrupt-table-seed-blocked");
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

latticra_status_t latticra_kernel_interrupt_table_report(
    const latticra_kernel_interrupt_table_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL INTERRUPT TABLE REPORT\n"
        "table_status=%s\n"
        "policy_status=%s\n"
        "driver_catalog_status=%s\n"
        "device_registry_status=%s\n"
        "vfs_namespace_status=%s\n"
        "ipc_table_status=%s\n"
        "syscall_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "route_count=%lu\n"
        "no_effect=%d\n"
        "interrupt_mask_allowed=%d\n"
        "interrupt_unmask_allowed=%d\n"
        "interrupt_dispatch_allowed=%d\n"
        "interrupt_ack_allowed=%d\n"
        "dma_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->table_status,
        result->policy_status,
        result->driver_catalog.catalog_status,
        result->driver_catalog.device_registry.registry_status,
        result->driver_catalog.device_registry.vfs_namespace.namespace_status,
        result->driver_catalog.device_registry.vfs_namespace.ipc_table.table_status,
        result->driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.table_status,
        result->driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        (unsigned long)result->route_count,
        result->no_effect,
        result->interrupt_mask_allowed,
        result->interrupt_unmask_allowed,
        result->interrupt_dispatch_allowed,
        result->interrupt_ack_allowed,
        result->dma_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->route_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "route[%lu].driver_name=%s\n"
            "route[%lu].irq_vector=%lu\n"
            "route[%lu].device_path=%s\n"
            "route[%lu].route_class=%s\n"
            "route[%lu].backing=%s\n"
            "route[%lu].table_status=%s\n"
            "route[%lu].authority_status=%s\n"
            "route[%lu].declared=%d\n"
            "route[%lu].connected=%d\n"
            "route[%lu].enabled=%d\n"
            "route[%lu].mask_allowed=%d\n"
            "route[%lu].unmask_allowed=%d\n"
            "route[%lu].dispatch_allowed=%d\n"
            "route[%lu].ack_allowed=%d\n"
            "route[%lu].dma_allowed=%d\n"
            "route[%lu].hardware_effect_allowed=%d\n"
            "route[%lu].host_effect_allowed=%d\n"
            "route[%lu].no_effect=%d\n",
            (unsigned long)i, result->routes[i].driver_name,
            (unsigned long)i, result->routes[i].irq_vector,
            (unsigned long)i, result->routes[i].device_path,
            (unsigned long)i, result->routes[i].route_class,
            (unsigned long)i, result->routes[i].backing,
            (unsigned long)i, result->routes[i].table_status,
            (unsigned long)i, result->routes[i].authority_status,
            (unsigned long)i, result->routes[i].declared,
            (unsigned long)i, result->routes[i].connected,
            (unsigned long)i, result->routes[i].enabled,
            (unsigned long)i, result->routes[i].mask_allowed,
            (unsigned long)i, result->routes[i].unmask_allowed,
            (unsigned long)i, result->routes[i].dispatch_allowed,
            (unsigned long)i, result->routes[i].ack_allowed,
            (unsigned long)i, result->routes[i].dma_allowed,
            (unsigned long)i, result->routes[i].hardware_effect_allowed,
            (unsigned long)i, result->routes[i].host_effect_allowed,
            (unsigned long)i, result->routes[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
