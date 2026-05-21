#include "latticra/seal_status_rollup.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_runtime_handoff_t fixture_handoff(void) {
    latticra_seal_runtime_handoff_t handoff;
    memset(&handoff, 0, sizeof(handoff));
    (void)snprintf(handoff.handoff_profile, sizeof(handoff.handoff_profile), "%s", "latticra-seal-runtime-handoff/0.1");
    (void)snprintf(handoff.decision_profile, sizeof(handoff.decision_profile), "%s", "latticra-seal-effect-decision/0.1");
    (void)snprintf(handoff.gate_profile, sizeof(handoff.gate_profile), "%s", "latticra-seal-capability-gate/0.1");
    (void)snprintf(handoff.requested_capability, sizeof(handoff.requested_capability), "%s", "seal.inspect");
    (void)snprintf(handoff.requested_effect, sizeof(handoff.requested_effect), "%s", "read-metadata");
    (void)snprintf(handoff.requested_scope, sizeof(handoff.requested_scope), "%s", "local-artifact");
    (void)snprintf(handoff.decision_state, sizeof(handoff.decision_state), "%s", "denied-gate");
    handoff.effect_allowed = 0u;
    handoff.effect_performed = 0u;
    (void)snprintf(handoff.runtime_boundary_state, sizeof(handoff.runtime_boundary_state), "%s", "disabled");
    (void)snprintf(handoff.runtime_request_label, sizeof(handoff.runtime_request_label), "%s", "runtime.preview");
    handoff.handoff_active = 0u;
    handoff.runtime_effect_performed = 0u;
    handoff.host_read_performed = 0u;
    handoff.host_write_performed = 0u;
    handoff.network_performed = 0u;
    handoff.runtime_authority_granted = 0u;
    (void)snprintf(handoff.handoff_state, sizeof(handoff.handoff_state), "%s", "denied-decision");
    handoff.error = LATTICRA_SEAL_RUNTIME_HANDOFF_OK;
    (void)snprintf(handoff.status, sizeof(handoff.status), "%s", "runtime-handoff-inactive-metadata");
    return handoff;
}

static int rollup_summarizes_chain_and_stays_metadata_only(void) {
    latticra_seal_runtime_handoff_t handoff = fixture_handoff();
    latticra_seal_status_rollup_t rollup;
    char rendered[LATTICRA_SEAL_STATUS_ROLLUP_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_status_rollup_from_handoff(&handoff, &rollup) == LATTICRA_STATUS_OK, "rollup status");
    EXPECT_TRUE(rollup.error == LATTICRA_SEAL_STATUS_ROLLUP_OK, "rollup ok");
    EXPECT_TRUE(strcmp(rollup.rollup_profile, "latticra-seal-status-rollup/0.1") == 0, "rollup profile");
    EXPECT_TRUE(rollup.report_present == 1u, "report present");
    EXPECT_TRUE(rollup.measurement_present == 1u, "measurement present");
    EXPECT_TRUE(rollup.manifest_present == 1u, "manifest present");
    EXPECT_TRUE(rollup.signature_policy_present == 1u, "signature policy present");
    EXPECT_TRUE(rollup.signature_metadata_present == 1u, "signature metadata present");
    EXPECT_TRUE(rollup.verification_policy_present == 1u, "verification policy present");
    EXPECT_TRUE(rollup.verification_receipt_present == 1u, "verification receipt present");
    EXPECT_TRUE(rollup.capability_gate_present == 1u, "capability gate present");
    EXPECT_TRUE(rollup.effect_decision_present == 1u, "effect decision present");
    EXPECT_TRUE(rollup.runtime_handoff_present == 1u, "runtime handoff present");
    EXPECT_TRUE(rollup.cryptographic_verification_supported == 0u, "verification support");
    EXPECT_TRUE(rollup.verified == 0u, "verified");
    EXPECT_TRUE(rollup.capability_gate_allowed == 0u, "capability gate allowed");
    EXPECT_TRUE(rollup.effect_allowed == 0u, "effect allowed");
    EXPECT_TRUE(rollup.handoff_active == 0u, "handoff active");
    EXPECT_TRUE(strcmp(rollup.runtime_boundary_state, "disabled") == 0, "runtime boundary");
    EXPECT_TRUE(rollup.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(rollup.host_read_performed == 0u, "host read");
    EXPECT_TRUE(rollup.host_write_performed == 0u, "host write");
    EXPECT_TRUE(rollup.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(rollup.rollup_state, "metadata-only") == 0, "rollup state");
    EXPECT_TRUE(latticra_seal_status_rollup_is_metadata_only(&rollup) == 1, "metadata helper");
    EXPECT_TRUE(latticra_seal_status_rollup_report(&rollup, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL STATUS ROLLUP") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "report_present=1") != 0, "render report present");
    EXPECT_TRUE(strstr(rendered, "runtime_handoff_present=1") != 0, "render handoff present");
    EXPECT_TRUE(strstr(rendered, "cryptographic_verification_supported=0") != 0, "render verification");
    EXPECT_TRUE(strstr(rendered, "verified=0") != 0, "render verified");
    EXPECT_TRUE(strstr(rendered, "capability_gate_allowed=0") != 0, "render capability gate");
    EXPECT_TRUE(strstr(rendered, "effect_allowed=0") != 0, "render effect allowed");
    EXPECT_TRUE(strstr(rendered, "handoff_active=0") != 0, "render handoff active");
    EXPECT_TRUE(strstr(rendered, "runtime_boundary_state=disabled") != 0, "render boundary");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime authority");
    EXPECT_TRUE(strstr(rendered, "host_read_performed=0") != 0, "render host read");
    EXPECT_TRUE(strstr(rendered, "host_write_performed=0") != 0, "render host write");
    EXPECT_TRUE(strstr(rendered, "network_performed=0") != 0, "render network");
    EXPECT_TRUE(strstr(rendered, "rollup_state=metadata-only") != 0, "render rollup state");
    return 0;
}

static int rollup_fails_closed(void) {
    latticra_seal_runtime_handoff_t handoff = fixture_handoff();
    latticra_seal_status_rollup_t rollup;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_status_rollup_from_handoff(0, &rollup) == LATTICRA_STATUS_OK, "null handoff status");
    EXPECT_TRUE(rollup.error == LATTICRA_SEAL_STATUS_ROLLUP_INVALID_INPUT, "null handoff error");
    handoff.error = LATTICRA_SEAL_RUNTIME_HANDOFF_INVALID_INPUT;
    EXPECT_TRUE(latticra_seal_status_rollup_from_handoff(&handoff, &rollup) == LATTICRA_STATUS_OK, "bad handoff status");
    EXPECT_TRUE(rollup.error == LATTICRA_SEAL_STATUS_ROLLUP_INVALID_HANDOFF, "bad handoff error");
    EXPECT_TRUE(latticra_seal_status_rollup_from_handoff(&handoff, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_status_rollup_is_metadata_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_status_rollup_report(&rollup, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_status_rollup_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null rollup");
    EXPECT_TRUE(latticra_seal_status_rollup_report(&rollup, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (rollup_summarizes_chain_and_stays_metadata_only() != 0) {
        return 1;
    }
    if (rollup_fails_closed() != 0) {
        return 1;
    }
    printf("seal status rollup invariants: ok\n");
    return 0;
}
