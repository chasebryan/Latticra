#include "latticra/kernel_scheduler.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void scheduler_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void scheduler_seed_result(latticra_kernel_scheduler_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    scheduler_copy(result->scheduler_status, sizeof(result->scheduler_status), "pending");
    scheduler_copy(result->policy_status, sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->slot_selection_allowed = 0;
    result->scheduler_activation_allowed = 0;
    result->evidence_level = 6u;
}

latticra_status_t latticra_kernel_scheduler_default_request(
    latticra_kernel_scheduler_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_subsystem_registry_default_request(&request->registry_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_slot_count = 3u;
    return LATTICRA_STATUS_OK;
}

static void scheduler_fill_slot(
    latticra_kernel_scheduler_slot_t *slot,
    size_t index,
    const char *label) {
    memset(slot, 0, sizeof(*slot));
    slot->slot_index = index;
    scheduler_copy(slot->label, sizeof(slot->label), label);
    scheduler_copy(slot->state, sizeof(slot->state), "registered");
    scheduler_copy(slot->selection_status, sizeof(slot->selection_status), "not-selected");
    slot->selectable = 0;
    slot->selected = 0;
    slot->no_effect = 1;
    slot->evidence_level = 6u;
}

static void scheduler_fill_slots(latticra_kernel_scheduler_result_t *result, size_t requested_slot_count) {
    size_t count = requested_slot_count;
    size_t i;
    if (count == 0u) count = 3u;
    if (count > LATTICRA_KERNEL_SCHEDULER_SLOT_MAX) count = LATTICRA_KERNEL_SCHEDULER_SLOT_MAX;

    result->slot_count = count;
    if (count > 0u) scheduler_fill_slot(&result->slots[0], 0u, "idle-metadata");
    if (count > 1u) scheduler_fill_slot(&result->slots[1], 1u, "kernel-report-metadata");
    if (count > 2u) scheduler_fill_slot(&result->slots[2], 2u, "operator-report-metadata");
    for (i = 3u; i < count; ++i) {
        scheduler_fill_slot(&result->slots[i], i, "reserved-metadata");
    }
}

latticra_status_t latticra_kernel_scheduler_evaluate(
    const latticra_kernel_scheduler_request_t *request,
    latticra_kernel_scheduler_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    scheduler_seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        scheduler_copy(result->scheduler_status, sizeof(result->scheduler_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_subsystem_registry_evaluate(&request->registry_request, &result->registry);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        scheduler_copy(result->scheduler_status, sizeof(result->scheduler_status), "registry-not-ready");
        result->no_effect = 0;
        return status;
    }

    scheduler_fill_slots(result, request->requested_slot_count);
    result->no_effect = result->registry.no_effect;
    scheduler_copy(result->scheduler_status, sizeof(result->scheduler_status),
        result->no_effect ? "scheduler-seed-ready" : "scheduler-seed-blocked");
    return result->status;
}

static latticra_status_t scheduler_append_text(
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

latticra_status_t latticra_kernel_scheduler_report(
    const latticra_kernel_scheduler_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = scheduler_append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER REPORT\n"
        "scheduler_status=%s\n"
        "policy_status=%s\n"
        "registry_status=%s\n"
        "kernel_status=%s\n"
        "slot_count=%lu\n"
        "no_effect=%d\n"
        "slot_selection_allowed=%d\n"
        "scheduler_activation_allowed=%d\n"
        "evidence_level=%u\n",
        result->scheduler_status,
        result->policy_status,
        result->registry.registry_status,
        result->registry.kernel.kernel_status,
        (unsigned long)result->slot_count,
        result->no_effect,
        result->slot_selection_allowed,
        result->scheduler_activation_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->slot_count; ++i) {
        status = scheduler_append_text(buffer, buffer_len, &used,
            "slot[%lu].label=%s\n"
            "slot[%lu].state=%s\n"
            "slot[%lu].selection_status=%s\n"
            "slot[%lu].selectable=%d\n"
            "slot[%lu].selected=%d\n"
            "slot[%lu].no_effect=%d\n",
            (unsigned long)i, result->slots[i].label,
            (unsigned long)i, result->slots[i].state,
            (unsigned long)i, result->slots[i].selection_status,
            (unsigned long)i, result->slots[i].selectable,
            (unsigned long)i, result->slots[i].selected,
            (unsigned long)i, result->slots[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
