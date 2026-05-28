#include "latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int vector_fixture_digest_ledger_is_fail_closed(void) {
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t ledger;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(&ledger) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(ledger.vector_fixture_digest_ledger_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            ledger.ledger_profile,
            "latticra-q-seal-ml-kem-vector-fixture-digest-ledger/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            ledger.formal_title,
            "Latticra Q-Seal ML-KEM Vector Fixture Digest Ledger") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(ledger.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(ledger.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(ledger.acvp_ml_kem_schema_bound == 1u, "acvp");
    EXPECT_TRUE(ledger.acvp_fixture_row_plan_bound == 1u, "fixture row plan");
    EXPECT_TRUE(
        ledger.acvp_fixture_digest_row_template_bound == 1u,
        "fixture digest row template");
    EXPECT_TRUE(ledger.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(ledger.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(ledger.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(ledger.kat_manifest_bound == 1u, "kat");
    EXPECT_TRUE(ledger.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(ledger.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(ledger.digest_algorithm_sha256_required == 1u, "digest");
    EXPECT_TRUE(ledger.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(ledger.offline_only_digest_recorded == 1u, "offline");
    EXPECT_TRUE(ledger.manifest_row_schema_recorded == 1u, "schema row");
    EXPECT_TRUE(ledger.canonical_path_policy_recorded == 1u, "path policy");
    EXPECT_TRUE(ledger.bundle_size_policy_recorded == 1u, "size policy");
    EXPECT_TRUE(ledger.parameter_coverage_policy_recorded == 1u, "parameter policy");
    EXPECT_TRUE(ledger.negative_case_coverage_policy_recorded == 1u, "negative policy");
    EXPECT_TRUE(ledger.import_review_policy_recorded == 1u, "import policy");
    EXPECT_TRUE(ledger.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(ledger.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(ledger.fixture_source_url_recorded == 0u, "source url");
    EXPECT_TRUE(ledger.fixture_source_digest_recorded == 0u, "source digest");
    EXPECT_TRUE(ledger.fixture_bundle_size_recorded == 0u, "bundle size");
    EXPECT_TRUE(ledger.fixture_license_review_recorded == 0u, "license");
    EXPECT_TRUE(ledger.fixture_storage_path_recorded == 0u, "storage");
    EXPECT_TRUE(ledger.fixture_schema_crosscheck_recorded == 0u, "crosscheck");
    EXPECT_TRUE(ledger.ml_kem_512_coverage_recorded == 0u, "512");
    EXPECT_TRUE(ledger.ml_kem_768_coverage_recorded == 0u, "768");
    EXPECT_TRUE(ledger.ml_kem_1024_coverage_recorded == 0u, "1024");
    EXPECT_TRUE(ledger.keygen_coverage_recorded == 0u, "keygen");
    EXPECT_TRUE(ledger.encaps_coverage_recorded == 0u, "encaps");
    EXPECT_TRUE(ledger.decaps_coverage_recorded == 0u, "decaps");
    EXPECT_TRUE(ledger.negative_case_coverage_recorded == 0u, "negative coverage");
    EXPECT_TRUE(ledger.fixture_import_reviewed == 0u, "import review");
    EXPECT_TRUE(ledger.fixture_digest_ledger_reviewed == 0u, "ledger review");
    EXPECT_TRUE(ledger.fixture_bundle_loaded == 0u, "loaded");
    EXPECT_TRUE(ledger.vector_execution_allowed == 0u, "vector execution");
    EXPECT_TRUE(ledger.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(ledger.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(ledger.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(ledger.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(ledger.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(ledger.required_fixture_digest_items_total == 35u, "total");
    EXPECT_TRUE(ledger.required_fixture_digest_items_satisfied == 20u, "satisfied");
    EXPECT_TRUE(
        ledger.error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_BLOCKED,
        "error");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_is_no_effect(&ledger) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_allows_fixture_lock(
            &ledger) == 0,
        "fixture lock");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
            &ledger,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "vector_fixture_digest_ledger_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_row_plan_bound=1") != 0,
        "row plan report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_digest_row_template_bound=1") != 0,
        "template report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_source_digest_recorded=0") != 0,
        "digest report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_digest_ledger_reviewed=0") != 0,
        "review report");
    EXPECT_TRUE(
        strstr(rendered, "required_fixture_digest_items_total=35") != 0,
        "total report");
    return 0;
}

static int vector_fixture_digest_ledger_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t ledger;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_allows_fixture_lock(0) ==
            0,
        "null lock");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(&ledger) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
            &ledger,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
            &ledger,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (vector_fixture_digest_ledger_is_fail_closed() != 0) {
        return 1;
    }
    if (vector_fixture_digest_ledger_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem vector fixture digest ledger invariants: ok\n");
    return 0;
}
