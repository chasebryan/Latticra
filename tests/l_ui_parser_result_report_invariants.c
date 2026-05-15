#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static const char VALID_FIXTURE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"operator-visible Nucleus preview report\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"Latticra / Nucleus Preview / effect-bound\" }\n"
    "  rail state {\n"
    "    field origin bind state.origin\n"
    "    field route bind state.route\n"
    "    field axis bind state.axis\n"
    "    field path bind state.path\n"
    "  }\n"
    "  rail trace {\n"
    "    field breadcrumb bind state.breadcrumb\n"
    "    field trace bind state.trace\n"
    "  }\n"
    "  rail safety {\n"
    "    field health bind state.health\n"
    "    field risk bind state.risk\n"
    "    field lock bind state.lock\n"
    "    field dark_phase bind state.dark_phase\n"
    "  }\n"
    "  rail gates {\n"
    "    field safe_portal bind state.safe_portal\n"
    "    field rollback bind state.rollback\n"
    "  }\n"
    "  rail effects {\n"
    "    field host bind state.host_effect\n"
    "    field external bind state.external_effect\n"
    "    field requested bind preview.requested_effect\n"
    "  }\n"
    "  rail policy {\n"
    "    field request bind preview.request\n"
    "    field policy bind preview.policy\n"
    "    field reason bind preview.reason\n"
    "  }\n"
    "  rail execution {\n"
    "    field executed bind preview.executed\n"
    "    field mutation bind preview.mutation_allowed\n"
    "    field server bind preview.server_interaction_allowed\n"
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"preview-only no-live-movement no-host-effect no-external-effect\" }\n"
    "}\n";

static int report_contains_valid_parse_summary(void) {
    latticra_l_ui_parse_result_t result;
    char report[LATTICRA_L_UI_PARSE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), &result) == LATTICRA_STATUS_OK,
        "valid source should parse before report");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "valid result report should fit default buffer");

    EXPECT_TRUE(strstr(report, "L-UI PARSE RESULT") != 0, "report title");
    EXPECT_TRUE(strstr(report, "status=0") != 0, "report status");
    EXPECT_TRUE(strstr(report, "error=ok") != 0, "report ok error");
    EXPECT_TRUE(strstr(report, "line=1") != 0, "report line");
    EXPECT_TRUE(strstr(report, "column=1") != 0, "report column");
    EXPECT_TRUE(strstr(report, "card_name=NucleusPreview") != 0, "report card name");
    EXPECT_TRUE(strstr(report, "rail_count=9") != 0, "report rail count");
    EXPECT_TRUE(strstr(report, "field_count=23") != 0, "report field count");
    EXPECT_TRUE(strstr(report, "effect=none") != 0, "report effect");
    EXPECT_TRUE(strstr(report, "boundary=preview_only") != 0, "report boundary");
    EXPECT_TRUE(strstr(report, "no_effect=1") != 0, "report no effect");
    EXPECT_TRUE(strstr(report, "execution_allowed=0") != 0, "report execution flag");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0") != 0, "report mutation flag");
    EXPECT_TRUE(strstr(report, "server_allowed=0") != 0, "report server flag");
    EXPECT_TRUE(strstr(report, "recovery_allowed=0") != 0, "report recovery flag");
    EXPECT_TRUE(strstr(report, "hardware_allowed=0") != 0, "report hardware flag");

    return 0;
}

static int report_contains_error_parse_summary(void) {
    latticra_l_ui_parse_result_t result;
    char report[LATTICRA_L_UI_PARSE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_l_ui_parse_source("", 0u, &result) == LATTICRA_STATUS_OK,
        "empty source should classify before report");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "error result report should fit default buffer");

    EXPECT_TRUE(strstr(report, "L-UI PARSE RESULT") != 0, "error report title");
    EXPECT_TRUE(strstr(report, "error=empty_source") != 0, "error report error label");
    EXPECT_TRUE(strstr(report, "rail_count=0") != 0, "error report rail count");
    EXPECT_TRUE(strstr(report, "field_count=0") != 0, "error report field count");
    EXPECT_TRUE(strstr(report, "no_effect=1") != 0, "error report no effect");
    EXPECT_TRUE(strstr(report, "execution_allowed=0") != 0, "error report execution flag");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0") != 0, "error report mutation flag");
    EXPECT_TRUE(strstr(report, "server_allowed=0") != 0, "error report server flag");
    EXPECT_TRUE(strstr(report, "recovery_allowed=0") != 0, "error report recovery flag");
    EXPECT_TRUE(strstr(report, "hardware_allowed=0") != 0, "error report hardware flag");

    return 0;
}

static int report_rejects_bad_arguments_and_small_buffers(void) {
    latticra_l_ui_parse_result_t result;
    char report[LATTICRA_L_UI_PARSE_REPORT_MAX];
    char small[8];

    EXPECT_TRUE(
        latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), &result) == LATTICRA_STATUS_OK,
        "valid source should parse before argument tests");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL parse result should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL report buffer should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small report buffer should be rejected");

    return 0;
}

int main(void) {
    if (report_contains_valid_parse_summary() != 0) return 1;
    if (report_contains_error_parse_summary() != 0) return 1;
    if (report_rejects_bad_arguments_and_small_buffers() != 0) return 1;

    puts("l_ui_parser_result_report_invariants: ok");
    return 0;
}
