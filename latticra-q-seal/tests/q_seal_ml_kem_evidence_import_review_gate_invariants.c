#include "latticra/q_seal_ml_kem_evidence_import_review_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int evidence_import_review_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_evidence_import_review_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.evidence_import_review_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.evidence_import_profile,
            "latticra-q-seal-ml-kem-evidence-import-review-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            gate.formal_title,
            "Latticra Q-Seal ML-KEM Evidence Import Review Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(gate.acvp_ml_kem_schema_bound == 1u, "acvp");
    EXPECT_TRUE(gate.evidence_import_packet_manifest_bound == 1u, "packet");
    EXPECT_TRUE(gate.vector_fixture_digest_ledger_bound == 1u, "fixture ledger");
    EXPECT_TRUE(gate.receipt_replay_results_bound == 1u, "replay");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role mapping");
    EXPECT_TRUE(gate.reviewer_identity_fixture_bound == 1u, "identity");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.source_digest_verification_bound == 1u, "digest verification");
    EXPECT_TRUE(gate.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.offline_evidence_intake_recorded == 1u, "offline");
    EXPECT_TRUE(gate.digest_algorithm_sha256_required == 1u, "sha256");
    EXPECT_TRUE(gate.immutable_import_record_required == 1u, "immutable");
    EXPECT_TRUE(gate.source_url_digest_size_license_required == 1u, "source metadata");
    EXPECT_TRUE(gate.parameter_set_coverage_required == 1u, "parameter coverage");
    EXPECT_TRUE(gate.operation_family_coverage_required == 1u, "operation coverage");
    EXPECT_TRUE(gate.replay_transcript_required == 1u, "transcript");
    EXPECT_TRUE(gate.tamper_replay_required == 1u, "tamper");
    EXPECT_TRUE(gate.reviewer_role_import_required == 1u, "role import");
    EXPECT_TRUE(gate.dual_reviewer_separation_required == 1u, "separation");
    EXPECT_TRUE(gate.approval_authority_required == 1u, "approval");
    EXPECT_TRUE(gate.no_implicit_operation_policy_recorded == 1u, "operation policy");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.fixture_digest_rows_imported == 0u, "fixture rows");
    EXPECT_TRUE(gate.receipt_replay_transcripts_imported == 0u, "replay transcripts");
    EXPECT_TRUE(gate.reviewer_role_records_imported == 0u, "role records");
    EXPECT_TRUE(gate.source_digest_receipts_imported == 0u, "source receipts");
    EXPECT_TRUE(gate.parameter_set_coverage_recorded == 0u, "parameter recorded");
    EXPECT_TRUE(gate.operation_family_coverage_recorded == 0u, "operation recorded");
    EXPECT_TRUE(gate.negative_case_coverage_recorded == 0u, "negative recorded");
    EXPECT_TRUE(gate.replay_tamper_evidence_recorded == 0u, "tamper recorded");
    EXPECT_TRUE(gate.evidence_import_reviewed == 0u, "reviewed");
    EXPECT_TRUE(gate.evidence_import_gate_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.vector_execution_allowed == 0u, "vector execution");
    EXPECT_TRUE(gate.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(gate.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_evidence_import_items_total == 37u, "total");
    EXPECT_TRUE(gate.required_evidence_import_items_satisfied == 27u, "satisfied");
    EXPECT_TRUE(
        gate.error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_allows_import_acceptance(
            &gate) == 0,
        "import acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "evidence_import_review_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "vector_fixture_digest_ledger_bound=1") != 0,
        "fixture ledger report");
    EXPECT_TRUE(
        strstr(rendered, "evidence_import_packet_manifest_bound=1") != 0,
        "packet report");
    EXPECT_TRUE(
        strstr(rendered, "receipt_replay_transcripts_imported=0") != 0,
        "replay transcript report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_role_records_imported=0") != 0,
        "role records report");
    EXPECT_TRUE(
        strstr(rendered, "required_evidence_import_items_total=37") != 0,
        "total report");
    return 0;
}

static int evidence_import_review_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_evidence_import_review_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_allows_import_acceptance(0) ==
            0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_review_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (evidence_import_review_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (evidence_import_review_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem evidence import review gate invariants: ok\n");
    return 0;
}
