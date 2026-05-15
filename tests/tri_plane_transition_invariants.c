#include "latticra/tri_plane_transition.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", message, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

static void set_label(char *destination, size_t destination_len, const char *source) {
    (void)snprintf(destination, destination_len, "%s", source);
}

static int safe_right_transition_is_allowed_preview(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_RIGHT, &preview) == LATTICRA_STATUS_OK,
        "safe right preview should return ok");
    EXPECT_TRUE(
        preview.result == LATTICRA_TRANSITION_ALLOWED_PREVIEW,
        "safe right preview should be allowed-preview");
    EXPECT_TRUE(preview.reason == LATTICRA_TRANSITION_REASON_OK, "safe right reason should be ok");
    EXPECT_TRUE(preview.movement == LATTICRA_MOVEMENT_RIGHT, "movement should be right");
    EXPECT_STR_EQ(preview.next_state.origin, "0/0", "origin should remain stable");
    EXPECT_STR_EQ(preview.next_state.axis, "RIGHT", "axis should preview right");
    EXPECT_STR_EQ(preview.next_state.path, "ROOT>0/1", "path should preview right");
    EXPECT_STR_EQ(preview.next_state.breadcrumb, "ROOT>RIGHT", "breadcrumb should preview right");
    EXPECT_TRUE(preview.origin_mutated == 0, "origin must not be marked mutated");
    EXPECT_TRUE(preview.recovery_executed == 0, "recovery must not execute");
    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&preview.next_state), "next state must be no-effect");

    return 0;
}

static int input_state_is_not_mutated(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_DOWN, &preview) == LATTICRA_STATUS_OK,
        "down preview should return ok");
    EXPECT_STR_EQ(current.origin, "0/0", "input origin should remain stable");
    EXPECT_STR_EQ(current.route, "ROOT", "input route should remain stable");
    EXPECT_STR_EQ(current.axis, "ROOT", "input axis should remain stable");
    EXPECT_STR_EQ(current.path, "ROOT>0/0", "input path should remain stable");
    EXPECT_STR_EQ(current.breadcrumb, "ROOT", "input breadcrumb should remain stable");
    EXPECT_TRUE(current.host_effect == LATTICRA_EFFECT_NONE, "input host effect should remain none");
    EXPECT_TRUE(current.external_effect == LATTICRA_EFFECT_NONE, "input external effect should remain none");

    return 0;
}

static int unknown_direction_is_denied_without_effects(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_UNKNOWN, &preview) == LATTICRA_STATUS_OK,
        "unknown direction should return ok with denied result");
    EXPECT_TRUE(preview.result == LATTICRA_TRANSITION_DENIED, "unknown direction should be denied");
    EXPECT_TRUE(
        preview.reason == LATTICRA_TRANSITION_REASON_UNKNOWN_DIRECTION,
        "unknown direction reason should be preserved");
    EXPECT_STR_EQ(preview.next_state.path, "ROOT>0/0", "denied path should remain current path");
    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&preview.next_state), "denied state should be no-effect");

    return 0;
}

static int closed_lock_denies_transition(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;
    set_label(current.lock, sizeof(current.lock), "closed");

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_RIGHT, &preview) == LATTICRA_STATUS_OK,
        "closed lock transition should return ok with denied result");
    EXPECT_TRUE(preview.result == LATTICRA_TRANSITION_DENIED, "closed lock should deny");
    EXPECT_TRUE(preview.reason == LATTICRA_TRANSITION_REASON_LOCK_CLOSED, "closed lock reason");
    EXPECT_STR_EQ(preview.next_state.lock, "closed", "denied preview should preserve lock");
    EXPECT_STR_EQ(preview.next_state.path, "ROOT>0/0", "denied preview should preserve path");
    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&preview.next_state), "closed lock denied state should be no-effect");

    return 0;
}

static int high_risk_denies_transition(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;
    set_label(current.risk, sizeof(current.risk), "high");

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_ENTER, &preview) == LATTICRA_STATUS_OK,
        "high risk transition should return ok with denied result");
    EXPECT_TRUE(preview.result == LATTICRA_TRANSITION_DENIED, "high risk should deny");
    EXPECT_TRUE(preview.reason == LATTICRA_TRANSITION_REASON_RISK_HIGH, "high risk reason");
    EXPECT_STR_EQ(preview.next_state.risk, "high", "denied preview should preserve risk");
    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&preview.next_state), "high risk denied state should be no-effect");

    return 0;
}

static int back_requires_available_rollback(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;
    set_label(current.rollback, sizeof(current.rollback), "unavailable");

    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_BACK, &preview) == LATTICRA_STATUS_OK,
        "back without rollback should return ok with denied result");
    EXPECT_TRUE(preview.result == LATTICRA_TRANSITION_DENIED, "back without rollback should deny");
    EXPECT_TRUE(
        preview.reason == LATTICRA_TRANSITION_REASON_ROLLBACK_UNAVAILABLE,
        "back denied reason should be rollback unavailable");
    EXPECT_TRUE(preview.recovery_executed == 0, "back denial must not execute recovery");
    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&preview.next_state), "back denied state should be no-effect");

    return 0;
}

static int labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_movement_label(LATTICRA_MOVEMENT_RIGHT), "right", "movement label");
    EXPECT_STR_EQ(
        latticra_transition_result_label(LATTICRA_TRANSITION_ALLOWED_PREVIEW),
        "allowed-preview",
        "result label");
    EXPECT_STR_EQ(
        latticra_transition_reason_label(LATTICRA_TRANSITION_REASON_LOCK_CLOSED),
        "lock-closed",
        "reason label");

    return 0;
}

static int null_arguments_are_rejected(void) {
    latticra_state_lattice_t current = latticra_state_lattice_default();
    latticra_transition_preview_t preview;

    EXPECT_TRUE(
        latticra_tri_plane_preview(NULL, LATTICRA_MOVEMENT_RIGHT, &preview) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL current should be rejected");
    EXPECT_TRUE(
        latticra_tri_plane_preview(&current, LATTICRA_MOVEMENT_RIGHT, NULL) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL preview should be rejected");

    return 0;
}

int main(void) {
    if (safe_right_transition_is_allowed_preview() != 0) {
        return 1;
    }
    if (input_state_is_not_mutated() != 0) {
        return 1;
    }
    if (unknown_direction_is_denied_without_effects() != 0) {
        return 1;
    }
    if (closed_lock_denies_transition() != 0) {
        return 1;
    }
    if (high_risk_denies_transition() != 0) {
        return 1;
    }
    if (back_requires_available_rollback() != 0) {
        return 1;
    }
    if (labels_are_stable() != 0) {
        return 1;
    }
    if (null_arguments_are_rejected() != 0) {
        return 1;
    }

    puts("tri_plane_transition_invariants: ok");
    return 0;
}
