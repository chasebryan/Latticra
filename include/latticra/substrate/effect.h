#ifndef LATTICRA_SUBSTRATE_EFFECT_H
#define LATTICRA_SUBSTRATE_EFFECT_H

#include "latticra/nucleus_task.h"
#include "latticra/runtime_boundary.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Effect Execution Context.
 * Carries the validated task, boundary classification, and evidence requirements.
 */
typedef struct {
    const latticra_nucleus_task_result_t *task;
    const latticra_runtime_boundary_result_t *boundary;
    int require_evidence;
    int require_seal_approval;
    char evidence_path[512];
} latticra_effect_context_t;

/**
 * Result of attempting a real effect.
 */
typedef struct {
    latticra_status_t status;
    int effect_performed;
    int evidence_written;
    char error_message[256];
    unsigned int evidence_level;
} latticra_effect_result_t;

/**
 * Execute a validated, boundary-checked task as a real effect.
 * This is the main entry point for moving from "report-only" to effectful behavior.
 *
 * At v0.3.0edge → v0.4 transition, this should remain heavily gated.
 */
latticra_status_t latticra_substrate_execute_effect(
    const latticra_effect_context_t *ctx,
    latticra_effect_result_t *result
);

/**
 * Check whether the current build/profile supports real effects
 * or is still report-only.
 */
int latticra_substrate_effects_enabled(void);

#ifdef __cplusplus
}
#endif

#endif /* LATTICRA_SUBSTRATE_EFFECT_H */
