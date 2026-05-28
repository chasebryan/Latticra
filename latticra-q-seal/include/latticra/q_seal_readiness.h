#ifndef LATTICRA_Q_SEAL_READINESS_H
#define LATTICRA_Q_SEAL_READINESS_H

#include "latticra/q_seal.h"
#include "latticra/q_seal_ml_kem.h"
#include "latticra/q_seal_ml_kem_acvp_capability_matrix.h"
#include "latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h"
#include "latticra/q_seal_ml_kem_acvp_fixture_row_plan.h"
#include "latticra/q_seal_ml_kem_acvp_intake.h"
#include "latticra/q_seal_ml_kem_acvp_parser_contract.h"
#include "latticra/q_seal_ml_kem_acvp_response_contract.h"
#include "latticra/q_seal_ml_kem_acvp_response_fixture.h"
#include "latticra/q_seal_ml_kem_acvp_submission_package_contract.h"
#include "latticra/q_seal_ml_kem_acvp_verdict_receipt_gate.h"
#include "latticra/q_seal_ml_kem_api_misuse_resistance.h"
#include "latticra/q_seal_ml_kem_ci_promotion_evidence.h"
#include "latticra/q_seal_ml_kem_code_owner_review.h"
#include "latticra/q_seal_ml_kem_constant_time_review.h"
#include "latticra/q_seal_ml_kem_clean_room_author_attestation_gate.h"
#include "latticra/q_seal_ml_kem_evidence_gate.h"
#include "latticra/q_seal_ml_kem_fips_conformance_matrix.h"
#include "latticra/q_seal_ml_kem_implementation_binding_manifest.h"
#include "latticra/q_seal_ml_kem_implementation_file_digest_plan.h"
#include "latticra/q_seal_ml_kem_implementation_frame.h"
#include "latticra/q_seal_ml_kem_implementation_traceability_matrix.h"
#include "latticra/q_seal_ml_kem_kat_manifest.h"
#include "latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h"
#include "latticra/q_seal_ml_kem_kat_result_row_fixture.h"
#include "latticra/q_seal_ml_kem_kat_result_schema.h"
#include "latticra/q_seal_ml_kem_kat_runner_contract.h"
#include "latticra/q_seal_ml_kem_memory_safety_evidence.h"
#include "latticra/q_seal_ml_kem_module_boundary_gate.h"
#include "latticra/q_seal_ml_kem_negative_test_evidence.h"
#include "latticra/q_seal_ml_kem_per_file_standards_trace_gate.h"
#include "latticra/q_seal_ml_kem_per_file_test_trace_gate.h"
#include "latticra/q_seal_ml_kem_primitive_source_acceptance_gate.h"
#include "latticra/q_seal_ml_kem_provider_differential.h"
#include "latticra/q_seal_ml_kem_randomness_source.h"
#include "latticra/q_seal_ml_kem_receipt_replay_results.h"
#include "latticra/q_seal_ml_kem_review_disposition_ledger.h"
#include "latticra/q_seal_ml_kem_reviewer_identity_fixture.h"
#include "latticra/q_seal_ml_kem_reviewer_role_mapping.h"
#include "latticra/q_seal_ml_kem_secret_state_contract.h"
#include "latticra/q_seal_ml_kem_side_channel_review.h"
#include "latticra/q_seal_ml_kem_source_digest_manifest.h"
#include "latticra/q_seal_ml_kem_source_digest_receipt.h"
#include "latticra/q_seal_ml_kem_source_digest_verification.h"
#include "latticra/q_seal_ml_kem_source_layout_gate.h"
#include "latticra/q_seal_ml_kem_sp800_227_usage_profile.h"
#include "latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h"
#include "latticra/q_seal_ml_kem_vector_fixture_lock.h"
#include "latticra/q_seal_ml_kem_vector_schema.h"
#include "latticra/q_seal_ml_kem_vector_source.h"
#include "latticra/q_seal_ml_kem_validation_claim_gate.h"
#include "latticra/q_seal_ml_kem_zeroization_evidence.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_READINESS_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_READINESS_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_READINESS_STATE_MAX 192u
#define LATTICRA_Q_SEAL_READINESS_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_READINESS_OK = 0,
    LATTICRA_Q_SEAL_READINESS_BLOCKED = 1,
    LATTICRA_Q_SEAL_READINESS_INVALID_INPUT = 2
} latticra_q_seal_readiness_error_t;

