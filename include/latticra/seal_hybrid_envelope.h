#ifndef LATTICRA_SEAL_HYBRID_ENVELOPE_H
#define LATTICRA_SEAL_HYBRID_ENVELOPE_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_HYBRID_ENVELOPE_PROFILE_MAX 64u
#define LATTICRA_SEAL_HYBRID_ENVELOPE_ALGORITHM_MAX 64u
#define LATTICRA_SEAL_HYBRID_ENVELOPE_STANDARDS_MAX 160u
#define LATTICRA_SEAL_HYBRID_ENVELOPE_STATE_MAX 96u
#define LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX 12288u
#define LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES 32u
#define LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES 32u
#define LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES 32u
#define LATTICRA_SEAL_HYBRID_SALT_BYTES 32u
#define LATTICRA_SEAL_HYBRID_NONCE_BYTES 12u
#define LATTICRA_SEAL_HYBRID_TAG_BYTES 16u
#define LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES 32u
#define LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES 32u
#define LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES 8u
#define LATTICRA_SEAL_HYBRID_RECORD_VERSION 1u
#define LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES 80u
#define LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES 64u
#define LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_BYTES 8u
#define LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES 8u
#define LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES \
    (LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_BYTES + \
     LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES)
#define LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS 256u
#define LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_BYTES 8u
#define LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES 8u
#define LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES \
    (LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_BYTES + \
     LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES + \
     LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES)
#define LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT 1u
#define LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE 2u
#define LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED 1u
#define LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD 2u
#define LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM 1u
#define LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM 1u
#define LATTICRA_SEAL_HYBRID_MESSAGE_MAX 1048576u
#define LATTICRA_SEAL_HYBRID_REUSE_GUARD_CAPACITY 64u

typedef enum {
    LATTICRA_SEAL_HYBRID_ENVELOPE_OK = 0,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT = 1,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET = 2,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_CLASSICAL_SHARED_SECRET_SIZE = 3,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_PQC_SHARED_SECRET = 4,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_PQC_SHARED_SECRET_SIZE = 5,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_SALT = 6,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_SALT_SIZE = 7,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_NONCE = 8,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_NONCE_SIZE = 9,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT = 10,
    LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL = 11,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG = 12,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE = 13,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE = 14,
    LATTICRA_SEAL_HYBRID_ENVELOPE_RANDOM_FAILURE = 15,
    LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE = 16,
    LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE = 17,
    LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE = 18,
    LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED = 19,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD = 20,
    LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET = 21,
    LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET = 22,
    LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT = 23,
    LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE = 24,
    LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_COMMITMENT = 25,
    LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE = 26,
    LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET = 27,
    LATTICRA_SEAL_HYBRID_ENVELOPE_REUSED_SALT_NONCE = 28
} latticra_seal_hybrid_envelope_error_t;

