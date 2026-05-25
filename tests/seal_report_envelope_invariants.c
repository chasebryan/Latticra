#include "latticra/seal_report_envelope.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_runtime_handoff_report_t fixture_report(const char *mode) {
    latticra_seal_runtime_handoff_report_t report;
    memset(&report, 0, sizeof(report));
    (void)snprintf(report.report_profile, sizeof(report.report_profile), "%s", "latticra-seal-runtime-handoff-report/0.1");
    (void)snprintf(report.handoff_profile, sizeof(report.handoff_profile), "%s", "latticra-seal-runtime-handoff-evaluation/0.1");
    (void)snprintf(report.decision_profile, sizeof(report.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(report.gate_profile, sizeof(report.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(report.receipt_profile, sizeof(report.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(report.verify_profile, sizeof(report.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(report.message_digest_algorithm, sizeof(report.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(report.message_digest_hex, sizeof(report.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(report.public_key_identity_label, sizeof(report.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(report.requested_capability, sizeof(report.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(report.requested_effect, sizeof(report.requested_effect), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(report.requested_handoff, sizeof(report.requested_handoff), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(report.requested_report, sizeof(report.requested_report), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(report.requested_scope, sizeof(report.requested_scope), "%s", "local-fixture-scope");
    report.verified = 1u;
    report.authority_usable = 0u;
    report.receipt_capability_gate_allowed = 0u;
    report.gate_allowed = 1u;
    (void)snprintf(report.gate_state, sizeof(report.gate_state), "%s", "allowed-metadata-only");
    if (mode != 0 && strcmp(mode, "evaluate-only") == 0) {
        (void)snprintf(report.decision_state, sizeof(report.decision_state), "%s", "allowed-evaluate-only");
        (void)snprintf(report.handoff_state, sizeof(report.handoff_state), "%s", "eligible-evaluate-only");
        (void)snprintf(report.report_state, sizeof(report.report_state), "%s", "ready-evaluate-only");
    } else {
        (void)snprintf(report.decision_state, sizeof(report.decision_state), "%s", "allowed-report-only");
        (void)snprintf(report.handoff_state, sizeof(report.handoff_state), "%s", "eligible-report-only");
        (void)snprintf(report.report_state, sizeof(report.report_state), "%s", "ready-report-only");
    }
    report.effect_allowed = 1u;
    report.handoff_eligible = 1u;
    report.report_ready = 1u;
    report.handoff_performed = 0u;
    report.effect_performed = 0u;
    report.runtime_authority_granted = 0u;
    report.host_read_performed = 0u;
    report.host_write_performed = 0u;
    report.network_performed = 0u;
    report.error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK;
    (void)snprintf(report.status, sizeof(report.status), "%s", "runtime-handoff-report-metadata");
    return report;
}

static int envelope_allows_report_only_metadata(void) {
    latticra_seal_runtime_handoff_report_t report = fixture_report("report-only");
    latticra_seal_report_envelope_t envelope;
    char rendered[LATTICRA_SEAL_REPORT_ENVELOPE_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK,
        "envelope status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_OK, "envelope ok");
    EXPECT_TRUE(strcmp(envelope.envelope_profile, "latticra-seal-report-envelope/0.1") == 0, "envelope profile");
    EXPECT_TRUE(strcmp(envelope.report_profile, report.report_profile) == 0, "report profile");
    EXPECT_TRUE(strcmp(envelope.handoff_profile, report.handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(envelope.decision_profile, report.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(envelope.gate_profile, report.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(envelope.receipt_profile, report.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(envelope.verify_profile, report.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(envelope.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(envelope.message_digest_hex, report.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(envelope.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(envelope.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(envelope.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(envelope.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(envelope.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(envelope.requested_envelope, "report-only") == 0, "requested envelope");
    EXPECT_TRUE(strcmp(envelope.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(strcmp(envelope.report_state, "ready-report-only") == 0, "report state");
    EXPECT_TRUE(envelope.report_ready == 1u, "report ready");
    EXPECT_TRUE(strcmp(envelope.envelope_state, "sealed-report-only") == 0, "envelope state");
    EXPECT_TRUE(envelope.envelope_ready == 1u, "envelope ready");
    EXPECT_TRUE(envelope.signature_performed == 0u, "signature performed");
    EXPECT_TRUE(envelope.handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(envelope.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(envelope.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(envelope.host_read_performed == 0u, "host read");
    EXPECT_TRUE(envelope.host_write_performed == 0u, "host write");
    EXPECT_TRUE(envelope.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_report_envelope_is_metadata_only(&envelope) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_report_envelope_render(&envelope, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL REPORT ENVELOPE") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "envelope_state=sealed-report-only") != 0, "render envelope state");
    EXPECT_TRUE(strstr(rendered, "envelope_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "signature_performed=0") != 0, "render signature performed");
    EXPECT_TRUE(strstr(rendered, "handoff_performed=0") != 0, "render handoff performed");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect performed");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    return 0;
}

static int envelope_allows_evaluate_only_metadata(void) {
    latticra_seal_runtime_handoff_report_t report = fixture_report("evaluate-only");
    latticra_seal_report_envelope_t envelope;

    EXPECT_TRUE(
        latticra_seal_report_envelope_from_report(&report, "evaluate-only", &envelope) == LATTICRA_STATUS_OK,
        "evaluate envelope status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_OK, "evaluate envelope ok");
    EXPECT_TRUE(strcmp(envelope.report_state, "ready-evaluate-only") == 0, "evaluate report state");
    EXPECT_TRUE(envelope.report_ready == 1u, "evaluate report ready");
    EXPECT_TRUE(strcmp(envelope.envelope_state, "sealed-evaluate-only") == 0, "evaluate envelope state");
    EXPECT_TRUE(envelope.envelope_ready == 1u, "evaluate envelope ready");
    EXPECT_TRUE(envelope.signature_performed == 0u, "evaluate signature performed");
    EXPECT_TRUE(envelope.handoff_performed == 0u, "evaluate handoff performed");
    EXPECT_TRUE(envelope.effect_performed == 0u, "evaluate effect performed");
    EXPECT_TRUE(envelope.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(envelope.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(envelope.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(envelope.network_performed == 0u, "evaluate network");
    return 0;
}

static int envelope_fails_closed(void) {
    latticra_seal_runtime_handoff_report_t report = fixture_report("report-only");
    latticra_seal_report_envelope_t envelope;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_report_envelope_from_report(0, "report-only", &envelope) == LATTICRA_STATUS_OK, "null report status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT, "null report error");
    report.error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "invalid report status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT, "invalid report error");
    report = fixture_report("report-only");
    report.report_ready = 0u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "report ready status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT, "report ready error");
    report = fixture_report("report-only");
    (void)snprintf(report.report_state, sizeof(report.report_state), "%s", "denied-report");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "report state status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT, "report state error");
    report = fixture_report("report-only");
    report.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY, "runtime error");
    report = fixture_report("report-only");
    report.handoff_performed = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "handoff status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT, "handoff error");
    report = fixture_report("report-only");
    report.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT, "effect error");
    report = fixture_report("report-only");
    report.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT, "host read error");
    report = fixture_report("report-only");
    report.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT, "host write error");
    report = fixture_report("report-only");
    report.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", &envelope) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT, "network error");
    report = fixture_report("report-only");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, 0, &envelope) == LATTICRA_STATUS_OK, "missing envelope null status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE, "missing envelope null error");
    EXPECT_TRUE(strcmp(envelope.envelope_state, "denied-envelope") == 0, "missing envelope null state");
    report = fixture_report("report-only");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "", &envelope) == LATTICRA_STATUS_OK, "missing envelope empty status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE, "missing envelope empty error");
    report = fixture_report("report-only");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "sign-now", &envelope) == LATTICRA_STATUS_OK, "unknown envelope status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE, "unknown envelope error");
    EXPECT_TRUE(strcmp(envelope.envelope_state, "denied-envelope") == 0, "unknown envelope state");
    report = fixture_report("report-only");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "evaluate-only", &envelope) == LATTICRA_STATUS_OK, "mismatch status");
    EXPECT_TRUE(envelope.error == LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE, "mismatch error");
    EXPECT_TRUE(strcmp(envelope.envelope_state, "denied-envelope") == 0, "mismatch state");
    EXPECT_TRUE(latticra_seal_report_envelope_from_report(&report, "report-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_report_envelope_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_report_envelope_render(&envelope, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_report_envelope_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null envelope render");
    EXPECT_TRUE(latticra_seal_report_envelope_render(&envelope, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");
    return 0;
}

int main(void) {
    if (envelope_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (envelope_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (envelope_fails_closed() != 0) {
        return 1;
    }
    printf("seal report envelope invariants: ok\n");
    return 0;
}
