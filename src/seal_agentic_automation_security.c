#include "latticra/seal_agentic_automation_security.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_agentic_automation_security_error_label(
    latticra_seal_agentic_automation_security_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_AGENTIC_OK:
        return "ok";
    case LATTICRA_SEAL_AGENTIC_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_AGENTIC_INVALID_ROLLUP:
        return "invalid-rollup";
    default:
        return "unknown";
    }
}

static void agentic_init(latticra_seal_agentic_automation_security_t *agentic) {
    memset(agentic, 0, sizeof(*agentic));
    copy_literal(agentic->agentic_profile, sizeof(agentic->agentic_profile), "latticra-seal-agentic-automation-security/0.1");
    copy_literal(agentic->request_id, sizeof(agentic->request_id), "unset");
    copy_literal(agentic->caller_id, sizeof(agentic->caller_id), "unset");
    copy_literal(agentic->tool_id, sizeof(agentic->tool_id), "unset");
    copy_literal(agentic->automation_context, sizeof(agentic->automation_context), "local-report-only");
    agentic->mcp_alignment_declared = 1u;
    agentic->mcp_protocol_implemented = 0u;
    agentic->mcp_server_implemented = 0u;
    agentic->mcp_client_implemented = 0u;
    agentic->agent_execution_supported = 0u;
    agentic->model_execution_supported = 0u;
    agentic->tool_execution_supported = 0u;
    agentic->shell_execution_supported = 0u;
    agentic->manifest_present = 0u;
    agentic->manifest_signed = 0u;
    agentic->parameter_schema_present = 0u;
    agentic->parameter_schema_valid = 0u;
    agentic->freshness_valid = 0u;
    agentic->replay_detected = 0u;
    agentic->receipt_required = 1u;
    agentic->receipt_generated = 0u;
    agentic->cryptographic_verification_supported = 0u;
    agentic->capability_enforcement_supported = 0u;
    agentic->runtime_authority_requested = 0u;
    agentic->runtime_authority_granted = 0u;
    agentic->unknown_tool_allowed = 0u;
    agentic->unsigned_manifest_allowed = 0u;
    agentic->network_access_allowed = 0u;
    agentic->private_key_access_allowed = 0u;
    agentic->system_mutation_allowed = 0u;
    agentic->host_read_performed = 0u;
    agentic->host_write_performed = 0u;
    agentic->network_performed = 0u;
    copy_literal(agentic->mode, sizeof(agentic->mode), "report-only");
    copy_literal(agentic->decision, sizeof(agentic->decision), "report-only");
    copy_literal(agentic->reason, sizeof(agentic->reason), "metadata-only");
    agentic->error = LATTICRA_SEAL_AGENTIC_INVALID_INPUT;
    copy_literal(agentic->status, sizeof(agentic->status), "invalid-input");
}

