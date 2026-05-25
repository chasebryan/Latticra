#include "latticra/seal_signer_handoff.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_signing_authorization_t fixture_authorization(const char *mode) {
    latticra_seal_signing_authorization_t authorization;
    memset(&authorization, 0, sizeof(authorization));
    (void)snprintf(
        authorization.signing_authorization_profile,
        sizeof(authorization.signing_authorization_profile),
        "%s",
        "latticra-seal-signing-authorization/0.1");
    (void)snprintf(authorization.signature_request_profile, sizeof(authorization.signature_request_profile), "%s", "latticra-seal-signature-request/0.1");
    (void)snprintf(authorization.envelope_profile, sizeof(authorization.envelope_profile), "%s", "latticra-seal-report-envelope/0.1");
    (void)snprintf(authorization.report_profile, sizeof(authorization.report_profile), "%s", "latticra-seal-runtime-handoff-report/0.1");
    (void)snprintf(authorization.handoff_profile, sizeof(authorization.handoff_profile), "%s", "latticra-seal-runtime-handoff-evaluation/0.1");
    (void)snprintf(authorization.decision_profile, sizeof(authorization.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(authorization.gate_profile, sizeof(authorization.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(authorization.receipt_profile, sizeof(authorization.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(authorization.verify_profile, sizeof(authorization.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(authorization.message_digest_algorithm, sizeof(authorization.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(
        authorization.message_digest_hex,
        sizeof(authorization.message_digest_hex),
        "%s",
        "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(authorization.public_key_identity_label, sizeof(authorization.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(authorization.requested_capability, sizeof(authorization.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(authorization.requested_effect, sizeof(authorization.requested_effect), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(authorization.requested_handoff, sizeof(authorization.requested_handoff), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(authorization.requested_report, sizeof(authorization.requested_report), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(authorization.requested_envelope, sizeof(authorization.requested_envelope), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(authorization.requested_signature, sizeof(authorization.requested_signature), "%s", "Ed25519-development");
    (void)snprintf(authorization.requested_signing_authorization, sizeof(authorization.requested_signing_authorization), "%s", "metadata-only");
    (void)snprintf(authorization.requested_scope, sizeof(authorization.requested_scope), "%s", "local-fixture-scope");
    (void)snprintf(authorization.signature_request_state, sizeof(authorization.signature_request_state), "%s", "requested-metadata-only");
    authorization.signature_request_ready = 1u;
    (void)snprintf(
        authorization.signing_authorization_state,
        sizeof(authorization.signing_authorization_state),
        "%s",
        "authorized-metadata-only");
    authorization.signing_authorization_ready = 1u;
    authorization.signature_performed = 0u;
    authorization.verification_performed = 0u;
    authorization.private_key_handling = 0u;
    authorization.key_generation_performed = 0u;
    authorization.trust_store_loaded = 0u;
    authorization.revocation_lookup_performed = 0u;
    authorization.handoff_performed = 0u;
    authorization.effect_performed = 0u;
    authorization.runtime_authority_granted = 0u;
    authorization.host_read_performed = 0u;
    authorization.host_write_performed = 0u;
    authorization.network_performed = 0u;
    (void)snprintf(authorization.mode, sizeof(authorization.mode), "%s", "metadata-only");
    authorization.error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK;
    (void)snprintf(authorization.status, sizeof(authorization.status), "%s", "signing-authorization-metadata");
    return authorization;
}

static int handoff_allows_report_only_metadata(void) {
    latticra_seal_signing_authorization_t authorization = fixture_authorization("report-only");
    latticra_seal_signer_handoff_t handoff;
    char rendered[LATTICRA_SEAL_SIGNER_HANDOFF_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK,
        "handoff status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_OK, "handoff ok");
    EXPECT_TRUE(strcmp(handoff.signer_handoff_profile, "latticra-seal-signer-handoff/0.1") == 0, "handoff profile");
    EXPECT_TRUE(strcmp(handoff.signing_authorization_profile, authorization.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(handoff.signature_request_profile, authorization.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(handoff.envelope_profile, authorization.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(handoff.report_profile, authorization.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(handoff.handoff_profile, authorization.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(handoff.decision_profile, authorization.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(handoff.gate_profile, authorization.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(handoff.receipt_profile, authorization.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(handoff.verify_profile, authorization.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(handoff.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(handoff.message_digest_hex, authorization.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(handoff.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(handoff.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(handoff.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(handoff.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(handoff.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(handoff.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(handoff.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(handoff.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(handoff.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(handoff.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(handoff.signature_request_state, "requested-metadata-only") == 0, "request state");
    EXPECT_TRUE(handoff.signature_request_ready == 1u, "request ready");
    EXPECT_TRUE(strcmp(handoff.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(handoff.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(handoff.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(handoff.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(handoff.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(handoff.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(handoff.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(handoff.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(handoff.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(handoff.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(handoff.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(handoff.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(handoff.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(handoff.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(handoff.host_read_performed == 0u, "host read");
    EXPECT_TRUE(handoff.host_write_performed == 0u, "host write");
    EXPECT_TRUE(handoff.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(handoff.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(latticra_seal_signer_handoff_is_metadata_only(&handoff) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signer_handoff_render(&handoff, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNER HANDOFF") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "requested_signer_handoff=metadata-only") != 0, "render requested handoff");
    EXPECT_TRUE(strstr(rendered, "signer_handoff_state=handoff-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "signer_handoff_ready=1") != 0, "render ready");
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

static int handoff_allows_evaluate_only_metadata(void) {
    latticra_seal_signing_authorization_t authorization = fixture_authorization("evaluate-only");
    latticra_seal_signer_handoff_t handoff;

    EXPECT_TRUE(
        latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK,
        "evaluate handoff status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_OK, "evaluate handoff ok");
    EXPECT_TRUE(strcmp(handoff.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(handoff.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(handoff.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(handoff.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(handoff.signer_handoff_state, "handoff-metadata-only") == 0, "evaluate handoff state");
    EXPECT_TRUE(handoff.signer_handoff_ready == 1u, "evaluate handoff ready");
    EXPECT_TRUE(handoff.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(handoff.verification_performed == 0u, "evaluate verification performed");
    EXPECT_TRUE(handoff.signer_invoked == 0u, "evaluate signer invoked");
    EXPECT_TRUE(handoff.private_key_handling == 0u, "evaluate private key handling");
    EXPECT_TRUE(handoff.key_generation_performed == 0u, "evaluate key generation");
    EXPECT_TRUE(handoff.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(handoff.revocation_lookup_performed == 0u, "evaluate revocation");
    EXPECT_TRUE(handoff.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(handoff.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(handoff.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(handoff.network_performed == 0u, "evaluate network");
    return 0;
}

static int handoff_fails_closed(void) {
    latticra_seal_signing_authorization_t authorization = fixture_authorization("report-only");
    latticra_seal_signer_handoff_t handoff;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(0, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "null authorization status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_INPUT, "null authorization error");
    authorization.error = LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "invalid authorization status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_INVALID_SIGNING_AUTHORIZATION, "invalid authorization error");
    authorization = fixture_authorization("report-only");
    authorization.signing_authorization_ready = 0u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "authorization ready status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION, "authorization ready error");
    authorization = fixture_authorization("report-only");
    (void)snprintf(authorization.signing_authorization_state, sizeof(authorization.signing_authorization_state), "%s", "denied-signature-request");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "authorization state status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION, "authorization state error");
    authorization = fixture_authorization("report-only");
    (void)snprintf(authorization.requested_signing_authorization, sizeof(authorization.requested_signing_authorization), "%s", "real-signing");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "authorization mode status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNING_AUTHORIZATION, "authorization mode error");
    authorization = fixture_authorization("report-only");
    authorization.requested_signature[0] = '\0';
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "missing signature status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM, "missing signature error");
    authorization = fixture_authorization("report-only");
    (void)snprintf(authorization.requested_signature, sizeof(authorization.requested_signature), "%s", "ML-DSA-future");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "unknown signature status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM, "unknown signature error");
    authorization = fixture_authorization("report-only");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, 0, &handoff) == LATTICRA_STATUS_OK, "missing handoff null status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF, "missing handoff null error");
    EXPECT_TRUE(strcmp(handoff.signer_handoff_state, "denied-signer-handoff") == 0, "missing handoff state");
    authorization = fixture_authorization("report-only");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "", &handoff) == LATTICRA_STATUS_OK, "missing handoff empty status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF, "missing handoff empty error");
    authorization = fixture_authorization("report-only");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "invoke-signer", &handoff) == LATTICRA_STATUS_OK, "unknown handoff status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNER_HANDOFF, "unknown handoff error");
    authorization = fixture_authorization("report-only");
    authorization.private_key_handling = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "private key status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY, "private key error");
    authorization = fixture_authorization("report-only");
    authorization.key_generation_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "key generation status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY, "key generation error");
    authorization = fixture_authorization("report-only");
    authorization.trust_store_loaded = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "trust store status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_PRIVATE_KEY, "trust store error");
    authorization = fixture_authorization("report-only");
    authorization.revocation_lookup_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "revocation status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT, "revocation error");
    authorization = fixture_authorization("report-only");
    authorization.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_RUNTIME_AUTHORITY, "runtime error");
    authorization = fixture_authorization("report-only");
    authorization.signature_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "signature performed status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "signature performed error");
    authorization = fixture_authorization("report-only");
    authorization.verification_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "verification status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "verification error");
    authorization = fixture_authorization("report-only");
    authorization.handoff_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "handoff performed status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "handoff performed error");
    authorization = fixture_authorization("report-only");
    authorization.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "effect error");
    authorization = fixture_authorization("report-only");
    authorization.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "host read error");
    authorization = fixture_authorization("report-only");
    authorization.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_HOST_EFFECT, "host write error");
    authorization = fixture_authorization("report-only");
    authorization.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", &handoff) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_NETWORK_EFFECT, "network error");
    EXPECT_TRUE(latticra_seal_signer_handoff_from_authorization(&authorization, "metadata-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signer_handoff_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signer_handoff_render(&handoff, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_signer_handoff_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null handoff render");
    EXPECT_TRUE(latticra_seal_signer_handoff_render(&handoff, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");
    return 0;
}

int main(void) {
    if (handoff_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (handoff_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (handoff_fails_closed() != 0) {
        return 1;
    }
    printf("seal signer handoff invariants: ok\n");
    return 0;
}
