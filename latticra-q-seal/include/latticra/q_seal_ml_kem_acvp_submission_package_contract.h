#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_submission_package_error_t;

typedef struct {
    char submission_package_profile
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_LABEL_MAX];
    char submission_package_scope
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_LABEL_MAX];
    char submission_package_state
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_STATE_MAX];
    unsigned acvp_submission_package_contract_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned acvp_intake_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned acvp_response_fixture_bound;
    unsigned kat_result_schema_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned vector_schema_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned submission_package_policy_recorded;
    unsigned offline_package_manifest_required;
    unsigned algorithm_registration_required;
    unsigned acvp_session_metadata_required;
    unsigned vsid_tgid_tcid_traceability_required;
    unsigned request_bundle_digest_required;
    unsigned response_bundle_digest_required;
    unsigned canonical_response_json_required;
    unsigned local_replay_transcript_required;
    unsigned no_secret_material_logging_required;
    unsigned no_network_submission_required;
    unsigned no_dynamic_code_loading_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned submission_package_reviewed;
    unsigned request_bundle_digest_bound;
    unsigned response_bundle_digest_bound;
    unsigned vector_execution_evidence_recorded;
    unsigned response_output_accepted;
    unsigned local_replay_transcript_recorded;
    unsigned acvp_client_boundary_reviewed;
    unsigned submission_receipt_recorded;
    unsigned validation_server_acceptance_recorded;
    unsigned acvp_submission_package_accepted;
    unsigned acvp_response_acceptance_recorded;
    unsigned response_json_generation_enabled;
    unsigned network_session_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_submission_package_items_total;
    unsigned required_submission_package_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_submission_package_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_submission_package_contract_t;

const char *latticra_q_seal_ml_kem_acvp_submission_package_error_label(
    latticra_q_seal_ml_kem_acvp_submission_package_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(
    latticra_q_seal_ml_kem_acvp_submission_package_contract_t *out);
int latticra_q_seal_ml_kem_acvp_submission_package_contract_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract);
int
latticra_q_seal_ml_kem_acvp_submission_package_contract_allows_package_acceptance(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
