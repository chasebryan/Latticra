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

static latticra_seal_policy_decision_t fixture_policy_decision(void) {
    latticra_seal_policy_decision_t policy_decision;
    memset(&policy_decision, 0, sizeof(policy_decision));
    (void)snprintf(policy_decision.policy_decision_profile, sizeof(policy_decision.policy_decision_profile), "%s", "latticra-seal-policy-decision/0.1");
    (void)snprintf(policy_decision.policy_id, sizeof(policy_decision.policy_id), "%s", "unset");
    (void)snprintf(policy_decision.policy_version, sizeof(policy_decision.policy_version), "%s", "unset");
    (void)snprintf(policy_decision.requested_action, sizeof(policy_decision.requested_action), "%s", "unset");
    (void)snprintf(policy_decision.requested_tool, sizeof(policy_decision.requested_tool), "%s", "unset");
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
    (void)snprintf(policy_decision.reason, sizeof(policy_decision.reason), "%s", "policy-decision-metadata-only");
    policy_decision.error = LATTICRA_SEAL_POLICY_DECISION_OK;
    (void)snprintf(policy_decision.status, sizeof(policy_decision.status), "%s", "policy-decision-metadata");
    return policy_decision;
}

static int runtime_gate_stays_report_only_and_blocked(void) {
    latticra_seal_policy_decision_t policy_decision = fixture_policy_decision();
    latticra_seal_runtime_gate_t gate;
    char rendered[LATTICRA_SEAL_RUNTIME_GATE_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, &gate) == LATTICRA_STATUS_OK, "runtime gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_RUNTIME_GATE_OK, "runtime gate ok");
    EXPECT_TRUE(strcmp(gate.runtime_enforcement_gate_profile, "latticra-seal-runtime-enforcement-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(gate.gate_id, "unset") == 0, "gate id");
    EXPECT_TRUE(strcmp(gate.gate_version, "unset") == 0, "gate version");
    EXPECT_TRUE(strcmp(gate.gate_state, "report-only") == 0, "gate state");
    EXPECT_TRUE(gate.runtime_enforcement_gate_supported == 0u, "gate supported");
    EXPECT_TRUE(gate.runtime_enforcement_supported == 0u, "runtime enforcement supported");
    EXPECT_TRUE(gate.runtime_enforcement_active == 0u, "runtime enforcement active");
    EXPECT_TRUE(gate.policy_decision_input_supported == 0u, "policy decision input supported");
    EXPECT_TRUE(gate.policy_decision_consumed == 0u, "policy decision consumed");
    EXPECT_TRUE(gate.runtime_handoff_eligible == 0u, "runtime handoff eligible");
    EXPECT_TRUE(gate.runtime_handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(gate.allow_enforcement_supported == 0u, "allow enforcement supported");
    EXPECT_TRUE(gate.deny_enforcement_supported == 0u, "deny enforcement supported");
    EXPECT_TRUE(gate.allow_enforcement_performed == 0u, "allow enforcement performed");
    EXPECT_TRUE(gate.deny_enforcement_performed == 0u, "deny enforcement performed");
    EXPECT_TRUE(gate.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(gate.default_blocked == 1u, "default blocked");
    EXPECT_TRUE(gate.operator_review_required == 1u, "operator review required");
    EXPECT_TRUE(gate.unknown_tool_blocked == 1u, "unknown tool blocked");
    EXPECT_TRUE(gate.unsigned_request_blocked == 1u, "unsigned request blocked");
    EXPECT_TRUE(gate.invalid_schema_blocked == 1u, "invalid schema blocked");
    EXPECT_TRUE(gate.stale_request_blocked == 1u, "stale request blocked");
    EXPECT_TRUE(gate.replayed_request_blocked == 1u, "replayed request blocked");
    EXPECT_TRUE(gate.invalid_signature_blocked == 1u, "invalid signature blocked");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(gate.host_read_performed == 0u, "host read");
    EXPECT_TRUE(gate.host_write_performed == 0u, "host write");
    EXPECT_TRUE(gate.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(gate.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(gate.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(gate.reason, "runtime-gate-metadata-only") == 0, "reason");
    EXPECT_TRUE(strcmp(gate.status, "runtime-gate-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_runtime_gate_is_report_only(&gate) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_runtime_gate_report(&gate, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME GATE") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "runtime_enforcement_gate_profile=latticra-seal-runtime-enforcement-gate/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "gate_state=report-only") != 0, "render gate state");
    EXPECT_TRUE(strstr(rendered, "runtime_enforcement_active=0") != 0, "render active");
    EXPECT_TRUE(strstr(rendered, "runtime_handoff_eligible=0") != 0, "render handoff eligible");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect");
    EXPECT_TRUE(strstr(rendered, "default_blocked=1") != 0, "render blocked");
    EXPECT_TRUE(strstr(rendered, "operator_review_required=1") != 0, "render operator review");
    EXPECT_TRUE(strstr(rendered, "unknown_tool_blocked=1") != 0, "render unknown tool");
    EXPECT_TRUE(strstr(rendered, "unsigned_request_blocked=1") != 0, "render unsigned request");
    EXPECT_TRUE(strstr(rendered, "stale_request_blocked=1") != 0, "render stale request");
    EXPECT_TRUE(strstr(rendered, "replayed_request_blocked=1") != 0, "render replayed request");
    EXPECT_TRUE(strstr(rendered, "invalid_signature_blocked=1") != 0, "render invalid signature");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "status=runtime-gate-metadata") != 0, "render status label");
    return 0;
}

static int runtime_gate_fails_closed(void) {
    latticra_seal_policy_decision_t policy_decision = fixture_policy_decision();
    latticra_seal_runtime_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(0, &gate) == LATTICRA_STATUS_OK, "null policy status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_RUNTIME_GATE_INVALID_INPUT, "null policy error");
    policy_decision.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, &gate) == LATTICRA_STATUS_OK, "bad policy status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_RUNTIME_GATE_INVALID_POLICY_DECISION, "bad policy error");
    EXPECT_TRUE(strcmp(gate.reason, "invalid-policy-decision") == 0, "bad policy reason");
    EXPECT_TRUE(latticra_seal_runtime_gate_from_policy_decision(&policy_decision, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_runtime_gate_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_runtime_gate_report(&gate, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_runtime_gate_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null gate");
    EXPECT_TRUE(latticra_seal_runtime_gate_report(&gate, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (runtime_gate_stays_report_only_and_blocked() != 0) {
        return 1;
    }
    if (runtime_gate_fails_closed() != 0) {
        return 1;
    }
    printf("seal runtime gate invariants: ok\n");
    return 0;
}
