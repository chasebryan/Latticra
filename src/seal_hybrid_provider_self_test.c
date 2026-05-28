#include "latticra/seal_hybrid_provider_self_test.h"

#include <openssl/core_names.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/params.h>
#include <openssl/x509.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_TRANSCRIPT_AAD_MAX 4096u
#define LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_MAX_ML_KEM_PUBLIC_KEY_DER_BYTES 2048u

static const unsigned char self_test_aad[] =
    "latticra-seal:hybrid-provider-self-test:v1";
static const unsigned char self_test_plaintext[] =
    "provider-derived P-256 and ML-KEM parameter-set secrets feed the Seal hybrid envelope";
static const unsigned char transcript_profile[] =
    "latticra-seal-hybrid-provider-transcript/v1";
static const unsigned char transcript_classical_algorithm_label[] =
    "classical-algorithm";
static const unsigned char transcript_pqc_algorithm_label[] =
    "pqc-algorithm";
static const unsigned char transcript_envelope_algorithm_label[] =
    "envelope-algorithm";
static const unsigned char transcript_context_label[] =
    "self-test-context";
static const unsigned char transcript_p256_sealer_public_key_label[] =
    "p256-sealer-public-key-spki";
static const unsigned char transcript_p256_opener_public_key_label[] =
    "p256-opener-public-key-spki";
static const unsigned char transcript_ml_kem_public_key_label[] =
    "ml-kem-public-key-spki";
static const unsigned char transcript_ml_kem_ciphertext_label[] =
    "ml-kem-ciphertext";

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static unsigned buffer_is_zero(const unsigned char *buffer, size_t buffer_len) {
    size_t index;
    unsigned char aggregate = 0u;

    for (index = 0u; index < buffer_len; index++) {
        aggregate = (unsigned char)(aggregate | buffer[index]);
    }

    return aggregate == 0u ? 1u : 0u;
}

static int append_transcript_bytes(
    unsigned char *buffer,
    size_t buffer_capacity,
    size_t *used,
    const unsigned char *bytes,
    size_t bytes_len) {
    if (buffer == NULL || used == NULL || *used > buffer_capacity ||
        (bytes == NULL && bytes_len != 0u) ||
        bytes_len > buffer_capacity - *used) {
        return 0;
    }
    if (bytes_len > 0u) {
        memcpy(buffer + *used, bytes, bytes_len);
    }
    *used += bytes_len;
    return 1;
}

static int append_transcript_u64(
    unsigned char *buffer,
    size_t buffer_capacity,
    size_t *used,
    size_t value) {
    unsigned char encoded[8];
    unsigned long long remaining = (unsigned long long)value;
    size_t index;

    for (index = 0u; index < sizeof(encoded); index++) {
        encoded[sizeof(encoded) - 1u - index] = (unsigned char)(remaining & 0xffu);
        remaining >>= 8u;
    }

    return append_transcript_bytes(buffer, buffer_capacity, used, encoded, sizeof(encoded));
}

static int append_transcript_field(
    unsigned char *buffer,
    size_t buffer_capacity,
    size_t *used,
    const unsigned char *bytes,
    size_t bytes_len) {
    return append_transcript_u64(buffer, buffer_capacity, used, bytes_len) &&
           append_transcript_bytes(buffer, buffer_capacity, used, bytes, bytes_len);
}

static int append_transcript_string(
    unsigned char *buffer,
    size_t buffer_capacity,
    size_t *used,
    const char *text) {
    return text != NULL &&
           append_transcript_field(
               buffer,
               buffer_capacity,
               used,
               (const unsigned char *)text,
               strlen(text));
}

static int serialize_public_key_der(
    EVP_PKEY *key,
    unsigned char *buffer,
    size_t buffer_capacity,
    size_t *buffer_len) {
    unsigned char *cursor;
    int der_len;
    int written;

    if (key == NULL || buffer == NULL || buffer_len == NULL) {
        return 0;
    }

    *buffer_len = 0u;
    der_len = i2d_PUBKEY(key, NULL);
    if (der_len <= 0 || (size_t)der_len > buffer_capacity) {
        return 0;
    }

    cursor = buffer;
    written = i2d_PUBKEY(key, &cursor);
    if (written != der_len) {
        return 0;
    }

    *buffer_len = (size_t)der_len;
    return 1;
}

static int deserialize_public_key_der(
    const unsigned char *buffer,
    size_t buffer_len,
    EVP_PKEY **out_key) {
    const unsigned char *cursor;
    EVP_PKEY *decoded_key;

    if (buffer == NULL || buffer_len == 0u || out_key == NULL ||
        buffer_len > (size_t)LONG_MAX) {
        return 0;
    }

    *out_key = NULL;
    cursor = buffer;
    decoded_key = d2i_PUBKEY(NULL, &cursor, (long)buffer_len);
    if (decoded_key == NULL || (size_t)(cursor - buffer) != buffer_len) {
        EVP_PKEY_free(decoded_key);
        return 0;
    }

    *out_key = decoded_key;
    return 1;
}

static int build_hybrid_transcript_aad(
    const char *ml_kem_algorithm_name,
    const unsigned char *p256_sealer_public_key,
    size_t p256_sealer_public_key_len,
    const unsigned char *p256_opener_public_key,
    size_t p256_opener_public_key_len,
    const unsigned char *ml_kem_public_key,
    size_t ml_kem_public_key_len,
    const unsigned char *ml_kem_ciphertext,
    size_t ml_kem_ciphertext_len,
    unsigned char *transcript,
    size_t transcript_capacity,
    size_t *transcript_len) {
    size_t used = 0u;

    if (ml_kem_algorithm_name == NULL ||
        p256_sealer_public_key == NULL ||
        p256_sealer_public_key_len == 0u ||
        p256_opener_public_key == NULL ||
        p256_opener_public_key_len == 0u ||
        ml_kem_public_key == NULL ||
        ml_kem_public_key_len == 0u ||
        ml_kem_ciphertext == NULL ||
        ml_kem_ciphertext_len == 0u ||
        transcript == NULL ||
        transcript_len == NULL) {
        return 0;
    }

    memset(transcript, 0, transcript_capacity);
    if (!append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_profile,
            sizeof(transcript_profile) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_classical_algorithm_label,
            sizeof(transcript_classical_algorithm_label) - 1u) ||
        !append_transcript_string(transcript, transcript_capacity, &used, "ECDH-P-256") ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_pqc_algorithm_label,
            sizeof(transcript_pqc_algorithm_label) - 1u) ||
        !append_transcript_string(transcript, transcript_capacity, &used, ml_kem_algorithm_name) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_envelope_algorithm_label,
            sizeof(transcript_envelope_algorithm_label) - 1u) ||
        !append_transcript_string(transcript, transcript_capacity, &used, "HKDF-SHA256+AES-256-GCM") ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_context_label,
            sizeof(transcript_context_label) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            self_test_aad,
            sizeof(self_test_aad) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_p256_sealer_public_key_label,
            sizeof(transcript_p256_sealer_public_key_label) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            p256_sealer_public_key,
            p256_sealer_public_key_len) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_p256_opener_public_key_label,
            sizeof(transcript_p256_opener_public_key_label) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            p256_opener_public_key,
            p256_opener_public_key_len) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_ml_kem_public_key_label,
            sizeof(transcript_ml_kem_public_key_label) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            ml_kem_public_key,
            ml_kem_public_key_len) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            transcript_ml_kem_ciphertext_label,
            sizeof(transcript_ml_kem_ciphertext_label) - 1u) ||
        !append_transcript_field(
            transcript,
            transcript_capacity,
            &used,
            ml_kem_ciphertext,
            ml_kem_ciphertext_len)) {
        OPENSSL_cleanse(transcript, transcript_capacity);
        return 0;
    }

    *transcript_len = used;
    return 1;
}

