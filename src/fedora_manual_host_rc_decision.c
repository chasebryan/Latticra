#include "latticra/fedora_manual_host_rc_decision.h"

#include <stdio.h>
#include <string.h>

static int bit(int v) { return v == 0 || v == 1; }

const char *latticra_fedora_manual_host_rc_decision_status_label(
    latticra_fedora_manual_host_rc_decision_status_t status)
{
    switch (status) {
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_CANDIDATE:
        return "candidate";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_BLOCKED:
        return "blocked";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_INVALID:
        return "invalid";
    default:
        return "unknown";
    }
}

const char *latticra_fedora_manual_host_rc_decision_denial_label(
    latticra_fedora_manual_host_rc_decision_denial_t denial)
{
    switch (denial) {
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NONE:
        return "none";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NOT_DISPOSABLE_FEDORA_VM:
        return "not-disposable-fedora-vm";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_DAILY_DRIVER_TARGET:
        return "daily-driver-target";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PRODUCTION_TARGET:
        return "production-target";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_IMMUTABLE_FEDORA_TARGET:
        return "immutable-fedora-target";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SNAPSHOT_MISSING:
        return "snapshot-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RECOVERY_PATH_MISSING:
        return "recovery-path-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_OPERATOR_CONSENT_MISSING:
        return "operator-consent-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE:
        return "local-rpm-not-current-tree";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_LISTING_MISSING:
        return "rpm-payload-listing-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_NOT_DOCUMENTATION_ONLY:
        return "rpm-payload-not-documentation-only";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_UNEXPECTED_RUNTIME_SURFACE:
        return "unexpected-runtime-surface";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INSTALLROOT_EVIDENCE_MISSING:
        return "installroot-evidence-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POST_REMOVAL_EVIDENCE_MISSING:
        return "post-removal-evidence-missing";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PREFLIGHT_NOT_READY:
        return "preflight-not-ready";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_GATE_NOT_ALLOWED:
        return "rpm-gate-not-allowed";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_REMOVAL_ROLLBACK_NOT_READY:
        return "removal-rollback-not-ready";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NETWORK_REQUIRED:
        return "network-required";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SERVICE_BOUNDARY:
        return "service-boundary";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_BOOT_BOUNDARY:
        return "boot-boundary";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_KERNEL_BOUNDARY:
        return "kernel-boundary";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POLICY_BOUNDARY:
        return "policy-boundary";
    case LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INVALID_INPUT:
        return "invalid-classifier-input";
    default:
        return "unknown";
    }
}

static int valid_input(const latticra_fedora_manual_host_rc_decision_input_t *input)
{
    return bit(input->target_is_disposable_fedora_vm) &&
           bit(input->target_is_daily_driver) &&
           bit(input->target_is_production_host) &&
           bit(input->target_is_immutable_fedora) &&
           bit(input->target_has_clean_snapshot) &&
           bit(input->target_has_recovery_path) &&
           bit(input->operator_consent_recorded) &&
           bit(input->local_rpm_built_from_current_tree) &&
           bit(input->rpm_payload_listing_recorded) &&
           bit(input->rpm_payload_is_documentation_only) &&
           bit(input->unexpected_runtime_surface_absent) &&
           bit(input->installroot_lifecycle_evidence_present) &&
           bit(input->post_removal_absence_evidence_present) &&
           bit(input->host_preflight_ready_local_rpm) &&
           bit(input->rpm_gate_allowed) &&
           bit(input->removal_rollback_ready) &&
           bit(input->network_requirement_detected) &&
           bit(input->service_boundary_detected) &&
           bit(input->boot_boundary_detected) &&
           bit(input->kernel_boundary_detected) &&
           bit(input->policy_boundary_detected);
}

