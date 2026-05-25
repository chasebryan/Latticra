#include "latticra/seal_key_material.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_signature(const char *signature) {
    return signature != NULL && strcmp(signature, "Ed25519-development") == 0;
}

static int is_allowed_metadata_label(const char *label) {
    return label != NULL && strcmp(label, "metadata-only") == 0;
}

const char *latticra_seal_key_material_error_label(
    latticra_seal_key_material_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_KEY_MATERIAL_OK:
        return "ok";
    case LATTICRA_SEAL_KEY_MATERIAL_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING:
        return "invalid-key-handling";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING:
        return "denied-key-handling";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION:
        return "denied-signing-operation";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL:
        return "denied-key-material";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE:
        return "denied-trust-store";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void key_material_init(latticra_seal_key_material_t *key_material) {
    memset(key_material, 0, sizeof(*key_material));
    copy_literal(
        key_material->key_material_profile,
        sizeof(key_material->key_material_profile),
        "latticra-seal-key-material/0.1");
    copy_literal(
        key_material->key_material_state,
        sizeof(key_material->key_material_state),
        "denied-key-handling");
    copy_literal(key_material->mode, sizeof(key_material->mode), "metadata-only");
    key_material->error = LATTICRA_SEAL_KEY_MATERIAL_INVALID_INPUT;
    copy_literal(key_material->status, sizeof(key_material->status), "invalid-input");
}

static void copy_key_handling_metadata(
    const latticra_seal_key_handling_t *key_handling,
    const char *requested_key_material,
    latticra_seal_key_material_t *out) {
    copy_literal(out->key_handling_profile, sizeof(out->key_handling_profile), key_handling->key_handling_profile);
    copy_literal(out->signing_operation_profile, sizeof(out->signing_operation_profile), key_handling->signing_operation_profile);
    copy_literal(out->signer_invocation_profile, sizeof(out->signer_invocation_profile), key_handling->signer_invocation_profile);
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), key_handling->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        key_handling->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), key_handling->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), key_handling->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), key_handling->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), key_handling->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), key_handling->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), key_handling->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), key_handling->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), key_handling->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), key_handling->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), key_handling->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), key_handling->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), key_handling->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), key_handling->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), key_handling->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), key_handling->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), key_handling->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), key_handling->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        key_handling->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), key_handling->requested_signer_handoff);
    copy_literal(out->requested_signer_invocation, sizeof(out->requested_signer_invocation), key_handling->requested_signer_invocation);
    copy_literal(
        out->requested_signing_operation,
        sizeof(out->requested_signing_operation),
        key_handling->requested_signing_operation);
    copy_literal(out->requested_key_handling, sizeof(out->requested_key_handling), key_handling->requested_key_handling);
    copy_literal(out->requested_key_material, sizeof(out->requested_key_material), requested_key_material);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), key_handling->requested_scope);
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        key_handling->signing_authorization_state);
    out->signing_authorization_ready = key_handling->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), key_handling->signer_handoff_state);
    out->signer_handoff_ready = key_handling->signer_handoff_ready;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), key_handling->signer_invocation_state);
    out->signer_invocation_ready = key_handling->signer_invocation_ready;
    copy_literal(out->signing_operation_state, sizeof(out->signing_operation_state), key_handling->signing_operation_state);
    out->signing_operation_ready = key_handling->signing_operation_ready;
    copy_literal(out->key_handling_state, sizeof(out->key_handling_state), key_handling->key_handling_state);
    out->key_handling_ready = key_handling->key_handling_ready;
    out->signature_performed = key_handling->signature_performed;
    out->verification_performed = key_handling->verification_performed;
    out->signer_invoked = key_handling->signer_invoked;
    out->public_key_parsed = key_handling->public_key_parsed;
    out->key_material_loaded = key_handling->key_material_loaded;
    out->private_key_handling = key_handling->private_key_handling;
    out->key_generation_performed = key_handling->key_generation_performed;
    out->hardware_key_used = key_handling->hardware_key_used;
    out->trust_store_loaded = key_handling->trust_store_loaded;
    out->revocation_lookup_performed = key_handling->revocation_lookup_performed;
    out->handoff_performed = key_handling->handoff_performed;
    out->effect_performed = key_handling->effect_performed;
    out->runtime_authority_granted = key_handling->runtime_authority_granted;
    out->host_read_performed = key_handling->host_read_performed;
    out->host_write_performed = key_handling->host_write_performed;
    out->network_performed = key_handling->network_performed;
}