static int record_envelope_provider_crypto_evidence(
    latticra_seal_hybrid_provider_self_test_t *out,
    const latticra_seal_hybrid_envelope_result_t *seal_result,
    const latticra_seal_hybrid_envelope_result_t *open_result) {
    int hkdf_provider_evidence;
    int hkdf_sha256_evidence;
    int aes_gcm_provider_evidence;
    int aes_gcm_nonce_evidence;
    int aes_gcm_tag_evidence;
    int commitment_mac_provider_evidence;
    int commitment_mac_sha256_evidence;
    int commitment_constant_time_evidence;
    int random_bytes_ex_evidence;
    int no_legacy_fallback_evidence;

    if (out == NULL || seal_result == NULL || open_result == NULL) {
        return 0;
    }

    hkdf_provider_evidence =
        seal_result->hkdf_provider_api_used == 1u &&
        seal_result->hkdf_extract_expand_standard_api_used == 1u &&
        seal_result->hkdf_manual_fallback_used == 0u &&
        open_result->hkdf_provider_api_used == 1u &&
        open_result->hkdf_extract_expand_standard_api_used == 1u &&
        open_result->hkdf_manual_fallback_used == 0u;
    hkdf_sha256_evidence =
        seal_result->hkdf_sha256_digest_bound == 1u &&
        open_result->hkdf_sha256_digest_bound == 1u;
    aes_gcm_provider_evidence =
        seal_result->aes_gcm_provider_api_used == 1u &&
        seal_result->aes_gcm_provider_cipher_fetched == 1u &&
        seal_result->aes_gcm_static_cipher_fallback_used == 0u &&
        open_result->aes_gcm_provider_api_used == 1u &&
        open_result->aes_gcm_provider_cipher_fetched == 1u &&
        open_result->aes_gcm_static_cipher_fallback_used == 0u;
    aes_gcm_nonce_evidence =
        seal_result->aes_gcm_96bit_nonce_configured == 1u &&
        open_result->aes_gcm_96bit_nonce_configured == 1u;
    aes_gcm_tag_evidence =
        seal_result->aes_gcm_128bit_tag_bound == 1u &&
        open_result->aes_gcm_128bit_tag_bound == 1u;
    commitment_mac_provider_evidence =
        seal_result->commitment_mac_provider_api_used == 1u &&
        seal_result->commitment_mac_provider_fetched == 1u &&
        seal_result->commitment_mac_legacy_fallback_used == 0u &&
        open_result->commitment_mac_provider_api_used == 1u &&
        open_result->commitment_mac_provider_fetched == 1u &&
        open_result->commitment_mac_legacy_fallback_used == 0u;
    commitment_mac_sha256_evidence =
        seal_result->commitment_mac_hmac_sha256_digest_bound == 1u &&
        seal_result->commitment_mac_256bit_key_used == 1u &&
        seal_result->commitment_mac_input_streamed == 1u &&
        open_result->commitment_mac_hmac_sha256_digest_bound == 1u &&
        open_result->commitment_mac_256bit_key_used == 1u &&
        open_result->commitment_mac_input_streamed == 1u;
    commitment_constant_time_evidence =
        open_result->record_commitment_checked_before_decrypt == 1u &&
        open_result->record_commitment_constant_time_compare == 1u &&
        open_result->record_commitment_verified == 1u;
    random_bytes_ex_evidence =
        seal_result->random_bytes_ex_api_used == 1u &&
        seal_result->random_bytes_strength_bits_requested ==
            LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS &&
        seal_result->random_bytes_manual_fallback_used == 0u &&
        seal_result->generated_salt_csprng_success == 1u &&
        seal_result->generated_nonce_csprng_success == 1u &&
        seal_result->generated_salt_random_bytes == LATTICRA_SEAL_HYBRID_SALT_BYTES &&
        seal_result->generated_nonce_random_bytes == LATTICRA_SEAL_HYBRID_NONCE_BYTES;
    no_legacy_fallback_evidence =
        seal_result->hkdf_manual_fallback_used == 0u &&
        open_result->hkdf_manual_fallback_used == 0u &&
        seal_result->aes_gcm_static_cipher_fallback_used == 0u &&
        open_result->aes_gcm_static_cipher_fallback_used == 0u &&
        seal_result->commitment_mac_legacy_fallback_used == 0u &&
        open_result->commitment_mac_legacy_fallback_used == 0u &&
        seal_result->random_bytes_manual_fallback_used == 0u;

    if (!hkdf_provider_evidence ||
        !hkdf_sha256_evidence ||
        !aes_gcm_provider_evidence ||
        !aes_gcm_nonce_evidence ||
        !aes_gcm_tag_evidence ||
        !commitment_mac_provider_evidence ||
        !commitment_mac_sha256_evidence ||
        !commitment_constant_time_evidence ||
        !random_bytes_ex_evidence ||
        !no_legacy_fallback_evidence) {
        return 0;
    }

    out->hybrid_envelope_provider_crypto_evidence_bound = 1u;
    out->hybrid_envelope_provider_crypto_cases_total++;
    out->hybrid_envelope_hkdf_provider_cases_total++;
    out->hybrid_envelope_hkdf_sha256_cases_total++;
    out->hybrid_envelope_aes_gcm_provider_cases_total++;
    out->hybrid_envelope_aes_gcm_96bit_nonce_cases_total++;
    out->hybrid_envelope_aes_gcm_128bit_tag_cases_total++;
    out->hybrid_envelope_commitment_mac_provider_cases_total++;
    out->hybrid_envelope_commitment_mac_hmac_sha256_cases_total++;
    out->hybrid_envelope_commitment_constant_time_compare_cases_total++;
    out->hybrid_envelope_random_bytes_ex_cases_total++;
    out->hybrid_envelope_random_bytes_strength_bits_requested =
        LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS;
    out->hybrid_envelope_no_legacy_crypto_fallback_cases_total++;
    return 1;
}

