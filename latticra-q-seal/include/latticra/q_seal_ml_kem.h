#ifndef LATTICRA_Q_SEAL_ML_KEM_H
#define LATTICRA_Q_SEAL_ML_KEM_H

#include "latticra/q_seal.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_PROFILE_MAX 64u
#define LATTICRA_Q_SEAL_ML_KEM_LABEL_MAX 64u
#define LATTICRA_Q_SEAL_ML_KEM_STATE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_REPORT_MAX 4096u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512 = 512,
    LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768 = 768,
    LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024 = 1024
} latticra_q_seal_ml_kem_parameter_set_t;

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET = 1,
    LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED = 2
} latticra_q_seal_ml_kem_error_t;

typedef struct {
    char ml_kem_profile[LATTICRA_Q_SEAL_ML_KEM_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_LABEL_MAX];
    char parameter_set_name[LATTICRA_Q_SEAL_ML_KEM_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_LABEL_MAX];
    unsigned parameter_set;
    unsigned security_category;
    unsigned n;
    unsigned q;
    unsigned k;
    unsigned eta1;
    unsigned eta2;
    unsigned du;
    unsigned dv;
    unsigned required_rbg_strength_bits;
    unsigned encapsulation_key_bytes;
    unsigned decapsulation_key_bytes;
    unsigned ciphertext_bytes;
    unsigned shared_secret_key_bytes;
    unsigned fips_203_parameter_set_tracked;
    unsigned known_answer_tests_required;
    unsigned acvp_vector_review_required;
    unsigned clean_room_required;
    unsigned apple_corecrypto_code_copied;
    unsigned provider_linked;
    unsigned key_generation_enabled;
    unsigned encapsulation_enabled;
    unsigned decapsulation_enabled;
    unsigned key_generation_performed;
    unsigned encapsulation_performed;
    unsigned decapsulation_performed;
    unsigned shared_secret_emitted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    char operation_state[LATTICRA_Q_SEAL_ML_KEM_STATE_MAX];
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_STATE_MAX];
    latticra_q_seal_ml_kem_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_STATE_MAX];
} latticra_q_seal_ml_kem_parameters_t;

const char *latticra_q_seal_ml_kem_error_label(
    latticra_q_seal_ml_kem_error_t error);
const char *latticra_q_seal_ml_kem_parameter_set_label(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set);
latticra_q_seal_status_t latticra_q_seal_ml_kem_parameters(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    latticra_q_seal_ml_kem_parameters_t *out);
int latticra_q_seal_ml_kem_parameters_are_authority_neutral(
    const latticra_q_seal_ml_kem_parameters_t *parameters);
latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_keygen_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters);
latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_encaps_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters);
latticra_q_seal_ml_kem_error_t latticra_q_seal_ml_kem_decaps_disabled(
    const latticra_q_seal_ml_kem_parameters_t *parameters);
latticra_q_seal_status_t latticra_q_seal_ml_kem_parameters_report(
    const latticra_q_seal_ml_kem_parameters_t *parameters,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
