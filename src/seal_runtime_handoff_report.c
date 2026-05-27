#include "latticra/seal_runtime_handoff_report.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_report(const char *report) {
    return strcmp(report, "report-only") == 0 ||
           strcmp(report, "evaluate-only") == 0;
}

const char *latticra_seal_runtime_handoff_report_error_label(
    latticra_seal_runtime_handoff_report_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_EVALUATION:
        return "invalid-evaluation";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_EVALUATION:
        return "denied-evaluation";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF:
        return "denied-handoff";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_REPORT:
        return "denied-report";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT:
        return "missing-requested-report";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_UNKNOWN_REPORT:
        return "denied-unknown-report";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE:
        return "denied-crypto-graduation-gate";
    default:
        return "unknown";
    }
}

static void report_init(latticra_seal_runtime_handoff_report_t *report) {
    memset(report, 0, sizeof(*report));
    copy_literal(report->report_profile, sizeof(report->report_profile), "latticra-seal-runtime-handoff-report/0.1");
    copy_literal(report->crypto_graduation_gate_state, sizeof(report->crypto_graduation_gate_state), "not-required");
    copy_literal(report->report_state, sizeof(report->report_state), "denied-evaluation");
    report->crypto_graduation_gate_present = 0u;
    report->crypto_graduation_gate_passed = 0u;
    report->standard_expectations_met = 0u;
    report->local_verify_graduated = 0u;
    report->receipt_promotion_graduated = 0u;
    report->authority_promotion_allowed = 0u;
    report->verified = 0u;
    report->authority_usable = 0u;
    report->receipt_capability_gate_allowed = 0u;
    report->gate_allowed = 0u;
    report->effect_allowed = 0u;
    report->handoff_eligible = 0u;
    report->report_ready = 0u;
    report->handoff_performed = 0u;
    report->effect_performed = 0u;
    report->runtime_authority_granted = 0u;
    report->host_read_performed = 0u;
    report->host_write_performed = 0u;
    report->network_performed = 0u;
    report->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_INPUT;
    copy_literal(report->status, sizeof(report->status), "invalid-input");
}

static void copy_evaluation_metadata(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    const char *requested_report,
    latticra_seal_runtime_handoff_report_t *out) {
    copy_literal(out->handoff_profile, sizeof(out->handoff_profile), evaluation->handoff_profile);
    copy_literal(out->decision_profile, sizeof(out->decision_profile), evaluation->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), evaluation->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), evaluation->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), evaluation->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), evaluation->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), evaluation->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), evaluation->public_key_identity_label);
    copy_literal(out->crypto_graduation_profile, sizeof(out->crypto_graduation_profile), evaluation->crypto_graduation_profile);
    copy_literal(out->assurance_baseline_profile, sizeof(out->assurance_baseline_profile), evaluation->assurance_baseline_profile);
    copy_literal(out->crypto_graduation_gate_state, sizeof(out->crypto_graduation_gate_state), evaluation->crypto_graduation_gate_state);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), evaluation->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), evaluation->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), evaluation->requested_handoff);
    copy_literal(out->requested_report, sizeof(out->requested_report), requested_report);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), evaluation->requested_scope);
    out->crypto_graduation_gate_present = evaluation->crypto_graduation_gate_present;
    out->crypto_graduation_gate_passed = evaluation->crypto_graduation_gate_passed;
    out->standard_expectations_met = evaluation->standard_expectations_met;
    out->local_verify_graduated = evaluation->local_verify_graduated;
    out->receipt_promotion_graduated = evaluation->receipt_promotion_graduated;
    out->authority_promotion_allowed = evaluation->authority_promotion_allowed;
    out->verified = evaluation->verified;
    out->authority_usable = evaluation->authority_usable;
    out->receipt_capability_gate_allowed = evaluation->receipt_capability_gate_allowed;
    out->gate_allowed = evaluation->gate_allowed;
    copy_literal(out->gate_state, sizeof(out->gate_state), evaluation->gate_state);
    copy_literal(out->decision_state, sizeof(out->decision_state), evaluation->decision_state);
    out->effect_allowed = evaluation->effect_allowed;
    copy_literal(out->handoff_state, sizeof(out->handoff_state), evaluation->handoff_state);
    out->handoff_eligible = evaluation->handoff_eligible;
    out->handoff_performed = evaluation->handoff_performed;
    out->effect_performed = evaluation->effect_performed;
    out->runtime_authority_granted = evaluation->runtime_authority_granted;
    out->host_read_performed = evaluation->host_read_performed;
    out->host_write_performed = evaluation->host_write_performed;
    out->network_performed = evaluation->network_performed;
}

