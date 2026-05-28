#include "latticra/seal_key_material.h"

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

static latticra_seal_key_handling_t fixture_key_handling(const char *mode) {
    latticra_seal_signing_operation_t operation = fixture_operation(mode);
    latticra_seal_key_handling_t key_handling;

    (void)latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling);
    return key_handling;
}

static int expect_denial(
    latticra_seal_key_handling_t *key_handling,
    const char *requested_key_material,
    latticra_seal_key_material_error_t expected_error,
    const char *expected_state,
    const char *expected_status,
    const char *message) {
    latticra_seal_key_material_t key_material;

    EXPECT_TRUE(
        latticra_seal_key_material_from_key_handling(key_handling, requested_key_material, &key_material) ==
            LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(key_material.error == expected_error, "expected denial error");
    EXPECT_TRUE(strcmp(key_material.key_material_state, expected_state) == 0, "expected denial state");
    EXPECT_TRUE(strcmp(key_material.status, expected_status) == 0, "expected denial status");
    EXPECT_TRUE(key_material.key_material_ready == 0u, "denial ready");
    return 0;
}

static int key_material_allows_report_only_metadata(void) {
    latticra_seal_key_handling_t key_handling = fixture_key_handling("report-only");
    latticra_seal_key_material_t key_material;
    char rendered[LATTICRA_SEAL_KEY_MATERIAL_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_key_material_from_key_handling(&key_handling, "metadata-only", &key_material) ==
            LATTICRA_STATUS_OK,
        "key material status");
    EXPECT_TRUE(key_material.error == LATTICRA_SEAL_KEY_MATERIAL_OK, "key material ok");
    EXPECT_TRUE(
        strcmp(key_material.key_material_profile, "latticra-seal-key-material/0.1") == 0,
        "key material profile");
    EXPECT_TRUE(strcmp(key_material.key_handling_profile, "latticra-seal-key-handling/0.1") == 0, "key handling profile");
    EXPECT_TRUE(strcmp(key_material.signing_operation_profile, key_handling.signing_operation_profile) == 0, "operation profile");
    EXPECT_TRUE(strcmp(key_material.signer_invocation_profile, key_handling.signer_invocation_profile) == 0, "invocation profile");
    EXPECT_TRUE(strcmp(key_material.signer_handoff_profile, key_handling.signer_handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(key_material.signing_authorization_profile, key_handling.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(key_material.signature_request_profile, key_handling.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(key_material.envelope_profile, key_handling.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(key_material.report_profile, key_handling.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(key_material.handoff_profile, key_handling.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(key_material.decision_profile, key_handling.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(key_material.gate_profile, key_handling.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(key_material.receipt_profile, key_handling.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(key_material.verify_profile, key_handling.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(key_material.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(key_material.message_digest_hex, key_handling.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(key_material.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(key_material.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(key_material.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(key_material.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(key_material.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(key_material.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(key_material.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(key_material.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(key_material.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(key_material.requested_signer_invocation, "metadata-only") == 0, "requested signer invocation");
    EXPECT_TRUE(strcmp(key_material.requested_signing_operation, "metadata-only") == 0, "requested operation");
    EXPECT_TRUE(strcmp(key_material.requested_key_handling, "metadata-only") == 0, "requested key handling");
    EXPECT_TRUE(strcmp(key_material.requested_key_material, "metadata-only") == 0, "requested key material");
    EXPECT_TRUE(strcmp(key_material.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(key_material.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(key_material.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(key_material.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(key_material.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(strcmp(key_material.signer_invocation_state, "invocation-metadata-only") == 0, "invocation state");
    EXPECT_TRUE(key_material.signer_invocation_ready == 1u, "invocation ready");
    EXPECT_TRUE(strcmp(key_material.signing_operation_state, "operation-metadata-only") == 0, "operation state");
    EXPECT_TRUE(key_material.signing_operation_ready == 1u, "operation ready");
    EXPECT_TRUE(strcmp(key_material.key_handling_state, "key-handling-metadata-only") == 0, "key handling state");
    EXPECT_TRUE(key_material.key_handling_ready == 1u, "key handling ready");
    EXPECT_TRUE(strcmp(key_material.key_material_state, "key-material-metadata-only") == 0, "key material state");
    EXPECT_TRUE(key_material.key_material_ready == 1u, "key material ready");
    EXPECT_TRUE(key_material.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(key_material.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(key_material.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(key_material.public_key_parsed == 0u, "public key parsed");
    EXPECT_TRUE(key_material.key_material_loaded == 0u, "key material loaded");
    EXPECT_TRUE(key_material.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(key_material.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(key_material.hardware_key_used == 0u, "hardware key used");
    EXPECT_TRUE(key_material.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(key_material.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(key_material.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(key_material.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(key_material.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(key_material.host_read_performed == 0u, "host read");
    EXPECT_TRUE(key_material.host_write_performed == 0u, "host write");
    EXPECT_TRUE(key_material.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(key_material.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(key_material.status, "key-material-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_key_material_is_metadata_only(&key_material) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL KEY MATERIAL") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "key_material_profile=latticra-seal-key-material/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "key_handling_profile=latticra-seal-key-handling/0.1") != 0, "render predecessor");
    EXPECT_TRUE(strstr(rendered, "requested_key_material=metadata-only") != 0, "render requested key material");
    EXPECT_TRUE(strstr(rendered, "key_material_state=key-material-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "key_material_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "public_key_parsed=0") != 0, "render public key parsed");
    EXPECT_TRUE(strstr(rendered, "key_material_loaded=0") != 0, "render key material loaded");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "hardware_key_used=0") != 0, "render hardware key");
    EXPECT_TRUE(strstr(rendered, "trust_store_loaded=0") != 0, "render trust store");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int key_material_allows_evaluate_only_metadata(void) {
    latticra_seal_key_handling_t key_handling = fixture_key_handling("evaluate-only");
    latticra_seal_key_material_t key_material;

    EXPECT_TRUE(
        latticra_seal_key_material_from_key_handling(&key_handling, "metadata-only", &key_material) ==
            LATTICRA_STATUS_OK,
        "evaluate key material status");
    EXPECT_TRUE(key_material.error == LATTICRA_SEAL_KEY_MATERIAL_OK, "evaluate key material ok");
    EXPECT_TRUE(strcmp(key_material.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(key_material.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(key_material.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(key_material.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(key_material.key_material_state, "key-material-metadata-only") == 0, "evaluate state");
    EXPECT_TRUE(key_material.key_material_ready == 1u, "evaluate ready");
    EXPECT_TRUE(key_material.public_key_parsed == 0u, "evaluate public key parsed");
    EXPECT_TRUE(key_material.key_material_loaded == 0u, "evaluate key material");
    EXPECT_TRUE(key_material.private_key_handling == 0u, "evaluate private key");
    EXPECT_TRUE(key_material.hardware_key_used == 0u, "evaluate hardware key");
    EXPECT_TRUE(key_material.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(key_material.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(key_material.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(key_material.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(key_material.network_performed == 0u, "evaluate network");
    return 0;
}

static int key_material_fails_closed(void) {
    latticra_seal_key_handling_t key_handling = fixture_key_handling("report-only");
    latticra_seal_key_material_t key_material;
    char tiny[1];
    char rendered[LATTICRA_SEAL_KEY_MATERIAL_RENDER_MAX];
    char unterminated_key_material[LATTICRA_SEAL_KEY_MATERIAL_LABEL_MAX];

    memset(unterminated_key_material, 'x', sizeof(unterminated_key_material));

    EXPECT_TRUE(
        latticra_seal_key_material_from_key_handling(0, "metadata-only", &key_material) ==
            LATTICRA_STATUS_OK,
        "null key handling status");
    EXPECT_TRUE(key_material.error == LATTICRA_SEAL_KEY_MATERIAL_INVALID_INPUT, "null key handling error");
    EXPECT_TRUE(strcmp(key_material.key_material_state, "denied-key-handling") == 0, "null key handling state");
    key_handling.error = LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING, "denied-key-handling", "invalid-key-handling", "invalid key handling status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    memset(key_handling.key_handling_state, 'z', sizeof(key_handling.key_handling_state));
    if (expect_denial(
            &key_handling,
            "metadata-only",
            LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING,
            "denied-key-handling",
            "invalid-key-handling",
            "unterminated key handling status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.key_handling_ready = 2u;
    if (expect_denial(
            &key_handling,
            "metadata-only",
            LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING,
            "denied-key-handling",
            "invalid-key-handling",
            "invalid key handling flag status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.key_handling_ready = 0u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling ready status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.key_handling_state, sizeof(key_handling.key_handling_state), "denied-key-handling");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling state status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_key_handling, sizeof(key_handling.requested_key_handling), "load-key-material");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "key handling request status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signing_operation_ready = 0u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation ready status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.signing_operation_state, sizeof(key_handling.signing_operation_state), "denied-signing-operation");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation state status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_signing_operation, sizeof(key_handling.requested_signing_operation), "sign-now");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation request status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signer_invocation_ready = 0u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation ready status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.signer_invocation_state, sizeof(key_handling.signer_invocation_state), "denied-signer-invocation");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation state status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_signer_invocation, sizeof(key_handling.requested_signer_invocation), "spawn-signer");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation request status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signer_handoff_ready = 0u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff ready status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.signer_handoff_state, sizeof(key_handling.signer_handoff_state), "denied-signer-handoff");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff state status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_signer_handoff, sizeof(key_handling.requested_signer_handoff), "invoke-signer");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff request status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signing_authorization_ready = 0u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization ready status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.signing_authorization_state, sizeof(key_handling.signing_authorization_state), "denied-signature-request");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization state status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_signing_authorization, sizeof(key_handling.requested_signing_authorization), "real-signing");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization request status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.requested_signature[0] = '\0';
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "missing signature status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    set_string(key_handling.requested_signature, sizeof(key_handling.requested_signature), "ML-DSA-future");
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "unknown signature status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, 0, LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "missing-requested-key-material", "missing key material null") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "missing-requested-key-material", "missing key material empty") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "parse-public-key", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "public key parse request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "load-key-material", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "handle-private-key", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "generate-key", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "use-hardware-key", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "hardware key request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "load-trust-store", LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "revocation-lookup", LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation request") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    if (expect_denial(&key_handling, "real-key-material", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "unknown key material status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    EXPECT_TRUE(latticra_seal_key_material_from_key_handling(
                    &key_handling,
                    unterminated_key_material,
                    &key_material) == LATTICRA_STATUS_OK,
                "unterminated requested key material status");
    EXPECT_TRUE(key_material.error == LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL,
                "unterminated requested key material error");
    EXPECT_TRUE(strcmp(key_material.requested_key_material, "invalid-key-material") == 0,
                "unterminated requested key material sanitized");
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_OK,
                "unterminated requested key material render");
    EXPECT_TRUE(strstr(rendered, "requested_key_material=invalid-key-material") != 0,
                "unterminated requested key material rendered sanitized");
    key_handling = fixture_key_handling("report-only");
    key_handling.public_key_parsed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "public key parsed status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.key_material_loaded = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material loaded status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.private_key_handling = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.key_generation_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.hardware_key_used = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "hardware key status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.trust_store_loaded = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.revocation_lookup_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.network_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "network status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.runtime_authority_granted = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_RUNTIME_AUTHORITY, "denied-runtime-authority", "denied-runtime-authority", "runtime status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signature_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signature performed status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.verification_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "verification status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.signer_invoked = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signer invoked status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.handoff_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "handoff performed status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.effect_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "effect status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.host_read_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host read status") != 0) {
        return 1;
    }
    key_handling = fixture_key_handling("report-only");
    key_handling.host_write_performed = 1u;
    if (expect_denial(&key_handling, "metadata-only", LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host write status") != 0) {
        return 1;
    }
    EXPECT_TRUE(
        latticra_seal_key_material_from_key_handling(&key_handling, "metadata-only", 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_key_material_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(
        latticra_seal_key_material_render(&key_material, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_key_material_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null render");
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");

    key_handling = fixture_key_handling("report-only");
    EXPECT_TRUE(latticra_seal_key_material_from_key_handling(
                    &key_handling,
                    "metadata-only",
                    &key_material) == LATTICRA_STATUS_OK,
                "tamper render source");
    memset(key_material.key_material_profile, 'z', sizeof(key_material.key_material_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated key material render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated key material render cleared");
    EXPECT_TRUE(latticra_seal_key_material_is_metadata_only(&key_material) == 0,
                "unterminated key material helper rejected");

    key_handling = fixture_key_handling("report-only");
    EXPECT_TRUE(latticra_seal_key_material_from_key_handling(
                    &key_handling,
                    "metadata-only",
                    &key_material) == LATTICRA_STATUS_OK,
                "authority key material render source");
    key_material.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority key material render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority key material render cleared");
    EXPECT_TRUE(latticra_seal_key_material_is_metadata_only(&key_material) == 0,
                "authority key material helper rejected");

    key_handling = fixture_key_handling("report-only");
    EXPECT_TRUE(latticra_seal_key_material_from_key_handling(
                    &key_handling,
                    "metadata-only",
                    &key_material) == LATTICRA_STATUS_OK,
                "ready flag key material render source");
    key_material.key_material_ready = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_material_render(&key_material, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "ready flag key material render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "ready flag key material render cleared");
    EXPECT_TRUE(latticra_seal_key_material_is_metadata_only(&key_material) == 0,
                "ready flag key material helper rejected");
    return 0;
}

int main(void) {
    if (key_material_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (key_material_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (key_material_fails_closed() != 0) {
        return 1;
    }
    printf("seal key-material invariants: ok\n");
    return 0;
}
