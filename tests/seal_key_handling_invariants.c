#include "latticra/seal_key_handling.h"

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
    operation.signature_performed = 0u;
    operation.verification_performed = 0u;
    operation.signer_invoked = 0u;
    operation.private_key_handling = 0u;
    operation.key_generation_performed = 0u;
    operation.trust_store_loaded = 0u;
    operation.revocation_lookup_performed = 0u;
    operation.handoff_performed = 0u;
    operation.effect_performed = 0u;
    operation.runtime_authority_granted = 0u;
    operation.host_read_performed = 0u;
    operation.host_write_performed = 0u;
    operation.network_performed = 0u;
    set_string(operation.mode, sizeof(operation.mode), "metadata-only");
    operation.error = LATTICRA_SEAL_SIGNING_OPERATION_OK;
    set_string(operation.status, sizeof(operation.status), "signing-operation-metadata");
    return operation;
}

static latticra_seal_signing_operation_t fixture_crypto_bound_operation(const char *mode) {
    latticra_seal_signing_operation_t operation = fixture_operation(mode);
    set_string(operation.crypto_graduation_profile, sizeof(operation.crypto_graduation_profile), "latticra-seal-crypto-graduation-gate/0.1");
    set_string(
        operation.assurance_baseline_profile,
        sizeof(operation.assurance_baseline_profile),
        "latticra-cryptographic-assurance-key-management/0.1");
    set_string(operation.crypto_graduation_gate_state, sizeof(operation.crypto_graduation_gate_state), "graduated-authority-neutral");
    operation.crypto_graduation_gate_present = 1u;
    operation.crypto_graduation_gate_passed = 1u;
    operation.standard_expectations_met = 1u;
    operation.local_verify_graduated = 1u;
    operation.receipt_promotion_graduated = 1u;
    operation.authority_promotion_allowed = 0u;
    return operation;
}

static int expect_denial(
    latticra_seal_signing_operation_t *operation,
    const char *requested_key_handling,
    latticra_seal_key_handling_error_t expected_error,
    const char *expected_state,
    const char *expected_status,
    const char *message) {
    latticra_seal_key_handling_t key_handling;

    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(operation, requested_key_handling, &key_handling) ==
            LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(key_handling.error == expected_error, "expected denial error");
    EXPECT_TRUE(strcmp(key_handling.key_handling_state, expected_state) == 0, "expected denial state");
    EXPECT_TRUE(strcmp(key_handling.status, expected_status) == 0, "expected denial status");
    EXPECT_TRUE(key_handling.key_handling_ready == 0u, "denial ready");
    EXPECT_TRUE(key_handling.public_key_parsed == 0u, "denial public key parsed");
    EXPECT_TRUE(key_handling.key_material_loaded == 0u, "denial key material loaded");
    EXPECT_TRUE(key_handling.hardware_key_used == 0u, "denial hardware key used");
    return 0;
}

