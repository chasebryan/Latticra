#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_response_fixture_error_t;

typedef struct {
    char response_fixture_profile
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_LABEL_MAX];
    char response_fixture_scope
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_LABEL_MAX];
    char response_fixture_state
        [LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_STATE_MAX];
    unsigned acvp_response_fixture_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned acvp_intake_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned kat_result_schema_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned vector_schema_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned response_fixture_policy_recorded;
    unsigned response_envelope_policy_recorded;
    unsigned acv_version_echo_required;
    unsigned vsid_echo_required;
    unsigned tgid_tcid_mapping_required;
    unsigned deterministic_ordering_required;
    unsigned keygen_response_fixture_required;
    unsigned encapsulation_response_fixture_required;
    unsigned decapsulation_response_fixture_required;
    unsigned key_check_response_fixture_required;
    unsigned canonical_hex_output_required;
    unsigned boolean_output_policy_recorded;
    unsigned no_secret_material_logging_required;
    unsigned no_network_submission_required;
    unsigned no_dynamic_code_loading_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned response_fixture_reviewed;
    unsigned fixture_bundle_digest_bound;
    unsigned parser_output_accepted;
    unsigned vector_execution_evidence_recorded;
    unsigned keygen_response_fixture_recorded;
    unsigned encapsulation_response_fixture_recorded;
    unsigned decapsulation_response_fixture_recorded;
    unsigned key_check_response_fixture_recorded;
    unsigned negative_response_fixture_recorded;
    unsigned response_schema_reviewed;
    unsigned response_security_reviewed;
    unsigned response_ci_replay_recorded;
    unsigned response_output_accepted;
    unsigned acvp_response_generation_evidence_recorded;
    unsigned response_json_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_response_fixture_items_total;
    unsigned required_response_fixture_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_response_fixture_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_response_fixture_t;

const char *latticra_q_seal_ml_kem_acvp_response_fixture_error_label(
    latticra_q_seal_ml_kem_acvp_response_fixture_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_fixture_prepare(
    latticra_q_seal_ml_kem_acvp_response_fixture_t *out);
int latticra_q_seal_ml_kem_acvp_response_fixture_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture);
int latticra_q_seal_ml_kem_acvp_response_fixture_allows_response_output(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_fixture_report(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
