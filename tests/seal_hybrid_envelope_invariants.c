#include "latticra/seal_hybrid_envelope.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int expect_generated_random_evidence(
    const latticra_seal_hybrid_envelope_result_t *result) {
    EXPECT_TRUE(result->random_bytes_ex_api_used == 1u, "random bytes ex api");
    EXPECT_TRUE(
        result->random_bytes_strength_bits_requested == LATTICRA_SEAL_HYBRID_RANDOM_STRENGTH_BITS,
        "random strength bits");
    EXPECT_TRUE(result->random_bytes_manual_fallback_used == 0u, "random no manual fallback");
    EXPECT_TRUE(result->generated_salt_csprng_success == 1u, "generated salt csprng");
    EXPECT_TRUE(result->generated_nonce_csprng_success == 1u, "generated nonce csprng");
    EXPECT_TRUE(
        result->generated_salt_random_bytes == LATTICRA_SEAL_HYBRID_SALT_BYTES,
        "generated salt random bytes");
    EXPECT_TRUE(
        result->generated_nonce_random_bytes == LATTICRA_SEAL_HYBRID_NONCE_BYTES,
        "generated nonce random bytes");
    return 0;
}

static int expect_generated_random_report(const char *rendered) {
    EXPECT_TRUE(strstr(rendered, "random_bytes_ex_api_used=1") != 0, "report random bytes ex");
    EXPECT_TRUE(
        strstr(rendered, "random_bytes_strength_bits_requested=256") != 0,
        "report random strength");
    EXPECT_TRUE(
        strstr(rendered, "random_bytes_manual_fallback_used=0") != 0,
        "report random no fallback");
    EXPECT_TRUE(
        strstr(rendered, "generated_salt_csprng_success=1") != 0,
        "report salt csprng");
    EXPECT_TRUE(
        strstr(rendered, "generated_nonce_csprng_success=1") != 0,
        "report nonce csprng");
    EXPECT_TRUE(strstr(rendered, "generated_salt_random_bytes=32") != 0, "report salt bytes");
    EXPECT_TRUE(strstr(rendered, "generated_nonce_random_bytes=12") != 0, "report nonce bytes");
    return 0;
}

static const unsigned char classical_shared_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
};

static const unsigned char pqc_shared_secret[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES] = {
    0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87,
    0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e, 0x0f,
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
};

static const unsigned char salt[LATTICRA_SEAL_HYBRID_SALT_BYTES] = {
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf
};

static const unsigned char nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES] = {
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb
};

static const unsigned char aad[] = "latticra-seal:hybrid-envelope:v1";
static const unsigned char plaintext[] = "Latticra substrate hybrid encryption keeps policy and bytes bound.";

static const unsigned char expected_fixture_ciphertext[] = {
    0x02, 0x77, 0x12, 0xc8, 0x5c, 0x13, 0xf8, 0xa3,
    0x7b, 0x0a, 0xc0, 0x76, 0x3c, 0x8e, 0x7b, 0x00,
    0x4a, 0xa9, 0x79, 0x0e, 0x94, 0x14, 0x82, 0x1d,
    0x55, 0x45, 0xf2, 0xbc, 0xe6, 0xe4, 0xaa, 0x5a,
    0x60, 0xc1, 0xff, 0x45, 0x10, 0x85, 0xc1, 0x85,
    0x0d, 0x38, 0x2d, 0x5c, 0x6b, 0x6a, 0x06, 0xd4,
    0xf5, 0xf4, 0x36, 0x61, 0xd4, 0x97, 0x43, 0x11,
    0x17, 0x9c, 0xca, 0xec, 0x7c, 0xec, 0xa1, 0xd2,
    0x5d, 0x6a
};

static const unsigned char expected_fixture_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x6d, 0x96, 0xba, 0xb1, 0x42, 0xb2, 0xa3, 0xa0,
    0x87, 0x56, 0xac, 0x8e, 0x13, 0x01, 0xa4, 0x35
};

static const unsigned char expected_fixture_detached_commitment
    [LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES] = {
    0x7c, 0xcd, 0x27, 0x76, 0xb0, 0xf0, 0x86, 0x96,
    0x2a, 0x82, 0x65, 0x08, 0x6e, 0x3d, 0x97, 0xb6,
    0xea, 0x05, 0xee, 0x9f, 0x42, 0xfc, 0x32, 0xb3,
    0xe2, 0x3f, 0x9b, 0x71, 0xfd, 0xd1, 0x40, 0x3a
};

static const unsigned char legacy_algorithm_unlabeled_ciphertext[] = {
    0x02, 0xd4, 0x8a, 0x18, 0xac, 0x90, 0x23, 0xdd,
    0xc6, 0x48, 0x6a, 0x77, 0xd7, 0x0c, 0x9c, 0xc0,
    0x49, 0x28, 0xd8, 0xf2, 0x56, 0xeb, 0x4f, 0xa7,
    0x3e, 0xd1, 0xff, 0xdc, 0xb1, 0x36, 0x15, 0x73,
    0x76, 0x9c, 0x0d, 0x96, 0x91, 0x5f, 0x12, 0xc9,
    0xb8, 0xea, 0x64, 0xf3, 0x9f, 0xf2, 0xc2, 0xff,
    0xf8, 0x69, 0x54, 0x12, 0xde, 0x57, 0x1c, 0x27,
    0x58, 0xc9, 0x76, 0x78, 0xb8, 0x24, 0x47, 0x69,
    0x9f, 0xbd
};

static const unsigned char legacy_algorithm_unlabeled_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x2a, 0xc2, 0xca, 0xb3, 0xed, 0x6d, 0x71, 0xf6,
    0x56, 0xd2, 0x00, 0x0e, 0xb3, 0x71, 0x29, 0x46
};

static const unsigned char legacy_detached_unrole_labeled_ciphertext[] = {
    0x2c, 0x9d, 0x17, 0xc7, 0xef, 0xef, 0xcb, 0x04,
    0xac, 0xd0, 0x04, 0xb6, 0x93, 0x8e, 0x04, 0xba,
    0xa3, 0x6d, 0x39, 0x75, 0xdf, 0xaa, 0xea, 0x53,
    0xca, 0xc2, 0xb1, 0x31, 0x6a, 0x98, 0xce, 0x9c,
    0x6f, 0x38, 0x99, 0x91, 0x27, 0xef, 0x64, 0x1e,
    0x89, 0xb0, 0xf0, 0x27, 0xbe, 0x0d, 0xaf, 0x8e,
    0x6e, 0xea, 0x11, 0x0a, 0xc2, 0xef, 0xf4, 0x92,
    0x11, 0xa8, 0x20, 0xf0, 0x58, 0x0c, 0x06, 0x95,
    0x1a, 0xe1
};

static const unsigned char legacy_detached_unrole_labeled_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x91, 0x6e, 0xf5, 0x9f, 0x13, 0x47, 0xd8, 0xc1,
    0xc2, 0x21, 0x76, 0x82, 0xa7, 0xd0, 0xb4, 0x6e
};

static const unsigned char legacy_detached_unsuite_bound_ciphertext[] = {
    0x0f, 0x49, 0x97, 0x69, 0x26, 0xcf, 0x9e, 0x2b,
    0xe7, 0x26, 0x7a, 0x12, 0x81, 0xc8, 0x20, 0x96,
    0x06, 0xba, 0xd7, 0x03, 0x88, 0xdd, 0xa5, 0x39,
    0xef, 0x3b, 0x62, 0x12, 0x8d, 0xe5, 0x18, 0xa6,
    0xa0, 0x8f, 0x91, 0x6c, 0x05, 0x44, 0xe2, 0xd1,
    0x10, 0xf0, 0xe8, 0x66, 0xf1, 0x66, 0xcf, 0x50,
    0x85, 0xf7, 0x05, 0x32, 0xf1, 0x80, 0x57, 0x5e,
    0xad, 0xea, 0xdb, 0x3f, 0xb4, 0x28, 0xee, 0x73,
    0x8a, 0xcf
};

static const unsigned char legacy_detached_unsuite_bound_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x66, 0x48, 0xf1, 0xfc, 0x29, 0x67, 0xea, 0xbc,
    0x7e, 0x12, 0x3d, 0xee, 0x8f, 0x8f, 0xec, 0xd4
};

static const unsigned char legacy_raw_aad_fixture_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x7e, 0x18, 0xe4, 0x3e, 0x6a, 0x4d, 0x1c, 0x25,
    0x0d, 0x1f, 0x92, 0xdc, 0xc7, 0xc0, 0xf8, 0xad
};

static const unsigned char expected_fixture_record_ciphertext[] = {
    0x25, 0x84, 0x4c, 0x73, 0x0f, 0xc2, 0xa9, 0x06,
    0xce, 0x7f, 0x7c, 0x8d, 0x3a, 0x71, 0xe4, 0x05,
    0x02, 0x92, 0xef, 0x28, 0x97, 0xa2, 0xb8, 0xaa,
    0xb7, 0x47, 0x75, 0x3b, 0x7f, 0xcb, 0x07, 0x2e,
    0xe5, 0x5c, 0x93, 0x30, 0x2a, 0x1d, 0x87, 0x29,
    0xdb, 0x92, 0x3b, 0x45, 0xdb, 0x84, 0x48, 0xd4,
    0xbe, 0x9f, 0xef, 0x3f, 0x39, 0x4e, 0xf9, 0x29,
    0x56, 0x96, 0x7e, 0xee, 0x1e, 0xab, 0xf4, 0x99,
    0x2f, 0xbb
};

static const unsigned char expected_fixture_record_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x5f, 0xf7, 0xe5, 0x51, 0xa3, 0x95, 0x9d, 0xa4,
    0x00, 0x59, 0x04, 0xbe, 0xa6, 0x13, 0x56, 0xac
};

static const unsigned char expected_fixture_record_commitment
    [LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES] = {
    0xe6, 0x08, 0x12, 0x56, 0x79, 0xe9, 0xe1, 0x10,
    0xb5, 0x64, 0x5e, 0xb0, 0x49, 0x93, 0x04, 0xab,
    0xa0, 0x71, 0xc4, 0x85, 0x03, 0xdf, 0x26, 0xda,
    0x87, 0x1c, 0x2f, 0x40, 0x91, 0xfb, 0x28, 0x31
};

static const unsigned char legacy_record_algorithm_unlabeled_ciphertext[] = {
    0x85, 0x5d, 0xd2, 0x72, 0x18, 0x03, 0x85, 0x45,
    0x5e, 0xa2, 0x1d, 0x26, 0x6f, 0xb1, 0xc0, 0xc5,
    0xcc, 0xe2, 0x78, 0xac, 0x2f, 0x7e, 0x71, 0xaa,
    0xf2, 0x47, 0xf5, 0x8f, 0xa6, 0x3c, 0x34, 0xe4,
    0x46, 0x38, 0x2f, 0x4d, 0x3c, 0x72, 0x7c, 0x01,
    0x34, 0x04, 0x24, 0xde, 0x74, 0xae, 0x0b, 0xee,
    0xdd, 0x86, 0xb2, 0x45, 0xa6, 0x60, 0x56, 0xb2,
    0x48, 0x7d, 0x07, 0xb0, 0x52, 0xfc, 0x56, 0x4a,
    0xe6, 0x1a
};

static const unsigned char legacy_record_algorithm_unlabeled_tag
    [LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x7e, 0xb4, 0x16, 0xf2, 0x18, 0x58, 0x28, 0x63,
    0x84, 0xb2, 0x8e, 0xeb, 0x3a, 0xc3, 0xfe, 0x8b
};

static const unsigned char legacy_record_algorithm_unlabeled_commitment
    [LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES] = {
    0x0b, 0xec, 0x52, 0xf1, 0x0c, 0x99, 0x8c, 0x76,
    0x97, 0x77, 0x60, 0xfd, 0x12, 0x65, 0xff, 0xf1,
    0xe4, 0xf2, 0x7f, 0xf7, 0x84, 0x83, 0x4a, 0x11,
    0x1f, 0xbf, 0xd4, 0x4c, 0x6e, 0xfb, 0xda, 0x3a
};

static const unsigned char legacy_record_unrole_labeled_ciphertext[] = {
    0xe2, 0x3a, 0x30, 0x1e, 0x67, 0x2e, 0xe0, 0x2c,
    0xf7, 0x5b, 0xb2, 0x88, 0x00, 0x5f, 0x71, 0xc8,
    0x14, 0x2a, 0x44, 0x6a, 0x9c, 0x0d, 0xae, 0x00,
    0x8a, 0x2c, 0x15, 0x36, 0xc2, 0xa2, 0xdd, 0x0a,
    0x59, 0xac, 0x5f, 0x8b, 0x38, 0x57, 0x17, 0x75,
    0x0c, 0x26, 0x67, 0x9c, 0x4b, 0x27, 0xb6, 0xf5,
    0xb7, 0x58, 0xd6, 0x2b, 0xfe, 0x0f, 0xd4, 0xda,
    0x84, 0x51, 0x39, 0xb9, 0x9e, 0xf0, 0x43, 0x91,
    0xf7, 0x5f
};

static const unsigned char legacy_record_unrole_labeled_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES] = {
    0x07, 0xe2, 0x44, 0x17, 0x5b, 0x5e, 0x09, 0x32,
    0x43, 0x48, 0x78, 0x8d, 0x96, 0x92, 0xb5, 0x89
};

static latticra_seal_hybrid_envelope_context_t fixture_context(void) {
    latticra_seal_hybrid_envelope_context_t context;
    context.classical_shared_secret = classical_shared_secret;
    context.classical_shared_secret_len = sizeof(classical_shared_secret);
    context.pqc_shared_secret = pqc_shared_secret;
    context.pqc_shared_secret_len = sizeof(pqc_shared_secret);
    context.salt = salt;
    context.salt_len = sizeof(salt);
    context.nonce = nonce;
    context.nonce_len = sizeof(nonce);
    context.aad = aad;
    context.aad_len = sizeof(aad) - 1u;
    return context;
}

static int all_bytes_equal(const unsigned char *buffer, size_t buffer_len, unsigned char value) {
    size_t index;

    for (index = 0u; index < buffer_len; index++) {
        if (buffer[index] != value) {
            return 0;
        }
    }

    return 1;
}

static void write_test_u64_be(unsigned char *out, size_t value) {
    unsigned long long remaining = (unsigned long long)value;
    size_t index;

    for (index = 0u; index < 8u; index++) {
        out[7u - index] = (unsigned char)(remaining & 0xffu);
        remaining >>= 8u;
    }
}

static int expect_malformed_record_rejected(
    const unsigned char *record,
    size_t record_len,
    const char *status_message) {
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        status_message);
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD, "malformed record error");
    EXPECT_TRUE(result.malformed_record_rejected == 1u, "malformed record rejection flag");
    EXPECT_TRUE(result.record_header_shape_validated == 0u, "malformed record shape not validated");
    EXPECT_TRUE(result.record_aad_framed == 0u, "malformed record no aad frame");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "malformed record no hkdf");
    EXPECT_TRUE(result.aes_gcm_decryption_performed == 0u, "malformed record no aead decrypt");
    EXPECT_TRUE(result.decryption_performed == 0u, "malformed record no decrypt");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "malformed record no tag verified");
    EXPECT_TRUE(recovered_len == 0u, "malformed record len reset");
    EXPECT_TRUE(recovered[0] == 0u, "malformed record plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "malformed record plaintext clear flag");
    return 0;
}

