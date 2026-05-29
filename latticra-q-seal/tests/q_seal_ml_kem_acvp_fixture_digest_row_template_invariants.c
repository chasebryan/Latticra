#include "latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_fixture_digest_row_template_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t template_record;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(
            &template_record) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        template_record.acvp_fixture_digest_row_template_present == 1u,
        "present");
    EXPECT_TRUE(
        strcmp(
            template_record.template_profile,
            "latticra-q-seal-ml-kem-acvp-fixture-digest-row-template/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            template_record.formal_title,
            "Latticra Q-Seal ML-KEM ACVP Fixture Digest Row Template") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(template_record.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") ==
            0,
        "standards");
    EXPECT_TRUE(template_record.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(template_record.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(template_record.acvp_fixture_row_plan_bound == 1u, "row plan");
    EXPECT_TRUE(
        template_record.vector_fixture_digest_ledger_bound == 1u,
        "digest ledger");
    EXPECT_TRUE(template_record.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(template_record.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(template_record.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(template_record.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(template_record.row_id_column_required == 1u, "row id");
    EXPECT_TRUE(template_record.parameter_set_column_required == 1u, "parameter");
    EXPECT_TRUE(template_record.mode_column_required == 1u, "mode");
    EXPECT_TRUE(template_record.test_type_column_required == 1u, "test type");
    EXPECT_TRUE(template_record.function_column_required == 1u, "function");
    EXPECT_TRUE(template_record.source_url_column_required == 1u, "source url");
    EXPECT_TRUE(template_record.sha256_digest_column_required == 1u, "digest");
    EXPECT_TRUE(template_record.bundle_size_column_required == 1u, "size");
    EXPECT_TRUE(template_record.storage_path_column_required == 1u, "storage");
    EXPECT_TRUE(template_record.license_review_column_required == 1u, "license");
    EXPECT_TRUE(template_record.schema_crosscheck_column_required == 1u, "crosscheck");
    EXPECT_TRUE(template_record.reviewer_identity_column_required == 1u, "reviewer");
    EXPECT_TRUE(template_record.review_timestamp_column_required == 1u, "timestamp");
    EXPECT_TRUE(template_record.ci_replay_transcript_column_required == 1u, "transcript");
    EXPECT_TRUE(template_record.tamper_evidence_column_required == 1u, "tamper");
    EXPECT_TRUE(template_record.planned_fixture_digest_rows_required == 15u, "rows required");
    EXPECT_TRUE(template_record.planned_fixture_digest_rows_reserved == 15u, "rows reserved");
    EXPECT_TRUE(template_record.ml_kem_512_row_class_reserved == 1u, "512");
    EXPECT_TRUE(template_record.ml_kem_768_row_class_reserved == 1u, "768");
    EXPECT_TRUE(template_record.ml_kem_1024_row_class_reserved == 1u, "1024");
    EXPECT_TRUE(template_record.keygen_row_class_reserved == 1u, "keygen");
    EXPECT_TRUE(template_record.encaps_row_class_reserved == 1u, "encaps");
    EXPECT_TRUE(template_record.decaps_row_class_reserved == 1u, "decaps");
    EXPECT_TRUE(template_record.val_row_class_reserved == 1u, "val");
    EXPECT_TRUE(template_record.key_check_row_class_reserved == 1u, "key check");
    EXPECT_TRUE(template_record.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(template_record.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(template_record.fixture_digest_rows_recorded == 0u, "rows");
    EXPECT_TRUE(template_record.source_url_rows_recorded == 0u, "source rows");
    EXPECT_TRUE(template_record.sha256_digest_rows_recorded == 0u, "digest rows");
    EXPECT_TRUE(template_record.bundle_size_rows_recorded == 0u, "size rows");
    EXPECT_TRUE(template_record.storage_path_rows_recorded == 0u, "storage rows");
    EXPECT_TRUE(template_record.license_review_rows_recorded == 0u, "license rows");
    EXPECT_TRUE(template_record.schema_crosscheck_rows_recorded == 0u, "schema rows");
    EXPECT_TRUE(template_record.reviewer_identity_rows_recorded == 0u, "reviewer rows");
    EXPECT_TRUE(template_record.review_timestamp_rows_recorded == 0u, "timestamp rows");
    EXPECT_TRUE(template_record.ci_replay_transcript_rows_recorded == 0u, "ci rows");
    EXPECT_TRUE(template_record.tamper_evidence_rows_recorded == 0u, "tamper rows");
    EXPECT_TRUE(template_record.digest_row_template_reviewed == 0u, "review");
    EXPECT_TRUE(
        template_record.fixture_digest_row_acceptance_allowed == 0u,
        "acceptance");
    EXPECT_TRUE(template_record.fixture_bundle_loaded == 0u, "bundle");
    EXPECT_TRUE(template_record.vector_execution_allowed == 0u, "vector");
    EXPECT_TRUE(template_record.response_json_generation_enabled == 0u, "response");
    EXPECT_TRUE(template_record.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(template_record.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(template_record.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(template_record.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(template_record.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(
        template_record.required_digest_row_template_items_total == 45u,
        "total");
    EXPECT_TRUE(
        template_record.required_digest_row_template_items_satisfied == 33u,
        "satisfied");
    EXPECT_TRUE(
        template_record.error ==
            LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_is_no_effect(
            &template_record) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_allows_digest_row_acceptance(
            &template_record) == 0,
        "accepts rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
            &template_record,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_digest_row_template_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "planned_fixture_digest_rows_reserved=15") != 0,
        "rows report");
    EXPECT_TRUE(
        strstr(rendered, "sha256_digest_rows_recorded=0") != 0,
        "digest report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_digest_row_acceptance_allowed=0") != 0,
        "acceptance report");
    EXPECT_TRUE(
        strstr(rendered, "required_digest_row_template_items_total=45") != 0,
        "total report");
    return 0;
}

static int acvp_fixture_digest_row_template_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t template_record;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_allows_digest_row_acceptance(
            0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(
            &template_record) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
            &template_record,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
            &template_record,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_fixture_digest_row_template_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_fixture_digest_row_template_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp fixture digest row template invariants: ok\n");
    return 0;
}
