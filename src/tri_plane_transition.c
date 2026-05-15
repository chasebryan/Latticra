#include "latticra/tri_plane_transition.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

static int label_equals(const char *actual, const char *expected) {
    return strcmp(actual, expected) == 0;
}

static void set_denied(
    latticra_transition_preview_t *preview,
    latticra_movement_t movement,
    latticra_transition_reason_t reason,
    const latticra_state_lattice_t *current) {
    preview->result = LATTICRA_TRANSITION_DENIED;
    preview->reason = reason;
    preview->movement = movement;
    preview->next_state = *current;
    preview->origin_mutated = 0;
    preview->recovery_executed = 0;
}

static void set_allowed(
    latticra_transition_preview_t *preview,
    latticra_movement_t movement,
    const latticra_state_lattice_t *current) {
    preview->result = LATTICRA_TRANSITION_ALLOWED_PREVIEW;
    preview->reason = LATTICRA_TRANSITION_REASON_OK;
    preview->movement = movement;
    preview->next_state = *current;
    preview->origin_mutated = 0;
    preview->recovery_executed = 0;
}

const char *latticra_movement_label(latticra_movement_t movement) {
    switch (movement) {
    case LATTICRA_MOVEMENT_UP:
        return "up";
    case LATTICRA_MOVEMENT_DOWN:
        return "down";
    case LATTICRA_MOVEMENT_LEFT:
        return "left";
    case LATTICRA_MOVEMENT_RIGHT:
        return "right";
    case LATTICRA_MOVEMENT_ENTER:
        return "enter";
    case LATTICRA_MOVEMENT_BACK:
        return "back";
    case LATTICRA_MOVEMENT_ROOT:
        return "root";
    case LATTICRA_MOVEMENT_UNKNOWN:
    default:
        return "unknown";
    }
}

const char *latticra_transition_result_label(latticra_transition_result_t result) {
    switch (result) {
    case LATTICRA_TRANSITION_ALLOWED_PREVIEW:
        return "allowed-preview";
    case LATTICRA_TRANSITION_DENIED:
        return "denied";
    default:
        return "unknown";
    }
}

const char *latticra_transition_reason_label(latticra_transition_reason_t reason) {
    switch (reason) {
    case LATTICRA_TRANSITION_REASON_OK:
        return "ok";
    case LATTICRA_TRANSITION_REASON_NULL_ARGUMENT:
        return "null-argument";
    case LATTICRA_TRANSITION_REASON_UNKNOWN_DIRECTION:
        return "unknown-direction";
    case LATTICRA_TRANSITION_REASON_LOCK_CLOSED:
        return "lock-closed";
    case LATTICRA_TRANSITION_REASON_RISK_HIGH:
        return "risk-high";
    case LATTICRA_TRANSITION_REASON_ROLLBACK_UNAVAILABLE:
        return "rollback-unavailable";
    default:
        return "unknown";
    }
}

latticra_status_t latticra_tri_plane_preview(
    const latticra_state_lattice_t *current,
    latticra_movement_t movement,
    latticra_transition_preview_t *preview) {
    if (current == NULL || preview == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (movement == LATTICRA_MOVEMENT_UNKNOWN) {
        set_denied(preview, movement, LATTICRA_TRANSITION_REASON_UNKNOWN_DIRECTION, current);
        return LATTICRA_STATUS_OK;
    }

    if (!label_equals(current->lock, "open")) {
        set_denied(preview, movement, LATTICRA_TRANSITION_REASON_LOCK_CLOSED, current);
        return LATTICRA_STATUS_OK;
    }

    if (label_equals(current->risk, "high")) {
        set_denied(preview, movement, LATTICRA_TRANSITION_REASON_RISK_HIGH, current);
        return LATTICRA_STATUS_OK;
    }

    if (movement == LATTICRA_MOVEMENT_BACK && !label_equals(current->rollback, "available")) {
        set_denied(preview, movement, LATTICRA_TRANSITION_REASON_ROLLBACK_UNAVAILABLE, current);
        return LATTICRA_STATUS_OK;
    }

    set_allowed(preview, movement, current);

    switch (movement) {
    case LATTICRA_MOVEMENT_UP:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "PARENT");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT");
        break;
    case LATTICRA_MOVEMENT_DOWN:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "CHILD");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/0>0/0");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT>CHILD");
        break;
    case LATTICRA_MOVEMENT_LEFT:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "LEFT");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/-1");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT>LEFT");
        break;
    case LATTICRA_MOVEMENT_RIGHT:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "RIGHT");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/1");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT>RIGHT");
        break;
    case LATTICRA_MOVEMENT_ENTER:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "FOCUS");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/0#focus");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT>FOCUS");
        break;
    case LATTICRA_MOVEMENT_BACK:
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "BACK");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/0");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT");
        break;
    case LATTICRA_MOVEMENT_ROOT:
        copy_literal(preview->next_state.route, sizeof(preview->next_state.route), "ROOT");
        copy_literal(preview->next_state.axis, sizeof(preview->next_state.axis), "ROOT");
        copy_literal(preview->next_state.path, sizeof(preview->next_state.path), "ROOT>0/0");
        copy_literal(preview->next_state.breadcrumb, sizeof(preview->next_state.breadcrumb), "ROOT");
        break;
    case LATTICRA_MOVEMENT_UNKNOWN:
    default:
        break;
    }

    preview->next_state.host_effect = LATTICRA_EFFECT_NONE;
    preview->next_state.external_effect = LATTICRA_EFFECT_NONE;

    return LATTICRA_STATUS_OK;
}
