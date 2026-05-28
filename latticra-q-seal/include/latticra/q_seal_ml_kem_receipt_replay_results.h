#ifndef LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_H
#define LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_receipt_replay_results_error_t;

typedef struct {
    char replay_profile[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_LABEL_MAX];
    char replay_scope[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_LABEL_MAX];
    char replay_state[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_STATE_MAX];
    unsigned receipt_replay_results_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_source_integrity_bound;
    unsigned digest_algorithm_sha256_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned source_digest_verification_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned source_receipt_result_schema_recorded;
    unsigned test_receipt_result_schema_recorded;
    unsigned build_receipt_result_schema_recorded;
    unsigned replay_command_template_recorded;
    unsigned tamper_result_template_recorded;
    unsigned ci_result_binding_recorded;
    unsigned offline_only_replay_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_files_created;
    unsigned source_replay_results_recorded;
    unsigned test_replay_results_recorded;
    unsigned build_replay_results_recorded;
    unsigned tamper_replay_results_recorded;
    unsigned replay_result_reviewed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_replay_items_total;
    unsigned required_replay_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_STATE_MAX];
    latticra_q_seal_ml_kem_receipt_replay_results_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_STATE_MAX];
} latticra_q_seal_ml_kem_receipt_replay_results_t;

const char *latticra_q_seal_ml_kem_receipt_replay_results_error_label(
    latticra_q_seal_ml_kem_receipt_replay_results_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_receipt_replay_results_prepare(
    latticra_q_seal_ml_kem_receipt_replay_results_t *out);
int latticra_q_seal_ml_kem_receipt_replay_results_is_no_effect(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results);
int latticra_q_seal_ml_kem_receipt_replay_results_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results);
latticra_q_seal_status_t latticra_q_seal_ml_kem_receipt_replay_results_report(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
