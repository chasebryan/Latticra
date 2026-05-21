#include "latticra/seal_runtime_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_policy_decision_t unsigned_request_policy_fixture(void) {
    latticra_seal_policy_decision_t policy_decision;
    memset(&policy_decision, 0, sizeof(policy_decision));
    (void)snprintf(policy_decision.policy_decision_profile, sizeof(policy_decision.policy_decision_profile), "%s", "latticra-seal-policy-decision/0.1");
    (void)snprintf(policy_decision.policy_id, sizeof(policy_decision.policy_id), "%s", "unset");
    (void)snprintf(policy_decision.policy_version, sizeof(policy_decision.policy_version), "%s", "unset");
    (void)snprintf(policy_decision.requested_action, sizeof(policy_decision.requested_action), "%s", "inspect");
    (void)snprintf(policy_decision.requested_tool, sizeof(policy_decision.requested_tool), "%s", "declared-tool-without-signature");
    policy_decision.policy_decision_supported = 0u;
    policy_decision.policy_evaluation_supported = 0u;
    policy_decision.policy_enforcement_supported = 0u;
    policy_decision.policy_id_present = 0u;
    policy_decision.policy_version_present = 0u;
    policy_decision.requested_action_present = 0u;
    policy_decision.requested_tool_present = 0u;
    policy_decision.signed_request_present = 0u;
    policy_decision.signature_valid = 0u;
    policy_decision.schema_valid = 0u;
    policy_decision.freshness_valid = 0u;
    policy_decision.replay_detected = 0u;
    (void)snprintf(policy_decision.default_decision, sizeof(policy_decision.default_decision), "%s", "deny");
    (void)snprintf(policy_decision.decision_state, sizeof(policy_decision.decision_state), "%s", "report-only");
    policy_decision.decision_allowed = 0u;
    policy_decision.decision_denied = 1u;
    policy_decision.operator_review_required = 1u;
    policy_decision.unknown_tool_denied = 1u;
    policy_decision.unsigned_request_denied = 1u;
    policy_decision.invalid_schema_denied = 1u;
    policy_decision.stale_request_denied = 1u;
    policy_decision.replayed_request_denied = 1u;
    policy_decision.invalid_signature_denied = 1u;
    policy_decision.runtime_authority_granted = 0u;
    policy_decision.host_read_performed = 0u;
    policy_decision.host_write_performed = 0u;
    policy_decision.network_performed = 0u;
    (void)snprintf(policy_decision.mode, sizeof(policy_decision.mode), "%s", "report-only");
    (void)snprintf(policy_decision.decision, sizeof(policy_decision.decision), "%s", "report-only");
    (void)snprintf(policy_decision.reason, sizeof(policy_decision.reason), "%s", "unsigned-request-case");
    policy_decision.error = LATTICRA_SEAL_POLICY_DECISION_OK;
    (void)snprintf(policy_decision.status, sizeof(policy_decision.status), "%s", "policy-decision-metadata");
    return policy_decision;
}

static int unsigned_request_case_remains_blocked(void) {
    latticra_seal_policy_decision_t policy_decision = unsigned_request_policy_fixture();
    latticra_seal_runtime_gate_t gate;
    char rendered[LATTICRA_SEAL_RUNTIME_GATE_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, &gate) == LATTICRA_STATUS_OK, "gate construction status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_RUNTIME_GATE_OK, "gate ok");
    EXPECT_TRUE(strcmp(gate.runtime_enforcement_gate_profile, "latticra-seal-runtime-enforcement-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(gate.gate_state, "report-only") == 0, "gate state");
    EXPECT_TRUE(gate.default_blocked == 1u, "default blocked");
    EXPECT_TRUE(gate.unsigned_request_blocked == 1u, "unsigned request blocked");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(gate.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(gate.host_read_performed == 0u, "host read");
    EXPECT_TRUE(gate.host_write_performed == 0u, "host write");
    EXPECT_TRUE(gate.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_runtime_gate_is_report_only(&gate) == 1, "gate report-only helper");
    EXPECT_TRUE(latticra_seal_runtime_gate_report(&gate, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME GATE") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "gate_state=report-only") != 0, "render gate state");
    EXPECT_TRUE(strstr(rendered, "default_blocked=1") != 0, "render default blocked");
    EXPECT_TRUE(strstr(rendered, "unsigned_request_blocked=1") != 0, "render unsigned request blocked");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime authority");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    return 0;
}

int main(void) {
    if (unsigned_request_case_remains_blocked() != 0) {
        return 1;
    }
    printf("seal unsigned request case: ok\n");
    return 0;
}
