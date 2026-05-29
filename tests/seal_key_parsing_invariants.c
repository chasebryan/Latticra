#include "latticra/seal_key_parsing.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static void set_string(char *destination, size_t destination_len, const char *source) {
    (void)snprintf(destination, destination_len, "%s", source != 0 ? source : "");
}

static void set_private_key_marker(char *destination, size_t destination_len) {
    (void)snprintf(destination, destination_len, "%s%s%s", "-----BEGIN ", "PRIVATE", " KEY-----");
}

static latticra_seal_signing_operation_t fixture_operation(const char *mode) {
    latticra_seal_signing_operation_t operation;
    const char *requested_mode = mode != 0 ? mode : "report-only";

    memset(&operation, 0, sizeof(operation));
    set_string(
        operation.signing_operation_profile,
        sizeof(operation.signing_operation_profile),
        "latticra-seal-signing-operation/0.1");
    set_string(operation.signer_invocation_profile, sizeof(operation.signer_invocation_profile), "latticra-seal-signer-invocation/0.1");
    set_string(operation.signer_handoff_profile, sizeof(operation.signer_handoff_profile), "latticra-seal-signer-handoff/0.1");
    set_string(
        operation.signing_authorization_profile,
        sizeof(operation.signing_authorization_profile),
        "latticra-seal-signing-authorization/0.1");
    set_string(operation.signature_request_profile, sizeof(operation.signature_request_profile), "latticra-seal-signature-request/0.1");
    set_string(operation.envelope_profile, sizeof(operation.envelope_profile), "latticra-seal-report-envelope/0.1");
    set_string(operation.report_profile, sizeof(operation.report_profile), "latticra-seal-runtime-handoff-report/0.1");
    set_string(operation.handoff_profile, sizeof(operation.handoff_profile), "latticra-seal-runtime-handoff-evaluation/0.1");
    set_string(operation.decision_profile, sizeof(operation.decision_profile), "latticra-seal-verified-effect-decision/0.1");
    set_string(operation.gate_profile, sizeof(operation.gate_profile), "latticra-seal-verified-capability-gate/0.1");
    set_string(operation.receipt_profile, sizeof(operation.receipt_profile), "latticra-seal-verified-receipt/0.1");
    set_string(operation.verify_profile, sizeof(operation.verify_profile), "latticra-seal-ed25519-verify/0.1");
    set_string(operation.message_digest_algorithm, sizeof(operation.message_digest_algorithm), "SHA-256");
    set_string(
        operation.message_digest_hex,
        sizeof(operation.message_digest_hex),
        "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    set_string(operation.public_key_identity_label, sizeof(operation.public_key_identity_label), "rfc8032-test-key");
    set_string(operation.crypto_graduation_gate_state, sizeof(operation.crypto_graduation_gate_state), "not-required");
    set_string(operation.requested_capability, sizeof(operation.requested_capability), "verified-receipt-report");
    set_string(operation.requested_effect, sizeof(operation.requested_effect), requested_mode);
    set_string(operation.requested_handoff, sizeof(operation.requested_handoff), requested_mode);
    set_string(operation.requested_report, sizeof(operation.requested_report), requested_mode);
    set_string(operation.requested_envelope, sizeof(operation.requested_envelope), requested_mode);
    set_string(operation.requested_signature, sizeof(operation.requested_signature), "Ed25519-development");
    set_string(operation.requested_signing_authorization, sizeof(operation.requested_signing_authorization), "metadata-only");
    set_string(operation.requested_signer_handoff, sizeof(operation.requested_signer_handoff), "metadata-only");
    set_string(operation.requested_signer_invocation, sizeof(operation.requested_signer_invocation), "metadata-only");
    set_string(operation.requested_signing_operation, sizeof(operation.requested_signing_operation), "metadata-only");
    set_string(operation.requested_scope, sizeof(operation.requested_scope), "local-fixture-scope");
    set_string(operation.signing_authorization_state, sizeof(operation.signing_authorization_state), "authorized-metadata-only");
    operation.signing_authorization_ready = 1u;
    set_string(operation.signer_handoff_state, sizeof(operation.signer_handoff_state), "handoff-metadata-only");
    operation.signer_handoff_ready = 1u;
    set_string(operation.signer_invocation_state, sizeof(operation.signer_invocation_state), "invocation-metadata-only");
    operation.signer_invocation_ready = 1u;
    set_string(operation.signing_operation_state, sizeof(operation.signing_operation_state), "operation-metadata-only");
    operation.signing_operation_ready = 1u;
    set_string(operation.mode, sizeof(operation.mode), "metadata-only");
    operation.error = LATTICRA_SEAL_SIGNING_OPERATION_OK;
    set_string(operation.status, sizeof(operation.status), "signing-operation-metadata");
    return operation;
}

static latticra_seal_public_key_parsing_t fixture_public_key_parsing(void) {
    latticra_seal_signing_operation_t operation = fixture_operation("report-only");
    latticra_seal_key_handling_t key_handling;
    latticra_seal_key_material_t key_material;
    latticra_seal_public_key_parsing_t public_key_parsing;

    (void)latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling);
    (void)latticra_seal_key_material_from_key_handling(&key_handling, "metadata-only", &key_material);
    (void)latticra_seal_public_key_parsing_from_key_material(&key_material, "metadata-only", &public_key_parsing);
    return public_key_parsing;
}

