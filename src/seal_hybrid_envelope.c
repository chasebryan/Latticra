#include "latticra/seal_hybrid_envelope.h"

#include <limits.h>
#include <openssl/opensslv.h>
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
#include <openssl/core_names.h>
#include <openssl/kdf.h>
#include <openssl/params.h>
#endif
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LATTICRA_SEAL_HYBRID_IKM_MAX 320u
#define LATTICRA_SEAL_HYBRID_HKDF_INFO_MAX 96u
#define LATTICRA_SEAL_HYBRID_RANDOM_NONZERO_ATTEMPTS 4u
#define LATTICRA_SEAL_HYBRID_RECORD_MAGIC_TEXT "LSEHENV1"
#define LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_TEXT "LSEDAAD1"
#define LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_LABEL_TEXT "LSEDCOM1"
#define LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_TEXT "LSEHAAD1"
#define LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_LABEL_TEXT "LSEHCOM1"

static const unsigned char hybrid_ikm_label[] = "Latticra-Seal-Hybrid-Envelope-v1";
static const unsigned char hybrid_classical_secret_role_label[] = "classical";
static const unsigned char hybrid_classical_secret_algorithm_label[] =
    "latticra-seal-hybrid-classical-kem-shared-secret-32/v1";
static const unsigned char hybrid_pqc_secret_role_label[] = "pqc";
static const unsigned char hybrid_pqc_secret_algorithm_label[] =
    "latticra-seal-hybrid-pqc-ml-kem-shared-secret-32/v1";
static const unsigned char hybrid_hkdf_info_detached[] =
    "latticra-seal-hybrid-envelope/aes-256-gcm/detached/suite-1/v1";
static const unsigned char hybrid_hkdf_info_detached_commitment[] =
    "latticra-seal-hybrid-envelope/hmac-sha256/detached-commit/suite-1/v1";
static const unsigned char hybrid_hkdf_info_attached_record[] =
    "latticra-seal-hybrid-envelope/aes-256-gcm/attached-record/suite-1/v1";
static const unsigned char hybrid_hkdf_info_attached_record_commitment[] =
    "latticra-seal-hybrid-envelope/hmac-sha256/record-commit/suite-1/v1";
static const unsigned char hybrid_record_magic[LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES] = {
    'L', 'S', 'E', 'H', 'E', 'N', 'V', '1'
};
static const unsigned char hybrid_detached_commitment_label[] = "LSEDCOM1";
static const unsigned char hybrid_record_commitment_label[] = "LSEHCOM1";

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static void result_init(latticra_seal_hybrid_envelope_result_t *result) {
    memset(result, 0, sizeof(*result));
    copy_literal(
        result->envelope_profile,
        sizeof(result->envelope_profile),
        "latticra-seal-hybrid-envelope/0.1");
    copy_literal(result->kdf_algorithm, sizeof(result->kdf_algorithm), "HKDF-SHA256");
    copy_literal(result->aead_algorithm, sizeof(result->aead_algorithm), "AES-256-GCM");
    copy_literal(
        result->standards_source,
        sizeof(result->standards_source),
        "NIST-FIPS-197,NIST-SP-800-38D,RFC-5869,NIST-SP-800-56C-REV2,RFC-2104,NIST-SP-800-227");
    result->hybrid_classical_pqc_secret_required = 1u;
    result->production_crypto_claim_allowed = 0u;
    result->fips_claim_allowed = 0u;
    result->runtime_authority_granted = 0u;
    result->error = LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT;
    copy_literal(result->operation_state, sizeof(result->operation_state), "invalid");
    copy_literal(result->status, sizeof(result->status), "invalid-input");
}

static void result_fail(
    latticra_seal_hybrid_envelope_result_t *result,
    latticra_seal_hybrid_envelope_error_t error) {
    result->error = error;
    copy_literal(result->operation_state, sizeof(result->operation_state), "rejected");
    copy_literal(
        result->status,
        sizeof(result->status),
        latticra_seal_hybrid_envelope_error_label(error));
}

static latticra_status_t hybrid_encrypt_with_domain(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned kdf_domain,
    latticra_seal_hybrid_envelope_result_t *out);

static latticra_status_t hybrid_decrypt_with_domain(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    unsigned kdf_domain,
    latticra_seal_hybrid_envelope_result_t *out);

static int validate_context(
    const latticra_seal_hybrid_envelope_context_t *context,
    latticra_seal_hybrid_envelope_result_t *result);

static int derive_record_commitment_key(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result);

static int derive_detached_commitment_key(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result);

static int compute_detached_commitment(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES]);

static int compute_record_commitment(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char *record,
    size_t ciphertext_len,
    const unsigned char *caller_aad,
    size_t caller_aad_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES]);

static int bytes_are_nonzero(const unsigned char *buffer, size_t buffer_len) {
    unsigned char accumulator = 0u;
    size_t index;

    if (buffer == NULL || buffer_len == 0u) {
        return 0;
    }

    for (index = 0u; index < buffer_len; index++) {
        accumulator |= buffer[index];
    }

    return accumulator != 0u;
}

static int byte_ranges_overlap(
    const unsigned char *left,
    size_t left_len,
    const unsigned char *right,
    size_t right_len) {
    uintptr_t left_start;
    uintptr_t left_end;
    uintptr_t right_start;
    uintptr_t right_end;

    if (left == NULL || right == NULL || left_len == 0u || right_len == 0u) {
        return 0;
    }

    left_start = (uintptr_t)left;
    right_start = (uintptr_t)right;
    if (left_len > (size_t)(UINTPTR_MAX - left_start) ||
        right_len > (size_t)(UINTPTR_MAX - right_start)) {
        return 1;
    }

    left_end = left_start + (uintptr_t)left_len;
    right_end = right_start + (uintptr_t)right_len;
    return left_start < right_end && right_start < left_end;
}

static int writable_range_overlaps_context(
    const unsigned char *writable,
    size_t writable_len,
    const latticra_seal_hybrid_envelope_context_t *context) {
    if (context == NULL) {
        return 0;
    }

    return byte_ranges_overlap(
               writable,
               writable_len,
               context->classical_shared_secret,
               context->classical_shared_secret_len) ||
           byte_ranges_overlap(
               writable,
               writable_len,
               context->pqc_shared_secret,
               context->pqc_shared_secret_len) ||
           byte_ranges_overlap(writable, writable_len, context->salt, context->salt_len) ||
           byte_ranges_overlap(writable, writable_len, context->nonce, context->nonce_len) ||
           byte_ranges_overlap(writable, writable_len, context->aad, context->aad_len);
}

static int encrypt_buffers_overlap(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *tag,
    size_t tag_len) {
    return byte_ranges_overlap(ciphertext, ciphertext_capacity, plaintext, plaintext_len) ||
           byte_ranges_overlap(tag, tag_len, plaintext, plaintext_len) ||
           byte_ranges_overlap(ciphertext, ciphertext_capacity, tag, tag_len) ||
           writable_range_overlaps_context(ciphertext, ciphertext_capacity, context) ||
           writable_range_overlaps_context(tag, tag_len, context);
}

static int decrypt_buffers_overlap(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity) {
    return byte_ranges_overlap(plaintext, plaintext_capacity, ciphertext, ciphertext_len) ||
           byte_ranges_overlap(plaintext, plaintext_capacity, tag, tag_len) ||
           writable_range_overlaps_context(plaintext, plaintext_capacity, context);
}

static int seal_outputs_overlap_inputs(
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
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len) {
    latticra_seal_hybrid_envelope_context_t context;

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = salt_len;
    context.nonce = nonce;
    context.nonce_len = nonce_len;
    context.aad = aad;
    context.aad_len = aad_len;

    return encrypt_buffers_overlap(
               &context,
               plaintext,
               plaintext_len,
               ciphertext,
               ciphertext_capacity,
               tag,
               tag_len) ||
           byte_ranges_overlap(salt, salt_len, classical_shared_secret, classical_shared_secret_len) ||
           byte_ranges_overlap(salt, salt_len, pqc_shared_secret, pqc_shared_secret_len) ||
           byte_ranges_overlap(salt, salt_len, aad, aad_len) ||
           byte_ranges_overlap(salt, salt_len, plaintext, plaintext_len) ||
           byte_ranges_overlap(nonce, nonce_len, classical_shared_secret, classical_shared_secret_len) ||
           byte_ranges_overlap(nonce, nonce_len, pqc_shared_secret, pqc_shared_secret_len) ||
           byte_ranges_overlap(nonce, nonce_len, aad, aad_len) ||
           byte_ranges_overlap(nonce, nonce_len, plaintext, plaintext_len) ||
           byte_ranges_overlap(ciphertext, ciphertext_capacity, salt, salt_len) ||
           byte_ranges_overlap(ciphertext, ciphertext_capacity, nonce, nonce_len) ||
           byte_ranges_overlap(salt, salt_len, nonce, nonce_len) ||
           byte_ranges_overlap(salt, salt_len, tag, tag_len) ||
           byte_ranges_overlap(nonce, nonce_len, tag, tag_len);
}

static int seal_committed_outputs_overlap_inputs(
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
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len) {
    return seal_outputs_overlap_inputs(
               classical_shared_secret,
               classical_shared_secret_len,
               pqc_shared_secret,
               pqc_shared_secret_len,
               aad,
               aad_len,
               plaintext,
               plaintext_len,
               ciphertext,
               ciphertext_capacity,
               salt,
               salt_len,
               nonce,
               nonce_len,
               tag,
               tag_len) ||
           byte_ranges_overlap(commitment, commitment_len, classical_shared_secret, classical_shared_secret_len) ||
           byte_ranges_overlap(commitment, commitment_len, pqc_shared_secret, pqc_shared_secret_len) ||
           byte_ranges_overlap(commitment, commitment_len, aad, aad_len) ||
           byte_ranges_overlap(commitment, commitment_len, plaintext, plaintext_len) ||
           byte_ranges_overlap(commitment, commitment_len, ciphertext, ciphertext_capacity) ||
           byte_ranges_overlap(commitment, commitment_len, salt, salt_len) ||
           byte_ranges_overlap(commitment, commitment_len, nonce, nonce_len) ||
           byte_ranges_overlap(commitment, commitment_len, tag, tag_len);
}

static int record_output_overlaps_inputs(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *record,
    size_t record_capacity) {
    return byte_ranges_overlap(record, record_capacity, classical_shared_secret, classical_shared_secret_len) ||
           byte_ranges_overlap(record, record_capacity, pqc_shared_secret, pqc_shared_secret_len) ||
           byte_ranges_overlap(record, record_capacity, aad, aad_len) ||
           byte_ranges_overlap(record, record_capacity, plaintext, plaintext_len);
}

static int encrypt_committed_buffers_overlap(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len) {
    return encrypt_buffers_overlap(
               context,
               plaintext,
               plaintext_len,
               ciphertext,
               ciphertext_capacity,
               tag,
               tag_len) ||
           byte_ranges_overlap(commitment, commitment_len, plaintext, plaintext_len) ||
           byte_ranges_overlap(commitment, commitment_len, ciphertext, ciphertext_capacity) ||
           byte_ranges_overlap(commitment, commitment_len, tag, tag_len) ||
           writable_range_overlaps_context(commitment, commitment_len, context);
}

static int decrypt_committed_buffers_overlap(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    const unsigned char *commitment,
    size_t commitment_len,
    unsigned char *plaintext,
    size_t plaintext_capacity) {
    return decrypt_buffers_overlap(
               context,
               ciphertext,
               ciphertext_len,
               tag,
               tag_len,
               plaintext,
               plaintext_capacity) ||
           byte_ranges_overlap(plaintext, plaintext_capacity, commitment, commitment_len);
}

static int record_open_output_overlaps_inputs(
    const unsigned char *classical_shared_secret,
    size_t classical_shared_secret_len,
    const unsigned char *pqc_shared_secret,
    size_t pqc_shared_secret_len,
    const unsigned char *aad,
    size_t aad_len,
    const unsigned char *record,
    size_t record_len,
    unsigned char *plaintext,
    size_t plaintext_capacity) {
    return byte_ranges_overlap(plaintext, plaintext_capacity, classical_shared_secret, classical_shared_secret_len) ||
           byte_ranges_overlap(plaintext, plaintext_capacity, pqc_shared_secret, pqc_shared_secret_len) ||
           byte_ranges_overlap(plaintext, plaintext_capacity, aad, aad_len) ||
           byte_ranges_overlap(plaintext, plaintext_capacity, record, record_len);
}

