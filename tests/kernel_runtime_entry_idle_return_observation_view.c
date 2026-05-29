#include "latticra/kernel_runtime_entry_idle_return_observation_view.h"

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
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_idle_return_observation_view_count == 4u,
        "default idle return observation view count");
    EXPECT_TRUE(request.runtime_entry_process_return_observation_view_request.
            requested_process_return_observation_view_count == 4u,
        "process return observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_process_return_observation_view_request.
            runtime_entry_scheduler_return_observation_view_request.
            requested_scheduler_return_observation_view_count == 4u,
        "scheduler return observation view request preserved");
    return 0;
}

static int idle_return_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "idle return observation view evaluates");
    EXPECT_TRUE(strcmp(result.idle_return_observation_view_status,
            "runtime-entry-idle-return-observation-view-seed-ready") == 0,
        "idle return observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_process_return_observation_view.
            process_return_observation_view_status,
            "runtime-entry-process-return-observation-view-seed-ready") == 0,
        "process return observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_process_return_observation_view.
            runtime_entry_scheduler_return_observation_view.
            scheduler_return_observation_view_status,
            "runtime-entry-scheduler-return-observation-view-seed-ready") ==
            0,
        "scheduler return observation view ready");
    EXPECT_TRUE(result.idle_return_observation_view_count == 4u,
        "idle return observation view count");
    EXPECT_TRUE(result.no_effect == 1,
        "idle return observation view no effect");
    EXPECT_TRUE(result.runtime_entry_idle_return_observation_view_allowed ==
            0,
        "idle return observation view denied");
    EXPECT_TRUE(
        result.runtime_entry_process_return_observation_view_allowed == 0,
        "process return observation view denied");
    EXPECT_TRUE(
        result.runtime_entry_scheduler_return_observation_view_allowed == 0,
        "scheduler return observation view denied");
    EXPECT_TRUE(result.process_return_observation_allowed == 0,
        "process return observation denied");
    EXPECT_TRUE(result.process_return_allowed == 0,
        "process return denied");
    EXPECT_TRUE(result.idle_return_observation_allowed == 0,
        "idle return observation denied");
    EXPECT_TRUE(result.idle_return_allowed == 0,
        "idle return denied");
    EXPECT_TRUE(result.idle_state_read_allowed == 0,
        "idle state read denied");
    EXPECT_TRUE(result.process_state_read_allowed == 0,
        "process state read denied");
    EXPECT_TRUE(result.scheduler_execution_allowed == 0,
        "scheduler execution denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.idle_return_observation_views[0].
            process_label,
            "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.idle_return_observation_views[0].
            idle_return_observation_view_class,
            "kernel-report-runtime-entry-idle-return-observation-view") ==
            0,
        "entry zero class");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_observation_view_token == 0ul,
        "entry zero idle return token");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_observation_view_token == 0ul,
        "entry zero process return token");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            scheduler_return_observation_view_token == 0ul,
        "entry zero scheduler return token");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            scheduler_return_slot == 6144ul,
        "entry zero scheduler return slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_slot == 7168ul,
        "entry zero process return slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_slot == 8192ul,
        "entry zero idle return slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_epoch_slot == 22ul,
        "entry zero idle return epoch slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_reason_slot == 23ul,
        "entry zero idle return reason slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_state_slot == 24ul,
        "entry zero idle state slot");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_observation_view_declared == 1,
        "process return observation view declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_observation_view_declared == 1,
        "idle return observation view declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_observation_declared == 1,
        "process return observation declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_declared == 1,
        "process return declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_observation_declared == 1,
        "idle return observation declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_declared == 1,
        "idle return declared");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_state_observation_declared == 1,
        "idle state observation declared");
    EXPECT_TRUE(strcmp(result.idle_return_observation_views[0].
            authority_status,
            "runtime-entry-idle-return-observation-view-authority-denied") ==
            0,
        "authority denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_observation_view_planned == 0,
        "idle return observation view not planned");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_planned == 0,
        "idle return not planned");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_planned == 0,
        "process return not planned");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_state_read_planned == 0,
        "idle state read not planned");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            runtime_entry_idle_return_observation_view_allowed == 0,
        "entry idle return observation view denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            runtime_entry_process_return_observation_view_allowed == 0,
        "entry process return observation view denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            process_return_observation_allowed == 0,
        "entry process return observation denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_state_read_allowed == 0,
        "entry idle state read denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].
            idle_return_observation_allowed == 0,
        "entry idle return observation denied");
    EXPECT_TRUE(result.idle_return_observation_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(strcmp(result.idle_return_observation_views[1].
            idle_return_observation_view_class,
            "entropy-runtime-entry-idle-return-observation-view") == 0,
        "entropy class");
    EXPECT_TRUE(result.idle_return_observation_views[1].
            idle_return_slot == 8193ul,
        "entry one idle return slot");
    return 0;
}

