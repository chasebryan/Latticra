#include "latticra/seal_signature.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_manifest_t fixture_manifest(void) {
    latticra_seal_manifest_t manifest;
    memset(&manifest, 0, sizeof(manifest));
    (void)snprintf(manifest.manifest_profile, sizeof(manifest.manifest_profile), "%s", "latticra-seal-manifest/0.1");
    (void)snprintf(manifest.manifest_kind, sizeof(manifest.manifest_kind), "%s", "unsigned-evidence-manifest");
    (void)snprintf(manifest.artifact_digest_algorithm, sizeof(manifest.artifact_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(manifest.artifact_digest_hex, sizeof(manifest.artifact_digest_hex), "%s", "03284a1ae75d2b26190b094726a77884d9b21569e8f85a80b92166b1682d2ebd");
    manifest.error = LATTICRA_SEAL_MANIFEST_OK;
    (void)snprintf(manifest.status, sizeof(manifest.status), "%s", "unsigned-manifest");
    return manifest;
}

static int signature_metadata_copies_manifest_fields(void) {
    latticra_seal_manifest_t manifest = fixture_manifest();
    latticra_seal_signature_t signature;
    char rendered[LATTICRA_SEAL_SIGNATURE_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "Ed25519-development", 64u, &signature) == LATTICRA_STATUS_OK, "signature status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_OK, "signature ok");
    EXPECT_TRUE(strcmp(signature.signature_profile, "latticra-seal-signature/0.1") == 0, "signature profile");
    EXPECT_TRUE(strcmp(signature.manifest_profile, "latticra-seal-manifest/0.1") == 0, "manifest profile");
    EXPECT_TRUE(strcmp(signature.manifest_kind, "unsigned-evidence-manifest") == 0, "manifest kind");
    EXPECT_TRUE(strcmp(signature.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(signature.artifact_digest_hex, manifest.artifact_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(signature.signer_identity_label, "dev-signer") == 0, "signer label");
    EXPECT_TRUE(strcmp(signature.signature_algorithm, "Ed25519-development") == 0, "algorithm label");
    EXPECT_TRUE(strcmp(signature.signature_state, "metadata-only") == 0, "signature state");
    EXPECT_TRUE(signature.signature_byte_length == 64u, "signature length");
    EXPECT_TRUE(signature.signature_supported == 1u, "signature flag");
    EXPECT_TRUE(signature.verification_supported == 0u, "verification flag");
    EXPECT_TRUE(signature.private_key_handling == 0u, "private key flag");
    EXPECT_TRUE(signature.network_lookup_allowed == 0u, "network flag");
    EXPECT_TRUE(signature.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_signature_is_metadata_only(&signature) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signature_report(&signature, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNATURE") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signature_supported=1") != 0, "render signature flag");
    EXPECT_TRUE(strstr(rendered, "verification_supported=0") != 0, "render verify flag");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render key flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    return 0;
}

static int signature_metadata_fails_closed(void) {
    latticra_seal_manifest_t manifest = fixture_manifest();
    latticra_seal_signature_t signature;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_signature_from_manifest(0, "dev-signer", "Ed25519-development", 64u, &signature) == LATTICRA_STATUS_OK, "null manifest status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_INVALID_INPUT, "null manifest error");
    manifest.error = LATTICRA_SEAL_MANIFEST_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "Ed25519-development", 64u, &signature) == LATTICRA_STATUS_OK, "invalid manifest status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_INVALID_MANIFEST, "invalid manifest error");
    manifest = fixture_manifest();
    manifest.artifact_digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "Ed25519-development", 64u, &signature) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_MISSING_DIGEST, "missing digest error");
    manifest = fixture_manifest();
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "", "Ed25519-development", 64u, &signature) == LATTICRA_STATUS_OK, "missing signer status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_MISSING_SIGNER, "missing signer error");
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "ML-DSA", 64u, &signature) == LATTICRA_STATUS_OK, "bad algorithm status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_UNSUPPORTED_ALGORITHM, "bad algorithm error");
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "Ed25519-development", 0u, &signature) == LATTICRA_STATUS_OK, "missing metadata status");
    EXPECT_TRUE(signature.error == LATTICRA_SEAL_SIGNATURE_MISSING_SIGNATURE_METADATA, "missing metadata error");
    EXPECT_TRUE(latticra_seal_signature_from_manifest(&manifest, "dev-signer", "Ed25519-development", 64u, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signature_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signature_report(&signature, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_signature_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null signature");
    EXPECT_TRUE(latticra_seal_signature_report(&signature, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (signature_metadata_copies_manifest_fields() != 0) {
        return 1;
    }
    if (signature_metadata_fails_closed() != 0) {
        return 1;
    }
    printf("seal signature invariants: ok\n");
    return 0;
}
