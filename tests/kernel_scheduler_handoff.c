#include "latticra/kernel_scheduler_handoff.h"

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
    latticra_kernel_scheduler_handoff_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_handoff_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_handoff_count == 4u,
        "default handoff count");
    EXPECT_TRUE(request.scheduler_dispatch_request.requested_dispatch_count == 4u,
        "scheduler dispatch seed request preserved");
    EXPECT_TRUE(request.scheduler_dispatch_request.scheduler_selection_request.requested_selection_count == 4u,
        "scheduler selection seed request preserved");
    EXPECT_TRUE(request.scheduler_dispatch_request.scheduler_selection_request.scheduler_credit_request.requested_credit_count == 4u,
        "scheduler credit seed request preserved");
    return 0;
}

static int scheduler_handoff_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_handoff_request_t request;
    latticra_kernel_scheduler_handoff_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_handoff_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler handoff evaluates");
    EXPECT_TRUE(strcmp(result.handoff_status,
            "scheduler-handoff-seed-ready") == 0,
        "scheduler handoff ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_dispatch.dispatch_status,
            "scheduler-dispatch-seed-ready") == 0,
        "scheduler dispatch ready");
    EXPECT_TRUE(strcmp(result.scheduler_dispatch.scheduler_selection.selection_status,
            "scheduler-selection-seed-ready") == 0,
        "scheduler selection ready");
    EXPECT_TRUE(result.handoff_count == 4u,
        "handoff count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler handoff no-effect");
    EXPECT_TRUE(result.scheduler_handoff_allowed == 0,
        "scheduler handoff denied");
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

    EXPECT_TRUE(strcmp(result.handoffs[0].process_label,
            "kernel-report-process-metadata") == 0,
        "handoff zero process");
    EXPECT_TRUE(strcmp(result.handoffs[0].handoff_class,
            "kernel-report-scheduler-handoff") == 0,
        "handoff zero class");
    EXPECT_TRUE(result.handoffs[0].handoff_token == 0ul,
        "handoff zero token");
    EXPECT_TRUE(result.handoffs[0].dispatch_token == 0ul,
        "handoff zero dispatch token");
    EXPECT_TRUE(result.handoffs[0].selection_token == 0ul,
        "handoff zero selection token");
    EXPECT_TRUE(result.handoffs[0].pid_token == 1ul,
        "handoff zero pid");
    EXPECT_TRUE(result.handoffs[0].credit_token == 0ul,
        "handoff zero credit token");
    EXPECT_TRUE(result.handoffs[0].decision_token == 0ul,
        "handoff zero decision token");
    EXPECT_TRUE(result.handoffs[0].switch_token == 0ul,
        "handoff zero switch token");
    EXPECT_TRUE(result.handoffs[0].tick_token == 1ul,
        "handoff zero tick token");
    EXPECT_TRUE(result.handoffs[0].candidate_rank == 1ul,
        "handoff zero candidate rank");
    EXPECT_TRUE(result.handoffs[0].dispatch_rank == 1ul,
        "handoff zero dispatch rank");
    EXPECT_TRUE(result.handoffs[0].handoff_rank == 1ul,
        "handoff zero rank");
    EXPECT_TRUE(result.handoffs[0].scheduler_credit_ns == 10000000ul,
        "handoff zero scheduler credit");
    EXPECT_TRUE(result.handoffs[0].quota_credit_ns == 10000000ul,
        "handoff zero quota credit");
    EXPECT_TRUE(result.handoffs[0].remaining_budget_ns == 10000000ul,
        "handoff zero remaining");
    EXPECT_TRUE(result.handoffs[0].candidate_declared == 1,
        "handoff zero candidate declared");
    EXPECT_TRUE(result.handoffs[0].dispatch_declared == 1,
        "handoff zero dispatch declared");
    EXPECT_TRUE(result.handoffs[0].handoff_declared == 1,
        "handoff zero declared");
    EXPECT_TRUE(strcmp(result.handoffs[0].authority_status,
            "scheduler-handoff-authority-denied") == 0,
        "handoff authority denied");
    EXPECT_TRUE(result.handoffs[0].declared == 1,
        "handoff declared");
    EXPECT_TRUE(result.handoffs[0].handoff_planned == 0,
        "handoff not planned");
    EXPECT_TRUE(result.handoffs[0].dispatch_planned == 0,
        "dispatch not planned");
    EXPECT_TRUE(result.handoffs[0].selected == 0,
        "handoff not selected");
    EXPECT_TRUE(result.handoffs[0].enqueued == 0,
        "handoff not enqueued");
    EXPECT_TRUE(result.handoffs[0].dequeued == 0,
        "handoff not dequeued");
    EXPECT_TRUE(result.handoffs[0].dispatched == 0,
        "handoff not dispatched");
    EXPECT_TRUE(result.handoffs[0].context_switch_planned == 0,
        "handoff no context switch planned");
    EXPECT_TRUE(result.handoffs[0].scheduler_handoff_allowed == 0,
        "entry scheduler handoff denied");
    EXPECT_TRUE(result.handoffs[0].scheduler_dispatch_allowed == 0,
        "entry scheduler dispatch denied");
    EXPECT_TRUE(result.handoffs[0].scheduler_selection_allowed == 0,
        "entry scheduler selection denied");
    EXPECT_TRUE(result.handoffs[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.handoffs[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.handoffs[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.handoffs[1].handoff_class,
            "entropy-scheduler-handoff") == 0,
        "entropy handoff class");
    EXPECT_TRUE(strcmp(result.handoffs[2].handoff_class,
            "console-scheduler-handoff") == 0,
        "console handoff class");
    EXPECT_TRUE(strcmp(result.handoffs[3].handoff_class,
            "idle-scheduler-handoff") == 0,
        "idle handoff class");
    return 0;
}

static int scheduler_handoff_caps_handoff_count(void) {
    latticra_kernel_scheduler_handoff_request_t request;
    latticra_kernel_scheduler_handoff_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_handoff_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_handoff_count = 99u;
    request.scheduler_dispatch_request.requested_dispatch_count = 99u;
    request.scheduler_dispatch_request.scheduler_selection_request.requested_selection_count = 99u;
    request.scheduler_dispatch_request.scheduler_selection_request.scheduler_credit_request.requested_credit_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler handoff evaluates cap");
    EXPECT_TRUE(result.handoff_count == LATTICRA_KERNEL_SCHEDULER_HANDOFF_MAX,
        "handoff count capped");
    EXPECT_TRUE(strcmp(result.handoffs[4].handoff_class,
            "reserved-scheduler-handoff") == 0,
        "reserved handoff class");
    EXPECT_TRUE(result.handoffs[4].handoff_token == 12004ul,
        "reserved handoff token");
    EXPECT_TRUE(result.handoffs[4].dispatch_token == 11004ul,
        "reserved dispatch token");
    EXPECT_TRUE(result.handoffs[4].selection_token == 10004ul,
        "reserved selection token");
    EXPECT_TRUE(result.handoffs[4].credit_token == 9004ul,
        "reserved credit token");
    EXPECT_TRUE(result.handoffs[4].decision_token == 8004ul,
        "reserved decision token");
    return 0;
}

static int scheduler_handoff_report_is_deterministic(void) {
    latticra_kernel_scheduler_handoff_request_t request;
    latticra_kernel_scheduler_handoff_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_HANDOFF_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_handoff_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler handoff evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER HANDOFF REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "handoff_status=scheduler-handoff-seed-ready\n") != 0,
        "handoff status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_dispatch_status=scheduler-dispatch-seed-ready\n") != 0,
        "scheduler dispatch status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_selection_status=scheduler-selection-seed-ready\n") != 0,
        "scheduler selection status emitted");
    EXPECT_TRUE(strstr(report, "handoff_count=4\n") != 0,
        "handoff count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_handoff_allowed=0\n") != 0,
        "scheduler handoff flag emitted");
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
    EXPECT_TRUE(strstr(report, "handoff[0].process_label=kernel-report-process-metadata\n") != 0,
        "handoff zero process emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].handoff_class=kernel-report-scheduler-handoff\n") != 0,
        "handoff zero class emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].handoff_rank=1\n") != 0,
        "handoff zero rank emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].scheduler_credit_ns=10000000\n") != 0,
        "handoff zero scheduler credit emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].handoff_declared=1\n") != 0,
        "handoff zero declared emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].handoff_planned=0\n") != 0,
        "handoff planned emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].dispatch_planned=0\n") != 0,
        "dispatch planned emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].dequeued=0\n") != 0,
        "dequeued emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].dispatched=0\n") != 0,
        "dispatched emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].context_switch_planned=0\n") != 0,
        "context switch planned emitted");
    EXPECT_TRUE(strstr(report, "handoff[0].no_effect=1\n") != 0,
        "handoff no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_handoff_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_HANDOFF_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_handoff_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_handoff_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_handoff_seed_is_metadata_only() != 0) return 1;
    if (scheduler_handoff_caps_handoff_count() != 0) return 1;
    if (scheduler_handoff_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_handoff: ok");
    return 0;
}
