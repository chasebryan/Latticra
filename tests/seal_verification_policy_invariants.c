#include "latticra/seal_verification_policy.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_signature_t fixture_signature(void) {
    latticra_seal_signature_t signature;
    memset(&signature, 0, sizeof(signature));
    (void)snprintf(signature.signature_profile, sizeof(signature.signature_profile), "%s", "latticra-seal-signature/0.1");
    (void)snprintf(signature.manifest_profile, sizeof(signature.manifest_profile), "%s", "latticra-seal-manifest/0.1");
    (void)snprintf(signature.artifact_digest_algorithm, sizeof(signature.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        signature.artifact_digest_hex,
        sizeof(signature.artifact_digest_hex),
        "%s",
        "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
    (void)snprintf(signature.signer_identity_label, sizeof(signature.signer_identity_label), "%s", "latticra-dev-signer");
    (void)snprintf(signature.signature_algorithm, sizeof(signature.signature_algorithm), "%s", "Ed25519-development");
    (void)snprintf(signature.signature_state, sizeof(signature.signature_state), "%s", "metadata-only");
    signature.signature_byte_length = 64u;
    signature.signature_supported = 1u;
    signature.verification_supported = 0u;
    signature.private_key_handling = 0u;
    signature.network_lookup_allowed = 0u;
    signature.runtime_authority_granted = 0u;
    signature.error = LATTICRA_SEAL_SIGNATURE_OK;
    (void)snprintf(signature.status, sizeof(signature.status), "%s", "signature-metadata");
    return signature;
}

static int policy_copies_signature_metadata(void) {
    latticra_seal_signature_t signature = fixture_signature();
    latticra_seal_verification_policy_t policy;
    char rendered[LATTICRA_SEAL_VERIFICATION_POLICY_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_verification_policy_from_signature(
            &signature,
            "latticra-dev-public-key",
            "local-fixture",
            &policy) == LATTICRA_STATUS_OK,
        "policy status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_OK, "policy ok");
    EXPECT_TRUE(strcmp(policy.verification_policy_profile, "latticra-seal-verification-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(policy.signature_profile, "latticra-seal-signature/0.1") == 0, "signature profile");
    EXPECT_TRUE(strcmp(policy.manifest_profile, "latticra-seal-manifest/0.1") == 0, "manifest profile");
    EXPECT_TRUE(strcmp(policy.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(policy.artifact_digest_hex, signature.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(policy.signer_identity_label, "latticra-dev-signer") == 0, "signer label");
    EXPECT_TRUE(strcmp(policy.signature_algorithm, "Ed25519-development") == 0, "signature algorithm");
    EXPECT_TRUE(strcmp(policy.public_key_identity_label, "latticra-dev-public-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(policy.trust_source, "local-fixture") == 0, "trust source");
    EXPECT_TRUE(strcmp(policy.verification_state, "unsupported") == 0, "verification state");
    EXPECT_TRUE(policy.cryptographic_verification_supported == 0u, "verification support flag");
    EXPECT_TRUE(policy.cryptographic_verification_performed == 0u, "verification performed flag");
    EXPECT_TRUE(policy.public_key_material_handling == 0u, "public key material flag");
    EXPECT_TRUE(policy.private_key_handling == 0u, "private key flag");
    EXPECT_TRUE(policy.network_lookup_allowed == 0u, "network lookup flag");
    EXPECT_TRUE(policy.revocation_lookup_allowed == 0u, "revocation lookup flag");
    EXPECT_TRUE(policy.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_verification_policy_is_metadata_only(&policy) == 1, "metadata helper");
    EXPECT_TRUE(
        latticra_seal_verification_policy_report(&policy, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL VERIFICATION POLICY") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "verification_state=unsupported") != 0, "render verification state");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_supported=0") != 0, "render verification support");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "public_key_material_handling=0") != 0, "render public key material");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key flag");
    EXPECT_TRUE(strstr(rendered, "network_lookup_allowed=0") != 0, "render network flag");
    EXPECT_TRUE(strstr(rendered, "revocation_lookup_allowed=0") != 0, "render revocation flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    return 0;
}

static int policy_defaults_trust_source(void) {
    latticra_seal_signature_t signature = fixture_signature();
    latticra_seal_verification_policy_t policy;

    EXPECT_TRUE(
        latticra_seal_verification_policy_from_signature(
            &signature,
            "latticra-dev-public-key",
            0,
            &policy) == LATTICRA_STATUS_OK,
        "default trust source status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_OK, "default trust source ok");
    EXPECT_TRUE(strcmp(policy.trust_source, "local-metadata-only") == 0, "default trust source");
    return 0;
}

static int policy_fails_closed(void) {
    latticra_seal_signature_t signature = fixture_signature();
    latticra_seal_verification_policy_t policy;
    char tiny[1];
    char rendered[LATTICRA_SEAL_VERIFICATION_POLICY_REPORT_MAX];
    char unterminated_public_key[LATTICRA_SEAL_VERIFICATION_POLICY_LABEL_MAX];
    char unterminated_trust_source[LATTICRA_SEAL_VERIFICATION_POLICY_STATE_MAX];

    memset(unterminated_public_key, 'p', sizeof(unterminated_public_key));
    memset(unterminated_trust_source, 't', sizeof(unterminated_trust_source));

    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(0, "key", "local", &policy) == LATTICRA_STATUS_OK, "null signature status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_INPUT, "null signature error");
    signature.error = LATTICRA_SEAL_SIGNATURE_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "bad signature status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE, "bad signature error");
    signature = fixture_signature();
    memset(signature.signature_profile, 'z', sizeof(signature.signature_profile));
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "unterminated signature status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE, "unterminated signature error");
    signature = fixture_signature();
    signature.signature_supported = 2u;
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "invalid signature flag status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_INVALID_SIGNATURE, "invalid signature flag error");
    signature = fixture_signature();
    signature.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_DIGEST, "missing digest error");
    signature = fixture_signature();
    signature.signer_identity_label[0] = '\0';
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "missing signer status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_SIGNER, "missing signer error");
    signature = fixture_signature();
    (void)snprintf(signature.signature_algorithm, sizeof(signature.signature_algorithm), "%s", "ML-DSA-future");
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "unsupported algorithm status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_UNSUPPORTED_ALGORITHM, "unsupported algorithm error");
    signature = fixture_signature();
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, 0, "local", &policy) == LATTICRA_STATUS_OK, "missing public key status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY, "missing public key error");
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, unterminated_public_key, "local", &policy) == LATTICRA_STATUS_OK, "unterminated public key identity status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_MISSING_PUBLIC_KEY_IDENTITY, "unterminated public key identity error");
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", unterminated_trust_source, &policy) == LATTICRA_STATUS_OK, "unterminated trust source status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_VERIFICATION_POLICY_OK, "unterminated trust source ok");
    EXPECT_TRUE(strcmp(policy.trust_source, "invalid-trust-source") == 0, "unterminated trust source sanitized");
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "unterminated trust source render");
    EXPECT_TRUE(strstr(rendered, "trust_source=invalid-trust-source") != 0, "unterminated trust source rendered sanitized");
    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_verification_policy_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_verification_policy_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null policy");
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");

    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "tamper policy source");
    memset(policy.verification_policy_profile, 'z', sizeof(policy.verification_policy_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated verification policy render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated verification policy render cleared");
    EXPECT_TRUE(latticra_seal_verification_policy_is_metadata_only(&policy) == 0,
                "unterminated verification policy helper rejected");

    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "authority verification policy source");
    policy.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority verification policy render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority verification policy render cleared");
    EXPECT_TRUE(latticra_seal_verification_policy_is_metadata_only(&policy) == 0,
                "authority verification policy helper rejected");

    EXPECT_TRUE(latticra_seal_verification_policy_from_signature(&signature, "key", "local", &policy) == LATTICRA_STATUS_OK, "flag verification policy source");
    policy.network_lookup_allowed = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_verification_policy_report(&policy, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "flag verification policy render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "flag verification policy render cleared");
    EXPECT_TRUE(latticra_seal_verification_policy_is_metadata_only(&policy) == 0,
                "flag verification policy helper rejected");
    return 0;
}

int main(void) {
    if (policy_copies_signature_metadata() != 0) {
        return 1;
    }
    if (policy_defaults_trust_source() != 0) {
        return 1;
    }
    if (policy_fails_closed() != 0) {
        return 1;
    }
    printf("seal verification policy invariants: ok\n");
    return 0;
}