static int known_answer_vector_matches(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t encrypt_result;
    latticra_seal_hybrid_envelope_result_t decrypt_result;

    memset(ciphertext, 0, sizeof(ciphertext));
    memset(recovered, 0, sizeof(recovered));
    memset(tag, 0, sizeof(tag));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &encrypt_result) == LATTICRA_STATUS_OK,
        "kat encrypt status");
    EXPECT_TRUE(encrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "kat encrypt ok");
    EXPECT_TRUE(ciphertext_len == sizeof(expected_fixture_ciphertext), "kat ciphertext len");
    EXPECT_TRUE(
        memcmp(ciphertext, expected_fixture_ciphertext, sizeof(expected_fixture_ciphertext)) == 0,
        "kat ciphertext bytes");
    EXPECT_TRUE(memcmp(tag, expected_fixture_tag, sizeof(expected_fixture_tag)) == 0, "kat tag bytes");
    EXPECT_TRUE(
        memcmp(expected_fixture_tag, legacy_raw_aad_fixture_tag, sizeof(expected_fixture_tag)) != 0,
        "kat tag changed by detached aad frame");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_ciphertext,
            legacy_detached_unrole_labeled_ciphertext,
            sizeof(expected_fixture_ciphertext)) != 0,
        "kat ciphertext changed by hybrid secret role labels");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_tag,
            legacy_detached_unrole_labeled_tag,
            sizeof(expected_fixture_tag)) != 0,
        "kat tag changed by hybrid secret role labels");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_ciphertext,
            legacy_detached_unsuite_bound_ciphertext,
            sizeof(expected_fixture_ciphertext)) != 0,
        "kat ciphertext changed by detached suite-bound kdf");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_tag,
            legacy_detached_unsuite_bound_tag,
            sizeof(expected_fixture_tag)) != 0,
        "kat tag changed by detached suite-bound kdf");
    EXPECT_TRUE(encrypt_result.hkdf_extract_expand_performed == 1u, "kat hkdf");
    EXPECT_TRUE(encrypt_result.hkdf_provider_api_used == 1u, "kat hkdf provider api");
    EXPECT_TRUE(
        encrypt_result.hkdf_extract_expand_standard_api_used == 1u,
        "kat hkdf standard api");
    EXPECT_TRUE(encrypt_result.hkdf_sha256_digest_bound == 1u, "kat hkdf sha256 bound");
    EXPECT_TRUE(encrypt_result.hkdf_manual_fallback_used == 0u, "kat hkdf no manual fallback");
    EXPECT_TRUE(
        encrypt_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "kat detached framed aad size");
    EXPECT_TRUE(encrypt_result.caller_aad_size_bytes == sizeof(aad) - 1u, "kat caller aad size");
    EXPECT_TRUE(
        encrypt_result.detached_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "kat detached aad size");
    EXPECT_TRUE(encrypt_result.detached_aad_framed == 1u, "kat detached aad framed");
    EXPECT_TRUE(
        encrypt_result.detached_aad_label_authenticated == 1u,
        "kat detached aad label authenticated");
    EXPECT_TRUE(
        encrypt_result.detached_caller_aad_length_authenticated == 1u,
        "kat detached aad length authenticated");
    EXPECT_TRUE(
        encrypt_result.detached_caller_aad_authenticated == 1u,
        "kat detached caller aad authenticated");
    EXPECT_TRUE(encrypt_result.classical_shared_secret_bound == 1u, "kat classical secret bound");
    EXPECT_TRUE(encrypt_result.pqc_shared_secret_bound == 1u, "kat pqc secret bound");
    EXPECT_TRUE(encrypt_result.hybrid_secret_length_framed == 1u, "kat hybrid secret length framed");
    EXPECT_TRUE(encrypt_result.hybrid_secret_role_labeled == 1u, "kat hybrid secret role labeled");
    EXPECT_TRUE(
        encrypt_result.hybrid_secret_algorithm_labeled == 1u,
        "kat hybrid secret algorithm labeled");
    EXPECT_TRUE(encrypt_result.hybrid_secret_order_bound == 1u, "kat hybrid secret order bound");
    EXPECT_TRUE(encrypt_result.hybrid_secret_components_distinct == 1u, "kat hybrid secrets distinct");
    EXPECT_TRUE(encrypt_result.kdf_domain_separated == 1u, "kat kdf separated");
    EXPECT_TRUE(
        encrypt_result.kdf_domain_id == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED,
        "kat detached kdf id");
    EXPECT_TRUE(
        encrypt_result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "kat detached suite id");
    EXPECT_TRUE(encrypt_result.detached_suite_kdf_bound == 1u, "kat detached suite kdf bound");
    EXPECT_TRUE(encrypt_result.detached_kdf_domain == 1u, "kat detached kdf domain");
    EXPECT_TRUE(encrypt_result.attached_record_kdf_domain == 0u, "kat not record kdf domain");
    EXPECT_TRUE(encrypt_result.aes_gcm_provider_api_used == 1u, "kat aes provider api");
    EXPECT_TRUE(encrypt_result.aes_gcm_provider_cipher_fetched == 1u, "kat aes provider fetch");
    EXPECT_TRUE(encrypt_result.aes_gcm_96bit_nonce_configured == 1u, "kat aes nonce length");
    EXPECT_TRUE(encrypt_result.aes_gcm_128bit_tag_bound == 1u, "kat aes tag length");
    EXPECT_TRUE(encrypt_result.aes_gcm_static_cipher_fallback_used == 0u, "kat aes no static fallback");
    EXPECT_TRUE(encrypt_result.aes_gcm_encryption_performed == 1u, "kat aead");
    EXPECT_TRUE(encrypt_result.hkdf_intermediate_material_zeroized == 1u, "kat hkdf intermediates zeroized");
    EXPECT_TRUE(encrypt_result.key_material_zeroized == 1u, "kat key zeroized");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &decrypt_result) == LATTICRA_STATUS_OK,
        "kat decrypt status");
    EXPECT_TRUE(decrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "kat decrypt ok");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "kat recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "kat recovered plaintext");
    EXPECT_TRUE(decrypt_result.authentication_tag_verified == 1u, "kat tag verified");
    EXPECT_TRUE(
        decrypt_result.unauthenticated_plaintext_staged == 1u,
        "kat unauthenticated plaintext staged");
    EXPECT_TRUE(decrypt_result.staged_plaintext_cleared == 1u, "kat staged plaintext cleared");
    EXPECT_TRUE(
        decrypt_result.plaintext_released_after_authentication == 1u,
        "kat plaintext released after auth");
    EXPECT_TRUE(
        decrypt_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "kat decrypt detached framed aad size");
    EXPECT_TRUE(decrypt_result.caller_aad_size_bytes == sizeof(aad) - 1u, "kat decrypt caller aad size");
    EXPECT_TRUE(
        decrypt_result.detached_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "kat decrypt detached aad size");
    EXPECT_TRUE(decrypt_result.detached_aad_framed == 1u, "kat decrypt detached aad framed");
    EXPECT_TRUE(
        decrypt_result.detached_aad_label_authenticated == 1u,
        "kat decrypt detached aad label authenticated");
    EXPECT_TRUE(
        decrypt_result.detached_caller_aad_length_authenticated == 1u,
        "kat decrypt detached aad length authenticated");
    EXPECT_TRUE(
        decrypt_result.detached_caller_aad_authenticated == 1u,
        "kat decrypt detached caller aad authenticated");
    EXPECT_TRUE(decrypt_result.classical_shared_secret_bound == 1u, "kat decrypt classical bound");
    EXPECT_TRUE(decrypt_result.pqc_shared_secret_bound == 1u, "kat decrypt pqc bound");
    EXPECT_TRUE(decrypt_result.hybrid_secret_length_framed == 1u, "kat decrypt length framed");
    EXPECT_TRUE(decrypt_result.hybrid_secret_role_labeled == 1u, "kat decrypt role labeled");
    EXPECT_TRUE(
        decrypt_result.hybrid_secret_algorithm_labeled == 1u,
        "kat decrypt algorithm labeled");
    EXPECT_TRUE(decrypt_result.hybrid_secret_order_bound == 1u, "kat decrypt order bound");
    EXPECT_TRUE(decrypt_result.hybrid_secret_components_distinct == 1u, "kat decrypt secrets distinct");
    EXPECT_TRUE(decrypt_result.kdf_domain_separated == 1u, "kat decrypt kdf separated");
    EXPECT_TRUE(decrypt_result.detached_kdf_domain == 1u, "kat decrypt detached domain");
    EXPECT_TRUE(
        decrypt_result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "kat decrypt detached suite id");
    EXPECT_TRUE(
        decrypt_result.detached_suite_kdf_bound == 1u,
        "kat decrypt detached suite kdf bound");
    EXPECT_TRUE(decrypt_result.hkdf_provider_api_used == 1u, "kat decrypt hkdf provider api");
    EXPECT_TRUE(
        decrypt_result.hkdf_extract_expand_standard_api_used == 1u,
        "kat decrypt hkdf standard api");
    EXPECT_TRUE(decrypt_result.hkdf_sha256_digest_bound == 1u, "kat decrypt hkdf sha256 bound");
    EXPECT_TRUE(decrypt_result.hkdf_manual_fallback_used == 0u, "kat decrypt no manual fallback");
    EXPECT_TRUE(decrypt_result.aes_gcm_provider_api_used == 1u, "kat decrypt aes provider api");
    EXPECT_TRUE(decrypt_result.aes_gcm_provider_cipher_fetched == 1u, "kat decrypt aes provider fetch");
    EXPECT_TRUE(decrypt_result.aes_gcm_96bit_nonce_configured == 1u, "kat decrypt aes nonce length");
    EXPECT_TRUE(decrypt_result.aes_gcm_128bit_tag_bound == 1u, "kat decrypt aes tag length");
    EXPECT_TRUE(decrypt_result.aes_gcm_static_cipher_fallback_used == 0u, "kat decrypt aes no fallback");
    EXPECT_TRUE(decrypt_result.hkdf_intermediate_material_zeroized == 1u, "kat decrypt hkdf zeroized");
    EXPECT_TRUE(decrypt_result.key_material_zeroized == 1u, "kat decrypt key zeroized");
    return 0;
}

static int known_answer_committed_detached_vector_opens(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t encrypt_result;
    latticra_seal_hybrid_envelope_result_t decrypt_result;

    memset(ciphertext, 0, sizeof(ciphertext));
    memset(recovered, 0, sizeof(recovered));
    memset(tag, 0, sizeof(tag));
    memset(commitment, 0, sizeof(commitment));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt_committed(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            commitment,
            sizeof(commitment),
            &encrypt_result) == LATTICRA_STATUS_OK,
        "committed kat encrypt status");
    EXPECT_TRUE(encrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "committed kat encrypt ok");
    EXPECT_TRUE(ciphertext_len == sizeof(expected_fixture_ciphertext), "committed kat ciphertext len");
    EXPECT_TRUE(
        memcmp(ciphertext, expected_fixture_ciphertext, sizeof(expected_fixture_ciphertext)) == 0,
        "committed kat ciphertext bytes");
    EXPECT_TRUE(memcmp(tag, expected_fixture_tag, sizeof(expected_fixture_tag)) == 0, "committed kat tag");
    EXPECT_TRUE(
        memcmp(commitment, expected_fixture_detached_commitment, sizeof(commitment)) == 0,
        "committed kat commitment");
    EXPECT_TRUE(
        encrypt_result.detached_commitment_size_bytes == LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES,
        "committed kat commitment size");
    EXPECT_TRUE(encrypt_result.detached_key_commitment_present == 1u, "committed kat commitment present");
    EXPECT_TRUE(
        encrypt_result.detached_commitment_key_kdf_bound == 1u,
        "committed kat commitment kdf");
    EXPECT_TRUE(
        encrypt_result.detached_commitment_caller_aad_bound == 1u,
        "committed kat commitment aad");
    EXPECT_TRUE(
        encrypt_result.detached_commitment_input_streamed == 1u,
        "committed kat commitment streamed");
    EXPECT_TRUE(
        encrypt_result.detached_commitment_key_material_zeroized == 1u,
        "committed kat commitment key zeroized");
    EXPECT_TRUE(encrypt_result.detached_commitment_verified == 0u, "committed kat encrypt not verified");
    EXPECT_TRUE(encrypt_result.detached_aad_framed == 1u, "committed kat detached aad framed");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt_committed(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            expected_fixture_detached_commitment,
            sizeof(expected_fixture_detached_commitment),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &decrypt_result) == LATTICRA_STATUS_OK,
        "committed kat decrypt status");
    EXPECT_TRUE(decrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "committed kat decrypt ok");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "committed kat recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "committed kat recovered plaintext");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_size_bytes == LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES,
        "committed kat decrypt commitment size");
    EXPECT_TRUE(decrypt_result.detached_key_commitment_present == 1u, "committed kat decrypt commitment");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_key_kdf_bound == 1u,
        "committed kat decrypt commitment kdf");
    EXPECT_TRUE(decrypt_result.detached_commitment_verified == 1u, "committed kat commitment verified");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_checked_before_decrypt == 1u,
        "committed kat commitment checked");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_caller_aad_bound == 1u,
        "committed kat decrypt commitment aad");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_input_streamed == 1u,
        "committed kat decrypt commitment streamed");
    EXPECT_TRUE(
        decrypt_result.detached_commitment_key_material_zeroized == 1u,
        "committed kat decrypt commitment key zeroized");
    EXPECT_TRUE(decrypt_result.authentication_tag_verified == 1u, "committed kat tag verified");
    EXPECT_TRUE(
        decrypt_result.unauthenticated_plaintext_staged == 1u,
        "committed kat staged after commitment");
    EXPECT_TRUE(decrypt_result.staged_plaintext_cleared == 1u, "committed kat staged cleared");
    EXPECT_TRUE(
        decrypt_result.plaintext_released_after_authentication == 1u,
        "committed kat plaintext release");
    return 0;
}

static int detached_aad_frame_rejects_legacy_raw_aad_tag(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            legacy_raw_aad_fixture_tag,
            sizeof(legacy_raw_aad_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy raw aad tag status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy raw aad tag rejected");
    EXPECT_TRUE(result.detached_aad_framed == 1u, "legacy raw aad detached frame used");
    EXPECT_TRUE(
        result.detached_aad_label_authenticated == 1u,
        "legacy raw aad label authenticated");
    EXPECT_TRUE(
        result.detached_caller_aad_length_authenticated == 1u,
        "legacy raw aad length authenticated");
    EXPECT_TRUE(
        result.detached_caller_aad_authenticated == 1u,
        "legacy raw aad caller authenticated");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "legacy raw aad tag not verified");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 1u,
        "legacy raw aad staged before auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "legacy raw aad staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "legacy raw aad no plaintext release after auth");
    EXPECT_TRUE(result.decryption_performed == 0u, "legacy raw aad no plaintext release");
    EXPECT_TRUE(recovered_len == 0u, "legacy raw aad len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy raw aad plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy raw aad clear flag");
    return 0;
}

static int detached_suite_kdf_rejects_legacy_unsuite_bound_vector(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            legacy_detached_unsuite_bound_ciphertext,
            sizeof(legacy_detached_unsuite_bound_ciphertext),
            legacy_detached_unsuite_bound_tag,
            sizeof(legacy_detached_unsuite_bound_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy detached unsuite vector status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy detached unsuite vector rejected");
    EXPECT_TRUE(
        result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "legacy detached suite id");
    EXPECT_TRUE(
        result.detached_suite_kdf_bound == 1u,
        "legacy detached suite kdf bound");
    EXPECT_TRUE(result.kdf_domain_separated == 1u, "legacy detached kdf separated");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "legacy detached tag not verified");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 1u,
        "legacy detached staged before auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "legacy detached staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "legacy detached no plaintext release after auth");
    EXPECT_TRUE(result.decryption_performed == 0u, "legacy detached no plaintext release");
    EXPECT_TRUE(recovered_len == 0u, "legacy detached len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy detached plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy detached clear flag");
    return 0;
}

static int hybrid_secret_role_labels_reject_legacy_unlabeled_detached_vector(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            legacy_detached_unrole_labeled_ciphertext,
            sizeof(legacy_detached_unrole_labeled_ciphertext),
            legacy_detached_unrole_labeled_tag,
            sizeof(legacy_detached_unrole_labeled_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy detached unrole vector status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy detached unrole vector rejected");
    EXPECT_TRUE(result.hybrid_secret_length_framed == 1u, "legacy unrole length framed");
    EXPECT_TRUE(result.hybrid_secret_role_labeled == 1u, "legacy unrole role labeled");
    EXPECT_TRUE(result.hybrid_secret_algorithm_labeled == 1u, "legacy unrole algorithm labeled");
    EXPECT_TRUE(result.hybrid_secret_order_bound == 1u, "legacy unrole order bound");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "legacy unrole tag not verified");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 1u, "legacy unrole staged before auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "legacy unrole staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "legacy unrole no plaintext release after auth");
    EXPECT_TRUE(result.decryption_performed == 0u, "legacy unrole no plaintext release");
    EXPECT_TRUE(recovered_len == 0u, "legacy unrole len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy unrole plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy unrole clear flag");
    return 0;
}

static int hybrid_secret_algorithm_labels_reject_legacy_unlabeled_detached_vector(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        memcmp(
            expected_fixture_ciphertext,
            legacy_algorithm_unlabeled_ciphertext,
            sizeof(expected_fixture_ciphertext)) != 0,
        "algorithm labels changed detached ciphertext");
    EXPECT_TRUE(
        memcmp(expected_fixture_tag, legacy_algorithm_unlabeled_tag, sizeof(expected_fixture_tag)) != 0,
        "algorithm labels changed detached tag");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            legacy_algorithm_unlabeled_ciphertext,
            sizeof(legacy_algorithm_unlabeled_ciphertext),
            legacy_algorithm_unlabeled_tag,
            sizeof(legacy_algorithm_unlabeled_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy algorithm-unlabeled detached vector status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy algorithm-unlabeled detached vector rejected");
    EXPECT_TRUE(result.hybrid_secret_role_labeled == 1u, "legacy algorithm detached role labeled");
    EXPECT_TRUE(
        result.hybrid_secret_algorithm_labeled == 1u,
        "legacy algorithm detached algorithm labeled");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "legacy algorithm detached tag not verified");
    EXPECT_TRUE(result.plaintext_released_after_authentication == 0u, "legacy algorithm no release");
    EXPECT_TRUE(recovered_len == 0u, "legacy algorithm detached len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy algorithm plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy algorithm clear flag");
    return 0;
}

static int known_answer_record_vector_opens(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(expected_fixture_record_ciphertext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t open_result;

    memset(record, 0, sizeof(record));
    memset(recovered, 0, sizeof(recovered));

    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(expected_fixture_record_ciphertext));
    memcpy(record + 20u, salt, sizeof(salt));
    memcpy(record + 52u, nonce, sizeof(nonce));
    memcpy(record + 64u, expected_fixture_record_tag, sizeof(expected_fixture_record_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        expected_fixture_record_ciphertext,
        sizeof(expected_fixture_record_ciphertext));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
            sizeof(expected_fixture_record_ciphertext),
        expected_fixture_record_commitment,
        sizeof(expected_fixture_record_commitment));

    EXPECT_TRUE(
        memcmp(expected_fixture_tag, expected_fixture_record_tag, sizeof(expected_fixture_tag)) != 0,
        "record kat tag binds header aad");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_ciphertext,
            expected_fixture_record_ciphertext,
            sizeof(expected_fixture_ciphertext)) != 0,
        "record kat uses distinct kdf domain");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_record_ciphertext,
            legacy_record_unrole_labeled_ciphertext,
            sizeof(expected_fixture_record_ciphertext)) != 0,
        "record kat ciphertext changed by hybrid secret role labels");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_record_tag,
            legacy_record_unrole_labeled_tag,
            sizeof(expected_fixture_record_tag)) != 0,
        "record kat tag changed by hybrid secret role labels");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "record kat open status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "record kat open ok");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "record kat recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "record kat recovered plaintext");
    EXPECT_TRUE(open_result.record_format_present == 1u, "record kat format");
    EXPECT_TRUE(open_result.record_size_bytes == sizeof(record), "record kat size");
    EXPECT_TRUE(
        open_result.record_commitment_size_bytes == LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES,
        "record kat commitment size");
    EXPECT_TRUE(open_result.record_key_commitment_present == 1u, "record kat commitment present");
    EXPECT_TRUE(open_result.record_commitment_key_kdf_bound == 1u, "record kat commitment kdf");
    EXPECT_TRUE(open_result.record_commitment_verified == 1u, "record kat commitment verified");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "record kat commitment checked before decrypt");
    EXPECT_TRUE(
        open_result.record_commitment_caller_aad_bound == 1u,
        "record kat commitment caller aad bound");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "record kat commitment streamed");
    EXPECT_TRUE(
        open_result.record_commitment_key_material_zeroized == 1u,
        "record kat commitment key zeroized");
    EXPECT_TRUE(
        open_result.record_suite_id == LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM,
        "record kat suite id");
    EXPECT_TRUE(open_result.record_suite_authenticated == 1u, "record kat suite authenticated");
    EXPECT_TRUE(open_result.record_kdf_domain_authenticated == 1u, "record kat kdf domain authenticated");
    EXPECT_TRUE(open_result.record_suite_kdf_bound == 1u, "record kat suite bound to kdf");
    EXPECT_TRUE(open_result.record_salt_nonce_nonzero == 1u, "record kat salt nonce nonzero");
    EXPECT_TRUE(open_result.record_header_shape_validated == 1u, "record kat shape validated");
    EXPECT_TRUE(open_result.malformed_record_rejected == 0u, "record kat not malformed");
    EXPECT_TRUE(
        open_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record kat aad includes framed record aad");
    EXPECT_TRUE(open_result.caller_aad_size_bytes == sizeof(aad) - 1u, "record kat caller aad size");
    EXPECT_TRUE(
        open_result.record_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record kat framed aad size");
    EXPECT_TRUE(open_result.record_aad_framed == 1u, "record kat aad framed");
    EXPECT_TRUE(open_result.record_aad_label_authenticated == 1u, "record kat aad label authenticated");
    EXPECT_TRUE(open_result.record_caller_aad_authenticated == 1u, "record kat caller aad authenticated");
    EXPECT_TRUE(open_result.record_header_authenticated == 1u, "record kat header authenticated");
    EXPECT_TRUE(open_result.attached_record_authenticated == 1u, "record kat authenticated");
    EXPECT_TRUE(open_result.classical_shared_secret_bound == 1u, "record kat classical bound");
    EXPECT_TRUE(open_result.pqc_shared_secret_bound == 1u, "record kat pqc bound");
    EXPECT_TRUE(open_result.hybrid_secret_length_framed == 1u, "record kat length framed");
    EXPECT_TRUE(open_result.hybrid_secret_role_labeled == 1u, "record kat role labeled");
    EXPECT_TRUE(open_result.hybrid_secret_algorithm_labeled == 1u, "record kat algorithm labeled");
    EXPECT_TRUE(open_result.hybrid_secret_order_bound == 1u, "record kat order bound");
    EXPECT_TRUE(open_result.kdf_domain_separated == 1u, "record kat kdf separated");
    EXPECT_TRUE(
        open_result.kdf_domain_id == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD,
        "record kat kdf id");
    EXPECT_TRUE(open_result.detached_kdf_domain == 0u, "record kat not detached domain");
    EXPECT_TRUE(open_result.attached_record_kdf_domain == 1u, "record kat attached domain");
    EXPECT_TRUE(open_result.authentication_tag_verified == 1u, "record kat tag verified");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 1u,
        "record kat unauthenticated plaintext staged");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 1u, "record kat staged plaintext cleared");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 1u,
        "record kat plaintext released after auth");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "record kat hkdf zeroized");
    return 0;
}

