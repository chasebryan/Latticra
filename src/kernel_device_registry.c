#include "latticra/kernel_device_registry.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void device_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_device_registry_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    device_copy(result->registry_status, sizeof(result->registry_status), "pending");
    device_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->device_open_allowed = 0;
    result->device_read_allowed = 0;
    result->device_write_allowed = 0;
    result->driver_bind_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 12u;
}

latticra_status_t latticra_kernel_device_registry_default_request(
    latticra_kernel_device_registry_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_vfs_namespace_default_request(&request->vfs_namespace_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_device_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_device(
    latticra_kernel_device_registry_entry_t *device,
    size_t index,
    unsigned long device_token,
    const char *path,
    const char *label,
    const char *device_class,
    const char *backing) {
    memset(device, 0, sizeof(*device));
    device->device_index = index;
    device->device_token = device_token;
    device_copy(device->path, sizeof(device->path), path);
    device_copy(device->label, sizeof(device->label), label);
    device_copy(device->device_class, sizeof(device->device_class), device_class);
    device_copy(device->backing, sizeof(device->backing), backing);
    device_copy(device->registry_status, sizeof(device->registry_status),
        "declared-metadata");
    device_copy(device->authority_status, sizeof(device->authority_status),
        "device-access-denied");
    device->declared = 1;
    device->registered = 0;
    device->open_allowed = 0;
    device->read_allowed = 0;
    device->write_allowed = 0;
    device->driver_bind_allowed = 0;
    device->hardware_effect_allowed = 0;
    device->host_effect_allowed = 0;
    device->no_effect = 1;
    device->evidence_level = 12u;
}

static void fill_devices(
    latticra_kernel_device_registry_result_t *result,
    size_t requested_device_count) {
    size_t count = requested_device_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_DEVICE_REGISTRY_DEVICE_MAX) {
        count = LATTICRA_KERNEL_DEVICE_REGISTRY_DEVICE_MAX;
    }

    result->device_count = count;
    if (count > 0u) {
        fill_device(&result->devices[0], 0u, 0ul, "/dev/console",
            "console-device-metadata", "character-device",
            "vfs-namespace-metadata");
    }
    if (count > 1u) {
        fill_device(&result->devices[1], 1u, 1ul, "/dev/root",
            "block-root-device-metadata", "block-device",
            "vfs-namespace-metadata");
    }
    if (count > 2u) {
        fill_device(&result->devices[2], 2u, 2ul, "/dev/random",
            "entropy-device-metadata", "character-device",
            "vfs-namespace-metadata");
    }
    if (count > 3u) {
        fill_device(&result->devices[3], 3u, 3ul, "/dev/clock",
            "clock-device-metadata", "timer-device",
            "vfs-namespace-metadata");
    }
    for (i = 4u; i < count; ++i) {
        fill_device(&result->devices[i], i, 1000ul + (unsigned long)i,
            "/dev/reserved", "reserved-device-metadata",
            "reserved-device", "reserved-vfs-metadata");
    }
}

latticra_status_t latticra_kernel_device_registry_evaluate(
    const latticra_kernel_device_registry_request_t *request,
    latticra_kernel_device_registry_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        device_copy(result->registry_status, sizeof(result->registry_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_vfs_namespace_evaluate(&request->vfs_namespace_request,
        &result->vfs_namespace);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        device_copy(result->registry_status, sizeof(result->registry_status),
            "vfs-namespace-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_devices(result, request->requested_device_count);
    result->no_effect = result->vfs_namespace.no_effect;
    device_copy(result->registry_status, sizeof(result->registry_status),
        result->no_effect ? "device-registry-seed-ready" :
            "device-registry-seed-blocked");
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

latticra_status_t latticra_kernel_device_registry_report(
    const latticra_kernel_device_registry_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL DEVICE REGISTRY REPORT\n"
        "registry_status=%s\n"
        "policy_status=%s\n"
        "vfs_namespace_status=%s\n"
        "ipc_table_status=%s\n"
        "syscall_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "device_count=%lu\n"
        "no_effect=%d\n"
        "device_open_allowed=%d\n"
        "device_read_allowed=%d\n"
        "device_write_allowed=%d\n"
        "driver_bind_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->registry_status,
        result->policy_status,
        result->vfs_namespace.namespace_status,
        result->vfs_namespace.ipc_table.table_status,
        result->vfs_namespace.ipc_table.syscall_table.table_status,
        result->vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        (unsigned long)result->device_count,
        result->no_effect,
        result->device_open_allowed,
        result->device_read_allowed,
        result->device_write_allowed,
        result->driver_bind_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->device_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "device[%lu].path=%s\n"
            "device[%lu].token=%lu\n"
            "device[%lu].label=%s\n"
            "device[%lu].class=%s\n"
            "device[%lu].backing=%s\n"
            "device[%lu].registry_status=%s\n"
            "device[%lu].authority_status=%s\n"
            "device[%lu].declared=%d\n"
            "device[%lu].registered=%d\n"
            "device[%lu].open_allowed=%d\n"
            "device[%lu].read_allowed=%d\n"
            "device[%lu].write_allowed=%d\n"
            "device[%lu].driver_bind_allowed=%d\n"
            "device[%lu].hardware_effect_allowed=%d\n"
            "device[%lu].host_effect_allowed=%d\n"
            "device[%lu].no_effect=%d\n",
            (unsigned long)i, result->devices[i].path,
            (unsigned long)i, result->devices[i].device_token,
            (unsigned long)i, result->devices[i].label,
            (unsigned long)i, result->devices[i].device_class,
            (unsigned long)i, result->devices[i].backing,
            (unsigned long)i, result->devices[i].registry_status,
            (unsigned long)i, result->devices[i].authority_status,
            (unsigned long)i, result->devices[i].declared,
            (unsigned long)i, result->devices[i].registered,
            (unsigned long)i, result->devices[i].open_allowed,
            (unsigned long)i, result->devices[i].read_allowed,
            (unsigned long)i, result->devices[i].write_allowed,
            (unsigned long)i, result->devices[i].driver_bind_allowed,
            (unsigned long)i, result->devices[i].hardware_effect_allowed,
            (unsigned long)i, result->devices[i].host_effect_allowed,
            (unsigned long)i, result->devices[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
