#include "latticra/seal_hybrid_provider_self_test.h"

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
    const latticra_seal_hybrid_provider_self_test_t *self_test,
    char rendered[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_REPORT_MAX]) {
    EXPECT_TRUE(
        self_test->error == LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE,
        "self-test ok or provider unavailable");
    EXPECT_TRUE(self_test->provider_linked == 1u, "provider linked unavailable");
    EXPECT_TRUE(self_test->secret_material_output_emitted == 0u, "unavailable no secret output");
    EXPECT_TRUE(self_test->record_output_emitted == 0u, "unavailable no record output");
    EXPECT_TRUE(self_test->plaintext_output_emitted == 0u, "unavailable no plaintext output");
    EXPECT_TRUE(self_test->production_crypto_claim_allowed == 0u, "unavailable production claim");
    EXPECT_TRUE(self_test->fips_claim_allowed == 0u, "unavailable fips claim");
    EXPECT_TRUE(self_test->runtime_authority_granted == 0u, "unavailable runtime");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_is_authority_neutral(self_test) == 1,
        "unavailable authority neutral");
    EXPECT_TRUE(
        strstr(self_test->operation_state, "provider-unavailable") != 0,
        "unavailable state");
    EXPECT_TRUE(
        strstr(self_test->blocked_reason, "provider-unavailable") != 0,
        "unavailable blocked reason");
    EXPECT_TRUE(
        strcmp(self_test->status, "hybrid-provider-self-test-provider-unavailable") == 0,
        "unavailable status");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_report(
            self_test,
            rendered,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_REPORT_MAX) == LATTICRA_STATUS_OK,
        "unavailable report");
    EXPECT_TRUE(
        strstr(rendered, "error=provider-unavailable") != 0,
        "unavailable report error");
    EXPECT_TRUE(
        strstr(rendered, "secret_material_output_emitted=0") != 0,
        "unavailable report no secret");
    EXPECT_TRUE(
        strstr(rendered, "runtime_authority_granted=0") != 0,
        "unavailable report no authority");
    return 0;
}

