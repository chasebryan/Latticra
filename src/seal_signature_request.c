#include "latticra/seal_signature_request.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_signature_request(const char *signature) {
    return strcmp(signature, "Ed25519-development") == 0;
}

const char *latticra_seal_signature_request_error_label(
    latticra_seal_signature_request_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_SIGNATURE_REQUEST_OK:
        return "ok";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE:
        return "invalid-envelope";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE:
        return "denied-envelope";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE:
        return "missing-requested-signature";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE:
        return "denied-unknown-signature";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void request_init(latticra_seal_signature_request_t *request) {
    memset(request, 0, sizeof(*request));
    copy_literal(
        request->signature_request_profile,
        sizeof(request->signature_request_profile),
        "latticra-seal-signature-request/0.1");
    copy_literal(
        request->signature_request_state,
        sizeof(request->signature_request_state),
        "denied-envelope");
    request->envelope_ready = 0u;
    request->signature_request_ready = 0u;
    request->signature_performed = 0u;
    request->verification_performed = 0u;
    request->private_key_handling = 0u;
    request->handoff_performed = 0u;
    request->effect_performed = 0u;
    request->runtime_authority_granted = 0u;
    request->host_read_performed = 0u;
    request->host_write_performed = 0u;
    request->network_performed = 0u;
    request->error = LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_INPUT;
    copy_literal(request->status, sizeof(request->status), "invalid-input");
}

static void copy_envelope_metadata(
    const latticra_seal_report_envelope_t *envelope,
    const char *requested_signature,
    latticra_seal_signature_request_t *out) {
    copy_literal(out->envelope_profile, sizeof(out->envelope_profile), envelope->envelope_profile);
    copy_literal(out->report_profile, sizeof(out->report_profile), envelope->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), envelope->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), envelope->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), envelope->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), envelope->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), envelope->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), envelope->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), envelope->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), envelope->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), envelope->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), envelope->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), envelope->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), envelope->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), envelope->requested_envelope);
    copy_literal(out->requested_signature, sizeof(out->requested_signature), requested_signature);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), envelope->requested_scope);
    copy_literal(out->envelope_state, sizeof(out->envelope_state), envelope->envelope_state);
    out->envelope_ready = envelope->envelope_ready;
    out->signature_performed = envelope->signature_performed;
    out->handoff_performed = envelope->handoff_performed;
    out->effect_performed = envelope->effect_performed;
    out->runtime_authority_granted = envelope->runtime_authority_granted;
    out->host_read_performed = envelope->host_read_performed;
    out->host_write_performed = envelope->host_write_performed;
    out->network_performed = envelope->network_performed;
}

latticra_status_t latticra_seal_signature_request_from_envelope(
    const latticra_seal_report_envelope_t *envelope,
    const char *requested_signature,
    latticra_seal_signature_request_t *out) {
    int envelope_report_ready;
    int envelope_evaluate_ready;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    request_init(out);

    if (envelope == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_envelope_metadata(envelope, requested_signature, out);

    if (envelope->error != LATTICRA_SEAL_REPORT_ENVELOPE_OK) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_INVALID_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "invalid-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->envelope_ready != 1u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    envelope_report_ready = strcmp(envelope->envelope_state, "sealed-report-only") == 0;
    envelope_evaluate_ready = strcmp(envelope->envelope_state, "sealed-evaluate-only") == 0;
    if (!envelope_report_ready && !envelope_evaluate_ready) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_ENVELOPE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->signature_performed != 0u ||
        envelope->handoff_performed != 0u ||
        envelope->effect_performed != 0u ||
        envelope->host_read_performed != 0u ||
        envelope->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_HOST_EFFECT;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (envelope->network_performed != 0u) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_NETWORK_EFFECT;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (requested_signature == NULL || requested_signature[0] == '\0') {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_MISSING_REQUESTED_SIGNATURE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "missing-requested-signature");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_signature_request(requested_signature)) {
        out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_DENIED_UNKNOWN_SIGNATURE;
        copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "denied-signature-request");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-signature");
        return LATTICRA_STATUS_OK;
    }

    out->signature_request_ready = 1u;
    out->signature_performed = 0u;
    out->verification_performed = 0u;
    out->private_key_handling = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_SIGNATURE_REQUEST_OK;
    copy_literal(out->signature_request_state, sizeof(out->signature_request_state), "requested-metadata-only");
    copy_literal(out->status, sizeof(out->status), "signature-request-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_signature_request_is_metadata_only(
    const latticra_seal_signature_request_t *request) {
    if (request == NULL) {
        return 0;
    }

    return request->signature_performed == 0u &&
           request->verification_performed == 0u &&
           request->private_key_handling == 0u &&
           request->handoff_performed == 0u &&
           request->effect_performed == 0u &&
           request->runtime_authority_granted == 0u &&
           request->host_read_performed == 0u &&
           request->host_write_performed == 0u &&
           request->network_performed == 0u;
}

latticra_status_t latticra_seal_signature_request_render(
    const latticra_seal_signature_request_t *request,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (request == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL SIGNATURE REQUEST\n"
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
        "requested_scope=%s\n"
        "envelope_state=%s\n"
        "envelope_ready=%u\n"
        "signature_request_state=%s\n"
        "signature_request_ready=%u\n"
        "signature_performed=%u\n"
        "verification_performed=%u\n"
        "private_key_handling=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        request->signature_request_profile,
        request->envelope_profile,
        request->report_profile,
        request->handoff_profile,
        request->decision_profile,
        request->gate_profile,
        request->receipt_profile,
        request->verify_profile,
        request->message_digest_algorithm,
        request->message_digest_hex,
        request->public_key_identity_label,
        request->requested_capability,
        request->requested_effect,
        request->requested_handoff,
        request->requested_report,
        request->requested_envelope,
        request->requested_signature,
        request->requested_scope,
        request->envelope_state,
        request->envelope_ready,
        request->signature_request_state,
        request->signature_request_ready,
        request->signature_performed,
        request->verification_performed,
        request->private_key_handling,
        request->handoff_performed,
        request->effect_performed,
        request->runtime_authority_granted,
        request->host_read_performed,
        request->host_write_performed,
        request->network_performed,
        latticra_seal_signature_request_error_label(request->error),
        request->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
