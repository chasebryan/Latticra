#ifndef LATTICRA_SEAL_SIGNED_REQUEST_H
#define LATTICRA_SEAL_SIGNED_REQUEST_H

#include "latticra/seal_request_freshness.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_SIGNED_REQUEST_PROFILE_MAX 64u
#define LATTICRA_SEAL_SIGNED_REQUEST_ID_MAX 64u
#define LATTICRA_SEAL_SIGNED_REQUEST_HASH_MAX 96u
#define LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX 64u
#define LATTICRA_SEAL_SIGNED_REQUEST_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_SIGNED_REQUEST_OK = 0,
    LATTICRA_SEAL_SIGNED_REQUEST_INVALID_INPUT = 1,
    LATTICRA_SEAL_SIGNED_REQUEST_INVALID_FRESHNESS = 2
} latticra_seal_signed_request_error_t;

typedef struct {
    char signed_request_profile[LATTICRA_SEAL_SIGNED_REQUEST_PROFILE_MAX];
    char signed_request_id[LATTICRA_SEAL_SIGNED_REQUEST_ID_MAX];
    char signature_algorithm[LATTICRA_SEAL_SIGNED_REQUEST_ID_MAX];
    char signing_key_id[LATTICRA_SEAL_SIGNED_REQUEST_ID_MAX];
    char signature_hash[LATTICRA_SEAL_SIGNED_REQUEST_HASH_MAX];
    unsigned signed_request_supported;
    unsigned signature_generation_supported;
    unsigned signature_verification_supported;
    unsigned signature_present;
    unsigned signature_valid;
    unsigned signature_algorithm_declared;
    unsigned signing_key_id_present;
    unsigned signature_hash_present;
    unsigned signed_request_id_present;
    unsigned identity_binding_declared;
    unsigned context_binding_declared;
    unsigned parameter_binding_declared;
    unsigned freshness_binding_declared;
    unsigned policy_binding_declared;
    unsigned trust_store_supported;
    unsigned revocation_lookup_supported;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX];
    char decision[LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX];
    char reason[LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX];
    latticra_seal_signed_request_error_t error;
    char status[LATTICRA_SEAL_SIGNED_REQUEST_STATE_MAX];
} latticra_seal_signed_request_t;

const char *latticra_seal_signed_request_error_label(
    latticra_seal_signed_request_error_t error);
latticra_status_t latticra_seal_signed_request_from_freshness(
    const latticra_seal_request_freshness_t *freshness,
    latticra_seal_signed_request_t *out);
int latticra_seal_signed_request_is_report_only(
    const latticra_seal_signed_request_t *signed_request);
latticra_status_t latticra_seal_signed_request_report(
    const latticra_seal_signed_request_t *signed_request,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
