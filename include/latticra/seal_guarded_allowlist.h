#ifndef LATTICRA_SEAL_GUARDED_ALLOWLIST_H
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_GUARDED_ALLOWLIST_PROFILE_MAX 64u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX 96u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_SOURCE_MAX 96u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_REASON_MAX 96u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_STATUS_MAX 64u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX 4096u
#define LATTICRA_SEAL_GUARDED_ALLOWLIST_ENTRY_MAX 3u

typedef enum {
    LATTICRA_SEAL_GUARDED_ALLOWLIST_OK = 0,
    LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_INPUT = 1,
    LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME = 2,
    LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_ALLOWLIST = 3,
    LATTICRA_SEAL_GUARDED_ALLOWLIST_BUFFER_TOO_SMALL = 4
} latticra_seal_guarded_allowlist_error_t;

typedef struct {
    char tool_name[LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX];
} latticra_seal_guarded_allowlist_entry_t;

typedef struct {
    char allowlist_source[LATTICRA_SEAL_GUARDED_ALLOWLIST_SOURCE_MAX];
    unsigned allowlist_entry_count;
    latticra_seal_guarded_allowlist_entry_t entries[LATTICRA_SEAL_GUARDED_ALLOWLIST_ENTRY_MAX];
} latticra_seal_guarded_allowlist_t;

typedef struct {
    char guarded_allowlist_profile[LATTICRA_SEAL_GUARDED_ALLOWLIST_PROFILE_MAX];
    char tool_name[LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX];
    char allowlist_source[LATTICRA_SEAL_GUARDED_ALLOWLIST_SOURCE_MAX];
    unsigned allowlist_entry_count;
    unsigned allowlist_lookup_performed;
    unsigned requested_tool_name_present;
    unsigned requested_tool_known;
    unsigned requested_tool_unknown;
    unsigned requested_tool_candidate;
    unsigned requested_tool_allow_candidate;
    unsigned allow_candidate_requires_policy_decision;
    unsigned allow_candidate_requires_runtime_gate;
    unsigned allow_candidate_requires_runtime_dry_run;
    unsigned allow_candidate_requires_operator_review;
    unsigned allow_candidate_grants_authority;
    unsigned allow_candidate_executes_tool;
    unsigned allow_candidate_reads_host;
    unsigned allow_candidate_writes_host;
    unsigned allow_candidate_uses_network;
    unsigned default_action_deny;
    unsigned would_allow;
    unsigned would_deny;
    unsigned would_require_operator_review;
    char blocked_reason[LATTICRA_SEAL_GUARDED_ALLOWLIST_REASON_MAX];
    unsigned report_only;
    char mode[LATTICRA_SEAL_GUARDED_ALLOWLIST_STATUS_MAX];
    char status[LATTICRA_SEAL_GUARDED_ALLOWLIST_STATUS_MAX];
    latticra_seal_guarded_allowlist_error_t error;
} latticra_seal_guarded_allowlist_result_t;

const char *latticra_seal_guarded_allowlist_error_label(
    latticra_seal_guarded_allowlist_error_t error);
latticra_seal_guarded_allowlist_t latticra_seal_guarded_allowlist_fixture(void);
latticra_status_t latticra_seal_guarded_allowlist_result_unknown(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out);
latticra_status_t latticra_seal_guarded_allowlist_result_candidate(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out);
latticra_status_t latticra_seal_guarded_allowlist_evaluate(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out);
int latticra_seal_guarded_allowlist_is_report_only(
    const latticra_seal_guarded_allowlist_result_t *result);
latticra_status_t latticra_seal_guarded_allowlist_report(
    const latticra_seal_guarded_allowlist_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
