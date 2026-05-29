#include "latticra/kernel_context_switch.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_is_stable(void) {
    latticra_kernel_context_switch_request_t request;

    EXPECT_TRUE(latticra_kernel_context_switch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_switch_count == 4u,
        "default switch count");
    EXPECT_TRUE(request.run_queue_request.requested_queue_count == 4u,
        "run queue seed request preserved");
    EXPECT_TRUE(request.run_queue_request.scheduler_tick_request.requested_tick_count == 4u,
        "scheduler tick seed request preserved");
    return 0;
}

static int context_switch_seed_is_metadata_only(void) {
    latticra_kernel_context_switch_request_t request;
    latticra_kernel_context_switch_result_t result;

    EXPECT_TRUE(latticra_kernel_context_switch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_context_switch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "context switch evaluates");
    EXPECT_TRUE(strcmp(result.switch_status, "context-switch-seed-ready") == 0,
        "context switch ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.run_queue.queue_status, "run-queue-seed-ready") == 0,
        "run queue ready");
    EXPECT_TRUE(strcmp(result.run_queue.scheduler_tick.tick_status,
            "scheduler-tick-seed-ready") == 0,
        "scheduler tick ready");
    EXPECT_TRUE(result.switch_count == 4u,
        "switch count four");
    EXPECT_TRUE(result.no_effect == 1,
        "context switch no-effect");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.register_save_allowed == 0,
        "register save denied");
    EXPECT_TRUE(result.register_restore_allowed == 0,
        "register restore denied");
    EXPECT_TRUE(result.stack_switch_allowed == 0,
        "stack switch denied");
    EXPECT_TRUE(result.address_space_switch_allowed == 0,
        "address space switch denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.switches[0].from_process_label,
            "idle-process-metadata") == 0,
        "switch zero from process");
    EXPECT_TRUE(strcmp(result.switches[0].to_process_label,
            "kernel-report-process-metadata") == 0,
        "switch zero to process");
    EXPECT_TRUE(strcmp(result.switches[0].scheduler_slot_label,
            "kernel-report-metadata") == 0,
        "switch zero scheduler slot");
    EXPECT_TRUE(strcmp(result.switches[0].switch_class,
            "idle-to-kernel-report-context-switch") == 0,
        "switch zero class");
    EXPECT_TRUE(result.switches[0].switch_token == 0ul,
        "switch zero token");
    EXPECT_TRUE(result.switches[0].from_pid_token == 0ul,
        "switch zero from pid");
    EXPECT_TRUE(result.switches[0].to_pid_token == 1ul,
        "switch zero to pid");
    EXPECT_TRUE(result.switches[0].queue_token == 1ul,
        "switch zero queue token");
    EXPECT_TRUE(result.switches[0].tick_token == 1ul,
        "switch zero tick token");
    EXPECT_TRUE(result.switches[0].priority == 10ul,
        "switch zero priority");
    EXPECT_TRUE(strcmp(result.switches[0].authority_status,
            "context-switch-authority-denied") == 0,
        "switch authority denied");
    EXPECT_TRUE(result.switches[0].declared == 1,
        "switch declared");
    EXPECT_TRUE(result.switches[0].prepared == 0,
        "switch not prepared");
    EXPECT_TRUE(result.switches[0].selected == 0,
        "switch not selected");
    EXPECT_TRUE(result.switches[0].committed == 0,
        "switch not committed");
    EXPECT_TRUE(result.switches[0].context_switch_allowed == 0,
        "switch context denied");
    EXPECT_TRUE(result.switches[0].register_save_allowed == 0,
        "switch register save denied");
    EXPECT_TRUE(result.switches[0].register_restore_allowed == 0,
        "switch register restore denied");
    EXPECT_TRUE(result.switches[0].stack_switch_allowed == 0,
        "switch stack denied");
    EXPECT_TRUE(result.switches[0].address_space_switch_allowed == 0,
        "switch address space denied");
    EXPECT_TRUE(result.switches[0].dispatch_allowed == 0,
        "switch dispatch denied");
    EXPECT_TRUE(result.switches[0].run_queue_mutation_allowed == 0,
        "switch run queue mutation denied");
    EXPECT_TRUE(result.switches[0].time_accounting_allowed == 0,
        "switch time accounting denied");
    EXPECT_TRUE(result.switches[0].process_wake_allowed == 0,
        "switch process wake denied");
    EXPECT_TRUE(result.switches[0].no_effect == 1,
        "switch no-effect");
    EXPECT_TRUE(strcmp(result.switches[1].switch_class,
            "kernel-report-to-entropy-context-switch") == 0,
        "kernel report switch class");
    EXPECT_TRUE(strcmp(result.switches[2].switch_class,
            "entropy-to-console-context-switch") == 0,
        "entropy switch class");
    EXPECT_TRUE(strcmp(result.switches[3].switch_class,
            "console-to-idle-context-switch") == 0,
        "console switch class");
    return 0;
}

