#include "latticra/kernel_state.h"

#include <stdio.h>
#include <string.h>

static void state_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

const char *latticra_kernel_state_label(latticra_kernel_state_kind_t state) {
    switch (state) {
        case LATTICRA_KERNEL_STATE_CREATED:
            return "created";
        case LATTICRA_KERNEL_STATE_INITIALIZED:
            return "initialized";
        case LATTICRA_KERNEL_STATE_REGISTRY_READY:
            return "registry-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_READY:
            return "scheduler-ready";
        case LATTICRA_KERNEL_STATE_MEMORY_MAP_READY:
            return "memory-map-ready";
        case LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY:
            return "process-table-ready";
        case LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY:
            return "syscall-table-ready";
        case LATTICRA_KERNEL_STATE_IPC_TABLE_READY:
            return "ipc-table-ready";
        case LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY:
            return "vfs-namespace-ready";
        case LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY:
            return "device-registry-ready";
        case LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY:
            return "driver-catalog-ready";
        default:
            return "unknown";
    }
}

static int is_allowed_transition(
    latticra_kernel_state_kind_t current_state,
    latticra_kernel_state_kind_t target_state) {
    if (current_state == target_state) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_CREATED &&
        target_state == LATTICRA_KERNEL_STATE_INITIALIZED) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_INITIALIZED &&
        target_state == LATTICRA_KERNEL_STATE_REGISTRY_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_REGISTRY_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SCHEDULER_READY &&
        target_state == LATTICRA_KERNEL_STATE_MEMORY_MAP_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_MEMORY_MAP_READY &&
        target_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY &&
        target_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY &&
        target_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY &&
        target_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY &&
        target_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY &&
        target_state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY) return 1;
    return 0;
}

static int state_requires_process_table(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
}

static int state_requires_syscall_table(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
}

static int state_requires_ipc_table(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
}

static int state_requires_vfs_namespace(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
}

static int state_requires_device_registry(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;
}

static int state_requires_driver_catalog(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;
}

static void seed_result(latticra_kernel_state_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    state_copy(result->state_status, sizeof(result->state_status), "pending");
    state_copy(result->gate_status, sizeof(result->gate_status), "deny");
    state_copy(result->transition_status, sizeof(result->transition_status), "not-evaluated");
    state_copy(result->effect_status, sizeof(result->effect_status), "none");
    result->previous_state = LATTICRA_KERNEL_STATE_CREATED;
    result->target_state = LATTICRA_KERNEL_STATE_CREATED;
    result->next_state = LATTICRA_KERNEL_STATE_CREATED;
    result->state_change_performed = 0;
    result->external_effect_performed = 0;
    result->denied = 1;
    result->evidence_level = 8u;
}

