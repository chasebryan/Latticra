#include "latticra/seal_verified_capability_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_verified_receipt_promotion_t fixture_receipt(void) {
    latticra_seal_verified_receipt_promotion_t receipt;
    memset(&receipt, 0, sizeof(receipt));
    (void)snprintf(receipt.receipt_profile, sizeof(receipt.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(receipt.verify_profile, sizeof(receipt.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(receipt.backend_profile, sizeof(receipt.backend_profile), "%s", "latticra-seal-crypto-verify-backend/0.1");
    (void)snprintf(receipt.verification_policy_profile, sizeof(receipt.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(receipt.message_label, sizeof(receipt.message_label), "%s", "rfc8032-test-vector-2");
    receipt.message_size_bytes = 1u;
    (void)snprintf(receipt.message_digest_algorithm, sizeof(receipt.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(receipt.message_digest_hex, sizeof(receipt.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(receipt.public_key_identity_label, sizeof(receipt.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(receipt.signature_algorithm, sizeof(receipt.signature_algorithm), "%s", "Ed25519-development");
    (void)snprintf(receipt.trust_source, sizeof(receipt.trust_source), "%s", "local-test-vector");
    (void)snprintf(receipt.verification_state, sizeof(receipt.verification_state), "%s", "verified");
    (void)snprintf(receipt.receipt_state, sizeof(receipt.receipt_state), "%s", "verified");
    receipt.cryptographic_verification_supported = 1u;
    receipt.cryptographic_verification_performed = 1u;
    receipt.verified = 1u;
    receipt.invalid = 0u;
    receipt.authority_usable = 0u;
    receipt.capability_gate_allowed = 0u;
    receipt.runtime_authority_granted = 0u;
    receipt.error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK;
    (void)snprintf(receipt.status, sizeof(receipt.status), "%s", "verified-receipt-metadata");
    return receipt;
}

static int gate_allows_metadata_only(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_verified_capability_gate_t gate;
    char rendered[LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_verified_capability_gate_from_receipt(
            &receipt,
            "verified-receipt-report",
            "report-only",
            "local-fixture-scope",
            &gate) == LATTICRA_STATUS_OK,
        "gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK, "gate ok");
    EXPECT_TRUE(strcmp(gate.gate_profile, "latticra-seal-verified-capability-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(gate.receipt_profile, "latticra-seal-verified-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(gate.verify_profile, "latticra-seal-ed25519-verify/0.1") == 0, "verify profile");
    EXPECT_TRUE(strcmp(gate.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(gate.message_digest_hex, receipt.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(gate.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(gate.receipt_state, "verified") == 0, "receipt state");
    EXPECT_TRUE(strcmp(gate.verification_state, "verified") == 0, "verification state");
    EXPECT_TRUE(strcmp(gate.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(gate.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(gate.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(gate.verified == 1u, "verified flag");
    EXPECT_TRUE(gate.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(gate.receipt_capability_gate_allowed == 0u, "receipt capability flag");
    EXPECT_TRUE(gate.gate_allowed == 1u, "gate allowed");
    EXPECT_TRUE(strcmp(gate.gate_state, "allowed-metadata-only") == 0, "gate state");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(gate.effect_performed == 0u, "effect flag");
    EXPECT_TRUE(gate.host_read_performed == 0u, "host read flag");
    EXPECT_TRUE(gate.host_write_performed == 0u, "host write flag");
    EXPECT_TRUE(gate.network_performed == 0u, "network flag");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_is_metadata_only(&gate) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_report(&gate, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL VERIFIED CAPABILITY GATE") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "gate_allowed=1") != 0, "report gate allowed");
    EXPECT_TRUE(strstr(rendered, "gate_state=allowed-metadata-only") != 0, "report gate state");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime flag");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "report effect flag");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "report host read flag");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "report host write flag");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "report network flag");
    return 0;
}

static int gate_allows_evaluate_only_inspection(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_verified_capability_gate_t gate;

    EXPECT_TRUE(
        latticra_seal_verified_capability_gate_from_receipt(
            &receipt,
            "verified-receipt-inspection",
            "evaluate-only",
            0,
            &gate) == LATTICRA_STATUS_OK,
        "evaluate-only status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_OK, "evaluate-only ok");
    EXPECT_TRUE(gate.gate_allowed == 1u, "evaluate-only allowed");
    EXPECT_TRUE(strcmp(gate.gate_state, "allowed-metadata-only") == 0, "evaluate-only gate state");
    EXPECT_TRUE(strcmp(gate.requested_scope, "unspecified-scope") == 0, "default scope");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "evaluate runtime flag");
    EXPECT_TRUE(gate.effect_performed == 0u, "evaluate effect flag");
    return 0;
}

static int gate_fails_closed(void) {
    latticra_seal_verified_receipt_promotion_t receipt = fixture_receipt();
    latticra_seal_verified_capability_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(0, "verified-receipt-report", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "null receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_INPUT, "null receipt error");
    receipt.error = LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "invalid receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_INVALID_RECEIPT, "invalid receipt error");
    receipt = fixture_receipt();
    (void)snprintf(receipt.receipt_state, sizeof(receipt.receipt_state), "%s", "unverified-metadata");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "unverified receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNVERIFIED, "unverified receipt error");
    receipt = fixture_receipt();
    receipt.invalid = 1u;
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "invalid flag status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_INVALID_RECEIPT, "invalid flag error");
    receipt = fixture_receipt();
    receipt.message_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_INVALID_RECEIPT, "missing digest error");
    receipt = fixture_receipt();
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, 0, "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "missing capability status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY, "missing capability error");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "unknown-capability", "report-only", "scope", &gate) == LATTICRA_STATUS_OK, "unknown capability status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_CAPABILITY, "unknown capability error");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", 0, "scope", &gate) == LATTICRA_STATUS_OK, "missing effect status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT, "missing effect error");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "execute-tool", "scope", &gate) == LATTICRA_STATUS_OK, "unknown effect status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_DENIED_UNKNOWN_EFFECT, "unknown effect error");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_from_receipt(&receipt, "verified-receipt-report", "report-only", "scope", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_report(&gate, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer clear");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null gate report");
    EXPECT_TRUE(latticra_seal_verified_capability_gate_report(&gate, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer report");
    return 0;
}

int main(void) {
    if (gate_allows_metadata_only() != 0) {
        return 1;
    }
    if (gate_allows_evaluate_only_inspection() != 0) {
        return 1;
    }
    if (gate_fails_closed() != 0) {
        return 1;
    }
    printf("seal verified capability gate invariants: ok\n");
    return 0;
}
