#ifndef LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_H
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_H

#include "latticra/seal_hybrid_envelope.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROFILE_MAX 96u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX 128u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_STATE_MAX 128u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_REPORT_MAX 4096u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_RECORD_MAX 512u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_512_CIPHERTEXT_BYTES 768u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_768_CIPHERTEXT_BYTES 1088u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_1024_CIPHERTEXT_BYTES 1568u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_MAX_ML_KEM_CIPHERTEXT_BYTES \
    LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_1024_CIPHERTEXT_BYTES

typedef enum {
    LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_OK = 0,
    LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE = 1,
    LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE = 2,
    LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE = 3
} latticra_seal_hybrid_provider_self_test_error_t;

typedef struct {
    char self_test_profile[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROFILE_MAX];
    char formal_title[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char classical_provider_name[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char pqc_provider_name[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char classical_algorithm_name[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char pqc_algorithm_name[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char envelope_algorithm_name[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    char standards_source[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_LABEL_MAX];
    unsigned provider_linked;
    unsigned classical_provider_available;
    unsigned pqc_provider_available;
    unsigned provider_runtime_used;
    unsigned p256_key_generation_performed;
    unsigned p256_ecdh_derive_performed;
    unsigned p256_shared_secret_match;
    unsigned p256_shared_secret_bytes;
    unsigned ml_kem_key_generation_performed;
    unsigned ml_kem_encapsulation_performed;
    unsigned ml_kem_decapsulation_performed;
    unsigned ml_kem_shared_secret_match;
    unsigned ml_kem_shared_secret_bytes;
    unsigned ml_kem_parameter_sets_tested;
    unsigned ml_kem_512_key_generation_performed;
    unsigned ml_kem_512_encapsulation_performed;
    unsigned ml_kem_512_decapsulation_performed;
    unsigned ml_kem_512_shared_secret_match;
    unsigned ml_kem_512_ciphertext_bytes;
    unsigned ml_kem_512_hybrid_envelope_authenticated;
    unsigned ml_kem_768_key_generation_performed;
    unsigned ml_kem_768_encapsulation_performed;
    unsigned ml_kem_768_decapsulation_performed;
    unsigned ml_kem_768_shared_secret_match;
    unsigned ml_kem_768_ciphertext_bytes;
    unsigned ml_kem_768_hybrid_envelope_authenticated;
    unsigned ml_kem_1024_key_generation_performed;
    unsigned ml_kem_1024_encapsulation_performed;
    unsigned ml_kem_1024_decapsulation_performed;
    unsigned ml_kem_1024_shared_secret_match;
    unsigned ml_kem_1024_ciphertext_bytes;
    unsigned ml_kem_1024_hybrid_envelope_authenticated;
    unsigned hybrid_envelope_record_sealed;
    unsigned hybrid_envelope_record_opened;
    unsigned hybrid_envelope_authenticated;
    unsigned hybrid_envelope_plaintext_recovered;
    unsigned hybrid_envelope_records_sealed_total;
    unsigned hybrid_envelope_records_opened_total;
    unsigned hybrid_envelope_records_authenticated_total;
    unsigned hybrid_transcript_aad_bound;
    unsigned hybrid_transcript_aad_size_bytes;
    unsigned hybrid_transcript_cases_bound_total;
    unsigned hybrid_transcript_tampering_rejected;
    unsigned hybrid_transcript_tampering_rejected_total;
    unsigned provider_algorithm_transcript_bound;
    unsigned p256_public_key_transcript_bound;
    unsigned p256_public_key_transcript_bytes;
    unsigned ml_kem_ciphertext_transcript_bound;
    unsigned ml_kem_ciphertext_transcript_bytes_total;
    unsigned classical_secret_internal_buffers_used;
    unsigned pqc_secret_internal_buffers_used;
    unsigned secret_material_output_emitted;
    unsigned record_output_emitted;
    unsigned plaintext_output_emitted;
    unsigned classical_secret_zeroized;
    unsigned pqc_secret_zeroized;
    unsigned record_buffer_zeroized;
    unsigned plaintext_buffer_zeroized;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    char operation_state[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_STATE_MAX];
    char blocked_reason[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_STATE_MAX];
    latticra_seal_hybrid_provider_self_test_error_t error;
    char status[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_STATE_MAX];
} latticra_seal_hybrid_provider_self_test_t;

const char *latticra_seal_hybrid_provider_self_test_error_label(
    latticra_seal_hybrid_provider_self_test_error_t error);
latticra_status_t latticra_seal_hybrid_provider_self_test_run(
    latticra_seal_hybrid_provider_self_test_t *out);
int latticra_seal_hybrid_provider_self_test_is_authority_neutral(
    const latticra_seal_hybrid_provider_self_test_t *self_test);
latticra_status_t latticra_seal_hybrid_provider_self_test_report(
    const latticra_seal_hybrid_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
