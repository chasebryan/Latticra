#include "latticra/l_ui_static_report.h"

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

static int l_ui_card_contains_required_rails(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();
    latticra_nucleus_preview_t preview;
    char report[LATTICRA_L_UI_REPORT_MAX];

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_TRANSITION_PREVIEW,
            LATTICRA_EFFECT_READ,
            &preview) == LATTICRA_STATUS_OK,
        "transition preview should classify before L-UI report");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(&state, &preview, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "L-UI report should fit default buffer");

    EXPECT_TRUE(strstr(report, "L-UI STATIC REPORT") != 0, "report title");
    EXPECT_TRUE(strstr(report, "kind=nucleus-preview") != 0, "report kind");
    EXPECT_TRUE(strstr(report, "rail.top=Latticra / Nucleus Preview / effect-bound") != 0, "top rail");
    EXPECT_TRUE(strstr(report, "rail.state=origin:0/0 route:ROOT axis:ROOT path:ROOT>0/0") != 0, "state rail");
    EXPECT_TRUE(strstr(report, "rail.trace=breadcrumb:ROOT trace:trace-preview") != 0, "trace rail");
    EXPECT_TRUE(strstr(report, "rail.safety=health:nominal risk:low lock:open dark_phase:off") != 0, "safety rail");
    EXPECT_TRUE(strstr(report, "rail.gates=safe_portal:planned rollback:available") != 0, "gate rail");
    EXPECT_TRUE(strstr(report, "rail.effects=host:none external:none requested:read") != 0, "effect rail");
    EXPECT_TRUE(strstr(report, "rail.policy=request:transition-preview policy:allow-preview reason:ok") != 0, "policy rail");
    EXPECT_TRUE(strstr(report, "rail.execution=executed:0 mutation:0 server:0 network:0 recovery:0 hardware:0") != 0, "execution rail");
    EXPECT_TRUE(
        strstr(report, "rail.bottom=preview-only no-live-movement no-host-effect no-external-effect") != 0,
        "bottom rail");

    return 0;
}

static int l_ui_card_handles_denied_requests(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();
    latticra_nucleus_preview_t preview;
    char report[LATTICRA_L_UI_REPORT_MAX];

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_RECOVERY_ACTION,
            LATTICRA_EFFECT_RECOVERY,
            &preview) == LATTICRA_STATUS_OK,
        "recovery request should classify before L-UI report");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(&state, &preview, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "denied L-UI report should fit default buffer");

    EXPECT_TRUE(strstr(report, "rail.effects=host:none external:none requested:recovery") != 0, "denied effect rail");
    EXPECT_TRUE(
        strstr(report, "rail.policy=request:recovery-action policy:deny reason:effect-requires-future-gate") != 0,
        "denied policy rail");
    EXPECT_TRUE(strstr(report, "rail.execution=executed:0 mutation:0 server:0 network:0 recovery:0 hardware:0") != 0, "denied execution rail");
    EXPECT_TRUE(
        strstr(report, "rail.bottom=preview-only no-live-movement no-host-effect no-external-effect") != 0,
        "denied bottom rail");

    return 0;
}

static int l_ui_card_rejects_bad_arguments_and_small_buffers(void) {
    latticra_state_lattice_t state = latticra_state_lattice_default();
    latticra_nucleus_preview_t preview;
    char report[LATTICRA_L_UI_REPORT_MAX];
    char small[8];

    EXPECT_TRUE(
        latticra_nucleus_classify_preview(
            LATTICRA_REQUEST_STATE_REPORT,
            LATTICRA_EFFECT_NONE,
            &preview) == LATTICRA_STATUS_OK,
        "state report should classify before argument tests");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(0, &preview, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL state should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(&state, 0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL preview should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(&state, &preview, 0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL buffer should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_nucleus_preview_card(&state, &preview, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small buffer should be rejected");

    return 0;
}

static int l_ui_labels_are_stable(void) {
    EXPECT_STR_EQ(
        latticra_l_ui_report_kind_label(LATTICRA_L_UI_REPORT_NUCLEUS_PREVIEW),
        "nucleus-preview",
        "L-UI report kind label");
    EXPECT_STR_EQ(
        latticra_l_ui_report_kind_label(LATTICRA_L_UI_REPORT_UNKNOWN),
        "unknown",
        "L-UI unknown kind label");

    return 0;
}

int main(void) {
    if (l_ui_card_contains_required_rails() != 0) {
        return 1;
    }
    if (l_ui_card_handles_denied_requests() != 0) {
        return 1;
    }
    if (l_ui_card_rejects_bad_arguments_and_small_buffers() != 0) {
        return 1;
    }
    if (l_ui_labels_are_stable() != 0) {
        return 1;
    }

    puts("l_ui_static_report_invariants: ok");
    return 0;
}
