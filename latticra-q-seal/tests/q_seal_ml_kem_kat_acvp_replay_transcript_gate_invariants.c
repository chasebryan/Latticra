#include "latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int replay_transcript_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.replay_transcript_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.transcript_profile,
            "latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            gate.formal_title,
            "Latticra Q-Seal ML-KEM KAT/ACVP Replay Transcript Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(gate.nist_acvp_ml_kem_bound == 1u, "acvp");
    EXPECT_TRUE(gate.ssdf_evidence_integrity_bound == 1u, "ssdf");
    EXPECT_TRUE(gate.kat_manifest_bound == 1u, "kat manifest");
    EXPECT_TRUE(gate.kat_runner_contract_bound == 1u, "runner");
    EXPECT_TRUE(gate.kat_result_schema_bound == 1u, "schema");
    EXPECT_TRUE(gate.kat_result_row_fixture_bound == 1u, "rows");
    EXPECT_TRUE(gate.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(gate.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(gate.acvp_submission_package_contract_bound == 1u, "submission");
    EXPECT_TRUE(gate.vector_fixture_digest_ledger_bound == 1u, "vector ledger");
    EXPECT_TRUE(gate.receipt_replay_results_bound == 1u, "receipt replay");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "review disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role mapping");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci promotion");
    EXPECT_TRUE(gate.provider_differential_bound == 1u, "provider differential");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(
        gate.deterministic_replay_transcript_schema_recorded == 1u,
        "transcript schema");
    EXPECT_TRUE(gate.transcript_digest_sha256_required == 1u, "digest");
    EXPECT_TRUE(gate.transcript_command_fingerprint_required == 1u, "command");
    EXPECT_TRUE(gate.fixture_digest_reference_required == 1u, "fixture digest");
    EXPECT_TRUE(gate.implementation_digest_reference_required == 1u, "implementation digest");
    EXPECT_TRUE(gate.parameter_set_coverage_required == 1u, "parameters");
    EXPECT_TRUE(gate.operation_family_coverage_required == 1u, "operations");
    EXPECT_TRUE(gate.positive_kat_transcript_lane_recorded == 1u, "positive lane");
    EXPECT_TRUE(gate.negative_kat_transcript_lane_recorded == 1u, "negative lane");
    EXPECT_TRUE(gate.malformed_kat_transcript_lane_recorded == 1u, "malformed lane");
    EXPECT_TRUE(
        gate.implicit_rejection_transcript_lane_recorded == 1u,
        "implicit lane");
    EXPECT_TRUE(gate.acvp_keygen_transcript_lane_recorded == 1u, "keygen lane");
    EXPECT_TRUE(
        gate.acvp_encap_decap_transcript_lane_recorded == 1u,
        "encap decap lane");
    EXPECT_TRUE(
        gate.acvp_decapsulation_val_transcript_lane_recorded == 1u,
        "decapsulation val lane");
    EXPECT_TRUE(gate.acvp_key_check_transcript_lane_recorded == 1u, "key check lane");
    EXPECT_TRUE(
        gate.provider_differential_transcript_lane_recorded == 1u,
        "provider lane");
    EXPECT_TRUE(gate.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(gate.offline_only_replay_recorded == 1u, "offline");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(gate.kat_replay_transcripts_recorded == 0u, "kat transcripts");
    EXPECT_TRUE(gate.acvp_replay_transcripts_recorded == 0u, "acvp transcripts");
    EXPECT_TRUE(gate.transcript_digests_verified == 0u, "digests verified");
    EXPECT_TRUE(gate.ci_replay_transcript_recorded == 0u, "ci transcript");
    EXPECT_TRUE(gate.review_disposition_recorded == 0u, "review");
    EXPECT_TRUE(gate.transcript_gate_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.kat_execution_allowed == 0u, "kat execution");
    EXPECT_TRUE(gate.acvp_response_generation_allowed == 0u, "response generation");
    EXPECT_TRUE(gate.acvp_submission_allowed == 0u, "submission allowed");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_transcript_items_total == 44u, "total");
    EXPECT_TRUE(gate.required_transcript_items_satisfied == 38u, "satisfied");
    EXPECT_TRUE(
        gate.error == LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_is_no_effect(
            &gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_allows_transcript_acceptance(
            &gate) == 0,
        "acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "replay_transcript_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_key_check_transcript_lane_recorded=1") != 0,
        "key check report");
    EXPECT_TRUE(
        strstr(rendered, "kat_replay_transcripts_recorded=0") != 0,
        "transcript report");
    EXPECT_TRUE(
        strstr(rendered, "required_transcript_items_total=44") != 0,
        "total report");
    return 0;
}

static int replay_transcript_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_allows_transcript_acceptance(
            0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report gate");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (replay_transcript_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (replay_transcript_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem kat acvp replay transcript gate invariants: ok\n");
    return 0;
}
