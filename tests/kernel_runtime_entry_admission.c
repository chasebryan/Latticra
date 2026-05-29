#include "latticra/kernel_runtime_entry_admission.h"

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
    latticra_kernel_runtime_entry_admission_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_admission_count == 4u,
        "default admission count");
    EXPECT_TRUE(request.scheduler_run_entry_request.requested_run_entry_count == 4u,
        "scheduler run-entry seed request preserved");
    EXPECT_TRUE(request.scheduler_run_entry_request.scheduler_activation_request.
            requested_activation_count == 4u,
        "scheduler activation seed request preserved");
    return 0;
}

static int runtime_entry_admission_seed_is_metadata_only(void) {
    latticra_kernel_runtime_entry_admission_request_t request;
    latticra_kernel_runtime_entry_admission_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry admission evaluates");
    EXPECT_TRUE(strcmp(result.admission_status,
            "runtime-entry-admission-seed-ready") == 0,
        "runtime entry admission ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_run_entry.run_entry_status,
            "scheduler-run-entry-seed-ready") == 0,
        "scheduler run-entry ready");
    EXPECT_TRUE(strcmp(result.scheduler_run_entry.scheduler_activation.
            activation_status, "scheduler-activation-seed-ready") == 0,
        "scheduler activation ready");
    EXPECT_TRUE(result.admission_count == 4u,
        "admission count four");
    EXPECT_TRUE(result.no_effect == 1,
        "runtime entry admission no-effect");
    EXPECT_TRUE(result.runtime_entry_admission_allowed == 0,
        "runtime entry admission denied");
    EXPECT_TRUE(result.runtime_entry_allowed == 0,
        "runtime entry denied");
    EXPECT_TRUE(result.scheduler_run_entry_allowed == 0,
        "scheduler run-entry denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.admissions[0].process_label,
            "kernel-report-process-metadata") == 0,
        "admission zero process");
    EXPECT_TRUE(strcmp(result.admissions[0].admission_class,
            "kernel-report-runtime-entry-admission") == 0,
        "admission zero class");
    EXPECT_TRUE(result.admissions[0].admission_token == 0ul,
        "admission zero token");
    EXPECT_TRUE(result.admissions[0].run_entry_token == 0ul,
        "admission zero run-entry token");
    EXPECT_TRUE(result.admissions[0].activation_token == 0ul,
        "admission zero activation token");
    EXPECT_TRUE(result.admissions[0].pid_token == 1ul,
        "admission zero pid");
    EXPECT_TRUE(result.admissions[0].run_entry_rank == 1ul,
        "admission zero run-entry rank");
    EXPECT_TRUE(result.admissions[0].admission_rank == 1ul,
        "admission zero rank");
    EXPECT_TRUE(result.admissions[0].remaining_budget_ns == 10000000ul,
        "admission zero remaining budget");
    EXPECT_TRUE(result.admissions[0].admission_declared == 1,
        "admission zero declared");
    EXPECT_TRUE(strcmp(result.admissions[0].authority_status,
            "runtime-entry-admission-authority-denied") == 0,
        "admission authority denied");
    EXPECT_TRUE(result.admissions[0].admission_planned == 0,
        "admission not planned");
    EXPECT_TRUE(result.admissions[0].admitted == 0,
        "runtime not admitted");
    EXPECT_TRUE(result.admissions[0].runtime_entry_planned == 0,
        "runtime entry not planned");
    EXPECT_TRUE(result.admissions[0].runtime_entry_entered == 0,
        "runtime entry not entered");
    EXPECT_TRUE(result.admissions[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.admissions[0].context_switch_planned == 0,
        "context switch not planned");
    EXPECT_TRUE(result.admissions[0].runtime_entry_admission_allowed == 0,
        "entry admission denied");
    EXPECT_TRUE(result.admissions[0].runtime_entry_allowed == 0,
        "entry runtime entry denied");
    EXPECT_TRUE(result.admissions[0].scheduler_run_entry_allowed == 0,
        "entry scheduler run-entry denied");
    EXPECT_TRUE(result.admissions[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.admissions[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.admissions[0].context_switch_allowed == 0,
        "entry context switch denied");
    EXPECT_TRUE(result.admissions[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.admissions[1].admission_class,
            "entropy-runtime-entry-admission") == 0,
        "entropy admission class");
    EXPECT_TRUE(strcmp(result.admissions[2].admission_class,
            "console-runtime-entry-admission") == 0,
        "console admission class");
    EXPECT_TRUE(strcmp(result.admissions[3].admission_class,
            "idle-runtime-entry-admission") == 0,
        "idle admission class");
    return 0;
}

static int runtime_entry_admission_caps_count(void) {
    latticra_kernel_runtime_entry_admission_request_t request;
    latticra_kernel_runtime_entry_admission_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_admission_count = 99u;
    request.scheduler_run_entry_request.requested_run_entry_count = 99u;
    request.scheduler_run_entry_request.scheduler_activation_request.
        requested_activation_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry admission evaluates cap");
    EXPECT_TRUE(result.admission_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_MAX,
        "admission count capped");
    EXPECT_TRUE(strcmp(result.admissions[4].admission_class,
            "reserved-runtime-entry-admission") == 0,
        "reserved admission class");
    EXPECT_TRUE(result.admissions[4].admission_token == 15004ul,
        "reserved admission token");
    EXPECT_TRUE(result.admissions[4].run_entry_token == 14004ul,
        "reserved run-entry token");
    EXPECT_TRUE(result.admissions[4].activation_token == 13004ul,
        "reserved activation token");
    return 0;
}

static int runtime_entry_admission_report_is_deterministic(void) {
    latticra_kernel_runtime_entry_admission_request_t request;
    latticra_kernel_runtime_entry_admission_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry admission evaluates for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY ADMISSION REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "admission_status=runtime-entry-admission-seed-ready\n") != 0,
        "admission status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_run_entry_status=scheduler-run-entry-seed-ready\n") != 0,
        "scheduler run-entry status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_activation_status=scheduler-activation-seed-ready\n") != 0,
        "scheduler activation status emitted");
    EXPECT_TRUE(strstr(report, "admission_count=4\n") != 0,
        "admission count emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_admission_allowed=0\n") != 0,
        "admission flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_run_entry_allowed=0\n") != 0,
        "scheduler run-entry flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report,
            "admission[0].process_label=kernel-report-process-metadata\n") != 0,
        "admission zero process emitted");
    EXPECT_TRUE(strstr(report,
            "admission[0].admission_class=kernel-report-runtime-entry-admission\n") != 0,
        "admission zero class emitted");
    EXPECT_TRUE(strstr(report, "admission[0].admission_rank=1\n") != 0,
        "admission zero rank emitted");
    EXPECT_TRUE(strstr(report, "admission[0].admission_declared=1\n") != 0,
        "admission zero declared emitted");
    EXPECT_TRUE(strstr(report, "admission[0].admission_planned=0\n") != 0,
        "admission planned emitted");
    EXPECT_TRUE(strstr(report, "admission[0].admitted=0\n") != 0,
        "admitted emitted");
    EXPECT_TRUE(strstr(report, "admission[0].runtime_entry_entered=0\n") != 0,
        "runtime entry entered emitted");
    EXPECT_TRUE(strstr(report, "admission[0].execution_entered=0\n") != 0,
        "execution entered emitted");
    EXPECT_TRUE(strstr(report, "admission[0].no_effect=1\n") != 0,
        "admission no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_admission_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_admission_report(&result, report,
            0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (runtime_entry_admission_seed_is_metadata_only() != 0) return 1;
    if (runtime_entry_admission_caps_count() != 0) return 1;
    if (runtime_entry_admission_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_admission: ok");
    return 0;
}
