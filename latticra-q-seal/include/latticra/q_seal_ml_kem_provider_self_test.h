#ifndef LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_H
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_LABEL_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_STATE_MAX 128u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_REPORT_MAX 4096u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES 32u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_MAX_CIPHERTEXT_BYTES 1568u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_INVALID_PARAMETER_SET = 1,
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE = 2,
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE = 3
} latticra_q_seal_ml_kem_provider_self_test_error_t;

typedef struct {
    char self_test_profile[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_LABEL_MAX];
    char provider_name[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_LABEL_MAX];
    char algorithm_name[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_LABEL_MAX];
    unsigned parameter_set;
    unsigned security_category;
    unsigned expected_ciphertext_bytes;
    unsigned observed_ciphertext_bytes;
    unsigned expected_shared_secret_bytes;
    unsigned encapsulated_shared_secret_bytes;
    unsigned decapsulated_shared_secret_bytes;
    unsigned provider_linked;
    unsigned provider_available;
    unsigned provider_runtime_used;
    unsigned key_generation_performed;
    unsigned keypair_algorithm_identity_verified;
    unsigned public_key_reimported;
    unsigned public_key_algorithm_identity_verified;
    unsigned public_key_bytes;
    unsigned encapsulation_performed;
    unsigned encapsulation_public_key_only;
    unsigned decapsulation_performed;
    unsigned tampered_ciphertext_decapsulation_performed;
    unsigned tampered_ciphertext_shared_secret_mismatch;
    unsigned tampered_ciphertext_rejected;
    unsigned malformed_ciphertext_length_decapsulation_rejected;
    unsigned malformed_ciphertext_length_no_secret_output;
    unsigned shared_secret_internal_buffers_used;
    unsigned shared_secret_match;
    unsigned shared_secret_constant_time_compare;
    unsigned tampered_ciphertext_constant_time_compare;
    unsigned shared_secret_zeroized;
    unsigned ciphertext_zeroized;
    unsigned shared_secret_output_emitted;
    unsigned ciphertext_output_emitted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    char operation_state[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_STATE_MAX];
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_STATE_MAX];
    latticra_q_seal_ml_kem_provider_self_test_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_STATE_MAX];
} latticra_q_seal_ml_kem_provider_self_test_t;

const char *latticra_q_seal_ml_kem_provider_self_test_error_label(
    latticra_q_seal_ml_kem_provider_self_test_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_self_test_run(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    latticra_q_seal_ml_kem_provider_self_test_t *out);
int latticra_q_seal_ml_kem_provider_self_test_is_authority_neutral(
    const latticra_q_seal_ml_kem_provider_self_test_t *self_test);
latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_self_test_report(
    const latticra_q_seal_ml_kem_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
