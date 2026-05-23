#include "latticra/seal_runtime_handoff_evaluation.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int is_allowed_handoff(const char *handoff) {
    return strcmp(handoff, "report-only") == 0 ||
           strcmp(handoff, "evaluate-only") == 0;
}

const char *latticra_seal_runtime_handoff_evaluation_error_label(
    latticra_seal_runtime_handoff_evaluation_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK:
        return "ok";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION:
        return "invalid-decision";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION:
        return "denied-decision";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT:
        return "denied-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF:
        return "missing-requested-handoff";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF:
        return "denied-unknown-handoff";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY:
        return "denied-runtime-authority";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT:
        return "denied-host-effect";
    case LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT:
        return "denied-network-effect";
    default:
        return "unknown";
    }
}

static void evaluation_init(latticra_seal_runtime_handoff_evaluation_t *evaluation) {
    memset(evaluation, 0, sizeof(*evaluation));
    copy_literal(evaluation->handoff_profile, sizeof(evaluation->handoff_profile), "latticra-seal-runtime-handoff-evaluation/0.1");
    copy_literal(evaluation->handoff_state, sizeof(evaluation->handoff_state), "denied-decision");
    evaluation->verified = 0u;
    evaluation->authority_usable = 0u;
    evaluation->receipt_capability_gate_allowed = 0u;
    evaluation->gate_allowed = 0u;
    evaluation->effect_allowed = 0u;
    evaluation->handoff_eligible = 0u;
    evaluation->handoff_performed = 0u;
    evaluation->effect_performed = 0u;
    evaluation->runtime_authority_granted = 0u;
    evaluation->host_read_performed = 0u;
    evaluation->host_write_performed = 0u;
    evaluation->network_performed = 0u;
    evaluation->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_INPUT;
    copy_literal(evaluation->status, sizeof(evaluation->status), "invalid-input");
}

static void copy_decision_metadata(
    const latticra_seal_verified_effect_decision_t *decision,
    const char *requested_handoff,
    latticra_seal_runtime_handoff_evaluation_t *out) {
    copy_literal(out->decision_profile, sizeof(out->decision_profile), decision->decision_profile);
    copy_literal(out->gate_profile, sizeof(out->gate_profile), decision->gate_profile);
    copy_literal(out->receipt_profile, sizeof(out->receipt_profile), decision->receipt_profile);
    copy_literal(out->verify_profile, sizeof(out->verify_profile), decision->verify_profile);
    copy_literal(out->message_digest_algorithm, sizeof(out->message_digest_algorithm), decision->message_digest_algorithm);
    copy_literal(out->message_digest_hex, sizeof(out->message_digest_hex), decision->message_digest_hex);
    copy_literal(out->public_key_identity_label, sizeof(out->public_key_identity_label), decision->public_key_identity_label);
    copy_literal(out->requested_capability, sizeof(out->requested_capability), decision->requested_capability);
    copy_literal(out->requested_effect, sizeof(out->requested_effect), decision->requested_effect);
    copy_literal(out->requested_handoff, sizeof(out->requested_handoff), requested_handoff);
    copy_literal(out->requested_scope, sizeof(out->requested_scope), decision->requested_scope);
    out->verified = decision->verified;
    out->authority_usable = decision->authority_usable;
    out->receipt_capability_gate_allowed = decision->receipt_capability_gate_allowed;
    out->gate_allowed = decision->gate_allowed;
    copy_literal(out->gate_state, sizeof(out->gate_state), decision->gate_state);
    copy_literal(out->decision_state, sizeof(out->decision_state), decision->decision_state);
    out->effect_allowed = decision->effect_allowed;
    out->effect_performed = decision->effect_performed;
    out->runtime_authority_granted = decision->runtime_authority_granted;
    out->host_read_performed = decision->host_read_performed;
    out->host_write_performed = decision->host_write_performed;
    out->network_performed = decision->network_performed;
}

