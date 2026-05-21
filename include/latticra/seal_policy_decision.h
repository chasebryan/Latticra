#ifndef LATTICRA_SEAL_POLICY_DECISION_H
#define LATTICRA_SEAL_POLICY_DECISION_H

#include "latticra/seal_signed_request.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_POLICY_DECISION_PROFILE_MAX 64u
#define LATTICRA_SEAL_POLICY_DECISION_ID_MAX 64u
#define LATTICRA_SEAL_POLICY_DECISION_STATE_MAX 64u
#define LATTICRA_SEAL_POLICY_DECISION_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_POLICY_DECISION_OK = 0,
    LATTICRA_SEAL_POLICY_DECISION_INVALID_INPUT = 1,
    LATTICRA_SEAL_POLICY_DECISION_INVALID_SIGNED_REQUEST = 2
} latticra_seal_policy_decision_error_t;

typedef struct {
    char policy_decision_profile[LATTICRA_SEAL_POLICY_DECISION_PROFILE_MAX];
    char policy_id[LATTICRA_SEAL_POLICY_DECISION_ID_MAX];
    char policy_version[LATTICRA_SEAL_POLICY_DECISION_ID_MAX];
    char requested_action[LATTICRA_SEAL_POLICY_DECISION_ID_MAX];
    char requested_tool[LATTICRA_SEAL_POLICY_DECISION_ID_MAX];
    unsigned policy_decision_supported;
    unsigned policy_evaluation_supported;
    unsigned policy_enforcement_supported;
    unsigned policy_id_present;
    unsigned policy_version_present;
    unsigned requested_action_present;
    unsigned requested_tool_present;
    unsigned signed_request_present;
    unsigned signature_valid;
    unsigned schema_valid;
    unsigned freshness_valid;
    unsigned replay_detected;
    char default_decision[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
    char decision_state[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
    unsigned decision_allowed;
    unsigned decision_denied;
    unsigned operator_review_required;
    unsigned unknown_tool_denied;
    unsigned unsigned_request_denied;
    unsigned invalid_schema_denied;
    unsigned stale_request_denied;
    unsigned replayed_request_denied;
    unsigned invalid_signature_denied;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
    char decision[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
    char reason[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
    latticra_seal_policy_decision_error_t error;
    char status[LATTICRA_SEAL_POLICY_DECISION_STATE_MAX];
} latticra_seal_policy_decision_t;

const char *latticra_seal_policy_decision_error_label(
    latticra_seal_policy_decision_error_t error);
latticra_status_t latticra_seal_policy_decision_from_signed_request(
    const latticra_seal_signed_request_t *signed_request,
    latticra_seal_policy_decision_t *out);
int latticra_seal_policy_decision_is_report_only(
    const latticra_seal_policy_decision_t *policy_decision);
latticra_status_t latticra_seal_policy_decision_report(
    const latticra_seal_policy_decision_t *policy_decision,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
