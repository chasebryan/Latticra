#include "latticra/seal_verified_effect_decision.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_verified_capability_gate_t fixture_gate(const char *effect) {
    latticra_seal_verified_capability_gate_t gate;
    memset(&gate, 0, sizeof(gate));
    (void)snprintf(gate.gate_profile, sizeof(gate.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(gate.receipt_profile, sizeof(gate.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(gate.verify_profile, sizeof(gate.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(gate.message_digest_algorithm, sizeof(gate.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(gate.message_digest_hex, sizeof(gate.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(gate.public_key_identity_label, sizeof(gate.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(gate.receipt_state, sizeof(gate.receipt_state), "%s", "verified");
    (void)snprintf(gate.verification_state, sizeof(gate.verification_state), "%s", "verified");
    (void)snprintf(gate.requested_capability, sizeof(gate.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(gate.requested_effect, sizeof(gate.requested_effect), "%s", effect != 0 ? effect : "report-only");
    (void)snprintf(gate.requested_scope, sizeof(gate.requested_scope), "%s", "local-fixture-scope");
    gate.verified = 1u;
    gate.authority_usable = 0u;
    gate.receipt_capability_gate_allowed = 0u;
    gate.gate_allowed = 1u;
    (void)snprintf(gate.gate_state, sizeof(gate.gate_state), "%s", "allowed-metadata-only");
    gate.runtime_authority_granted = 0u;
    gate.effect_performed = 0u;
    gate.host_read_performed = 0u;
    gate.host_write_performed = 0u;
    gate.network_performed = 0u;
    gate.error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK;
    (void)snprintf(gate.status, sizeof(gate.status), "%s", "verified-capability-gate-metadata");
    return gate;
}

static int decision_allows_report_only_metadata(void) {
    latticra_seal_verified_capability_gate_t gate = fixture_gate("report-only");
    latticra_seal_verified_effect_decision_t decision;
    char rendered[LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK,
        "report decision status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK, "report decision ok");
    EXPECT_TRUE(strcmp(decision.decision_profile, "latticra-seal-verified-effect-decision/0.1") == 0, "decision profile");
    EXPECT_TRUE(strcmp(decision.gate_profile, gate.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(decision.receipt_profile, gate.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(decision.verify_profile, gate.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(decision.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(decision.message_digest_hex, gate.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(decision.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(decision.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(decision.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(decision.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(decision.verified == 1u, "verified");
    EXPECT_TRUE(decision.authority_usable == 0u, "authority usable");
    EXPECT_TRUE(decision.receipt_capability_gate_allowed == 0u, "receipt capability flag");
    EXPECT_TRUE(decision.gate_allowed == 1u, "gate allowed");
    EXPECT_TRUE(strcmp(decision.gate_state, "allowed-metadata-only") == 0, "gate state");
    EXPECT_TRUE(strcmp(decision.decision_state, "allowed-report-only") == 0, "decision state");
    EXPECT_TRUE(decision.effect_allowed == 1u, "effect allowed");
    EXPECT_TRUE(decision.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(decision.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(decision.host_read_performed == 0u, "host read");
    EXPECT_TRUE(decision.host_write_performed == 0u, "host write");
    EXPECT_TRUE(decision.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_is_metadata_only(&decision) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_report(&decision, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "report render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL VERIFIED EFFECT DECISION") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "decision_state=allowed-report-only") != 0, "report decision");
    EXPECT_TRUE(strstr(rendered, "effect_allowed=1") != 0, "report effect allowed");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "report effect performed");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "report host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "report host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "report network");
    return 0;
}

static int decision_allows_evaluate_only_metadata(void) {
    latticra_seal_verified_capability_gate_t gate = fixture_gate("evaluate-only");
    latticra_seal_verified_effect_decision_t decision;

    EXPECT_TRUE(
        latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK,
        "evaluate decision status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK, "evaluate decision ok");
    EXPECT_TRUE(strcmp(decision.decision_state, "allowed-evaluate-only") == 0, "evaluate decision state");
    EXPECT_TRUE(decision.effect_allowed == 1u, "evaluate effect allowed");
    EXPECT_TRUE(decision.effect_performed == 0u, "evaluate effect performed");
    EXPECT_TRUE(decision.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(decision.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(decision.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(decision.network_performed == 0u, "evaluate network");
    return 0;
}

static int decision_fails_closed(void) {
    latticra_seal_verified_capability_gate_t gate = fixture_gate("report-only");
    latticra_seal_verified_effect_decision_t decision;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(0, &decision) == LATTICRA_STATUS_OK, "null gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_INPUT, "null gate error");
    gate.error = LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "invalid gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_GATE, "invalid gate error");
    gate = fixture_gate("report-only");
    gate.gate_allowed = 0u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "denied gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_GATE, "denied gate error");
    gate = fixture_gate("report-only");
    (void)snprintf(gate.gate_state, sizeof(gate.gate_state), "%s", "denied-gate");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "denied state status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_GATE, "denied state error");
    gate = fixture_gate("report-only");
    gate.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_RUNTIME_AUTHORITY, "runtime error");
    gate = fixture_gate("report-only");
    gate.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT, "effect error");
    gate = fixture_gate("report-only");
    gate.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT, "host read error");
    gate = fixture_gate("report-only");
    gate.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_HOST_EFFECT, "host write error");
    gate = fixture_gate("report-only");
    gate.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_NETWORK_EFFECT, "network error");
    gate = fixture_gate("report-only");
    gate.requested_effect[0] = '\0';
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "missing effect status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_MISSING_REQUESTED_EFFECT, "missing effect error");
    EXPECT_TRUE(strcmp(decision.decision_state, "denied-effect") == 0, "missing effect state");
    gate = fixture_gate("execute-tool");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "unknown effect status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_DENIED_UNKNOWN_EFFECT, "unknown effect error");
    EXPECT_TRUE(strcmp(decision.decision_state, "denied-effect") == 0, "unknown effect state");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_from_gate(&gate, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_report(&decision, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null decision report");
    EXPECT_TRUE(latticra_seal_verified_effect_decision_report(&decision, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer report");
    return 0;
}

int main(void) {
    if (decision_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (decision_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (decision_fails_closed() != 0) {
        return 1;
    }
    printf("seal verified effect decision invariants: ok\n");
    return 0;
}