typedef struct {
    char readiness_profile[LATTICRA_Q_SEAL_READINESS_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_READINESS_LABEL_MAX];
    char subsystem_path[LATTICRA_Q_SEAL_READINESS_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_READINESS_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_READINESS_LABEL_MAX];
    char readiness_state[LATTICRA_Q_SEAL_READINESS_STATE_MAX];
    unsigned readiness_profile_present;
    unsigned foundation_present;
    unsigned ml_kem_parameters_present;
    unsigned ml_kem_512_parameters_present;
    unsigned ml_kem_768_parameters_present;
    unsigned ml_kem_1024_parameters_present;
    unsigned evidence_gate_present;
    unsigned fips_conformance_matrix_present;
    unsigned sp800_227_usage_profile_present;
    unsigned kat_manifest_present;
    unsigned kat_runner_contract_present;
    unsigned replay_transcript_gate_present;
    unsigned kat_result_schema_present;
    unsigned kat_result_row_fixture_present;
    unsigned acvp_intake_present;
    unsigned acvp_capability_matrix_present;
    unsigned acvp_fixture_row_plan_present;
    unsigned acvp_fixture_digest_row_template_present;
    unsigned acvp_parser_contract_present;
    unsigned acvp_response_contract_present;
    unsigned acvp_response_fixture_present;
    unsigned acvp_submission_package_contract_present;
    unsigned acvp_verdict_receipt_gate_present;
    unsigned vector_schema_present;
    unsigned vector_source_intake_present;
    unsigned vector_fixture_lock_present;
    unsigned vector_fixture_digest_ledger_present;
    unsigned negative_test_evidence_present;
    unsigned memory_safety_evidence_present;
    unsigned api_misuse_resistance_present;
    unsigned source_digest_manifest_present;
    unsigned source_digest_receipt_present;
    unsigned source_digest_verification_present;
    unsigned receipt_replay_results_present;
    unsigned code_owner_review_present;
    unsigned review_disposition_ledger_present;
    unsigned reviewer_identity_fixture_present;
    unsigned reviewer_role_mapping_present;
    unsigned ci_promotion_evidence_present;
    unsigned validation_claim_gate_present;
    unsigned module_boundary_gate_present;
    unsigned constant_time_review_present;
    unsigned randomness_source_contract_present;
    unsigned zeroization_evidence_present;
    unsigned side_channel_review_present;
    unsigned provider_differential_present;
    unsigned implementation_binding_manifest_present;
    unsigned source_layout_gate_present;
    unsigned implementation_file_digest_plan_present;
    unsigned clean_room_author_attestation_gate_present;
    unsigned per_file_standards_trace_gate_present;
    unsigned per_file_test_trace_gate_present;
    unsigned implementation_traceability_matrix_present;
    unsigned primitive_source_acceptance_gate_present;
    unsigned implementation_frame_present;
    unsigned secret_state_contract_present;
    unsigned clean_room_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned provider_runtime_used;
    unsigned components_total;
    unsigned components_present;
    unsigned runtime_blockers_total;
    unsigned required_readiness_items_total;
    unsigned required_readiness_items_satisfied;
    unsigned design_frame_integration_ready;
    unsigned runtime_crypto_ready;
    unsigned operations_enabled;
    unsigned key_generation_enabled;
    unsigned encapsulation_enabled;
    unsigned decapsulation_enabled;
    unsigned shared_secret_emitted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned post_quantum_migration_claim_allowed;
    unsigned runtime_authority_granted;
    char blocked_reason[LATTICRA_Q_SEAL_READINESS_STATE_MAX];
    latticra_q_seal_readiness_error_t error;
    char status[LATTICRA_Q_SEAL_READINESS_STATE_MAX];
} latticra_q_seal_readiness_t;

const char *latticra_q_seal_readiness_error_label(
    latticra_q_seal_readiness_error_t error);
latticra_q_seal_status_t latticra_q_seal_readiness_prepare(
    latticra_q_seal_readiness_t *out);
int latticra_q_seal_readiness_is_design_frame_ready(
    const latticra_q_seal_readiness_t *readiness);
int latticra_q_seal_readiness_allows_runtime_crypto(
    const latticra_q_seal_readiness_t *readiness);
latticra_q_seal_status_t latticra_q_seal_readiness_report(
    const latticra_q_seal_readiness_t *readiness,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
