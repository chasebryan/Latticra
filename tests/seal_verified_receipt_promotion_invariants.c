#include "latticra/seal_verified_receipt_promotion.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_ed25519_verify_result_t fixture_verified_result(void) {
    latticra_seal_ed25519_verify_result_t result;
    memset(&result, 0, sizeof(result));
    (void)snprintf(result.ed25519_verify_profile, sizeof(result.ed25519_verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(result.backend_profile, sizeof(result.backend_profile), "%s", "latticra-seal-crypto-verify-backend/0.1");
    (void)snprintf(result.verification_policy_profile, sizeof(result.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(result.message_label, sizeof(result.message_label), "%s", "rfc8032-test-vector-2");
    result.message_size_bytes = 1u;
    (void)snprintf(result.message_digest_algorithm, sizeof(result.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(result.message_digest_hex, sizeof(result.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(result.public_key_identity_label, sizeof(result.public_key_identity_label), "%s", "rfc8032-test-key");
    result.public_key_size_bytes = LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES;
    (void)snprintf(result.signature_algorithm, sizeof(result.signature_algorithm), "%s", "Ed25519-development");
    result.signature_size_bytes = LATTICRA_SEAL_ED25519_SIGNATURE_BYTES;
    (void)snprintf(result.trust_source, sizeof(result.trust_source), "%s", "local-test-vector");
    (void)snprintf(result.crypto_verify_state, sizeof(result.crypto_verify_state), "%s", "verified");
    result.cryptographic_verification_supported = 1u;
    result.cryptographic_verification_performed = 1u;
    result.verified = 1u;
    result.invalid = 0u;
    result.authority_usable = 0u;
    result.capability_gate_allowed = 0u;
    result.runtime_authority_granted = 0u;
    result.error = LATTICRA_SEAL_ED25519_VERIFY_OK;
    (void)snprintf(result.status, sizeof(result.status), "%s", "ed25519-verified");
    return result;
}

static int promotion_copies_verified_result(void) {
    latticra_seal_ed25519_verify_result_t result = fixture_verified_result();
    latticra_seal_verified_receipt_promotion_t receipt;
    char rendered[LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK,
        "promotion status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK, "promotion ok");
    EXPECT_TRUE(strcmp(receipt.receipt_profile, "latticra-seal-verified-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(receipt.verify_profile, "latticra-seal-ed25519-verify/0.1") == 0, "verify profile");
    EXPECT_TRUE(strcmp(receipt.backend_profile, "latticra-seal-crypto-verify-backend/0.1") == 0, "backend profile");
    EXPECT_TRUE(strcmp(receipt.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(receipt.message_label, "rfc8032-test-vector-2") == 0, "message label");
    EXPECT_TRUE(receipt.message_size_bytes == 1u, "message size");
    EXPECT_TRUE(strcmp(receipt.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(receipt.message_digest_hex, result.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(receipt.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(receipt.signature_algorithm, "Ed25519-development") == 0, "signature algorithm");
    EXPECT_TRUE(strcmp(receipt.trust_source, "local-test-vector") == 0, "trust source");
    EXPECT_TRUE(strcmp(receipt.verification_state, "verified") == 0, "verification state");
    EXPECT_TRUE(strcmp(receipt.receipt_state, "verified") == 0, "receipt state");
    EXPECT_TRUE(receipt.cryptographic_verification_supported == 1u, "verification supported");
    EXPECT_TRUE(receipt.cryptographic_verification_performed == 1u, "verification performed");
    EXPECT_TRUE(receipt.verified == 1u, "verified");
    EXPECT_TRUE(receipt.invalid == 0u, "invalid");
    EXPECT_TRUE(receipt.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(receipt.capability_gate_allowed == 0u, "capability flag");
    EXPECT_TRUE(receipt.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_is_authority_neutral(&receipt) == 1, "authority neutral helper");
    EXPECT_TRUE(
        latticra_seal_verified_receipt_promotion_report(&receipt, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL VERIFIED RECEIPT PROMOTION") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "receipt_state=verified") != 0, "report receipt state");
    EXPECT_TRUE(strstr(rendered, "verification_state=verified") != 0, "report verification state");
    EXPECT_TRUE(strstr(rendered, "verified=1") != 0, "report verified flag");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != 0, "report authority flag");
    EXPECT_TRUE(strstr(rendered, "capability_gate_allowed=0") != 0, "report capability flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime flag");
    return 0;
}

static int promotion_fails_closed(void) {
    latticra_seal_ed25519_verify_result_t result = fixture_verified_result();
    latticra_seal_verified_receipt_promotion_t receipt;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(0, &receipt) == LATTICRA_STATUS_OK, "null result status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_INPUT, "null result error");
    result.error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE;
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "invalid result status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_RESULT, "invalid result error");
    result = fixture_verified_result();
    result.cryptographic_verification_supported = 0u;
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "unsupported status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_UNSUPPORTED_VERIFICATION, "unsupported error");
    result = fixture_verified_result();
    result.cryptographic_verification_performed = 0u;
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "not performed status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_VERIFICATION_NOT_PERFORMED, "not performed error");
    result = fixture_verified_result();
    result.verified = 0u;
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "not verified status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_NOT_VERIFIED, "not verified error");
    result = fixture_verified_result();
    result.invalid = 1u;
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "invalid flag status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_NOT_VERIFIED, "invalid flag error");
    result = fixture_verified_result();
    (void)snprintf(result.crypto_verify_state, sizeof(result.crypto_verify_state), "%s", "invalid-signature");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "bad state status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_INVALID_VERIFY_STATE, "bad state error");
    result = fixture_verified_result();
    result.message_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_MESSAGE_DIGEST, "missing digest error");
    result = fixture_verified_result();
    result.public_key_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, &receipt) == LATTICRA_STATUS_OK, "missing public key status");
    EXPECT_TRUE(receipt.error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_MISSING_PUBLIC_KEY_IDENTITY, "missing public key error");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_from_ed25519_result(&result, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_is_authority_neutral(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_report(&receipt, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null receipt");
    EXPECT_TRUE(latticra_seal_verified_receipt_promotion_report(&receipt, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (promotion_copies_verified_result() != 0) {
        return 1;
    }
    if (promotion_fails_closed() != 0) {
        return 1;
    }
    printf("seal verified receipt promotion invariants: ok\n");
    return 0;
}
