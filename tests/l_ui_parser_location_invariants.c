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

static const char RAIL_ONLY_FIXTURE[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"x\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top {}\n"
    "  rail state {}\n"
    "  rail trace {}\n"
    "  rail safety {}\n"
    "  rail gates {}\n"
    "  rail effects {}\n"
    "  rail policy {}\n"
    "  rail execution {}\n"
    "  rail bottom {}\n"
    "}\n";

static void expected_location_for_index(
    const char *source,
    size_t target_index,
    size_t *line,
    size_t *column) {
    size_t index = 0u;
    size_t current_line = 1u;
    size_t current_column = 1u;
    size_t source_len = strlen(source);

    if (target_index > source_len) {
        target_index = source_len;
    }

    while (index < target_index) {
        if (source[index] == '\r') {
            if (index + 1u < source_len && source[index + 1u] == '\n') {
                index += 2u;
            } else {
                index += 1u;
            }
            current_line += 1u;
            current_column = 1u;
        } else if (source[index] == '\n') {
            index += 1u;
            current_line += 1u;
            current_column = 1u;
        } else {
            index += 1u;
            current_column += 1u;
        }
    }

    *line = current_line;
    *column = current_column;
}

static int expected_location_for_slice(
    const char *source,
    const char *needle,
    size_t *line,
    size_t *column) {
    const char *found = strstr(source, needle);
    if (found == 0) {
        return 1;
    }
    expected_location_for_index(source, (size_t)(found - source), line, column);
    return 0;
}

static int assert_error_at(
    const char *source,
    latticra_l_ui_parse_error_t expected_error,
    const char *needle,
    const char *message) {
    latticra_l_ui_parse_result_t result;
    size_t expected_line;
    size_t expected_column;

    EXPECT_TRUE(expected_location_for_slice(source, needle, &expected_line, &expected_column) == 0, message);
    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK,
        "parse should classify location source");
    EXPECT_TRUE(result.error == expected_error, message);
    EXPECT_TRUE(result.line == expected_line, message);
    EXPECT_TRUE(result.column == expected_column, message);
    EXPECT_TRUE(result.no_effect == 1, "location result no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "location result execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "location result mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "location result server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "location result recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "location result hardware flag");

    return 0;
}

static int unsupported_version_reports_precise_location(void) {
    const char source[] = "\n  lui 9.9\ncard NucleusPreview {}\n";
    return assert_error_at(
        source,
        LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION,
        "lui",
        "unsupported version location");
}

static int unsupported_effect_reports_effect_token_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  effect network\n"
        "  boundary preview_only\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "effect network", "effect location");
}

static int unsupported_boundary_reports_boundary_token_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  effect none\n"
        "  boundary live\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY, "boundary live", "boundary location");
}

static int unknown_binding_prefix_reports_binding_target_location(void) {
    char source[sizeof(RAIL_ONLY_FIXTURE) + 64u];
    (void)snprintf(source, sizeof(source), "%s  field bad bind host.value\n", RAIL_ONLY_FIXTURE);
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX, "host.value", "binding target location");
}

static int forbidden_marker_reports_marker_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  effect none\n"
        "  boundary preview_only\n"
        "  execute command\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER, "execute ", "forbidden marker location");
}

static int unterminated_string_reports_opening_quote_location(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"unterminated\n}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNTERMINATED_STRING, "\"unterminated", "unterminated string location");
}

static int unbalanced_open_brace_reports_opening_brace_location(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, "{", "open brace location");
}

static int unbalanced_close_brace_reports_closing_brace_location(void) {
    const char source[] = "lui 0.1\n}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, "}", "close brace location");
}

static int missing_effect_reports_card_body_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  boundary preview_only\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_MISSING_EFFECT, "{", "missing effect card body location");
}

static int missing_boundary_reports_card_body_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  effect none\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_MISSING_BOUNDARY, "{", "missing boundary card body location");
}

