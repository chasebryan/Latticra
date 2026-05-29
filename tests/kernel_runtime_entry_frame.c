#include "latticra/kernel_runtime_entry_frame.h"

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
    latticra_kernel_runtime_entry_frame_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_frame_count == 4u,
        "default frame count");
    EXPECT_TRUE(request.runtime_entry_admission_request.requested_admission_count == 4u,
        "runtime entry admission seed request preserved");
    EXPECT_TRUE(request.runtime_entry_admission_request.scheduler_run_entry_request.
            requested_run_entry_count == 4u,
        "scheduler run-entry seed request preserved");
    return 0;
}

static int runtime_entry_frame_seed_is_metadata_only(void) {
    latticra_kernel_runtime_entry_frame_request_t request;
    latticra_kernel_runtime_entry_frame_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry frame evaluates");
    EXPECT_TRUE(strcmp(result.frame_status,
            "runtime-entry-frame-seed-ready") == 0,
        "runtime entry frame ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.runtime_entry_admission.admission_status,
            "runtime-entry-admission-seed-ready") == 0,
        "runtime entry admission ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_admission.scheduler_run_entry.
            run_entry_status, "scheduler-run-entry-seed-ready") == 0,
        "scheduler run-entry ready");
    EXPECT_TRUE(result.frame_count == 4u,
        "frame count four");
    EXPECT_TRUE(result.no_effect == 1,
        "runtime entry frame no-effect");
    EXPECT_TRUE(result.runtime_entry_frame_allowed == 0,
        "runtime entry frame denied");
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
    EXPECT_TRUE(result.stack_switch_allowed == 0,
        "stack switch denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.frames[0].process_label,
            "kernel-report-process-metadata") == 0,
        "frame zero process");
    EXPECT_TRUE(strcmp(result.frames[0].frame_class,
            "kernel-report-runtime-entry-frame") == 0,
        "frame zero class");
    EXPECT_TRUE(result.frames[0].frame_token == 0ul,
        "frame zero token");
    EXPECT_TRUE(result.frames[0].admission_token == 0ul,
        "frame zero admission token");
    EXPECT_TRUE(result.frames[0].run_entry_token == 0ul,
        "frame zero run-entry token");
    EXPECT_TRUE(result.frames[0].activation_token == 0ul,
        "frame zero activation token");
    EXPECT_TRUE(result.frames[0].pid_token == 1ul,
        "frame zero pid");
    EXPECT_TRUE(result.frames[0].run_entry_rank == 1ul,
        "frame zero run-entry rank");
    EXPECT_TRUE(result.frames[0].admission_rank == 1ul,
        "frame zero admission rank");
    EXPECT_TRUE(result.frames[0].frame_rank == 1ul,
        "frame zero frame rank");
    EXPECT_TRUE(result.frames[0].remaining_budget_ns == 10000000ul,
        "frame zero remaining budget");
    EXPECT_TRUE(result.frames[0].admission_declared == 1,
        "frame zero admission declared");
    EXPECT_TRUE(result.frames[0].frame_declared == 1,
        "frame zero frame declared");
    EXPECT_TRUE(strcmp(result.frames[0].authority_status,
            "runtime-entry-frame-authority-denied") == 0,
        "frame authority denied");
    EXPECT_TRUE(result.frames[0].frame_planned == 0,
        "frame not planned");
    EXPECT_TRUE(result.frames[0].frame_built == 0,
        "frame not built");
    EXPECT_TRUE(result.frames[0].frame_installed == 0,
        "frame not installed");
    EXPECT_TRUE(result.frames[0].admitted == 0,
        "runtime not admitted");
    EXPECT_TRUE(result.frames[0].runtime_entry_planned == 0,
        "runtime entry not planned");
    EXPECT_TRUE(result.frames[0].runtime_entry_entered == 0,
        "runtime entry not entered");
    EXPECT_TRUE(result.frames[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.frames[0].context_switch_planned == 0,
        "context switch not planned");
    EXPECT_TRUE(result.frames[0].runtime_entry_frame_allowed == 0,
        "entry frame denied");
    EXPECT_TRUE(result.frames[0].runtime_entry_admission_allowed == 0,
        "entry admission denied");
    EXPECT_TRUE(result.frames[0].runtime_entry_allowed == 0,
        "entry runtime entry denied");
    EXPECT_TRUE(result.frames[0].scheduler_run_entry_allowed == 0,
        "entry scheduler run-entry denied");
    EXPECT_TRUE(result.frames[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.frames[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.frames[0].context_switch_allowed == 0,
        "entry context switch denied");
    EXPECT_TRUE(result.frames[0].stack_switch_allowed == 0,
        "entry stack switch denied");
    EXPECT_TRUE(result.frames[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.frames[1].frame_class,
            "entropy-runtime-entry-frame") == 0,
        "entropy frame class");
    EXPECT_TRUE(strcmp(result.frames[2].frame_class,
            "console-runtime-entry-frame") == 0,
        "console frame class");
    EXPECT_TRUE(strcmp(result.frames[3].frame_class,
            "idle-runtime-entry-frame") == 0,
        "idle frame class");
    return 0;
}

static int runtime_entry_frame_caps_count(void) {
    latticra_kernel_runtime_entry_frame_request_t request;
    latticra_kernel_runtime_entry_frame_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_frame_count = 99u;
    request.runtime_entry_admission_request.requested_admission_count = 99u;
    request.runtime_entry_admission_request.scheduler_run_entry_request.
        requested_run_entry_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry frame evaluates cap");
    EXPECT_TRUE(result.frame_count == LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_MAX,
        "frame count capped");
    EXPECT_TRUE(strcmp(result.frames[4].frame_class,
            "reserved-runtime-entry-frame") == 0,
        "reserved frame class");
    EXPECT_TRUE(result.frames[4].frame_token == 16004ul,
        "reserved frame token");
    EXPECT_TRUE(result.frames[4].admission_token == 15004ul,
        "reserved admission token");
    EXPECT_TRUE(result.frames[4].run_entry_token == 14004ul,
        "reserved run-entry token");
    EXPECT_TRUE(result.frames[4].activation_token == 13004ul,
        "reserved activation token");
    return 0;
}

static int runtime_entry_frame_report_is_deterministic(void) {
    latticra_kernel_runtime_entry_frame_request_t request;
    latticra_kernel_runtime_entry_frame_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "runtime entry frame evaluates for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY FRAME REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "frame_status=runtime-entry-frame-seed-ready\n") != 0,
        "frame status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_admission_status=runtime-entry-admission-seed-ready\n") != 0,
        "admission status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_run_entry_status=scheduler-run-entry-seed-ready\n") != 0,
        "scheduler run-entry status emitted");
    EXPECT_TRUE(strstr(report, "frame_count=4\n") != 0,
        "frame count emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_frame_allowed=0\n") != 0,
        "frame flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_admission_allowed=0\n") != 0,
        "admission flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report, "stack_switch_allowed=0\n") != 0,
        "stack switch flag emitted");
    EXPECT_TRUE(strstr(report,
            "frame[0].process_label=kernel-report-process-metadata\n") != 0,
        "frame zero process emitted");
    EXPECT_TRUE(strstr(report,
            "frame[0].frame_class=kernel-report-runtime-entry-frame\n") != 0,
        "frame zero class emitted");
    EXPECT_TRUE(strstr(report, "frame[0].frame_rank=1\n") != 0,
        "frame zero rank emitted");
    EXPECT_TRUE(strstr(report, "frame[0].frame_declared=1\n") != 0,
        "frame zero declared emitted");
    EXPECT_TRUE(strstr(report, "frame[0].frame_planned=0\n") != 0,
        "frame planned emitted");
    EXPECT_TRUE(strstr(report, "frame[0].frame_built=0\n") != 0,
        "frame built emitted");
    EXPECT_TRUE(strstr(report, "frame[0].frame_installed=0\n") != 0,
        "frame installed emitted");
    EXPECT_TRUE(strstr(report, "frame[0].runtime_entry_entered=0\n") != 0,
        "runtime entry entered emitted");
    EXPECT_TRUE(strstr(report, "frame[0].execution_entered=0\n") != 0,
        "execution entered emitted");
    EXPECT_TRUE(strstr(report, "frame[0].no_effect=1\n") != 0,
        "frame no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_frame_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_frame_report(&result, report,
            0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (runtime_entry_frame_seed_is_metadata_only() != 0) return 1;
    if (runtime_entry_frame_caps_count() != 0) return 1;
    if (runtime_entry_frame_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_frame: ok");
    return 0;
}
