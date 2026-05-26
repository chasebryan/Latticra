#include "latticra/kernel_timer_source.h"

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
    latticra_kernel_timer_source_request_t request;

    EXPECT_TRUE(latticra_kernel_timer_source_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_timer_count == 4u,
        "default timer count");
    EXPECT_TRUE(request.interrupt_table_request.requested_route_count == 4u,
        "interrupt table seed request preserved");
    EXPECT_TRUE(request.interrupt_table_request.driver_catalog_request.requested_driver_count == 4u,
        "driver catalog seed request preserved");
    return 0;
}

static int timer_source_seed_is_metadata_only(void) {
    latticra_kernel_timer_source_request_t request;
    latticra_kernel_timer_source_result_t result;

    EXPECT_TRUE(latticra_kernel_timer_source_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_timer_source_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "timer source evaluates");
    EXPECT_TRUE(strcmp(result.timer_status, "timer-source-seed-ready") == 0,
        "timer source ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.interrupt_table.table_status,
            "interrupt-table-seed-ready") == 0,
        "interrupt table ready");
    EXPECT_TRUE(strcmp(result.interrupt_table.driver_catalog.catalog_status,
            "driver-catalog-seed-ready") == 0,
        "driver catalog ready");
    EXPECT_TRUE(result.timer_count == 4u,
        "timer count four");
    EXPECT_TRUE(result.no_effect == 1,
        "timer source no-effect");
    EXPECT_TRUE(result.timer_tick_allowed == 0,
        "timer tick denied");
    EXPECT_TRUE(result.timer_arm_allowed == 0,
        "timer arm denied");
    EXPECT_TRUE(result.timer_disarm_allowed == 0,
        "timer disarm denied");
    EXPECT_TRUE(result.scheduler_tick_allowed == 0,
        "scheduler tick denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.time_read_allowed == 0,
        "time read denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.timers[0].name, "kernel-tick-timer-metadata") == 0,
        "kernel tick timer name");
    EXPECT_TRUE(result.timers[0].irq_vector == 35ul,
        "kernel tick irq vector");
    EXPECT_TRUE(result.timers[0].period_ns == 10000000ul,
        "kernel tick period");
    EXPECT_TRUE(strcmp(result.timers[0].timer_class, "scheduler-tick-source") == 0,
        "kernel tick class");
    EXPECT_TRUE(strcmp(result.timers[1].timer_class, "monotonic-time-source") == 0,
        "monotonic timer class");
    EXPECT_TRUE(strcmp(result.timers[2].driver_name, "entropy-driver-metadata") == 0,
        "entropy timer driver");
    EXPECT_TRUE(strcmp(result.timers[3].device_path, "/dev/console") == 0,
        "console timer path");
    EXPECT_TRUE(strcmp(result.timers[0].authority_status, "timer-authority-denied") == 0,
        "timer authority denied");
    EXPECT_TRUE(result.timers[0].declared == 1,
        "timer declared");
    EXPECT_TRUE(result.timers[0].armed == 0,
        "timer not armed");
    EXPECT_TRUE(result.timers[0].running == 0,
        "timer not running");
    EXPECT_TRUE(result.timers[0].tick_allowed == 0,
        "timer tick denied");
    EXPECT_TRUE(result.timers[0].arm_allowed == 0,
        "timer arm denied");
    EXPECT_TRUE(result.timers[0].disarm_allowed == 0,
        "timer disarm denied");
    EXPECT_TRUE(result.timers[0].scheduler_tick_allowed == 0,
        "timer scheduler tick denied");
    EXPECT_TRUE(result.timers[0].preemption_allowed == 0,
        "timer preemption denied");
    EXPECT_TRUE(result.timers[0].time_read_allowed == 0,
        "timer time read denied");
    EXPECT_TRUE(result.timers[0].hardware_effect_allowed == 0,
        "timer hardware effect denied");
    EXPECT_TRUE(result.timers[0].host_effect_allowed == 0,
        "timer host effect denied");
    EXPECT_TRUE(result.timers[0].no_effect == 1,
        "timer no-effect");
    return 0;
}

static int timer_source_caps_timer_count(void) {
    latticra_kernel_timer_source_request_t request;
    latticra_kernel_timer_source_result_t result;

    EXPECT_TRUE(latticra_kernel_timer_source_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_timer_count = 99u;
    EXPECT_TRUE(latticra_kernel_timer_source_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "timer source evaluates cap");
    EXPECT_TRUE(result.timer_count == LATTICRA_KERNEL_TIMER_SOURCE_TIMER_MAX,
        "timer count capped");
    EXPECT_TRUE(strcmp(result.timers[4].name, "reserved-timer-metadata") == 0,
        "reserved timer name");
    EXPECT_TRUE(result.timers[4].timer_token == 3004ul,
        "reserved timer token");
    return 0;
}

static int timer_source_report_is_deterministic(void) {
    latticra_kernel_timer_source_request_t request;
    latticra_kernel_timer_source_result_t result;
    char report[LATTICRA_KERNEL_TIMER_SOURCE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_timer_source_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_timer_source_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "timer source evaluates for report");
    EXPECT_TRUE(latticra_kernel_timer_source_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL TIMER SOURCE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "timer_status=timer-source-seed-ready\n") != 0,
        "timer status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "interrupt_table_status=interrupt-table-seed-ready\n") != 0,
        "interrupt table emitted");
    EXPECT_TRUE(strstr(report, "timer_count=4\n") != 0,
        "timer count emitted");
    EXPECT_TRUE(strstr(report, "timer_tick_allowed=0\n") != 0,
        "tick flag emitted");
    EXPECT_TRUE(strstr(report, "timer_arm_allowed=0\n") != 0,
        "arm flag emitted");
    EXPECT_TRUE(strstr(report, "timer_disarm_allowed=0\n") != 0,
        "disarm flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_tick_allowed=0\n") != 0,
        "scheduler tick flag emitted");
    EXPECT_TRUE(strstr(report, "preemption_allowed=0\n") != 0,
        "preemption flag emitted");
    EXPECT_TRUE(strstr(report, "time_read_allowed=0\n") != 0,
        "time read flag emitted");
    EXPECT_TRUE(strstr(report, "timer[0].name=kernel-tick-timer-metadata\n") != 0,
        "kernel tick emitted");
    EXPECT_TRUE(strstr(report, "timer[0].irq_vector=35\n") != 0,
        "timer vector emitted");
    EXPECT_TRUE(strstr(report, "timer[0].period_ns=10000000\n") != 0,
        "timer period emitted");
    EXPECT_TRUE(strstr(report, "timer[1].timer_class=monotonic-time-source\n") != 0,
        "monotonic class emitted");
    EXPECT_TRUE(strstr(report, "timer[0].armed=0\n") != 0,
        "armed flag emitted");
    EXPECT_TRUE(strstr(report, "timer[0].running=0\n") != 0,
        "running flag emitted");
    EXPECT_TRUE(strstr(report, "timer[0].no_effect=1\n") != 0,
        "timer no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_timer_source_result_t result;
    char report[LATTICRA_KERNEL_TIMER_SOURCE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_timer_source_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_timer_source_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_timer_source_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_timer_source_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_timer_source_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_timer_source_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (timer_source_seed_is_metadata_only() != 0) return 1;
    if (timer_source_caps_timer_count() != 0) return 1;
    if (timer_source_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_timer_source: ok");
    return 0;
}
