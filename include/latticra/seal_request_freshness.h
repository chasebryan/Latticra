#ifndef LATTICRA_SEAL_REQUEST_FRESHNESS_H
#define LATTICRA_SEAL_REQUEST_FRESHNESS_H

#include "latticra/seal_parameter_schema.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_REQUEST_FRESHNESS_PROFILE_MAX 64u
#define LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX 64u
#define LATTICRA_SEAL_REQUEST_FRESHNESS_TIME_MAX 64u
#define LATTICRA_SEAL_REQUEST_FRESHNESS_HASH_MAX 96u
#define LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX 64u
#define LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_REQUEST_FRESHNESS_OK = 0,
    LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_INPUT = 1,
    LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_SCHEMA = 2
} latticra_seal_request_freshness_error_t;

typedef struct {
    char freshness_profile[LATTICRA_SEAL_REQUEST_FRESHNESS_PROFILE_MAX];
    char request_id[LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX];
    char caller_id[LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX];
    char tool_id[LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX];
    char request_timestamp[LATTICRA_SEAL_REQUEST_FRESHNESS_TIME_MAX];
    char request_expiration[LATTICRA_SEAL_REQUEST_FRESHNESS_TIME_MAX];
    char nonce[LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX];
    char context_hash[LATTICRA_SEAL_REQUEST_FRESHNESS_HASH_MAX];
    char parameter_hash[LATTICRA_SEAL_REQUEST_FRESHNESS_HASH_MAX];
    unsigned request_freshness_supported;
    unsigned request_freshness_validation_supported;
    unsigned replay_protection_supported;
    unsigned request_id_present;
    unsigned caller_id_present;
    unsigned tool_id_present;
    unsigned request_timestamp_present;
    unsigned request_expiration_present;
    unsigned nonce_present;
    unsigned context_hash_present;
    unsigned parameter_hash_present;
    unsigned freshness_valid;
    unsigned replay_detected;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX];
    char decision[LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX];
    char reason[LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX];
    latticra_seal_request_freshness_error_t error;
    char status[LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX];
} latticra_seal_request_freshness_t;

const char *latticra_seal_request_freshness_error_label(
    latticra_seal_request_freshness_error_t error);
latticra_status_t latticra_seal_request_freshness_from_schema(
    const latticra_seal_parameter_schema_t *schema,
    latticra_seal_request_freshness_t *out);
int latticra_seal_request_freshness_is_report_only(
    const latticra_seal_request_freshness_t *freshness);
latticra_status_t latticra_seal_request_freshness_report(
    const latticra_seal_request_freshness_t *freshness,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
