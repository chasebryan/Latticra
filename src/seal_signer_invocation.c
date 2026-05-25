#include "latticra/seal_signer_invocation.h"

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

static int is_allowed_signer_invocation(const char *invocation) {
    return invocation != NULL && strcmp(invocation, "metadata-only") == 0;
}

const char *latticra_seal_signer_invocation_error_label(
    latticra_seal_signer_invocation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNER_INVOCATION_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF:
        return "invalid-signer-handoff";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF:
        return "denied-signer-handoff";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION:
        return "denied-signing-authorization";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM:
        return "denied-signature-algorithm";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION:
        return "denied-signer-invocation";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY:
        return "denied-private-key";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void invocation_init(latticra_seal_signer_invocation_t *invocation) {
    memset(invocation, 0, sizeof(*invocation));
    copy_literal(
        invocation->signer_invocation_profile,
        sizeof(invocation->signer_invocation_profile),
        "latticra-seal-signer-invocation/0.1");
    copy_literal(
        invocation->signer_invocation_state,
        sizeof(invocation->signer_invocation_state),
        "denied-signer-handoff");
    copy_literal(invocation->mode, sizeof(invocation->mode), "metadata-only");
    invocation->signing_authorization_ready = 0u;
    invocation->signer_handoff_ready = 0u;
    invocation->signer_invocation_ready = 0u;
    invocation->signature_performed = 0u;
    invocation->verification_performed = 0u;
    invocation->signer_invoked = 0u;
    invocation->private_key_handling = 0u;
    invocation->key_generation_performed = 0u;
    invocation->trust_store_loaded = 0u;
    invocation->revocation_lookup_performed = 0u;
    invocation->handoff_performed = 0u;
    invocation->effect_performed = 0u;
    invocation->runtime_authority_granted = 0u;
    invocation->host_read_performed = 0u;
    invocation->host_write_performed = 0u;
    invocation->network_performed = 0u;
    invocation->error = LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_INPUT;
    copy_literal(invocation->status, sizeof(invocation->status), "invalid-input");
}

static void copy_handoff_metadata(
    const latticra_seal_signer_handoff_t *handoff,
    const char *requested_signer_invocation,
    latticra_seal_signer_invocation_t *out) {
    copy_literal(out->signer_handoff_profile, sizeof(out->signer_handoff_profile), handoff->signer_handoff_profile);
    copy_literal(
        out->signing_authorization_profile,
        sizeof(out->signing_authorization_profile),
        handoff->signing_authorization_profile);
    copy_literal(out->signature_request_profile, sizeof(out->signature_request_profile), handoff->signature_request_profile);
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), handoff->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), handoff->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), handoff->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), handoff->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), handoff->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), handoff->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), handoff->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), handoff->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), handoff->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), handoff->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), handoff->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), handoff->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), handoff->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), handoff->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), handoff->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), handoff->requested_signature);
    copy_literal(
        out->requested_signing_authorization,
        sizeof(out->requested_signing_authorization),
        handoff->requested_signing_authorization);
    copy_literal(out->requested_signer_handoff, sizeof(out->requested_signer_handoff), handoff->requested_signer_handoff);
    copy_literal(
        out->requested_signer_invocation,
        sizeof(out->requested_signer_invocation),
        requested_signer_invocation);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), handoff->requested_scope);
    copy_literal(
        out->signing_authorization_state,
        sizeof(out->signing_authorization_state),
        handoff->signing_authorization_state);
    out->signing_authorization_ready = handoff->signing_authorization_ready;
    copy_literal(out->signer_handoff_state, sizeof(out->signer_handoff_state), handoff->signer_handoff_state);
    out->signer_handoff_ready = handoff->signer_handoff_ready;
    out->signature_performed = handoff->signature_performed;
    out->verification_performed = handoff->verification_performed;
    out->signer_invoked = handoff->signer_invoked;
    out->private_key_handling = handoff->private_key_handling;
    out->key_generation_performed = handoff->key_generation_performed;
    out->trust_store_loaded = handoff->trust_store_loaded;
    out->revocation_lookup_performed = handoff->revocation_lookup_performed;
    out->handoff_performed = handoff->handoff_performed;
    out->effect_performed = handoff->effect_performed;
    out->runtime_authority_granted = handoff->runtime_authority_granted;
    out->host_read_performed = handoff->host_read_performed;
    out->host_write_performed = handoff->host_write_performed;
    out->network_performed = handoff->network_performed;
}