static int select_hkdf_info(
    unsigned kdf_domain,
    const unsigned char **info,
    size_t *info_len) {
    if (info == NULL || info_len == NULL) {
        return 0;
    }

    switch (kdf_domain) {
    case LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED:
        *info = hybrid_hkdf_info_detached;
        *info_len = sizeof(hybrid_hkdf_info_detached) - 1u;
        return 1;
    case LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD:
        *info = hybrid_hkdf_info_attached_record;
        *info_len = sizeof(hybrid_hkdf_info_attached_record) - 1u;
        return 1;
    default:
        *info = NULL;
        *info_len = 0u;
        return 0;
    }
}

static void mark_kdf_domain(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned kdf_domain) {
    if (result == NULL) {
        return;
    }

    result->kdf_domain_separated = 1u;
    result->kdf_domain_id = kdf_domain;
    result->detached_kdf_domain =
        kdf_domain == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED ? 1u : 0u;
    result->attached_record_kdf_domain =
        kdf_domain == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD ? 1u : 0u;
    if (kdf_domain == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED) {
        result->detached_suite_id = LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM;
        result->detached_suite_kdf_bound = 1u;
    }
}

static void mark_detached_commitment_present(
    latticra_seal_hybrid_envelope_result_t *result) {
    if (result == NULL) {
        return;
    }

    result->detached_commitment_size_bytes = LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES;
    result->detached_key_commitment_present = 1u;
    result->detached_commitment_key_kdf_bound = 1u;
    result->detached_commitment_caller_aad_bound = 1u;
    result->detached_commitment_input_streamed = 1u;
}

static void mark_detached_commitment_precheck(
    latticra_seal_hybrid_envelope_result_t *result) {
    mark_detached_commitment_present(result);
    if (result == NULL) {
        return;
    }
    result->detached_commitment_checked_before_decrypt = 1u;
}

static void clear_detached_output_buffers(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *tag,
    size_t tag_len) {
    size_t tag_clear_len = tag_len;

    if (ciphertext != NULL && ciphertext_capacity > 0u) {
        OPENSSL_cleanse(ciphertext, ciphertext_capacity);
        if (result != NULL) {
            result->failed_ciphertext_output_cleared = 1u;
        }
    }

    if (tag_clear_len > LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        tag_clear_len = LATTICRA_SEAL_HYBRID_TAG_BYTES;
    }
    if (tag != NULL && tag_clear_len > 0u) {
        OPENSSL_cleanse(tag, tag_clear_len);
        if (result != NULL) {
            result->failed_tag_output_cleared = 1u;
        }
    }
}

static void clear_commitment_output_buffer(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *commitment,
    size_t commitment_len) {
    size_t commitment_clear_len = commitment_len;

    if (commitment_clear_len > LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        commitment_clear_len = LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES;
    }
    if (commitment != NULL && commitment_clear_len > 0u) {
        OPENSSL_cleanse(commitment, commitment_clear_len);
        if (result != NULL) {
            result->failed_commitment_output_cleared = 1u;
        }
    }
}

static void clear_detached_committed_output_buffers(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len) {
    clear_detached_output_buffers(result, ciphertext, ciphertext_capacity, tag, tag_len);
    clear_commitment_output_buffer(result, commitment, commitment_len);
}

static void clear_seal_output_buffers(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len) {
    size_t salt_clear_len = salt_len;
    size_t nonce_clear_len = nonce_len;

    clear_detached_output_buffers(result, ciphertext, ciphertext_capacity, tag, tag_len);

    if (salt_clear_len > LATTICRA_SEAL_HYBRID_SALT_BYTES) {
        salt_clear_len = LATTICRA_SEAL_HYBRID_SALT_BYTES;
    }
    if (salt != NULL && salt_clear_len > 0u) {
        OPENSSL_cleanse(salt, salt_clear_len);
        if (result != NULL) {
            result->failed_salt_output_cleared = 1u;
        }
    }

    if (nonce_clear_len > LATTICRA_SEAL_HYBRID_NONCE_BYTES) {
        nonce_clear_len = LATTICRA_SEAL_HYBRID_NONCE_BYTES;
    }
    if (nonce != NULL && nonce_clear_len > 0u) {
        OPENSSL_cleanse(nonce, nonce_clear_len);
        if (result != NULL) {
            result->failed_nonce_output_cleared = 1u;
        }
    }
}

static void clear_seal_committed_output_buffers(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    unsigned char *salt,
    size_t salt_len,
    unsigned char *nonce,
    size_t nonce_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned char *commitment,
    size_t commitment_len) {
    clear_seal_output_buffers(
        result,
        ciphertext,
        ciphertext_capacity,
        salt,
        salt_len,
        nonce,
        nonce_len,
        tag,
        tag_len);
    clear_commitment_output_buffer(result, commitment, commitment_len);
}

static int random_bytes_with_report(
    unsigned char *buffer,
    size_t buffer_len,
    latticra_seal_hybrid_envelope_result_t *result) {
    int ok;

    if (buffer == NULL || buffer_len == 0u || buffer_len > (size_t)INT_MAX) {
        return 0;
    }

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    ok = RAND_bytes_ex(NULL, buffer, buffer_len, LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS) == 1;
    if (ok && result != NULL) {
        result->random_bytes_ex_api_used = 1u;
        result->random_bytes_strength_bits_requested = LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS;
        result->random_bytes_manual_fallback_used = 0u;
    }
#else
    ok = RAND_bytes(buffer, (int)buffer_len) == 1;
    if (ok && result != NULL) {
        result->random_bytes_manual_fallback_used = 1u;
    }
#endif

    return ok;
}

static int random_nonzero_bytes(
    unsigned char *buffer,
    size_t buffer_len,
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned is_salt) {
    unsigned attempt;

    for (attempt = 0u; attempt < LATTICRA_SEAL_HYBRID_RANDOM_NONZERO_ATTEMPTS; attempt++) {
        if (!random_bytes_with_report(buffer, buffer_len, result)) {
            return 0;
        }
        if (bytes_are_nonzero(buffer, buffer_len)) {
            if (result != NULL) {
                if (is_salt) {
                    result->generated_salt_csprng_success = 1u;
                    result->generated_salt_random_bytes = (unsigned)buffer_len;
                } else {
                    result->generated_nonce_csprng_success = 1u;
                    result->generated_nonce_random_bytes = (unsigned)buffer_len;
                }
            }
            return 1;
        }
    }

    OPENSSL_cleanse(buffer, buffer_len);
    return 0;
}

static void mark_generated_random_pair(latticra_seal_hybrid_envelope_result_t *result) {
    if (result == NULL) {
        return;
    }
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    result->random_bytes_ex_api_used = 1u;
    result->random_bytes_strength_bits_requested = LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS;
    result->random_bytes_manual_fallback_used = 0u;
#else
    result->random_bytes_manual_fallback_used = 1u;
#endif
    result->generated_salt_csprng_success = 1u;
    result->generated_nonce_csprng_success = 1u;
    result->generated_salt_random_bytes = LATTICRA_SEAL_HYBRID_SALT_BYTES;
    result->generated_nonce_random_bytes = LATTICRA_SEAL_HYBRID_NONCE_BYTES;
}

const char *latticra_seal_hybrid_envelope_error_label(
    latticra_seal_hybrid_envelope_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_HYBRID_ENVELOPE_OK:
        return "ok";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET:
        return "missing-classical-shared-secret";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_CLASSICAL_SHARED_SECRET_SIZE:
        return "invalid-classical-shared-secret-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_PQC_SHARED_SECRET:
        return "missing-pqc-shared-secret";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_PQC_SHARED_SECRET_SIZE:
        return "invalid-pqc-shared-secret-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_SALT:
        return "missing-salt";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_SALT_SIZE:
        return "invalid-salt-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_NONCE:
        return "missing-nonce";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_NONCE_SIZE:
        return "invalid-nonce-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT:
        return "missing-output";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL:
        return "output-buffer-too-small";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG:
        return "missing-tag";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE:
        return "invalid-tag-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE:
        return "message-too-large";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_RANDOM_FAILURE:
        return "random-failure";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE:
        return "kdf-failure";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE:
        return "encryption-failure";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE:
        return "decryption-failure";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED:
        return "authentication-failed";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD:
        return "invalid-record";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET:
        return "weak-classical-shared-secret";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET:
        return "weak-pqc-shared-secret";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT:
        return "weak-salt";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE:
        return "weak-nonce";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_COMMITMENT:
        return "missing-commitment";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE:
        return "invalid-commitment-size";
    case LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET:
        return "duplicate-hybrid-shared-secret";
    default:
        return "unknown";
    }
}

int latticra_seal_hybrid_envelope_random_bytes(
    unsigned char *buffer,
    size_t buffer_len) {
    return random_bytes_with_report(buffer, buffer_len, NULL);
}

static void seal_result_fail(
    latticra_seal_hybrid_envelope_result_t *result,
    latticra_seal_hybrid_envelope_error_t error,
    size_t classical_shared_secret_len,
    size_t pqc_shared_secret_len,
    size_t aad_len,
    size_t plaintext_len,
    size_t salt_len,
    size_t nonce_len,
    size_t tag_len) {
    result->classical_shared_secret_size_bytes = classical_shared_secret_len;
    result->pqc_shared_secret_size_bytes = pqc_shared_secret_len;
    result->aad_size_bytes = aad_len;
    result->plaintext_size_bytes = plaintext_len;
    result->salt_size_bytes = salt_len;
    result->nonce_size_bytes = nonce_len;
    result->tag_size_bytes = tag_len;
    result_fail(result, error);
}

