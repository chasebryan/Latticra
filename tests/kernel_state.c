#include "latticra/kernel_state.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_denies_state_change(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.current_state == LATTICRA_KERNEL_STATE_CREATED,
        "default current state");
    EXPECT_TRUE(request.target_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "default target state");
    EXPECT_TRUE(request.gate == LATTICRA_KERNEL_STATE_GATE_DENY,
        "default gate deny");

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "default transition evaluates");
    EXPECT_TRUE(strcmp(result.gate_status, "deny") == 0,
        "gate status deny");
    EXPECT_TRUE(strcmp(result.transition_status, "gate-denied") == 0,
        "transition denied by gate");
    EXPECT_TRUE(result.previous_state == LATTICRA_KERNEL_STATE_CREATED,
        "previous state created");
    EXPECT_TRUE(result.target_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "target state initialized");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_CREATED,
        "next state unchanged");
    EXPECT_TRUE(result.state_change_performed == 0,
        "default does not change state");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "no external effect");
    EXPECT_TRUE(result.denied == 1,
        "denied flag set");
    return 0;
}

static int allowed_transition_changes_state(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "allowed transition evaluates");
    EXPECT_TRUE(strcmp(result.gate_status, "allow") == 0,
        "gate status allow");
    EXPECT_TRUE(strcmp(result.transition_status, "transition-applied") == 0,
        "transition applied");
    EXPECT_TRUE(strcmp(result.effect_status, "in-memory-state-change") == 0,
        "effect status internal state change");
    EXPECT_TRUE(result.previous_state == LATTICRA_KERNEL_STATE_CREATED,
        "previous created");
    EXPECT_TRUE(result.target_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "target initialized");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "next initialized");
    EXPECT_TRUE(result.state_change_performed == 1,
        "state change performed");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "external effect remains absent");
    EXPECT_TRUE(result.denied == 0,
        "not denied");
    EXPECT_TRUE(strcmp(result.memory_map.map_status, "memory-map-seed-ready") == 0,
        "memory map ready");
    return 0;
}

