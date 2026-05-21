#ifndef LATTICRA_FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_H
#define LATTICRA_FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_H

#include <stddef.h>
#include "latticra/fedora_host_install_preflight.h"
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_SNAPSHOT_OS_ID_MAX 64u
#define LATTICRA_FEDORA_SNAPSHOT_OS_ID_LIKE_MAX 128u
#define LATTICRA_FEDORA_SNAPSHOT_PATH_MAX 256u
#define LATTICRA_FEDORA_SNAPSHOT_LABEL_MAX 64u
#define LATTICRA_FEDORA_SNAPSHOT_REPORT_MAX 4096u

typedef enum {
    LATTICRA_FEDORA_SNAPSHOT_CAPTURED = 0,
    LATTICRA_FEDORA_SNAPSHOT_PARTIAL = 1,
    LATTICRA_FEDORA_SNAPSHOT_INVALID = 2
} latticra_fedora_snapshot_capture_status_t;

typedef struct {
    const char *os_release_text;
    size_t os_release_text_len;
    int os_release_readable;
    int host_install_requested;
    int ostree_booted_marker_present;
    int rpm_command_present;
    int dnf_command_present;
    int rpmbuild_command_present;
    int rpmlint_command_present;
    const char *local_rpm_path;
    size_t local_rpm_path_len;
    int local_rpm_readable;
    int running_as_root;
    int operator_privilege_assertion;
    int network_required;
    int package_is_doc_only;
    int command_entrypoint_expected;
} latticra_fedora_snapshot_capture_input_t;

typedef struct {
    latticra_fedora_snapshot_capture_status_t capture_status;
    char capture_status_label[LATTICRA_FEDORA_SNAPSHOT_LABEL_MAX];
    char os_id[LATTICRA_FEDORA_SNAPSHOT_OS_ID_MAX];
    char os_id_like[LATTICRA_FEDORA_SNAPSHOT_OS_ID_LIKE_MAX];
    char local_rpm_path[LATTICRA_FEDORA_SNAPSHOT_PATH_MAX];
    latticra_fedora_host_install_preflight_snapshot_t snapshot;
    latticra_fedora_host_install_preflight_result_t preflight;
    int no_effect;
    int os_release_read_allowed;
    int command_probe_allowed;
    int local_rpm_probe_allowed;
    int sudo_validation_allowed;
    int install_command_allowed;
    int package_build_allowed;
    int network_allowed;
    int host_mutation_performed;
    int host_install_performed;
    int snapshot_forwarded_to_classifier;
    unsigned int evidence_level;
} latticra_fedora_snapshot_capture_result_t;

const char *latticra_fedora_snapshot_capture_status_label(
    latticra_fedora_snapshot_capture_status_t status);

latticra_status_t latticra_fedora_install_preflight_snapshot_capture(
    const latticra_fedora_snapshot_capture_input_t *input,
    latticra_fedora_snapshot_capture_result_t *result);

latticra_status_t latticra_fedora_install_preflight_snapshot_report(
    const latticra_fedora_snapshot_capture_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
