#include "latticra/q_seal_ml_kem_implementation_file_digest_plan.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int implementation_file_digest_plan_is_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_file_digest_plan_t plan;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(&plan) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            plan.digest_plan_profile,
            "latticra-q-seal-ml-kem-implementation-file-digest-plan/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            plan.formal_title,
            "Latticra Q-Seal ML-KEM Implementation File Digest Plan") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            plan.standards_basis,
            "NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(strcmp(plan.digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(plan.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(plan.implementation_file_digest_plan_present == 1u, "present");
    EXPECT_TRUE(plan.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(plan.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(plan.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(plan.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(plan.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(plan.digest_algorithm_sha256_recorded == 1u, "sha256");
    EXPECT_TRUE(plan.source_digest_manifest_bound == 1u, "source digest manifest");
    EXPECT_TRUE(plan.source_digest_receipt_bound == 1u, "source digest receipt");
    EXPECT_TRUE(plan.source_digest_verification_bound == 1u, "source digest verification");
    EXPECT_TRUE(plan.receipt_replay_results_bound == 1u, "replay results");
    EXPECT_TRUE(plan.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(plan.implementation_traceability_matrix_bound == 1u, "traceability");
    EXPECT_TRUE(plan.primitive_source_acceptance_gate_bound == 1u, "source acceptance");
    EXPECT_TRUE(plan.source_layout_gate_bound == 1u, "source layout");
    EXPECT_TRUE(plan.fips_conformance_matrix_bound == 1u, "fips");
    EXPECT_TRUE(plan.sp800_227_usage_profile_bound == 1u, "usage");
    EXPECT_TRUE(plan.kat_manifest_bound == 1u, "kat");
    EXPECT_TRUE(plan.acvp_contracts_bound == 1u, "acvp");
    EXPECT_TRUE(plan.code_owner_review_bound == 1u, "owner");
    EXPECT_TRUE(plan.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(plan.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(plan.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(plan.per_file_digest_row_schema_recorded == 1u, "schema");
    EXPECT_TRUE(plan.per_file_trace_columns_recorded == 1u, "trace columns");
    EXPECT_TRUE(plan.per_file_review_columns_recorded == 1u, "review columns");
    EXPECT_TRUE(plan.source_files_created == 0u, "source files");
    EXPECT_TRUE(plan.implementation_file_digest_rows_recorded == 0u, "implementation rows");
    EXPECT_TRUE(plan.test_file_digest_rows_recorded == 0u, "test rows");
    EXPECT_TRUE(plan.build_script_digest_rows_recorded == 0u, "build rows");
    EXPECT_TRUE(plan.digest_receipt_reviewed == 0u, "receipt review");
    EXPECT_TRUE(plan.digest_replay_verified == 0u, "replay verified");
    EXPECT_TRUE(plan.file_digest_plan_accepted == 0u, "accepted");
    EXPECT_TRUE(plan.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(plan.shared_secret_emission_allowed == 0u, "shared secret");
    EXPECT_TRUE(plan.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(plan.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(plan.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(plan.required_digest_plan_items_total == 33u, "total");
    EXPECT_TRUE(plan.required_digest_plan_items_satisfied == 26u, "satisfied");
    EXPECT_TRUE(plan.error == LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_is_no_effect(&plan) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_allows_digest_row_acceptance(
            &plan) == 0,
        "allows digest row acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
            &plan,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION FILE DIGEST PLAN") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "implementation_file_digest_plan_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "digest_algorithm=SHA-256") != 0, "algorithm report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_digest_row_schema_recorded=1") != 0,
        "schema report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_file_digest_rows_recorded=0") != 0,
        "digest rows report");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_emission_allowed=0") != 0,
        "shared secret report");
    EXPECT_TRUE(
        strstr(rendered, "required_digest_plan_items_total=33") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-implementation-file-digest-plan-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_file_digest_plan_t plan;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_allows_digest_row_acceptance(
            0) == 0,
        "null digest row acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(&plan) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
            &plan,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report plan");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
            &plan,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (implementation_file_digest_plan_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem implementation file digest plan invariants: ok\n");
    return 0;
}
