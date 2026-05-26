#include "latticra/nucleus_preview.h"

#include <stdio.h>

static int effect_is_preview_allowed(latticra_effect_t effect) {
    return effect == LATTICRA_EFFECT_NONE || effect == LATTICRA_EFFECT_READ;
}

static int request_is_preview_allowed(latticra_request_kind_t kind) {
    return kind == LATTICRA_REQUEST_STATE_REPORT ||
           kind == LATTICRA_REQUEST_TRANSITION_PREVIEW;
}

const char *latticra_request_kind_label(latticra_request_kind_t kind) {
    switch (kind) {
    case LATTICRA_REQUEST_STATE_REPORT:
        return "state-report";
    case LATTICRA_REQUEST_TRANSITION_PREVIEW:
        return "transition-preview";
    case LATTICRA_REQUEST_SERVER_INTERACTION:
        return "server-interaction";
    case LATTICRA_REQUEST_SELF_UPDATE:
        return "self-update";
    case LATTICRA_REQUEST_RECOVERY_ACTION:
        return "recovery-action";
    case LATTICRA_REQUEST_HARDWARE_ACTION:
        return "hardware-action";
    case LATTICRA_REQUEST_UNKNOWN:
    default:
        return "unknown";
    }
}

const char *latticra_policy_result_label(latticra_policy_result_t result) {
    switch (result) {
    case LATTICRA_POLICY_ALLOW_PREVIEW:
        return "allow-preview";
    case LATTICRA_POLICY_DENY:
        return "deny";
    default:
        return "unknown";
    }
}

const char *latticra_policy_reason_label(latticra_policy_reason_t reason) {
    switch (reason) {
    case LATTICRA_POLICY_REASON_OK:
        return "ok";
    case LATTICRA_POLICY_REASON_NULL_ARGUMENT:
        return "null-argument";
    case LATTICRA_POLICY_REASON_UNKNOWN_REQUEST:
        return "unknown-request";
    case LATTICRA_POLICY_REASON_EFFECT_BLOCKED:
        return "effect-blocked";
    case LATTICRA_POLICY_REASON_EFFECT_REQUIRES_FUTURE_GATE:
        return "effect-requires-future-gate";
    default:
        return "unknown";
    }
}

latticra_status_t latticra_nucleus_classify_preview(
    latticra_request_kind_t request_kind,
    latticra_effect_t requested_effect,
    latticra_nucleus_preview_t *preview) {
    if (preview == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    preview->request_kind = request_kind;
    preview->requested_effect = requested_effect;
    preview->policy_result = LATTICRA_POLICY_DENY;
    preview->policy_reason = LATTICRA_POLICY_REASON_EFFECT_BLOCKED;
    preview->executed = 0;
    preview->mutation_allowed = 0;
    preview->server_interaction_allowed = 0;
    preview->network_allowed = 0;
    preview->recovery_allowed = 0;
    preview->hardware_allowed = 0;

    if (request_kind == LATTICRA_REQUEST_UNKNOWN) {
        preview->policy_reason = LATTICRA_POLICY_REASON_UNKNOWN_REQUEST;
        return LATTICRA_STATUS_OK;
    }

    if (!request_is_preview_allowed(request_kind)) {
        preview->policy_reason = LATTICRA_POLICY_REASON_EFFECT_REQUIRES_FUTURE_GATE;
        return LATTICRA_STATUS_OK;
    }

    if (!effect_is_preview_allowed(requested_effect)) {
        preview->policy_reason = LATTICRA_POLICY_REASON_EFFECT_BLOCKED;
        return LATTICRA_STATUS_OK;
    }

    preview->policy_result = LATTICRA_POLICY_ALLOW_PREVIEW;
    preview->policy_reason = LATTICRA_POLICY_REASON_OK;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_nucleus_preview_report(
    const latticra_nucleus_preview_t *preview,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (preview == 0 || buffer == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA NUCLEUS PREVIEW\n"
        "request=%s\n"
        "requested_effect=%s\n"
        "policy=%s\n"
        "reason=%s\n"
        "executed=%d\n"
        "mutation_allowed=%d\n"
        "server_interaction_allowed=%d\n"
        "network_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n",
        latticra_request_kind_label(preview->request_kind),
        latticra_effect_label(preview->requested_effect),
        latticra_policy_result_label(preview->policy_result),
        latticra_policy_reason_label(preview->policy_reason),
        preview->executed,
        preview->mutation_allowed,
        preview->server_interaction_allowed,
        preview->network_allowed,
        preview->recovery_allowed,
        preview->hardware_allowed);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
