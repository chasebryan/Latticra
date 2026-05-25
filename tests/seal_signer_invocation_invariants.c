#include "latticra/seal_signer_invocation.h"

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

static latticra_seal_signer_handoff_t fixture_handoff(const char *mode) {
    latticra_seal_signer_handoff_t handoff;
    const char *requested_mode = mode != 0 ? mode : "report-only";

    memset(&handoff, 0, sizeof(handoff));
    set_string(handoff.signer_handoff_profile, sizeof(handoff.signer_handoff_profile), "latticra-seal-signer-handoff/0.1");
    set_string(
        handoff.signing_authorization_profile,
        sizeof(handoff.signing_authorization_profile),
        "latticra-seal-signing-authorization/0.1");
    set_string(handoff.signature_request_profile, sizeof(handoff.signature_request_profile), "latticra-seal-signature-request/0.1");
    set_string(handoff.envelope_profile, sizeof(handoff.envelope_profile), "latticra-seal-report-envelope/0.1");
    set_string(handoff.report_profile, sizeof(handoff.report_profile), "latticra-seal-runtime-handoff-report/0.1");
    set_string(handoff.handoff_profile, sizeof(handoff.handoff_profile), "latticra-seal-runtime-handoff-evaluation/0.1");
    set_string(handoff.decision_profile, sizeof(handoff.decision_profile), "latticra-seal-verified-effect-decision/0.1");
    set_string(handoff.gate_profile, sizeof(handoff.gate_profile), "latticra-seal-verified-capability-gate/0.1");
    set_string(handoff.receipt_profile, sizeof(handoff.receipt_profile), "latticra-seal-verified-receipt/0.1");
    set_string(handoff.verify_profile, sizeof(handoff.verify_profile), "latticra-seal-ed25519-verify/0.1");
    set_string(handoff.message_digest_algorithm, sizeof(handoff.message_digest_algorithm), "SHA-256");
    set_string(
        handoff.message_digest_hex,
        sizeof(handoff.message_digest_hex),
        "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    set_string(handoff.public_key_identity_label, sizeof(handoff.public_key_identity_label), "rfc8032-test-key");
    set_string(handoff.requested_capability, sizeof(handoff.requested_capability), "verified-receipt-report");
    set_string(handoff.requested_effect, sizeof(handoff.requested_effect), requested_mode);
    set_string(handoff.requested_handoff, sizeof(handoff.requested_handoff), requested_mode);
    set_string(handoff.requested_report, sizeof(handoff.requested_report), requested_mode);
    set_string(handoff.requested_envelope, sizeof(handoff.requested_envelope), requested_mode);
    set_string(handoff.requested_signature, sizeof(handoff.requested_signature), "Ed25519-development");
    set_string(handoff.requested_signing_authorization, sizeof(handoff.requested_signing_authorization), "metadata-only");
    set_string(handoff.requested_signer_handoff, sizeof(handoff.requested_signer_handoff), "metadata-only");
    set_string(handoff.requested_scope, sizeof(handoff.requested_scope), "local-fixture-scope");
    set_string(handoff.signature_request_state, sizeof(handoff.signature_request_state), "requested-metadata-only");
    handoff.signature_request_ready = 1u;
    set_string(handoff.signing_authorization_state, sizeof(handoff.signing_authorization_state), "authorized-metadata-only");
    handoff.signing_authorization_ready = 1u;
    set_string(handoff.signer_handoff_state, sizeof(handoff.signer_handoff_state), "handoff-metadata-only");
    handoff.signer_handoff_ready = 1u;
    handoff.signature_performed = 0u;
    handoff.verification_performed = 0u;
    handoff.signer_invoked = 0u;
    handoff.private_key_handling = 0u;
    handoff.key_generation_performed = 0u;
    handoff.trust_store_loaded = 0u;
    handoff.revocation_lookup_performed = 0u;
    handoff.handoff_performed = 0u;
    handoff.effect_performed = 0u;
    handoff.runtime_authority_granted = 0u;
    handoff.host_read_performed = 0u;
    handoff.host_write_performed = 0u;
    handoff.network_performed = 0u;
    set_string(handoff.mode, sizeof(handoff.mode), "metadata-only");
    handoff.error = LATTICRA_SEAL_SIGNER_HANDOFF_OK;
    set_string(handoff.status, sizeof(handoff.status), "signer-handoff-metadata");
    return handoff;
}

static int expect_denial(
    latticra_seal_signer_handoff_t *handoff,
    const char *requested_signer_invocation,
    latticra_seal_signer_invocation_error_t expected_error,
    const char *expected_state,
    const char *expected_status,
    const char *message) {
    latticra_seal_signer_invocation_t invocation;

    EXPECT_TRUE(
        latticra_seal_signer_invocation_from_handoff(handoff, requested_signer_invocation, &invocation) ==
            LATTICRA_STATUS_OK,
        message);
    EXPECT_TRUE(invocation.error == expected_error, "expected denial error");
    EXPECT_TRUE(strcmp(invocation.signer_invocation_state, expected_state) == 0, "expected denial state");
    EXPECT_TRUE(strcmp(invocation.status, expected_status) == 0, "expected denial status");
    EXPECT_TRUE(invocation.signer_invocation_ready == 0u, "denial ready");
    return 0;
}

static int invocation_allows_report_only_metadata(void) {
    latticra_seal_signer_handoff_t handoff = fixture_handoff("report-only");
    latticra_seal_signer_invocation_t invocation;
    char rendered[LATTICRA_SEAL_SIGNER_INVOCATION_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_signer_invocation_from_handoff(&handoff, "metadata-only", &invocation) == LATTICRA_STATUS_OK,
        "invocation status");
    EXPECT_TRUE(invocation.error == LATTICRA_SEAL_SIGNER_INVOCATION_OK, "invocation ok");
    EXPECT_TRUE(strcmp(invocation.signer_invocation_profile, "latticra-seal-signer-invocation/0.1") == 0, "invocation profile");
    EXPECT_TRUE(strcmp(invocation.signer_handoff_profile, handoff.signer_handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(invocation.signing_authorization_profile, handoff.signing_authorization_profile) == 0, "authorization profile");
    EXPECT_TRUE(strcmp(invocation.signature_request_profile, handoff.signature_request_profile) == 0, "request profile");
    EXPECT_TRUE(strcmp(invocation.envelope_profile, handoff.envelope_profile) == 0, "envelope profile");
    EXPECT_TRUE(strcmp(invocation.report_profile, handoff.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(invocation.handoff_profile, handoff.handoff_profile) == 0, "handoff predecessor profile");
    EXPECT_TRUE(strcmp(invocation.decision_profile, handoff.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(invocation.gate_profile, handoff.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(invocation.receipt_profile, handoff.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(invocation.verify_profile, handoff.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(invocation.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(invocation.message_digest_hex, handoff.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(invocation.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(invocation.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(invocation.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(invocation.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(invocation.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(invocation.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(invocation.requested_signature, "Ed25519-development") == 0, "requested signature");
    EXPECT_TRUE(strcmp(invocation.requested_signing_authorization, "metadata-only") == 0, "requested authorization");
    EXPECT_TRUE(strcmp(invocation.requested_signer_handoff, "metadata-only") == 0, "requested signer handoff");
    EXPECT_TRUE(strcmp(invocation.requested_signer_invocation, "metadata-only") == 0, "requested signer invocation");
    EXPECT_TRUE(strcmp(invocation.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(invocation.signing_authorization_state, "authorized-metadata-only") == 0, "authorization state");
    EXPECT_TRUE(invocation.signing_authorization_ready == 1u, "authorization ready");
    EXPECT_TRUE(strcmp(invocation.signer_handoff_state, "handoff-metadata-only") == 0, "handoff state");
    EXPECT_TRUE(invocation.signer_handoff_ready == 1u, "handoff ready");
    EXPECT_TRUE(strcmp(invocation.signer_invocation_state, "invocation-metadata-only") == 0, "invocation state");
    EXPECT_TRUE(invocation.signer_invocation_ready == 1u, "invocation ready");
    EXPECT_TRUE(invocation.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(invocation.verification_performed == 0u, "verification performed");
    EXPECT_TRUE(invocation.signer_invoked == 0u, "signer invoked");
    EXPECT_TRUE(invocation.private_key_handling == 0u, "private key handling");
    EXPECT_TRUE(invocation.key_generation_performed == 0u, "key generation");
    EXPECT_TRUE(invocation.trust_store_loaded == 0u, "trust store");
    EXPECT_TRUE(invocation.revocation_lookup_performed == 0u, "revocation lookup");
    EXPECT_TRUE(invocation.handoff_performed == 0u, "runtime handoff performed");
    EXPECT_TRUE(invocation.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(invocation.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(invocation.host_read_performed == 0u, "host read");
    EXPECT_TRUE(invocation.host_write_performed == 0u, "host write");
    EXPECT_TRUE(invocation.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(invocation.mode, "metadata-only") == 0, "mode");
    EXPECT_TRUE(strcmp(invocation.status, "signer-invocation-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_signer_invocation_is_metadata_only(&invocation) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_signer_invocation_render(&invocation, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNER INVOCATION") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "requested_signer_invocation=metadata-only") != 0, "render requested invocation");
    EXPECT_TRUE(strstr(rendered, "signer_invocation_state=invocation-metadata-only") != 0, "render state");
    EXPECT_TRUE(strstr(rendered, "signer_invocation_ready=1") != 0, "render ready");
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

static int invocation_allows_evaluate_only_metadata(void) {
    latticra_seal_signer_handoff_t handoff = fixture_handoff("evaluate-only");
    latticra_seal_signer_invocation_t invocation;

    EXPECT_TRUE(
        latticra_seal_signer_invocation_from_handoff(&handoff, "metadata-only", &invocation) == LATTICRA_STATUS_OK,
        "evaluate invocation status");
    EXPECT_TRUE(invocation.error == LATTICRA_SEAL_SIGNER_INVOCATION_OK, "evaluate invocation ok");
    EXPECT_TRUE(strcmp(invocation.requested_effect, "evaluate-only") == 0, "evaluate requested effect");
    EXPECT_TRUE(strcmp(invocation.requested_handoff, "evaluate-only") == 0, "evaluate requested handoff");
    EXPECT_TRUE(strcmp(invocation.requested_report, "evaluate-only") == 0, "evaluate requested report");
    EXPECT_TRUE(strcmp(invocation.requested_envelope, "evaluate-only") == 0, "evaluate requested envelope");
    EXPECT_TRUE(strcmp(invocation.signer_invocation_state, "invocation-metadata-only") == 0, "evaluate invocation state");
    EXPECT_TRUE(invocation.signer_invocation_ready == 1u, "evaluate invocation ready");
    EXPECT_TRUE(invocation.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(invocation.verification_performed == 0u, "evaluate verification performed");
    EXPECT_TRUE(invocation.signer_invoked == 0u, "evaluate signer invoked");
    EXPECT_TRUE(invocation.private_key_handling == 0u, "evaluate private key handling");
    EXPECT_TRUE(invocation.key_generation_performed == 0u, "evaluate key generation");
    EXPECT_TRUE(invocation.trust_store_loaded == 0u, "evaluate trust store");
    EXPECT_TRUE(invocation.revocation_lookup_performed == 0u, "evaluate revocation");
    EXPECT_TRUE(invocation.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(invocation.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(invocation.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(invocation.network_performed == 0u, "evaluate network");
    return 0;
}

static int invocation_fails_closed(void) {
    latticra_seal_signer_handoff_t handoff = fixture_handoff("report-only");
    latticra_seal_signer_invocation_t invocation;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_signer_invocation_from_handoff(0, "metadata-only", &invocation) == LATTICRA_STATUS_OK, "null handoff status");
    EXPECT_TRUE(invocation.error == LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT, "null handoff error");
    EXPECT_TRUE(strcmp(invocation.signer_invocation_state, "denied-signer-handoff") == 0, "null handoff state");
    handoff.error = LATTICRA_SEAL_SIGNER_HANDOFF_DENIED_SIGNATURE_ALGORITHM;
    if (expect_denial(
            &handoff,
            "metadata-only",
            LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF,
            "denied-signer-handoff",
            "invalid-signer-handoff",
            "invalid handoff status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.signer_handoff_ready = 0u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff ready status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    set_string(handoff.signer_handoff_state, sizeof(handoff.signer_handoff_state), "denied-signer-handoff");
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff state status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    set_string(handoff.requested_signer_handoff, sizeof(handoff.requested_signer_handoff), "invoke-signer");
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF, "denied-signer-handoff", "denied-signer-handoff", "handoff request status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.signing_authorization_ready = 0u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization ready status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    set_string(handoff.signing_authorization_state, sizeof(handoff.signing_authorization_state), "denied-signature-request");
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization state status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    set_string(handoff.requested_signing_authorization, sizeof(handoff.requested_signing_authorization), "real-signing");
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION, "denied-signing-authorization", "denied-signing-authorization", "authorization mode status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.requested_signature[0] = '\0';
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "missing signature status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    set_string(handoff.requested_signature, sizeof(handoff.requested_signature), "ML-DSA-future");
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM, "denied-signature-algorithm", "denied-signature-algorithm", "unknown signature status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    if (expect_denial(&handoff, 0, LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "missing-requested-signer-invocation", "missing invocation null status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    if (expect_denial(&handoff, "", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "missing-requested-signer-invocation", "missing invocation empty status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    if (expect_denial(&handoff, "spawn-signer", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION, "denied-signer-invocation", "denied-signer-invocation", "unknown invocation status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.private_key_handling = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "private key status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.key_generation_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "key generation status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.trust_store_loaded = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY, "denied-private-key", "denied-private-key", "trust store status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.revocation_lookup_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "revocation status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.network_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT, "denied-network-effect", "denied-network-effect", "network status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.runtime_authority_granted = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY, "denied-runtime-authority", "denied-runtime-authority", "runtime status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.signature_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signature performed status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.verification_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "verification status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.signer_invoked = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "signer invoked status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.handoff_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "handoff performed status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.effect_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "effect status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.host_read_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host read status") != 0) {
        return 1;
    }
    handoff = fixture_handoff("report-only");
    handoff.host_write_performed = 1u;
    if (expect_denial(&handoff, "metadata-only", LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT, "denied-host-effect", "denied-host-effect", "host write status") != 0) {
        return 1;
    }
    EXPECT_TRUE(latticra_seal_signer_invocation_from_handoff(&handoff, "metadata-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signer_invocation_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signer_invocation_render(&invocation, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_signer_invocation_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null invocation render");
    EXPECT_TRUE(latticra_seal_signer_invocation_render(&invocation, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");
    return 0;
}

int main(void) {
    if (invocation_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (invocation_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (invocation_fails_closed() != 0) {
        return 1;
    }
    printf("seal signer invocation invariants: ok\n");
    return 0;
}
