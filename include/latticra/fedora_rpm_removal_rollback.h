#ifndef LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_H
#define LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_H

#include <stddef.h>
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PACKAGE_MAX 64u
#define LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_REPORT_MAX 4096u

typedef enum {
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_READY = 0,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIED = 1,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL = 2,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_INVALID = 3
} latticra_fedora_rpm_removal_rollback_status_t;

typedef enum {
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NONE = 0,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OPERATOR_CONFIRMATION_MISSING = 1,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NAME_MISMATCH = 2,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_IDENTITY_MISSING = 3,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_QUERY_NOT_READY = 4,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_PACKAGE_NOT_INSTALLED = 5,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_OWNED_FILE_LIST_MISSING = 6,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_README_OWNERSHIP_MISSING = 7,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_UNEXPECTED_RUNTIME_SURFACE_PRESENT = 8,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POST_REMOVAL_CHECK_MISSING = 9,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_FAILURE_REPORT_MISSING = 10,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_NETWORK_REQUIRED = 11,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_SERVICE_OPERATION_REQUESTED = 12,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_BOOT_OPERATION_REQUESTED = 13,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_KERNEL_OPERATION_REQUESTED = 14,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_POLICY_OPERATION_REQUESTED = 15,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_DENIAL_INVALID_INPUT = 16
} latticra_fedora_rpm_removal_rollback_denial_t;

typedef enum {
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_NONE = 0,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_PACKAGE_INSTALLED_OWNERSHIP_UNKNOWN = 1,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_OWNED_FILES_PRESENT_PACKAGE_QUERY_FAILED = 2,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_RUNTIME_SURFACE_PRESENT_BEFORE_REMOVAL = 3,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_ABSENCE_CHECK_NOT_READY = 4,
    LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PARTIAL_UNKNOWN_HOST_STATE = 5
} latticra_fedora_rpm_removal_rollback_partial_t;

typedef struct {
    int operator_removal_confirmation;
    const char *package_name;
    size_t package_name_len;
    int package_identity_present;
    int package_query_ready;
    int installed_package_detected;
    int owned_file_list_available;
    int readme_owned_by_package;
    int unexpected_runtime_surface_absent;
    int post_removal_absence_check_planned;
    int failure_report_planned;
    int network_required;
    int service_operation_requested;
    int boot_operation_requested;
    int kernel_operation_requested;
    int policy_operation_requested;
} latticra_fedora_rpm_removal_rollback_input_t;

typedef struct {
    latticra_fedora_rpm_removal_rollback_status_t status;
    latticra_fedora_rpm_removal_rollback_denial_t denial;
    latticra_fedora_rpm_removal_rollback_partial_t partial_state;
    char package_name[LATTICRA_FEDORA_RPM_REMOVAL_ROLLBACK_PACKAGE_MAX];
    int operator_removal_confirmation;
    int package_identity_present;
    int package_query_ready;
    int installed_package_detected;
    int owned_file_list_available;
    int readme_owned_by_package;
    int unexpected_runtime_surface_absent;
    int post_removal_absence_check_planned;
    int failure_report_planned;
    int network_required;
    int service_operation_requested;
    int boot_operation_requested;
    int kernel_operation_requested;
    int policy_operation_requested;
    int classifier_evaluated;
    int removal_allowed;
    int rollback_planned;
    int partial_failure_report_required;
    int removal_performed;
    int host_mutation_performed;
    int network_allowed;
    int service_operation_allowed;
    int boot_operation_allowed;
    int kernel_operation_allowed;
    int policy_operation_allowed;
    unsigned int evidence_level;
} latticra_fedora_rpm_removal_rollback_result_t;

const char *latticra_fedora_rpm_removal_rollback_status_label(
    latticra_fedora_rpm_removal_rollback_status_t status);
const char *latticra_fedora_rpm_removal_rollback_denial_label(
    latticra_fedora_rpm_removal_rollback_denial_t denial);
const char *latticra_fedora_rpm_removal_rollback_partial_label(
    latticra_fedora_rpm_removal_rollback_partial_t partial_state);

latticra_status_t latticra_fedora_rpm_removal_rollback_classify(
    const latticra_fedora_rpm_removal_rollback_input_t *input,
    latticra_fedora_rpm_removal_rollback_result_t *result);

latticra_status_t latticra_fedora_rpm_removal_rollback_report(
    const latticra_fedora_rpm_removal_rollback_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