static int allowed_process_syscall_ipc_vfs_device_driver_interrupt_timer_tick_queue_and_context_transitions_are_metadata_only(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for process state");
    request.current_state = LATTICRA_KERNEL_STATE_MEMORY_MAP_READY;
    request.target_state = LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "process-table transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY,
        "next process-table-ready");
    EXPECT_TRUE(strcmp(result.process_table.table_status, "process-table-seed-ready") == 0,
        "process table ready");
    EXPECT_TRUE(result.process_table.process_spawn_allowed == 0,
        "process spawn denied");
    EXPECT_TRUE(result.process_table.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "process transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "process transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "syscall-table transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY,
        "next syscall-table-ready");
    EXPECT_TRUE(strcmp(result.syscall_table.table_status, "syscall-table-seed-ready") == 0,
        "syscall table ready");
    EXPECT_TRUE(strcmp(result.process_table.table_status, "process-table-seed-ready") == 0,
        "syscall transition keeps process table ready");
    EXPECT_TRUE(result.syscall_table.syscall_dispatch_allowed == 0,
        "syscall dispatch denied");
    EXPECT_TRUE(result.syscall_table.file_io_allowed == 0,
        "syscall file I/O denied");
    EXPECT_TRUE(result.syscall_table.network_allowed == 0,
        "syscall network denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "syscall transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "syscall transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "ipc-table transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY,
        "next ipc-table-ready");
    EXPECT_TRUE(strcmp(result.ipc_table.table_status, "ipc-table-seed-ready") == 0,
        "ipc table ready");
    EXPECT_TRUE(strcmp(result.syscall_table.table_status, "syscall-table-seed-ready") == 0,
        "ipc transition keeps syscall table ready");
    EXPECT_TRUE(strcmp(result.process_table.table_status, "process-table-seed-ready") == 0,
        "ipc transition keeps process table ready");
    EXPECT_TRUE(result.ipc_table.ipc_send_allowed == 0,
        "ipc send denied");
    EXPECT_TRUE(result.ipc_table.ipc_receive_allowed == 0,
        "ipc receive denied");
    EXPECT_TRUE(result.ipc_table.queue_mutation_allowed == 0,
        "ipc queue mutation denied");
    EXPECT_TRUE(result.ipc_table.endpoint_bind_allowed == 0,
        "ipc endpoint bind denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "ipc transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "ipc transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "vfs namespace transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY,
        "next vfs-namespace-ready");
    EXPECT_TRUE(strcmp(result.vfs_namespace.namespace_status, "vfs-namespace-seed-ready") == 0,
        "vfs namespace ready");
    EXPECT_TRUE(strcmp(result.ipc_table.table_status, "ipc-table-seed-ready") == 0,
        "vfs transition keeps ipc table ready");
    EXPECT_TRUE(strcmp(result.syscall_table.table_status, "syscall-table-seed-ready") == 0,
        "vfs transition keeps syscall table ready");
    EXPECT_TRUE(result.vfs_namespace.filesystem_lookup_allowed == 0,
        "filesystem lookup denied");
    EXPECT_TRUE(result.vfs_namespace.filesystem_read_allowed == 0,
        "filesystem read denied");
    EXPECT_TRUE(result.vfs_namespace.filesystem_write_allowed == 0,
        "filesystem write denied");
    EXPECT_TRUE(result.vfs_namespace.namespace_mutation_allowed == 0,
        "namespace mutation denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "vfs transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "vfs transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "device registry transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY,
        "next device-registry-ready");
    EXPECT_TRUE(strcmp(result.device_registry.registry_status, "device-registry-seed-ready") == 0,
        "device registry ready");
    EXPECT_TRUE(strcmp(result.vfs_namespace.namespace_status, "vfs-namespace-seed-ready") == 0,
        "device transition keeps vfs namespace ready");
    EXPECT_TRUE(result.device_registry.device_open_allowed == 0,
        "device open denied");
    EXPECT_TRUE(result.device_registry.device_read_allowed == 0,
        "device read denied");
    EXPECT_TRUE(result.device_registry.device_write_allowed == 0,
        "device write denied");
    EXPECT_TRUE(result.device_registry.driver_bind_allowed == 0,
        "driver bind denied");
    EXPECT_TRUE(result.device_registry.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.device_registry.host_effect_allowed == 0,
        "host effect denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "device transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "device transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;
    request.target_state = LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "driver catalog transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY,
        "next driver-catalog-ready");
    EXPECT_TRUE(strcmp(result.driver_catalog.catalog_status, "driver-catalog-seed-ready") == 0,
        "driver catalog ready");
    EXPECT_TRUE(strcmp(result.device_registry.registry_status, "device-registry-seed-ready") == 0,
        "driver transition keeps device registry ready");
    EXPECT_TRUE(strcmp(result.vfs_namespace.namespace_status, "vfs-namespace-seed-ready") == 0,
        "driver transition keeps vfs namespace ready");
    EXPECT_TRUE(result.driver_catalog.driver_probe_allowed == 0,
        "driver probe denied");
    EXPECT_TRUE(result.driver_catalog.driver_load_allowed == 0,
        "driver load denied");
    EXPECT_TRUE(result.driver_catalog.driver_bind_allowed == 0,
        "driver bind denied");
    EXPECT_TRUE(result.driver_catalog.interrupt_allowed == 0,
        "interrupt denied");
    EXPECT_TRUE(result.driver_catalog.dma_allowed == 0,
        "dma denied");
    EXPECT_TRUE(result.driver_catalog.hardware_effect_allowed == 0,
        "driver hardware effect denied");
    EXPECT_TRUE(result.driver_catalog.host_effect_allowed == 0,
        "driver host effect denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "driver transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "driver transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;
    request.target_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "interrupt table transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY,
        "next interrupt-table-ready");
    EXPECT_TRUE(strcmp(result.interrupt_table.table_status, "interrupt-table-seed-ready") == 0,
        "interrupt table ready");
    EXPECT_TRUE(strcmp(result.driver_catalog.catalog_status, "driver-catalog-seed-ready") == 0,
        "interrupt transition keeps driver catalog ready");
    EXPECT_TRUE(strcmp(result.device_registry.registry_status, "device-registry-seed-ready") == 0,
        "interrupt transition keeps device registry ready");
    EXPECT_TRUE(result.interrupt_table.interrupt_mask_allowed == 0,
        "interrupt mask denied");
    EXPECT_TRUE(result.interrupt_table.interrupt_unmask_allowed == 0,
        "interrupt unmask denied");
    EXPECT_TRUE(result.interrupt_table.interrupt_dispatch_allowed == 0,
        "interrupt dispatch denied");
    EXPECT_TRUE(result.interrupt_table.interrupt_ack_allowed == 0,
        "interrupt ack denied");
    EXPECT_TRUE(result.interrupt_table.dma_allowed == 0,
        "interrupt dma denied");
    EXPECT_TRUE(result.interrupt_table.hardware_effect_allowed == 0,
        "interrupt hardware effect denied");
    EXPECT_TRUE(result.interrupt_table.host_effect_allowed == 0,
        "interrupt host effect denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "interrupt transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "interrupt transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "timer source transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY,
        "next timer-source-ready");
    EXPECT_TRUE(strcmp(result.timer_source.timer_status, "timer-source-seed-ready") == 0,
        "timer source ready");
    EXPECT_TRUE(strcmp(result.interrupt_table.table_status, "interrupt-table-seed-ready") == 0,
        "timer transition keeps interrupt table ready");
    EXPECT_TRUE(strcmp(result.driver_catalog.catalog_status, "driver-catalog-seed-ready") == 0,
        "timer transition keeps driver catalog ready");
    EXPECT_TRUE(result.timer_source.timer_count == 4u,
        "timer source count");
    EXPECT_TRUE(result.timer_source.timer_tick_allowed == 0,
        "timer tick denied");
    EXPECT_TRUE(result.timer_source.timer_arm_allowed == 0,
        "timer arm denied");
    EXPECT_TRUE(result.timer_source.timer_disarm_allowed == 0,
        "timer disarm denied");
    EXPECT_TRUE(result.timer_source.scheduler_tick_allowed == 0,
        "timer scheduler tick denied");
    EXPECT_TRUE(result.timer_source.preemption_allowed == 0,
        "timer preemption denied");
    EXPECT_TRUE(result.timer_source.time_read_allowed == 0,
        "timer time read denied");
    EXPECT_TRUE(result.timer_source.hardware_effect_allowed == 0,
        "timer hardware effect denied");
    EXPECT_TRUE(result.timer_source.host_effect_allowed == 0,
        "timer host effect denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "timer transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "timer transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "scheduler tick transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY,
        "next scheduler-tick-ready");
    EXPECT_TRUE(strcmp(result.scheduler_tick.tick_status, "scheduler-tick-seed-ready") == 0,
        "scheduler tick ready");
    EXPECT_TRUE(strcmp(result.timer_source.timer_status, "timer-source-seed-ready") == 0,
        "scheduler tick transition keeps timer source ready");
    EXPECT_TRUE(strcmp(result.interrupt_table.table_status, "interrupt-table-seed-ready") == 0,
        "scheduler tick transition keeps interrupt table ready");
    EXPECT_TRUE(result.scheduler_tick.tick_count == 4u,
        "scheduler tick count");
    EXPECT_TRUE(result.scheduler_tick.timer_tick_allowed == 0,
        "scheduler tick timer tick denied");
    EXPECT_TRUE(result.scheduler_tick.scheduler_tick_allowed == 0,
        "scheduler tick denied");
    EXPECT_TRUE(result.scheduler_tick.run_queue_mutation_allowed == 0,
        "scheduler tick run queue mutation denied");
    EXPECT_TRUE(result.scheduler_tick.context_switch_allowed == 0,
        "scheduler tick context switch denied");
    EXPECT_TRUE(result.scheduler_tick.preemption_allowed == 0,
        "scheduler tick preemption denied");
    EXPECT_TRUE(result.scheduler_tick.time_accounting_allowed == 0,
        "scheduler tick time accounting denied");
    EXPECT_TRUE(result.scheduler_tick.time_read_allowed == 0,
        "scheduler tick time read denied");
    EXPECT_TRUE(result.scheduler_tick.process_wake_allowed == 0,
        "scheduler tick process wake denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "scheduler tick transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "scheduler tick transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;
    request.target_state = LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "run queue transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_RUN_QUEUE_READY,
        "next run-queue-ready");
    EXPECT_TRUE(strcmp(result.run_queue.queue_status, "run-queue-seed-ready") == 0,
        "run queue ready");
    EXPECT_TRUE(strcmp(result.scheduler_tick.tick_status, "scheduler-tick-seed-ready") == 0,
        "run queue transition keeps scheduler tick ready");
    EXPECT_TRUE(strcmp(result.timer_source.timer_status, "timer-source-seed-ready") == 0,
        "run queue transition keeps timer source ready");
    EXPECT_TRUE(result.run_queue.queue_count == 4u,
        "run queue count");
    EXPECT_TRUE(result.run_queue.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.run_queue.enqueue_allowed == 0,
        "run queue enqueue denied");
    EXPECT_TRUE(result.run_queue.dequeue_allowed == 0,
        "run queue dequeue denied");
    EXPECT_TRUE(result.run_queue.dispatch_allowed == 0,
        "run queue dispatch denied");
    EXPECT_TRUE(result.run_queue.context_switch_allowed == 0,
        "run queue context switch denied");
    EXPECT_TRUE(result.run_queue.preemption_allowed == 0,
        "run queue preemption denied");
    EXPECT_TRUE(result.run_queue.time_accounting_allowed == 0,
        "run queue time accounting denied");
    EXPECT_TRUE(result.run_queue.process_wake_allowed == 0,
        "run queue process wake denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "run queue transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "run queue transition not denied");

    request.current_state = LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "context switch transition evaluates");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY,
        "next context-switch-ready");
    EXPECT_TRUE(strcmp(result.context_switch.switch_status,
            "context-switch-seed-ready") == 0,
        "context switch ready");
    EXPECT_TRUE(strcmp(result.run_queue.queue_status, "run-queue-seed-ready") == 0,
        "context switch transition keeps run queue ready");
    EXPECT_TRUE(strcmp(result.scheduler_tick.tick_status,
            "scheduler-tick-seed-ready") == 0,
        "context switch transition keeps scheduler tick ready");
    EXPECT_TRUE(result.context_switch.switch_count == 4u,
        "context switch count");
    EXPECT_TRUE(result.context_switch.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.context_switch.register_save_allowed == 0,
        "register save denied");
    EXPECT_TRUE(result.context_switch.register_restore_allowed == 0,
        "register restore denied");
    EXPECT_TRUE(result.context_switch.stack_switch_allowed == 0,
        "stack switch denied");
    EXPECT_TRUE(result.context_switch.address_space_switch_allowed == 0,
        "address space switch denied");
    EXPECT_TRUE(result.context_switch.dispatch_allowed == 0,
        "context switch dispatch denied");
    EXPECT_TRUE(result.context_switch.run_queue_mutation_allowed == 0,
        "context switch run queue mutation denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "context switch transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "context switch transition not denied");
    return 0;
}

