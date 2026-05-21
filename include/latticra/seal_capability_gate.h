#ifndef LATTICRA_SEAL_CAPABILITY_GATE_H
#define LATTICRA_SEAL_CAPABILITY_GATE_H

#include "latticra/seal_verification_receipt.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX 128u
#define LATTICRA_SEAL_CAPABILITY_GATE_ALGORITHM_MAX 32u
#define LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX 64u
#define LATTICRA_SEAL_CAPABILITY_GATE_DIGEST_MAX 65u
#define LATTICRA_SEAL_CAPABILITY_GATE_REPORT_MAX 3072u

typedef enum {
    LATTICRA_SEAL_CAPABILITY_GATE_OK = 0,
    LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT = 1,
    LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT = 2,
    LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST = 3,
    LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER = 4,
    LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY = 5,
    LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY = 6,
    LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT = 7
} latticra_seal_capability_gate_error_t;

typedef struct {
    char gate_profile[LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX];
    char receipt_profile[LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX];
    char verification_policy_profile[LATTICRA_SEAL_CAPABILITY_GATE_PROFILE_MAX];
    char artifact_digest_algorithm[LATTICRA_SEAL_CAPABILITY_GATE_ALGORITHM_MAX];
    char artifact_digest_hex[LATTICRA_SEAL_CAPABILITY_GATE_DIGEST_MAX];
    char signer_identity_label[LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX];
    char public_key_identity_label[LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX];
    char receipt_state[LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX];
    char verification_state[LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX];
    char requested_capability[LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX];
    char requested_effect[LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX];
    char requested_scope[LATTICRA_SEAL_CAPABILITY_GATE_LABEL_MAX];
    unsigned verified;
    unsigned authority_usable;
    unsigned receipt_capability_gate_allowed;
    unsigned gate_allowed;
    char gate_state[LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX];
    unsigned runtime_authority_granted;
    latticra_seal_capability_gate_error_t error;
    char status[LATTICRA_SEAL_CAPABILITY_GATE_STATE_MAX];
} latticra_seal_capability_gate_t;

const char *latticra_seal_capability_gate_error_label(
    latticra_seal_capability_gate_error_t error);
latticra_status_t latticra_seal_capability_gate_from_receipt(
    const latticra_seal_verification_receipt_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_capability_gate_t *out);
int latticra_seal_capability_gate_is_denied_metadata(
    const latticra_seal_capability_gate_t *gate);
latticra_status_t latticra_seal_capability_gate_report(
    const latticra_seal_capability_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
