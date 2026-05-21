#ifndef LATTICRA_FEDORA_HOST_INSTALL_PREFLIGHT_H
#define LATTICRA_FEDORA_HOST_INSTALL_PREFLIGHT_H

#include <stddef.h>
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_PREFLIGHT_LABEL_MAX 64u
#define LATTICRA_FEDORA_PREFLIGHT_REPORT_MAX 2048u

typedef enum {
    LATTICRA_FEDORA_PREFLIGHT_REPORT_ONLY = 0,
    LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM = 1,
    LATTICRA_FEDORA_PREFLIGHT_BLOCKED = 2,
    LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED = 3,
    LATTICRA_FEDORA_PREFLIGHT_INVALID = 4
} latticra_fedora_preflight_classification_t;

typedef enum {
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_NONE = 0,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_NOT_REQUESTED = 1,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_NON_FEDORA_HOST = 2,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_IMMUTABLE_HOST = 3,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_NETWORK_REQUIRED = 4,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_REQUIRED_TOOLING_MISSING = 5,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_LOCAL_RPM_MISSING = 6,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_PRIVILEGE_MISSING = 7,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT = 8,
    LATTICRA_FEDORA_PREFLIGHT_DENIAL_INVALID_SNAPSHOT = 9
} latticra_fedora_preflight_denial_t;

typedef struct {
    const char *os_id;
    size_t os_id_len;
    const char *os_id_like;
    size_t os_id_like_len;
    int host_install_requested;
    int immutable_host;
    int rpm_available;
    int dnf_available;
    int rpmbuild_available;
    int rpmlint_available;
    int local_rpm_present;
    int root_or_sudo_available;
    int network_required;
    int package_is_doc_only;
    int command_entrypoint_expected;
} latticra_fedora_host_install_preflight_snapshot_t;

typedef struct {
    latticra_fedora_preflight_classification_t classification;
    latticra_fedora_preflight_denial_t denial;
    char host_classification[LATTICRA_FEDORA_PREFLIGHT_LABEL_MAX];
    char install_lane[LATTICRA_FEDORA_PREFLIGHT_LABEL_MAX];
    int no_effect;
    int fedora_host;
    int mutable_fedora_host;
    int immutable_host;
    int rpm_available;
    int dnf_available;
    int rpmbuild_available;
    int rpmlint_available;
    int local_rpm_present;
    int local_only;
    int preflight_passed;
    int host_install_candidate;
    int host_install_performed;
    int host_mutation_performed;
    int network_allowed;
    unsigned int evidence_level;
} latticra_fedora_host_install_preflight_result_t;

const char *latticra_fedora_preflight_classification_label(
    latticra_fedora_preflight_classification_t classification);
const char *latticra_fedora_preflight_denial_label(
    latticra_fedora_preflight_denial_t denial);

latticra_status_t latticra_fedora_host_install_preflight_classify(
    const latticra_fedora_host_install_preflight_snapshot_t *snapshot,
    latticra_fedora_host_install_preflight_result_t *result);

latticra_status_t latticra_fedora_host_install_preflight_report(
    const latticra_fedora_host_install_preflight_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
