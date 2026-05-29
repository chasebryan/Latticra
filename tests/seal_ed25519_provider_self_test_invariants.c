#include "latticra/seal_ed25519_provider_self_test.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int provider_unavailable_fails_closed(
    const latticra_seal_ed25519_provider_self_test_t *self_test,
    char rendered[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_REPORT_MAX]) {
    EXPECT_TRUE(
        self_test->error == LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE,
        "provider unavailable error");
    EXPECT_TRUE(self_test->provider_linked == 1u, "provider linked unavailable");
    EXPECT_TRUE(self_test->ed25519_private_key_output_emitted == 0u, "unavailable no private key output");
    EXPECT_TRUE(self_test->ed25519_signature_output_emitted == 0u, "unavailable no signature output");
    EXPECT_TRUE(self_test->signing_authority_granted == 0u, "unavailable authority");
    EXPECT_TRUE(self_test->runtime_authority_granted == 0u, "unavailable runtime");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_is_authority_neutral(self_test) == 1,
        "unavailable authority neutral");
    EXPECT_TRUE(
        strcmp(self_test->operation_state, "ed25519-provider-unavailable") == 0,
        "unavailable state");
    EXPECT_TRUE(
        strcmp(self_test->blocked_reason, "ed25519-provider-unavailable") == 0,
        "unavailable blocked reason");
    EXPECT_TRUE(
        strcmp(self_test->status, "ed25519-provider-self-test-provider-unavailable") == 0,
        "unavailable status");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_report(
            self_test,
            rendered,
            LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_REPORT_MAX) == LATTICRA_STATUS_OK,
        "unavailable report");
    EXPECT_TRUE(
        strstr(rendered, "error=provider-unavailable") != 0,
        "unavailable report error");
    EXPECT_TRUE(
        strstr(rendered, "runtime_authority_granted=0") != 0,
        "unavailable report runtime");
    return 0;
}

static int provider_self_test_passes(void) {
    latticra_seal_ed25519_provider_self_test_t self_test;
    char rendered[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_REPORT_MAX];
    char tiny[1];

    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_run(&self_test) == LATTICRA_STATUS_OK,
        "self-test status");
    EXPECT_TRUE(
        strcmp(self_test.self_test_profile, "latticra-seal-ed25519-provider-self-test/0.1") == 0,
        "profile");
    EXPECT_TRUE(strcmp(self_test.provider_name, "OpenSSL-EVP") == 0, "provider");
    EXPECT_TRUE(strcmp(self_test.signature_algorithm, "Ed25519") == 0, "algorithm");
    EXPECT_TRUE(strstr(self_test.standards_source, "NIST-FIPS-186-5") != 0, "fips source");
    EXPECT_TRUE(strstr(self_test.standards_source, "RFC-8032") != 0, "rfc source");
    EXPECT_TRUE(self_test.message_prehashed_before_signing == 0u, "no prehash before signing");
    EXPECT_TRUE(self_test.ed25519_private_key_exported == 0u, "private key not exported");
    EXPECT_TRUE(self_test.ed25519_private_key_output_emitted == 0u, "private key output");
    EXPECT_TRUE(self_test.ed25519_public_key_output_emitted == 0u, "public key output");
    EXPECT_TRUE(self_test.ed25519_signature_output_emitted == 0u, "signature output");
    EXPECT_TRUE(self_test.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(self_test.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(self_test.signing_authority_granted == 0u, "signing authority");
    EXPECT_TRUE(self_test.key_storage_allowed == 0u, "key storage");
    EXPECT_TRUE(self_test.network_lookup_allowed == 0u, "network");
    EXPECT_TRUE(self_test.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_is_authority_neutral(&self_test) == 1,
        "authority neutral");

    if (self_test.error != LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_OK) {
        return provider_unavailable_fails_closed(&self_test, rendered);
    }

    EXPECT_TRUE(self_test.provider_linked == 1u, "provider linked");
    EXPECT_TRUE(self_test.provider_runtime_used == 1u, "provider runtime");
    EXPECT_TRUE(self_test.ed25519_key_generation_performed == 1u, "keygen");
    EXPECT_TRUE(self_test.ed25519_public_key_export_performed == 1u, "public key export");
    EXPECT_TRUE(self_test.ed25519_public_key_only_verification_performed == 1u, "public-key-only verify");
    EXPECT_TRUE(self_test.ed25519_signature_generation_performed == 1u, "signature generation");
    EXPECT_TRUE(self_test.ed25519_signature_verification_performed == 1u, "signature verification");
    EXPECT_TRUE(self_test.ed25519_signature_valid == 1u, "signature valid");
    EXPECT_TRUE(self_test.ed25519_tampered_message_rejected == 1u, "tampered message rejected");
    EXPECT_TRUE(self_test.ed25519_tampered_signature_rejected == 1u, "tampered signature rejected");
    EXPECT_TRUE(
        self_test.ed25519_public_key_bytes ==
            LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PUBLIC_KEY_BYTES,
        "public key bytes");
    EXPECT_TRUE(
        self_test.ed25519_signature_bytes ==
            LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES,
        "signature bytes");
    EXPECT_TRUE(self_test.one_shot_sign_api_used == 1u, "one-shot sign");
    EXPECT_TRUE(self_test.one_shot_verify_api_used == 1u, "one-shot verify");
    EXPECT_TRUE(self_test.public_key_buffer_zeroized == 1u, "public key zeroized");
    EXPECT_TRUE(self_test.signature_buffer_zeroized == 1u, "signature zeroized");
    EXPECT_TRUE(
        strcmp(self_test.operation_state, "ed25519-provider-self-test-passed") == 0,
        "state");
    EXPECT_TRUE(strcmp(self_test.blocked_reason, "authority-remains-denied") == 0, "blocked");
    EXPECT_TRUE(strcmp(self_test.status, "ed25519-provider-self-test-passed") == 0, "status");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_report(
            &self_test,
            rendered,
            sizeof(rendered)) == LATTICRA_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA SEAL ED25519 PROVIDER SELF-TEST") != 0,
        "report header");
    EXPECT_TRUE(strstr(rendered, "ed25519_key_generation_performed=1") != 0, "report keygen");
    EXPECT_TRUE(
        strstr(rendered, "ed25519_signature_generation_performed=1") != 0,
        "report sign");
    EXPECT_TRUE(
        strstr(rendered, "ed25519_signature_verification_performed=1") != 0,
        "report verify");
    EXPECT_TRUE(
        strstr(rendered, "ed25519_tampered_signature_rejected=1") != 0,
        "report tamper");
    EXPECT_TRUE(
        strstr(rendered, "ed25519_private_key_output_emitted=0") != 0,
        "report no private key");
    EXPECT_TRUE(
        strstr(rendered, "ed25519_signature_output_emitted=0") != 0,
        "report no signature output");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_report(&self_test, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report cleared");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_report(0, rendered, sizeof(rendered)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null self test report");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_report(&self_test, 0, sizeof(rendered)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    latticra_seal_ed25519_provider_self_test_t self_test;

    if (provider_self_test_passes() != 0) {
        return 1;
    }

    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_run(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_is_authority_neutral(0) == 0,
        "null authority helper");
    memset(&self_test, 0, sizeof(self_test));
    self_test.ed25519_private_key_output_emitted = 1u;
    EXPECT_TRUE(
        latticra_seal_ed25519_provider_self_test_is_authority_neutral(&self_test) == 0,
        "authority helper detects output");

    printf("seal ed25519 provider self-test invariants: ok\n");
    return 0;
}
