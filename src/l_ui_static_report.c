#include "latticra/l_ui_static_report.h"

#include <stdio.h>

const char *latticra_l_ui_report_kind_label(latticra_l_ui_report_kind_t kind) {
    switch (kind) {
    case LATTICRA_L_UI_REPORT_NUCLEUS_PREVIEW:
        return "nucleus-preview";
    case LATTICRA_L_UI_REPORT_UNKNOWN:
    default:
        return "unknown";
    }
}

latticra_status_t latticra_l_ui_nucleus_preview_card(
    const latticra_state_lattice_t *state,
    const latticra_nucleus_preview_t *preview,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (state == 0 || preview == 0 || buffer == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "L-UI STATIC REPORT\n"
        "kind=%s\n"
        "rail.top=Latticra / Nucleus Preview / effect-bound\n"
        "rail.state=origin:%s route:%s axis:%s path:%s\n"
        "rail.trace=breadcrumb:%s trace:%s\n"
        "rail.safety=health:%s risk:%s lock:%s dark_phase:%s\n"
        "rail.gates=safe_portal:%s rollback:%s\n"
        "rail.effects=host:%s external:%s requested:%s\n"
        "rail.policy=request:%s policy:%s reason:%s\n"
        "rail.execution=executed:%d mutation:%d server:%d network:%d recovery:%d hardware:%d\n"
        "rail.bottom=preview-only no-live-movement no-host-effect no-external-effect\n",
        latticra_l_ui_report_kind_label(LATTICRA_L_UI_REPORT_NUCLEUS_PREVIEW),
        state->origin,
        state->route,
        state->axis,
        state->path,
        state->breadcrumb,
        state->trace,
        state->health,
        state->risk,
        state->lock,
        state->dark_phase,
        state->safe_portal,
        state->rollback,
        latticra_effect_label(state->host_effect),
        latticra_effect_label(state->external_effect),
        latticra_effect_label(preview->requested_effect),
        latticra_request_kind_label(preview->request_kind),
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
