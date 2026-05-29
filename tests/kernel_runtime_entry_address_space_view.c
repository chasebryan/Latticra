#include "latticra/kernel_runtime_entry_address_space_view.h"

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
    latticra_kernel_runtime_entry_address_space_view_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_address_space_view_count == 4u,
        "default address space view count");
    EXPECT_TRUE(request.runtime_entry_stack_view_request.
            requested_stack_view_count == 4u,
        "runtime entry stack view seed request preserved");
    EXPECT_TRUE(request.runtime_entry_stack_view_request.
            runtime_entry_register_view_request.
            requested_register_view_count == 4u,
        "runtime entry register view seed request preserved");
    EXPECT_TRUE(request.runtime_entry_stack_view_request.
            runtime_entry_register_view_request.runtime_entry_frame_request.
            requested_frame_count == 4u,
        "runtime entry frame seed request preserved");
    EXPECT_TRUE(request.runtime_entry_stack_view_request.
            runtime_entry_register_view_request.runtime_entry_frame_request.
            runtime_entry_admission_request.requested_admission_count == 4u,
        "runtime entry admission seed request preserved");
    return 0;
}

static int runtime_entry_address_space_view_seed_is_metadata_only(void) {
    latticra_kernel_runtime_entry_address_space_view_request_t request;
    latticra_kernel_runtime_entry_address_space_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry address space view evaluates");
    EXPECT_TRUE(strcmp(result.address_space_view_status,
            "runtime-entry-address-space-view-seed-ready") == 0,
        "runtime entry address space view ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.runtime_entry_stack_view.stack_view_status,
            "runtime-entry-stack-view-seed-ready") == 0,
        "runtime entry stack view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_stack_view.
            runtime_entry_register_view.register_view_status,
            "runtime-entry-register-view-seed-ready") == 0,
        "runtime entry register view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_stack_view.
            runtime_entry_register_view.runtime_entry_frame.frame_status,
            "runtime-entry-frame-seed-ready") == 0,
        "runtime entry frame ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_stack_view.
            runtime_entry_register_view.runtime_entry_frame.
            runtime_entry_admission.admission_status,
            "runtime-entry-admission-seed-ready") == 0,
        "runtime entry admission ready");
    EXPECT_TRUE(result.address_space_view_count == 4u,
        "address space view count four");
    EXPECT_TRUE(result.runtime_entry_stack_view.stack_view_count == 4u,
        "stack view count four");
    EXPECT_TRUE(result.no_effect == 1,
        "runtime entry address space view no-effect");
    EXPECT_TRUE(result.runtime_entry_address_space_view_allowed == 0,
        "runtime entry address space view denied");
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
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.stack_switch_allowed == 0,
        "stack switch denied");
    EXPECT_TRUE(result.address_space_switch_allowed == 0,
        "address space switch denied");
    EXPECT_TRUE(result.page_table_write_allowed == 0,
        "page table write denied");
    EXPECT_TRUE(result.tlb_flush_allowed == 0,
        "tlb flush denied");
    EXPECT_TRUE(result.mmu_update_allowed == 0,
        "mmu update denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.address_space_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "address space view zero process");
    EXPECT_TRUE(strcmp(result.address_space_views[0].
            address_space_view_class,
            "kernel-report-runtime-entry-address-space-view") == 0,
        "address space view zero class");
    EXPECT_TRUE(result.address_space_views[0].address_space_view_token == 0ul,
        "address space view zero token");
    EXPECT_TRUE(result.address_space_views[0].stack_view_token == 0ul,
        "address space view zero stack view token");
    EXPECT_TRUE(result.address_space_views[0].register_view_token == 0ul,
        "address space view zero register view token");
    EXPECT_TRUE(result.address_space_views[0].frame_token == 0ul,
        "address space view zero frame token");
    EXPECT_TRUE(result.address_space_views[0].admission_token == 0ul,
        "address space view zero admission token");
    EXPECT_TRUE(result.address_space_views[0].run_entry_token == 0ul,
        "address space view zero run-entry token");
    EXPECT_TRUE(result.address_space_views[0].activation_token == 0ul,
        "address space view zero activation token");
    EXPECT_TRUE(result.address_space_views[0].pid_token == 1ul,
        "address space view zero pid");
    EXPECT_TRUE(result.address_space_views[0].frame_rank == 1ul,
        "address space view zero frame rank");
    EXPECT_TRUE(result.address_space_views[0].register_view_rank == 1ul,
        "address space view zero register view rank");
    EXPECT_TRUE(result.address_space_views[0].stack_view_rank == 1ul,
        "address space view zero stack view rank");
    EXPECT_TRUE(result.address_space_views[0].address_space_view_rank == 1ul,
        "address space view zero rank");
    EXPECT_TRUE(result.address_space_views[0].remaining_budget_ns ==
            10000000ul,
        "address space view zero remaining budget");
    EXPECT_TRUE(result.address_space_views[0].address_space_slot_count == 4ul,
        "address space slot count");
    EXPECT_TRUE(result.address_space_views[0].address_space_window_bytes ==
            1048576ul,
        "address space window bytes");
    EXPECT_TRUE(result.address_space_views[0].stack_view_declared == 1,
        "stack view declared");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_view_declared == 1,
        "address space view declared");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_root_declared == 1,
        "address space root declared");
    EXPECT_TRUE(result.address_space_views[0].user_range_declared == 1,
        "user range declared");
    EXPECT_TRUE(result.address_space_views[0].kernel_range_declared == 1,
        "kernel range declared");
    EXPECT_TRUE(result.address_space_views[0].guard_region_declared == 1,
        "guard region declared");
    EXPECT_TRUE(strcmp(result.address_space_views[0].authority_status,
            "runtime-entry-address-space-view-authority-denied") == 0,
        "address space view authority denied");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_view_planned == 0,
        "address space view not planned");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_capture_planned == 0,
        "address space capture not planned");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_switch_planned == 0,
        "address space switch not planned");
    EXPECT_TRUE(result.address_space_views[0].page_table_walk_planned == 0,
        "page table walk not planned");
    EXPECT_TRUE(result.address_space_views[0].mmu_update_planned == 0,
        "mmu update not planned");
    EXPECT_TRUE(result.address_space_views[0].runtime_entry_entered == 0,
        "runtime entry not entered");
    EXPECT_TRUE(result.address_space_views[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.address_space_views[0].context_switch_planned == 0,
        "context switch not planned");
    EXPECT_TRUE(result.address_space_views[0].
            runtime_entry_address_space_view_allowed == 0,
        "entry address space view denied");
    EXPECT_TRUE(result.address_space_views[0].
            runtime_entry_stack_view_allowed == 0,
        "entry stack view denied");
    EXPECT_TRUE(result.address_space_views[0].
            runtime_entry_register_view_allowed == 0,
        "entry register view denied");
    EXPECT_TRUE(result.address_space_views[0].stack_switch_allowed == 0,
        "entry stack switch denied");
    EXPECT_TRUE(result.address_space_views[0].
            address_space_switch_allowed == 0,
        "entry address space switch denied");
    EXPECT_TRUE(result.address_space_views[0].page_table_write_allowed == 0,
        "entry page table write denied");
    EXPECT_TRUE(result.address_space_views[0].tlb_flush_allowed == 0,
        "entry tlb flush denied");
    EXPECT_TRUE(result.address_space_views[0].mmu_update_allowed == 0,
        "entry mmu update denied");
    EXPECT_TRUE(result.address_space_views[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.address_space_views[1].
            address_space_view_class,
            "entropy-runtime-entry-address-space-view") == 0,
        "entropy address space view class");
    EXPECT_TRUE(strcmp(result.address_space_views[2].
            address_space_view_class,
            "console-runtime-entry-address-space-view") == 0,
        "console address space view class");
    EXPECT_TRUE(strcmp(result.address_space_views[3].
            address_space_view_class,
            "idle-runtime-entry-address-space-view") == 0,
        "idle address space view class");
    return 0;
}

