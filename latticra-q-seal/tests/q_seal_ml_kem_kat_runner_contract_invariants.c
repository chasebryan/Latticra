#include "latticra/q_seal_ml_kem_kat_runner_contract.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int kat_runner_contract_is_fail_closed(void) {
    latticra_q_seal_ml_kem_kat_runner_contract_t contract;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(contract.kat_runner_contract_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(contract.runner_profile, "latticra-q-seal-ml-kem-kat-runner-contract/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(contract.formal_title, "Latticra Q-Seal ML-KEM KAT Runner Contract") ==
            0,
        "title");
    EXPECT_TRUE(
        strcmp(contract.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") ==
            0,
        "standards");
    EXPECT_TRUE(contract.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(contract.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(contract.kat_manifest_bound == 1u, "kat manifest");
    EXPECT_TRUE(contract.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(contract.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(contract.kat_result_schema_bound == 1u, "result schema bound");
    EXPECT_TRUE(contract.kat_result_row_fixture_bound == 1u, "row fixture bound");
    EXPECT_TRUE(contract.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(contract.vector_source_bound == 1u, "source");
    EXPECT_TRUE(contract.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(contract.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(contract.negative_test_evidence_bound == 1u, "negative evidence");
    EXPECT_TRUE(contract.provider_differential_bound == 1u, "provider");
    EXPECT_TRUE(contract.replay_transcript_gate_bound == 1u, "transcript gate");
    EXPECT_TRUE(contract.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(contract.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(contract.deterministic_replay_policy_recorded == 1u, "deterministic");
    EXPECT_TRUE(contract.offline_fixture_policy_recorded == 1u, "offline");
    EXPECT_TRUE(contract.no_network_execution_required == 1u, "network");
    EXPECT_TRUE(contract.no_dynamic_provider_loading_required == 1u, "provider loading");
    EXPECT_TRUE(contract.seed_material_handling_policy_recorded == 1u, "seed");
    EXPECT_TRUE(contract.positive_result_row_policy_recorded == 1u, "positive policy");
    EXPECT_TRUE(contract.negative_result_row_policy_recorded == 1u, "negative policy");
    EXPECT_TRUE(contract.malformed_result_row_policy_recorded == 1u, "malformed policy");
    EXPECT_TRUE(
        contract.implicit_rejection_result_policy_recorded == 1u,
        "implicit policy");
    EXPECT_TRUE(contract.parameter_set_coverage_required == 1u, "parameter coverage");
    EXPECT_TRUE(contract.operation_family_coverage_required == 1u, "operation coverage");
    EXPECT_TRUE(contract.transcript_retention_policy_recorded == 1u, "transcript");
    EXPECT_TRUE(contract.failure_triage_policy_recorded == 1u, "triage");
    EXPECT_TRUE(contract.no_embedded_vectors_policy_recorded == 1u, "no embedded");
    EXPECT_TRUE(contract.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(contract.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(contract.kat_runner_implementation_present == 0u, "runner impl");
    EXPECT_TRUE(contract.fixture_bundle_loaded == 0u, "fixture load");
    EXPECT_TRUE(contract.fixture_bundle_digest_verified == 0u, "fixture digest");
    EXPECT_TRUE(contract.fixture_bundle_license_reviewed == 0u, "license");
    EXPECT_TRUE(contract.fixture_bundle_storage_reviewed == 0u, "storage");
    EXPECT_TRUE(contract.parser_reviewed_for_runner == 0u, "parser review");
    EXPECT_TRUE(contract.result_schema_reviewed == 0u, "result schema");
    EXPECT_TRUE(contract.positive_result_rows_recorded == 0u, "positive rows");
    EXPECT_TRUE(contract.negative_result_rows_recorded == 0u, "negative rows");
    EXPECT_TRUE(contract.malformed_result_rows_recorded == 0u, "malformed rows");
    EXPECT_TRUE(contract.implicit_rejection_rows_recorded == 0u, "implicit rows");
    EXPECT_TRUE(contract.provider_differential_rows_recorded == 0u, "differential rows");
    EXPECT_TRUE(contract.ci_kat_replay_transcript_recorded == 0u, "ci replay");
    EXPECT_TRUE(contract.operation_implementation_present == 0u, "operation impl");
    EXPECT_TRUE(contract.kat_execution_enabled == 0u, "kat execution");
    EXPECT_TRUE(contract.acvp_response_generation_enabled == 0u, "response generation");
    EXPECT_TRUE(contract.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(contract.operation_execution_allowed == 0u, "operation execution");
    EXPECT_TRUE(contract.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(contract.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(contract.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(contract.required_kat_runner_contract_items_total == 47u, "total");
    EXPECT_TRUE(contract.required_kat_runner_contract_items_satisfied == 31u, "satisfied");
    EXPECT_TRUE(
        contract.error == LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_is_no_effect(&contract) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_allows_runner_execution(&contract) == 0,
        "allows execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_report(
            &contract,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "kat_runner_contract_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "kat_manifest_bound=1") != 0, "manifest report");
    EXPECT_TRUE(strstr(rendered, "kat_result_schema_bound=1") != 0, "schema report");
    EXPECT_TRUE(strstr(rendered, "kat_result_row_fixture_bound=1") != 0, "row report");
    EXPECT_TRUE(
        strstr(rendered, "replay_transcript_gate_bound=1") != 0,
        "transcript gate report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_bundle_loaded=0") != 0,
        "fixture report");
    EXPECT_TRUE(
        strstr(rendered, "kat_execution_enabled=0") != 0,
        "execution report");
    EXPECT_TRUE(
        strstr(rendered, "required_kat_runner_contract_items_total=47") != 0,
        "total report");
    return 0;
}

static int kat_runner_contract_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_kat_runner_contract_t contract;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_allows_runner_execution(0) == 0,
        "null execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_report(&contract, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_runner_contract_report(&contract, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (kat_runner_contract_is_fail_closed() != 0) {
        return 1;
    }
    if (kat_runner_contract_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem kat runner contract invariants: ok\n");
    return 0;
}
