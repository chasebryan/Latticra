#ifndef LATTICRA_TRI_PLANE_TRANSITION_H
#define LATTICRA_TRI_PLANE_TRANSITION_H

#include "latticra/state_lattice.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LATTICRA_MOVEMENT_UP = 0,
    LATTICRA_MOVEMENT_DOWN = 1,
    LATTICRA_MOVEMENT_LEFT = 2,
    LATTICRA_MOVEMENT_RIGHT = 3,
    LATTICRA_MOVEMENT_ENTER = 4,
    LATTICRA_MOVEMENT_BACK = 5,
    LATTICRA_MOVEMENT_ROOT = 6,
    LATTICRA_MOVEMENT_UNKNOWN = 7
} latticra_movement_t;

typedef enum {
    LATTICRA_TRANSITION_ALLOWED_PREVIEW = 0,
    LATTICRA_TRANSITION_DENIED = 1
} latticra_transition_result_t;

typedef enum {
    LATTICRA_TRANSITION_REASON_OK = 0,
    LATTICRA_TRANSITION_REASON_NULL_ARGUMENT = 1,
    LATTICRA_TRANSITION_REASON_UNKNOWN_DIRECTION = 2,
    LATTICRA_TRANSITION_REASON_LOCK_CLOSED = 3,
    LATTICRA_TRANSITION_REASON_RISK_HIGH = 4,
    LATTICRA_TRANSITION_REASON_ROLLBACK_UNAVAILABLE = 5
} latticra_transition_reason_t;

typedef struct {
    latticra_transition_result_t result;
    latticra_transition_reason_t reason;
    latticra_movement_t movement;
    latticra_state_lattice_t next_state;
    int origin_mutated;
    int recovery_executed;
} latticra_transition_preview_t;

const char *latticra_movement_label(latticra_movement_t movement);
const char *latticra_transition_result_label(latticra_transition_result_t result);
const char *latticra_transition_reason_label(latticra_transition_reason_t reason);

latticra_status_t latticra_tri_plane_preview(
    const latticra_state_lattice_t *current,
    latticra_movement_t movement,
    latticra_transition_preview_t *preview);

#ifdef __cplusplus
}
#endif

#endif
