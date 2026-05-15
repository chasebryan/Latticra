#ifndef LATTICRA_NUCLEUS_PREVIEW_H
#define LATTICRA_NUCLEUS_PREVIEW_H

#include "latticra/state_lattice.h"
#include "latticra/tri_plane_transition.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_NUCLEUS_REPORT_MAX 768u

typedef enum {
    LATTICRA_REQUEST_STATE_REPORT = 0,
    LATTICRA_REQUEST_TRANSITION_PREVIEW = 1,
    LATTICRA_REQUEST_SERVER_INTERACTION = 2,
    LATTICRA_REQUEST_SELF_UPDATE = 3,
    LATTICRA_REQUEST_RECOVERY_ACTION = 4,
    LATTICRA_REQUEST_HARDWARE_ACTION = 5,
    LATTICRA_REQUEST_UNKNOWN = 6
} latticra_request_kind_t;

typedef enum {
    LATTICRA_POLICY_ALLOW_PREVIEW = 0,
    LATTICRA_POLICY_DENY = 1
} latticra_policy_result_t;

typedef enum {
    LATTICRA_POLICY_REASON_OK = 0,
    LATTICRA_POLICY_REASON_NULL_ARGUMENT = 1,
    LATTICRA_POLICY_REASON_UNKNOWN_REQUEST = 2,
    LATTICRA_POLICY_REASON_EFFECT_BLOCKED = 3,
    LATTICRA_POLICY_REASON_EFFECT_REQUIRES_FUTURE_GATE = 4
} latticra_policy_reason_t;

typedef struct {
    latticra_request_kind_t request_kind;
    latticra_effect_t requested_effect;
    latticra_policy_result_t policy_result;
    latticra_policy_reason_t policy_reason;
    int executed;
    int mutation_allowed;
    int server_interaction_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_nucleus_preview_t;

const char *latticra_request_kind_label(latticra_request_kind_t kind);
const char *latticra_policy_result_label(latticra_policy_result_t result);
const char *latticra_policy_reason_label(latticra_policy_reason_t reason);

latticra_status_t latticra_nucleus_classify_preview(
    latticra_request_kind_t request_kind,
    latticra_effect_t requested_effect,
    latticra_nucleus_preview_t *preview);

latticra_status_t latticra_nucleus_preview_report(
    const latticra_nucleus_preview_t *preview,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
