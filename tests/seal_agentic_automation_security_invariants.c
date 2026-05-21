#include "latticra/seal_agentic_automation_security.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_status_rollup_t fixture_rollup(void) {
    latticra_seal_status_rollup_t rollup;
    memset(&rollup, 0, sizeof(rollup));
    (void)snprintf(rollup.rollup_profile, sizeof(rollup.rollup_profile), "%s", "latticra-seal-status-rollup/0.1");
    rollup.report_present = 1u;
    rollup.measurement_present = 1u;
    rollup.manifest_present = 1u;
    rollup.signature_policy_present = 1u;
    rollup.signature_metadata_present = 1u;
    rollup.verification_policy_present = 1u;
    rollup.verification_receipt_present = 1u;
    rollup.capability_gate_present = 1u;
    rollup.effect_decision_present = 1u;
    rollup.runtime_handoff_present = 1u;
    rollup.cryptographic_verification_supported = 0u;
    rollup.verified = 0u;
    rollup.capability_gate_allowed = 0u;
    rollup.effect_allowed = 0u;
    rollup.handoff_active = 0u;
    (void)snprintf(rollup.runtime_boundary_state, sizeof(rollup.runtime_boundary_state), "%s", "disabled");
    rollup.runtime_authority_granted = 0u;
    rollup.host_read_performed = 0u;
    rollup.host_write_performed = 0u;
    rollup.network_performed = 0u;
    (void)snprintf(rollup.rollup_state, sizeof(rollup.rollup_state), "%s", "metadata-only");
    rollup.error = LATTICRA_SEAL_STATUS_ROLLUP_OK;
    (void)snprintf(rollup.status, sizeof(rollup.status), "%s", "status-rollup-metadata");
    return rollup;
}