static void self_test_init(latticra_seal_hybrid_provider_self_test_t *out) {
    memset(out, 0, sizeof(*out));
    copy_literal(
        out->self_test_profile,
        sizeof(out->self_test_profile),
        "latticra-seal-hybrid-provider-self-test/0.1");
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Seal Hybrid Provider Self-Test");
    copy_literal(out->classical_provider_name, sizeof(out->classical_provider_name), "OpenSSL-EVP");
    copy_literal(out->pqc_provider_name, sizeof(out->pqc_provider_name), "OpenSSL-EVP");
    copy_literal(out->classical_algorithm_name, sizeof(out->classical_algorithm_name), "ECDH-P-256");
    copy_literal(
        out->pqc_algorithm_name,
        sizeof(out->pqc_algorithm_name),
        "ML-KEM-512,ML-KEM-768,ML-KEM-1024");
    copy_literal(
        out->envelope_algorithm_name,
        sizeof(out->envelope_algorithm_name),
        "HKDF-SHA256+AES-256-GCM");
    copy_literal(
        out->standards_source,
        sizeof(out->standards_source),
        "NIST-SP-800-56A-REV3,NIST-FIPS-203,NIST-SP-800-56C-REV2,NIST-FIPS-197,NIST-SP-800-38D,NIST-SP-800-90A-REV1");
    out->provider_linked = 1u;
    out->secret_material_output_emitted = 0u;
    out->record_output_emitted = 0u;
    out->plaintext_output_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE;
    copy_literal(out->operation_state, sizeof(out->operation_state), "provider-self-test-not-started");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "provider-not-yet-used");
    copy_literal(out->status, sizeof(out->status), "provider-self-test-not-started");
}

static void self_test_fail(
    latticra_seal_hybrid_provider_self_test_t *out,
    latticra_seal_hybrid_provider_self_test_error_t error,
    const char *operation_state,
    const char *blocked_reason,
    const char *status) {
    out->secret_material_output_emitted = 0u;
    out->record_output_emitted = 0u;
    out->plaintext_output_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->error = error;
    copy_literal(out->operation_state, sizeof(out->operation_state), operation_state);
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), blocked_reason);
    copy_literal(out->status, sizeof(out->status), status);
}

static int generate_p256_key(EVP_PKEY **out_key) {
    EVP_PKEY_CTX *ctx;
    OSSL_PARAM params[2];
    char group_name[] = "prime256v1";
    int ok = 0;

    if (out_key == NULL) {
        return 0;
    }

    *out_key = NULL;
    ctx = EVP_PKEY_CTX_new_from_name(NULL, "EC", NULL);
    if (ctx == NULL) {
        return 0;
    }

    params[0] = OSSL_PARAM_construct_utf8_string(OSSL_PKEY_PARAM_GROUP_NAME, group_name, 0u);
    params[1] = OSSL_PARAM_construct_end();

    if (EVP_PKEY_keygen_init(ctx) > 0 &&
        EVP_PKEY_CTX_set_params(ctx, params) > 0 &&
        EVP_PKEY_keygen(ctx, out_key) > 0 &&
        *out_key != NULL) {
        ok = 1;
    }

    EVP_PKEY_CTX_free(ctx);
    return ok;
}

static int derive_ecdh_secret(
    EVP_PKEY *private_key,
    EVP_PKEY *peer_key,
    unsigned char out[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES],
    size_t *out_len) {
    EVP_PKEY_CTX *ctx;
    size_t secret_len = 0u;
    int ok = 0;

    if (private_key == NULL || peer_key == NULL || out == NULL || out_len == NULL) {
        return 0;
    }

    *out_len = 0u;
    ctx = EVP_PKEY_CTX_new_from_pkey(NULL, private_key, NULL);
    if (ctx == NULL) {
        return 0;
    }

    if (EVP_PKEY_derive_init(ctx) > 0 &&
        EVP_PKEY_derive_set_peer(ctx, peer_key) > 0 &&
        EVP_PKEY_derive(ctx, NULL, &secret_len) > 0 &&
        secret_len == LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES &&
        EVP_PKEY_derive(ctx, out, &secret_len) > 0 &&
        secret_len == LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES) {
        *out_len = secret_len;
        ok = 1;
    }

    EVP_PKEY_CTX_free(ctx);
    return ok;
}

static int generate_ml_kem_key(const char *algorithm_name, EVP_PKEY **out_key) {
    EVP_PKEY_CTX *ctx;
    int ok = 0;

    if (algorithm_name == NULL || out_key == NULL) {
        return 0;
    }

    *out_key = NULL;
    ctx = EVP_PKEY_CTX_new_from_name(NULL, algorithm_name, NULL);
    if (ctx == NULL) {
        return 0;
    }

    if (EVP_PKEY_keygen_init(ctx) > 0 &&
        EVP_PKEY_keygen(ctx, out_key) > 0 &&
        *out_key != NULL) {
        ok = 1;
    }

    EVP_PKEY_CTX_free(ctx);
    return ok;
}

static int ml_kem_encapsulate(
    EVP_PKEY *keypair,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char shared_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES],
    size_t *shared_secret_len);

static int ml_kem_decapsulate(
    EVP_PKEY *keypair,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    unsigned char shared_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES],
    size_t *shared_secret_len);

