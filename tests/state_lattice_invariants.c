#include "latticra/state_lattice.h"

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

static int default_fixture_has_required_labels(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();

    EXPECT_STR_EQ(state.origin, "0/0", "origin");
    EXPECT_STR_EQ(state.route, "ROOT", "route");
    EXPECT_STR_EQ(state.axis, "ROOT", "axis");
    EXPECT_STR_EQ(state.path, "ROOT>0/0", "path");
    EXPECT_STR_EQ(state.breadcrumb, "ROOT", "breadcrumb");
    EXPECT_STR_EQ(state.trace, "trace-preview", "trace");
    EXPECT_STR_EQ(state.safe_portal, "planned", "safe portal");
    EXPECT_STR_EQ(state.rollback, "available", "rollback");
    EXPECT_STR_EQ(state.health, "nominal", "health");
    EXPECT_STR_EQ(state.risk, "low", "risk");
    EXPECT_STR_EQ(state.lock, "open", "lock");
    EXPECT_STR_EQ(state.dark_phase, "off", "dark phase");

    return 0;
}

static int default_fixture_has_no_effects(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();

    EXPECT_TRUE(latticra_state_lattice_is_no_effect(&state), "default fixture should be no-effect");
    EXPECT_TRUE(state.host_effect == LATTICRA_EFFECT_NONE, "host effect should be none");
    EXPECT_TRUE(state.external_effect == LATTICRA_EFFECT_NONE, "external effect should be none");
    EXPECT_STR_EQ(latticra_effect_label(state.host_effect), "none", "host effect label");
    EXPECT_STR_EQ(latticra_effect_label(state.external_effect), "none", "external effect label");

    return 0;
}

static int report_contains_operator_visible_fields(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();
    char report[LATTICRA_REPORT_MAX];

    EXPECT_TRUE(
        latticra_state_lattice_report(&state, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report should fit default buffer");
    EXPECT_TRUE(strstr(report, "LATTICRA STATE LATTICE") != NULL, "report title");
    EXPECT_TRUE(strstr(report, "origin=0/0") != NULL, "report origin");
    EXPECT_TRUE(strstr(report, "route=ROOT") != NULL, "report route");
    EXPECT_TRUE(strstr(report, "axis=ROOT") != NULL, "report axis");
    EXPECT_TRUE(strstr(report, "path=ROOT>0/0") != NULL, "report path");
    EXPECT_TRUE(strstr(report, "safe_portal=planned") != NULL, "report safe portal");
    EXPECT_TRUE(strstr(report, "rollback=available") != NULL, "report rollback");
    EXPECT_TRUE(strstr(report, "dark_phase=off") != NULL, "report dark phase");
    EXPECT_TRUE(strstr(report, "host_effect=none") != NULL, "report host effect");
    EXPECT_TRUE(strstr(report, "external_effect=none") != NULL, "report external effect");

    return 0;
}

static int report_rejects_bad_arguments_and_small_buffers(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();
    char small[8];

    EXPECT_TRUE(
        latticra_state_lattice_report(NULL, small, sizeof(small)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL state should be rejected");
    EXPECT_TRUE(
        latticra_state_lattice_report(&state, NULL, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL buffer should be rejected");
    EXPECT_TRUE(
        latticra_state_lattice_report(&state, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small buffer should be rejected");

    return 0;
}

int main(void) {
    if (default_fixture_has_required_labels() != 0) {
        return 1;
    }
    if (default_fixture_has_no_effects() != 0) {
        return 1;
    }
    if (report_contains_operator_visible_fields() != 0) {
        return 1;
    }
    if (report_rejects_bad_arguments_and_small_buffers() != 0) {
        return 1;
    }

    puts("state_lattice_invariants: ok");
    return 0;
}