static int validate_seal_inputs_before_random(
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
    unsigned char *tag,
    size_t tag_len,
    latticra_seal_hybrid_envelope_result_t *out) {
    if (classical_shared_secret == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET);
        return 0;
    }
    if (classical_shared_secret_len != LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_CLASSICAL_SHARED_SECRET_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(classical_shared_secret, classical_shared_secret_len)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        out->weak_shared_secret_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET);
        return 0;
    }
    out->classical_shared_secret_nonzero = 1u;
    if (pqc_shared_secret == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_PQC_SHARED_SECRET);
        return 0;
    }
    if (pqc_shared_secret_len != LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_PQC_SHARED_SECRET_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(pqc_shared_secret, pqc_shared_secret_len)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        out->weak_shared_secret_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET);
        return 0;
    }
    out->pqc_shared_secret_nonzero = 1u;
    if (CRYPTO_memcmp(
            classical_shared_secret,
            pqc_shared_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES) == 0) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        out->duplicate_hybrid_shared_secret_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET);
        return 0;
    }
    out->hybrid_secret_components_distinct = 1u;
    if (aad == NULL && aad_len != 0u) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return 0;
    }
    if (aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return 0;
    }
    if (plaintext == NULL && plaintext_len != 0u) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return 0;
    }
    if (plaintext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return 0;
    }
    if (ciphertext == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        return 0;
    }
    if (ciphertext_capacity < plaintext_len) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        return 0;
    }
    if (tag == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG);
        return 0;
    }
    if (tag_len != LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE);
        return 0;
    }

    return 1;
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t context;
    latticra_status_t status;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    if (ciphertext_len != NULL) {
        *ciphertext_len = 0u;
    }
    out->classical_shared_secret_size_bytes = classical_shared_secret_len;
    out->pqc_shared_secret_size_bytes = pqc_shared_secret_len;
    out->aad_size_bytes = aad_len;
    out->plaintext_size_bytes = plaintext_len;
    out->salt_size_bytes = salt_len;
    out->nonce_size_bytes = nonce_len;
    out->tag_size_bytes = tag_len;

    if (salt == NULL) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_SALT,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (salt_len != LATTICRA_SEAL_HYBRID_SALT_BYTES) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_SALT_SIZE,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (nonce == NULL) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_NONCE,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (nonce_len != LATTICRA_SEAL_HYBRID_NONCE_BYTES) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_NONCE_SIZE,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }

    if (ciphertext_len == NULL) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (!validate_seal_inputs_before_random(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_capacity,
            tag,
            tag_len,
            out)) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (seal_outputs_overlap_inputs(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len)) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        out->unsafe_buffer_overlap_rejected = 1u;
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }

    if (!random_nonzero_bytes(salt, salt_len, out, 1u) ||
        !random_nonzero_bytes(nonce, nonce_len, out, 0u)) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_RANDOM_FAILURE,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        return LATTICRA_STATUS_OK;
    }

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = salt_len;
    context.nonce = nonce;
    context.nonce_len = nonce_len;
    context.aad = aad;
    context.aad_len = aad_len;

    status = latticra_seal_hybrid_envelope_encrypt(
        &context,
        plaintext,
        plaintext_len,
        ciphertext,
        ciphertext_capacity,
        ciphertext_len,
        tag,
        tag_len,
        out);
    if (out->error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        clear_seal_output_buffers(
            out, ciphertext, ciphertext_capacity, salt, salt_len, nonce, nonce_len, tag, tag_len);
    }
    out->salt_generated = 1u;
    out->nonce_generated = 1u;
    mark_generated_random_pair(out);
    out->detached_salt_caller_supplied = 0u;
    out->detached_nonce_caller_supplied = 0u;
    if (out->error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        copy_literal(out->operation_state, sizeof(out->operation_state), "sealed");
        copy_literal(out->status, sizeof(out->status), "hybrid-envelope-sealed");
    }
    return status;
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t context;

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = salt_len;
    context.nonce = nonce;
    context.nonce_len = nonce_len;
    context.aad = aad;
    context.aad_len = aad_len;

    return latticra_seal_hybrid_envelope_decrypt(
        &context,
        ciphertext,
        ciphertext_len,
        tag,
        tag_len,
        plaintext,
        plaintext_capacity,
        plaintext_len,
        out);
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t context;
    unsigned char commitment_key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    unsigned char computed_commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    latticra_status_t status;
    int commitment_key_ready = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    memset(commitment_key, 0, sizeof(commitment_key));
    memset(computed_commitment, 0, sizeof(computed_commitment));
    if (ciphertext_len != NULL) {
        *ciphertext_len = 0u;
    }
    out->classical_shared_secret_size_bytes = classical_shared_secret_len;
    out->pqc_shared_secret_size_bytes = pqc_shared_secret_len;
    out->aad_size_bytes = aad_len;
    out->plaintext_size_bytes = plaintext_len;
    out->salt_size_bytes = salt_len;
    out->nonce_size_bytes = nonce_len;
    out->tag_size_bytes = tag_len;
    out->detached_commitment_size_bytes = commitment_len;

    if (commitment == NULL) {
        clear_seal_committed_output_buffers(
            out,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_COMMITMENT);
        return LATTICRA_STATUS_OK;
    }
    if (commitment_len != LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        clear_seal_committed_output_buffers(
            out,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE);
        return LATTICRA_STATUS_OK;
    }
    if (seal_committed_outputs_overlap_inputs(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len)) {
        clear_seal_committed_output_buffers(
            out,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len);
        out->unsafe_buffer_overlap_rejected = 1u;
        seal_result_fail(
            out,
            LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT,
            classical_shared_secret_len,
            pqc_shared_secret_len,
            aad_len,
            plaintext_len,
            salt_len,
            nonce_len,
            tag_len);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }

    status = latticra_seal_hybrid_envelope_seal(
        classical_shared_secret,
        classical_shared_secret_len,
        pqc_shared_secret,
        pqc_shared_secret_len,
        aad,
        aad_len,
        plaintext,
        plaintext_len,
        ciphertext,
        ciphertext_capacity,
        ciphertext_len,
        salt,
        salt_len,
        nonce,
        nonce_len,
        tag,
        tag_len,
        out);
    if (status != LATTICRA_STATUS_OK ||
        out->error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK ||
        ciphertext_len == NULL) {
        clear_commitment_output_buffer(out, commitment, commitment_len);
        out->detached_commitment_size_bytes = commitment_len;
        return status;
    }

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = salt_len;
    context.nonce = nonce;
    context.nonce_len = nonce_len;
    context.aad = aad;
    context.aad_len = aad_len;

    if (!derive_detached_commitment_key(&context, commitment_key, out)) {
        clear_seal_committed_output_buffers(
            out,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        return LATTICRA_STATUS_OK;
    }
    commitment_key_ready = 1;
    mark_detached_commitment_present(out);

    if (!compute_detached_commitment(
            commitment_key,
            &context,
            ciphertext,
            *ciphertext_len,
            tag,
            tag_len,
            computed_commitment)) {
        clear_seal_committed_output_buffers(
            out,
            ciphertext,
            ciphertext_capacity,
            salt,
            salt_len,
            nonce,
            nonce_len,
            tag,
            tag_len,
            commitment,
            commitment_len);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
        out->detached_commitment_key_material_zeroized = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
        return LATTICRA_STATUS_OK;
    }

    memcpy(commitment, computed_commitment, sizeof(computed_commitment));
    mark_detached_commitment_present(out);
    copy_literal(out->operation_state, sizeof(out->operation_state), "committed-sealed");
    copy_literal(out->status, sizeof(out->status), "hybrid-envelope-committed-sealed");

    OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
    OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
    if (commitment_key_ready) {
        out->detached_commitment_key_material_zeroized = 1u;
    }
    return LATTICRA_STATUS_OK;
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t context;
    latticra_status_t status;

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = salt_len;
    context.nonce = nonce;
    context.nonce_len = nonce_len;
    context.aad = aad;
    context.aad_len = aad_len;

    status = latticra_seal_hybrid_envelope_decrypt_committed(
        &context,
        ciphertext,
        ciphertext_len,
        tag,
        tag_len,
        commitment,
        commitment_len,
        plaintext,
        plaintext_capacity,
        plaintext_len,
        out);
    if (status == LATTICRA_STATUS_OK &&
        out != NULL &&
        out->error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        copy_literal(out->operation_state, sizeof(out->operation_state), "committed-opened");
        copy_literal(out->status, sizeof(out->status), "hybrid-envelope-committed-opened");
    }
    return status;
}

static void record_result_init(latticra_seal_hybrid_envelope_result_t *result) {
    result_init(result);
    result->record_format_present = 1u;
    result->record_version = LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    result->record_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES;
    result->record_protected_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES;
    result->record_commitment_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    result->record_key_commitment_present = 1u;
}

static void clear_plaintext_output_buffer(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *plaintext,
    size_t plaintext_capacity) {
    if (plaintext != NULL && plaintext_capacity > 0u) {
        OPENSSL_cleanse(plaintext, plaintext_capacity);
        if (result != NULL) {
            result->failed_plaintext_output_cleared = 1u;
        }
    }
}

static void clear_record_output_buffer(
    latticra_seal_hybrid_envelope_result_t *result,
    unsigned char *record,
    size_t record_capacity) {
    if (record != NULL && record_capacity > 0u) {
        OPENSSL_cleanse(record, record_capacity);
        if (result != NULL) {
            result->failed_record_output_cleared = 1u;
        }
    }
}

static void write_u64_be(unsigned char *out, size_t value) {
    unsigned long long remaining = (unsigned long long)value;
    size_t index;

    for (index = 0u; index < 8u; index++) {
        out[7u - index] = (unsigned char)(remaining & 0xffu);
        remaining >>= 8u;
    }
}

static unsigned long long read_u64_be(const unsigned char *in) {
    unsigned long long value = 0u;
    size_t index;

    for (index = 0u; index < 8u; index++) {
        value = (value << 8u) | (unsigned long long)in[index];
    }

    return value;
}

static void write_record_header(
    unsigned char *record,
    const unsigned char salt[LATTICRA_SEAL_HYBRID_SALT_BYTES],
    const unsigned char nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES],
    const unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES],
    size_t ciphertext_len) {
    unsigned char flags =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);

    memcpy(record, hybrid_record_magic, sizeof(hybrid_record_magic));
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] = flags;
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_u64_be(record + 12u, ciphertext_len);
    memcpy(record + 20u, salt, LATTICRA_SEAL_HYBRID_SALT_BYTES);
    memcpy(record + 52u, nonce, LATTICRA_SEAL_HYBRID_NONCE_BYTES);
    memcpy(record + 64u, tag, LATTICRA_SEAL_HYBRID_TAG_BYTES);
}

static int build_record_aad(
    const unsigned char *record,
    const unsigned char *aad,
    size_t aad_len,
    unsigned char **out,
    size_t *out_len) {
    unsigned char *combined;
    size_t combined_len;

    if (record == NULL || out == NULL || out_len == NULL) {
        return 0;
    }
    if (aad == NULL && aad_len != 0u) {
        return 0;
    }
    if (aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES) {
        return 0;
    }

    combined_len = LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + aad_len;
    combined = (unsigned char *)malloc(combined_len);
    if (combined == NULL) {
        return 0;
    }

    memcpy(
        combined,
        LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_TEXT,
        LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_BYTES);
    memcpy(
        combined + LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_BYTES,
        record,
        LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES);
    write_u64_be(
        combined + LATTICRA_SEAL_HYBRID_RECORD_AAD_LABEL_BYTES +
            LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES,
        aad_len);
    if (aad_len > 0u) {
        memcpy(combined + LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES, aad, aad_len);
    }

    *out = combined;
    *out_len = combined_len;
    return 1;
}

static int build_detached_aad(
    const unsigned char *aad,
    size_t aad_len,
    unsigned char **out,
    size_t *out_len) {
    unsigned char *combined;
    size_t combined_len;

    if (out == NULL || out_len == NULL) {
        return 0;
    }
    if (aad == NULL && aad_len != 0u) {
        return 0;
    }
    if (aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES) {
        return 0;
    }

    combined_len = LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + aad_len;
    combined = (unsigned char *)malloc(combined_len);
    if (combined == NULL) {
        return 0;
    }

    memcpy(
        combined,
        LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_TEXT,
        LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_BYTES);
    write_u64_be(combined + LATTICRA_SEAL_HYBRID_DETACHED_AAD_LABEL_BYTES, aad_len);
    if (aad_len > 0u) {
        memcpy(combined + LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES, aad, aad_len);
    }

    *out = combined;
    *out_len = combined_len;
    return 1;
}

