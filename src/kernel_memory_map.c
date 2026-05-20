#include "latticra/kernel_memory_map.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void memory_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void memory_seed_result(latticra_kernel_memory_map_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    memory_copy(result->map_status, sizeof(result->map_status), "pending");
    memory_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->mapping_allowed = 0;
    result->write_allowed = 0;
    result->execute_allowed = 0;
    result->evidence_level = 7u;
}

latticra_status_t latticra_kernel_memory_map_default_request(
    latticra_kernel_memory_map_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_scheduler_default_request(&request->scheduler_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_region_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_region(
    latticra_kernel_memory_map_region_t *region,
    size_t index,
    const char *label,
    const char *role,
    unsigned long base_token,
    unsigned long size_token) {
    memset(region, 0, sizeof(*region));
    region->region_index = index;
    memory_copy(region->label, sizeof(region->label), label);
    memory_copy(region->role, sizeof(region->role), role);
    memory_copy(region->map_status, sizeof(region->map_status), "metadata-only");
    region->base_token = base_token;
    region->size_token = size_token;
    region->mapped = 0;
    region->writable = 0;
    region->executable = 0;
    region->no_effect = 1;
    region->evidence_level = 7u;
}

static void fill_regions(latticra_kernel_memory_map_result_t *result, size_t requested_region_count) {
    size_t count = requested_region_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_MEMORY_MAP_REGION_MAX) count = LATTICRA_KERNEL_MEMORY_MAP_REGION_MAX;

    result->region_count = count;
    if (count > 0u) fill_region(&result->regions[0], 0u, "kernel-text-metadata", "code-region-label", 0x1000ul, 0x1000ul);
    if (count > 1u) fill_region(&result->regions[1], 1u, "kernel-data-metadata", "data-region-label", 0x2000ul, 0x1000ul);
    if (count > 2u) fill_region(&result->regions[2], 2u, "kernel-stack-metadata", "stack-region-label", 0x3000ul, 0x1000ul);
    if (count > 3u) fill_region(&result->regions[3], 3u, "kernel-report-metadata", "report-region-label", 0x4000ul, 0x1000ul);
    for (i = 4u; i < count; ++i) {
        fill_region(&result->regions[i], i, "reserved-memory-metadata", "reserved-region-label", 0x5000ul + (unsigned long)i * 0x1000ul, 0x1000ul);
    }
}

latticra_status_t latticra_kernel_memory_map_evaluate(
    const latticra_kernel_memory_map_request_t *request,
    latticra_kernel_memory_map_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memory_seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        memory_copy(result->map_status, sizeof(result->map_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_scheduler_evaluate(&request->scheduler_request, &result->scheduler);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        memory_copy(result->map_status, sizeof(result->map_status), "scheduler-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_regions(result, request->requested_region_count);
    result->no_effect = result->scheduler.no_effect;
    memory_copy(result->map_status, sizeof(result->map_status),
        result->no_effect ? "memory-map-seed-ready" : "memory-map-seed-blocked");
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

latticra_status_t latticra_kernel_memory_map_report(
    const latticra_kernel_memory_map_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL MEMORY MAP REPORT\n"
        "map_status=%s\n"
        "policy_status=%s\n"
        "scheduler_status=%s\n"
        "kernel_status=%s\n"
        "region_count=%lu\n"
        "no_effect=%d\n"
        "mapping_allowed=%d\n"
        "write_allowed=%d\n"
        "execute_allowed=%d\n"
        "evidence_level=%u\n",
        result->map_status,
        result->policy_status,
        result->scheduler.scheduler_status,
        result->scheduler.registry.kernel.kernel_status,
        (unsigned long)result->region_count,
        result->no_effect,
        result->mapping_allowed,
        result->write_allowed,
        result->execute_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->region_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "region[%lu].label=%s\n"
            "region[%lu].role=%s\n"
            "region[%lu].map_status=%s\n"
            "region[%lu].base_token=%lu\n"
            "region[%lu].size_token=%lu\n"
            "region[%lu].mapped=%d\n"
            "region[%lu].writable=%d\n"
            "region[%lu].executable=%d\n"
            "region[%lu].no_effect=%d\n",
            (unsigned long)i, result->regions[i].label,
            (unsigned long)i, result->regions[i].role,
            (unsigned long)i, result->regions[i].map_status,
            (unsigned long)i, result->regions[i].base_token,
            (unsigned long)i, result->regions[i].size_token,
            (unsigned long)i, result->regions[i].mapped,
            (unsigned long)i, result->regions[i].writable,
            (unsigned long)i, result->regions[i].executable,
            (unsigned long)i, result->regions[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
