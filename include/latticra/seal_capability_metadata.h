#ifndef LATTICRA_SEAL_CAPABILITY_METADATA_H
#define LATTICRA_SEAL_CAPABILITY_METADATA_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_CAPABILITY_METADATA_PROFILE_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX 96u
#define LATTICRA_SEAL_CAPABILITY_METADATA_SCOPE_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_METADATA_EFFECT_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_METADATA_SOURCE_MAX 96u
#define LATTICRA_SEAL_CAPABILITY_METADATA_REASON_MAX 96u
#define LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX 4096u
#define LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX 3u

typedef enum {
    LATTICRA_SEAL_CAPABILITY_METADATA_OK = 0,
    LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_INPUT = 1,
    LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME = 2,
    LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE = 3,
    LATTICRA_SEAL_CAPABILITY_METADATA_BUFFER_TOO_SMALL = 4
} latticra_seal_capability_metadata_error_t;

typedef struct {
    char capability_name[LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX];
    char capability_scope[LATTICRA_SEAL_CAPABILITY_METADATA_SCOPE_MAX];
    char capability_effect_class[LATTICRA_SEAL_CAPABILITY_METADATA_EFFECT_MAX];
} latticra_seal_capability_metadata_entry_t;

typedef struct {
    char capability_fixture_source[LATTICRA_SEAL_CAPABILITY_METADATA_SOURCE_MAX];
    unsigned capability_fixture_entry_count;
    latticra_seal_capability_metadata_entry_t entries[LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX];
} latticra_seal_capability_metadata_fixture_t;

typedef struct {
    char capability_metadata_profile[LATTICRA_SEAL_CAPABILITY_METADATA_PROFILE_MAX];
    char capability_name[LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX];
    char capability_scope[LATTICRA_SEAL_CAPABILITY_METADATA_SCOPE_MAX];
    char capability_effect_class[LATTICRA_SEAL_CAPABILITY_METADATA_EFFECT_MAX];
    char capability_fixture_source[LATTICRA_SEAL_CAPABILITY_METADATA_SOURCE_MAX];
    unsigned capability_fixture_entry_count;
    unsigned capability_lookup_performed;
    unsigned capability_name_present;
    unsigned capability_known;
    unsigned capability_unknown;
    unsigned capability_candidate;
    unsigned capability_requires_guarded_allowlist;
    unsigned capability_requires_policy_decision;
    unsigned capability_requires_runtime_gate;
    unsigned capability_requires_runtime_dry_run;
    unsigned capability_requires_operator_review;
    unsigned capability_grants_authority;
    unsigned capability_executes_tool;
    unsigned capability_reads_host;
    unsigned capability_writes_host;
    unsigned capability_uses_network;
    unsigned default_action_deny;
    unsigned would_allow;
    unsigned would_deny;
    unsigned would_require_operator_review;
    unsigned unknown_tool_denied;
    unsigned unsigned_request_denied;
    unsigned invalid_schema_denied;
    unsigned stale_request_denied;
    unsigned replayed_request_denied;
    unsigned invalid_signature_denied;
    unsigned unknown_capability_denied;
    unsigned missing_capability_denied;
    unsigned invalid_capability_denied;
    char blocked_reason[LATTICRA_SEAL_CAPABILITY_METADATA_REASON_MAX];
    unsigned report_only;
    char mode[LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX];
    char status[LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX];
    latticra_seal_capability_metadata_error_t error;
} latticra_seal_capability_metadata_result_t;

const char *latticra_seal_capability_metadata_error_label(
    latticra_seal_capability_metadata_error_t error);
latticra_seal_capability_metadata_fixture_t latticra_seal_capability_metadata_fixture(void);
latticra_status_t latticra_seal_capability_metadata_result_missing(
    latticra_seal_capability_metadata_result_t *out);
latticra_status_t latticra_seal_capability_metadata_result_unknown(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out);
latticra_status_t latticra_seal_capability_metadata_result_candidate(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out);
latticra_status_t latticra_seal_capability_metadata_evaluate(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out);
int latticra_seal_capability_metadata_is_report_only(
    const latticra_seal_capability_metadata_result_t *result);
latticra_status_t latticra_seal_capability_metadata_report(
    const latticra_seal_capability_metadata_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