static int record_header_is_valid(
    const unsigned char *record,
    size_t record_len,
    size_t *ciphertext_len) {
    unsigned char flags;
    unsigned long long parsed_ciphertext_len;
    size_t payload_len;
    size_t expected_min_len;

    if (record == NULL ||
        record_len < LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES ||
        memcmp(record, hybrid_record_magic, sizeof(hybrid_record_magic)) != 0 ||
        record[8] != (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION ||
        record[10] != (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM ||
        record[11] != (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD) {
        return 0;
    }

    flags = record[9];
    if (flags !=
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE)) {
        return 0;
    }

    expected_min_len =
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    if (record_len < expected_min_len) {
        return 0;
    }

    payload_len =
        record_len -
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES -
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    parsed_ciphertext_len = read_u64_be(record + 12u);
    if (parsed_ciphertext_len != (unsigned long long)payload_len ||
        parsed_ciphertext_len > (unsigned long long)LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        return 0;
    }

    *ciphertext_len = payload_len;
    return 1;
}

static int validate_record_salt_nonce_before_open(
    const unsigned char *record,
    latticra_seal_hybrid_envelope_result_t *result) {
    result->salt_size_bytes = LATTICRA_SEAL_HYBRID_SALT_BYTES;
    result->nonce_size_bytes = LATTICRA_SEAL_HYBRID_NONCE_BYTES;

    if (!bytes_are_nonzero(record + 20u, LATTICRA_SEAL_HYBRID_SALT_BYTES)) {
        result->weak_salt_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT);
        return 0;
    }
    result->salt_nonzero = 1u;

    if (!bytes_are_nonzero(record + 52u, LATTICRA_SEAL_HYBRID_NONCE_BYTES)) {
        result->weak_nonce_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE);
        return 0;
    }
    result->nonce_nonzero = 1u;
    result->record_salt_nonce_nonzero = 1u;
    return 1;
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    unsigned char salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char commitment_key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    unsigned char commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES];
    unsigned char *record_aad = NULL;
    latticra_seal_hybrid_envelope_context_t context;
    size_t record_aad_len = 0u;
    size_t ciphertext_len = 0u;
    latticra_status_t status = LATTICRA_STATUS_OK;
    int commitment_key_ready = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    record_result_init(out);
    memset(salt, 0, sizeof(salt));
    memset(nonce, 0, sizeof(nonce));
    memset(tag, 0, sizeof(tag));
    memset(commitment_key, 0, sizeof(commitment_key));
    memset(commitment, 0, sizeof(commitment));
    if (record_len != NULL) {
        *record_len = 0u;
    }

    if (record_len == NULL || record == NULL) {
        clear_record_output_buffer(out, record, record_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        clear_record_output_buffer(out, record, record_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return LATTICRA_STATUS_OK;
    }
    if (record_capacity < LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES ||
        record_capacity <
            LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
                LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES ||
        record_capacity -
                LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES -
                LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES <
            plaintext_len) {
        clear_record_output_buffer(out, record, record_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        return LATTICRA_STATUS_OK;
    }
    if (!validate_seal_inputs_before_random(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            plaintext,
            plaintext_len,
            record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
            record_capacity -
                LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES -
                LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES,
            tag,
            sizeof(tag),
            out)) {
        clear_record_output_buffer(out, record, record_capacity);
        return LATTICRA_STATUS_OK;
    }
    if (aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES) {
        clear_record_output_buffer(out, record, record_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return LATTICRA_STATUS_OK;
    }
    if (record_output_overlaps_inputs(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            plaintext,
            plaintext_len,
            record,
            record_capacity)) {
        clear_record_output_buffer(out, record, record_capacity);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (!random_nonzero_bytes(salt, sizeof(salt), out, 1u) ||
        !random_nonzero_bytes(nonce, sizeof(nonce), out, 0u)) {
        clear_record_output_buffer(out, record, record_capacity);
        OPENSSL_cleanse(salt, sizeof(salt));
        OPENSSL_cleanse(nonce, sizeof(nonce));
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_RANDOM_FAILURE);
        return LATTICRA_STATUS_OK;
    }
    out->salt_generated = 1u;
    out->nonce_generated = 1u;

    memset(tag, 0, sizeof(tag));
    write_record_header(record, salt, nonce, tag, plaintext_len);
    if (!build_record_aad(record, aad, aad_len, &record_aad, &record_aad_len)) {
        clear_record_output_buffer(out, record, record_capacity);
        OPENSSL_cleanse(salt, sizeof(salt));
        OPENSSL_cleanse(nonce, sizeof(nonce));
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
        return LATTICRA_STATUS_OK;
    }

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = salt;
    context.salt_len = sizeof(salt);
    context.nonce = nonce;
    context.nonce_len = sizeof(nonce);
    context.aad = record_aad;
    context.aad_len = record_aad_len;

    status = hybrid_encrypt_with_domain(
        &context,
        plaintext,
        plaintext_len,
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        record_capacity -
            LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES -
            LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES,
        &ciphertext_len,
        tag,
        sizeof(tag),
        LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD,
        out);
    out->record_format_present = 1u;
    out->record_version = LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    out->record_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES;
    out->record_protected_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES;
    out->record_suite_id = LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    out->caller_aad_size_bytes = aad_len;
    out->record_aad_size_bytes = record_aad_len;
    out->record_aad_framed = 1u;
    out->salt_generated = 1u;
    out->nonce_generated = 1u;
    mark_generated_random_pair(out);
    out->detached_salt_caller_supplied = 0u;
    out->detached_nonce_caller_supplied = 0u;
    out->attached_record_salt_generated = 1u;
    out->attached_record_nonce_generated = 1u;

    if (status != LATTICRA_STATUS_OK || out->error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        clear_record_output_buffer(out, record, record_capacity);
        if (record_aad != NULL) {
            OPENSSL_cleanse(record_aad, record_aad_len);
            free(record_aad);
        }
        OPENSSL_cleanse(salt, sizeof(salt));
        OPENSSL_cleanse(nonce, sizeof(nonce));
        OPENSSL_cleanse(tag, sizeof(tag));
        return status;
    }

    write_record_header(record, salt, nonce, tag, ciphertext_len);
    if (!derive_record_commitment_key(&context, commitment_key, out)) {
        clear_record_output_buffer(out, record, record_capacity);
        OPENSSL_cleanse(record_aad, record_aad_len);
        free(record_aad);
        OPENSSL_cleanse(salt, sizeof(salt));
        OPENSSL_cleanse(nonce, sizeof(nonce));
        OPENSSL_cleanse(tag, sizeof(tag));
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(commitment, sizeof(commitment));
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        return LATTICRA_STATUS_OK;
    }
    commitment_key_ready = 1;
    out->record_commitment_key_kdf_bound = 1u;
    out->record_commitment_caller_aad_bound = 1u;
    if (!compute_record_commitment(
            commitment_key,
            record,
            ciphertext_len,
            aad,
            aad_len,
            commitment)) {
        clear_record_output_buffer(out, record, record_capacity);
        OPENSSL_cleanse(record_aad, record_aad_len);
        free(record_aad);
        OPENSSL_cleanse(salt, sizeof(salt));
        OPENSSL_cleanse(nonce, sizeof(nonce));
        OPENSSL_cleanse(tag, sizeof(tag));
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(commitment, sizeof(commitment));
        out->record_commitment_key_material_zeroized = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
        return LATTICRA_STATUS_OK;
    }
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES + ciphertext_len,
        commitment,
        sizeof(commitment));
    *record_len =
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        ciphertext_len +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    out->record_size_bytes = *record_len;
    out->record_commitment_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    out->record_key_commitment_present = 1u;
    out->record_commitment_caller_aad_bound = 1u;
    out->record_commitment_input_streamed = 1u;
    out->attached_record_sealed = 1u;
    out->record_header_authenticated = 1u;
    out->record_suite_authenticated = 1u;
    out->record_kdf_domain_authenticated = 1u;
    out->record_suite_kdf_bound = 1u;
    out->record_salt_nonce_nonzero = 1u;
    out->record_header_shape_validated = 1u;
    out->record_aad_label_authenticated = 1u;
    out->record_caller_aad_authenticated = 1u;
    copy_literal(out->operation_state, sizeof(out->operation_state), "record-sealed");
    copy_literal(out->status, sizeof(out->status), "hybrid-envelope-record-sealed");
    OPENSSL_cleanse(record_aad, record_aad_len);
    free(record_aad);
    OPENSSL_cleanse(salt, sizeof(salt));
    OPENSSL_cleanse(nonce, sizeof(nonce));
    OPENSSL_cleanse(tag, sizeof(tag));
    OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
    OPENSSL_cleanse(commitment, sizeof(commitment));
    if (commitment_key_ready) {
        out->record_commitment_key_material_zeroized = 1u;
    }
    return LATTICRA_STATUS_OK;
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    unsigned char commitment_key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    unsigned char expected_commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES];
    unsigned char *record_aad = NULL;
    latticra_seal_hybrid_envelope_context_t context;
    size_t record_aad_len = 0u;
    size_t ciphertext_len = 0u;
    int commitment_key_zeroized = 0;
    latticra_status_t status;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    record_result_init(out);
    out->record_size_bytes = record_len;
    memset(commitment_key, 0, sizeof(commitment_key));
    memset(expected_commitment, 0, sizeof(expected_commitment));
    if (plaintext_len != NULL) {
        *plaintext_len = 0u;
    }

    if (plaintext_len == NULL || plaintext == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        return LATTICRA_STATUS_OK;
    }
    if (!record_header_is_valid(record, record_len, &ciphertext_len)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->malformed_record_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD);
        return LATTICRA_STATUS_OK;
    }
    out->record_suite_id = (unsigned)record[10];
    out->record_header_shape_validated = 1u;
    if (plaintext_capacity < ciphertext_len) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        return LATTICRA_STATUS_OK;
    }
    if (aad == NULL && aad_len != 0u) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return LATTICRA_STATUS_OK;
    }
    if (record_open_output_overlaps_inputs(
            classical_shared_secret,
            classical_shared_secret_len,
            pqc_shared_secret,
            pqc_shared_secret_len,
            aad,
            aad_len,
            record,
            record_len,
            plaintext,
            plaintext_capacity)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (!validate_record_salt_nonce_before_open(record, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        return LATTICRA_STATUS_OK;
    }
    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = record + 20u;
    context.salt_len = LATTICRA_SEAL_HYBRID_SALT_BYTES;
    context.nonce = record + 52u;
    context.nonce_len = LATTICRA_SEAL_HYBRID_NONCE_BYTES;
    context.aad = aad;
    context.aad_len = aad_len;
    if (!validate_context(&context, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->record_format_present = 1u;
        out->record_version = LATTICRA_SEAL_HYBRID_RECORD_VERSION;
        out->record_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES;
        out->record_protected_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES;
        out->record_commitment_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
        out->record_size_bytes = record_len;
        out->record_suite_id = (unsigned)record[10];
        out->record_header_shape_validated = 1u;
        out->record_key_commitment_present = 1u;
        out->detached_salt_caller_supplied = 0u;
        out->detached_nonce_caller_supplied = 0u;
        return LATTICRA_STATUS_OK;
    }
    mark_kdf_domain(out, LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD);
    out->record_suite_id = (unsigned)record[10];
    out->record_suite_kdf_bound = 1u;
    out->record_header_shape_validated = 1u;
    out->caller_aad_size_bytes = aad_len;
    out->detached_salt_caller_supplied = 0u;
    out->detached_nonce_caller_supplied = 0u;
    if (!derive_record_commitment_key(&context, commitment_key, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        return LATTICRA_STATUS_OK;
    }
    out->hkdf_extract_expand_performed = 1u;
    out->classical_shared_secret_bound = 1u;
    out->pqc_shared_secret_bound = 1u;
    out->hybrid_secret_length_framed = 1u;
    out->hybrid_secret_role_labeled = 1u;
    out->hybrid_secret_algorithm_labeled = 1u;
    out->hybrid_secret_order_bound = 1u;
    out->record_commitment_key_kdf_bound = 1u;
    out->record_commitment_checked_before_decrypt = 1u;
    out->record_commitment_caller_aad_bound = 1u;
    if (!compute_record_commitment(
            commitment_key,
            record,
            ciphertext_len,
            aad,
            aad_len,
            expected_commitment)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        out->record_commitment_key_material_zeroized = 1u;
        return LATTICRA_STATUS_OK;
    }
    out->record_commitment_input_streamed = 1u;
    if (CRYPTO_memcmp(
            expected_commitment,
            record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES + ciphertext_len,
            LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES) != 0) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->record_commitment_tampering_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        out->record_commitment_key_material_zeroized = 1u;
        return LATTICRA_STATUS_OK;
    }
    OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
    OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
    commitment_key_zeroized = 1;

    if (!build_record_aad(record, aad, aad_len, &record_aad, &record_aad_len)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
        return LATTICRA_STATUS_OK;
    }

    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = classical_shared_secret_len;
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = pqc_shared_secret_len;
    context.salt = record + 20u;
    context.salt_len = LATTICRA_SEAL_HYBRID_SALT_BYTES;
    context.nonce = record + 52u;
    context.nonce_len = LATTICRA_SEAL_HYBRID_NONCE_BYTES;
    context.aad = record_aad;
    context.aad_len = record_aad_len;

    status = hybrid_decrypt_with_domain(
        &context,
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        ciphertext_len,
        record + 64u,
        LATTICRA_SEAL_HYBRID_TAG_BYTES,
        plaintext,
        plaintext_capacity,
        plaintext_len,
        LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD,
        out);
    out->record_format_present = 1u;
    out->record_version = LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    out->record_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES;
    out->record_protected_header_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES;
    out->record_commitment_size_bytes = LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES;
    out->record_size_bytes = record_len;
    out->record_suite_id = (unsigned)record[10];
    out->record_suite_kdf_bound = 1u;
    out->record_salt_nonce_nonzero = 1u;
    out->record_header_shape_validated = 1u;
    out->record_key_commitment_present = 1u;
    out->record_commitment_key_kdf_bound = 1u;
    out->record_commitment_verified = 1u;
    out->record_commitment_checked_before_decrypt = 1u;
    out->record_commitment_caller_aad_bound = 1u;
    out->record_commitment_input_streamed = 1u;
    out->record_commitment_key_material_zeroized = commitment_key_zeroized ? 1u : 0u;
    out->caller_aad_size_bytes = aad_len;
    out->record_aad_size_bytes = record_aad_len;
    out->record_aad_framed = 1u;
    out->detached_salt_caller_supplied = 0u;
    out->detached_nonce_caller_supplied = 0u;

    if (status == LATTICRA_STATUS_OK && out->error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        out->attached_record_opened = 1u;
        out->attached_record_authenticated = 1u;
        out->record_header_authenticated = 1u;
        out->record_suite_authenticated = 1u;
        out->record_kdf_domain_authenticated = 1u;
        out->record_aad_label_authenticated = 1u;
        out->record_caller_aad_authenticated = 1u;
        out->attached_record_salt_generated = 1u;
        out->attached_record_nonce_generated = 1u;
        copy_literal(out->operation_state, sizeof(out->operation_state), "record-opened");
        copy_literal(out->status, sizeof(out->status), "hybrid-envelope-record-opened");
    } else {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
    }

    OPENSSL_cleanse(record_aad, record_aad_len);
    free(record_aad);
    return status;
}

static void copy_context_sizes(
    const latticra_seal_hybrid_envelope_context_t *context,
    latticra_seal_hybrid_envelope_result_t *result) {
    if (context == NULL) {
        return;
    }

    result->classical_shared_secret_size_bytes = context->classical_shared_secret_len;
    result->pqc_shared_secret_size_bytes = context->pqc_shared_secret_len;
    result->salt_size_bytes = context->salt_len;
    result->nonce_size_bytes = context->nonce_len;
    result->aad_size_bytes = context->aad_len;
    result->caller_aad_size_bytes = context->aad_len;
}

static int validate_context(
    const latticra_seal_hybrid_envelope_context_t *context,
    latticra_seal_hybrid_envelope_result_t *result) {
    copy_context_sizes(context, result);

    if (context == NULL) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return 0;
    }
    if (context->classical_shared_secret == NULL) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET);
        return 0;
    }
    if (context->classical_shared_secret_len != LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_CLASSICAL_SHARED_SECRET_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(context->classical_shared_secret, context->classical_shared_secret_len)) {
        result->weak_shared_secret_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET);
        return 0;
    }
    result->classical_shared_secret_nonzero = 1u;
    if (context->pqc_shared_secret == NULL) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_PQC_SHARED_SECRET);
        return 0;
    }
    if (context->pqc_shared_secret_len != LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_PQC_SHARED_SECRET_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(context->pqc_shared_secret, context->pqc_shared_secret_len)) {
        result->weak_shared_secret_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET);
        return 0;
    }
    result->pqc_shared_secret_nonzero = 1u;
    if (CRYPTO_memcmp(
            context->classical_shared_secret,
            context->pqc_shared_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES) == 0) {
        result->duplicate_hybrid_shared_secret_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET);
        return 0;
    }
    result->hybrid_secret_components_distinct = 1u;
    if (context->salt == NULL) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_SALT);
        return 0;
    }
    if (context->salt_len != LATTICRA_SEAL_HYBRID_SALT_BYTES) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_SALT_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(context->salt, context->salt_len)) {
        result->weak_salt_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT);
        return 0;
    }
    result->salt_nonzero = 1u;
    if (context->nonce == NULL) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_NONCE);
        return 0;
    }
    if (context->nonce_len != LATTICRA_SEAL_HYBRID_NONCE_BYTES) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_NONCE_SIZE);
        return 0;
    }
    if (!bytes_are_nonzero(context->nonce, context->nonce_len)) {
        result->weak_nonce_rejected = 1u;
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE);
        return 0;
    }
    result->nonce_nonzero = 1u;
    result->detached_salt_caller_supplied = 1u;
    result->detached_nonce_caller_supplied = 1u;
    if (context->aad == NULL && context->aad_len != 0u) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return 0;
    }
    if (context->aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        result_fail(result, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return 0;
    }

    return 1;
}

