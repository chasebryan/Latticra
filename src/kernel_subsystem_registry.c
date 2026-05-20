#include "latticra/kernel_subsystem_registry.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void registry_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

const char *latticra_kernel_subsystem_kind_label(
    latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return "boot";
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
            return "runtime";
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return "scheduler";
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return "memory";
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return "process";
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return "filesystem";
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return "network";
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return "device";
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
            return "security";
        default:
            return "unknown";
    }
}

static void seed_registry_result(latticra_kernel_subsystem_registry_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    registry_copy(result->registry_status, sizeof(result->registry_status), "pending");
    result->no_effect = 1;
    result->evidence_level = 5u;
}

latticra_status_t latticra_kernel_subsystem_registry_default_request(
    latticra_kernel_subsystem_registry_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    return latticra_kernel_default_request(&request->kernel_request);
}

static void fill_entry(
    latticra_kernel_subsystem_entry_t *entry,
    latticra_kernel_subsystem_kind_t kind,
    const char *status,
    unsigned int evidence_level) {
    memset(entry, 0, sizeof(*entry));
    entry->kind = kind;
    registry_copy(entry->name, sizeof(entry->name), latticra_kernel_subsystem_kind_label(kind));
    registry_copy(entry->status, sizeof(entry->status), status);
    registry_copy(entry->effect_boundary, sizeof(entry->effect_boundary), "no-effect");
    entry->no_effect = 1;
    entry->active = 0;
    entry->evidence_level = evidence_level;
}

static void fill_entries(latticra_kernel_subsystem_registry_result_t *result) {
    result->entry_count = LATTICRA_KERNEL_SUBSYSTEM_COUNT;

    fill_entry(&result->entries[0], LATTICRA_KERNEL_SUBSYSTEM_BOOT,
        result->kernel.boot_status, result->evidence_level);
    fill_entry(&result->entries[1], LATTICRA_KERNEL_SUBSYSTEM_RUNTIME,
        result->kernel.runtime_status, result->evidence_level);
    fill_entry(&result->entries[2], LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER,
        result->kernel.scheduler_status, result->evidence_level);
    fill_entry(&result->entries[3], LATTICRA_KERNEL_SUBSYSTEM_MEMORY,
        result->kernel.memory_status, result->evidence_level);
    fill_entry(&result->entries[4], LATTICRA_KERNEL_SUBSYSTEM_PROCESS,
        result->kernel.process_status, result->evidence_level);
    fill_entry(&result->entries[5], LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM,
        result->kernel.filesystem_status, result->evidence_level);
    fill_entry(&result->entries[6], LATTICRA_KERNEL_SUBSYSTEM_NETWORK,
        result->kernel.network_status, result->evidence_level);
    fill_entry(&result->entries[7], LATTICRA_KERNEL_SUBSYSTEM_DEVICE,
        result->kernel.device_status, result->evidence_level);
    fill_entry(&result->entries[8], LATTICRA_KERNEL_SUBSYSTEM_SECURITY,
        result->kernel.security_status, result->evidence_level);
}

latticra_status_t latticra_kernel_subsystem_registry_evaluate(
    const latticra_kernel_subsystem_registry_request_t *request,
    latticra_kernel_subsystem_registry_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_registry_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        registry_copy(result->registry_status, sizeof(result->registry_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_initialize(&request->kernel_request, &result->kernel);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        registry_copy(result->registry_status, sizeof(result->registry_status), "kernel-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_entries(result);

    result->no_effect = result->kernel.no_effect;
    registry_copy(result->registry_status, sizeof(result->registry_status),
        result->no_effect ? "registry-ready" : "registry-blocked");
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

latticra_status_t latticra_kernel_subsystem_registry_report(
    const latticra_kernel_subsystem_registry_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SUBSYSTEM REGISTRY REPORT\n"
        "registry_status=%s\n"
        "kernel_status=%s\n"
        "kernel_no_effect=%d\n"
        "entry_count=%lu\n"
        "no_effect=%d\n"
        "evidence_level=%u\n",
        result->registry_status,
        result->kernel.kernel_status,
        result->kernel.no_effect,
        (unsigned long)result->entry_count,
        result->no_effect,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->entry_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "subsystem[%lu].name=%s\n"
            "subsystem[%lu].status=%s\n"
            "subsystem[%lu].effect_boundary=%s\n"
            "subsystem[%lu].no_effect=%d\n"
            "subsystem[%lu].active=%d\n"
            "subsystem[%lu].evidence_level=%u\n",
            (unsigned long)i,
            result->entries[i].name,
            (unsigned long)i,
            result->entries[i].status,
            (unsigned long)i,
            result->entries[i].effect_boundary,
            (unsigned long)i,
            result->entries[i].no_effect,
            (unsigned long)i,
            result->entries[i].active,
            (unsigned long)i,
            result->entries[i].evidence_level);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
