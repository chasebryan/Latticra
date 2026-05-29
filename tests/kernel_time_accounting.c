#include "latticra/kernel_time_accounting.h"

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
    latticra_kernel_time_accounting_request_t request;

    EXPECT_TRUE(latticra_kernel_time_accounting_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_account_count == 4u,
        "default account count");
    EXPECT_TRUE(request.context_switch_request.requested_switch_count == 4u,
        "context switch seed request preserved");
    EXPECT_TRUE(request.context_switch_request.run_queue_request.requested_queue_count == 4u,
        "run queue seed request preserved");
    return 0;
}

static int time_accounting_seed_is_metadata_only(void) {
    latticra_kernel_time_accounting_request_t request;
    latticra_kernel_time_accounting_result_t result;

    EXPECT_TRUE(latticra_kernel_time_accounting_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_time_accounting_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "time accounting evaluates");
    EXPECT_TRUE(strcmp(result.accounting_status, "time-accounting-seed-ready") == 0,
        "time accounting ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.context_switch.switch_status,
            "context-switch-seed-ready") == 0,
        "context switch ready");
    EXPECT_TRUE(strcmp(result.context_switch.run_queue.queue_status,
            "run-queue-seed-ready") == 0,
        "run queue ready");
    EXPECT_TRUE(result.account_count == 4u,
        "account count four");
    EXPECT_TRUE(result.no_effect == 1,
        "time accounting no-effect");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.time_read_allowed == 0,
        "time read denied");
    EXPECT_TRUE(result.cpu_usage_write_allowed == 0,
        "cpu usage write denied");
    EXPECT_TRUE(result.quota_update_allowed == 0,
        "quota update denied");
    EXPECT_TRUE(result.scheduler_credit_update_allowed == 0,
        "scheduler credit update denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.accounts[0].process_label,
            "kernel-report-process-metadata") == 0,
        "account zero process");
    EXPECT_TRUE(strcmp(result.accounts[0].accounting_class,
            "kernel-report-time-accounting") == 0,
        "account zero class");
    EXPECT_TRUE(result.accounts[0].account_token == 0ul,
        "account zero token");
    EXPECT_TRUE(result.accounts[0].pid_token == 1ul,
        "account zero pid");
    EXPECT_TRUE(result.accounts[0].switch_token == 0ul,
        "account zero switch token");
    EXPECT_TRUE(result.accounts[0].tick_token == 1ul,
        "account zero tick token");
    EXPECT_TRUE(result.accounts[0].charged_budget_ns == 10000000ul,
        "account zero budget");
    EXPECT_TRUE(result.accounts[0].consumed_ns == 0ul,
        "account zero consumed");
    EXPECT_TRUE(strcmp(result.accounts[0].authority_status,
            "time-accounting-authority-denied") == 0,
        "account authority denied");
    EXPECT_TRUE(result.accounts[0].declared == 1,
        "account declared");
    EXPECT_TRUE(result.accounts[0].sampled == 0,
        "account not sampled");
    EXPECT_TRUE(result.accounts[0].charged == 0,
        "account not charged");
    EXPECT_TRUE(result.accounts[0].persisted == 0,
        "account not persisted");
    EXPECT_TRUE(result.accounts[0].time_accounting_allowed == 0,
        "account time accounting denied");
    EXPECT_TRUE(result.accounts[0].time_read_allowed == 0,
        "account time read denied");
    EXPECT_TRUE(result.accounts[0].cpu_usage_write_allowed == 0,
        "account cpu usage write denied");
    EXPECT_TRUE(result.accounts[0].quota_update_allowed == 0,
        "account quota update denied");
    EXPECT_TRUE(result.accounts[0].scheduler_credit_update_allowed == 0,
        "account scheduler credit denied");
    EXPECT_TRUE(result.accounts[0].context_switch_allowed == 0,
        "account context switch denied");
    EXPECT_TRUE(result.accounts[0].run_queue_mutation_allowed == 0,
        "account run queue mutation denied");
    EXPECT_TRUE(result.accounts[0].preemption_allowed == 0,
        "account preemption denied");
    EXPECT_TRUE(result.accounts[0].process_wake_allowed == 0,
        "account process wake denied");
    EXPECT_TRUE(result.accounts[0].no_effect == 1,
        "account no-effect");
    EXPECT_TRUE(strcmp(result.accounts[1].accounting_class,
            "entropy-time-accounting") == 0,
        "entropy accounting class");
    EXPECT_TRUE(strcmp(result.accounts[2].accounting_class,
            "console-time-accounting") == 0,
        "console accounting class");
    EXPECT_TRUE(strcmp(result.accounts[3].accounting_class,
            "idle-time-accounting") == 0,
        "idle accounting class");
    return 0;
}

