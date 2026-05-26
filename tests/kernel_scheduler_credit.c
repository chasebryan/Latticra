#include "latticra/kernel_scheduler_credit.h"

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
    latticra_kernel_scheduler_credit_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_credit_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_credit_count == 4u,
        "default credit count");
    EXPECT_TRUE(request.preemption_request.requested_decision_count == 4u,
        "preemption seed request preserved");
    EXPECT_TRUE(request.preemption_request.time_accounting_request.requested_account_count == 4u,
        "time accounting seed request preserved");
    EXPECT_TRUE(request.preemption_request.time_accounting_request.context_switch_request.requested_switch_count == 4u,
        "context switch seed request preserved");
    return 0;
}

static int scheduler_credit_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_credit_request_t request;
    latticra_kernel_scheduler_credit_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_credit_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler credit evaluates");
    EXPECT_TRUE(strcmp(result.credit_status,
            "scheduler-credit-seed-ready") == 0,
        "scheduler credit ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.preemption.preemption_status,
            "preemption-seed-ready") == 0,
        "preemption ready");
    EXPECT_TRUE(strcmp(result.preemption.time_accounting.accounting_status,
            "time-accounting-seed-ready") == 0,
        "time accounting ready");
    EXPECT_TRUE(strcmp(result.preemption.time_accounting.context_switch.switch_status,
            "context-switch-seed-ready") == 0,
        "context switch ready");
    EXPECT_TRUE(result.credit_count == 4u,
        "credit count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler credit no-effect");
    EXPECT_TRUE(result.scheduler_credit_update_allowed == 0,
        "scheduler credit update denied");
    EXPECT_TRUE(result.quota_update_allowed == 0,
        "quota update denied");
    EXPECT_TRUE(result.cpu_usage_write_allowed == 0,
        "cpu usage write denied");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.time_read_allowed == 0,
        "time read denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.credits[0].process_label,
            "kernel-report-process-metadata") == 0,
        "credit zero process");
    EXPECT_TRUE(strcmp(result.credits[0].credit_class,
            "kernel-report-scheduler-credit") == 0,
        "credit zero class");
    EXPECT_TRUE(result.credits[0].credit_token == 0ul,
        "credit zero token");
    EXPECT_TRUE(result.credits[0].pid_token == 1ul,
        "credit zero pid");
    EXPECT_TRUE(result.credits[0].decision_token == 0ul,
        "credit zero decision token");
    EXPECT_TRUE(result.credits[0].switch_token == 0ul,
        "credit zero switch token");
    EXPECT_TRUE(result.credits[0].tick_token == 1ul,
        "credit zero tick token");
    EXPECT_TRUE(result.credits[0].charged_budget_ns == 10000000ul,
        "credit zero budget");
    EXPECT_TRUE(result.credits[0].consumed_ns == 0ul,
        "credit zero consumed");
    EXPECT_TRUE(result.credits[0].remaining_budget_ns == 10000000ul,
        "credit zero remaining");
    EXPECT_TRUE(result.credits[0].scheduler_credit_ns == 10000000ul,
        "credit zero scheduler credit");
    EXPECT_TRUE(result.credits[0].quota_credit_ns == 10000000ul,
        "credit zero quota credit");
    EXPECT_TRUE(result.credits[0].credit_update_requested == 0,
        "credit zero no update request");
    EXPECT_TRUE(strcmp(result.credits[0].authority_status,
            "scheduler-credit-authority-denied") == 0,
        "credit authority denied");
    EXPECT_TRUE(result.credits[0].declared == 1,
        "credit declared");
    EXPECT_TRUE(result.credits[0].computed == 0,
        "credit not computed");
    EXPECT_TRUE(result.credits[0].queued == 0,
        "credit not queued");
    EXPECT_TRUE(result.credits[0].persisted == 0,
        "credit not persisted");
    EXPECT_TRUE(result.credits[0].scheduler_credit_update_allowed == 0,
        "credit scheduler update denied");
    EXPECT_TRUE(result.credits[0].quota_update_allowed == 0,
        "credit quota update denied");
    EXPECT_TRUE(result.credits[0].cpu_usage_write_allowed == 0,
        "credit cpu usage write denied");
    EXPECT_TRUE(result.credits[0].preemption_allowed == 0,
        "credit preemption denied");
    EXPECT_TRUE(result.credits[0].dispatch_allowed == 0,
        "credit dispatch denied");
    EXPECT_TRUE(result.credits[0].run_queue_mutation_allowed == 0,
        "credit run queue mutation denied");
    EXPECT_TRUE(result.credits[0].no_effect == 1,
        "credit no-effect");
    EXPECT_TRUE(strcmp(result.credits[1].credit_class,
            "entropy-scheduler-credit") == 0,
        "entropy credit class");
    EXPECT_TRUE(strcmp(result.credits[2].credit_class,
            "console-scheduler-credit") == 0,
        "console credit class");
    EXPECT_TRUE(strcmp(result.credits[3].credit_class,
            "idle-scheduler-credit") == 0,
        "idle credit class");
    return 0;
}

