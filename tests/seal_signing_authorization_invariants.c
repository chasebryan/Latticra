#include "latticra/seal_signing_authorization.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_signature_request_t fixture_request(const char *mode) {
    latticra_seal_signature_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.signature_request_profile, sizeof(request.signature_request_profile), "%s", "latticra-seal-signature-request/0.1");
    (void)snprintf(request.envelope_profile, sizeof(request.envelope_profile), "%s", "latticra-seal-report-envelope/0.1");
    (void)snprintf(request.report_profile, sizeof(request.report_profile), "%s", "latticra-seal-runtime-handoff-report/0.1");
    (void)snprintf(request.handoff_profile, sizeof(request.handoff_profile), "%s", "latticra-seal-runtime-handoff-evaluation/0.1");
    (void)snprintf(request.decision_profile, sizeof(request.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(request.gate_profile, sizeof(request.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(request.receipt_profile, sizeof(request.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(request.verify_profile, sizeof(request.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(request.message_digest_algorithm, sizeof(request.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(request.message_digest_hex, sizeof(request.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(request.public_key_identity_label, sizeof(request.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(request.crypto_graduation_gate_state, sizeof(request.crypto_graduation_gate_state), "%s", "not-required");
    (void)snprintf(request.requested_capability, sizeof(request.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(request.requested_effect, sizeof(request.requested_effect), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(request.requested_handoff, sizeof(request.requested_handoff), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(request.requested_report, sizeof(request.requested_report), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(request.requested_envelope, sizeof(request.requested_envelope), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(request.requested_signature, sizeof(request.requested_signature), "%s", "Ed25519-development");
    (void)snprintf(request.requested_scope, sizeof(request.requested_scope), "%s", "local-fixture-scope");
    if (mode != 0 && strcmp(mode, "evaluate-only") == 0) {
        (void)snprintf(request.envelope_state, sizeof(request.envelope_state), "%s", "sealed-evaluate-only");
    } else {
        (void)snprintf(request.envelope_state, sizeof(request.envelope_state), "%s", "sealed-report-only");
    }
    request.envelope_ready = 1u;
    (void)snprintf(request.signature_request_state, sizeof(request.signature_request_state), "%s", "requested-metadata-only");
    request.signature_request_ready = 1u;
    request.signature_performed = 0u;
    request.verification_performed = 0u;
    request.private_key_handling = 0u;
    request.handoff_performed = 0u;
    request.effect_performed = 0u;
    request.runtime_authority_granted = 0u;
    request.host_read_performed = 0u;
    request.host_write_performed = 0u;
    request.network_performed = 0u;
    request.error = LATTICRA_SEAL_SIGNATURE_REQUEST_OK;
    (void)snprintf(request.status, sizeof(request.status), "%s", "signature-request-metadata");
    return request;
}

static latticra_seal_signature_request_t fixture_crypto_bound_request(const char *mode) {
    latticra_seal_signature_request_t request = fixture_request(mode);
    (void)snprintf(
        request.crypto_graduation_profile,
        sizeof(request.crypto_graduation_profile),
        "%s",
        "latticra-seal-crypto-graduation-gate/0.1");
    (void)snprintf(
        request.assurance_baseline_profile,
        sizeof(request.assurance_baseline_profile),
        "%s",
        "latticra-cryptographic-assurance-key-management/0.1");
    (void)snprintf(
        request.crypto_graduation_gate_state,
        sizeof(request.crypto_graduation_gate_state),
        "%s",
        "graduated-authority-neutral");
    request.crypto_graduation_gate_present = 1u;
    request.crypto_graduation_gate_passed = 1u;
    request.standard_expectations_met = 1u;
    request.local_verify_graduated = 1u;
    request.receipt_promotion_graduated = 1u;
    request.authority_promotion_allowed = 0u;
    return request;
}

static int authorization_allows_report_only_metadata(void) {
    latticra_seal_signature_request_t request = fixture_request("report-only");
    latticra_seal_signing_authorization_t authorization;
    char rendered[LATTICRA_SEAL_SIGNING_AUTHORIZATION_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK,
        "authorization status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK, "authorization ok");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_profile, "latticra-seal-signing-authorization/0.1") == 0, "authorization profile");
    EXPECT_TRUE(strcmp(authorization.signature_request_profile, request.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(authorization.envelope_profile, request.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(authorization.report_profile, request.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(authorization.handoff_profile, request.handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(authorization.decision_profile, request.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(authorization.gate_profile, request.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(authorization.receipt_profile, request.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(authorization.verify_profile, request.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(authorization.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(authorization.message_digest_hex, request.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(authorization.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(authorization.crypto_graduation_gate_state, "not-required") == 0, "crypto gate legacy");
    EXPECT_TRUE(strcmp(authorization.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(authorization.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(authorization.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(authorization.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(authorization.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(authorization.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(authorization.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(authorization.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(authorization.crypto_graduation_gate_present == 0u, "crypto present legacy");
    EXPECT_TRUE(authorization.standard_expectations_met == 0u, "standard legacy");
    EXPECT_TRUE(strcmp(authorization.signature_request_state, "requested-metadata-only") == 0, "request state");
    EXPECT_TRUE(authorization.signature_request_ready == 1u, "request ready");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(authorization.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(authorization.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(authorization.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(authorization.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(authorization.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(authorization.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(authorization.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(authorization.handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(authorization.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(authorization.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(authorization.host_read_performed == 0u, "host read");
    EXPECT_TRUE(authorization.host_write_performed == 0u, "host write");
    EXPECT_TRUE(authorization.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(authorization.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(latticra_seal_signing_authorization_is_metadata_only(&authorization) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNING AUTHORIZATION") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signing_authorization_state=authorized-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "signing_authorization_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "signature_performed=0") != 0, "render signature performed");
    EXPECT_TRUE(strstr(rendered, "verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=0") != 0, "render key generation");
    EXPECT_TRUE(strstr(rendered, "trust_store_loaded=0") != 0, "render trust store");
    EXPECT_TRUE(strstr(rendered, "revocation_lookup_performed=0") != 0, "render revocation");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int authorization_carries_crypto_graduation_evidence(void) {
    latticra_seal_signature_request_t request = fixture_crypto_bound_request("report-only");
    latticra_seal_signing_authorization_t authorization;
    char rendered[LATTICRA_SEAL_SIGNING_AUTHORIZATION_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK,
        "crypto authorization status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK, "crypto authorization ok");
    EXPECT_TRUE(strcmp(authorization.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "crypto profile");
    EXPECT_TRUE(strcmp(authorization.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "assurance profile");
    EXPECT_TRUE(strcmp(authorization.crypto_graduation_gate_state, "graduated-authority-neutral") == 0, "crypto state");
    EXPECT_TRUE(authorization.crypto_graduation_gate_present == 1u, "crypto present");
    EXPECT_TRUE(authorization.crypto_graduation_gate_passed == 1u, "crypto passed");
    EXPECT_TRUE(authorization.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(authorization.local_verify_graduated == 1u, "local verify");
    EXPECT_TRUE(authorization.receipt_promotion_graduated == 1u, "receipt promotion");
    EXPECT_TRUE(authorization.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(authorization.signing_authorization_ready == 1u, "crypto authorization ready");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "authorized-metadata-only") == 0, "crypto authorization state");
    EXPECT_TRUE(authorization.signature_performed == 0u, "crypto signature");
    EXPECT_TRUE(authorization.verification_performed == 0u, "crypto verification");
    EXPECT_TRUE(authorization.private_key_handling == 0u, "crypto private key");
    EXPECT_TRUE(authorization.key_generation_performed == 0u, "crypto key generation");
    EXPECT_TRUE(authorization.runtime_authority_granted == 0u, "crypto runtime");
    EXPECT_TRUE(authorization.host_read_performed == 0u, "crypto host read");
    EXPECT_TRUE(authorization.host_write_performed == 0u, "crypto host write");
    EXPECT_TRUE(authorization.network_performed == 0u, "crypto network");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "crypto render");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_gate_present=1") != 0, "render crypto present");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "render standard");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "render authority promotion");
    return 0;
}

static int authorization_allows_evaluate_only_metadata(void) {
    latticra_seal_signature_request_t request = fixture_request("evaluate-only");
    latticra_seal_signing_authorization_t authorization;

    EXPECT_TRUE(
        latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK,
        "evaluate authorization status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_OK, "evaluate authorization ok");
    EXPECT_TRUE(strcmp(authorization.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(authorization.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(authorization.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(authorization.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "authorized-metadata-only") == 0, "evaluate authorization state");
    EXPECT_TRUE(authorization.signing_authorization_ready == 1u, "evaluate authorization ready");
    EXPECT_TRUE(authorization.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(authorization.verification_performed == 0u, "evaluate verification performed");
    EXPECT_TRUE(authorization.private_key_handling == 0u, "evaluate private key handling");
    EXPECT_TRUE(authorization.key_generation_performed == 0u, "evaluate key generation");
    EXPECT_TRUE(authorization.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(authorization.revocation_lookup_performed == 0u, "evaluate revocation");
    EXPECT_TRUE(authorization.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(authorization.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(authorization.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(authorization.network_performed == 0u, "evaluate network");
    return 0;
}

static int authorization_fails_closed(void) {
    latticra_seal_signature_request_t request = fixture_request("report-only");
    latticra_seal_signing_authorization_t authorization;
    char tiny[1];
    char rendered[LATTICRA_SEAL_SIGNING_AUTHORIZATION_RENDER_MAX];
    char unterminated_authorization[LATTICRA_SEAL_SIGNING_AUTHORIZATION_LABEL_MAX];

    memset(unterminated_authorization, 'x', sizeof(unterminated_authorization));

    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(0, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "null request status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_INPUT, "null request error");
    request.error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "invalid request status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST, "invalid request error");
    request = fixture_request("report-only");
    memset(request.signature_request_state, 'z', sizeof(request.signature_request_state));
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "unterminated request status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST, "unterminated request error");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "denied-signature-request") == 0, "unterminated request state");
    request = fixture_request("report-only");
    request.signature_request_ready = 2u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "invalid request flag status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_INVALID_SIGNATURE_REQUEST, "invalid request flag error");
    request = fixture_request("report-only");
    request.signature_request_ready = 0u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "request ready status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST, "request ready error");
    request = fixture_request("report-only");
    (void)snprintf(request.signature_request_state, sizeof(request.signature_request_state), "%s", "denied-signature-request");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "request state status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_REQUEST, "request state error");
    request = fixture_request("report-only");
    request.requested_signature[0] = '\0';
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "missing signature status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM, "missing signature error");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "denied-signature-algorithm") == 0, "missing signature state");
    request = fixture_request("report-only");
    (void)snprintf(request.requested_signature, sizeof(request.requested_signature), "%s", "ML-DSA-future");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "unknown signature status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_SIGNATURE_ALGORITHM, "unknown signature error");
    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, 0, &authorization) == LATTICRA_STATUS_OK, "missing authorization null status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST, "missing authorization null error");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "denied-authorization-request") == 0, "missing authorization state");
    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "", &authorization) == LATTICRA_STATUS_OK, "missing authorization empty status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST, "missing authorization empty error");
    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "real-signing", &authorization) == LATTICRA_STATUS_OK, "unknown authorization status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST, "unknown authorization error");
    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(
                    &request,
                    unterminated_authorization,
                    &authorization) == LATTICRA_STATUS_OK,
                "unterminated requested signing authorization status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_AUTHORIZATION_REQUEST,
                "unterminated requested signing authorization error");
    EXPECT_TRUE(strcmp(authorization.requested_signing_authorization,
                       "invalid-signing-authorization") == 0,
                "unterminated requested signing authorization sanitized");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_OK,
                "unterminated requested signing authorization render");
    EXPECT_TRUE(strstr(rendered,
                       "requested_signing_authorization=invalid-signing-authorization") != 0,
                "unterminated requested signing authorization rendered sanitized");
    request = fixture_request("report-only");
    request.private_key_handling = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "private key status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_PRIVATE_KEY, "private key error");
    request = fixture_request("report-only");
    request.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_RUNTIME_AUTHORITY, "runtime error");
    request = fixture_request("report-only");
    request.signature_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "signature performed status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "signature performed error");
    request = fixture_request("report-only");
    request.verification_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "verification status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "verification error");
    request = fixture_request("report-only");
    request.handoff_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "handoff status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "handoff error");
    request = fixture_request("report-only");
    request.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "effect error");
    request = fixture_request("report-only");
    request.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "host read error");
    request = fixture_request("report-only");
    request.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_HOST_EFFECT, "host write error");
    request = fixture_request("report-only");
    request.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_NETWORK_EFFECT, "network error");
    request = fixture_crypto_bound_request("report-only");
    request.standard_expectations_met = 0u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "failed crypto gate status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE, "failed crypto gate error");
    EXPECT_TRUE(strcmp(authorization.signing_authorization_state, "denied-crypto-graduation-gate") == 0, "failed crypto gate state");
    request = fixture_crypto_bound_request("report-only");
    request.authority_promotion_allowed = 1u;
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", &authorization) == LATTICRA_STATUS_OK, "authority crypto gate status");
    EXPECT_TRUE(authorization.error == LATTICRA_SEAL_SIGNING_AUTHORIZATION_DENIED_CRYPTO_GRADUATION_GATE, "authority crypto gate error");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(&request, "metadata-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signing_authorization_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null authorization render");
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");

    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(
                    &request,
                    "metadata-only",
                    &authorization) == LATTICRA_STATUS_OK,
                "tamper render source");
    memset(authorization.signing_authorization_profile,
           'z',
           sizeof(authorization.signing_authorization_profile));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "unterminated authorization render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated authorization render cleared");
    EXPECT_TRUE(latticra_seal_signing_authorization_is_metadata_only(&authorization) == 0,
                "unterminated authorization helper rejected");

    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(
                    &request,
                    "metadata-only",
                    &authorization) == LATTICRA_STATUS_OK,
                "authority authorization render source");
    authorization.runtime_authority_granted = 1u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "authority authorization render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "authority authorization render cleared");
    EXPECT_TRUE(latticra_seal_signing_authorization_is_metadata_only(&authorization) == 0,
                "authority authorization helper rejected");

    request = fixture_request("report-only");
    EXPECT_TRUE(latticra_seal_signing_authorization_from_request(
                    &request,
                    "metadata-only",
                    &authorization) == LATTICRA_STATUS_OK,
                "ready flag authorization render source");
    authorization.signing_authorization_ready = 2u;
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signing_authorization_render(&authorization, rendered, sizeof(rendered)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "ready flag authorization render rejected");
    EXPECT_TRUE(rendered[0] == '\0', "ready flag authorization render cleared");
    EXPECT_TRUE(latticra_seal_signing_authorization_is_metadata_only(&authorization) == 0,
                "ready flag authorization helper rejected");
    return 0;
}

int main(void) {
    if (authorization_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (authorization_carries_crypto_graduation_evidence() != 0) {
        return 1;
    }
    if (authorization_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (authorization_fails_closed() != 0) {
        return 1;
    }
    printf("seal signing authorization invariants: ok\n");
    return 0;
}
