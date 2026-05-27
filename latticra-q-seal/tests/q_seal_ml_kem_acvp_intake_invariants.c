#include "latticra/q_seal_ml_kem_acvp_intake.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_intake_is_offline_and_blocked(void) {
    latticra_q_seal_ml_kem_acvp_intake_t intake;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_prepare(&intake) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(intake.intake_profile, "latticra-q-seal-ml-kem-acvp-intake/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(intake.formal_title, "Latticra Q-Seal ML-KEM ACVP Intake") == 0,
        "formal title");
    EXPECT_TRUE(strcmp(intake.acvp_document, "NIST-ACVP-ML-KEM-JSON") == 0, "document");
    EXPECT_TRUE(strcmp(intake.algorithm, "ML-KEM") == 0, "algorithm");
    EXPECT_TRUE(strcmp(intake.revision, "FIPS203") == 0, "revision");
    EXPECT_TRUE(strcmp(intake.intake_state, "offline-intake-shape-only") == 0, "state");
    EXPECT_TRUE(intake.acvp_intake_present == 1u, "present");
    EXPECT_TRUE(intake.acvp_document_tracked == 1u, "document tracked");
    EXPECT_TRUE(intake.acvp_ml_kem_schema_tracked == 1u, "schema");
    EXPECT_TRUE(intake.algorithm_ml_kem_required == 1u, "algorithm required");
    EXPECT_TRUE(intake.revision_fips203_required == 1u, "revision required");
    EXPECT_TRUE(intake.keygen_mode_required == 1u, "keygen");
    EXPECT_TRUE(intake.encap_decap_mode_required == 1u, "encap decap");
    EXPECT_TRUE(intake.ml_kem_512_required == 1u, "512");
    EXPECT_TRUE(intake.ml_kem_768_required == 1u, "768");
    EXPECT_TRUE(intake.ml_kem_1024_required == 1u, "1024");
    EXPECT_TRUE(intake.vector_source_url_recorded == 0u, "source");
    EXPECT_TRUE(intake.vector_bundle_digest_recorded == 0u, "digest");
    EXPECT_TRUE(intake.vector_license_review_recorded == 0u, "license");
    EXPECT_TRUE(intake.vector_json_schema_reviewed == 0u, "schema review");
    EXPECT_TRUE(intake.vector_json_loaded == 0u, "loaded");
    EXPECT_TRUE(intake.response_json_generation_enabled == 0u, "response");
    EXPECT_TRUE(intake.offline_fixture_only == 1u, "offline");
    EXPECT_TRUE(intake.network_session_enabled == 0u, "network");
    EXPECT_TRUE(intake.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(intake.operation_execution_allowed == 0u, "operation execution");
    EXPECT_TRUE(intake.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(intake.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(intake.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(intake.required_intake_items_total == 13u, "total");
    EXPECT_TRUE(intake.required_intake_items_satisfied == 9u, "satisfied");
    EXPECT_TRUE(
        intake.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        strcmp(latticra_q_seal_ml_kem_acvp_intake_error_label(intake.error), "blocked") == 0,
        "error label");
    EXPECT_TRUE(latticra_q_seal_ml_kem_acvp_intake_is_offline_only(&intake) == 1, "offline only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(&intake) == 0,
        "allows vector execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_report(&intake, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL ML-KEM ACVP INTAKE") != 0, "header");
    EXPECT_TRUE(strstr(rendered, "algorithm=ML-KEM") != 0, "report algorithm");
    EXPECT_TRUE(strstr(rendered, "revision=FIPS203") != 0, "report revision");
    EXPECT_TRUE(strstr(rendered, "vector_json_loaded=0") != 0, "report loaded");
    EXPECT_TRUE(strstr(rendered, "network_session_enabled=0") != 0, "report network");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-acvp-intake-offline-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_intake_t intake;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_acvp_intake_is_offline_only(0) == 0, "null offline");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(0) == 0,
        "null execute");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_prepare(&intake) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_report(&intake, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report intake");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_intake_report(&intake, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (acvp_intake_is_offline_and_blocked() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp intake invariants: ok\n");
    return 0;
}
