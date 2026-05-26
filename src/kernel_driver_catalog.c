#include "latticra/kernel_driver_catalog.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void driver_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_driver_catalog_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    driver_copy(result->catalog_status, sizeof(result->catalog_status), "pending");
    driver_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->driver_probe_allowed = 0;
    result->driver_load_allowed = 0;
    result->driver_bind_allowed = 0;
    result->interrupt_allowed = 0;
    result->dma_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 13u;
}

latticra_status_t latticra_kernel_driver_catalog_default_request(
    latticra_kernel_driver_catalog_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_device_registry_default_request(&request->device_registry_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_driver_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_driver(
    latticra_kernel_driver_catalog_entry_t *driver,
    size_t index,
    unsigned long driver_token,
    const char *name,
    const char *device_path,
    const char *device_class,
    const char *driver_class) {
    memset(driver, 0, sizeof(*driver));
    driver->driver_index = index;
    driver->driver_token = driver_token;
    driver_copy(driver->name, sizeof(driver->name), name);
    driver_copy(driver->device_path, sizeof(driver->device_path), device_path);
    driver_copy(driver->device_class, sizeof(driver->device_class), device_class);
    driver_copy(driver->driver_class, sizeof(driver->driver_class), driver_class);
    driver_copy(driver->backing, sizeof(driver->backing), "device-registry-metadata");
    driver_copy(driver->catalog_status, sizeof(driver->catalog_status),
        "declared-metadata");
    driver_copy(driver->authority_status, sizeof(driver->authority_status),
        "driver-authority-denied");
    driver->declared = 1;
    driver->loaded = 0;
    driver->bound = 0;
    driver->probe_allowed = 0;
    driver->load_allowed = 0;
    driver->bind_allowed = 0;
    driver->interrupt_allowed = 0;
    driver->dma_allowed = 0;
    driver->hardware_effect_allowed = 0;
    driver->host_effect_allowed = 0;
    driver->no_effect = 1;
    driver->evidence_level = 13u;
}

static void fill_drivers(
    latticra_kernel_driver_catalog_result_t *result,
    size_t requested_driver_count) {
    size_t count = requested_driver_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_DRIVER_CATALOG_DRIVER_MAX) {
        count = LATTICRA_KERNEL_DRIVER_CATALOG_DRIVER_MAX;
    }

    result->driver_count = count;
    if (count > 0u) {
        fill_driver(&result->drivers[0], 0u, 0ul, "console-driver-metadata",
            "/dev/console", "character-device", "tty-console-driver");
    }
    if (count > 1u) {
        fill_driver(&result->drivers[1], 1u, 1ul, "root-block-driver-metadata",
            "/dev/root", "block-device", "root-block-driver");
    }
    if (count > 2u) {
        fill_driver(&result->drivers[2], 2u, 2ul, "entropy-driver-metadata",
            "/dev/random", "character-device", "entropy-driver");
    }
    if (count > 3u) {
        fill_driver(&result->drivers[3], 3u, 3ul, "clock-driver-metadata",
            "/dev/clock", "timer-device", "monotonic-clock-driver");
    }
    for (i = 4u; i < count; ++i) {
        fill_driver(&result->drivers[i], i, 2000ul + (unsigned long)i,
            "reserved-driver-metadata", "/dev/reserved",
            "reserved-device", "reserved-driver");
    }
}

latticra_status_t latticra_kernel_driver_catalog_evaluate(
    const latticra_kernel_driver_catalog_request_t *request,
    latticra_kernel_driver_catalog_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        driver_copy(result->catalog_status, sizeof(result->catalog_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_device_registry_evaluate(&request->device_registry_request,
        &result->device_registry);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        driver_copy(result->catalog_status, sizeof(result->catalog_status),
            "device-registry-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_drivers(result, request->requested_driver_count);
    result->no_effect = result->device_registry.no_effect;
    driver_copy(result->catalog_status, sizeof(result->catalog_status),
        result->no_effect ? "driver-catalog-seed-ready" :
            "driver-catalog-seed-blocked");
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

latticra_status_t latticra_kernel_driver_catalog_report(
    const latticra_kernel_driver_catalog_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL DRIVER CATALOG REPORT\n"
        "catalog_status=%s\n"
        "policy_status=%s\n"
        "device_registry_status=%s\n"
        "vfs_namespace_status=%s\n"
        "ipc_table_status=%s\n"
        "syscall_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "driver_count=%lu\n"
        "no_effect=%d\n"
        "driver_probe_allowed=%d\n"
        "driver_load_allowed=%d\n"
        "driver_bind_allowed=%d\n"
        "interrupt_allowed=%d\n"
        "dma_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->catalog_status,
        result->policy_status,
        result->device_registry.registry_status,
        result->device_registry.vfs_namespace.namespace_status,
        result->device_registry.vfs_namespace.ipc_table.table_status,
        result->device_registry.vfs_namespace.ipc_table.syscall_table.table_status,
        result->device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        (unsigned long)result->driver_count,
        result->no_effect,
        result->driver_probe_allowed,
        result->driver_load_allowed,
        result->driver_bind_allowed,
        result->interrupt_allowed,
        result->dma_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->driver_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "driver[%lu].name=%s\n"
            "driver[%lu].token=%lu\n"
            "driver[%lu].device_path=%s\n"
            "driver[%lu].device_class=%s\n"
            "driver[%lu].driver_class=%s\n"
            "driver[%lu].backing=%s\n"
            "driver[%lu].catalog_status=%s\n"
            "driver[%lu].authority_status=%s\n"
            "driver[%lu].declared=%d\n"
            "driver[%lu].loaded=%d\n"
            "driver[%lu].bound=%d\n"
            "driver[%lu].probe_allowed=%d\n"
            "driver[%lu].load_allowed=%d\n"
            "driver[%lu].bind_allowed=%d\n"
            "driver[%lu].interrupt_allowed=%d\n"
            "driver[%lu].dma_allowed=%d\n"
            "driver[%lu].hardware_effect_allowed=%d\n"
            "driver[%lu].host_effect_allowed=%d\n"
            "driver[%lu].no_effect=%d\n",
            (unsigned long)i, result->drivers[i].name,
            (unsigned long)i, result->drivers[i].driver_token,
            (unsigned long)i, result->drivers[i].device_path,
            (unsigned long)i, result->drivers[i].device_class,
            (unsigned long)i, result->drivers[i].driver_class,
            (unsigned long)i, result->drivers[i].backing,
            (unsigned long)i, result->drivers[i].catalog_status,
            (unsigned long)i, result->drivers[i].authority_status,
            (unsigned long)i, result->drivers[i].declared,
            (unsigned long)i, result->drivers[i].loaded,
            (unsigned long)i, result->drivers[i].bound,
            (unsigned long)i, result->drivers[i].probe_allowed,
            (unsigned long)i, result->drivers[i].load_allowed,
            (unsigned long)i, result->drivers[i].bind_allowed,
            (unsigned long)i, result->drivers[i].interrupt_allowed,
            (unsigned long)i, result->drivers[i].dma_allowed,
            (unsigned long)i, result->drivers[i].hardware_effect_allowed,
            (unsigned long)i, result->drivers[i].host_effect_allowed,
            (unsigned long)i, result->drivers[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
