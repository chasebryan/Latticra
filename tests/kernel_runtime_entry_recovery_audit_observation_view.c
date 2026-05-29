#include "latticra/kernel_runtime_entry_recovery_audit_observation_view.h"

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
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_recovery_audit_observation_view_count == 4u,
        "default recovery audit observation view count");
    EXPECT_TRUE(request.runtime_entry_recovery_closeout_observation_view_request.
            requested_recovery_closeout_observation_view_count == 4u,
        "recovery closeout observation view request preserved");
    EXPECT_TRUE(request.runtime_entry_recovery_closeout_observation_view_request.
            runtime_entry_recovery_outcome_observation_view_request.
            requested_recovery_outcome_observation_view_count == 4u,
        "recovery outcome observation view request preserved");
    return 0;
}

static int recovery_audit_observation_view_is_metadata_only(void) {
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery audit observation view evaluates");
    EXPECT_TRUE(strcmp(result.recovery_audit_observation_view_status,
            "runtime-entry-recovery-audit-observation-view-seed-ready") == 0,
        "recovery audit observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_closeout_observation_view.
            recovery_closeout_observation_view_status,
            "runtime-entry-recovery-closeout-observation-view-seed-ready") == 0,
        "recovery closeout observation view ready");
    EXPECT_TRUE(strcmp(result.runtime_entry_recovery_closeout_observation_view.
            runtime_entry_recovery_outcome_observation_view.
            recovery_outcome_observation_view_status,
            "runtime-entry-recovery-outcome-observation-view-seed-ready") == 0,
        "recovery outcome observation view ready");
    EXPECT_TRUE(result.recovery_audit_observation_view_count == 4u,
        "recovery audit observation view count");
    EXPECT_TRUE(result.no_effect == 1, "no effect");
    EXPECT_TRUE(result.runtime_entry_recovery_audit_observation_view_allowed == 0,
        "recovery audit observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_closeout_observation_view_allowed == 0,
        "recovery closeout observation view denied");
    EXPECT_TRUE(result.runtime_entry_recovery_outcome_observation_view_allowed == 0,
        "recovery outcome observation view denied");
    EXPECT_TRUE(result.recovery_audit_observation_allowed == 0,
        "recovery audit observation denied");
    EXPECT_TRUE(result.recovery_audit_allowed == 0,
        "recovery audit denied");
    EXPECT_TRUE(result.recovery_closeout_allowed == 0,
        "recovery closeout denied");
    EXPECT_TRUE(result.recovery_outcome_allowed == 0,
        "recovery outcome denied");
    EXPECT_TRUE(result.persistence_allowed == 0,
        "persistence denied");
    EXPECT_TRUE(result.recovery_authority_allowed == 0,
        "recovery authority denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");
    EXPECT_TRUE(result.evidence_level == 49u, "result evidence level");

    EXPECT_TRUE(strcmp(result.recovery_audit_observation_views[0].
            process_label, "kernel-report-process-metadata") == 0,
        "entry zero process");
    EXPECT_TRUE(strcmp(result.recovery_audit_observation_views[0].
            recovery_audit_observation_view_class,
            "kernel-report-runtime-entry-recovery-audit-observation-view") == 0,
        "entry zero class");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_observation_view_token == 0ul,
        "entry zero recovery audit token");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_closeout_observation_view_token == 0ul,
        "entry zero recovery closeout token");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_outcome_observation_view_token == 0ul,
        "entry zero recovery outcome token");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_observation_slot == 16384ul,
        "entry zero recovery audit observation slot");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_closeout_observation_slot == 15360ul,
        "entry zero recovery closeout observation slot");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_slot == 37ul,
        "entry zero recovery audit slot");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_closeout_slot == 36ul,
        "entry zero recovery closeout slot");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_observation_declared == 1,
        "recovery audit observation declared");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_declared == 1,
        "recovery audit declared");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_observation_planned == 0,
        "recovery audit observation not planned");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            runtime_entry_recovery_audit_observation_view_allowed == 0,
        "entry recovery audit observation view denied");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_observation_allowed == 0,
        "entry recovery audit observation denied");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            recovery_audit_allowed == 0,
        "entry recovery audit denied");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].no_effect == 1,
        "entry no effect");
    EXPECT_TRUE(result.recovery_audit_observation_views[0].
            evidence_level == 49u,
        "entry evidence level");
    return 0;
}

static int recovery_audit_observation_view_caps_count(void) {
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        result;

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_recovery_audit_observation_view_count = 99u;
    request.runtime_entry_recovery_closeout_observation_view_request.
        requested_recovery_closeout_observation_view_count = 99u;
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "recovery audit observation view evaluates cap");
    EXPECT_TRUE(result.recovery_audit_observation_view_count ==
            LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_MAX,
        "recovery audit observation view capped");
    EXPECT_TRUE(strcmp(result.recovery_audit_observation_views[4].
            recovery_audit_observation_view_class,
            "reserved-runtime-entry-recovery-audit-observation-view") == 0,
        "reserved class");
    EXPECT_TRUE(result.recovery_audit_observation_views[4].
            recovery_audit_observation_view_token == 37004ul,
        "reserved recovery audit observation token");
    return 0;
}

static int report_is_deterministic(void) {
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        result;
    char report[
        LATTICRA_KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_REPORT_MAX];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &request, &result) == LATTICRA_STATUS_OK,
        "evaluate for report");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_report(
            &result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL RUNTIME ENTRY RECOVERY AUDIT OBSERVATION VIEW REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready\n") != 0,
        "status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_closeout_observation_view_status=runtime-entry-recovery-closeout-observation-view-seed-ready\n") != 0,
        "recovery closeout status emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_outcome_observation_view_status=runtime-entry-recovery-outcome-observation-view-seed-ready\n") != 0,
        "recovery outcome status emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view_count=4\n") != 0,
        "count emitted");
    EXPECT_TRUE(strstr(report,
            "runtime_entry_recovery_audit_observation_view_allowed=0\n") != 0,
        "recovery audit observation view denied emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_observation_allowed=0\n") != 0,
        "recovery audit observation emitted");
    EXPECT_TRUE(strstr(report, "recovery_audit_allowed=0\n") != 0,
        "recovery audit emitted");
    EXPECT_TRUE(strstr(report, "recovery_closeout_allowed=0\n") != 0,
        "recovery closeout emitted");
    EXPECT_TRUE(strstr(report, "evidence_level=49\n") != 0,
        "evidence emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view[0].recovery_audit_observation_slot=16384\n") != 0,
        "entry audit observation slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view[0].recovery_audit_slot=37\n") != 0,
        "entry audit slot emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view[0].recovery_audit_observation_allowed=0\n") != 0,
        "entry audit observation denied emitted");
    EXPECT_TRUE(strstr(report,
            "recovery_audit_observation_view[0].no_effect=1\n") != 0,
        "entry no effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_runtime_entry_recovery_audit_observation_view_request_t
        request;
    latticra_kernel_runtime_entry_recovery_audit_observation_view_result_t
        result;
    char tiny[8];

    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(strcmp(result.recovery_audit_observation_view_status,
            "null-request") == 0,
        "null evaluate status");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_default_request(
            &request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_evaluate(
            &request, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_report(
            0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_report(
            &result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_kernel_runtime_entry_recovery_audit_observation_view_report(
            &result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "tiny report cleared");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (recovery_audit_observation_view_is_metadata_only() != 0) return 1;
    if (recovery_audit_observation_view_caps_count() != 0) return 1;
    if (report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_runtime_entry_recovery_audit_observation_view: ok");
    return 0;
}