static int append_bytes(
    unsigned char *buffer,
    size_t buffer_len,
    size_t *used,
    const unsigned char *bytes,
    size_t bytes_len) {
    if (*used > buffer_len || bytes_len > (buffer_len - *used)) {
        return 0;
    }

    memcpy(buffer + *used, bytes, bytes_len);
    *used += bytes_len;
    return 1;
}

static int append_size_be(
    unsigned char *buffer,
    size_t buffer_len,
    size_t *used,
    size_t value) {
    unsigned char encoded[8];
    unsigned long long remaining = (unsigned long long)value;
    size_t index;

    for (index = 0u; index < sizeof(encoded); index++) {
        encoded[sizeof(encoded) - 1u - index] = (unsigned char)(remaining & 0xffu);
        remaining >>= 8u;
    }

    return append_bytes(buffer, buffer_len, used, encoded, sizeof(encoded));
}

static int build_hybrid_ikm(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned char *ikm,
    size_t ikm_len,
    size_t *used) {
    *used = 0u;

    return append_bytes(
               ikm,
               ikm_len,
               used,
               hybrid_ikm_label,
               sizeof(hybrid_ikm_label) - 1u) &&
           append_size_be(
               ikm,
               ikm_len,
               used,
               sizeof(hybrid_classical_secret_role_label) - 1u) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               hybrid_classical_secret_role_label,
               sizeof(hybrid_classical_secret_role_label) - 1u) &&
           append_size_be(
               ikm,
               ikm_len,
               used,
               sizeof(hybrid_classical_secret_algorithm_label) - 1u) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               hybrid_classical_secret_algorithm_label,
               sizeof(hybrid_classical_secret_algorithm_label) - 1u) &&
           append_size_be(ikm, ikm_len, used, context->classical_shared_secret_len) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               context->classical_shared_secret,
               context->classical_shared_secret_len) &&
           append_size_be(
               ikm,
               ikm_len,
               used,
               sizeof(hybrid_pqc_secret_role_label) - 1u) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               hybrid_pqc_secret_role_label,
               sizeof(hybrid_pqc_secret_role_label) - 1u) &&
           append_size_be(
               ikm,
               ikm_len,
               used,
               sizeof(hybrid_pqc_secret_algorithm_label) - 1u) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               hybrid_pqc_secret_algorithm_label,
               sizeof(hybrid_pqc_secret_algorithm_label) - 1u) &&
           append_size_be(ikm, ikm_len, used, context->pqc_shared_secret_len) &&
           append_bytes(
               ikm,
               ikm_len,
               used,
               context->pqc_shared_secret,
               context->pqc_shared_secret_len);
}

static int derive_hybrid_key_from_info(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *hkdf_info,
    size_t hkdf_info_len,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result) {
    unsigned char ikm[LATTICRA_SEAL_HYBRID_IKM_MAX];
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_KDF *kdf = NULL;
    EVP_KDF_CTX *kdf_ctx = NULL;
    OSSL_PARAM params[6];
    char digest_name[] = "SHA256";
    int hkdf_mode = EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND;
#else
    unsigned char prk[EVP_MAX_MD_SIZE];
    unsigned char expand_input[LATTICRA_SEAL_HYBRID_HKDF_INFO_MAX + 1u];
    unsigned int prk_len = 0u;
    unsigned int key_len = 0u;
#endif
    size_t ikm_used = 0u;
    int ok = 0;

    memset(ikm, 0, sizeof(ikm));
#if !defined(OPENSSL_VERSION_MAJOR) || OPENSSL_VERSION_MAJOR < 3
    memset(prk, 0, sizeof(prk));
    memset(expand_input, 0, sizeof(expand_input));
#endif

    if (hkdf_info == NULL ||
        hkdf_info_len == 0u ||
        hkdf_info_len > LATTICRA_SEAL_HYBRID_HKDF_INFO_MAX) {
        goto cleanup;
    }
    if (!build_hybrid_ikm(context, ikm, sizeof(ikm), &ikm_used)) {
        goto cleanup;
    }

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    kdf = EVP_KDF_fetch(NULL, "HKDF", NULL);
    if (kdf == NULL) {
        goto cleanup;
    }
    kdf_ctx = EVP_KDF_CTX_new(kdf);
    if (kdf_ctx == NULL) {
        goto cleanup;
    }

    params[0] = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST, digest_name, 0u);
    params[1] = OSSL_PARAM_construct_int(OSSL_KDF_PARAM_MODE, &hkdf_mode);
    params[2] = OSSL_PARAM_construct_octet_string(
        OSSL_KDF_PARAM_SALT,
        (void *)context->salt,
        context->salt_len);
    params[3] = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY, ikm, ikm_used);
    params[4] = OSSL_PARAM_construct_octet_string(
        OSSL_KDF_PARAM_INFO,
        (void *)hkdf_info,
        hkdf_info_len);
    params[5] = OSSL_PARAM_construct_end();

    if (EVP_KDF_derive(kdf_ctx, key, LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES, params) != 1) {
        goto cleanup;
    }

    ok = 1;
    if (result != NULL) {
        result->hkdf_provider_api_used = 1u;
        result->hkdf_extract_expand_standard_api_used = 1u;
        result->hkdf_sha256_digest_bound = 1u;
        result->hkdf_manual_fallback_used = 0u;
    }
#else
    if (HMAC(
            EVP_sha256(),
            context->salt,
            (int)context->salt_len,
            ikm,
            ikm_used,
            prk,
            &prk_len) == NULL ||
        prk_len != LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES) {
        goto cleanup;
    }

    memcpy(expand_input, hkdf_info, hkdf_info_len);
    expand_input[hkdf_info_len] = 0x01u;

    if (HMAC(
            EVP_sha256(),
            prk,
            (int)prk_len,
            expand_input,
            hkdf_info_len + 1u,
            key,
            &key_len) == NULL ||
        key_len != LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES) {
        goto cleanup;
    }

    ok = 1;
    if (result != NULL) {
        result->hkdf_extract_expand_standard_api_used = 1u;
        result->hkdf_sha256_digest_bound = 1u;
        result->hkdf_manual_fallback_used = 1u;
    }
#endif

cleanup:
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_KDF_CTX_free(kdf_ctx);
    EVP_KDF_free(kdf);
#endif
    OPENSSL_cleanse(ikm, sizeof(ikm));
#if !defined(OPENSSL_VERSION_MAJOR) || OPENSSL_VERSION_MAJOR < 3
    OPENSSL_cleanse(prk, sizeof(prk));
    OPENSSL_cleanse(expand_input, sizeof(expand_input));
#endif
    if (result != NULL) {
        result->hkdf_intermediate_material_zeroized = 1u;
    }
    return ok;
}

static int derive_hybrid_key(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned kdf_domain,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result) {
    const unsigned char *hkdf_info = NULL;
    size_t hkdf_info_len = 0u;

    if (!select_hkdf_info(kdf_domain, &hkdf_info, &hkdf_info_len)) {
        return 0;
    }

    return derive_hybrid_key_from_info(context, hkdf_info, hkdf_info_len, key, result);
}

static int derive_detached_commitment_key(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result) {
    return derive_hybrid_key_from_info(
        context,
        hybrid_hkdf_info_detached_commitment,
        sizeof(hybrid_hkdf_info_detached_commitment) - 1u,
        key,
        result);
}

static int derive_record_commitment_key(
    const latticra_seal_hybrid_envelope_context_t *context,
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    latticra_seal_hybrid_envelope_result_t *result) {
    return derive_hybrid_key_from_info(
        context,
        hybrid_hkdf_info_attached_record_commitment,
        sizeof(hybrid_hkdf_info_attached_record_commitment) - 1u,
        key,
        result);
}

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
static int hmac_sha256_commitment_stream(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES],
    const unsigned char *record,
    size_t ciphertext_len,
    const unsigned char *caller_aad,
    size_t caller_aad_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES]) {
    EVP_MAC *mac = NULL;
    EVP_MAC_CTX *ctx = NULL;
    OSSL_PARAM params[2];
    char digest_name[] = "SHA256";
    size_t commitment_len = 0u;
    int ok = 0;

    mac = EVP_MAC_fetch(NULL, "HMAC", NULL);
    if (mac == NULL) {
        goto cleanup;
    }
    ctx = EVP_MAC_CTX_new(mac);
    if (ctx == NULL) {
        goto cleanup;
    }

    params[0] = OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_DIGEST, digest_name, 0u);
    params[1] = OSSL_PARAM_construct_end();
    if (EVP_MAC_init(ctx, key, LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES, params) != 1 ||
        EVP_MAC_update(
            ctx,
            hybrid_record_commitment_label,
            sizeof(hybrid_record_commitment_label) - 1u) != 1 ||
        EVP_MAC_update(ctx, record, LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES) != 1 ||
        EVP_MAC_update(
            ctx,
            aad_length_be,
            LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES) != 1) {
        goto cleanup;
    }
    if (caller_aad_len > 0u && EVP_MAC_update(ctx, caller_aad, caller_aad_len) != 1) {
        goto cleanup;
    }
    if (ciphertext_len > 0u &&
        EVP_MAC_update(
            ctx,
            record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
            ciphertext_len) != 1) {
        goto cleanup;
    }
    if (EVP_MAC_final(
            ctx,
            commitment,
            &commitment_len,
            LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES) != 1 ||
        commitment_len != LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES) {
        goto cleanup;
    }

    ok = 1;

