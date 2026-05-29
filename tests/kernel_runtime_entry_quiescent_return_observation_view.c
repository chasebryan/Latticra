#include "latticra/kernel_runtime_entry_quiescent_return_observation_view.h"

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
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_quiescent_return_observation_view_count == 4u,
        "default quiescent return observation view count");
    EXPECT_TRUE(request.runtime_entry_idle_return_observation_view_request.
            requested_idle_return_observation_view_count == 4u,
        "idle return observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_idle_return_observation_view_request.
            runtime_entry_process_return_observation_view_request.
            requested_process_return_observation_view_count == 4u,
        "process return observation view request preserved");
    return 0;
}

static int quiescent_return_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "quiescent return observation view evaluates");
    EXPECT_TRUE(strcmp(result.quiescent_return_observation_view_status,
            "runtime-entry-quiescent-return-observation-view-seed-ready") == 0,
        "quiescent return observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_idle_return_observation_view.
            idle_return_observation_view_status,
            "runtime-entry-idle-return-observation-view-seed-ready") == 0,
        "idle return observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_idle_return_observation_view.
            runtime_entry_process_return_observation_view.
            process_return_observation_view_status,
            "runtime-entry-process-return-observation-view-seed-ready") == 0,
        "process return observation view ready");
    EXPECT_TRUE(result.quiescent_return_observation_view_count == 4u,
        "quiescent return observation view count");
    EXPECT_TRUE(result.no_effect == 1, "no effect");
    EXPECT_TRUE(result.runtime_entry_quiescent_return_observation_view_allowed == 0,
        "quiescent return observation view denied");
    EXPECT_TRUE(result.quiescent_return_observation_allowed == 0,
        "quiescent return observation denied");
    EXPECT_TRUE(result.quiescent_return_allowed == 0,
        "quiescent return denied");
    EXPECT_TRUE(result.quiescent_state_read_allowed == 0,
        "quiescent state read denied");
    EXPECT_TRUE(result.idle_return_allowed == 0,
        "idle return denied");
    EXPECT_TRUE(result.persistence_allowed == 0,
        "persistence denied");
    EXPECT_TRUE(result.recovery_authority_allowed == 0,
        "recovery authority denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.quiescent_return_observation_views[0].
            process_label, "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.quiescent_return_observation_views[0].
            quiescent_return_observation_view_class,
            "kernel-report-runtime-entry-quiescent-return-observation-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_return_observation_view_token == 0ul,
        "entry zero quiescent token");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            idle_return_observation_view_token == 0ul,
        "entry zero idle token");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_slot == 9216ul,
        "entry zero quiescent slot");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_epoch_slot == 25ul,
        "entry zero quiescent epoch slot");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_reason_slot == 26ul,
        "entry zero quiescent reason slot");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_return_declared == 1,
        "quiescent return declared");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            quiescent_return_planned == 0,
        "quiescent return not planned");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].
            persistence_allowed == 0,
        "entry persistence denied");
    EXPECT_TRUE(result.quiescent_return_observation_views[0].no_effect == 1,
        "entry no effect");
    return 0;
}

static int quiescent_return_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_quiescent_return_observation_view_count = 99u;
    request.runtime_entry_idle_return_observation_view_request.
        requested_idle_return_observation_view_count = 99u;
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "quiescent return observation view evaluates cap");
    EXPECT_TRUE(result.quiescent_return_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_MAX,
        "quiescent return observation view capped");
    EXPECT_TRUE(strcmp(result.quiescent_return_observation_views[4].
            quiescent_return_observation_view_class,
            "reserved-runtime-entry-quiescent-return-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.quiescent_return_observation_views[4].
            quiescent_return_observation_view_token == 30004ul,
        "reserved quiescent return observation token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY QUIESCENT RETURN OBSERVATION VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready\n") != 0,
        "idle status emitted");
    EXPECT_TRUE(strstr(report,
            "quiescent_return_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report, "persistence_allowed=0\n") != 0,
        "persistence emitted");
    EXPECT_TRUE(strstr(report, "recovery_authority_allowed=0\n") != 0,
        "recovery emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=42\n") != 0,
        "evidence emitted");
    EXPECT_TRUE(strstr(report,
            "quiescent_return_observation_view[0].quiescent_slot=9216\n") != 0,
        "entry slot emitted");
    EXPECT_TRUE(strstr(report,
            "quiescent_return_observation_view[0].quiescent_return_allowed=0\n") != 0,
        "entry denied emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_quiescent_return_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_quiescent_return_observation_view_result_t
        result;
    char tiny[8];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(strcmp(result.quiescent_return_observation_view_status,
            "null-request") == 0,
        "null evaluate status");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_evaluate(
            &request, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_report(
            0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_report(
            &result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_quiescent_return_observation_view_report(
            &result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "tiny report cleared");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (quiescent_return_observation_view_is_metadata_only() != 0) return 1;
    if (quiescent_return_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_quiescent_return_observation_view: ok");
    return 0;
}
