#include "latticra/seal_report_envelope.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_envelope(const char *envelope) {
    return strcmp(envelope, "report-only") == 0 ||
           strcmp(envelope, "evaluate-only") == 0;
}

const char *latticra_seal_report_envelope_error_label(
    latticra_seal_report_envelope_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_REPORT_ENVELOPE_OK:
        return "ok";
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT:
        return "invalid-report";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT:
        return "denied-report";
    case LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE:
        return "missing-requested-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE:
        return "denied-unknown-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE:
        return "denied-envelope";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void envelope_init(latticra_seal_report_envelope_t *envelope) {
    memset(envelope, 0, sizeof(*envelope));
    copy_literal(envelope->envelope_profile, sizeof(envelope->envelope_profile), "latticra-seal-report-envelope/0.1");
    copy_literal(envelope->envelope_state, sizeof(envelope->envelope_state), "denied-report");
    envelope->report_ready = 0u;
    envelope->envelope_ready = 0u;
    envelope->signature_performed = 0u;
    envelope->handoff_performed = 0u;
    envelope->effect_performed = 0u;
    envelope->runtime_authority_granted = 0u;
    envelope->host_read_performed = 0u;
    envelope->host_write_performed = 0u;
    envelope->network_performed = 0u;
    envelope->error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_INPUT;
    copy_literal(envelope->status, sizeof(envelope->status), "invalid-input");
}

static void copy_report_metadata(
    const latticra_seal_runtime_handoff_report_t *report,
    const char *requested_envelope,
    latticra_seal_report_envelope_t *out) {
    copy_literal(out->report_profile, sizeof(out->report_profile), report->report_profile);
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), report->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), report->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), report->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), report->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), report->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), report->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), report->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), report->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), report->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), report->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), report->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), report->requested_report);
    copy_literal(out->requested_envelope, sizeof(out->requested_envelope), requested_envelope);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), report->requested_scope);
    copy_literal(out->report_state, sizeof(out->report_state), report->report_state);
    out->report_ready = report->report_ready;
    out->handoff_performed = report->handoff_performed;
    out->effect_performed = report->effect_performed;
    out->runtime_authority_granted = report->runtime_authority_granted;
    out->host_read_performed = report->host_read_performed;
    out->host_write_performed = report->host_write_performed;
    out->network_performed = report->network_performed;
}

latticra_status_t latticra_seal_report_envelope_from_report(
    const latticra_seal_runtime_handoff_report_t *report,
    const char *requested_envelope,
    latticra_seal_report_envelope_t *out) {
    int report_only_ready;
    int evaluate_only_ready;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    envelope_init(out);

    if (report == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_report_metadata(report, requested_envelope, out);

    if (report->error != LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_INVALID_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "invalid-report");
        return LATTICRA_STATUS_OK;
    }

    if (report->report_ready != 1u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-report");
        return LATTICRA_STATUS_OK;
    }

    report_only_ready = strcmp(report->report_state, "ready-report-only") == 0;
    evaluate_only_ready = strcmp(report->report_state, "ready-evaluate-only") == 0;
    if (!report_only_ready && !evaluate_only_ready) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_REPORT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-report");
        return LATTICRA_STATUS_OK;
    }

    if (report->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (report->handoff_performed != 0u ||
        report->effect_performed != 0u ||
        report->host_read_performed != 0u ||
        report->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_HOST_EFFECT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (report->network_performed != 0u) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_NETWORK_EFFECT;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (requested_envelope == NULL || requested_envelope[0] == '\0') {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_MISSING_REQUESTED_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "missing-requested-envelope");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_envelope(requested_envelope)) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_UNKNOWN_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-envelope");
        return LATTICRA_STATUS_OK;
    }

    if ((report_only_ready && strcmp(requested_envelope, "report-only") != 0) ||
        (evaluate_only_ready && strcmp(requested_envelope, "evaluate-only") != 0)) {
        out->error = LATTICRA_SEAL_REPORT_ENVELOPE_DENIED_ENVELOPE;
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "denied-envelope");
        copy_literal(out->status, sizeof(out->status), "denied-envelope");
        return LATTICRA_STATUS_OK;
    }

    out->envelope_ready = 1u;
    out->signature_performed = 0u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_REPORT_ENVELOPE_OK;

    if (strcmp(requested_envelope, "report-only") == 0) {
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "sealed-report-only");
    } else {
        copy_literal(out->envelope_state, sizeof(out->envelope_state), "sealed-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "sealed-report-envelope-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_report_envelope_is_metadata_only(
    const latticra_seal_report_envelope_t *envelope) {
    if (envelope == NULL) {
        return 0;
    }

    return envelope->signature_performed == 0u &&
           envelope->handoff_performed == 0u &&
           envelope->effect_performed == 0u &&
           envelope->runtime_authority_granted == 0u &&
           envelope->host_read_performed == 0u &&
           envelope->host_write_performed == 0u &&
           envelope->network_performed == 0u;
}

latticra_status_t latticra_seal_report_envelope_render(
    const latticra_seal_report_envelope_t *envelope,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (envelope == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL REPORT ENVELOPE\n"
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
        "requested_scope=%s\n"
        "report_state=%s\n"
        "report_ready=%u\n"
        "envelope_state=%s\n"
        "envelope_ready=%u\n"
        "signature_performed=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        envelope->envelope_profile,
        envelope->report_profile,
        envelope->handoff_profile,
        envelope->decision_profile,
        envelope->gate_profile,
        envelope->receipt_profile,
        envelope->verify_profile,
        envelope->message_digest_algorithm,
        envelope->message_digest_hex,
        envelope->public_key_identity_label,
        envelope->requested_capability,
        envelope->requested_effect,
        envelope->requested_handoff,
        envelope->requested_report,
        envelope->requested_envelope,
        envelope->requested_scope,
        envelope->report_state,
        envelope->report_ready,
        envelope->envelope_state,
        envelope->envelope_ready,
        envelope->signature_performed,
        envelope->handoff_performed,
        envelope->effect_performed,
        envelope->runtime_authority_granted,
        envelope->host_read_performed,
        envelope->host_write_performed,
        envelope->network_performed,
        latticra_seal_report_envelope_error_label(envelope->error),
        envelope->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
