#ifndef LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_validation_claim_gate_error_t;

typedef struct {
    char validation_claim_profile
        [LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_LABEL_MAX];
    char validation_claim_scope
        [LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_LABEL_MAX];
    char validation_claim_state
        [LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_STATE_MAX];
    unsigned validation_claim_gate_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_protocol_bound;
    unsigned acvp_verdict_receipt_gate_bound;
    unsigned replay_transcript_gate_bound;
    unsigned acvp_submission_package_contract_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned readiness_profile_bound;
    unsigned module_boundary_gate_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned source_digest_verification_bound;
    unsigned provider_differential_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned public_claim_taxonomy_recorded;
    unsigned no_implicit_fips_claim_policy_recorded;
    unsigned no_implicit_acvp_claim_policy_recorded;
    unsigned module_boundary_required;
    unsigned security_policy_required;
    unsigned acvp_certificate_or_validation_record_required;
    unsigned cmvp_certificate_required;
    unsigned implementation_digest_receipt_required;
    unsigned release_artifact_digest_required;
    unsigned release_notes_claim_review_required;
    unsigned docs_public_surface_review_required;
    unsigned operator_warning_required;
    unsigned rollback_claim_revocation_required;
    unsigned no_secret_material_logging_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_claim_evidence_recorded;
    unsigned acvp_pass_evidence_recorded;
    unsigned cmvp_certificate_recorded;
    unsigned module_boundary_recorded;
    unsigned security_policy_recorded;
    unsigned release_artifact_digest_recorded;
    unsigned public_claim_review_recorded;
    unsigned reviewer_disposition_recorded;
    unsigned validation_claim_gate_accepted;
    unsigned public_validation_claim_allowed;
    unsigned fips_validation_claim_allowed;
    unsigned post_quantum_migration_claim_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned operation_execution_allowed;
    unsigned runtime_authority_granted;
    unsigned required_validation_claim_items_total;
    unsigned required_validation_claim_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_STATE_MAX];
    latticra_q_seal_ml_kem_validation_claim_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_STATE_MAX];
} latticra_q_seal_ml_kem_validation_claim_gate_t;

const char *latticra_q_seal_ml_kem_validation_claim_gate_error_label(
    latticra_q_seal_ml_kem_validation_claim_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_validation_claim_gate_prepare(
    latticra_q_seal_ml_kem_validation_claim_gate_t *out);
int latticra_q_seal_ml_kem_validation_claim_gate_is_no_effect(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate);
int latticra_q_seal_ml_kem_validation_claim_gate_allows_validation_claims(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_validation_claim_gate_report(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
