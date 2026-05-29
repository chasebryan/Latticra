#ifndef LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_evidence_import_review_gate_error_t;

typedef struct {
    char evidence_import_profile[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_LABEL_MAX];
    char evidence_import_scope[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_LABEL_MAX];
    char evidence_import_state[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_STATE_MAX];
    unsigned evidence_import_review_gate_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_schema_bound;
    unsigned evidence_import_packet_manifest_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned receipt_replay_results_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned reviewer_identity_fixture_bound;
    unsigned review_disposition_ledger_bound;
    unsigned source_digest_verification_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned offline_evidence_intake_recorded;
    unsigned digest_algorithm_sha256_required;
    unsigned immutable_import_record_required;
    unsigned source_url_digest_size_license_required;
    unsigned parameter_set_coverage_required;
    unsigned operation_family_coverage_required;
    unsigned replay_transcript_required;
    unsigned tamper_replay_required;
    unsigned reviewer_role_import_required;
    unsigned dual_reviewer_separation_required;
    unsigned approval_authority_required;
    unsigned no_implicit_operation_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned fixture_digest_rows_imported;
    unsigned receipt_replay_transcripts_imported;
    unsigned reviewer_role_records_imported;
    unsigned source_digest_receipts_imported;
    unsigned parameter_set_coverage_recorded;
    unsigned operation_family_coverage_recorded;
    unsigned negative_case_coverage_recorded;
    unsigned replay_tamper_evidence_recorded;
    unsigned evidence_import_reviewed;
    unsigned evidence_import_gate_accepted;
    unsigned vector_execution_allowed;
    unsigned acvp_submission_allowed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_evidence_import_items_total;
    unsigned required_evidence_import_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_STATE_MAX];
    latticra_q_seal_ml_kem_evidence_import_review_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_STATE_MAX];
} latticra_q_seal_ml_kem_evidence_import_review_gate_t;

const char *latticra_q_seal_ml_kem_evidence_import_review_gate_error_label(
    latticra_q_seal_ml_kem_evidence_import_review_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(
    latticra_q_seal_ml_kem_evidence_import_review_gate_t *out);
int latticra_q_seal_ml_kem_evidence_import_review_gate_is_no_effect(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate);
int latticra_q_seal_ml_kem_evidence_import_review_gate_allows_import_acceptance(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_import_review_gate_report(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
