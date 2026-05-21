#include "latticra/seal_signature_policy.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_signature_policy_error_label(latticra_seal_signature_policy_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_POLICY_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_MANIFEST:
        return "invalid-manifest";
    default:
        return "unknown";
    }
}

static void policy_init(latticra_seal_signature_policy_t *policy) {
    memset(policy, 0, sizeof(*policy));
    copy_literal(policy->policy_profile, sizeof(policy->policy_profile), "latticra-seal-signature-policy/0.1");
    copy_literal(policy->planned_signature_algorithm, sizeof(policy->planned_signature_algorithm), "Ed25519-planned");
    copy_literal(policy->post_quantum_algorithm_planned, sizeof(policy->post_quantum_algorithm_planned), "ML-DSA-planned");
    copy_literal(policy->conservative_root_algorithm_planned, sizeof(policy->conservative_root_algorithm_planned), "SLH-DSA-planned");
    copy_literal(policy->signature_state, sizeof(policy->signature_state), "unsupported");
    policy->signature_supported = 0u;
    policy->verification_supported = 0u;
    policy->public_key_metadata_supported = 0u;
    policy->private_key_handling = 0u;
    policy->network_lookup_allowed = 0u;
    policy->runtime_authority_granted = 0u;
    policy->error = LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_INPUT;
    copy_literal(policy->status, sizeof(policy->status), "invalid-input");
}

latticra_status_t latticra_seal_signature_policy_from_manifest(
    const latticra_seal_manifest_t *manifest,
    latticra_seal_signature_policy_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    policy_init(out);

    if (manifest == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (manifest->error != LATTICRA_SEAL_MANIFEST_OK) {
        out->error = LATTICRA_SEAL_SIGNATURE_POLICY_INVALID_MANIFEST;
        copy_literal(out->status, sizeof(out->status), "invalid-manifest");
        return LATTICRA_STATUS_OK;
    }

    copy_literal(out->manifest_profile, sizeof(out->manifest_profile), manifest->manifest_profile);
    copy_literal(out->manifest_kind, sizeof(out->manifest_kind), manifest->manifest_kind);
    out->error = LATTICRA_SEAL_SIGNATURE_POLICY_OK;
    copy_literal(out->status, sizeof(out->status), "signature-policy-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signature_policy_is_metadata_only(
    const latticra_seal_signature_policy_t *policy) {
    if (policy == NULL) {
        return 0;
    }

    return policy->signature_supported == 0u &&
           policy->verification_supported == 0u &&
           policy->public_key_metadata_supported == 0u &&
           policy->private_key_handling == 0u &&
           policy->network_lookup_allowed == 0u &&
           policy->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_signature_policy_report(
    const latticra_seal_signature_policy_t *policy,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (policy == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNATURE POLICY\n"
        "policy_profile=%s\n"
        "manifest_profile=%s\n"
        "manifest_kind=%s\n"
        "planned_signature_algorithm=%s\n"
        "post_quantum_algorithm_planned=%s\n"
        "conservative_root_algorithm_planned=%s\n"
        "signature_state=%s\n"
        "signature_supported=%u\n"
        "verification_supported=%u\n"
        "public_key_metadata_supported=%u\n"
        "private_key_handling=%u\n"
        "network_lookup_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        policy->policy_profile,
        policy->manifest_profile,
        policy->manifest_kind,
        policy->planned_signature_algorithm,
        policy->post_quantum_algorithm_planned,
        policy->conservative_root_algorithm_planned,
        policy->signature_state,
        policy->signature_supported,
        policy->verification_supported,
        policy->public_key_metadata_supported,
        policy->private_key_handling,
        policy->network_lookup_allowed,
        policy->runtime_authority_granted,
        latticra_seal_signature_policy_error_label(policy->error),
        policy->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