static int denied_transition_does_not_change_state(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for illegal transition");
    request.current_state = LATTICRA_KERNEL_STATE_CREATED;
    request.target_state = LATTICRA_KERNEL_STATE_MEMORY_MAP_READY;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "illegal transition evaluates");
    EXPECT_TRUE(strcmp(result.transition_status, "transition-denied") == 0,
        "illegal transition denied");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_CREATED,
        "illegal transition unchanged");
    EXPECT_TRUE(result.state_change_performed == 0,
        "illegal transition no state change");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "illegal transition no external effect");
    EXPECT_TRUE(result.denied == 1,
        "illegal transition denied flag");
    return 0;
}

static int allowed_noop_is_stable(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for noop");
    request.current_state = LATTICRA_KERNEL_STATE_INITIALIZED;
    request.target_state = LATTICRA_KERNEL_STATE_INITIALIZED;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "noop evaluates");
    EXPECT_TRUE(strcmp(result.transition_status, "no-op") == 0,
        "noop status");
    EXPECT_TRUE(result.next_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "noop next state");
    EXPECT_TRUE(result.state_change_performed == 0,
        "noop no state change");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "noop no external effect");
    EXPECT_TRUE(result.denied == 0,
        "noop not denied");
    return 0;
}

static int report_records_state_change(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;
    char report[LATTICRA_KERNEL_STATE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL STATE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "state_status=changed\n") != 0,
        "state status emitted");
    EXPECT_TRUE(strstr(report, "gate_status=allow\n") != 0,
        "gate emitted");
    EXPECT_TRUE(strstr(report, "transition_status=transition-applied\n") != 0,
        "transition emitted");
    EXPECT_TRUE(strstr(report, "effect_status=in-memory-state-change\n") != 0,
        "effect status emitted");
    EXPECT_TRUE(strstr(report, "previous_state=created\n") != 0,
        "previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=initialized\n") != 0,
        "next emitted");
    EXPECT_TRUE(strstr(report, "state_change_performed=1\n") != 0,
        "state change emitted");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "external effect emitted");
    EXPECT_TRUE(strstr(report, "denied=0\n") != 0,
        "denied emitted");
    EXPECT_TRUE(strstr(report, "memory_map_status=memory-map-seed-ready\n") != 0,
        "memory map emitted");
    return 0;
}

