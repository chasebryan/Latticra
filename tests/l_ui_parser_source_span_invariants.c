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

static int expected_span_for_slice(
    const char *source,
    const char *needle,
    latticra_l_ui_source_span_t *span) {
    const char *found = strstr(source, needle);
    if (found == 0) {
        return 1;
    }
    span->start_offset = (size_t)(found - source);
    span->end_offset = span->start_offset + strlen(needle);
    expected_location_for_index(source, span->start_offset, &span->start_line, &span->start_column);
    expected_location_for_index(source, span->end_offset, &span->end_line, &span->end_column);
    return 0;
}

static int expected_empty_span_for_slice(
    const char *source,
    const char *needle,
    latticra_l_ui_source_span_t *span) {
    const char *found = strstr(source, needle);
    if (found == 0) {
        return 1;
    }
    span->start_offset = (size_t)(found - source);
    span->end_offset = span->start_offset;
    expected_location_for_index(source, span->start_offset, &span->start_line, &span->start_column);
    span->end_line = span->start_line;
    span->end_column = span->start_column;
    return 0;
}

static int span_equals(const latticra_l_ui_source_span_t *actual, const latticra_l_ui_source_span_t *expected) {
    return actual->start_offset == expected->start_offset &&
           actual->end_offset == expected->end_offset &&
           actual->start_line == expected->start_line &&
           actual->start_column == expected->start_column &&
           actual->end_line == expected->end_line &&
           actual->end_column == expected->end_column;
}

static int assert_span_for_source(
    const char *source,
    latticra_l_ui_parse_error_t expected_error,
    const latticra_l_ui_source_span_t *expected_span,
    const char *message) {
    latticra_l_ui_parse_result_t result;

    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK,
        "span source should classify");
    EXPECT_TRUE(result.error == expected_error, message);
    EXPECT_TRUE(span_equals(&result.span, expected_span), message);
    EXPECT_TRUE(result.line == expected_span->start_line, message);
    EXPECT_TRUE(result.column == expected_span->start_column, message);
    EXPECT_TRUE(result.no_effect == 1, "span result no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "span result execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "span result mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "span result server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "span result recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "span result hardware flag");

    return 0;
}

static int unsupported_effect_reports_effect_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n  boundary preview_only\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "effect network", &expected) == 0, "expected effect span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &expected, "effect span");
}

static int unsupported_boundary_reports_boundary_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary live\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "boundary ", &expected) == 0, "expected boundary span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY, &expected, "boundary span");
}

static int unknown_binding_prefix_reports_binding_span(void) {
    char source[sizeof(RAIL_ONLY_FIXTURE) + 64u];
    latticra_l_ui_source_span_t expected;
    (void)snprintf(source, sizeof(source), "%s  field bad bind host.value\n", RAIL_ONLY_FIXTURE);
    EXPECT_TRUE(expected_span_for_slice(source, "host.", &expected) == 0, "expected binding span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX, &expected, "binding span");
}

static int forbidden_marker_reports_marker_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary preview_only\n  execute command\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "execute ", &expected) == 0, "expected marker span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER, &expected, "marker span");
}

static int unterminated_string_reports_string_span(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"unterminated\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "\"unterminated\n}\n", &expected) == 0, "expected string span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNTERMINATED_STRING, &expected, "string span");
}

static int unbalanced_open_brace_reports_brace_span(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "{", &expected) == 0, "expected open brace span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, &expected, "open brace span");
}

static int unbalanced_close_brace_reports_brace_span(void) {
    const char source[] = "lui 0.1\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "}", &expected) == 0, "expected close brace span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, &expected, "close brace span");
}

static int missing_effect_reports_empty_card_body_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  boundary preview_only\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_empty_span_for_slice(source, "{", &expected) == 0, "expected missing effect span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_MISSING_EFFECT, &expected, "missing effect span");
}

static int missing_boundary_reports_empty_card_body_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_empty_span_for_slice(source, "{", &expected) == 0, "expected missing boundary span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_MISSING_BOUNDARY, &expected, "missing boundary span");
}

