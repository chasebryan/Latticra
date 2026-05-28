#include "latticra/kernel_runtime_entry_syscall_exit_view.h"

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
    latticra_kernel_runtime_entry_syscall_exit_view_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_syscall_exit_view_count == 4u,
        "default syscall exit view count");
    EXPECT_TRUE(request.runtime_entry_syscall_return_view_request.
            requested_syscall_return_view_count == 4u,
        "syscall return view request preserved");
    EXPECT_TRUE(request.runtime_entry_syscall_return_view_request.
            runtime_entry_syscall_dispatch_view_request.
            requested_syscall_dispatch_view_count == 4u,
        "syscall dispatch view request preserved");
    return 0;
}

static int syscall_exit_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_syscall_exit_view_request_t request;
    latticra_kernel_runtime_entry_syscall_exit_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "syscall exit view evaluates");
    EXPECT_TRUE(strcmp(result.syscall_exit_view_status,
            "runtime-entry-syscall-exit-view-seed-ready") == 0,
        "syscall exit view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_syscall_return_view.
            syscall_return_view_status,
            "runtime-entry-syscall-return-view-seed-ready") == 0,
        "syscall return view ready");
    EXPECT_TRUE(result.syscall_exit_view_count == 4u,
        "syscall exit view count");
    EXPECT_TRUE(result.no_effect == 1,
        "syscall exit view no effect");
    EXPECT_TRUE(result.runtime_entry_syscall_exit_view_allowed == 0,
        "syscall exit view denied");
    EXPECT_TRUE(result.runtime_entry_syscall_return_view_allowed == 0,
        "syscall return view denied");
    EXPECT_TRUE(result.syscall_return_allowed == 0,
        "syscall return denied");
    EXPECT_TRUE(result.syscall_exit_allowed == 0,
        "syscall exit denied");
    EXPECT_TRUE(result.syscall_exit_commit_allowed == 0,
        "syscall exit commit denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.syscall_exit_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.syscall_exit_views[0].syscall_exit_view_class,
            "kernel-report-runtime-entry-syscall-exit-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_view_token == 0ul,
        "entry zero token");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_return_view_token == 0ul,
        "entry zero return token");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_number == 512ul,
        "entry zero syscall number");
    EXPECT_TRUE(result.syscall_exit_views[0].handler_slot == 0ul,
        "entry zero handler slot");
    EXPECT_TRUE(result.syscall_exit_views[0].dispatch_slot == 1024ul,
        "entry zero dispatch slot");
    EXPECT_TRUE(result.syscall_exit_views[0].return_slot == 2048ul,
        "entry zero return slot");
    EXPECT_TRUE(result.syscall_exit_views[0].exit_slot == 3072ul,
        "entry zero exit slot");
    EXPECT_TRUE(result.syscall_exit_views[0].result_register_slot == 10ul,
        "entry zero result register slot");
    EXPECT_TRUE(result.syscall_exit_views[0].errno_slot == 11ul,
        "entry zero errno slot");
    EXPECT_TRUE(result.syscall_exit_views[0].status_slot == 12ul,
        "entry zero status slot");
    EXPECT_TRUE(result.syscall_exit_views[0].argument_count == 6ul,
        "entry zero argument count");
    EXPECT_TRUE(result.syscall_exit_views[0].
            syscall_return_view_declared == 1,
        "syscall return view declared");
    EXPECT_TRUE(result.syscall_exit_views[0].
            syscall_exit_view_declared == 1,
        "syscall exit view declared");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_declared == 1,
        "syscall exit declared");
    EXPECT_TRUE(result.syscall_exit_views[0].
            syscall_exit_window_declared == 1,
        "syscall exit window declared");
    EXPECT_TRUE(strcmp(result.syscall_exit_views[0].authority_status,
            "runtime-entry-syscall-exit-view-authority-denied") == 0,
        "authority denied");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_view_planned == 0,
        "syscall exit view not planned");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_planned == 0,
        "syscall exit not planned");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_commit_planned == 0,
        "syscall exit commit not planned");
    EXPECT_TRUE(result.syscall_exit_views[0].
            runtime_entry_syscall_exit_view_allowed == 0,
        "entry syscall exit view denied");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_allowed == 0,
        "entry syscall exit denied");
    EXPECT_TRUE(result.syscall_exit_views[0].syscall_exit_commit_allowed == 0,
        "entry syscall exit commit denied");
    EXPECT_TRUE(result.syscall_exit_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.syscall_exit_views[1].
            syscall_exit_view_class,
            "entropy-runtime-entry-syscall-exit-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.syscall_exit_views[1].syscall_number == 513ul,
        "entry one syscall number");
    EXPECT_TRUE(result.syscall_exit_views[1].exit_slot == 3073ul,
        "entry one exit slot");
    return 0;
}

static int syscall_exit_view_caps_count(void) {
    latticra_kernel_runtime_entry_syscall_exit_view_request_t request;
    latticra_kernel_runtime_entry_syscall_exit_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_syscall_exit_view_count = 99u;
    request.runtime_entry_syscall_return_view_request.
        requested_syscall_return_view_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "syscall exit view evaluates cap");
    EXPECT_TRUE(result.syscall_exit_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_MAX,
        "syscall exit view capped");
    EXPECT_TRUE(strcmp(result.syscall_exit_views[4].syscall_exit_view_class,
            "reserved-runtime-entry-syscall-exit-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.syscall_exit_views[4].
            syscall_exit_view_token == 24004ul,
        "reserved syscall exit token");
    EXPECT_TRUE(result.syscall_exit_views[4].
            syscall_return_view_token == 23004ul,
        "reserved syscall return token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_syscall_exit_view_request_t request;
    latticra_kernel_runtime_entry_syscall_exit_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY SYSCALL EXIT VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view_status=runtime-entry-syscall-exit-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready\n") != 0,
        "syscall return status emitted");
    EXPECT_TRUE(strstr(report, "syscall_exit_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_syscall_exit_view_allowed=0\n") != 0,
        "syscall exit view authority emitted");
    EXPECT_TRUE(strstr(report, "syscall_exit_allowed=0\n") != 0,
        "syscall exit emitted");
    EXPECT_TRUE(strstr(report, "syscall_exit_commit_allowed=0\n") != 0,
        "syscall exit commit emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].syscall_exit_view_class=kernel-report-runtime-entry-syscall-exit-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].exit_slot=3072\n") != 0,
        "entry exit slot emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].status_slot=12\n") != 0,
        "entry status slot emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].syscall_exit_view_planned=0\n") != 0,
        "exit view plan emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].runtime_entry_syscall_exit_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_exit_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_syscall_exit_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_evaluate(0,
            &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_evaluate(0,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_exit_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (syscall_exit_view_is_metadata_only() != 0) return 1;
    if (syscall_exit_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_syscall_exit_view: ok");
    return 0;
}
