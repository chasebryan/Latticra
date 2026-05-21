#include "latticra/seal_agentic_automation_security.h"

#include <stdio.h>
#include <string.h>

static latticra_seal_status_rollup_t fixture_rollup(void) {
    latticra_seal_status_rollup_t rollup;
    memset(&rollup, 0, sizeof(rollup));
    (void)snprintf(rollup.rollup_profile, sizeof(rollup.rollup_profile), "%s", "latticra-seal-status-rollup/0.1");
    rollup.report_present = 1u;
    rollup.measurement_present = 1u;
    rollup.manifest_present = 1u;
    rollup.signature_policy_present = 1u;
    rollup.signature_metadata_present = 1u;
    rollup.verification_policy_present = 1u;
    rollup.verification_receipt_present = 1u;
    rollup.capability_gate_present = 1u;
    rollup.effect_decision_present = 1u;
    rollup.runtime_handoff_present = 1u;
    rollup.cryptographic_verification_supported = 0u;
    rollup.verified = 0u;
    rollup.capability_gate_allowed = 0u;
    rollup.effect_allowed = 0u;
    rollup.handoff_active = 0u;
    (void)snprintf(rollup.runtime_boundary_state, sizeof(rollup.runtime_boundary_state), "%s", "disabled");
    rollup.runtime_authority_granted = 0u;
    rollup.host_read_performed = 0u;
    rollup.host_write_performed = 0u;
    rollup.network_performed = 0u;
    (void)snprintf(rollup.rollup_state, sizeof(rollup.rollup_state), "%s", "metadata-only");
    rollup.error = LATTICRA_SEAL_STATUS_ROLLUP_OK;
    (void)snprintf(rollup.status, sizeof(rollup.status), "%s", "status-rollup-metadata");
    return rollup;
}

int main(void) {
    latticra_seal_status_rollup_t rollup = fixture_rollup();
    latticra_seal_agentic_automation_security_t agentic;
    char rendered[LATTICRA_SEAL_AGENTIC_REPORT_MAX];

    if (latticra_seal_agentic_automation_security_from_rollup(&rollup, &agentic) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal agentic automation security metadata\n");
        return 1;
    }

    if (agentic.error != LATTICRA_SEAL_AGENTIC_OK) {
        fprintf(stderr, "invalid Seal agentic automation security metadata: %s\n",
                latticra_seal_agentic_automation_security_error_label(agentic.error));
        return 1;
    }

    if (latticra_seal_agentic_automation_security_report(&agentic, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal agentic automation security report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}