cleanup:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    return ok;
}
#else
static int hmac_sha256_commitment_stream(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES],
    const unsigned char *record,
    size_t ciphertext_len,
    const unsigned char *caller_aad,
    size_t caller_aad_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES]) {
    HMAC_CTX *ctx = NULL;
    unsigned int commitment_len = 0u;
    int ok = 0;

    ctx = HMAC_CTX_new();
    if (ctx == NULL) {
        goto cleanup;
    }
    if (HMAC_Init_ex(ctx, key, LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES, EVP_sha256(), NULL) != 1 ||
        HMAC_Update(
            ctx,
            hybrid_record_commitment_label,
            sizeof(hybrid_record_commitment_label) - 1u) != 1 ||
        HMAC_Update(ctx, record, LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES) != 1 ||
        HMAC_Update(
            ctx,
            aad_length_be,
            LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES) != 1) {
        goto cleanup;
    }
    if (caller_aad_len > 0u && HMAC_Update(ctx, caller_aad, caller_aad_len) != 1) {
        goto cleanup;
    }
    if (ciphertext_len > 0u &&
        HMAC_Update(
            ctx,
            record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
            ciphertext_len) != 1) {
        goto cleanup;
    }
    if (HMAC_Final(ctx, commitment, &commitment_len) != 1 ||
        commitment_len != LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES) {
        goto cleanup;
    }

    ok = 1;

cleanup:
    HMAC_CTX_free(ctx);
    return ok;
}
#endif

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
static int hmac_sha256_detached_commitment_stream(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char suite_domain[2],
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    const unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES],
    const unsigned char ciphertext_length_be[8],
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES]) {
    EVP_MAC *mac = NULL;
    EVP_MAC_CTX *ctx = NULL;
    OSSL_PARAM params[2];
    char digest_name[] = "SHA256";
    size_t commitment_len = 0u;
    int ok = 0;

    mac = EVP_MAC_fetch(NULL, "HMAC", NULL);
    if (mac == NULL) {
        goto cleanup;
    }
    ctx = EVP_MAC_CTX_new(mac);
    if (ctx == NULL) {
        goto cleanup;
    }

    params[0] = OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_DIGEST, digest_name, 0u);
    params[1] = OSSL_PARAM_construct_end();
    if (EVP_MAC_init(ctx, key, LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES, params) != 1 ||
        EVP_MAC_update(
            ctx,
            hybrid_detached_commitment_label,
            sizeof(hybrid_detached_commitment_label) - 1u) != 1 ||
        EVP_MAC_update(ctx, suite_domain, 2u) != 1 ||
        EVP_MAC_update(ctx, context->salt, LATTICRA_SEAL_HYBRID_SALT_BYTES) != 1 ||
        EVP_MAC_update(ctx, context->nonce, LATTICRA_SEAL_HYBRID_NONCE_BYTES) != 1 ||
        EVP_MAC_update(ctx, tag, LATTICRA_SEAL_HYBRID_TAG_BYTES) != 1 ||
        EVP_MAC_update(
            ctx,
            aad_length_be,
            LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES) != 1) {
        goto cleanup;
    }
    if (context->aad_len > 0u && EVP_MAC_update(ctx, context->aad, context->aad_len) != 1) {
        goto cleanup;
    }
    if (EVP_MAC_update(ctx, ciphertext_length_be, 8u) != 1) {
        goto cleanup;
    }
    if (ciphertext_len > 0u && EVP_MAC_update(ctx, ciphertext, ciphertext_len) != 1) {
        goto cleanup;
    }
    if (EVP_MAC_final(
            ctx,
            commitment,
            &commitment_len,
            LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) != 1 ||
        commitment_len != LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        goto cleanup;
    }

    ok = 1;

cleanup:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    return ok;
}
#else
static int hmac_sha256_detached_commitment_stream(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char suite_domain[2],
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    const unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES],
    const unsigned char ciphertext_length_be[8],
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES]) {
    HMAC_CTX *ctx = NULL;
    unsigned int commitment_len = 0u;
    int ok = 0;

    ctx = HMAC_CTX_new();
    if (ctx == NULL) {
        goto cleanup;
    }
    if (HMAC_Init_ex(ctx, key, LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES, EVP_sha256(), NULL) != 1 ||
        HMAC_Update(
            ctx,
            hybrid_detached_commitment_label,
            sizeof(hybrid_detached_commitment_label) - 1u) != 1 ||
        HMAC_Update(ctx, suite_domain, 2u) != 1 ||
        HMAC_Update(ctx, context->salt, LATTICRA_SEAL_HYBRID_SALT_BYTES) != 1 ||
        HMAC_Update(ctx, context->nonce, LATTICRA_SEAL_HYBRID_NONCE_BYTES) != 1 ||
        HMAC_Update(ctx, tag, LATTICRA_SEAL_HYBRID_TAG_BYTES) != 1 ||
        HMAC_Update(
            ctx,
            aad_length_be,
            LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES) != 1) {
        goto cleanup;
    }
    if (context->aad_len > 0u && HMAC_Update(ctx, context->aad, context->aad_len) != 1) {
        goto cleanup;
    }
    if (HMAC_Update(ctx, ciphertext_length_be, 8u) != 1) {
        goto cleanup;
    }
    if (ciphertext_len > 0u && HMAC_Update(ctx, ciphertext, ciphertext_len) != 1) {
        goto cleanup;
    }
    if (HMAC_Final(ctx, commitment, &commitment_len) != 1 ||
        commitment_len != LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        goto cleanup;
    }

    ok = 1;

cleanup:
    HMAC_CTX_free(ctx);
    return ok;
}
#endif

static int compute_detached_commitment(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES]) {
    unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_DETACHED_CALLER_AAD_LENGTH_BYTES];
    unsigned char ciphertext_length_be[8];
    unsigned char suite_domain[2];
    int ok;

    if (key == NULL || context == NULL || tag == NULL || commitment == NULL ||
        (ciphertext == NULL && ciphertext_len != 0u) ||
        (context->aad == NULL && context->aad_len != 0u) ||
        ciphertext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX ||
        context->aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX ||
        tag_len != LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        return 0;
    }

    suite_domain[0] = (unsigned char)LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM;
    suite_domain[1] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED;
    write_u64_be(aad_length_be, context->aad_len);
    write_u64_be(ciphertext_length_be, ciphertext_len);
    ok = hmac_sha256_detached_commitment_stream(
        key,
        suite_domain,
        context,
        ciphertext,
        ciphertext_len,
        tag,
        aad_length_be,
        ciphertext_length_be,
        commitment);
    OPENSSL_cleanse(aad_length_be, sizeof(aad_length_be));
    OPENSSL_cleanse(ciphertext_length_be, sizeof(ciphertext_length_be));
    OPENSSL_cleanse(suite_domain, sizeof(suite_domain));
    return ok;
}

static int compute_record_commitment(
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char *record,
    size_t ciphertext_len,
    const unsigned char *caller_aad,
    size_t caller_aad_len,
    unsigned char commitment[LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES]) {
    unsigned char aad_length_be[LATTICRA_SEAL_HYBRID_RECORD_CALLER_AAD_LENGTH_BYTES];
    int ok;

    if (key == NULL || record == NULL || commitment == NULL ||
        (caller_aad == NULL && caller_aad_len != 0u) ||
        ciphertext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX ||
        caller_aad_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        return 0;
    }

    write_u64_be(aad_length_be, caller_aad_len);
    ok = hmac_sha256_commitment_stream(
        key,
        aad_length_be,
        record,
        ciphertext_len,
        caller_aad,
        caller_aad_len,
        commitment);
    OPENSSL_cleanse(aad_length_be, sizeof(aad_length_be));
    return ok;
}

static int aes_256_gcm_encrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t *ciphertext_len,
    unsigned char *tag,
    latticra_seal_hybrid_envelope_result_t *result) {
    EVP_CIPHER_CTX *ctx = NULL;
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_CIPHER *cipher = NULL;
#else
    const EVP_CIPHER *cipher = NULL;
#endif
    int len = 0;
    int total = 0;
    int ok = 0;

    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        return 0;
    }

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    cipher = EVP_CIPHER_fetch(NULL, "AES-256-GCM", NULL);
#else
    cipher = EVP_aes_256_gcm();
#endif
    if (cipher == NULL) {
        goto cleanup;
    }

    if (EVP_EncryptInit_ex(ctx, cipher, NULL, NULL, NULL) != 1 ||
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, LATTICRA_SEAL_HYBRID_NONCE_BYTES, NULL) != 1 ||
        EVP_EncryptInit_ex(ctx, NULL, NULL, key, context->nonce) != 1) {
        goto cleanup;
    }

    if (context->aad_len > 0u &&
        EVP_EncryptUpdate(ctx, NULL, &len, context->aad, (int)context->aad_len) != 1) {
        goto cleanup;
    }

    len = 0;
    if (plaintext_len > 0u &&
        EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len) != 1) {
        goto cleanup;
    }
    total += len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + total, &len) != 1) {
        goto cleanup;
    }
    total += len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, LATTICRA_SEAL_HYBRID_TAG_BYTES, tag) != 1) {
        goto cleanup;
    }

    *ciphertext_len = (size_t)total;
    ok = 1;
    if (result != NULL) {
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
        result->aes_gcm_provider_api_used = 1u;
        result->aes_gcm_provider_cipher_fetched = 1u;
        result->aes_gcm_static_cipher_fallback_used = 0u;
#else
        result->aes_gcm_static_cipher_fallback_used = 1u;
#endif
        result->aes_gcm_96bit_nonce_configured = 1u;
        result->aes_gcm_128bit_tag_bound = 1u;
    }

cleanup:
    EVP_CIPHER_CTX_free(ctx);
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_CIPHER_free(cipher);
#endif
    return ok;
}

static int aes_256_gcm_decrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES],
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    unsigned char *plaintext,
    size_t *plaintext_len,
    int *auth_failed,
    latticra_seal_hybrid_envelope_result_t *result) {
    EVP_CIPHER_CTX *ctx = NULL;
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_CIPHER *cipher = NULL;
#else
    const EVP_CIPHER *cipher = NULL;
#endif
    int len = 0;
    int total = 0;
    int final_result;
    int ok = 0;

    *auth_failed = 0;
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        return 0;
    }

#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    cipher = EVP_CIPHER_fetch(NULL, "AES-256-GCM", NULL);
#else
    cipher = EVP_aes_256_gcm();
#endif
    if (cipher == NULL) {
        goto cleanup;
    }

    if (EVP_DecryptInit_ex(ctx, cipher, NULL, NULL, NULL) != 1 ||
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, LATTICRA_SEAL_HYBRID_NONCE_BYTES, NULL) != 1 ||
        EVP_DecryptInit_ex(ctx, NULL, NULL, key, context->nonce) != 1) {
        goto cleanup;
    }

    if (context->aad_len > 0u &&
        EVP_DecryptUpdate(ctx, NULL, &len, context->aad, (int)context->aad_len) != 1) {
        goto cleanup;
    }

    len = 0;
    if (ciphertext_len > 0u &&
        EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, (int)ciphertext_len) != 1) {
        goto cleanup;
    }
    total += len;

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, LATTICRA_SEAL_HYBRID_TAG_BYTES, (void *)tag) != 1) {
        goto cleanup;
    }

    final_result = EVP_DecryptFinal_ex(ctx, plaintext + total, &len);
    if (final_result == 1) {
        total += len;
        *plaintext_len = (size_t)total;
        ok = 1;
        if (result != NULL) {
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
            result->aes_gcm_provider_api_used = 1u;
            result->aes_gcm_provider_cipher_fetched = 1u;
            result->aes_gcm_static_cipher_fallback_used = 0u;
#else
            result->aes_gcm_static_cipher_fallback_used = 1u;
#endif
            result->aes_gcm_96bit_nonce_configured = 1u;
            result->aes_gcm_128bit_tag_bound = 1u;
        }
        goto cleanup;
    }

    *auth_failed = 1;

cleanup:
    EVP_CIPHER_CTX_free(ctx);
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
    EVP_CIPHER_free(cipher);
#endif
    return ok;
}

