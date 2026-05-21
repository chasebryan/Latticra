#include "latticra/seal_parameter_schema.h"

#include <stdio.h>
#include <string.h>

static latticra_seal_agentic_automation_security_t fixture_agentic(void) {
    latticra_seal_agentic_automation_security_t agentic;
    memset(&agentic, 0, sizeof(agentic));
    (void)snprintf(agentic.agentic_profile, sizeof(agentic.agentic_profile), "%s", "latticra-seal-agentic-automation-security/0.1");
    (void)snprintf(agentic.request_id, sizeof(agentic.request_id), "%s", "unset");
    (void)snprintf(agentic.caller_id, sizeof(agentic.caller_id), "%s", "unset");
    (void)snprintf(agentic.tool_id, sizeof(agentic.tool_id), "%s", "unset");
    (void)snprintf(agentic.automation_context, sizeof(agentic.automation_context), "%s", "local-report-only");
    agentic.mcp_alignment_declared = 1u;
    agentic.mcp_protocol_implemented = 0u;
    agentic.mcp_server_implemented = 0u;
    agentic.mcp_client_implemented = 0u;
    agentic.agent_execution_supported = 0u;
    agentic.model_execution_supported = 0u;
    agentic.tool_execution_supported = 0u;
    agentic.shell_execution_supported = 0u;
    agentic.manifest_present = 1u;
    agentic.manifest_signed = 0u;
    agentic.parameter_schema_present = 0u;
    agentic.parameter_schema_valid = 0u;
    agentic.freshness_valid = 0u;
    agentic.replay_detected = 0u;
    agentic.receipt_required = 1u;
    agentic.receipt_generated = 0u;
    agentic.cryptographic_verification_supported = 0u;
    agentic.capability_enforcement_supported = 0u;
    agentic.runtime_authority_requested = 0u;
    agentic.runtime_authority_granted = 0u;
    agentic.unknown_tool_allowed = 0u;
    agentic.unsigned_manifest_allowed = 0u;
    agentic.network_access_allowed = 0u;
    agentic.private_key_access_allowed = 0u;
    agentic.system_mutation_allowed = 0u;
    agentic.host_read_performed = 0u;
    agentic.host_write_performed = 0u;
    agentic.network_performed = 0u;
    (void)snprintf(agentic.mode, sizeof(agentic.mode), "%s", "report-only");
    (void)snprintf(agentic.decision, sizeof(agentic.decision), "%s", "report-only");
    (void)snprintf(agentic.reason, sizeof(agentic.reason), "%s", "metadata-only");
    agentic.error = LATTICRA_SEAL_AGENTIC_OK;
    (void)snprintf(agentic.status, sizeof(agentic.status), "%s", "agentic-automation-security-metadata");
    return agentic;
}

int main(void) {
    latticra_seal_agentic_automation_security_t agentic = fixture_agentic();
    latticra_seal_parameter_schema_t schema;
    char rendered[LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_MAX];

    if (latticra_seal_parameter_schema_from_agentic(&agentic, &schema) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal parameter schema metadata\n");
        return 1;
    }

    if (schema.error != LATTICRA_SEAL_PARAMETER_SCHEMA_OK) {
        fprintf(stderr, "invalid Seal parameter schema metadata: %s\n",
                latticra_seal_parameter_schema_error_label(schema.error));
        return 1;
    }

    if (latticra_seal_parameter_schema_report(&schema, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal parameter schema report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}