static void mirror_input(
    const latticra_fedora_manual_host_rc_decision_input_t *input,
    latticra_fedora_manual_host_rc_decision_result_t *result)
{
    result->target_is_disposable_fedora_vm = input->target_is_disposable_fedora_vm;
    result->target_is_daily_driver = input->target_is_daily_driver;
    result->target_is_production_host = input->target_is_production_host;
    result->target_is_immutable_fedora = input->target_is_immutable_fedora;
    result->target_has_clean_snapshot = input->target_has_clean_snapshot;
    result->target_has_recovery_path = input->target_has_recovery_path;
    result->operator_consent_recorded = input->operator_consent_recorded;
    result->local_rpm_built_from_current_tree = input->local_rpm_built_from_current_tree;
    result->rpm_payload_listing_recorded = input->rpm_payload_listing_recorded;
    result->rpm_payload_is_documentation_only = input->rpm_payload_is_documentation_only;
    result->unexpected_runtime_surface_absent = input->unexpected_runtime_surface_absent;
    result->installroot_lifecycle_evidence_present = input->installroot_lifecycle_evidence_present;
    result->post_removal_absence_evidence_present = input->post_removal_absence_evidence_present;
    result->host_preflight_ready_local_rpm = input->host_preflight_ready_local_rpm;
    result->rpm_gate_allowed = input->rpm_gate_allowed;
    result->removal_rollback_ready = input->removal_rollback_ready;
    result->network_requirement_detected = input->network_requirement_detected;
    result->service_boundary_detected = input->service_boundary_detected;
    result->boot_boundary_detected = input->boot_boundary_detected;
    result->kernel_boundary_detected = input->kernel_boundary_detected;
    result->policy_boundary_detected = input->policy_boundary_detected;
}

static void invalidate(latticra_fedora_manual_host_rc_decision_result_t *result)
{
    result->status = LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_INVALID;
    result->denial = LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INVALID_INPUT;
    result->manual_host_release_candidate_ready = 0;
}

static void block(
    latticra_fedora_manual_host_rc_decision_result_t *result,
    latticra_fedora_manual_host_rc_decision_denial_t denial)
{
    result->status = LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_BLOCKED;
    result->denial = denial;
    result->manual_host_release_candidate_ready = 0;
}

