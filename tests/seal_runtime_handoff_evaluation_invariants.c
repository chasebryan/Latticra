#include "latticra/seal_runtime_handoff_evaluation.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_verified_effect_decision_t fixture_decision(const char *effect) {
    latticra_seal_verified_effect_decision_t decision;
    memset(&decision, 0, sizeof(decision));
    (void)snprintf(decision.decision_profile, sizeof(decision.decision_profile), "%s", "latticra-seal-verified-effect-decision/0.1");
    (void)snprintf(decision.gate_profile, sizeof(decision.gate_profile), "%s", "latticra-seal-verified-capability-gate/0.1");
    (void)snprintf(decision.receipt_profile, sizeof(decision.receipt_profile), "%s", "latticra-seal-verified-receipt/0.1");
    (void)snprintf(decision.verify_profile, sizeof(decision.verify_profile), "%s", "latticra-seal-ed25519-verify/0.1");
    (void)snprintf(decision.message_digest_algorithm, sizeof(decision.message_digest_algorithm), "%s", "SHA-256");
    (void)snprintf(decision.message_digest_hex, sizeof(decision.message_digest_hex), "%s", "aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999");
    (void)snprintf(decision.public_key_identity_label, sizeof(decision.public_key_identity_label), "%s", "rfc8032-test-key");
    (void)snprintf(decision.crypto_graduation_gate_state, sizeof(decision.crypto_graduation_gate_state), "%s", "not-required");
    (void)snprintf(decision.requested_capability, sizeof(decision.requested_capability), "%s", "verified-receipt-report");
    (void)snprintf(decision.requested_effect, sizeof(decision.requested_effect), "%s", effect != 0 ? effect : "report-only");
    (void)snprintf(decision.requested_scope, sizeof(decision.requested_scope), "%s", "local-fixture-scope");
    decision.verified = 1u;
    decision.authority_usable = 0u;
    decision.receipt_capability_gate_allowed = 0u;
    decision.gate_allowed = 1u;
    (void)snprintf(decision.gate_state, sizeof(decision.gate_state), "%s", "allowed-metadata-only");
    if (effect != 0 && strcmp(effect, "evaluate-only") == 0) {
        (void)snprintf(decision.decision_state, sizeof(decision.decision_state), "%s", "allowed-evaluate-only");
    } else {
        (void)snprintf(decision.decision_state, sizeof(decision.decision_state), "%s", "allowed-report-only");
    }
    decision.effect_allowed = 1u;
    decision.effect_performed = 0u;
    decision.runtime_authority_granted = 0u;
    decision.host_read_performed = 0u;
    decision.host_write_performed = 0u;
    decision.network_performed = 0u;
    decision.error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK;
    (void)snprintf(decision.status, sizeof(decision.status), "%s", "verified-effect-decision-metadata");
    return decision;
}

static latticra_seal_verified_effect_decision_t fixture_crypto_bound_decision(const char *effect) {
    latticra_seal_verified_effect_decision_t decision = fixture_decision(effect);
    (void)snprintf(
        decision.crypto_graduation_profile,
        sizeof(decision.crypto_graduation_profile),
        "%s",
        "latticra-seal-crypto-graduation-gate/0.1");
    (void)snprintf(
        decision.assurance_baseline_profile,
        sizeof(decision.assurance_baseline_profile),
        "%s",
        "latticra-cryptographic-assurance-key-management/0.1");
    (void)snprintf(
        decision.crypto_graduation_gate_state,
        sizeof(decision.crypto_graduation_gate_state),
        "%s",
        "graduated-authority-neutral");
    decision.crypto_graduation_gate_present = 1u;
    decision.crypto_graduation_gate_passed = 1u;
    decision.standard_expectations_met = 1u;
    decision.local_verify_graduated = 1u;
    decision.receipt_promotion_graduated = 1u;
    decision.authority_promotion_allowed = 0u;
    return decision;
}