static int hybrid_secret_role_labels_reject_legacy_unlabeled_record_vector(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(legacy_record_unrole_labeled_ciphertext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(record, 0, sizeof(record));
    memset(recovered, 0x7f, sizeof(recovered));

    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(legacy_record_unrole_labeled_ciphertext));
    memcpy(record + 20u, salt, sizeof(salt));
    memcpy(record + 52u, nonce, sizeof(nonce));
    memcpy(record + 64u, legacy_record_unrole_labeled_tag, sizeof(legacy_record_unrole_labeled_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        legacy_record_unrole_labeled_ciphertext,
        sizeof(legacy_record_unrole_labeled_ciphertext));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy record unrole vector status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy record unrole vector rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "legacy record unrole shape");
    EXPECT_TRUE(result.record_suite_kdf_bound == 1u, "legacy record unrole suite kdf");
    EXPECT_TRUE(result.hybrid_secret_length_framed == 1u, "legacy record unrole length framed");
    EXPECT_TRUE(result.hybrid_secret_role_labeled == 1u, "legacy record unrole role labeled");
    EXPECT_TRUE(result.hybrid_secret_algorithm_labeled == 1u, "legacy record unrole algorithm labeled");
    EXPECT_TRUE(result.hybrid_secret_order_bound == 1u, "legacy record unrole order bound");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "legacy record unrole tag not verified");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "legacy record unrole commitment checked");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "legacy record unrole commitment rejected");
    EXPECT_TRUE(
        result.record_commitment_caller_aad_bound == 1u,
        "legacy record unrole commitment caller aad bound");
    EXPECT_TRUE(
        result.record_commitment_input_streamed == 1u,
        "legacy record unrole commitment streamed");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 0u,
        "legacy record unrole not staged before commitment auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "legacy record unrole no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "legacy record unrole no plaintext release after auth");
    EXPECT_TRUE(result.decryption_performed == 0u, "legacy record unrole no plaintext release");
    EXPECT_TRUE(recovered_len == 0u, "legacy record unrole len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy record unrole plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy record unrole clear flag");
    return 0;
}

static int hybrid_secret_algorithm_labels_reject_legacy_unlabeled_record_vector(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(legacy_record_algorithm_unlabeled_ciphertext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(record, 0, sizeof(record));
    memset(recovered, 0x7f, sizeof(recovered));

    EXPECT_TRUE(
        memcmp(
            expected_fixture_record_ciphertext,
            legacy_record_algorithm_unlabeled_ciphertext,
            sizeof(expected_fixture_record_ciphertext)) != 0,
        "algorithm labels changed record ciphertext");
    EXPECT_TRUE(
        memcmp(
            expected_fixture_record_tag,
            legacy_record_algorithm_unlabeled_tag,
            sizeof(expected_fixture_record_tag)) != 0,
        "algorithm labels changed record tag");
    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(legacy_record_algorithm_unlabeled_ciphertext));
    memcpy(record + 20u, salt, sizeof(salt));
    memcpy(record + 52u, nonce, sizeof(nonce));
    memcpy(
        record + 64u,
        legacy_record_algorithm_unlabeled_tag,
        sizeof(legacy_record_algorithm_unlabeled_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        legacy_record_algorithm_unlabeled_ciphertext,
        sizeof(legacy_record_algorithm_unlabeled_ciphertext));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
            sizeof(legacy_record_algorithm_unlabeled_ciphertext),
        legacy_record_algorithm_unlabeled_commitment,
        sizeof(legacy_record_algorithm_unlabeled_commitment));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "legacy algorithm-unlabeled record vector status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "legacy algorithm-unlabeled record vector rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "legacy algorithm record shape");
    EXPECT_TRUE(result.hybrid_secret_algorithm_labeled == 1u, "legacy algorithm record labeled");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "legacy algorithm record commitment checked");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "legacy algorithm record commitment rejected");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 0u, "legacy algorithm record not staged");
    EXPECT_TRUE(result.plaintext_released_after_authentication == 0u, "legacy algorithm record no release");
    EXPECT_TRUE(recovered_len == 0u, "legacy algorithm record len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "legacy algorithm record plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "legacy algorithm record clear flag");
    return 0;
}

static int random_bytes_can_fill_nonce_material(void) {
    unsigned char generated[LATTICRA_SEAL_HYBRID_NONCE_BYTES];

    memset(generated, 0, sizeof(generated));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_random_bytes(generated, sizeof(generated)) == 1,
        "random fill");
    EXPECT_TRUE(latticra_seal_hybrid_envelope_random_bytes(0, sizeof(generated)) == 0, "null random");
    EXPECT_TRUE(latticra_seal_hybrid_envelope_random_bytes(generated, 0u) == 0, "empty random");
    return 0;
}

static int encrypt_decrypt_round_trip(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t encrypt_result;
    latticra_seal_hybrid_envelope_result_t decrypt_result;
    char rendered[LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX];

    memset(ciphertext, 0, sizeof(ciphertext));
    memset(recovered, 0, sizeof(recovered));
    memset(tag, 0, sizeof(tag));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &encrypt_result) == LATTICRA_STATUS_OK,
        "encrypt status");
    EXPECT_TRUE(encrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "encrypt ok");
    EXPECT_TRUE(strcmp(encrypt_result.envelope_profile, "latticra-seal-hybrid-envelope/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(encrypt_result.kdf_algorithm, "HKDF-SHA256") == 0, "kdf");
    EXPECT_TRUE(strcmp(encrypt_result.aead_algorithm, "AES-256-GCM") == 0, "aead");
    EXPECT_TRUE(strstr(encrypt_result.standards_source, "NIST-FIPS-197") != 0, "standards aes");
    EXPECT_TRUE(strstr(encrypt_result.standards_source, "NIST-SP-800-38D") != 0, "standards gcm");
    EXPECT_TRUE(strstr(encrypt_result.standards_source, "RFC-5869") != 0, "standards hkdf");
    EXPECT_TRUE(
        strstr(encrypt_result.standards_source, "NIST-SP-800-56C-REV2") != 0,
        "standards nist hkdf");
    EXPECT_TRUE(encrypt_result.classical_shared_secret_size_bytes == 32u, "classical size");
    EXPECT_TRUE(encrypt_result.pqc_shared_secret_size_bytes == 32u, "pqc size");
    EXPECT_TRUE(encrypt_result.salt_size_bytes == 32u, "salt size");
    EXPECT_TRUE(encrypt_result.nonce_size_bytes == 12u, "nonce size");
    EXPECT_TRUE(encrypt_result.salt_nonzero == 1u, "salt nonzero");
    EXPECT_TRUE(encrypt_result.nonce_nonzero == 1u, "nonce nonzero");
    EXPECT_TRUE(encrypt_result.weak_salt_rejected == 0u, "salt not rejected");
    EXPECT_TRUE(encrypt_result.weak_nonce_rejected == 0u, "nonce not rejected");
    EXPECT_TRUE(
        encrypt_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "detached framed aad size");
    EXPECT_TRUE(encrypt_result.caller_aad_size_bytes == sizeof(aad) - 1u, "detached caller aad size");
    EXPECT_TRUE(
        encrypt_result.detached_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "detached aad size");
    EXPECT_TRUE(encrypt_result.detached_aad_framed == 1u, "detached aad framed");
    EXPECT_TRUE(
        encrypt_result.detached_aad_label_authenticated == 1u,
        "detached aad label authenticated");
    EXPECT_TRUE(
        encrypt_result.detached_caller_aad_length_authenticated == 1u,
        "detached aad length authenticated");
    EXPECT_TRUE(
        encrypt_result.detached_caller_aad_authenticated == 1u,
        "detached caller aad authenticated");
    EXPECT_TRUE(encrypt_result.plaintext_size_bytes == sizeof(plaintext) - 1u, "plaintext size");
    EXPECT_TRUE(ciphertext_len == sizeof(plaintext) - 1u, "ciphertext len");
    EXPECT_TRUE(encrypt_result.ciphertext_size_bytes == ciphertext_len, "result ciphertext size");
    EXPECT_TRUE(encrypt_result.tag_size_bytes == LATTICRA_SEAL_HYBRID_TAG_BYTES, "tag size");
    EXPECT_TRUE(encrypt_result.hybrid_classical_pqc_secret_required == 1u, "hybrid required");
    EXPECT_TRUE(encrypt_result.hkdf_extract_expand_performed == 1u, "hkdf performed");
    EXPECT_TRUE(encrypt_result.hkdf_provider_api_used == 1u, "hkdf provider api");
    EXPECT_TRUE(encrypt_result.hkdf_extract_expand_standard_api_used == 1u, "hkdf standard api");
    EXPECT_TRUE(encrypt_result.hkdf_sha256_digest_bound == 1u, "hkdf sha256 bound");
    EXPECT_TRUE(encrypt_result.hkdf_manual_fallback_used == 0u, "hkdf no manual fallback");
    EXPECT_TRUE(encrypt_result.classical_shared_secret_bound == 1u, "classical secret bound");
    EXPECT_TRUE(encrypt_result.pqc_shared_secret_bound == 1u, "pqc secret bound");
    EXPECT_TRUE(encrypt_result.hybrid_secret_length_framed == 1u, "hybrid secret length framed");
    EXPECT_TRUE(encrypt_result.hybrid_secret_role_labeled == 1u, "hybrid secret role labeled");
    EXPECT_TRUE(
        encrypt_result.hybrid_secret_algorithm_labeled == 1u,
        "hybrid secret algorithm labeled");
    EXPECT_TRUE(encrypt_result.hybrid_secret_order_bound == 1u, "hybrid secret order bound");
    EXPECT_TRUE(encrypt_result.hybrid_secret_components_distinct == 1u, "hybrid secrets distinct");
    EXPECT_TRUE(encrypt_result.kdf_domain_separated == 1u, "kdf domain separated");
    EXPECT_TRUE(
        encrypt_result.kdf_domain_id == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_DETACHED,
        "detached kdf id");
    EXPECT_TRUE(
        encrypt_result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "detached suite id");
    EXPECT_TRUE(encrypt_result.detached_suite_kdf_bound == 1u, "detached suite kdf bound");
    EXPECT_TRUE(encrypt_result.detached_kdf_domain == 1u, "detached kdf domain");
    EXPECT_TRUE(encrypt_result.attached_record_kdf_domain == 0u, "not record kdf domain");
    EXPECT_TRUE(encrypt_result.aes_gcm_provider_api_used == 1u, "aes provider api");
    EXPECT_TRUE(encrypt_result.aes_gcm_provider_cipher_fetched == 1u, "aes provider fetch");
    EXPECT_TRUE(encrypt_result.aes_gcm_96bit_nonce_configured == 1u, "aes nonce length");
    EXPECT_TRUE(encrypt_result.aes_gcm_128bit_tag_bound == 1u, "aes tag length");
    EXPECT_TRUE(encrypt_result.aes_gcm_static_cipher_fallback_used == 0u, "aes no static fallback");
    EXPECT_TRUE(encrypt_result.aes_gcm_encryption_performed == 1u, "aes encryption performed");
    EXPECT_TRUE(encrypt_result.salt_generated == 0u, "low-level salt not generated");
    EXPECT_TRUE(encrypt_result.nonce_generated == 0u, "low-level nonce not generated");
    EXPECT_TRUE(encrypt_result.detached_salt_caller_supplied == 1u, "low-level salt caller supplied");
    EXPECT_TRUE(encrypt_result.detached_nonce_caller_supplied == 1u, "low-level nonce caller supplied");
    EXPECT_TRUE(encrypt_result.attached_record_salt_generated == 0u, "low-level no record salt");
    EXPECT_TRUE(encrypt_result.attached_record_nonce_generated == 0u, "low-level no record nonce");
    EXPECT_TRUE(encrypt_result.encryption_performed == 1u, "encryption performed");
    EXPECT_TRUE(encrypt_result.secret_material_emitted == 0u, "secret material not emitted");
    EXPECT_TRUE(encrypt_result.hkdf_intermediate_material_zeroized == 1u, "hkdf intermediates zeroized");
    EXPECT_TRUE(encrypt_result.key_material_zeroized == 1u, "key zeroized");
    EXPECT_TRUE(latticra_seal_hybrid_envelope_result_is_authority_neutral(&encrypt_result) == 1, "authority neutral");
    EXPECT_TRUE(memcmp(ciphertext, plaintext, ciphertext_len) != 0, "ciphertext differs");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&encrypt_result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "encrypt report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL HYBRID ENVELOPE RESULT") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "aead_algorithm=AES-256-GCM") != 0, "report aead");
    EXPECT_TRUE(strstr(rendered, "classical_shared_secret_nonzero=1") != 0, "report classical nonzero");
    EXPECT_TRUE(strstr(rendered, "pqc_shared_secret_nonzero=1") != 0, "report pqc nonzero");
    EXPECT_TRUE(strstr(rendered, "salt_nonzero=1") != 0, "report salt nonzero");
    EXPECT_TRUE(strstr(rendered, "nonce_nonzero=1") != 0, "report nonce nonzero");
    EXPECT_TRUE(strstr(rendered, "aad_size_bytes=48") != 0, "report detached framed aad size");
    EXPECT_TRUE(strstr(rendered, "caller_aad_size_bytes=32") != 0, "report detached caller aad");
    EXPECT_TRUE(strstr(rendered, "detached_aad_size_bytes=48") != 0, "report detached aad size");
    EXPECT_TRUE(strstr(rendered, "detached_aad_framed=1") != 0, "report detached aad framed");
    EXPECT_TRUE(
        strstr(rendered, "detached_aad_label_authenticated=1") != 0,
        "report detached aad label");
    EXPECT_TRUE(
        strstr(rendered, "detached_caller_aad_length_authenticated=1") != 0,
        "report detached aad length");
    EXPECT_TRUE(
        strstr(rendered, "detached_caller_aad_authenticated=1") != 0,
        "report detached caller aad");
    EXPECT_TRUE(strstr(rendered, "weak_shared_secret_rejected=0") != 0, "report no weak secret");
    EXPECT_TRUE(strstr(rendered, "weak_salt_rejected=0") != 0, "report no weak salt");
    EXPECT_TRUE(strstr(rendered, "weak_nonce_rejected=0") != 0, "report no weak nonce");
    EXPECT_TRUE(strstr(rendered, "classical_shared_secret_bound=1") != 0, "report classical bound");
    EXPECT_TRUE(strstr(rendered, "pqc_shared_secret_bound=1") != 0, "report pqc bound");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_length_framed=1") != 0, "report length framed");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_role_labeled=1") != 0, "report role labeled");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_algorithm_labeled=1") != 0, "report algorithm labeled");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_order_bound=1") != 0, "report order bound");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_components_distinct=1") != 0, "report distinct");
    EXPECT_TRUE(
        strstr(rendered, "duplicate_hybrid_shared_secret_rejected=0") != 0,
        "report no duplicate");
    EXPECT_TRUE(strstr(rendered, "kdf_domain_separated=1") != 0, "report kdf separated");
    EXPECT_TRUE(strstr(rendered, "kdf_domain_id=1") != 0, "report detached kdf id");
    EXPECT_TRUE(strstr(rendered, "detached_suite_id=1") != 0, "report detached suite id");
    EXPECT_TRUE(
        strstr(rendered, "detached_suite_kdf_bound=1") != 0,
        "report detached suite kdf bound");
    EXPECT_TRUE(strstr(rendered, "detached_kdf_domain=1") != 0, "report detached kdf");
    EXPECT_TRUE(strstr(rendered, "attached_record_kdf_domain=0") != 0, "report not record kdf");
    EXPECT_TRUE(strstr(rendered, "detached_salt_caller_supplied=1") != 0, "report detached salt");
    EXPECT_TRUE(strstr(rendered, "detached_nonce_caller_supplied=1") != 0, "report detached nonce");
    EXPECT_TRUE(strstr(rendered, "attached_record_salt_generated=0") != 0, "report no record salt");
    EXPECT_TRUE(strstr(rendered, "attached_record_nonce_generated=0") != 0, "report no record nonce");
    EXPECT_TRUE(strstr(rendered, "failed_salt_output_cleared=0") != 0, "report no salt clear");
    EXPECT_TRUE(strstr(rendered, "failed_nonce_output_cleared=0") != 0, "report no nonce clear");
    EXPECT_TRUE(strstr(rendered, "failed_ciphertext_output_cleared=0") != 0, "report no ciphertext clear");
    EXPECT_TRUE(strstr(rendered, "failed_tag_output_cleared=0") != 0, "report no tag clear");
    EXPECT_TRUE(strstr(rendered, "failed_plaintext_output_cleared=0") != 0, "report no plaintext clear");
    EXPECT_TRUE(strstr(rendered, "failed_record_output_cleared=0") != 0, "report no record clear");
    EXPECT_TRUE(strstr(rendered, "unsafe_buffer_overlap_rejected=0") != 0, "report no overlap rejection");
    EXPECT_TRUE(strstr(rendered, "encryption_performed=1") != 0, "report encryption");
    EXPECT_TRUE(strstr(rendered, "hkdf_provider_api_used=1") != 0, "report hkdf provider");
    EXPECT_TRUE(
        strstr(rendered, "hkdf_extract_expand_standard_api_used=1") != 0,
        "report hkdf standard api");
    EXPECT_TRUE(strstr(rendered, "hkdf_sha256_digest_bound=1") != 0, "report hkdf sha256");
    EXPECT_TRUE(strstr(rendered, "hkdf_manual_fallback_used=0") != 0, "report no hkdf fallback");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_provider_api_used=1") != 0, "report aes provider");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_provider_cipher_fetched=1") != 0, "report aes fetch");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_96bit_nonce_configured=1") != 0, "report aes nonce");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_128bit_tag_bound=1") != 0, "report aes tag");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_static_cipher_fallback_used=0") != 0, "report aes no fallback");
    EXPECT_TRUE(strstr(rendered, "hkdf_intermediate_material_zeroized=1") != 0, "report hkdf zeroized");
    EXPECT_TRUE(strstr(rendered, "production_crypto_claim_allowed=0") != 0, "report production claim");
    EXPECT_TRUE(strstr(rendered, "fips_claim_allowed=0") != 0, "report fips claim");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            ciphertext,
            ciphertext_len,
            tag,
            sizeof(tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &decrypt_result) == LATTICRA_STATUS_OK,
        "decrypt status");
    EXPECT_TRUE(decrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "decrypt ok");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "recovered plaintext");
    EXPECT_TRUE(decrypt_result.hkdf_extract_expand_performed == 1u, "decrypt hkdf");
    EXPECT_TRUE(decrypt_result.hkdf_provider_api_used == 1u, "decrypt hkdf provider");
    EXPECT_TRUE(
        decrypt_result.hkdf_extract_expand_standard_api_used == 1u,
        "decrypt hkdf standard api");
    EXPECT_TRUE(decrypt_result.hkdf_sha256_digest_bound == 1u, "decrypt hkdf sha256");
    EXPECT_TRUE(decrypt_result.hkdf_manual_fallback_used == 0u, "decrypt no hkdf fallback");
    EXPECT_TRUE(decrypt_result.aes_gcm_provider_api_used == 1u, "decrypt aes provider");
    EXPECT_TRUE(decrypt_result.aes_gcm_provider_cipher_fetched == 1u, "decrypt aes fetch");
    EXPECT_TRUE(decrypt_result.aes_gcm_96bit_nonce_configured == 1u, "decrypt aes nonce");
    EXPECT_TRUE(decrypt_result.aes_gcm_128bit_tag_bound == 1u, "decrypt aes tag");
    EXPECT_TRUE(decrypt_result.aes_gcm_static_cipher_fallback_used == 0u, "decrypt aes no fallback");
    EXPECT_TRUE(decrypt_result.classical_shared_secret_bound == 1u, "decrypt classical bound");
    EXPECT_TRUE(decrypt_result.pqc_shared_secret_bound == 1u, "decrypt pqc bound");
    EXPECT_TRUE(decrypt_result.hybrid_secret_length_framed == 1u, "decrypt length framed");
    EXPECT_TRUE(decrypt_result.hybrid_secret_role_labeled == 1u, "decrypt role labeled");
    EXPECT_TRUE(decrypt_result.hybrid_secret_algorithm_labeled == 1u, "decrypt algorithm labeled");
    EXPECT_TRUE(decrypt_result.hybrid_secret_order_bound == 1u, "decrypt order bound");
    EXPECT_TRUE(decrypt_result.hybrid_secret_components_distinct == 1u, "decrypt secrets distinct");
    EXPECT_TRUE(decrypt_result.kdf_domain_separated == 1u, "decrypt kdf separated");
    EXPECT_TRUE(decrypt_result.detached_kdf_domain == 1u, "decrypt detached kdf domain");
    EXPECT_TRUE(
        decrypt_result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "decrypt detached suite id");
    EXPECT_TRUE(decrypt_result.detached_suite_kdf_bound == 1u, "decrypt detached suite kdf bound");
    EXPECT_TRUE(
        decrypt_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "decrypt detached framed aad size");
    EXPECT_TRUE(decrypt_result.caller_aad_size_bytes == sizeof(aad) - 1u, "decrypt caller aad size");
    EXPECT_TRUE(
        decrypt_result.detached_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "decrypt detached aad size");
    EXPECT_TRUE(decrypt_result.detached_aad_framed == 1u, "decrypt detached aad framed");
    EXPECT_TRUE(
        decrypt_result.detached_aad_label_authenticated == 1u,
        "decrypt detached aad label authenticated");
    EXPECT_TRUE(
        decrypt_result.detached_caller_aad_length_authenticated == 1u,
        "decrypt detached aad length authenticated");
    EXPECT_TRUE(
        decrypt_result.detached_caller_aad_authenticated == 1u,
        "decrypt detached caller aad authenticated");
    EXPECT_TRUE(decrypt_result.aes_gcm_decryption_performed == 1u, "aes decryption performed");
    EXPECT_TRUE(decrypt_result.authentication_tag_verified == 1u, "tag verified");
    EXPECT_TRUE(decrypt_result.unauthenticated_plaintext_staged == 1u, "decrypt staged before auth");
    EXPECT_TRUE(decrypt_result.staged_plaintext_cleared == 1u, "decrypt staged plaintext cleared");
    EXPECT_TRUE(
        decrypt_result.plaintext_released_after_authentication == 1u,
        "decrypt plaintext released after auth");
    EXPECT_TRUE(decrypt_result.salt_generated == 0u, "decrypt salt not generated");
    EXPECT_TRUE(decrypt_result.nonce_generated == 0u, "decrypt nonce not generated");
    EXPECT_TRUE(decrypt_result.detached_salt_caller_supplied == 1u, "decrypt salt caller supplied");
    EXPECT_TRUE(decrypt_result.detached_nonce_caller_supplied == 1u, "decrypt nonce caller supplied");
    EXPECT_TRUE(decrypt_result.decryption_performed == 1u, "decryption performed");
    EXPECT_TRUE(decrypt_result.secret_material_emitted == 0u, "decrypt secret not emitted");
    EXPECT_TRUE(decrypt_result.hkdf_intermediate_material_zeroized == 1u, "decrypt hkdf zeroized");
    EXPECT_TRUE(decrypt_result.key_material_zeroized == 1u, "decrypt key zeroized");
    EXPECT_TRUE(latticra_seal_hybrid_envelope_result_is_authority_neutral(&decrypt_result) == 1, "decrypt authority neutral");
    return 0;
}

