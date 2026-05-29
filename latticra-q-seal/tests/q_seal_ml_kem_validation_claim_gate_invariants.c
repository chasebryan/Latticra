#include "latticra/q_seal_ml_kem_validation_claim_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int validation_claim_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_validation_claim_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.validation_claim_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.validation_claim_profile,
            "latticra-q-seal-ml-kem-validation-claim-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(gate.formal_title, "Latticra Q-Seal ML-KEM Validation Claim Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-CMVP,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(gate.acvp_ml_kem_protocol_bound == 1u, "acvp");
    EXPECT_TRUE(gate.acvp_verdict_receipt_gate_bound == 1u, "verdict");
    EXPECT_TRUE(gate.replay_transcript_gate_bound == 1u, "replay");
    EXPECT_TRUE(gate.acvp_submission_package_contract_bound == 1u, "package");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(gate.readiness_profile_bound == 1u, "readiness");
    EXPECT_TRUE(gate.module_boundary_gate_bound == 1u, "module boundary");
    EXPECT_TRUE(gate.security_policy_gate_bound == 1u, "security policy gate");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(gate.source_digest_verification_bound == 1u, "source digest");
    EXPECT_TRUE(gate.provider_differential_bound == 1u, "provider");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.public_claim_taxonomy_recorded == 1u, "taxonomy");
    EXPECT_TRUE(gate.no_implicit_fips_claim_policy_recorded == 1u, "fips policy");
    EXPECT_TRUE(gate.no_implicit_acvp_claim_policy_recorded == 1u, "acvp policy");
    EXPECT_TRUE(gate.module_boundary_required == 1u, "module boundary required");
    EXPECT_TRUE(gate.security_policy_required == 1u, "security policy required");
    EXPECT_TRUE(
        gate.acvp_certificate_or_validation_record_required == 1u,
        "acvp certificate required");
    EXPECT_TRUE(gate.cmvp_certificate_required == 1u, "cmvp certificate required");
    EXPECT_TRUE(gate.implementation_digest_receipt_required == 1u, "implementation digest");
    EXPECT_TRUE(gate.release_artifact_digest_required == 1u, "release digest");
    EXPECT_TRUE(gate.release_notes_claim_review_required == 1u, "release notes");
    EXPECT_TRUE(gate.docs_public_surface_review_required == 1u, "public docs");
    EXPECT_TRUE(gate.operator_warning_required == 1u, "operator warning");
    EXPECT_TRUE(gate.rollback_claim_revocation_required == 1u, "rollback");
    EXPECT_TRUE(gate.no_secret_material_logging_required == 1u, "secret logging");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(gate.implementation_claim_evidence_recorded == 0u, "claim evidence");
    EXPECT_TRUE(gate.acvp_pass_evidence_recorded == 0u, "acvp pass");
    EXPECT_TRUE(gate.cmvp_certificate_recorded == 0u, "cmvp cert");
    EXPECT_TRUE(gate.module_boundary_recorded == 0u, "module boundary");
    EXPECT_TRUE(gate.security_policy_recorded == 0u, "security policy");
    EXPECT_TRUE(gate.release_artifact_digest_recorded == 0u, "artifact digest");
    EXPECT_TRUE(gate.public_claim_review_recorded == 0u, "claim review");
    EXPECT_TRUE(gate.reviewer_disposition_recorded == 0u, "reviewer disposition");
    EXPECT_TRUE(gate.validation_claim_gate_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.public_validation_claim_allowed == 0u, "public claim");
    EXPECT_TRUE(gate.fips_validation_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.post_quantum_migration_claim_allowed == 0u, "migration claim");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_validation_claim_items_total == 42u, "total");
    EXPECT_TRUE(gate.required_validation_claim_items_satisfied == 33u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_allows_validation_claims(&gate) == 0,
        "allows claims");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM VALIDATION CLAIM GATE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "validation_claim_gate_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "module_boundary_gate_bound=1") != 0, "boundary report");
    EXPECT_TRUE(
        strstr(rendered, "security_policy_gate_bound=1") != 0,
        "security policy report");
    EXPECT_TRUE(strstr(rendered, "cmvp_certificate_required=1") != 0, "cmvp report");
    EXPECT_TRUE(strstr(rendered, "public_validation_claim_allowed=0") != 0, "claim report");
    EXPECT_TRUE(
        strstr(rendered, "required_validation_claim_items_total=42") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-validation-claim-gate-blocked") != 0,
        "status");
    return 0;
}

static int validation_claim_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_validation_claim_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_allows_validation_claims(0) == 0,
        "null claims");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_validation_claim_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (validation_claim_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (validation_claim_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem validation claim gate invariants: ok\n");
    return 0;
}
