#ifndef LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_H
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_source_digest_receipt_error_t;

typedef struct {
    char receipt_profile[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_LABEL_MAX];
    char receipt_scope[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_LABEL_MAX];
    char receipt_state[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_STATE_MAX];
    unsigned source_digest_receipt_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_source_integrity_bound;
    unsigned digest_algorithm_sha256_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned source_digest_manifest_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned planned_source_receipts_count;
    unsigned planned_test_receipts_count;
    unsigned planned_build_receipts_count;
    unsigned receipt_schema_recorded;
    unsigned normalized_path_policy_recorded;
    unsigned hash_command_policy_recorded;
    unsigned reproducible_snapshot_policy_recorded;
    unsigned tamper_evidence_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_files_created;
    unsigned source_receipts_recorded;
    unsigned test_receipts_recorded;
    unsigned build_receipts_recorded;
    unsigned source_receipts_verified;
    unsigned reviewed_digest_receipt_recorded;
    unsigned receipt_replay_check_recorded;
    unsigned ci_digest_verification_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_receipt_items_total;
    unsigned required_receipt_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_STATE_MAX];
    latticra_q_seal_ml_kem_source_digest_receipt_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_STATE_MAX];
} latticra_q_seal_ml_kem_source_digest_receipt_t;

const char *latticra_q_seal_ml_kem_source_digest_receipt_error_label(
    latticra_q_seal_ml_kem_source_digest_receipt_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_receipt_prepare(
    latticra_q_seal_ml_kem_source_digest_receipt_t *out);
int latticra_q_seal_ml_kem_source_digest_receipt_is_no_effect(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt);
int latticra_q_seal_ml_kem_source_digest_receipt_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_receipt_report(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
