#include "latticra/fedora_disposable_vm_effect_gate.h"

#include <stdio.h>
#include <string.h>

static int bit(int value) { return value == 0 || value == 1; }

const char *latticra_fedora_disposable_vm_effect_gate_status_label(
    latticra_fedora_disposable_vm_effect_gate_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_ELIGIBLE:
        return "eligible";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_BLOCKED:
        return "blocked";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_disposable_vm_effect_gate_denial_label(
    latticra_fedora_disposable_vm_effect_gate_denial_t denial)
{
    switch (denial) {
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NOT_DISPOSABLE_VM:
        return "not-disposable-fedora-vm";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DAILY_DRIVER:
        return "daily-driver-target";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_PRODUCTION_HOST:
        return "production-target";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_IMMUTABLE_HOST:
        return "immutable-fedora-target";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_SNAPSHOT_MISSING:
        return "snapshot-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RECOVERY_PATH_MISSING:
        return "recovery-path-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_OPERATOR_CONSENT_MISSING:
        return "operator-consent-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE:
        return "local-rpm-not-current-tree";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_NAME_MISMATCH:
        return "rpm-name-mismatch";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_VERSION_MISSING:
        return "rpm-version-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_LISTING_MISSING:
        return "rpm-payload-listing-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_NOT_DOC_ONLY:
        return "rpm-payload-not-documentation-only";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RUNTIME_SURFACE_PRESENT:
        return "unexpected-runtime-surface";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INSTALLROOT_EVIDENCE_MISSING:
        return "installroot-evidence-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_EVIDENCE_MISSING:
        return "post-removal-evidence-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_TRANSCRIPT_CONTRACT_MISSING:
        return "transcript-contract-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DECISION_CLASSIFIER_MISSING:
        return "decision-classifier-missing";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_GATE_NOT_ALLOWED:
        return "rpm-gate-not-allowed";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_ROLLBACK_NOT_READY:
        return "removal-rollback-not-ready";
    case LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INVALID_INPUT:
        return "invalid-classifier-input";
    default:
        return "unknown";
    }
}

static int valid_input(const latticra_fedora_disposable_vm_effect_gate_input_t *input)
{
    return bit(input->target_is_disposable_fedora_vm) &&
           bit(input->target_is_daily_driver) &&
           bit(input->target_is_production_host) &&
           bit(input->target_is_immutable_fedora) &&
           bit(input->target_has_clean_snapshot) &&
           bit(input->target_has_recovery_path) &&
           bit(input->operator_consent_recorded) &&
           bit(input->local_rpm_built_from_current_tree) &&
           bit(input->rpm_name_is_latticra) &&
           bit(input->rpm_version_recorded) &&
           bit(input->rpm_payload_listing_recorded) &&
           bit(input->rpm_payload_is_documentation_only) &&
           bit(input->unexpected_runtime_surface_absent) &&
           bit(input->installroot_lifecycle_evidence_present) &&
           bit(input->post_removal_absence_evidence_present) &&
           bit(input->manual_host_dry_run_transcript_contract_present) &&
           bit(input->manual_host_rc_decision_classifier_present) &&
           bit(input->rpm_gate_allowed) && bit(input->removal_rollback_ready);
}

static void mirror_input(
    const latticra_fedora_disposable_vm_effect_gate_input_t *input,
    latticra_fedora_disposable_vm_effect_gate_result_t *result)
{
    result->target_is_disposable_fedora_vm = input->target_is_disposable_fedora_vm;
    result->target_is_daily_driver = input->target_is_daily_driver;
    result->target_is_production_host = input->target_is_production_host;
    result->target_is_immutable_fedora = input->target_is_immutable_fedora;
    result->target_has_clean_snapshot = input->target_has_clean_snapshot;
    result->target_has_recovery_path = input->target_has_recovery_path;
    result->operator_consent_recorded = input->operator_consent_recorded;
    result->local_rpm_built_from_current_tree = input->local_rpm_built_from_current_tree;
    result->rpm_name_is_latticra = input->rpm_name_is_latticra;
    result->rpm_version_recorded = input->rpm_version_recorded;
    result->rpm_payload_listing_recorded = input->rpm_payload_listing_recorded;
    result->rpm_payload_is_documentation_only = input->rpm_payload_is_documentation_only;
    result->unexpected_runtime_surface_absent = input->unexpected_runtime_surface_absent;
    result->installroot_lifecycle_evidence_present = input->installroot_lifecycle_evidence_present;
    result->post_removal_absence_evidence_present = input->post_removal_absence_evidence_present;
    result->manual_host_dry_run_transcript_contract_present = input->manual_host_dry_run_transcript_contract_present;
    result->manual_host_rc_decision_classifier_present = input->manual_host_rc_decision_classifier_present;
    result->rpm_gate_allowed = input->rpm_gate_allowed;
    result->removal_rollback_ready = input->removal_rollback_ready;
}

static void block(
    latticra_fedora_disposable_vm_effect_gate_result_t *result,
    latticra_fedora_disposable_vm_effect_gate_denial_t denial)
{
    result->status = LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_BLOCKED;
    result->denial = denial;
    result->disposable_vm_effect_eligible = 0;
}

static void invalid(latticra_fedora_disposable_vm_effect_gate_result_t *result)
{
    result->status = LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_INVALID;
    result->denial = LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INVALID_INPUT;
    result->disposable_vm_effect_eligible = 0;
}

latticra_status_t latticra_fedora_disposable_vm_effect_gate_classify(
    const latticra_fedora_disposable_vm_effect_gate_input_t *input,
    latticra_fedora_disposable_vm_effect_gate_result_t *result)
{
    if (input == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));
    result->classifier_evaluated = 1;
    result->effect_gate_present = 1;
    result->host_install_ready = 0;
    result->production_installer_ready = 0;
    result->fedora_distribution_ready = 0;
    result->fedora_approval_claimed = 0;
    result->daily_driver_allowed = 0;
    result->production_host_allowed = 0;
    result->immutable_host_allowed = 0;
    result->evidence_level = 8u;

    if (!valid_input(input)) {
        invalid(result);
        return LATTICRA_STATUS_OK;
    }

    mirror_input(input, result);

    if (!result->target_is_disposable_fedora_vm) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NOT_DISPOSABLE_VM);
    } else if (result->target_is_daily_driver) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DAILY_DRIVER);
    } else if (result->target_is_production_host) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_PRODUCTION_HOST);
    } else if (result->target_is_immutable_fedora) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_IMMUTABLE_HOST);
    } else if (!result->target_has_clean_snapshot) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_SNAPSHOT_MISSING);
    } else if (!result->target_has_recovery_path) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RECOVERY_PATH_MISSING);
    } else if (!result->operator_consent_recorded) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_OPERATOR_CONSENT_MISSING);
    } else if (!result->local_rpm_built_from_current_tree) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE);
    } else if (!result->rpm_name_is_latticra) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_NAME_MISMATCH);
    } else if (!result->rpm_version_recorded) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_VERSION_MISSING);
    } else if (!result->rpm_payload_listing_recorded) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_LISTING_MISSING);
    } else if (!result->rpm_payload_is_documentation_only) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_NOT_DOC_ONLY);
    } else if (!result->unexpected_runtime_surface_absent) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RUNTIME_SURFACE_PRESENT);
    } else if (!result->installroot_lifecycle_evidence_present) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INSTALLROOT_EVIDENCE_MISSING);
    } else if (!result->post_removal_absence_evidence_present) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_EVIDENCE_MISSING);
    } else if (!result->manual_host_dry_run_transcript_contract_present) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_TRANSCRIPT_CONTRACT_MISSING);
    } else if (!result->manual_host_rc_decision_classifier_present) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DECISION_CLASSIFIER_MISSING);
    } else if (!result->rpm_gate_allowed) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_GATE_NOT_ALLOWED);
    } else if (!result->removal_rollback_ready) {
        block(result, LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_ROLLBACK_NOT_READY);
    } else {
        result->status = LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_ELIGIBLE;
        result->denial = LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NONE;
        result->disposable_vm_effect_eligible = 1;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_disposable_vm_effect_gate_report(
    const latticra_fedora_disposable_vm_effect_gate_result_t *result,
    char *buffer,
    size_t buffer_len)
{
    int n;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    n = snprintf(buffer, buffer_len,
        "FEDORA DISPOSABLE VM EFFECT GATE CLASSIFIER\n"
        "disposable_vm_effect_gate_status=%s\n"
        "disposable_vm_effect_gate_denial=%s\n"
        "target_is_disposable_fedora_vm=%d\n"
        "target_is_daily_driver=%d\n"
        "target_is_production_host=%d\n"
        "target_is_immutable_fedora=%d\n"
        "target_has_clean_snapshot=%d\n"
        "target_has_recovery_path=%d\n"
        "operator_consent_recorded=%d\n"
        "local_rpm_built_from_current_tree=%d\n"
        "rpm_name_is_latticra=%d\n"
        "rpm_version_recorded=%d\n"
        "rpm_payload_listing_recorded=%d\n"
        "rpm_payload_is_documentation_only=%d\n"
        "unexpected_runtime_surface_absent=%d\n"
        "installroot_lifecycle_evidence_present=%d\n"
        "post_removal_absence_evidence_present=%d\n"
        "manual_host_dry_run_transcript_contract_present=%d\n"
        "manual_host_rc_decision_classifier_present=%d\n"
        "rpm_gate_allowed=%d\n"
        "removal_rollback_ready=%d\n"
        "classifier_evaluated=%d\n"
        "effect_gate_present=%d\n"
        "disposable_vm_effect_eligible=%d\n"
        "host_install_ready=%d\n"
        "production_installer_ready=%d\n"
        "fedora_distribution_ready=%d\n"
        "fedora_approval_claimed=%d\n"
        "daily_driver_allowed=%d\n"
        "production_host_allowed=%d\n"
        "immutable_host_allowed=%d\n"
        "evidence_level=%u\n",
        latticra_fedora_disposable_vm_effect_gate_status_label(result->status),
        latticra_fedora_disposable_vm_effect_gate_denial_label(result->denial),
        result->target_is_disposable_fedora_vm,
        result->target_is_daily_driver,
        result->target_is_production_host,
        result->target_is_immutable_fedora,
        result->target_has_clean_snapshot,
        result->target_has_recovery_path,
        result->operator_consent_recorded,
        result->local_rpm_built_from_current_tree,
        result->rpm_name_is_latticra,
        result->rpm_version_recorded,
        result->rpm_payload_listing_recorded,
        result->rpm_payload_is_documentation_only,
        result->unexpected_runtime_surface_absent,
        result->installroot_lifecycle_evidence_present,
        result->post_removal_absence_evidence_present,
        result->manual_host_dry_run_transcript_contract_present,
        result->manual_host_rc_decision_classifier_present,
        result->rpm_gate_allowed,
        result->removal_rollback_ready,
        result->classifier_evaluated,
        result->effect_gate_present,
        result->disposable_vm_effect_eligible,
        result->host_install_ready,
        result->production_installer_ready,
        result->fedora_distribution_ready,
        result->fedora_approval_claimed,
        result->daily_driver_allowed,
        result->production_host_allowed,
        result->immutable_host_allowed,
        result->evidence_level);

    if (n < 0 || (size_t)n >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
