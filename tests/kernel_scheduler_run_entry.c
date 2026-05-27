#include "latticra/kernel_scheduler_run_entry.h"

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
    latticra_kernel_scheduler_run_entry_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_run_entry_count == 4u,
        "default run entry count");
    EXPECT_TRUE(request.scheduler_activation_request.requested_activation_count == 4u,
        "scheduler activation seed request preserved");
    EXPECT_TRUE(request.scheduler_activation_request.scheduler_handoff_request.
            requested_handoff_count == 4u,
        "scheduler handoff seed request preserved");
    return 0;
}

static int scheduler_run_entry_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_run_entry_request_t request;
    latticra_kernel_scheduler_run_entry_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler run entry evaluates");
    EXPECT_TRUE(strcmp(result.run_entry_status,
            "scheduler-run-entry-seed-ready") == 0,
        "scheduler run entry ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_activation.activation_status,
            "scheduler-activation-seed-ready") == 0,
        "scheduler activation ready");
    EXPECT_TRUE(strcmp(result.scheduler_activation.scheduler_handoff.handoff_status,
            "scheduler-handoff-seed-ready") == 0,
        "scheduler handoff ready");
    EXPECT_TRUE(result.run_entry_count == 4u,
        "run entry count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler run entry no-effect");
    EXPECT_TRUE(result.scheduler_run_entry_allowed == 0,
        "scheduler run entry denied");
    EXPECT_TRUE(result.scheduler_activation_allowed == 0,
        "scheduler activation denied");
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
    EXPECT_TRUE(result.runtime_entry_allowed == 0,
        "runtime entry denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.run_entries[0].process_label,
            "kernel-report-process-metadata") == 0,
        "run entry zero process");
    EXPECT_TRUE(strcmp(result.run_entries[0].run_entry_class,
            "kernel-report-scheduler-run-entry") == 0,
        "run entry zero class");
    EXPECT_TRUE(result.run_entries[0].run_entry_token == 0ul,
        "run entry zero token");
    EXPECT_TRUE(result.run_entries[0].activation_token == 0ul,
        "run entry zero activation token");
    EXPECT_TRUE(result.run_entries[0].handoff_token == 0ul,
        "run entry zero handoff token");
    EXPECT_TRUE(result.run_entries[0].dispatch_token == 0ul,
        "run entry zero dispatch token");
    EXPECT_TRUE(result.run_entries[0].selection_token == 0ul,
        "run entry zero selection token");
    EXPECT_TRUE(result.run_entries[0].pid_token == 1ul,
        "run entry zero pid");
    EXPECT_TRUE(result.run_entries[0].activation_rank == 1ul,
        "run entry zero activation rank");
    EXPECT_TRUE(result.run_entries[0].run_entry_rank == 1ul,
        "run entry zero rank");
    EXPECT_TRUE(result.run_entries[0].scheduler_credit_ns == 10000000ul,
        "run entry zero scheduler credit");
    EXPECT_TRUE(result.run_entries[0].remaining_budget_ns == 10000000ul,
        "run entry zero remaining");
    EXPECT_TRUE(result.run_entries[0].run_entry_declared == 1,
        "run entry zero declared");
    EXPECT_TRUE(strcmp(result.run_entries[0].authority_status,
            "scheduler-run-entry-authority-denied") == 0,
        "run entry authority denied");
    EXPECT_TRUE(result.run_entries[0].declared == 1,
        "run entry declared");
    EXPECT_TRUE(result.run_entries[0].activation_planned == 0,
        "activation not planned");
    EXPECT_TRUE(result.run_entries[0].run_entry_planned == 0,
        "run entry not planned");
    EXPECT_TRUE(result.run_entries[0].run_entry_prepared == 0,
        "run entry not prepared");
    EXPECT_TRUE(result.run_entries[0].activated == 0,
        "activation not performed");
    EXPECT_TRUE(result.run_entries[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.run_entries[0].context_switch_planned == 0,
        "run entry no context switch planned");
    EXPECT_TRUE(result.run_entries[0].scheduler_run_entry_allowed == 0,
        "entry scheduler run entry denied");
    EXPECT_TRUE(result.run_entries[0].scheduler_activation_allowed == 0,
        "entry scheduler activation denied");
    EXPECT_TRUE(result.run_entries[0].scheduler_handoff_allowed == 0,
        "entry scheduler handoff denied");
    EXPECT_TRUE(result.run_entries[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.run_entries[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.run_entries[0].context_switch_allowed == 0,
        "entry context switch denied");
    EXPECT_TRUE(result.run_entries[0].runtime_entry_allowed == 0,
        "entry runtime entry denied");
    EXPECT_TRUE(result.run_entries[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.run_entries[1].run_entry_class,
            "entropy-scheduler-run-entry") == 0,
        "entropy run entry class");
    EXPECT_TRUE(strcmp(result.run_entries[2].run_entry_class,
            "console-scheduler-run-entry") == 0,
        "console run entry class");
    EXPECT_TRUE(strcmp(result.run_entries[3].run_entry_class,
            "idle-scheduler-run-entry") == 0,
        "idle run entry class");
    return 0;
}

static int scheduler_run_entry_caps_count(void) {
    latticra_kernel_scheduler_run_entry_request_t request;
    latticra_kernel_scheduler_run_entry_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_run_entry_count = 99u;
    request.scheduler_activation_request.requested_activation_count = 99u;
    request.scheduler_activation_request.scheduler_handoff_request.
        requested_handoff_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler run entry evaluates cap");
    EXPECT_TRUE(result.run_entry_count == LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_MAX,
        "run entry count capped");
    EXPECT_TRUE(strcmp(result.run_entries[4].run_entry_class,
            "reserved-scheduler-run-entry") == 0,
        "reserved run entry class");
    EXPECT_TRUE(result.run_entries[4].run_entry_token == 14004ul,
        "reserved run entry token");
    EXPECT_TRUE(result.run_entries[4].activation_token == 13004ul,
        "reserved activation token");
    EXPECT_TRUE(result.run_entries[4].handoff_token == 12004ul,
        "reserved handoff token");
    return 0;
}

static int scheduler_run_entry_report_is_deterministic(void) {
    latticra_kernel_scheduler_run_entry_request_t request;
    latticra_kernel_scheduler_run_entry_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler run entry evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER RUN ENTRY REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "run_entry_status=scheduler-run-entry-seed-ready\n") != 0,
        "run entry status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_activation_status=scheduler-activation-seed-ready\n") != 0,
        "scheduler activation status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_handoff_status=scheduler-handoff-seed-ready\n") != 0,
        "scheduler handoff status emitted");
    EXPECT_TRUE(strstr(report, "run_entry_count=4\n") != 0,
        "run entry count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_run_entry_allowed=0\n") != 0,
        "scheduler run entry flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_activation_allowed=0\n") != 0,
        "scheduler activation flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_handoff_allowed=0\n") != 0,
        "scheduler handoff flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report,
            "run_entry[0].process_label=kernel-report-process-metadata\n") != 0,
        "run entry zero process emitted");
    EXPECT_TRUE(strstr(report,
            "run_entry[0].run_entry_class=kernel-report-scheduler-run-entry\n") != 0,
        "run entry zero class emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].run_entry_rank=1\n") != 0,
        "run entry zero rank emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].run_entry_declared=1\n") != 0,
        "run entry zero declared emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].run_entry_planned=0\n") != 0,
        "run entry planned emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].run_entry_prepared=0\n") != 0,
        "run entry prepared emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].execution_entered=0\n") != 0,
        "execution entered emitted");
    EXPECT_TRUE(strstr(report, "run_entry[0].no_effect=1\n") != 0,
        "run entry no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_run_entry_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_run_entry_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_run_entry_seed_is_metadata_only() != 0) return 1;
    if (scheduler_run_entry_caps_count() != 0) return 1;
    if (scheduler_run_entry_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_run_entry: ok");
    return 0;
}