static int zero_length_plaintext_round_trip(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[1];
    unsigned char recovered[1];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t ciphertext_len = 99u;
    size_t recovered_len = 99u;
    latticra_seal_hybrid_envelope_result_t encrypt_result;
    latticra_seal_hybrid_envelope_result_t decrypt_result;

    memset(ciphertext, 0x7au, sizeof(ciphertext));
    memset(recovered, 0x7bu, sizeof(recovered));
    memset(tag, 0, sizeof(tag));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            0,
            0u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &encrypt_result) == LATTICRA_STATUS_OK,
        "zero encrypt status");
    EXPECT_TRUE(encrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "zero encrypt ok");
    EXPECT_TRUE(ciphertext_len == 0u, "zero ciphertext len");
    EXPECT_TRUE(encrypt_result.plaintext_size_bytes == 0u, "zero plaintext size");
    EXPECT_TRUE(encrypt_result.ciphertext_size_bytes == 0u, "zero ciphertext result size");
    EXPECT_TRUE(encrypt_result.authentication_tag_verified == 0u, "zero encrypt no verify");
    EXPECT_TRUE(encrypt_result.key_material_zeroized == 1u, "zero encrypt key zeroized");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            ciphertext,
            ciphertext_len,
            tag,
            sizeof(tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &decrypt_result) == LATTICRA_STATUS_OK,
        "zero decrypt status");
    EXPECT_TRUE(decrypt_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "zero decrypt ok");
    EXPECT_TRUE(recovered_len == 0u, "zero recovered len");
    EXPECT_TRUE(recovered[0] == 0x7bu, "zero decrypt leaves output byte untouched");
    EXPECT_TRUE(decrypt_result.plaintext_size_bytes == 0u, "zero decrypt plaintext size");
    EXPECT_TRUE(decrypt_result.unauthenticated_plaintext_staged == 1u, "zero decrypt staged");
    EXPECT_TRUE(decrypt_result.staged_plaintext_cleared == 1u, "zero decrypt empty staging cleared");
    EXPECT_TRUE(
        decrypt_result.plaintext_released_after_authentication == 1u,
        "zero decrypt releases empty plaintext after auth");
    EXPECT_TRUE(decrypt_result.authentication_tag_verified == 1u, "zero decrypt tag verified");
    EXPECT_TRUE(decrypt_result.key_material_zeroized == 1u, "zero decrypt key zeroized");
    return 0;
}

static int seal_open_generates_salt_and_nonce(void) {
    unsigned char first_ciphertext[sizeof(plaintext)];
    unsigned char second_ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char first_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char second_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char first_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char second_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char first_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char second_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t first_ciphertext_len = 0u;
    size_t second_ciphertext_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t second_seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;
    char rendered[LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX];

    memset(first_ciphertext, 0, sizeof(first_ciphertext));
    memset(second_ciphertext, 0, sizeof(second_ciphertext));
    memset(recovered, 0, sizeof(recovered));
    memset(first_salt, 0, sizeof(first_salt));
    memset(second_salt, 0, sizeof(second_salt));
    memset(first_nonce, 0, sizeof(first_nonce));
    memset(second_nonce, 0, sizeof(second_nonce));
    memset(first_tag, 0, sizeof(first_tag));
    memset(second_tag, 0, sizeof(second_tag));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            first_ciphertext,
            sizeof(first_ciphertext),
            &first_ciphertext_len,
            first_salt,
            sizeof(first_salt),
            first_nonce,
            sizeof(first_nonce),
            first_tag,
            sizeof(first_tag),
            &seal_result) == LATTICRA_STATUS_OK,
        "seal status");
    EXPECT_TRUE(seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "seal ok");
    EXPECT_TRUE(strcmp(seal_result.operation_state, "sealed") == 0, "seal operation");
    EXPECT_TRUE(strcmp(seal_result.status, "hybrid-envelope-sealed") == 0, "seal result status");
    EXPECT_TRUE(seal_result.salt_generated == 1u, "seal salt generated");
    EXPECT_TRUE(seal_result.nonce_generated == 1u, "seal nonce generated");
    EXPECT_TRUE(expect_generated_random_evidence(&seal_result) == 0, "seal random evidence");
    EXPECT_TRUE(seal_result.salt_nonzero == 1u, "seal salt nonzero");
    EXPECT_TRUE(seal_result.nonce_nonzero == 1u, "seal nonce nonzero");
    EXPECT_TRUE(seal_result.kdf_domain_separated == 1u, "seal kdf separated");
    EXPECT_TRUE(seal_result.detached_kdf_domain == 1u, "seal detached kdf domain");
    EXPECT_TRUE(
        seal_result.detached_suite_id == LATTICRA_SEAL_HYBRID_SUITE_HKDF_SHA256_AES_256_GCM,
        "seal detached suite id");
    EXPECT_TRUE(seal_result.detached_suite_kdf_bound == 1u, "seal detached suite kdf bound");
    EXPECT_TRUE(seal_result.attached_record_kdf_domain == 0u, "seal not record kdf");
    EXPECT_TRUE(
        seal_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_DETACHED_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "seal detached framed aad size");
    EXPECT_TRUE(seal_result.caller_aad_size_bytes == sizeof(aad) - 1u, "seal caller aad size");
    EXPECT_TRUE(seal_result.detached_aad_framed == 1u, "seal detached aad framed");
    EXPECT_TRUE(seal_result.detached_aad_label_authenticated == 1u, "seal detached aad label");
    EXPECT_TRUE(
        seal_result.detached_caller_aad_length_authenticated == 1u,
        "seal detached aad length");
    EXPECT_TRUE(seal_result.detached_caller_aad_authenticated == 1u, "seal detached caller aad");
    EXPECT_TRUE(seal_result.detached_salt_caller_supplied == 0u, "seal salt not caller supplied");
    EXPECT_TRUE(seal_result.detached_nonce_caller_supplied == 0u, "seal nonce not caller supplied");
    EXPECT_TRUE(seal_result.attached_record_salt_generated == 0u, "seal not record salt");
    EXPECT_TRUE(seal_result.attached_record_nonce_generated == 0u, "seal not record nonce");
    EXPECT_TRUE(seal_result.hkdf_extract_expand_performed == 1u, "seal hkdf");
    EXPECT_TRUE(seal_result.aes_gcm_encryption_performed == 1u, "seal aead");
    EXPECT_TRUE(seal_result.encryption_performed == 1u, "seal encryption");
    EXPECT_TRUE(seal_result.secret_material_emitted == 0u, "seal secret not emitted");
    EXPECT_TRUE(seal_result.hkdf_intermediate_material_zeroized == 1u, "seal hkdf zeroized");
    EXPECT_TRUE(seal_result.key_material_zeroized == 1u, "seal zeroized");
    EXPECT_TRUE(memcmp(first_salt, salt, sizeof(first_salt)) != 0, "seal did not use fixture salt");
    EXPECT_TRUE(memcmp(first_nonce, nonce, sizeof(first_nonce)) != 0, "seal did not use fixture nonce");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&seal_result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "seal report");
    EXPECT_TRUE(strstr(rendered, "salt_generated=1") != 0, "report generated salt");
    EXPECT_TRUE(strstr(rendered, "nonce_generated=1") != 0, "report generated nonce");
    EXPECT_TRUE(expect_generated_random_report(rendered) == 0, "seal random report");
    EXPECT_TRUE(strstr(rendered, "salt_nonzero=1") != 0, "report seal salt nonzero");
    EXPECT_TRUE(strstr(rendered, "nonce_nonzero=1") != 0, "report seal nonce nonzero");
    EXPECT_TRUE(strstr(rendered, "kdf_domain_separated=1") != 0, "report seal kdf separated");
    EXPECT_TRUE(strstr(rendered, "detached_kdf_domain=1") != 0, "report seal detached kdf");
    EXPECT_TRUE(strstr(rendered, "detached_suite_id=1") != 0, "report seal detached suite id");
    EXPECT_TRUE(
        strstr(rendered, "detached_suite_kdf_bound=1") != 0,
        "report seal detached suite kdf");
    EXPECT_TRUE(strstr(rendered, "detached_aad_framed=1") != 0, "report seal detached aad framed");
    EXPECT_TRUE(
        strstr(rendered, "detached_caller_aad_length_authenticated=1") != 0,
        "report seal detached aad length");
    EXPECT_TRUE(strstr(rendered, "detached_salt_caller_supplied=0") != 0, "report seal detached salt");
    EXPECT_TRUE(strstr(rendered, "detached_nonce_caller_supplied=0") != 0, "report seal detached nonce");
    EXPECT_TRUE(strstr(rendered, "status=hybrid-envelope-sealed") != 0, "report sealed status");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            first_ciphertext,
            first_ciphertext_len,
            first_salt,
            sizeof(first_salt),
            first_nonce,
            sizeof(first_nonce),
            first_tag,
            sizeof(first_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "open status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "open ok");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "open recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "open recovered plaintext");
    EXPECT_TRUE(open_result.authentication_tag_verified == 1u, "open tag verified");
    EXPECT_TRUE(open_result.unauthenticated_plaintext_staged == 1u, "open staged before auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 1u, "open staged plaintext cleared");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 1u,
        "open plaintext released after auth");
    EXPECT_TRUE(open_result.decryption_performed == 1u, "open performed");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "open hkdf zeroized");
    EXPECT_TRUE(open_result.salt_generated == 0u, "open does not generate salt");
    EXPECT_TRUE(open_result.nonce_generated == 0u, "open does not generate nonce");
    EXPECT_TRUE(open_result.detached_salt_caller_supplied == 1u, "open detached salt supplied");
    EXPECT_TRUE(open_result.detached_nonce_caller_supplied == 1u, "open detached nonce supplied");
    EXPECT_TRUE(open_result.detached_suite_kdf_bound == 1u, "open detached suite kdf bound");
    EXPECT_TRUE(open_result.detached_aad_framed == 1u, "open detached aad framed");
    EXPECT_TRUE(open_result.detached_caller_aad_authenticated == 1u, "open detached caller aad");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            second_ciphertext,
            sizeof(second_ciphertext),
            &second_ciphertext_len,
            second_salt,
            sizeof(second_salt),
            second_nonce,
            sizeof(second_nonce),
            second_tag,
            sizeof(second_tag),
            &second_seal_result) == LATTICRA_STATUS_OK,
        "second seal status");
    EXPECT_TRUE(second_seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "second seal ok");
    EXPECT_TRUE(first_ciphertext_len == second_ciphertext_len, "second ciphertext len");
    EXPECT_TRUE(
        memcmp(first_salt, second_salt, sizeof(first_salt)) != 0 ||
            memcmp(first_nonce, second_nonce, sizeof(first_nonce)) != 0 ||
            memcmp(first_tag, second_tag, sizeof(first_tag)) != 0 ||
            memcmp(first_ciphertext, second_ciphertext, first_ciphertext_len) != 0,
        "fresh seal material differs");
    return 0;
}