static int missing_rail_reports_empty_card_body_span(void) {
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary preview_only\n  rail top {}\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_empty_span_for_slice(source, "{", &expected) == 0, "expected missing rail span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_MISSING_RAIL, &expected, "missing rail span");
}

static int span_offsets_are_zero_based(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "span offset parse");
    EXPECT_TRUE(result.span.start_offset == (size_t)(strstr(source, "effect network") - source), "zero-based start offset");
    return 0;
}

static int span_end_offset_is_exclusive(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "exclusive offset parse");
    EXPECT_TRUE(result.span.end_offset == result.span.start_offset + strlen("effect network"), "exclusive end offset");
    return 0;
}

static int span_line_columns_are_one_based(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "one-based span parse");
    EXPECT_TRUE(result.span.start_line > 0u, "span start line one-based");
    EXPECT_TRUE(result.span.start_column > 0u, "span start column one-based");
    EXPECT_TRUE(result.span.end_line > 0u, "span end line one-based");
    EXPECT_TRUE(result.span.end_column > 0u, "span end column one-based");
    return 0;
}

static int span_columns_are_byte_based(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  \303\251\303\251effect network\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "effect network", &expected) == 0, "expected byte span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &expected, "byte-based span column");
}

static int span_scanner_handles_lf_newlines(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "effect network", &expected) == 0, "expected LF span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &expected, "LF span");
}

static int span_scanner_handles_crlf_newlines(void) {
    const char source[] = "lui 0.1\r\ncard NucleusPreview {\r\n  purpose \"x\"\r\n  effect network\r\n}\r\n";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "effect network", &expected) == 0, "expected CRLF span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &expected, "CRLF span");
}

static int span_scanner_handles_cr_newlines(void) {
    const char source[] = "lui 0.1\rcard NucleusPreview {\r  purpose \"x\"\r  effect network\r}\r";
    latticra_l_ui_source_span_t expected;
    EXPECT_TRUE(expected_span_for_slice(source, "effect network", &expected) == 0, "expected CR span");
    return assert_span_for_source(source, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, &expected, "CR span");
}

static int span_metadata_preserves_no_effect_flags(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "no-effect span parse");
    EXPECT_TRUE(result.no_effect == 1, "span no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "span execution");
    EXPECT_TRUE(result.mutation_allowed == 0, "span mutation");
    EXPECT_TRUE(result.server_allowed == 0, "span server");
    EXPECT_TRUE(result.recovery_allowed == 0, "span recovery");
    EXPECT_TRUE(result.hardware_allowed == 0, "span hardware");
    return 0;
}

static int span_reports_are_deterministic(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result_one;
    latticra_l_ui_parse_result_t result_two;
    char report_one[LATTICRA_L_UI_PARSE_REPORT_MAX];
    char report_two[LATTICRA_L_UI_PARSE_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result_one) == LATTICRA_STATUS_OK, "first span parse");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result_two) == LATTICRA_STATUS_OK, "second span parse");
    EXPECT_TRUE(latticra_l_ui_parse_result_report(&result_one, report_one, sizeof(report_one)) == LATTICRA_STATUS_OK, "first span report");
    EXPECT_TRUE(latticra_l_ui_parse_result_report(&result_two, report_two, sizeof(report_two)) == LATTICRA_STATUS_OK, "second span report");
    EXPECT_TRUE(strcmp(report_one, report_two) == 0, "span reports deterministic");
    return 0;
}

static int parse_result_report_includes_span_fields(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    char report[LATTICRA_L_UI_PARSE_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "span report parse");
    EXPECT_TRUE(latticra_l_ui_parse_result_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "span report render");
    EXPECT_TRUE(strstr(report, "span_start_offset=") != 0, "parse report span start offset");
    EXPECT_TRUE(strstr(report, "span_end_offset=") != 0, "parse report span end offset");
    EXPECT_TRUE(strstr(report, "span_start_line=") != 0, "parse report span start line");
    EXPECT_TRUE(strstr(report, "span_start_column=") != 0, "parse report span start column");
    EXPECT_TRUE(strstr(report, "span_end_line=") != 0, "parse report span end line");
    EXPECT_TRUE(strstr(report, "span_end_column=") != 0, "parse report span end column");
    return 0;
}