static int report_records_process_syscall_ipc_vfs_device_driver_interrupt_timer_tick_queue_and_context_readiness(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;
    char report[LATTICRA_KERNEL_STATE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for syscall report");
    request.current_state = LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "syscall transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "syscall report writes");

    EXPECT_TRUE(strstr(report, "previous_state=process-table-ready\n") != 0,
        "process previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=syscall-table-ready\n") != 0,
        "syscall next emitted");
    EXPECT_TRUE(strstr(report, "process_table_status=process-table-seed-ready\n") != 0,
        "process table emitted");
    EXPECT_TRUE(strstr(report, "syscall_table_status=syscall-table-seed-ready\n") != 0,
        "syscall table emitted");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "syscall report external effect emitted");

    request.current_state = LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "ipc transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "ipc report writes");

    EXPECT_TRUE(strstr(report, "previous_state=syscall-table-ready\n") != 0,
        "syscall previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=ipc-table-ready\n") != 0,
        "ipc next emitted");
    EXPECT_TRUE(strstr(report, "process_table_status=process-table-seed-ready\n") != 0,
        "ipc process table emitted");
    EXPECT_TRUE(strstr(report, "syscall_table_status=syscall-table-seed-ready\n") != 0,
        "ipc syscall table emitted");
    EXPECT_TRUE(strstr(report, "ipc_table_status=ipc-table-seed-ready\n") != 0,
        "ipc table emitted");

    request.current_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "vfs transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "vfs report writes");

    EXPECT_TRUE(strstr(report, "previous_state=ipc-table-ready\n") != 0,
        "ipc previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=vfs-namespace-ready\n") != 0,
        "vfs next emitted");
    EXPECT_TRUE(strstr(report, "ipc_table_status=ipc-table-seed-ready\n") != 0,
        "vfs ipc table emitted");
    EXPECT_TRUE(strstr(report, "vfs_namespace_status=vfs-namespace-seed-ready\n") != 0,
        "vfs namespace emitted");

    request.current_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "device transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "device report writes");

    EXPECT_TRUE(strstr(report, "previous_state=vfs-namespace-ready\n") != 0,
        "vfs previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=device-registry-ready\n") != 0,
        "device next emitted");
    EXPECT_TRUE(strstr(report, "vfs_namespace_status=vfs-namespace-seed-ready\n") != 0,
        "device report vfs namespace emitted");
    EXPECT_TRUE(strstr(report, "device_registry_status=device-registry-seed-ready\n") != 0,
        "device registry emitted");

    request.current_state = LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;
    request.target_state = LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "driver transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "driver report writes");

    EXPECT_TRUE(strstr(report, "previous_state=device-registry-ready\n") != 0,
        "device previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=driver-catalog-ready\n") != 0,
        "driver next emitted");
    EXPECT_TRUE(strstr(report, "device_registry_status=device-registry-seed-ready\n") != 0,
        "driver report device registry emitted");
    EXPECT_TRUE(strstr(report, "driver_catalog_status=driver-catalog-seed-ready\n") != 0,
        "driver catalog emitted");

    request.current_state = LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;
    request.target_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "interrupt transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "interrupt report writes");

    EXPECT_TRUE(strstr(report, "previous_state=driver-catalog-ready\n") != 0,
        "driver previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=interrupt-table-ready\n") != 0,
        "interrupt next emitted");
    EXPECT_TRUE(strstr(report, "driver_catalog_status=driver-catalog-seed-ready\n") != 0,
        "interrupt report driver catalog emitted");
    EXPECT_TRUE(strstr(report, "interrupt_table_status=interrupt-table-seed-ready\n") != 0,
        "interrupt table emitted");

    request.current_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "timer transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "timer report writes");

    EXPECT_TRUE(strstr(report, "previous_state=interrupt-table-ready\n") != 0,
        "interrupt previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=timer-source-ready\n") != 0,
        "timer next emitted");
    EXPECT_TRUE(strstr(report, "interrupt_table_status=interrupt-table-seed-ready\n") != 0,
        "timer report interrupt table emitted");
    EXPECT_TRUE(strstr(report, "timer_source_status=timer-source-seed-ready\n") != 0,
        "timer source emitted");

    request.current_state = LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "scheduler tick transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "scheduler tick report writes");

    EXPECT_TRUE(strstr(report, "previous_state=timer-source-ready\n") != 0,
        "timer previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=scheduler-tick-ready\n") != 0,
        "scheduler tick next emitted");
    EXPECT_TRUE(strstr(report, "timer_source_status=timer-source-seed-ready\n") != 0,
        "scheduler tick report timer source emitted");
    EXPECT_TRUE(strstr(report, "scheduler_tick_status=scheduler-tick-seed-ready\n") != 0,
        "scheduler tick emitted");

    request.current_state = LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;
    request.target_state = LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "run queue transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "run queue report writes");

    EXPECT_TRUE(strstr(report, "previous_state=scheduler-tick-ready\n") != 0,
        "scheduler tick previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=run-queue-ready\n") != 0,
        "run queue next emitted");
    EXPECT_TRUE(strstr(report, "scheduler_tick_status=scheduler-tick-seed-ready\n") != 0,
        "run queue report scheduler tick emitted");
    EXPECT_TRUE(strstr(report, "run_queue_status=run-queue-seed-ready\n") != 0,
        "run queue emitted");

    request.current_state = LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "context switch transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "context switch report writes");

    EXPECT_TRUE(strstr(report, "previous_state=run-queue-ready\n") != 0,
        "run queue previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=context-switch-ready\n") != 0,
        "context switch next emitted");
    EXPECT_TRUE(strstr(report, "run_queue_status=run-queue-seed-ready\n") != 0,
        "context switch report run queue emitted");
    EXPECT_TRUE(strstr(report, "context_switch_status=context-switch-seed-ready\n") != 0,
        "context switch emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_state_result_t result;
    char report[LATTICRA_KERNEL_STATE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_state_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_state_transition(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null transition request");
    EXPECT_TRUE(latticra_kernel_state_transition(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null transition result");
    EXPECT_TRUE(latticra_kernel_state_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_state_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_denies_state_change() != 0) return 1;
    if (allowed_transition_changes_state() != 0) return 1;
    if (allowed_process_syscall_ipc_vfs_device_driver_interrupt_timer_tick_queue_and_context_transitions_are_metadata_only() != 0) return 1;
    if (denied_transition_does_not_change_state() != 0) return 1;
    if (allowed_noop_is_stable() != 0) return 1;
    if (report_records_state_change() != 0) return 1;
    if (report_records_process_syscall_ipc_vfs_device_driver_interrupt_timer_tick_queue_and_context_readiness() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_state: ok");
    return 0;
}
