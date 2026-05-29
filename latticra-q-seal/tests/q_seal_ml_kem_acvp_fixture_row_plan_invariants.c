#include "latticra/q_seal_ml_kem_acvp_fixture_row_plan.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_fixture_row_plan_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_t plan;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(&plan) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(plan.acvp_fixture_row_plan_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(plan.row_plan_profile, "latticra-q-seal-ml-kem-acvp-fixture-row-plan/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(plan.formal_title, "Latticra Q-Seal ML-KEM ACVP Fixture Row Plan") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(plan.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(plan.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(plan.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(plan.acvp_capability_matrix_bound == 1u, "matrix");
    EXPECT_TRUE(plan.acvp_fixture_digest_row_template_bound == 1u, "template");
    EXPECT_TRUE(plan.vector_fixture_digest_ledger_bound == 1u, "ledger");
    EXPECT_TRUE(plan.top_level_vector_set_fields_recorded == 1u, "vector set");
    EXPECT_TRUE(plan.test_group_fields_recorded == 1u, "group fields");
    EXPECT_TRUE(plan.test_case_fields_recorded == 1u, "case fields");
    EXPECT_TRUE(plan.response_group_fields_recorded == 1u, "response group");
    EXPECT_TRUE(plan.response_case_fields_recorded == 1u, "response case");
    EXPECT_TRUE(plan.parameter_set_rows_total == 3u, "parameter total");
    EXPECT_TRUE(plan.parameter_set_rows_planned == 3u, "parameter planned");
    EXPECT_TRUE(plan.keygen_aft_rows_required == 3u, "keygen required");
    EXPECT_TRUE(plan.keygen_aft_rows_planned == 3u, "keygen planned");
    EXPECT_TRUE(plan.encapsulation_aft_rows_required == 3u, "encapsulation required");
    EXPECT_TRUE(plan.encapsulation_aft_rows_planned == 3u, "encapsulation planned");
    EXPECT_TRUE(plan.decapsulation_val_rows_required == 3u, "decapsulation required");
    EXPECT_TRUE(plan.decapsulation_val_rows_planned == 3u, "decapsulation planned");
    EXPECT_TRUE(
        plan.encapsulation_key_check_val_rows_required == 3u,
        "encapsulation key check required");
    EXPECT_TRUE(
        plan.encapsulation_key_check_val_rows_planned == 3u,
        "encapsulation key check planned");
    EXPECT_TRUE(
        plan.decapsulation_key_check_val_rows_required == 3u,
        "decapsulation key check required");
    EXPECT_TRUE(
        plan.decapsulation_key_check_val_rows_planned == 3u,
        "decapsulation key check planned");
    EXPECT_TRUE(plan.minimum_fixture_row_classes_required == 15u, "classes required");
    EXPECT_TRUE(plan.minimum_fixture_row_classes_planned == 15u, "classes planned");
    EXPECT_TRUE(plan.fixture_row_ids_reserved == 1u, "row ids");
    EXPECT_TRUE(plan.digest_columns_required == 1u, "digest columns");
    EXPECT_TRUE(plan.source_url_columns_required == 1u, "source columns");
    EXPECT_TRUE(plan.license_review_columns_required == 1u, "license columns");
    EXPECT_TRUE(plan.schema_crosscheck_columns_required == 1u, "schema columns");
    EXPECT_TRUE(plan.review_columns_required == 1u, "review columns");
    EXPECT_TRUE(plan.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(plan.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(plan.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(plan.acvp_registration_json_reviewed == 0u, "registration review");
    EXPECT_TRUE(plan.capability_matrix_reviewed == 0u, "matrix review");
    EXPECT_TRUE(plan.fixture_row_plan_reviewed == 0u, "plan review");
    EXPECT_TRUE(plan.fixture_digest_rows_recorded == 0u, "digest rows");
    EXPECT_TRUE(plan.fixture_source_digests_recorded == 0u, "source digests");
    EXPECT_TRUE(plan.fixture_storage_paths_recorded == 0u, "storage");
    EXPECT_TRUE(plan.fixture_license_review_recorded == 0u, "license");
    EXPECT_TRUE(plan.fixture_schema_crosscheck_recorded == 0u, "schema");
    EXPECT_TRUE(plan.fixture_import_reviewed == 0u, "import review");
    EXPECT_TRUE(plan.fixture_digest_ledger_reviewed == 0u, "ledger review");
    EXPECT_TRUE(plan.row_plan_to_digest_ledger_reviewed == 0u, "plan ledger review");
    EXPECT_TRUE(plan.fixture_bundle_loaded == 0u, "bundle");
    EXPECT_TRUE(plan.vector_execution_allowed == 0u, "vector execution");
    EXPECT_TRUE(plan.response_json_generation_enabled == 0u, "response generation");
    EXPECT_TRUE(plan.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(plan.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(plan.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(plan.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(plan.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(plan.required_fixture_row_plan_items_total == 36u, "total");
    EXPECT_TRUE(plan.required_fixture_row_plan_items_satisfied == 25u, "satisfied");
    EXPECT_TRUE(
        plan.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_is_no_effect(&plan) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_allows_fixture_digest_rows(
            &plan) == 0,
        "allows rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(
            &plan,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_row_plan_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "minimum_fixture_row_classes_planned=15") != 0, "rows report");
    EXPECT_TRUE(strstr(rendered, "fixture_digest_rows_recorded=0") != 0, "digest report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_digest_row_template_bound=1") != 0,
        "template report");
    EXPECT_TRUE(
        strstr(rendered, "required_fixture_row_plan_items_total=36") != 0,
        "total report");
    return 0;
}

static int acvp_fixture_row_plan_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_t plan;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_allows_fixture_digest_rows(0) == 0,
        "null rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(&plan) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(&plan, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(
            &plan,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_fixture_row_plan_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_fixture_row_plan_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp fixture row plan invariants: ok\n");
    return 0;
}
