#include "latticra/kernel_runtime_entry_privilege_level_view.h"

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
    latticra_kernel_runtime_entry_privilege_level_view_request_t request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_privilege_level_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_privilege_level_view_count == 4u,
        "default privilege level view count");
    EXPECT_TRUE(request.runtime_entry_address_space_view_request.
            requested_address_space_view_count == 4u,
        "address space view request preserved");
    EXPECT_TRUE(request.runtime_entry_address_space_view_request.
            runtime_entry_stack_view_request.requested_stack_view_count == 4u,
        "stack view request preserved");
    return 0;
}

static int privilege_level_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_privilege_level_view_request_t request;
    latticra_kernel_runtime_entry_privilege_level_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_privilege_level_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "privilege level view evaluates");
    EXPECT_TRUE(strcmp(result.privilege_level_view_status,
            "runtime-entry-privilege-level-view-seed-ready") == 0,
        "privilege level view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_address_space_view.
            address_space_view_status,
            "runtime-entry-address-space-view-seed-ready") == 0,
        "address space view ready");
    EXPECT_TRUE(result.privilege_level_view_count == 4u,
        "privilege level view count");
    EXPECT_TRUE(result.no_effect == 1,
        "privilege level view no effect");
    EXPECT_TRUE(result.runtime_entry_privilege_level_view_allowed == 0,
        "privilege level view denied");
    EXPECT_TRUE(result.runtime_entry_address_space_view_allowed == 0,
        "address space view denied");
    EXPECT_TRUE(result.privilege_transition_allowed == 0,
        "privilege transition denied");
    EXPECT_TRUE(result.syscall_gate_allowed == 0,
        "syscall gate denied");
    EXPECT_TRUE(result.interrupt_return_allowed == 0,
        "interrupt return denied");
    EXPECT_TRUE(result.runtime_entry_allowed == 0,
        "runtime entry denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.privilege_level_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.privilege_level_views[0].
            privilege_level_view_class,
            "kernel-report-runtime-entry-privilege-level-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.privilege_level_views[0].
            privilege_level_view_token == 0ul,
        "entry zero token");
    EXPECT_TRUE(result.privilege_level_views[0].
            address_space_view_token == 0ul,
        "entry zero address space view token");
    EXPECT_TRUE(result.privilege_level_views[0].pid_token == 1ul,
        "entry zero pid");
    EXPECT_TRUE(result.privilege_level_views[0].
            privilege_level_view_rank == 1ul,
        "entry zero rank");
    EXPECT_TRUE(result.privilege_level_views[0].privilege_level == 0ul,
        "entry zero privilege level");
    EXPECT_TRUE(result.privilege_level_views[0].ring_number == 0ul,
        "entry zero ring");
    EXPECT_TRUE(result.privilege_level_views[0].
            capability_slot_count == 4ul,
        "entry capability slots");
    EXPECT_TRUE(result.privilege_level_views[0].
            privilege_boundary_declared == 1,
        "privilege boundary declared");
    EXPECT_TRUE(result.privilege_level_views[0].syscall_gate_declared == 1,
        "syscall gate declared");
    EXPECT_TRUE(strcmp(result.privilege_level_views[0].authority_status,
            "runtime-entry-privilege-level-view-authority-denied") == 0,
        "authority denied");
    EXPECT_TRUE(result.privilege_level_views[0].
            privilege_transition_planned == 0,
        "privilege transition not planned");
    EXPECT_TRUE(result.privilege_level_views[0].syscall_gate_planned == 0,
        "syscall gate not planned");
    EXPECT_TRUE(result.privilege_level_views[0].
            interrupt_return_planned == 0,
        "interrupt return not planned");
    EXPECT_TRUE(result.privilege_level_views[0].
            runtime_entry_privilege_level_view_allowed == 0,
        "entry privilege level view denied");
    EXPECT_TRUE(result.privilege_level_views[0].
            privilege_transition_allowed == 0,
        "entry privilege transition denied");
    EXPECT_TRUE(result.privilege_level_views[0].syscall_gate_allowed == 0,
        "entry syscall gate denied");
    EXPECT_TRUE(result.privilege_level_views[0].
            interrupt_return_allowed == 0,
        "entry interrupt return denied");
    EXPECT_TRUE(result.privilege_level_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.privilege_level_views[1].
            privilege_level_view_class,
            "entropy-runtime-entry-privilege-level-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.privilege_level_views[1].privilege_level == 3ul,
        "entry one user privilege");
    return 0;
}

static int privilege_level_view_caps_count(void) {
    latticra_kernel_runtime_entry_privilege_level_view_request_t request;
    latticra_kernel_runtime_entry_privilege_level_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_privilege_level_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_privilege_level_view_count = 99u;
    request.runtime_entry_address_space_view_request.
        requested_address_space_view_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "privilege level view evaluates cap");
    EXPECT_TRUE(result.privilege_level_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_MAX,
        "privilege level view capped");
    EXPECT_TRUE(strcmp(result.privilege_level_views[4].
            privilege_level_view_class,
            "reserved-runtime-entry-privilege-level-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.privilege_level_views[4].
            privilege_level_view_token == 20004ul,
        "reserved privilege token");
    EXPECT_TRUE(result.privilege_level_views[4].
            address_space_view_token == 19004ul,
        "reserved address space token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_privilege_level_view_request_t request;
    latticra_kernel_runtime_entry_privilege_level_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_privilege_level_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY PRIVILEGE LEVEL VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_address_space_view_status=runtime-entry-address-space-view-seed-ready\n") != 0,
        "address status emitted");
    EXPECT_TRUE(strstr(report, "privilege_level_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_privilege_level_view_allowed=0\n") != 0,
        "privilege view authority emitted");
    EXPECT_TRUE(strstr(report, "privilege_transition_allowed=0\n") != 0,
        "privilege transition emitted");
    EXPECT_TRUE(strstr(report, "syscall_gate_allowed=0\n") != 0,
        "syscall gate emitted");
    EXPECT_TRUE(strstr(report, "interrupt_return_allowed=0\n") != 0,
        "interrupt return emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].privilege_level_view_class=kernel-report-runtime-entry-privilege-level-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].privilege_level=0\n") != 0,
        "entry privilege emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].syscall_gate_declared=1\n") != 0,
        "syscall gate declared emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].privilege_transition_planned=0\n") != 0,
        "transition planned emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].runtime_entry_privilege_level_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "privilege_level_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_privilege_level_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_privilege_level_view_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_evaluate(0,
            &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_evaluate(0,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_privilege_level_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (privilege_level_view_is_metadata_only() != 0) return 1;
    if (privilege_level_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_privilege_level_view: ok");
    return 0;
}
