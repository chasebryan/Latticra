#include "latticra/kernel_scheduler_dispatch.h"

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
    latticra_kernel_scheduler_dispatch_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_dispatch_count == 4u,
        "default dispatch count");
    EXPECT_TRUE(request.scheduler_selection_request.requested_selection_count == 4u,
        "scheduler selection seed request preserved");
    EXPECT_TRUE(request.scheduler_selection_request.scheduler_credit_request.requested_credit_count == 4u,
        "scheduler credit seed request preserved");
    EXPECT_TRUE(request.scheduler_selection_request.scheduler_credit_request.preemption_request.requested_decision_count == 4u,
        "preemption seed request preserved");
    return 0;
}

static int scheduler_dispatch_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_dispatch_request_t request;
    latticra_kernel_scheduler_dispatch_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler dispatch evaluates");
    EXPECT_TRUE(strcmp(result.dispatch_status,
            "scheduler-dispatch-seed-ready") == 0,
        "scheduler dispatch ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_selection.selection_status,
            "scheduler-selection-seed-ready") == 0,
        "scheduler selection ready");
    EXPECT_TRUE(strcmp(result.scheduler_selection.scheduler_credit.credit_status,
            "scheduler-credit-seed-ready") == 0,
        "scheduler credit ready");
    EXPECT_TRUE(result.dispatch_count == 4u,
        "dispatch count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler dispatch no-effect");
    EXPECT_TRUE(result.scheduler_dispatch_allowed == 0,
        "scheduler dispatch denied");
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

    EXPECT_TRUE(strcmp(result.dispatches[0].process_label,
            "kernel-report-process-metadata") == 0,
        "dispatch zero process");
    EXPECT_TRUE(strcmp(result.dispatches[0].dispatch_class,
            "kernel-report-scheduler-dispatch") == 0,
        "dispatch zero class");
    EXPECT_TRUE(result.dispatches[0].dispatch_token == 0ul,
        "dispatch zero token");
    EXPECT_TRUE(result.dispatches[0].selection_token == 0ul,
        "dispatch zero selection token");
    EXPECT_TRUE(result.dispatches[0].pid_token == 1ul,
        "dispatch zero pid");
    EXPECT_TRUE(result.dispatches[0].credit_token == 0ul,
        "dispatch zero credit token");
    EXPECT_TRUE(result.dispatches[0].decision_token == 0ul,
        "dispatch zero decision token");
    EXPECT_TRUE(result.dispatches[0].switch_token == 0ul,
        "dispatch zero switch token");
    EXPECT_TRUE(result.dispatches[0].tick_token == 1ul,
        "dispatch zero tick token");
    EXPECT_TRUE(result.dispatches[0].candidate_rank == 1ul,
        "dispatch zero candidate rank");
    EXPECT_TRUE(result.dispatches[0].dispatch_rank == 1ul,
        "dispatch zero rank");
    EXPECT_TRUE(result.dispatches[0].scheduler_credit_ns == 10000000ul,
        "dispatch zero scheduler credit");
    EXPECT_TRUE(result.dispatches[0].quota_credit_ns == 10000000ul,
        "dispatch zero quota credit");
    EXPECT_TRUE(result.dispatches[0].remaining_budget_ns == 10000000ul,
        "dispatch zero remaining");
    EXPECT_TRUE(result.dispatches[0].candidate_declared == 1,
        "dispatch zero candidate declared");
    EXPECT_TRUE(result.dispatches[0].dispatch_declared == 1,
        "dispatch zero declared");
    EXPECT_TRUE(strcmp(result.dispatches[0].authority_status,
            "scheduler-dispatch-authority-denied") == 0,
        "dispatch authority denied");
    EXPECT_TRUE(result.dispatches[0].declared == 1,
        "dispatch declared");
    EXPECT_TRUE(result.dispatches[0].dispatch_planned == 0,
        "dispatch not planned");
    EXPECT_TRUE(result.dispatches[0].selected == 0,
        "dispatch not selected");
    EXPECT_TRUE(result.dispatches[0].enqueued == 0,
        "dispatch not enqueued");
    EXPECT_TRUE(result.dispatches[0].dequeued == 0,
        "dispatch not dequeued");
    EXPECT_TRUE(result.dispatches[0].dispatched == 0,
        "dispatch not dispatched");
    EXPECT_TRUE(result.dispatches[0].context_switch_planned == 0,
        "dispatch no context switch planned");
    EXPECT_TRUE(result.dispatches[0].scheduler_dispatch_allowed == 0,
        "entry scheduler dispatch denied");
    EXPECT_TRUE(result.dispatches[0].scheduler_selection_allowed == 0,
        "entry scheduler selection denied");
    EXPECT_TRUE(result.dispatches[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.dispatches[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.dispatches[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.dispatches[1].dispatch_class,
            "entropy-scheduler-dispatch") == 0,
        "entropy dispatch class");
    EXPECT_TRUE(strcmp(result.dispatches[2].dispatch_class,
            "console-scheduler-dispatch") == 0,
        "console dispatch class");
    EXPECT_TRUE(strcmp(result.dispatches[3].dispatch_class,
            "idle-scheduler-dispatch") == 0,
        "idle dispatch class");
    return 0;
}

static int scheduler_dispatch_caps_dispatch_count(void) {
    latticra_kernel_scheduler_dispatch_request_t request;
    latticra_kernel_scheduler_dispatch_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_dispatch_count = 99u;
    request.scheduler_selection_request.requested_selection_count = 99u;
    request.scheduler_selection_request.scheduler_credit_request.requested_credit_count = 99u;
    request.scheduler_selection_request.scheduler_credit_request.preemption_request.requested_decision_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler dispatch evaluates cap");
    EXPECT_TRUE(result.dispatch_count == LATTICRA_KERNEL_SCHEDULER_DISPATCH_MAX,
        "dispatch count capped");
    EXPECT_TRUE(strcmp(result.dispatches[4].dispatch_class,
            "reserved-scheduler-dispatch") == 0,
        "reserved dispatch class");
    EXPECT_TRUE(result.dispatches[4].dispatch_token == 11004ul,
        "reserved dispatch token");
    EXPECT_TRUE(result.dispatches[4].selection_token == 10004ul,
        "reserved selection token");
    EXPECT_TRUE(result.dispatches[4].credit_token == 9004ul,
        "reserved credit token");
    EXPECT_TRUE(result.dispatches[4].decision_token == 8004ul,
        "reserved decision token");
    EXPECT_TRUE(result.dispatches[4].switch_token == 6004ul,
        "reserved switch token");
    return 0;
}

static int scheduler_dispatch_report_is_deterministic(void) {
    latticra_kernel_scheduler_dispatch_request_t request;
    latticra_kernel_scheduler_dispatch_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_DISPATCH_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler dispatch evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER DISPATCH REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "dispatch_status=scheduler-dispatch-seed-ready\n") != 0,
        "dispatch status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_selection_status=scheduler-selection-seed-ready\n") != 0,
        "scheduler selection status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_credit_status=scheduler-credit-seed-ready\n") != 0,
        "scheduler credit status emitted");
    EXPECT_TRUE(strstr(report, "dispatch_count=4\n") != 0,
        "dispatch count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_dispatch_allowed=0\n") != 0,
        "scheduler dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_selection_allowed=0\n") != 0,
        "scheduler selection flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].process_label=kernel-report-process-metadata\n") != 0,
        "dispatch zero process emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dispatch_class=kernel-report-scheduler-dispatch\n") != 0,
        "dispatch zero class emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dispatch_rank=1\n") != 0,
        "dispatch zero rank emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].scheduler_credit_ns=10000000\n") != 0,
        "dispatch zero scheduler credit emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dispatch_declared=1\n") != 0,
        "dispatch zero declared emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dispatch_planned=0\n") != 0,
        "dispatch planned emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dequeued=0\n") != 0,
        "dequeued emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].dispatched=0\n") != 0,
        "dispatched emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].context_switch_planned=0\n") != 0,
        "context switch planned emitted");
    EXPECT_TRUE(strstr(report, "dispatch[0].no_effect=1\n") != 0,
        "dispatch no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_dispatch_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_DISPATCH_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_dispatch_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_dispatch_seed_is_metadata_only() != 0) return 1;
    if (scheduler_dispatch_caps_dispatch_count() != 0) return 1;
    if (scheduler_dispatch_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_dispatch: ok");
    return 0;
}
