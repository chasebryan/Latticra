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
    EXPECT_TRUE(machine.network_allowed == 0,
        "machine network denied");
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
    EXPECT_TRUE(result.network_allowed == 0,
        "default step network denied");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_CREATED,
        "machine remains created");
    EXPECT_TRUE(machine.network_allowed == 0,
        "machine keeps network denied");
    EXPECT_TRUE(machine.log_count == 1u,
        "denial logged");
    EXPECT_TRUE(strcmp(machine.log[0].status, "transition-denied") == 0,
        "log status denied");
    EXPECT_TRUE(machine.log[0].state_change_performed == 0,
        "log no state change");
    EXPECT_TRUE(machine.log[0].external_effect_performed == 0,
        "log no external effect");
    EXPECT_TRUE(machine.log[0].network_allowed == 0,
        "log network denied");
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
    EXPECT_TRUE(result.transition.network_allowed == 0,
        "allowed transition network denied");
    EXPECT_TRUE(result.network_allowed == 0,
        "allowed step network denied");
    EXPECT_TRUE(machine.current_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "machine current initialized");
    EXPECT_TRUE(strcmp(machine.machine_status, "initialized") == 0,
        "machine status initialized");
    EXPECT_TRUE(machine.state_mutated == 1,
        "machine mutation flag set");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "machine external effects absent");
    EXPECT_TRUE(machine.network_allowed == 0,
        "machine network denied after allowed step");
    EXPECT_TRUE(machine.log_count == 1u,
        "allowed step logged");
    EXPECT_TRUE(machine.log[0].from_state == LATTICRA_KERNEL_STATE_CREATED,
        "log from created");
    EXPECT_TRUE(machine.log[0].to_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "log to initialized");
    EXPECT_TRUE(machine.log[0].state_change_performed == 1,
        "log state change");
    EXPECT_TRUE(machine.log[0].network_allowed == 0,
        "allowed log network denied");
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
    request.target_state = LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "device registry ready to driver catalog ready");
    request.target_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "driver catalog ready to interrupt table ready");
    request.target_state = LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "interrupt table ready to timer source ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "timer source ready to scheduler tick ready");
    request.target_state = LATTICRA_KERNEL_STATE_RUN_QUEUE_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler tick ready to run queue ready");
    request.target_state = LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "run queue ready to context switch ready");
    request.target_state = LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "context switch ready to time accounting ready");
    request.target_state = LATTICRA_KERNEL_STATE_PREEMPTION_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "time accounting ready to preemption ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "preemption ready to scheduler credit ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler credit ready to scheduler selection ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler selection ready to scheduler dispatch ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler dispatch ready to scheduler handoff ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_ACTIVATION_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler handoff ready to scheduler activation ready");
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_RUN_ENTRY_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler activation ready to scheduler run entry ready");
    request.target_state = LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADMISSION_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "scheduler run entry ready to runtime entry admission ready");
    request.target_state = LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_FRAME_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry admission ready to runtime entry frame ready");
    request.target_state = LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_REGISTER_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry frame ready to runtime entry register view ready");
    request.target_state = LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_STACK_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry register view ready to runtime entry stack view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry stack view ready to runtime entry address space view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry address space view ready to runtime entry privilege level view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry privilege level view ready to runtime entry syscall gate view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry syscall gate view ready to runtime entry syscall dispatch view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry syscall dispatch view ready to runtime entry syscall return view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry syscall return view ready to runtime entry syscall exit view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry syscall exit view ready to runtime entry user mode resume view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry user mode resume view ready to runtime entry post resume observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry post resume observation view ready to runtime entry scheduler return observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry scheduler return observation view ready to runtime entry process return observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry process return observation view ready to runtime entry idle return observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry idle return observation view ready to runtime entry quiescent return observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry quiescent return observation view ready to runtime entry persistence boundary observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry persistence boundary observation view ready to runtime entry recovery boundary observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry recovery boundary observation view ready to runtime entry recovery plan observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry recovery plan observation view ready to runtime entry recovery disposition observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry recovery disposition observation view ready to runtime entry recovery outcome observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry recovery outcome observation view ready to runtime entry recovery closeout observation view ready");
    request.target_state =
        LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY;
    EXPECT_TRUE(latticra_kernel_state_machine_step(&machine, &request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry recovery closeout observation view ready to runtime entry recovery audit observation view ready");

    EXPECT_TRUE(machine.current_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY,
        "machine reaches runtime entry recovery audit observation view ready");
    EXPECT_TRUE(strcmp(machine.machine_status,
            "runtime-entry-recovery-audit-observation-view-ready") == 0,
        "machine status runtime entry recovery audit observation view ready");
    EXPECT_TRUE(machine.log_count == 46u,
        "forty six transitions logged");
    EXPECT_TRUE(machine.external_effect_performed == 0,
        "sequence external effects absent");
    EXPECT_TRUE(machine.network_allowed == 0,
        "sequence network denied");
    EXPECT_TRUE(machine.log[4].to_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY,
        "log process table ready");
    EXPECT_TRUE(machine.log[5].to_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY,
        "log syscall table ready");
    EXPECT_TRUE(machine.log[5].network_allowed == 0,
        "syscall log network denied");
    EXPECT_TRUE(machine.log[6].to_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY,
        "log ipc table ready");
    EXPECT_TRUE(machine.log[6].network_allowed == 0,
        "ipc log network denied");
    EXPECT_TRUE(machine.log[7].to_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY,
        "log vfs namespace ready");
    EXPECT_TRUE(machine.log[8].to_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY,
        "log device registry ready");
    EXPECT_TRUE(machine.log[9].to_state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY,
        "log driver catalog ready");
    EXPECT_TRUE(machine.log[10].to_state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY,
        "log interrupt table ready");
    EXPECT_TRUE(machine.log[11].to_state == LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY,
        "log timer source ready");
    EXPECT_TRUE(machine.log[12].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY,
        "log scheduler tick ready");
    EXPECT_TRUE(machine.log[13].to_state == LATTICRA_KERNEL_STATE_RUN_QUEUE_READY,
        "log run queue ready");
    EXPECT_TRUE(machine.log[14].to_state == LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY,
        "log context switch ready");
    EXPECT_TRUE(machine.log[15].to_state == LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY,
        "log time accounting ready");
    EXPECT_TRUE(machine.log[16].to_state == LATTICRA_KERNEL_STATE_PREEMPTION_READY,
        "log preemption ready");
    EXPECT_TRUE(machine.log[17].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY,
        "log scheduler credit ready");
    EXPECT_TRUE(machine.log[18].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_SELECTION_READY,
        "log scheduler selection ready");
    EXPECT_TRUE(machine.log[19].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_DISPATCH_READY,
        "log scheduler dispatch ready");
    EXPECT_TRUE(machine.log[20].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_HANDOFF_READY,
        "log scheduler handoff ready");
    EXPECT_TRUE(machine.log[21].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_ACTIVATION_READY,
        "log scheduler activation ready");
    EXPECT_TRUE(machine.log[22].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_RUN_ENTRY_READY,
        "log scheduler run entry ready");
    EXPECT_TRUE(machine.log[23].to_state == LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADMISSION_READY,
        "log runtime entry admission ready");
    EXPECT_TRUE(machine.log[24].to_state == LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_FRAME_READY,
        "log runtime entry frame ready");
    EXPECT_TRUE(machine.log[25].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_REGISTER_VIEW_READY,
        "log runtime entry register view ready");
    EXPECT_TRUE(machine.log[26].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_STACK_VIEW_READY,
        "log runtime entry stack view ready");
    EXPECT_TRUE(machine.log[27].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_READY,
        "log runtime entry address space view ready");
    EXPECT_TRUE(machine.log[28].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_READY,
        "log runtime entry privilege level view ready");
    EXPECT_TRUE(machine.log[29].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_READY,
        "log runtime entry syscall gate view ready");
    EXPECT_TRUE(machine.log[30].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_READY,
        "log runtime entry syscall dispatch view ready");
    EXPECT_TRUE(machine.log[31].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_READY,
        "log runtime entry syscall return view ready");
    EXPECT_TRUE(machine.log[32].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_READY,
        "log runtime entry syscall exit view ready");
    EXPECT_TRUE(machine.log[33].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_READY,
        "log runtime entry user mode resume view ready");
    EXPECT_TRUE(machine.log[34].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_READY,
        "log runtime entry post resume observation view ready");
    EXPECT_TRUE(machine.log[35].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_READY,
        "log runtime entry scheduler return observation view ready");
    EXPECT_TRUE(machine.log[36].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_READY,
        "log runtime entry process return observation view ready");
    EXPECT_TRUE(machine.log[37].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_READY,
        "log runtime entry idle return observation view ready");
    EXPECT_TRUE(machine.log[38].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_READY,
        "log runtime entry quiescent return observation view ready");
    EXPECT_TRUE(machine.log[39].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_READY,
        "log runtime entry persistence boundary observation view ready");
    EXPECT_TRUE(machine.log[40].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_READY,
        "log runtime entry recovery boundary observation view ready");
    EXPECT_TRUE(machine.log[41].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_READY,
        "log runtime entry recovery plan observation view ready");
    EXPECT_TRUE(machine.log[42].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_READY,
        "log runtime entry recovery disposition observation view ready");
    EXPECT_TRUE(machine.log[43].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_READY,
        "log runtime entry recovery outcome observation view ready");
    EXPECT_TRUE(machine.log[44].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_READY,
        "log runtime entry recovery closeout observation view ready");
    EXPECT_TRUE(machine.log[45].to_state ==
            LATTICRA_KERNEL_STATE_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_READY,
        "log runtime entry recovery audit observation view ready");
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
    EXPECT_TRUE(result.network_allowed == 0,
        "illegal step network denied");
    EXPECT_TRUE(machine.network_allowed == 0,
        "illegal machine network denied");
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
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0,
        "network flag emitted");
    EXPECT_TRUE(strstr(report, "log[0].from=created\n") != 0,
        "log from emitted");
    EXPECT_TRUE(strstr(report, "log[0].to=initialized\n") != 0,
        "log to emitted");
    EXPECT_TRUE(strstr(report, "log[0].status=machine-mutated\n") != 0,
        "log status emitted");
    EXPECT_TRUE(strstr(report, "log[0].state_change_performed=1\n") != 0,
        "log state change emitted");
    EXPECT_TRUE(strstr(report, "log[0].network_allowed=0\n") != 0,
        "log network emitted");
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
