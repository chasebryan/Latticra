#ifndef LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_H
#define LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_H

#include <stddef.h>
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_REPORT_MAX 4096u

typedef enum {
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_ELIGIBLE = 0,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_BLOCKED = 1,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_INVALID = 2
} latticra_fedora_disposable_vm_effect_gate_status_t;

typedef enum {
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NONE = 0,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_NOT_DISPOSABLE_VM = 1,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DAILY_DRIVER = 2,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_PRODUCTION_HOST = 3,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_IMMUTABLE_HOST = 4,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_SNAPSHOT_MISSING = 5,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RECOVERY_PATH_MISSING = 6,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_OPERATOR_CONSENT_MISSING = 7,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_LOCAL_RPM_NOT_CURRENT_TREE = 8,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_NAME_MISMATCH = 9,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_VERSION_MISSING = 10,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_LISTING_MISSING = 11,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_PAYLOAD_NOT_DOC_ONLY = 12,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RUNTIME_SURFACE_PRESENT = 13,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INSTALLROOT_EVIDENCE_MISSING = 14,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_EVIDENCE_MISSING = 15,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_TRANSCRIPT_CONTRACT_MISSING = 16,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_DECISION_CLASSIFIER_MISSING = 17,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_RPM_GATE_NOT_ALLOWED = 18,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_REMOVAL_ROLLBACK_NOT_READY = 19,
    LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INVALID_INPUT = 20
} latticra_fedora_disposable_vm_effect_gate_denial_t;

typedef struct {
    int target_is_disposable_fedora_vm;
    int target_is_daily_driver;
    int target_is_production_host;
    int target_is_immutable_fedora;
    int target_has_clean_snapshot;
    int target_has_recovery_path;
    int operator_consent_recorded;
    int local_rpm_built_from_current_tree;
    int rpm_name_is_latticra;
    int rpm_version_recorded;
    int rpm_payload_listing_recorded;
    int rpm_payload_is_documentation_only;
    int unexpected_runtime_surface_absent;
    int installroot_lifecycle_evidence_present;
    int post_removal_absence_evidence_present;
    int manual_host_dry_run_transcript_contract_present;
    int manual_host_rc_decision_classifier_present;
    int rpm_gate_allowed;
    int removal_rollback_ready;
} latticra_fedora_disposable_vm_effect_gate_input_t;

typedef struct {
    latticra_fedora_disposable_vm_effect_gate_status_t status;
    latticra_fedora_disposable_vm_effect_gate_denial_t denial;
    int target_is_disposable_fedora_vm;
    int target_is_daily_driver;
    int target_is_production_host;
    int target_is_immutable_fedora;
    int target_has_clean_snapshot;
    int target_has_recovery_path;
    int operator_consent_recorded;
    int local_rpm_built_from_current_tree;
    int rpm_name_is_latticra;
    int rpm_version_recorded;
    int rpm_payload_listing_recorded;
    int rpm_payload_is_documentation_only;
    int unexpected_runtime_surface_absent;
    int installroot_lifecycle_evidence_present;
    int post_removal_absence_evidence_present;
    int manual_host_dry_run_transcript_contract_present;
    int manual_host_rc_decision_classifier_present;
    int rpm_gate_allowed;
    int removal_rollback_ready;
    int classifier_evaluated;
    int effect_gate_present;
    int disposable_vm_effect_eligible;
    int host_install_ready;
    int production_installer_ready;
    int fedora_distribution_ready;
    int fedora_approval_claimed;
    int daily_driver_allowed;
    int production_host_allowed;
    int immutable_host_allowed;
    unsigned int evidence_level;
} latticra_fedora_disposable_vm_effect_gate_result_t;

const char *latticra_fedora_disposable_vm_effect_gate_status_label(
    latticra_fedora_disposable_vm_effect_gate_status_t status);
const char *latticra_fedora_disposable_vm_effect_gate_denial_label(
    latticra_fedora_disposable_vm_effect_gate_denial_t denial);

latticra_status_t latticra_fedora_disposable_vm_effect_gate_classify(
    const latticra_fedora_disposable_vm_effect_gate_input_t *input,
    latticra_fedora_disposable_vm_effect_gate_result_t *result);

latticra_status_t latticra_fedora_disposable_vm_effect_gate_report(
    const latticra_fedora_disposable_vm_effect_gate_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
