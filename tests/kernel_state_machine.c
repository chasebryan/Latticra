#include "latticra/kernel_state_machine.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int machine_init_is_stable(void) {
    latticra_kernel_state_machine_t machine;

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine init status");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_CREATED,
        "machine starts created");
    EXPECT_TRUE(strcmp(machine.machine_status, "created") == 0,
        "machine status created");
    EXPECT_TRUE(machine.log_count == 0u,
        "machine log empty");
    EXPECT_TRUE(machine.state_mutated == 0,
        "machine not yet mutated");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "machine external effects absent");
    return 0;
}

static int default_step_is_denied_and_logged(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(&request) == LATTICRA_STATUS_OK,
        "step request initialized");

    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "default step evaluates");
    EXPECT_TRUE(strcmp(result.step_status, "transition-denied") == 0,
        "default step denied");
    EXPECT_TRUE(result.machine_state_before == LATTICRA_KERNEL_STATE_CREATED,
        "default before created");
    EXPECT_TRUE(result.machine_state_after == LATTICRA_KERNEL_STATE_CREATED,
        "default after created");
    EXPECT_TRUE(result.state_mutated == 0,
        "default no mutation");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "default no external effect");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_CREATED,
        "machine remains created");
    EXPECT_TRUE(machine.log_count == 1u,
        "denial logged");
    EXPECT_TRUE(strcmp(machine.log[0].status, "transition-denied") == 0,
        "log status denied");
    EXPECT_TRUE(machine.log[0].state_change_performed == 0,
        "log no state change");
    EXPECT_TRUE(machine.log[0].external_effect_performed == 0,
        "log no external effect");
    return 0;
}

static int allowed_step_mutates_machine_state(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized for allowed step");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(&request) == LATTICRA_STATUS_OK,
        "step request initialized for allowed step");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "allowed step evaluates");
    EXPECT_TRUE(strcmp(result.step_status, "machine-mutated") == 0,
        "allowed step mutates");
    EXPECT_TRUE(result.machine_state_before == LATTICRA_KERNEL_STATE_CREATED,
        "allowed before created");
    EXPECT_TRUE(result.machine_state_after == LATTICRA_KERNEL_STATE_INITIALIZED,
        "allowed after initialized");
    EXPECT_TRUE(result.state_mutated == 1,
        "allowed state mutated");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "allowed external effect absent");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "machine current initialized");
    EXPECT_TRUE(strcmp(machine.machine_status, "initialized") == 0,
        "machine status initialized");
    EXPECT_TRUE(machine.state_mutated == 1,
        "machine mutation flag set");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "machine external effects absent");
    EXPECT_TRUE(machine.log_count == 1u,
        "allowed step logged");
    EXPECT_TRUE(machine.log[0].from_state == LATTICRA_KERNEL_STATE_CREATED,
        "log from created");
    EXPECT_TRUE(machine.log[0].to_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "log to initialized");
    EXPECT_TRUE(machine.log[0].state_change_performed == 1,
        "log state change");
    return 0;
}

static int sequential_steps_advance_ladder(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized for sequence");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(&request) == LATTICRA_STATUS_OK,
        "step request initialized for sequence");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "created to initialized");
    request.target_state = LATTICRA_KERNEL_STATE_REGISTRY_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "initialized to registry ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "registry ready to scheduler ready");
    request.target_state = LATTICRA_KERNEL_STATE_MEMORY_MAP_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler ready to memory map ready");
    request.target_state = LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "memory map ready to process table ready");
    request.target_state = LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "process table ready to syscall table ready");
    request.target_state = LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "syscall table ready to ipc table ready");
    request.target_state = LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "ipc table ready to vfs namespace ready");
    request.target_state = LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "vfs namespace ready to device registry ready");

    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY,
        "machine reaches device registry ready");
    EXPECT_TRUE(strcmp(machine.machine_status, "device-registry-ready") == 0,
        "machine status device registry ready");
    EXPECT_TRUE(machine.log_count == 9u,
        "nine transitions logged");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "sequence external effects absent");
    EXPECT_TRUE(machine.log[4].to_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY,
        "log process table ready");
    EXPECT_TRUE(machine.log[5].to_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY,
        "log syscall table ready");
    EXPECT_TRUE(machine.log[6].to_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY,
        "log ipc table ready");
    EXPECT_TRUE(machine.log[7].to_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY,
        "log vfs namespace ready");
    EXPECT_TRUE(machine.log[8].to_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY,
        "log device registry ready");
    return 0;
}

static int illegal_step_does_not_mutate_machine(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized for illegal step");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(&request) == LATTICRA_STATUS_OK,
        "step request initialized for illegal step");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.target_state = LATTICRA_KERNEL_STATE_MEMORY_MAP_READY;

    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "illegal step evaluates");
    EXPECT_TRUE(strcmp(result.step_status, "transition-denied") == 0,
        "illegal step denied");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_CREATED,
        "illegal step leaves state unchanged");
    EXPECT_TRUE(machine.log_count == 1u,
        "illegal step logged");
    EXPECT_TRUE(machine.log[0].state_change_performed == 0,
        "illegal log no state change");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "illegal external effects absent");
    return 0;
}

static int machine_report_is_deterministic(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;
    char report[LATTICRA_KERNEL_STATE_MACHINE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized for report");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(&request) == LATTICRA_STATUS_OK,
        "step request initialized for report");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "step for report");
    EXPECT_TRUE(latticra_kernel_state_machine_report(&machine, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "machine report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL STATE MACHINE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "machine_status=initialized\n") != 0,
        "machine status emitted");
    EXPECT_TRUE(strstr(report, "current_state=initialized\n") != 0,
        "current state emitted");
    EXPECT_TRUE(strstr(report, "log_count=1\n") != 0,
        "log count emitted");
    EXPECT_TRUE(strstr(report, "state_mutated=1\n") != 0,
        "mutation flag emitted");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "external effect emitted");
    EXPECT_TRUE(strstr(report, "log[0].from=created\n") != 0,
        "log from emitted");
    EXPECT_TRUE(strstr(report, "log[0].to=initialized\n") != 0,
        "log to emitted");
    EXPECT_TRUE(strstr(report, "log[0].status=machine-mutated\n") != 0,
        "log status emitted");
    EXPECT_TRUE(strstr(report, "log[0].state_change_performed=1\n") != 0,
        "log state change emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;
    char report[LATTICRA_KERNEL_STATE_MACHINE_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    memset(&result, 0, sizeof(result));

    EXPECT_TRUE(latticra_kernel_state_machine_init(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null machine init");
    EXPECT_TRUE(latticra_kernel_state_machine_default_step_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default step request");
    EXPECT_TRUE(latticra_kernel_state_machine_step(0, &request, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null machine step");
    EXPECT_TRUE(latticra_kernel_state_machine_init(&machine) == LATTICRA_STATUS_OK,
        "machine initialized for null guards");
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, 0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null request step");
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null result step");
    EXPECT_TRUE(latticra_kernel_state_machine_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report machine");
    EXPECT_TRUE(latticra_kernel_state_machine_report(&machine, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_state_machine_report(&machine, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (machine_init_is_stable() != 0) return 1;
    if (default_step_is_denied_and_logged() != 0) return 1;
    if (allowed_step_mutates_machine_state() != 0) return 1;
    if (sequential_steps_advance_ladder() != 0) return 1;
    if (illegal_step_does_not_mutate_machine() != 0) return 1;
    if (machine_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_state_machine: ok");
    return 0;
}
