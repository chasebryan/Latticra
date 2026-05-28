#include "latticra/seal_signing_operation.h"

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

static latticra_seal_signer_invocation_t fixture_invocation(const char *mode) {
    latticra_seal_signer_invocation_t invocation;
    const char *requested_mode = mode != 0 ? mode : "report-only";

    memset(&invocation, 0, sizeof(invocation));
    set_string(
        invocation.signer_invocation_profile,
        sizeof(invocation.signer_invocation_profile),
        "latticra-seal-signer-invocation/0.1");
    set_string(invocation.signer_handoff_profile, sizeof(invocation.signer_handoff_profile), "latticra-seal-signer-handoff/0.1");
    set_string(
        invocation.signing_authorization_profile,
        sizeof(invocation.signing_authorization_profile),
        "latticra-seal-signing-authorization/0.1");
    set_string(invocation.signature_request_profile, sizeof(invocation.signature_request_profile), "latticra-seal-signature-request/0.1");
    set_string(invocation.envelope_profile, sizeof(invocation.envelope_profile), "latticra-seal-report-envelope/0.1");
    set_string(invocation.report_profile, sizeof(invocation.report_profile), "latticra-seal-runtime-handoff-report/0.1");
    set_string(invocation.handoff_profile, sizeof(invocation.handoff_profile), "latticra-seal-runtime-handoff-evaluation/0.1");
    set_string(invocation.decision_profile, sizeof(invocation.decision_profile), "latticra-seal-verified-effect-decision/0.1");
    set_string(invocation.gate_profile, sizeof(invocation.gate_profile), "latticra-seal-verified-capability-gate/0.1");
    set_string(invocation.receipt_profile, sizeof(invocation.receipt_profile), "latticra-seal-verified-receipt/0.1");
    set_string(invocation.verify_profile, sizeof(invocation.verify_profile), "latticra-seal-ed25519-verify/0.1");
    set_string(invocation.message_digest_algorithm, sizeof(invocation.message_digest_algorithm), "SHA-256");
    set_string(
        invocation.message_digest_hex,
        sizeof(invocation.message_digest_hex),
        "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    set_string(invocation.public_key_identity_label, sizeof(invocation.public_key_identity_label), "rfc8032-test-key");
    set_string(invocation.crypto_graduation_gate_state, sizeof(invocation.crypto_graduation_gate_state), "not-required");
    set_string(invocation.requested_capability, sizeof(invocation.requested_capability), "verified-receipt-report");
    set_string(invocation.requested_effect, sizeof(invocation.requested_effect), requested_mode);
    set_string(invocation.requested_handoff, sizeof(invocation.requested_handoff), requested_mode);
    set_string(invocation.requested_report, sizeof(invocation.requested_report), requested_mode);
    set_string(invocation.requested_envelope, sizeof(invocation.requested_envelope), requested_mode);
    set_string(invocation.requested_signature, sizeof(invocation.requested_signature), "Ed25519-development");
    set_string(invocation.requested_signing_authorization, sizeof(invocation.requested_signing_authorization), "metadata-only");
    set_string(invocation.requested_signer_handoff, sizeof(invocation.requested_signer_handoff), "metadata-only");
    set_string(invocation.requested_signer_invocation, sizeof(invocation.requested_signer_invocation), "metadata-only");
    set_string(invocation.requested_scope, sizeof(invocation.requested_scope), "local-fixture-scope");
    set_string(invocation.signing_authorization_state, sizeof(invocation.signing_authorization_state), "authorized-metadata-only");
    invocation.signing_authorization_ready = 1u;
    set_string(invocation.signer_handoff_state, sizeof(invocation.signer_handoff_state), "handoff-metadata-only");
    invocation.signer_handoff_ready = 1u;
    set_string(invocation.signer_invocation_state, sizeof(invocation.signer_invocation_state), "invocation-metadata-only");
    invocation.signer_invocation_ready = 1u;
    invocation.signature_performed = 0u;
    invocation.verification_performed = 0u;
    invocation.signer_invoked = 0u;
    invocation.private_key_handling = 0u;
    invocation.key_generation_performed = 0u;
    invocation.trust_store_loaded = 0u;
    invocation.revocation_lookup_performed = 0u;
    invocation.handoff_performed = 0u;
    invocation.effect_performed = 0u;
    invocation.runtime_authority_granted = 0u;
    invocation.host_read_performed = 0u;
    invocation.host_write_performed = 0u;
    invocation.network_performed = 0u;
    set_string(invocation.mode, sizeof(invocation.mode), "metadata-only");
    invocation.error = LATTICRA_SEAL_SIGNER_INVOCATION_OK;
    set_string(invocation.status, sizeof(invocation.status), "signer-invocation-metadata");
    return invocation;
}

static int expect_denial(
    latticra_seal_signer_invocation_t *invocation,
    const char *requested_signing_operation,
    latticra_seal_signing_operation_error_t expected_error,
    const char *expected_state,
    const char *expected_status,
    const char *message) {
    latticra_seal_signing_operation_t operation;

    EXPECT_TRUE(
        latticra_seal_signing_operation_from_invocation(invocation, requested_signing_operation, &operation) ==
            LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(operation.error == expected_error, "expected denial error");
    EXPECT_TRUE(strcmp(operation.signing_operation_state, expected_state) == 0, "expected denial state");
    EXPECT_TRUE(strcmp(operation.status, expected_status) == 0, "expected denial status");
    EXPECT_TRUE(operation.signing_operation_ready == 0u, "denial ready");
    return 0;
}

static int operation_allows_report_only_metadata(void) {
    latticra_seal_signer_invocation_t invocation = fixture_invocation("report-only");
    latticra_seal_signing_operation_t operation;
    char rendered[LATTICRA_SEAL_SIGNING_OPERATION_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signing_operation_from_invocation(&invocation, "metadata-only", &operation) ==
            LATTICRA_STATUS_OK,
        "operation status");
    EXPECT_TRUE(operation.error == LATTICRA_SEAL_SIGNING_OPERATION_OK, "operation ok");
    EXPECT_TRUE(
        strcmp(operation.signing_operation_profile, "latticra-seal-signing-operation/0.1") == 0,
        "operation profile");
    EXPECT_TRUE(strcmp(operation.signer_invocation_profile, invocation.signer_invocation_profile) == 0, "invocation profile");
    EXPECT_TRUE(strcmp(operation.signer_handoff_profile, invocation.signer_handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(operation.signing_authorization_profile, invocation.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(operation.signature_request_profile, invocation.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(operation.envelope_profile, invocation.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(operation.report_profile, invocation.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(operation.handoff_profile, invocation.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(operation.decision_profile, invocation.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(operation.gate_profile, invocation.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(operation.receipt_profile, invocation.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(operation.verify_profile, invocation.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(operation.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(operation.message_digest_hex, invocation.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(operation.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(operation.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(operation.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(operation.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(operation.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(operation.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(operation.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(operation.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(operation.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(operation.requested_signer_invocation, "metadata-only") == 0, "requested signer invocation");
    EXPECT_TRUE(strcmp(operation.requested_signing_operation, "metadata-only") == 0, "requested signing operation");
    EXPECT_TRUE(strcmp(operation.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(operation.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(operation.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(operation.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(operation.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(strcmp(operation.signer_invocation_state, "invocation-metadata-only") == 0, "invocation state");
    EXPECT_TRUE(operation.signer_invocation_ready == 1u, "invocation ready");
    EXPECT_TRUE(strcmp(operation.signing_operation_state, "operation-metadata-only") == 0, "operation state");
    EXPECT_TRUE(operation.signing_operation_ready == 1u, "operation ready");
    EXPECT_TRUE(operation.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(operation.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(operation.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(operation.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(operation.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(operation.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(operation.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(operation.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(operation.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(operation.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(operation.host_read_performed == 0u, "host read");
    EXPECT_TRUE(operation.host_write_performed == 0u, "host write");
    EXPECT_TRUE(operation.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(operation.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(operation.status, "signing-operation-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_signing_operation_is_metadata_only(&operation) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNING OPERATION") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "requested_signer_invocation=metadata-only") != 0, "render requested invocation");
    EXPECT_TRUE(strstr(rendered, "requested_signing_operation=metadata-only") != 0, "render requested operation");
    EXPECT_TRUE(strstr(rendered, "signing_operation_state=operation-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "signing_operation_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "signer_invoked=0") != 0, "render signer invoked");
    EXPECT_TRUE(strstr(rendered, "signature_performed=0") != 0, "render signature performed");
    EXPECT_TRUE(strstr(rendered, "verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=0") != 0, "render key generation");
    EXPECT_TRUE(strstr(rendered, "trust_store_loaded=0") != 0, "render trust store");
    EXPECT_TRUE(strstr(rendered, "revocation_lookup_performed=0") != 0, "render revocation");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int operation_allows_evaluate_only_metadata(void) {
    latticra_seal_signer_invocation_t invocation = fixture_invocation("evaluate-only");
    latticra_seal_signing_operation_t operation;

    EXPECT_TRUE(
        latticra_seal_signing_operation_from_invocation(&invocation, "metadata-only", &operation) ==
            LATTICRA_STATUS_OK,
        "evaluate operation status");
    EXPECT_TRUE(operation.error == LATTICRA_SEAL_SIGNING_OPERATION_OK, "evaluate operation ok");
    EXPECT_TRUE(strcmp(operation.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(operation.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(operation.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(operation.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(operation.signing_operation_state, "operation-metadata-only") == 0, "evaluate operation state");
    EXPECT_TRUE(operation.signing_operation_ready == 1u, "evaluate operation ready");
    EXPECT_TRUE(operation.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(operation.verification_performed == 0u, "evaluate verification performed");
    EXPECT_TRUE(operation.signer_invoked == 0u, "evaluate signer invoked");
    EXPECT_TRUE(operation.private_key_handling == 0u, "evaluate private key handling");
    EXPECT_TRUE(operation.key_generation_performed == 0u, "evaluate key generation");
    EXPECT_TRUE(operation.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(operation.revocation_lookup_performed == 0u, "evaluate revocation");
    EXPECT_TRUE(operation.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(operation.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(operation.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(operation.network_performed == 0u, "evaluate network");
    return 0;
}

static int operation_fails_closed(void) {
    latticra_seal_signer_invocation_t invocation = fixture_invocation("report-only");
    latticra_seal_signing_operation_t operation;
    char tiny[1];
    char rendered[LATTICRA_SEAL_SIGNING_OPERATION_RENDER_MAX];
    char unterminated_operation[LATTICRA_SEAL_SIGNING_OPERATION_LABEL_MAX];

    memset(unterminated_operation, 'x', sizeof(unterminated_operation));

    EXPECT_TRUE(
        latticra_seal_signing_operation_from_invocation(0, "metadata-only", &operation) == LATTICRA_STATUS_OK,
        "null invocation status");
    EXPECT_TRUE(operation.error == LATTICRA_SEAL_SIGNING_OPERATION_INVALID_INPUT, "null invocation error");
    EXPECT_TRUE(strcmp(operation.signing_operation_state, "denied-signer-invocation") == 0, "null invocation state");
    invocation.error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION;
    if (expect_denial(
            &invocation,
            "metadata-only",
            LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION,
            "denied-signer-invocation",
            "invalid-signer-invocation",
            "invalid invocation status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    memset(invocation.signer_invocation_state, 'z', sizeof(invocation.signer_invocation_state));
    if (expect_denial(
            &invocation,
            "metadata-only",
            LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION,
            "denied-signer-invocation",
            "invalid-signer-invocation",
            "unterminated invocation status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signer_invocation_ready = 2u;
    if (expect_denial(
            &invocation,
            "metadata-only",
            LATTICRA_SEAL_SIGNING_OPERATION_INVALID_SIGNER_INVOCATION,
            "denied-signer-invocation",
            "invalid-signer-invocation",
            "invalid invocation flag status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signer_invocation_ready = 0u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation ready status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.signer_invocation_state, sizeof(invocation.signer_invocation_state), "denied-signer-invocation");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation state status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.requested_signer_invocation, sizeof(invocation.requested_signer_invocation), "spawn-signer");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "invocation request status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signer_handoff_ready = 0u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff ready status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.signer_handoff_state, sizeof(invocation.signer_handoff_state), "denied-signer-handoff");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff state status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.requested_signer_handoff, sizeof(invocation.requested_signer_handoff), "invoke-signer");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff request status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signing_authorization_ready = 0u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization ready status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.signing_authorization_state, sizeof(invocation.signing_authorization_state), "denied-signature-request");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization state status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.requested_signing_authorization, sizeof(invocation.requested_signing_authorization), "real-signing");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization mode status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.requested_signature[0] = '\0';
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "missing signature status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    set_string(invocation.requested_signature, sizeof(invocation.requested_signature), "ML-DSA-future");
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "unknown signature status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    if (expect_denial(&invocation, 0, LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION, "denied-signing-operation", "missing-requested-signing-operation", "missing operation null status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    if (expect_denial(&invocation, "", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION, "denied-signing-operation", "missing-requested-signing-operation", "missing operation empty status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    if (expect_denial(&invocation, "sign-now", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION, "denied-signing-operation", "denied-signing-operation", "unknown operation status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    EXPECT_TRUE(latticra_seal_signing_operation_from_invocation(
                    &invocation,
                    unterminated_operation,
                    &operation) == LATTICRA_STATUS_OK,
                "unterminated requested signing operation status");
    EXPECT_TRUE(operation.error == LATTICRA_SEAL_SIGNING_OPERATION_DENIED_SIGNING_OPERATION,
                "unterminated requested signing operation error");
    EXPECT_TRUE(strcmp(operation.requested_signing_operation, "invalid-signing-operation") == 0,
                "unterminated requested signing operation sanitized");
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_OK,
                "unterminated requested signing operation render");
    EXPECT_TRUE(strstr(rendered, "requested_signing_operation=invalid-signing-operation") != 0,
                "unterminated requested signing operation rendered sanitized");
    invocation = fixture_invocation("report-only");
    invocation.private_key_handling = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.key_generation_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.trust_store_loaded = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "trust store status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.revocation_lookup_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.network_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "network status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.runtime_authority_granted = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_RUNTIME_AUTHORITY, "denied-runtime-authority", "denied-runtime-authority", "runtime status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signature_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signature performed status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.verification_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "verification status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.signer_invoked = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signer invoked status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.handoff_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "handoff performed status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.effect_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "effect status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.host_read_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host read status") != 0) {
        return 1;
    }
    invocation = fixture_invocation("report-only");
    invocation.host_write_performed = 1u;
    if (expect_denial(&invocation, "metadata-only", LATTICRA_SEAL_SIGNING_OPERATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host write status") != 0) {
        return 1;
    }
    EXPECT_TRUE(
        latticra_seal_signing_operation_from_invocation(&invocation, "metadata-only", 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_signing_operation_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(
        latticra_seal_signing_operation_render(&operation, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_signing_operation_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null operation render");
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");

    invocation = fixture_invocation("report-only");
    EXPECT_TRUE(latticra_seal_signing_operation_from_invocation(
                    &invocation,
                    "metadata-only",
                    &operation) == LATTICRA_STATUS_OK,
                "tamper render source");
    memset(operation.signing_operation_profile, 'z', sizeof(operation.signing_operation_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated signing operation render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated signing operation render cleared");
    EXPECT_TRUE(latticra_seal_signing_operation_is_metadata_only(&operation) == 0,
                "unterminated signing operation helper rejected");

    invocation = fixture_invocation("report-only");
    EXPECT_TRUE(latticra_seal_signing_operation_from_invocation(
                    &invocation,
                    "metadata-only",
                    &operation) == LATTICRA_STATUS_OK,
                "authority signing operation render source");
    operation.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority signing operation render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority signing operation render cleared");
    EXPECT_TRUE(latticra_seal_signing_operation_is_metadata_only(&operation) == 0,
                "authority signing operation helper rejected");

    invocation = fixture_invocation("report-only");
    EXPECT_TRUE(latticra_seal_signing_operation_from_invocation(
                    &invocation,
                    "metadata-only",
                    &operation) == LATTICRA_STATUS_OK,
                "ready flag signing operation render source");
    operation.signing_operation_ready = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_operation_render(&operation, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "ready flag signing operation render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "ready flag signing operation render cleared");
    EXPECT_TRUE(latticra_seal_signing_operation_is_metadata_only(&operation) == 0,
                "ready flag signing operation helper rejected");
    return 0;
}

int main(void) {
    if (operation_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (operation_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (operation_fails_closed() != 0) {
        return 1;
    }
    printf("seal signing operation invariants: ok\n");
    return 0;
}