static int committed_seal_open_generates_salt_nonce_and_commitment(void) {
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char salt_out[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char nonce_out[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;
    char rendered[LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX];

    memset(ciphertext, 0, sizeof(ciphertext));
    memset(recovered, 0, sizeof(recovered));
    memset(salt_out, 0, sizeof(salt_out));
    memset(nonce_out, 0, sizeof(nonce_out));
    memset(tag, 0, sizeof(tag));
    memset(commitment, 0, sizeof(commitment));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_committed(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            salt_out,
            sizeof(salt_out),
            nonce_out,
            sizeof(nonce_out),
            tag,
            sizeof(tag),
            commitment,
            sizeof(commitment),
            &seal_result) == LATTICRA_STATUS_OK,
        "committed seal status");
    EXPECT_TRUE(seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "committed seal ok");
    EXPECT_TRUE(strcmp(seal_result.operation_state, "committed-sealed") == 0, "committed seal operation");
    EXPECT_TRUE(
        strcmp(seal_result.status, "hybrid-envelope-committed-sealed") == 0,
        "committed seal result status");
    EXPECT_TRUE(seal_result.salt_generated == 1u, "committed seal salt generated");
    EXPECT_TRUE(seal_result.nonce_generated == 1u, "committed seal nonce generated");
    EXPECT_TRUE(expect_generated_random_evidence(&seal_result) == 0, "committed seal random evidence");
    EXPECT_TRUE(seal_result.detached_salt_caller_supplied == 0u, "committed seal salt generated flag");
    EXPECT_TRUE(seal_result.detached_nonce_caller_supplied == 0u, "committed seal nonce generated flag");
    EXPECT_TRUE(
        seal_result.detached_commitment_size_bytes == LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES,
        "committed seal commitment size");
    EXPECT_TRUE(seal_result.detached_key_commitment_present == 1u, "committed seal commitment present");
    EXPECT_TRUE(seal_result.detached_commitment_key_kdf_bound == 1u, "committed seal commitment kdf");
    EXPECT_TRUE(seal_result.detached_commitment_caller_aad_bound == 1u, "committed seal commitment aad");
    EXPECT_TRUE(seal_result.detached_commitment_input_streamed == 1u, "committed seal commitment streamed");
    EXPECT_TRUE(
        seal_result.detached_commitment_key_material_zeroized == 1u,
        "committed seal commitment key zeroized");
    EXPECT_TRUE(all_bytes_equal(commitment, sizeof(commitment), 0u) == 0, "committed seal commitment nonzero");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&seal_result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "committed seal report");
    EXPECT_TRUE(expect_generated_random_report(rendered) == 0, "committed seal random report");
    EXPECT_TRUE(
        strstr(rendered, "detached_commitment_size_bytes=32") != 0,
        "committed seal commitment size report");
    EXPECT_TRUE(
        strstr(rendered, "detached_key_commitment_present=1") != 0,
        "committed seal commitment report");
    EXPECT_TRUE(
        strstr(rendered, "detached_commitment_key_kdf_bound=1") != 0,
        "committed seal commitment kdf report");
    EXPECT_TRUE(
        strstr(rendered, "detached_commitment_input_streamed=1") != 0,
        "committed seal commitment streamed report");
    EXPECT_TRUE(
        strstr(rendered, "detached_commitment_key_material_zeroized=1") != 0,
        "committed seal commitment key zeroized report");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_committed(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            ciphertext,
            ciphertext_len,
            salt_out,
            sizeof(salt_out),
            nonce_out,
            sizeof(nonce_out),
            tag,
            sizeof(tag),
            commitment,
            sizeof(commitment),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "committed open status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "committed open ok");
    EXPECT_TRUE(strcmp(open_result.operation_state, "committed-opened") == 0, "committed open operation");
    EXPECT_TRUE(
        strcmp(open_result.status, "hybrid-envelope-committed-opened") == 0,
        "committed open result status");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "committed open recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "committed open recovered plaintext");
    EXPECT_TRUE(open_result.detached_commitment_verified == 1u, "committed open commitment verified");
    EXPECT_TRUE(
        open_result.detached_commitment_checked_before_decrypt == 1u,
        "committed open commitment checked");
    EXPECT_TRUE(open_result.authentication_tag_verified == 1u, "committed open tag verified");
    EXPECT_TRUE(open_result.plaintext_released_after_authentication == 1u, "committed open release");
    return 0;
}

static int attached_record_seal_open_round_trip(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char tampered_record[sizeof(record)];
    unsigned char recovered[sizeof(plaintext)];
    size_t record_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;
    char rendered[LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX];

    memset(record, 0, sizeof(record));
    memset(tampered_record, 0, sizeof(tampered_record));
    memset(recovered, 0, sizeof(recovered));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &seal_result) == LATTICRA_STATUS_OK,
        "record seal status");
    EXPECT_TRUE(seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "record seal ok");
    EXPECT_TRUE(
        record_len ==
            LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
                sizeof(plaintext) - 1u +
                LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES,
        "record len");
    EXPECT_TRUE(seal_result.record_format_present == 1u, "record format");
    EXPECT_TRUE(seal_result.record_version == LATTICRA_SEAL_HYBRID_RECORD_VERSION, "record version");
    EXPECT_TRUE(
        seal_result.record_suite_id == LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM,
        "record suite id");
    EXPECT_TRUE(seal_result.record_suite_authenticated == 1u, "record suite authenticated");
    EXPECT_TRUE(seal_result.record_kdf_domain_authenticated == 1u, "record kdf domain authenticated");
    EXPECT_TRUE(seal_result.record_suite_kdf_bound == 1u, "record suite bound to kdf");
    EXPECT_TRUE(seal_result.record_salt_nonce_nonzero == 1u, "record salt nonce nonzero");
    EXPECT_TRUE(seal_result.record_header_shape_validated == 1u, "record shape validated");
    EXPECT_TRUE(seal_result.malformed_record_rejected == 0u, "record not malformed");
    EXPECT_TRUE(seal_result.record_header_size_bytes == LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES, "record header size");
    EXPECT_TRUE(
        seal_result.record_protected_header_size_bytes == LATTICRA_SEAL_HYBRID_RECORD_PROTECTED_HEADER_BYTES,
        "record protected header size");
    EXPECT_TRUE(
        seal_result.record_commitment_size_bytes == LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES,
        "record commitment size");
    EXPECT_TRUE(seal_result.record_size_bytes == record_len, "record size");
    EXPECT_TRUE(
        seal_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record seal aad includes framed record aad");
    EXPECT_TRUE(seal_result.caller_aad_size_bytes == sizeof(aad) - 1u, "record caller aad size");
    EXPECT_TRUE(
        seal_result.record_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record framed aad size");
    EXPECT_TRUE(seal_result.record_aad_framed == 1u, "record aad framed");
    EXPECT_TRUE(seal_result.detached_aad_framed == 0u, "record not detached aad framed");
    EXPECT_TRUE(seal_result.record_aad_label_authenticated == 1u, "record aad label authenticated");
    EXPECT_TRUE(seal_result.record_caller_aad_authenticated == 1u, "record caller aad authenticated");
    EXPECT_TRUE(seal_result.classical_shared_secret_bound == 1u, "record classical secret bound");
    EXPECT_TRUE(seal_result.pqc_shared_secret_bound == 1u, "record pqc secret bound");
    EXPECT_TRUE(seal_result.hybrid_secret_length_framed == 1u, "record hybrid secret length framed");
    EXPECT_TRUE(seal_result.hybrid_secret_role_labeled == 1u, "record hybrid secret role labeled");
    EXPECT_TRUE(seal_result.hybrid_secret_algorithm_labeled == 1u, "record hybrid algorithm labeled");
    EXPECT_TRUE(seal_result.hybrid_secret_order_bound == 1u, "record hybrid secret order bound");
    EXPECT_TRUE(seal_result.hybrid_secret_components_distinct == 1u, "record hybrid secrets distinct");
    EXPECT_TRUE(seal_result.attached_record_sealed == 1u, "record sealed");
    EXPECT_TRUE(seal_result.record_header_authenticated == 1u, "record seal header authenticated");
    EXPECT_TRUE(seal_result.record_key_commitment_present == 1u, "record commitment present");
    EXPECT_TRUE(seal_result.record_commitment_key_kdf_bound == 1u, "record commitment kdf bound");
    EXPECT_TRUE(
        seal_result.record_commitment_caller_aad_bound == 1u,
        "record commitment caller aad bound");
    EXPECT_TRUE(
        seal_result.record_commitment_input_streamed == 1u,
        "record commitment streamed");
    EXPECT_TRUE(
        seal_result.record_commitment_key_material_zeroized == 1u,
        "record commitment key zeroized");
    EXPECT_TRUE(seal_result.kdf_domain_separated == 1u, "record kdf separated");
    EXPECT_TRUE(
        seal_result.kdf_domain_id == LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD,
        "record kdf id");
    EXPECT_TRUE(seal_result.detached_kdf_domain == 0u, "record not detached kdf");
    EXPECT_TRUE(seal_result.attached_record_kdf_domain == 1u, "record attached kdf");
    EXPECT_TRUE(seal_result.salt_generated == 1u, "record salt generated");
    EXPECT_TRUE(seal_result.nonce_generated == 1u, "record nonce generated");
    EXPECT_TRUE(expect_generated_random_evidence(&seal_result) == 0, "record random evidence");
    EXPECT_TRUE(seal_result.salt_nonzero == 1u, "record salt nonzero");
    EXPECT_TRUE(seal_result.nonce_nonzero == 1u, "record nonce nonzero");
    EXPECT_TRUE(seal_result.detached_salt_caller_supplied == 0u, "record salt not detached");
    EXPECT_TRUE(seal_result.detached_nonce_caller_supplied == 0u, "record nonce not detached");
    EXPECT_TRUE(seal_result.attached_record_salt_generated == 1u, "record attached salt generated");
    EXPECT_TRUE(seal_result.attached_record_nonce_generated == 1u, "record attached nonce generated");
    EXPECT_TRUE(seal_result.hkdf_provider_api_used == 1u, "record hkdf provider");
    EXPECT_TRUE(
        seal_result.hkdf_extract_expand_standard_api_used == 1u,
        "record hkdf standard api");
    EXPECT_TRUE(seal_result.hkdf_sha256_digest_bound == 1u, "record hkdf sha256");
    EXPECT_TRUE(seal_result.hkdf_manual_fallback_used == 0u, "record no hkdf fallback");
    EXPECT_TRUE(seal_result.aes_gcm_provider_api_used == 1u, "record aes provider");
    EXPECT_TRUE(seal_result.aes_gcm_provider_cipher_fetched == 1u, "record aes fetch");
    EXPECT_TRUE(seal_result.aes_gcm_96bit_nonce_configured == 1u, "record aes nonce");
    EXPECT_TRUE(seal_result.aes_gcm_128bit_tag_bound == 1u, "record aes tag");
    EXPECT_TRUE(seal_result.aes_gcm_static_cipher_fallback_used == 0u, "record aes no fallback");
    EXPECT_TRUE(seal_result.hkdf_intermediate_material_zeroized == 1u, "record hkdf zeroized");
    EXPECT_TRUE(strcmp(seal_result.operation_state, "record-sealed") == 0, "record operation");
    EXPECT_TRUE(strcmp(seal_result.status, "hybrid-envelope-record-sealed") == 0, "record status");
    EXPECT_TRUE(memcmp(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES) == 0, "record magic");
    EXPECT_TRUE(record[8] == LATTICRA_SEAL_HYBRID_RECORD_VERSION, "record version byte");
    EXPECT_TRUE(
        record[9] ==
            (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                            LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE),
        "record flags");
    EXPECT_TRUE(
        record[10] == (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM,
        "record suite byte");
    EXPECT_TRUE(
        record[11] == (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD,
        "record kdf domain byte");
    EXPECT_TRUE(
        memcmp(record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES, plaintext, sizeof(plaintext) - 1u) != 0,
        "record ciphertext differs");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&seal_result, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK,
        "record seal report");
    EXPECT_TRUE(strstr(rendered, "record_format_present=1") != 0, "record format report");
    EXPECT_TRUE(strstr(rendered, "record_suite_id=1") != 0, "record suite report");
    EXPECT_TRUE(strstr(rendered, "record_suite_authenticated=1") != 0, "record suite auth report");
    EXPECT_TRUE(strstr(rendered, "record_kdf_domain_authenticated=1") != 0, "record kdf auth report");
    EXPECT_TRUE(strstr(rendered, "record_suite_kdf_bound=1") != 0, "record suite kdf report");
    EXPECT_TRUE(strstr(rendered, "record_salt_nonce_nonzero=1") != 0, "record salt nonce report");
    EXPECT_TRUE(strstr(rendered, "record_header_shape_validated=1") != 0, "record shape report");
    EXPECT_TRUE(strstr(rendered, "malformed_record_rejected=0") != 0, "record no malformed report");
    EXPECT_TRUE(strstr(rendered, "caller_aad_size_bytes=32") != 0, "record caller aad report");
    EXPECT_TRUE(strstr(rendered, "record_aad_size_bytes=112") != 0, "record framed aad report");
    EXPECT_TRUE(strstr(rendered, "record_aad_framed=1") != 0, "record aad framed report");
    EXPECT_TRUE(strstr(rendered, "detached_aad_framed=0") != 0, "record not detached aad report");
    EXPECT_TRUE(strstr(rendered, "record_aad_label_authenticated=1") != 0, "record aad label report");
    EXPECT_TRUE(strstr(rendered, "record_caller_aad_authenticated=1") != 0, "record caller aad report");
    EXPECT_TRUE(strstr(rendered, "classical_shared_secret_bound=1") != 0, "record classical bound report");
    EXPECT_TRUE(strstr(rendered, "pqc_shared_secret_bound=1") != 0, "record pqc bound report");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_length_framed=1") != 0, "record length framed report");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_role_labeled=1") != 0, "record role labeled report");
    EXPECT_TRUE(
        strstr(rendered, "hybrid_secret_algorithm_labeled=1") != 0,
        "record algorithm labeled report");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_order_bound=1") != 0, "record order bound report");
    EXPECT_TRUE(strstr(rendered, "hybrid_secret_components_distinct=1") != 0, "record distinct report");
    EXPECT_TRUE(strstr(rendered, "record_header_authenticated=1") != 0, "record auth report");
    EXPECT_TRUE(strstr(rendered, "record_commitment_size_bytes=32") != 0, "record commitment size report");
    EXPECT_TRUE(strstr(rendered, "record_key_commitment_present=1") != 0, "record commitment report");
    EXPECT_TRUE(
        strstr(rendered, "record_commitment_key_kdf_bound=1") != 0,
        "record commitment kdf report");
    EXPECT_TRUE(
        strstr(rendered, "record_commitment_caller_aad_bound=1") != 0,
        "record commitment caller aad report");
    EXPECT_TRUE(
        strstr(rendered, "record_commitment_input_streamed=1") != 0,
        "record commitment streamed report");
    EXPECT_TRUE(
        strstr(rendered, "record_commitment_key_material_zeroized=1") != 0,
        "record commitment key zeroized report");
    EXPECT_TRUE(strstr(rendered, "attached_record_sealed=1") != 0, "record sealed report");
    EXPECT_TRUE(strstr(rendered, "kdf_domain_separated=1") != 0, "record kdf report");
    EXPECT_TRUE(strstr(rendered, "kdf_domain_id=2") != 0, "record kdf id report");
    EXPECT_TRUE(strstr(rendered, "attached_record_kdf_domain=1") != 0, "record attached kdf report");
    EXPECT_TRUE(strstr(rendered, "detached_salt_caller_supplied=0") != 0, "record detached salt report");
    EXPECT_TRUE(strstr(rendered, "detached_nonce_caller_supplied=0") != 0, "record detached nonce report");
    EXPECT_TRUE(strstr(rendered, "attached_record_salt_generated=1") != 0, "record attached salt report");
    EXPECT_TRUE(strstr(rendered, "attached_record_nonce_generated=1") != 0, "record attached nonce report");
    EXPECT_TRUE(expect_generated_random_report(rendered) == 0, "record random report");
    EXPECT_TRUE(strstr(rendered, "failed_plaintext_output_cleared=0") != 0, "record no plaintext clear report");
    EXPECT_TRUE(strstr(rendered, "failed_record_output_cleared=0") != 0, "record no record clear report");
    EXPECT_TRUE(strstr(rendered, "unsafe_buffer_overlap_rejected=0") != 0, "record no overlap report");
    EXPECT_TRUE(strstr(rendered, "hkdf_provider_api_used=1") != 0, "record hkdf provider report");
    EXPECT_TRUE(
        strstr(rendered, "hkdf_extract_expand_standard_api_used=1") != 0,
        "record hkdf standard report");
    EXPECT_TRUE(strstr(rendered, "hkdf_sha256_digest_bound=1") != 0, "record hkdf sha256 report");
    EXPECT_TRUE(strstr(rendered, "hkdf_manual_fallback_used=0") != 0, "record no fallback report");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_provider_api_used=1") != 0, "record aes provider report");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_provider_cipher_fetched=1") != 0, "record aes fetch report");
    EXPECT_TRUE(
        strstr(rendered, "aes_gcm_96bit_nonce_configured=1") != 0,
        "record aes nonce report");
    EXPECT_TRUE(strstr(rendered, "aes_gcm_128bit_tag_bound=1") != 0, "record aes tag report");
    EXPECT_TRUE(
        strstr(rendered, "aes_gcm_static_cipher_fallback_used=0") != 0,
        "record aes no fallback report");
    EXPECT_TRUE(strstr(rendered, "hkdf_intermediate_material_zeroized=1") != 0, "record hkdf zeroized report");
    EXPECT_TRUE(strstr(rendered, "status=hybrid-envelope-record-sealed") != 0, "record status report");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "record open status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "record open ok");
    EXPECT_TRUE(open_result.attached_record_opened == 1u, "record opened");
    EXPECT_TRUE(open_result.attached_record_authenticated == 1u, "record authenticated");
    EXPECT_TRUE(open_result.record_header_authenticated == 1u, "record open header authenticated");
    EXPECT_TRUE(open_result.record_key_commitment_present == 1u, "record open commitment present");
    EXPECT_TRUE(open_result.record_commitment_key_kdf_bound == 1u, "record open commitment kdf");
    EXPECT_TRUE(open_result.record_commitment_verified == 1u, "record open commitment verified");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "record open commitment before decrypt");
    EXPECT_TRUE(
        open_result.record_commitment_caller_aad_bound == 1u,
        "record open commitment caller aad bound");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "record open commitment streamed");
    EXPECT_TRUE(
        open_result.record_commitment_key_material_zeroized == 1u,
        "record open commitment key zeroized");
    EXPECT_TRUE(open_result.record_suite_authenticated == 1u, "record open suite authenticated");
    EXPECT_TRUE(open_result.record_kdf_domain_authenticated == 1u, "record open kdf domain authenticated");
    EXPECT_TRUE(open_result.record_suite_kdf_bound == 1u, "record open suite bound to kdf");
    EXPECT_TRUE(open_result.record_salt_nonce_nonzero == 1u, "record open salt nonce nonzero");
    EXPECT_TRUE(open_result.record_header_shape_validated == 1u, "record open shape validated");
    EXPECT_TRUE(open_result.malformed_record_rejected == 0u, "record open not malformed");
    EXPECT_TRUE(open_result.record_aad_framed == 1u, "record open aad framed");
    EXPECT_TRUE(open_result.detached_aad_framed == 0u, "record open not detached aad framed");
    EXPECT_TRUE(open_result.record_aad_label_authenticated == 1u, "record open aad label authenticated");
    EXPECT_TRUE(open_result.record_caller_aad_authenticated == 1u, "record open caller aad authenticated");
    EXPECT_TRUE(open_result.classical_shared_secret_bound == 1u, "record open classical bound");
    EXPECT_TRUE(open_result.pqc_shared_secret_bound == 1u, "record open pqc bound");
    EXPECT_TRUE(open_result.hybrid_secret_length_framed == 1u, "record open length framed");
    EXPECT_TRUE(open_result.hybrid_secret_role_labeled == 1u, "record open role labeled");
    EXPECT_TRUE(open_result.hybrid_secret_algorithm_labeled == 1u, "record open algorithm labeled");
    EXPECT_TRUE(open_result.hybrid_secret_order_bound == 1u, "record open order bound");
    EXPECT_TRUE(open_result.salt_nonzero == 1u, "record open salt nonzero");
    EXPECT_TRUE(open_result.nonce_nonzero == 1u, "record open nonce nonzero");
    EXPECT_TRUE(open_result.kdf_domain_separated == 1u, "record open kdf separated");
    EXPECT_TRUE(open_result.attached_record_kdf_domain == 1u, "record open attached kdf");
    EXPECT_TRUE(open_result.detached_salt_caller_supplied == 0u, "record open salt not detached");
    EXPECT_TRUE(open_result.detached_nonce_caller_supplied == 0u, "record open nonce not detached");
    EXPECT_TRUE(open_result.attached_record_salt_generated == 1u, "record open attached salt generated");
    EXPECT_TRUE(open_result.attached_record_nonce_generated == 1u, "record open attached nonce generated");
    EXPECT_TRUE(open_result.hkdf_provider_api_used == 1u, "record open hkdf provider");
    EXPECT_TRUE(
        open_result.hkdf_extract_expand_standard_api_used == 1u,
        "record open hkdf standard api");
    EXPECT_TRUE(open_result.hkdf_sha256_digest_bound == 1u, "record open hkdf sha256");
    EXPECT_TRUE(open_result.hkdf_manual_fallback_used == 0u, "record open no hkdf fallback");
    EXPECT_TRUE(open_result.aes_gcm_provider_api_used == 1u, "record open aes provider");
    EXPECT_TRUE(open_result.aes_gcm_provider_cipher_fetched == 1u, "record open aes fetch");
    EXPECT_TRUE(open_result.aes_gcm_96bit_nonce_configured == 1u, "record open aes nonce");
    EXPECT_TRUE(open_result.aes_gcm_128bit_tag_bound == 1u, "record open aes tag");
    EXPECT_TRUE(open_result.aes_gcm_static_cipher_fallback_used == 0u, "record open aes no fallback");
    EXPECT_TRUE(open_result.authentication_tag_verified == 1u, "record tag verified");
    EXPECT_TRUE(open_result.unauthenticated_plaintext_staged == 1u, "record open staged before auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 1u, "record open staged plaintext cleared");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 1u,
        "record open plaintext released after auth");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "record open hkdf zeroized");
    EXPECT_TRUE(
        open_result.aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record open aad includes framed record aad");
    EXPECT_TRUE(open_result.caller_aad_size_bytes == sizeof(aad) - 1u, "record open caller aad size");
    EXPECT_TRUE(
        open_result.record_aad_size_bytes ==
            LATTICRA_SEAL_HYBRID_RECORD_AAD_FRAME_BYTES + sizeof(aad) - 1u,
        "record open framed aad size");
    EXPECT_TRUE(strcmp(open_result.operation_state, "record-opened") == 0, "record open operation");
    EXPECT_TRUE(strcmp(open_result.status, "hybrid-envelope-record-opened") == 0, "record open status text");
    EXPECT_TRUE(recovered_len == sizeof(plaintext) - 1u, "record recovered len");
    EXPECT_TRUE(memcmp(recovered, plaintext, recovered_len) == 0, "record recovered plaintext");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            1u,
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "record small output status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL,
        "record small output error");
    EXPECT_TRUE(recovered_len == 0u, "record small output len reset");
    EXPECT_TRUE(recovered[0] == 0u, "record small output plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "record small output plaintext clear flag");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            0,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "record invalid aad status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "record invalid aad error");
    EXPECT_TRUE(recovered_len == 0u, "record invalid aad len reset");
    EXPECT_TRUE(recovered[0] == 0u, "record invalid aad plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "record invalid aad plaintext clear flag");

    memcpy(tampered_record, record, record_len);
    tampered_record[8] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "bad record open status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD, "bad record error");
    EXPECT_TRUE(open_result.malformed_record_rejected == 1u, "bad record malformed flag");
    EXPECT_TRUE(open_result.record_header_shape_validated == 0u, "bad record shape not validated");
    EXPECT_TRUE(recovered_len == 0u, "bad record len reset");
    EXPECT_TRUE(recovered[0] == 0u, "bad record plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "bad record plaintext clear flag");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "bad record no decrypt");

    memcpy(tampered_record, record, record_len);
    tampered_record[10] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "bad record suite status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD, "bad record suite error");
    EXPECT_TRUE(open_result.malformed_record_rejected == 1u, "bad record suite malformed flag");
    EXPECT_TRUE(open_result.record_header_shape_validated == 0u, "bad record suite shape not validated");
    EXPECT_TRUE(open_result.record_suite_authenticated == 0u, "bad record suite not authenticated");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "bad record suite no decrypt");

    memcpy(tampered_record, record, record_len);
    tampered_record[11] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "bad record kdf domain status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_RECORD,
        "bad record kdf domain error");
    EXPECT_TRUE(open_result.malformed_record_rejected == 1u, "bad record kdf malformed flag");
    EXPECT_TRUE(open_result.record_header_shape_validated == 0u, "bad record kdf shape not validated");
    EXPECT_TRUE(open_result.record_kdf_domain_authenticated == 0u, "bad record kdf not authenticated");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "bad record kdf no decrypt");

    memcpy(tampered_record, record, record_len);
    tampered_record[20] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "tampered protected header status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "tampered protected header auth");
    EXPECT_TRUE(recovered_len == 0u, "tampered protected header len reset");
    EXPECT_TRUE(recovered[0] == 0u, "tampered protected header plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "tampered protected header clear flag");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "tampered protected header commitment checked");
    EXPECT_TRUE(
        open_result.record_commitment_tampering_rejected == 1u,
        "tampered protected header commitment rejected");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "tampered protected header commitment streamed");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 0u,
        "tampered protected header not staged before commitment auth");
    EXPECT_TRUE(
        open_result.staged_plaintext_cleared == 0u,
        "tampered protected header no staged buffer");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 0u,
        "tampered protected header no plaintext release after auth");
    EXPECT_TRUE(open_result.record_header_authenticated == 0u, "tampered protected header not authenticated");

    memcpy(tampered_record, record, record_len);
    tampered_record[64] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "tampered record tag status");
    EXPECT_TRUE(open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED, "tampered record auth");
    EXPECT_TRUE(recovered_len == 0u, "tampered record len reset");
    EXPECT_TRUE(recovered[0] == 0u, "tampered record plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "tampered record plaintext clear flag");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "tampered record commitment checked");
    EXPECT_TRUE(
        open_result.record_commitment_tampering_rejected == 1u,
        "tampered record commitment rejected");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "tampered record commitment streamed");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 0u,
        "tampered record not staged before commitment auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 0u, "tampered record no staged buffer");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 0u,
        "tampered record no plaintext release after auth");
    EXPECT_TRUE(open_result.attached_record_authenticated == 0u, "tampered record not authenticated");
    return 0;
}