static int idle_return_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_idle_return_observation_view_count = 99u;
    request.runtime_entry_process_return_observation_view_request.
        requested_process_return_observation_view_count = 99u;
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "idle return observation view evaluates cap");
    EXPECT_TRUE(result.idle_return_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_MAX,
        "idle return observation view capped");
    EXPECT_TRUE(strcmp(result.idle_return_observation_views[4].
            idle_return_observation_view_class,
            "reserved-runtime-entry-idle-return-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.idle_return_observation_views[4].
            idle_return_observation_view_token == 29004ul,
        "reserved idle return observation token");
    EXPECT_TRUE(result.idle_return_observation_views[4].
            process_return_observation_view_token == 28004ul,
        "reserved process return observation token");
    EXPECT_TRUE(result.idle_return_observation_views[4].
            scheduler_return_observation_view_token == 27004ul,
        "reserved scheduler return observation token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_idle_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY IDLE RETURN OBSERVATION VIEW REPORT\n") !=
            0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready\n") != 0,
        "process return status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_scheduler_return_observation_view_status=runtime-entry-scheduler-return-observation-view-seed-ready\n") != 0,
        "scheduler return status emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_idle_return_observation_view_allowed=0\n") != 0,
        "idle return observation view authority emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_process_return_observation_view_allowed=0\n") != 0,
        "process return observation view authority emitted");
    EXPECT_TRUE(strstr(report,
            "process_return_observation_allowed=0\n") != 0,
        "process return observation emitted");
    EXPECT_TRUE(strstr(report, "process_return_allowed=0\n") != 0,
        "process return emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_allowed=0\n") != 0,
        "idle return observation emitted");
    EXPECT_TRUE(strstr(report, "idle_return_allowed=0\n") != 0,
        "idle return emitted");
    EXPECT_TRUE(strstr(report, "idle_state_read_allowed=0\n") != 0,
        "idle state read emitted");
    EXPECT_TRUE(strstr(report, "process_state_read_allowed=0\n") != 0,
        "process state read emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].idle_return_observation_view_class=kernel-report-runtime-entry-idle-return-observation-view\n") != 0,
        "entry class emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].process_return_slot=7168\n") != 0,
        "entry process return slot emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].idle_return_slot=8192\n") != 0,
        "entry idle return slot emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].idle_state_read_planned=0\n") != 0,
        "idle state read plan emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].process_state_read_planned=0\n") != 0,
        "process state read plan emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].runtime_entry_idle_return_observation_view_allowed=0\n") != 0,
        "entry authority emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].runtime_entry_process_return_observation_view_allowed=0\n") != 0,
        "entry process authority emitted");
    EXPECT_TRUE(strstr(report,
            "idle_return_observation_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_idle_return_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_evaluate(
            0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_report(0,
            report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_report(
            &result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_idle_return_observation_view_report(
            &result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (idle_return_observation_view_is_metadata_only() != 0) return 1;
    if (idle_return_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    printf("kernel_runtime_entry_idle_return_observation_view: ok\n");
    return 0;
}