static int evaluation_allows_report_only_metadata(void) {
    latticra_seal_verified_effect_decision_t decision = fixture_decision("report-only");
    latticra_seal_runtime_handoff_evaluation_t evaluation;
    char rendered[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK,
        "report handoff status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK, "report handoff ok");
    EXPECT_TRUE(strcmp(evaluation.handoff_profile, "latticra-seal-runtime-handoff-evaluation/0.1") == 0, "handoff profile");
    EXPECT_TRUE(strcmp(evaluation.decision_profile, decision.decision_profile) == 0, "decision profile");
    EXPECT_TRUE(strcmp(evaluation.gate_profile, decision.gate_profile) == 0, "gate profile");
    EXPECT_TRUE(strcmp(evaluation.receipt_profile, decision.receipt_profile) == 0, "receipt profile");
    EXPECT_TRUE(strcmp(evaluation.verify_profile, decision.verify_profile) == 0, "verify profile");
    EXPECT_TRUE(strcmp(evaluation.message_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(evaluation.message_digest_hex, decision.message_digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(evaluation.public_key_identity_label, "rfc8032-test-key") == 0, "public key identity");
    EXPECT_TRUE(strcmp(evaluation.crypto_graduation_gate_state, "not-required") == 0, "crypto gate legacy");
    EXPECT_TRUE(strcmp(evaluation.requested_capability, "verified-receipt-report") == 0, "requested capability");
    EXPECT_TRUE(strcmp(evaluation.requested_effect, "report-only") == 0, "requested effect");
    EXPECT_TRUE(strcmp(evaluation.requested_handoff, "report-only") == 0, "requested handoff");
    EXPECT_TRUE(strcmp(evaluation.requested_scope, "local-fixture-scope") == 0, "requested scope");
    EXPECT_TRUE(evaluation.verified == 1u, "verified");
    EXPECT_TRUE(evaluation.authority_usable == 0u, "authority usable");
    EXPECT_TRUE(evaluation.receipt_capability_gate_allowed == 0u, "receipt capability flag");
    EXPECT_TRUE(evaluation.gate_allowed == 1u, "gate allowed");
    EXPECT_TRUE(evaluation.crypto_graduation_gate_present == 0u, "crypto present legacy");
    EXPECT_TRUE(evaluation.standard_expectations_met == 0u, "standard legacy");
    EXPECT_TRUE(strcmp(evaluation.gate_state, "allowed-metadata-only") == 0, "gate state");
    EXPECT_TRUE(strcmp(evaluation.decision_state, "allowed-report-only") == 0, "decision state");
    EXPECT_TRUE(evaluation.effect_allowed == 1u, "effect allowed");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "eligible-report-only") == 0, "handoff state");
    EXPECT_TRUE(evaluation.handoff_eligible == 1u, "handoff eligible");
    EXPECT_TRUE(evaluation.handoff_performed == 0u, "handoff performed");
    EXPECT_TRUE(evaluation.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(evaluation.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(evaluation.host_read_performed == 0u, "host read");
    EXPECT_TRUE(evaluation.host_write_performed == 0u, "host write");
    EXPECT_TRUE(evaluation.network_performed == 0u, "network");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_is_metadata_only(&evaluation) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_report(&evaluation, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "report render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME HANDOFF EVALUATION") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "handoff_state=eligible-report-only") != 0, "report handoff");
    EXPECT_TRUE(strstr(rendered, "handoff_eligible=1") != 0, "report eligible");
    EXPECT_TRUE(strstr(rendered, "handoff_performed=0") != 0, "report handoff performed");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "report effect performed");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "report host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "report host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "report network");
    return 0;
}

static int evaluation_carries_crypto_graduation_evidence(void) {
    latticra_seal_verified_effect_decision_t decision = fixture_crypto_bound_decision("report-only");
    latticra_seal_runtime_handoff_evaluation_t evaluation;
    char rendered[LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK,
        "crypto handoff status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK, "crypto handoff ok");
    EXPECT_TRUE(strcmp(evaluation.crypto_graduation_profile, "latticra-seal-crypto-graduation-gate/0.1") == 0, "crypto profile");
    EXPECT_TRUE(strcmp(evaluation.assurance_baseline_profile, "latticra-cryptographic-assurance-key-management/0.1") == 0, "assurance profile");
    EXPECT_TRUE(strcmp(evaluation.crypto_graduation_gate_state, "graduated-authority-neutral") == 0, "crypto state");
    EXPECT_TRUE(evaluation.crypto_graduation_gate_present == 1u, "crypto present");
    EXPECT_TRUE(evaluation.crypto_graduation_gate_passed == 1u, "crypto passed");
    EXPECT_TRUE(evaluation.standard_expectations_met == 1u, "standards");
    EXPECT_TRUE(evaluation.local_verify_graduated == 1u, "local verify");
    EXPECT_TRUE(evaluation.receipt_promotion_graduated == 1u, "receipt promotion");
    EXPECT_TRUE(evaluation.authority_promotion_allowed == 0u, "authority promotion");
    EXPECT_TRUE(evaluation.handoff_eligible == 1u, "crypto eligible");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "eligible-report-only") == 0, "crypto handoff state");
    EXPECT_TRUE(evaluation.handoff_performed == 0u, "crypto handoff performed");
    EXPECT_TRUE(evaluation.effect_performed == 0u, "crypto effect performed");
    EXPECT_TRUE(evaluation.runtime_authority_granted == 0u, "crypto runtime");
    EXPECT_TRUE(evaluation.host_read_performed == 0u, "crypto host read");
    EXPECT_TRUE(evaluation.host_write_performed == 0u, "crypto host write");
    EXPECT_TRUE(evaluation.network_performed == 0u, "crypto network");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_report(&evaluation, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "crypto report");
    EXPECT_TRUE(strstr(rendered, "crypto_graduation_gate_present=1") != 0, "report crypto present");
    EXPECT_TRUE(strstr(rendered, "standard_expectations_met=1") != 0, "report standard");
    EXPECT_TRUE(strstr(rendered, "authority_promotion_allowed=0") != 0, "report authority promotion");
    return 0;
}

