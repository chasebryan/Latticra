#ifndef LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_H
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_source_digest_verification_error_t;

typedef struct {
    char verification_profile[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_LABEL_MAX];
    char verification_scope[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_LABEL_MAX];
    char verification_state[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_STATE_MAX];
    unsigned source_digest_verification_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_source_integrity_bound;
    unsigned digest_algorithm_sha256_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned receipt_schema_bound;
    unsigned normalized_path_policy_bound;
    unsigned replay_harness_template_recorded;
    unsigned tamper_fixture_template_recorded;
    unsigned offline_only_verification_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_files_created;
    unsigned source_receipts_available;
    unsigned test_receipts_available;
    unsigned build_receipts_available;
    unsigned source_digest_replay_executed;
    unsigned tamper_fixture_executed;
    unsigned ci_verification_harness_recorded;
    unsigned verification_result_reviewed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_verification_items_total;
    unsigned required_verification_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_STATE_MAX];
    latticra_q_seal_ml_kem_source_digest_verification_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_STATE_MAX];
} latticra_q_seal_ml_kem_source_digest_verification_t;

const char *latticra_q_seal_ml_kem_source_digest_verification_error_label(
    latticra_q_seal_ml_kem_source_digest_verification_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_verification_prepare(
    latticra_q_seal_ml_kem_source_digest_verification_t *out);
int latticra_q_seal_ml_kem_source_digest_verification_is_no_effect(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification);
int latticra_q_seal_ml_kem_source_digest_verification_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_verification_report(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
