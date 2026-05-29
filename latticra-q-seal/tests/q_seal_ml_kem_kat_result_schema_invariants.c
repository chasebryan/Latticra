#include "latticra/q_seal_ml_kem_kat_result_schema.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int kat_result_schema_is_fail_closed(void) {
    latticra_q_seal_ml_kem_kat_result_schema_t schema;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_prepare(&schema) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(schema.kat_result_schema_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(schema.result_schema_profile, "latticra-q-seal-ml-kem-kat-result-schema/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(schema.formal_title, "Latticra Q-Seal ML-KEM KAT Result Schema") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(schema.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(schema.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(schema.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(schema.kat_manifest_bound == 1u, "kat manifest");
    EXPECT_TRUE(schema.kat_runner_contract_bound == 1u, "kat runner");
    EXPECT_TRUE(schema.kat_result_row_fixture_bound == 1u, "row fixture");
    EXPECT_TRUE(schema.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(schema.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(schema.vector_schema_bound == 1u, "vector schema");
    EXPECT_TRUE(schema.vector_fixture_lock_bound == 1u, "fixture lock");
    EXPECT_TRUE(schema.vector_fixture_digest_ledger_bound == 1u, "digest ledger");
    EXPECT_TRUE(schema.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(schema.provider_differential_bound == 1u, "provider");
    EXPECT_TRUE(schema.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(schema.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(schema.deterministic_result_ordering_required == 1u, "ordering");
    EXPECT_TRUE(schema.result_envelope_policy_recorded == 1u, "envelope");
    EXPECT_TRUE(schema.fixture_digest_reference_required == 1u, "fixture digest");
    EXPECT_TRUE(schema.vector_family_reference_required == 1u, "vector family");
    EXPECT_TRUE(schema.parameter_set_field_required == 1u, "parameter field");
    EXPECT_TRUE(schema.operation_family_field_required == 1u, "operation field");
    EXPECT_TRUE(schema.test_type_field_required == 1u, "test type");
    EXPECT_TRUE(schema.tgid_tcid_mapping_required == 1u, "tgid tcid");
    EXPECT_TRUE(schema.expected_result_field_required == 1u, "expected");
    EXPECT_TRUE(schema.observed_result_field_required == 1u, "observed");
    EXPECT_TRUE(schema.pass_fail_field_required == 1u, "pass fail");
    EXPECT_TRUE(schema.failure_reason_field_required == 1u, "failure");
    EXPECT_TRUE(schema.implicit_rejection_result_required == 1u, "implicit");
    EXPECT_TRUE(schema.provider_differential_field_required == 1u, "differential");
    EXPECT_TRUE(schema.transcript_digest_field_required == 1u, "transcript");
    EXPECT_TRUE(schema.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(schema.no_network_submission_required == 1u, "network");
    EXPECT_TRUE(schema.no_dynamic_provider_loading_required == 1u, "provider loading");
    EXPECT_TRUE(schema.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(schema.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(schema.result_schema_reviewed == 0u, "reviewed");
    EXPECT_TRUE(schema.fixture_bundle_digest_bound == 0u, "fixture bound");
    EXPECT_TRUE(schema.result_row_fixture_recorded == 0u, "row fixture");
    EXPECT_TRUE(schema.positive_result_rows_recorded == 0u, "positive rows");
    EXPECT_TRUE(schema.negative_result_rows_recorded == 0u, "negative rows");
    EXPECT_TRUE(schema.malformed_result_rows_recorded == 0u, "malformed rows");
    EXPECT_TRUE(schema.implicit_rejection_rows_recorded == 0u, "implicit rows");
    EXPECT_TRUE(schema.provider_differential_rows_recorded == 0u, "provider rows");
    EXPECT_TRUE(schema.ci_kat_replay_transcript_bound == 0u, "ci transcript");
    EXPECT_TRUE(schema.kat_runner_execution_recorded == 0u, "runner execution");
    EXPECT_TRUE(schema.acvp_response_generation_evidence_recorded == 0u, "response evidence");
    EXPECT_TRUE(schema.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(schema.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(schema.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(schema.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(schema.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(schema.required_kat_result_schema_items_total == 44u, "total");
    EXPECT_TRUE(schema.required_kat_result_schema_items_satisfied == 33u, "satisfied");
    EXPECT_TRUE(
        schema.error == LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_is_no_effect(&schema) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_allows_result_recording(&schema) == 0,
        "allows result");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_report(
            &schema,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_schema_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "kat_runner_contract_bound=1") != 0,
        "runner report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_row_fixture_bound=1") != 0,
        "row fixture report");
    EXPECT_TRUE(
        strstr(rendered, "result_schema_reviewed=0") != 0,
        "review report");
    EXPECT_TRUE(
        strstr(rendered, "required_kat_result_schema_items_total=44") != 0,
        "total report");
    return 0;
}

static int kat_result_schema_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_kat_result_schema_t schema;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_allows_result_recording(0) == 0,
        "null result");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_prepare(&schema) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_report(&schema, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_result_schema_report(&schema, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (kat_result_schema_is_fail_closed() != 0) {
        return 1;
    }
    if (kat_result_schema_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem kat result schema invariants: ok\n");
    return 0;
}
