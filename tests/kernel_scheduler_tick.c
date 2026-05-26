#include "latticra/kernel_scheduler_tick.h"

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
    latticra_kernel_scheduler_tick_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_tick_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_tick_count == 4u,
        "default tick count");
    EXPECT_TRUE(request.timer_source_request.requested_timer_count == 4u,
        "timer source seed request preserved");
    EXPECT_TRUE(request.timer_source_request.interrupt_table_request.requested_route_count == 4u,
        "interrupt table seed request preserved");
    return 0;
}

static int scheduler_tick_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_tick_request_t request;
    latticra_kernel_scheduler_tick_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_tick_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler tick evaluates");
    EXPECT_TRUE(strcmp(result.tick_status, "scheduler-tick-seed-ready") == 0,
        "scheduler tick ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.timer_source.timer_status,
            "timer-source-seed-ready") == 0,
        "timer source ready");
    EXPECT_TRUE(strcmp(result.timer_source.interrupt_table.table_status,
            "interrupt-table-seed-ready") == 0,
        "interrupt table ready");
    EXPECT_TRUE(strcmp(result.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.scheduler.scheduler_status,
            "scheduler-seed-ready") == 0,
        "scheduler ready");
    EXPECT_TRUE(result.tick_count == 4u,
        "tick count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler tick no-effect");
    EXPECT_TRUE(result.timer_tick_allowed == 0,
        "timer tick denied");
    EXPECT_TRUE(result.scheduler_tick_allowed == 0,
        "scheduler tick denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.time_read_allowed == 0,
        "time read denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.ticks[0].timer_name, "kernel-tick-timer-metadata") == 0,
        "tick zero timer");
    EXPECT_TRUE(result.ticks[0].timer_token == 0ul,
        "tick zero timer token");
    EXPECT_TRUE(result.ticks[0].irq_vector == 35ul,
        "tick zero irq");
    EXPECT_TRUE(result.ticks[0].budget_ns == 10000000ul,
        "tick zero budget");
    EXPECT_TRUE(strcmp(result.ticks[0].scheduler_slot_label, "idle-metadata") == 0,
        "tick zero scheduler slot");
    EXPECT_TRUE(strcmp(result.ticks[0].process_label, "idle-process-metadata") == 0,
        "tick zero process");
    EXPECT_TRUE(strcmp(result.ticks[0].tick_class, "scheduler-clock-tick") == 0,
        "tick zero class");
    EXPECT_TRUE(strcmp(result.ticks[0].authority_status,
            "scheduler-tick-authority-denied") == 0,
        "tick authority denied");
    EXPECT_TRUE(result.ticks[0].declared == 1,
        "tick declared");
    EXPECT_TRUE(result.ticks[0].pending == 0,
        "tick not pending");
    EXPECT_TRUE(result.ticks[0].dispatched == 0,
        "tick not dispatched");
    EXPECT_TRUE(result.ticks[0].run_queue_mutation_allowed == 0,
        "tick run queue mutation denied");
    EXPECT_TRUE(result.ticks[0].context_switch_allowed == 0,
        "tick context switch denied");
    EXPECT_TRUE(result.ticks[0].time_accounting_allowed == 0,
        "tick time accounting denied");
    EXPECT_TRUE(result.ticks[0].process_wake_allowed == 0,
        "tick process wake denied");
    EXPECT_TRUE(result.ticks[0].no_effect == 1,
        "tick no-effect");
    EXPECT_TRUE(strcmp(result.ticks[1].tick_class, "time-accounting-sample") == 0,
        "monotonic tick class");
    EXPECT_TRUE(strcmp(result.ticks[2].tick_class, "entropy-wakeup-window") == 0,
        "entropy tick class");
    EXPECT_TRUE(strcmp(result.ticks[3].tick_class, "console-timeout-window") == 0,
        "console tick class");
    return 0;
}

static int scheduler_tick_caps_tick_count(void) {
    latticra_kernel_scheduler_tick_request_t request;
    latticra_kernel_scheduler_tick_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_tick_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_tick_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_tick_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler tick evaluates cap");
    EXPECT_TRUE(result.tick_count == LATTICRA_KERNEL_SCHEDULER_TICK_MAX,
        "tick count capped");
    EXPECT_TRUE(strcmp(result.ticks[4].tick_class, "reserved-scheduler-tick") == 0,
        "reserved tick class");
    EXPECT_TRUE(result.ticks[4].tick_token == 4004ul,
        "reserved tick token");
    return 0;
}

static int scheduler_tick_report_is_deterministic(void) {
    latticra_kernel_scheduler_tick_request_t request;
    latticra_kernel_scheduler_tick_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_TICK_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_tick_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler tick evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL SCHEDULER TICK REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "tick_status=scheduler-tick-seed-ready\n") != 0,
        "tick status emitted");
    EXPECT_TRUE(strstr(report, "timer_source_status=timer-source-seed-ready\n") != 0,
        "timer source emitted");
    EXPECT_TRUE(strstr(report, "scheduler_status=scheduler-seed-ready\n") != 0,
        "scheduler emitted");
    EXPECT_TRUE(strstr(report, "tick_count=4\n") != 0,
        "tick count emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "time_accounting_allowed=0\n") != 0,
        "time accounting flag emitted");
    EXPECT_TRUE(strstr(report, "process_wake_allowed=0\n") != 0,
        "process wake flag emitted");
    EXPECT_TRUE(strstr(report, "tick[0].timer_name=kernel-tick-timer-metadata\n") != 0,
        "tick zero timer emitted");
    EXPECT_TRUE(strstr(report, "tick[0].scheduler_slot_label=idle-metadata\n") != 0,
        "tick zero slot emitted");
    EXPECT_TRUE(strstr(report, "tick[0].tick_class=scheduler-clock-tick\n") != 0,
        "tick zero class emitted");
    EXPECT_TRUE(strstr(report, "tick[0].pending=0\n") != 0,
        "pending emitted");
    EXPECT_TRUE(strstr(report, "tick[0].dispatched=0\n") != 0,
        "dispatched emitted");
    EXPECT_TRUE(strstr(report, "tick[0].no_effect=1\n") != 0,
        "tick no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_tick_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_TICK_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_tick_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_tick_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_tick_seed_is_metadata_only() != 0) return 1;
    if (scheduler_tick_caps_tick_count() != 0) return 1;
    if (scheduler_tick_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_tick: ok");
    return 0;
}
