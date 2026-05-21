#ifndef LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_H
#define LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_H

#include "latticra/seal_status_rollup.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_AGENTIC_PROFILE_MAX 96u
#define LATTICRA_SEAL_AGENTIC_ID_MAX 64u
#define LATTICRA_SEAL_AGENTIC_STATE_MAX 64u
#define LATTICRA_SEAL_AGENTIC_REPORT_MAX 4096u

typedef enum {
    LATTICRA_SEAL_AGENTIC_OK = 0,
    LATTICRA_SEAL_AGENTIC_INVALID_INPUT = 1,
    LATTICRA_SEAL_AGENTIC_INVALID_ROLLUP = 2
} latticra_seal_agentic_automation_security_error_t;

typedef struct {
    char agentic_profile[LATTICRA_SEAL_AGENTIC_PROFILE_MAX];
    char request_id[LATTICRA_SEAL_AGENTIC_ID_MAX];
    char caller_id[LATTICRA_SEAL_AGENTIC_ID_MAX];
    char tool_id[LATTICRA_SEAL_AGENTIC_ID_MAX];
    char automation_context[LATTICRA_SEAL_AGENTIC_ID_MAX];
    unsigned mcp_alignment_declared;
    unsigned mcp_protocol_implemented;
    unsigned mcp_server_implemented;
    unsigned mcp_client_implemented;
    unsigned agent_execution_supported;
    unsigned model_execution_supported;
    unsigned tool_execution_supported;
    unsigned shell_execution_supported;
    unsigned manifest_present;
    unsigned manifest_signed;
    unsigned parameter_schema_present;
    unsigned parameter_schema_valid;
    unsigned freshness_valid;
    unsigned replay_detected;
    unsigned receipt_required;
    unsigned receipt_generated;
    unsigned cryptographic_verification_supported;
    unsigned capability_enforcement_supported;
    unsigned runtime_authority_requested;
    unsigned runtime_authority_granted;
    unsigned unknown_tool_allowed;
    unsigned unsigned_manifest_allowed;
    unsigned network_access_allowed;
    unsigned private_key_access_allowed;
    unsigned system_mutation_allowed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    char mode[LATTICRA_SEAL_AGENTIC_STATE_MAX];
    char decision[LATTICRA_SEAL_AGENTIC_STATE_MAX];
    char reason[LATTICRA_SEAL_AGENTIC_STATE_MAX];
    latticra_seal_agentic_automation_security_error_t error;
    char status[LATTICRA_SEAL_AGENTIC_STATE_MAX];
} latticra_seal_agentic_automation_security_t;

const char *latticra_seal_agentic_automation_security_error_label(
    latticra_seal_agentic_automation_security_error_t error);
latticra_status_t latticra_seal_agentic_automation_security_from_rollup(
    const latticra_seal_status_rollup_t *rollup,
    latticra_seal_agentic_automation_security_t *out);
int latticra_seal_agentic_automation_security_is_report_only(
    const latticra_seal_agentic_automation_security_t *agentic);
latticra_status_t latticra_seal_agentic_automation_security_report(
    const latticra_seal_agentic_automation_security_t *agentic,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
