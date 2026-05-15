#include "latticra/nucleus_preview.h"

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

static int state_report_no_effect_is_allowed_preview(void) {
    latticra_nucleus_preview_t preview;

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_STATE_REPORT,
            LATTICRA_EFFECT_NONE,
            &preview) == LATTICRA_STATUS_OK,
        "state report classification should return ok");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_ALLOW_PREVIEW, "state report should be allowed preview");
    EXPECT_TRUE(preview.policy_reason == LATTICRA_POLICY_REASON_OK, "state report reason should be ok");
    EXPECT_TRUE(preview.executed == 0, "state report preview must not execute");
    EXPECT_TRUE(preview.mutation_allowed == 0, "state report preview must not allow mutation");
    EXPECT_TRUE(preview.server_interaction_allowed == 0, "state report preview must not allow server interaction");
    EXPECT_TRUE(preview.recovery_allowed == 0, "state report preview must not allow recovery");
    EXPECT_TRUE(preview.hardware_allowed == 0, "state report preview must not allow hardware");

    return 0;
}

static int transition_preview_read_effect_is_allowed_preview(void) {
    latticra_nucleus_preview_t preview;

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_TRANSITION_PREVIEW,
            LATTICRA_EFFECT_READ,
            &preview) == LATTICRA_STATUS_OK,
        "transition preview read classification should return ok");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_ALLOW_PREVIEW, "transition read should be allowed preview");
    EXPECT_TRUE(preview.policy_reason == LATTICRA_POLICY_REASON_OK, "transition read reason should be ok");
    EXPECT_TRUE(preview.executed == 0, "transition preview must not execute");
    EXPECT_TRUE(preview.mutation_allowed == 0, "transition preview must not allow mutation");

    return 0;
}

static int mutating_effect_is_denied_for_preview_request(void) {
    latticra_nucleus_preview_t preview;

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_TRANSITION_PREVIEW,
            LATTICRA_EFFECT_LOCAL_MUTATION,
            &preview) == LATTICRA_STATUS_OK,
        "mutating preview classification should return ok with denied policy");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "mutating effect should deny");
    EXPECT_TRUE(preview.policy_reason == LATTICRA_POLICY_REASON_EFFECT_BLOCKED, "mutating effect blocked reason");
    EXPECT_TRUE(preview.executed == 0, "mutating denial must not execute");
    EXPECT_TRUE(preview.mutation_allowed == 0, "mutating denial must not allow mutation");

    return 0;
}

static int server_update_recovery_and_hardware_are_future_gated(void) {
    latticra_nucleus_preview_t preview;

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_SERVER_INTERACTION,
            LATTICRA_EFFECT_NETWORK,
            &preview) == LATTICRA_STATUS_OK,
        "server interaction should classify");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "server interaction should deny");
    EXPECT_TRUE(
        preview.policy_reason == LATTICRA_POLICY_REASON_EFFECT_REQUIRES_FUTURE_GATE,
        "server interaction requires future gate");
    EXPECT_TRUE(preview.server_interaction_allowed == 0, "server interaction must remain blocked");

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_SELF_UPDATE,
            LATTICRA_EFFECT_LOCAL_MUTATION,
            &preview) == LATTICRA_STATUS_OK,
        "self update should classify");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "self update should deny");
    EXPECT_TRUE(preview.mutation_allowed == 0, "self update must not allow mutation");

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_RECOVERY_ACTION,
            LATTICRA_EFFECT_RECOVERY,
            &preview) == LATTICRA_STATUS_OK,
        "recovery should classify");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "recovery should deny");
    EXPECT_TRUE(preview.recovery_allowed == 0, "recovery must remain blocked");

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_HARDWARE_ACTION,
            LATTICRA_EFFECT_HARDWARE,
            &preview) == LATTICRA_STATUS_OK,
        "hardware should classify");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "hardware should deny");
    EXPECT_TRUE(preview.hardware_allowed == 0, "hardware must remain blocked");

    return 0;
}

static int unknown_request_is_denied(void) {
    latticra_nucleus_preview_t preview;

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_UNKNOWN,
            LATTICRA_EFFECT_NONE,
            &preview) == LATTICRA_STATUS_OK,
        "unknown request should classify");
    EXPECT_TRUE(preview.policy_result == LATTICRA_POLICY_DENY, "unknown request should deny");
    EXPECT_TRUE(preview.policy_reason == LATTICRA_POLICY_REASON_UNKNOWN_REQUEST, "unknown request reason");
    EXPECT_TRUE(preview.executed == 0, "unknown request must not execute");

    return 0;
}

static int labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_request_kind_label(LATTICRA_REQUEST_STATE_REPORT), "state-report", "request kind label");
    EXPECT_STR_EQ(latticra_policy_result_label(LATTICRA_POLICY_ALLOW_PREVIEW), "allow-preview", "policy result label");
    EXPECT_STR_EQ(latticra_policy_reason_label(LATTICRA_POLICY_REASON_EFFECT_BLOCKED), "effect-blocked", "policy reason label");

    return 0;
}

static int null_preview_is_rejected(void) {
    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_STATE_REPORT,
            LATTICRA_EFFECT_NONE,
            0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL preview should be rejected");

    return 0;
}

int main(void) {
    if (state_report_no_effect_is_allowed_preview() != 0) {
        return 1;
    }
    if (transition_preview_read_effect_is_allowed_preview() != 0) {
        return 1;
    }
    if (mutating_effect_is_denied_for_preview_request() != 0) {
        return 1;
    }
    if (server_update_recovery_and_hardware_are_future_gated() != 0) {
        return 1;
    }
    if (unknown_request_is_denied() != 0) {
        return 1;
    }
    if (labels_are_stable() != 0) {
        return 1;
    }
    if (null_preview_is_rejected() != 0) {
        return 1;
    }

    puts("nucleus_preview_invariants: ok");
    return 0;
}