static int scheduler_credit_caps_credit_count(void) {
    latticra_kernel_scheduler_credit_request_t request;
    latticra_kernel_scheduler_credit_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_credit_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_credit_count = 99u;
    request.preemption_request.requested_decision_count = 99u;
    request.preemption_request.time_accounting_request.requested_account_count = 99u;
    request.preemption_request.time_accounting_request.context_switch_request.requested_switch_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_credit_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler credit evaluates cap");
    EXPECT_TRUE(result.credit_count == LATTICRA_KERNEL_SCHEDULER_CREDIT_MAX,
        "credit count capped");
    EXPECT_TRUE(strcmp(result.credits[4].credit_class,
            "reserved-scheduler-credit") == 0,
        "reserved credit class");
    EXPECT_TRUE(result.credits[4].credit_token == 9004ul,
        "reserved credit token");
    EXPECT_TRUE(result.credits[4].decision_token == 8004ul,
        "reserved decision token");
    EXPECT_TRUE(result.credits[4].switch_token == 6004ul,
        "reserved switch token");
    return 0;
}

static int scheduler_credit_report_is_deterministic(void) {
    latticra_kernel_scheduler_credit_request_t request;
    latticra_kernel_scheduler_credit_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_CREDIT_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_credit_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler credit evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER CREDIT REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "credit_status=scheduler-credit-seed-ready\n") != 0,
        "credit status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "preemption_status=preemption-seed-ready\n") != 0,
        "preemption status emitted");
    EXPECT_TRUE(strstr(report, "time_accounting_status=time-accounting-seed-ready\n") != 0,
        "time accounting emitted");
    EXPECT_TRUE(strstr(report, "context_switch_status=context-switch-seed-ready\n") != 0,
        "context switch emitted");
    EXPECT_TRUE(strstr(report, "credit_count=4\n") != 0,
        "credit count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_credit_update_allowed=0\n") != 0,
        "scheduler credit flag emitted");
    EXPECT_TRUE(strstr(report, "quota_update_allowed=0\n") != 0,
        "quota flag emitted");
    EXPECT_TRUE(strstr(report, "cpu_usage_write_allowed=0\n") != 0,
        "cpu usage flag emitted");
    EXPECT_TRUE(strstr(report, "preemption_allowed=0\n") != 0,
        "preemption flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "credit[0].process_label=kernel-report-process-metadata\n") != 0,
        "credit zero process emitted");
    EXPECT_TRUE(strstr(report, "credit[0].credit_class=kernel-report-scheduler-credit\n") != 0,
        "credit zero class emitted");
    EXPECT_TRUE(strstr(report, "credit[0].remaining_budget_ns=10000000\n") != 0,
        "credit zero remaining emitted");
    EXPECT_TRUE(strstr(report, "credit[0].scheduler_credit_ns=10000000\n") != 0,
        "credit zero scheduler credit emitted");
    EXPECT_TRUE(strstr(report, "credit[0].quota_credit_ns=10000000\n") != 0,
        "credit zero quota credit emitted");
    EXPECT_TRUE(strstr(report, "credit[0].credit_update_requested=0\n") != 0,
        "credit zero update request emitted");
    EXPECT_TRUE(strstr(report, "credit[0].computed=0\n") != 0,
        "computed emitted");
    EXPECT_TRUE(strstr(report, "credit[0].queued=0\n") != 0,
        "queued emitted");
    EXPECT_TRUE(strstr(report, "credit[0].persisted=0\n") != 0,
        "persisted emitted");
    EXPECT_TRUE(strstr(report, "credit[0].no_effect=1\n") != 0,
        "credit no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_credit_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_CREDIT_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_credit_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_credit_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_credit_seed_is_metadata_only() != 0) return 1;
    if (scheduler_credit_caps_credit_count() != 0) return 1;
    if (scheduler_credit_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_credit: ok");
    return 0;
}
