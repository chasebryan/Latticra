#include "latticra/fedora_disposable_vm_effect_gate.h"

#include <assert.h>
#include <string.h>

static latticra_fedora_disposable_vm_effect_gate_input_t eligible_input(void)
{
    latticra_fedora_disposable_vm_effect_gate_input_t input;
    memset(&input, 0, sizeof(input));
    input.target_is_disposable_fedora_vm = 1;
    input.target_has_clean_snapshot = 1;
    input.target_has_recovery_path = 1;
    input.operator_consent_recorded = 1;
    input.local_rpm_built_from_current_tree = 1;
    input.rpm_name_is_latticra = 1;
    input.rpm_version_recorded = 1;
    input.rpm_payload_listing_recorded = 1;
    input.rpm_payload_is_documentation_only = 1;
    input.unexpected_runtime_surface_absent = 1;
    input.installroot_lifecycle_evidence_present = 1;
    input.post_removal_absence_evidence_present = 1;
    input.manual_host_dry_run_transcript_contract_present = 1;
    input.manual_host_rc_decision_classifier_present = 1;
    input.rpm_gate_allowed = 1;
    input.removal_rollback_ready = 1;
    return input;
}

static latticra_fedora_disposable_vm_effect_gate_result_t classify(
    latticra_fedora_disposable_vm_effect_gate_input_t input)
{
    latticra_fedora_disposable_vm_effect_gate_result_t result;
    assert(latticra_fedora_disposable_vm_effect_gate_classify(&input, &result) ==
           LATTICRA_STATUS_OK);
    assert(result.effect_gate_present == 1);
    assert(result.host_install_ready == 0);
    assert(result.production_installer_ready == 0);
    assert(result.fedora_distribution_ready == 0);
    assert(result.fedora_approval_claimed == 0);
    assert(result.daily_driver_allowed == 0);
    assert(result.production_host_allowed == 0);
    assert(result.immutable_host_allowed == 0);
    return result;
}

static void eligible_case_reports_eligible_without_readiness_claims(void)
{
    char report[LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_REPORT_MAX];
    latticra_fedora_disposable_vm_effect_gate_result_t result = classify(eligible_input());

    assert(result.status == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_ELIGIBLE);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NONE);
    assert(result.disposable_vm_effect_eligible == 1);
    assert(result.classifier_evaluated == 1);
    assert(result.evidence_level == 8u);

    assert(latticra_fedora_disposable_vm_effect_gate_report(&result, report, sizeof(report)) ==
           LATTICRA_STATUS_OK);
    assert(strstr(report, "FEDORA DISPOSABLE VM EFFECT GATE CLASSIFIER") != NULL);
    assert(strstr(report, "disposable_vm_effect_gate_status=eligible") != NULL);
    assert(strstr(report, "disposable_vm_effect_gate_denial=none") != NULL);
    assert(strstr(report, "disposable_vm_effect_eligible=1") != NULL);
    assert(strstr(report, "host_install_ready=0") != NULL);
    assert(strstr(report, "production_installer_ready=0") != NULL);
    assert(strstr(report, "fedora_distribution_ready=0") != NULL);
    assert(strstr(report, "fedora_approval_claimed=0") != NULL);
    assert(strstr(report, "daily_driver_allowed=0") != NULL);
    assert(strstr(report, "production_host_allowed=0") != NULL);
    assert(strstr(report, "immutable_host_allowed=0") != NULL);
    assert(strstr(report, "evidence_level=8") != NULL);
}

static void target_blocks_fail_closed(void)
{
    latticra_fedora_disposable_vm_effect_gate_input_t input;
    latticra_fedora_disposable_vm_effect_gate_result_t result;

    input = eligible_input();
    input.target_is_disposable_fedora_vm = 0;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_BLOCKED);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NOT_DISPOSABLE_VM);
    assert(result.disposable_vm_effect_eligible == 0);

    input = eligible_input();
    input.target_is_daily_driver = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DAILY_DRIVER);

    input = eligible_input();
    input.target_is_production_host = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_PRODUCTION_HOST);

    input = eligible_input();
    input.target_is_immutable_fedora = 1;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_IMMUTABLE_HOST);

    input = eligible_input();
    input.target_has_clean_snapshot = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_SNAPSHOT_MISSING);

    input = eligible_input();
    input.target_has_recovery_path = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RECOVERY_PATH_MISSING);

    input = eligible_input();
    input.operator_consent_recorded = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_OPERATOR_CONSENT_MISSING);
}

static void package_and_prior_evidence_blocks_fail_closed(void)
{
    latticra_fedora_disposable_vm_effect_gate_input_t input;
    latticra_fedora_disposable_vm_effect_gate_result_t result;

    input = eligible_input();
    input.local_rpm_built_from_current_tree = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE);

    input = eligible_input();
    input.rpm_name_is_latticra = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_NAME_MISMATCH);

    input = eligible_input();
    input.rpm_version_recorded = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_VERSION_MISSING);

    input = eligible_input();
    input.rpm_payload_listing_recorded = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_LISTING_MISSING);

    input = eligible_input();
    input.rpm_payload_is_documentation_only = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_NOT_DOC_ONLY);

    input = eligible_input();
    input.unexpected_runtime_surface_absent = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RUNTIME_SURFACE_PRESENT);

    input = eligible_input();
    input.installroot_lifecycle_evidence_present = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INSTALLROOT_EVIDENCE_MISSING);

    input = eligible_input();
    input.post_removal_absence_evidence_present = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_EVIDENCE_MISSING);

    input = eligible_input();
    input.manual_host_dry_run_transcript_contract_present = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_TRANSCRIPT_CONTRACT_MISSING);

    input = eligible_input();
    input.manual_host_rc_decision_classifier_present = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DECISION_CLASSIFIER_MISSING);

    input = eligible_input();
    input.rpm_gate_allowed = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_GATE_NOT_ALLOWED);

    input = eligible_input();
    input.removal_rollback_ready = 0;
    result = classify(input);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_ROLLBACK_NOT_READY);
}

static void invalid_and_api_error_cases_are_bounded(void)
{
    char tiny[4];
    latticra_fedora_disposable_vm_effect_gate_input_t input = eligible_input();
    latticra_fedora_disposable_vm_effect_gate_result_t result;

    input.rpm_gate_allowed = 2;
    result = classify(input);
    assert(result.status == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_INVALID);
    assert(result.denial == LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INVALID_INPUT);
    assert(result.disposable_vm_effect_eligible == 0);

    assert(latticra_fedora_disposable_vm_effect_gate_classify(NULL, &result) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_disposable_vm_effect_gate_classify(&input, NULL) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_disposable_vm_effect_gate_report(NULL, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_disposable_vm_effect_gate_report(&result, NULL, sizeof(tiny)) ==
           LATTICRA_STATUS_NULL_ARGUMENT);
    assert(latticra_fedora_disposable_vm_effect_gate_report(&result, tiny, sizeof(tiny)) ==
           LATTICRA_STATUS_BUFFER_TOO_SMALL);
}

int main(void)
{
    eligible_case_reports_eligible_without_readiness_claims();
    target_blocks_fail_closed();
    package_and_prior_evidence_blocks_fail_closed();
    invalid_and_api_error_cases_are_bounded();
    return 0;
}
