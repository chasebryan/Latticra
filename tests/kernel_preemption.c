#include "latticra/kernel_preemption.h"

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
    latticra_kernel_preemption_request_t request;

    EXPECT_TRUE(latticra_kernel_preemption_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_decision_count == 4u,
        "default decision count");
    EXPECT_TRUE(request.time_accounting_request.requested_account_count == 4u,
        "time accounting seed request preserved");
    EXPECT_TRUE(request.time_accounting_request.context_switch_request.requested_switch_count == 4u,
        "context switch seed request preserved");
    return 0;
}

static int preemption_seed_is_metadata_only(void) {
    latticra_kernel_preemption_request_t request;
    latticra_kernel_preemption_result_t result;

    EXPECT_TRUE(latticra_kernel_preemption_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_preemption_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "preemption evaluates");
    EXPECT_TRUE(strcmp(result.preemption_status, "preemption-seed-ready") == 0,
        "preemption ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.time_accounting.accounting_status,
            "time-accounting-seed-ready") == 0,
        "time accounting ready");
    EXPECT_TRUE(strcmp(result.time_accounting.context_switch.switch_status,
            "context-switch-seed-ready") == 0,
        "context switch ready");
    EXPECT_TRUE(result.decision_count == 4u,
        "decision count four");
    EXPECT_TRUE(result.no_effect == 1,
        "preemption no-effect");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.time_read_allowed == 0,
        "time read denied");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.scheduler_credit_update_allowed == 0,
        "scheduler credit update denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.decisions[0].process_label,
            "kernel-report-process-metadata") == 0,
        "decision zero process");
    EXPECT_TRUE(strcmp(result.decisions[0].decision_class,
            "kernel-report-preemption-decision") == 0,
        "decision zero class");
    EXPECT_TRUE(result.decisions[0].decision_token == 0ul,
        "decision zero token");
    EXPECT_TRUE(result.decisions[0].pid_token == 1ul,
        "decision zero pid");
    EXPECT_TRUE(result.decisions[0].switch_token == 0ul,
        "decision zero switch token");
    EXPECT_TRUE(result.decisions[0].tick_token == 1ul,
        "decision zero tick token");
    EXPECT_TRUE(result.decisions[0].charged_budget_ns == 10000000ul,
        "decision zero budget");
    EXPECT_TRUE(result.decisions[0].consumed_ns == 0ul,
        "decision zero consumed");
    EXPECT_TRUE(result.decisions[0].remaining_budget_ns == 10000000ul,
        "decision zero remaining");
    EXPECT_TRUE(result.decisions[0].preemption_requested == 0,
        "decision zero no preemption request");
    EXPECT_TRUE(strcmp(result.decisions[0].authority_status,
            "preemption-authority-denied") == 0,
        "decision authority denied");
    EXPECT_TRUE(result.decisions[0].declared == 1,
        "decision declared");
    EXPECT_TRUE(result.decisions[0].evaluated == 0,
        "decision not evaluated");
    EXPECT_TRUE(result.decisions[0].armed == 0,
        "decision not armed");
    EXPECT_TRUE(result.decisions[0].dispatched == 0,
        "decision not dispatched");
    EXPECT_TRUE(result.decisions[0].preemption_allowed == 0,
        "decision preemption denied");
    EXPECT_TRUE(result.decisions[0].dispatch_allowed == 0,
        "decision dispatch denied");
    EXPECT_TRUE(result.decisions[0].run_queue_mutation_allowed == 0,
        "decision run queue mutation denied");
    EXPECT_TRUE(result.decisions[0].no_effect == 1,
        "decision no-effect");
    EXPECT_TRUE(strcmp(result.decisions[1].decision_class,
            "entropy-preemption-decision") == 0,
        "entropy decision class");
    EXPECT_TRUE(strcmp(result.decisions[2].decision_class,
            "console-preemption-decision") == 0,
        "console decision class");
    EXPECT_TRUE(strcmp(result.decisions[3].decision_class,
            "idle-preemption-decision") == 0,
        "idle decision class");
    return 0;
}

static int preemption_caps_decision_count(void) {
    latticra_kernel_preemption_request_t request;
    latticra_kernel_preemption_result_t result;

    EXPECT_TRUE(latticra_kernel_preemption_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_decision_count = 99u;
    request.time_accounting_request.requested_account_count = 99u;
    request.time_accounting_request.context_switch_request.requested_switch_count = 99u;
    EXPECT_TRUE(latticra_kernel_preemption_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "preemption evaluates cap");
    EXPECT_TRUE(result.decision_count == LATTICRA_KERNEL_PREEMPTION_MAX,
        "decision count capped");
    EXPECT_TRUE(strcmp(result.decisions[4].decision_class,
            "reserved-preemption-decision") == 0,
        "reserved decision class");
    EXPECT_TRUE(result.decisions[4].decision_token == 8004ul,
        "reserved decision token");
    EXPECT_TRUE(result.decisions[4].switch_token == 6004ul,
        "reserved switch token");
    return 0;
}

static int preemption_report_is_deterministic(void) {
    latticra_kernel_preemption_request_t request;
    latticra_kernel_preemption_result_t result;
    char report[LATTICRA_KERNEL_PREEMPTION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_preemption_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_preemption_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "preemption evaluates for report");
    EXPECT_TRUE(latticra_kernel_preemption_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL PREEMPTION REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "preemption_status=preemption-seed-ready\n") != 0,
        "preemption status emitted");
    EXPECT_TRUE(strstr(report, "time_accounting_status=time-accounting-seed-ready\n") != 0,
        "time accounting emitted");
    EXPECT_TRUE(strstr(report, "context_switch_status=context-switch-seed-ready\n") != 0,
        "context switch emitted");
    EXPECT_TRUE(strstr(report, "decision_count=4\n") != 0,
        "decision count emitted");
    EXPECT_TRUE(strstr(report, "preemption_allowed=0\n") != 0,
        "preemption flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "decision[0].process_label=kernel-report-process-metadata\n") != 0,
        "decision zero process emitted");
    EXPECT_TRUE(strstr(report, "decision[0].decision_class=kernel-report-preemption-decision\n") != 0,
        "decision zero class emitted");
    EXPECT_TRUE(strstr(report, "decision[0].remaining_budget_ns=10000000\n") != 0,
        "decision zero remaining emitted");
    EXPECT_TRUE(strstr(report, "decision[0].preemption_requested=0\n") != 0,
        "decision zero request emitted");
    EXPECT_TRUE(strstr(report, "decision[0].armed=0\n") != 0,
        "armed emitted");
    EXPECT_TRUE(strstr(report, "decision[0].dispatched=0\n") != 0,
        "dispatched emitted");
    EXPECT_TRUE(strstr(report, "decision[0].no_effect=1\n") != 0,
        "decision no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_preemption_result_t result;
    char report[LATTICRA_KERNEL_PREEMPTION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_preemption_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_preemption_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_preemption_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_preemption_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_preemption_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_preemption_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (preemption_seed_is_metadata_only() != 0) return 1;
    if (preemption_caps_decision_count() != 0) return 1;
    if (preemption_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_preemption: ok");
    return 0;
}