static int missing_rail_reports_card_body_location(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  effect none\n"
        "  boundary preview_only\n"
        "  rail top {}\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_MISSING_RAIL, "{", "missing rail card body location");
}

static int location_scanner_handles_lf_newlines(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "effect network", "LF newline location");
}

static int location_scanner_handles_crlf_newlines(void) {
    const char source[] = "lui 0.1\r\ncard NucleusPreview {\r\n  purpose \"x\"\r\n  effect network\r\n}\r\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "effect network", "CRLF newline location");
}

static int location_scanner_handles_cr_newlines(void) {
    const char source[] = "lui 0.1\rcard NucleusPreview {\r  purpose \"x\"\r  effect network\r}\r";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "effect network", "CR newline location");
}

static int location_columns_are_byte_based(void) {
    const char source[] =
        "lui 0.1\n"
        "card NucleusPreview {\n"
        "  purpose \"x\"\n"
        "  \303\251\303\251effect network\n"
        "}\n";
    return assert_error_at(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "effect network", "byte-based column location");
}

static int success_result_remains_line_one_column_one(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(
        latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), &result) == LATTICRA_STATUS_OK,
        "valid fixture should parse");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "valid fixture error");
    EXPECT_TRUE(result.line == 1u, "success line");
    EXPECT_TRUE(result.column == 1u, "success column");
    return 0;
}

static int error_locations_preserve_no_effect_flags(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";

    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK,
        "error fixture should classify");
    EXPECT_TRUE(result.no_effect == 1, "error no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "error execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "error mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "error server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "error recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "error hardware flag");
    return 0;
}

static int location_reports_are_deterministic(void) {
    latticra_l_ui_parse_result_t result_one;
    latticra_l_ui_parse_result_t result_two;
    char report_one[LATTICRA_L_UI_PARSE_REPORT_MAX];
    char report_two[LATTICRA_L_UI_PARSE_REPORT_MAX];
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";

    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, strlen(source), &result_one) == LATTICRA_STATUS_OK,
        "first location parse should classify");
    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, strlen(source), &result_two) == LATTICRA_STATUS_OK,
        "second location parse should classify");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result_one, report_one, sizeof(report_one)) == LATTICRA_STATUS_OK,
        "first report should render");
    EXPECT_TRUE(
        latticra_l_ui_parse_result_report(&result_two, report_two, sizeof(report_two)) == LATTICRA_STATUS_OK,
        "second report should render");
    EXPECT_TRUE(strcmp(report_one, report_two) == 0, "location reports should be deterministic");
    EXPECT_TRUE(strstr(report_one, "line=4") != 0, "location report line");
    EXPECT_TRUE(strstr(report_one, "column=3") != 0, "location report column");

    return 0;
}

int main(void) {
    if (unsupported_version_reports_precise_location() != 0) return 1;
    if (unsupported_effect_reports_effect_token_location() != 0) return 1;
    if (unsupported_boundary_reports_boundary_token_location() != 0) return 1;
    if (unknown_binding_prefix_reports_binding_target_location() != 0) return 1;
    if (forbidden_marker_reports_marker_location() != 0) return 1;
    if (unterminated_string_reports_opening_quote_location() != 0) return 1;
    if (unbalanced_open_brace_reports_opening_brace_location() != 0) return 1;
    if (unbalanced_close_brace_reports_closing_brace_location() != 0) return 1;
    if (missing_effect_reports_card_body_location() != 0) return 1;
    if (missing_boundary_reports_card_body_location() != 0) return 1;
    if (missing_rail_reports_card_body_location() != 0) return 1;
    if (location_scanner_handles_lf_newlines() != 0) return 1;
    if (location_scanner_handles_crlf_newlines() != 0) return 1;
    if (location_scanner_handles_cr_newlines() != 0) return 1;
    if (location_columns_are_byte_based() != 0) return 1;
    if (success_result_remains_line_one_column_one() != 0) return 1;
    if (error_locations_preserve_no_effect_flags() != 0) return 1;
    if (location_reports_are_deterministic() != 0) return 1;

    puts("l_ui_parser_location_invariants: ok");
    return 0;
}
