#include "latticra/seal_runtime_handoff_report.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_runtime_handoff_evaluation_t fixture_evaluation(const char *mode) {
    latticra_seal_runtime_handoff_evaluation_t evaluation;
    memset(&evaluation, 0, sizeof(evaluation));
    (void)snprintf(evaluation.handoff_profile, sizeof(evaluation.handoff_profile), "%s", "latticra-seal-runtime-handoff-evaluation/0.1");
    (void)snprintf(evaluation.decision_profile, sizeof(evaluation.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(evaluation.gate_profile, sizeof(evaluation.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(evaluation.receipt_profile, sizeof(evaluation.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(evaluation.verify_profile, sizeof(evaluation.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(evaluation.message_digest_algorithm, sizeof(evaluation.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(evaluation.message_digest_hex, sizeof(evaluation.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(evaluation.public_key_identity_label, sizeof(evaluation.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(evaluation.crypto_graduation_gate_state, sizeof(evaluation.crypto_graduation_gate_state), "%s", "not-required");
    (void)snprintf(evaluation.requested_capability, sizeof(evaluation.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(evaluation.requested_effect, sizeof(evaluation.requested_effect), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(evaluation.requested_handoff, sizeof(evaluation.requested_handoff), "%s", mode != 0 ? mode : "report-only");
    (void)snprintf(evaluation.requested_scope, sizeof(evaluation.requested_scope), "%s", "local-fixture-scope");
    evaluation.verified = 1u;
    evaluation.authority_usable = 0u;
    evaluation.receipt_capability_gate_allowed = 0u;
    evaluation.gate_allowed = 1u;
    (void)snprintf(evaluation.gate_state, sizeof(evaluation.gate_state), "%s", "allowed-metadata-only");
    if (mode != 0 && strcmp(mode, "evaluate-only") == 0) {
        (void)snprintf(evaluation.decision_state, sizeof(evaluation.decision_state), "%s", "allowed-evaluate-only");
        (void)snprintf(evaluation.handoff_state, sizeof(evaluation.handoff_state), "%s", "eligible-evaluate-only");
    } else {
        (void)snprintf(evaluation.decision_state, sizeof(evaluation.decision_state), "%s", "allowed-report-only");
        (void)snprintf(evaluation.handoff_state, sizeof(evaluation.handoff_state), "%s", "eligible-report-only");
    }
    evaluation.effect_allowed = 1u;
    evaluation.handoff_eligible = 1u;
    evaluation.handoff_performed = 0u;
    evaluation.effect_performed = 0u;
    evaluation.runtime_authority_granted = 0u;
    evaluation.host_read_performed = 0u;
    evaluation.host_write_performed = 0u;
    evaluation.network_performed = 0u;
    evaluation.error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK;
    (void)snprintf(evaluation.status, sizeof(evaluation.status), "%s", "runtime-handoff-evaluation-metadata");
    return evaluation;
}

static latticra_seal_runtime_handoff_evaluation_t fixture_crypto_bound_evaluation(const char *mode) {
    latticra_seal_runtime_handoff_evaluation_t evaluation = fixture_evaluation(mode);
    (void)snprintf(
        evaluation.crypto_graduation_profile,
        sizeof(evaluation.crypto_graduation_profile),
        "%s",
        "latticra-seal-crypto-graduation-gate/0.1");
    (void)snprintf(
        evaluation.assurance_baseline_profile,
        sizeof(evaluation.assurance_baseline_profile),
        "%s",
        "latticra-cryptographic-assurance-key-management/0.1");
    (void)snprintf(
        evaluation.crypto_graduation_gate_state,
        sizeof(evaluation.crypto_graduation_gate_state),
        "%s",
        "graduated-authority-neutral");
    evaluation.crypto_graduation_gate_present = 1u;
    evaluation.crypto_graduation_gate_passed = 1u;
    evaluation.standard_expectations_met = 1u;
    evaluation.local_verify_graduated = 1u;
    evaluation.receipt_promotion_graduated = 1u;
    evaluation.authority_promotion_allowed = 0u;
    return evaluation;
}

static int report_allows_report_only_metadata(void) {
    latticra_seal_runtime_handoff_evaluation_t evaluation = fixture_evaluation("report-only");
    latticra_seal_runtime_handoff_report_t report;
    char rendered[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK, "report ok");
    EXPECT_TRUE(strcmp(report.report_profile, "latticra-seal-runtime-handoff-report/0.1") == 0, "report profile");
    EXPECT_TRUE(strcmp(report.handoff_profile, evaluation.handoff_profile) == 0, "handoff profile");
    EXPECT_TRUE(strcmp(report.decision_profile, evaluation.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(report.gate_profile, evaluation.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(report.receipt_profile, evaluation.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(report.verify_profile, evaluation.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(report.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(report.message_digest_hex, evaluation.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(report.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(report.crypto_graduation_gate_state, "not-required") == 0, "crypto gate legacy");
    EXPECT_TRUE(strcmp(report.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(report.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(report.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(report.requested_report, "report-only") == 0, "requested report");
    EXPECT_TRUE(strcmp(report.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(report.verified == 1u, "verified");
    EXPECT_TRUE(report.authority_usable == 0u, "authority usable");
    EXPECT_TRUE(report.receipt_capability_gate_allowed == 0u, "receipt capability flag");
    EXPECT_TRUE(report.gate_allowed == 1u, "gate allowed");
    EXPECT_TRUE(report.crypto_graduation_gate_present == 0u, "crypto present legacy");
    EXPECT_TRUE(report.standard_expectations_met == 0u, "standard legacy");
    EXPECT_TRUE(strcmp(report.gate_state, "allowed-metadata-only") == 0, "gate state");
    EXPECT_TRUE(strcmp(report.decision_state, "allowed-report-only") == 0, "decision state");
    EXPECT_TRUE(report.effect_allowed == 1u, "effect allowed");
    EXPECT_TRUE(strcmp(report.handoff_state, "eligible-report-only") == 0, "handoff state");
    EXPECT_TRUE(report.handoff_eligible == 1u, "handoff eligible");
    EXPECT_TRUE(strcmp(report.report_state, "ready-report-only") == 0, "report state");
    EXPECT_TRUE(report.report_ready == 1u, "report ready");
    EXPECT_TRUE(report.handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(report.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(report.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(report.host_read_performed == 0u, "host read");
    EXPECT_TRUE(report.host_write_performed == 0u, "host write");
    EXPECT_TRUE(report.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_is_metadata_only(&report) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_render(&report, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME HANDOFF REPORT") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "report_state=ready-report-only") != 0, "render report state");
    EXPECT_TRUE(strstr(rendered, "report_ready=1") != 0, "render ready");
    EXPECT_TRUE(strstr(rendered, "handoff_performed=0") != 0, "render handoff performed");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect performed");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    return 0;
}

static int report_carries_crypto_graduation_evidence(void) {
    latticra_seal_runtime_handoff_evaluation_t evaluation = fixture_crypto_bound_evaluation("report-only");
    latticra_seal_runtime_handoff_report_t report;
    char rendered[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_RENDER_MAX];

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK,
        "crypto report status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK, "crypto report ok");
    EXPECT_TRUE(strcmp(report.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "crypto profile");
    EXPECT_TRUE(strcmp(report.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "assurance profile");
    EXPECT_TRUE(strcmp(report.crypto_graduation_gate_state, "graduated-authority-neutral") == 0, "crypto state");
    EXPECT_TRUE(report.crypto_graduation_gate_present == 1u, "crypto present");
    EXPECT_TRUE(report.crypto_graduation_gate_passed == 1u, "crypto passed");
    EXPECT_TRUE(report.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(report.local_verify_graduated == 1u, "local verify");
    EXPECT_TRUE(report.receipt_promotion_graduated == 1u, "receipt promotion");
    EXPECT_TRUE(report.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(report.report_ready == 1u, "crypto ready");
    EXPECT_TRUE(strcmp(report.report_state, "ready-report-only") == 0, "crypto report state");
    EXPECT_TRUE(report.handoff_performed == 0u, "crypto handoff performed");
    EXPECT_TRUE(report.effect_performed == 0u, "crypto effect performed");
    EXPECT_TRUE(report.runtime_authority_granted == 0u, "crypto runtime");
    EXPECT_TRUE(report.host_read_performed == 0u, "crypto host read");
    EXPECT_TRUE(report.host_write_performed == 0u, "crypto host write");
    EXPECT_TRUE(report.network_performed == 0u, "crypto network");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_render(&report, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "crypto render");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_gate_present=1") != 0, "render crypto present");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "render standard");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "render authority promotion");
    return 0;
}

static int report_allows_evaluate_only_metadata(void) {
    latticra_seal_runtime_handoff_evaluation_t evaluation = fixture_evaluation("evaluate-only");
    latticra_seal_runtime_handoff_report_t report;

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "evaluate-only", &report) == LATTICRA_STATUS_OK,
        "evaluate report status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK, "evaluate report ok");
    EXPECT_TRUE(strcmp(report.report_state, "ready-evaluate-only") == 0, "evaluate report state");
    EXPECT_TRUE(report.report_ready == 1u, "evaluate report ready");
    EXPECT_TRUE(report.handoff_performed == 0u, "evaluate handoff performed");
    EXPECT_TRUE(report.effect_performed == 0u, "evaluate effect performed");
    EXPECT_TRUE(report.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(report.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(report.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(report.network_performed == 0u, "evaluate network");
    return 0;
}

static int report_fails_closed(void) {
    latticra_seal_runtime_handoff_evaluation_t evaluation = fixture_evaluation("report-only");
    latticra_seal_runtime_handoff_report_t report;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(0, "report-only", &report) == LATTICRA_STATUS_OK, "null evaluation status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT, "null evaluation error");
    evaluation.error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "invalid evaluation status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_EVALUATION, "invalid evaluation error");
    evaluation = fixture_evaluation("report-only");
    evaluation.handoff_eligible = 0u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "handoff flag status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF, "handoff flag error");
    evaluation = fixture_evaluation("report-only");
    (void)snprintf(evaluation.handoff_state, sizeof(evaluation.handoff_state), "%s", "denied-handoff");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "handoff state status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF, "handoff state error");
    evaluation = fixture_evaluation("report-only");
    evaluation.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_RUNTIME_AUTHORITY, "runtime error");
    evaluation = fixture_evaluation("report-only");
    evaluation.handoff_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "handoff performed status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT, "handoff performed error");
    evaluation = fixture_evaluation("report-only");
    evaluation.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT, "effect error");
    evaluation = fixture_evaluation("report-only");
    evaluation.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT, "host read error");
    evaluation = fixture_evaluation("report-only");
    evaluation.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT, "host write error");
    evaluation = fixture_evaluation("report-only");
    evaluation.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_NETWORK_EFFECT, "network error");
    evaluation = fixture_crypto_bound_evaluation("report-only");
    evaluation.standard_expectations_met = 0u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "failed crypto gate status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE, "failed crypto gate error");
    EXPECT_TRUE(strcmp(report.report_state, "denied-crypto-graduation-gate") == 0, "failed crypto gate state");
    evaluation = fixture_crypto_bound_evaluation("report-only");
    evaluation.authority_promotion_allowed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", &report) == LATTICRA_STATUS_OK, "authority crypto gate status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE, "authority crypto gate error");
    evaluation = fixture_evaluation("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, 0, &report) == LATTICRA_STATUS_OK, "missing report null status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT, "missing report null error");
    EXPECT_TRUE(strcmp(report.report_state, "denied-report") == 0, "missing report null state");
    evaluation = fixture_evaluation("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "", &report) == LATTICRA_STATUS_OK, "missing report empty status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT, "missing report empty error");
    evaluation = fixture_evaluation("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "execute-tool", &report) == LATTICRA_STATUS_OK, "unknown report status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_UNKNOWN_REPORT, "unknown report error");
    EXPECT_TRUE(strcmp(report.report_state, "denied-report") == 0, "unknown report state");
    evaluation = fixture_evaluation("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "evaluate-only", &report) == LATTICRA_STATUS_OK, "mismatch status");
    EXPECT_TRUE(report.error == LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_REPORT, "mismatch error");
    EXPECT_TRUE(strcmp(report.report_state, "denied-report") == 0, "mismatch state");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_from_evaluation(&evaluation, "report-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_render(&report, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render clear");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_render(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report render");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report_render(&report, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer render");
    return 0;
}

int main(void) {
    if (report_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (report_carries_crypto_graduation_evidence() != 0) {
        return 1;
    }
    if (report_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (report_fails_closed() != 0) {
        return 1;
    }
    printf("seal runtime handoff report invariants: ok\n");
    return 0;
}
