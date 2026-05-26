#include "latticra/kernel_lifecycle.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_is_denied(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.target_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY,
        "default target scheduler-credit-ready");
    EXPECT_TRUE(request.gate == LATTICRA_KERNEL_STATE_GATE_DENY,
        "default gate deny");
    EXPECT_TRUE(request.max_steps == LATTICRA_KERNEL_LIFECYCLE_STEP_MAX,
        "default max steps");

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "default lifecycle evaluates");
    EXPECT_TRUE(strcmp(result.lifecycle_status, "not-started") == 0,
        "default lifecycle not started");
    EXPECT_TRUE(strcmp(result.policy_status, "gate-denied") == 0,
        "default policy gate denied");
    EXPECT_TRUE(result.final_state == LATTICRA_KERNEL_STATE_CREATED,
        "default final state created");
    EXPECT_TRUE(result.step_count == 0u,
        "default no steps");
    EXPECT_TRUE(result.state_change_count == 0u,
        "default no state changes");
    EXPECT_TRUE(result.lifecycle_complete == 0,
        "default not complete");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "default external effects absent");
    return 0;
}

static int allowed_lifecycle_reaches_scheduler_credit_ready(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "allowed lifecycle evaluates");
    EXPECT_TRUE(strcmp(result.lifecycle_status, "lifecycle-complete") == 0,
        "lifecycle complete");
    EXPECT_TRUE(strcmp(result.policy_status, "gate-allowed") == 0,
        "policy gate allowed");
    EXPECT_TRUE(result.final_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY,
        "final state scheduler-credit-ready");
    EXPECT_TRUE(result.step_count == 18u,
        "eighteen steps to scheduler-credit-ready");
    EXPECT_TRUE(result.state_change_count == 18u,
        "eighteen state changes");
    EXPECT_TRUE(result.lifecycle_complete == 1,
        "complete flag set");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "external effects absent");
    EXPECT_TRUE(result.machine.log_count == 18u,
        "machine log has eighteen entries");
    EXPECT_TRUE(result.machine.log[0].from_state == LATTICRA_KERNEL_STATE_CREATED,
        "log zero from created");
    EXPECT_TRUE(result.machine.log[0].to_state == LATTICRA_KERNEL_STATE_INITIALIZED,
        "log zero to initialized");
    EXPECT_TRUE(result.machine.log[4].to_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY,
        "log four to process-table-ready");
    EXPECT_TRUE(result.machine.log[5].to_state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY,
        "log five to syscall-table-ready");
    EXPECT_TRUE(result.machine.log[6].to_state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY,
        "log six to ipc-table-ready");
    EXPECT_TRUE(result.machine.log[7].to_state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY,
        "log seven to vfs-namespace-ready");
    EXPECT_TRUE(result.machine.log[8].to_state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY,
        "log eight to device-registry-ready");
    EXPECT_TRUE(result.machine.log[9].to_state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY,
        "log nine to driver-catalog-ready");
    EXPECT_TRUE(result.machine.log[10].to_state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY,
        "log ten to interrupt-table-ready");
    EXPECT_TRUE(result.machine.log[11].to_state == LATTICRA_KERNEL_STATE_TIMER_SOURCE_READY,
        "log eleven to timer-source-ready");
    EXPECT_TRUE(result.machine.log[12].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_TICK_READY,
        "log twelve to scheduler-tick-ready");
    EXPECT_TRUE(result.machine.log[12].state_change_performed == 1,
        "scheduler tick step changed state");
    EXPECT_TRUE(result.machine.log[13].to_state == LATTICRA_KERNEL_STATE_RUN_QUEUE_READY,
        "log thirteen to run-queue-ready");
    EXPECT_TRUE(result.machine.log[13].state_change_performed == 1,
        "run queue step changed state");
    EXPECT_TRUE(result.machine.log[14].to_state == LATTICRA_KERNEL_STATE_CONTEXT_SWITCH_READY,
        "log fourteen to context-switch-ready");
    EXPECT_TRUE(result.machine.log[14].state_change_performed == 1,
        "context switch step changed state");
    EXPECT_TRUE(result.machine.log[15].to_state == LATTICRA_KERNEL_STATE_TIME_ACCOUNTING_READY,
        "log fifteen to time-accounting-ready");
    EXPECT_TRUE(result.machine.log[15].state_change_performed == 1,
        "time accounting step changed state");
    EXPECT_TRUE(result.machine.log[16].to_state == LATTICRA_KERNEL_STATE_PREEMPTION_READY,
        "log sixteen to preemption-ready");
    EXPECT_TRUE(result.machine.log[16].state_change_performed == 1,
        "preemption step changed state");
    EXPECT_TRUE(result.machine.log[17].to_state == LATTICRA_KERNEL_STATE_SCHEDULER_CREDIT_READY,
        "log seventeen to scheduler-credit-ready");
    EXPECT_TRUE(result.machine.log[17].state_change_performed == 1,
        "last step changed state");
    return 0;
}

