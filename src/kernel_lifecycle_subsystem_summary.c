// SPDX-License-Identifier: AGPL-3.0-or-later

#include "latticra/kernel_lifecycle_subsystem_summary.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void summary_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_summary_result(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    summary_copy(result->summary_status, sizeof(result->summary_status), "pending");
    summary_copy(result->final_state, sizeof(result->final_state), "created");
    result->runtime_entry_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->memory_allocation_allowed = 0;
    result->process_spawn_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->ipc_send_allowed = 0;
    result->ipc_receive_allowed = 0;
    result->filesystem_lookup_allowed = 0;
    result->filesystem_read_allowed = 0;
    result->filesystem_write_allowed = 0;
    result->namespace_mutation_allowed = 0;
    result->no_external_effect_chain = 1;
    result->evidence_level = 11u;
}

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_default_request(
    latticra_kernel_lifecycle_subsystem_summary_request_t *request) {
    latticra_status_t status;

    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));

    status = latticra_kernel_lifecycle_default_request(&request->lifecycle_request);
    if (status != LATTICRA_STATUS_OK) return status;

    status = latticra_kernel_subsystem_registry_default_request(&request->registry_request);
    if (status != LATTICRA_STATUS_OK) return status;

    request->lifecycle_request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request->lifecycle_request.target_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
    request->lifecycle_request.max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    return LATTICRA_STATUS_OK;
}

static int state_at_or_after(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_state_kind_t required_state) {
    return final_state >= required_state;
}

static int lifecycle_ready_for_subsystem(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INITIALIZED);
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SCHEDULER_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_MEMORY_MAP_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_IPC_TABLE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY);
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return 0;
    }
}

static const char *lifecycle_relation_for(
    latticra_kernel_state_kind_t final_state,
    latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_INITIALIZED) ?
                "boot-sequence-seeded" : "boot-sequence-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
            return "runtime-not-entered";
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SCHEDULER_READY) ?
                "scheduler-ready-metadata" : "scheduler-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_MEMORY_MAP_READY) ?
                "memory-map-ready" : "memory-map-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_IPC_TABLE_READY) ?
                "ipc-table-ready" : (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY) ?
                        "process-table-ready" : "process-table-not-ready");
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY) ?
                "vfs-namespace-ready" : (state_at_or_after(final_state,
                    LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) ?
                        "filesystem-syscall-metadata-ready" :
                        "filesystem-syscall-metadata-not-ready");
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) ?
                "network-syscall-metadata-ready" : "network-syscall-metadata-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return state_at_or_after(final_state, LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) ?
                "device-syscall-metadata-ready" : "device-syscall-metadata-not-ready";
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
            return "security-not-production-boundary";
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return "unknown";
    }
}

static const char *authority_status_for(latticra_kernel_subsystem_kind_t kind) {
    switch (kind) {
        case LATTICRA_KERNEL_SUBSYSTEM_BOOT:
            return "boot-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_RUNTIME:
            return "runtime-entry-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER:
            return "scheduler-execution-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_MEMORY:
            return "memory-allocation-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_PROCESS:
            return "process-execution-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM:
            return "filesystem-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_NETWORK:
            return "network-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_DEVICE:
            return "device-denied";
        case LATTICRA_KERNEL_SUBSYSTEM_SECURITY:
            return "not-production-boundary";
        case LATTICRA_KERNEL_SUBSYSTEM_COUNT:
        default:
            return "unknown-denied";
    }
}

static void fill_summary_entries(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    size_t i;
    size_t count = result->registry.entry_count;

    if (count > LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX) {
        count = LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_ENTRY_MAX;
    }

    result->entry_count = count;

    for (i = 0u; i < count; ++i) {
        latticra_kernel_lifecycle_subsystem_summary_entry_t *entry = &result->entries[i];
        const latticra_kernel_subsystem_entry_t *registry_entry = &result->registry.entries[i];

        memset(entry, 0, sizeof(*entry));
        entry->kind = registry_entry->kind;
        summary_copy(entry->name, sizeof(entry->name), registry_entry->name);
        summary_copy(entry->registry_status, sizeof(entry->registry_status), registry_entry->status);
        summary_copy(entry->lifecycle_relation, sizeof(entry->lifecycle_relation),
            lifecycle_relation_for(result->lifecycle.final_state, registry_entry->kind));
        summary_copy(entry->authority_status, sizeof(entry->authority_status),
            authority_status_for(registry_entry->kind));
        summary_copy(entry->effect_boundary, sizeof(entry->effect_boundary), registry_entry->effect_boundary);
        entry->lifecycle_ready = lifecycle_ready_for_subsystem(
            result->lifecycle.final_state,
            registry_entry->kind);
        entry->authority_allowed = 0;
        entry->no_effect = registry_entry->no_effect;
        entry->evidence_level = registry_entry->evidence_level;
    }
}