static int agentic_report_stays_report_only(void) {
    latticra_seal_status_rollup_t rollup = fixture_rollup();
    latticra_seal_agentic_automation_security_t agentic;
    char rendered[LATTICRA_SEAL_AGENTIC_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_agentic_automation_security_from_rollup(&rollup, &agentic) == LATTICRA_STATUS_OK, "agentic status");
    EXPECT_TRUE(agentic.error == LATTICRA_SEAL_AGENTIC_OK, "agentic ok");
    EXPECT_TRUE(strcmp(agentic.agentic_profile, "latticra-seal-agentic-automation-security/0.1") == 0, "agentic profile");
    EXPECT_TRUE(strcmp(agentic.request_id, "unset") == 0, "request id");
    EXPECT_TRUE(strcmp(agentic.caller_id, "unset") == 0, "caller id");
    EXPECT_TRUE(strcmp(agentic.tool_id, "unset") == 0, "tool id");
    EXPECT_TRUE(strcmp(agentic.automation_context, "local-report-only") == 0, "automation context");
    EXPECT_TRUE(agentic.mcp_alignment_declared == 1u, "mcp alignment declared");
    EXPECT_TRUE(agentic.mcp_protocol_implemented == 0u, "mcp protocol");
    EXPECT_TRUE(agentic.mcp_server_implemented == 0u, "mcp server");
    EXPECT_TRUE(agentic.mcp_client_implemented == 0u, "mcp client");
    EXPECT_TRUE(agentic.agent_execution_supported == 0u, "agent execution");
    EXPECT_TRUE(agentic.model_execution_supported == 0u, "model execution");
    EXPECT_TRUE(agentic.tool_execution_supported == 0u, "tool execution");
    EXPECT_TRUE(agentic.shell_execution_supported == 0u, "shell execution");
    EXPECT_TRUE(agentic.manifest_present == 1u, "manifest present copied");
    EXPECT_TRUE(agentic.manifest_signed == 0u, "manifest signed");
    EXPECT_TRUE(agentic.parameter_schema_present == 0u, "parameter schema present");
    EXPECT_TRUE(agentic.parameter_schema_valid == 0u, "parameter schema valid");
    EXPECT_TRUE(agentic.freshness_valid == 0u, "freshness");
    EXPECT_TRUE(agentic.replay_detected == 0u, "replay");
    EXPECT_TRUE(agentic.receipt_required == 1u, "receipt required");
    EXPECT_TRUE(agentic.receipt_generated == 0u, "receipt generated");
    EXPECT_TRUE(agentic.cryptographic_verification_supported == 0u, "crypto verification");
    EXPECT_TRUE(agentic.capability_enforcement_supported == 0u, "capability enforcement");
    EXPECT_TRUE(agentic.runtime_authority_requested == 0u, "runtime authority requested");
    EXPECT_TRUE(agentic.runtime_authority_granted == 0u, "runtime authority granted");
    EXPECT_TRUE(agentic.unknown_tool_allowed == 0u, "unknown tool");
    EXPECT_TRUE(agentic.unsigned_manifest_allowed == 0u, "unsigned manifest");
    EXPECT_TRUE(agentic.network_access_allowed == 0u, "network access");
    EXPECT_TRUE(agentic.private_key_access_allowed == 0u, "private key access");
    EXPECT_TRUE(agentic.system_mutation_allowed == 0u, "system mutation");
    EXPECT_TRUE(agentic.host_read_performed == 0u, "host read");
    EXPECT_TRUE(agentic.host_write_performed == 0u, "host write");
    EXPECT_TRUE(agentic.network_performed == 0u, "network performed");
    EXPECT_TRUE(strcmp(agentic.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(agentic.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(agentic.reason, "metadata-only") == 0, "reason");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_is_report_only(&agentic) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_report(&agentic, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL AGENTIC AUTOMATION SECURITY") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "agentic_profile=latticra-seal-agentic-automation-security/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "mcp_alignment_declared=1") != 0, "render alignment");
    EXPECT_TRUE(strstr(rendered, "mcp_protocol_implemented=0") != 0, "render mcp protocol");
    EXPECT_TRUE(strstr(rendered, "agent_execution_supported=0") != 0, "render agent execution");
    EXPECT_TRUE(strstr(rendered, "tool_execution_supported=0") != 0, "render tool execution");
    EXPECT_TRUE(strstr(rendered, "shell_execution_supported=0") != 0, "render shell execution");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "unknown_tool_allowed=0") != 0, "render unknown tool");
    EXPECT_TRUE(strstr(rendered, "unsigned_manifest_allowed=0") != 0, "render unsigned manifest");
    EXPECT_TRUE(strstr(rendered, "system_mutation_allowed=0") != 0, "render system mutation");
    EXPECT_TRUE(strstr(rendered, "status=agentic-automation-security-metadata") != 0, "render status label");
    return 0;
}

static int agentic_report_fails_closed(void) {
    latticra_seal_status_rollup_t rollup = fixture_rollup();
    latticra_seal_agentic_automation_security_t agentic;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_agentic_automation_security_from_rollup(0, &agentic) == LATTICRA_STATUS_OK, "null rollup status");
    EXPECT_TRUE(agentic.error == LATTICRA_SEAL_AGENTIC_INVALID_INPUT, "null rollup error");
    rollup.cryptographic_verification_supported = 1u;
    EXPECT_TRUE(latticra_seal_agentic_automation_security_from_rollup(&rollup, &agentic) == LATTICRA_STATUS_OK, "bad rollup status");
    EXPECT_TRUE(agentic.error == LATTICRA_SEAL_AGENTIC_INVALID_ROLLUP, "bad rollup error");
    EXPECT_TRUE(strcmp(agentic.reason, "invalid-rollup") == 0, "bad rollup reason");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_from_rollup(&rollup, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_report(&agentic, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null agentic");
    EXPECT_TRUE(latticra_seal_agentic_automation_security_report(&agentic, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (agentic_report_stays_report_only() != 0) {
        return 1;
    }
    if (agentic_report_fails_closed() != 0) {
        return 1;
    }
    printf("seal agentic automation security invariants: ok\n");
    return 0;
}
