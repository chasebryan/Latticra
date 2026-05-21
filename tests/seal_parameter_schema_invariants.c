#include "latticra/seal_parameter_schema.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

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

static int parameter_schema_stays_report_only(void) {
    latticra_seal_agentic_automation_security_t agentic = fixture_agentic();
    latticra_seal_parameter_schema_t schema;
    char rendered[LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_parameter_schema_from_agentic(&agentic, &schema) == LATTICRA_STATUS_OK, "schema status");
    EXPECT_TRUE(schema.error == LATTICRA_SEAL_PARAMETER_SCHEMA_OK, "schema ok");
    EXPECT_TRUE(strcmp(schema.schema_profile, "latticra-seal-parameter-schema/0.1") == 0, "schema profile");
    EXPECT_TRUE(strcmp(schema.schema_id, "unset") == 0, "schema id");
    EXPECT_TRUE(strcmp(schema.schema_version, "unset") == 0, "schema version");
    EXPECT_TRUE(strcmp(schema.schema_language, "unset") == 0, "schema language");
    EXPECT_TRUE(strcmp(schema.schema_hash, "unset") == 0, "schema hash");
    EXPECT_TRUE(schema.schema_present == 0u, "schema present");
    EXPECT_TRUE(schema.schema_parsing_supported == 0u, "schema parsing supported");
    EXPECT_TRUE(schema.schema_validation_supported == 0u, "schema validation supported");
    EXPECT_TRUE(schema.schema_valid == 0u, "schema valid");
    EXPECT_TRUE(schema.max_input_bytes_declared == 0u, "max input bytes");
    EXPECT_TRUE(schema.parameter_count_declared == 0u, "parameter count");
    EXPECT_TRUE(schema.required_parameter_count_declared == 0u, "required parameter count");
    EXPECT_TRUE(schema.unknown_parameters_allowed == 0u, "unknown parameters allowed");
    EXPECT_TRUE(schema.parameter_forwarding_allowed == 0u, "parameter forwarding allowed");
    EXPECT_TRUE(schema.input_size_within_limit == 0u, "input size within limit");
    EXPECT_TRUE(schema.parameter_names_reported == 0u, "parameter names reported");
    EXPECT_TRUE(schema.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(schema.host_read_performed == 0u, "host read");
    EXPECT_TRUE(schema.host_write_performed == 0u, "host write");
    EXPECT_TRUE(schema.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(schema.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(schema.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(schema.reason, "parameter-schema-metadata-only") == 0, "reason");
    EXPECT_TRUE(strcmp(schema.status, "parameter-schema-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_parameter_schema_is_report_only(&schema) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_parameter_schema_report(&schema, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL PARAMETER SCHEMA") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "schema_profile=latticra-seal-parameter-schema/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "schema_present=0") != 0, "render schema present");
    EXPECT_TRUE(strstr(rendered, "schema_parsing_supported=0") != 0, "render schema parsing");
    EXPECT_TRUE(strstr(rendered, "schema_validation_supported=0") != 0, "render schema validation");
    EXPECT_TRUE(strstr(rendered, "schema_valid=0") != 0, "render schema valid");
    EXPECT_TRUE(strstr(rendered, "unknown_parameters_allowed=0") != 0, "render unknown parameters");
    EXPECT_TRUE(strstr(rendered, "parameter_forwarding_allowed=0") != 0, "render parameter forwarding");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "mode=report-only") != 0, "render mode");
    EXPECT_TRUE(strstr(rendered, "decision=report-only") != 0, "render decision");
    EXPECT_TRUE(strstr(rendered, "status=parameter-schema-metadata") != 0, "render status label");
    return 0;
}

static int parameter_schema_fails_closed(void) {
    latticra_seal_agentic_automation_security_t agentic = fixture_agentic();
    latticra_seal_parameter_schema_t schema;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_parameter_schema_from_agentic(0, &schema) == LATTICRA_STATUS_OK, "null agentic status");
    EXPECT_TRUE(schema.error == LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_INPUT, "null agentic error");
    agentic.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_parameter_schema_from_agentic(&agentic, &schema) == LATTICRA_STATUS_OK, "bad agentic status");
    EXPECT_TRUE(schema.error == LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_AGENTIC, "bad agentic error");
    EXPECT_TRUE(strcmp(schema.reason, "invalid-agentic") == 0, "bad agentic reason");
    EXPECT_TRUE(latticra_seal_parameter_schema_from_agentic(&agentic, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_parameter_schema_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_parameter_schema_report(&schema, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_parameter_schema_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null schema");
    EXPECT_TRUE(latticra_seal_parameter_schema_report(&schema, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (parameter_schema_stays_report_only() != 0) {
        return 1;
    }
    if (parameter_schema_fails_closed() != 0) {
        return 1;
    }
    printf("seal parameter schema invariants: ok\n");
    return 0;
}