static int evaluation_allows_evaluate_only_metadata(void) {
    latticra_seal_verified_effect_decision_t decision = fixture_decision("evaluate-only");
    latticra_seal_runtime_handoff_evaluation_t evaluation;

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "evaluate-only", &evaluation) == LATTICRA_STATUS_OK,
        "evaluate handoff status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK, "evaluate handoff ok");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "eligible-evaluate-only") == 0, "evaluate handoff state");
    EXPECT_TRUE(evaluation.handoff_eligible == 1u, "evaluate handoff eligible");
    EXPECT_TRUE(evaluation.handoff_performed == 0u, "evaluate handoff performed");
    EXPECT_TRUE(evaluation.effect_performed == 0u, "evaluate effect performed");
    EXPECT_TRUE(evaluation.runtime_authority_granted == 0u, "evaluate runtime");
    EXPECT_TRUE(evaluation.host_read_performed == 0u, "evaluate host read");
    EXPECT_TRUE(evaluation.host_write_performed == 0u, "evaluate host write");
    EXPECT_TRUE(evaluation.network_performed == 0u, "evaluate network");
    return 0;
}

static int evaluation_fails_closed(void) {
    latticra_seal_verified_effect_decision_t decision = fixture_decision("report-only");
    latticra_seal_runtime_handoff_evaluation_t evaluation;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(0, "report-only", &evaluation) == LATTICRA_STATUS_OK, "null decision status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT, "null decision error");
    decision.error = LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "invalid decision status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION, "invalid decision error");
    decision = fixture_decision("report-only");
    decision.effect_allowed = 0u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "denied effect flag status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT, "denied effect flag error");
    decision = fixture_decision("report-only");
    (void)snprintf(decision.decision_state, sizeof(decision.decision_state), "%s", "denied-effect");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "denied decision status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION, "denied decision error");
    decision = fixture_decision("report-only");
    decision.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "runtime status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY, "runtime error");
    decision = fixture_decision("report-only");
    decision.effect_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "effect status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT, "effect error");
    decision = fixture_decision("report-only");
    decision.host_read_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "host read status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT, "host read error");
    decision = fixture_decision("report-only");
    decision.host_write_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "host write status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT, "host write error");
    decision = fixture_decision("report-only");
    decision.network_performed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "network status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT, "network error");
    decision = fixture_crypto_bound_decision("report-only");
    decision.standard_expectations_met = 0u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "failed crypto gate status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE, "failed crypto gate error");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "denied-crypto-graduation-gate") == 0, "failed crypto gate state");
    decision = fixture_crypto_bound_decision("report-only");
    decision.authority_promotion_allowed = 1u;
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", &evaluation) == LATTICRA_STATUS_OK, "authority crypto gate status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_CRYPTO_GRADUATION_GATE, "authority crypto gate error");
    decision = fixture_decision("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, 0, &evaluation) == LATTICRA_STATUS_OK, "missing handoff null status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF, "missing handoff null error");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "denied-effect") == 0, "missing handoff null state");
    decision = fixture_decision("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "", &evaluation) == LATTICRA_STATUS_OK, "missing handoff empty status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF, "missing handoff empty error");
    decision = fixture_decision("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "execute-tool", &evaluation) == LATTICRA_STATUS_OK, "unknown handoff status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF, "unknown handoff error");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "denied-effect") == 0, "unknown handoff state");
    decision = fixture_decision("report-only");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "evaluate-only", &evaluation) == LATTICRA_STATUS_OK, "mismatch status");
    EXPECT_TRUE(evaluation.error == LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT, "mismatch error");
    EXPECT_TRUE(strcmp(evaluation.handoff_state, "denied-effect") == 0, "mismatch state");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_from_decision(&decision, "report-only", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_report(&evaluation, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null evaluation report");
    EXPECT_TRUE(latticra_seal_runtime_handoff_evaluation_report(&evaluation, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer report");
    return 0;
}

int main(void) {
    if (evaluation_allows_report_only_metadata() != 0) {
        return 1;
    }
    if (evaluation_carries_crypto_graduation_evidence() != 0) {
        return 1;
    }
    if (evaluation_allows_evaluate_only_metadata() != 0) {
        return 1;
    }
    if (evaluation_fails_closed() != 0) {
        return 1;
    }
    printf("seal runtime handoff evaluation invariants: ok\n");
    return 0;
}