static int expect_zero_authority_effects(const latticra_seal_key_parsing_result_t *key_parsing) {
    EXPECT_TRUE(key_parsing->key_material_loaded == 0u, "key material loaded");
    EXPECT_TRUE(key_parsing->private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(key_parsing->key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(key_parsing->hardware_key_used == 0u, "hardware key used");
    EXPECT_TRUE(key_parsing->trust_store_loaded == 0u, "trust store loaded");
    EXPECT_TRUE(key_parsing->revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(key_parsing->signature_performed == 0u, "signature performed");
    EXPECT_TRUE(key_parsing->verification_performed == 0u, "verification performed");
    EXPECT_TRUE(key_parsing->signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(key_parsing->handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(key_parsing->effect_performed == 0u, "effect performed");
    EXPECT_TRUE(key_parsing->runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(key_parsing->host_read_performed == 0u, "host read");
    EXPECT_TRUE(key_parsing->host_write_performed == 0u, "host write");
    EXPECT_TRUE(key_parsing->network_performed == 0u, "network");
    return 0;
}

static int key_parsing_accepts_raw_ed25519_public_key(void) {
    latticra_seal_public_key_parsing_t public_key_parsing = fixture_public_key_parsing();
    latticra_seal_key_parsing_result_t key_parsing;
    unsigned char public_key[32];
    char rendered[LATTICRA_SEAL_KEY_PARSING_REPORT_MAX];
    size_t i;

    for (i = 0u; i < sizeof(public_key); ++i) {
        public_key[i] = (unsigned char)i;
    }

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            &key_parsing) == LATTICRA_STATUS_OK,
        "raw key parsing status");
    EXPECT_TRUE(key_parsing.error == LATTICRA_SEAL_KEY_PARSING_OK, "raw key parsing ok");
    EXPECT_TRUE(strcmp(latticra_seal_key_parsing_error_label(key_parsing.error), "ok") == 0, "raw error label");
    EXPECT_TRUE(
        strcmp(
            latticra_seal_key_parsing_format_label(LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32),
            "ed25519-raw-public-key-32") == 0,
        "raw format label");
    EXPECT_TRUE(strcmp(key_parsing.key_parsing_profile, "latticra-seal-key-parsing/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(key_parsing.public_key_parsing_profile, "latticra-seal-public-key-parsing/0.1") == 0, "predecessor profile");
    EXPECT_TRUE(strcmp(key_parsing.key_material_profile, "latticra-seal-key-material/0.1") == 0, "key material profile");
    EXPECT_TRUE(strcmp(key_parsing.requested_key_parsing, "public-key-bytes-only") == 0, "requested key parsing");
    EXPECT_TRUE(strcmp(key_parsing.requested_public_key_parsing, "metadata-only") == 0, "requested predecessor");
    EXPECT_TRUE(strcmp(key_parsing.key_parsing_input_format, "ed25519-raw-public-key-32") == 0, "input format");
    EXPECT_TRUE(key_parsing.key_parsing_input_length == 32u, "input length");
    EXPECT_TRUE(strcmp(key_parsing.key_parsing_algorithm, "Ed25519-development") == 0, "algorithm");
    EXPECT_TRUE(strcmp(key_parsing.key_parsing_state, "public-key-parsed-metadata-only") == 0, "state");
    EXPECT_TRUE(key_parsing.key_parsing_ready == 1u, "ready");
    EXPECT_TRUE(strcmp(key_parsing.public_key_parsing_state, "public-key-parsing-metadata-only") == 0, "predecessor state");
    EXPECT_TRUE(key_parsing.public_key_parsing_ready == 1u, "predecessor ready");
    EXPECT_TRUE(key_parsing.public_key_parsed == 1u, "public key parsed");
    EXPECT_TRUE(expect_zero_authority_effects(&key_parsing) == 0, "raw no authority effects");
    EXPECT_TRUE(strcmp(key_parsing.blocked_reason, "none") == 0, "blocked reason");
    EXPECT_TRUE(strcmp(key_parsing.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(key_parsing.status, "key-parsing-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 1, "no effect helper");
    EXPECT_TRUE(latticra_seal_key_parsing_render(&key_parsing, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL KEY PARSING") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "key_parsing_profile=latticra-seal-key-parsing/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "key_parsing_input_format=ed25519-raw-public-key-32") != 0, "render format");
    EXPECT_TRUE(strstr(rendered, "key_parsing_input_length=32") != 0, "render length");
    EXPECT_TRUE(strstr(rendered, "public_key_parsed=1") != 0, "render parsed");
    EXPECT_TRUE(strstr(rendered, "key_material_loaded=0") != 0, "render key material");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    EXPECT_TRUE(strstr(rendered, "blocked_reason=none") != 0, "render blocked reason");
    EXPECT_TRUE(strstr(rendered, "error=ok") != 0, "render error");
    return 0;
}

static int key_parsing_accepts_hex_ed25519_public_key(void) {
    latticra_seal_public_key_parsing_t public_key_parsing = fixture_public_key_parsing();
    latticra_seal_key_parsing_result_t key_parsing;
    const unsigned char public_key_hex[] = "00112233445566778899aabbccddeeff00112233445566778899AABBCCDDEEFF";

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key_hex,
            64u,
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64,
            &key_parsing) == LATTICRA_STATUS_OK,
        "hex key parsing status");
    EXPECT_TRUE(key_parsing.error == LATTICRA_SEAL_KEY_PARSING_OK, "hex key parsing ok");
    EXPECT_TRUE(strcmp(key_parsing.key_parsing_input_format, "ed25519-hex-public-key-64") == 0, "hex input format");
    EXPECT_TRUE(key_parsing.key_parsing_input_length == 64u, "hex input length");
    EXPECT_TRUE(key_parsing.key_parsing_ready == 1u, "hex ready");
    EXPECT_TRUE(key_parsing.public_key_parsed == 1u, "hex parsed");
    EXPECT_TRUE(expect_zero_authority_effects(&key_parsing) == 0, "hex no authority effects");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 1, "hex no effect helper");
    return 0;
}

static int expect_failure(
    const latticra_seal_public_key_parsing_t *public_key_parsing,
    const unsigned char *public_key_bytes,
    size_t public_key_len,
    latticra_seal_key_parsing_format_t format,
    latticra_seal_key_parsing_error_t expected_error,
    const char *expected_status,
    const char *expected_reason,
    const char *message) {
    latticra_seal_key_parsing_result_t key_parsing;

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            public_key_parsing,
            public_key_bytes,
            public_key_len,
            format,
            &key_parsing) == LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(key_parsing.error == expected_error, "failure error");
    EXPECT_TRUE(strcmp(key_parsing.status, expected_status) == 0, "failure status");
    EXPECT_TRUE(strcmp(key_parsing.blocked_reason, expected_reason) == 0, "failure reason");
    EXPECT_TRUE(key_parsing.key_parsing_ready == 0u, "failure ready");
    EXPECT_TRUE(key_parsing.public_key_parsed == 0u, "failure parsed");
    EXPECT_TRUE(expect_zero_authority_effects(&key_parsing) == 0, "failure no authority effects");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 0, "failure no effect helper");
    return 0;
}

static int key_parsing_fails_closed(void) {
    latticra_seal_public_key_parsing_t public_key_parsing = fixture_public_key_parsing();
    latticra_seal_key_parsing_result_t key_parsing;
    unsigned char public_key[32];
    unsigned char public_key_long[33];
    unsigned char oversized[LATTICRA_SEAL_KEY_PARSING_INPUT_MAX + 1u];
    unsigned char invalid_hex[64];
    unsigned char private_marker[32];
    char tiny[1];
    char rendered[LATTICRA_SEAL_KEY_PARSING_REPORT_MAX];

    memset(public_key, 0x5a, sizeof(public_key));
    memset(public_key_long, 0x5a, sizeof(public_key_long));
    memset(oversized, 0x5a, sizeof(oversized));
    memset(invalid_hex, (int)'f', sizeof(invalid_hex));
    invalid_hex[17] = (unsigned char)'x';
    set_private_key_marker((char *)private_marker, sizeof(private_marker));

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(
        expect_failure(
            0,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "missing-predecessor",
        "null predecessor") == 0,
        "null predecessor failure");

    public_key_parsing = fixture_public_key_parsing();
    memset(public_key_parsing.public_key_parsing_state, 'z', sizeof(public_key_parsing.public_key_parsing_state));
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "invalid-predecessor-metadata",
            "unterminated predecessor public key parsing status") == 0,
        "unterminated predecessor failure");

    public_key_parsing = fixture_public_key_parsing();
    public_key_parsing.public_key_parsing_ready = 2u;
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR,
            "invalid-predecessor",
            "invalid-predecessor-metadata",
            "invalid predecessor public key parsing flag status") == 0,
        "invalid predecessor flag failure");

    public_key_parsing = fixture_public_key_parsing();
    public_key_parsing.public_key_parsing_ready = 0u;
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY,
            "predecessor-not-ready",
            "predecessor-not-ready",
            "predecessor not ready") == 0,
        "predecessor not ready failure");

    public_key_parsing = fixture_public_key_parsing();
    public_key_parsing.public_key_parsed = 1u;
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED,
            "effect-denied",
            "predecessor-public-key-already-parsed",
            "predecessor parsed") == 0,
        "predecessor parsed failure");

    public_key_parsing = fixture_public_key_parsing();
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            0,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT,
            "invalid-input",
            "missing-public-key-bytes",
            "missing bytes") == 0,
        "missing bytes failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            0u,
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
            "invalid-public-key-bytes",
            "empty-public-key-bytes",
            "empty bytes") == 0,
        "empty bytes failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key_long,
            sizeof(public_key_long),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
            "invalid-public-key-bytes",
            "invalid-ed25519-raw-public-key-length",
            "raw length") == 0,
        "raw length failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            oversized,
            sizeof(oversized),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT,
            "oversized-input",
            "oversized-public-key-bytes",
            "oversized input") == 0,
        "oversized failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            invalid_hex,
            sizeof(invalid_hex),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64,
            LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES,
            "invalid-public-key-bytes",
            "invalid-ed25519-hex-public-key-byte",
            "invalid hex") == 0,
        "invalid hex failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_PEM_PUBLIC_KEY_UNSUPPORTED,
            LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT,
            "unsupported-format",
            "unsupported-key-format",
            "unsupported pem") == 0,
        "unsupported pem failure");
    EXPECT_TRUE(
        expect_failure(
            &public_key_parsing,
            private_marker,
            strlen((const char *)private_marker),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED,
            LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED,
            "private-key-denied",
            "private-key-marker-denied",
            "private key marker") == 0,
        "private key marker failure");

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            &key_parsing) == LATTICRA_STATUS_OK,
        "render fixture status");
    tiny[0] = 'x';
    EXPECT_TRUE(
        latticra_seal_key_parsing_render(&key_parsing, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clears buffer");
    EXPECT_TRUE(latticra_seal_key_parsing_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null render result");
    EXPECT_TRUE(latticra_seal_key_parsing_render(&key_parsing, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null render buffer");

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            &key_parsing) == LATTICRA_STATUS_OK,
        "tamper render fixture status");
    memset(key_parsing.key_parsing_profile, 'z', sizeof(key_parsing.key_parsing_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_parsing_render(&key_parsing, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated key parsing render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated key parsing render cleared");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 0,
                "unterminated key parsing helper rejected");

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            &key_parsing) == LATTICRA_STATUS_OK,
        "authority key parsing render source");
    key_parsing.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_parsing_render(&key_parsing, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority key parsing render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority key parsing render cleared");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 0,
                "authority key parsing helper rejected");

    EXPECT_TRUE(
        latticra_seal_key_parsing_from_public_key_bytes(
            &public_key_parsing,
            public_key,
            sizeof(public_key),
            LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32,
            &key_parsing) == LATTICRA_STATUS_OK,
        "ready flag key parsing render source");
    key_parsing.key_parsing_ready = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_parsing_render(&key_parsing, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "ready flag key parsing render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "ready flag key parsing render cleared");
    EXPECT_TRUE(latticra_seal_key_parsing_is_no_effect(&key_parsing) == 0,
                "ready flag key parsing helper rejected");
    return 0;
}

int main(void) {
    if (key_parsing_accepts_raw_ed25519_public_key() != 0) {
        return 1;
    }
    if (key_parsing_accepts_hex_ed25519_public_key() != 0) {
        return 1;
    }
    if (key_parsing_fails_closed() != 0) {
        return 1;
    }

    printf("seal key parsing invariants: ok\n");
    return 0;
}
