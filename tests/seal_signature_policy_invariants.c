#include "latticra/seal_signature_policy.h"

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
    manifest.error = LATTICRA_SEAL_MANIFEST_OK;
    (void)snprintf(manifest.status, sizeof(manifest.status), "%s", "unsigned-manifest");
    return manifest;
}

static int policy_copies_manifest_metadata(void) {
    latticra_seal_manifest_t manifest = fixture_manifest();
    latticra_seal_signature_policy_t policy;
    char rendered[LATTICRA_SEAL_SIGNATURE_POLICY_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_signature_policy_from_manifest(&manifest, &policy) == LATTICRA_STATUS_OK, "policy status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_SIGNATURE_POLICY_OK, "policy ok");
    EXPECT_TRUE(strcmp(policy.policy_profile, "latticra-seal-signature-policy/0.1") == 0, "policy profile");
    EXPECT_TRUE(strcmp(policy.manifest_profile, "latticra-seal-manifest/0.1") == 0, "manifest profile");
    EXPECT_TRUE(strcmp(policy.manifest_kind, "unsigned-evidence-manifest") == 0, "manifest kind");
    EXPECT_TRUE(strcmp(policy.signature_state, "unsupported") == 0, "signature state");
    EXPECT_TRUE(policy.signature_supported == 0u, "signature flag");
    EXPECT_TRUE(policy.verification_supported == 0u, "verification flag");
    EXPECT_TRUE(policy.public_key_metadata_supported == 0u, "public metadata flag");
    EXPECT_TRUE(policy.private_key_handling == 0u, "private key flag");
    EXPECT_TRUE(policy.network_lookup_allowed == 0u, "network flag");
    EXPECT_TRUE(policy.runtime_authority_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_signature_policy_is_metadata_only(&policy) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signature_policy_report(&policy, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNATURE POLICY") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signature_supported=0") != 0, "render signature flag");
    EXPECT_TRUE(strstr(rendered, "verification_supported=0") != 0, "render verification flag");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    return 0;
}

static int policy_fails_closed(void) {
    latticra_seal_manifest_t manifest = fixture_manifest();
    latticra_seal_signature_policy_t policy;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_signature_policy_from_manifest(0, &policy) == LATTICRA_STATUS_OK, "null manifest status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_INPUT, "null manifest error");
    manifest.error = LATTICRA_SEAL_MANIFEST_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_signature_policy_from_manifest(&manifest, &policy) == LATTICRA_STATUS_OK, "bad manifest status");
    EXPECT_TRUE(policy.error == LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_MANIFEST, "bad manifest error");
    EXPECT_TRUE(latticra_seal_signature_policy_from_manifest(&manifest, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signature_policy_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signature_policy_report(&policy, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_signature_policy_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null policy");
    EXPECT_TRUE(latticra_seal_signature_policy_report(&policy, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (policy_copies_manifest_metadata() != 0) {
        return 1;
    }
    if (policy_fails_closed() != 0) {
        return 1;
    }
    printf("seal signature policy invariants: ok\n");
    return 0;
}