static int time_accounting_caps_account_count(void) {
    latticra_kernel_time_accounting_request_t request;
    latticra_kernel_time_accounting_result_t result;

    EXPECT_TRUE(latticra_kernel_time_accounting_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_account_count = 99u;
    request.context_switch_request.requested_switch_count = 99u;
    EXPECT_TRUE(latticra_kernel_time_accounting_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "time accounting evaluates cap");
    EXPECT_TRUE(result.account_count == LATTICRA_KERNEL_TIME_ACCOUNTING_MAX,
        "account count capped");
    EXPECT_TRUE(strcmp(result.accounts[4].accounting_class,
            "reserved-time-accounting") == 0,
        "reserved accounting class");
    EXPECT_TRUE(result.accounts[4].account_token == 7004ul,
        "reserved account token");
    EXPECT_TRUE(result.accounts[4].switch_token == 6004ul,
        "reserved switch token");
    return 0;
}

static int time_accounting_report_is_deterministic(void) {
    latticra_kernel_time_accounting_request_t request;
    latticra_kernel_time_accounting_result_t result;
    char report[LATTICRA_KERNEL_TIME_ACCOUNTING_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_time_accounting_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_time_accounting_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "time accounting evaluates for report");
    EXPECT_TRUE(latticra_kernel_time_accounting_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL TIME ACCOUNTING REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "accounting_status=time-accounting-seed-ready\n") != 0,
        "accounting status emitted");
    EXPECT_TRUE(strstr(report, "context_switch_status=context-switch-seed-ready\n") != 0,
        "context switch emitted");
    EXPECT_TRUE(strstr(report, "run_queue_status=run-queue-seed-ready\n") != 0,
        "run queue emitted");
    EXPECT_TRUE(strstr(report, "account_count=4\n") != 0,
        "account count emitted");
    EXPECT_TRUE(strstr(report, "time_accounting_allowed=0\n") != 0,
        "time accounting flag emitted");
    EXPECT_TRUE(strstr(report, "time_read_allowed=0\n") != 0,
        "time read flag emitted");
    EXPECT_TRUE(strstr(report, "cpu_usage_write_allowed=0\n") != 0,
        "cpu usage write flag emitted");
    EXPECT_TRUE(strstr(report, "quota_update_allowed=0\n") != 0,
        "quota update flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_credit_update_allowed=0\n") != 0,
        "scheduler credit flag emitted");
    EXPECT_TRUE(strstr(report, "account[0].process_label=kernel-report-process-metadata\n") != 0,
        "account zero process emitted");
    EXPECT_TRUE(strstr(report, "account[0].accounting_class=kernel-report-time-accounting\n") != 0,
        "account zero class emitted");
    EXPECT_TRUE(strstr(report, "account[0].sampled=0\n") != 0,
        "sampled emitted");
    EXPECT_TRUE(strstr(report, "account[0].charged=0\n") != 0,
        "charged emitted");
    EXPECT_TRUE(strstr(report, "account[0].persisted=0\n") != 0,
        "persisted emitted");
    EXPECT_TRUE(strstr(report, "account[0].no_effect=1\n") != 0,
        "account no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_time_accounting_result_t result;
    char report[LATTICRA_KERNEL_TIME_ACCOUNTING_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_time_accounting_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_time_accounting_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_time_accounting_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_time_accounting_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_time_accounting_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_time_accounting_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (time_accounting_seed_is_metadata_only() != 0) return 1;
    if (time_accounting_caps_account_count() != 0) return 1;
    if (time_accounting_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_time_accounting: ok");
    return 0;
}
