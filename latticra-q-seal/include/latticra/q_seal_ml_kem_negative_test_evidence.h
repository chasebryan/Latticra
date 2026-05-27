#ifndef LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_H
#define LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_negative_test_evidence_error_t;

typedef struct {
    char evidence_profile[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_LABEL_MAX];
    char acvp_source[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_LABEL_MAX];
    char evidence_scope[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_LABEL_MAX];
    char evidence_state[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_STATE_MAX];
    unsigned negative_test_evidence_present;
    unsigned fips_203_source_verified;
    unsigned acvp_ml_kem_schema_tracked;
    unsigned vector_schema_bound;
    unsigned vector_source_bound;
    unsigned malformed_ciphertext_tests_required;
    unsigned malformed_key_tests_required;
    unsigned negative_replay_tests_required;
    unsigned length_validation_tests_recorded;
    unsigned encoding_canonicality_tests_recorded;
    unsigned invalid_ciphertext_tests_recorded;
    unsigned invalid_public_key_tests_recorded;
    unsigned invalid_secret_key_tests_recorded;
    unsigned decapsulation_failure_tests_recorded;
    unsigned implicit_rejection_tests_recorded;
    unsigned parser_rejection_tests_recorded;
    unsigned fuzzing_corpus_recorded;
    unsigned differential_negative_tests_recorded;
    unsigned implementation_binding_recorded;
    unsigned negative_tests_executed;
    unsigned parser_execution_allowed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_negative_test_items_total;
    unsigned required_negative_test_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_STATE_MAX];
    latticra_q_seal_ml_kem_negative_test_evidence_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_STATE_MAX];
} latticra_q_seal_ml_kem_negative_test_evidence_t;

const char *latticra_q_seal_ml_kem_negative_test_evidence_error_label(
    latticra_q_seal_ml_kem_negative_test_evidence_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_negative_test_evidence_prepare(
    latticra_q_seal_ml_kem_negative_test_evidence_t *out);
int latticra_q_seal_ml_kem_negative_test_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence);
int latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence);
latticra_q_seal_status_t latticra_q_seal_ml_kem_negative_test_evidence_report(
    const latticra_q_seal_ml_kem_negative_test_evidence_t *evidence,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
