#include "latticra/q_seal_readiness.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int readiness_profile_aggregates_fail_closed_state(void) {
    latticra_q_seal_readiness_t readiness;
    char rendered[LATTICRA_Q_SEAL_READINESS_REPORT_MAX];

    EXPECT_TRUE(latticra_q_seal_readiness_prepare(&readiness) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(strcmp(readiness.readiness_profile, "latticra-q-seal-readiness/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(readiness.formal_title, "Latticra Q-Seal Readiness Profile") == 0, "title");
    EXPECT_TRUE(strcmp(readiness.subsystem_path, "latticra-q-seal") == 0, "path");
    EXPECT_TRUE(
        strcmp(readiness.standards_basis, "NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(strcmp(readiness.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(
        strcmp(readiness.readiness_state, "design-frame-ready-runtime-crypto-blocked") == 0,
        "state");
    EXPECT_TRUE(readiness.readiness_profile_present == 1u, "present");
    EXPECT_TRUE(readiness.foundation_present == 1u, "foundation");
    EXPECT_TRUE(readiness.ml_kem_parameters_present == 1u, "parameters");
    EXPECT_TRUE(readiness.ml_kem_512_parameters_present == 1u, "512");
    EXPECT_TRUE(readiness.ml_kem_768_parameters_present == 1u, "768");
    EXPECT_TRUE(readiness.ml_kem_1024_parameters_present == 1u, "1024");
    EXPECT_TRUE(readiness.evidence_gate_present == 1u, "evidence");
    EXPECT_TRUE(readiness.fips_conformance_matrix_present == 1u, "conformance");
    EXPECT_TRUE(readiness.sp800_227_usage_profile_present == 1u, "usage profile");
    EXPECT_TRUE(readiness.kat_manifest_present == 1u, "kat manifest");
    EXPECT_TRUE(readiness.kat_runner_contract_present == 1u, "kat runner");
    EXPECT_TRUE(readiness.replay_transcript_gate_present == 1u, "replay transcript");
    EXPECT_TRUE(readiness.kat_result_schema_present == 1u, "kat result schema");
    EXPECT_TRUE(readiness.kat_result_row_fixture_present == 1u, "kat result rows");
    EXPECT_TRUE(readiness.acvp_intake_present == 1u, "acvp");
    EXPECT_TRUE(readiness.acvp_capability_matrix_present == 1u, "acvp matrix");
    EXPECT_TRUE(readiness.acvp_fixture_row_plan_present == 1u, "acvp rows");
    EXPECT_TRUE(
        readiness.acvp_fixture_digest_row_template_present == 1u,
        "acvp digest row template");
    EXPECT_TRUE(readiness.acvp_parser_contract_present == 1u, "acvp parser");
    EXPECT_TRUE(readiness.acvp_response_contract_present == 1u, "acvp response");
    EXPECT_TRUE(readiness.acvp_response_fixture_present == 1u, "acvp response fixture");
    EXPECT_TRUE(
        readiness.acvp_submission_package_contract_present == 1u,
        "acvp submission package");
    EXPECT_TRUE(readiness.acvp_verdict_receipt_gate_present == 1u, "acvp verdict receipt");
    EXPECT_TRUE(readiness.vector_schema_present == 1u, "vector schema");
    EXPECT_TRUE(readiness.vector_source_intake_present == 1u, "vector source");
    EXPECT_TRUE(readiness.vector_fixture_lock_present == 1u, "fixture lock");
    EXPECT_TRUE(readiness.vector_fixture_digest_ledger_present == 1u, "digest ledger");
    EXPECT_TRUE(readiness.negative_test_evidence_present == 1u, "negative test");
    EXPECT_TRUE(readiness.memory_safety_evidence_present == 1u, "memory safety");
    EXPECT_TRUE(readiness.api_misuse_resistance_present == 1u, "api misuse");
    EXPECT_TRUE(readiness.source_digest_manifest_present == 1u, "source digest");
    EXPECT_TRUE(readiness.source_digest_receipt_present == 1u, "source receipt");
    EXPECT_TRUE(readiness.source_digest_verification_present == 1u, "source verification");
    EXPECT_TRUE(readiness.receipt_replay_results_present == 1u, "replay results");
    EXPECT_TRUE(readiness.code_owner_review_present == 1u, "code owner");
    EXPECT_TRUE(readiness.review_disposition_ledger_present == 1u, "disposition");
    EXPECT_TRUE(readiness.reviewer_identity_fixture_present == 1u, "identity");
    EXPECT_TRUE(readiness.reviewer_role_mapping_present == 1u, "role mapping");
    EXPECT_TRUE(readiness.ci_promotion_evidence_present == 1u, "ci promotion");
    EXPECT_TRUE(readiness.validation_claim_gate_present == 1u, "validation claim");
    EXPECT_TRUE(readiness.module_boundary_gate_present == 1u, "module boundary");
    EXPECT_TRUE(readiness.constant_time_review_present == 1u, "constant time");
    EXPECT_TRUE(readiness.randomness_source_contract_present == 1u, "randomness");
    EXPECT_TRUE(readiness.zeroization_evidence_present == 1u, "zeroization");
    EXPECT_TRUE(readiness.side_channel_review_present == 1u, "side channel");
    EXPECT_TRUE(readiness.provider_differential_present == 1u, "provider");
    EXPECT_TRUE(readiness.implementation_binding_manifest_present == 1u, "binding");
    EXPECT_TRUE(readiness.source_layout_gate_present == 1u, "source layout");
    EXPECT_TRUE(readiness.implementation_file_digest_plan_present == 1u, "file digest plan");
    EXPECT_TRUE(readiness.clean_room_author_attestation_gate_present == 1u, "author attestation");
    EXPECT_TRUE(readiness.per_file_standards_trace_gate_present == 1u, "standards trace");
    EXPECT_TRUE(readiness.per_file_test_trace_gate_present == 1u, "test trace");
    EXPECT_TRUE(readiness.implementation_traceability_matrix_present == 1u, "traceability");
    EXPECT_TRUE(readiness.primitive_source_acceptance_gate_present == 1u, "source acceptance");
    EXPECT_TRUE(readiness.implementation_frame_present == 1u, "implementation");
    EXPECT_TRUE(readiness.secret_state_contract_present == 1u, "secret state");
    EXPECT_TRUE(readiness.clean_room_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(readiness.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(readiness.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(readiness.provider_runtime_used == 0u, "provider runtime");
    EXPECT_TRUE(readiness.components_total == 52u, "components total");
    EXPECT_TRUE(readiness.components_present == 52u, "components present");
    EXPECT_TRUE(readiness.runtime_blockers_total == 49u, "runtime blockers");
    EXPECT_TRUE(readiness.required_readiness_items_total == 1487u, "readiness total");
    EXPECT_TRUE(readiness.required_readiness_items_satisfied == 1029u, "readiness satisfied");
    EXPECT_TRUE(readiness.design_frame_integration_ready == 1u, "design frame");
    EXPECT_TRUE(readiness.runtime_crypto_ready == 0u, "runtime crypto");
    EXPECT_TRUE(readiness.operations_enabled == 0u, "operations");
    EXPECT_TRUE(readiness.key_generation_enabled == 0u, "keygen");
    EXPECT_TRUE(readiness.encapsulation_enabled == 0u, "encaps");
    EXPECT_TRUE(readiness.decapsulation_enabled == 0u, "decaps");
    EXPECT_TRUE(readiness.shared_secret_emitted == 0u, "shared secret");
    EXPECT_TRUE(readiness.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(readiness.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(readiness.runtime_authority_granted == 0u, "authority");
    EXPECT_TRUE(readiness.error == LATTICRA_Q_SEAL_READINESS_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_readiness_is_design_frame_ready(&readiness) == 1,
        "design ready function");
    EXPECT_TRUE(
        latticra_q_seal_readiness_allows_runtime_crypto(&readiness) == 0,
        "runtime function");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL READINESS PROFILE") != 0, "header");
    EXPECT_TRUE(strstr(rendered, "components_present=52") != 0, "components report");
    EXPECT_TRUE(
        strstr(rendered, "fips_conformance_matrix_present=1") != 0,
        "conformance report");
    EXPECT_TRUE(
        strstr(rendered, "sp800_227_usage_profile_present=1") != 0,
        "usage profile report");
    EXPECT_TRUE(strstr(rendered, "kat_manifest_present=1") != 0, "kat report");
    EXPECT_TRUE(strstr(rendered, "kat_runner_contract_present=1") != 0, "runner report");
    EXPECT_TRUE(
        strstr(rendered, "replay_transcript_gate_present=1") != 0,
        "transcript gate report");
    EXPECT_TRUE(strstr(rendered, "kat_result_schema_present=1") != 0, "schema report");
    EXPECT_TRUE(
        strstr(rendered, "kat_result_row_fixture_present=1") != 0,
        "row fixture report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_capability_matrix_present=1") != 0,
        "acvp matrix report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_row_plan_present=1") != 0,
        "acvp rows report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_fixture_digest_row_template_present=1") != 0,
        "acvp digest row template report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_parser_contract_present=1") != 0,
        "acvp parser report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_response_contract_present=1") != 0,
        "acvp response report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_response_fixture_present=1") != 0,
        "acvp response fixture report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_submission_package_contract_present=1") != 0,
        "acvp submission package report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_verdict_receipt_gate_present=1") != 0,
        "acvp verdict receipt report");
    EXPECT_TRUE(
        strstr(rendered, "vector_fixture_lock_present=1") != 0,
        "fixture lock report");
    EXPECT_TRUE(
        strstr(rendered, "vector_fixture_digest_ledger_present=1") != 0,
        "digest ledger report");
    EXPECT_TRUE(strstr(rendered, "negative_test_evidence_present=1") != 0, "negative report");
    EXPECT_TRUE(strstr(rendered, "memory_safety_evidence_present=1") != 0, "memory report");
    EXPECT_TRUE(strstr(rendered, "api_misuse_resistance_present=1") != 0, "api report");
    EXPECT_TRUE(strstr(rendered, "source_digest_manifest_present=1") != 0, "digest report");
    EXPECT_TRUE(strstr(rendered, "source_digest_receipt_present=1") != 0, "receipt report");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_verification_present=1") != 0,
        "verification report");
    EXPECT_TRUE(
        strstr(rendered, "receipt_replay_results_present=1") != 0,
        "replay report");
    EXPECT_TRUE(strstr(rendered, "code_owner_review_present=1") != 0, "owner report");
    EXPECT_TRUE(
        strstr(rendered, "review_disposition_ledger_present=1") != 0,
        "disposition report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_identity_fixture_present=1") != 0,
        "identity report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_role_mapping_present=1") != 0,
        "role report");
    EXPECT_TRUE(strstr(rendered, "ci_promotion_evidence_present=1") != 0, "ci report");
    EXPECT_TRUE(
        strstr(rendered, "validation_claim_gate_present=1") != 0,
        "validation claim report");
    EXPECT_TRUE(
        strstr(rendered, "module_boundary_gate_present=1") != 0,
        "module boundary report");
    EXPECT_TRUE(strstr(rendered, "constant_time_review_present=1") != 0, "constant report");
    EXPECT_TRUE(
        strstr(rendered, "randomness_source_contract_present=1") != 0,
        "randomness report");
    EXPECT_TRUE(strstr(rendered, "zeroization_evidence_present=1") != 0, "zeroization report");
    EXPECT_TRUE(strstr(rendered, "side_channel_review_present=1") != 0, "side-channel report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_binding_manifest_present=1") != 0,
        "binding report");
    EXPECT_TRUE(
        strstr(rendered, "source_layout_gate_present=1") != 0,
        "source layout report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_file_digest_plan_present=1") != 0,
        "file digest plan report");
    EXPECT_TRUE(
        strstr(rendered, "clean_room_author_attestation_gate_present=1") != 0,
        "author attestation report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_standards_trace_gate_present=1") != 0,
        "standards trace report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_test_trace_gate_present=1") != 0,
        "test trace report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_traceability_matrix_present=1") != 0,
        "traceability report");
    EXPECT_TRUE(
        strstr(rendered, "primitive_source_acceptance_gate_present=1") != 0,
        "source acceptance report");
    EXPECT_TRUE(strstr(rendered, "runtime_blockers_total=49") != 0, "blockers report");
    EXPECT_TRUE(
        strstr(rendered, "design_frame_integration_ready=1") != 0,
        "design report");
    EXPECT_TRUE(strstr(rendered, "runtime_crypto_ready=0") != 0, "runtime report");
    EXPECT_TRUE(strstr(rendered, "status=q-seal-readiness-profile-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_readiness_t readiness;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_readiness_prepare(0) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_readiness_is_design_frame_ready(0) == 0, "null design");
    EXPECT_TRUE(latticra_q_seal_readiness_allows_runtime_crypto(0) == 0, "null runtime");
    EXPECT_TRUE(latticra_q_seal_readiness_prepare(&readiness) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report readiness");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (readiness_profile_aggregates_fail_closed_state() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal readiness invariants: ok\n");
    return 0;
}