static int run_ml_kem_envelope_case(
    const char *algorithm_name,
    size_t expected_ciphertext_len,
    const unsigned char classical_sealer_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES],
    const unsigned char classical_opener_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES],
    const unsigned char *p256_sealer_public_key,
    size_t p256_sealer_public_key_len,
    const unsigned char *p256_opener_public_key,
    size_t p256_opener_public_key_len,
    latticra_seal_hybrid_provider_self_test_t *out,
    unsigned *key_generation_performed,
    unsigned *encapsulation_performed,
    unsigned *decapsulation_performed,
    unsigned *shared_secret_match,
    unsigned *ciphertext_bytes,
    unsigned *envelope_authenticated) {
    EVP_PKEY *ml_kem_key = NULL;
    EVP_PKEY *ml_kem_public_key_only = NULL;
    unsigned char ml_kem_sender_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES];
    unsigned char ml_kem_recipient_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES];
    unsigned char ml_kem_ciphertext
        [LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_MAX_ML_KEM_CIPHERTEXT_BYTES];
    unsigned char tampered_ml_kem_ciphertext
        [LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_MAX_ML_KEM_CIPHERTEXT_BYTES];
    unsigned char ml_kem_public_key
        [LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_MAX_ML_KEM_PUBLIC_KEY_DER_BYTES];
    unsigned char tampered_ml_kem_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES];
    unsigned char transcript_aad[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_TRANSCRIPT_AAD_MAX];
    unsigned char tampered_transcript_aad
        [LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_TRANSCRIPT_AAD_MAX];
    unsigned char record[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_RECORD_MAX];
    unsigned char recovered[sizeof(self_test_plaintext) - 1u];
    unsigned char wrong_secret_recovered[sizeof(self_test_plaintext) - 1u];
    unsigned char tamper_recovered[sizeof(self_test_plaintext) - 1u];
    size_t ml_kem_sender_secret_len = 0u;
    size_t ml_kem_recipient_secret_len = 0u;
    size_t ml_kem_ciphertext_len = 0u;
    size_t ml_kem_public_key_len = 0u;
    size_t tampered_ml_kem_secret_len = 0u;
    size_t transcript_aad_len = 0u;
    size_t record_len = 0u;
    size_t recovered_len = 0u;
    size_t wrong_secret_recovered_len = 42u;
    size_t tamper_recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;
    latticra_seal_hybrid_envelope_result_t wrong_secret_result;
    latticra_seal_hybrid_envelope_result_t tamper_result;
    int ok = 0;
    unsigned case_secret_zeroized = 0u;
    unsigned case_record_zeroized = 0u;
    unsigned case_plaintext_zeroized = 0u;

    memset(ml_kem_sender_secret, 0, sizeof(ml_kem_sender_secret));
    memset(ml_kem_recipient_secret, 0, sizeof(ml_kem_recipient_secret));
    memset(ml_kem_ciphertext, 0, sizeof(ml_kem_ciphertext));
    memset(tampered_ml_kem_ciphertext, 0, sizeof(tampered_ml_kem_ciphertext));
    memset(ml_kem_public_key, 0, sizeof(ml_kem_public_key));
    memset(tampered_ml_kem_secret, 0, sizeof(tampered_ml_kem_secret));
    memset(transcript_aad, 0, sizeof(transcript_aad));
    memset(tampered_transcript_aad, 0, sizeof(tampered_transcript_aad));
    memset(record, 0, sizeof(record));
    memset(recovered, 0, sizeof(recovered));
    memset(wrong_secret_recovered, 0x7f, sizeof(wrong_secret_recovered));
    memset(tamper_recovered, 0x7f, sizeof(tamper_recovered));
    memset(&seal_result, 0, sizeof(seal_result));
    memset(&open_result, 0, sizeof(open_result));
    memset(&wrong_secret_result, 0, sizeof(wrong_secret_result));
    memset(&tamper_result, 0, sizeof(tamper_result));

    if (!generate_ml_kem_key(algorithm_name, &ml_kem_key)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE,
            "ml-kem-provider-unavailable",
            "openssl-ml-kem-provider-unavailable",
            "hybrid-provider-self-test-provider-unavailable");
        goto cleanup;
    }
    out->pqc_provider_available = 1u;
    *key_generation_performed = 1u;
    if (EVP_PKEY_is_a(ml_kem_key, algorithm_name) != 1) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-keypair-algorithm-identity-failed",
            "openssl-ml-kem-keypair-algorithm-identity-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->ml_kem_keypair_algorithm_identity_verified_cases_total++;

    if (!serialize_public_key_der(
            ml_kem_key,
            ml_kem_public_key,
            sizeof(ml_kem_public_key),
            &ml_kem_public_key_len)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-public-key-transcript-failed",
            "openssl-ml-kem-public-key-transcript-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    if (!deserialize_public_key_der(
            ml_kem_public_key,
            ml_kem_public_key_len,
            &ml_kem_public_key_only)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-public-key-reimport-failed",
            "openssl-ml-kem-public-key-reimport-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->ml_kem_public_key_reimported_cases_total++;
    if (EVP_PKEY_is_a(ml_kem_public_key_only, algorithm_name) != 1) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-public-key-algorithm-identity-failed",
            "openssl-ml-kem-public-key-algorithm-identity-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->ml_kem_public_key_algorithm_identity_verified_cases_total++;

    if (!ml_kem_encapsulate(
            ml_kem_public_key_only,
            ml_kem_ciphertext,
            sizeof(ml_kem_ciphertext),
            &ml_kem_ciphertext_len,
            ml_kem_sender_secret,
            &ml_kem_sender_secret_len) ||
        ml_kem_ciphertext_len != expected_ciphertext_len) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-encapsulation-failed",
            "openssl-ml-kem-encapsulation-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    *encapsulation_performed = 1u;
    out->ml_kem_encapsulation_public_key_only_cases_total++;
    *ciphertext_bytes = (unsigned)ml_kem_ciphertext_len;

    if (!ml_kem_decapsulate(
            ml_kem_key,
            ml_kem_ciphertext,
            ml_kem_ciphertext_len,
            ml_kem_recipient_secret,
            &ml_kem_recipient_secret_len)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-decapsulation-failed",
            "openssl-ml-kem-decapsulation-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    *decapsulation_performed = 1u;
    out->pqc_secret_internal_buffers_used = 1u;

    if (ml_kem_sender_secret_len != sizeof(ml_kem_sender_secret) ||
        ml_kem_recipient_secret_len != sizeof(ml_kem_recipient_secret) ||
        CRYPTO_memcmp(
            ml_kem_sender_secret,
            ml_kem_recipient_secret,
            sizeof(ml_kem_sender_secret)) != 0) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-shared-secret-mismatch",
            "openssl-ml-kem-shared-secret-mismatch",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    *shared_secret_match = 1u;

    memcpy(tampered_ml_kem_ciphertext, ml_kem_ciphertext, ml_kem_ciphertext_len);
    tampered_ml_kem_ciphertext[ml_kem_ciphertext_len - 1u] ^= 0x01u;
    if (!ml_kem_decapsulate(
            ml_kem_key,
            tampered_ml_kem_ciphertext,
            ml_kem_ciphertext_len,
            tampered_ml_kem_secret,
            &tampered_ml_kem_secret_len) ||
        tampered_ml_kem_secret_len != sizeof(tampered_ml_kem_secret)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-tampered-decapsulation-failed",
            "openssl-ml-kem-tampered-decapsulation-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    if (CRYPTO_memcmp(
            ml_kem_sender_secret,
            tampered_ml_kem_secret,
            sizeof(ml_kem_sender_secret)) == 0) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "ml-kem-tampered-ciphertext-preserved-secret",
            "openssl-ml-kem-tampered-ciphertext-preserved-secret",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->ml_kem_tampered_ciphertext_shared_secret_mismatch_total++;
    out->ml_kem_ciphertext_tampering_rejected_total++;

    if (!build_hybrid_transcript_aad(
            algorithm_name,
            p256_sealer_public_key,
            p256_sealer_public_key_len,
            p256_opener_public_key,
            p256_opener_public_key_len,
            ml_kem_public_key,
            ml_kem_public_key_len,
            ml_kem_ciphertext,
            ml_kem_ciphertext_len,
            transcript_aad,
            sizeof(transcript_aad),
            &transcript_aad_len)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-transcript-build-failed",
            "provider-transcript-aad-build-failed",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }
    out->hybrid_transcript_aad_bound = 1u;
    out->provider_algorithm_transcript_bound = 1u;
    out->p256_public_key_transcript_bound = 1u;
    out->ml_kem_public_key_transcript_bound = 1u;
    out->ml_kem_ciphertext_transcript_bound = 1u;
    out->hybrid_transcript_cases_bound_total++;
    out->hybrid_transcript_aad_size_bytes += (unsigned)transcript_aad_len;
    out->ml_kem_public_key_transcript_bytes_total += (unsigned)ml_kem_public_key_len;
    out->ml_kem_ciphertext_transcript_bytes_total += (unsigned)ml_kem_ciphertext_len;
    if (out->p256_public_key_transcript_bytes == 0u) {
        out->p256_public_key_transcript_bytes =
            (unsigned)(p256_sealer_public_key_len + p256_opener_public_key_len);
    }

    if (latticra_seal_hybrid_envelope_seal_record(
            classical_sealer_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES,
            ml_kem_sender_secret,
            sizeof(ml_kem_sender_secret),
            transcript_aad,
            transcript_aad_len,
            self_test_plaintext,
            sizeof(self_test_plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &seal_result) != LATTICRA_STATUS_OK ||
        seal_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-envelope-seal-failed",
            "provider-secrets-did-not-seal-record",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }
    out->hybrid_envelope_records_sealed_total++;

    if (latticra_seal_hybrid_envelope_open_record(
            classical_opener_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES,
            ml_kem_recipient_secret,
            sizeof(ml_kem_recipient_secret),
            transcript_aad,
            transcript_aad_len,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) != LATTICRA_STATUS_OK ||
        open_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK ||
        recovered_len != sizeof(self_test_plaintext) - 1u ||
        CRYPTO_memcmp(recovered, self_test_plaintext, recovered_len) != 0) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-envelope-open-failed",
            "provider-secrets-did-not-open-record",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }
    out->hybrid_envelope_records_opened_total++;
    if (open_result.authentication_tag_verified == 1u) {
        out->hybrid_envelope_records_authenticated_total++;
        *envelope_authenticated = 1u;
    }
    if (!record_envelope_provider_crypto_evidence(out, &seal_result, &open_result)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-envelope-provider-crypto-evidence-missing",
            "seal-envelope-provider-crypto-evidence-missing",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }

    if (latticra_seal_hybrid_envelope_open_record(
            classical_opener_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES,
            tampered_ml_kem_secret,
            sizeof(tampered_ml_kem_secret),
            transcript_aad,
            transcript_aad_len,
            record,
            record_len,
            wrong_secret_recovered,
            sizeof(wrong_secret_recovered),
            &wrong_secret_recovered_len,
            &wrong_secret_result) != LATTICRA_STATUS_OK ||
        wrong_secret_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED ||
        wrong_secret_result.record_commitment_checked_before_decrypt != 1u ||
        wrong_secret_result.record_commitment_constant_time_compare != 1u ||
        wrong_secret_result.record_commitment_tampering_rejected != 1u ||
        wrong_secret_result.authentication_tag_verified != 0u ||
        wrong_secret_result.plaintext_released_after_authentication != 0u ||
        wrong_secret_recovered_len != 0u ||
        buffer_is_zero(wrong_secret_recovered, sizeof(wrong_secret_recovered)) != 1u) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-envelope-wrong-pqc-secret-accepted",
            "tampered-ml-kem-secret-opened-record",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }
    out->hybrid_envelope_wrong_pqc_secret_rejected = 1u;
    out->hybrid_envelope_wrong_pqc_secret_rejected_total++;
    out->hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total++;

    memcpy(tampered_transcript_aad, transcript_aad, transcript_aad_len);
    tampered_transcript_aad[transcript_aad_len - 1u] ^= 0x01u;
    if (latticra_seal_hybrid_envelope_open_record(
            classical_opener_secret,
            LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES,
            ml_kem_recipient_secret,
            sizeof(ml_kem_recipient_secret),
            tampered_transcript_aad,
            transcript_aad_len,
            record,
            record_len,
            tamper_recovered,
            sizeof(tamper_recovered),
            &tamper_recovered_len,
            &tamper_result) != LATTICRA_STATUS_OK ||
        tamper_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED ||
        tamper_result.record_commitment_tampering_rejected != 1u ||
        tamper_result.record_commitment_constant_time_compare != 1u ||
        tamper_result.authentication_tag_verified != 0u ||
        tamper_result.plaintext_released_after_authentication != 0u ||
        tamper_recovered_len != 0u ||
        buffer_is_zero(tamper_recovered, sizeof(tamper_recovered)) != 1u) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE,
            "hybrid-transcript-tamper-accepted",
            "provider-transcript-aad-tamper-not-rejected",
            "hybrid-provider-self-test-envelope-failure");
        goto cleanup;
    }
    out->hybrid_transcript_tampering_rejected = 1u;
    out->hybrid_transcript_tampering_rejected_total++;
    out->hybrid_transcript_tamper_constant_time_compare_cases_total++;
    ok = 1;

