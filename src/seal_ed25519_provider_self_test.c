#include "latticra/seal_ed25519_provider_self_test.h"

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

static const unsigned char self_test_message[] =
    "latticra-seal ed25519 provider self-test signs original message bytes";

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

const char *latticra_seal_ed25519_provider_self_test_error_label(
    latticra_seal_ed25519_provider_self_test_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_OK:
        return "ok";
    case LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE:
        return "provider-unavailable";
    case LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_FAILURE:
        return "provider-failure";
    default:
        return "unknown";
    }
}

static void self_test_init(latticra_seal_ed25519_provider_self_test_t *self_test) {
    memset(self_test, 0, sizeof(*self_test));
    copy_literal(
        self_test->self_test_profile,
        sizeof(self_test->self_test_profile),
        "latticra-seal-ed25519-provider-self-test/0.1");
    copy_literal(
        self_test->formal_title,
        sizeof(self_test->formal_title),
        "Latticra Seal Ed25519 Provider Self-Test");
    copy_literal(self_test->provider_name, sizeof(self_test->provider_name), "OpenSSL-EVP");
    copy_literal(self_test->signature_algorithm, sizeof(self_test->signature_algorithm), "Ed25519");
    copy_literal(
        self_test->standards_source,
        sizeof(self_test->standards_source),
        "NIST-FIPS-186-5,RFC-8032,OpenSSL-EVP-Ed25519");
    copy_literal(
        self_test->operation_scope,
        sizeof(self_test->operation_scope),
        "local-provider-self-test-no-runtime-authority");
    self_test->provider_linked = 1u;
    self_test->message_prehashed_before_signing = 0u;
    self_test->ed25519_private_key_exported = 0u;
    self_test->ed25519_private_key_output_emitted = 0u;
    self_test->ed25519_public_key_output_emitted = 0u;
    self_test->ed25519_signature_output_emitted = 0u;
    self_test->production_crypto_claim_allowed = 0u;
    self_test->fips_claim_allowed = 0u;
    self_test->signing_authority_granted = 0u;
    self_test->key_storage_allowed = 0u;
    self_test->network_lookup_allowed = 0u;
    self_test->runtime_authority_granted = 0u;
    copy_literal(self_test->operation_state, sizeof(self_test->operation_state), "blocked");
    copy_literal(self_test->blocked_reason, sizeof(self_test->blocked_reason), "invalid-input");
    self_test->error = LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_FAILURE;
    copy_literal(self_test->status, sizeof(self_test->status), "invalid-input");
}

static latticra_status_t provider_unavailable(
    latticra_seal_ed25519_provider_self_test_t *self_test) {
    copy_literal(
        self_test->operation_state,
        sizeof(self_test->operation_state),
        "ed25519-provider-unavailable");
    copy_literal(
        self_test->blocked_reason,
        sizeof(self_test->blocked_reason),
        "ed25519-provider-unavailable");
    self_test->error = LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_UNAVAILABLE;
    copy_literal(
        self_test->status,
        sizeof(self_test->status),
        "ed25519-provider-self-test-provider-unavailable");
    return LATTICRA_STATUS_OK;
}

static latticra_status_t provider_failure(
    latticra_seal_ed25519_provider_self_test_t *self_test,
    const char *reason) {
    copy_literal(self_test->operation_state, sizeof(self_test->operation_state), "ed25519-provider-failure");
    copy_literal(self_test->blocked_reason, sizeof(self_test->blocked_reason), reason);
    self_test->error = LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PROVIDER_FAILURE;
    copy_literal(self_test->status, sizeof(self_test->status), "ed25519-provider-self-test-provider-failure");
    return LATTICRA_STATUS_OK;
}

static int ed25519_sign(
    EVP_PKEY *private_key,
    const unsigned char *message,
    size_t message_len,
    unsigned char *signature,
    size_t *signature_len) {
    EVP_MD_CTX *ctx = NULL;
    int result = 0;

    if (private_key == NULL || message == NULL || signature == NULL || signature_len == NULL) {
        return 0;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        return 0;
    }

    *signature_len = LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES;
    if (EVP_DigestSignInit(ctx, NULL, NULL, NULL, private_key) == 1 &&
        EVP_DigestSign(ctx, signature, signature_len, message, message_len) == 1 &&
        *signature_len == LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES) {
        result = 1;
    }

    EVP_MD_CTX_free(ctx);
    return result;
}

static int ed25519_verify(
    EVP_PKEY *public_key,
    const unsigned char *message,
    size_t message_len,
    const unsigned char *signature,
    size_t signature_len) {
    EVP_MD_CTX *ctx = NULL;
    int result = -1;

    if (public_key == NULL || message == NULL || signature == NULL) {
        return -1;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        return -1;
    }

    if (EVP_DigestVerifyInit(ctx, NULL, NULL, NULL, public_key) == 1) {
        result = EVP_DigestVerify(ctx, signature, signature_len, message, message_len);
    }

    EVP_MD_CTX_free(ctx);
    return result;
}

