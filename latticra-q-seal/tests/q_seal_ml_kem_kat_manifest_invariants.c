#include "latticra/q_seal_ml_kem_kat_manifest.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int kat_manifest_is_fail_closed(void) {
    latticra_q_seal_ml_kem_kat_manifest_t manifest;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(manifest.ml_kem_kat_manifest_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(manifest.manifest_profile, "latticra-q-seal-ml-kem-kat-manifest/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(manifest.formal_title, "Latticra Q-Seal ML-KEM KAT Manifest") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(manifest.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") ==
            0,
        "standards");
    EXPECT_TRUE(manifest.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(manifest.acvp_ml_kem_schema_bound == 1u, "acvp schema");
    EXPECT_TRUE(manifest.acvp_keygen_aft_required == 1u, "keygen aft");
    EXPECT_TRUE(manifest.acvp_encapdecap_aft_required == 1u, "encap aft");
    EXPECT_TRUE(manifest.acvp_decapsulation_val_required == 1u, "decap val");
    EXPECT_TRUE(manifest.acvp_keycheck_val_required == 1u, "key check");
    EXPECT_TRUE(manifest.ml_kem_512_coverage_required == 1u, "512");
    EXPECT_TRUE(manifest.ml_kem_768_coverage_required == 1u, "768");
    EXPECT_TRUE(manifest.ml_kem_1024_coverage_required == 1u, "1024");
    EXPECT_TRUE(manifest.seed_material_handling_policy_recorded == 1u, "seed");
    EXPECT_TRUE(manifest.positive_vector_family_required == 1u, "positive");
    EXPECT_TRUE(manifest.negative_vector_family_required == 1u, "negative");
    EXPECT_TRUE(manifest.malformed_vector_family_required == 1u, "malformed");
    EXPECT_TRUE(manifest.implicit_rejection_vector_required == 1u, "implicit");
    EXPECT_TRUE(manifest.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(manifest.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(manifest.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(manifest.vector_source_bound == 1u, "source");
    EXPECT_TRUE(manifest.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(manifest.vector_fixture_digest_ledger_bound == 1u, "ledger");
    EXPECT_TRUE(manifest.negative_test_evidence_bound == 1u, "negative evidence");
    EXPECT_TRUE(manifest.provider_differential_bound == 1u, "provider");
    EXPECT_TRUE(manifest.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(manifest.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(manifest.no_embedded_vectors_policy_recorded == 1u, "no embedded");
    EXPECT_TRUE(manifest.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(manifest.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(manifest.kat_runner_implementation_present == 0u, "runner");
    EXPECT_TRUE(manifest.vector_bundle_digest_recorded == 0u, "digest");
    EXPECT_TRUE(manifest.vector_bundle_license_reviewed == 0u, "license");
    EXPECT_TRUE(manifest.vector_bundle_storage_reviewed == 0u, "storage");
    EXPECT_TRUE(manifest.kat_parser_reviewed == 0u, "parser review");
    EXPECT_TRUE(manifest.positive_vectors_verified == 0u, "positive verified");
    EXPECT_TRUE(manifest.negative_vectors_verified == 0u, "negative verified");
    EXPECT_TRUE(manifest.malformed_vectors_verified == 0u, "malformed verified");
    EXPECT_TRUE(manifest.cross_provider_differential_recorded == 0u, "differential");
    EXPECT_TRUE(manifest.ci_kat_replay_recorded == 0u, "ci");
    EXPECT_TRUE(manifest.known_answer_vectors_loaded == 0u, "loaded");
    EXPECT_TRUE(manifest.known_answer_vectors_verified == 0u, "verified");
    EXPECT_TRUE(manifest.acvp_vector_review_recorded == 0u, "review");
    EXPECT_TRUE(manifest.operation_implementation_present == 0u, "implementation");
    EXPECT_TRUE(manifest.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(manifest.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(manifest.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(manifest.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(manifest.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(manifest.required_kat_manifest_items_total == 40u, "total");
    EXPECT_TRUE(manifest.required_kat_manifest_items_satisfied == 26u, "satisfied");
    EXPECT_TRUE(
        manifest.error == LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_is_no_effect(&manifest) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_allows_kat_execution(&manifest) == 0,
        "allows kat");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_report(&manifest, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "ml_kem_kat_manifest_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "acvp_keygen_aft_required=1") != 0, "keygen report");
    EXPECT_TRUE(strstr(rendered, "known_answer_vectors_loaded=0") != 0, "loaded report");
    EXPECT_TRUE(
        strstr(rendered, "required_kat_manifest_items_total=40") != 0,
        "total report");
    return 0;
}

static int kat_manifest_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_kat_manifest_t manifest;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_kat_manifest_is_no_effect(0) == 0, "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_allows_kat_execution(0) == 0,
        "null execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_report(&manifest, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_manifest_report(&manifest, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (kat_manifest_is_fail_closed() != 0) {
        return 1;
    }
    if (kat_manifest_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem kat manifest invariants: ok\n");
    return 0;
}
