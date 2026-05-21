#ifndef LATTICRA_FEDORA_RPM_GATE_H
#define LATTICRA_FEDORA_RPM_GATE_H

#include <stddef.h>
#include "latticra/fedora_host_install_preflight.h"
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_RPM_GATE_PATH_MAX 256u
#define LATTICRA_FEDORA_RPM_GATE_LABEL_MAX 64u
#define LATTICRA_FEDORA_RPM_GATE_REPORT_MAX 4096u

typedef enum {
    LATTICRA_FEDORA_RPM_GATE_ALLOWED = 0,
    LATTICRA_FEDORA_RPM_GATE_DENIED = 1,
    LATTICRA_FEDORA_RPM_GATE_INVALID = 2
} latticra_fedora_rpm_gate_status_t;

typedef enum {
    LATTICRA_FEDORA_RPM_GATE_DENIAL_NONE = 0,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_NOT_FEDORA_HOST = 1,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_IMMUTABLE_FEDORA_HOST = 2,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_LOCAL_RPM_MISSING = 3,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_PRIVILEGE_MISSING = 4,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_NETWORK_REQUIRED = 5,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_OPERATOR_CONFIRMATION_MISSING = 6,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_DRY_RUN_MISSING = 7,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_ROLLBACK_PLAN_MISSING = 8,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_NOT_READY = 9,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_PREFLIGHT_DENIED = 10,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_LIVE_PROBE_MISSING = 11,
    LATTICRA_FEDORA_RPM_GATE_DENIAL_INVALID_INPUT = 12
} latticra_fedora_rpm_gate_denial_t;

typedef struct {
    int fedora_host;
    int mutable_fedora_host;
    int immutable_host;
    int local_rpm_present;
    const char *local_rpm_path;
    size_t local_rpm_path_len;
    int root_or_sudo_available;
    int network_required;
    int operator_install_confirmation;
    int dry_run_passed;
    int rollback_or_remove_plan_present;
    latticra_fedora_preflight_classification_t preflight_classification;
    latticra_fedora_preflight_denial_t preflight_denial;
    int snapshot_captured;
    int live_probe_performed;
} latticra_fedora_rpm_gate_input_t;

typedef struct {
    latticra_fedora_rpm_gate_status_t gate_status;
    latticra_fedora_rpm_gate_denial_t denial;
    char local_rpm_path[LATTICRA_FEDORA_RPM_GATE_PATH_MAX];
    int fedora_host;
    int mutable_fedora_host;
    int immutable_host;
    int local_rpm_present;
    int root_or_sudo_available;
    int network_required;
    int operator_install_confirmation;
    int dry_run_passed;
    int rollback_or_remove_plan_present;
    latticra_fedora_preflight_classification_t preflight_classification;
    latticra_fedora_preflight_denial_t preflight_denial;
    int snapshot_captured;
    int live_probe_performed;
    int gate_evaluated;
    int install_mutation_allowed;
    int install_mutation_performed;
    int host_mutation_performed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_fedora_rpm_gate_result_t;

const char *latticra_fedora_rpm_gate_status_label(
    latticra_fedora_rpm_gate_status_t status);
const char *latticra_fedora_rpm_gate_denial_label(
    latticra_fedora_rpm_gate_denial_t denial);

latticra_status_t latticra_fedora_rpm_gate_classify(
    const latticra_fedora_rpm_gate_input_t *input,
    latticra_fedora_rpm_gate_result_t *result);

latticra_status_t latticra_fedora_rpm_gate_report(
    const latticra_fedora_rpm_gate_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
