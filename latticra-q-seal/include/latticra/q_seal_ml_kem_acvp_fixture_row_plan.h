#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_t;

typedef struct {
    char row_plan_profile[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_LABEL_MAX];
    char row_plan_scope[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_LABEL_MAX];
    char row_plan_state[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_STATE_MAX];
    unsigned acvp_fixture_row_plan_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned top_level_vector_set_fields_recorded;
    unsigned test_group_fields_recorded;
    unsigned test_case_fields_recorded;
    unsigned response_group_fields_recorded;
    unsigned response_case_fields_recorded;
    unsigned parameter_set_rows_total;
    unsigned parameter_set_rows_planned;
    unsigned keygen_aft_rows_required;
    unsigned keygen_aft_rows_planned;
    unsigned encapsulation_aft_rows_required;
    unsigned encapsulation_aft_rows_planned;
    unsigned decapsulation_val_rows_required;
    unsigned decapsulation_val_rows_planned;
    unsigned encapsulation_key_check_val_rows_required;
    unsigned encapsulation_key_check_val_rows_planned;
    unsigned decapsulation_key_check_val_rows_required;
    unsigned decapsulation_key_check_val_rows_planned;
    unsigned minimum_fixture_row_classes_required;
    unsigned minimum_fixture_row_classes_planned;
    unsigned fixture_row_ids_reserved;
    unsigned digest_columns_required;
    unsigned source_url_columns_required;
    unsigned license_review_columns_required;
    unsigned schema_crosscheck_columns_required;
    unsigned review_columns_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned acvp_registration_json_reviewed;
    unsigned capability_matrix_reviewed;
    unsigned fixture_row_plan_reviewed;
    unsigned fixture_digest_rows_recorded;
    unsigned fixture_source_digests_recorded;
    unsigned fixture_storage_paths_recorded;
    unsigned fixture_license_review_recorded;
    unsigned fixture_schema_crosscheck_recorded;
    unsigned fixture_import_reviewed;
    unsigned fixture_digest_ledger_reviewed;
    unsigned row_plan_to_digest_ledger_reviewed;
    unsigned fixture_bundle_loaded;
    unsigned vector_execution_allowed;
    unsigned response_json_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_fixture_row_plan_items_total;
    unsigned required_fixture_row_plan_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_fixture_row_plan_t;

const char *latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_label(
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *out);
int latticra_q_seal_ml_kem_acvp_fixture_row_plan_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan);
int latticra_q_seal_ml_kem_acvp_fixture_row_plan_allows_fixture_digest_rows(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
