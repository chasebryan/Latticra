#include "latticra/seal_policy_decision.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_signed_request_t fixture_signed_request(void) {
    latticra_seal_signed_request_t signed_request;
    memset(&signed_request, 0, sizeof(signed_request));
    (void)snprintf(signed_request.signed_request_profile, sizeof(signed_request.signed_request_profile), "%s", "latticra-seal-signed-request/0.1");
    (void)snprintf(signed_request.signed_request_id, sizeof(signed_request.signed_request_id), "%s", "unset");
    (void)snprintf(signed_request.signature_algorithm, sizeof(signed_request.signature_algorithm), "%s", "unset");
    (void)snprintf(signed_request.signing_key_id, sizeof(signed_request.signing_key_id), "%s", "unset");
    (void)snprintf(signed_request.signature_hash, sizeof(signed_request.signature_hash), "%s", "unset");
    signed_request.signed_request_supported = 0u;
    signed_request.signature_generation_supported = 0u;
    signed_request.signature_verification_supported = 0u;
    signed_request.signature_present = 0u;
    signed_request.signature_valid = 0u;
    signed_request.signature_algorithm_declared = 0u;
    signed_request.signing_key_id_present = 0u;
    signed_request.signature_hash_present = 0u;
    signed_request.signed_request_id_present = 0u;
    signed_request.identity_binding_declared = 0u;
    signed_request.context_binding_declared = 0u;
    signed_request.parameter_binding_declared = 0u;
    signed_request.freshness_binding_declared = 0u;
    signed_request.policy_binding_declared = 0u;
    signed_request.trust_store_supported = 0u;
    signed_request.revocation_lookup_supported = 0u;
    signed_request.runtime_authority_granted = 0u;
    signed_request.host_read_performed = 0u;
    signed_request.host_write_performed = 0u;
    signed_request.network_performed = 0u;
    (void)snprintf(signed_request.mode, sizeof(signed_request.mode), "%s", "report-only");
    (void)snprintf(signed_request.decision, sizeof(signed_request.decision), "%s", "report-only");
    (void)snprintf(signed_request.reason, sizeof(signed_request.reason), "%s", "signed-request-metadata-only");
    signed_request.error = LATTICRA_SEAL_SIGNED_REQUEST_OK;
    (void)snprintf(signed_request.status, sizeof(signed_request.status), "%s", "signed-request-metadata");
    return signed_request;
}

