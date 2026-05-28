#include "latticra/q_seal_ml_kem_acvp_parser_contract.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_parser_contract_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_parser_contract_t contract;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(contract.acvp_parser_contract_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(contract.parser_profile, "latticra-q-seal-ml-kem-acvp-parser-contract/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(contract.formal_title, "Latticra Q-Seal ML-KEM ACVP Parser Contract") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(contract.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(contract.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(contract.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(contract.acvp_intake_bound == 1u, "intake");
    EXPECT_TRUE(contract.acvp_capability_matrix_bound == 1u, "matrix");
    EXPECT_TRUE(contract.acvp_fixture_row_plan_bound == 1u, "row plan");
    EXPECT_TRUE(contract.acvp_fixture_digest_row_template_bound == 1u, "row template");
    EXPECT_TRUE(contract.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(contract.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(contract.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(contract.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(contract.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(contract.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(contract.vector_set_fields_policy_recorded == 1u, "vector set");
    EXPECT_TRUE(contract.test_group_fields_policy_recorded == 1u, "groups");
    EXPECT_TRUE(contract.test_case_fields_policy_recorded == 1u, "cases");
    EXPECT_TRUE(contract.response_fields_policy_recorded == 1u, "responses");
    EXPECT_TRUE(contract.parameter_set_allowlist_required == 1u, "parameter allowlist");
    EXPECT_TRUE(contract.mode_allowlist_required == 1u, "mode allowlist");
    EXPECT_TRUE(contract.test_type_allowlist_required == 1u, "test type allowlist");
    EXPECT_TRUE(contract.function_allowlist_required == 1u, "function allowlist");
    EXPECT_TRUE(contract.hex_string_decoder_policy_recorded == 1u, "hex");
    EXPECT_TRUE(contract.integer_range_policy_recorded == 1u, "range");
    EXPECT_TRUE(contract.max_input_size_policy_recorded == 1u, "size");
    EXPECT_TRUE(contract.max_nesting_depth_policy_recorded == 1u, "depth");
    EXPECT_TRUE(contract.duplicate_key_rejection_required == 1u, "duplicate");
    EXPECT_TRUE(contract.unknown_field_rejection_policy_recorded == 1u, "unknown");
    EXPECT_TRUE(contract.malformed_json_rejection_required == 1u, "malformed");
    EXPECT_TRUE(contract.canonical_output_mapping_required == 1u, "canonical");
    EXPECT_TRUE(contract.no_dynamic_code_loading_required == 1u, "dynamic");
    EXPECT_TRUE(contract.no_network_fetch_required == 1u, "network");
    EXPECT_TRUE(contract.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(contract.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(contract.parser_implementation_present == 0u, "parser");
    EXPECT_TRUE(contract.parser_negative_tests_recorded == 0u, "negative tests");
    EXPECT_TRUE(contract.parser_fuzzing_recorded == 0u, "fuzzing");
    EXPECT_TRUE(contract.parser_schema_reviewed == 0u, "schema review");
    EXPECT_TRUE(contract.parser_security_reviewed == 0u, "security review");
    EXPECT_TRUE(contract.parser_ci_replay_recorded == 0u, "ci replay");
    EXPECT_TRUE(contract.fixture_digest_rows_recorded == 0u, "rows");
    EXPECT_TRUE(contract.fixture_import_reviewed == 0u, "import review");
    EXPECT_TRUE(contract.parser_output_accepted == 0u, "accepted");
    EXPECT_TRUE(contract.vector_execution_allowed == 0u, "vector");
    EXPECT_TRUE(contract.response_json_generation_enabled == 0u, "response");
    EXPECT_TRUE(contract.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(contract.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(contract.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(contract.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(contract.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(contract.required_parser_contract_items_total == 40u, "total");
    EXPECT_TRUE(contract.required_parser_contract_items_satisfied == 31u, "satisfied");
    EXPECT_TRUE(
        contract.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_is_no_effect(&contract) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_allows_vector_parser(&contract) == 0,
        "allows parser");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_report(
            &contract,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "acvp_parser_contract_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "malformed_json_rejection_required=1") != 0, "malformed report");
    EXPECT_TRUE(strstr(rendered, "parser_implementation_present=0") != 0, "parser report");
    EXPECT_TRUE(strstr(rendered, "parser_output_accepted=0") != 0, "accepted report");
    EXPECT_TRUE(
        strstr(rendered, "required_parser_contract_items_total=40") != 0,
        "total report");
    return 0;
}

static int acvp_parser_contract_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_parser_contract_t contract;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_allows_vector_parser(0) == 0,
        "null parser");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_report(&contract, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_parser_contract_report(
            &contract,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_parser_contract_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_parser_contract_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp parser contract invariants: ok\n");
    return 0;
}
