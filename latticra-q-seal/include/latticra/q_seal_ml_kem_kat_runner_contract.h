#ifndef LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_H
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_kat_runner_contract_error_t;

typedef struct {
    char runner_profile[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_LABEL_MAX];
    char runner_scope[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_LABEL_MAX];
    char runner_state[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_STATE_MAX];
    unsigned kat_runner_contract_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned kat_manifest_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned kat_result_schema_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_bound;
    unsigned vector_fixture_lock_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned provider_differential_bound;
    unsigned replay_transcript_gate_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned deterministic_replay_policy_recorded;
    unsigned offline_fixture_policy_recorded;
    unsigned no_network_execution_required;
    unsigned no_dynamic_provider_loading_required;
    unsigned seed_material_handling_policy_recorded;
    unsigned positive_result_row_policy_recorded;
    unsigned negative_result_row_policy_recorded;
    unsigned malformed_result_row_policy_recorded;
    unsigned implicit_rejection_result_policy_recorded;
    unsigned parameter_set_coverage_required;
    unsigned operation_family_coverage_required;
    unsigned transcript_retention_policy_recorded;
    unsigned failure_triage_policy_recorded;
    unsigned no_embedded_vectors_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned kat_runner_implementation_present;
    unsigned fixture_bundle_loaded;
    unsigned fixture_bundle_digest_verified;
    unsigned fixture_bundle_license_reviewed;
    unsigned fixture_bundle_storage_reviewed;
    unsigned parser_reviewed_for_runner;
    unsigned result_schema_reviewed;
    unsigned positive_result_rows_recorded;
    unsigned negative_result_rows_recorded;
    unsigned malformed_result_rows_recorded;
    unsigned implicit_rejection_rows_recorded;
    unsigned provider_differential_rows_recorded;
    unsigned ci_kat_replay_transcript_recorded;
    unsigned operation_implementation_present;
    unsigned kat_execution_enabled;
    unsigned acvp_response_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_kat_runner_contract_items_total;
    unsigned required_kat_runner_contract_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_STATE_MAX];
    latticra_q_seal_ml_kem_kat_runner_contract_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_STATE_MAX];
} latticra_q_seal_ml_kem_kat_runner_contract_t;

const char *latticra_q_seal_ml_kem_kat_runner_contract_error_label(
    latticra_q_seal_ml_kem_kat_runner_contract_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_runner_contract_prepare(
    latticra_q_seal_ml_kem_kat_runner_contract_t *out);
int latticra_q_seal_ml_kem_kat_runner_contract_is_no_effect(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract);
int latticra_q_seal_ml_kem_kat_runner_contract_allows_runner_execution(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_runner_contract_report(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
