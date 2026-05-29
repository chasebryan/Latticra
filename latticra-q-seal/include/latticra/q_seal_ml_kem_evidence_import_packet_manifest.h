#ifndef LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST_H
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_t;

typedef struct {
    char evidence_packet_profile[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_LABEL_MAX];
    char evidence_packet_scope[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_LABEL_MAX];
    char evidence_packet_state[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_STATE_MAX];
    unsigned evidence_import_packet_manifest_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_schema_bound;
    unsigned evidence_import_review_gate_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned receipt_replay_results_bound;
    unsigned source_digest_receipt_bound;
    unsigned source_digest_verification_bound;
    unsigned reviewer_identity_fixture_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned review_disposition_ledger_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned offline_packet_intake_recorded;
    unsigned digest_algorithm_sha256_required;
    unsigned immutable_packet_record_required;
    unsigned source_url_column_required;
    unsigned source_digest_column_required;
    unsigned bundle_size_column_required;
    unsigned license_column_required;
    unsigned storage_path_column_required;
    unsigned parameter_set_column_required;
    unsigned operation_family_column_required;
    unsigned negative_case_column_required;
    unsigned replay_transcript_column_required;
    unsigned tamper_evidence_column_required;
    unsigned reviewer_role_column_required;
    unsigned reviewer_identity_column_required;
    unsigned disposition_column_required;
    unsigned import_timestamp_column_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned fixture_digest_packet_rows_imported;
    unsigned receipt_replay_packet_rows_imported;
    unsigned source_digest_packet_rows_imported;
    unsigned reviewer_role_packet_rows_imported;
    unsigned coverage_packet_rows_imported;
    unsigned tamper_packet_rows_imported;
    unsigned evidence_packet_reviewed;
    unsigned evidence_packet_manifest_accepted;
    unsigned vector_execution_allowed;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned implementation_promotion_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_evidence_packet_items_total;
    unsigned required_evidence_packet_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_STATE_MAX];
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_STATE_MAX];
} latticra_q_seal_ml_kem_evidence_import_packet_manifest_t;

const char *latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_label(
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *out);
int latticra_q_seal_ml_kem_evidence_import_packet_manifest_is_no_effect(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest);
int latticra_q_seal_ml_kem_evidence_import_packet_manifest_allows_packet_acceptance(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
