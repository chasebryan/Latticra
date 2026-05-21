#include "latticra/fedora_manual_host_rc_decision.h"

#include <assert.h>
#include <string.h>

static latticra_fedora_manual_host_rc_decision_input_t candidate_input(void)
{
    latticra_fedora_manual_host_rc_decision_input_t input;
    memset(&input, 0, sizeof(input));
    input.target_is_disposable_fedora_vm = 1;
    input.target_is_daily_driver = 0;
    input.target_is_production_host = 0;
    input.target_is_immutable_fedora = 0;
    input.target_has_clean_snapshot = 1;
    input.target_has_recovery_path = 1;
    input.operator_consent_recorded = 1;
    input.local_rpm_built_from_current_tree = 1;
    input.rpm_payload_listing_recorded = 1;
    input.rpm_payload_is_documentation_only = 1;
    input.unexpected_runtime_surface_absent = 1;
    input.installroot_lifecycle_evidence_present = 1;
    input.post_removal_absence_evidence_present = 1;
    input.host_preflight_ready_local_rpm = 1;
    input.rpm_gate_allowed = 1;
    input.removal_rollback_ready = 1;
    return input;
}

static latticra_fedora_manual_host_rc_decision_result_t classify(
    latticra_fedora_manual_host_rc_decision_input_t input)
{
    latticra_fedora_manual_host_rc_decision_result_t result;
    assert(latticra_fedora_manual_host_rc_decision_classify(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.live_host_validation_completed == 0);
    assert(result.host_change_performed == 0);
    assert(result.sudo_invoked == 0);
    assert(result.rpm_invoked == 0);
    assert(result.dnf_invoked == 0);
    assert(result.network_allowed == 0);
    assert(result.service_operation_allowed == 0);
    assert(result.boot_operation_allowed == 0);
    assert(result.kernel_operation_allowed == 0);
    assert(result.policy_operation_allowed == 0);
    assert(result.production_installer_ready == 0);
    assert(result.fedora_distribution_ready == 0);
    assert(result.fedora_approval_claimed == 0);
    return result;
}

static void candidate_case_reports_candidate_without_mutation(void)
{
    char report[LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_REPORT_MAX];
    latticra_fedora_manual_host_rc_decision_result_t result = classify(candidate_input());

    assert(result.status == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_CANDIDATE);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NONE);
    assert(result.manual_host_release_candidate_ready == 1);
    assert(result.classifier_evaluated == 1);
    assert(result.evidence_level == 7u);

    assert(latticra_fedora_manual_host_rc_decision_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA MANUAL HOST RC DECISION CLASSIFIER") != NULL);
    assert(strstr(report, "manual_host_rc_status=candidate") != NULL);
    assert(strstr(report, "manual_host_rc_denial=none") != NULL);
    assert(strstr(report, "target_is_disposable_fedora_vm=1") != NULL);
    assert(strstr(report, "target_is_daily_driver=0") != NULL);
    assert(strstr(report, "target_is_production_host=0") != NULL);
    assert(strstr(report, "target_is_immutable_fedora=0") != NULL);
    assert(strstr(report, "manual_host_release_candidate_ready=1") != NULL);
    assert(strstr(report, "live_host_validation_completed=0") != NULL);
    assert(strstr(report, "host_change_performed=0") != NULL);
    assert(strstr(report, "sudo_invoked=0") != NULL);
    assert(strstr(report, "rpm_invoked=0") != NULL);
    assert(strstr(report, "dnf_invoked=0") != NULL);
    assert(strstr(report, "network_allowed=0") != NULL);
    assert(strstr(report, "service_operation_allowed=0") != NULL);
    assert(strstr(report, "boot_operation_allowed=0") != NULL);
    assert(strstr(report, "kernel_operation_allowed=0") != NULL);
    assert(strstr(report, "policy_operation_allowed=0") != NULL);
    assert(strstr(report, "production_installer_ready=0") != NULL);
    assert(strstr(report, "fedora_distribution_ready=0") != NULL);
    assert(strstr(report, "fedora_approval_claimed=0") != NULL);
    assert(strstr(report, "evidence_level=7") != NULL);
}

static void target_safety_blocks_fail_closed(void)
{
    latticra_fedora_manual_host_rc_decision_input_t input;
    latticra_fedora_manual_host_rc_decision_result_t result;

    input = candidate_input();
    input.target_is_disposable_fedora_vm = 0;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_BLOCKED);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NOT_DISPOSABLE_FEDORA_VM);
    assert(result.manual_host_release_candidate_ready == 0);

    input = candidate_input();
    input.target_is_daily_driver = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_DAILY_DRIVER_TARGET);

    input = candidate_input();
    input.target_is_production_host = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PRODUCTION_TARGET);

    input = candidate_input();
    input.target_is_immutable_fedora = 1;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_IMMUTABLE_FEDORA_TARGET);

    input = candidate_input();
    input.target_has_clean_snapshot = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SNAPSHOT_MISSING);

    input = candidate_input();
    input.target_has_recovery_path = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RECOVERY_PATH_MISSING);

    input = candidate_input();
    input.operator_consent_recorded = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_OPERATOR_CONSENT_MISSING);
}

