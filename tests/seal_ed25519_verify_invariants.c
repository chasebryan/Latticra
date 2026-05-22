#include "latticra/seal_ed25519_verify.h"

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
    (void)snprintf(backend.crypto_verify_state, sizeof(backend.crypto_verify_state), "%s", "unsupported");
    backend.cryptographic_verification_supported = 0u;
    backend.cryptographic_verification_performed = 0u;
    backend.verified = 0u;
    backend.invalid = 0u;
    backend.authority_usable = 0u;
    backend.capability_gate_allowed = 0u;
    backend.runtime_authority_granted = 0u;
    backend.error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK;
    (void)snprintf(backend.status, sizeof(backend.status), "%s", "crypto-verify-backend-metadata");
    return backend;
}

static int verify_valid_ed25519_vector(void) {
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
    latticra_seal_ed25519_verify_result_t result;
    char rendered[LATTICRA_SEAL_ED25519_VERIFY_REPORT_MAX];

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
            &result) == LATTICRA_STATUS_OK,
        "verify status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_OK, "verify ok");
    EXPECT_TRUE(strcmp(result.ed25519_verify_profile, "latticra-seal-ed25519-verify/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(result.backend_profile, "latticra-seal-crypto-verify-backend/0.1") == 0, "backend profile");
    EXPECT_TRUE(strcmp(result.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(result.message_label, "rfc8032-test-vector-2") == 0, "message label");
    EXPECT_TRUE(result.message_size_bytes == 1u, "message size");
    EXPECT_TRUE(strcmp(result.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(result.message_digest_hex[0] != '\0', "digest hex");
    EXPECT_TRUE(strcmp(result.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(result.public_key_size_bytes == LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES, "public key size");
    EXPECT_TRUE(strcmp(result.signature_algorithm, "Ed25519-development") == 0, "algorithm");
    EXPECT_TRUE(result.signature_size_bytes == LATTICRA_SEAL_ED25519_SIGNATURE_BYTES, "signature size");
    EXPECT_TRUE(strcmp(result.trust_source, "local-test-vector") == 0, "trust source");
    EXPECT_TRUE(strcmp(result.crypto_verify_state, "verified") == 0, "verify state");
    EXPECT_TRUE(result.cryptographic_verification_supported == 1u, "verification supported");
    EXPECT_TRUE(result.cryptographic_verification_performed == 1u, "verification performed");
    EXPECT_TRUE(result.verified == 1u, "verified flag");
    EXPECT_TRUE(result.invalid == 0u, "invalid flag");
    EXPECT_TRUE(result.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(result.capability_gate_allowed == 0u, "capability gate flag");
    EXPECT_TRUE(result.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_ed25519_verify_result_is_authority_neutral(&result) == 1, "authority neutral helper");
    EXPECT_TRUE(
        latticra_seal_ed25519_verify_report(&result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL ED25519 VERIFY RESULT") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "crypto_verify_state=verified") != 0, "report verified state");
    EXPECT_TRUE(strstr(rendered, "verified=1") != 0, "report verified flag");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != 0, "report authority flag");
    EXPECT_TRUE(strstr(rendered, "capability_gate_allowed=0") != 0, "report capability flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime flag");
    return 0;
}

static int verify_invalid_signature_vector(void) {
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
    latticra_seal_ed25519_verify_result_t result;

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
            &result) == LATTICRA_STATUS_OK,
        "invalid verify status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE, "invalid signature error");
    EXPECT_TRUE(strcmp(result.crypto_verify_state, "invalid-signature") == 0, "invalid signature state");
    EXPECT_TRUE(result.cryptographic_verification_supported == 1u, "invalid verification support");
    EXPECT_TRUE(result.cryptographic_verification_performed == 1u, "invalid verification performed");
    EXPECT_TRUE(result.verified == 0u, "invalid verified flag");
    EXPECT_TRUE(result.invalid == 1u, "invalid invalid flag");
    EXPECT_TRUE(result.authority_usable == 0u, "invalid authority flag");
    EXPECT_TRUE(result.capability_gate_allowed == 0u, "invalid capability flag");
    EXPECT_TRUE(result.runtime_authority_granted == 0u, "invalid runtime flag");
    return 0;
}

static int verify_fails_closed(void) {
    unsigned char message[] = {0x72};
    unsigned char public_key[LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES] = {0};
    unsigned char signature[LATTICRA_SEAL_ED25519_SIGNATURE_BYTES] = {0};
    latticra_seal_crypto_verify_backend_t backend = fixture_backend();
    latticra_seal_ed25519_verify_result_t result;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_ed25519_verify_local(0, "msg", message, sizeof(message), public_key, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "null backend status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_INPUT, "null backend error");
    backend.error = LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "bad backend status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_BACKEND, "bad backend error");
    backend = fixture_backend();
    (void)snprintf(backend.signature_algorithm, sizeof(backend.signature_algorithm), "%s", "ML-DSA-planned");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "unsupported algorithm status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_UNSUPPORTED_ALGORITHM, "unsupported algorithm error");
    backend = fixture_backend();
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", 0, sizeof(message), public_key, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "missing message status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_MISSING_MESSAGE, "missing message error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, 0u, public_key, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "empty message status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_MISSING_MESSAGE, "empty message error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), 0, sizeof(public_key), signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "missing key status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_MISSING_PUBLIC_KEY, "missing key error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, 31u, signature, sizeof(signature), &result) == LATTICRA_STATUS_OK, "bad key size status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_PUBLIC_KEY_SIZE, "bad key size error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, sizeof(public_key), 0, sizeof(signature), &result) == LATTICRA_STATUS_OK, "missing signature status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_MISSING_SIGNATURE, "missing signature error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, sizeof(public_key), signature, 63u, &result) == LATTICRA_STATUS_OK, "bad signature size status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE_SIZE, "bad signature size error");
    EXPECT_TRUE(latticra_seal_ed25519_verify_local(&backend, "msg", message, sizeof(message), public_key, sizeof(public_key), signature, sizeof(signature), 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_ed25519_verify_result_is_authority_neutral(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_ed25519_verify_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer clear");
    EXPECT_TRUE(latticra_seal_ed25519_verify_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null result");
    EXPECT_TRUE(latticra_seal_ed25519_verify_report(&result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (verify_valid_ed25519_vector() != 0) {
        return 1;
    }
    if (verify_invalid_signature_vector() != 0) {
        return 1;
    }
    if (verify_fails_closed() != 0) {
        return 1;
    }
    printf("seal ed25519 verify invariants: ok\n");
    return 0;
}