static int malformed_attached_records_are_rejected_before_crypto(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char malformed[sizeof(record)];
    size_t record_len = 0u;
    latticra_seal_hybrid_envelope_result_t seal_result;

    memset(record, 0, sizeof(record));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &seal_result) == LATTICRA_STATUS_OK,
        "malformed record setup status");
    EXPECT_TRUE(seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "malformed record setup ok");

    memcpy(malformed, record, record_len);
    malformed[0] ^= 0x01u;
    EXPECT_TRUE(
        expect_malformed_record_rejected(malformed, record_len, "malformed record magic status") == 0,
        "malformed record magic rejected");

    memcpy(malformed, record, record_len);
    malformed[9] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT;
    EXPECT_TRUE(
        expect_malformed_record_rejected(malformed, record_len, "malformed record flags status") == 0,
        "malformed record flags rejected");

    EXPECT_TRUE(
        expect_malformed_record_rejected(
            record,
            LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES - 1u,
            "malformed short record status") == 0,
        "malformed short record rejected");

    memcpy(malformed, record, record_len);
    write_test_u64_be(malformed + 12u, record_len);
    EXPECT_TRUE(
        expect_malformed_record_rejected(malformed, record_len, "malformed record length status") == 0,
        "malformed record length rejected");

    memcpy(malformed, record, record_len);
    write_test_u64_be(
        malformed + 12u,
        LATTICRA_SEAL_HYBRID_MESSAGE_MAX + 1u);
    EXPECT_TRUE(
        expect_malformed_record_rejected(malformed, record_len, "oversized record length status") == 0,
        "oversized record length rejected");

    return 0;
}

static int hybrid_secret_components_are_bound(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char mutated_classical[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES];
    unsigned char mutated_pqc[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES];
    size_t record_len = 0u;
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;

    memset(record, 0, sizeof(record));
    memset(recovered, 0x7f, sizeof(recovered));
    memcpy(mutated_classical, classical_shared_secret, sizeof(mutated_classical));
    memcpy(mutated_pqc, pqc_shared_secret, sizeof(mutated_pqc));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &seal_result) == LATTICRA_STATUS_OK,
        "hybrid secret binding seal status");
    EXPECT_TRUE(seal_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "hybrid secret binding seal ok");
    EXPECT_TRUE(seal_result.classical_shared_secret_bound == 1u, "hybrid seal classical bound");
    EXPECT_TRUE(seal_result.pqc_shared_secret_bound == 1u, "hybrid seal pqc bound");
    EXPECT_TRUE(seal_result.hybrid_secret_length_framed == 1u, "hybrid seal length framed");
    EXPECT_TRUE(seal_result.hybrid_secret_role_labeled == 1u, "hybrid seal role labeled");
    EXPECT_TRUE(seal_result.hybrid_secret_algorithm_labeled == 1u, "hybrid seal algorithm labeled");
    EXPECT_TRUE(seal_result.hybrid_secret_order_bound == 1u, "hybrid seal order bound");
    EXPECT_TRUE(seal_result.hybrid_secret_components_distinct == 1u, "hybrid seal secrets distinct");

    mutated_classical[0] ^= 0x01u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            mutated_classical,
            sizeof(mutated_classical),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "mutated classical open status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "mutated classical auth failed");
    EXPECT_TRUE(open_result.classical_shared_secret_bound == 1u, "mutated classical bound flag");
    EXPECT_TRUE(open_result.pqc_shared_secret_bound == 1u, "mutated classical pqc bound flag");
    EXPECT_TRUE(open_result.hybrid_secret_length_framed == 1u, "mutated classical length framed");
    EXPECT_TRUE(open_result.hybrid_secret_role_labeled == 1u, "mutated classical role labeled");
    EXPECT_TRUE(
        open_result.hybrid_secret_algorithm_labeled == 1u,
        "mutated classical algorithm labeled");
    EXPECT_TRUE(open_result.hybrid_secret_order_bound == 1u, "mutated classical order bound");
    EXPECT_TRUE(open_result.authentication_tag_verified == 0u, "mutated classical tag not verified");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "mutated classical commitment checked");
    EXPECT_TRUE(
        open_result.record_commitment_tampering_rejected == 1u,
        "mutated classical commitment rejected");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "mutated classical commitment streamed");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 0u,
        "mutated classical not staged before commitment auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 0u, "mutated classical no staged buffer");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 0u,
        "mutated classical no plaintext release after auth");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "mutated classical no decrypt");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "mutated classical hkdf zeroized");
    EXPECT_TRUE(
        open_result.record_commitment_key_material_zeroized == 1u,
        "mutated classical commitment key zeroized");
    EXPECT_TRUE(recovered_len == 0u, "mutated classical len reset");
    EXPECT_TRUE(recovered[0] == 0u, "mutated classical plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "mutated classical plaintext clear flag");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    mutated_pqc[0] ^= 0x01u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            mutated_pqc,
            sizeof(mutated_pqc),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "mutated pqc open status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "mutated pqc auth failed");
    EXPECT_TRUE(open_result.classical_shared_secret_bound == 1u, "mutated pqc classical bound flag");
    EXPECT_TRUE(open_result.pqc_shared_secret_bound == 1u, "mutated pqc bound flag");
    EXPECT_TRUE(open_result.hybrid_secret_length_framed == 1u, "mutated pqc length framed");
    EXPECT_TRUE(open_result.hybrid_secret_role_labeled == 1u, "mutated pqc role labeled");
    EXPECT_TRUE(open_result.hybrid_secret_algorithm_labeled == 1u, "mutated pqc algorithm labeled");
    EXPECT_TRUE(open_result.hybrid_secret_order_bound == 1u, "mutated pqc order bound");
    EXPECT_TRUE(open_result.authentication_tag_verified == 0u, "mutated pqc tag not verified");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "mutated pqc commitment checked");
    EXPECT_TRUE(
        open_result.record_commitment_tampering_rejected == 1u,
        "mutated pqc commitment rejected");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "mutated pqc commitment streamed");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 0u,
        "mutated pqc not staged before commitment auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 0u, "mutated pqc no staged buffer");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 0u,
        "mutated pqc no plaintext release after auth");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "mutated pqc no decrypt");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "mutated pqc hkdf zeroized");
    EXPECT_TRUE(
        open_result.record_commitment_key_material_zeroized == 1u,
        "mutated pqc commitment key zeroized");
    EXPECT_TRUE(recovered_len == 0u, "mutated pqc len reset");
    EXPECT_TRUE(recovered[0] == 0u, "mutated pqc plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "mutated pqc plaintext clear flag");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            classical_shared_secret,
            sizeof(classical_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) == LATTICRA_STATUS_OK,
        "swapped hybrid secret open status");
    EXPECT_TRUE(
        open_result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "swapped hybrid secret auth failed");
    EXPECT_TRUE(open_result.classical_shared_secret_bound == 1u, "swapped hybrid classical bound");
    EXPECT_TRUE(open_result.pqc_shared_secret_bound == 1u, "swapped hybrid pqc bound");
    EXPECT_TRUE(open_result.hybrid_secret_length_framed == 1u, "swapped hybrid length framed");
    EXPECT_TRUE(open_result.hybrid_secret_role_labeled == 1u, "swapped hybrid role labeled");
    EXPECT_TRUE(open_result.hybrid_secret_algorithm_labeled == 1u, "swapped hybrid algorithm labeled");
    EXPECT_TRUE(open_result.hybrid_secret_order_bound == 1u, "swapped hybrid order bound");
    EXPECT_TRUE(open_result.authentication_tag_verified == 0u, "swapped hybrid tag not verified");
    EXPECT_TRUE(
        open_result.record_commitment_checked_before_decrypt == 1u,
        "swapped hybrid commitment checked");
    EXPECT_TRUE(
        open_result.record_commitment_tampering_rejected == 1u,
        "swapped hybrid commitment rejected");
    EXPECT_TRUE(
        open_result.record_commitment_input_streamed == 1u,
        "swapped hybrid commitment streamed");
    EXPECT_TRUE(
        open_result.unauthenticated_plaintext_staged == 0u,
        "swapped hybrid not staged before commitment auth");
    EXPECT_TRUE(open_result.staged_plaintext_cleared == 0u, "swapped hybrid no staged buffer");
    EXPECT_TRUE(
        open_result.plaintext_released_after_authentication == 0u,
        "swapped hybrid no plaintext release after auth");
    EXPECT_TRUE(open_result.decryption_performed == 0u, "swapped hybrid no decrypt");
    EXPECT_TRUE(open_result.hkdf_intermediate_material_zeroized == 1u, "swapped hybrid hkdf zeroized");
    EXPECT_TRUE(
        open_result.record_commitment_key_material_zeroized == 1u,
        "swapped hybrid commitment key zeroized");
    EXPECT_TRUE(recovered_len == 0u, "swapped hybrid len reset");
    EXPECT_TRUE(recovered[0] == 0u, "swapped hybrid plaintext cleared");
    EXPECT_TRUE(open_result.failed_plaintext_output_cleared == 1u, "swapped hybrid plaintext clear flag");
    return 0;
}

static int duplicate_hybrid_secret_components_are_rejected_before_kdf(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    size_t ciphertext_len = 42u;
    size_t record_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    context.pqc_shared_secret = classical_shared_secret;
    context.pqc_shared_secret_len = sizeof(classical_shared_secret);
    memset(ciphertext, 0x7au, sizeof(ciphertext));
    memset(tag, 0x7bu, sizeof(tag));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "duplicate hybrid encrypt status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET,
        "duplicate hybrid encrypt error");
    EXPECT_TRUE(result.duplicate_hybrid_shared_secret_rejected == 1u, "duplicate hybrid flag");
    EXPECT_TRUE(result.hybrid_secret_components_distinct == 0u, "duplicate hybrid not distinct");
    EXPECT_TRUE(result.classical_shared_secret_nonzero == 1u, "duplicate hybrid classical checked");
    EXPECT_TRUE(result.pqc_shared_secret_nonzero == 1u, "duplicate hybrid pqc checked");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "duplicate hybrid no hkdf");
    EXPECT_TRUE(result.aes_gcm_encryption_performed == 0u, "duplicate hybrid no aead");
    EXPECT_TRUE(result.encryption_performed == 0u, "duplicate hybrid no encryption");
    EXPECT_TRUE(ciphertext_len == 0u, "duplicate hybrid ciphertext len reset");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "duplicate hybrid ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "duplicate hybrid tag cleared");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "duplicate hybrid ciphertext clear flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "duplicate hybrid tag clear flag");

    memset(record, 0x7cu, sizeof(record));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            classical_shared_secret,
            sizeof(classical_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "duplicate hybrid record seal status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_DUPLICATE_HYBRID_SHARED_SECRET,
        "duplicate hybrid record seal error");
    EXPECT_TRUE(result.duplicate_hybrid_shared_secret_rejected == 1u, "duplicate record flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "duplicate record no hkdf");
    EXPECT_TRUE(record_len == 0u, "duplicate record len reset");
    EXPECT_TRUE(all_bytes_equal(record, sizeof(record), 0u), "duplicate record cleared");
    EXPECT_TRUE(result.failed_record_output_cleared == 1u, "duplicate record clear flag");
    return 0;
}

static int aad_tampering_fails_closed(void) {
    static const unsigned char tampered_aad[] = "latticra-seal:hybrid-envelope:v1:tampered";
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char generated_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char generated_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char generated_tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            generated_salt,
            sizeof(generated_salt),
            generated_nonce,
            sizeof(generated_nonce),
            generated_tag,
            sizeof(generated_tag),
            &result) == LATTICRA_STATUS_OK,
        "tamper seal status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "tamper seal ok");

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            tampered_aad,
            sizeof(tampered_aad) - 1u,
            ciphertext,
            ciphertext_len,
            generated_salt,
            sizeof(generated_salt),
            generated_nonce,
            sizeof(generated_nonce),
            generated_tag,
            sizeof(generated_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "tamper open status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED, "aad auth failed");
    EXPECT_TRUE(recovered_len == 0u, "aad recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "aad plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "aad plaintext clear flag");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "aad tag not verified");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 1u, "aad staged before auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "aad staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "aad no plaintext release after auth");
    EXPECT_TRUE(result.decryption_performed == 0u, "aad no decrypt");
    return 0;
}

static int detached_ciphertext_salt_nonce_tampering_fails_closed(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char tampered_ciphertext[sizeof(expected_fixture_ciphertext)];
    unsigned char tampered_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char tampered_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memcpy(tampered_ciphertext, expected_fixture_ciphertext, sizeof(tampered_ciphertext));
    tampered_ciphertext[0] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            tampered_ciphertext,
            sizeof(tampered_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "detached ciphertext tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "detached ciphertext tamper rejected");
    EXPECT_TRUE(result.detached_aad_framed == 1u, "detached ciphertext tamper framed aad");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "detached ciphertext tamper no tag");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 1u,
        "detached ciphertext tamper staged before auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "detached ciphertext tamper staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "detached ciphertext tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "detached ciphertext tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "detached ciphertext tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "detached ciphertext tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "detached ciphertext tamper clear flag");

    memcpy(tampered_salt, salt, sizeof(tampered_salt));
    tampered_salt[0] ^= 0x01u;
    context = fixture_context();
    context.salt = tampered_salt;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "detached salt tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "detached salt tamper rejected");
    EXPECT_TRUE(result.salt_nonzero == 1u, "detached salt tamper nonzero");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 1u, "detached salt tamper hkdf");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "detached salt tamper no tag");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 1u, "detached salt tamper staged");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "detached salt tamper staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "detached salt tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "detached salt tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "detached salt tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "detached salt tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "detached salt tamper clear flag");

    memcpy(tampered_nonce, nonce, sizeof(tampered_nonce));
    tampered_nonce[0] ^= 0x01u;
    context = fixture_context();
    context.nonce = tampered_nonce;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "detached nonce tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "detached nonce tamper rejected");
    EXPECT_TRUE(result.nonce_nonzero == 1u, "detached nonce tamper nonzero");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 1u, "detached nonce tamper hkdf");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "detached nonce tamper no tag");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 1u, "detached nonce tamper staged");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "detached nonce tamper staged cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "detached nonce tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "detached nonce tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "detached nonce tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "detached nonce tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "detached nonce tamper clear flag");
    return 0;
}

static int expect_committed_detached_tamper_rejected(
    const latticra_seal_hybrid_envelope_context_t *context,
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *tag,
    const unsigned char *commitment,
    const char *status_message) {
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt_committed(
            context,
            ciphertext,
            ciphertext_len,
            tag,
            LATTICRA_SEAL_HYBRID_TAG_BYTES,
            commitment,
            LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        status_message);
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "committed detached tamper rejected");
    EXPECT_TRUE(
        result.detached_commitment_size_bytes == LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES,
        "committed detached tamper commitment size");
    EXPECT_TRUE(result.detached_key_commitment_present == 1u, "committed detached tamper present");
    EXPECT_TRUE(result.detached_commitment_key_kdf_bound == 1u, "committed detached tamper kdf");
    EXPECT_TRUE(
        result.detached_commitment_checked_before_decrypt == 1u,
        "committed detached tamper checked");
    EXPECT_TRUE(
        result.detached_commitment_caller_aad_bound == 1u,
        "committed detached tamper aad bound");
    EXPECT_TRUE(
        result.detached_commitment_input_streamed == 1u,
        "committed detached tamper streamed");
    EXPECT_TRUE(
        result.detached_commitment_tampering_rejected == 1u,
        "committed detached tamper flag");
    EXPECT_TRUE(
        result.detached_commitment_key_material_zeroized == 1u,
        "committed detached tamper key zeroized");
    EXPECT_TRUE(result.detached_aad_framed == 0u, "committed detached tamper no aad frame");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "committed detached tamper no tag");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 0u,
        "committed detached tamper not staged before commitment auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "committed detached tamper no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "committed detached tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "committed detached tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "committed detached tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "committed detached tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "committed detached tamper clear flag");
    return 0;
}