latticra_status_t latticra_seal_signer_invocation_from_handoff(
    const latticra_seal_signer_handoff_t *handoff,
    const char *requested_signer_invocation,
    latticra_seal_signer_invocation_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    invocation_init(out);

    if (handoff == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_handoff_metadata(handoff, requested_signer_invocation, out);

    if (handoff->error != LATTICRA_SEAL_SIGNER_HANDOFF_OK) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_INVALID_SIGNER_HANDOFF;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "invalid-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signer_handoff_ready != 1u ||
        strcmp(handoff->signer_handoff_state, "handoff-metadata-only") != 0 ||
        strcmp(handoff->requested_signer_handoff, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_HANDOFF;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-signer-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signing_authorization_ready != 1u ||
        strcmp(handoff->signing_authorization_state, "authorized-metadata-only") != 0 ||
        strcmp(handoff->requested_signing_authorization, "metadata-only") != 0) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNING_AUTHORIZATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signing-authorization");
        copy_literal(out->status, sizeof(out->status), "denied-signing-authorization");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->requested_signature[0] == '\0' || !is_allowed_signature(handoff->requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNATURE_ALGORITHM;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signature-algorithm");
        copy_literal(out->status, sizeof(out->status), "denied-signature-algorithm");
        return LATTICRA_STATUS_OK;
    }

    if (requested_signer_invocation == NULL || requested_signer_invocation[0] == '\0') {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_signer_invocation(requested_signer_invocation)) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_SIGNER_INVOCATION;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-signer-invocation");
        copy_literal(out->status, sizeof(out->status), "denied-signer-invocation");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->private_key_handling != 0u ||
        handoff->key_generation_performed != 0u ||
        handoff->trust_store_loaded != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_PRIVATE_KEY;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-private-key");
        copy_literal(out->status, sizeof(out->status), "denied-private-key");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->revocation_lookup_performed != 0u ||
        handoff->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (handoff->signature_performed != 0u ||
        handoff->verification_performed != 0u ||
        handoff->signer_invoked != 0u ||
        handoff->handoff_performed != 0u ||
        handoff->effect_performed != 0u ||
        handoff->host_read_performed != 0u ||
        handoff->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNER_INVOCATION_DENIED_HOST_EFFECT;
        copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    out->signer_invocation_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->signer_invoked = 0u;
    out->private_key_handling = 0u;
    out->key_generation_performed = 0u;
    out->trust_store_loaded = 0u;
    out->revocation_lookup_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_SIGNER_INVOCATION_OK;
    copy_literal(out->signer_invocation_state, sizeof(out->signer_invocation_state), "invocation-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signer-invocation-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signer_invocation_is_metadata_only(
    const latticra_seal_signer_invocation_t *invocation) {
    if (invocation == NULL) {
        return 0;
    }

    return invocation->signature_performed == 0u &&
           invocation->verification_performed == 0u &&
           invocation->signer_invoked == 0u &&
           invocation->private_key_handling == 0u &&
           invocation->key_generation_performed == 0u &&
           invocation->trust_store_loaded == 0u &&
           invocation->revocation_lookup_performed == 0u &&
           invocation->handoff_performed == 0u &&
           invocation->effect_performed == 0u &&
           invocation->runtime_authority_granted == 0u &&
           invocation->host_read_performed == 0u &&
           invocation->host_write_performed == 0u &&
           invocation->network_performed == 0u;
}

latticra_status_t latticra_seal_signer_invocation_render(
    const latticra_seal_signer_invocation_t *invocation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (invocation == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNER INVOCATION\n"
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
        "requested_scope=%s\n"
        "signing_authorization_state=%s\n"
        "signing_authorization_ready=%u\n"
        "signer_handoff_state=%s\n"
        "signer_handoff_ready=%u\n"
        "signer_invocation_state=%s\n"
        "signer_invocation_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "signer_invoked=%u\n"
        "private_key_handling=%u\n"
        "key_generation_performed=%u\n"
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
        invocation->signer_invocation_profile,
        invocation->signer_handoff_profile,
        invocation->signing_authorization_profile,
        invocation->signature_request_profile,
        invocation->envelope_profile,
        invocation->report_profile,
        invocation->handoff_profile,
        invocation->decision_profile,
        invocation->gate_profile,
        invocation->receipt_profile,
        invocation->verify_profile,
        invocation->message_digest_algorithm,
        invocation->message_digest_hex,
        invocation->public_key_identity_label,
        invocation->requested_capability,
        invocation->requested_effect,
        invocation->requested_handoff,
        invocation->requested_report,
        invocation->requested_envelope,
        invocation->requested_signature,
        invocation->requested_signing_authorization,
        invocation->requested_signer_handoff,
        invocation->requested_signer_invocation,
        invocation->requested_scope,
        invocation->signing_authorization_state,
        invocation->signing_authorization_ready,
        invocation->signer_handoff_state,
        invocation->signer_handoff_ready,
        invocation->signer_invocation_state,
        invocation->signer_invocation_ready,
        invocation->signature_performed,
        invocation->verification_performed,
        invocation->signer_invoked,
        invocation->private_key_handling,
        invocation->key_generation_performed,
        invocation->trust_store_loaded,
        invocation->revocation_lookup_performed,
        invocation->handoff_performed,
        invocation->effect_performed,
        invocation->runtime_authority_granted,
        invocation->host_read_performed,
        invocation->host_write_performed,
        invocation->network_performed,
        invocation->mode,
        latticra_seal_signer_invocation_error_label(invocation->error),
        invocation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
