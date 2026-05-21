#ifndef LATTICRA_FEDORA_LIVE_SNAPSHOT_ADAPTER_H
#define LATTICRA_FEDORA_LIVE_SNAPSHOT_ADAPTER_H

#include <stddef.h>
#include "latticra/fedora_install_preflight_snapshot.h"
#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_FEDORA_LIVE_ADAPTER_PATH_MAX 256u
#define LATTICRA_FEDORA_LIVE_ADAPTER_TEXT_MAX 4096u
#define LATTICRA_FEDORA_LIVE_ADAPTER_REPORT_MAX 4096u
#define LATTICRA_FEDORA_LIVE_ADAPTER_LABEL_MAX 64u

typedef enum {
    LATTICRA_FEDORA_LIVE_ADAPTER_CAPTURED = 0,
    LATTICRA_FEDORA_LIVE_ADAPTER_PARTIAL = 1,
    LATTICRA_FEDORA_LIVE_ADAPTER_INVALID = 2
} latticra_fedora_live_adapter_status_t;

typedef struct {
    const char *os_release_path;
    size_t os_release_path_len;
    const char *local_rpm_path;
    size_t local_rpm_path_len;
    int host_install_requested;
    int operator_privilege_assertion;
    int network_required;
    int package_is_doc_only;
    int command_entrypoint_expected;
} latticra_fedora_live_snapshot_adapter_request_t;

typedef struct {
    latticra_fedora_live_adapter_status_t adapter_status;
    char adapter_status_label[LATTICRA_FEDORA_LIVE_ADAPTER_LABEL_MAX];
    char os_release_path[LATTICRA_FEDORA_LIVE_ADAPTER_PATH_MAX];
    char local_rpm_path[LATTICRA_FEDORA_LIVE_ADAPTER_PATH_MAX];
    char os_release_text[LATTICRA_FEDORA_LIVE_ADAPTER_TEXT_MAX];
    size_t os_release_text_len;
    latticra_fedora_snapshot_capture_input_t capture_input;
    latticra_fedora_snapshot_capture_result_t capture;
    int live_probe_performed;
    int os_release_read_attempted;
    int os_release_readable;
    int command_probe_performed;
    int local_rpm_probe_performed;
    int ostree_marker_probe_performed;
    int id_probe_performed;
    int rpm_command_present;
    int dnf_command_present;
    int rpmbuild_command_present;
    int rpmlint_command_present;
    int ostree_booted_marker_present;
    int local_rpm_readable;
    int running_as_root;
    int no_effect;
    int sudo_validation_allowed;
    int install_command_allowed;
    int package_build_allowed;
    int network_allowed;
    int host_mutation_performed;
    int host_install_performed;
    unsigned int evidence_level;
} latticra_fedora_live_snapshot_adapter_result_t;

const char *latticra_fedora_live_snapshot_adapter_status_label(
    latticra_fedora_live_adapter_status_t status);

latticra_status_t latticra_fedora_live_snapshot_adapter_capture(
    const latticra_fedora_live_snapshot_adapter_request_t *request,
    latticra_fedora_live_snapshot_adapter_result_t *result);

latticra_status_t latticra_fedora_live_snapshot_adapter_report(
    const latticra_fedora_live_snapshot_adapter_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