cleanup:
    EVP_PKEY_free(ml_kem_public_key_only);
    EVP_PKEY_free(ml_kem_key);
    OPENSSL_cleanse(ml_kem_sender_secret, sizeof(ml_kem_sender_secret));
    OPENSSL_cleanse(ml_kem_recipient_secret, sizeof(ml_kem_recipient_secret));
    OPENSSL_cleanse(ml_kem_ciphertext, sizeof(ml_kem_ciphertext));
    OPENSSL_cleanse(tampered_ml_kem_ciphertext, sizeof(tampered_ml_kem_ciphertext));
    OPENSSL_cleanse(ml_kem_public_key, sizeof(ml_kem_public_key));
    OPENSSL_cleanse(tampered_ml_kem_secret, sizeof(tampered_ml_kem_secret));
    OPENSSL_cleanse(transcript_aad, sizeof(transcript_aad));
    OPENSSL_cleanse(tampered_transcript_aad, sizeof(tampered_transcript_aad));
    OPENSSL_cleanse(record, sizeof(record));
    OPENSSL_cleanse(recovered, sizeof(recovered));
    OPENSSL_cleanse(wrong_secret_recovered, sizeof(wrong_secret_recovered));
    OPENSSL_cleanse(tamper_recovered, sizeof(tamper_recovered));
    case_secret_zeroized =
        buffer_is_zero(ml_kem_sender_secret, sizeof(ml_kem_sender_secret)) == 1u &&
        buffer_is_zero(ml_kem_recipient_secret, sizeof(ml_kem_recipient_secret)) == 1u &&
        buffer_is_zero(tampered_ml_kem_secret, sizeof(tampered_ml_kem_secret)) == 1u
            ? 1u
            : 0u;
    case_record_zeroized = buffer_is_zero(record, sizeof(record));
    case_plaintext_zeroized =
        buffer_is_zero(recovered, sizeof(recovered)) == 1u &&
        buffer_is_zero(wrong_secret_recovered, sizeof(wrong_secret_recovered)) == 1u &&
        buffer_is_zero(tamper_recovered, sizeof(tamper_recovered)) == 1u
            ? 1u
            : 0u;
    out->pqc_secret_zeroized =
        out->pqc_secret_zeroized == 1u && case_secret_zeroized == 1u ? 1u : 0u;
    out->record_buffer_zeroized =
        out->record_buffer_zeroized == 1u && case_record_zeroized == 1u ? 1u : 0u;
    out->plaintext_buffer_zeroized =
        out->plaintext_buffer_zeroized == 1u && case_plaintext_zeroized == 1u ? 1u : 0u;
    return ok;
}

static int ml_kem_encapsulate(
    EVP_PKEY *keypair,
    unsigned char *ciphertext,
    size_t ciphertext_capacity,
    size_t *ciphertext_len,
    unsigned char shared_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES],
    size_t *shared_secret_len) {
    EVP_PKEY_CTX *ctx;
    int ok = 0;

    if (keypair == NULL || ciphertext == NULL || ciphertext_len == NULL ||
        shared_secret == NULL || shared_secret_len == NULL) {
        return 0;
    }

    *ciphertext_len = ciphertext_capacity;
    *shared_secret_len = LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES;
    ctx = EVP_PKEY_CTX_new_from_pkey(NULL, keypair, NULL);
    if (ctx == NULL) {
        return 0;
    }

    if (EVP_PKEY_encapsulate_init(ctx, NULL) > 0 &&
        EVP_PKEY_encapsulate(ctx, NULL, ciphertext_len, NULL, shared_secret_len) > 0 &&
        *ciphertext_len <= ciphertext_capacity &&
        *shared_secret_len == LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES &&
        EVP_PKEY_encapsulate(
            ctx,
            ciphertext,
            ciphertext_len,
            shared_secret,
            shared_secret_len) > 0 &&
        *shared_secret_len == LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES) {
        ok = 1;
    }

    EVP_PKEY_CTX_free(ctx);
    return ok;
}