static int runtime_entry_address_space_view_caps_count(void) {
    latticra_kernel_runtime_entry_address_space_view_request_t request;
    latticra_kernel_runtime_entry_address_space_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_address_space_view_count = 99u;
    request.runtime_entry_stack_view_request.requested_stack_view_count = 99u;
    request.runtime_entry_stack_view_request.runtime_entry_register_view_request.
        requested_register_view_count = 99u;
    request.runtime_entry_stack_view_request.runtime_entry_register_view_request.
        runtime_entry_frame_request.requested_frame_count = 99u;
    request.runtime_entry_stack_view_request.runtime_entry_register_view_request.
        runtime_entry_frame_request.runtime_entry_admission_request.
        requested_admission_count = 99u;
    request.runtime_entry_stack_view_request.runtime_entry_register_view_request.
        runtime_entry_frame_request.runtime_entry_admission_request.
        scheduler_run_entry_request.requested_run_entry_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry address space view evaluates cap");
    EXPECT_TRUE(result.address_space_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_MAX,
        "address space view count capped");
    EXPECT_TRUE(strcmp(result.address_space_views[4].
            address_space_view_class,
            "reserved-runtime-entry-address-space-view") == 0,
        "reserved address space view class");
    EXPECT_TRUE(result.address_space_views[4].address_space_view_token ==
            19004ul,
        "reserved address space view token");
    EXPECT_TRUE(result.address_space_views[4].stack_view_token == 18004ul,
        "reserved stack view token");
    EXPECT_TRUE(result.address_space_views[4].register_view_token == 17004ul,
        "reserved register view token");
    EXPECT_TRUE(result.address_space_views[4].frame_token == 16004ul,
        "reserved frame token");
    EXPECT_TRUE(result.address_space_views[4].admission_token == 15004ul,
        "reserved admission token");
    EXPECT_TRUE(result.address_space_views[4].run_entry_token == 14004ul,
        "reserved run-entry token");
    EXPECT_TRUE(result.address_space_views[4].activation_token == 13004ul,
        "reserved activation token");
    return 0;
}

