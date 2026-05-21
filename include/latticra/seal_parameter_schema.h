#ifndef LATTICRA_SEAL_PARAMETER_SCHEMA_H
#define LATTICRA_SEAL_PARAMETER_SCHEMA_H

#include "latticra/seal_agentic_automation_security.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PARAMETER_SCHEMA_PROFILE_MAX 64u
#define LATTICRA_SEAL_PARAMETER_SCHEMA_ID_MAX 64u
#define LATTICRA_SEAL_PARAMETER_SCHEMA_HASH_MAX 96u
#define LATTICRA_SEAL_PARAMETER_SCHEMA_STATE_MAX 64u
#define LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_PARAMETER_SCHEMA_OK = 0,
    LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_INPUT = 1,
    LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_AGENTIC = 2
} latticra_seal_parameter_schema_error_t;

typedef struct {
    char schema_profile[LATTICRA_SEAL_PARAMETER_SCHEMA_PROFILE_MAX];
    char schema_id[LATTICRA_SEAL_PARAMETER_SCHEMA_ID_MAX];
    char schema_version[LATTICRA_SEAL_PARAMETER_SCHEMA_ID_MAX];
    char schema_language[LATTICRA_SEAL_PARAMETER_SCHEMA_ID_MAX];
    char schema_hash[LATTICRA_SEAL_PARAMETER_SCHEMA_HASH_MAX];
    unsigned schema_present;
    unsigned schema_parsing_supported;
    unsigned schema_validation_supported;
    unsigned schema_valid;
    unsigned max_input_bytes_declared;
    unsigned parameter_count_declared;
    unsigned required_parameter_count_declared;
    unsigned unknown_parameters_allowed;
    unsigned parameter_forwarding_allowed;
    unsigned input_size_within_limit;
    unsigned parameter_names_reported;
    unsigned runtime_authority_granted;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_PARAMETER_SCHEMA_STATE_MAX];
    char decision[LATTICRA_SEAL_PARAMETER_SCHEMA_STATE_MAX];
    char reason[LATTICRA_SEAL_PARAMETER_SCHEMA_STATE_MAX];
    latticra_seal_parameter_schema_error_t error;
    char status[LATTICRA_SEAL_PARAMETER_SCHEMA_STATE_MAX];
} latticra_seal_parameter_schema_t;

const char *latticra_seal_parameter_schema_error_label(
    latticra_seal_parameter_schema_error_t error);
latticra_status_t latticra_seal_parameter_schema_from_agentic(
    const latticra_seal_agentic_automation_security_t *agentic,
    latticra_seal_parameter_schema_t *out);
int latticra_seal_parameter_schema_is_report_only(
    const latticra_seal_parameter_schema_t *schema);
latticra_status_t latticra_seal_parameter_schema_report(
    const latticra_seal_parameter_schema_t *schema,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
