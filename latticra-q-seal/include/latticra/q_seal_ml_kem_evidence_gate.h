#ifndef LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PATH_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_STATE_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_evidence_gate_error_t;

typedef struct {
    char gate_profile[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX];
    char standards_publication_date[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX];
    char standards_errata_state[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX];
    char kat_manifest_path[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PATH_MAX];
    char acvp_vector_source[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_LABEL_MAX];
    unsigned ml_kem_evidence_gate_present;
    unsigned fips_203_source_verified;
    unsigned fips_203_errata_review_required;
    unsigned fips_203_errata_review_recorded;
    unsigned parameter_sets_recorded;
    unsigned ml_kem_512_parameters_recorded;
    unsigned ml_kem_768_parameters_recorded;
    unsigned ml_kem_1024_parameters_recorded;
    unsigned known_answer_test_manifest_present;
    unsigned known_answer_vectors_embedded;
    unsigned known_answer_vectors_loaded;
    unsigned known_answer_vectors_verified;
    unsigned acvp_vector_review_required;
    unsigned acvp_vector_review_recorded;
    unsigned clean_room_required;
    unsigned clean_room_implementation_review_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned provider_differential_test_contract_required;
    unsigned provider_differential_test_contract_recorded;
    unsigned provider_linked;
    unsigned constant_time_review_required;
    unsigned constant_time_review_recorded;
    unsigned side_channel_review_required;
    unsigned side_channel_review_recorded;
    unsigned randomness_source_contract_required;
    unsigned randomness_source_contract_recorded;
    unsigned intermediate_zeroization_contract_required;
    unsigned intermediate_zeroization_contract_recorded;
    unsigned memory_safety_review_required;
    unsigned memory_safety_review_recorded;
    unsigned api_misuse_resistance_review_required;
    unsigned api_misuse_resistance_review_recorded;
    unsigned fuzzing_and_negative_tests_required;
    unsigned fuzzing_and_negative_tests_recorded;
    unsigned ci_quality_gate_required;
    unsigned ci_quality_gate_recorded;
    unsigned required_evidence_items_total;
    unsigned required_evidence_items_satisfied;
    unsigned implementation_present;
    unsigned operations_enabled;
    unsigned key_generation_enabled;
    unsigned encapsulation_enabled;
    unsigned decapsulation_enabled;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    char gate_state[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_STATE_MAX];
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_STATE_MAX];
    latticra_q_seal_ml_kem_evidence_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_STATE_MAX];
} latticra_q_seal_ml_kem_evidence_gate_t;

const char *latticra_q_seal_ml_kem_evidence_gate_error_label(
    latticra_q_seal_ml_kem_evidence_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_gate_prepare(
    latticra_q_seal_ml_kem_evidence_gate_t *out);
int latticra_q_seal_ml_kem_evidence_gate_is_fail_closed(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate);
int latticra_q_seal_ml_kem_evidence_gate_allows_operations(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_gate_report(
    const latticra_q_seal_ml_kem_evidence_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