static void evidence_blocks_fail_closed(void)
{
    latticra_fedora_manual_host_rc_decision_input_t input;
    latticra_fedora_manual_host_rc_decision_result_t result;

    input = candidate_input();
    input.local_rpm_built_from_current_tree = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE);

    input = candidate_input();
    input.rpm_payload_listing_recorded = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_LISTING_MISSING);

    input = candidate_input();
    input.rpm_payload_is_documentation_only = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_NOT_DOCUMENTATION_ONLY);

    input = candidate_input();
    input.unexpected_runtime_surface_absent = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_UNEXPECTED_RUNTIME_SURFACE);

    input = candidate_input();
    input.installroot_lifecycle_evidence_present = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INSTALLROOT_EVIDENCE_MISSING);

    input = candidate_input();
    input.post_removal_absence_evidence_present = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POST_REMOVAL_EVIDENCE_MISSING);

    input = candidate_input();
    input.host_preflight_ready_local_rpm = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PREFLIGHT_NOT_READY);

    input = candidate_input();
    input.rpm_gate_allowed = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_GATE_NOT_ALLOWED);

    input = candidate_input();
    input.removal_rollback_ready = 0;
    result = classify(input);
    assert(result.denial ==
           LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_REMOVAL_ROLLBACK_NOT_READY);
}

static void boundary_blocks_fail_closed(void)
{
    latticra_fedora_manual_host_rc_decision_input_t input;
    latticra_fedora_manual_host_rc_decision_result_t result;

    input = candidate_input();
    input.network_requirement_detected = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NETWORK_REQUIRED);
    assert(result.network_allowed == 0);

    input = candidate_input();
    input.service_boundary_detected = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SERVICE_BOUNDARY);

    input = candidate_input();
    input.boot_boundary_detected = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_BOOT_BOUNDARY);

    input = candidate_input();
    input.kernel_boundary_detected = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_KERNEL_BOUNDARY);

    input = candidate_input();
    input.policy_boundary_detected = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POLICY_BOUNDARY);
}

static void invalid_and_api_error_cases_are_bounded(void)
{
    char tiny[4];
    latticra_fedora_manual_host_rc_decision_input_t input = candidate_input();
    latticra_fedora_manual_host_rc_decision_result_t result;

    input.rpm_gate_allowed = 2;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_INVALID);
    assert(result.denial == LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INVALID_INPUT);
    assert(result.manual_host_release_candidate_ready == 0);

    assert(latticra_fedora_manual_host_rc_decision_classify(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_manual_host_rc_decision_classify(&input, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_manual_host_rc_decision_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_manual_host_rc_decision_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_manual_host_rc_decision_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    candidate_case_reports_candidate_without_mutation();
    target_safety_blocks_fail_closed();
    evidence_blocks_fail_closed();
    boundary_blocks_fail_closed();
    invalid_and_api_error_cases_are_bounded();
    return 0;
}
