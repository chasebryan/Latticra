#ifndef LATTICRA_SEAL_REPORT_ENVELOPE_H
#define LATTICRA_SEAL_REPORT_ENVELOPE_H

#include "latticra/seal_runtime_handoff_report.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX 64u
#define LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX 128u
#define LATTICRA_SEAL_REPORT_ENVELOPE_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX 64u
#define LATTICRA_SEAL_REPORT_ENVELOPE_DIGEST_MAX 65u
#define LATTICRA_SEAL_REPORT_ENVELOPE_RENDER_MAX 4096u

typedef enum {
    LATTICRA_SEAL_REPORT_ENVELOPE_OK = 0,
    LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT = 1,
    LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT = 2,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT = 3,
    LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE = 4,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE = 5,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE = 6,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY = 7,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT = 8,
    LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT = 9
} latticra_seal_report_envelope_error_t;

typedef struct {
    char envelope_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char report_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char handoff_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char decision_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char gate_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char verify_profile[LATTICRA_SEAL_REPORT_ENVELOPE_PROFILE_MAX];
    char message_digest_algorithm[LATTICRA_SEAL_REPORT_ENVELOPE_ALGORITHM_MAX];
    char message_digest_hex[LATTICRA_SEAL_REPORT_ENVELOPE_DIGEST_MAX];
    char public_key_identity_label[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_capability[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_handoff[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_report[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_envelope[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_REPORT_ENVELOPE_LABEL_MAX];
    unsigned verified;
    unsigned authority_usable;
    unsigned receipt_capability_gate_allowed;
    unsigned gate_allowed;
    char gate_state[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
    char decision_state[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
    unsigned effect_allowed;
    char handoff_state[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
    unsigned handoff_eligible;
    char report_state[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
    unsigned report_ready;
    char envelope_state[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
    unsigned envelope_ready;
    unsigned signature_performed;
    unsigned handoff_performed;
    unsigned effect_performed;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_report_envelope_error_t error;
    char status[LATTICRA_SEAL_REPORT_ENVELOPE_STATE_MAX];
} latticra_seal_report_envelope_t;

const char *latticra_seal_report_envelope_error_label(
    latticra_seal_report_envelope_error_t error);
latticra_status_t latticra_seal_report_envelope_from_report(
    const latticra_seal_runtime_handoff_report_t *report,
    const char *requested_envelope,
    latticra_seal_report_envelope_t *out);
int latticra_seal_report_envelope_is_metadata_only(
    const latticra_seal_report_envelope_t *envelope);
latticra_status_t latticra_seal_report_envelope_render(
    const latticra_seal_report_envelope_t *envelope,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
