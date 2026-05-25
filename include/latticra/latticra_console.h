#ifndef LATTICRA_CONSOLE_H
#define LATTICRA_CONSOLE_H

#include "latticra/kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_CONSOLE_ID_MAX 64u
#define LATTICRA_CONSOLE_LABEL_MAX 64u
#define LATTICRA_CONSOLE_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_CONSOLE_REPORT_MAX 20000u

typedef enum {
    LATTICRA_CONSOLE_PROFILE_HOSTED_REFERENCE = 0,
    LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED = 1,
    LATTICRA_CONSOLE_PROFILE_HOST_EMBEDDED = 2,
    LATTICRA_CONSOLE_PROFILE_OS_BASE_PLANNING = 3
} latticra_console_profile_t;

typedef struct {
    char console_id[LATTICRA_CONSOLE_ID_MAX];
    latticra_console_profile_t profile;
    int panel_installable;
    int host_embeddable;
    const char *source_identity;
    size_t source_identity_len;
    latticra_l_ui_source_span_t source_span;
} latticra_console_request_t;

typedef struct {
    latticra_status_t status;
    char console_id[LATTICRA_CONSOLE_ID_MAX];
    char console_name[LATTICRA_CONSOLE_LABEL_MAX];
    char short_name[LATTICRA_CONSOLE_LABEL_MAX];
    char profile_label[LATTICRA_CONSOLE_LABEL_MAX];
    char component_key[LATTICRA_CONSOLE_LABEL_MAX];
    char console_status[LATTICRA_CONSOLE_LABEL_MAX];
    char command_registry_status[LATTICRA_CONSOLE_LABEL_MAX];
    char substrate_bridge_status[LATTICRA_CONSOLE_LABEL_MAX];
    char panel_install_status[LATTICRA_CONSOLE_LABEL_MAX];
    char host_embedding_status[LATTICRA_CONSOLE_LABEL_MAX];
    char os_base_status[LATTICRA_CONSOLE_LABEL_MAX];
    char source_identity[LATTICRA_CONSOLE_SOURCE_IDENTITY_MAX];
    latticra_l_ui_source_span_t source_span;
    latticra_kernel_result_t kernel;
    int no_effect;
    int configurable;
    int panel_installable;
    int command_registry_present;
    int substrate_bridge_present;
    int host_embeddable;
    int host_embedded_now;
    int operator_shell_present;
    int execution_allowed;
    int host_mutation_allowed;
    int file_io_allowed;
    int network_allowed;
    int runtime_enforcement_allowed;
    int boot_allowed;
    unsigned int command_count;
    unsigned int evidence_level;
} latticra_console_result_t;

latticra_status_t latticra_console_default_request(
    latticra_console_request_t *request);

const char *latticra_console_profile_label(latticra_console_profile_t profile);

latticra_status_t latticra_console_initialize(
    const latticra_console_request_t *request,
    latticra_console_result_t *result);

latticra_status_t latticra_console_report(
    const latticra_console_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
