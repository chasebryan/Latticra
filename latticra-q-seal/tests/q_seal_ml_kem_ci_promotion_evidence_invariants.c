#include "latticra/q_seal_ml_kem_ci_promotion_evidence.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int ci_promotion_evidence_is_fail_closed(void) {
    latticra_q_seal_ml_kem_ci_promotion_evidence_t evidence;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            evidence.promotion_profile,
            "latticra-q-seal-ml-kem-ci-promotion-evidence/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(evidence.formal_title, "Latticra Q-Seal ML-KEM CI Promotion Evidence") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            evidence.standards_basis,
            "NIST-SP-800-218-SSDF-and-FIPS-203-and-SP-800-227") == 0,
        "standards");
    EXPECT_TRUE(strcmp(evidence.promotion_state, "ci-promotion-blocked") == 0, "state");
    EXPECT_TRUE(evidence.ci_promotion_evidence_present == 1u, "present");
    EXPECT_TRUE(evidence.ssdf_secure_build_gate_recorded == 1u, "ssdf");
    EXPECT_TRUE(evidence.fips_203_parameter_gate_bound == 1u, "fips203");
    EXPECT_TRUE(evidence.sp_800_227_kem_usage_gate_bound == 1u, "sp800227");
    EXPECT_TRUE(evidence.make_quality_security_standards_bound == 1u, "make");
    EXPECT_TRUE(evidence.local_wrapper_scripts_recorded == 1u, "wrappers");
    EXPECT_TRUE(evidence.qseal_subsystem_scripts_recorded == 1u, "subsystem scripts");
    EXPECT_TRUE(evidence.readiness_gate_bound == 1u, "readiness");
    EXPECT_TRUE(evidence.implementation_binding_manifest_required == 1u, "binding required");
    EXPECT_TRUE(evidence.implementation_binding_manifest_bound == 1u, "binding bound");
    EXPECT_TRUE(evidence.replay_transcript_gate_bound == 1u, "transcript gate");
    EXPECT_TRUE(evidence.acvp_verdict_receipt_gate_bound == 1u, "verdict receipt");
    EXPECT_TRUE(evidence.validation_claim_gate_bound == 1u, "validation claim");
    EXPECT_TRUE(evidence.module_boundary_gate_bound == 1u, "module boundary");
    EXPECT_TRUE(evidence.security_policy_gate_bound == 1u, "security policy");
    EXPECT_TRUE(evidence.evidence_import_packet_manifest_bound == 1u, "packet manifest");
    EXPECT_TRUE(evidence.evidence_import_review_gate_bound == 1u, "evidence import");
    EXPECT_TRUE(evidence.kat_acvp_gate_passing_recorded == 0u, "kat acvp result");
    EXPECT_TRUE(evidence.constant_time_gate_passing_recorded == 0u, "constant result");
    EXPECT_TRUE(evidence.memory_safety_gate_passing_recorded == 0u, "memory result");
    EXPECT_TRUE(evidence.side_channel_gate_passing_recorded == 0u, "side result");
    EXPECT_TRUE(evidence.negative_test_gate_passing_recorded == 0u, "negative result");
    EXPECT_TRUE(evidence.provider_differential_gate_passing_recorded == 0u, "provider result");
    EXPECT_TRUE(evidence.implementation_binding_ci_result_recorded == 0u, "binding result");
    EXPECT_TRUE(evidence.promotion_workflow_recorded == 0u, "workflow");
    EXPECT_TRUE(evidence.release_claim_gate_recorded == 0u, "release");
    EXPECT_TRUE(evidence.signed_artifact_receipt_recorded == 0u, "receipt");
    EXPECT_TRUE(evidence.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(evidence.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(evidence.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(evidence.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(evidence.required_promotion_items_total == 26u, "total");
    EXPECT_TRUE(evidence.required_promotion_items_satisfied == 16u, "satisfied");
    EXPECT_TRUE(evidence.error == LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_is_no_effect(&evidence) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(
            &evidence) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_report(
            &evidence,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM CI PROMOTION EVIDENCE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "ci_promotion_evidence_present=1") != 0, "present report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_binding_manifest_bound=1") != 0,
        "binding report");
    EXPECT_TRUE(
        strstr(rendered, "replay_transcript_gate_bound=1") != 0,
        "transcript gate report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_verdict_receipt_gate_bound=1") != 0,
        "verdict receipt report");
    EXPECT_TRUE(
        strstr(rendered, "validation_claim_gate_bound=1") != 0,
        "validation claim report");
    EXPECT_TRUE(
        strstr(rendered, "module_boundary_gate_bound=1") != 0,
        "module boundary report");
    EXPECT_TRUE(
        strstr(rendered, "security_policy_gate_bound=1") != 0,
        "security policy report");
    EXPECT_TRUE(
        strstr(rendered, "evidence_import_packet_manifest_bound=1") != 0,
        "packet manifest report");
    EXPECT_TRUE(
        strstr(rendered, "evidence_import_review_gate_bound=1") != 0,
        "evidence import report");
    EXPECT_TRUE(strstr(rendered, "operation_execution_allowed=0") != 0, "operation report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-ci-promotion-evidence-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_ci_promotion_evidence_t evidence;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(0) == 0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_report(
            &evidence,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report evidence");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_ci_promotion_evidence_report(
            &evidence,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (ci_promotion_evidence_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem ci promotion evidence invariants: ok\n");
    return 0;
}