latticra_status_t latticra_seal_runtime_handoff_report_from_evaluation(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    const char *requested_report,
    latticra_seal_runtime_handoff_report_t *out) {
    int handoff_report;
    int handoff_evaluate;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    report_init(out);

    if (evaluation == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_evaluation_metadata(evaluation, requested_report, out);

    if (evaluation->error != LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_INVALID_EVALUATION;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-evaluation");
        copy_literal(out->status, sizeof(out->status), "invalid-evaluation");
        return LATTICRA_STATUS_OK;
    }

    if (evaluation->crypto_graduation_gate_present != 0u &&
        (evaluation->crypto_graduation_gate_passed != 1u ||
         evaluation->standard_expectations_met != 1u ||
         evaluation->local_verify_graduated != 1u ||
         evaluation->receipt_promotion_graduated != 1u ||
         evaluation->authority_promotion_allowed != 0u ||
         strcmp(evaluation->crypto_graduation_gate_state, "graduated-authority-neutral") != 0)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_CRYPTO_GRADUATION_GATE;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-crypto-graduation-gate");
        copy_literal(out->status, sizeof(out->status), "denied-crypto-graduation-gate");
        return LATTICRA_STATUS_OK;
    }

    if (evaluation->handoff_eligible != 1u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-handoff");
        return LATTICRA_STATUS_OK;
    }

    handoff_report = strcmp(evaluation->handoff_state, "eligible-report-only") == 0;
    handoff_evaluate = strcmp(evaluation->handoff_state, "eligible-evaluate-only") == 0;
    if (!handoff_report && !handoff_evaluate) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HANDOFF;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-handoff");
        copy_literal(out->status, sizeof(out->status), "denied-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (evaluation->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (evaluation->handoff_performed != 0u ||
        evaluation->effect_performed != 0u ||
        evaluation->host_read_performed != 0u ||
        evaluation->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_HOST_EFFECT;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (evaluation->network_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_NETWORK_EFFECT;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (requested_report == NULL || requested_report[0] == '\0') {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_MISSING_REQUESTED_REPORT;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "missing-requested-report");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_report(requested_report)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_UNKNOWN_REPORT;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-report");
        return LATTICRA_STATUS_OK;
    }

    if ((handoff_report && strcmp(requested_report, "report-only") != 0) ||
        (handoff_evaluate && strcmp(requested_report, "evaluate-only") != 0)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_DENIED_REPORT;
        copy_literal(out->report_state, sizeof(out->report_state), "denied-report");
        copy_literal(out->status, sizeof(out->status), "denied-report");
        return LATTICRA_STATUS_OK;
    }

    out->report_ready = 1u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_OK;

    if (strcmp(requested_report, "report-only") == 0) {
        copy_literal(out->report_state, sizeof(out->report_state), "ready-report-only");
    } else {
        copy_literal(out->report_state, sizeof(out->report_state), "ready-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "runtime-handoff-report-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_handoff_report_is_metadata_only(
    const latticra_seal_runtime_handoff_report_t *report) {
    if (report == NULL) {
        return 0;
    }

    return report->handoff_performed == 0u &&
           report->effect_performed == 0u &&
           report->runtime_authority_granted == 0u &&
           report->host_read_performed == 0u &&
           report->host_write_performed == 0u &&
           report->network_performed == 0u;
}

latticra_status_t latticra_seal_runtime_handoff_report_render(
    const latticra_seal_runtime_handoff_report_t *report,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (report == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME HANDOFF REPORT\n"
        "report_profile=%s\n"
        "handoff_profile=%s\n"
        "decision_profile=%s\n"
        "gate_profile=%s\n"
        "receipt_profile=%s\n"
        "verify_profile=%s\n"
        "message_digest_algorithm=%s\n"
        "message_digest_hex=%s\n"
        "public_key_identity_label=%s\n"
        "crypto_graduation_profile=%s\n"
        "assurance_baseline_profile=%s\n"
        "crypto_graduation_gate_state=%s\n"
        "requested_capability=%s\n"
        "requested_effect=%s\n"
        "requested_handoff=%s\n"
        "requested_report=%s\n"
        "requested_scope=%s\n"
        "crypto_graduation_gate_present=%u\n"
        "crypto_graduation_gate_passed=%u\n"
        "standard_expectations_met=%u\n"
        "local_verify_graduated=%u\n"
        "receipt_promotion_graduated=%u\n"
        "authority_promotion_allowed=%u\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "decision_state=%s\n"
        "effect_allowed=%u\n"
        "handoff_state=%s\n"
        "handoff_eligible=%u\n"
        "report_state=%s\n"
        "report_ready=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        report->report_profile,
        report->handoff_profile,
        report->decision_profile,
        report->gate_profile,
        report->receipt_profile,
        report->verify_profile,
        report->message_digest_algorithm,
        report->message_digest_hex,
        report->public_key_identity_label,
        report->crypto_graduation_profile,
        report->assurance_baseline_profile,
        report->crypto_graduation_gate_state,
        report->requested_capability,
        report->requested_effect,
        report->requested_handoff,
        report->requested_report,
        report->requested_scope,
        report->crypto_graduation_gate_present,
        report->crypto_graduation_gate_passed,
        report->standard_expectations_met,
        report->local_verify_graduated,
        report->receipt_promotion_graduated,
        report->authority_promotion_allowed,
        report->verified,
        report->authority_usable,
        report->receipt_capability_gate_allowed,
        report->gate_allowed,
        report->gate_state,
        report->decision_state,
        report->effect_allowed,
        report->handoff_state,
        report->handoff_eligible,
        report->report_state,
        report->report_ready,
        report->handoff_performed,
        report->effect_performed,
        report->runtime_authority_granted,
        report->host_read_performed,
        report->host_write_performed,
        report->network_performed,
        latticra_seal_runtime_handoff_report_error_label(report->error),
        report->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
