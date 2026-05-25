#ifndef LATTICRA_CONSOLE_H
#define LATTICRA_CONSOLE_H

#include "latticra/kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_CONSOLE_ID_MAX 64u
#define LATTICRA_CONSOLE_LABEL_MAX 64u
#define LATTICRA_CONSOLE_COMMAND_USAGE_MAX 96u
#define LATTICRA_CONSOLE_COMMAND_DESCRIPTION_MAX 160u
#define LATTICRA_CONSOLE_SOURCE_IDENTITY_MAX 128u
#define LATTICRA_CONSOLE_REPORT_MAX 20000u
#define LATTICRA_CONSOLE_COMMAND_REGISTRY_REPORT_MAX 12000u
#define LATTICRA_CONSOLE_HELP_REPORT_MAX 12000u
#define LATTICRA_CONSOLE_MANPAGE_REPORT_MAX 20000u
#define LATTICRA_CONSOLE_BOUNDARY_REPORT_MAX 20000u
#define LATTICRA_CONSOLE_HOST_CONTRACT_REPORT_MAX 12000u
#define LATTICRA_CONSOLE_HOST_INVENTORY_REPORT_MAX 12000u
#define LATTICRA_CONSOLE_RECEIPT_REPORT_MAX 12000u

typedef enum {
    LATTICRA_CONSOLE_PROFILE_HOSTED_REFERENCE = 0,
    LATTICRA_CONSOLE_PROFILE_PANEL_EMBEDDED = 1,
    LATTICRA_CONSOLE_PROFILE_HOST_EMBEDDED = 2,
    LATTICRA_CONSOLE_PROFILE_OS_BASE_PLANNING = 3
} latticra_console_profile_t;

typedef enum {
    LATTICRA_CONSOLE_COMMAND_CORE = 0,
    LATTICRA_CONSOLE_COMMAND_PANEL = 1,
    LATTICRA_CONSOLE_COMMAND_SUBSTRATE = 2,
    LATTICRA_CONSOLE_COMMAND_HOST = 3,
    LATTICRA_CONSOLE_COMMAND_OS_BASE = 4
} latticra_console_command_category_t;

typedef enum {
    LATTICRA_CONSOLE_COMMAND_EFFECT_NONE = 0,
    LATTICRA_CONSOLE_COMMAND_EFFECT_LOCAL_METADATA = 1,
    LATTICRA_CONSOLE_COMMAND_EFFECT_FUTURE_GATED = 2
} latticra_console_command_effect_t;

typedef struct {
    char name[LATTICRA_CONSOLE_LABEL_MAX];
    char usage[LATTICRA_CONSOLE_COMMAND_USAGE_MAX];
    char description[LATTICRA_CONSOLE_COMMAND_DESCRIPTION_MAX];
    char capability_label[LATTICRA_CONSOLE_LABEL_MAX];
    latticra_console_command_category_t category;
    latticra_console_command_effect_t effect;
    int no_effect;
    int panel_visible;
    int launches_host_process;
    int requires_future_gate;
} latticra_console_command_t;

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
    char command_name[LATTICRA_CONSOLE_LABEL_MAX];
    char capability_label[LATTICRA_CONSOLE_LABEL_MAX];
    char seal_capability_label[LATTICRA_CONSOLE_COMMAND_USAGE_MAX];
    latticra_runtime_boundary_request_kind_t runtime_request_kind;
    latticra_runtime_boundary_effect_t runtime_requested_effect;
    latticra_runtime_boundary_mode_t runtime_mode;
    latticra_runtime_boundary_policy_t runtime_policy;
    latticra_runtime_boundary_denial_t runtime_denial;
    latticra_runtime_boundary_policy_matrix_cell_t runtime_policy_matrix_cell;
    int no_effect;
    int execution_allowed;
    int host_mutation_allowed;
    int network_allowed;
    int runtime_enforcement_allowed;
    int boot_allowed;
    int requires_future_gate;
    int seal_capability_grants_authority;
} latticra_console_command_boundary_t;

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
    char host_embedding_contract_status[LATTICRA_CONSOLE_LABEL_MAX];
    char host_inventory_contract_status[LATTICRA_CONSOLE_LABEL_MAX];
    char receipt_contract_status[LATTICRA_CONSOLE_LABEL_MAX];
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
    int host_embedding_contract_present;
    int host_inventory_contract_present;
    int receipt_contract_present;
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

const char *latticra_console_command_category_label(
    latticra_console_command_category_t category);

const char *latticra_console_command_effect_label(
    latticra_console_command_effect_t effect);

size_t latticra_console_command_count(void);

const latticra_console_command_t *latticra_console_command_at(size_t index);

const latticra_console_command_t *latticra_console_find_command(const char *name);

latticra_status_t latticra_console_command_registry_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_help_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_manpage_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_command_boundary_classify(
    const latticra_console_command_t *command,
    latticra_console_command_boundary_t *boundary);

latticra_status_t latticra_console_command_boundary_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_host_contract_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_host_inventory_report(
    char *buffer,
    size_t buffer_len);

latticra_status_t latticra_console_receipt_report(
    char *buffer,
    size_t buffer_len);

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
