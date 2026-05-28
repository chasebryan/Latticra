#include "latticra/kernel_runtime_entry_user_mode_resume_view.h"

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
    latticra_kernel_runtime_entry_user_mode_resume_view_request_t request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_user_mode_resume_view_count == 4u,
        "default user mode resume view count");
    EXPECT_TRUE(request.runtime_entry_syscall_exit_view_request.
            requested_syscall_exit_view_count == 4u,
        "syscall exit view request preserved");
    EXPECT_TRUE(request.runtime_entry_syscall_exit_view_request.
            runtime_entry_syscall_return_view_request.
            requested_syscall_return_view_count == 4u,
        "syscall return view request preserved");
    return 0;
}

static int user_mode_resume_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_user_mode_resume_view_request_t request;
    latticra_kernel_runtime_entry_user_mode_resume_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "user mode resume view evaluates");
    EXPECT_TRUE(strcmp(result.user_mode_resume_view_status,
            "runtime-entry-user-mode-resume-view-seed-ready") == 0,
        "user mode resume view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_syscall_exit_view.
            syscall_exit_view_status,
            "runtime-entry-syscall-exit-view-seed-ready") == 0,
        "syscall exit view ready");
    EXPECT_TRUE(result.user_mode_resume_view_count == 4u,
        "user mode resume view count");
    EXPECT_TRUE(result.no_effect == 1,
        "user mode resume view no effect");
    EXPECT_TRUE(result.runtime_entry_user_mode_resume_view_allowed == 0,
        "user mode resume view denied");
    EXPECT_TRUE(result.runtime_entry_syscall_exit_view_allowed == 0,
        "syscall exit view denied");
    EXPECT_TRUE(result.syscall_exit_allowed == 0,
        "syscall exit denied");
    EXPECT_TRUE(result.user_mode_resume_allowed == 0,
        "user mode resume denied");
    EXPECT_TRUE(result.user_instruction_resume_allowed == 0,
        "user instruction resume denied");
    EXPECT_TRUE(result.resume_frame_commit_allowed == 0,
        "resume frame commit denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.user_mode_resume_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.user_mode_resume_views[0].
            user_mode_resume_view_class,
            "kernel-report-runtime-entry-user-mode-resume-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_mode_resume_view_token == 0ul,
        "entry zero token");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            syscall_exit_view_token == 0ul,
        "entry zero exit token");
    EXPECT_TRUE(result.user_mode_resume_views[0].syscall_number == 512ul,
        "entry zero syscall number");
    EXPECT_TRUE(result.user_mode_resume_views[0].handler_slot == 0ul,
        "entry zero handler slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].dispatch_slot == 1024ul,
        "entry zero dispatch slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].return_slot == 2048ul,
        "entry zero return slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].exit_slot == 3072ul,
        "entry zero exit slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].resume_slot == 4096ul,
        "entry zero resume slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].instruction_pointer_slot ==
            13ul,
        "entry zero instruction pointer slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].stack_pointer_slot == 14ul,
        "entry zero stack pointer slot");
    EXPECT_TRUE(result.user_mode_resume_views[0].argument_count == 6ul,
        "entry zero argument count");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_mode_resume_view_declared == 1,
        "user mode resume view declared");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_mode_resume_declared == 1,
        "user mode resume declared");
    EXPECT_TRUE(result.user_mode_resume_views[0].resume_frame_declared == 1,
        "resume frame declared");
    EXPECT_TRUE(strcmp(result.user_mode_resume_views[0].authority_status,
            "runtime-entry-user-mode-resume-view-authority-denied") == 0,
        "authority denied");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_mode_resume_view_planned == 0,
        "user mode resume view not planned");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_mode_resume_planned == 0,
        "user mode resume not planned");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_instruction_resume_planned == 0,
        "user instruction resume not planned");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            runtime_entry_user_mode_resume_view_allowed == 0,
        "entry user mode resume view denied");
    EXPECT_TRUE(result.user_mode_resume_views[0].user_mode_resume_allowed == 0,
        "entry user mode resume denied");
    EXPECT_TRUE(result.user_mode_resume_views[0].
            user_instruction_resume_allowed == 0,
        "entry user instruction resume denied");
    EXPECT_TRUE(result.user_mode_resume_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.user_mode_resume_views[1].
            user_mode_resume_view_class,
            "entropy-runtime-entry-user-mode-resume-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.user_mode_resume_views[1].syscall_number == 513ul,
        "entry one syscall number");
    EXPECT_TRUE(result.user_mode_resume_views[1].resume_slot == 4097ul,
        "entry one resume slot");
    return 0;
}

static int user_mode_resume_view_caps_count(void) {
    latticra_kernel_runtime_entry_user_mode_resume_view_request_t request;
    latticra_kernel_runtime_entry_user_mode_resume_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_user_mode_resume_view_count = 99u;
    request.runtime_entry_syscall_exit_view_request.
        requested_syscall_exit_view_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "user mode resume view evaluates cap");
    EXPECT_TRUE(result.user_mode_resume_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_MAX,
        "user mode resume view capped");
    EXPECT_TRUE(strcmp(result.user_mode_resume_views[4].
            user_mode_resume_view_class,
            "reserved-runtime-entry-user-mode-resume-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.user_mode_resume_views[4].
            user_mode_resume_view_token == 25004ul,
        "reserved user mode resume token");
    EXPECT_TRUE(result.user_mode_resume_views[4].
            syscall_exit_view_token == 24004ul,
        "reserved syscall exit token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_user_mode_resume_view_request_t request;
    latticra_kernel_runtime_entry_user_mode_resume_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY USER MODE RESUME VIEW REPORT\n") !=
            0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_syscall_exit_view_status=runtime-entry-syscall-exit-view-seed-ready\n") != 0,
        "syscall exit status emitted");
    EXPECT_TRUE(strstr(report, "user_mode_resume_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_user_mode_resume_view_allowed=0\n") != 0,
        "user mode resume view authority emitted");
    EXPECT_TRUE(strstr(report, "user_mode_resume_allowed=0\n") != 0,
        "user mode resume emitted");
    EXPECT_TRUE(strstr(report, "user_instruction_resume_allowed=0\n") != 0,
        "user instruction resume emitted");
    EXPECT_TRUE(strstr(report, "resume_frame_commit_allowed=0\n") != 0,
        "resume frame commit emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].user_mode_resume_view_class=kernel-report-runtime-entry-user-mode-resume-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].resume_slot=4096\n") != 0,
        "entry resume slot emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].instruction_pointer_slot=13\n") != 0,
        "entry instruction pointer emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].user_mode_resume_view_planned=0\n") != 0,
        "resume view plan emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].runtime_entry_user_mode_resume_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "user_mode_resume_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_user_mode_resume_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
            0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_runtime_entry_user_mode_resume_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (user_mode_resume_view_is_metadata_only() != 0) return 1;
    if (user_mode_resume_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_user_mode_resume_view: ok");
    return 0;
}
