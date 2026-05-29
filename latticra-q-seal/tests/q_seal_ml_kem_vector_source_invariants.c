#include "latticra/q_seal_ml_kem_vector_source.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int vector_source_intake_records_authority_without_fetching(void) {
    latticra_q_seal_ml_kem_vector_source_t source;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_prepare(&source) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(source.source_profile, "latticra-q-seal-ml-kem-vector-source/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(source.formal_title, "Latticra Q-Seal ML-KEM Vector Source Intake") == 0,
        "title");
    EXPECT_TRUE(strcmp(source.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(strcmp(source.acvp_document, "NIST-ACVP-ML-KEM-JSON") == 0, "acvp");
    EXPECT_TRUE(
        strcmp(source.approved_source_authority, "NIST-ACVP-or-reviewed-equivalent") == 0,
        "authority");
    EXPECT_TRUE(strcmp(source.digest_algorithm, "SHA-256") == 0, "digest");
    EXPECT_TRUE(
        strcmp(source.source_state, "authority-and-digest-policy-recorded-bundle-not-accepted") == 0,
        "state");
    EXPECT_TRUE(source.vector_source_intake_present == 1u, "present");
    EXPECT_TRUE(source.fips_203_source_verified == 1u, "fips");
    EXPECT_TRUE(source.acvp_documentation_tracked == 1u, "acvp tracked");
    EXPECT_TRUE(source.approved_source_authority_recorded == 1u, "authority recorded");
    EXPECT_TRUE(source.source_freshness_policy_recorded == 1u, "freshness");
    EXPECT_TRUE(source.digest_algorithm_recorded == 1u, "digest recorded");
    EXPECT_TRUE(source.bundle_source_url_recorded == 0u, "bundle url");
    EXPECT_TRUE(source.bundle_digest_recorded == 0u, "bundle digest");
    EXPECT_TRUE(source.bundle_size_recorded == 0u, "bundle size");
    EXPECT_TRUE(source.bundle_license_review_recorded == 0u, "license");
    EXPECT_TRUE(source.bundle_hash_verified == 0u, "hash verified");
    EXPECT_TRUE(source.bundle_schema_crosscheck_recorded == 0u, "schema crosscheck");
    EXPECT_TRUE(source.errata_review_binding_recorded == 0u, "errata");
    EXPECT_TRUE(source.offline_storage_path_recorded == 0u, "storage path");
    EXPECT_TRUE(source.bundle_import_review_recorded == 0u, "import review");
    EXPECT_TRUE(source.bundle_fetch_performed == 0u, "fetch");
    EXPECT_TRUE(source.bundle_imported == 0u, "imported");
    EXPECT_TRUE(source.network_fetch_enabled == 0u, "network");
    EXPECT_TRUE(source.vector_processing_allowed == 0u, "processing");
    EXPECT_TRUE(source.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(source.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(source.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(source.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(source.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(source.required_source_items_total == 14u, "total");
    EXPECT_TRUE(source.required_source_items_satisfied == 5u, "satisfied");
    EXPECT_TRUE(source.error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_is_no_fetch(&source) == 1,
        "no fetch");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(&source) == 0,
        "bundle acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_report(&source, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM VECTOR SOURCE INTAKE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "vector_source_intake_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "digest_algorithm=SHA-256") != 0, "digest report");
    EXPECT_TRUE(strstr(rendered, "bundle_source_url_recorded=0") != 0, "url report");
    EXPECT_TRUE(strstr(rendered, "bundle_hash_verified=0") != 0, "hash report");
    EXPECT_TRUE(strstr(rendered, "network_fetch_enabled=0") != 0, "network report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-vector-source-intake-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_vector_source_t source;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_vector_source_is_no_fetch(0) == 0, "null no fetch");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_prepare(&source) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_report(&source, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report source");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_source_report(&source, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (vector_source_intake_records_authority_without_fetching() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem vector source invariants: ok\n");
    return 0;
}
