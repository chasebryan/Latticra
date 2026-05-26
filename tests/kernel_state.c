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

static int allowed_process_syscall_ipc_and_vfs_transitions_are_metadata_only(void) {
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
    EXPECT_TRUE(result.ipc_table.ipc_send_allowed == 0,
        "ipc send denied");
    EXPECT_TRUE(result.ipc_table.ipc_receive_allowed == 0,
        "ipc receive denied");
    EXPECT_TRUE(result.ipc_table.queue_mutation_allowed == 0,
        "ipc queue mutation denied");
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
    EXPECT_TRUE(result.vfs_namespace.path_lookup_allowed == 0,
        "vfs path lookup denied");
    EXPECT_TRUE(result.vfs_namespace.file_read_allowed == 0,
        "vfs file read denied");
    EXPECT_TRUE(result.vfs_namespace.file_write_allowed == 0,
        "vfs file write denied");
    EXPECT_TRUE(result.vfs_namespace.namespace_mutation_allowed == 0,
        "vfs namespace mutation denied");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "vfs transition no external effect");
    EXPECT_TRUE(result.denied == 0,
        "vfs transition not denied");
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

static int report_records_process_syscall_ipc_and_vfs_readiness(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;
    char report[LATTICRA_KERNEL_STATE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_state_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for syscall report");
    request.current_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
    request.target_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_transition(&request, &result) == LATTICRA_STATUS_OK,
        "vfs transition for report");
    EXPECT_TRUE(latticra_kernel_state_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "syscall report writes");

    EXPECT_TRUE(strstr(report, "previous_state=ipc-table-ready\n") != 0,
        "ipc previous emitted");
    EXPECT_TRUE(strstr(report, "next_state=vfs-namespace-ready\n") != 0,
        "vfs next emitted");
    EXPECT_TRUE(strstr(report, "process_table_status=process-table-seed-ready\n") != 0,
        "process table emitted");
    EXPECT_TRUE(strstr(report, "syscall_table_status=syscall-table-seed-ready\n") != 0,
        "syscall table emitted");
    EXPECT_TRUE(strstr(report, "ipc_table_status=ipc-table-seed-ready\n") != 0,
        "ipc table emitted");
    EXPECT_TRUE(strstr(report, "vfs_namespace_status=vfs-namespace-seed-ready\n") != 0,
        "vfs namespace emitted");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "vfs report external effect emitted");
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
    if (allowed_process_syscall_ipc_and_vfs_transitions_are_metadata_only() != 0) return 1;
    if (denied_transition_does_not_change_state() != 0) return 1;
    if (allowed_noop_is_stable() != 0) return 1;
    if (report_records_state_change() != 0) return 1;
    if (report_records_process_syscall_ipc_and_vfs_readiness() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_state: ok");
    return 0;
}