static int context_switch_caps_switch_count(void) {
    latticra_kernel_context_switch_request_t request;
    latticra_kernel_context_switch_result_t result;

    EXPECT_TRUE(latticra_kernel_context_switch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_switch_count = 99u;
    EXPECT_TRUE(latticra_kernel_context_switch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "context switch evaluates cap");
    EXPECT_TRUE(result.switch_count == LATTICRA_KERNEL_CONTEXT_SWITCH_MAX,
        "switch count capped");
    EXPECT_TRUE(strcmp(result.switches[4].switch_class,
            "reserved-context-switch") == 0,
        "reserved switch class");
    EXPECT_TRUE(result.switches[4].switch_token == 6004ul,
        "reserved switch token");
    EXPECT_TRUE(result.switches[4].from_pid_token == 1004ul,
        "reserved from pid token");
    return 0;
}

static int context_switch_report_is_deterministic(void) {
    latticra_kernel_context_switch_request_t request;
    latticra_kernel_context_switch_result_t result;
    char report[LATTICRA_KERNEL_CONTEXT_SWITCH_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_context_switch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_context_switch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "context switch evaluates for report");
    EXPECT_TRUE(latticra_kernel_context_switch_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL CONTEXT SWITCH REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "switch_status=context-switch-seed-ready\n") != 0,
        "switch status emitted");
    EXPECT_TRUE(strstr(report, "run_queue_status=run-queue-seed-ready\n") != 0,
        "run queue emitted");
    EXPECT_TRUE(strstr(report, "scheduler_tick_status=scheduler-tick-seed-ready\n") != 0,
        "scheduler tick emitted");
    EXPECT_TRUE(strstr(report, "switch_count=4\n") != 0,
        "switch count emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "register_save_allowed=0\n") != 0,
        "register save flag emitted");
    EXPECT_TRUE(strstr(report, "register_restore_allowed=0\n") != 0,
        "register restore flag emitted");
    EXPECT_TRUE(strstr(report, "stack_switch_allowed=0\n") != 0,
        "stack switch flag emitted");
    EXPECT_TRUE(strstr(report, "address_space_switch_allowed=0\n") != 0,
        "address space flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "switch[0].from_process_label=idle-process-metadata\n") != 0,
        "switch zero from emitted");
    EXPECT_TRUE(strstr(report, "switch[0].to_process_label=kernel-report-process-metadata\n") != 0,
        "switch zero to emitted");
    EXPECT_TRUE(strstr(report, "switch[0].switch_class=idle-to-kernel-report-context-switch\n") != 0,
        "switch zero class emitted");
    EXPECT_TRUE(strstr(report, "switch[0].prepared=0\n") != 0,
        "prepared emitted");
    EXPECT_TRUE(strstr(report, "switch[0].selected=0\n") != 0,
        "selected emitted");
    EXPECT_TRUE(strstr(report, "switch[0].committed=0\n") != 0,
        "committed emitted");
    EXPECT_TRUE(strstr(report, "switch[0].no_effect=1\n") != 0,
        "switch no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_context_switch_result_t result;
    char report[LATTICRA_KERNEL_CONTEXT_SWITCH_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_context_switch_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_context_switch_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_context_switch_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_context_switch_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_context_switch_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_context_switch_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (context_switch_seed_is_metadata_only() != 0) return 1;
    if (context_switch_caps_switch_count() != 0) return 1;
    if (context_switch_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_context_switch: ok");
    return 0;
}