static int request_is_key_material(const char *requested_key_material) {
    return requested_key_material != NULL &&
           (strcmp(requested_key_material, "parse-public-key") == 0 ||
            strcmp(requested_key_material, "load-key-material") == 0);
}

static int request_is_private_key(const char *requested_key_material) {
    return requested_key_material != NULL &&
           (strcmp(requested_key_material, "handle-private-key") == 0 ||
            strcmp(requested_key_material, "generate-key") == 0 ||
            strcmp(requested_key_material, "use-hardware-key") == 0);
}

latticra_status_t latticra_seal_key_material_from_key_handling(
    const latticra_seal_key_handling_t *key_handling,
    const char *requested_key_material,
    latticra_seal_key_material_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    key_material_init(out);

    if (key_handling == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_key_handling_metadata(key_handling, requested_key_material, out);

    if (key_handling->error != LATTICRA_SEAL_KEY_HANDLING_OK) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_INVALID_KEY_HANDLING;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-handling");
        copy_literal(out->status, sizeof(out->status), "invalid-key-handling");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->key_handling_ready != 1u ||
        strcmp(key_handling->key_handling_state, "key-handling-metadata-only") != 0 ||
        strcmp(key_handling->requested_key_handling, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_HANDLING;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-handling");
        copy_literal(out->status, sizeof(out->status), "denied-key-handling");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->signing_operation_ready != 1u ||
        strcmp(key_handling->signing_operation_state, "operation-metadata-only") != 0 ||
        strcmp(key_handling->requested_signing_operation, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_OPERATION;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-signing-operation");
        copy_literal(out->status, sizeof(out->status), "denied-signing-operation");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->signer_invocation_ready != 1u ||
        strcmp(key_handling->signer_invocation_state, "invocation-metadata-only") != 0 ||
        strcmp(key_handling->requested_signer_invocation, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_INVOCATION;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->signer_handoff_ready != 1u ||
        strcmp(key_handling->signer_handoff_state, "handoff-metadata-only") != 0 ||
        strcmp(key_handling->requested_signer_handoff, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNER_HANDOFF;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->signing_authorization_ready != 1u ||
        strcmp(key_handling->signing_authorization_state, "authorized-metadata-only") != 0 ||
        strcmp(key_handling->requested_signing_authorization, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->requested_signature[0] == '\0' || !is_allowed_signature(key_handling->requested_signature)) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (requested_key_material == NULL || requested_key_material[0] == '\0') {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "missing-requested-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_key_material(requested_key_material)) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (request_is_private_key(requested_key_material)) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (strcmp(requested_key_material, "load-trust-store") == 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (strcmp(requested_key_material, "revocation-lookup") == 0) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_metadata_label(requested_key_material)) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->public_key_parsed != 0u ||
        key_handling->key_material_loaded != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_KEY_MATERIAL;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-key-material");
        copy_literal(out->status, sizeof(out->status), "denied-key-material");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->private_key_handling != 0u ||
        key_handling->key_generation_performed != 0u ||
        key_handling->hardware_key_used != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_PRIVATE_KEY;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_TRUST_STORE;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-trust-store");
        copy_literal(out->status, sizeof(out->status), "denied-trust-store");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->revocation_lookup_performed != 0u ||
        key_handling->network_performed != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_NETWORK_EFFECT;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (key_handling->signature_performed != 0u ||
        key_handling->verification_performed != 0u ||
        key_handling->signer_invoked != 0u ||
        key_handling->handoff_performed != 0u ||
        key_handling->effect_performed != 0u ||
        key_handling->host_read_performed != 0u ||
        key_handling->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_KEY_MATERIAL_DENIED_HOST_EFFECT;
        copy_literal(out->key_material_state, sizeof(out->key_material_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->key_material_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->signer_invoked = 0u;
    out->public_key_parsed = 0u;
    out->key_material_loaded = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->hardware_key_used = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_KEY_MATERIAL_OK;
    copy_literal(out->key_material_state, sizeof(out->key_material_state), "key-material-metadata-only");
    copy_literal(out->status, sizeof(out->status), "key-material-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_key_material_is_metadata_only(
    const latticra_seal_key_material_t *key_material) {
    if (key_material == NULL) {
        return 0;
    }

    return key_material->signature_performed == 0u &&
           key_material->verification_performed == 0u &&
           key_material->signer_invoked == 0u &&
           key_material->public_key_parsed == 0u &&
           key_material->key_material_loaded == 0u &&
           key_material->private_key_handling == 0u &&
           key_material->key_generation_performed == 0u &&
           key_material->hardware_key_used == 0u &&
           key_material->trust_store_loaded == 0u &&
           key_material->revocation_lookup_performed == 0u &&
           key_material->handoff_performed == 0u &&
           key_material->effect_performed == 0u &&
           key_material->runtime_authority_granted == 0u &&
           key_material->host_read_performed == 0u &&
           key_material->host_write_performed == 0u &&
           key_material->network_performed == 0u;
}

latticra_status_t latticra_seal_key_material_render(
    const latticra_seal_key_material_t *key_material,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (key_material == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL KEY MATERIAL\n"
        "key_material_profile=%s\n"
        "key_handling_profile=%s\n"
        "signing_operation_profile=%s\n"
        "signer_invocation_profile=%s\n"
        "signer_handoff_profile=%s\n"
        "signing_authorization_profile=%s\n"
        "signature_request_profile=%s\n"
        "envelope_profile=%s\n"
        "report_profile=%s\n"
        "handoff_profile=%s\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_handoff=%s\n"
        "requested_report=%s\n"
        "requested_envelope=%s\n"
        "requested_signature=%s\n"
        "requested_signing_authorization=%s\n"
        "requested_signer_handoff=%s\n"
        "requested_signer_invocation=%s\n"
        "requested_signing_operation=%s\n"
        "requested_key_handling=%s\n"
        "requested_key_material=%s\n"
        "requested_scope=%s\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signer_handoff_state=%s\n"
        "signer_handoff_ready=%u\n"
        "signer_invocation_state=%s\n"
        "signer_invocation_ready=%u\n"
        "signing_operation_state=%s\n"
        "signing_operation_ready=%u\n"
        "key_handling_state=%s\n"
        "key_handling_ready=%u\n"
        "key_material_state=%s\n"
        "key_material_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "public_key_parsed=%u\n"
        "key_material_loaded=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
        "hardware_key_used=%u\n"
        "trust_store_loaded=%u\n"
        "revocation_lookup_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        key_material->key_material_profile,
        key_material->key_handling_profile,
        key_material->signing_operation_profile,
        key_material->signer_invocation_profile,
        key_material->signer_handoff_profile,
        key_material->signing_authorization_profile,
        key_material->signature_request_profile,
        key_material->envelope_profile,
        key_material->report_profile,
        key_material->handoff_profile,
        key_material->decision_profile,
        key_material->gate_profile,
        key_material->receipt_profile,
        key_material->verify_profile,
        key_material->message_digest_algorithm,
        key_material->message_digest_hex,
        key_material->public_key_identity_label,
        key_material->requested_capability,
        key_material->requested_effect,
        key_material->requested_handoff,
        key_material->requested_report,
        key_material->requested_envelope,
        key_material->requested_signature,
        key_material->requested_signing_authorization,
        key_material->requested_signer_handoff,
        key_material->requested_signer_invocation,
        key_material->requested_signing_operation,
        key_material->requested_key_handling,
        key_material->requested_key_material,
        key_material->requested_scope,
        key_material->signing_authorization_state,
        key_material->signing_authorization_ready,
        key_material->signer_handoff_state,
        key_material->signer_handoff_ready,
        key_material->signer_invocation_state,
        key_material->signer_invocation_ready,
        key_material->signing_operation_state,
        key_material->signing_operation_ready,
        key_material->key_handling_state,
        key_material->key_handling_ready,
        key_material->key_material_state,
        key_material->key_material_ready,
        key_material->signature_performed,
        key_material->verification_performed,
        key_material->signer_invoked,
        key_material->public_key_parsed,
        key_material->key_material_loaded,
        key_material->private_key_handling,
        key_material->key_generation_performed,
        key_material->hardware_key_used,
        key_material->trust_store_loaded,
        key_material->revocation_lookup_performed,
        key_material->handoff_performed,
        key_material->effect_performed,
        key_material->runtime_authority_granted,
        key_material->host_read_performed,
        key_material->host_write_performed,
        key_material->network_performed,
        key_material->mode,
        latticra_seal_key_material_error_label(key_material->error),
        key_material->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
