#include "latticra/q_seal_ml_kem_acvp_verdict_receipt_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_verdict_receipt_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.acvp_verdict_receipt_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.verdict_receipt_profile,
            "latticra-q-seal-ml-kem-acvp-verdict-receipt-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            gate.formal_title,
            "Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(gate.acvp_ml_kem_protocol_bound == 1u, "acvp protocol");
    EXPECT_TRUE(gate.acvp_submission_package_contract_bound == 1u, "package");
    EXPECT_TRUE(gate.replay_transcript_gate_bound == 1u, "replay");
    EXPECT_TRUE(gate.acvp_response_contract_bound == 1u, "response");
    EXPECT_TRUE(gate.acvp_response_fixture_bound == 1u, "response fixture");
    EXPECT_TRUE(gate.acvp_parser_contract_bound == 1u, "parser");
    EXPECT_TRUE(gate.acvp_capability_matrix_bound == 1u, "capability");
    EXPECT_TRUE(gate.vector_fixture_digest_ledger_bound == 1u, "ledger");
    EXPECT_TRUE(gate.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_identity_fixture_bound == 1u, "identity");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.offline_verdict_receipt_policy_recorded == 1u, "offline policy");
    EXPECT_TRUE(gate.validation_server_receipt_required == 1u, "server receipt");
    EXPECT_TRUE(gate.acvp_session_identifier_required == 1u, "session");
    EXPECT_TRUE(gate.vsid_tgid_tcid_verdict_mapping_required == 1u, "mapping");
    EXPECT_TRUE(gate.algorithm_revision_required == 1u, "revision");
    EXPECT_TRUE(gate.parameter_set_verdicts_required == 1u, "parameter verdicts");
    EXPECT_TRUE(gate.operation_verdicts_required == 1u, "operation verdicts");
    EXPECT_TRUE(gate.pass_fail_verdict_required == 1u, "pass fail");
    EXPECT_TRUE(gate.server_response_digest_required == 1u, "server digest");
    EXPECT_TRUE(gate.receipt_digest_sha256_required == 1u, "sha256");
    EXPECT_TRUE(gate.certificate_or_validation_record_required == 1u, "certificate");
    EXPECT_TRUE(gate.validation_date_required == 1u, "date");
    EXPECT_TRUE(gate.lab_or_server_identity_required == 1u, "server identity");
    EXPECT_TRUE(gate.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(gate.offline_only_intake_recorded == 1u, "offline");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.submission_receipt_bound == 0u, "receipt bound");
    EXPECT_TRUE(gate.validation_server_acceptance_bound == 0u, "server acceptance");
    EXPECT_TRUE(gate.pass_verdict_recorded == 0u, "pass recorded");
    EXPECT_TRUE(gate.certificate_identifier_recorded == 0u, "cert id");
    EXPECT_TRUE(gate.receipt_digest_verified == 0u, "digest verified");
    EXPECT_TRUE(gate.reviewer_disposition_recorded == 0u, "review");
    EXPECT_TRUE(gate.acvp_verdict_receipt_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.network_session_enabled == 0u, "network");
    EXPECT_TRUE(gate.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_verdict_receipt_items_total == 39u, "total");
    EXPECT_TRUE(gate.required_verdict_receipt_items_satisfied == 32u, "satisfied");
    EXPECT_TRUE(
        gate.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_allows_verdict_acceptance(
            &gate) == 0,
        "allows verdict");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM ACVP VERDICT RECEIPT GATE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "acvp_verdict_receipt_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "validation_server_receipt_required=1") != 0,
        "receipt report");
    EXPECT_TRUE(
        strstr(rendered, "fips_claim_allowed=0") != 0,
        "fips claim report");
    EXPECT_TRUE(
        strstr(rendered, "required_verdict_receipt_items_total=39") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-acvp-verdict-receipt-gate-blocked") != 0,
        "status");
    return 0;
}

static int acvp_verdict_receipt_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_allows_verdict_acceptance(0) ==
            0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_verdict_receipt_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_verdict_receipt_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp verdict receipt gate invariants: ok\n");
    return 0;
}
