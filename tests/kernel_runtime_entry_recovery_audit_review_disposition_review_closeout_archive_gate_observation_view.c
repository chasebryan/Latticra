#include "latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.h"

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
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(
        request.requested_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count == 4u,
        "default recovery audit review disposition review observation view count");
    EXPECT_TRUE(request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
            requested_recovery_audit_review_disposition_review_closeout_observation_view_count == 4u,
        "recovery audit review disposition review observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
            requested_recovery_audit_review_disposition_observation_view_count == 4u,
        "recovery audit review disposition observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
            runtime_entry_recovery_audit_review_observation_view_request.
            requested_recovery_audit_review_observation_view_count == 4u,
        "recovery audit review observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
            runtime_entry_recovery_audit_review_observation_view_request.
            runtime_entry_recovery_audit_observation_view_request.
            requested_recovery_audit_observation_view_count == 4u,
        "recovery audit observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
            runtime_entry_recovery_audit_review_observation_view_request.
            runtime_entry_recovery_audit_observation_view_request.
            runtime_entry_recovery_closeout_observation_view_request.
            requested_recovery_closeout_observation_view_count == 4u,
        "recovery closeout observation view request preserved");
    return 0;
}

static int recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery audit review disposition review observation view evaluates");
    EXPECT_TRUE(strcmp(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status,
            "runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready") == 0,
        "recovery audit review disposition review observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            recovery_audit_review_disposition_review_closeout_observation_view_status,
            "runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready") == 0,
        "recovery audit review disposition observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            recovery_audit_review_disposition_observation_view_status,
            "runtime-entry-recovery-audit-review-disposition-observation-view-seed-ready") == 0,
        "recovery audit review disposition observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view.
            recovery_audit_review_observation_view_status,
            "runtime-entry-recovery-audit-review-observation-view-seed-ready") == 0,
        "recovery audit review observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.
            runtime_entry_recovery_audit_review_disposition_review_observation_view.
            runtime_entry_recovery_audit_review_disposition_observation_view.
            runtime_entry_recovery_audit_review_observation_view.
            runtime_entry_recovery_audit_observation_view.
            recovery_audit_observation_view_status,
            "runtime-entry-recovery-audit-observation-view-seed-ready") == 0,
        "recovery audit observation view ready");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count == 4u,
        "recovery audit review disposition review observation view count");
    EXPECT_TRUE(result.no_effect == 1, "no effect");
    EXPECT_TRUE(result.runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed == 0,
        "recovery audit review disposition review observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed == 0,
        "recovery audit review disposition observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_audit_review_observation_view_allowed == 0,
        "recovery audit review observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_audit_observation_view_allowed == 0,
        "recovery audit observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_closeout_observation_view_allowed == 0,
        "recovery closeout observation view denied");
    EXPECT_TRUE(result.recovery_audit_review_observation_allowed == 0,
        "recovery audit review observation denied");
    EXPECT_TRUE(result.recovery_audit_review_allowed == 0,
        "recovery audit review denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed == 0,
        "recovery audit review disposition review observation denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_allowed == 0,
        "recovery audit review disposition review denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_observation_allowed == 0,
        "recovery audit review disposition observation denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_allowed == 0,
        "recovery audit review disposition denied");
    EXPECT_TRUE(result.recovery_audit_observation_allowed == 0,
        "recovery audit observation denied");
    EXPECT_TRUE(result.recovery_audit_allowed == 0,
        "recovery audit denied");
    EXPECT_TRUE(result.recovery_authority_allowed == 0,
        "recovery authority denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");
    EXPECT_TRUE(result.evidence_level == 54u, "result evidence level");

    EXPECT_TRUE(strcmp(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            process_label, "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_class,
            "kernel-report-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_token == 0ul,
        "entry zero recovery audit review disposition token");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_observation_view_token == 0ul,
        "entry zero recovery audit review disposition observation token");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_observation_view_token == 0ul,
        "entry zero recovery audit review token");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_observation_view_token == 0ul,
        "entry zero recovery audit token");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_slot == 21504ul,
        "entry zero recovery audit review disposition review observation slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_observation_slot == 20480ul,
        "entry zero recovery audit review disposition observation slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_observation_slot == 17408ul,
        "entry zero recovery audit review observation slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_observation_slot == 16384ul,
        "entry zero recovery audit observation slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_slot == 42ul,
        "entry zero recovery audit review disposition review closeout slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_slot == 41ul,
        "entry zero recovery audit review disposition review slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_slot == 39ul,
        "entry zero recovery audit review disposition slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_slot == 38ul,
        "entry zero recovery audit review slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_slot == 37ul,
        "entry zero recovery audit slot");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_declared == 1,
        "recovery audit review disposition review observation declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_declared == 1,
        "recovery audit review disposition review closeout declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_declared == 1,
        "recovery audit review disposition review declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_observation_declared == 1,
        "recovery audit review disposition observation declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_declared == 1,
        "recovery audit review disposition declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_observation_declared == 1,
        "recovery audit review observation declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_declared == 1,
        "recovery audit review declared");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_planned == 0,
        "recovery audit review disposition review observation not planned");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_planned == 0,
        "recovery audit review disposition review closeout not planned");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_planned == 0,
        "recovery audit review disposition review not planned");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_observation_planned == 0,
        "recovery audit review disposition observation not planned");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_observation_planned == 0,
        "recovery audit review observation not planned");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed == 0,
        "entry recovery audit review disposition review observation view denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed == 0,
        "entry recovery audit review disposition observation view denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            runtime_entry_recovery_audit_review_observation_view_allowed == 0,
        "entry recovery audit review observation view denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            runtime_entry_recovery_audit_observation_view_allowed == 0,
        "entry recovery audit observation view denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed == 0,
        "entry recovery audit review disposition review observation denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_archive_gate_allowed == 0,
        "entry recovery audit review disposition review closeout denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_allowed == 0,
        "entry recovery audit review disposition review denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_review_closeout_observation_allowed == 0,
        "entry recovery audit review disposition observation denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_disposition_allowed == 0,
        "entry recovery audit review disposition denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_observation_allowed == 0,
        "entry recovery audit review observation denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            recovery_audit_review_allowed == 0,
        "entry recovery audit review denied");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[0].
            evidence_level == 54u,
        "entry evidence level");
    return 0;
}

