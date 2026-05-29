#include "latticra/kernel_runtime_entry_recovery_plan_observation_view.h"

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
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(
        request.requested_recovery_plan_observation_view_count == 4u,
        "default recovery plan observation view count");
    EXPECT_TRUE(request.runtime_entry_recovery_boundary_observation_view_request.
            requested_recovery_boundary_observation_view_count == 4u,
        "recovery boundary observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_boundary_observation_view_request.
            runtime_entry_persistence_boundary_observation_view_request.
            requested_persistence_boundary_observation_view_count == 4u,
        "persistence boundary observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_boundary_observation_view_request.
            runtime_entry_persistence_boundary_observation_view_request.
            runtime_entry_quiescent_return_observation_view_request.
            runtime_entry_idle_return_observation_view_request.
            requested_idle_return_observation_view_count == 4u,
        "idle return observation view request preserved");
    return 0;
}

static int recovery_plan_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery plan observation view evaluates");
    EXPECT_TRUE(strcmp(result.recovery_plan_observation_view_status,
            "runtime-entry-recovery-plan-observation-view-seed-ready") == 0,
        "recovery plan observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_boundary_observation_view.
            recovery_boundary_observation_view_status,
            "runtime-entry-recovery-boundary-observation-view-seed-ready") == 0,
        "recovery boundary observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_boundary_observation_view.
            runtime_entry_persistence_boundary_observation_view.
            persistence_boundary_observation_view_status,
            "runtime-entry-persistence-boundary-observation-view-seed-ready") == 0,
        "persistence boundary observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_boundary_observation_view.
            runtime_entry_persistence_boundary_observation_view.
            runtime_entry_quiescent_return_observation_view.
            quiescent_return_observation_view_status,
            "runtime-entry-quiescent-return-observation-view-seed-ready") == 0,
        "quiescent return observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_boundary_observation_view.
            runtime_entry_persistence_boundary_observation_view.
            runtime_entry_quiescent_return_observation_view.
            runtime_entry_idle_return_observation_view.
            idle_return_observation_view_status,
            "runtime-entry-idle-return-observation-view-seed-ready") == 0,
        "idle return observation view ready");
    EXPECT_TRUE(result.recovery_plan_observation_view_count == 4u,
        "recovery plan observation view count");
    EXPECT_TRUE(result.no_effect == 1, "no effect");
    EXPECT_TRUE(result.runtime_entry_recovery_plan_observation_view_allowed == 0,
        "recovery plan observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_boundary_observation_view_allowed == 0,
        "recovery boundary observation view denied");
    EXPECT_TRUE(result.runtime_entry_persistence_boundary_observation_view_allowed == 0,
        "persistence boundary observation view denied");
    EXPECT_TRUE(result.runtime_entry_quiescent_return_observation_view_allowed == 0,
        "quiescent return observation view denied");
    EXPECT_TRUE(result.recovery_plan_observation_allowed == 0,
        "recovery plan observation denied");
    EXPECT_TRUE(result.recovery_boundary_observation_allowed == 0,
        "recovery boundary observation denied");
    EXPECT_TRUE(result.recovery_boundary_allowed == 0,
        "recovery boundary denied");
    EXPECT_TRUE(result.recovery_plan_allowed == 0,
        "recovery plan denied");
    EXPECT_TRUE(result.persistence_boundary_observation_allowed == 0,
        "persistence boundary observation denied");
    EXPECT_TRUE(result.persistence_boundary_allowed == 0,
        "persistence boundary denied");
    EXPECT_TRUE(result.persistence_commit_allowed == 0,
        "persistence commit denied");
    EXPECT_TRUE(result.persistence_allowed == 0,
        "persistence denied");
    EXPECT_TRUE(result.recovery_authority_allowed == 0,
        "recovery authority denied");
    EXPECT_TRUE(result.quiescent_return_allowed == 0,
        "quiescent return denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.recovery_plan_observation_views[0].
            process_label, "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.recovery_plan_observation_views[0].
            recovery_plan_observation_view_class,
            "kernel-report-runtime-entry-recovery-plan-observation-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_observation_view_token == 0ul,
        "entry zero recovery plan token");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_boundary_observation_view_token == 0ul,
        "entry zero recovery boundary token");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            persistence_boundary_observation_view_token == 0ul,
        "entry zero persistence boundary token");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            quiescent_return_observation_view_token == 0ul,
        "entry zero quiescent token");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_boundary_slot == 11264ul,
        "entry zero recovery boundary slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_observation_slot == 12288ul,
        "entry zero recovery plan observation slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            persistence_boundary_slot == 10240ul,
        "entry zero persistence boundary slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_epoch_slot == 30ul,
        "entry zero recovery epoch slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_reason_slot == 31ul,
        "entry zero recovery reason slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_slot == 32ul,
        "entry zero recovery plan slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_authority_slot == 33ul,
        "entry zero recovery authority slot");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            persistence_boundary_declared == 1,
        "persistence boundary declared");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_boundary_declared == 1,
        "recovery boundary declared");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_observation_declared == 1,
        "recovery plan observation declared");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_observation_planned == 0,
        "recovery plan observation not planned");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_boundary_planned == 0,
        "recovery boundary not planned");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_allowed == 0,
        "entry recovery plan denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_plan_observation_allowed == 0,
        "entry recovery plan observation denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            runtime_entry_recovery_boundary_observation_view_allowed == 0,
        "entry recovery boundary observation view denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            persistence_boundary_allowed == 0,
        "entry persistence boundary denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            persistence_commit_allowed == 0,
        "entry persistence commit denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].
            recovery_authority_allowed == 0,
        "entry recovery authority denied");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(result.recovery_plan_observation_views[0].evidence_level == 45u,
        "entry evidence level");
    return 0;
}

