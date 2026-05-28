#include "latticra/q_seal_ml_kem_kat_result_row_fixture.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int kat_result_row_fixture_is_fail_closed(void) {
    latticra_q_seal_ml_kem_kat_result_row_fixture_t fixture;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(fixture.kat_result_row_fixture_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            fixture.row_fixture_profile,
            "latticra-q-seal-ml-kem-kat-result-row-fixture/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(fixture.formal_title, "Latticra Q-Seal ML-KEM KAT Result Row Fixture") ==
            0,
        "title");
    EXPECT_TRUE(
        strcmp(fixture.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") ==
            0,
        "standards");
    EXPECT_TRUE(fixture.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(fixture.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(fixture.kat_manifest_bound == 1u, "kat manifest");
    EXPECT_TRUE(fixture.kat_runner_contract_bound == 1u, "runner");
    EXPECT_TRUE(fixture.kat_result_schema_bound == 1u, "schema");
    EXPECT_TRUE(fixture.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(fixture.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(fixture.vector_schema_bound == 1u, "vector schema");
    EXPECT_TRUE(fixture.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(fixture.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(fixture.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(fixture.provider_differential_bound == 1u, "provider");
    EXPECT_TRUE(fixture.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(fixture.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(fixture.result_row_fixture_policy_recorded == 1u, "policy");
    EXPECT_TRUE(fixture.row_id_policy_recorded == 1u, "row id");
    EXPECT_TRUE(fixture.fixture_digest_reference_required == 1u, "fixture digest");
    EXPECT_TRUE(fixture.vector_family_reference_required == 1u, "vector family");
    EXPECT_TRUE(fixture.parameter_set_field_required == 1u, "parameter");
    EXPECT_TRUE(fixture.operation_family_field_required == 1u, "operation");
    EXPECT_TRUE(fixture.test_type_field_required == 1u, "test type");
    EXPECT_TRUE(fixture.tgid_tcid_mapping_required == 1u, "ids");
    EXPECT_TRUE(fixture.expected_result_field_required == 1u, "expected");
    EXPECT_TRUE(fixture.observed_result_field_required == 1u, "observed");
    EXPECT_TRUE(fixture.pass_fail_field_required == 1u, "pass fail");
    EXPECT_TRUE(fixture.failure_reason_field_required == 1u, "failure");
    EXPECT_TRUE(fixture.implicit_rejection_row_policy_recorded == 1u, "implicit");
    EXPECT_TRUE(fixture.provider_differential_row_policy_recorded == 1u, "differential");
    EXPECT_TRUE(fixture.transcript_digest_reference_required == 1u, "transcript");
    EXPECT_TRUE(fixture.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(fixture.deterministic_ordering_required == 1u, "ordering");
    EXPECT_TRUE(fixture.no_network_submission_required == 1u, "network");
    EXPECT_TRUE(fixture.no_dynamic_provider_loading_required == 1u, "provider loading");
    EXPECT_TRUE(fixture.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(fixture.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(fixture.row_fixture_reviewed == 0u, "reviewed");
    EXPECT_TRUE(fixture.fixture_bundle_digest_bound == 0u, "bundle digest");
    EXPECT_TRUE(fixture.positive_result_row_fixture_recorded == 0u, "positive row");
    EXPECT_TRUE(fixture.negative_result_row_fixture_recorded == 0u, "negative row");
    EXPECT_TRUE(fixture.malformed_result_row_fixture_recorded == 0u, "malformed row");
    EXPECT_TRUE(fixture.implicit_rejection_row_fixture_recorded == 0u, "implicit row");
    EXPECT_TRUE(fixture.provider_differential_row_fixture_recorded == 0u, "provider row");
    EXPECT_TRUE(fixture.ci_kat_replay_transcript_bound == 0u, "ci transcript");
    EXPECT_TRUE(fixture.kat_runner_execution_recorded == 0u, "runner execution");
    EXPECT_TRUE(
        fixture.acvp_response_generation_evidence_recorded == 0u,
        "response evidence");
    EXPECT_TRUE(fixture.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(fixture.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(fixture.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(fixture.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(fixture.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(fixture.required_kat_result_row_fixture_items_total == 44u, "total");
    EXPECT_TRUE(fixture.required_kat_result_row_fixture_items_satisfied == 34u, "satisfied");
    EXPECT_TRUE(
        fixture.error == LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_is_no_effect(&fixture) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_allows_result_rows(&fixture) == 0,
        "allows rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_report(
            &fixture,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_row_fixture_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_schema_bound=1") != 0,
        "schema report");
    EXPECT_TRUE(
        strstr(rendered, "positive_result_row_fixture_recorded=0") != 0,
        "row report");
    EXPECT_TRUE(
        strstr(rendered, "required_kat_result_row_fixture_items_total=44") != 0,
        "total report");
    return 0;
}

static int kat_result_row_fixture_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_kat_result_row_fixture_t fixture;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_allows_result_rows(0) == 0,
        "null rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_report(&fixture, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_row_fixture_report(
            &fixture,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (kat_result_row_fixture_is_fail_closed() != 0) {
        return 1;
    }
    if (kat_result_row_fixture_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem kat result row fixture invariants: ok\n");
    return 0;
}