static int policy_decision_stays_report_only_and_default_denied(void) {
    latticra_seal_signed_request_t signed_request = fixture_signed_request();
    latticra_seal_policy_decision_t policy_decision;
    char rendered[LATTICRA_SEAL_POLICY_DECISION_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) == LATTICRA_STATUS_OK, "policy decision status");
    EXPECT_TRUE(policy_decision.error == LATTICRA_SEAL_POLICY_DECISION_OK, "policy decision ok");
    EXPECT_TRUE(strcmp(policy_decision.policy_decision_profile, "latticra-seal-policy-decision/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(policy_decision.policy_id, "unset") == 0, "policy id");
    EXPECT_TRUE(strcmp(policy_decision.policy_version, "unset") == 0, "policy version");
    EXPECT_TRUE(strcmp(policy_decision.requested_action, "unset") == 0, "requested action");
    EXPECT_TRUE(strcmp(policy_decision.requested_tool, "unset") == 0, "requested tool");
    EXPECT_TRUE(policy_decision.policy_decision_supported == 0u, "decision supported");
    EXPECT_TRUE(policy_decision.policy_evaluation_supported == 0u, "evaluation supported");
    EXPECT_TRUE(policy_decision.policy_enforcement_supported == 0u, "enforcement supported");
    EXPECT_TRUE(policy_decision.policy_id_present == 0u, "policy id present");
    EXPECT_TRUE(policy_decision.policy_version_present == 0u, "policy version present");
    EXPECT_TRUE(policy_decision.requested_action_present == 0u, "requested action present");
    EXPECT_TRUE(policy_decision.requested_tool_present == 0u, "requested tool present");
    EXPECT_TRUE(policy_decision.signed_request_present == 0u, "signed request present");
    EXPECT_TRUE(policy_decision.signature_valid == 0u, "signature valid");
    EXPECT_TRUE(policy_decision.schema_valid == 0u, "schema valid");
    EXPECT_TRUE(policy_decision.freshness_valid == 0u, "freshness valid");
    EXPECT_TRUE(policy_decision.replay_detected == 0u, "replay detected");
    EXPECT_TRUE(strcmp(policy_decision.default_decision, "deny") == 0, "default decision");
    EXPECT_TRUE(strcmp(policy_decision.decision_state, "report-only") == 0, "decision state");
    EXPECT_TRUE(policy_decision.decision_allowed == 0u, "decision allowed");
    EXPECT_TRUE(policy_decision.decision_denied == 1u, "decision denied");
    EXPECT_TRUE(policy_decision.operator_review_required == 1u, "operator review");
    EXPECT_TRUE(policy_decision.unknown_tool_denied == 1u, "unknown tool denied");
    EXPECT_TRUE(policy_decision.unsigned_request_denied == 1u, "unsigned request denied");
    EXPECT_TRUE(policy_decision.invalid_schema_denied == 1u, "invalid schema denied");
    EXPECT_TRUE(policy_decision.stale_request_denied == 1u, "stale request denied");
    EXPECT_TRUE(policy_decision.replayed_request_denied == 1u, "replayed request denied");
    EXPECT_TRUE(policy_decision.invalid_signature_denied == 1u, "invalid signature denied");
    EXPECT_TRUE(policy_decision.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(policy_decision.host_read_performed == 0u, "host read");
    EXPECT_TRUE(policy_decision.host_write_performed == 0u, "host write");
    EXPECT_TRUE(policy_decision.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(policy_decision.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(policy_decision.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(policy_decision.reason, "policy-decision-metadata-only") == 0, "reason");
    EXPECT_TRUE(strcmp(policy_decision.status, "policy-decision-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_policy_decision_is_report_only(&policy_decision) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_policy_decision_report(&policy_decision, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL POLICY DECISION") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "policy_decision_profile=latticra-seal-policy-decision/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "default_decision=deny") != 0, "render default decision");
    EXPECT_TRUE(strstr(rendered, "decision_allowed=0") != 0, "render allowed");
    EXPECT_TRUE(strstr(rendered, "decision_denied=1") != 0, "render denied");
    EXPECT_TRUE(strstr(rendered, "operator_review_required=1") != 0, "render operator review");
    EXPECT_TRUE(strstr(rendered, "unknown_tool_denied=1") != 0, "render unknown tool");
    EXPECT_TRUE(strstr(rendered, "unsigned_request_denied=1") != 0, "render unsigned request");
    EXPECT_TRUE(strstr(rendered, "stale_request_denied=1") != 0, "render stale request");
    EXPECT_TRUE(strstr(rendered, "replayed_request_denied=1") != 0, "render replayed request");
    EXPECT_TRUE(strstr(rendered, "invalid_signature_denied=1") != 0, "render invalid signature");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "status=policy-decision-metadata") != 0, "render status label");
    return 0;
}

static int policy_decision_fails_closed(void) {
    latticra_seal_signed_request_t signed_request = fixture_signed_request();
    latticra_seal_policy_decision_t policy_decision;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(0, &policy_decision) == LATTICRA_STATUS_OK, "null signed request status");
    EXPECT_TRUE(policy_decision.error == LATTICRA_SEAL_POLICY_DECISION_INVALID_INPUT, "null signed request error");
    signed_request.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, &policy_decision) == LATTICRA_STATUS_OK, "bad signed request status");
    EXPECT_TRUE(policy_decision.error == LATTICRA_SEAL_POLICY_DECISION_INVALID_SIGNED_REQUEST, "bad signed request error");
    EXPECT_TRUE(strcmp(policy_decision.reason, "invalid-signed-request") == 0, "bad signed request reason");
    EXPECT_TRUE(latticra_seal_policy_decision_from_signed_request(&signed_request, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_policy_decision_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_policy_decision_report(&policy_decision, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_policy_decision_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null policy decision");
    EXPECT_TRUE(latticra_seal_policy_decision_report(&policy_decision, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (policy_decision_stays_report_only_and_default_denied() != 0) {
        return 1;
    }
    if (policy_decision_fails_closed() != 0) {
        return 1;
    }
    printf("seal policy decision invariants: ok\n");
    return 0;
}