static int lifecycle_can_stop_at_intermediate_target(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for intermediate target");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.target_state = LATTICRA_KERNEL_STATE_SCHEDULER_READY;

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "intermediate lifecycle evaluates");
    EXPECT_TRUE(strcmp(result.lifecycle_status, "lifecycle-complete") == 0,
        "intermediate lifecycle complete");
    EXPECT_TRUE(result.final_state == LATTICRA_KERNEL_STATE_SCHEDULER_READY,
        "final state scheduler-ready");
    EXPECT_TRUE(result.step_count == 3u,
        "three steps to scheduler-ready");
    EXPECT_TRUE(result.state_change_count == 3u,
        "three state changes");
    EXPECT_TRUE(result.lifecycle_complete == 1,
        "intermediate complete flag");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "intermediate external effects absent");
    return 0;
}

static int lifecycle_can_stop_at_process_table_ready(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for process target");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.target_state = LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "process lifecycle evaluates");
    EXPECT_TRUE(strcmp(result.lifecycle_status, "lifecycle-complete") == 0,
        "process lifecycle complete");
    EXPECT_TRUE(result.final_state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY,
        "final state process-table-ready");
    EXPECT_TRUE(result.step_count == 5u,
        "five steps to process-table-ready");
    EXPECT_TRUE(result.state_change_count == 5u,
        "five state changes");
    EXPECT_TRUE(result.lifecycle_complete == 1,
        "process complete flag");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "process external effects absent");
    return 0;
}

static int lifecycle_respects_step_limit(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for limit");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;
    request.max_steps = 2u;

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "limited lifecycle evaluates");
    EXPECT_TRUE(strcmp(result.lifecycle_status, "step-limit-reached") == 0,
        "step limit reached");
    EXPECT_TRUE(result.final_state == LATTICRA_KERNEL_STATE_REGISTRY_READY,
        "final state registry-ready after limit");
    EXPECT_TRUE(result.step_count == 2u,
        "two steps performed");
    EXPECT_TRUE(result.state_change_count == 2u,
        "two state changes");
    EXPECT_TRUE(result.lifecycle_complete == 0,
        "limited lifecycle incomplete");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "limited external effects absent");
    return 0;
}

