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
        case LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY:
            return "interrupt-table-ready";
        case LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY:
            return "timer-source-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY:
            return "scheduler-tick-ready";
        case LATTICRA_KERNEL_STATE_RUN_QUEUE_READY:
            return "run-queue-ready";
        case LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY:
            return "context-switch-ready";
        case LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY:
            return "time-accounting-ready";
        case LATTICRA_KERNEL_STATE_PREEMPTION_READY:
            return "preemption-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY:
            return "scheduler-credit-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY:
            return "scheduler-selection-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY:
            return "scheduler-dispatch-ready";
        case LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY:
            return "scheduler-handoff-ready";
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
    if (current_state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY &&
        target_state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY &&
        target_state == LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY &&
        target_state == LATTICRA_KERNEL_STATE_RUN_QUEUE_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_RUN_QUEUE_READY &&
        target_state == LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY &&
        target_state == LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY &&
        target_state == LATTICRA_KERNEL_STATE_PREEMPTION_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_PREEMPTION_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY) return 1;
    if (current_state == LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY &&
        target_state == LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY) return 1;
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

static int state_requires_interrupt_table(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
}

static int state_requires_timer_source(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;
}

static int state_requires_scheduler_tick(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;
}

static int state_requires_run_queue(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;
}

static int state_requires_context_switch(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY;
}

static int state_requires_time_accounting(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY;
}

static int state_requires_preemption(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_PREEMPTION_READY;
}

static int state_requires_scheduler_credit(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY;
}

static int state_requires_scheduler_selection(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY;
}

static int state_requires_scheduler_dispatch(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY;
}

static int state_requires_scheduler_handoff(latticra_kernel_state_kind_t state) {
    return state >= LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY;
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
    result->network_allowed = 0;
    result->denied = 1;
    result->evidence_level = 8u;
}