static latticra_status_t hybrid_encrypt_with_domain(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    unsigned kdf_domain,
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t framed_context;
    const latticra_seal_hybrid_envelope_context_t *crypto_context = context;
    unsigned char *detached_aad = NULL;
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    size_t detached_aad_len = 0u;
    int key_ready = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    memset(key, 0, sizeof(key));
    if (ciphertext_len != NULL) {
        *ciphertext_len = 0u;
    }

    if (!validate_context(context, out)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        return LATTICRA_STATUS_OK;
    }
    if (plaintext == NULL && plaintext_len != 0u) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext_len == NULL || ciphertext == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext_capacity < plaintext_len) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        return LATTICRA_STATUS_OK;
    }
    if (tag == NULL) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG);
        return LATTICRA_STATUS_OK;
    }
    if (tag_len != LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE);
        return LATTICRA_STATUS_OK;
    }
    if (encrypt_buffers_overlap(
            context,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_capacity,
            tag,
            tag_len)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }

    out->plaintext_size_bytes = plaintext_len;
    out->tag_size_bytes = tag_len;
    mark_kdf_domain(out, kdf_domain);

    if (kdf_domain == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED) {
        if (context->aad_len >
            LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES) {
            clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
            goto cleanup;
        }
        if (!build_detached_aad(context->aad, context->aad_len, &detached_aad, &detached_aad_len)) {
            clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
            goto cleanup;
        }
        framed_context = *context;
        framed_context.aad = detached_aad;
        framed_context.aad_len = detached_aad_len;
        crypto_context = &framed_context;
        out->aad_size_bytes = detached_aad_len;
        out->caller_aad_size_bytes = context->aad_len;
        out->detached_aad_size_bytes = detached_aad_len;
        out->detached_aad_framed = 1u;
        out->detached_aad_label_authenticated = 1u;
        out->detached_caller_aad_length_authenticated = 1u;
        out->detached_caller_aad_authenticated = 1u;
    }

    if (!derive_hybrid_key(crypto_context, kdf_domain, key, out)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        goto cleanup;
    }
    key_ready = 1;
    out->hkdf_extract_expand_performed = 1u;
    out->classical_shared_secret_bound = 1u;
    out->pqc_shared_secret_bound = 1u;
    out->hybrid_secret_length_framed = 1u;
    out->hybrid_secret_role_labeled = 1u;
    out->hybrid_secret_algorithm_labeled = 1u;
    out->hybrid_secret_order_bound = 1u;

    if (!aes_256_gcm_encrypt(
            crypto_context,
            key,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_len,
            tag,
            out)) {
        clear_detached_output_buffers(out, ciphertext, ciphertext_capacity, tag, tag_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
        goto cleanup;
    }

    out->ciphertext_size_bytes = *ciphertext_len;
    out->aes_gcm_encryption_performed = 1u;
    out->encryption_performed = 1u;
    out->secret_material_emitted = 0u;
    out->error = LATTICRA_SEAL_HYBRID_ENVELOPE_OK;
    copy_literal(out->operation_state, sizeof(out->operation_state), "encrypted");
    copy_literal(out->status, sizeof(out->status), "hybrid-envelope-encrypted");

cleanup:
    OPENSSL_cleanse(key, sizeof(key));
    if (detached_aad != NULL) {
        OPENSSL_cleanse(detached_aad, detached_aad_len);
        free(detached_aad);
    }
    if (key_ready) {
        out->key_material_zeroized = 1u;
    }
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_hybrid_envelope_encrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *plaintext,
    size_t plaintext_len,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char *tag,
    size_t tag_len,
    latticra_seal_hybrid_envelope_result_t *out) {
    return hybrid_encrypt_with_domain(
        context,
        plaintext,
        plaintext_len,
        ciphertext,
        ciphertext_capacity,
        ciphertext_len,
        tag,
        tag_len,
        LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED,
        out);
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    unsigned char commitment_key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    unsigned char computed_commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    latticra_status_t status;
    int commitment_key_ready = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    memset(commitment_key, 0, sizeof(commitment_key));
    memset(computed_commitment, 0, sizeof(computed_commitment));
    if (ciphertext_len != NULL) {
        *ciphertext_len = 0u;
    }
    out->plaintext_size_bytes = plaintext_len;
    out->tag_size_bytes = tag_len;
    out->detached_commitment_size_bytes = commitment_len;

    if (commitment == NULL) {
        clear_detached_committed_output_buffers(
            out, ciphertext, ciphertext_capacity, tag, tag_len, commitment, commitment_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_COMMITMENT);
        return LATTICRA_STATUS_OK;
    }
    if (commitment_len != LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        clear_detached_committed_output_buffers(
            out, ciphertext, ciphertext_capacity, tag, tag_len, commitment, commitment_len);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE);
        return LATTICRA_STATUS_OK;
    }
    if (encrypt_committed_buffers_overlap(
            context,
            plaintext,
            plaintext_len,
            ciphertext,
            ciphertext_capacity,
            tag,
            tag_len,
            commitment,
            commitment_len)) {
        clear_detached_committed_output_buffers(
            out, ciphertext, ciphertext_capacity, tag, tag_len, commitment, commitment_len);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }

    status = latticra_seal_hybrid_envelope_encrypt(
        context,
        plaintext,
        plaintext_len,
        ciphertext,
        ciphertext_capacity,
        ciphertext_len,
        tag,
        tag_len,
        out);
    if (status != LATTICRA_STATUS_OK ||
        out->error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK ||
        ciphertext_len == NULL) {
        clear_commitment_output_buffer(out, commitment, commitment_len);
        out->detached_commitment_size_bytes = commitment_len;
        return status;
    }

    if (!derive_detached_commitment_key(context, commitment_key, out)) {
        clear_detached_committed_output_buffers(
            out, ciphertext, ciphertext_capacity, tag, tag_len, commitment, commitment_len);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        return LATTICRA_STATUS_OK;
    }
    commitment_key_ready = 1;
    mark_detached_commitment_present(out);

    if (!compute_detached_commitment(
            commitment_key,
            context,
            ciphertext,
            *ciphertext_len,
            tag,
            tag_len,
            computed_commitment)) {
        clear_detached_committed_output_buffers(
            out, ciphertext, ciphertext_capacity, tag, tag_len, commitment, commitment_len);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
        out->detached_commitment_key_material_zeroized = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_ENCRYPTION_FAILURE);
        return LATTICRA_STATUS_OK;
    }

    memcpy(commitment, computed_commitment, sizeof(computed_commitment));
    mark_detached_commitment_present(out);
    copy_literal(out->operation_state, sizeof(out->operation_state), "committed-encrypted");
    copy_literal(out->status, sizeof(out->status), "hybrid-envelope-committed-encrypted");

    OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
    OPENSSL_cleanse(computed_commitment, sizeof(computed_commitment));
    if (commitment_key_ready) {
        out->detached_commitment_key_material_zeroized = 1u;
    }
    return LATTICRA_STATUS_OK;
}

static latticra_status_t hybrid_decrypt_with_domain(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    unsigned kdf_domain,
    latticra_seal_hybrid_envelope_result_t *out) {
    latticra_seal_hybrid_envelope_context_t framed_context;
    const latticra_seal_hybrid_envelope_context_t *crypto_context = context;
    unsigned char *detached_aad = NULL;
    unsigned char *staged_plaintext = NULL;
    unsigned char empty_plaintext[1];
    unsigned char key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    size_t detached_aad_len = 0u;
    size_t staged_plaintext_len = 0u;
    int auth_failed = 0;
    int key_ready = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    memset(key, 0, sizeof(key));
    memset(empty_plaintext, 0, sizeof(empty_plaintext));
    if (plaintext_len != NULL) {
        *plaintext_len = 0u;
    }

    if (!validate_context(context, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext == NULL && ciphertext_len != 0u) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_len == NULL || plaintext == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_capacity < ciphertext_len) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        return LATTICRA_STATUS_OK;
    }
    if (tag == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG);
        return LATTICRA_STATUS_OK;
    }
    if (tag_len != LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE);
        return LATTICRA_STATUS_OK;
    }
    if (decrypt_buffers_overlap(
            context,
            ciphertext,
            ciphertext_len,
            tag,
            tag_len,
            plaintext,
            plaintext_capacity)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }

    out->ciphertext_size_bytes = ciphertext_len;
    out->tag_size_bytes = tag_len;
    mark_kdf_domain(out, kdf_domain);

    if (kdf_domain == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED) {
        if (context->aad_len >
            LATTICRA_SEAL_HYBRID_MESSAGE_MAX - LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES) {
            clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
            goto cleanup;
        }
        if (!build_detached_aad(context->aad, context->aad_len, &detached_aad, &detached_aad_len)) {
            clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
            goto cleanup;
        }
        framed_context = *context;
        framed_context.aad = detached_aad;
        framed_context.aad_len = detached_aad_len;
        crypto_context = &framed_context;
        out->aad_size_bytes = detached_aad_len;
        out->caller_aad_size_bytes = context->aad_len;
        out->detached_aad_size_bytes = detached_aad_len;
        out->detached_aad_framed = 1u;
        out->detached_aad_label_authenticated = 1u;
        out->detached_caller_aad_length_authenticated = 1u;
        out->detached_caller_aad_authenticated = 1u;
    }

    if (!derive_hybrid_key(crypto_context, kdf_domain, key, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        goto cleanup;
    }
    key_ready = 1;
    out->hkdf_extract_expand_performed = 1u;
    out->classical_shared_secret_bound = 1u;
    out->pqc_shared_secret_bound = 1u;
    out->hybrid_secret_length_framed = 1u;
    out->hybrid_secret_role_labeled = 1u;
    out->hybrid_secret_algorithm_labeled = 1u;
    out->hybrid_secret_order_bound = 1u;

    if (ciphertext_len > 0u) {
        staged_plaintext = (unsigned char *)malloc(ciphertext_len);
        if (staged_plaintext == NULL) {
            clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
            goto cleanup;
        }
    }
    out->unauthenticated_plaintext_staged = 1u;

    if (!aes_256_gcm_decrypt(
            crypto_context,
            key,
            ciphertext,
            ciphertext_len,
            tag,
            staged_plaintext != NULL ? staged_plaintext : empty_plaintext,
            &staged_plaintext_len,
            &auth_failed,
            out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        if (auth_failed) {
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED);
        } else {
            result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
        }
        goto cleanup;
    }

    if (staged_plaintext_len > 0u && staged_plaintext == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
        goto cleanup;
    }

    if (staged_plaintext_len > 0u) {
        memcpy(plaintext, staged_plaintext, staged_plaintext_len);
    }
    *plaintext_len = staged_plaintext_len;
    out->plaintext_size_bytes = *plaintext_len;
    out->aes_gcm_decryption_performed = 1u;
    out->authentication_tag_verified = 1u;
    out->plaintext_released_after_authentication = 1u;
    out->decryption_performed = 1u;
    out->secret_material_emitted = 0u;
    out->error = LATTICRA_SEAL_HYBRID_ENVELOPE_OK;
    copy_literal(out->operation_state, sizeof(out->operation_state), "decrypted");
    copy_literal(out->status, sizeof(out->status), "hybrid-envelope-decrypted");

cleanup:
    OPENSSL_cleanse(key, sizeof(key));
    if (detached_aad != NULL) {
        OPENSSL_cleanse(detached_aad, detached_aad_len);
        free(detached_aad);
    }
    if (staged_plaintext != NULL) {
        OPENSSL_cleanse(staged_plaintext, ciphertext_len);
        free(staged_plaintext);
        out->staged_plaintext_cleared = 1u;
    } else if (out->unauthenticated_plaintext_staged) {
        OPENSSL_cleanse(empty_plaintext, sizeof(empty_plaintext));
        out->staged_plaintext_cleared = 1u;
    }
    if (key_ready) {
        out->key_material_zeroized = 1u;
    }
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_hybrid_envelope_decrypt(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    size_t tag_len,
    unsigned char *plaintext,
    size_t plaintext_capacity,
    size_t *plaintext_len,
    latticra_seal_hybrid_envelope_result_t *out) {
    return hybrid_decrypt_with_domain(
        context,
        ciphertext,
        ciphertext_len,
        tag,
        tag_len,
        plaintext,
        plaintext_capacity,
        plaintext_len,
        LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED,
        out);
}

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
    latticra_seal_hybrid_envelope_result_t *out) {
    unsigned char commitment_key[LATTICRA_SEAL_HYBRID_AEAD_KEY_BYTES];
    unsigned char expected_commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    latticra_status_t status;
    int commitment_key_zeroized = 0;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);
    memset(commitment_key, 0, sizeof(commitment_key));
    memset(expected_commitment, 0, sizeof(expected_commitment));
    if (plaintext_len != NULL) {
        *plaintext_len = 0u;
    }
    out->ciphertext_size_bytes = ciphertext_len;
    out->tag_size_bytes = tag_len;
    out->detached_commitment_size_bytes = commitment_len;

    if (commitment == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_COMMITMENT);
        return LATTICRA_STATUS_OK;
    }
    if (commitment_len != LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE);
        return LATTICRA_STATUS_OK;
    }
    if (!validate_context(context, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext == NULL && ciphertext_len != 0u) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (ciphertext_len > LATTICRA_SEAL_HYBRID_MESSAGE_MAX) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MESSAGE_TOO_LARGE);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_len == NULL || plaintext == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (plaintext_capacity < ciphertext_len) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (tag == NULL) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (tag_len != LATTICRA_SEAL_HYBRID_TAG_BYTES) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    if (decrypt_committed_buffers_overlap(
            context,
            ciphertext,
            ciphertext_len,
            tag,
            tag_len,
            commitment,
            commitment_len,
            plaintext,
            plaintext_capacity)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->unsafe_buffer_overlap_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT);
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }

    out->ciphertext_size_bytes = ciphertext_len;
    out->tag_size_bytes = tag_len;
    mark_kdf_domain(out, LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED);
    if (!derive_detached_commitment_key(context, commitment_key, out)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_KDF_FAILURE);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        out->detached_commitment_size_bytes = commitment_len;
        return LATTICRA_STATUS_OK;
    }
    out->hkdf_extract_expand_performed = 1u;
    out->classical_shared_secret_bound = 1u;
    out->pqc_shared_secret_bound = 1u;
    out->hybrid_secret_length_framed = 1u;
    out->hybrid_secret_role_labeled = 1u;
    out->hybrid_secret_algorithm_labeled = 1u;
    out->hybrid_secret_order_bound = 1u;
    mark_detached_commitment_precheck(out);

    if (!compute_detached_commitment(
            commitment_key,
            context,
            ciphertext,
            ciphertext_len,
            tag,
            tag_len,
            expected_commitment)) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_DECRYPTION_FAILURE);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        out->detached_commitment_key_material_zeroized = 1u;
        return LATTICRA_STATUS_OK;
    }

    if (CRYPTO_memcmp(
            expected_commitment,
            commitment,
            LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES) != 0) {
        clear_plaintext_output_buffer(out, plaintext, plaintext_capacity);
        out->detached_commitment_tampering_rejected = 1u;
        result_fail(out, LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED);
        OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
        OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
        out->detached_commitment_key_material_zeroized = 1u;
        return LATTICRA_STATUS_OK;
    }

    OPENSSL_cleanse(commitment_key, sizeof(commitment_key));
    OPENSSL_cleanse(expected_commitment, sizeof(expected_commitment));
    commitment_key_zeroized = 1;

    status = hybrid_decrypt_with_domain(
        context,
        ciphertext,
        ciphertext_len,
        tag,
        tag_len,
        plaintext,
        plaintext_capacity,
        plaintext_len,
        LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED,
        out);
    mark_detached_commitment_precheck(out);
    out->detached_commitment_verified = 1u;
    out->detached_commitment_key_material_zeroized = commitment_key_zeroized ? 1u : 0u;
    if (status == LATTICRA_STATUS_OK && out->error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        copy_literal(out->operation_state, sizeof(out->operation_state), "committed-decrypted");
        copy_literal(out->status, sizeof(out->status), "hybrid-envelope-committed-decrypted");
    }
    return status;
}

