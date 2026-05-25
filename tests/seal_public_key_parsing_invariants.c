#include "latticra/seal_public_key_parsing.h"

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

static latticra_seal_key_material_t fixture_key_material(const char *mode) {
    latticra_seal_signing_operation_t operation = fixture_operation(mode);
    latticra_seal_key_handling_t key_handling;
    latticra_seal_key_material_t key_material;

    (void)latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling);
    (void)latticra_seal_key_material_from_key_handling(&key_handling, "metadata-only", &key_material);
    return key_material;
}

static int expect_denial(
    latticra_seal_key_material_t *key_material,
    const char *requested_public_key_parsing,
    latticra_seal_public_key_parsing_error_t expected_error,
    const char *expected_state,
    const char *expected_status,
    const char *message) {
    latticra_seal_public_key_parsing_t public_key_parsing;

    EXPECT_TRUE(
        latticra_seal_public_key_parsing_from_key_material(
            key_material,
            requested_public_key_parsing,
            &public_key_parsing) == LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(public_key_parsing.error == expected_error, "expected denial error");
    EXPECT_TRUE(strcmp(public_key_parsing.public_key_parsing_state, expected_state) == 0, "expected denial state");
    EXPECT_TRUE(strcmp(public_key_parsing.status, expected_status) == 0, "expected denial status");
    EXPECT_TRUE(public_key_parsing.public_key_parsing_ready == 0u, "denial ready");
    EXPECT_TRUE(public_key_parsing.public_key_parsed == key_material->public_key_parsed, "denial parsed flag copied");
    return 0;
}

static int public_key_parsing_allows_report_only_metadata(void) {
    latticra_seal_key_material_t key_material = fixture_key_material("report-only");
    latticra_seal_public_key_parsing_t public_key_parsing;
    char rendered[LATTICRA_SEAL_PUBLIC_KEY_PARSING_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_public_key_parsing_from_key_material(&key_material, "metadata-only", &public_key_parsing) ==
            LATTICRA_STATUS_OK,
        "public key parsing status");
    EXPECT_TRUE(public_key_parsing.error == LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK, "public key parsing ok");
    EXPECT_TRUE(
        strcmp(public_key_parsing.public_key_parsing_profile, "latticra-seal-public-key-parsing/0.1") == 0,
        "public key parsing profile");
    EXPECT_TRUE(strcmp(public_key_parsing.key_material_profile, "latticra-seal-key-material/0.1") == 0, "key material profile");
    EXPECT_TRUE(strcmp(public_key_parsing.key_handling_profile, "latticra-seal-key-handling/0.1") == 0, "key handling profile");
    EXPECT_TRUE(strcmp(public_key_parsing.signing_operation_profile, key_material.signing_operation_profile) == 0, "operation profile");
    EXPECT_TRUE(strcmp(public_key_parsing.signer_invocation_profile, key_material.signer_invocation_profile) == 0, "invocation profile");
    EXPECT_TRUE(strcmp(public_key_parsing.signer_handoff_profile, key_material.signer_handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(public_key_parsing.signing_authorization_profile, key_material.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(public_key_parsing.signature_request_profile, key_material.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(public_key_parsing.envelope_profile, key_material.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(public_key_parsing.report_profile, key_material.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(public_key_parsing.handoff_profile, key_material.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(public_key_parsing.decision_profile, key_material.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(public_key_parsing.gate_profile, key_material.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(public_key_parsing.receipt_profile, key_material.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(public_key_parsing.verify_profile, key_material.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(public_key_parsing.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(public_key_parsing.message_digest_hex, key_material.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(public_key_parsing.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_signer_invocation, "metadata-only") == 0, "requested signer invocation");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_signing_operation, "metadata-only") == 0, "requested operation");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_key_handling, "metadata-only") == 0, "requested key handling");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_key_material, "metadata-only") == 0, "requested key material");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_public_key_parsing, "metadata-only") == 0, "requested public key parsing");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(public_key_parsing.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(public_key_parsing.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(public_key_parsing.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(public_key_parsing.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(strcmp(public_key_parsing.signer_invocation_state, "invocation-metadata-only") == 0, "invocation state");
    EXPECT_TRUE(public_key_parsing.signer_invocation_ready == 1u, "invocation ready");
    EXPECT_TRUE(strcmp(public_key_parsing.signing_operation_state, "operation-metadata-only") == 0, "operation state");
    EXPECT_TRUE(public_key_parsing.signing_operation_ready == 1u, "operation ready");
    EXPECT_TRUE(strcmp(public_key_parsing.key_handling_state, "key-handling-metadata-only") == 0, "key handling state");
    EXPECT_TRUE(public_key_parsing.key_handling_ready == 1u, "key handling ready");
    EXPECT_TRUE(strcmp(public_key_parsing.key_material_state, "key-material-metadata-only") == 0, "key material state");
    EXPECT_TRUE(public_key_parsing.key_material_ready == 1u, "key material ready");
    EXPECT_TRUE(
        strcmp(public_key_parsing.public_key_parsing_state, "public-key-parsing-metadata-only") == 0,
        "public key parsing state");
    EXPECT_TRUE(public_key_parsing.public_key_parsing_ready == 1u, "public key parsing ready");
    EXPECT_TRUE(public_key_parsing.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(public_key_parsing.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(public_key_parsing.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(public_key_parsing.public_key_parsed == 0u, "public key parsed");
    EXPECT_TRUE(public_key_parsing.key_material_loaded == 0u, "key material loaded");
    EXPECT_TRUE(public_key_parsing.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(public_key_parsing.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(public_key_parsing.hardware_key_used == 0u, "hardware key used");
    EXPECT_TRUE(public_key_parsing.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(public_key_parsing.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(public_key_parsing.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(public_key_parsing.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(public_key_parsing.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(public_key_parsing.host_read_performed == 0u, "host read");
    EXPECT_TRUE(public_key_parsing.host_write_performed == 0u, "host write");
    EXPECT_TRUE(public_key_parsing.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(public_key_parsing.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(public_key_parsing.status, "public-key-parsing-metadata") == 0, "status");
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_is_metadata_only(&public_key_parsing) == 1,
        "metadata helper");
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_render(&public_key_parsing, rendered, sizeof(rendered)) ==
            LATTICRA_STATUS_OK,
        "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL PUBLIC KEY PARSING") != 0, "render header");
    EXPECT_TRUE(
        strstr(rendered, "public_key_parsing_profile=latticra-seal-public-key-parsing/0.1") != 0,
        "render profile");
    EXPECT_TRUE(strstr(rendered, "key_material_profile=latticra-seal-key-material/0.1") != 0, "render predecessor");
    EXPECT_TRUE(strstr(rendered, "requested_public_key_parsing=metadata-only") != 0, "render requested");
    EXPECT_TRUE(
        strstr(rendered, "public_key_parsing_state=public-key-parsing-metadata-only") != 0,
        "render state");
    EXPECT_TRUE(strstr(rendered, "public_key_parsing_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "public_key_parsed=0") != 0, "render public key parsed");
    EXPECT_TRUE(strstr(rendered, "key_material_loaded=0") != 0, "render key material loaded");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "hardware_key_used=0") != 0, "render hardware key");
    EXPECT_TRUE(strstr(rendered, "trust_store_loaded=0") != 0, "render trust store");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int public_key_parsing_allows_evaluate_only_metadata(void) {
    latticra_seal_key_material_t key_material = fixture_key_material("evaluate-only");
    latticra_seal_public_key_parsing_t public_key_parsing;

    EXPECT_TRUE(
        latticra_seal_public_key_parsing_from_key_material(&key_material, "metadata-only", &public_key_parsing) ==
            LATTICRA_STATUS_OK,
        "evaluate public key parsing status");
    EXPECT_TRUE(public_key_parsing.error == LATTICRA_SEAL_PUBLIC_KEY_PARSING_OK, "evaluate public key parsing ok");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(public_key_parsing.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(public_key_parsing.key_material_state, "key-material-metadata-only") == 0, "evaluate key material state");
    EXPECT_TRUE(public_key_parsing.key_material_ready == 1u, "evaluate key material ready");
    EXPECT_TRUE(
        strcmp(public_key_parsing.public_key_parsing_state, "public-key-parsing-metadata-only") == 0,
        "evaluate state");
    EXPECT_TRUE(public_key_parsing.public_key_parsing_ready == 1u, "evaluate ready");
    EXPECT_TRUE(public_key_parsing.public_key_parsed == 0u, "evaluate public key parsed");
    EXPECT_TRUE(public_key_parsing.key_material_loaded == 0u, "evaluate key material");
    EXPECT_TRUE(public_key_parsing.private_key_handling == 0u, "evaluate private key");
    EXPECT_TRUE(public_key_parsing.hardware_key_used == 0u, "evaluate hardware key");
    EXPECT_TRUE(public_key_parsing.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(public_key_parsing.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(public_key_parsing.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(public_key_parsing.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(public_key_parsing.network_performed == 0u, "evaluate network");
    return 0;
}

static int public_key_parsing_fails_closed(void) {
    latticra_seal_key_material_t key_material = fixture_key_material("report-only");
    latticra_seal_public_key_parsing_t public_key_parsing;
    char tiny[1];

    EXPECT_TRUE(
        latticra_seal_public_key_parsing_from_key_material(0, "metadata-only", &public_key_parsing) ==
            LATTICRA_STATUS_OK,
        "null key material status");
    EXPECT_TRUE(public_key_parsing.error == LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_INPUT, "null key material error");
    EXPECT_TRUE(
        strcmp(public_key_parsing.public_key_parsing_state, "denied-key-material") == 0,
        "null key material state");
    key_material.error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_INVALID_KEY_MATERIAL, "denied-key-material", "invalid-key-material", "invalid key material status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.key_material_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.key_material_state, sizeof(key_material.key_material_state), "denied-key-material");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_key_material, sizeof(key_material.requested_key_material), "load-key-material");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.key_handling_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.key_handling_state, sizeof(key_material.key_handling_state), "denied-key-handling");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_key_handling, sizeof(key_material.requested_key_handling), "load-key-material");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signing_operation_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.signing_operation_state, sizeof(key_material.signing_operation_state), "denied-signing-operation");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_signing_operation, sizeof(key_material.requested_signing_operation), "sign-now");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signer_invocation_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.signer_invocation_state, sizeof(key_material.signer_invocation_state), "denied-signer-invocation");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_signer_invocation, sizeof(key_material.requested_signer_invocation), "spawn-signer");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signer_handoff_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.signer_handoff_state, sizeof(key_material.signer_handoff_state), "denied-signer-handoff");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_signer_handoff, sizeof(key_material.requested_signer_handoff), "invoke-signer");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signing_authorization_ready = 0u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization ready status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.signing_authorization_state, sizeof(key_material.signing_authorization_state), "denied-signature-request");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization state status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_signing_authorization, sizeof(key_material.requested_signing_authorization), "real-signing");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization request status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.requested_signature[0] = '\0';
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "missing signature status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    set_string(key_material.requested_signature, sizeof(key_material.requested_signature), "ML-DSA-future");
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "unknown signature status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, 0, LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING, "denied-public-key-parsing", "missing-requested-public-key-parsing", "missing public key parsing null") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING, "denied-public-key-parsing", "missing-requested-public-key-parsing", "missing public key parsing empty") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "parse-public-key", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING, "denied-public-key-parsing", "denied-public-key-parsing", "public key parse request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "load-key-material", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "handle-private-key", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "generate-key", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "use-hardware-key", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "hardware key request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "load-trust-store", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "revocation-lookup", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation request") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    if (expect_denial(&key_material, "real-public-key", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING, "denied-public-key-parsing", "denied-public-key-parsing", "unknown public key parsing status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.public_key_parsed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PUBLIC_KEY_PARSING, "denied-public-key-parsing", "denied-public-key-parsing", "public key parsed status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.key_material_loaded = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material loaded status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.private_key_handling = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.key_generation_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.hardware_key_used = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "hardware key status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.trust_store_loaded = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.revocation_lookup_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.network_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "network status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.runtime_authority_granted = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_RUNTIME_AUTHORITY, "denied-runtime-authority", "denied-runtime-authority", "runtime status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signature_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signature performed status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.verification_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "verification status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.signer_invoked = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signer invoked status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.handoff_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "handoff performed status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.effect_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "effect status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.host_read_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host read status") != 0) {
        return 1;
    }
    key_material = fixture_key_material("report-only");
    key_material.host_write_performed = 1u;
    if (expect_denial(&key_material, "metadata-only", LATTICRA_SEAL_PUBLIC_KEY_PARSING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host write status") != 0) {
        return 1;
    }
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_from_key_material(&key_material, "metadata-only", 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_public_key_parsing_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_render(&public_key_parsing, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null render");
    EXPECT_TRUE(
        latticra_seal_public_key_parsing_render(&public_key_parsing, 0, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null buffer render");
    return 0;
}

int main(void) {
    if (public_key_parsing_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (public_key_parsing_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (public_key_parsing_fails_closed() != 0) {
        return 1;
    }
    printf("seal public-key parsing invariants: ok\n");
    return 0;
}
