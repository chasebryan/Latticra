#include "latticra/seal_capability_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_verification_receipt_t fixture_receipt(void) {
    latticra_seal_verification_receipt_t receipt;
    memset(&receipt, 0, sizeof(receipt));
    (void)snprintf(receipt.receipt_profile, sizeof(receipt.receipt_profile), "%s", "latticra-seal-verification-receipt/0.1");
    (void)snprintf(receipt.verification_policy_profile, sizeof(receipt.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(receipt.artifact_digest_algorithm, sizeof(receipt.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        receipt.artifact_digest_hex,
        sizeof(receipt.artifact_digest_hex),
        "%s",
        "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
    (void)snprintf(receipt.signer_identity_label, sizeof(receipt.signer_identity_label), "%s", "latticra-dev-signer");
    (void)snprintf(receipt.public_key_identity_label, sizeof(receipt.public_key_identity_label), "%s", "latticra-dev-public-key");
    (void)snprintf(receipt.receipt_state, sizeof(receipt.receipt_state), "%s", "unverified-metadata");
    (void)snprintf(receipt.verification_state, sizeof(receipt.verification_state), "%s", "unsupported");
    receipt.cryptographic_verification_supported = 0u;
    receipt.cryptographic_verification_performed = 0u;
    receipt.verified = 0u;
    receipt.invalid = 0u;
    receipt.authority_usable = 0u;
    receipt.capability_gate_allowed = 0u;
    receipt.runtime_authority_granted = 0u;
    receipt.error = LATTICRA_SEAL_VERIFICATION_RECEIPT_OK;
    (void)snprintf(receipt.status, sizeof(receipt.status), "%s", "verification-receipt-metadata");
    return receipt;
}

static int gate_copies_receipt_metadata_and_denies(void) {
    latticra_seal_verification_receipt_t receipt = fixture_receipt();
    latticra_seal_capability_gate_t gate;
    char rendered[LATTICRA_SEAL_CAPABILITY_GATE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_capability_gate_from_receipt(
            &receipt,
            "seal.inspect",
            "read-metadata",
            "local-artifact",
            &gate) == LATTICRA_STATUS_OK,
        "gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_OK, "gate ok");
    EXPECT_TRUE(strcmp(gate.gate_profile, "latticra-seal-capability-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(gate.receipt_profile, "latticra-seal-verification-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(gate.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(gate.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(gate.artifact_digest_hex, receipt.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(gate.signer_identity_label, "latticra-dev-signer") == 0, "signer label");
    EXPECT_TRUE(strcmp(gate.public_key_identity_label, "latticra-dev-public-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(gate.receipt_state, "unverified-metadata") == 0, "receipt state");
    EXPECT_TRUE(strcmp(gate.verification_state, "unsupported") == 0, "verification state");
    EXPECT_TRUE(strcmp(gate.requested_capability, "seal.inspect") == 0, "requested capability");
    EXPECT_TRUE(strcmp(gate.requested_effect, "read-metadata") == 0, "requested effect");
    EXPECT_TRUE(strcmp(gate.requested_scope, "local-artifact") == 0, "requested scope");
    EXPECT_TRUE(gate.verified == 0u, "verified flag");
    EXPECT_TRUE(gate.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(gate.receipt_capability_gate_allowed == 0u, "receipt gate flag");
    EXPECT_TRUE(gate.gate_allowed == 0u, "gate allowed flag");
    EXPECT_TRUE(strcmp(gate.gate_state, "denied-unverified") == 0, "gate state");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_capability_gate_is_denied_metadata(&gate) == 1, "denied metadata helper");
    EXPECT_TRUE(
        latticra_seal_capability_gate_report(&gate, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL CAPABILITY GATE") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "gate_state=denied-unverified") != 0, "render gate state");
    EXPECT_TRUE(strstr(rendered, "verified=0") != 0, "render verified");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "receipt_capability_gate_allowed=0") != 0, "render receipt gate");
    EXPECT_TRUE(strstr(rendered, "gate_allowed=0") != 0, "render gate allowed");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int gate_defaults_scope(void) {
    latticra_seal_verification_receipt_t receipt = fixture_receipt();
    latticra_seal_capability_gate_t gate;

    EXPECT_TRUE(
        latticra_seal_capability_gate_from_receipt(&receipt, "seal.inspect", "read-metadata", 0, &gate) == LATTICRA_STATUS_OK,
        "default scope status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_OK, "default scope ok");
    EXPECT_TRUE(strcmp(gate.requested_scope, "unspecified-scope") == 0, "default scope");
    return 0;
}

static int gate_fails_closed(void) {
    latticra_seal_verification_receipt_t receipt = fixture_receipt();
    latticra_seal_capability_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(0, "cap", "effect", "scope", &gate) == LATTICRA_STATUS_OK, "null receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT, "null receipt error");
    receipt.error = LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", "effect", "scope", &gate) == LATTICRA_STATUS_OK, "bad receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT, "bad receipt error");
    receipt = fixture_receipt();
    receipt.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", "effect", "scope", &gate) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST, "missing digest error");
    receipt = fixture_receipt();
    receipt.signer_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", "effect", "scope", &gate) == LATTICRA_STATUS_OK, "missing signer status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER, "missing signer error");
    receipt = fixture_receipt();
    receipt.public_key_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", "effect", "scope", &gate) == LATTICRA_STATUS_OK, "missing public key status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY, "missing public key error");
    receipt = fixture_receipt();
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, 0, "effect", "scope", &gate) == LATTICRA_STATUS_OK, "missing capability status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY, "missing capability error");
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", 0, "scope", &gate) == LATTICRA_STATUS_OK, "missing effect status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT, "missing effect error");
    EXPECT_TRUE(latticra_seal_capability_gate_from_receipt(&receipt, "cap", "effect", "scope", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_capability_gate_is_denied_metadata(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_capability_gate_report(&gate, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_capability_gate_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null gate");
    EXPECT_TRUE(latticra_seal_capability_gate_report(&gate, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (gate_copies_receipt_metadata_and_denies() != 0) {
        return 1;
    }
    if (gate_defaults_scope() != 0) {
        return 1;
    }
    if (gate_fails_closed() != 0) {
        return 1;
    }
    printf("seal capability gate invariants: ok\n");
    return 0;
}