static int key_handling_allows_report_only_metadata(void) {
    latticra_seal_signing_operation_t operation = fixture_operation("report-only");
    latticra_seal_key_handling_t key_handling;
    char rendered[LATTICRA_SEAL_KEY_HANDLING_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling) ==
            LATTICRA_STATUS_OK,
        "key handling status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_OK, "key handling ok");
    EXPECT_TRUE(
        strcmp(key_handling.key_handling_profile, "latticra-seal-key-handling/0.1") == 0,
        "key handling profile");
    EXPECT_TRUE(strcmp(key_handling.signing_operation_profile, operation.signing_operation_profile) == 0, "operation profile");
    EXPECT_TRUE(strcmp(key_handling.signer_invocation_profile, operation.signer_invocation_profile) == 0, "invocation profile");
    EXPECT_TRUE(strcmp(key_handling.signer_handoff_profile, operation.signer_handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(key_handling.signing_authorization_profile, operation.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(key_handling.signature_request_profile, operation.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(key_handling.envelope_profile, operation.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(key_handling.report_profile, operation.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(key_handling.handoff_profile, operation.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(key_handling.decision_profile, operation.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(key_handling.gate_profile, operation.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(key_handling.receipt_profile, operation.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(key_handling.verify_profile, operation.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(key_handling.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(key_handling.message_digest_hex, operation.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(key_handling.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(key_handling.crypto_graduation_gate_state, "not-required") == 0, "crypto gate legacy");
    EXPECT_TRUE(key_handling.crypto_graduation_gate_present == 0u, "crypto present legacy");
    EXPECT_TRUE(key_handling.standard_expectations_met == 0u, "standard legacy");
    EXPECT_TRUE(strcmp(key_handling.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(key_handling.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(key_handling.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(key_handling.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(key_handling.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(key_handling.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(key_handling.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(key_handling.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(key_handling.requested_signer_invocation, "metadata-only") == 0, "requested signer invocation");
    EXPECT_TRUE(strcmp(key_handling.requested_signing_operation, "metadata-only") == 0, "requested operation");
    EXPECT_TRUE(strcmp(key_handling.requested_key_handling, "metadata-only") == 0, "requested key handling");
    EXPECT_TRUE(strcmp(key_handling.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(key_handling.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(key_handling.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(key_handling.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(key_handling.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(strcmp(key_handling.signer_invocation_state, "invocation-metadata-only") == 0, "invocation state");
    EXPECT_TRUE(key_handling.signer_invocation_ready == 1u, "invocation ready");
    EXPECT_TRUE(strcmp(key_handling.signing_operation_state, "operation-metadata-only") == 0, "operation state");
    EXPECT_TRUE(key_handling.signing_operation_ready == 1u, "operation ready");
    EXPECT_TRUE(strcmp(key_handling.key_handling_state, "key-handling-metadata-only") == 0, "key handling state");
    EXPECT_TRUE(key_handling.key_handling_ready == 1u, "key handling ready");
    EXPECT_TRUE(key_handling.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(key_handling.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(key_handling.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(key_handling.public_key_parsed == 0u, "public key parsed");
    EXPECT_TRUE(key_handling.key_material_loaded == 0u, "key material loaded");
    EXPECT_TRUE(key_handling.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(key_handling.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(key_handling.hardware_key_used == 0u, "hardware key used");
    EXPECT_TRUE(key_handling.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(key_handling.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(key_handling.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(key_handling.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(key_handling.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(key_handling.host_read_performed == 0u, "host read");
    EXPECT_TRUE(key_handling.host_write_performed == 0u, "host write");
    EXPECT_TRUE(key_handling.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(key_handling.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(key_handling.status, "key-handling-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(&key_handling) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL KEY HANDLING") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "key_handling_profile=latticra-seal-key-handling/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "requested_signing_operation=metadata-only") != 0, "render requested operation");
    EXPECT_TRUE(strstr(rendered, "requested_key_handling=metadata-only") != 0, "render requested key handling");
    EXPECT_TRUE(strstr(rendered, "key_handling_state=key-handling-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "key_handling_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "public_key_parsed=0") != 0, "render public key parsed");
    EXPECT_TRUE(strstr(rendered, "key_material_loaded=0") != 0, "render key material loaded");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "hardware_key_used=0") != 0, "render hardware key");
    EXPECT_TRUE(strstr(rendered, "trust_store_loaded=0") != 0, "render trust store");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int key_handling_carries_crypto_graduation_evidence(void) {
    latticra_seal_signing_operation_t operation = fixture_crypto_bound_operation("report-only");
    latticra_seal_key_handling_t key_handling;
    char rendered[LATTICRA_SEAL_KEY_HANDLING_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling) ==
            LATTICRA_STATUS_OK,
        "crypto key handling status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_OK, "crypto key handling ok");
    EXPECT_TRUE(strcmp(key_handling.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "crypto profile");
    EXPECT_TRUE(strcmp(key_handling.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "assurance profile");
    EXPECT_TRUE(strcmp(key_handling.crypto_graduation_gate_state, "graduated-authority-neutral") == 0, "crypto state");
    EXPECT_TRUE(key_handling.crypto_graduation_gate_present == 1u, "crypto present");
    EXPECT_TRUE(key_handling.crypto_graduation_gate_passed == 1u, "crypto passed");
    EXPECT_TRUE(key_handling.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(key_handling.local_verify_graduated == 1u, "local verify");
    EXPECT_TRUE(key_handling.receipt_promotion_graduated == 1u, "receipt promotion");
    EXPECT_TRUE(key_handling.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(key_handling.key_handling_ready == 1u, "crypto key handling ready");
    EXPECT_TRUE(strcmp(key_handling.key_handling_state, "key-handling-metadata-only") == 0, "crypto key handling state");
    EXPECT_TRUE(key_handling.public_key_parsed == 0u, "crypto public key parsed");
    EXPECT_TRUE(key_handling.key_material_loaded == 0u, "crypto key material");
    EXPECT_TRUE(key_handling.private_key_handling == 0u, "crypto private key");
    EXPECT_TRUE(key_handling.key_generation_performed == 0u, "crypto key generation");
    EXPECT_TRUE(key_handling.hardware_key_used == 0u, "crypto hardware key");
    EXPECT_TRUE(key_handling.trust_store_loaded == 0u, "crypto trust store");
    EXPECT_TRUE(key_handling.runtime_authority_granted == 0u, "crypto runtime");
    EXPECT_TRUE(key_handling.host_read_performed == 0u, "crypto host read");
    EXPECT_TRUE(key_handling.host_write_performed == 0u, "crypto host write");
    EXPECT_TRUE(key_handling.network_performed == 0u, "crypto network");
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "crypto render");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_gate_present=1") != 0, "render crypto present");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "render standard");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "render authority promotion");
    return 0;
}

static int key_handling_allows_evaluate_only_metadata(void) {
    latticra_seal_signing_operation_t operation = fixture_operation("evaluate-only");
    latticra_seal_key_handling_t key_handling;

    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(&operation, "metadata-only", &key_handling) ==
            LATTICRA_STATUS_OK,
        "evaluate key handling status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_OK, "evaluate key handling ok");
    EXPECT_TRUE(strcmp(key_handling.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(key_handling.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(key_handling.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(key_handling.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(key_handling.key_handling_state, "key-handling-metadata-only") == 0, "evaluate state");
    EXPECT_TRUE(key_handling.key_handling_ready == 1u, "evaluate ready");
    EXPECT_TRUE(key_handling.public_key_parsed == 0u, "evaluate public key parsed");
    EXPECT_TRUE(key_handling.key_material_loaded == 0u, "evaluate key material");
    EXPECT_TRUE(key_handling.private_key_handling == 0u, "evaluate private key");
    EXPECT_TRUE(key_handling.hardware_key_used == 0u, "evaluate hardware key");
    EXPECT_TRUE(key_handling.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(key_handling.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(key_handling.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(key_handling.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(key_handling.network_performed == 0u, "evaluate network");
    return 0;
}

static int key_handling_fails_closed(void) {
    latticra_seal_signing_operation_t operation = fixture_operation("report-only");
    latticra_seal_key_handling_t key_handling;
    char tiny[1];
    char rendered[LATTICRA_SEAL_KEY_HANDLING_RENDER_MAX];
    char unterminated_key_handling[LATTICRA_SEAL_KEY_HANDLING_LABEL_MAX];

    memset(unterminated_key_handling, 'x', sizeof(unterminated_key_handling));

    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(0, "metadata-only", &key_handling) ==
            LATTICRA_STATUS_OK,
        "null operation status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_INVALID_INPUT, "null operation error");
    EXPECT_TRUE(strcmp(key_handling.key_handling_state, "denied-signing-operation") == 0, "null operation state");
    operation.error = LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION,
            "denied-signing-operation",
            "invalid-signing-operation",
            "invalid operation status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    memset(operation.signing_operation_state, 'z', sizeof(operation.signing_operation_state));
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION,
            "denied-signing-operation",
            "invalid-signing-operation",
            "unterminated operation status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signing_operation_ready = 2u;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_INVALID_SIGNING_OPERATION,
            "denied-signing-operation",
            "invalid-signing-operation",
            "invalid operation flag status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signing_operation_ready = 0u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation ready status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.signing_operation_state, sizeof(operation.signing_operation_state), "denied-signing-operation");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation state status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.requested_signing_operation, sizeof(operation.requested_signing_operation), "sign-now");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "operation request status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signer_invocation_ready = 0u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation ready status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.signer_invocation_state, sizeof(operation.signer_invocation_state), "denied-signer-invocation");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation state status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.requested_signer_invocation, sizeof(operation.requested_signer_invocation), "spawn-signer");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation request status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signer_handoff_ready = 0u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff ready status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.signer_handoff_state, sizeof(operation.signer_handoff_state), "denied-signer-handoff");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff state status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.requested_signer_handoff, sizeof(operation.requested_signer_handoff), "invoke-signer");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff request status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signing_authorization_ready = 0u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization ready status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.signing_authorization_state, sizeof(operation.signing_authorization_state), "denied-signature-request");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization state status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.requested_signing_authorization, sizeof(operation.requested_signing_authorization), "real-signing");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization mode status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.requested_signature[0] = '\0';
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "missing signature status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(operation.requested_signature, sizeof(operation.requested_signature), "ML-DSA-future");
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "unknown signature status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, 0, LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING, "denied-key-handling", "missing-requested-key-handling", "missing key handling null") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "", LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING, "denied-key-handling", "missing-requested-key-handling", "missing key handling empty") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "parse-public-key", LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "public key parse request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "load-key-material", LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_MATERIAL, "denied-key-material", "denied-key-material", "key material request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "handle-private-key", LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "generate-key", LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "use-hardware-key", LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "hardware key request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "load-trust-store", LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "revocation-lookup", LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation request") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    if (expect_denial(&operation, "real-key-handling", LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING, "denied-key-handling", "denied-key-handling", "unknown key handling status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    unterminated_key_handling,
                    &key_handling) == LATTICRA_STATUS_OK,
                "unterminated requested key handling status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING,
                "unterminated requested key handling error");
    EXPECT_TRUE(strcmp(key_handling.requested_key_handling, "invalid-key-handling") == 0,
                "unterminated requested key handling sanitized");
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_OK,
                "unterminated requested key handling render");
    EXPECT_TRUE(strstr(rendered, "requested_key_handling=invalid-key-handling") != 0,
                "unterminated requested key handling rendered sanitized");
    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    "metadata-only\nruntime_authority_granted=1",
                    &key_handling) == LATTICRA_STATUS_OK,
                "newline requested key handling status");
    EXPECT_TRUE(key_handling.error == LATTICRA_SEAL_KEY_HANDLING_DENIED_KEY_HANDLING,
                "newline requested key handling denied");
    EXPECT_TRUE(strcmp(key_handling.requested_key_handling, "invalid-key-handling") == 0,
                "newline requested key handling sanitized");
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_OK,
                "newline requested key handling render");
    EXPECT_TRUE(strstr(rendered, "requested_key_handling=invalid-key-handling") != 0,
                "newline requested key handling rendered sanitized");
    EXPECT_TRUE(strstr(rendered, "\nruntime_authority_granted=1\n") == 0,
                "newline requested key handling cannot forge report line");
    operation = fixture_operation("report-only");
    operation.private_key_handling = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.key_generation_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.trust_store_loaded = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_TRUST_STORE, "denied-trust-store", "denied-trust-store", "trust store status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.revocation_lookup_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.network_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "network status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.runtime_authority_granted = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_RUNTIME_AUTHORITY, "denied-runtime-authority", "denied-runtime-authority", "runtime status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signature_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signature performed status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.verification_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "verification status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.signer_invoked = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signer invoked status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.handoff_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "handoff performed status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.effect_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "effect status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.host_read_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host read status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.host_write_performed = 1u;
    if (expect_denial(&operation, "metadata-only", LATTICRA_SEAL_KEY_HANDLING_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host write status") != 0) {
        return 1;
    }
    operation = fixture_crypto_bound_operation("report-only");
    operation.standard_expectations_met = 0u;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE,
            "denied-crypto-graduation-gate",
            "denied-crypto-graduation-gate",
            "failed crypto gate status") != 0) {
        return 1;
    }
    operation = fixture_crypto_bound_operation("report-only");
    operation.authority_promotion_allowed = 1u;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE,
            "denied-crypto-graduation-gate",
            "denied-crypto-graduation-gate",
            "authority crypto gate status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.crypto_graduation_gate_passed = 1u;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE,
            "denied-crypto-graduation-gate",
            "denied-crypto-graduation-gate",
            "absent crypto gate stale pass status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    operation.authority_promotion_allowed = 1u;
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE,
            "denied-crypto-graduation-gate",
            "denied-crypto-graduation-gate",
            "absent crypto gate authority status") != 0) {
        return 1;
    }
    operation = fixture_operation("report-only");
    set_string(
        operation.crypto_graduation_profile,
        sizeof(operation.crypto_graduation_profile),
        "latticra-seal-crypto-graduation-gate/0.1");
    if (expect_denial(
            &operation,
            "metadata-only",
            LATTICRA_SEAL_KEY_HANDLING_DENIED_CRYPTO_GRADUATION_GATE,
            "denied-crypto-graduation-gate",
            "denied-crypto-graduation-gate",
            "absent crypto gate stale profile status") != 0) {
        return 1;
    }
    EXPECT_TRUE(
        latticra_seal_key_handling_from_operation(&operation, "metadata-only", 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(
        latticra_seal_key_handling_render(&key_handling, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_key_handling_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null render");
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");

    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    "metadata-only",
                    &key_handling) == LATTICRA_STATUS_OK,
                "tamper render source");
    memset(key_handling.key_handling_profile, 'z', sizeof(key_handling.key_handling_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated key handling render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated key handling render cleared");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(&key_handling) == 0,
                "unterminated key handling helper rejected");

    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    "metadata-only",
                    &key_handling) == LATTICRA_STATUS_OK,
                "authority key handling render source");
    key_handling.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority key handling render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority key handling render cleared");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(&key_handling) == 0,
                "authority key handling helper rejected");

    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    "metadata-only",
                    &key_handling) == LATTICRA_STATUS_OK,
                "ready flag key handling render source");
    key_handling.key_handling_ready = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "ready flag key handling render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "ready flag key handling render cleared");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(&key_handling) == 0,
                "ready flag key handling helper rejected");

    operation = fixture_operation("report-only");
    EXPECT_TRUE(latticra_seal_key_handling_from_operation(
                    &operation,
                    "metadata-only",
                    &key_handling) == LATTICRA_STATUS_OK,
                "absent crypto gate render source");
    key_handling.crypto_graduation_gate_passed = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_key_handling_render(&key_handling, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "absent crypto gate stale render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "absent crypto gate stale render cleared");
    EXPECT_TRUE(latticra_seal_key_handling_is_metadata_only(&key_handling) == 0,
                "absent crypto gate stale helper rejected");
    return 0;
}

int main(void) {
    if (key_handling_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (key_handling_carries_crypto_graduation_evidence() != 0) {
        return 1;
    }
    if (key_handling_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (key_handling_fails_closed() != 0) {
        return 1;
    }
    printf("seal key-handling invariants: ok\n");
    return 0;
}
