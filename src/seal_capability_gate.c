#include "latticra/seal_capability_gate.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_capability_gate_error_label(
    latticra_seal_capability_gate_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CAPABILITY_GATE_OK:
        return "ok";
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT:
        return "invalid-receipt";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST:
        return "missing-digest";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER:
        return "missing-signer";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY:
        return "missing-public-key-identity";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY:
        return "missing-requested-capability";
    case LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT:
        return "missing-requested-effect";
    default:
        return "unknown";
    }
}

static void gate_init(latticra_seal_capability_gate_t *gate) {
    memset(gate, 0, sizeof(*gate));
    copy_literal(gate->gate_profile, sizeof(gate->gate_profile), "latticra-seal-capability-gate/0.1");
    copy_literal(gate->gate_state, sizeof(gate->gate_state), "denied-unverified");
    gate->verified = 0u;
    gate->authority_usable = 0u;
    gate->receipt_capability_gate_allowed = 0u;
    gate->gate_allowed = 0u;
    gate->runtime_authority_granted = 0u;
    gate->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_INPUT;
    copy_literal(gate->status, sizeof(gate->status), "invalid-input");
}

latticra_status_t latticra_seal_capability_gate_from_receipt(
    const latticra_seal_verification_receipt_t *receipt,
    const char *requested_capability,
    const char *requested_effect,
    const char *requested_scope,
    latticra_seal_capability_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    gate_init(out);

    if (receipt == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (receipt->error != LATTICRA_SEAL_VERIFICATION_RECEIPT_OK) {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_INVALID_RECEIPT;
        copy_literal(out->status, sizeof(out->status), "invalid-receipt");
        return LATTICRA_STATUS_OK;
    }

    if (receipt->artifact_digest_hex[0] == '\0') {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_DIGEST;
        copy_literal(out->status, sizeof(out->status), "missing-digest");
        return LATTICRA_STATUS_OK;
    }

    if (receipt->signer_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_SIGNER;
        copy_literal(out->status, sizeof(out->status), "missing-signer");
        return LATTICRA_STATUS_OK;
    }

    if (receipt->public_key_identity_label[0] == '\0') {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_PUBLIC_KEY_IDENTITY;
        copy_literal(out->status, sizeof(out->status), "missing-public-key-identity");
        return LATTICRA_STATUS_OK;
    }

    if (requested_capability == NULL || requested_capability[0] == '\0') {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_CAPABILITY;
        copy_literal(out->status, sizeof(out->status), "missing-requested-capability");
        return LATTICRA_STATUS_OK;
    }

    if (requested_effect == NULL || requested_effect[0] == '\0') {
        out->error = LATTICRA_SEAL_CAPABILITY_GATE_MISSING_REQUESTED_EFFECT;
        copy_literal(out->status, sizeof(out->status), "missing-requested-effect");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), receipt->receipt_profile);
    copy_literal(out->verification_policy_profile, sizeof(out->verification_policy_profile), receipt->verification_policy_profile);
    copy_literal(out->artifact_digest_algorithm, sizeof(out->artifact_digest_algorithm), receipt->artifact_digest_algorithm);
    copy_literal(out->artifact_digest_hex, sizeof(out->artifact_digest_hex), receipt->artifact_digest_hex);
    copy_literal(out->signer_identity_label, sizeof(out->signer_identity_label), receipt->signer_identity_label);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), receipt->public_key_identity_label);
    copy_literal(out->receipt_state, sizeof(out->receipt_state), receipt->receipt_state);
    copy_literal(out->verification_state, sizeof(out->verification_state), receipt->verification_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), requested_effect);
    copy_literal(
        out->requested_scope,
        sizeof(out->requested_scope),
        requested_scope != NULL && requested_scope[0] != '\0' ? requested_scope : "unspecified-scope");
    out->verified = receipt->verified;
    out->authority_usable = receipt->authority_usable;
    out->receipt_capability_gate_allowed = receipt->capability_gate_allowed;
    out->gate_allowed = 0u;
    copy_literal(out->gate_state, sizeof(out->gate_state), "denied-unverified");
    out->runtime_authority_granted = 0u;
    out->error = LATTICRA_SEAL_CAPABILITY_GATE_OK;
    copy_literal(out->status, sizeof(out->status), "capability-gate-denied-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_capability_gate_is_denied_metadata(
    const latticra_seal_capability_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->verified == 0u &&
           gate->authority_usable == 0u &&
           gate->receipt_capability_gate_allowed == 0u &&
           gate->gate_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_capability_gate_report(
    const latticra_seal_capability_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL CAPABILITY GATE\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verification_policy_profile=%s\n"
        "artifact_digest_algorithm=%s\n"
        "artifact_digest_hex=%s\n"
        "signer_identity_label=%s\n"
        "public_key_identity_label=%s\n"
        "receipt_state=%s\n"
        "verification_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_scope=%s\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        gate->gate_profile,
        gate->receipt_profile,
        gate->verification_policy_profile,
        gate->artifact_digest_algorithm,
        gate->artifact_digest_hex,
        gate->signer_identity_label,
        gate->public_key_identity_label,
        gate->receipt_state,
        gate->verification_state,
        gate->requested_capability,
        gate->requested_effect,
        gate->requested_scope,
        gate->verified,
        gate->authority_usable,
        gate->receipt_capability_gate_allowed,
        gate->gate_allowed,
        gate->gate_state,
        gate->runtime_authority_granted,
        latticra_seal_capability_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
