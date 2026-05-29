#ifndef LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE_H
#define LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_ci_promotion_evidence_error_t;

typedef struct {
    char promotion_profile[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_LABEL_MAX];
    char promotion_scope[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_LABEL_MAX];
    char promotion_state[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_STATE_MAX];
    unsigned ci_promotion_evidence_present;
    unsigned ssdf_secure_build_gate_recorded;
    unsigned fips_203_parameter_gate_bound;
    unsigned sp_800_227_kem_usage_gate_bound;
    unsigned make_quality_security_standards_bound;
    unsigned local_wrapper_scripts_recorded;
    unsigned qseal_subsystem_scripts_recorded;
    unsigned readiness_gate_bound;
    unsigned implementation_binding_manifest_required;
    unsigned implementation_binding_manifest_bound;
    unsigned replay_transcript_gate_bound;
    unsigned acvp_verdict_receipt_gate_bound;
    unsigned validation_claim_gate_bound;
    unsigned module_boundary_gate_bound;
    unsigned security_policy_gate_bound;
    unsigned evidence_import_packet_manifest_bound;
    unsigned evidence_import_review_gate_bound;
    unsigned kat_acvp_gate_passing_recorded;
    unsigned constant_time_gate_passing_recorded;
    unsigned memory_safety_gate_passing_recorded;
    unsigned side_channel_gate_passing_recorded;
    unsigned negative_test_gate_passing_recorded;
    unsigned provider_differential_gate_passing_recorded;
    unsigned implementation_binding_ci_result_recorded;
    unsigned promotion_workflow_recorded;
    unsigned release_claim_gate_recorded;
    unsigned signed_artifact_receipt_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_promotion_items_total;
    unsigned required_promotion_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_STATE_MAX];
    latticra_q_seal_ml_kem_ci_promotion_evidence_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_STATE_MAX];
} latticra_q_seal_ml_kem_ci_promotion_evidence_t;

const char *latticra_q_seal_ml_kem_ci_promotion_evidence_error_label(
    latticra_q_seal_ml_kem_ci_promotion_evidence_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(
    latticra_q_seal_ml_kem_ci_promotion_evidence_t *out);
int latticra_q_seal_ml_kem_ci_promotion_evidence_is_no_effect(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence);
int latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence);
latticra_q_seal_status_t latticra_q_seal_ml_kem_ci_promotion_evidence_report(
    const latticra_q_seal_ml_kem_ci_promotion_evidence_t *evidence,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
