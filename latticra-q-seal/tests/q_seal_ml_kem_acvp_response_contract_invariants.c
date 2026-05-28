#include "latticra/q_seal_ml_kem_acvp_response_contract.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_response_contract_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_response_contract_t contract;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(contract.acvp_response_contract_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(contract.response_profile, "latticra-q-seal-ml-kem-acvp-response-contract/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(contract.formal_title, "Latticra Q-Seal ML-KEM ACVP Response Contract") == 0,
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
    EXPECT_TRUE(contract.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(contract.acvp_response_fixture_bound == 1u, "response fixture");
    EXPECT_TRUE(contract.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(contract.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(contract.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(contract.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(contract.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(contract.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(contract.response_envelope_policy_recorded == 1u, "envelope");
    EXPECT_TRUE(contract.keygen_response_fields_policy_recorded == 1u, "keygen");
    EXPECT_TRUE(contract.encapsulation_response_fields_policy_recorded == 1u, "encapsulation");
    EXPECT_TRUE(contract.decapsulation_response_fields_policy_recorded == 1u, "decapsulation");
    EXPECT_TRUE(contract.key_check_response_fields_policy_recorded == 1u, "key check");
    EXPECT_TRUE(contract.tcid_tgid_mapping_required == 1u, "tcid tgid");
    EXPECT_TRUE(contract.acv_version_echo_policy_recorded == 1u, "acv version");
    EXPECT_TRUE(contract.vsid_echo_policy_recorded == 1u, "vsid");
    EXPECT_TRUE(contract.parameter_set_crosscheck_required == 1u, "parameter");
    EXPECT_TRUE(contract.function_crosscheck_required == 1u, "function");
    EXPECT_TRUE(contract.hex_output_canonicalization_required == 1u, "hex");
    EXPECT_TRUE(contract.boolean_output_policy_recorded == 1u, "boolean");
    EXPECT_TRUE(contract.deterministic_ordering_required == 1u, "ordering");
    EXPECT_TRUE(contract.duplicate_response_rejection_required == 1u, "duplicate");
    EXPECT_TRUE(contract.unknown_response_field_rejection_required == 1u, "unknown");
    EXPECT_TRUE(contract.response_size_limit_recorded == 1u, "size");
    EXPECT_TRUE(contract.no_dynamic_code_loading_required == 1u, "dynamic");
    EXPECT_TRUE(contract.no_network_submission_required == 1u, "network");
    EXPECT_TRUE(contract.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(contract.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(contract.response_generator_implementation_present == 0u, "generator");
    EXPECT_TRUE(contract.response_negative_tests_recorded == 0u, "negative tests");
    EXPECT_TRUE(contract.response_schema_reviewed == 0u, "schema review");
    EXPECT_TRUE(contract.response_security_reviewed == 0u, "security review");
    EXPECT_TRUE(contract.response_ci_replay_recorded == 0u, "ci replay");
    EXPECT_TRUE(contract.parser_output_accepted == 0u, "parser output");
    EXPECT_TRUE(contract.vector_execution_evidence_recorded == 0u, "vector evidence");
    EXPECT_TRUE(contract.response_json_generation_enabled == 0u, "generation");
    EXPECT_TRUE(contract.response_output_accepted == 0u, "accepted");
    EXPECT_TRUE(contract.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(contract.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(contract.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(contract.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(contract.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(contract.required_response_contract_items_total == 42u, "total");
    EXPECT_TRUE(contract.required_response_contract_items_satisfied == 33u, "satisfied");
    EXPECT_TRUE(
        contract.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_is_no_effect(&contract) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_allows_response_generation(
            &contract) == 0,
        "allows response");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_report(
            &contract,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "acvp_response_contract_present=1") != 0, "present report");
    EXPECT_TRUE(
        strstr(rendered, "keygen_response_fields_policy_recorded=1") != 0,
        "keygen report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_response_fixture_bound=1") != 0,
        "fixture report");
    EXPECT_TRUE(
        strstr(rendered, "response_json_generation_enabled=0") != 0,
        "generation report");
    EXPECT_TRUE(
        strstr(rendered, "required_response_contract_items_total=42") != 0,
        "total report");
    return 0;
}

static int acvp_response_contract_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_response_contract_t contract;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_allows_response_generation(0) == 0,
        "null response");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_report(&contract, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_contract_report(
            &contract,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_response_contract_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_response_contract_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp response contract invariants: ok\n");
    return 0;
}
