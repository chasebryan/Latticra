#include "latticra/q_seal_ml_kem_provider_self_test.h"

#include "latticra/q_seal_ml_kem_secret_ops.h"

#include <openssl/evp.h>
#include <openssl/x509.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_MAX_PUBLIC_KEY_DER_BYTES 2048u

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

static void self_test_init(latticra_q_seal_ml_kem_provider_self_test_t *out) {
    memset(out, 0, sizeof(*out));
    copy_literal(
        out->self_test_profile,
        sizeof(out->self_test_profile),
        "latticra-q-seal-ml-kem-provider-self-test/0.1");
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Q-Seal ML-KEM Provider Self-Test");
    copy_literal(out->provider_name, sizeof(out->provider_name), "OpenSSL-EVP");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    out->expected_shared_secret_bytes = LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES;
    out->provider_linked = 1u;
    out->shared_secret_output_emitted = 0u;
    out->ciphertext_output_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->operation_state, sizeof(out->operation_state), "invalid");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-parameter-set");
    out->error = LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_INVALID_PARAMETER_SET;
    copy_literal(out->status, sizeof(out->status), "invalid-parameter-set");
}

static void self_test_fail(
    latticra_q_seal_ml_kem_provider_self_test_t *out,
    latticra_q_seal_ml_kem_provider_self_test_error_t error,
    const char *operation_state,
    const char *blocked_reason,
    const char *status) {
    out->shared_secret_match = 0u;
    out->shared_secret_output_emitted = 0u;
    out->ciphertext_output_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->operation_state, sizeof(out->operation_state), operation_state);
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), blocked_reason);
    out->error = error;
    copy_literal(out->status, sizeof(out->status), status);
}

