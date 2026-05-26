#include "latticra/kernel_scheduler_selection.h"

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
    latticra_kernel_scheduler_selection_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_selection_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_selection_count == 4u,
        "default selection count");
    EXPECT_TRUE(request.scheduler_credit_request.requested_credit_count == 4u,
        "scheduler credit seed request preserved");
    EXPECT_TRUE(request.scheduler_credit_request.preemption_request.requested_decision_count == 4u,
        "preemption seed request preserved");
    EXPECT_TRUE(request.scheduler_credit_request.preemption_request.time_accounting_request.requested_account_count == 4u,
        "time accounting seed request preserved");
    return 0;
}

static int scheduler_selection_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_selection_request_t request;
    latticra_kernel_scheduler_selection_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_selection_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler selection evaluates");
    EXPECT_TRUE(strcmp(result.selection_status,
            "scheduler-selection-seed-ready") == 0,
        "scheduler selection ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_credit.credit_status,
            "scheduler-credit-seed-ready") == 0,
        "scheduler credit ready");
    EXPECT_TRUE(strcmp(result.scheduler_credit.preemption.preemption_status,
            "preemption-seed-ready") == 0,
        "preemption ready");
    EXPECT_TRUE(result.selection_count == 4u,
        "selection count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler selection no-effect");
    EXPECT_TRUE(result.scheduler_selection_allowed == 0,
        "scheduler selection denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
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
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.selections[0].process_label,
            "kernel-report-process-metadata") == 0,
        "selection zero process");
    EXPECT_TRUE(strcmp(result.selections[0].selection_class,
            "kernel-report-scheduler-selection") == 0,
        "selection zero class");
    EXPECT_TRUE(result.selections[0].selection_token == 0ul,
        "selection zero token");
    EXPECT_TRUE(result.selections[0].pid_token == 1ul,
        "selection zero pid");
    EXPECT_TRUE(result.selections[0].credit_token == 0ul,
        "selection zero credit token");
    EXPECT_TRUE(result.selections[0].decision_token == 0ul,
        "selection zero decision token");
    EXPECT_TRUE(result.selections[0].switch_token == 0ul,
        "selection zero switch token");
    EXPECT_TRUE(result.selections[0].tick_token == 1ul,
        "selection zero tick token");
    EXPECT_TRUE(result.selections[0].candidate_rank == 1ul,
        "selection zero rank");
    EXPECT_TRUE(result.selections[0].scheduler_credit_ns == 10000000ul,
        "selection zero scheduler credit");
    EXPECT_TRUE(result.selections[0].quota_credit_ns == 10000000ul,
        "selection zero quota credit");
    EXPECT_TRUE(result.selections[0].remaining_budget_ns == 10000000ul,
        "selection zero remaining");
    EXPECT_TRUE(result.selections[0].candidate_declared == 1,
        "selection zero candidate declared");
    EXPECT_TRUE(strcmp(result.selections[0].authority_status,
            "scheduler-selection-authority-denied") == 0,
        "selection authority denied");
    EXPECT_TRUE(result.selections[0].declared == 1,
        "selection declared");
    EXPECT_TRUE(result.selections[0].compared == 0,
        "selection not compared");
    EXPECT_TRUE(result.selections[0].selected == 0,
        "selection not selected");
    EXPECT_TRUE(result.selections[0].enqueued == 0,
        "selection not enqueued");
    EXPECT_TRUE(result.selections[0].dispatched == 0,
        "selection not dispatched");
    EXPECT_TRUE(result.selections[0].scheduler_selection_allowed == 0,
        "entry scheduler selection denied");
    EXPECT_TRUE(result.selections[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.selections[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.selections[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.selections[1].selection_class,
            "entropy-scheduler-selection") == 0,
        "entropy selection class");
    EXPECT_TRUE(strcmp(result.selections[2].selection_class,
            "console-scheduler-selection") == 0,
        "console selection class");
    EXPECT_TRUE(strcmp(result.selections[3].selection_class,
            "idle-scheduler-selection") == 0,
        "idle selection class");
    return 0;
}

static int scheduler_selection_caps_selection_count(void) {
    latticra_kernel_scheduler_selection_request_t request;
    latticra_kernel_scheduler_selection_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_selection_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_selection_count = 99u;
    request.scheduler_credit_request.requested_credit_count = 99u;
    request.scheduler_credit_request.preemption_request.requested_decision_count = 99u;
    request.scheduler_credit_request.preemption_request.time_accounting_request.requested_account_count = 99u;
    request.scheduler_credit_request.preemption_request.time_accounting_request.context_switch_request.requested_switch_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_selection_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler selection evaluates cap");
    EXPECT_TRUE(result.selection_count == LATTICRA_KERNEL_SCHEDULER_SELECTION_MAX,
        "selection count capped");
    EXPECT_TRUE(strcmp(result.selections[4].selection_class,
            "reserved-scheduler-selection") == 0,
        "reserved selection class");
    EXPECT_TRUE(result.selections[4].selection_token == 10004ul,
        "reserved selection token");
    EXPECT_TRUE(result.selections[4].credit_token == 9004ul,
        "reserved credit token");
    EXPECT_TRUE(result.selections[4].decision_token == 8004ul,
        "reserved decision token");
    EXPECT_TRUE(result.selections[4].switch_token == 6004ul,
        "reserved switch token");
    return 0;
}

static int scheduler_selection_report_is_deterministic(void) {
    latticra_kernel_scheduler_selection_request_t request;
    latticra_kernel_scheduler_selection_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_SELECTION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_selection_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler selection evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER SELECTION REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "selection_status=scheduler-selection-seed-ready\n") != 0,
        "selection status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_credit_status=scheduler-credit-seed-ready\n") != 0,
        "scheduler credit status emitted");
    EXPECT_TRUE(strstr(report, "preemption_status=preemption-seed-ready\n") != 0,
        "preemption status emitted");
    EXPECT_TRUE(strstr(report, "selection_count=4\n") != 0,
        "selection count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_selection_allowed=0\n") != 0,
        "scheduler selection flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_credit_update_allowed=0\n") != 0,
        "scheduler credit update flag emitted");
    EXPECT_TRUE(strstr(report, "selection[0].process_label=kernel-report-process-metadata\n") != 0,
        "selection zero process emitted");
    EXPECT_TRUE(strstr(report, "selection[0].selection_class=kernel-report-scheduler-selection\n") != 0,
        "selection zero class emitted");
    EXPECT_TRUE(strstr(report, "selection[0].candidate_rank=1\n") != 0,
        "selection zero rank emitted");
    EXPECT_TRUE(strstr(report, "selection[0].scheduler_credit_ns=10000000\n") != 0,
        "selection zero scheduler credit emitted");
    EXPECT_TRUE(strstr(report, "selection[0].candidate_declared=1\n") != 0,
        "selection zero candidate emitted");
    EXPECT_TRUE(strstr(report, "selection[0].compared=0\n") != 0,
        "compared emitted");
    EXPECT_TRUE(strstr(report, "selection[0].selected=0\n") != 0,
        "selected emitted");
    EXPECT_TRUE(strstr(report, "selection[0].enqueued=0\n") != 0,
        "enqueued emitted");
    EXPECT_TRUE(strstr(report, "selection[0].dispatched=0\n") != 0,
        "dispatched emitted");
    EXPECT_TRUE(strstr(report, "selection[0].no_effect=1\n") != 0,
        "selection no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_selection_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_SELECTION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_selection_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_selection_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_selection_seed_is_metadata_only() != 0) return 1;
    if (scheduler_selection_caps_selection_count() != 0) return 1;
    if (scheduler_selection_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_selection: ok");
    return 0;
}
