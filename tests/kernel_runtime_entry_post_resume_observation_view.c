#include "latticra/kernel_runtime_entry_post_resume_observation_view.h"

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
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_post_resume_observation_view_count == 4u,
        "default post resume observation view count");
    EXPECT_TRUE(request.runtime_entry_user_mode_resume_view_request.
            requested_user_mode_resume_view_count == 4u,
        "user mode resume view request preserved");
    EXPECT_TRUE(request.runtime_entry_user_mode_resume_view_request.
            runtime_entry_syscall_exit_view_request.
            requested_syscall_exit_view_count == 4u,
        "syscall exit view request preserved");
    return 0;
}

static int post_resume_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "post resume observation view evaluates");
    EXPECT_TRUE(strcmp(result.post_resume_observation_view_status,
            "runtime-entry-post-resume-observation-view-seed-ready") == 0,
        "post resume observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_user_mode_resume_view.
            user_mode_resume_view_status,
            "runtime-entry-user-mode-resume-view-seed-ready") == 0,
        "user mode resume view ready");
    EXPECT_TRUE(result.post_resume_observation_view_count == 4u,
        "post resume observation view count");
    EXPECT_TRUE(result.no_effect == 1,
        "post resume observation view no effect");
    EXPECT_TRUE(result.runtime_entry_post_resume_observation_view_allowed == 0,
        "post resume observation view denied");
    EXPECT_TRUE(result.runtime_entry_user_mode_resume_view_allowed == 0,
        "user mode resume view denied");
    EXPECT_TRUE(result.user_mode_resume_allowed == 0,
        "user mode resume denied");
    EXPECT_TRUE(result.post_resume_observation_allowed == 0,
        "post resume observation denied");
    EXPECT_TRUE(result.instruction_pointer_read_allowed == 0,
        "instruction pointer read denied");
    EXPECT_TRUE(result.stack_pointer_read_allowed == 0,
        "stack pointer read denied");
    EXPECT_TRUE(result.cpu_mode_read_allowed == 0,
        "cpu mode read denied");
    EXPECT_TRUE(result.scheduler_execution_allowed == 0,
        "scheduler execution denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.post_resume_observation_views[0].process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.post_resume_observation_views[0].
            post_resume_observation_view_class,
            "kernel-report-runtime-entry-post-resume-observation-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_view_token == 0ul,
        "entry zero token");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            user_mode_resume_view_token == 0ul,
        "entry zero user mode resume token");
    EXPECT_TRUE(result.post_resume_observation_views[0].syscall_number ==
            512ul,
        "entry zero syscall number");
    EXPECT_TRUE(result.post_resume_observation_views[0].resume_slot == 4096ul,
        "entry zero resume slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].observation_slot ==
            5120ul,
        "entry zero observation slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            instruction_pointer_slot == 13ul,
        "entry zero instruction pointer slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            stack_pointer_slot == 14ul,
        "entry zero stack pointer slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].cpu_mode_slot == 15ul,
        "entry zero cpu mode slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            observation_epoch_slot == 16ul,
        "entry zero observation epoch slot");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_view_declared == 1,
        "post resume observation view declared");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_declared == 1,
        "post resume observation declared");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            instruction_pointer_observation_declared == 1,
        "instruction pointer observation declared");
    EXPECT_TRUE(strcmp(result.post_resume_observation_views[0].
            authority_status,
            "runtime-entry-post-resume-observation-view-authority-denied") ==
            0,
        "authority denied");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_view_planned == 0,
        "post resume observation view not planned");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_planned == 0,
        "post resume observation not planned");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            instruction_pointer_read_planned == 0,
        "instruction pointer read not planned");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            runtime_entry_post_resume_observation_view_allowed == 0,
        "entry post resume observation view denied");
    EXPECT_TRUE(result.post_resume_observation_views[0].
            post_resume_observation_allowed == 0,
        "entry post resume observation denied");
    EXPECT_TRUE(result.post_resume_observation_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.post_resume_observation_views[1].
            post_resume_observation_view_class,
            "entropy-runtime-entry-post-resume-observation-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.post_resume_observation_views[1].observation_slot ==
            5121ul,
        "entry one observation slot");
    return 0;
}

static int post_resume_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_post_resume_observation_view_count = 99u;
    request.runtime_entry_user_mode_resume_view_request.
        requested_user_mode_resume_view_count = 99u;
    EXPECT_TRUE(latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "post resume observation view evaluates cap");
    EXPECT_TRUE(result.post_resume_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_MAX,
        "post resume observation view capped");
    EXPECT_TRUE(strcmp(result.post_resume_observation_views[4].
            post_resume_observation_view_class,
            "reserved-runtime-entry-post-resume-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.post_resume_observation_views[4].
            post_resume_observation_view_token == 26004ul,
        "reserved post resume observation token");
    EXPECT_TRUE(result.post_resume_observation_views[4].
            user_mode_resume_view_token == 25004ul,
        "reserved user mode resume token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(latticra_kernel_runtime_entry_post_resume_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY POST RESUME OBSERVATION VIEW REPORT\n") !=
            0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view_status=runtime-entry-post-resume-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready\n") != 0,
        "user mode resume status emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_post_resume_observation_view_allowed=0\n") != 0,
        "post resume observation view authority emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_allowed=0\n") != 0,
        "post resume observation emitted");
    EXPECT_TRUE(strstr(report,
            "instruction_pointer_read_allowed=0\n") != 0,
        "instruction pointer read emitted");
    EXPECT_TRUE(strstr(report, "cpu_mode_read_allowed=0\n") != 0,
        "cpu mode read emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view[0].post_resume_observation_view_class=kernel-report-runtime-entry-post-resume-observation-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view[0].observation_slot=5120\n") != 0,
        "entry observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view[0].instruction_pointer_read_planned=0\n") != 0,
        "instruction pointer read plan emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view[0].runtime_entry_post_resume_observation_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "post_resume_observation_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
            0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_post_resume_observation_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (post_resume_observation_view_is_metadata_only() != 0) return 1;
    if (post_resume_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_post_resume_observation_view: ok");
    return 0;
}
