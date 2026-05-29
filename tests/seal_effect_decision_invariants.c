#include "latticra/seal_effect_decision.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_capability_gate_t fixture_gate(void) {
    latticra_seal_capability_gate_t gate;
    memset(&gate, 0, sizeof(gate));
    (void)snprintf(gate.gate_profile, sizeof(gate.gate_profile), "%s", "latticra-seal-capability-gate/0.1");
    (void)snprintf(gate.receipt_profile, sizeof(gate.receipt_profile), "%s", "latticra-seal-verification-receipt/0.1");
    (void)snprintf(gate.verification_policy_profile, sizeof(gate.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(gate.artifact_digest_algorithm, sizeof(gate.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        gate.artifact_digest_hex,
        sizeof(gate.artifact_digest_hex),
        "%s",
        "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
    (void)snprintf(gate.signer_identity_label, sizeof(gate.signer_identity_label), "%s", "latticra-dev-signer");
    (void)snprintf(gate.public_key_identity_label, sizeof(gate.public_key_identity_label), "%s", "latticra-dev-public-key");
    (void)snprintf(gate.receipt_state, sizeof(gate.receipt_state), "%s", "unverified-metadata");
    (void)snprintf(gate.verification_state, sizeof(gate.verification_state), "%s", "unsupported");
    (void)snprintf(gate.requested_capability, sizeof(gate.requested_capability), "%s", "seal.inspect");
    (void)snprintf(gate.requested_effect, sizeof(gate.requested_effect), "%s", "read-metadata");
    (void)snprintf(gate.requested_scope, sizeof(gate.requested_scope), "%s", "local-artifact");
    (void)snprintf(gate.gate_state, sizeof(gate.gate_state), "%s", "denied-unverified");
    gate.verified = 0u;
    gate.authority_usable = 0u;
    gate.receipt_capability_gate_allowed = 0u;
    gate.gate_allowed = 0u;
    gate.runtime_authority_granted = 0u;
    gate.error = LATTICRA_SEAL_CAPABILITY_GATE_OK;
    (void)snprintf(gate.status, sizeof(gate.status), "%s", "capability-gate-denied-metadata");
    return gate;
}

static int decision_copies_gate_metadata_and_denies(void) {
    latticra_seal_capability_gate_t gate = fixture_gate();
    latticra_seal_effect_decision_t decision;
    char rendered[LATTICRA_SEAL_EFFECT_DECISION_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "decision status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_OK, "decision ok");
    EXPECT_TRUE(strcmp(decision.decision_profile, "latticra-seal-effect-decision/0.1") == 0, "decision profile");
    EXPECT_TRUE(strcmp(decision.gate_profile, "latticra-seal-capability-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(decision.receipt_profile, "latticra-seal-verification-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(decision.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(decision.artifact_digest_hex, gate.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(decision.requested_capability, "seal.inspect") == 0, "requested capability");
    EXPECT_TRUE(strcmp(decision.requested_effect, "read-metadata") == 0, "requested effect");
    EXPECT_TRUE(strcmp(decision.requested_scope, "local-artifact") == 0, "requested scope");
    EXPECT_TRUE(strcmp(decision.gate_state, "denied-unverified") == 0, "gate state");
    EXPECT_TRUE(strcmp(decision.decision_state, "denied-gate") == 0, "decision state");
    EXPECT_TRUE(decision.gate_allowed == 0u, "gate allowed");
    EXPECT_TRUE(decision.effect_allowed == 0u, "effect allowed");
    EXPECT_TRUE(decision.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(decision.host_read_performed == 0u, "host read");
    EXPECT_TRUE(decision.host_write_performed == 0u, "host write");
    EXPECT_TRUE(decision.network_performed == 0u, "network");
    EXPECT_TRUE(decision.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(latticra_seal_effect_decision_is_denied_metadata(&decision) == 1, "denied metadata helper");
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL EFFECT DECISION") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "decision_state=denied-gate") != 0, "render decision state");
    EXPECT_TRUE(strstr(rendered, "gate_allowed=0") != 0, "render gate allowed");
    EXPECT_TRUE(strstr(rendered, "effect_allowed=0") != 0, "render effect allowed");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect performed");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int decision_fails_closed(void) {
    latticra_seal_capability_gate_t gate = fixture_gate();
    latticra_seal_effect_decision_t decision;
    char tiny[1];
    char rendered[LATTICRA_SEAL_EFFECT_DECISION_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(0, &decision) == LATTICRA_STATUS_OK, "null gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT, "null gate error");
    gate.error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "bad gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE, "bad gate error");
    gate = fixture_gate();
    memset(gate.gate_profile, 'z', sizeof(gate.gate_profile));
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "unterminated gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE, "unterminated gate error");
    gate = fixture_gate();
    gate.gate_allowed = 2u;
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "invalid gate flag status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE, "invalid gate flag error");
    gate = fixture_gate();
    gate.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "authority gate status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_INVALID_GATE, "authority gate error");
    gate = fixture_gate();
    gate.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_MISSING_DIGEST, "missing digest error");
    gate = fixture_gate();
    gate.requested_capability[0] = '\0';
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "missing capability status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_CAPABILITY, "missing capability error");
    gate = fixture_gate();
    gate.requested_effect[0] = '\0';
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "missing effect status");
    EXPECT_TRUE(decision.error == LATTICRA_SEAL_EFFECT_DECISION_MISSING_REQUESTED_EFFECT, "missing effect error");
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_effect_decision_is_denied_metadata(0) == 0, "null helper");
    gate = fixture_gate();
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "small buffer decision source");
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_effect_decision_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null decision");
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");

    gate = fixture_gate();
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "tamper decision source");
    memset(decision.decision_profile, 'z', sizeof(decision.decision_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated effect decision render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated effect decision render cleared");
    EXPECT_TRUE(latticra_seal_effect_decision_is_denied_metadata(&decision) == 0,
                "unterminated effect decision helper rejected");

    gate = fixture_gate();
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "authority effect decision source");
    decision.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority effect decision render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority effect decision render cleared");
    EXPECT_TRUE(latticra_seal_effect_decision_is_denied_metadata(&decision) == 0,
                "authority effect decision helper rejected");

    gate = fixture_gate();
    EXPECT_TRUE(latticra_seal_effect_decision_from_gate(&gate, &decision) == LATTICRA_STATUS_OK, "flag effect decision source");
    decision.effect_allowed = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_effect_decision_report(&decision, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "flag effect decision render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "flag effect decision render cleared");
    EXPECT_TRUE(latticra_seal_effect_decision_is_denied_metadata(&decision) == 0,
                "flag effect decision helper rejected");
    return 0;
}

int main(void) {
    if (decision_copies_gate_metadata_and_denies() != 0) {
        return 1;
    }
    if (decision_fails_closed() != 0) {
        return 1;
    }
    printf("seal effect decision invariants: ok\n");
    return 0;
}
