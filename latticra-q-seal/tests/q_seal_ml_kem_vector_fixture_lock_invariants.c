#include "latticra/q_seal_ml_kem_vector_fixture_lock.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int vector_fixture_lock_is_fail_closed(void) {
    latticra_q_seal_ml_kem_vector_fixture_lock_t lock;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_prepare(&lock) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(lock.vector_fixture_lock_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(lock.lock_profile, "latticra-q-seal-ml-kem-vector-fixture-lock/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(lock.formal_title, "Latticra Q-Seal ML-KEM Vector Fixture Lock") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(lock.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(lock.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(lock.acvp_ml_kem_schema_bound == 1u, "acvp");
    EXPECT_TRUE(lock.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(lock.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(lock.kat_manifest_bound == 1u, "kat");
    EXPECT_TRUE(lock.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(lock.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(lock.digest_algorithm_sha256_required == 1u, "digest");
    EXPECT_TRUE(lock.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(lock.offline_only_fixture_recorded == 1u, "offline");
    EXPECT_TRUE(lock.fixture_manifest_schema_recorded == 1u, "manifest schema");
    EXPECT_TRUE(lock.fixture_hash_manifest_required == 1u, "hash manifest");
    EXPECT_TRUE(lock.ml_kem_512_fixture_required == 1u, "512");
    EXPECT_TRUE(lock.ml_kem_768_fixture_required == 1u, "768");
    EXPECT_TRUE(lock.ml_kem_1024_fixture_required == 1u, "1024");
    EXPECT_TRUE(lock.keygen_fixture_family_required == 1u, "keygen");
    EXPECT_TRUE(lock.encaps_fixture_family_required == 1u, "encaps");
    EXPECT_TRUE(lock.decaps_fixture_family_required == 1u, "decaps");
    EXPECT_TRUE(lock.malformed_fixture_family_required == 1u, "malformed");
    EXPECT_TRUE(lock.implicit_rejection_fixture_required == 1u, "implicit");
    EXPECT_TRUE(lock.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(lock.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(lock.fixture_source_digest_recorded == 0u, "source digest");
    EXPECT_TRUE(lock.fixture_license_review_recorded == 0u, "license");
    EXPECT_TRUE(lock.fixture_storage_path_recorded == 0u, "storage");
    EXPECT_TRUE(lock.fixture_schema_crosscheck_recorded == 0u, "crosscheck");
    EXPECT_TRUE(lock.fixture_parameter_coverage_recorded == 0u, "coverage");
    EXPECT_TRUE(lock.fixture_negative_case_coverage_recorded == 0u, "negative coverage");
    EXPECT_TRUE(lock.fixture_import_reviewed == 0u, "review");
    EXPECT_TRUE(lock.fixture_bundle_loaded == 0u, "loaded");
    EXPECT_TRUE(lock.vector_execution_allowed == 0u, "vector execution");
    EXPECT_TRUE(lock.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(lock.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(lock.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(lock.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(lock.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(lock.required_fixture_lock_items_total == 28u, "total");
    EXPECT_TRUE(lock.required_fixture_lock_items_satisfied == 21u, "satisfied");
    EXPECT_TRUE(
        lock.error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_BLOCKED,
        "error");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_is_no_effect(&lock) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_allows_vector_execution(&lock) ==
            0,
        "execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_report(
            &lock,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "vector_fixture_lock_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_source_digest_recorded=0") != 0,
        "digest report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_bundle_loaded=0") != 0,
        "loaded report");
    EXPECT_TRUE(
        strstr(rendered, "required_fixture_lock_items_total=28") != 0,
        "total report");
    return 0;
}

static int vector_fixture_lock_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_vector_fixture_lock_t lock;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_allows_vector_execution(0) == 0,
        "null execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_prepare(&lock) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_report(&lock, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_lock_report(&lock, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (vector_fixture_lock_is_fail_closed() != 0) {
        return 1;
    }
    if (vector_fixture_lock_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem vector fixture lock invariants: ok\n");
    return 0;
}