static int provider_self_test_passes(void) {
    latticra_seal_hybrid_provider_self_test_t self_test;
    char rendered[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_run(&self_test) == LATTICRA_STATUS_OK,
        "self-test status");
    EXPECT_TRUE(
        strcmp(self_test.self_test_profile, "latticra-seal-hybrid-provider-self-test/0.1") == 0,
        "profile");
    EXPECT_TRUE(strcmp(self_test.classical_provider_name, "OpenSSL-EVP") == 0, "classical provider");
    EXPECT_TRUE(strcmp(self_test.pqc_provider_name, "OpenSSL-EVP") == 0, "pqc provider");
    EXPECT_TRUE(strcmp(self_test.classical_algorithm_name, "ECDH-P-256") == 0, "p256 algorithm");
    EXPECT_TRUE(
        strcmp(self_test.pqc_algorithm_name, "ML-KEM-512,ML-KEM-768,ML-KEM-1024") == 0,
        "ml-kem algorithm");
    EXPECT_TRUE(strcmp(self_test.envelope_algorithm_name, "HKDF-SHA256+AES-256-GCM") == 0, "envelope");
    EXPECT_TRUE(strstr(self_test.standards_source, "NIST-SP-800-56A-REV3") != 0, "p256 standard");
    EXPECT_TRUE(strstr(self_test.standards_source, "NIST-FIPS-203") != 0, "ml-kem standard");
    EXPECT_TRUE(strstr(self_test.standards_source, "NIST-SP-800-90A-REV1") != 0, "random standard");
    if (self_test.error != LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_OK) {
        return provider_unavailable_fails_closed(&self_test, rendered);
    }
    EXPECT_TRUE(self_test.provider_linked == 1u, "provider linked");
    EXPECT_TRUE(self_test.classical_provider_available == 1u, "classical provider available");
    EXPECT_TRUE(self_test.pqc_provider_available == 1u, "pqc provider available");
    EXPECT_TRUE(self_test.provider_runtime_used == 1u, "provider runtime");
    EXPECT_TRUE(self_test.p256_key_generation_performed == 1u, "p256 keygen");
    EXPECT_TRUE(self_test.p256_peer_public_keys_reimported == 1u, "p256 public reimport");
    EXPECT_TRUE(self_test.p256_ecdh_peer_public_key_only == 1u, "p256 public-only peer");
    EXPECT_TRUE(self_test.p256_ecdh_derive_performed == 1u, "p256 derive");
    EXPECT_TRUE(self_test.p256_shared_secret_match == 1u, "p256 match");
    EXPECT_TRUE(
        self_test.p256_shared_secret_bytes == LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES,
        "p256 bytes");
    EXPECT_TRUE(self_test.ml_kem_key_generation_performed == 1u, "ml-kem keygen");
    EXPECT_TRUE(self_test.ml_kem_encapsulation_performed == 1u, "ml-kem encaps");
    EXPECT_TRUE(self_test.ml_kem_decapsulation_performed == 1u, "ml-kem decaps");
    EXPECT_TRUE(self_test.ml_kem_shared_secret_match == 1u, "ml-kem match");
    EXPECT_TRUE(
        self_test.ml_kem_shared_secret_bytes == LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES,
        "ml-kem bytes");
    EXPECT_TRUE(
        self_test.ml_kem_keypair_algorithm_identity_verified_cases_total == 3u,
        "ml-kem keypair algorithm identity cases");
    EXPECT_TRUE(
        self_test.ml_kem_public_key_reimported_cases_total == 3u,
        "ml-kem public reimport cases");
    EXPECT_TRUE(
        self_test.ml_kem_public_key_algorithm_identity_verified_cases_total == 3u,
        "ml-kem public key algorithm identity cases");
    EXPECT_TRUE(
        self_test.ml_kem_encapsulation_public_key_only_cases_total == 3u,
        "ml-kem public-only encaps cases");
    EXPECT_TRUE(
        self_test.ml_kem_tampered_ciphertext_shared_secret_mismatch_total == 3u,
        "ml-kem tampered ciphertext mismatch cases");
    EXPECT_TRUE(
        self_test.ml_kem_ciphertext_tampering_rejected_total == 3u,
        "ml-kem ciphertext tampering cases");
    EXPECT_TRUE(self_test.ml_kem_parameter_sets_tested == 3u, "ml-kem parameter sets");
    EXPECT_TRUE(self_test.ml_kem_512_key_generation_performed == 1u, "ml-kem-512 keygen");
    EXPECT_TRUE(self_test.ml_kem_512_encapsulation_performed == 1u, "ml-kem-512 encaps");
    EXPECT_TRUE(self_test.ml_kem_512_decapsulation_performed == 1u, "ml-kem-512 decaps");
    EXPECT_TRUE(self_test.ml_kem_512_shared_secret_match == 1u, "ml-kem-512 match");
    EXPECT_TRUE(
        self_test.ml_kem_512_ciphertext_bytes ==
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_512_CIPHERTEXT_BYTES,
        "ml-kem-512 ciphertext");
    EXPECT_TRUE(self_test.ml_kem_512_hybrid_envelope_authenticated == 1u, "ml-kem-512 envelope");
    EXPECT_TRUE(self_test.ml_kem_768_key_generation_performed == 1u, "ml-kem-768 keygen");
    EXPECT_TRUE(self_test.ml_kem_768_encapsulation_performed == 1u, "ml-kem-768 encaps");
    EXPECT_TRUE(self_test.ml_kem_768_decapsulation_performed == 1u, "ml-kem-768 decaps");
    EXPECT_TRUE(self_test.ml_kem_768_shared_secret_match == 1u, "ml-kem-768 match");
    EXPECT_TRUE(
        self_test.ml_kem_768_ciphertext_bytes ==
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_768_CIPHERTEXT_BYTES,
        "ml-kem-768 ciphertext");
    EXPECT_TRUE(self_test.ml_kem_768_hybrid_envelope_authenticated == 1u, "ml-kem-768 envelope");
    EXPECT_TRUE(self_test.ml_kem_1024_key_generation_performed == 1u, "ml-kem-1024 keygen");
    EXPECT_TRUE(self_test.ml_kem_1024_encapsulation_performed == 1u, "ml-kem-1024 encaps");
    EXPECT_TRUE(self_test.ml_kem_1024_decapsulation_performed == 1u, "ml-kem-1024 decaps");
    EXPECT_TRUE(self_test.ml_kem_1024_shared_secret_match == 1u, "ml-kem-1024 match");
    EXPECT_TRUE(
        self_test.ml_kem_1024_ciphertext_bytes ==
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_1024_CIPHERTEXT_BYTES,
        "ml-kem-1024 ciphertext");
    EXPECT_TRUE(
        self_test.ml_kem_1024_hybrid_envelope_authenticated == 1u,
        "ml-kem-1024 envelope");
    EXPECT_TRUE(self_test.hybrid_envelope_record_sealed == 1u, "record sealed");
    EXPECT_TRUE(self_test.hybrid_envelope_record_opened == 1u, "record opened");
    EXPECT_TRUE(self_test.hybrid_envelope_authenticated == 1u, "record authenticated");
    EXPECT_TRUE(self_test.hybrid_envelope_plaintext_recovered == 1u, "plaintext recovered");
    EXPECT_TRUE(self_test.hybrid_envelope_records_sealed_total == 3u, "records sealed total");
    EXPECT_TRUE(self_test.hybrid_envelope_records_opened_total == 3u, "records opened total");
    EXPECT_TRUE(
        self_test.hybrid_envelope_records_authenticated_total == 3u,
        "records authenticated total");
    EXPECT_TRUE(
        self_test.hybrid_envelope_provider_crypto_evidence_bound == 1u,
        "envelope provider crypto evidence bound");
    EXPECT_TRUE(
        self_test.hybrid_envelope_provider_crypto_cases_total == 3u,
        "envelope provider crypto cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_hkdf_provider_cases_total == 3u,
        "envelope provider hkdf cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_hkdf_sha256_cases_total == 3u,
        "envelope hkdf sha256 cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_aes_gcm_provider_cases_total == 3u,
        "envelope provider aes-gcm cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_aes_gcm_96bit_nonce_cases_total == 3u,
        "envelope aes-gcm nonce cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_aes_gcm_128bit_tag_cases_total == 3u,
        "envelope aes-gcm tag cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_commitment_mac_provider_cases_total == 3u,
        "envelope provider commitment mac cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_commitment_mac_hmac_sha256_cases_total == 3u,
        "envelope commitment hmac sha256 cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_commitment_constant_time_compare_cases_total == 3u,
        "envelope commitment constant-time compare cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_random_bytes_ex_cases_total == 3u,
        "envelope random bytes ex cases");
    EXPECT_TRUE(
        self_test.hybrid_envelope_random_bytes_strength_bits_requested ==
            LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS,
        "envelope random strength bits");
    EXPECT_TRUE(
        self_test.hybrid_envelope_no_legacy_crypto_fallback_cases_total == 3u,
        "envelope no legacy fallback cases");
    EXPECT_TRUE(self_test.hybrid_transcript_aad_bound == 1u, "transcript aad bound");
    EXPECT_TRUE(
        self_test.hybrid_transcript_cases_bound_total == 3u,
        "transcript cases bound total");
    EXPECT_TRUE(
        self_test.hybrid_transcript_tampering_rejected == 1u,
        "transcript tampering rejected");
    EXPECT_TRUE(
        self_test.hybrid_transcript_tampering_rejected_total == 3u,
        "transcript tampering total");
    EXPECT_TRUE(
        self_test.hybrid_transcript_tamper_constant_time_compare_cases_total == 3u,
        "transcript tamper constant-time compare total");
    EXPECT_TRUE(
        self_test.hybrid_envelope_wrong_pqc_secret_rejected == 1u,
        "wrong pqc secret rejected");
    EXPECT_TRUE(
        self_test.hybrid_envelope_wrong_pqc_secret_rejected_total == 3u,
        "wrong pqc secret rejected total");
    EXPECT_TRUE(
        self_test.hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total == 3u,
        "wrong pqc secret constant-time compare total");
    EXPECT_TRUE(
        self_test.provider_algorithm_transcript_bound == 1u,
        "algorithm transcript bound");
    EXPECT_TRUE(
        self_test.p256_public_key_transcript_bound == 1u,
        "p256 transcript bound");
    EXPECT_TRUE(
        self_test.p256_public_key_transcript_bytes > 0u,
        "p256 transcript bytes");
    EXPECT_TRUE(
        self_test.ml_kem_public_key_transcript_bound == 1u,
        "ml-kem public key transcript bound");
    EXPECT_TRUE(
        self_test.ml_kem_public_key_transcript_bytes_total > 0u,
        "ml-kem public key transcript bytes");
    EXPECT_TRUE(
        self_test.ml_kem_ciphertext_transcript_bound == 1u,
        "ml-kem ciphertext transcript bound");
    EXPECT_TRUE(
        self_test.ml_kem_ciphertext_transcript_bytes_total ==
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_512_CIPHERTEXT_BYTES +
                LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_768_CIPHERTEXT_BYTES +
                LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_1024_CIPHERTEXT_BYTES,
        "ml-kem ciphertext transcript bytes");
    EXPECT_TRUE(
        self_test.hybrid_transcript_aad_size_bytes >
            self_test.ml_kem_public_key_transcript_bytes_total +
                self_test.ml_kem_ciphertext_transcript_bytes_total,
        "transcript aad includes framed public keys and metadata");
    EXPECT_TRUE(self_test.classical_secret_internal_buffers_used == 1u, "classical buffer");
    EXPECT_TRUE(self_test.pqc_secret_internal_buffers_used == 1u, "pqc buffer");
    EXPECT_TRUE(self_test.secret_material_output_emitted == 0u, "secret output");
    EXPECT_TRUE(self_test.record_output_emitted == 0u, "record output");
    EXPECT_TRUE(self_test.plaintext_output_emitted == 0u, "plaintext output");
    EXPECT_TRUE(self_test.classical_secret_zeroized == 1u, "classical zeroized");
    EXPECT_TRUE(self_test.pqc_secret_zeroized == 1u, "pqc zeroized");
    EXPECT_TRUE(self_test.record_buffer_zeroized == 1u, "record zeroized");
    EXPECT_TRUE(self_test.plaintext_buffer_zeroized == 1u, "plaintext zeroized");
    EXPECT_TRUE(self_test.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(self_test.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(self_test.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_is_authority_neutral(&self_test) == 1,
        "authority neutral");
    EXPECT_TRUE(strcmp(self_test.operation_state, "hybrid-provider-self-test-passed") == 0, "state");
    EXPECT_TRUE(strcmp(self_test.blocked_reason, "authority-remains-denied") == 0, "blocked");
    EXPECT_TRUE(strcmp(self_test.status, "hybrid-provider-self-test-passed") == 0, "status");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_report(
            &self_test,
            rendered,
            sizeof(rendered)) == LATTICRA_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL HYBRID PROVIDER SELF-TEST") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "p256_shared_secret_match=1") != 0, "report p256");
    EXPECT_TRUE(
        strstr(rendered, "p256_ecdh_peer_public_key_only=1") != 0,
        "report p256 public-only peer");
    EXPECT_TRUE(strstr(rendered, "ml_kem_shared_secret_match=1") != 0, "report ml-kem");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_keypair_algorithm_identity_verified_cases_total=3") != 0,
        "report ml-kem keypair algorithm identity");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_encapsulation_public_key_only_cases_total=3") != 0,
        "report ml-kem public-only encaps");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_public_key_algorithm_identity_verified_cases_total=3") != 0,
        "report ml-kem public key algorithm identity");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_ciphertext_tampering_rejected_total=3") != 0,
        "report ml-kem ciphertext tamper");
    EXPECT_TRUE(strstr(rendered, "ml_kem_parameter_sets_tested=3") != 0, "report parameter sets");
    EXPECT_TRUE(strstr(rendered, "ml_kem_768_shared_secret_match=1") != 0, "report ml-kem-768");
    EXPECT_TRUE(strstr(rendered, "ml_kem_1024_shared_secret_match=1") != 0, "report ml-kem-1024");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_records_authenticated_total=3") != 0,
        "report record total");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_provider_crypto_cases_total=3") != 0,
        "report provider crypto cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_hkdf_provider_cases_total=3") != 0,
        "report provider hkdf cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_aes_gcm_provider_cases_total=3") != 0,
        "report provider aes-gcm cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_commitment_mac_provider_cases_total=3") != 0,
        "report provider mac cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_commitment_constant_time_compare_cases_total=3") != 0,
        "report commitment constant-time compare cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_random_bytes_ex_cases_total=3") != 0,
        "report provider random cases");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_no_legacy_crypto_fallback_cases_total=3") != 0,
        "report no legacy fallback cases");
    EXPECT_TRUE(strstr(rendered, "hybrid_transcript_cases_bound_total=3") != 0, "report transcript total");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_transcript_tampering_rejected_total=3") != 0,
        "report transcript tamper total");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_transcript_tamper_constant_time_compare_cases_total=3") != 0,
        "report transcript tamper constant-time compare total");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_wrong_pqc_secret_rejected_total=3") != 0,
        "report wrong pqc secret rejected");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total=3") != 0,
        "report wrong pqc secret constant-time compare");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_public_key_transcript_bound=1") != 0,
        "report ml-kem public key bound");
    EXPECT_TRUE(
        strstr(rendered, "ml_kem_ciphertext_transcript_bytes_total=3424") != 0,
        "report transcript ciphertext bytes");
    EXPECT_TRUE(strstr(rendered, "hybrid_envelope_authenticated=1") != 0, "report auth");
    EXPECT_TRUE(strstr(rendered, "secret_material_output_emitted=0") != 0, "report no secret");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report no authority");
    return 0;
}

static int invalid_paths_fail_closed(void) {
    latticra_seal_hybrid_provider_self_test_t self_test;
    char tiny[1];

    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_run(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null run");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_is_authority_neutral(0) == 0,
        "null neutral");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_run(&self_test) == LATTICRA_STATUS_OK,
        "valid setup");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_report(&self_test, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report");
    EXPECT_TRUE(tiny[0] == '\0', "tiny cleared");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report self");
    EXPECT_TRUE(
        latticra_seal_hybrid_provider_self_test_report(&self_test, 0, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (provider_self_test_passes() != 0) {
        return 1;
    }
    if (invalid_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra seal hybrid provider self-test invariants: ok\n");
    return 0;
}
