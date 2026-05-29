#include "latticra/seal_crypto_verify_backend.h"

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

static int backend_copies_policy_metadata(void) {
    latticra_seal_verification_policy_t policy = fixture_policy();
    latticra_seal_crypto_verify_backend_t backend;
    char rendered[LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK,
        "backend status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK, "backend ok");
    EXPECT_TRUE(strcmp(backend.backend_profile, "latticra-seal-crypto-verify-backend/0.1") == 0, "backend profile");
    EXPECT_TRUE(strcmp(backend.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(backend.signature_profile, "latticra-seal-signature/0.1") == 0, "signature profile");
    EXPECT_TRUE(strcmp(backend.manifest_profile, "latticra-seal-manifest/0.1") == 0, "manifest profile");
    EXPECT_TRUE(strcmp(backend.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(backend.artifact_digest_hex, policy.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(backend.signer_identity_label, "latticra-dev-signer") == 0, "signer label");
    EXPECT_TRUE(strcmp(backend.signature_algorithm, "Ed25519-development") == 0, "signature algorithm");
    EXPECT_TRUE(strcmp(backend.public_key_identity_label, "latticra-dev-public-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(backend.trust_source, "local-fixture") == 0, "trust source");
    EXPECT_TRUE(strcmp(backend.crypto_verify_state, "ready-local-ed25519") == 0, "crypto verify state");
    EXPECT_TRUE(backend.cryptographic_verification_supported == 1u, "verification support flag");
    EXPECT_TRUE(backend.cryptographic_verification_performed == 0u, "verification performed flag");
    EXPECT_TRUE(backend.verified == 0u, "verified flag");
    EXPECT_TRUE(backend.invalid == 0u, "invalid flag");
    EXPECT_TRUE(backend.authority_usable == 0u, "authority flag");
    EXPECT_TRUE(backend.capability_gate_allowed == 0u, "capability gate flag");
    EXPECT_TRUE(backend.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_is_metadata_only(&backend) == 0, "metadata helper");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_is_authority_neutral(&backend) == 1, "authority neutral helper");
    EXPECT_TRUE(
        latticra_seal_crypto_verify_backend_report(&backend, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL CRYPTO VERIFY BACKEND") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "crypto_verify_state=ready-local-ed25519") != 0, "render crypto verify state");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_supported=1") != 0, "render verification support");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "verified=0") != 0, "render verified flag");
    EXPECT_TRUE(strstr(rendered, "authority_usable=0") != 0, "render authority flag");
    EXPECT_TRUE(strstr(rendered, "capability_gate_allowed=0") != 0, "render capability gate flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    EXPECT_TRUE(strstr(rendered, "status=crypto-verify-backend-ready") != 0, "render ready status");
    return 0;
}

static int backend_fails_closed(void) {
    latticra_seal_verification_policy_t policy = fixture_policy();
    latticra_seal_crypto_verify_backend_t backend;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(0, &backend) == LATTICRA_STATUS_OK, "null policy status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_INPUT, "null policy error");
    policy.error = LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK, "bad policy status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_INVALID_POLICY, "bad policy error");
    policy = fixture_policy();
    policy.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_DIGEST, "missing digest error");
    policy = fixture_policy();
    policy.signer_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK, "missing signer status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_SIGNER, "missing signer error");
    policy = fixture_policy();
    policy.public_key_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK, "missing public key status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_MISSING_PUBLIC_KEY_IDENTITY, "missing public key error");
    policy = fixture_policy();
    (void)snprintf(policy.signature_algorithm, sizeof(policy.signature_algorithm), "%s", "ML-DSA-planned");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, &backend) == LATTICRA_STATUS_OK, "unsupported algorithm status");
    EXPECT_TRUE(backend.error == LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_UNSUPPORTED_ALGORITHM, "unsupported algorithm error");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_from_policy(&policy, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_is_authority_neutral(0) == 0, "null authority helper");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_report(&backend, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null backend");
    EXPECT_TRUE(latticra_seal_crypto_verify_backend_report(&backend, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (backend_copies_policy_metadata() != 0) {
        return 1;
    }
    if (backend_fails_closed() != 0) {
        return 1;
    }
    printf("seal crypto verify backend invariants: ok\n");
    return 0;
}