typedef struct {
    unsigned initialized;
    unsigned entries_used;
    unsigned next_entry;
    unsigned suite_ids[LATTICRA_SEAL_HYBRID_REUSE_GUARD_CAPACITY];
    unsigned kdf_domains[LATTICRA_SEAL_HYBRID_REUSE_GUARD_CAPACITY];
    unsigned char salts[LATTICRA_SEAL_HYBRID_REUSE_GUARD_CAPACITY]
        [LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char nonces[LATTICRA_SEAL_HYBRID_REUSE_GUARD_CAPACITY]
        [LATTICRA_SEAL_HYBRID_NONCE_BYTES];
} latticra_seal_hybrid_envelope_reuse_guard_t;

typedef struct {
    const unsigned char *classical_shared_secret;
    size_t classical_shared_secret_len;
    const unsigned char *pqc_shared_secret;
    size_t pqc_shared_secret_len;
    const unsigned char *salt;
    size_t salt_len;
    const unsigned char *nonce;
    size_t nonce_len;
    const unsigned char *aad;
    size_t aad_len;
} latticra_seal_hybrid_envelope_context_t;

typedef struct {
    char envelope_profile[LATTICRA_SEAL_HYBRID_ENVELOPE_PROFILE_MAX];
    char kdf_algorithm[LATTICRA_SEAL_HYBRID_ENVELOPE_ALGORITHM_MAX];
    char aead_algorithm[LATTICRA_SEAL_HYBRID_ENVELOPE_ALGORITHM_MAX];
    char standards_source[LATTICRA_SEAL_HYBRID_ENVELOPE_STANDARDS_MAX];
    size_t classical_shared_secret_size_bytes;
    size_t pqc_shared_secret_size_bytes;
    size_t salt_size_bytes;
    size_t nonce_size_bytes;
    size_t aad_size_bytes;
    size_t caller_aad_size_bytes;
    size_t detached_aad_size_bytes;
    size_t record_aad_size_bytes;
    size_t plaintext_size_bytes;
    size_t ciphertext_size_bytes;
    size_t tag_size_bytes;
    size_t detached_commitment_size_bytes;
    size_t record_header_size_bytes;
    size_t record_protected_header_size_bytes;
    size_t record_commitment_size_bytes;
    size_t record_size_bytes;
    unsigned detached_suite_id;
    unsigned detached_suite_kdf_bound;
    unsigned detached_key_commitment_present;
    unsigned detached_commitment_key_kdf_bound;
    unsigned detached_commitment_verified;
    unsigned detached_commitment_checked_before_decrypt;
    unsigned detached_commitment_caller_aad_bound;
    unsigned detached_commitment_input_streamed;
    unsigned detached_commitment_constant_time_compare;
    unsigned detached_commitment_tampering_rejected;
    unsigned record_suite_id;
    unsigned record_suite_authenticated;
    unsigned record_kdf_domain_authenticated;
    unsigned record_suite_kdf_bound;
    unsigned record_salt_nonce_nonzero;
    unsigned record_header_shape_validated;
    unsigned malformed_record_rejected;
    unsigned record_key_commitment_present;
    unsigned record_commitment_key_kdf_bound;
    unsigned record_commitment_verified;
    unsigned record_commitment_checked_before_decrypt;
    unsigned record_commitment_caller_aad_bound;
    unsigned record_commitment_input_streamed;
    unsigned record_commitment_constant_time_compare;
    unsigned record_commitment_tampering_rejected;
    unsigned commitment_mac_provider_api_used;
    unsigned commitment_mac_provider_fetched;
    unsigned commitment_mac_hmac_sha256_digest_bound;
    unsigned commitment_mac_256bit_key_used;
    unsigned commitment_mac_input_streamed;
    unsigned commitment_mac_legacy_fallback_used;
    unsigned detached_aad_framed;
    unsigned detached_aad_label_authenticated;
    unsigned detached_caller_aad_length_authenticated;
    unsigned detached_caller_aad_authenticated;
    unsigned record_aad_framed;
    unsigned record_aad_label_authenticated;
    unsigned record_caller_aad_authenticated;
    unsigned hybrid_classical_pqc_secret_required;
    unsigned classical_shared_secret_bound;
    unsigned pqc_shared_secret_bound;
    unsigned hybrid_secret_length_framed;
    unsigned hybrid_secret_role_labeled;
    unsigned hybrid_secret_algorithm_labeled;
    unsigned hybrid_secret_order_bound;
    unsigned hybrid_secret_components_distinct;
    unsigned duplicate_hybrid_shared_secret_rejected;
    unsigned classical_shared_secret_nonzero;
    unsigned pqc_shared_secret_nonzero;
    unsigned salt_nonzero;
    unsigned nonce_nonzero;
    unsigned aead_nonce_uniqueness_required;
    unsigned salt_bound_to_hkdf;
    unsigned nonce_bound_to_aead;
    unsigned generated_key_nonce_pair_csprng_backed;
    unsigned caller_salt_nonce_reuse_guard_required;
    unsigned caller_salt_nonce_reuse_tracking_present;
    unsigned caller_salt_nonce_reuse_guard_capacity;
    unsigned caller_salt_nonce_reuse_guard_entries_used;
    unsigned caller_salt_nonce_reuse_tracked;
    unsigned caller_salt_nonce_reuse_rejected;
    unsigned weak_shared_secret_rejected;
    unsigned weak_salt_rejected;
    unsigned weak_nonce_rejected;
    unsigned record_format_present;
    unsigned record_version;
    unsigned record_header_authenticated;
    unsigned hkdf_extract_expand_performed;
    unsigned hkdf_provider_api_used;
    unsigned hkdf_extract_expand_standard_api_used;
    unsigned hkdf_sha256_digest_bound;
    unsigned hkdf_manual_fallback_used;
    unsigned aes_gcm_provider_api_used;
    unsigned aes_gcm_provider_cipher_fetched;
    unsigned aes_gcm_96bit_nonce_configured;
    unsigned aes_gcm_128bit_tag_bound;
    unsigned aes_gcm_static_cipher_fallback_used;
    unsigned aes_gcm_encryption_performed;
    unsigned aes_gcm_decryption_performed;
    unsigned authentication_tag_verified;
    unsigned unauthenticated_plaintext_staged;
    unsigned staged_plaintext_cleared;
    unsigned plaintext_released_after_authentication;
    unsigned attached_record_sealed;
    unsigned attached_record_opened;
    unsigned attached_record_authenticated;
    unsigned kdf_domain_separated;
    unsigned kdf_domain_id;
    unsigned detached_kdf_domain;
    unsigned attached_record_kdf_domain;
    unsigned salt_generated;
    unsigned nonce_generated;
    unsigned random_bytes_ex_api_used;
    unsigned random_bytes_strength_bits_requested;
    unsigned random_bytes_manual_fallback_used;
    unsigned generated_salt_csprng_success;
    unsigned generated_nonce_csprng_success;
    unsigned generated_salt_random_bytes;
    unsigned generated_nonce_random_bytes;
    unsigned detached_salt_caller_supplied;
    unsigned detached_nonce_caller_supplied;
    unsigned attached_record_salt_generated;
    unsigned attached_record_nonce_generated;
    unsigned failed_salt_output_cleared;
    unsigned failed_nonce_output_cleared;
    unsigned failed_ciphertext_output_cleared;
    unsigned failed_tag_output_cleared;
    unsigned failed_commitment_output_cleared;
    unsigned failed_plaintext_output_cleared;
    unsigned failed_record_output_cleared;
    unsigned successful_ciphertext_tail_cleared;
    unsigned successful_plaintext_tail_cleared;
    unsigned successful_record_tail_cleared;
    unsigned unsafe_buffer_overlap_rejected;
    unsigned encryption_performed;
    unsigned decryption_performed;
    unsigned secret_material_emitted;
    unsigned hkdf_intermediate_material_zeroized;
    unsigned key_material_zeroized;
    unsigned detached_commitment_key_material_zeroized;
    unsigned record_commitment_key_material_zeroized;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    latticra_seal_hybrid_envelope_error_t error;
    char operation_state[LATTICRA_SEAL_HYBRID_ENVELOPE_STATE_MAX];
    char status[LATTICRA_SEAL_HYBRID_ENVELOPE_STATE_MAX];
} latticra_seal_hybrid_envelope_result_t;

const char *latticra_seal_hybrid_envelope_error_label(
    latticra_seal_hybrid_envelope_error_t error);
int latticra_seal_hybrid_envelope_random_bytes(
    unsigned char *buffer,
    size_t buffer_len);
latticra_status_t latticra_seal_hybrid_envelope_reuse_guard_init(
    latticra_seal_hybrid_envelope_reuse_guard_t *guard);
latticra_status_t latticra_seal_hybrid_envelope_seal(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_open(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *salt,
    size_t salt_len,
    const unsigned char *nonce,
    size_t nonce_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_seal_committed(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_open_committed(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *salt,
    size_t salt_len,
    const unsigned char *nonce,
    size_t nonce_len,
    const unsigned char *tag,
    size_t tag_len,
    const unsigned char *commitment,
    size_t commitment_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_seal_record(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *record,
    size_t record_capacity,
    size_t *record_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_open_record(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *record,
    size_t record_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_encrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_encrypt_guarded(
    latticra_seal_hybrid_envelope_reuse_guard_t *guard,
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_encrypt_committed(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_encrypt_committed_guarded(
    latticra_seal_hybrid_envelope_reuse_guard_t *guard,
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_decrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out);
latticra_status_t latticra_seal_hybrid_envelope_decrypt_committed(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    const unsigned char *commitment,
    size_t commitment_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out);
int latticra_seal_hybrid_envelope_result_is_authority_neutral(
    const latticra_seal_hybrid_envelope_result_t *result);
latticra_status_t latticra_seal_hybrid_envelope_report(
    const latticra_seal_hybrid_envelope_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