static int committed_detached_tampering_fails_before_decrypt(void) {
    static const unsigned char tampered_aad[] = "latticra-seal:hybrid-envelope:v1:tampered";
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char tampered_ciphertext[sizeof(expected_fixture_ciphertext)];
    unsigned char tampered_salt[sizeof(salt)];
    unsigned char tampered_nonce[sizeof(nonce)];
    unsigned char tampered_tag[sizeof(expected_fixture_tag)];
    unsigned char tampered_commitment[sizeof(expected_fixture_detached_commitment)];

    memcpy(tampered_ciphertext, expected_fixture_ciphertext, sizeof(tampered_ciphertext));
    tampered_ciphertext[0] ^= 0x01u;
    if (expect_committed_detached_tamper_rejected(
            &context,
            tampered_ciphertext,
            sizeof(tampered_ciphertext),
            expected_fixture_tag,
            expected_fixture_detached_commitment,
            "committed detached ciphertext tamper status") != 0) {
        return 1;
    }

    memcpy(tampered_salt, salt, sizeof(tampered_salt));
    tampered_salt[0] ^= 0x01u;
    context = fixture_context();
    context.salt = tampered_salt;
    if (expect_committed_detached_tamper_rejected(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            expected_fixture_detached_commitment,
            "committed detached salt tamper status") != 0) {
        return 1;
    }

    memcpy(tampered_nonce, nonce, sizeof(tampered_nonce));
    tampered_nonce[0] ^= 0x01u;
    context = fixture_context();
    context.nonce = tampered_nonce;
    if (expect_committed_detached_tamper_rejected(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            expected_fixture_detached_commitment,
            "committed detached nonce tamper status") != 0) {
        return 1;
    }

    memcpy(tampered_tag, expected_fixture_tag, sizeof(tampered_tag));
    tampered_tag[0] ^= 0x01u;
    context = fixture_context();
    if (expect_committed_detached_tamper_rejected(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            tampered_tag,
            expected_fixture_detached_commitment,
            "committed detached tag tamper status") != 0) {
        return 1;
    }

    context = fixture_context();
    context.aad = tampered_aad;
    context.aad_len = sizeof(tampered_aad) - 1u;
    if (expect_committed_detached_tamper_rejected(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            expected_fixture_detached_commitment,
            "committed detached aad tamper status") != 0) {
        return 1;
    }

    memcpy(tampered_commitment, expected_fixture_detached_commitment, sizeof(tampered_commitment));
    tampered_commitment[0] ^= 0x01u;
    context = fixture_context();
    if (expect_committed_detached_tamper_rejected(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            tampered_commitment,
            "committed detached commitment tamper status") != 0) {
        return 1;
    }

    return 0;
}

static void build_fixture_record(unsigned char *record) {
    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(expected_fixture_record_ciphertext));
    memcpy(record + 20u, salt, sizeof(salt));
    memcpy(record + 52u, nonce, sizeof(nonce));
    memcpy(record + 64u, expected_fixture_record_tag, sizeof(expected_fixture_record_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        expected_fixture_record_ciphertext,
        sizeof(expected_fixture_record_ciphertext));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
            sizeof(expected_fixture_record_ciphertext),
        expected_fixture_record_commitment,
        sizeof(expected_fixture_record_commitment));
}

static int record_ciphertext_and_nonce_tampering_fails_closed(void) {
    static const unsigned char tampered_aad[] = "latticra-seal:hybrid-envelope:v1:tampered";
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(expected_fixture_record_ciphertext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char tampered_record[sizeof(record)];
    unsigned char recovered[sizeof(plaintext)];
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(record, 0, sizeof(record));
    build_fixture_record(record);

    memcpy(tampered_record, record, sizeof(record));
    tampered_record[LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            sizeof(tampered_record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "record ciphertext tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "record ciphertext tamper rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "record ciphertext tamper shape");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 1u, "record ciphertext tamper salt nonce");
    EXPECT_TRUE(result.record_aad_framed == 0u, "record ciphertext tamper no aad frame");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "record ciphertext tamper no tag");
    EXPECT_TRUE(
        result.record_commitment_caller_aad_bound == 1u,
        "record ciphertext tamper commitment caller aad bound");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "record ciphertext tamper commitment checked");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "record ciphertext tamper commitment rejected");
    EXPECT_TRUE(
        result.record_commitment_input_streamed == 1u,
        "record ciphertext tamper commitment streamed");
    EXPECT_TRUE(
        result.unauthenticated_plaintext_staged == 0u,
        "record ciphertext tamper not staged before commitment auth");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "record ciphertext tamper no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "record ciphertext tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "record ciphertext tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "record ciphertext tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "record ciphertext tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "record ciphertext tamper clear flag");

    memcpy(tampered_record, record, sizeof(record));
    tampered_record[52] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            sizeof(tampered_record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "record nonce tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "record nonce tamper rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "record nonce tamper shape");
    EXPECT_TRUE(result.nonce_nonzero == 1u, "record nonce tamper nonzero");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 1u, "record nonce tamper salt nonce");
    EXPECT_TRUE(result.record_aad_framed == 0u, "record nonce tamper no aad frame");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "record nonce tamper no tag");
    EXPECT_TRUE(
        result.record_commitment_caller_aad_bound == 1u,
        "record nonce tamper commitment caller aad bound");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "record nonce tamper commitment checked");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "record nonce tamper commitment rejected");
    EXPECT_TRUE(
        result.record_commitment_input_streamed == 1u,
        "record nonce tamper commitment streamed");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 0u, "record nonce tamper not staged");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "record nonce tamper no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "record nonce tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "record nonce tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "record nonce tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "record nonce tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "record nonce tamper clear flag");

    memcpy(tampered_record, record, sizeof(record));
    tampered_record[sizeof(tampered_record) - 1u] ^= 0x01u;
    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            tampered_record,
            sizeof(tampered_record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "record commitment tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "record commitment tamper rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "record commitment tamper shape");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 1u, "record commitment tamper salt nonce");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "record commitment tamper checked");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "record commitment tamper flag");
    EXPECT_TRUE(
        result.record_commitment_caller_aad_bound == 1u,
        "record commitment tamper caller aad bound");
    EXPECT_TRUE(
        result.record_commitment_input_streamed == 1u,
        "record commitment tamper streamed");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "record commitment tamper no tag");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 0u, "record commitment tamper not staged");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "record commitment tamper no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "record commitment tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "record commitment tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "record commitment tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "record commitment tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "record commitment tamper clear flag");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            tampered_aad,
            sizeof(tampered_aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "record caller aad tamper status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED,
        "record caller aad tamper rejected");
    EXPECT_TRUE(result.record_header_shape_validated == 1u, "record caller aad tamper shape");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 1u, "record caller aad tamper salt nonce");
    EXPECT_TRUE(
        result.record_commitment_checked_before_decrypt == 1u,
        "record caller aad tamper commitment checked");
    EXPECT_TRUE(
        result.record_commitment_caller_aad_bound == 1u,
        "record caller aad tamper commitment aad bound");
    EXPECT_TRUE(
        result.record_commitment_tampering_rejected == 1u,
        "record caller aad tamper commitment rejected");
    EXPECT_TRUE(
        result.record_commitment_input_streamed == 1u,
        "record caller aad tamper commitment streamed");
    EXPECT_TRUE(result.record_aad_framed == 0u, "record caller aad tamper no aad frame");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "record caller aad tamper no tag");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 0u, "record caller aad tamper not staged");
    EXPECT_TRUE(result.staged_plaintext_cleared == 0u, "record caller aad tamper no staged buffer");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "record caller aad tamper no plaintext release");
    EXPECT_TRUE(result.decryption_performed == 0u, "record caller aad tamper no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "record caller aad tamper len reset");
    EXPECT_TRUE(all_bytes_equal(recovered, sizeof(recovered), 0u), "record caller aad tamper cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "record caller aad tamper clear flag");
    return 0;
}

static int authentication_failure_fails_closed(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t ciphertext_len = 0u;
    size_t recovered_len = 123u;
    latticra_seal_hybrid_envelope_result_t result;

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "auth encrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "auth encrypt ok");

    memset(recovered, 0x7f, sizeof(recovered));
    tag[0] ^= 0x01u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            ciphertext,
            ciphertext_len,
            tag,
            sizeof(tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "auth decrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_AUTHENTICATION_FAILED, "auth failed");
    EXPECT_TRUE(recovered_len == 0u, "auth recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "auth plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "auth plaintext clear flag");
    EXPECT_TRUE(result.decryption_performed == 0u, "auth no decrypt performed");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "auth tag not verified");
    EXPECT_TRUE(result.unauthenticated_plaintext_staged == 1u, "auth staged before tag check");
    EXPECT_TRUE(result.staged_plaintext_cleared == 1u, "auth staged plaintext cleared");
    EXPECT_TRUE(
        result.plaintext_released_after_authentication == 0u,
        "auth no plaintext release after tag failure");
    EXPECT_TRUE(result.hkdf_intermediate_material_zeroized == 1u, "auth hkdf zeroized");
    EXPECT_TRUE(result.key_material_zeroized == 1u, "auth key zeroized");
    return 0;
}

static int weak_shared_secrets_are_rejected(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char zero_secret[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES];
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char generated_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char generated_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    size_t ciphertext_len = 42u;
    size_t recovered_len = 42u;
    size_t record_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(zero_secret, 0, sizeof(zero_secret));
    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(recovered, 0x7f, sizeof(recovered));
    memset(generated_salt, 0x5au, sizeof(generated_salt));
    memset(generated_nonce, 0x6bu, sizeof(generated_nonce));
    memset(tag, 0x4cu, sizeof(tag));
    memset(record, 0x8cu, sizeof(record));

    context.classical_shared_secret = zero_secret;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "weak classical encrypt status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET,
        "weak classical error");
    EXPECT_TRUE(result.weak_shared_secret_rejected == 1u, "weak classical rejected");
    EXPECT_TRUE(result.classical_shared_secret_nonzero == 0u, "weak classical nonzero flag");
    EXPECT_TRUE(result.pqc_shared_secret_nonzero == 0u, "weak classical stops before pqc flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak classical no hkdf");
    EXPECT_TRUE(result.encryption_performed == 0u, "weak classical no encryption");
    EXPECT_TRUE(ciphertext_len == 0u, "weak classical ciphertext len reset");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "weak classical ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "weak classical tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "weak classical ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "weak classical tag cleared");

    context = fixture_context();
    context.pqc_shared_secret = zero_secret;
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "weak pqc decrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET, "weak pqc error");
    EXPECT_TRUE(result.weak_shared_secret_rejected == 1u, "weak pqc rejected");
    EXPECT_TRUE(result.classical_shared_secret_nonzero == 1u, "weak pqc classical checked");
    EXPECT_TRUE(result.pqc_shared_secret_nonzero == 0u, "weak pqc nonzero flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak pqc no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "weak pqc no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "weak pqc recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "weak pqc plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "weak pqc plaintext clear flag");

    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(generated_salt, 0x5au, sizeof(generated_salt));
    memset(generated_nonce, 0x6bu, sizeof(generated_nonce));
    memset(tag, 0x4cu, sizeof(tag));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            zero_secret,
            sizeof(zero_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            generated_salt,
            sizeof(generated_salt),
            generated_nonce,
            sizeof(generated_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "weak seal status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_CLASSICAL_SHARED_SECRET,
        "weak seal error");
    EXPECT_TRUE(result.weak_shared_secret_rejected == 1u, "weak seal rejected");
    EXPECT_TRUE(result.salt_generated == 0u, "weak seal no salt generated");
    EXPECT_TRUE(result.nonce_generated == 0u, "weak seal no nonce generated");
    EXPECT_TRUE(result.failed_salt_output_cleared == 1u, "weak seal salt cleared flag");
    EXPECT_TRUE(result.failed_nonce_output_cleared == 1u, "weak seal nonce cleared flag");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "weak seal ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "weak seal tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(generated_salt, sizeof(generated_salt), 0u), "weak seal salt cleared");
    EXPECT_TRUE(all_bytes_equal(generated_nonce, sizeof(generated_nonce), 0u), "weak seal nonce cleared");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "weak seal ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "weak seal tag cleared");

    record_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            zero_secret,
            sizeof(zero_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "weak record seal status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_PQC_SHARED_SECRET, "weak record seal error");
    EXPECT_TRUE(result.weak_shared_secret_rejected == 1u, "weak record seal rejected");
    EXPECT_TRUE(result.salt_generated == 0u, "weak record seal no salt generated");
    EXPECT_TRUE(result.nonce_generated == 0u, "weak record seal no nonce generated");
    EXPECT_TRUE(record_len == 0u, "weak record seal len reset");
    EXPECT_TRUE(all_bytes_equal(record, sizeof(record), 0u), "weak record seal clears record");
    EXPECT_TRUE(result.failed_record_output_cleared == 1u, "weak record seal clear flag");
    return 0;
}

static int weak_salt_and_nonce_are_rejected(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char zero_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char zero_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char recovered[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(expected_fixture_record_ciphertext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    size_t ciphertext_len = 42u;
    size_t recovered_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(zero_salt, 0, sizeof(zero_salt));
    memset(zero_nonce, 0, sizeof(zero_nonce));
    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(recovered, 0x7f, sizeof(recovered));
    memset(tag, 0x4cu, sizeof(tag));

    context.salt = zero_salt;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "weak salt encrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT, "weak salt error");
    EXPECT_TRUE(result.salt_nonzero == 0u, "weak salt nonzero flag");
    EXPECT_TRUE(result.nonce_nonzero == 0u, "weak salt stops before nonce");
    EXPECT_TRUE(result.weak_salt_rejected == 1u, "weak salt rejected");
    EXPECT_TRUE(result.weak_nonce_rejected == 0u, "weak salt no nonce rejection");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak salt no hkdf");
    EXPECT_TRUE(result.encryption_performed == 0u, "weak salt no encryption");
    EXPECT_TRUE(ciphertext_len == 0u, "weak salt ciphertext len reset");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "weak salt ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "weak salt tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "weak salt ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "weak salt tag cleared");

    context = fixture_context();
    context.nonce = zero_nonce;
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            expected_fixture_ciphertext,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "weak nonce decrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE, "weak nonce error");
    EXPECT_TRUE(result.salt_nonzero == 1u, "weak nonce salt checked");
    EXPECT_TRUE(result.nonce_nonzero == 0u, "weak nonce nonzero flag");
    EXPECT_TRUE(result.weak_salt_rejected == 0u, "weak nonce no salt rejection");
    EXPECT_TRUE(result.weak_nonce_rejected == 1u, "weak nonce rejected");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak nonce no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "weak nonce no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "weak nonce recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "weak nonce plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "weak nonce plaintext clear flag");

    memset(record, 0, sizeof(record));
    memset(recovered, 0x7f, sizeof(recovered));
    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(expected_fixture_record_ciphertext));
    memcpy(record + 52u, nonce, sizeof(nonce));
    memcpy(record + 64u, expected_fixture_record_tag, sizeof(expected_fixture_record_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        expected_fixture_record_ciphertext,
        sizeof(expected_fixture_record_ciphertext));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "weak record salt open status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_SALT, "weak record salt error");
    EXPECT_TRUE(result.record_format_present == 1u, "weak record salt keeps format evidence");
    EXPECT_TRUE(result.record_header_authenticated == 0u, "weak record salt header not authenticated");
    EXPECT_TRUE(result.attached_record_authenticated == 0u, "weak record salt not authenticated");
    EXPECT_TRUE(result.weak_salt_rejected == 1u, "weak record salt rejected");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 0u, "weak record salt nonce gate");
    EXPECT_TRUE(result.record_aad_framed == 0u, "weak record salt no aad frame");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak record salt no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "weak record salt no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "weak record salt recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "weak record salt plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "weak record salt plaintext clear flag");

    memset(record, 0, sizeof(record));
    memset(recovered, 0x7f, sizeof(recovered));
    memcpy(record, "LSEHENV1", LATTICRA_SEAL_HYBRID_RECORD_MAGIC_BYTES);
    record[8] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_VERSION;
    record[9] =
        (unsigned char)(LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_SALT |
                        LATTICRA_SEAL_HYBRID_RECORD_FLAG_GENERATED_NONCE);
    record[10] = (unsigned char)LATTICRA_SEAL_HYBRID_RECORD_SUITE_HKDF_SHA256_AES_256_GCM;
    record[11] = (unsigned char)LATTICRA_SEAL_HYBRID_KDF_DOMAIN_ATTACHED_RECORD;
    write_test_u64_be(record + 12u, sizeof(expected_fixture_record_ciphertext));
    memcpy(record + 20u, salt, sizeof(salt));
    memcpy(record + 64u, expected_fixture_record_tag, sizeof(expected_fixture_record_tag));
    memcpy(
        record + LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES,
        expected_fixture_record_ciphertext,
        sizeof(expected_fixture_record_ciphertext));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            sizeof(record),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "weak record nonce open status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_WEAK_NONCE, "weak record nonce error");
    EXPECT_TRUE(result.salt_nonzero == 1u, "weak record nonce salt checked");
    EXPECT_TRUE(result.nonce_nonzero == 0u, "weak record nonce nonzero flag");
    EXPECT_TRUE(result.weak_nonce_rejected == 1u, "weak record nonce rejected");
    EXPECT_TRUE(result.record_salt_nonce_nonzero == 0u, "weak record nonce salt nonce gate");
    EXPECT_TRUE(result.record_aad_framed == 0u, "weak record nonce no aad frame");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "weak record nonce no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "weak record nonce no decrypt");
    EXPECT_TRUE(recovered_len == 0u, "weak record nonce recovered len reset");
    EXPECT_TRUE(recovered[0] == 0u, "weak record nonce plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "weak record nonce plaintext clear flag");

    return 0;
}

static int unsafe_buffer_overlap_is_rejected(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char encrypt_overlap[sizeof(plaintext) + 8u];
    unsigned char decrypt_overlap[sizeof(expected_fixture_ciphertext) + 8u];
    unsigned char seal_overlap[sizeof(plaintext) + 8u];
    unsigned char record_overlap[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES +
        8u
    ];
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char mutable_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char mutable_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    size_t output_len = 42u;
    size_t record_len = 42u;
    latticra_seal_hybrid_envelope_result_t result;

    memset(encrypt_overlap, 0x41, sizeof(encrypt_overlap));
    memset(tag, 0x4c, sizeof(tag));
    memcpy(encrypt_overlap, plaintext, sizeof(plaintext) - 1u);
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            encrypt_overlap,
            sizeof(plaintext) - 1u,
            encrypt_overlap + 1u,
            sizeof(plaintext) - 1u,
            &output_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "unsafe encrypt overlap status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "unsafe encrypt overlap error");
    EXPECT_TRUE(result.unsafe_buffer_overlap_rejected == 1u, "unsafe encrypt overlap flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "unsafe encrypt overlap no hkdf");
    EXPECT_TRUE(result.encryption_performed == 0u, "unsafe encrypt overlap no encryption");
    EXPECT_TRUE(output_len == 0u, "unsafe encrypt overlap len reset");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "unsafe encrypt overlap ciphertext cleared");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "unsafe encrypt overlap tag cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "unsafe encrypt overlap clears tag");

    memset(decrypt_overlap, 0x42, sizeof(decrypt_overlap));
    memcpy(decrypt_overlap, expected_fixture_ciphertext, sizeof(expected_fixture_ciphertext));
    output_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            decrypt_overlap,
            sizeof(expected_fixture_ciphertext),
            expected_fixture_tag,
            sizeof(expected_fixture_tag),
            decrypt_overlap + 1u,
            sizeof(expected_fixture_ciphertext),
            &output_len,
            &result) == LATTICRA_STATUS_OK,
        "unsafe decrypt overlap status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "unsafe decrypt overlap error");
    EXPECT_TRUE(result.unsafe_buffer_overlap_rejected == 1u, "unsafe decrypt overlap flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "unsafe decrypt overlap no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "unsafe decrypt overlap no decrypt");
    EXPECT_TRUE(result.authentication_tag_verified == 0u, "unsafe decrypt overlap no auth");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "unsafe decrypt overlap plaintext clear flag");
    EXPECT_TRUE(output_len == 0u, "unsafe decrypt overlap len reset");

    memset(seal_overlap, 0x43, sizeof(seal_overlap));
    memset(mutable_salt, 0x5a, sizeof(mutable_salt));
    memset(mutable_nonce, 0x6b, sizeof(mutable_nonce));
    memset(tag, 0x4c, sizeof(tag));
    memcpy(seal_overlap, plaintext, sizeof(plaintext) - 1u);
    output_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            seal_overlap,
            sizeof(plaintext) - 1u,
            seal_overlap + 1u,
            sizeof(plaintext) - 1u,
            &output_len,
            mutable_salt,
            sizeof(mutable_salt),
            mutable_nonce,
            sizeof(mutable_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "unsafe seal overlap status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "unsafe seal overlap error");
    EXPECT_TRUE(result.unsafe_buffer_overlap_rejected == 1u, "unsafe seal overlap flag");
    EXPECT_TRUE(result.salt_generated == 0u, "unsafe seal overlap no salt generated");
    EXPECT_TRUE(result.nonce_generated == 0u, "unsafe seal overlap no nonce generated");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "unsafe seal overlap no hkdf");
    EXPECT_TRUE(result.encryption_performed == 0u, "unsafe seal overlap no encryption");
    EXPECT_TRUE(output_len == 0u, "unsafe seal overlap len reset");
    EXPECT_TRUE(all_bytes_equal(mutable_salt, sizeof(mutable_salt), 0u), "unsafe seal overlap clears salt");
    EXPECT_TRUE(all_bytes_equal(mutable_nonce, sizeof(mutable_nonce), 0u), "unsafe seal overlap clears nonce");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "unsafe seal overlap clears tag");

    memset(record_overlap, 0x44, sizeof(record_overlap));
    memcpy(record_overlap + 4u, plaintext, sizeof(plaintext) - 1u);
    record_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record_overlap + 4u,
            sizeof(plaintext) - 1u,
            record_overlap,
            sizeof(record_overlap),
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "unsafe record seal overlap status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "unsafe record seal overlap error");
    EXPECT_TRUE(result.unsafe_buffer_overlap_rejected == 1u, "unsafe record seal overlap flag");
    EXPECT_TRUE(result.salt_generated == 0u, "unsafe record seal overlap no salt");
    EXPECT_TRUE(result.nonce_generated == 0u, "unsafe record seal overlap no nonce");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "unsafe record seal overlap no hkdf");
    EXPECT_TRUE(result.attached_record_sealed == 0u, "unsafe record seal overlap not sealed");
    EXPECT_TRUE(record_len == 0u, "unsafe record seal overlap len reset");
    EXPECT_TRUE(all_bytes_equal(record_overlap, sizeof(record_overlap), 0u), "unsafe record seal overlap clears record");
    EXPECT_TRUE(result.failed_record_output_cleared == 1u, "unsafe record seal overlap clear flag");

    memset(record, 0, sizeof(record));
    record_len = 0u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "unsafe record open setup status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "unsafe record open setup ok");

    output_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_open_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            record,
            record_len,
            record + 1u,
            record_len - 1u,
            &output_len,
            &result) == LATTICRA_STATUS_OK,
        "unsafe record open overlap status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "unsafe record open overlap error");
    EXPECT_TRUE(result.unsafe_buffer_overlap_rejected == 1u, "unsafe record open overlap flag");
    EXPECT_TRUE(result.hkdf_extract_expand_performed == 0u, "unsafe record open overlap no hkdf");
    EXPECT_TRUE(result.decryption_performed == 0u, "unsafe record open overlap no decrypt");
    EXPECT_TRUE(result.attached_record_authenticated == 0u, "unsafe record open overlap not authenticated");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "unsafe record open overlap plaintext clear flag");
    EXPECT_TRUE(output_len == 0u, "unsafe record open overlap len reset");

    return 0;
}