int latticra_seal_hybrid_envelope_result_is_authority_neutral(
    const latticra_seal_hybrid_envelope_result_t *result) {
    if (result == NULL) {
        return 0;
    }

    return result->secret_material_emitted == 0u &&
           result->production_crypto_claim_allowed == 0u &&
           result->fips_claim_allowed == 0u &&
           result->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_hybrid_envelope_report(
    const latticra_seal_hybrid_envelope_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL HYBRID ENVELOPE RESULT\n"
        "envelope_profile=%s\n"
        "kdf_algorithm=%s\n"
        "aead_algorithm=%s\n"
        "standards_source=%s\n"
        "classical_shared_secret_size_bytes=%zu\n"
        "pqc_shared_secret_size_bytes=%zu\n"
        "classical_shared_secret_nonzero=%u\n"
        "pqc_shared_secret_nonzero=%u\n"
        "salt_nonzero=%u\n"
        "nonce_nonzero=%u\n"
        "weak_shared_secret_rejected=%u\n"
        "weak_salt_rejected=%u\n"
        "weak_nonce_rejected=%u\n"
        "salt_size_bytes=%zu\n"
        "nonce_size_bytes=%zu\n"
        "aad_size_bytes=%zu\n"
        "caller_aad_size_bytes=%zu\n"
        "detached_aad_size_bytes=%zu\n"
        "record_aad_size_bytes=%zu\n"
        "plaintext_size_bytes=%zu\n"
        "ciphertext_size_bytes=%zu\n"
        "tag_size_bytes=%zu\n"
        "detached_commitment_size_bytes=%zu\n"
        "record_header_size_bytes=%zu\n"
        "record_protected_header_size_bytes=%zu\n"
        "record_commitment_size_bytes=%zu\n"
        "record_size_bytes=%zu\n"
        "detached_suite_id=%u\n"
        "detached_suite_kdf_bound=%u\n"
        "detached_key_commitment_present=%u\n"
        "detached_commitment_key_kdf_bound=%u\n"
        "detached_commitment_verified=%u\n"
        "detached_commitment_checked_before_decrypt=%u\n"
        "detached_commitment_caller_aad_bound=%u\n"
        "detached_commitment_input_streamed=%u\n"
        "detached_commitment_tampering_rejected=%u\n"
        "record_suite_id=%u\n"
        "record_suite_authenticated=%u\n"
        "record_kdf_domain_authenticated=%u\n"
        "record_suite_kdf_bound=%u\n"
        "record_salt_nonce_nonzero=%u\n"
        "record_header_shape_validated=%u\n"
        "malformed_record_rejected=%u\n"
        "record_key_commitment_present=%u\n"
        "record_commitment_key_kdf_bound=%u\n"
        "record_commitment_verified=%u\n"
        "record_commitment_checked_before_decrypt=%u\n"
        "record_commitment_caller_aad_bound=%u\n"
        "record_commitment_input_streamed=%u\n"
        "record_commitment_tampering_rejected=%u\n"
        "detached_aad_framed=%u\n"
        "detached_aad_label_authenticated=%u\n"
        "detached_caller_aad_length_authenticated=%u\n"
        "detached_caller_aad_authenticated=%u\n"
        "record_aad_framed=%u\n"
        "record_aad_label_authenticated=%u\n"
        "record_caller_aad_authenticated=%u\n"
        "hybrid_classical_pqc_secret_required=%u\n"
        "classical_shared_secret_bound=%u\n"
        "pqc_shared_secret_bound=%u\n"
        "hybrid_secret_length_framed=%u\n"
        "hybrid_secret_role_labeled=%u\n"
        "hybrid_secret_algorithm_labeled=%u\n"
        "hybrid_secret_order_bound=%u\n"
        "hybrid_secret_components_distinct=%u\n"
        "duplicate_hybrid_shared_secret_rejected=%u\n"
        "record_format_present=%u\n"
        "record_version=%u\n"
        "record_header_authenticated=%u\n"
        "hkdf_extract_expand_performed=%u\n"
        "hkdf_provider_api_used=%u\n"
        "hkdf_extract_expand_standard_api_used=%u\n"
        "hkdf_sha256_digest_bound=%u\n"
        "hkdf_manual_fallback_used=%u\n"
        "aes_gcm_provider_api_used=%u\n"
        "aes_gcm_provider_cipher_fetched=%u\n"
        "aes_gcm_96bit_nonce_configured=%u\n"
        "aes_gcm_128bit_tag_bound=%u\n"
        "aes_gcm_static_cipher_fallback_used=%u\n"
        "aes_gcm_encryption_performed=%u\n"
        "aes_gcm_decryption_performed=%u\n"
        "authentication_tag_verified=%u\n"
        "unauthenticated_plaintext_staged=%u\n"
        "staged_plaintext_cleared=%u\n"
        "plaintext_released_after_authentication=%u\n"
        "attached_record_sealed=%u\n"
        "attached_record_opened=%u\n"
        "attached_record_authenticated=%u\n"
        "kdf_domain_separated=%u\n"
        "kdf_domain_id=%u\n"
        "detached_kdf_domain=%u\n"
        "attached_record_kdf_domain=%u\n"
        "salt_generated=%u\n"
        "nonce_generated=%u\n"
        "random_bytes_ex_api_used=%u\n"
        "random_bytes_strength_bits_requested=%u\n"
        "random_bytes_manual_fallback_used=%u\n"
        "generated_salt_csprng_success=%u\n"
        "generated_nonce_csprng_success=%u\n"
        "generated_salt_random_bytes=%u\n"
        "generated_nonce_random_bytes=%u\n"
        "detached_salt_caller_supplied=%u\n"
        "detached_nonce_caller_supplied=%u\n"
        "attached_record_salt_generated=%u\n"
        "attached_record_nonce_generated=%u\n"
        "failed_salt_output_cleared=%u\n"
        "failed_nonce_output_cleared=%u\n"
        "failed_ciphertext_output_cleared=%u\n"
        "failed_tag_output_cleared=%u\n"
        "failed_commitment_output_cleared=%u\n"
        "failed_plaintext_output_cleared=%u\n"
        "failed_record_output_cleared=%u\n"
        "unsafe_buffer_overlap_rejected=%u\n"
        "encryption_performed=%u\n"
        "decryption_performed=%u\n"
        "secret_material_emitted=%u\n"
        "hkdf_intermediate_material_zeroized=%u\n"
        "key_material_zeroized=%u\n"
        "detached_commitment_key_material_zeroized=%u\n"
        "record_commitment_key_material_zeroized=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "operation_state=%s\n"
        "error=%s\n"
        "status=%s\n",
        result->envelope_profile,
        result->kdf_algorithm,
        result->aead_algorithm,
        result->standards_source,
        result->classical_shared_secret_size_bytes,
        result->pqc_shared_secret_size_bytes,
        result->classical_shared_secret_nonzero,
        result->pqc_shared_secret_nonzero,
        result->salt_nonzero,
        result->nonce_nonzero,
        result->weak_shared_secret_rejected,
        result->weak_salt_rejected,
        result->weak_nonce_rejected,
        result->salt_size_bytes,
        result->nonce_size_bytes,
        result->aad_size_bytes,
        result->caller_aad_size_bytes,
        result->detached_aad_size_bytes,
        result->record_aad_size_bytes,
        result->plaintext_size_bytes,
        result->ciphertext_size_bytes,
        result->tag_size_bytes,
        result->detached_commitment_size_bytes,
        result->record_header_size_bytes,
        result->record_protected_header_size_bytes,
        result->record_commitment_size_bytes,
        result->record_size_bytes,
        result->detached_suite_id,
        result->detached_suite_kdf_bound,
        result->detached_key_commitment_present,
        result->detached_commitment_key_kdf_bound,
        result->detached_commitment_verified,
        result->detached_commitment_checked_before_decrypt,
        result->detached_commitment_caller_aad_bound,
        result->detached_commitment_input_streamed,
        result->detached_commitment_tampering_rejected,
        result->record_suite_id,
        result->record_suite_authenticated,
        result->record_kdf_domain_authenticated,
        result->record_suite_kdf_bound,
        result->record_salt_nonce_nonzero,
        result->record_header_shape_validated,
        result->malformed_record_rejected,
        result->record_key_commitment_present,
        result->record_commitment_key_kdf_bound,
        result->record_commitment_verified,
        result->record_commitment_checked_before_decrypt,
        result->record_commitment_caller_aad_bound,
        result->record_commitment_input_streamed,
        result->record_commitment_tampering_rejected,
        result->detached_aad_framed,
        result->detached_aad_label_authenticated,
        result->detached_caller_aad_length_authenticated,
        result->detached_caller_aad_authenticated,
        result->record_aad_framed,
        result->record_aad_label_authenticated,
        result->record_caller_aad_authenticated,
        result->hybrid_classical_pqc_secret_required,
        result->classical_shared_secret_bound,
        result->pqc_shared_secret_bound,
        result->hybrid_secret_length_framed,
        result->hybrid_secret_role_labeled,
        result->hybrid_secret_algorithm_labeled,
        result->hybrid_secret_order_bound,
        result->hybrid_secret_components_distinct,
        result->duplicate_hybrid_shared_secret_rejected,
        result->record_format_present,
        result->record_version,
        result->record_header_authenticated,
        result->hkdf_extract_expand_performed,
        result->hkdf_provider_api_used,
        result->hkdf_extract_expand_standard_api_used,
        result->hkdf_sha256_digest_bound,
        result->hkdf_manual_fallback_used,
        result->aes_gcm_provider_api_used,
        result->aes_gcm_provider_cipher_fetched,
        result->aes_gcm_96bit_nonce_configured,
        result->aes_gcm_128bit_tag_bound,
        result->aes_gcm_static_cipher_fallback_used,
        result->aes_gcm_encryption_performed,
        result->aes_gcm_decryption_performed,
        result->authentication_tag_verified,
        result->unauthenticated_plaintext_staged,
        result->staged_plaintext_cleared,
        result->plaintext_released_after_authentication,
        result->attached_record_sealed,
        result->attached_record_opened,
        result->attached_record_authenticated,
        result->kdf_domain_separated,
        result->kdf_domain_id,
        result->detached_kdf_domain,
        result->attached_record_kdf_domain,
        result->salt_generated,
        result->nonce_generated,
        result->random_bytes_ex_api_used,
        result->random_bytes_strength_bits_requested,
        result->random_bytes_manual_fallback_used,
        result->generated_salt_csprng_success,
        result->generated_nonce_csprng_success,
        result->generated_salt_random_bytes,
        result->generated_nonce_random_bytes,
        result->detached_salt_caller_supplied,
        result->detached_nonce_caller_supplied,
        result->attached_record_salt_generated,
        result->attached_record_nonce_generated,
        result->failed_salt_output_cleared,
        result->failed_nonce_output_cleared,
        result->failed_ciphertext_output_cleared,
        result->failed_tag_output_cleared,
        result->failed_commitment_output_cleared,
        result->failed_plaintext_output_cleared,
        result->failed_record_output_cleared,
        result->unsafe_buffer_overlap_rejected,
        result->encryption_performed,
        result->decryption_performed,
        result->secret_material_emitted,
        result->hkdf_intermediate_material_zeroized,
        result->key_material_zeroized,
        result->detached_commitment_key_material_zeroized,
        result->record_commitment_key_material_zeroized,
        result->production_crypto_claim_allowed,
        result->fips_claim_allowed,
        result->runtime_authority_granted,
        result->operation_state,
        latticra_seal_hybrid_envelope_error_label(result->error),
        result->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
