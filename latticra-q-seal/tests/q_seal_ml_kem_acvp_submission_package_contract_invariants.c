#include "latticra/q_seal_ml_kem_acvp_submission_package_contract.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_submission_package_contract_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_submission_package_contract_t contract;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(
            &contract) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(contract.acvp_submission_package_contract_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            contract.submission_package_profile,
            "latticra-q-seal-ml-kem-acvp-submission-package-contract/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            contract.formal_title,
            "Latticra Q-Seal ML-KEM ACVP Submission Package Contract") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(contract.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(contract.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(contract.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(contract.acvp_intake_bound == 1u, "intake");
    EXPECT_TRUE(contract.acvp_capability_matrix_bound == 1u, "matrix");
    EXPECT_TRUE(contract.acvp_fixture_row_plan_bound == 1u, "row plan");
    EXPECT_TRUE(contract.acvp_fixture_digest_row_template_bound == 1u, "digest row");
    EXPECT_TRUE(contract.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(contract.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(contract.acvp_response_fixture_bound == 1u, "response fixture");
    EXPECT_TRUE(contract.kat_result_schema_bound == 1u, "kat schema");
    EXPECT_TRUE(contract.kat_result_row_fixture_bound == 1u, "kat row");
    EXPECT_TRUE(contract.vector_schema_bound == 1u, "vector schema");
    EXPECT_TRUE(contract.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(contract.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(contract.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(contract.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(contract.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(contract.submission_package_policy_recorded == 1u, "policy");
    EXPECT_TRUE(contract.offline_package_manifest_required == 1u, "manifest");
    EXPECT_TRUE(contract.algorithm_registration_required == 1u, "registration");
    EXPECT_TRUE(contract.acvp_session_metadata_required == 1u, "session");
    EXPECT_TRUE(contract.vsid_tgid_tcid_traceability_required == 1u, "ids");
    EXPECT_TRUE(contract.request_bundle_digest_required == 1u, "request digest");
    EXPECT_TRUE(contract.response_bundle_digest_required == 1u, "response digest");
    EXPECT_TRUE(contract.canonical_response_json_required == 1u, "canonical json");
    EXPECT_TRUE(contract.local_replay_transcript_required == 1u, "replay");
    EXPECT_TRUE(contract.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(contract.no_network_submission_required == 1u, "network policy");
    EXPECT_TRUE(contract.no_dynamic_code_loading_required == 1u, "dynamic");
    EXPECT_TRUE(contract.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(contract.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(contract.submission_package_reviewed == 0u, "reviewed");
    EXPECT_TRUE(contract.request_bundle_digest_bound == 0u, "request bound");
    EXPECT_TRUE(contract.response_bundle_digest_bound == 0u, "response bound");
    EXPECT_TRUE(contract.vector_execution_evidence_recorded == 0u, "vector evidence");
    EXPECT_TRUE(contract.response_output_accepted == 0u, "response output");
    EXPECT_TRUE(contract.local_replay_transcript_recorded == 0u, "transcript");
    EXPECT_TRUE(contract.acvp_client_boundary_reviewed == 0u, "client boundary");
    EXPECT_TRUE(contract.submission_receipt_recorded == 0u, "receipt");
    EXPECT_TRUE(contract.validation_server_acceptance_recorded == 0u, "server");
    EXPECT_TRUE(contract.acvp_submission_package_accepted == 0u, "package");
    EXPECT_TRUE(contract.acvp_response_acceptance_recorded == 0u, "acceptance");
    EXPECT_TRUE(contract.response_json_generation_enabled == 0u, "generation");
    EXPECT_TRUE(contract.network_session_enabled == 0u, "network");
    EXPECT_TRUE(contract.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(contract.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(contract.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(contract.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(contract.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(contract.required_submission_package_items_total == 41u, "total");
    EXPECT_TRUE(contract.required_submission_package_items_satisfied == 30u, "satisfied");
    EXPECT_TRUE(
        contract.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_is_no_effect(
            &contract) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_allows_package_acceptance(
            &contract) == 0,
        "allows acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
            &contract,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_submission_package_contract_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_response_fixture_bound=1") != 0,
        "fixture report");
    EXPECT_TRUE(
        strstr(rendered, "network_session_enabled=0") != 0,
        "network report");
    EXPECT_TRUE(
        strstr(rendered, "required_submission_package_items_total=41") != 0,
        "total report");
    return 0;
}

static int acvp_submission_package_contract_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_submission_package_contract_t contract;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_allows_package_acceptance(
            0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(
            &contract) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
            &contract,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
            &contract,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_submission_package_contract_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_submission_package_contract_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp submission package contract invariants: ok\n");
    return 0;
}