latticra_status_t latticra_seal_ed25519_provider_self_test_run(
    latticra_seal_ed25519_provider_self_test_t *out) {
    EVP_PKEY_CTX *keygen_ctx = NULL;
    EVP_PKEY *private_key = NULL;
    EVP_PKEY *public_key = NULL;
    unsigned char public_key_bytes[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PUBLIC_KEY_BYTES];
    unsigned char signature[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES];
    unsigned char tampered_message[sizeof(self_test_message) - 1u];
    unsigned char tampered_signature[LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_SIGNATURE_BYTES];
    size_t public_key_len = sizeof(public_key_bytes);
    size_t signature_len = sizeof(signature);
    int verify_result;
    int tampered_message_result;
    int tampered_signature_result;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    self_test_init(out);
    memset(public_key_bytes, 0, sizeof(public_key_bytes));
    memset(signature, 0, sizeof(signature));
    memset(tampered_message, 0, sizeof(tampered_message));
    memset(tampered_signature, 0, sizeof(tampered_signature));

    keygen_ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, NULL);
    if (keygen_ctx == NULL) {
        return provider_unavailable(out);
    }
    if (EVP_PKEY_keygen_init(keygen_ctx) <= 0 ||
        EVP_PKEY_keygen(keygen_ctx, &private_key) <= 0 ||
        private_key == NULL) {
        EVP_PKEY_CTX_free(keygen_ctx);
        return provider_unavailable(out);
    }
    out->provider_runtime_used = 1u;
    out->ed25519_key_generation_performed = 1u;

    if (EVP_PKEY_get_raw_public_key(private_key, public_key_bytes, &public_key_len) != 1 ||
        public_key_len != LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_PUBLIC_KEY_BYTES) {
        EVP_PKEY_free(private_key);
        EVP_PKEY_CTX_free(keygen_ctx);
        OPENSSL_cleanse(public_key_bytes, sizeof(public_key_bytes));
        OPENSSL_cleanse(signature, sizeof(signature));
        return provider_failure(out, "public-key-export-failed");
    }
    out->ed25519_public_key_export_performed = 1u;
    out->ed25519_public_key_bytes = (unsigned)public_key_len;

    public_key = EVP_PKEY_new_raw_public_key(EVP_PKEY_ED25519, NULL, public_key_bytes, public_key_len);
    if (public_key == NULL) {
        EVP_PKEY_free(private_key);
        EVP_PKEY_CTX_free(keygen_ctx);
        OPENSSL_cleanse(public_key_bytes, sizeof(public_key_bytes));
        OPENSSL_cleanse(signature, sizeof(signature));
        return provider_failure(out, "public-key-only-provider-key-failed");
    }

    if (!ed25519_sign(
            private_key,
            self_test_message,
            sizeof(self_test_message) - 1u,
            signature,
            &signature_len)) {
        EVP_PKEY_free(public_key);
        EVP_PKEY_free(private_key);
        EVP_PKEY_CTX_free(keygen_ctx);
        OPENSSL_cleanse(public_key_bytes, sizeof(public_key_bytes));
        OPENSSL_cleanse(signature, sizeof(signature));
        return provider_failure(out, "ed25519-sign-failed");
    }
    out->one_shot_sign_api_used = 1u;
    out->ed25519_signature_generation_performed = 1u;
    out->ed25519_signature_bytes = (unsigned)signature_len;

    verify_result = ed25519_verify(
        public_key,
        self_test_message,
        sizeof(self_test_message) - 1u,
        signature,
        signature_len);
    out->one_shot_verify_api_used = 1u;
    out->ed25519_signature_verification_performed = verify_result >= 0 ? 1u : 0u;
    out->ed25519_public_key_only_verification_performed = verify_result >= 0 ? 1u : 0u;
    out->ed25519_signature_valid = verify_result == 1 ? 1u : 0u;

    memcpy(tampered_message, self_test_message, sizeof(tampered_message));
    tampered_message[0] = (unsigned char)(tampered_message[0] ^ 0x01u);
    tampered_message_result = ed25519_verify(
        public_key,
        tampered_message,
        sizeof(tampered_message),
        signature,
        signature_len);
    out->ed25519_tampered_message_rejected = tampered_message_result == 0 ? 1u : 0u;

    memcpy(tampered_signature, signature, signature_len);
    tampered_signature[0] = (unsigned char)(tampered_signature[0] ^ 0x01u);
    tampered_signature_result = ed25519_verify(
        public_key,
        self_test_message,
        sizeof(self_test_message) - 1u,
        tampered_signature,
        signature_len);
    out->ed25519_tampered_signature_rejected = tampered_signature_result == 0 ? 1u : 0u;

    EVP_PKEY_free(public_key);
    EVP_PKEY_free(private_key);
    EVP_PKEY_CTX_free(keygen_ctx);
    OPENSSL_cleanse(tampered_message, sizeof(tampered_message));
    OPENSSL_cleanse(tampered_signature, sizeof(tampered_signature));
    OPENSSL_cleanse(public_key_bytes, sizeof(public_key_bytes));
    OPENSSL_cleanse(signature, sizeof(signature));
    out->public_key_buffer_zeroized = buffer_is_zero(public_key_bytes, sizeof(public_key_bytes));
    out->signature_buffer_zeroized = buffer_is_zero(signature, sizeof(signature));

    if (out->ed25519_signature_valid != 1u ||
        out->ed25519_tampered_message_rejected != 1u ||
        out->ed25519_tampered_signature_rejected != 1u ||
        out->public_key_buffer_zeroized != 1u ||
        out->signature_buffer_zeroized != 1u) {
        return provider_failure(out, "ed25519-self-test-invariant-failed");
    }

    copy_literal(
        out->operation_state,
        sizeof(out->operation_state),
        "ed25519-provider-self-test-passed");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "authority-remains-denied");
    out->error = LATTICRA_SEAL_ED25519_PROVIDER_SELF_TEST_OK;
    copy_literal(out->status, sizeof(out->status), "ed25519-provider-self-test-passed");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_ed25519_provider_self_test_is_authority_neutral(
    const latticra_seal_ed25519_provider_self_test_t *self_test) {
    if (self_test == NULL) {
        return 0;
    }

    return self_test->ed25519_private_key_output_emitted == 0u &&
           self_test->ed25519_signature_output_emitted == 0u &&
           self_test->production_crypto_claim_allowed == 0u &&
           self_test->fips_claim_allowed == 0u &&
           self_test->signing_authority_granted == 0u &&
           self_test->key_storage_allowed == 0u &&
           self_test->network_lookup_allowed == 0u &&
           self_test->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_ed25519_provider_self_test_report(
    const latticra_seal_ed25519_provider_self_test_t *self_test,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (self_test == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL ED25519 PROVIDER SELF-TEST\n"
        "self_test_profile=%s\n"
        "formal_title=%s\n"
        "provider_name=%s\n"
        "signature_algorithm=%s\n"
        "standards_source=%s\n"
        "operation_scope=%s\n"
        "provider_linked=%u\n"
        "provider_runtime_used=%u\n"
        "ed25519_key_generation_performed=%u\n"
        "ed25519_public_key_export_performed=%u\n"
        "ed25519_public_key_only_verification_performed=%u\n"
        "ed25519_signature_generation_performed=%u\n"
        "ed25519_signature_verification_performed=%u\n"
        "ed25519_signature_valid=%u\n"
        "ed25519_tampered_message_rejected=%u\n"
        "ed25519_tampered_signature_rejected=%u\n"
        "ed25519_public_key_bytes=%u\n"
        "ed25519_signature_bytes=%u\n"
        "one_shot_sign_api_used=%u\n"
        "one_shot_verify_api_used=%u\n"
        "message_prehashed_before_signing=%u\n"
        "ed25519_private_key_exported=%u\n"
        "ed25519_private_key_output_emitted=%u\n"
        "ed25519_public_key_output_emitted=%u\n"
        "ed25519_signature_output_emitted=%u\n"
        "public_key_buffer_zeroized=%u\n"
        "signature_buffer_zeroized=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "signing_authority_granted=%u\n"
        "key_storage_allowed=%u\n"
        "network_lookup_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "operation_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        self_test->self_test_profile,
        self_test->formal_title,
        self_test->provider_name,
        self_test->signature_algorithm,
        self_test->standards_source,
        self_test->operation_scope,
        self_test->provider_linked,
        self_test->provider_runtime_used,
        self_test->ed25519_key_generation_performed,
        self_test->ed25519_public_key_export_performed,
        self_test->ed25519_public_key_only_verification_performed,
        self_test->ed25519_signature_generation_performed,
        self_test->ed25519_signature_verification_performed,
        self_test->ed25519_signature_valid,
        self_test->ed25519_tampered_message_rejected,
        self_test->ed25519_tampered_signature_rejected,
        self_test->ed25519_public_key_bytes,
        self_test->ed25519_signature_bytes,
        self_test->one_shot_sign_api_used,
        self_test->one_shot_verify_api_used,
        self_test->message_prehashed_before_signing,
        self_test->ed25519_private_key_exported,
        self_test->ed25519_private_key_output_emitted,
        self_test->ed25519_public_key_output_emitted,
        self_test->ed25519_signature_output_emitted,
        self_test->public_key_buffer_zeroized,
        self_test->signature_buffer_zeroized,
        self_test->production_crypto_claim_allowed,
        self_test->fips_claim_allowed,
        self_test->signing_authority_granted,
        self_test->key_storage_allowed,
        self_test->network_lookup_allowed,
        self_test->runtime_authority_granted,
        self_test->operation_state,
        self_test->blocked_reason,
        latticra_seal_ed25519_provider_self_test_error_label(self_test->error),
        self_test->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
