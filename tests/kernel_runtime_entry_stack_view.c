#include "latticra/kernel_runtime_entry_stack_view.h"

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
    latticra_kernel_runtime_entry_stack_view_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_stack_view_count == 4u,
        "default stack view count");
    EXPECT_TRUE(request.runtime_entry_register_view_request.
            requested_register_view_count == 4u,
        "runtime entry register view seed request preserved");
    EXPECT_TRUE(request.runtime_entry_register_view_request.
            runtime_entry_frame_request.requested_frame_count == 4u,
        "runtime entry frame seed request preserved");
    EXPECT_TRUE(request.runtime_entry_register_view_request.
            runtime_entry_frame_request.runtime_entry_admission_request.
            requested_admission_count == 4u,
        "runtime entry admission seed request preserved");
    return 0;
}

static int runtime_entry_stack_view_seed_is_metadata_only(void) {
    latticra_kernel_runtime_entry_stack_view_request_t request;
    latticra_kernel_runtime_entry_stack_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_evaluate(&request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry stack view evaluates");
    EXPECT_TRUE(strcmp(result.stack_view_status,
            "runtime-entry-stack-view-seed-ready") == 0,
        "runtime entry stack view ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.runtime_entry_register_view.register_view_status,
            "runtime-entry-register-view-seed-ready") == 0,
        "runtime entry register view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_register_view.runtime_entry_frame.
            frame_status, "runtime-entry-frame-seed-ready") == 0,
        "runtime entry frame ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_register_view.runtime_entry_frame.
            runtime_entry_admission.admission_status,
            "runtime-entry-admission-seed-ready") == 0,
        "runtime entry admission ready");
    EXPECT_TRUE(result.stack_view_count == 4u,
        "stack view count four");
    EXPECT_TRUE(result.runtime_entry_register_view.register_view_count == 4u,
        "register view count four");
    EXPECT_TRUE(result.no_effect == 1,
        "runtime entry stack view no-effect");
    EXPECT_TRUE(result.runtime_entry_stack_view_allowed == 0,
        "runtime entry stack view denied");
    EXPECT_TRUE(result.runtime_entry_register_view_allowed == 0,
        "runtime entry register view denied");
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
    EXPECT_TRUE(result.register_save_allowed == 0,
        "register save denied");
    EXPECT_TRUE(result.register_restore_allowed == 0,
        "register restore denied");
    EXPECT_TRUE(result.stack_switch_allowed == 0,
        "stack switch denied");
    EXPECT_TRUE(result.address_space_switch_allowed == 0,
        "address space switch denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.stack_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "stack view zero process");
    EXPECT_TRUE(strcmp(result.stack_views[0].stack_view_class,
            "kernel-report-runtime-entry-stack-view") == 0,
        "stack view zero class");
    EXPECT_TRUE(result.stack_views[0].stack_view_token == 0ul,
        "stack view zero token");
    EXPECT_TRUE(result.stack_views[0].register_view_token == 0ul,
        "stack view zero register view token");
    EXPECT_TRUE(result.stack_views[0].frame_token == 0ul,
        "stack view zero frame token");
    EXPECT_TRUE(result.stack_views[0].admission_token == 0ul,
        "stack view zero admission token");
    EXPECT_TRUE(result.stack_views[0].run_entry_token == 0ul,
        "stack view zero run-entry token");
    EXPECT_TRUE(result.stack_views[0].activation_token == 0ul,
        "stack view zero activation token");
    EXPECT_TRUE(result.stack_views[0].pid_token == 1ul,
        "stack view zero pid");
    EXPECT_TRUE(result.stack_views[0].frame_rank == 1ul,
        "stack view zero frame rank");
    EXPECT_TRUE(result.stack_views[0].register_view_rank == 1ul,
        "stack view zero register view rank");
    EXPECT_TRUE(result.stack_views[0].stack_view_rank == 1ul,
        "stack view zero rank");
    EXPECT_TRUE(result.stack_views[0].remaining_budget_ns == 10000000ul,
        "stack view zero remaining budget");
    EXPECT_TRUE(result.stack_views[0].stack_slot_count == 4ul,
        "stack slot count");
    EXPECT_TRUE(result.stack_views[0].stack_window_bytes == 4096ul,
        "stack window bytes");
    EXPECT_TRUE(result.stack_views[0].register_view_declared == 1,
        "register view declared");
    EXPECT_TRUE(result.stack_views[0].stack_view_declared == 1,
        "stack view declared");
    EXPECT_TRUE(result.stack_views[0].stack_base_declared == 1,
        "stack base declared");
    EXPECT_TRUE(result.stack_views[0].stack_pointer_declared == 1,
        "stack pointer declared");
    EXPECT_TRUE(result.stack_views[0].stack_limit_declared == 1,
        "stack limit declared");
    EXPECT_TRUE(result.stack_views[0].guard_page_declared == 1,
        "guard page declared");
    EXPECT_TRUE(strcmp(result.stack_views[0].authority_status,
            "runtime-entry-stack-view-authority-denied") == 0,
        "stack view authority denied");
    EXPECT_TRUE(result.stack_views[0].stack_view_planned == 0,
        "stack view not planned");
    EXPECT_TRUE(result.stack_views[0].stack_view_built == 0,
        "stack view not built");
    EXPECT_TRUE(result.stack_views[0].stack_view_installed == 0,
        "stack view not installed");
    EXPECT_TRUE(result.stack_views[0].stack_capture_planned == 0,
        "stack capture not planned");
    EXPECT_TRUE(result.stack_views[0].stack_switch_planned == 0,
        "stack switch not planned");
    EXPECT_TRUE(result.stack_views[0].stack_map_planned == 0,
        "stack map not planned");
    EXPECT_TRUE(result.stack_views[0].runtime_entry_entered == 0,
        "runtime entry not entered");
    EXPECT_TRUE(result.stack_views[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.stack_views[0].context_switch_planned == 0,
        "context switch not planned");
    EXPECT_TRUE(result.stack_views[0].runtime_entry_stack_view_allowed == 0,
        "entry stack view denied");
    EXPECT_TRUE(result.stack_views[0].runtime_entry_register_view_allowed == 0,
        "entry register view denied");
    EXPECT_TRUE(result.stack_views[0].register_save_allowed == 0,
        "entry register save denied");
    EXPECT_TRUE(result.stack_views[0].register_restore_allowed == 0,
        "entry register restore denied");
    EXPECT_TRUE(result.stack_views[0].stack_switch_allowed == 0,
        "entry stack switch denied");
    EXPECT_TRUE(result.stack_views[0].address_space_switch_allowed == 0,
        "entry address space switch denied");
    EXPECT_TRUE(result.stack_views[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.stack_views[1].stack_view_class,
            "entropy-runtime-entry-stack-view") == 0,
        "entropy stack view class");
    EXPECT_TRUE(strcmp(result.stack_views[2].stack_view_class,
            "console-runtime-entry-stack-view") == 0,
        "console stack view class");
    EXPECT_TRUE(strcmp(result.stack_views[3].stack_view_class,
            "idle-runtime-entry-stack-view") == 0,
        "idle stack view class");
    return 0;
}

static int runtime_entry_stack_view_caps_count(void) {
    latticra_kernel_runtime_entry_stack_view_request_t request;
    latticra_kernel_runtime_entry_stack_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_stack_view_count = 99u;
    request.runtime_entry_register_view_request.
        requested_register_view_count = 99u;
    request.runtime_entry_register_view_request.runtime_entry_frame_request.
        requested_frame_count = 99u;
    request.runtime_entry_register_view_request.runtime_entry_frame_request.
        runtime_entry_admission_request.requested_admission_count = 99u;
    request.runtime_entry_register_view_request.runtime_entry_frame_request.
        runtime_entry_admission_request.scheduler_run_entry_request.
        requested_run_entry_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_evaluate(&request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry stack view evaluates cap");
    EXPECT_TRUE(result.stack_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_STACK_VIEW_MAX,
        "stack view count capped");
    EXPECT_TRUE(strcmp(result.stack_views[4].stack_view_class,
            "reserved-runtime-entry-stack-view") == 0,
        "reserved stack view class");
    EXPECT_TRUE(result.stack_views[4].stack_view_token == 18004ul,
        "reserved stack view token");
    EXPECT_TRUE(result.stack_views[4].register_view_token == 17004ul,
        "reserved register view token");
    EXPECT_TRUE(result.stack_views[4].frame_token == 16004ul,
        "reserved frame token");
    EXPECT_TRUE(result.stack_views[4].admission_token == 15004ul,
        "reserved admission token");
    EXPECT_TRUE(result.stack_views[4].run_entry_token == 14004ul,
        "reserved run-entry token");
    EXPECT_TRUE(result.stack_views[4].activation_token == 13004ul,
        "reserved activation token");
    return 0;
}

static int runtime_entry_stack_view_report_is_deterministic(void) {
    latticra_kernel_runtime_entry_stack_view_request_t request;
    latticra_kernel_runtime_entry_stack_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_STACK_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_evaluate(&request,
            &result) == LATTICRA_STATUS_OK,
        "runtime entry stack view evaluates for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_report(&result,
            report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY STACK VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "stack_view_status=runtime-entry-stack-view-seed-ready\n") != 0,
        "stack view status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_register_view_status=runtime-entry-register-view-seed-ready\n") != 0,
        "register view status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_frame_status=runtime-entry-frame-seed-ready\n") != 0,
        "frame status emitted");
    EXPECT_TRUE(strstr(report, "stack_view_count=4\n") != 0,
        "stack view count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_stack_view_allowed=0\n") != 0,
        "stack view flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_register_view_allowed=0\n") != 0,
        "register view flag emitted");
    EXPECT_TRUE(strstr(report, "stack_switch_allowed=0\n") != 0,
        "stack switch flag emitted");
    EXPECT_TRUE(strstr(report, "register_save_allowed=0\n") != 0,
        "register save flag emitted");
    EXPECT_TRUE(strstr(report, "register_restore_allowed=0\n") != 0,
        "register restore flag emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].process_label=kernel-report-process-metadata\n") != 0,
        "stack view zero process emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_view_class=kernel-report-runtime-entry-stack-view\n") != 0,
        "stack view zero class emitted");
    EXPECT_TRUE(strstr(report, "stack_view[0].stack_view_rank=1\n") != 0,
        "stack view zero rank emitted");
    EXPECT_TRUE(strstr(report, "stack_view[0].stack_slot_count=4\n") != 0,
        "stack slot count emitted");
    EXPECT_TRUE(strstr(report, "stack_view[0].stack_window_bytes=4096\n") != 0,
        "stack window emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_pointer_declared=1\n") != 0,
        "stack pointer emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].guard_page_declared=1\n") != 0,
        "guard page emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_view_planned=0\n") != 0,
        "stack view planned emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_capture_planned=0\n") != 0,
        "stack capture emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_switch_planned=0\n") != 0,
        "stack switch planned emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].runtime_entry_stack_view_allowed=0\n") != 0,
        "entry stack view allowed emitted");
    EXPECT_TRUE(strstr(report,
            "stack_view[0].stack_switch_allowed=0\n") != 0,
        "entry stack switch emitted");
    EXPECT_TRUE(strstr(report, "stack_view[0].no_effect=1\n") != 0,
        "stack view no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_stack_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_STACK_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_evaluate(0,
            &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_stack_view_report(&result,
            report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (runtime_entry_stack_view_seed_is_metadata_only() != 0) return 1;
    if (runtime_entry_stack_view_caps_count() != 0) return 1;
    if (runtime_entry_stack_view_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_stack_view: ok");
    return 0;
}
