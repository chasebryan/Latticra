#include "latticra/seal_ed25519_verify.h"

#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static void bytes_to_hex(const unsigned char *bytes, size_t bytes_len, char *out, size_t out_len) {
    size_t index;

    if (out_len == 0u) {
        return;
    }

    out[0] = '\0';
    if (bytes == NULL || out_len < ((bytes_len * 2u) + 1u)) {
        return;
    }

    for (index = 0u; index < bytes_len; index++) {
        (void)snprintf(out + (index * 2u), out_len - (index * 2u), "%02x", bytes[index]);
    }
}

static int sha256_hex(const unsigned char *message, size_t message_len, char *out, size_t out_len) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0u;

    if (EVP_Digest(message, message_len, digest, &digest_len, EVP_sha256(), NULL) != 1) {
        return 0;
    }

    bytes_to_hex(digest, digest_len, out, out_len);
    return out[0] != '\0';
}

const char *latticra_seal_ed25519_verify_error_label(
    latticra_seal_ed25519_verify_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_ED25519_VERIFY_OK:
        return "ok";
    case LATTICRA_SEAL_ED25519_VERIFY_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_ED25519_VERIFY_INVALID_BACKEND:
        return "invalid-backend";
    case LATTICRA_SEAL_ED25519_VERIFY_MISSING_MESSAGE:
        return "missing-message";
    case LATTICRA_SEAL_ED25519_VERIFY_MESSAGE_TOO_LARGE:
        return "message-too-large";
    case LATTICRA_SEAL_ED25519_VERIFY_MISSING_PUBLIC_KEY:
        return "missing-public-key";
    case LATTICRA_SEAL_ED25519_VERIFY_INVALID_PUBLIC_KEY_SIZE:
        return "invalid-public-key-size";
    case LATTICRA_SEAL_ED25519_VERIFY_MISSING_SIGNATURE:
        return "missing-signature";
    case LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE_SIZE:
        return "invalid-signature-size";
    case LATTICRA_SEAL_ED25519_VERIFY_UNSUPPORTED_ALGORITHM:
        return "unsupported-algorithm";
    case LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE:
        return "invalid-signature";
    case LATTICRA_SEAL_ED25519_VERIFY_PROVIDER_FAILURE:
        return "verification-provider-failure";
    default:
        return "unknown";
    }
}

static void result_init(latticra_seal_ed25519_verify_result_t *result) {
    memset(result, 0, sizeof(*result));
    copy_literal(result->ed25519_verify_profile, sizeof(result->ed25519_verify_profile), "latticra-seal-ed25519-verify/0.1");
    copy_literal(result->message_digest_algorithm, sizeof(result->message_digest_algorithm), "SHA-256");
    copy_literal(result->signature_algorithm, sizeof(result->signature_algorithm), "Ed25519-development");
    copy_literal(result->crypto_verify_state, sizeof(result->crypto_verify_state), "invalid");
    result->cryptographic_verification_supported = 1u;
    result->cryptographic_verification_performed = 0u;
    result->verified = 0u;
    result->invalid = 1u;
    result->authority_usable = 0u;
    result->capability_gate_allowed = 0u;
    result->runtime_authority_granted = 0u;
    result->error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_INPUT;
    copy_literal(result->status, sizeof(result->status), "invalid-input");
}

static void copy_backend_metadata(
    const latticra_seal_crypto_verify_backend_t *backend,
    latticra_seal_ed25519_verify_result_t *out) {
    copy_literal(out->backend_profile, sizeof(out->backend_profile), backend->backend_profile);
    copy_literal(out->verification_policy_profile, sizeof(out->verification_policy_profile), backend->verification_policy_profile);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), backend->public_key_identity_label);
    copy_literal(out->signature_algorithm, sizeof(out->signature_algorithm), backend->signature_algorithm);
    copy_literal(out->trust_source, sizeof(out->trust_source), backend->trust_source);
}

static int openssl_ed25519_verify(
    const unsigned char *message,
    size_t message_len,
    const unsigned char *public_key,
    const unsigned char *signature) {
    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *ctx = NULL;
    int result = -1;

    pkey = EVP_PKEY_new_raw_public_key(EVP_PKEY_ED25519, NULL, public_key, LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES);
    if (pkey == NULL) {
        return -1;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        EVP_PKEY_free(pkey);
        return -1;
    }

    if (EVP_DigestVerifyInit(ctx, NULL, NULL, NULL, pkey) == 1) {
        result = EVP_DigestVerify(ctx, signature, LATTICRA_SEAL_ED25519_SIGNATURE_BYTES, message, message_len);
    }

    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    return result;
}

