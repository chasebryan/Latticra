#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_t;

typedef struct {
    char verdict_receipt_profile
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_LABEL_MAX];
    char verdict_receipt_scope
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_LABEL_MAX];
    char verdict_receipt_state
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_STATE_MAX];
    unsigned acvp_verdict_receipt_gate_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_protocol_bound;
    unsigned acvp_submission_package_contract_bound;
    unsigned replay_transcript_gate_bound;
    unsigned acvp_response_contract_bound;
    unsigned acvp_response_fixture_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_identity_fixture_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned offline_verdict_receipt_policy_recorded;
    unsigned validation_server_receipt_required;
    unsigned acvp_session_identifier_required;
    unsigned vsid_tgid_tcid_verdict_mapping_required;
    unsigned algorithm_revision_required;
    unsigned parameter_set_verdicts_required;
    unsigned operation_verdicts_required;
    unsigned pass_fail_verdict_required;
    unsigned server_response_digest_required;
    unsigned receipt_digest_sha256_required;
    unsigned certificate_or_validation_record_required;
    unsigned validation_date_required;
    unsigned lab_or_server_identity_required;
    unsigned no_secret_material_logging_required;
    unsigned offline_only_intake_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned submission_receipt_bound;
    unsigned validation_server_acceptance_bound;
    unsigned pass_verdict_recorded;
    unsigned certificate_identifier_recorded;
    unsigned receipt_digest_verified;
    unsigned reviewer_disposition_recorded;
    unsigned acvp_verdict_receipt_accepted;
    unsigned network_session_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_verdict_receipt_items_total;
    unsigned required_verdict_receipt_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t;

const char *latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_label(
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *out);
int latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate);
int latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_allows_verdict_acceptance(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
