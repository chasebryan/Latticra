#ifndef LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_t;

typedef struct {
    char transcript_profile[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_LABEL_MAX];
    char transcript_scope[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_LABEL_MAX];
    char transcript_state[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_STATE_MAX];
    unsigned replay_transcript_gate_present;
    unsigned fips_203_algorithm_bound;
    unsigned nist_acvp_ml_kem_bound;
    unsigned ssdf_evidence_integrity_bound;
    unsigned kat_manifest_bound;
    unsigned kat_runner_contract_bound;
    unsigned kat_result_schema_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned acvp_submission_package_contract_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned receipt_replay_results_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned provider_differential_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned deterministic_replay_transcript_schema_recorded;
    unsigned transcript_digest_sha256_required;
    unsigned transcript_command_fingerprint_required;
    unsigned fixture_digest_reference_required;
    unsigned implementation_digest_reference_required;
    unsigned parameter_set_coverage_required;
    unsigned operation_family_coverage_required;
    unsigned positive_kat_transcript_lane_recorded;
    unsigned negative_kat_transcript_lane_recorded;
    unsigned malformed_kat_transcript_lane_recorded;
    unsigned implicit_rejection_transcript_lane_recorded;
    unsigned acvp_keygen_transcript_lane_recorded;
    unsigned acvp_encap_decap_transcript_lane_recorded;
    unsigned acvp_decapsulation_val_transcript_lane_recorded;
    unsigned acvp_key_check_transcript_lane_recorded;
    unsigned provider_differential_transcript_lane_recorded;
    unsigned no_secret_material_logging_required;
    unsigned offline_only_replay_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned kat_replay_transcripts_recorded;
    unsigned acvp_replay_transcripts_recorded;
    unsigned transcript_digests_verified;
    unsigned ci_replay_transcript_recorded;
    unsigned review_disposition_recorded;
    unsigned transcript_gate_accepted;
    unsigned kat_execution_allowed;
    unsigned acvp_response_generation_allowed;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_transcript_items_total;
    unsigned required_transcript_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_STATE_MAX];
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_STATE_MAX];
} latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t;

const char *latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_label(
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *out);
int latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_is_no_effect(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate);
int latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_allows_transcript_acceptance(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