static int ml_kem_decapsulate(
    EVP_PKEY *keypair,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    unsigned char shared_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES],
    size_t *shared_secret_len) {
    EVP_PKEY_CTX *ctx;
    int ok = 0;

    if (keypair == NULL || ciphertext == NULL || shared_secret == NULL || shared_secret_len == NULL) {
        return 0;
    }

    *shared_secret_len = LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES;
    ctx = EVP_PKEY_CTX_new_from_pkey(NULL, keypair, NULL);
    if (ctx == NULL) {
        return 0;
    }

    if (EVP_PKEY_decapsulate_init(ctx, NULL) > 0 &&
        EVP_PKEY_decapsulate(ctx, NULL, shared_secret_len, ciphertext, ciphertext_len) > 0 &&
        *shared_secret_len == LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES &&
        EVP_PKEY_decapsulate(ctx, shared_secret, shared_secret_len, ciphertext, ciphertext_len) > 0 &&
        *shared_secret_len == LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES) {
        ok = 1;
    }

    EVP_PKEY_CTX_free(ctx);
    return ok;
}

const char *latticra_seal_hybrid_provider_self_test_error_label(
    latticra_seal_hybrid_provider_self_test_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_OK:
        return "ok";
    case LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE:
        return "provider-unavailable";
    case LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE:
        return "provider-failure";
    case LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ENVELOPE_FAILURE:
        return "envelope-failure";
    default:
        return "unknown";
    }
}

latticra_status_t latticra_seal_hybrid_provider_self_test_run(
    latticra_seal_hybrid_provider_self_test_t *out) {
    EVP_PKEY *alice_p256 = NULL;
    EVP_PKEY *bob_p256 = NULL;
    EVP_PKEY *alice_p256_public = NULL;
    EVP_PKEY *bob_p256_public = NULL;
    unsigned char alice_ecdh_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES];
    unsigned char bob_ecdh_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES];
    unsigned char alice_p256_public_key[512];
    unsigned char bob_p256_public_key[512];
    size_t alice_ecdh_secret_len = 0u;
    size_t bob_ecdh_secret_len = 0u;
    size_t alice_p256_public_key_len = 0u;
    size_t bob_p256_public_key_len = 0u;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    self_test_init(out);
    memset(alice_ecdh_secret, 0, sizeof(alice_ecdh_secret));
    memset(bob_ecdh_secret, 0, sizeof(bob_ecdh_secret));
    memset(alice_p256_public_key, 0, sizeof(alice_p256_public_key));
    memset(bob_p256_public_key, 0, sizeof(bob_p256_public_key));
    copy_literal(out->operation_state, sizeof(out->operation_state), "provider-self-test-started");

    if (!generate_p256_key(&alice_p256) || !generate_p256_key(&bob_p256)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE,
            "p256-provider-unavailable",
            "openssl-p256-provider-unavailable",
            "hybrid-provider-self-test-provider-unavailable");
        goto cleanup;
    }
    out->classical_provider_available = 1u;
    out->provider_runtime_used = 1u;
    out->p256_key_generation_performed = 1u;

    if (!serialize_public_key_der(
            alice_p256,
            alice_p256_public_key,
            sizeof(alice_p256_public_key),
            &alice_p256_public_key_len) ||
        !serialize_public_key_der(
            bob_p256,
            bob_p256_public_key,
            sizeof(bob_p256_public_key),
            &bob_p256_public_key_len)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "p256-public-key-transcript-failed",
            "openssl-p256-public-key-transcript-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    if (!deserialize_public_key_der(
            alice_p256_public_key,
            alice_p256_public_key_len,
            &alice_p256_public) ||
        !deserialize_public_key_der(
            bob_p256_public_key,
            bob_p256_public_key_len,
            &bob_p256_public)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "p256-public-key-reimport-failed",
            "openssl-p256-public-key-reimport-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }

    if (!derive_ecdh_secret(alice_p256, bob_p256_public, alice_ecdh_secret, &alice_ecdh_secret_len) ||
        !derive_ecdh_secret(bob_p256, alice_p256_public, bob_ecdh_secret, &bob_ecdh_secret_len)) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "p256-ecdh-derive-failed",
            "openssl-p256-ecdh-derive-failed",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->p256_peer_public_keys_reimported = 1u;
    out->p256_ecdh_peer_public_key_only = 1u;
    out->p256_ecdh_derive_performed = 1u;
    out->p256_shared_secret_bytes = (unsigned)alice_ecdh_secret_len;
    out->classical_secret_internal_buffers_used = 1u;

    if (alice_ecdh_secret_len != sizeof(alice_ecdh_secret) ||
        bob_ecdh_secret_len != sizeof(bob_ecdh_secret) ||
        CRYPTO_memcmp(alice_ecdh_secret, bob_ecdh_secret, sizeof(alice_ecdh_secret)) != 0) {
        self_test_fail(
            out,
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "p256-shared-secret-mismatch",
            "openssl-p256-shared-secret-mismatch",
            "hybrid-provider-self-test-provider-failure");
        goto cleanup;
    }
    out->p256_shared_secret_match = 1u;
    out->pqc_secret_zeroized = 1u;
    out->record_buffer_zeroized = 1u;
    out->plaintext_buffer_zeroized = 1u;

    if (!run_ml_kem_envelope_case(
            "ML-KEM-512",
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_512_CIPHERTEXT_BYTES,
            alice_ecdh_secret,
            bob_ecdh_secret,
            alice_p256_public_key,
            alice_p256_public_key_len,
            bob_p256_public_key,
            bob_p256_public_key_len,
            out,
            &out->ml_kem_512_key_generation_performed,
            &out->ml_kem_512_encapsulation_performed,
            &out->ml_kem_512_decapsulation_performed,
            &out->ml_kem_512_shared_secret_match,
            &out->ml_kem_512_ciphertext_bytes,
            &out->ml_kem_512_hybrid_envelope_authenticated)) {
        goto cleanup;
    }
    out->ml_kem_parameter_sets_tested++;

    if (!run_ml_kem_envelope_case(
            "ML-KEM-768",
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_768_CIPHERTEXT_BYTES,
            alice_ecdh_secret,
            bob_ecdh_secret,
            alice_p256_public_key,
            alice_p256_public_key_len,
            bob_p256_public_key,
            bob_p256_public_key_len,
            out,
            &out->ml_kem_768_key_generation_performed,
            &out->ml_kem_768_encapsulation_performed,
            &out->ml_kem_768_decapsulation_performed,
            &out->ml_kem_768_shared_secret_match,
            &out->ml_kem_768_ciphertext_bytes,
            &out->ml_kem_768_hybrid_envelope_authenticated)) {
        goto cleanup;
    }
    out->ml_kem_parameter_sets_tested++;

    if (!run_ml_kem_envelope_case(
            "ML-KEM-1024",
            LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_ML_KEM_1024_CIPHERTEXT_BYTES,
            alice_ecdh_secret,
            bob_ecdh_secret,
            alice_p256_public_key,
            alice_p256_public_key_len,
            bob_p256_public_key,
            bob_p256_public_key_len,
            out,
            &out->ml_kem_1024_key_generation_performed,
            &out->ml_kem_1024_encapsulation_performed,
            &out->ml_kem_1024_decapsulation_performed,
            &out->ml_kem_1024_shared_secret_match,
            &out->ml_kem_1024_ciphertext_bytes,
            &out->ml_kem_1024_hybrid_envelope_authenticated)) {
        goto cleanup;
    }
    out->ml_kem_parameter_sets_tested++;

    out->ml_kem_key_generation_performed = 1u;
    out->ml_kem_encapsulation_performed = 1u;
    out->ml_kem_decapsulation_performed = 1u;
    out->ml_kem_shared_secret_match = 1u;
    out->ml_kem_shared_secret_bytes = LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES;
    out->hybrid_envelope_record_sealed = 1u;
    out->hybrid_envelope_record_opened = 1u;
    out->hybrid_envelope_authenticated = 1u;
    out->hybrid_envelope_plaintext_recovered = 1u;
    out->error = LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_OK;
    copy_literal(out->operation_state, sizeof(out->operation_state), "hybrid-provider-self-test-passed");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "authority-remains-denied");
    copy_literal(out->status, sizeof(out->status), "hybrid-provider-self-test-passed");