static int recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count = 99u;
    request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
        requested_recovery_audit_review_disposition_review_closeout_observation_view_count = 99u;
    request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
        requested_recovery_audit_review_disposition_observation_view_count = 99u;
    request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
        runtime_entry_recovery_audit_review_observation_view_request.
        requested_recovery_audit_review_observation_view_count = 99u;
    request.runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_request.
        runtime_entry_recovery_audit_review_disposition_review_observation_view_request.
            runtime_entry_recovery_audit_review_disposition_observation_view_request.
        runtime_entry_recovery_audit_review_observation_view_request.
        runtime_entry_recovery_audit_observation_view_request.
        requested_recovery_audit_observation_view_count = 99u;
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery audit review disposition review observation view evaluates cap");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_MAX,
        "recovery audit review disposition review observation view capped");
    EXPECT_TRUE(strcmp(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[4].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_class,
            "reserved-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_views[4].
            recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_token == 42004ul,
        "reserved recovery audit review disposition review observation token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY RECOVERY AUDIT REVIEW DISPOSITION REVIEW CLOSEOUT ARCHIVE GATE OBSERVATION VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready\n") != 0,
        "recovery audit review disposition status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_review_observation_view_status=runtime-entry-recovery-audit-review-observation-view-seed-ready\n") != 0,
        "recovery audit review status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready\n") != 0,
        "recovery audit status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0\n") != 0,
        "recovery audit review disposition review observation view denied emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0\n") != 0,
        "recovery audit review disposition observation view denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_observation_allowed=0\n") != 0,
        "recovery audit review observation emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_review_allowed=0\n") != 0,
        "recovery audit review emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0\n") != 0,
        "recovery audit review disposition review observation emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0\n") != 0,
        "recovery audit review disposition review closeout emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_allowed=0\n") != 0,
        "recovery audit review disposition review emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_observation_allowed=0\n") != 0,
        "recovery audit review disposition observation emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_allowed=0\n") != 0,
        "recovery audit review disposition emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_allowed=0\n") != 0,
        "recovery audit emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=54\n") != 0,
        "evidence emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_observation_slot=21504\n") != 0,
        "entry audit review disposition review observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_observation_slot=20480\n") != 0,
        "entry audit review disposition observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_observation_slot=17408\n") != 0,
        "entry audit review observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_slot=42\n") != 0,
        "entry audit review disposition review closeout slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_slot=41\n") != 0,
        "entry audit review disposition review slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_slot=39\n") != 0,
        "entry audit review disposition slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_slot=38\n") != 0,
        "entry audit review slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_declared=1\n") != 0,
        "entry audit review disposition review closeout declared emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_planned=0\n") != 0,
        "entry audit review disposition review closeout not planned emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0\n") != 0,
        "entry audit review disposition review observation denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0\n") != 0,
        "entry audit review disposition review closeout denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_allowed=0\n") != 0,
        "entry audit review disposition review denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_review_closeout_observation_allowed=0\n") != 0,
        "entry audit review disposition observation denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_disposition_allowed=0\n") != 0,
        "entry audit review disposition denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].recovery_audit_review_observation_allowed=0\n") != 0,
        "entry audit review observation denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_review_disposition_review_closeout_archive_gate_observation_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_result_t
        result;
    char tiny[8];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(strcmp(result.recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status,
            "null-request") == 0,
        "null evaluate status");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_evaluate(
            &request, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_report(
            0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_report(
            &result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_report(
            &result, tiny, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_is_metadata_only() != 0) {
        return 1;
    }
    if (recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view: ok");
    return 0;
}
