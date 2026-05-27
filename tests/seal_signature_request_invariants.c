#include "latticra/seal_signature_request.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_report_envelope_t fixture_envelope(const char *mode) {
    latticra_seal_report_envelope_t envelope;
    memset(&envelope, 0, sizeof(envelope));
    (void)snprintf(envelope.envelope_profile, sizeof(envelope.envelope_profile), "%s", "latticra-seal-report-envelope/0.1");
    (void)snprintf(envelope.report_profile, sizeof(envelope.report_profile), "%s", "latticra-seal-runtime-handoff-report/0.1");
    (void)snprintf(envelope.handoff_profile, sizeof(envelope.handoff_profile), "%s", "latticra-seal-runtime-handoff-evaluation/0.1");
    (void)snprintf(envelope.decision_profile, sizeof(envelope.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(envelope.gate_profile, sizeof(envelope.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(envelope.receipt_profile, sizeof(envelope.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(envelope.verify_profile, sizeof(envelope.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(envelope.message_digest_algorithm, sizeof(envelope.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(envelope.message_digest_hex, sizeof(envelope.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(envelope.public_key_identity_label, sizeof(envelope.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(envelope.crypto_graduation_gate_state, sizeof(envelope.crypto_graduation_gate_state), "%s", "not-required");
    (void)snprintf(envelope.requested_capability, sizeof(envelope.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(envelope.requested_effect, sizeof(envelope.requested_effect), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(envelope.requested_handoff, sizeof(envelope.requested_handoff), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(envelope.requested_report, sizeof(envelope.requested_report), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(envelope.requested_envelope, sizeof(envelope.requested_envelope), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(envelope.requested_scope, sizeof(envelope.requested_scope), "%s", "local-fixture-scope");
    if (mode != 0 && strcmp(mode, "evaluate-only") == 0) {
        (void)snprintf(envelope.report_state, sizeof(envelope.report_state), "%s", "ready-evaluate-only");
        (void)snprintf(envelope.envelope_state, sizeof(envelope.envelope_state), "%s", "sealed-evaluate-only");
    } else {
        (void)snprintf(envelope.report_state, sizeof(envelope.report_state), "%s", "ready-report-only");
        (void)snprintf(envelope.envelope_state, sizeof(envelope.envelope_state), "%s", "sealed-report-only");
    }
    envelope.report_ready = 1u;
    envelope.envelope_ready = 1u;
    envelope.signature_performed = 0u;
    envelope.handoff_performed = 0u;
    envelope.effect_performed = 0u;
    envelope.runtime_authority_granted = 0u;
    envelope.host_read_performed = 0u;
    envelope.host_write_performed = 0u;
    envelope.network_performed = 0u;
    envelope.error = LATTICRA_SEAL_REPORT_ENVELOPE_OK;
    (void)snprintf(envelope.status, sizeof(envelope.status), "%s", "sealed-report-envelope-metadata");
    return envelope;
}

static latticra_seal_report_envelope_t fixture_crypto_bound_envelope(const char *mode) {
    latticra_seal_report_envelope_t envelope = fixture_envelope(mode);
    (void)snprintf(
        envelope.crypto_graduation_profile,
        sizeof(envelope.crypto_graduation_profile),
        "%s",
        "latticra-seal-crypto-graduation-gate/0.1");
    (void)snprintf(
        envelope.assurance_baseline_profile,
        sizeof(envelope.assurance_baseline_profile),
        "%s",
        "latticra-cryptographic-assurance-key-management/0.1");
    (void)snprintf(
        envelope.crypto_graduation_gate_state,
        sizeof(envelope.crypto_graduation_gate_state),
        "%s",
        "graduated-authority-neutral");
    envelope.crypto_graduation_gate_present = 1u;
    envelope.crypto_graduation_gate_passed = 1u;
    envelope.standard_expectations_met = 1u;
    envelope.local_verify_graduated = 1u;
    envelope.receipt_promotion_graduated = 1u;
    envelope.authority_promotion_allowed = 0u;
    return envelope;
}

static int request_allows_report_only_metadata(void) {
    latticra_seal_report_envelope_t envelope = fixture_envelope("report-only");
    latticra_seal_signature_request_t request;
    char rendered[LATTICRA_SEAL_SIGNATURE_REQUEST_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK,
        "signature request status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_OK, "signature request ok");
    EXPECT_TRUE(strcmp(request.signature_request_profile, "latticra-seal-signature-request/0.1") == 0, "request profile");
    EXPECT_TRUE(strcmp(request.envelope_profile, envelope.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(request.report_profile, envelope.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(request.handoff_profile, envelope.handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(request.decision_profile, envelope.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(request.gate_profile, envelope.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(request.receipt_profile, envelope.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(request.verify_profile, envelope.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(request.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(request.message_digest_hex, envelope.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(request.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(request.crypto_graduation_gate_state, "not-required") == 0, "crypto gate legacy");
    EXPECT_TRUE(strcmp(request.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(request.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(request.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(request.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(request.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(request.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(request.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(request.crypto_graduation_gate_present == 0u, "crypto present legacy");
    EXPECT_TRUE(request.standard_expectations_met == 0u, "standard legacy");
    EXPECT_TRUE(strcmp(request.envelope_state, "sealed-report-only") == 0, "envelope state");
    EXPECT_TRUE(request.envelope_ready == 1u, "envelope ready");
    EXPECT_TRUE(strcmp(request.signature_request_state, "requested-metadata-only") == 0, "request state");
    EXPECT_TRUE(request.signature_request_ready == 1u, "request ready");
    EXPECT_TRUE(request.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(request.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(request.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(request.handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(request.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(request.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(request.host_read_performed == 0u, "host read");
    EXPECT_TRUE(request.host_write_performed == 0u, "host write");
    EXPECT_TRUE(request.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_signature_request_is_metadata_only(&request) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signature_request_render(&request, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNATURE REQUEST") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signature_request_state=requested-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "signature_request_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "signature_performed=0") != 0, "render signature performed");
    EXPECT_TRUE(strstr(rendered, "verification_performed=0") != 0, "render verification performed");
    EXPECT_TRUE(strstr(rendered, "private_key_handling=0") != 0, "render private key handling");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    return 0;
}

static int request_carries_crypto_graduation_evidence(void) {
    latticra_seal_report_envelope_t envelope = fixture_crypto_bound_envelope("report-only");
    latticra_seal_signature_request_t request;
    char rendered[LATTICRA_SEAL_SIGNATURE_REQUEST_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK,
        "crypto request status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_OK, "crypto request ok");
    EXPECT_TRUE(strcmp(request.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "crypto profile");
    EXPECT_TRUE(strcmp(request.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "assurance profile");
    EXPECT_TRUE(strcmp(request.crypto_graduation_gate_state, "graduated-authority-neutral") == 0, "crypto state");
    EXPECT_TRUE(request.crypto_graduation_gate_present == 1u, "crypto present");
    EXPECT_TRUE(request.crypto_graduation_gate_passed == 1u, "crypto passed");
    EXPECT_TRUE(request.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(request.local_verify_graduated == 1u, "local verify");
    EXPECT_TRUE(request.receipt_promotion_graduated == 1u, "receipt promotion");
    EXPECT_TRUE(request.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(request.signature_request_ready == 1u, "crypto request ready");
    EXPECT_TRUE(strcmp(request.signature_request_state, "requested-metadata-only") == 0, "crypto request state");
    EXPECT_TRUE(request.signature_performed == 0u, "crypto signature");
    EXPECT_TRUE(request.verification_performed == 0u, "crypto verification");
    EXPECT_TRUE(request.private_key_handling == 0u, "crypto private key");
    EXPECT_TRUE(request.runtime_authority_granted == 0u, "crypto runtime");
    EXPECT_TRUE(request.host_read_performed == 0u, "crypto host read");
    EXPECT_TRUE(request.host_write_performed == 0u, "crypto host write");
    EXPECT_TRUE(request.network_performed == 0u, "crypto network");
    EXPECT_TRUE(latticra_seal_signature_request_render(&request, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "crypto render");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_gate_present=1") != 0, "render crypto present");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "render standard");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "render authority promotion");
    return 0;
}

static int request_allows_evaluate_only_metadata(void) {
    latticra_seal_report_envelope_t envelope = fixture_envelope("evaluate-only");
    latticra_seal_signature_request_t request;

    EXPECT_TRUE(
        latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK,
        "evaluate signature request status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_OK, "evaluate request ok");
    EXPECT_TRUE(strcmp(request.envelope_state, "sealed-evaluate-only") == 0, "evaluate envelope state");
    EXPECT_TRUE(request.envelope_ready == 1u, "evaluate envelope ready");
    EXPECT_TRUE(strcmp(request.signature_request_state, "requested-metadata-only") == 0, "evaluate request state");
    EXPECT_TRUE(request.signature_request_ready == 1u, "evaluate request ready");
    EXPECT_TRUE(request.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(request.verification_performed == 0u, "evaluate verification performed");
    EXPECT_TRUE(request.private_key_handling == 0u, "evaluate private key handling");
    EXPECT_TRUE(request.handoff_performed == 0u, "evaluate handoff performed");
    EXPECT_TRUE(request.effect_performed == 0u, "evaluate effect performed");
    EXPECT_TRUE(request.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(request.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(request.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(request.network_performed == 0u, "evaluate network");
    return 0;
}

static int request_fails_closed(void) {
    latticra_seal_report_envelope_t envelope = fixture_envelope("report-only");
    latticra_seal_signature_request_t request;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(0, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "null envelope status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT, "null envelope error");
    envelope.error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "invalid envelope status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE, "invalid envelope error");
    envelope = fixture_envelope("report-only");
    envelope.envelope_ready = 0u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "envelope ready status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE, "envelope ready error");
    envelope = fixture_envelope("report-only");
    (void)snprintf(envelope.envelope_state, sizeof(envelope.envelope_state), "%s", "denied-envelope");
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "envelope state status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE, "envelope state error");
    envelope = fixture_envelope("report-only");
    envelope.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY, "runtime error");
    envelope = fixture_envelope("report-only");
    envelope.signature_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "signature performed status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT, "signature performed error");
    envelope = fixture_envelope("report-only");
    envelope.handoff_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "handoff status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT, "handoff error");
    envelope = fixture_envelope("report-only");
    envelope.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT, "effect error");
    envelope = fixture_envelope("report-only");
    envelope.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT, "host read error");
    envelope = fixture_envelope("report-only");
    envelope.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT, "host write error");
    envelope = fixture_envelope("report-only");
    envelope.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT, "network error");
    envelope = fixture_crypto_bound_envelope("report-only");
    envelope.standard_expectations_met = 0u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "failed crypto gate status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE, "failed crypto gate error");
    EXPECT_TRUE(strcmp(request.signature_request_state, "denied-crypto-graduation-gate") == 0, "failed crypto gate state");
    envelope = fixture_crypto_bound_envelope("report-only");
    envelope.authority_promotion_allowed = 1u;
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", &request) == LATTICRA_STATUS_OK, "authority crypto gate status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_CRYPTO_GRADUATION_GATE, "authority crypto gate error");
    envelope = fixture_envelope("report-only");
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, 0, &request) == LATTICRA_STATUS_OK, "missing signature null status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE, "missing signature null error");
    EXPECT_TRUE(strcmp(request.signature_request_state, "denied-signature-request") == 0, "missing signature null state");
    envelope = fixture_envelope("report-only");
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "", &request) == LATTICRA_STATUS_OK, "missing signature empty status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE, "missing signature empty error");
    envelope = fixture_envelope("report-only");
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "ML-DSA-future", &request) == LATTICRA_STATUS_OK, "unknown signature status");
    EXPECT_TRUE(request.error == LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE, "unknown signature error");
    EXPECT_TRUE(strcmp(request.signature_request_state, "denied-signature-request") == 0, "unknown signature state");
    EXPECT_TRUE(latticra_seal_signature_request_from_envelope(&envelope, "Ed25519-development", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signature_request_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signature_request_render(&request, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_signature_request_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null request render");
    EXPECT_TRUE(latticra_seal_signature_request_render(&request, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");
    return 0;
}

int main(void) {
    if (request_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (request_carries_crypto_graduation_evidence() != 0) {
        return 1;
    }
    if (request_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (request_fails_closed() != 0) {
        return 1;
    }
    printf("seal signature request invariants: ok\n");
    return 0;
}