static int diagnostic_report_includes_span_fields(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    char report[LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX];
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "diagnostic span parse");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "diagnostic span map");
    EXPECT_TRUE(latticra_l_ui_diagnostic_report(&diagnostic, report, sizeof(report)) == LATTICRA_STATUS_OK, "diagnostic span report");
    EXPECT_TRUE(strstr(report, "span_start_offset=") != 0, "diagnostic report span start offset");
    EXPECT_TRUE(strstr(report, "span_end_offset=") != 0, "diagnostic report span end offset");
    EXPECT_TRUE(strstr(report, "span_start_line=") != 0, "diagnostic report span start line");
    EXPECT_TRUE(strstr(report, "span_start_column=") != 0, "diagnostic report span start column");
    EXPECT_TRUE(strstr(report, "span_end_line=") != 0, "diagnostic report span end line");
    EXPECT_TRUE(strstr(report, "span_end_column=") != 0, "diagnostic report span end column");
    return 0;
}

static int diagnostic_copies_parse_result_span(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n}\n";
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;
    EXPECT_TRUE(latticra_l_ui_parse_source(source, strlen(source), &result) == LATTICRA_STATUS_OK, "diagnostic copy parse");
    EXPECT_TRUE(latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK, "diagnostic copy map");
    EXPECT_TRUE(span_equals(&diagnostic.span, &result.span), "diagnostic should copy parse result span");
    return 0;
}

static int success_span_uses_default_empty_span(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), &result) == LATTICRA_STATUS_OK, "success span parse");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "success span error");
    EXPECT_TRUE(result.span.start_offset == 0u, "success span start offset");
    EXPECT_TRUE(result.span.end_offset == 0u, "success span end offset");
    EXPECT_TRUE(result.span.start_line == 1u, "success span start line");
    EXPECT_TRUE(result.span.start_column == 1u, "success span start column");
    EXPECT_TRUE(result.span.end_line == 1u, "success span end line");
    EXPECT_TRUE(result.span.end_column == 1u, "success span end column");
    return 0;
}

int main(void) {
    if (unsupported_effect_reports_effect_span() != 0) return 1;
    if (unsupported_boundary_reports_boundary_span() != 0) return 1;
    if (unknown_binding_prefix_reports_binding_span() != 0) return 1;
    if (forbidden_marker_reports_marker_span() != 0) return 1;
    if (unterminated_string_reports_string_span() != 0) return 1;
    if (unbalanced_open_brace_reports_brace_span() != 0) return 1;
    if (unbalanced_close_brace_reports_brace_span() != 0) return 1;
    if (missing_effect_reports_empty_card_body_span() != 0) return 1;
    if (missing_boundary_reports_empty_card_body_span() != 0) return 1;
    if (missing_rail_reports_empty_card_body_span() != 0) return 1;
    if (span_offsets_are_zero_based() != 0) return 1;
    if (span_end_offset_is_exclusive() != 0) return 1;
    if (span_line_columns_are_one_based() != 0) return 1;
    if (span_columns_are_byte_based() != 0) return 1;
    if (span_scanner_handles_lf_newlines() != 0) return 1;
    if (span_scanner_handles_crlf_newlines() != 0) return 1;
    if (span_scanner_handles_cr_newlines() != 0) return 1;
    if (span_metadata_preserves_no_effect_flags() != 0) return 1;
    if (span_reports_are_deterministic() != 0) return 1;
    if (parse_result_report_includes_span_fields() != 0) return 1;
    if (diagnostic_report_includes_span_fields() != 0) return 1;
    if (diagnostic_copies_parse_result_span() != 0) return 1;
    if (success_span_uses_default_empty_span() != 0) return 1;

    puts("l_ui_parser_source_span_invariants: ok");
    return 0;
}
