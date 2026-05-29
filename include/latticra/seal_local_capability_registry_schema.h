#ifndef LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_H
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_PROFILE_MAX 64u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_FORMAT_MAX 32u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_MAX 32u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_MODE_MAX 32u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_STATUS_MAX 32u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX 16u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_ID_MAX 64u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAMESPACE_MAX 64u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAME_MAX 96u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DESCRIPTION_MAX 256u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DEFAULT_DECISION_MAX 16u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_BLOCKED_REASON_MAX 160u
#define LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_REPORT_MAX 16384u

typedef enum {
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK = 0,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT = 1,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_PROFILE = 2,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE = 3,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS = 4,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS = 5,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_DEFAULT_DECISION = 6,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED = 7,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY = 8,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT = 9,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY = 10,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_BUFFER_TOO_SMALL = 11
} latticra_seal_local_capability_registry_schema_error_t;

typedef enum {
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_INVALID = 0,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_TOOL_BOUNDARY = 1,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_REQUEST_BOUNDARY = 2,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_POLICY_BOUNDARY = 3,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_RUNTIME_BOUNDARY = 4,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_EVIDENCE_BOUNDARY = 5,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY = 6
} latticra_seal_local_capability_registry_scope_t;

typedef enum {
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_INVALID = 0,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE = 1,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_TOOL = 2,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_READ = 3,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_WRITE = 4,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NETWORK = 5,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_RUNTIME_AUTHORITY = 6
} latticra_seal_local_capability_registry_effect_class_t;

typedef enum {
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_INVALID = 0,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_NONE = 1,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY = 2,
    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_FUTURE_GUARDED = 3
} latticra_seal_local_capability_registry_authority_class_t;

typedef struct {
    char capability_id[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_ID_MAX];
    char capability_namespace[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAMESPACE_MAX];
    char capability_name[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAME_MAX];
    char capability_description[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DESCRIPTION_MAX];
    latticra_seal_local_capability_registry_scope_t capability_scope;
    latticra_seal_local_capability_registry_effect_class_t capability_effect_class;
    latticra_seal_local_capability_registry_authority_class_t capability_authority_class;
    char capability_default_decision[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DEFAULT_DECISION_MAX];
    unsigned capability_requires_guarded_allowlist;
    unsigned capability_requires_policy_decision;
    unsigned capability_requires_runtime_gate;
    unsigned capability_requires_runtime_dry_run;
    unsigned capability_requires_operator_review;
    unsigned capability_requires_verification_receipt;
    unsigned capability_requires_signed_request;
    unsigned capability_grants_authority;
    unsigned capability_executes_tool;
    unsigned capability_reads_host;
    unsigned capability_writes_host;
    unsigned capability_uses_network;
    unsigned capability_report_only;
    unsigned capability_deprecated;
    char capability_blocked_reason[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_BLOCKED_REASON_MAX];
} latticra_seal_local_capability_registry_entry_t;

typedef struct {
    char registry_schema_profile[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_PROFILE_MAX];
    char registry_format_version[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_FORMAT_MAX];
    char registry_scope[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_MAX];
    char registry_mode[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_MODE_MAX];
    char registry_status[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_STATUS_MAX];
    unsigned registry_contract_present;
    unsigned registry_schema_planning_only;
    unsigned registry_loader_implemented;
    unsigned registry_file_loading_supported;
    unsigned registry_network_loading_supported;
    unsigned registry_signature_verification_supported;
    unsigned registry_trust_store_supported;
    unsigned registry_entry_count;
    unsigned registry_entry_count_max;
    unsigned registry_entry_id_max;
    unsigned registry_namespace_max;
    unsigned registry_name_max;
    unsigned registry_description_max;
    unsigned registry_blocked_reason_max;
    unsigned default_action_deny;
    unsigned runtime_authority_granted;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_local_capability_registry_schema_error_t last_error;
    latticra_seal_local_capability_registry_entry_t entries[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX];
} latticra_seal_local_capability_registry_schema_t;

const char *latticra_seal_local_capability_registry_schema_error_label(
    latticra_seal_local_capability_registry_schema_error_t error);
const char *latticra_seal_local_capability_registry_scope_label(
    latticra_seal_local_capability_registry_scope_t scope);
const char *latticra_seal_local_capability_registry_effect_class_label(
    latticra_seal_local_capability_registry_effect_class_t effect_class);
const char *latticra_seal_local_capability_registry_authority_class_label(
    latticra_seal_local_capability_registry_authority_class_t authority_class);
latticra_status_t latticra_seal_local_capability_registry_schema_init(
    latticra_seal_local_capability_registry_schema_t *out);
latticra_status_t latticra_seal_local_capability_registry_schema_add_entry(
    latticra_seal_local_capability_registry_schema_t *schema,
    const latticra_seal_local_capability_registry_entry_t *entry);
latticra_status_t latticra_seal_local_capability_registry_schema_add_default_entry(
    latticra_seal_local_capability_registry_schema_t *schema);
latticra_status_t latticra_seal_local_capability_registry_schema_validate(
    latticra_seal_local_capability_registry_schema_t *schema);
int latticra_seal_local_capability_registry_schema_is_report_only(
    const latticra_seal_local_capability_registry_schema_t *schema);
latticra_status_t latticra_seal_local_capability_registry_schema_render(
    const latticra_seal_local_capability_registry_schema_t *schema,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