latticra_status_t latticra_seal_agentic_automation_security_from_rollup(
    const latticra_seal_status_rollup_t *rollup,
    latticra_seal_agentic_automation_security_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    agentic_init(out);

    if (rollup == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (rollup->error != LATTICRA_SEAL_STATUS_ROLLUP_OK ||
        latticra_seal_status_rollup_is_metadata_only(rollup) != 1) {
        out->error = LATTICRA_SEAL_AGENTIC_INVALID_ROLLUP;
        copy_literal(out->status, sizeof(out->status), "invalid-rollup");
        copy_literal(out->reason, sizeof(out->reason), "invalid-rollup");
        return LATTICRA_STATUS_OK;
    }

    out->manifest_present = rollup->manifest_present;
    out->cryptographic_verification_supported = rollup->cryptographic_verification_supported;
    out->runtime_authority_granted = rollup->runtime_authority_granted;
    out->host_read_performed = rollup->host_read_performed;
    out->host_write_performed = rollup->host_write_performed;
    out->network_performed = rollup->network_performed;
    out->error = LATTICRA_SEAL_AGENTIC_OK;
    copy_literal(out->status, sizeof(out->status), "agentic-automation-security-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_agentic_automation_security_is_report_only(
    const latticra_seal_agentic_automation_security_t *agentic) {
    if (agentic == NULL) {
        return 0;
    }

    return agentic->mcp_protocol_implemented == 0u &&
           agentic->mcp_server_implemented == 0u &&
           agentic->mcp_client_implemented == 0u &&
           agentic->agent_execution_supported == 0u &&
           agentic->model_execution_supported == 0u &&
           agentic->tool_execution_supported == 0u &&
           agentic->shell_execution_supported == 0u &&
           agentic->manifest_signed == 0u &&
           agentic->parameter_schema_valid == 0u &&
           agentic->freshness_valid == 0u &&
           agentic->replay_detected == 0u &&
           agentic->receipt_generated == 0u &&
           agentic->cryptographic_verification_supported == 0u &&
           agentic->capability_enforcement_supported == 0u &&
           agentic->runtime_authority_requested == 0u &&
           agentic->runtime_authority_granted == 0u &&
           agentic->unknown_tool_allowed == 0u &&
           agentic->unsigned_manifest_allowed == 0u &&
           agentic->network_access_allowed == 0u &&
           agentic->private_key_access_allowed == 0u &&
           agentic->system_mutation_allowed == 0u &&
           agentic->host_read_performed == 0u &&
           agentic->host_write_performed == 0u &&
           agentic->network_performed == 0u;
}

latticra_status_t latticra_seal_agentic_automation_security_report(
    const latticra_seal_agentic_automation_security_t *agentic,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (agentic == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL AGENTIC AUTOMATION SECURITY\n"
        "agentic_profile=%s\n"
        "request_id=%s\n"
        "caller_id=%s\n"
        "tool_id=%s\n"
        "automation_context=%s\n"
        "mcp_alignment_declared=%u\n"
        "mcp_protocol_implemented=%u\n"
        "mcp_server_implemented=%u\n"
        "mcp_client_implemented=%u\n"
        "agent_execution_supported=%u\n"
        "model_execution_supported=%u\n"
        "tool_execution_supported=%u\n"
        "shell_execution_supported=%u\n"
        "manifest_present=%u\n"
        "manifest_signed=%u\n"
        "parameter_schema_present=%u\n"
        "parameter_schema_valid=%u\n"
        "freshness_valid=%u\n"
        "replay_detected=%u\n"
        "receipt_required=%u\n"
        "receipt_generated=%u\n"
        "cryptographic_verification_supported=%u\n"
        "capability_enforcement_supported=%u\n"
        "runtime_authority_requested=%u\n"
        "runtime_authority_granted=%u\n"
        "unknown_tool_allowed=%u\n"
        "unsigned_manifest_allowed=%u\n"
        "network_access_allowed=%u\n"
        "private_key_access_allowed=%u\n"
        "system_mutation_allowed=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        agentic->agentic_profile,
        agentic->request_id,
        agentic->caller_id,
        agentic->tool_id,
        agentic->automation_context,
        agentic->mcp_alignment_declared,
        agentic->mcp_protocol_implemented,
        agentic->mcp_server_implemented,
        agentic->mcp_client_implemented,
        agentic->agent_execution_supported,
        agentic->model_execution_supported,
        agentic->tool_execution_supported,
        agentic->shell_execution_supported,
        agentic->manifest_present,
        agentic->manifest_signed,
        agentic->parameter_schema_present,
        agentic->parameter_schema_valid,
        agentic->freshness_valid,
        agentic->replay_detected,
        agentic->receipt_required,
        agentic->receipt_generated,
        agentic->cryptographic_verification_supported,
        agentic->capability_enforcement_supported,
        agentic->runtime_authority_requested,
        agentic->runtime_authority_granted,
        agentic->unknown_tool_allowed,
        agentic->unsigned_manifest_allowed,
        agentic->network_access_allowed,
        agentic->private_key_access_allowed,
        agentic->system_mutation_allowed,
        agentic->host_read_performed,
        agentic->host_write_performed,
        agentic->network_performed,
        agentic->mode,
        agentic->decision,
        agentic->reason,
        latticra_seal_agentic_automation_security_error_label(agentic->error),
        agentic->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
