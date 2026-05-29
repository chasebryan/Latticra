#include "latticra/kernel_runtime_entry_syscall_return_view.h"

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
    latticra_kernel_runtime_entry_syscall_return_view_request_t request;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_syscall_return_view_count == 4u,
        "default syscall return view count");
    EXPECT_TRUE(request.runtime_entry_syscall_dispatch_view_request.
            requested_syscall_dispatch_view_count == 4u,
        "syscall dispatch view request preserved");
    EXPECT_TRUE(request.runtime_entry_syscall_dispatch_view_request.
            runtime_entry_syscall_gate_view_request.
            requested_syscall_gate_view_count == 4u,
        "syscall gate view request preserved");
    return 0;
}

static int syscall_return_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_syscall_return_view_request_t request;
    latticra_kernel_runtime_entry_syscall_return_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "syscall return view evaluates");
    EXPECT_TRUE(strcmp(result.syscall_return_view_status,
            "runtime-entry-syscall-return-view-seed-ready") == 0,
        "syscall return view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_syscall_dispatch_view.
            syscall_dispatch_view_status,
            "runtime-entry-syscall-dispatch-view-seed-ready") == 0,
        "syscall dispatch view ready");
    EXPECT_TRUE(result.syscall_return_view_count == 4u,
        "syscall return view count");
    EXPECT_TRUE(result.no_effect == 1,
        "syscall return view no effect");
    EXPECT_TRUE(result.runtime_entry_syscall_return_view_allowed == 0,
        "syscall return view denied");
    EXPECT_TRUE(result.runtime_entry_syscall_dispatch_view_allowed == 0,
        "syscall dispatch view denied");
    EXPECT_TRUE(result.syscall_dispatch_allowed == 0,
        "syscall dispatch denied");
    EXPECT_TRUE(result.syscall_handler_allowed == 0,
        "syscall handler denied");
    EXPECT_TRUE(result.syscall_return_allowed == 0,
        "syscall return denied");
    EXPECT_TRUE(result.syscall_result_copy_allowed == 0,
        "syscall result copy denied");
    EXPECT_TRUE(result.interrupt_return_allowed == 0,
        "interrupt return denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.syscall_return_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.syscall_return_views[0].
            syscall_return_view_class,
            "kernel-report-runtime-entry-syscall-return-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_view_token == 0ul,
        "entry zero token");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_dispatch_view_token == 0ul,
        "entry zero dispatch token");
    EXPECT_TRUE(result.syscall_return_views[0].syscall_number == 512ul,
        "entry zero syscall number");
    EXPECT_TRUE(result.syscall_return_views[0].handler_slot == 0ul,
        "entry zero handler slot");
    EXPECT_TRUE(result.syscall_return_views[0].dispatch_slot == 1024ul,
        "entry zero dispatch slot");
    EXPECT_TRUE(result.syscall_return_views[0].return_slot == 2048ul,
        "entry zero return slot");
    EXPECT_TRUE(result.syscall_return_views[0].result_register_slot == 10ul,
        "entry zero result register slot");
    EXPECT_TRUE(result.syscall_return_views[0].errno_slot == 11ul,
        "entry zero errno slot");
    EXPECT_TRUE(result.syscall_return_views[0].argument_count == 6ul,
        "entry zero argument count");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_view_declared == 1,
        "syscall return view declared");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_declared == 1,
        "syscall return declared");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_result_window_declared == 1,
        "syscall result window declared");
    EXPECT_TRUE(strcmp(result.syscall_return_views[0].authority_status,
            "runtime-entry-syscall-return-view-authority-denied") == 0,
        "authority denied");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_view_planned == 0,
        "syscall return view not planned");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_planned == 0,
        "syscall return not planned");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_result_copy_planned == 0,
        "syscall result copy not planned");
    EXPECT_TRUE(result.syscall_return_views[0].
            runtime_entry_syscall_return_view_allowed == 0,
        "entry syscall return view denied");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_return_allowed == 0,
        "entry syscall return denied");
    EXPECT_TRUE(result.syscall_return_views[0].
            syscall_result_copy_allowed == 0,
        "entry syscall result copy denied");
    EXPECT_TRUE(result.syscall_return_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.syscall_return_views[1].
            syscall_return_view_class,
            "entropy-runtime-entry-syscall-return-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.syscall_return_views[1].syscall_number == 513ul,
        "entry one syscall number");
    EXPECT_TRUE(result.syscall_return_views[1].return_slot == 2049ul,
        "entry one return slot");
    return 0;
}

static int syscall_return_view_caps_count(void) {
    latticra_kernel_runtime_entry_syscall_return_view_request_t request;
    latticra_kernel_runtime_entry_syscall_return_view_result_t result;

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_syscall_return_view_count = 99u;
    request.runtime_entry_syscall_dispatch_view_request.
        requested_syscall_dispatch_view_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "syscall return view evaluates cap");
    EXPECT_TRUE(result.syscall_return_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_MAX,
        "syscall return view capped");
    EXPECT_TRUE(strcmp(result.syscall_return_views[4].
            syscall_return_view_class,
            "reserved-runtime-entry-syscall-return-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.syscall_return_views[4].
            syscall_return_view_token == 23004ul,
        "reserved syscall return token");
    EXPECT_TRUE(result.syscall_return_views[4].
            syscall_dispatch_view_token == 22004ul,
        "reserved syscall dispatch token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_syscall_return_view_request_t request;
    latticra_kernel_runtime_entry_syscall_return_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY SYSCALL RETURN VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_syscall_dispatch_view_status=runtime-entry-syscall-dispatch-view-seed-ready\n") != 0,
        "syscall dispatch status emitted");
    EXPECT_TRUE(strstr(report, "syscall_return_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_syscall_return_view_allowed=0\n") != 0,
        "syscall return view authority emitted");
    EXPECT_TRUE(strstr(report, "syscall_return_allowed=0\n") != 0,
        "syscall return emitted");
    EXPECT_TRUE(strstr(report, "syscall_result_copy_allowed=0\n") != 0,
        "syscall result copy emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].syscall_return_view_class=kernel-report-runtime-entry-syscall-return-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].return_slot=2048\n") != 0,
        "entry return slot emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].result_register_slot=10\n") != 0,
        "entry result register emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].syscall_return_view_planned=0\n") != 0,
        "return view plan emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].runtime_entry_syscall_return_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "syscall_return_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_syscall_return_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_evaluate(0,
            &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_evaluate(0,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_syscall_return_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (syscall_return_view_is_metadata_only() != 0) return 1;
    if (syscall_return_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_syscall_return_view: ok");
    return 0;
}