static int runtime_entry_address_space_view_report_is_deterministic(void) {
    latticra_kernel_runtime_entry_address_space_view_request_t request;
    latticra_kernel_runtime_entry_address_space_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "runtime entry address space view evaluates for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY ADDRESS SPACE VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "address_space_view_status=runtime-entry-address-space-view-seed-ready\n") != 0,
        "address space view status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_stack_view_status=runtime-entry-stack-view-seed-ready\n") != 0,
        "stack view status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_register_view_status=runtime-entry-register-view-seed-ready\n") != 0,
        "register view status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_frame_status=runtime-entry-frame-seed-ready\n") != 0,
        "frame status emitted");
    EXPECT_TRUE(strstr(report, "address_space_view_count=4\n") != 0,
        "address space view count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_address_space_view_allowed=0\n") != 0,
        "address space view flag emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_stack_view_allowed=0\n") != 0,
        "stack view flag emitted");
    EXPECT_TRUE(strstr(report, "address_space_switch_allowed=0\n") != 0,
        "address space switch flag emitted");
    EXPECT_TRUE(strstr(report, "page_table_write_allowed=0\n") != 0,
        "page table write flag emitted");
    EXPECT_TRUE(strstr(report, "tlb_flush_allowed=0\n") != 0,
        "tlb flush flag emitted");
    EXPECT_TRUE(strstr(report, "mmu_update_allowed=0\n") != 0,
        "mmu update flag emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].process_label=kernel-report-process-metadata\n") != 0,
        "address space view zero process emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_view_class=kernel-report-runtime-entry-address-space-view\n") != 0,
        "address space view zero class emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_view_rank=1\n") != 0,
        "address space view zero rank emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_slot_count=4\n") != 0,
        "address space slot count emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_window_bytes=1048576\n") != 0,
        "address space window emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_root_declared=1\n") != 0,
        "address space root emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].guard_region_declared=1\n") != 0,
        "guard region emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_view_planned=0\n") != 0,
        "address space view planned emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_capture_planned=0\n") != 0,
        "address space capture emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_switch_planned=0\n") != 0,
        "address space switch planned emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].page_table_walk_planned=0\n") != 0,
        "page table walk planned emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].runtime_entry_address_space_view_allowed=0\n") != 0,
        "entry address space view allowed emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].address_space_switch_allowed=0\n") != 0,
        "entry address space switch emitted");
    EXPECT_TRUE(strstr(report,
            "address_space_view[0].page_table_write_allowed=0\n") != 0,
        "entry page table write emitted");
    EXPECT_TRUE(strstr(report, "address_space_view[0].no_effect=1\n") != 0,
        "address space view no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_address_space_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_address_space_view_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_evaluate(0,
            &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_evaluate(0,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_address_space_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (runtime_entry_address_space_view_seed_is_metadata_only() != 0) {
        return 1;
    }
    if (runtime_entry_address_space_view_caps_count() != 0) return 1;
    if (runtime_entry_address_space_view_report_is_deterministic() != 0) {
        return 1;
    }
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_address_space_view: ok");
    return 0;
}