static int invalid_inputs_fail_closed(void) {
    latticra_seal_hybrid_envelope_context_t context = fixture_context();
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned char tag[LATTICRA_SEAL_HYBRID_TAG_BYTES];
    unsigned char commitment[LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES];
    unsigned char mutable_salt[LATTICRA_SEAL_HYBRID_SALT_BYTES];
    unsigned char mutable_nonce[LATTICRA_SEAL_HYBRID_NONCE_BYTES];
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
        sizeof(plaintext) +
        LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(plaintext)];
    size_t record_len = 99u;
    size_t ciphertext_len = 99u;
    size_t recovered_len = 99u;
    latticra_seal_hybrid_envelope_result_t result;
    char tiny[1];

    memset(mutable_salt, 0, sizeof(mutable_salt));
    memset(mutable_nonce, 0, sizeof(mutable_nonce));
    memset(commitment, 0, sizeof(commitment));
    memset(record, 0, sizeof(record));
    memset(recovered, 0, sizeof(recovered));

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            0,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "null context status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_INPUT, "null context error");

    context = fixture_context();
    context.pqc_shared_secret = 0;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "missing pqc status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_PQC_SHARED_SECRET, "missing pqc error");
    EXPECT_TRUE(ciphertext_len == 0u, "missing pqc output len reset");

    context = fixture_context();
    context.classical_shared_secret_len = 31u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "bad classical size status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_CLASSICAL_SHARED_SECRET_SIZE,
        "bad classical size error");

    context = fixture_context();
    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(tag, 0x4cu, sizeof(tag));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            1u,
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "small output status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL, "small output error");
    EXPECT_TRUE(ciphertext_len == 0u, "small output len reset");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "small output ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "small output tag cleared flag");
    EXPECT_TRUE(ciphertext[0] == 0u, "small output provided ciphertext capacity cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "small output tag cleared");

    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(tag, 0x4cu, sizeof(tag));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            15u,
            &result) == LATTICRA_STATUS_OK,
        "bad tag size status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_TAG_SIZE, "bad tag size error");

    context = fixture_context();
    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(tag, 0x4cu, sizeof(tag));
    memset(commitment, 0x5eu, sizeof(commitment));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt_committed(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            commitment,
            LATTICRA_SEAL_HYBRID_DETACHED_COMMITMENT_BYTES - 1u,
            &result) == LATTICRA_STATUS_OK,
        "committed encrypt invalid commitment size status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_COMMITMENT_SIZE,
        "committed encrypt invalid commitment size error");
    EXPECT_TRUE(ciphertext_len == 0u, "committed encrypt invalid commitment len reset");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "committed encrypt invalid ciphertext clear");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "committed encrypt invalid tag clear");
    EXPECT_TRUE(result.failed_commitment_output_cleared == 1u, "committed encrypt invalid commitment clear");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "committed encrypt invalid ciphertext zeroized");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "committed encrypt invalid tag zeroized");
    EXPECT_TRUE(commitment[0] == 0u, "committed encrypt invalid commitment zeroized");

    context = fixture_context();
    ciphertext_len = 0u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "decrypt cleanup fixture encrypt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OK, "decrypt cleanup fixture encrypt ok");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            ciphertext,
            ciphertext_len,
            tag,
            sizeof(tag),
            recovered,
            1u,
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "decrypt small output status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL,
        "decrypt small output error");
    EXPECT_TRUE(recovered_len == 0u, "decrypt small output len reset");
    EXPECT_TRUE(recovered[0] == 0u, "decrypt small output plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "decrypt small output plaintext clear flag");

    memset(recovered, 0x7f, sizeof(recovered));
    recovered_len = 42u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_decrypt(
            &context,
            ciphertext,
            ciphertext_len,
            0,
            sizeof(tag),
            recovered,
            sizeof(recovered),
            &recovered_len,
            &result) == LATTICRA_STATUS_OK,
        "decrypt missing tag status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_TAG, "decrypt missing tag error");
    EXPECT_TRUE(recovered_len == 0u, "decrypt missing tag len reset");
    EXPECT_TRUE(recovered[0] == 0u, "decrypt missing tag plaintext cleared");
    EXPECT_TRUE(result.failed_plaintext_output_cleared == 1u, "decrypt missing tag plaintext clear flag");

    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(mutable_nonce, 0x6bu, sizeof(mutable_nonce));
    memset(tag, 0x4cu, sizeof(tag));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            0,
            LATTICRA_SEAL_HYBRID_SALT_BYTES,
            mutable_nonce,
            sizeof(mutable_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "seal missing salt status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_SALT, "seal missing salt error");
    EXPECT_TRUE(result.salt_generated == 0u, "seal missing salt not generated");
    EXPECT_TRUE(ciphertext_len == 0u, "seal missing salt output len reset");
    EXPECT_TRUE(result.failed_salt_output_cleared == 0u, "seal missing salt no salt clear flag");
    EXPECT_TRUE(result.failed_nonce_output_cleared == 1u, "seal missing salt nonce cleared flag");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "seal missing salt ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "seal missing salt tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(mutable_nonce, sizeof(mutable_nonce), 0u), "seal missing salt nonce cleared");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "seal missing salt ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "seal missing salt tag cleared");

    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(mutable_salt, 0x5au, sizeof(mutable_salt));
    memset(mutable_nonce, 0x6bu, sizeof(mutable_nonce));
    memset(tag, 0x4cu, sizeof(tag));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            mutable_salt,
            31u,
            mutable_nonce,
            sizeof(mutable_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "seal bad salt size status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_INVALID_SALT_SIZE, "seal bad salt size error");
    EXPECT_TRUE(ciphertext_len == 0u, "seal bad salt size output len reset");
    EXPECT_TRUE(result.failed_salt_output_cleared == 1u, "seal bad salt size salt cleared flag");
    EXPECT_TRUE(result.failed_nonce_output_cleared == 1u, "seal bad salt size nonce cleared flag");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "seal bad salt size ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "seal bad salt size tag cleared flag");
    EXPECT_TRUE(mutable_salt[0] == 0u, "seal bad salt size provided salt capacity cleared");
    EXPECT_TRUE(all_bytes_equal(mutable_nonce, sizeof(mutable_nonce), 0u), "seal bad salt size nonce cleared");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "seal bad salt size ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "seal bad salt size tag cleared");

    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(tag, 0x4cu, sizeof(tag));
    memset(mutable_salt, 0x5a, sizeof(mutable_salt));
    memset(mutable_nonce, 0x6bu, sizeof(mutable_nonce));
    ciphertext_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            0,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            mutable_salt,
            sizeof(mutable_salt),
            mutable_nonce,
            sizeof(mutable_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "seal missing classical status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET,
        "seal missing classical error");
    EXPECT_TRUE(result.salt_generated == 0u, "seal invalid secret no salt generated");
    EXPECT_TRUE(result.nonce_generated == 0u, "seal invalid secret no nonce generated");
    EXPECT_TRUE(ciphertext_len == 0u, "seal invalid secret output len reset");
    EXPECT_TRUE(result.failed_salt_output_cleared == 1u, "seal invalid secret salt cleared flag");
    EXPECT_TRUE(result.failed_nonce_output_cleared == 1u, "seal invalid secret nonce cleared flag");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "seal invalid secret ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "seal invalid secret tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(mutable_salt, sizeof(mutable_salt), 0u), "seal invalid secret salt cleared");
    EXPECT_TRUE(all_bytes_equal(mutable_nonce, sizeof(mutable_nonce), 0u), "seal invalid secret nonce cleared");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "seal invalid secret ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "seal invalid secret tag cleared");

    memset(mutable_salt, 0x5a, sizeof(mutable_salt));
    memset(mutable_nonce, 0x6bu, sizeof(mutable_nonce));
    memset(ciphertext, 0x9du, sizeof(ciphertext));
    memset(tag, 0x4cu, sizeof(tag));
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            0,
            mutable_salt,
            sizeof(mutable_salt),
            mutable_nonce,
            sizeof(mutable_nonce),
            tag,
            sizeof(tag),
            &result) == LATTICRA_STATUS_OK,
        "seal missing length status");
    EXPECT_TRUE(result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_OUTPUT, "seal missing length error");
    EXPECT_TRUE(result.salt_generated == 0u, "seal missing length no salt generated");
    EXPECT_TRUE(result.nonce_generated == 0u, "seal missing length no nonce generated");
    EXPECT_TRUE(result.failed_salt_output_cleared == 1u, "seal missing length salt cleared flag");
    EXPECT_TRUE(result.failed_nonce_output_cleared == 1u, "seal missing length nonce cleared flag");
    EXPECT_TRUE(result.failed_ciphertext_output_cleared == 1u, "seal missing length ciphertext cleared flag");
    EXPECT_TRUE(result.failed_tag_output_cleared == 1u, "seal missing length tag cleared flag");
    EXPECT_TRUE(all_bytes_equal(mutable_salt, sizeof(mutable_salt), 0u), "seal missing length salt cleared");
    EXPECT_TRUE(all_bytes_equal(mutable_nonce, sizeof(mutable_nonce), 0u), "seal missing length nonce cleared");
    EXPECT_TRUE(all_bytes_equal(ciphertext, sizeof(ciphertext), 0u), "seal missing length ciphertext cleared");
    EXPECT_TRUE(all_bytes_equal(tag, sizeof(tag), 0u), "seal missing length tag cleared");

    memset(record, 0x8c, sizeof(record));
    record_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            classical_shared_secret,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            1u,
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "record seal small output status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_OUTPUT_BUFFER_TOO_SMALL,
        "record seal small output error");
    EXPECT_TRUE(record_len == 0u, "record seal small output len reset");
    EXPECT_TRUE(record[0] == 0u, "record seal small output clears provided capacity");
    EXPECT_TRUE(result.failed_record_output_cleared == 1u, "record seal small output clear flag");

    memset(record, 0x8c, sizeof(record));
    record_len = 99u;
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_seal_record(
            0,
            sizeof(classical_shared_secret),
            pqc_shared_secret,
            sizeof(pqc_shared_secret),
            aad,
            sizeof(aad) - 1u,
            plaintext,
            sizeof(plaintext) - 1u,
            record,
            sizeof(record),
            &record_len,
            &result) == LATTICRA_STATUS_OK,
        "record seal invalid secret status");
    EXPECT_TRUE(
        result.error == LATTICRA_SEAL_HYBRID_ENVELOPE_MISSING_CLASSICAL_SHARED_SECRET,
        "record seal invalid secret error");
    EXPECT_TRUE(record_len == 0u, "record seal invalid len reset");
    EXPECT_TRUE(result.attached_record_sealed == 0u, "record seal invalid not sealed");
    EXPECT_TRUE(all_bytes_equal(record, sizeof(record), 0u), "record seal invalid clears record");
    EXPECT_TRUE(result.failed_record_output_cleared == 1u, "record seal invalid clear flag");

    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_encrypt(
            &context,
            plaintext,
            sizeof(plaintext) - 1u,
            ciphertext,
            sizeof(ciphertext),
            &ciphertext_len,
            tag,
            sizeof(tag),
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null result");
    EXPECT_TRUE(latticra_seal_hybrid_envelope_result_is_authority_neutral(0) == 0, "null authority helper");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report");
    EXPECT_TRUE(tiny[0] == '\0', "tiny report clear");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(
        latticra_seal_hybrid_envelope_report(&result, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (random_bytes_can_fill_nonce_material() != 0) {
        return 1;
    }
    if (known_answer_vector_matches() != 0) {
        return 1;
    }
    if (known_answer_committed_detached_vector_opens() != 0) {
        return 1;
    }
    if (detached_aad_frame_rejects_legacy_raw_aad_tag() != 0) {
        return 1;
    }
    if (detached_suite_kdf_rejects_legacy_unsuite_bound_vector() != 0) {
        return 1;
    }
    if (hybrid_secret_role_labels_reject_legacy_unlabeled_detached_vector() != 0) {
        return 1;
    }
    if (hybrid_secret_algorithm_labels_reject_legacy_unlabeled_detached_vector() != 0) {
        return 1;
    }
    if (known_answer_record_vector_opens() != 0) {
        return 1;
    }
    if (hybrid_secret_role_labels_reject_legacy_unlabeled_record_vector() != 0) {
        return 1;
    }
    if (hybrid_secret_algorithm_labels_reject_legacy_unlabeled_record_vector() != 0) {
        return 1;
    }
    if (encrypt_decrypt_round_trip() != 0) {
        return 1;
    }
    if (zero_length_plaintext_round_trip() != 0) {
        return 1;
    }
    if (seal_open_generates_salt_and_nonce() != 0) {
        return 1;
    }
    if (committed_seal_open_generates_salt_nonce_and_commitment() != 0) {
        return 1;
    }
    if (attached_record_seal_open_round_trip() != 0) {
        return 1;
    }
    if (malformed_attached_records_are_rejected_before_crypto() != 0) {
        return 1;
    }
    if (hybrid_secret_components_are_bound() != 0) {
        return 1;
    }
    if (duplicate_hybrid_secret_components_are_rejected_before_kdf() != 0) {
        return 1;
    }
    if (aad_tampering_fails_closed() != 0) {
        return 1;
    }
    if (detached_ciphertext_salt_nonce_tampering_fails_closed() != 0) {
        return 1;
    }
    if (committed_detached_tampering_fails_before_decrypt() != 0) {
        return 1;
    }
    if (record_ciphertext_and_nonce_tampering_fails_closed() != 0) {
        return 1;
    }
    if (authentication_failure_fails_closed() != 0) {
        return 1;
    }
    if (weak_shared_secrets_are_rejected() != 0) {
        return 1;
    }
    if (weak_salt_and_nonce_are_rejected() != 0) {
        return 1;
    }
    if (unsafe_buffer_overlap_is_rejected() != 0) {
        return 1;
    }
    if (invalid_inputs_fail_closed() != 0) {
        return 1;
    }
    printf("seal hybrid envelope invariants: ok\n");
    return 0;
}
