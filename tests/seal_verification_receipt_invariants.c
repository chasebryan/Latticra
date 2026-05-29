#include "latticra/seal_verification_receipt.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_verification_policy_t fixture_policy(void) {
    latticra_seal_verification_policy_t policy;
    memset(&policy, 0, sizeof(policy));
    (void)snprintf(policy.verification_policy_profile, sizeof(policy.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(policy.signature_profile, sizeof(policy.signature_profile), "%s", "latticra-seal-signature/0.1");
    (void)snprintf(policy.manifest_profile, sizeof(policy.manifest_profile), "%s", "latticra-seal-manifest/0.1");
    (void)snprintf(policy.artifact_digest_algorithm, sizeof(policy.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        policy.artifact_digest_hex,
        sizeof(policy.artifact_digest_hex),
        "%s",
        "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
    (void)snprintf(policy.signer_identity_label, sizeof(policy.signer_identity_label), "%s", "latticra-dev-signer");
    (void)snprintf(policy.signature_algorithm, sizeof(policy.signature_algorithm), "%s", "Ed25519-development");
    (void)snprintf(policy.public_key_identity_label, sizeof(policy.public_key_identity_label), "%s", "latticra-dev-public-key");
    (void)snprintf(policy.trust_source, sizeof(policy.trust_source), "%s", "local-fixture");
    (void)snprintf(policy.verification_state, sizeof(policy.verification_state), "%s", "unsupported");
    policy.cryptographic_verification_supported = 0u;
    policy.cryptographic_verification_performed = 0u;
    policy.public_key_material_handling = 0u;
    policy.private_key_handling = 0u;
    policy.network_lookup_allowed = 0u;
    policy.revocation_lookup_allowed = 0u;
    policy.runtime_authority_granted = 0u;
    policy.error = LATTICRA_SEAL_VERIFICATION_POLICY_OK;
    (void)snprintf(policy.status, sizeof(policy.status), "%s", "verification-policy-metadata");
    return policy;
}

static int receipt_copies_policy_metadata(void) {
    latticra_seal_verification_policy_t policy = fixture_policy();
    latticra_seal_verification_receipt_t receipt;
    char rendered[LATTICRA_SEAL_VERIFICATION_RECEIPT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK,
        "receipt status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_OK, "receipt ok");
    EXPECT_TRUE(strcmp(receipt.receipt_profile, "latticra-seal-verification-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(receipt.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(receipt.signature_profile, "latticra-seal-signature/0.1") == 0, "signature profile");
    EXPECT_TRUE(strcmp(receipt.manifest_profile, "latticra-seal-manifest/0.1") == 0, "manifest profile");
    EXPECT_TRUE(strcmp(receipt.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(receipt.artifact_digest_hex, policy.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(receipt.signer_identity_label, "latticra-dev-signer") == 0, "signer label");
    EXPECT_TRUE(strcmp(receipt.signature_algorithm, "Ed25519-development") == 0, "signature algorithm");
    EXPECT_TRUE(strcmp(receipt.public_key_identity_label, "latticra-dev-public-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(receipt.trust_source, "local-fixture") == 0, "trust source");
    EXPECT_TRUE(strcmp(receipt.verification_state, "unsupported") == 0, "verification state");
    EXPECT_TRUE(strcmp(receipt.receipt_state, "unverified-metadata") == 0, "receipt state");
    EXPECT_TRUE(receipt.cryptographic_verification_supported == 0u, "verification support flag");
    EXPECT_TRUE(receipt.cryptographic_verification_performed == 0u, "verification performed flag");
    EXPECT_TRUE(receipt.verified == 0u, "verified flag");
    EXPECT_TRUE(receipt.invalid == 0u, "invalid flag");
    EXPECT_TRUE(receipt.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(receipt.capability_gate_allowed == 0u, "capability gate flag");
    EXPECT_TRUE(receipt.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_verification_receipt_is_unverified_metadata(&receipt) == 1, "metadata helper");
    EXPECT_TRUE(
        latticra_seal_verification_receipt_report(&receipt, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL VERIFICATION RECEIPT") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "receipt_state=unverified-metadata") != 0, "render receipt state");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_supported=0") != 0, "render verification support");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "verified=0") != 0, "render verified flag");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != 0, "render authority flag");
    EXPECT_TRUE(strstr(rendered, "capability_gate_allowed=0") != 0, "render capability gate flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    return 0;
}

static int receipt_fails_closed(void) {
    latticra_seal_verification_policy_t policy = fixture_policy();
    latticra_seal_verification_receipt_t receipt;
    char tiny[1];
    char rendered[LATTICRA_SEAL_VERIFICATION_RECEIPT_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(0, &receipt) == LATTICRA_STATUS_OK, "null policy status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_INPUT, "null policy error");
    policy.error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "bad policy status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY, "bad policy error");
    policy = fixture_policy();
    memset(policy.verification_policy_profile, 'z', sizeof(policy.verification_policy_profile));
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "unterminated policy status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY, "unterminated policy error");
    policy = fixture_policy();
    policy.network_lookup_allowed = 2u;
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "invalid policy flag status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY, "invalid policy flag error");
    policy = fixture_policy();
    policy.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "authority policy status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_INVALID_POLICY, "authority policy error");
    policy = fixture_policy();
    policy.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_DIGEST, "missing digest error");
    policy = fixture_policy();
    policy.signer_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "missing signer status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_SIGNER, "missing signer error");
    policy = fixture_policy();
    policy.public_key_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "missing public key status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFICATION_RECEIPT_MISSING_PUBLIC_KEY_IDENTITY, "missing public key error");
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_verification_receipt_is_unverified_metadata(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_verification_receipt_report(&receipt, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_verification_receipt_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null receipt");
    EXPECT_TRUE(latticra_seal_verification_receipt_report(&receipt, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");

    policy = fixture_policy();
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "tamper receipt source");
    memset(receipt.receipt_profile, 'z', sizeof(receipt.receipt_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_receipt_report(&receipt, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated verification receipt render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated verification receipt render cleared");
    EXPECT_TRUE(latticra_seal_verification_receipt_is_unverified_metadata(&receipt) == 0,
                "unterminated verification receipt helper rejected");

    policy = fixture_policy();
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "authority verification receipt source");
    receipt.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_receipt_report(&receipt, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority verification receipt render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority verification receipt render cleared");
    EXPECT_TRUE(latticra_seal_verification_receipt_is_unverified_metadata(&receipt) == 0,
                "authority verification receipt helper rejected");

    policy = fixture_policy();
    EXPECT_TRUE(latticra_seal_verification_receipt_from_policy(&policy, &receipt) == LATTICRA_STATUS_OK, "flag verification receipt source");
    receipt.verified = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_receipt_report(&receipt, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "flag verification receipt render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "flag verification receipt render cleared");
    EXPECT_TRUE(latticra_seal_verification_receipt_is_unverified_metadata(&receipt) == 0,
                "flag verification receipt helper rejected");
    return 0;
}

int main(void) {
    if (receipt_copies_policy_metadata() != 0) {
        return 1;
    }
    if (receipt_fails_closed() != 0) {
        return 1;
    }
    printf("seal verification receipt invariants: ok\n");
    return 0;
}
