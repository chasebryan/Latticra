#include "latticra/substrate/effect.h"

#include <stdio.h>
#include <string.h>

/* Current profile: still heavily report-only by default.
 * This will be flipped to effect-capable builds later.
 */
static int g_effects_enabled = 0;

int latticra_substrate_effects_enabled(void) {
    return g_effects_enabled;
}

/* Placeholder implementation.
 * In real effect mode this will:
 *   - Validate context against contracts
 *   - Perform the narrow effect (file, command, etc.)
 *   - Record rich evidence
 *   - Return structured result
 */
latticra_status_t latticra_substrate_execute_effect(
    const latticra_effect_context_t *ctx,
    latticra_effect_result_t *result
) {
    if (result == NULL) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(result, 0, sizeof(*result));

    if (!latticra_substrate_effects_enabled()) {
        result->status = LATTICRA_STATUS_OK;
        result->effect_performed = 0;
        result->evidence_written = 0;
        snprintf(result->error_message, sizeof(result->error_message),
                 "Effects disabled in current profile (report-only mode)");
        return LATTICRA_STATUS_OK;
    }

    if (ctx == NULL) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        snprintf(result->error_message, sizeof(result->error_message), "Null effect context");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    /* TODO (Phase 1): Actual effect dispatch based on task->record.requested_effect */
    result->status = LATTICRA_STATUS_OK;
    result->effect_performed = 0;   /* Still disabled */
    result->evidence_written = 0;
    snprintf(result->error_message, sizeof(result->error_message),
             "Real effect execution not yet implemented in this build profile");

    return LATTICRA_STATUS_OK;
}