cleanup:
    EVP_PKEY_free(bob_p256_public);
    EVP_PKEY_free(alice_p256_public);
    EVP_PKEY_free(bob_p256);
    EVP_PKEY_free(alice_p256);
    OPENSSL_cleanse(alice_ecdh_secret, sizeof(alice_ecdh_secret));
    OPENSSL_cleanse(bob_ecdh_secret, sizeof(bob_ecdh_secret));
    OPENSSL_cleanse(alice_p256_public_key, sizeof(alice_p256_public_key));
    OPENSSL_cleanse(bob_p256_public_key, sizeof(bob_p256_public_key));

    out->classical_secret_zeroized =
        buffer_is_zero(alice_ecdh_secret, sizeof(alice_ecdh_secret)) == 1u &&
        buffer_is_zero(bob_ecdh_secret, sizeof(bob_ecdh_secret)) == 1u
            ? 1u
            : 0u;
    return LATTICRA_STATUS_OK;
}

int latticra_seal_hybrid_provider_self_test_is_authority_neutral(
    const latticra_seal_hybrid_provider_self_test_t *self_test) {
    if (self_test == NULL) {
        return 0;
    }

    return self_test->secret_material_output_emitted == 0u &&
           self_test->record_output_emitted == 0u &&
           self_test->plaintext_output_emitted == 0u &&
           self_test->production_crypto_claim_allowed == 0u &&
           self_test->fips_claim_allowed == 0u &&
           self_test->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_hybrid_provider_self_test_report(
    const latticra_seal_hybrid_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (self_test == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL HYBRID PROVIDER SELF-TEST\n"
        "self_test_profile=%s\n"
        "formal_title=%s\n"
        "classical_provider_name=%s\n"
        "pqc_provider_name=%s\n"
        "classical_algorithm_name=%s\n"
        "pqc_algorithm_name=%s\n"
        "envelope_algorithm_name=%s\n"
        "standards_source=%s\n"
        "provider_linked=%u\n"
        "classical_provider_available=%u\n"
        "pqc_provider_available=%u\n"
        "provider_runtime_used=%u\n"
        "p256_key_generation_performed=%u\n"
        "p256_peer_public_keys_reimported=%u\n"
        "p256_ecdh_peer_public_key_only=%u\n"
        "p256_ecdh_derive_performed=%u\n"
        "p256_shared_secret_match=%u\n"
        "p256_shared_secret_bytes=%u\n"
        "ml_kem_key_generation_performed=%u\n"
        "ml_kem_encapsulation_performed=%u\n"
        "ml_kem_decapsulation_performed=%u\n"
        "ml_kem_shared_secret_match=%u\n"
        "ml_kem_shared_secret_bytes=%u\n"
        "ml_kem_keypair_algorithm_identity_verified_cases_total=%u\n"
        "ml_kem_public_key_reimported_cases_total=%u\n"
        "ml_kem_public_key_algorithm_identity_verified_cases_total=%u\n"
        "ml_kem_encapsulation_public_key_only_cases_total=%u\n"
        "ml_kem_tampered_ciphertext_shared_secret_mismatch_total=%u\n"
        "ml_kem_ciphertext_tampering_rejected_total=%u\n"
        "ml_kem_parameter_sets_tested=%u\n"
        "ml_kem_512_key_generation_performed=%u\n"
        "ml_kem_512_encapsulation_performed=%u\n"
        "ml_kem_512_decapsulation_performed=%u\n"
        "ml_kem_512_shared_secret_match=%u\n"
        "ml_kem_512_ciphertext_bytes=%u\n"
        "ml_kem_512_hybrid_envelope_authenticated=%u\n"
        "ml_kem_768_key_generation_performed=%u\n"
        "ml_kem_768_encapsulation_performed=%u\n"
        "ml_kem_768_decapsulation_performed=%u\n"
        "ml_kem_768_shared_secret_match=%u\n"
        "ml_kem_768_ciphertext_bytes=%u\n"
        "ml_kem_768_hybrid_envelope_authenticated=%u\n"
        "ml_kem_1024_key_generation_performed=%u\n"
        "ml_kem_1024_encapsulation_performed=%u\n"
        "ml_kem_1024_decapsulation_performed=%u\n"
        "ml_kem_1024_shared_secret_match=%u\n"
        "ml_kem_1024_ciphertext_bytes=%u\n"
        "ml_kem_1024_hybrid_envelope_authenticated=%u\n"
        "hybrid_envelope_record_sealed=%u\n"
        "hybrid_envelope_record_opened=%u\n"
        "hybrid_envelope_authenticated=%u\n"
        "hybrid_envelope_plaintext_recovered=%u\n"
        "hybrid_envelope_records_sealed_total=%u\n"
        "hybrid_envelope_records_opened_total=%u\n"
        "hybrid_envelope_records_authenticated_total=%u\n"
        "hybrid_envelope_provider_crypto_evidence_bound=%u\n"
        "hybrid_envelope_provider_crypto_cases_total=%u\n"
        "hybrid_envelope_hkdf_provider_cases_total=%u\n"
        "hybrid_envelope_hkdf_sha256_cases_total=%u\n"
        "hybrid_envelope_aes_gcm_provider_cases_total=%u\n"
        "hybrid_envelope_aes_gcm_96bit_nonce_cases_total=%u\n"
        "hybrid_envelope_aes_gcm_128bit_tag_cases_total=%u\n"
        "hybrid_envelope_commitment_mac_provider_cases_total=%u\n"
        "hybrid_envelope_commitment_mac_hmac_sha256_cases_total=%u\n"
        "hybrid_envelope_commitment_constant_time_compare_cases_total=%u\n"
        "hybrid_envelope_random_bytes_ex_cases_total=%u\n"
        "hybrid_envelope_random_bytes_strength_bits_requested=%u\n"
        "hybrid_envelope_no_legacy_crypto_fallback_cases_total=%u\n"
        "hybrid_transcript_aad_bound=%u\n"
        "hybrid_transcript_aad_size_bytes=%u\n"
        "hybrid_transcript_cases_bound_total=%u\n"
        "hybrid_transcript_tampering_rejected=%u\n"
        "hybrid_transcript_tampering_rejected_total=%u\n"
        "hybrid_transcript_tamper_constant_time_compare_cases_total=%u\n"
        "hybrid_envelope_wrong_pqc_secret_rejected=%u\n"
        "hybrid_envelope_wrong_pqc_secret_rejected_total=%u\n"
        "hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total=%u\n"
        "provider_algorithm_transcript_bound=%u\n"
        "p256_public_key_transcript_bound=%u\n"
        "p256_public_key_transcript_bytes=%u\n"
        "ml_kem_public_key_transcript_bound=%u\n"
        "ml_kem_public_key_transcript_bytes_total=%u\n"
        "ml_kem_ciphertext_transcript_bound=%u\n"
        "ml_kem_ciphertext_transcript_bytes_total=%u\n"
        "classical_secret_internal_buffers_used=%u\n"
        "pqc_secret_internal_buffers_used=%u\n"
        "secret_material_output_emitted=%u\n"
        "record_output_emitted=%u\n"
        "plaintext_output_emitted=%u\n"
        "classical_secret_zeroized=%u\n"
        "pqc_secret_zeroized=%u\n"
        "record_buffer_zeroized=%u\n"
        "plaintext_buffer_zeroized=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "operation_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        self_test->self_test_profile,
        self_test->formal_title,
        self_test->classical_provider_name,
        self_test->pqc_provider_name,
        self_test->classical_algorithm_name,
        self_test->pqc_algorithm_name,
        self_test->envelope_algorithm_name,
        self_test->standards_source,
        self_test->provider_linked,
        self_test->classical_provider_available,
        self_test->pqc_provider_available,
        self_test->provider_runtime_used,
        self_test->p256_key_generation_performed,
        self_test->p256_peer_public_keys_reimported,
        self_test->p256_ecdh_peer_public_key_only,
        self_test->p256_ecdh_derive_performed,
        self_test->p256_shared_secret_match,
        self_test->p256_shared_secret_bytes,
        self_test->ml_kem_key_generation_performed,
        self_test->ml_kem_encapsulation_performed,
        self_test->ml_kem_decapsulation_performed,
        self_test->ml_kem_shared_secret_match,
        self_test->ml_kem_shared_secret_bytes,
        self_test->ml_kem_keypair_algorithm_identity_verified_cases_total,
        self_test->ml_kem_public_key_reimported_cases_total,
        self_test->ml_kem_public_key_algorithm_identity_verified_cases_total,
        self_test->ml_kem_encapsulation_public_key_only_cases_total,
        self_test->ml_kem_tampered_ciphertext_shared_secret_mismatch_total,
        self_test->ml_kem_ciphertext_tampering_rejected_total,
        self_test->ml_kem_parameter_sets_tested,
        self_test->ml_kem_512_key_generation_performed,
        self_test->ml_kem_512_encapsulation_performed,
        self_test->ml_kem_512_decapsulation_performed,
        self_test->ml_kem_512_shared_secret_match,
        self_test->ml_kem_512_ciphertext_bytes,
        self_test->ml_kem_512_hybrid_envelope_authenticated,
        self_test->ml_kem_768_key_generation_performed,
        self_test->ml_kem_768_encapsulation_performed,
        self_test->ml_kem_768_decapsulation_performed,
        self_test->ml_kem_768_shared_secret_match,
        self_test->ml_kem_768_ciphertext_bytes,
        self_test->ml_kem_768_hybrid_envelope_authenticated,
        self_test->ml_kem_1024_key_generation_performed,
        self_test->ml_kem_1024_encapsulation_performed,
        self_test->ml_kem_1024_decapsulation_performed,
        self_test->ml_kem_1024_shared_secret_match,
        self_test->ml_kem_1024_ciphertext_bytes,
        self_test->ml_kem_1024_hybrid_envelope_authenticated,
        self_test->hybrid_envelope_record_sealed,
        self_test->hybrid_envelope_record_opened,
        self_test->hybrid_envelope_authenticated,
        self_test->hybrid_envelope_plaintext_recovered,
        self_test->hybrid_envelope_records_sealed_total,
        self_test->hybrid_envelope_records_opened_total,
        self_test->hybrid_envelope_records_authenticated_total,
        self_test->hybrid_envelope_provider_crypto_evidence_bound,
        self_test->hybrid_envelope_provider_crypto_cases_total,
        self_test->hybrid_envelope_hkdf_provider_cases_total,
        self_test->hybrid_envelope_hkdf_sha256_cases_total,
        self_test->hybrid_envelope_aes_gcm_provider_cases_total,
        self_test->hybrid_envelope_aes_gcm_96bit_nonce_cases_total,
        self_test->hybrid_envelope_aes_gcm_128bit_tag_cases_total,
        self_test->hybrid_envelope_commitment_mac_provider_cases_total,
        self_test->hybrid_envelope_commitment_mac_hmac_sha256_cases_total,
        self_test->hybrid_envelope_commitment_constant_time_compare_cases_total,
        self_test->hybrid_envelope_random_bytes_ex_cases_total,
        self_test->hybrid_envelope_random_bytes_strength_bits_requested,
        self_test->hybrid_envelope_no_legacy_crypto_fallback_cases_total,
        self_test->hybrid_transcript_aad_bound,
        self_test->hybrid_transcript_aad_size_bytes,
        self_test->hybrid_transcript_cases_bound_total,
        self_test->hybrid_transcript_tampering_rejected,
        self_test->hybrid_transcript_tampering_rejected_total,
        self_test->hybrid_transcript_tamper_constant_time_compare_cases_total,
        self_test->hybrid_envelope_wrong_pqc_secret_rejected,
        self_test->hybrid_envelope_wrong_pqc_secret_rejected_total,
        self_test->hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total,
        self_test->provider_algorithm_transcript_bound,
        self_test->p256_public_key_transcript_bound,
        self_test->p256_public_key_transcript_bytes,
        self_test->ml_kem_public_key_transcript_bound,
        self_test->ml_kem_public_key_transcript_bytes_total,
        self_test->ml_kem_ciphertext_transcript_bound,
        self_test->ml_kem_ciphertext_transcript_bytes_total,
        self_test->classical_secret_internal_buffers_used,
        self_test->pqc_secret_internal_buffers_used,
        self_test->secret_material_output_emitted,
        self_test->record_output_emitted,
        self_test->plaintext_output_emitted,
        self_test->classical_secret_zeroized,
        self_test->pqc_secret_zeroized,
        self_test->record_buffer_zeroized,
        self_test->plaintext_buffer_zeroized,
        self_test->production_crypto_claim_allowed,
        self_test->fips_claim_allowed,
        self_test->runtime_authority_granted,
        self_test->operation_state,
        self_test->blocked_reason,
        latticra_seal_hybrid_provider_self_test_error_label(self_test->error),
        self_test->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