latticra_status_t latticra_seal_runtime_handoff_evaluation_from_decision(
    const latticra_seal_verified_effect_decision_t *decision,
    const char *requested_handoff,
    latticra_seal_runtime_handoff_evaluation_t *out) {
    int decision_report;
    int decision_evaluate;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    evaluation_init(out);

    if (decision == NULL) {
        return LATTICRA_STATUS_OK;
    }

    copy_decision_metadata(decision, requested_handoff, out);

    if (decision->error != LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_OK) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_INVALID_DECISION;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
        copy_literal(out->status, sizeof(out->status), "invalid-decision");
        return LATTICRA_STATUS_OK;
    }

    if (decision->effect_allowed != 1u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-effect");
        return LATTICRA_STATUS_OK;
    }

    decision_report = strcmp(decision->decision_state, "allowed-report-only") == 0;
    decision_evaluate = strcmp(decision->decision_state, "allowed-evaluate-only") == 0;
    if (!decision_report && !decision_evaluate) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_DECISION;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-decision");
        copy_literal(out->status, sizeof(out->status), "denied-decision");
        return LATTICRA_STATUS_OK;
    }

    if (decision->runtime_authority_granted != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_RUNTIME_AUTHORITY;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-runtime-authority");
        copy_literal(out->status, sizeof(out->status), "denied-runtime-authority");
        return LATTICRA_STATUS_OK;
    }

    if (decision->effect_performed != 0u ||
        decision->host_read_performed != 0u ||
        decision->host_write_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_HOST_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-host-effect");
        copy_literal(out->status, sizeof(out->status), "denied-host-effect");
        return LATTICRA_STATUS_OK;
    }

    if (decision->network_performed != 0u) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_NETWORK_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-network-effect");
        copy_literal(out->status, sizeof(out->status), "denied-network-effect");
        return LATTICRA_STATUS_OK;
    }

    if (requested_handoff == NULL || requested_handoff[0] == '\0') {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_MISSING_REQUESTED_HANDOFF;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "missing-requested-handoff");
        return LATTICRA_STATUS_OK;
    }

    if (!is_allowed_handoff(requested_handoff)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_UNKNOWN_HANDOFF;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-unknown-handoff");
        return LATTICRA_STATUS_OK;
    }

    if ((decision_report && strcmp(requested_handoff, "report-only") != 0) ||
        (decision_evaluate && strcmp(requested_handoff, "evaluate-only") != 0)) {
        out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_DENIED_EFFECT;
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "denied-effect");
        copy_literal(out->status, sizeof(out->status), "denied-effect");
        return LATTICRA_STATUS_OK;
    }

    out->handoff_eligible = 1u;
    out->handoff_performed = 0u;
    out->effect_performed = 0u;
    out->runtime_authority_granted = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->error = LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_OK;

    if (strcmp(requested_handoff, "report-only") == 0) {
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "eligible-report-only");
    } else {
        copy_literal(out->handoff_state, sizeof(out->handoff_state), "eligible-evaluate-only");
    }

    copy_literal(out->status, sizeof(out->status), "runtime-handoff-evaluation-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_runtime_handoff_evaluation_is_metadata_only(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation) {
    if (evaluation == NULL) {
        return 0;
    }

    return evaluation->handoff_performed == 0u &&
           evaluation->effect_performed == 0u &&
           evaluation->runtime_authority_granted == 0u &&
           evaluation->host_read_performed == 0u &&
           evaluation->host_write_performed == 0u &&
           evaluation->network_performed == 0u;
}

latticra_status_t latticra_seal_runtime_handoff_evaluation_report(
    const latticra_seal_runtime_handoff_evaluation_t *evaluation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evaluation == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL RUNTIME HANDOFF EVALUATION\n"
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
        "requested_scope=%s\n"
        "verified=%u\n"
        "authority_usable=%u\n"
        "receipt_capability_gate_allowed=%u\n"
        "gate_allowed=%u\n"
        "gate_state=%s\n"
        "decision_state=%s\n"
        "effect_allowed=%u\n"
        "handoff_state=%s\n"
        "handoff_eligible=%u\n"
        "handoff_performed=%u\n"
        "effect_performed=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "error=%s\n"
        "status=%s\n",
        evaluation->handoff_profile,
        evaluation->decision_profile,
        evaluation->gate_profile,
        evaluation->receipt_profile,
        evaluation->verify_profile,
        evaluation->message_digest_algorithm,
        evaluation->message_digest_hex,
        evaluation->public_key_identity_label,
        evaluation->requested_capability,
        evaluation->requested_effect,
        evaluation->requested_handoff,
        evaluation->requested_scope,
        evaluation->verified,
        evaluation->authority_usable,
        evaluation->receipt_capability_gate_allowed,
        evaluation->gate_allowed,
        evaluation->gate_state,
        evaluation->decision_state,
        evaluation->effect_allowed,
        evaluation->handoff_state,
        evaluation->handoff_eligible,
        evaluation->handoff_performed,
        evaluation->effect_performed,
        evaluation->runtime_authority_granted,
        evaluation->host_read_performed,
        evaluation->host_write_performed,
        evaluation->network_performed,
        latticra_seal_runtime_handoff_evaluation_error_label(evaluation->error),
        evaluation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
