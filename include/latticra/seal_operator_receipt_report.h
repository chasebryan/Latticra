#ifndef LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_H
#define LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_H

#include "latticra/seal_capability_metadata.h"
#include "latticra/seal_policy_decision.h"
#include "latticra/seal_request_freshness.h"
#include "latticra/seal_runtime_dry_run.h"
#include "latticra/seal_signed_request.h"
#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_OPERATOR_RECEIPT_PROFILE_MAX 64u
#define LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX 64u
#define LATTICRA_SEAL_OPERATOR_RECEIPT_REASON_MAX 96u
#define LATTICRA_SEAL_OPERATOR_RECEIPT_CAPABILITY_MAX 96u
#define LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK = 0,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT = 1,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA = 2,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION = 3,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS = 4,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST = 5,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN = 6,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE = 7,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT = 8,
    LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_BUFFER_TOO_SMALL = 9
} latticra_seal_operator_receipt_report_error_t;

typedef struct {
    const latticra_seal_capability_metadata_result_t *capability_metadata;
    const latticra_seal_policy_decision_t *policy_decision;
    const latticra_seal_request_freshness_t *request_freshness;
    const latticra_seal_signed_request_t *signed_request;
    const latticra_seal_runtime_dry_run_t *runtime_dry_run;
} latticra_seal_operator_receipt_report_sources_t;

typedef struct {
    char operator_receipt_profile[LATTICRA_SEAL_OPERATOR_RECEIPT_PROFILE_MAX];
    char receipt_mode[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    char receipt_status[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    unsigned source_capability_metadata_present;
    unsigned source_policy_decision_present;
    unsigned source_request_freshness_present;
    unsigned source_signed_request_present;
    unsigned source_runtime_dry_run_present;
    unsigned source_denial_reason_present;
    char capability_name[LATTICRA_SEAL_OPERATOR_RECEIPT_CAPABILITY_MAX];
    unsigned capability_known;
    unsigned capability_candidate;
    char policy_decision_state[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    char request_freshness_state[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    char signed_request_state[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    char runtime_dry_run_state[LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX];
    unsigned default_action_deny;
    unsigned would_allow;
    unsigned would_deny;
    unsigned would_require_operator_review;
    unsigned would_execute_tool;
    unsigned would_read_host;
    unsigned would_write_host;
    unsigned would_use_network;
    unsigned would_grant_runtime_authority;
    unsigned unknown_tool_denied;
    unsigned unsigned_request_denied;
    unsigned invalid_schema_denied;
    unsigned stale_request_denied;
    unsigned replayed_request_denied;
    unsigned invalid_signature_denied;
    char blocked_reason[LATTICRA_SEAL_OPERATOR_RECEIPT_REASON_MAX];
    unsigned receipt_complete;
    unsigned receipt_invalid;
    unsigned report_only;
    unsigned runtime_authority_granted;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_operator_receipt_report_error_t error;
} latticra_seal_operator_receipt_report_t;

const char *latticra_seal_operator_receipt_report_error_label(
    latticra_seal_operator_receipt_report_error_t error);
latticra_status_t latticra_seal_operator_receipt_report_from_sources(
    const latticra_seal_operator_receipt_report_sources_t *sources,
    latticra_seal_operator_receipt_report_t *out);
int latticra_seal_operator_receipt_report_is_report_only(
    const latticra_seal_operator_receipt_report_t *receipt);
latticra_status_t latticra_seal_operator_receipt_report_render(
    const latticra_seal_operator_receipt_report_t *receipt,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