latticra_status_t latticra_seal_ed25519_verify_local(
    const latticra_seal_crypto_verify_backend_t *backend,
    const char *message_label,
    const unsigned char *message,
    size_t message_len,
    const unsigned char *public_key,
    size_t public_key_len,
    const unsigned char *signature,
    size_t signature_len,
    latticra_seal_ed25519_verify_result_t *out) {
    int verify_result;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out);

    if (backend == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (backend->error != LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_OK) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_BACKEND;
        copy_literal(out->status, sizeof(out->status), "invalid-backend");
        return LATTICRA_STATUS_OK;
    }

    copy_backend_metadata(backend, out);

    if (strcmp(backend->signature_algorithm, "Ed25519-development") != 0) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_UNSUPPORTED_ALGORITHM;
        copy_literal(out->crypto_verify_state, sizeof(out->crypto_verify_state), "unsupported-algorithm");
        copy_literal(out->status, sizeof(out->status), "unsupported-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (message == NULL || message_len == 0u) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_MISSING_MESSAGE;
        copy_literal(out->status, sizeof(out->status), "missing-message");
        return LATTICRA_STATUS_OK;
    }

    if (message_len > LATTICRA_SEAL_ED25519_MESSAGE_MAX) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_MESSAGE_TOO_LARGE;
        copy_literal(out->status, sizeof(out->status), "message-too-large");
        return LATTICRA_STATUS_OK;
    }

    if (public_key == NULL) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_MISSING_PUBLIC_KEY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key");
        return LATTICRA_STATUS_OK;
    }

    if (public_key_len != LATTICRA_SEAL_ED25519_PUBLIC_KEY_BYTES) {
        out->public_key_size_bytes = public_key_len;
        out->error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_PUBLIC_KEY_SIZE;
        copy_literal(out->status, sizeof(out->status), "invalid-public-key-size");
        return LATTICRA_STATUS_OK;
    }

    if (signature == NULL) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_MISSING_SIGNATURE;
        copy_literal(out->status, sizeof(out->status), "missing-signature");
        return LATTICRA_STATUS_OK;
    }

    if (signature_len != LATTICRA_SEAL_ED25519_SIGNATURE_BYTES) {
        out->signature_size_bytes = signature_len;
        out->error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE_SIZE;
        copy_literal(out->status, sizeof(out->status), "invalid-signature-size");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->message_label, sizeof(out->message_label), message_label != NULL ? message_label : "unspecified-message");
    out->message_size_bytes = message_len;
    out->public_key_size_bytes = public_key_len;
    out->signature_size_bytes = signature_len;

    if (!sha256_hex(message, message_len, out->message_digest_hex, sizeof(out->message_digest_hex))) {
        out->error = LATTICRA_SEAL_ED25519_VERIFY_PROVIDER_FAILURE;
        copy_literal(out->status, sizeof(out->status), "verification-provider-failure");
        return LATTICRA_STATUS_OK;
    }

    verify_result = openssl_ed25519_verify(message, message_len, public_key, signature);
    out->cryptographic_verification_performed = 1u;

    if (verify_result == 1) {
        out->verified = 1u;
        out->invalid = 0u;
        copy_literal(out->crypto_verify_state, sizeof(out->crypto_verify_state), "verified");
        out->error = LATTICRA_SEAL_ED25519_VERIFY_OK;
        copy_literal(out->status, sizeof(out->status), "ed25519-verified");
        return LATTICRA_STATUS_OK;
    }

    if (verify_result == 0) {
        out->verified = 0u;
        out->invalid = 1u;
        copy_literal(out->crypto_verify_state, sizeof(out->crypto_verify_state), "invalid-signature");
        out->error = LATTICRA_SEAL_ED25519_VERIFY_INVALID_SIGNATURE;
        copy_literal(out->status, sizeof(out->status), "invalid-signature");
        return LATTICRA_STATUS_OK;
    }

    out->verified = 0u;
    out->invalid = 1u;
    out->error = LATTICRA_SEAL_ED25519_VERIFY_PROVIDER_FAILURE;
    copy_literal(out->crypto_verify_state, sizeof(out->crypto_verify_state), "invalid");
    copy_literal(out->status, sizeof(out->status), "verification-provider-failure");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_ed25519_verify_result_is_authority_neutral(
    const latticra_seal_ed25519_verify_result_t *result) {
    if (result == NULL) {
        return 0;
    }

    return result->authority_usable == 0u &&
           result->capability_gate_allowed == 0u &&
           result->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_ed25519_verify_report(
    const latticra_seal_ed25519_verify_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL ED25519 VERIFY RESULT\n"
        "ed25519_verify_profile=%s\n"
        "backend_profile=%s\n"
        "verification_policy_profile=%s\n"
        "message_label=%s\n"
        "message_size_bytes=%zu\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "public_key_size_bytes=%zu\n"
        "signature_algorithm=%s\n"
        "signature_size_bytes=%zu\n"
        "trust_source=%s\n"
        "crypto_verify_state=%s\n"
        "cryptographic_verification_supported=%u\n"
        "cryptographic_verification_performed=%u\n"
        "verified=%u\n"
        "invalid=%u\n"
        "authority_usable=%u\n"
        "capability_gate_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        result->ed25519_verify_profile,
        result->backend_profile,
        result->verification_policy_profile,
        result->message_label,
        result->message_size_bytes,
        result->message_digest_algorithm,
        result->message_digest_hex,
        result->public_key_identity_label,
        result->public_key_size_bytes,
        result->signature_algorithm,
        result->signature_size_bytes,
        result->trust_source,
        result->crypto_verify_state,
        result->cryptographic_verification_supported,
        result->cryptographic_verification_performed,
        result->verified,
        result->invalid,
        result->authority_usable,
        result->capability_gate_allowed,
        result->runtime_authority_granted,
        latticra_seal_ed25519_verify_error_label(result->error),
        result->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
