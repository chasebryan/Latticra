#include "latticra/q_seal_ml_kem_acvp_response_fixture.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_response_fixture_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_response_fixture_t fixture;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(fixture.acvp_response_fixture_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            fixture.response_fixture_profile,
            "latticra-q-seal-ml-kem-acvp-response-fixture/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(fixture.formal_title, "Latticra Q-Seal ML-KEM ACVP Response Fixture") ==
            0,
        "title");
    EXPECT_TRUE(
        strcmp(fixture.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(fixture.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(fixture.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(fixture.acvp_intake_bound == 1u, "intake");
    EXPECT_TRUE(fixture.acvp_capability_matrix_bound == 1u, "matrix");
    EXPECT_TRUE(fixture.acvp_fixture_row_plan_bound == 1u, "row plan");
    EXPECT_TRUE(fixture.acvp_fixture_digest_row_template_bound == 1u, "digest row");
    EXPECT_TRUE(fixture.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(fixture.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(fixture.kat_result_schema_bound == 1u, "kat schema");
    EXPECT_TRUE(fixture.kat_result_row_fixture_bound == 1u, "kat row fixture");
    EXPECT_TRUE(fixture.vector_schema_bound == 1u, "vector schema");
    EXPECT_TRUE(fixture.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(fixture.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(fixture.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(fixture.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(fixture.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(fixture.response_fixture_policy_recorded == 1u, "fixture policy");
    EXPECT_TRUE(fixture.response_envelope_policy_recorded == 1u, "envelope");
    EXPECT_TRUE(fixture.acv_version_echo_required == 1u, "acv version");
    EXPECT_TRUE(fixture.vsid_echo_required == 1u, "vsid");
    EXPECT_TRUE(fixture.tgid_tcid_mapping_required == 1u, "ids");
    EXPECT_TRUE(fixture.deterministic_ordering_required == 1u, "ordering");
    EXPECT_TRUE(fixture.keygen_response_fixture_required == 1u, "keygen");
    EXPECT_TRUE(fixture.encapsulation_response_fixture_required == 1u, "encapsulation");
    EXPECT_TRUE(fixture.decapsulation_response_fixture_required == 1u, "decapsulation");
    EXPECT_TRUE(fixture.key_check_response_fixture_required == 1u, "key check");
    EXPECT_TRUE(fixture.canonical_hex_output_required == 1u, "hex");
    EXPECT_TRUE(fixture.boolean_output_policy_recorded == 1u, "boolean");
    EXPECT_TRUE(fixture.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(fixture.no_network_submission_required == 1u, "network");
    EXPECT_TRUE(fixture.no_dynamic_code_loading_required == 1u, "dynamic");
    EXPECT_TRUE(fixture.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(fixture.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(fixture.response_fixture_reviewed == 0u, "reviewed");
    EXPECT_TRUE(fixture.fixture_bundle_digest_bound == 0u, "digest");
    EXPECT_TRUE(fixture.parser_output_accepted == 0u, "parser output");
    EXPECT_TRUE(fixture.vector_execution_evidence_recorded == 0u, "vector evidence");
    EXPECT_TRUE(fixture.keygen_response_fixture_recorded == 0u, "keygen row");
    EXPECT_TRUE(fixture.encapsulation_response_fixture_recorded == 0u, "encap row");
    EXPECT_TRUE(fixture.decapsulation_response_fixture_recorded == 0u, "decap row");
    EXPECT_TRUE(fixture.key_check_response_fixture_recorded == 0u, "key check row");
    EXPECT_TRUE(fixture.negative_response_fixture_recorded == 0u, "negative row");
    EXPECT_TRUE(fixture.response_schema_reviewed == 0u, "schema review");
    EXPECT_TRUE(fixture.response_security_reviewed == 0u, "security review");
    EXPECT_TRUE(fixture.response_ci_replay_recorded == 0u, "ci replay");
    EXPECT_TRUE(fixture.response_output_accepted == 0u, "output");
    EXPECT_TRUE(
        fixture.acvp_response_generation_evidence_recorded == 0u,
        "generation evidence");
    EXPECT_TRUE(fixture.response_json_generation_enabled == 0u, "generation");
    EXPECT_TRUE(fixture.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(fixture.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(fixture.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(fixture.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(fixture.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(fixture.required_response_fixture_items_total == 46u, "total");
    EXPECT_TRUE(fixture.required_response_fixture_items_satisfied == 32u, "satisfied");
    EXPECT_TRUE(
        fixture.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_is_no_effect(&fixture) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_allows_response_output(&fixture) ==
            0,
        "allows output");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_report(
            &fixture,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_response_fixture_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_row_fixture_bound=1") != 0,
        "kat row report");
    EXPECT_TRUE(
        strstr(rendered, "keygen_response_fixture_required=1") != 0,
        "keygen report");
    EXPECT_TRUE(
        strstr(rendered, "response_output_accepted=0") != 0,
        "output report");
    EXPECT_TRUE(
        strstr(rendered, "required_response_fixture_items_total=46") != 0,
        "total report");
    return 0;
}

static int acvp_response_fixture_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_response_fixture_t fixture;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_allows_response_output(0) == 0,
        "null output");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_report(&fixture, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_response_fixture_report(
            &fixture,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_response_fixture_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_response_fixture_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp response fixture invariants: ok\n");
    return 0;
}
