#ifndef LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_H
#define LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_H

#include <stddef.h>
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_REPORT_MAX 4096u

typedef enum {
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_CANDIDATE = 0,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_BLOCKED = 1,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_INVALID = 2
} latticra_fedora_manual_host_rc_decision_status_t;

typedef enum {
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NONE = 0,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NOT_DISPOSABLE_FEDORA_VM = 1,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_DAILY_DRIVER_TARGET = 2,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PRODUCTION_TARGET = 3,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_IMMUTABLE_FEDORA_TARGET = 4,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SNAPSHOT_MISSING = 5,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RECOVERY_PATH_MISSING = 6,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_OPERATOR_CONSENT_MISSING = 7,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE = 8,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_LISTING_MISSING = 9,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_PAYLOAD_NOT_DOCUMENTATION_ONLY = 10,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_UNEXPECTED_RUNTIME_SURFACE = 11,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INSTALLROOT_EVIDENCE_MISSING = 12,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POST_REMOVAL_EVIDENCE_MISSING = 13,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_PREFLIGHT_NOT_READY = 14,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_RPM_GATE_NOT_ALLOWED = 15,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_REMOVAL_ROLLBACK_NOT_READY = 16,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_NETWORK_REQUIRED = 17,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_SERVICE_BOUNDARY = 18,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_BOOT_BOUNDARY = 19,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_KERNEL_BOUNDARY = 20,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_POLICY_BOUNDARY = 21,
    LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INVALID_INPUT = 22
} latticra_fedora_manual_host_rc_decision_denial_t;

typedef struct {
    int target_is_disposable_fedora_vm;
    int target_is_daily_driver;
    int target_is_production_host;
    int target_is_immutable_fedora;
    int target_has_clean_snapshot;
    int target_has_recovery_path;
    int operator_consent_recorded;
    int local_rpm_built_from_current_tree;
    int rpm_payload_listing_recorded;
    int rpm_payload_is_documentation_only;
    int unexpected_runtime_surface_absent;
    int installroot_lifecycle_evidence_present;
    int post_removal_absence_evidence_present;
    int host_preflight_ready_local_rpm;
    int rpm_gate_allowed;
    int removal_rollback_ready;
    int network_requirement_detected;
    int service_boundary_detected;
    int boot_boundary_detected;
    int kernel_boundary_detected;
    int policy_boundary_detected;
} latticra_fedora_manual_host_rc_decision_input_t;

typedef struct {
    latticra_fedora_manual_host_rc_decision_status_t status;
    latticra_fedora_manual_host_rc_decision_denial_t denial;
    int target_is_disposable_fedora_vm;
    int target_is_daily_driver;
    int target_is_production_host;
    int target_is_immutable_fedora;
    int target_has_clean_snapshot;
    int target_has_recovery_path;
    int operator_consent_recorded;
    int local_rpm_built_from_current_tree;
    int rpm_payload_listing_recorded;
    int rpm_payload_is_documentation_only;
    int unexpected_runtime_surface_absent;
    int installroot_lifecycle_evidence_present;
    int post_removal_absence_evidence_present;
    int host_preflight_ready_local_rpm;
    int rpm_gate_allowed;
    int removal_rollback_ready;
    int network_requirement_detected;
    int service_boundary_detected;
    int boot_boundary_detected;
    int kernel_boundary_detected;
    int policy_boundary_detected;
    int classifier_evaluated;
    int manual_host_release_candidate_ready;
    int live_host_validation_completed;
    int host_change_performed;
    int sudo_invoked;
    int rpm_invoked;
    int dnf_invoked;
    int network_allowed;
    int service_operation_allowed;
    int boot_operation_allowed;
    int kernel_operation_allowed;
    int policy_operation_allowed;
    int production_installer_ready;
    int fedora_distribution_ready;
    int fedora_approval_claimed;
    unsigned int evidence_level;
} latticra_fedora_manual_host_rc_decision_result_t;

const char *latticra_fedora_manual_host_rc_decision_status_label(
    latticra_fedora_manual_host_rc_decision_status_t status);
const char *latticra_fedora_manual_host_rc_decision_denial_label(
    latticra_fedora_manual_host_rc_decision_denial_t denial);

latticra_status_t latticra_fedora_manual_host_rc_decision_classify(
    const latticra_fedora_manual_host_rc_decision_input_t *input,
    latticra_fedora_manual_host_rc_decision_result_t *result);

latticra_status_t latticra_fedora_manual_host_rc_decision_report(
    const latticra_fedora_manual_host_rc_decision_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