latticra_status_t latticra_fedora_manual_host_rc_decision_classify(
    const latticra_fedora_manual_host_rc_decision_input_t *input,
    latticra_fedora_manual_host_rc_decision_result_t *result)
{
    if (input == NULL || result == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(result, 0, sizeof(*result));
    result->classifier_evaluated = 1;
    result->live_host_validation_completed = 0;
    result->host_change_performed = 0;
    result->sudo_invoked = 0;
    result->rpm_invoked = 0;
    result->dnf_invoked = 0;
    result->network_allowed = 0;
    result->service_operation_allowed = 0;
    result->boot_operation_allowed = 0;
    result->kernel_operation_allowed = 0;
    result->policy_operation_allowed = 0;
    result->production_installer_ready = 0;
    result->fedora_distribution_ready = 0;
    result->fedora_approval_claimed = 0;
    result->evidence_level = 7u;

    if (!valid_input(input)) {
        invalidate(result);
        return LATTICRA_STATUS_OK;
    }

    mirror_input(input, result);

    if (!result->target_is_disposable_fedora_vm) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NOT_DISPOSABLE_FEDORA_VM);
    } else if (result->target_is_daily_driver) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_DAILY_DRIVER_TARGET);
    } else if (result->target_is_production_host) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PRODUCTION_TARGET);
    } else if (result->target_is_immutable_fedora) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_IMMUTABLE_FEDORA_TARGET);
    } else if (!result->target_has_clean_snapshot) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SNAPSHOT_MISSING);
    } else if (!result->target_has_recovery_path) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RECOVERY_PATH_MISSING);
    } else if (!result->operator_consent_recorded) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_OPERATOR_CONSENT_MISSING);
    } else if (!result->local_rpm_built_from_current_tree) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE);
    } else if (!result->rpm_payload_listing_recorded) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_LISTING_MISSING);
    } else if (!result->rpm_payload_is_documentation_only) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_NOT_DOCUMENTATION_ONLY);
    } else if (!result->unexpected_runtime_surface_absent) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_UNEXPECTED_RUNTIME_SURFACE);
    } else if (!result->installroot_lifecycle_evidence_present) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INSTALLROOT_EVIDENCE_MISSING);
    } else if (!result->post_removal_absence_evidence_present) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POST_REMOVAL_EVIDENCE_MISSING);
    } else if (!result->host_preflight_ready_local_rpm) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PREFLIGHT_NOT_READY);
    } else if (!result->rpm_gate_allowed) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_GATE_NOT_ALLOWED);
    } else if (!result->removal_rollback_ready) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_REMOVAL_ROLLBACK_NOT_READY);
    } else if (result->network_requirement_detected) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NETWORK_REQUIRED);
    } else if (result->service_boundary_detected) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SERVICE_BOUNDARY);
    } else if (result->boot_boundary_detected) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_BOOT_BOUNDARY);
    } else if (result->kernel_boundary_detected) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_KERNEL_BOUNDARY);
    } else if (result->policy_boundary_detected) {
        block(result, LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POLICY_BOUNDARY);
    } else {
        result->status = LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_CANDIDATE;
        result->denial = LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NONE;
        result->manual_host_release_candidate_ready = 1;
    }

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_fedora_manual_host_rc_decision_report(
    const latticra_fedora_manual_host_rc_decision_result_t *result,
    char *buffer,
    size_t buffer_len)
{
    int n;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    n = snprintf(buffer, buffer_len,
        "FEDORA MANUAL HOST RC DECISION CLASSIFIER\n"
        "manual_host_rc_status=%s\n"
        "manual_host_rc_denial=%s\n"
        "target_is_disposable_fedora_vm=%d\n"
        "target_is_daily_driver=%d\n"
        "target_is_production_host=%d\n"
        "target_is_immutable_fedora=%d\n"
        "target_has_clean_snapshot=%d\n"
        "target_has_recovery_path=%d\n"
        "operator_consent_recorded=%d\n"
        "local_rpm_built_from_current_tree=%d\n"
        "rpm_payload_listing_recorded=%d\n"
        "rpm_payload_is_documentation_only=%d\n"
        "unexpected_runtime_surface_absent=%d\n"
        "installroot_lifecycle_evidence_present=%d\n"
        "post_removal_absence_evidence_present=%d\n"
        "host_preflight_ready_local_rpm=%d\n"
        "rpm_gate_allowed=%d\n"
        "removal_rollback_ready=%d\n"
        "network_requirement_detected=%d\n"
        "service_boundary_detected=%d\n"
        "boot_boundary_detected=%d\n"
        "kernel_boundary_detected=%d\n"
        "policy_boundary_detected=%d\n"
        "classifier_evaluated=%d\n"
        "manual_host_release_candidate_ready=%d\n"
        "live_host_validation_completed=%d\n"
        "host_change_performed=%d\n"
        "sudo_invoked=%d\n"
        "rpm_invoked=%d\n"
        "dnf_invoked=%d\n"
        "network_allowed=%d\n"
        "service_operation_allowed=%d\n"
        "boot_operation_allowed=%d\n"
        "kernel_operation_allowed=%d\n"
        "policy_operation_allowed=%d\n"
        "production_installer_ready=%d\n"
        "fedora_distribution_ready=%d\n"
        "fedora_approval_claimed=%d\n"
        "evidence_level=%u\n",
        latticra_fedora_manual_host_rc_decision_status_label(result->status),
        latticra_fedora_manual_host_rc_decision_denial_label(result->denial),
        result->target_is_disposable_fedora_vm,
        result->target_is_daily_driver,
        result->target_is_production_host,
        result->target_is_immutable_fedora,
        result->target_has_clean_snapshot,
        result->target_has_recovery_path,
        result->operator_consent_recorded,
        result->local_rpm_built_from_current_tree,
        result->rpm_payload_listing_recorded,
        result->rpm_payload_is_documentation_only,
        result->unexpected_runtime_surface_absent,
        result->installroot_lifecycle_evidence_present,
        result->post_removal_absence_evidence_present,
        result->host_preflight_ready_local_rpm,
        result->rpm_gate_allowed,
        result->removal_rollback_ready,
        result->network_requirement_detected,
        result->service_boundary_detected,
        result->boot_boundary_detected,
        result->kernel_boundary_detected,
        result->policy_boundary_detected,
        result->classifier_evaluated,
        result->manual_host_release_candidate_ready,
        result->live_host_validation_completed,
        result->host_change_performed,
        result->sudo_invoked,
        result->rpm_invoked,
        result->dnf_invoked,
        result->network_allowed,
        result->service_operation_allowed,
        result->boot_operation_allowed,
        result->kernel_operation_allowed,
        result->policy_operation_allowed,
        result->production_installer_ready,
        result->fedora_distribution_ready,
        result->fedora_approval_claimed,
        result->evidence_level);

    if (n < 0 || (size_t)n >= buffer_len) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