const char *latticra_q_seal_ml_kem_provider_self_test_error_label(
    latticra_q_seal_ml_kem_provider_self_test_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_INVALID_PARAMETER_SET:
        return "invalid-parameter-set";
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE:
        return "provider-unavailable";
    case LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE:
        return "provider-failure";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_self_test_run(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    latticra_q_seal_ml_kem_provider_self_test_t *out) {
    latticra_q_seal_ml_kem_parameters_t parameters;
    EVP_PKEY_CTX *keygen_ctx = NULL;
    EVP_PKEY_CTX *encaps_ctx = NULL;
    EVP_PKEY_CTX *decaps_ctx = NULL;
    EVP_PKEY_CTX *tamper_decaps_ctx = NULL;
    EVP_PKEY *keypair = NULL;
    EVP_PKEY *public_key = NULL;
    unsigned char ciphertext[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_MAX_CIPHERTEXT_BYTES];
    unsigned char tampered_ciphertext
        [LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_MAX_CIPHERTEXT_BYTES];
    unsigned char public_key_der
        [LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_MAX_PUBLIC_KEY_DER_BYTES];
    unsigned char encapsulated_secret[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES];
    unsigned char decapsulated_secret[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES];
    unsigned char tampered_secret[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES];
    size_t ciphertext_len = 0u;
    size_t public_key_der_len = 0u;
    size_t encapsulated_secret_len = 0u;
    size_t decapsulated_secret_len = 0u;
    size_t tampered_secret_len = 0u;
    unsigned secrets_equal = 0u;
    unsigned tampered_secret_equal = 1u;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    self_test_init(out);
    memset(ciphertext, 0, sizeof(ciphertext));
    memset(tampered_ciphertext, 0, sizeof(tampered_ciphertext));
    memset(public_key_der, 0, sizeof(public_key_der));
    memset(encapsulated_secret, 0, sizeof(encapsulated_secret));
    memset(decapsulated_secret, 0, sizeof(decapsulated_secret));
    memset(tampered_secret, 0, sizeof(tampered_secret));

    if (latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        parameters.error != LATTICRA_Q_SEAL_ML_KEM_OK) {
        return LATTICRA_Q_SEAL_STATUS_OK;
    }

    out->parameter_set = parameters.parameter_set;
    out->security_category = parameters.security_category;
    out->expected_ciphertext_bytes = parameters.ciphertext_bytes;
    copy_literal(out->algorithm_name, sizeof(out->algorithm_name), parameters.parameter_set_name);
    copy_literal(out->operation_state, sizeof(out->operation_state), "provider-self-test-started");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "provider-not-yet-used");

    keygen_ctx = EVP_PKEY_CTX_new_from_name(NULL, parameters.parameter_set_name, NULL);
    if (keygen_ctx == NULL) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE,
            "provider-unavailable",
            "openssl-ml-kem-provider-unavailable",
            "ml-kem-provider-unavailable");
        goto cleanup;
    }

    out->provider_available = 1u;
    out->provider_runtime_used = 1u;

    if (EVP_PKEY_keygen_init(keygen_ctx) <= 0 ||
        EVP_PKEY_keygen(keygen_ctx, &keypair) <= 0 ||
        keypair == NULL) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-keygen-failed",
            "openssl-ml-kem-keygen-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->key_generation_performed = 1u;
    if (EVP_PKEY_is_a(keypair, parameters.parameter_set_name) != 1) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-keypair-algorithm-identity-failed",
            "openssl-ml-kem-keypair-algorithm-identity-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->keypair_algorithm_identity_verified = 1u;

    if (!serialize_public_key_der(
            keypair,
            public_key_der,
            sizeof(public_key_der),
            &public_key_der_len) ||
        !deserialize_public_key_der(public_key_der, public_key_der_len, &public_key)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-public-key-reimport-failed",
            "openssl-ml-kem-public-key-reimport-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->public_key_reimported = 1u;
    if (EVP_PKEY_is_a(public_key, parameters.parameter_set_name) != 1) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-public-key-algorithm-identity-failed",
            "openssl-ml-kem-public-key-algorithm-identity-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->public_key_algorithm_identity_verified = 1u;
    out->public_key_bytes = (unsigned)public_key_der_len;

    encaps_ctx = EVP_PKEY_CTX_new_from_pkey(NULL, public_key, NULL);
    if (encaps_ctx == NULL ||
        EVP_PKEY_encapsulate_init(encaps_ctx, NULL) <= 0 ||
        EVP_PKEY_encapsulate(
            encaps_ctx,
            NULL,
            &ciphertext_len,
            NULL,
            &encapsulated_secret_len) <= 0 ||
        ciphertext_len != parameters.ciphertext_bytes ||
        ciphertext_len > sizeof(ciphertext) ||
        encapsulated_secret_len != sizeof(encapsulated_secret)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-encapsulation-size-failed",
            "openssl-ml-kem-encapsulation-size-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }

    if (EVP_PKEY_encapsulate(
            encaps_ctx,
            ciphertext,
            &ciphertext_len,
            encapsulated_secret,
            &encapsulated_secret_len) <= 0 ||
        ciphertext_len != parameters.ciphertext_bytes ||
        encapsulated_secret_len != sizeof(encapsulated_secret)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-encapsulation-failed",
            "openssl-ml-kem-encapsulation-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->encapsulation_performed = 1u;
    out->encapsulation_public_key_only = 1u;
    out->observed_ciphertext_bytes = (unsigned)ciphertext_len;
    out->encapsulated_shared_secret_bytes = (unsigned)encapsulated_secret_len;

    decaps_ctx = EVP_PKEY_CTX_new_from_pkey(NULL, keypair, NULL);
    if (decaps_ctx == NULL ||
        EVP_PKEY_decapsulate_init(decaps_ctx, NULL) <= 0 ||
        EVP_PKEY_decapsulate(
            decaps_ctx,
            NULL,
            &decapsulated_secret_len,
            ciphertext,
            ciphertext_len) <= 0 ||
        decapsulated_secret_len != sizeof(decapsulated_secret)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-decapsulation-size-failed",
            "openssl-ml-kem-decapsulation-size-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }

    if (EVP_PKEY_decapsulate(
            decaps_ctx,
            decapsulated_secret,
            &decapsulated_secret_len,
            ciphertext,
            ciphertext_len) <= 0 ||
        decapsulated_secret_len != sizeof(decapsulated_secret)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-decapsulation-failed",
            "openssl-ml-kem-decapsulation-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->decapsulation_performed = 1u;
    out->decapsulated_shared_secret_bytes = (unsigned)decapsulated_secret_len;
    out->shared_secret_internal_buffers_used = 1u;

    if (latticra_q_seal_ml_kem_constant_time_equal(
            encapsulated_secret,
            decapsulated_secret,
            sizeof(encapsulated_secret),
            &secrets_equal) != LATTICRA_Q_SEAL_STATUS_OK ||
        secrets_equal != 1u) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-shared-secret-mismatch",
            "openssl-ml-kem-shared-secret-mismatch",
            "ml-kem-provider-failure");
        goto cleanup;
    }

    out->shared_secret_constant_time_compare = 1u;
    out->shared_secret_match = 1u;

    memcpy(tampered_ciphertext, ciphertext, ciphertext_len);
    tampered_ciphertext[ciphertext_len - 1u] ^= 0x01u;
    tampered_secret_len = sizeof(tampered_secret);
    tamper_decaps_ctx = EVP_PKEY_CTX_new_from_pkey(NULL, keypair, NULL);
    if (tamper_decaps_ctx == NULL ||
        EVP_PKEY_decapsulate_init(tamper_decaps_ctx, NULL) <= 0 ||
        EVP_PKEY_decapsulate(
            tamper_decaps_ctx,
            tampered_secret,
            &tampered_secret_len,
            tampered_ciphertext,
            ciphertext_len) <= 0 ||
        tampered_secret_len != sizeof(tampered_secret)) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-tampered-decapsulation-failed",
            "openssl-ml-kem-tampered-decapsulation-failed",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->tampered_ciphertext_decapsulation_performed = 1u;
    if (latticra_q_seal_ml_kem_constant_time_equal(
            encapsulated_secret,
            tampered_secret,
            sizeof(encapsulated_secret),
            &tampered_secret_equal) != LATTICRA_Q_SEAL_STATUS_OK ||
        tampered_secret_equal != 0u) {
        self_test_fail(
            out,
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_PROVIDER_FAILURE,
            "provider-tampered-ciphertext-preserved-secret",
            "openssl-ml-kem-tampered-ciphertext-preserved-secret",
            "ml-kem-provider-failure");
        goto cleanup;
    }
    out->tampered_ciphertext_constant_time_compare = 1u;
    out->tampered_ciphertext_shared_secret_mismatch = 1u;
    out->tampered_ciphertext_rejected = 1u;

    out->error = LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_OK;
    copy_literal(out->operation_state, sizeof(out->operation_state), "provider-self-test-passed");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "authority-remains-denied");
    copy_literal(out->status, sizeof(out->status), "ml-kem-provider-self-test-passed");

cleanup:
    EVP_PKEY_CTX_free(tamper_decaps_ctx);
    EVP_PKEY_CTX_free(decaps_ctx);
    EVP_PKEY_CTX_free(encaps_ctx);
    EVP_PKEY_CTX_free(keygen_ctx);
    EVP_PKEY_free(public_key);
    EVP_PKEY_free(keypair);

    (void)latticra_q_seal_ml_kem_secure_zero(public_key_der, sizeof(public_key_der));
    (void)latticra_q_seal_ml_kem_secure_zero(tampered_ciphertext, sizeof(tampered_ciphertext));
    (void)latticra_q_seal_ml_kem_secure_zero(
        encapsulated_secret,
        sizeof(encapsulated_secret));
    (void)latticra_q_seal_ml_kem_secure_zero(
        decapsulated_secret,
        sizeof(decapsulated_secret));
    (void)latticra_q_seal_ml_kem_secure_zero(
        tampered_secret,
        sizeof(tampered_secret));
    (void)latticra_q_seal_ml_kem_secure_zero(ciphertext, sizeof(ciphertext));
    out->shared_secret_zeroized =
        buffer_is_zero(encapsulated_secret, sizeof(encapsulated_secret)) == 1u &&
        buffer_is_zero(decapsulated_secret, sizeof(decapsulated_secret)) == 1u &&
        buffer_is_zero(tampered_secret, sizeof(tampered_secret)) == 1u
            ? 1u
            : 0u;
    out->ciphertext_zeroized =
        buffer_is_zero(ciphertext, sizeof(ciphertext)) == 1u &&
        buffer_is_zero(tampered_ciphertext, sizeof(tampered_ciphertext)) == 1u
            ? 1u
            : 0u;
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_provider_self_test_is_authority_neutral(
    const latticra_q_seal_ml_kem_provider_self_test_t *self_test) {
    if (self_test == NULL) {
        return 0;
    }

    return self_test->shared_secret_output_emitted == 0u &&
           self_test->ciphertext_output_emitted == 0u &&
           self_test->production_crypto_claim_allowed == 0u &&
           self_test->fips_claim_allowed == 0u &&
           self_test->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_self_test_report(
    const latticra_q_seal_ml_kem_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (self_test == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM PROVIDER SELF-TEST\n"
        "self_test_profile=%s\n"
        "formal_title=%s\n"
        "provider_name=%s\n"
        "algorithm_name=%s\n"
        "standards_source=%s\n"
        "parameter_set=%u\n"
        "security_category=%u\n"
        "expected_ciphertext_bytes=%u\n"
        "observed_ciphertext_bytes=%u\n"
        "expected_shared_secret_bytes=%u\n"
        "encapsulated_shared_secret_bytes=%u\n"
        "decapsulated_shared_secret_bytes=%u\n"
        "provider_linked=%u\n"
        "provider_available=%u\n"
        "provider_runtime_used=%u\n"
        "key_generation_performed=%u\n"
        "keypair_algorithm_identity_verified=%u\n"
        "public_key_reimported=%u\n"
        "public_key_algorithm_identity_verified=%u\n"
        "public_key_bytes=%u\n"
        "encapsulation_performed=%u\n"
        "encapsulation_public_key_only=%u\n"
        "decapsulation_performed=%u\n"
        "tampered_ciphertext_decapsulation_performed=%u\n"
        "tampered_ciphertext_shared_secret_mismatch=%u\n"
        "tampered_ciphertext_rejected=%u\n"
        "shared_secret_internal_buffers_used=%u\n"
        "shared_secret_match=%u\n"
        "shared_secret_constant_time_compare=%u\n"
        "tampered_ciphertext_constant_time_compare=%u\n"
        "shared_secret_zeroized=%u\n"
        "ciphertext_zeroized=%u\n"
        "shared_secret_output_emitted=%u\n"
        "ciphertext_output_emitted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "operation_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        self_test->self_test_profile,
        self_test->formal_title,
        self_test->provider_name,
        self_test->algorithm_name,
        self_test->standards_source,
        self_test->parameter_set,
        self_test->security_category,
        self_test->expected_ciphertext_bytes,
        self_test->observed_ciphertext_bytes,
        self_test->expected_shared_secret_bytes,
        self_test->encapsulated_shared_secret_bytes,
        self_test->decapsulated_shared_secret_bytes,
        self_test->provider_linked,
        self_test->provider_available,
        self_test->provider_runtime_used,
        self_test->key_generation_performed,
        self_test->keypair_algorithm_identity_verified,
        self_test->public_key_reimported,
        self_test->public_key_algorithm_identity_verified,
        self_test->public_key_bytes,
        self_test->encapsulation_performed,
        self_test->encapsulation_public_key_only,
        self_test->decapsulation_performed,
        self_test->tampered_ciphertext_decapsulation_performed,
        self_test->tampered_ciphertext_shared_secret_mismatch,
        self_test->tampered_ciphertext_rejected,
        self_test->shared_secret_internal_buffers_used,
        self_test->shared_secret_match,
        self_test->shared_secret_constant_time_compare,
        self_test->tampered_ciphertext_constant_time_compare,
        self_test->shared_secret_zeroized,
        self_test->ciphertext_zeroized,
        self_test->shared_secret_output_emitted,
        self_test->ciphertext_output_emitted,
        self_test->production_crypto_claim_allowed,
        self_test->fips_claim_allowed,
        self_test->runtime_authority_granted,
        self_test->operation_state,
        self_test->blocked_reason,
        latticra_q_seal_ml_kem_provider_self_test_error_label(self_test->error),
        self_test->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
