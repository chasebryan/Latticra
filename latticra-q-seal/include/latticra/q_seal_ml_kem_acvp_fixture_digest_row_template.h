#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_t;

typedef struct {
    char template_profile
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_LABEL_MAX];
    char template_scope[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_LABEL_MAX];
    char template_state[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_STATE_MAX];
    unsigned acvp_fixture_digest_row_template_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned vector_source_intake_bound;
    unsigned vector_schema_bound;
    unsigned vector_fixture_lock_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned row_id_column_required;
    unsigned parameter_set_column_required;
    unsigned mode_column_required;
    unsigned test_type_column_required;
    unsigned function_column_required;
    unsigned source_url_column_required;
    unsigned sha256_digest_column_required;
    unsigned bundle_size_column_required;
    unsigned storage_path_column_required;
    unsigned license_review_column_required;
    unsigned schema_crosscheck_column_required;
    unsigned reviewer_identity_column_required;
    unsigned review_timestamp_column_required;
    unsigned ci_replay_transcript_column_required;
    unsigned tamper_evidence_column_required;
    unsigned planned_fixture_digest_rows_required;
    unsigned planned_fixture_digest_rows_reserved;
    unsigned ml_kem_512_row_class_reserved;
    unsigned ml_kem_768_row_class_reserved;
    unsigned ml_kem_1024_row_class_reserved;
    unsigned keygen_row_class_reserved;
    unsigned encaps_row_class_reserved;
    unsigned decaps_row_class_reserved;
    unsigned val_row_class_reserved;
    unsigned key_check_row_class_reserved;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned fixture_digest_rows_recorded;
    unsigned source_url_rows_recorded;
    unsigned sha256_digest_rows_recorded;
    unsigned bundle_size_rows_recorded;
    unsigned storage_path_rows_recorded;
    unsigned license_review_rows_recorded;
    unsigned schema_crosscheck_rows_recorded;
    unsigned reviewer_identity_rows_recorded;
    unsigned review_timestamp_rows_recorded;
    unsigned ci_replay_transcript_rows_recorded;
    unsigned tamper_evidence_rows_recorded;
    unsigned digest_row_template_reviewed;
    unsigned fixture_digest_row_acceptance_allowed;
    unsigned fixture_bundle_loaded;
    unsigned vector_execution_allowed;
    unsigned response_json_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_digest_row_template_items_total;
    unsigned required_digest_row_template_items_satisfied;
    char blocked_reason
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t;

const char *latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_label(
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *out);
int latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record);
int latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_allows_digest_row_acceptance(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
