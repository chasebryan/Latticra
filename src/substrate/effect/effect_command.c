#include "latticra/substrate/effect_command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/* Very conservative initial implementation.
 * In this early phase we still mostly refuse or simulate.
 * Real guarded execution will be filled in carefully.
 */
latticra_status_t latticra_substrate_execute_command(
    const latticra_effect_context_t *ctx,
    const latticra_effect_command_request_t *request,
    latticra_effect_command_result_t *result
) {
    if (result == NULL) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(result, 0, sizeof(*result));

    if (!latticra_substrate_effects_enabled()) {
        result->exit_code = -1;
        snprintf(result->stderr, sizeof(result->stderr),
                 "Effects disabled in current profile");
        return LATTICRA_STATUS_OK;
    }

    if (ctx == NULL || request == NULL) {
        result->exit_code = -1;
        snprintf(result->stderr, sizeof(result->stderr), "Null argument");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    /* === Phase 1 Guarded Execution (initially very strict) === */
    /* For now we refuse actual execution until contracts + allowlists are wired. */
    result->exit_code = 126; /* "command cannot be executed" convention */
    result->timed_out = 0;
    snprintf(result->stderr, sizeof(result->stderr),
             "Real command execution is not yet enabled in this build. "
             "This is the guard point for the first effectful capability.");

    /* In a real implementation we would:
       - Validate command against allowlist from contract
       - Set up pipes for stdout/stderr capture
       - fork + exec with restricted environment
       - Enforce timeouts
       - Record full evidence
    */

    return LATTICRA_STATUS_OK;
}
