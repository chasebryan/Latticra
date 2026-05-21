#include "latticra/seal_status_rollup.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_status_rollup_error_label(
    latticra_seal_status_rollup_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_STATUS_ROLLUP_OK:
        return "ok";
    case LATTICRA_SEAL_STATUS_ROLLUP_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_STATUS_ROLLUP_INVALID_HANDOFF:
        return "invalid-handoff";
    default:
        return "unknown";
    }
}

static void rollup_init(latticra_seal_status_rollup_t *rollup) {
    memset(rollup, 0, sizeof(*rollup));
    copy_literal(rollup->rollup_profile, sizeof(rollup->rollup_profile), "latticra-seal-status-rollup/0.1");
    copy_literal(rollup->runtime_boundary_state, sizeof(rollup->runtime_boundary_state), "disabled");
    copy_literal(rollup->rollup_state, sizeof(rollup->rollup_state), "metadata-only");
    rollup->cryptographic_verification_supported = 0u;
    rollup->verified = 0u;
    rollup->capability_gate_allowed = 0u;
    rollup->effect_allowed = 0u;
    rollup->handoff_active = 0u;
    rollup->runtime_authority_granted = 0u;
    rollup->host_read_performed = 0u;
    rollup->host_write_performed = 0u;
    rollup->network_performed = 0u;
    rollup->error = LATTICRA_SEAL_STATUS_ROLLUP_INVALID_INPUT;
    copy_literal(rollup->status, sizeof(rollup->status), "invalid-input");
}

latticra_status_t latticra_seal_status_rollup_from_handoff(
    const latticra_seal_runtime_handoff_t *handoff,
    latticra_seal_status_rollup_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    rollup_init(out);

    if (handoff == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (handoff->error != LATTICRA_SEAL_RUNTIME_HANDOFF_OK) {
        out->error = LATTICRA_SEAL_STATUS_ROLLUP_INVALID_HANDOFF;
        copy_literal(out->status, sizeof(out->status), "invalid-handoff");
        return LATTICRA_STATUS_OK;
    }

    out->report_present = 1u;
    out->measurement_present = 1u;
    out->manifest_present = 1u;
    out->signature_policy_present = 1u;
    out->signature_metadata_present = 1u;
    out->verification_policy_present = 1u;
    out->verification_receipt_present = 1u;
    out->capability_gate_present = 1u;
    out->effect_decision_present = 1u;
    out->runtime_handoff_present = 1u;
    out->cryptographic_verification_supported = 0u;
    out->verified = 0u;
    out->capability_gate_allowed = 0u;
    out->effect_allowed = handoff->effect_allowed;
    out->handoff_active = handoff->handoff_active;
    copy_literal(out->runtime_boundary_state, sizeof(out->runtime_boundary_state), handoff->runtime_boundary_state);
    out->runtime_authority_granted = handoff->runtime_authority_granted;
    out->host_read_performed = handoff->host_read_performed;
    out->host_write_performed = handoff->host_write_performed;
    out->network_performed = handoff->network_performed;
    copy_literal(out->rollup_state, sizeof(out->rollup_state), "metadata-only");
    out->error = LATTICRA_SEAL_STATUS_ROLLUP_OK;
    copy_literal(out->status, sizeof(out->status), "status-rollup-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_status_rollup_is_metadata_only(
    const latticra_seal_status_rollup_t *rollup) {
    if (rollup == NULL) {
        return 0;
    }

    return rollup->cryptographic_verification_supported == 0u &&
           rollup->verified == 0u &&
           rollup->capability_gate_allowed == 0u &&
           rollup->effect_allowed == 0u &&
           rollup->handoff_active == 0u &&
           rollup->runtime_authority_granted == 0u &&
           rollup->host_read_performed == 0u &&
           rollup->host_write_performed == 0u &&
           rollup->network_performed == 0u;
}

latticra_status_t latticra_seal_status_rollup_report(
    const latticra_seal_status_rollup_t *rollup,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (rollup == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL STATUS ROLLUP\n"
        "rollup_profile=%s\n"
        "report_present=%u\n"
        "measurement_present=%u\n"
        "manifest_present=%u\n"
        "signature_policy_present=%u\n"
        "signature_metadata_present=%u\n"
        "verification_policy_present=%u\n"
        "verification_receipt_present=%u\n"
        "capability_gate_present=%u\n"
        "effect_decision_present=%u\n"
        "runtime_handoff_present=%u\n"
        "cryptographic_verification_supported=%u\n"
        "verified=%u\n"
        "capability_gate_allowed=%u\n"
        "effect_allowed=%u\n"
        "handoff_active=%u\n"
        "runtime_boundary_state=%s\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "rollup_state=%s\n"
        "error=%s\n"
        "status=%s\n",
        rollup->rollup_profile,
        rollup->report_present,
        rollup->measurement_present,
        rollup->manifest_present,
        rollup->signature_policy_present,
        rollup->signature_metadata_present,
        rollup->verification_policy_present,
        rollup->verification_receipt_present,
        rollup->capability_gate_present,
        rollup->effect_decision_present,
        rollup->runtime_handoff_present,
        rollup->cryptographic_verification_supported,
        rollup->verified,
        rollup->capability_gate_allowed,
        rollup->effect_allowed,
        rollup->handoff_active,
        rollup->runtime_boundary_state,
        rollup->runtime_authority_granted,
        rollup->host_read_performed,
        rollup->host_write_performed,
        rollup->network_performed,
        rollup->rollup_state,
        latticra_seal_status_rollup_error_label(rollup->error),
        rollup->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
