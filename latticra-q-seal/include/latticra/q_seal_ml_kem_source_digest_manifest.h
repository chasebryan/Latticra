#ifndef LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST_H
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_source_digest_manifest_error_t;

typedef struct {
    char digest_profile[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_LABEL_MAX];
    char digest_algorithm[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_LABEL_MAX];
    char digest_state[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_STATE_MAX];
    unsigned source_digest_manifest_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_source_integrity_bound;
    unsigned digest_algorithm_sha256_recorded;
    unsigned clean_room_source_boundary_recorded;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned digest_template_recorded;
    unsigned hash_command_policy_recorded;
    unsigned third_party_source_denial_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_files_created;
    unsigned source_file_digests_recorded;
    unsigned test_file_digests_recorded;
    unsigned build_script_digests_recorded;
    unsigned reviewed_digest_receipt_recorded;
    unsigned reproducible_source_snapshot_recorded;
    unsigned digest_verification_ci_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_digest_items_total;
    unsigned required_digest_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_STATE_MAX];
    latticra_q_seal_ml_kem_source_digest_manifest_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_STATE_MAX];
} latticra_q_seal_ml_kem_source_digest_manifest_t;

const char *latticra_q_seal_ml_kem_source_digest_manifest_error_label(
    latticra_q_seal_ml_kem_source_digest_manifest_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_manifest_prepare(
    latticra_q_seal_ml_kem_source_digest_manifest_t *out);
int latticra_q_seal_ml_kem_source_digest_manifest_is_clean_room_no_effect(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest);
int latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_manifest_report(
    const latticra_q_seal_ml_kem_source_digest_manifest_t *manifest,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
