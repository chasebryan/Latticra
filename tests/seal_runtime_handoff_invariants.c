#include "latticra/seal_runtime_handoff.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_effect_decision_t fixture_decision(void) {
    latticra_seal_effect_decision_t decision;
    memset(&decision, 0, sizeof(decision));
    (void)snprintf(decision.decision_profile, sizeof(decision.decision_profile), "%s", "latticra-seal-effect-decision/0.1");
    (void)snprintf(decision.gate_profile, sizeof(decision.gate_profile), "%s", "latticra-seal-capability-gate/0.1");
    (void)snprintf(decision.requested_capability, sizeof(decision.requested_capability), "%s", "seal.inspect");
    (void)snprintf(decision.requested_effect, sizeof(decision.requested_effect), "%s", "read-metadata");
    (void)snprintf(decision.requested_scope, sizeof(decision.requested_scope), "%s", "local-artifact");
    (void)snprintf(decision.decision_state, sizeof(decision.decision_state), "%s", "denied-gate");
    decision.gate_allowed = 0u;
    decision.effect_allowed = 0u;
    decision.effect_performed = 0u;
    decision.host_read_performed = 0u;
    decision.host_write_performed = 0u;
    decision.network_performed = 0u;
    decision.runtime_authority_granted = 0u;
    decision.error = LATTICRA_SEAL_EFFECT_DECISION_OK;
    (void)snprintf(decision.status, sizeof(decision.status), "%s", "effect-decision-denied-metadata");
    return decision;
}

static int handoff_copies_decision_metadata_and_stays_inactive(void) {
    latticra_seal_effect_decision_t decision = fixture_decision();
    latticra_seal_runtime_handoff_t handoff;
    char rendered[LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_runtime_handoff_from_decision(&decision, "runtime.preview", &handoff) == LATTICRA_STATUS_OK,
        "handoff status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_OK, "handoff ok");
    EXPECT_TRUE(strcmp(handoff.handoff_profile, "latticra-seal-runtime-handoff/0.1") == 0, "handoff profile");
    EXPECT_TRUE(strcmp(handoff.decision_profile, "latticra-seal-effect-decision/0.1") == 0, "decision profile");
    EXPECT_TRUE(strcmp(handoff.gate_profile, "latticra-seal-capability-gate/0.1") == 0, "gate profile");
    EXPECT_TRUE(strcmp(handoff.requested_capability, "seal.inspect") == 0, "requested capability");
    EXPECT_TRUE(strcmp(handoff.requested_effect, "read-metadata") == 0, "requested effect");
    EXPECT_TRUE(strcmp(handoff.requested_scope, "local-artifact") == 0, "requested scope");
    EXPECT_TRUE(strcmp(handoff.decision_state, "denied-gate") == 0, "decision state");
    EXPECT_TRUE(handoff.effect_allowed == 0u, "effect allowed");
    EXPECT_TRUE(handoff.effect_performed == 0u, "effect performed");
    EXPECT_TRUE(strcmp(handoff.runtime_boundary_state, "disabled") == 0, "runtime boundary");
    EXPECT_TRUE(strcmp(handoff.runtime_request_label, "runtime.preview") == 0, "runtime request");
    EXPECT_TRUE(handoff.handoff_active == 0u, "handoff active");
    EXPECT_TRUE(handoff.runtime_effect_performed == 0u, "runtime effect");
    EXPECT_TRUE(handoff.host_read_performed == 0u, "host read");
    EXPECT_TRUE(handoff.host_write_performed == 0u, "host write");
    EXPECT_TRUE(handoff.network_performed == 0u, "network");
    EXPECT_TRUE(handoff.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(strcmp(handoff.handoff_state, "denied-decision") == 0, "handoff state");
    EXPECT_TRUE(latticra_seal_runtime_handoff_is_inactive_metadata(&handoff) == 1, "inactive helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report(&handoff, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL RUNTIME HANDOFF") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "runtime_boundary_state=disabled") != 0, "render boundary");
    EXPECT_TRUE(strstr(rendered, "handoff_active=0") != 0, "render handoff active");
    EXPECT_TRUE(strstr(rendered, "runtime_effect_performed=0") != 0, "render runtime effect");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime authority");
    EXPECT_TRUE(strstr(rendered, "handoff_state=denied-decision") != 0, "render handoff state");
    return 0;
}

static int handoff_defaults_runtime_request(void) {
    latticra_seal_effect_decision_t decision = fixture_decision();
    latticra_seal_runtime_handoff_t handoff;

    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(&decision, 0, &handoff) == LATTICRA_STATUS_OK, "default request status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_OK, "default request ok");
    EXPECT_TRUE(strcmp(handoff.runtime_request_label, "no-runtime-request") == 0, "default request");
    return 0;
}

static int handoff_fails_closed(void) {
    latticra_seal_effect_decision_t decision = fixture_decision();
    latticra_seal_runtime_handoff_t handoff;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(0, "runtime", &handoff) == LATTICRA_STATUS_OK, "null decision status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_INPUT, "null decision error");
    decision.error = LATTICRA_SEAL_EFFECT_DECISION_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(&decision, "runtime", &handoff) == LATTICRA_STATUS_OK, "bad decision status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_DECISION, "bad decision error");
    decision = fixture_decision();
    decision.requested_capability[0] = '\0';
    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(&decision, "runtime", &handoff) == LATTICRA_STATUS_OK, "missing capability status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_CAPABILITY, "missing capability error");
    decision = fixture_decision();
    decision.requested_effect[0] = '\0';
    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(&decision, "runtime", &handoff) == LATTICRA_STATUS_OK, "missing effect status");
    EXPECT_TRUE(handoff.error == LATTICRA_SEAL_RUNTIME_HANDOFF_MISSING_REQUESTED_EFFECT, "missing effect error");
    EXPECT_TRUE(latticra_seal_runtime_handoff_from_decision(&decision, "runtime", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_runtime_handoff_is_inactive_metadata(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report(&handoff, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null handoff");
    EXPECT_TRUE(latticra_seal_runtime_handoff_report(&handoff, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (handoff_copies_decision_metadata_and_stays_inactive() != 0) {
        return 1;
    }
    if (handoff_defaults_runtime_request() != 0) {
        return 1;
    }
    if (handoff_fails_closed() != 0) {
        return 1;
    }
    printf("seal runtime handoff invariants: ok\n");
    return 0;
}