static int lifecycle_report_is_deterministic(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    EXPECT_TRUE(latticra_kernel_lifecycle_run(&request, &result) == LATTICRA_STATUS_OK,
        "lifecycle run for report");
    EXPECT_TRUE(latticra_kernel_lifecycle_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "lifecycle report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL LIFECYCLE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "lifecycle_status=lifecycle-complete\n") != 0,
        "lifecycle status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=gate-allowed\n") != 0,
        "policy status emitted");
    EXPECT_TRUE(strstr(report, "final_state=scheduler-credit-ready\n") != 0,
        "final state emitted");
    EXPECT_TRUE(strstr(report, "step_count=18\n") != 0,
        "step count emitted");
    EXPECT_TRUE(strstr(report, "state_change_count=18\n") != 0,
        "state change count emitted");
    EXPECT_TRUE(strstr(report, "lifecycle_complete=1\n") != 0,
        "complete flag emitted");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "external effect emitted");
    EXPECT_TRUE(strstr(report, "machine_log_count=18\n") != 0,
        "machine log count emitted");
    EXPECT_TRUE(strstr(report, "log[0].from=created\n") != 0,
        "log zero from emitted");
    EXPECT_TRUE(strstr(report, "log[4].to=process-table-ready\n") != 0,
        "log process to emitted");
    EXPECT_TRUE(strstr(report, "log[5].to=syscall-table-ready\n") != 0,
        "log syscall to emitted");
    EXPECT_TRUE(strstr(report, "log[6].to=ipc-table-ready\n") != 0,
        "log ipc to emitted");
    EXPECT_TRUE(strstr(report, "log[7].to=vfs-namespace-ready\n") != 0,
        "log vfs to emitted");
    EXPECT_TRUE(strstr(report, "log[8].to=device-registry-ready\n") != 0,
        "log device to emitted");
    EXPECT_TRUE(strstr(report, "log[9].to=driver-catalog-ready\n") != 0,
        "log driver to emitted");
    EXPECT_TRUE(strstr(report, "log[10].to=interrupt-table-ready\n") != 0,
        "log interrupt to emitted");
    EXPECT_TRUE(strstr(report, "log[11].to=timer-source-ready\n") != 0,
        "log timer source to emitted");
    EXPECT_TRUE(strstr(report, "log[12].to=scheduler-tick-ready\n") != 0,
        "log scheduler tick to emitted");
    EXPECT_TRUE(strstr(report, "log[12].state_change_performed=1\n") != 0,
        "log scheduler tick change emitted");
    EXPECT_TRUE(strstr(report, "log[13].to=run-queue-ready\n") != 0,
        "log run queue to emitted");
    EXPECT_TRUE(strstr(report, "log[13].state_change_performed=1\n") != 0,
        "log run queue change emitted");
    EXPECT_TRUE(strstr(report, "log[14].to=context-switch-ready\n") != 0,
        "log context switch to emitted");
    EXPECT_TRUE(strstr(report, "log[14].state_change_performed=1\n") != 0,
        "log context switch change emitted");
    EXPECT_TRUE(strstr(report, "log[15].to=time-accounting-ready\n") != 0,
        "log time accounting to emitted");
    EXPECT_TRUE(strstr(report, "log[15].state_change_performed=1\n") != 0,
        "log time accounting change emitted");
    EXPECT_TRUE(strstr(report, "log[16].to=preemption-ready\n") != 0,
        "log preemption to emitted");
    EXPECT_TRUE(strstr(report, "log[16].state_change_performed=1\n") != 0,
        "log preemption change emitted");
    EXPECT_TRUE(strstr(report, "log[17].to=scheduler-credit-ready\n") != 0,
        "log final to emitted");
    EXPECT_TRUE(strstr(report, "log[17].state_change_performed=1\n") != 0,
        "log final change emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_lifecycle_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_lifecycle_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_lifecycle_run(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null lifecycle request");
    EXPECT_TRUE(latticra_kernel_lifecycle_run(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null lifecycle result");
    EXPECT_TRUE(latticra_kernel_lifecycle_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_lifecycle_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_lifecycle_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_denied() != 0) return 1;
    if (allowed_lifecycle_reaches_scheduler_credit_ready() != 0) return 1;
    if (lifecycle_can_stop_at_intermediate_target() != 0) return 1;
    if (lifecycle_can_stop_at_process_table_ready() != 0) return 1;
    if (lifecycle_respects_step_limit() != 0) return 1;
    if (lifecycle_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_lifecycle: ok");
    return 0;
}
