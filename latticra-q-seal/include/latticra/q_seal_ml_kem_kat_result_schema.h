#ifndef LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_H
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_kat_result_schema_error_t;

typedef struct {
    char result_schema_profile[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_LABEL_MAX];
    char result_scope[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_LABEL_MAX];
    char schema_state[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_STATE_MAX];
    unsigned kat_result_schema_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned kat_manifest_bound;
    unsigned kat_runner_contract_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned vector_schema_bound;
    unsigned vector_fixture_lock_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned provider_differential_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned deterministic_result_ordering_required;
    unsigned result_envelope_policy_recorded;
    unsigned fixture_digest_reference_required;
    unsigned vector_family_reference_required;
    unsigned parameter_set_field_required;
    unsigned operation_family_field_required;
    unsigned test_type_field_required;
    unsigned tgid_tcid_mapping_required;
    unsigned expected_result_field_required;
    unsigned observed_result_field_required;
    unsigned pass_fail_field_required;
    unsigned failure_reason_field_required;
    unsigned implicit_rejection_result_required;
    unsigned provider_differential_field_required;
    unsigned transcript_digest_field_required;
    unsigned no_secret_material_logging_required;
    unsigned no_network_submission_required;
    unsigned no_dynamic_provider_loading_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned result_schema_reviewed;
    unsigned fixture_bundle_digest_bound;
    unsigned result_row_fixture_recorded;
    unsigned positive_result_rows_recorded;
    unsigned negative_result_rows_recorded;
    unsigned malformed_result_rows_recorded;
    unsigned implicit_rejection_rows_recorded;
    unsigned provider_differential_rows_recorded;
    unsigned ci_kat_replay_transcript_bound;
    unsigned kat_runner_execution_recorded;
    unsigned acvp_response_generation_evidence_recorded;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_kat_result_schema_items_total;
    unsigned required_kat_result_schema_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_STATE_MAX];
    latticra_q_seal_ml_kem_kat_result_schema_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_STATE_MAX];
} latticra_q_seal_ml_kem_kat_result_schema_t;

const char *latticra_q_seal_ml_kem_kat_result_schema_error_label(
    latticra_q_seal_ml_kem_kat_result_schema_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_schema_prepare(
    latticra_q_seal_ml_kem_kat_result_schema_t *out);
int latticra_q_seal_ml_kem_kat_result_schema_is_no_effect(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema);
int latticra_q_seal_ml_kem_kat_result_schema_allows_result_recording(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_schema_report(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
