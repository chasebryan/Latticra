#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_parser_contract_error_t;

typedef struct {
    char parser_profile[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_LABEL_MAX];
    char parser_scope[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_LABEL_MAX];
    char parser_state[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_STATE_MAX];
    unsigned acvp_parser_contract_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned acvp_intake_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_intake_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned vector_set_fields_policy_recorded;
    unsigned test_group_fields_policy_recorded;
    unsigned test_case_fields_policy_recorded;
    unsigned response_fields_policy_recorded;
    unsigned parameter_set_allowlist_required;
    unsigned mode_allowlist_required;
    unsigned test_type_allowlist_required;
    unsigned function_allowlist_required;
    unsigned hex_string_decoder_policy_recorded;
    unsigned integer_range_policy_recorded;
    unsigned max_input_size_policy_recorded;
    unsigned max_nesting_depth_policy_recorded;
    unsigned duplicate_key_rejection_required;
    unsigned unknown_field_rejection_policy_recorded;
    unsigned malformed_json_rejection_required;
    unsigned canonical_output_mapping_required;
    unsigned no_dynamic_code_loading_required;
    unsigned no_network_fetch_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned parser_implementation_present;
    unsigned parser_negative_tests_recorded;
    unsigned parser_fuzzing_recorded;
    unsigned parser_schema_reviewed;
    unsigned parser_security_reviewed;
    unsigned parser_ci_replay_recorded;
    unsigned fixture_digest_rows_recorded;
    unsigned fixture_import_reviewed;
    unsigned parser_output_accepted;
    unsigned vector_execution_allowed;
    unsigned response_json_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_parser_contract_items_total;
    unsigned required_parser_contract_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_parser_contract_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_parser_contract_t;

const char *latticra_q_seal_ml_kem_acvp_parser_contract_error_label(
    latticra_q_seal_ml_kem_acvp_parser_contract_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_parser_contract_prepare(
    latticra_q_seal_ml_kem_acvp_parser_contract_t *out);
int latticra_q_seal_ml_kem_acvp_parser_contract_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract);
int latticra_q_seal_ml_kem_acvp_parser_contract_allows_vector_parser(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_parser_contract_report(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