static void finalize_summary(
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    summary_copy(result->final_state, sizeof(result->final_state),
        latticra_kernel_state_label(result->lifecycle.final_state));

    result->lifecycle_step_count = result->lifecycle.step_count;
    result->lifecycle_state_change_count = result->lifecycle.state_change_count;
    result->lifecycle_complete = result->lifecycle.lifecycle_complete;
    result->lifecycle_state_mutated = result->lifecycle.state_change_count > 0u;
    result->external_effect_performed = result->lifecycle.external_effect_performed;
    result->registry_no_effect = result->registry.no_effect;
    result->runtime_entry_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->memory_allocation_allowed = 0;
    result->process_spawn_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->ipc_send_allowed = 0;
    result->ipc_receive_allowed = 0;
    result->filesystem_lookup_allowed = 0;
    result->filesystem_read_allowed = 0;
    result->filesystem_write_allowed = 0;
    result->namespace_mutation_allowed = 0;
    result->no_external_effect_chain =
        result->external_effect_performed == 0 && result->registry_no_effect == 1;

    fill_summary_entries(result);

    summary_copy(result->summary_status, sizeof(result->summary_status),
        (result->lifecycle_complete == 1 &&
         result->lifecycle.final_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY &&
         result->registry_no_effect == 1 &&
         result->external_effect_performed == 0) ?
            "summary-ready" : "summary-incomplete");
}

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_evaluate(
    const latticra_kernel_lifecycle_subsystem_summary_request_t *request,
    latticra_kernel_lifecycle_subsystem_summary_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_summary_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        summary_copy(result->summary_status, sizeof(result->summary_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_lifecycle_run(&request->lifecycle_request, &result->lifecycle);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        summary_copy(result->summary_status, sizeof(result->summary_status), "lifecycle-failed");
        return status;
    }

    status = latticra_kernel_subsystem_registry_evaluate(&request->registry_request, &result->registry);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        summary_copy(result->summary_status, sizeof(result->summary_status), "registry-failed");
        return status;
    }

    finalize_summary(result);
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

latticra_status_t latticra_kernel_lifecycle_subsystem_summary_report(
    const latticra_kernel_lifecycle_subsystem_summary_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT\n"
        "summary_status=%s\n"
        "final_state=%s\n"
        "lifecycle_status=%s\n"
        "registry_status=%s\n"
        "lifecycle_complete=%d\n"
        "lifecycle_step_count=%lu\n"
        "lifecycle_state_change_count=%lu\n"
        "lifecycle_state_mutated=%d\n"
        "external_effect_performed=%d\n"
        "registry_no_effect=%d\n"
        "runtime_entry_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "memory_allocation_allowed=%d\n"
        "process_spawn_allowed=%d\n"
        "syscall_dispatch_allowed=%d\n"
        "ipc_send_allowed=%d\n"
        "ipc_receive_allowed=%d\n"
        "filesystem_lookup_allowed=%d\n"
        "filesystem_read_allowed=%d\n"
        "filesystem_write_allowed=%d\n"
        "namespace_mutation_allowed=%d\n"
        "no_external_effect_chain=%d\n"
        "entry_count=%lu\n"
        "evidence_level=%u\n",
        result->summary_status,
        result->final_state,
        result->lifecycle.lifecycle_status,
        result->registry.registry_status,
        result->lifecycle_complete,
        (unsigned long)result->lifecycle_step_count,
        (unsigned long)result->lifecycle_state_change_count,
        result->lifecycle_state_mutated,
        result->external_effect_performed,
        result->registry_no_effect,
        result->runtime_entry_allowed,
        result->scheduler_execution_allowed,
        result->memory_allocation_allowed,
        result->process_spawn_allowed,
        result->syscall_dispatch_allowed,
        result->ipc_send_allowed,
        result->ipc_receive_allowed,
        result->filesystem_lookup_allowed,
        result->filesystem_read_allowed,
        result->filesystem_write_allowed,
        result->namespace_mutation_allowed,
        result->no_external_effect_chain,
        (unsigned long)result->entry_count,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->entry_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "subsystem[%lu].name=%s\n"
            "subsystem[%lu].registry_status=%s\n"
            "subsystem[%lu].lifecycle_relation=%s\n"
            "subsystem[%lu].authority_status=%s\n"
            "subsystem[%lu].effect_boundary=%s\n"
            "subsystem[%lu].lifecycle_ready=%d\n"
            "subsystem[%lu].authority_allowed=%d\n"
            "subsystem[%lu].no_effect=%d\n"
            "subsystem[%lu].evidence_level=%u\n",
            (unsigned long)i,
            result->entries[i].name,
            (unsigned long)i,
            result->entries[i].registry_status,
            (unsigned long)i,
            result->entries[i].lifecycle_relation,
            (unsigned long)i,
            result->entries[i].authority_status,
            (unsigned long)i,
            result->entries[i].effect_boundary,
            (unsigned long)i,
            result->entries[i].lifecycle_ready,
            (unsigned long)i,
            result->entries[i].authority_allowed,
            (unsigned long)i,
            result->entries[i].no_effect,
            (unsigned long)i,
            result->entries[i].evidence_level);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