static int recovery_plan_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_recovery_plan_observation_view_count = 99u;
    request.runtime_entry_recovery_boundary_observation_view_request.
        requested_recovery_boundary_observation_view_count = 99u;
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery plan observation view evaluates cap");
    EXPECT_TRUE(result.recovery_plan_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_MAX,
        "recovery plan observation view capped");
    EXPECT_TRUE(strcmp(result.recovery_plan_observation_views[4].
            recovery_plan_observation_view_class,
            "reserved-runtime-entry-recovery-plan-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.recovery_plan_observation_views[4].
            recovery_plan_observation_view_token == 33004ul,
        "reserved recovery plan observation token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY RECOVERY PLAN OBSERVATION VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view_status=runtime-entry-recovery-plan-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_boundary_observation_view_status=runtime-entry-recovery-boundary-observation-view-seed-ready\n") != 0,
        "recovery boundary status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_persistence_boundary_observation_view_status=runtime-entry-persistence-boundary-observation-view-seed-ready\n") != 0,
        "persistence status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready\n") != 0,
        "quiescent status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_plan_observation_view_allowed=0\n") != 0,
        "recovery plan observation view denied emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_boundary_observation_view_allowed=0\n") != 0,
        "recovery boundary observation view denied emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_persistence_boundary_observation_view_allowed=0\n") != 0,
        "persistence boundary observation view denied emitted");
    EXPECT_TRUE(strstr(report, "recovery_plan_observation_allowed=0\n") != 0,
        "recovery plan observation emitted");
    EXPECT_TRUE(strstr(report, "recovery_boundary_allowed=0\n") != 0,
        "recovery boundary emitted");
    EXPECT_TRUE(strstr(report, "recovery_plan_allowed=0\n") != 0,
        "recovery plan emitted");
    EXPECT_TRUE(strstr(report, "persistence_boundary_allowed=0\n") != 0,
        "persistence boundary emitted");
    EXPECT_TRUE(strstr(report, "persistence_commit_allowed=0\n") != 0,
        "persistence commit emitted");
    EXPECT_TRUE(strstr(report, "recovery_authority_allowed=0\n") != 0,
        "recovery emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=45\n") != 0,
        "evidence emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].recovery_boundary_observation_view_token=0\n") != 0,
        "entry recovery boundary token emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].recovery_boundary_slot=11264\n") != 0,
        "entry slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].recovery_plan_observation_slot=12288\n") != 0,
        "entry plan observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].recovery_plan_observation_allowed=0\n") != 0,
        "entry plan observation denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].recovery_boundary_allowed=0\n") != 0,
        "entry denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_plan_observation_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_recovery_plan_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_plan_observation_view_result_t
        result;
    char tiny[8];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(strcmp(result.recovery_plan_observation_view_status,
            "null-request") == 0,
        "null evaluate status");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_evaluate(
            &request, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_report(
            0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_report(
            &result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_plan_observation_view_report(
            &result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "tiny report cleared");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (recovery_plan_observation_view_is_metadata_only() != 0) return 1;
    if (recovery_plan_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_recovery_plan_observation_view: ok");
    return 0;
}