static void update_network_evidence(latticra_kernel_state_result_t *result) {
    result->network_allowed =
        result->syscall_table.network_allowed || result->ipc_table.network_allowed;
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
    if (latticra_kernel_interrupt_table_default_request(&request->interrupt_table_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (latticra_kernel_timer_source_default_request(&request->timer_source_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->timer_source_request.interrupt_table_request = request->interrupt_table_request;
    if (latticra_kernel_scheduler_tick_default_request(&request->scheduler_tick_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_tick_request.timer_source_request = request->timer_source_request;
    if (latticra_kernel_run_queue_default_request(&request->run_queue_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->run_queue_request.scheduler_tick_request = request->scheduler_tick_request;
    if (latticra_kernel_context_switch_default_request(&request->context_switch_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->context_switch_request.run_queue_request = request->run_queue_request;
    if (latticra_kernel_time_accounting_default_request(&request->time_accounting_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->time_accounting_request.context_switch_request = request->context_switch_request;
    if (latticra_kernel_preemption_default_request(&request->preemption_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->preemption_request.time_accounting_request = request->time_accounting_request;
    if (latticra_kernel_scheduler_credit_default_request(
            &request->scheduler_credit_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_credit_request.preemption_request = request->preemption_request;
    if (latticra_kernel_scheduler_selection_default_request(
            &request->scheduler_selection_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_selection_request.scheduler_credit_request =
        request->scheduler_credit_request;
    if (latticra_kernel_scheduler_dispatch_default_request(
            &request->scheduler_dispatch_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_dispatch_request.scheduler_selection_request =
        request->scheduler_selection_request;
    if (latticra_kernel_scheduler_handoff_default_request(
            &request->scheduler_handoff_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->scheduler_handoff_request.scheduler_dispatch_request =
        request->scheduler_dispatch_request;
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
    latticra_kernel_interrupt_table_request_t interrupt_request;
    latticra_kernel_timer_source_request_t timer_request;
    latticra_kernel_scheduler_tick_request_t scheduler_tick_request;
    latticra_kernel_run_queue_request_t run_queue_request;
    latticra_kernel_context_switch_request_t context_switch_request;
    latticra_kernel_time_accounting_request_t time_accounting_request;
    latticra_kernel_preemption_request_t preemption_request;
    latticra_kernel_scheduler_credit_request_t scheduler_credit_request;
    latticra_kernel_scheduler_selection_request_t scheduler_selection_request;
    latticra_kernel_scheduler_dispatch_request_t scheduler_dispatch_request;
    latticra_kernel_scheduler_handoff_request_t scheduler_handoff_request;

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
    interrupt_request = request->interrupt_table_request;
    interrupt_request.driver_catalog_request = driver_request;
    timer_request = request->timer_source_request;
    timer_request.interrupt_table_request = interrupt_request;
    scheduler_tick_request = request->scheduler_tick_request;
    scheduler_tick_request.timer_source_request = timer_request;
    run_queue_request = request->run_queue_request;
    run_queue_request.scheduler_tick_request = scheduler_tick_request;
    context_switch_request = request->context_switch_request;
    context_switch_request.run_queue_request = run_queue_request;
    time_accounting_request = request->time_accounting_request;
    time_accounting_request.context_switch_request = context_switch_request;
    preemption_request = request->preemption_request;
    preemption_request.time_accounting_request = time_accounting_request;
    scheduler_credit_request = request->scheduler_credit_request;
    scheduler_credit_request.preemption_request = preemption_request;
    scheduler_selection_request = request->scheduler_selection_request;
    scheduler_selection_request.scheduler_credit_request = scheduler_credit_request;
    scheduler_dispatch_request = request->scheduler_dispatch_request;
    scheduler_dispatch_request.scheduler_selection_request =
        scheduler_selection_request;
    scheduler_handoff_request = request->scheduler_handoff_request;
    scheduler_handoff_request.scheduler_dispatch_request =
        scheduler_dispatch_request;

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
        interrupt_request.driver_catalog_request = driver_request;
        timer_request.interrupt_table_request = interrupt_request;
        scheduler_tick_request.timer_source_request = timer_request;
        run_queue_request.scheduler_tick_request = scheduler_tick_request;
        context_switch_request.run_queue_request = run_queue_request;
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
        interrupt_request.driver_catalog_request = driver_request;
        timer_request.interrupt_table_request = interrupt_request;
        scheduler_tick_request.timer_source_request = timer_request;
        run_queue_request.scheduler_tick_request = scheduler_tick_request;
        context_switch_request.run_queue_request = run_queue_request;
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
        interrupt_request.driver_catalog_request = driver_request;
        timer_request.interrupt_table_request = interrupt_request;
        scheduler_tick_request.timer_source_request = timer_request;
        run_queue_request.scheduler_tick_request = scheduler_tick_request;
        context_switch_request.run_queue_request = run_queue_request;
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
        interrupt_request.driver_catalog_request = driver_request;
        timer_request.interrupt_table_request = interrupt_request;
        scheduler_tick_request.timer_source_request = timer_request;
        run_queue_request.scheduler_tick_request = scheduler_tick_request;
        context_switch_request.run_queue_request = run_queue_request;
    }

    if (state_requires_interrupt_table(request->target_state)) {
        status = latticra_kernel_interrupt_table_evaluate(&interrupt_request,
            &result->interrupt_table);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "interrupt-table-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_timer_source(request->target_state)) {
        timer_request.interrupt_table_request = interrupt_request;
        status = latticra_kernel_timer_source_evaluate(&timer_request,
            &result->timer_source);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "timer-source-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_scheduler_tick(request->target_state)) {
        scheduler_tick_request.timer_source_request = timer_request;
        status = latticra_kernel_scheduler_tick_evaluate(&scheduler_tick_request,
            &result->scheduler_tick);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "scheduler-tick-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_run_queue(request->target_state)) {
        run_queue_request.scheduler_tick_request = scheduler_tick_request;
        status = latticra_kernel_run_queue_evaluate(&run_queue_request,
            &result->run_queue);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "run-queue-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_context_switch(request->target_state)) {
        context_switch_request.run_queue_request = run_queue_request;
        status = latticra_kernel_context_switch_evaluate(&context_switch_request,
            &result->context_switch);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "context-switch-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_time_accounting(request->target_state)) {
        time_accounting_request.context_switch_request = context_switch_request;
        status = latticra_kernel_time_accounting_evaluate(&time_accounting_request,
            &result->time_accounting);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "time-accounting-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_preemption(request->target_state)) {
        preemption_request.time_accounting_request = time_accounting_request;
        status = latticra_kernel_preemption_evaluate(&preemption_request,
            &result->preemption);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "preemption-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->time_accounting = result->preemption.time_accounting;
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_scheduler_credit(request->target_state)) {
        scheduler_credit_request.preemption_request = preemption_request;
        status = latticra_kernel_scheduler_credit_evaluate(
            &scheduler_credit_request, &result->scheduler_credit);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "scheduler-credit-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->preemption = result->scheduler_credit.preemption;
        result->time_accounting = result->preemption.time_accounting;
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_scheduler_selection(request->target_state)) {
        scheduler_selection_request.scheduler_credit_request =
            scheduler_credit_request;
        status = latticra_kernel_scheduler_selection_evaluate(
            &scheduler_selection_request, &result->scheduler_selection);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "scheduler-selection-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->scheduler_credit = result->scheduler_selection.scheduler_credit;
        result->preemption = result->scheduler_credit.preemption;
        result->time_accounting = result->preemption.time_accounting;
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_scheduler_dispatch(request->target_state)) {
        scheduler_dispatch_request.scheduler_selection_request =
            scheduler_selection_request;
        status = latticra_kernel_scheduler_dispatch_evaluate(
            &scheduler_dispatch_request, &result->scheduler_dispatch);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "scheduler-dispatch-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->scheduler_selection =
            result->scheduler_dispatch.scheduler_selection;
        result->scheduler_credit = result->scheduler_selection.scheduler_credit;
        result->preemption = result->scheduler_credit.preemption;
        result->time_accounting = result->preemption.time_accounting;
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    if (state_requires_scheduler_handoff(request->target_state)) {
        scheduler_handoff_request.scheduler_dispatch_request =
            scheduler_dispatch_request;
        status = latticra_kernel_scheduler_handoff_evaluate(
            &scheduler_handoff_request, &result->scheduler_handoff);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            state_copy(result->state_status, sizeof(result->state_status),
                "scheduler-handoff-not-ready");
            state_copy(result->transition_status, sizeof(result->transition_status), "blocked");
            return status;
        }
        result->scheduler_dispatch =
            result->scheduler_handoff.scheduler_dispatch;
        result->scheduler_selection =
            result->scheduler_dispatch.scheduler_selection;
        result->scheduler_credit = result->scheduler_selection.scheduler_credit;
        result->preemption = result->scheduler_credit.preemption;
        result->time_accounting = result->preemption.time_accounting;
        result->context_switch = result->time_accounting.context_switch;
        result->run_queue = result->context_switch.run_queue;
        result->scheduler_tick = result->run_queue.scheduler_tick;
        result->timer_source = result->scheduler_tick.timer_source;
        result->interrupt_table = result->timer_source.interrupt_table;
        result->driver_catalog = result->interrupt_table.driver_catalog;
        result->device_registry = result->driver_catalog.device_registry;
        result->vfs_namespace = result->device_registry.vfs_namespace;
        result->ipc_table = result->vfs_namespace.ipc_table;
        result->syscall_table = result->ipc_table.syscall_table;
        result->process_table = result->syscall_table.process_table;
        result->memory_map = result->process_table.memory_map;
    }

    update_network_evidence(result);

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
        "network_allowed=%d\n"
        "syscall_network_allowed=%d\n"
        "ipc_network_allowed=%d\n"
        "denied=%d\n"
        "memory_map_status=%s\n"
        "process_table_status=%s\n"
        "syscall_table_status=%s\n"
        "ipc_table_status=%s\n"
        "vfs_namespace_status=%s\n"
        "device_registry_status=%s\n"
        "driver_catalog_status=%s\n"
        "interrupt_table_status=%s\n"
        "timer_source_status=%s\n"
        "scheduler_tick_status=%s\n"
        "run_queue_status=%s\n"
        "context_switch_status=%s\n"
        "time_accounting_status=%s\n"
        "preemption_status=%s\n"
        "scheduler_credit_status=%s\n"
        "scheduler_selection_status=%s\n"
        "scheduler_dispatch_status=%s\n"
        "scheduler_handoff_status=%s\n"
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
        result->network_allowed,
        result->syscall_table.network_allowed,
        result->ipc_table.network_allowed,
        result->denied,
        result->memory_map.map_status,
        result->process_table.table_status,
        result->syscall_table.table_status,
        result->ipc_table.table_status,
        result->vfs_namespace.namespace_status,
        result->device_registry.registry_status,
        result->driver_catalog.catalog_status,
        result->interrupt_table.table_status,
        result->timer_source.timer_status,
        result->scheduler_tick.tick_status,
        result->run_queue.queue_status,
        result->context_switch.switch_status,
        result->time_accounting.accounting_status,
        result->preemption.preemption_status,
        result->scheduler_credit.credit_status,
        result->scheduler_selection.selection_status,
        result->scheduler_dispatch.dispatch_status,
        result->scheduler_handoff.handoff_status,
        result->evidence_level);

    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
