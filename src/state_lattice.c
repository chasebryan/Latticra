#include "latticra/state_lattice.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

latticra_state_lattice_t latticra_state_lattice_default(void) {
    latticra_state_lattice_t state;
    memset(&state, 0, sizeof(state));

    copy_literal(state.origin, sizeof(state.origin), "0/0");
    copy_literal(state.route, sizeof(state.route), "ROOT");
    copy_literal(state.axis, sizeof(state.axis), "ROOT");
    copy_literal(state.path, sizeof(state.path), "ROOT>0/0");
    copy_literal(state.breadcrumb, sizeof(state.breadcrumb), "ROOT");
    copy_literal(state.trace, sizeof(state.trace), "trace-preview");
    copy_literal(state.safe_portal, sizeof(state.safe_portal), "planned");
    copy_literal(state.rollback, sizeof(state.rollback), "available");
    copy_literal(state.health, sizeof(state.health), "nominal");
    copy_literal(state.risk, sizeof(state.risk), "low");
    copy_literal(state.lock, sizeof(state.lock), "open");
    copy_literal(state.dark_phase, sizeof(state.dark_phase), "off");
    state.host_effect = LATTICRA_EFFECT_NONE;
    state.external_effect = LATTICRA_EFFECT_NONE;

    return state;
}

const char *latticra_effect_label(latticra_effect_t effect) {
    switch (effect) {
    case LATTICRA_EFFECT_NONE:
        return "none";
    case LATTICRA_EFFECT_READ:
        return "read";
    case LATTICRA_EFFECT_LOCAL_MUTATION:
        return "local_mutation";
    case LATTICRA_EFFECT_HOST_MUTATION:
        return "host_mutation";
    case LATTICRA_EFFECT_NETWORK:
        return "network";
    case LATTICRA_EFFECT_HARDWARE:
        return "hardware";
    case LATTICRA_EFFECT_BOOT:
        return "boot";
    case LATTICRA_EFFECT_RECOVERY:
        return "recovery";
    case LATTICRA_EFFECT_EXTERNAL:
        return "external";
    default:
        return "unknown";
    }
}

int latticra_state_lattice_is_no_effect(const latticra_state_lattice_t *state) {
    if (state == NULL) {
        return 0;
    }
    return state->host_effect == LATTICRA_EFFECT_NONE &&
           state->external_effect == LATTICRA_EFFECT_NONE;
}

latticra_status_t latticra_state_lattice_report(
    const latticra_state_lattice_t *state,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (state == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA STATE LATTICE\n"
        "origin=%s\n"
        "route=%s\n"
        "axis=%s\n"
        "path=%s\n"
        "breadcrumb=%s\n"
        "trace=%s\n"
        "safe_portal=%s\n"
        "rollback=%s\n"
        "health=%s\n"
        "risk=%s\n"
        "lock=%s\n"
        "dark_phase=%s\n"
        "host_effect=%s\n"
        "external_effect=%s\n",
        state->origin,
        state->route,
        state->axis,
        state->path,
        state->breadcrumb,
        state->trace,
        state->safe_portal,
        state->rollback,
        state->health,
        state->risk,
        state->lock,
        state->dark_phase,
        latticra_effect_label(state->host_effect),
        latticra_effect_label(state->external_effect));

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