latticra_status_t latticra_kernel_state_default_request(
    latticra_kernel_state_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_memory_map_default_request(&request->memory_map_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_process_table_default_request(&request->process_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_syscall_table_default_request(&request->syscall_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_ipc_table_default_request(&request->ipc_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_vfs_namespace_default_request(&request->vfs_namespace_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_device_registry_default_request(&request->device_registry_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_driver_catalog_default_request(&request->driver_catalog_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->current_state = LATTICRA_KERNEL_STATE_CREATED;
    request->target_state = LATTICRA_KERNEL_STATE_INITIALIZED;
    request->gate = LATTICRA_KERNEL_STATE_GATE_DENY;
    return LATTICRA_STATUS_OK;
}

static void deny_transition(latticra_kernel_state_result_t *result, const char *reason) {
    result->next_state = result->previous_state;
    result->state_change_performed = 0;
    result->external_effect_performed = 0;
    result->denied = 1;
    state_copy(result->state_status, sizeof(result->state_status), "unchanged");
    state_copy(result->transition_status, sizeof(result->transition_status), reason);
    state_copy(result->effect_status, sizeof(result->effect_status), "none");
}

latticra_status_t latticra_kernel_state_transition(
    const latticra_kernel_state_request_t *request,
    latticra_kernel_state_result_t *result) {
    latticra_status_t status;
    latticra_kernel_process_table_request_t process_request;
    latticra_kernel_syscall_table_request_t syscall_request;
    latticra_kernel_ipc_table_request_t ipc_request;
    latticra_kernel_vfs_namespace_request_t vfs_request;
    latticra_kernel_device_registry_request_t device_request;
    latticra_kernel_driver_catalog_request_t driver_request;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        state_copy(result->state_status, sizeof(result->state_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result->previous_state = request->current_state;
    result->target_state = request->target_state;
    result->next_state = request->current_state;

    status = latticra_kernel_memory_map_evaluate(&request->memory_map_request, &result->memory_map);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        state_copy(result->state_status, sizeof(result->state_status), "memory-map-not-ready");
        state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
        return status;
    }

    process_request = request->process_table_request;
    process_request.memory_map_request = request->memory_map_request;
    syscall_request = request->syscall_table_request;
    syscall_request.process_table_request = process_request;
    ipc_request = request->ipc_table_request;
    ipc_request.syscall_table_request = syscall_request;
    vfs_request = request->vfs_namespace_request;
    vfs_request.ipc_table_request = ipc_request;
    device_request = request->device_registry_request;
    device_request.vfs_namespace_request = vfs_request;
    driver_request = request->driver_catalog_request;
    driver_request.device_registry_request = device_request;

    if (state_requires_process_table(request->target_state)) {
        status = latticra_kernel_process_table_evaluate(&process_request, &result->process_table);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "process-table-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_syscall_table(request->target_state)) {
        status = latticra_kernel_syscall_table_evaluate(&syscall_request, &result->syscall_table);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "syscall-table-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
        ipc_request.syscall_table_request = syscall_request;
    }

    if (state_requires_ipc_table(request->target_state)) {
        status = latticra_kernel_ipc_table_evaluate(&ipc_request, &result->ipc_table);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "ipc-table-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
        vfs_request.ipc_table_request = ipc_request;
        device_request.vfs_namespace_request = vfs_request;
        driver_request.device_registry_request = device_request;
    }

    if (state_requires_vfs_namespace(request->target_state)) {
        status = latticra_kernel_vfs_namespace_evaluate(&vfs_request,
            &result->vfs_namespace);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "vfs-namespace-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
        device_request.vfs_namespace_request = vfs_request;
        driver_request.device_registry_request = device_request;
    }

    if (state_requires_device_registry(request->target_state)) {
        status = latticra_kernel_device_registry_evaluate(&device_request,
            &result->device_registry);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "device-registry-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
        driver_request.device_registry_request = device_request;
    }

    if (state_requires_driver_catalog(request->target_state)) {
        status = latticra_kernel_driver_catalog_evaluate(&driver_request,
            &result->driver_catalog);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "driver-catalog-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (request->gate != LATTICRA_KERNEL_STATE_GATE_ALLOW) {
        state_copy(result->gate_status, sizeof(result->gate_status), "deny");
        deny_transition(result, "gate-denied");
        return result->status;
    }

    state_copy(result->gate_status, sizeof(result->gate_status), "allow");

    if (!is_allowed_transition(request->current_state, request->target_state)) {
        deny_transition(result, "transition-denied");
        return result->status;
    }

    result->next_state = request->target_state;
    result->state_change_performed = request->current_state != request->target_state;
    result->external_effect_performed = 0;
    result->denied = 0;
    state_copy(result->state_status, sizeof(result->state_status),
        result->state_change_performed ? "changed" : "unchanged");
    state_copy(result->transition_status, sizeof(result->transition_status),
        result->state_change_performed ? "transition-applied" : "no-op");
    state_copy(result->effect_status, sizeof(result->effect_status),
        result->state_change_performed ? "in-memory-state-change" : "none");
    return result->status;
}

latticra_status_t latticra_kernel_state_report(
    const latticra_kernel_state_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    written = snprintf(buffer, buffer_len,
        "LATTICRA KERNEL STATE REPORT\n"
        "state_status=%s\n"
        "gate_status=%s\n"
        "transition_status=%s\n"
        "effect_status=%s\n"
        "previous_state=%s\n"
        "target_state=%s\n"
        "next_state=%s\n"
        "state_change_performed=%d\n"
        "external_effect_performed=%d\n"
        "denied=%d\n"
        "memory_map_status=%s\n"
        "process_table_status=%s\n"
        "syscall_table_status=%s\n"
        "ipc_table_status=%s\n"
        "vfs_namespace_status=%s\n"
        "device_registry_status=%s\n"
        "driver_catalog_status=%s\n"
        "evidence_level=%u\n",
        result->state_status,
        result->gate_status,
        result->transition_status,
        result->effect_status,
        latticra_kernel_state_label(result->previous_state),
        latticra_kernel_state_label(result->target_state),
        latticra_kernel_state_label(result->next_state),
        result->state_change_performed,
        result->external_effect_performed,
        result->denied,
        result->memory_map.map_status,
        result->process_table.table_status,
        result->syscall_table.table_status,
        result->ipc_table.table_status,
        result->vfs_namespace.namespace_status,
        result->device_registry.registry_status,
        result->driver_catalog.catalog_status,
        result->evidence_level);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
