#include "latticra/seal_crypto_graduation_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_crypto_verify_backend_t fixture_backend(void) {
    latticra_seal_crypto_verify_backend_t backend;
    memset(&backend, 0, sizeof(backend));
    (void)snprintf(backend.backend_profile, sizeof(backend.backend_profile), "%s", "latticra-seal-crypto-verify-backend/0.1");
    (void)snprintf(backend.verification_policy_profile, sizeof(backend.verification_policy_profile), "%s", "latticra-seal-verification-policy/0.1");
    (void)snprintf(backend.signature_profile, sizeof(backend.signature_profile), "%s", "latticra-seal-signature/0.1");
    (void)snprintf(backend.manifest_profile, sizeof(backend.manifest_profile), "%s", "latticra-seal-manifest/0.1");
    (void)snprintf(backend.artifact_digest_algorithm, sizeof(backend.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        backend.artifact_digest_hex,
        sizeof(backend.artifact_digest_hex),
        "%s",
        "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
    (void)snprintf(backend.signer_identity_label, sizeof(backend.signer_identity_label), "%s", "latticra-dev-signer");
    (void)snprintf(backend.signature_algorithm, sizeof(backend.signature_algorithm), "%s", "Ed25519-development");
    (void)snprintf(backend.public_key_identity_label, sizeof(backend.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(backend.trust_source, sizeof(backend.trust_source), "%s", "local-test-vector");
    (void)snprintf(backend.crypto_verify_state, sizeof(backend.crypto_verify_state), "%s", "ready-local-ed25519");
    backend.cryptographic_verification_supported = 1u;
    backend.error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK;
    (void)snprintf(backend.status, sizeof(backend.status), "%s", "crypto-verify-backend-ready");
    return backend;
}

static int build_valid_fixture(
    latticra_seal_ed25519_verify_result_t *verify_result,
    latticra_seal_verified_receipt_promotion_t *receipt) {
    static const unsigned char public_key[LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES] = {
        0x3d, 0x40, 0x17, 0xc3, 0xe8, 0x43, 0x89, 0x5a,
        0x92, 0xb7, 0x0a, 0xa7, 0x4d, 0x1b, 0x7e, 0xbc,
        0x9c, 0x98, 0x2c, 0xcf, 0x2e, 0xc4, 0x96, 0x8c,
        0xc0, 0xcd, 0x55, 0xf1, 0x2a, 0xf4, 0x66, 0x0c
    };
    static const unsigned char message[] = {0x72};
    static const unsigned char signature[LATTICRA_SEAL_ED25519_SIGNATURE_BYTES] = {
        0x92, 0xa0, 0x09, 0xa9, 0xf0, 0xd4, 0xca, 0xb8,
        0x72, 0x0e, 0x82, 0x0b, 0x5f, 0x64, 0x25, 0x40,
        0xa2, 0xb2, 0x7b, 0x54, 0x16, 0x50, 0x3f, 0x8f,
        0xb3, 0x76, 0x22, 0x23, 0xeb, 0xdb, 0x69, 0xda,
        0x08, 0x5a, 0xc1, 0xe4, 0x3e, 0x15, 0x99, 0x6e,
        0x45, 0x8f, 0x36, 0x13, 0xd0, 0xf1, 0x1d, 0x8c,
        0x38, 0x7b, 0x2e, 0xae, 0xb4, 0x30, 0x2a, 0xee,
        0xb0, 0x0d, 0x29, 0x16, 0x12, 0xbb, 0x0c, 0x00
    };
    latticra_seal_crypto_verify_backend_t backend = fixture_backend();

    EXPECT_TRUE(
        latticra_seal_ed25519_verify_local(
            &backend,
            "rfc8032-test-vector-2",
            message,
            sizeof(message),
            public_key,
            sizeof(public_key),
            signature,
            sizeof(signature),
            verify_result) == LATTICRA_STATUS_OK,
        "valid verify status");
    EXPECT_TRUE(verify_result->error == LATTICRA_SEAL_ED25519_VERIFY_OK, "valid verify result");
    EXPECT_TRUE(
        latticra_seal_verified_receipt_promotion_from_ed25519_result(
            verify_result,
            receipt) == LATTICRA_STATUS_OK,
        "valid receipt status");
    EXPECT_TRUE(receipt->error == LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_OK, "valid receipt");
    return 0;
}

static int valid_crypto_material_graduates_without_authority(void) {
    latticra_seal_ed25519_verify_result_t verify_result;
    latticra_seal_verified_receipt_promotion_t receipt;
    latticra_seal_crypto_graduation_gate_t gate;
    char rendered[LATTICRA_SEAL_CRYPTO_GRADUATION_REPORT_MAX];

    EXPECT_TRUE(build_valid_fixture(&verify_result, &receipt) == 0, "valid fixture");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_OK, "gate ok");
    EXPECT_TRUE(strcmp(gate.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(gate.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "baseline profile");
    EXPECT_TRUE(strcmp(gate.verify_profile, "latticra-seal-ed25519-verify/0.1") == 0, "verify profile");
    EXPECT_TRUE(strcmp(gate.receipt_profile, "latticra-seal-verified-receipt/0.1") == 0, "receipt profile");
    EXPECT_TRUE(strcmp(gate.signature_algorithm, "Ed25519-development") == 0, "algorithm");
    EXPECT_TRUE(strcmp(gate.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(gate.public_key_size_bytes == LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES, "key size");
    EXPECT_TRUE(gate.signature_size_bytes == LATTICRA_SEAL_ED25519_SIGNATURE_BYTES, "signature size");
    EXPECT_TRUE(gate.verify_result_present == 1u, "verify present");
    EXPECT_TRUE(gate.receipt_present == 1u, "receipt present");
    EXPECT_TRUE(gate.provider_backed_verification_required == 1u, "provider required");
    EXPECT_TRUE(gate.deterministic_test_vector_required == 1u, "deterministic vector");
    EXPECT_TRUE(gate.negative_test_vector_required == 1u, "negative vector");
    EXPECT_TRUE(gate.rfc8032_test_vector_tracked == 1u, "rfc8032");
    EXPECT_TRUE(gate.fips_186_5_signature_standard_tracked == 1u, "fips 186-5");
    EXPECT_TRUE(gate.fips_180_4_digest_standard_tracked == 1u, "fips 180-4");
    EXPECT_TRUE(gate.fips_140_3_claim_gate_required == 1u, "fips 140-3");
    EXPECT_TRUE(gate.sp_800_57_key_management_required == 1u, "sp 800-57");
    EXPECT_TRUE(gate.sp_800_131a_transition_review_required == 1u, "sp 800-131a");
    EXPECT_TRUE(gate.fips_204_ml_dsa_planning_tracked == 1u, "fips 204");
    EXPECT_TRUE(gate.fips_205_slh_dsa_planning_tracked == 1u, "fips 205");
    EXPECT_TRUE(gate.cryptographic_verification_supported == 1u, "supported");
    EXPECT_TRUE(gate.cryptographic_verification_performed == 1u, "performed");
    EXPECT_TRUE(gate.verified == 1u, "verified");
    EXPECT_TRUE(gate.invalid == 0u, "invalid");
    EXPECT_TRUE(gate.local_verify_graduated == 1u, "local verify graduated");
    EXPECT_TRUE(gate.receipt_promotion_graduated == 1u, "receipt graduated");
    EXPECT_TRUE(gate.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.signing_authority_granted == 0u, "signing authority");
    EXPECT_TRUE(gate.key_generation_allowed == 0u, "key generation");
    EXPECT_TRUE(gate.key_storage_allowed == 0u, "key storage");
    EXPECT_TRUE(gate.revocation_lookup_allowed == 0u, "revocation");
    EXPECT_TRUE(gate.network_lookup_allowed == 0u, "network");
    EXPECT_TRUE(gate.authority_usable == 0u, "authority usable");
    EXPECT_TRUE(gate.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(gate.capability_gate_allowed == 0u, "capability");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(gate.gate_state, "graduated-authority-neutral") == 0, "gate state");
    EXPECT_TRUE(strcmp(gate.blocked_reason, "authority-remains-denied") == 0, "blocked reason");
    EXPECT_TRUE(latticra_seal_crypto_graduation_gate_is_authority_neutral(&gate) == 1, "authority neutral");

    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_report(&gate, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL CRYPTO GRADUATION GATE") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_profile=latticra-seal-crypto-graduation-gate/0.1") != 0, "report profile");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "report standard");
    EXPECT_TRUE(strstr(rendered, "production_crypto_claim_allowed=0") != 0, "report production");
    EXPECT_TRUE(strstr(rendered, "fips_claim_allowed=0") != 0, "report fips");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "report authority");
    return 0;
}

static int invalid_verify_result_fails_closed(void) {
    static const unsigned char public_key[LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES] = {
        0x3d, 0x40, 0x17, 0xc3, 0xe8, 0x43, 0x89, 0x5a,
        0x92, 0xb7, 0x0a, 0xa7, 0x4d, 0x1b, 0x7e, 0xbc,
        0x9c, 0x98, 0x2c, 0xcf, 0x2e, 0xc4, 0x96, 0x8c,
        0xc0, 0xcd, 0x55, 0xf1, 0x2a, 0xf4, 0x66, 0x0c
    };
    static const unsigned char message[] = {0x72};
    unsigned char signature[LATTICRA_SEAL_ED25519_SIGNATURE_BYTES] = {
        0x92, 0xa0, 0x09, 0xa9, 0xf0, 0xd4, 0xca, 0xb8,
        0x72, 0x0e, 0x82, 0x0b, 0x5f, 0x64, 0x25, 0x40,
        0xa2, 0xb2, 0x7b, 0x54, 0x16, 0x50, 0x3f, 0x8f,
        0xb3, 0x76, 0x22, 0x23, 0xeb, 0xdb, 0x69, 0xda,
        0x08, 0x5a, 0xc1, 0xe4, 0x3e, 0x15, 0x99, 0x6e,
        0x45, 0x8f, 0x36, 0x13, 0xd0, 0xf1, 0x1d, 0x8c,
        0x38, 0x7b, 0x2e, 0xae, 0xb4, 0x30, 0x2a, 0xee,
        0xb0, 0x0d, 0x29, 0x16, 0x12, 0xbb, 0x0c, 0x00
    };
    latticra_seal_crypto_verify_backend_t backend = fixture_backend();
    latticra_seal_ed25519_verify_result_t verify_result;
    latticra_seal_verified_receipt_promotion_t receipt;
    latticra_seal_crypto_graduation_gate_t gate;

    signature[0] ^= 0x01u;
    EXPECT_TRUE(
        latticra_seal_ed25519_verify_local(
            &backend,
            "tampered-signature",
            message,
            sizeof(message),
            public_key,
            sizeof(public_key),
            signature,
            sizeof(signature),
            &verify_result) == LATTICRA_STATUS_OK,
        "invalid verify status");
    EXPECT_TRUE(verify_result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE, "invalid verify");
    EXPECT_TRUE(
        latticra_seal_verified_receipt_promotion_from_ed25519_result(
            &verify_result,
            &receipt) == LATTICRA_STATUS_OK,
        "invalid receipt status");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "invalid gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_VERIFY_RESULT, "invalid gate error");
    EXPECT_TRUE(strcmp(gate.gate_state, "blocked") == 0, "invalid blocked");
    EXPECT_TRUE(gate.local_verify_graduated == 0u, "invalid local");
    EXPECT_TRUE(gate.receipt_promotion_graduated == 0u, "invalid receipt");
    EXPECT_TRUE(gate.standard_expectations_met == 0u, "invalid standards");
    EXPECT_TRUE(gate.authority_promotion_allowed == 0u, "invalid authority");
    return 0;
}

static int malformed_metadata_fails_closed(void) {
    latticra_seal_ed25519_verify_result_t verify_result;
    latticra_seal_verified_receipt_promotion_t receipt;
    latticra_seal_crypto_graduation_gate_t gate;

    EXPECT_TRUE(build_valid_fixture(&verify_result, &receipt) == 0, "malformed fixture");
    verify_result.message_digest_hex[0] = '\0';
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "missing digest gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_MESSAGE_DIGEST, "missing digest");

    EXPECT_TRUE(build_valid_fixture(&verify_result, &receipt) == 0, "authority fixture");
    receipt.runtime_authority_granted = 1u;
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "authority gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_AUTHORITY_NOT_NEUTRAL, "authority error");

    EXPECT_TRUE(build_valid_fixture(&verify_result, &receipt) == 0, "size fixture");
    verify_result.signature_size_bytes = 63u;
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "size gate status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_INVALID_KEY_OR_SIGNATURE_SIZE, "size error");
    return 0;
}

static int null_and_buffer_handling_fails_closed(void) {
    latticra_seal_ed25519_verify_result_t verify_result;
    latticra_seal_verified_receipt_promotion_t receipt;
    latticra_seal_crypto_graduation_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(build_valid_fixture(&verify_result, &receipt) == 0, "null fixture");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            0,
            &receipt,
            &gate) == LATTICRA_STATUS_OK,
        "missing verify status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_VERIFY_RESULT, "missing verify");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            0,
            &gate) == LATTICRA_STATUS_OK,
        "missing receipt status");
    EXPECT_TRUE(gate.error == LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_MISSING_RECEIPT, "missing receipt");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_from_verified_receipt(
            &verify_result,
            &receipt,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_crypto_graduation_gate_is_authority_neutral(0) == 0, "null helper");
    EXPECT_TRUE(
        latticra_seal_crypto_graduation_gate_report(&gate, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(latticra_seal_crypto_graduation_gate_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report gate");
    EXPECT_TRUE(latticra_seal_crypto_graduation_gate_report(&gate, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report buffer");
    return 0;
}

int main(void) {
    if (valid_crypto_material_graduates_without_authority() != 0) {
        return 1;
    }
    if (invalid_verify_result_fails_closed() != 0) {
        return 1;
    }
    if (malformed_metadata_fails_closed() != 0) {
        return 1;
    }
    if (null_and_buffer_handling_fails_closed() != 0) {
        return 1;
    }
    printf("seal crypto graduation gate invariants: ok\n");
    return 0;
}
