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

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", message, (expected), (actual)); \
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

static int diagnostic_for_source(
    const char *source,
    latticra_l_ui_diagnostic_t *diagnostic) {
    latticra_l_ui_parse_result_t result;
    if (latticra_l_ui_parse_source(source, strlen(source), &result) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_l_ui_diagnostic_from_parse_result(&result, diagnostic) != LATTICRA_STATUS_OK) {
        return 1;
    }
    return 0;
}

static int expect_diagnostic(
    const char *source,
    latticra_l_ui_diagnostic_severity_t severity,
    const char *code,
    const char *message,
    const char *hint) {
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(diagnostic_for_source(source, &diagnostic) == 0, "diagnostic should be created");
    EXPECT_TRUE(diagnostic.severity == severity, "diagnostic severity");
    EXPECT_STR_EQ(diagnostic.code, code, "diagnostic code");
    EXPECT_STR_EQ(diagnostic.message, message, "diagnostic message");
    EXPECT_STR_EQ(diagnostic.hint, hint, "diagnostic hint");
    EXPECT_TRUE(diagnostic.line == 1u, "diagnostic line should be one-based");
    EXPECT_TRUE(diagnostic.column == 1u, "diagnostic column should be one-based");
    EXPECT_TRUE(diagnostic.no_effect == 1, "diagnostic no_effect flag");
    EXPECT_TRUE(diagnostic.execution_allowed == 0, "diagnostic execution flag");
    EXPECT_TRUE(diagnostic.mutation_allowed == 0, "diagnostic mutation flag");
    EXPECT_TRUE(diagnostic.server_allowed == 0, "diagnostic server flag");
    EXPECT_TRUE(diagnostic.recovery_allowed == 0, "diagnostic recovery flag");
    EXPECT_TRUE(diagnostic.hardware_allowed == 0, "diagnostic hardware flag");

    return 0;
}

static int ok_result_has_lui0000(void) {
    return expect_diagnostic(
        VALID_FIXTURE,
        LATTICRA_L_UI_DIAGNOSTIC_OK,
        "LUI0000",
        "Parse completed successfully.",
        "");
}

static int empty_source_reports_lui0002(void) {
    return expect_diagnostic(
        "",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0002",
        "L-UI source is empty.",
        "Provide L-UI source beginning with: lui 0.1");
}

static int unsupported_version_reports_lui0003(void) {
    return expect_diagnostic(
        "lui 9.9\ncard NucleusPreview {}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0003",
        "L-UI version is not supported.",
        "Use version header: lui 0.1");
}

static int missing_card_reports_lui0004(void) {
    return expect_diagnostic(
        "lui 0.1\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0004",
        "Required card declaration is missing.",
        "Add card NucleusPreview { ... }");
}

static int missing_purpose_reports_lui0005(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  effect none\n  boundary preview_only\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0005",
        "Required purpose clause is missing.",
        "Add a purpose string.");
}

static int missing_effect_reports_lui0006(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  boundary preview_only\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0006",
        "Required effect clause is missing.",
        "Add effect none.");
}

static int unsupported_effect_reports_lui0007(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n  boundary preview_only\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0007",
        "Effect declaration is not supported.",
        "Use only effect none.");
}

static int missing_boundary_reports_lui0008(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0008",
        "Required boundary clause is missing.",
        "Add boundary preview_only.");
}

static int unsupported_boundary_reports_lui0009(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary live\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0009",
        "Boundary declaration is not supported.",
        "Use only boundary preview_only.");
}

static int missing_rail_reports_lui0010(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary preview_only\n  rail top {}\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0010",
        "Required rail is missing.",
        "Add the required NucleusPreview rails.");
}

static int unknown_binding_prefix_reports_lui0012(void) {
    char source[sizeof(VALID_FIXTURE) + 64u];
    (void)snprintf(source, sizeof(source), "%s\nfield bad bind host.value\n", VALID_FIXTURE);
    return expect_diagnostic(
        source,
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0012",
        "Binding prefix is not supported.",
        "Use only state. or preview. binding prefixes.");
}

static int missing_required_binding_reports_lui0013(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n"
        "  purpose \"x\"\n  effect none\n  boundary preview_only\n"
        "  rail top {}\n  rail state {}\n  rail trace {}\n  rail safety {}\n  rail gates {}\n"
        "  rail effects {}\n  rail policy {}\n  rail execution {}\n  rail bottom {}\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0013",
        "Required binding is missing.",
        "Add all required NucleusPreview bindings.");
}

static int unterminated_string_reports_lui0014(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"unterminated\n}\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0014",
        "String literal is not terminated.",
        "Close the string literal.");
}

static int unbalanced_brace_reports_lui0015(void) {
    return expect_diagnostic(
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n",
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0015",
        "Braces are not balanced.",
        "Balance opening and closing braces.");
}

static int forbidden_marker_reports_lui0016(void) {
    char source[sizeof(VALID_FIXTURE) + 64u];
    (void)snprintf(source, sizeof(source), "%s\nexecute command\n", VALID_FIXTURE);
    return expect_diagnostic(
        source,
        LATTICRA_L_UI_DIAGNOSTIC_ERROR,
        "LUI0016",
        "Source contains a forbidden behavior marker.",
        "Remove behavior markers outside the static report grammar.");
}

static int source_too_large_reports_lui0017(void) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(
        latticra_l_ui_parse_source("x", LATTICRA_L_UI_SOURCE_MAX + 1u, &result) == LATTICRA_STATUS_OK,
        "oversized source should classify");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK,
        "oversized diagnostic should be created");
    EXPECT_TRUE(diagnostic.severity == LATTICRA_L_UI_DIAGNOSTIC_ERROR, "oversized severity");
    EXPECT_STR_EQ(diagnostic.code, "LUI0017", "oversized code");
    EXPECT_STR_EQ(diagnostic.message, "Source exceeds the supported size limit.", "oversized message");
    EXPECT_STR_EQ(diagnostic.hint, "Keep L-UI source at or below LATTICRA_L_UI_SOURCE_MAX.", "oversized hint");
    EXPECT_TRUE(diagnostic.no_effect == 1, "oversized no_effect");
    EXPECT_TRUE(diagnostic.execution_allowed == 0, "oversized execution");
    return 0;
}

static int internal_error_reports_lui0018(void) {
    latticra_l_ui_parse_result_t result;
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(
        latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), &result) == LATTICRA_STATUS_OK,
        "valid source should parse before internal override");
    result.error = LATTICRA_L_UI_PARSE_INTERNAL_ERROR;
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_from_parse_result(&result, &diagnostic) == LATTICRA_STATUS_OK,
        "internal diagnostic should be created");
    EXPECT_TRUE(diagnostic.severity == LATTICRA_L_UI_DIAGNOSTIC_INTERNAL, "internal severity");
    EXPECT_STR_EQ(diagnostic.code, "LUI0018", "internal code");
    EXPECT_STR_EQ(diagnostic.message, "Parser reached an internal error.", "internal message");
    EXPECT_STR_EQ(diagnostic.hint, "Report the internal parser error.", "internal hint");
    return 0;
}

static int error_diagnostics_preserve_no_effect_flags(void) {
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "error diagnostic should be created");
    EXPECT_TRUE(diagnostic.no_effect == 1, "error diagnostic no_effect");
    EXPECT_TRUE(diagnostic.execution_allowed == 0, "error diagnostic execution");
    EXPECT_TRUE(diagnostic.mutation_allowed == 0, "error diagnostic mutation");
    EXPECT_TRUE(diagnostic.server_allowed == 0, "error diagnostic server");
    EXPECT_TRUE(diagnostic.recovery_allowed == 0, "error diagnostic recovery");
    EXPECT_TRUE(diagnostic.hardware_allowed == 0, "error diagnostic hardware");
    return 0;
}

static int line_and_column_are_one_based(void) {
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "line diagnostic should be created");
    EXPECT_TRUE(diagnostic.line == 1u, "diagnostic line");
    EXPECT_TRUE(diagnostic.column == 1u, "diagnostic column");
    return 0;
}

static int messages_are_stable(void) {
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "message diagnostic should be created");
    EXPECT_STR_EQ(diagnostic.message, "L-UI source is empty.", "stable message");
    return 0;
}

static int hints_are_stable(void) {
    latticra_l_ui_diagnostic_t diagnostic;

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "hint diagnostic should be created");
    EXPECT_STR_EQ(
        diagnostic.hint,
        "Provide L-UI source beginning with: lui 0.1",
        "stable hint");
    return 0;
}

static int diagnostic_report_contains_required_fields(void) {
    latticra_l_ui_diagnostic_t diagnostic;
    char report[LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX];

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "report diagnostic should be created");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_report(&diagnostic, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "diagnostic report should fit default buffer");
    EXPECT_TRUE(strstr(report, "L-UI PARSE DIAGNOSTIC") != 0, "report title");
    EXPECT_TRUE(strstr(report, "severity=error") != 0, "report severity");
    EXPECT_TRUE(strstr(report, "code=LUI0002") != 0, "report code");
    EXPECT_TRUE(strstr(report, "message=L-UI source is empty.") != 0, "report message");
    EXPECT_TRUE(strstr(report, "line=1") != 0, "report line");
    EXPECT_TRUE(strstr(report, "column=1") != 0, "report column");
    EXPECT_TRUE(strstr(report, "hint=Provide L-UI source beginning with: lui 0.1") != 0, "report hint");
    EXPECT_TRUE(strstr(report, "no_effect=1") != 0, "report no_effect");
    EXPECT_TRUE(strstr(report, "execution_allowed=0") != 0, "report execution flag");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0") != 0, "report mutation flag");
    EXPECT_TRUE(strstr(report, "server_allowed=0") != 0, "report server flag");
    EXPECT_TRUE(strstr(report, "recovery_allowed=0") != 0, "report recovery flag");
    EXPECT_TRUE(strstr(report, "hardware_allowed=0") != 0, "report hardware flag");
    return 0;
}

static int diagnostic_report_rejects_bad_arguments_and_small_buffers(void) {
    latticra_l_ui_diagnostic_t diagnostic;
    char report[LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX];
    char small[8];

    EXPECT_TRUE(diagnostic_for_source("", &diagnostic) == 0, "argument diagnostic should be created");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_from_parse_result(0, &diagnostic) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL parse result should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_from_parse_result((const latticra_l_ui_parse_result_t *)&diagnostic, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL diagnostic should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL diagnostic report input should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_report(&diagnostic, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL diagnostic report buffer should be rejected");
    EXPECT_TRUE(
        latticra_l_ui_diagnostic_report(&diagnostic, small, sizeof(small)) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "small diagnostic report buffer should be rejected");
    return 0;
}

static int severity_labels_are_stable(void) {
    EXPECT_STR_EQ(
        latticra_l_ui_diagnostic_severity_label(LATTICRA_L_UI_DIAGNOSTIC_OK),
        "ok",
        "ok severity label");
    EXPECT_STR_EQ(
        latticra_l_ui_diagnostic_severity_label(LATTICRA_L_UI_DIAGNOSTIC_ERROR),
        "error",
        "error severity label");
    EXPECT_STR_EQ(
        latticra_l_ui_diagnostic_severity_label(LATTICRA_L_UI_DIAGNOSTIC_INTERNAL),
        "internal",
        "internal severity label");
    return 0;
}

int main(void) {
    if (ok_result_has_lui0000() != 0) return 1;
    if (empty_source_reports_lui0002() != 0) return 1;
    if (unsupported_version_reports_lui0003() != 0) return 1;
    if (missing_card_reports_lui0004() != 0) return 1;
    if (missing_purpose_reports_lui0005() != 0) return 1;
    if (missing_effect_reports_lui0006() != 0) return 1;
    if (unsupported_effect_reports_lui0007() != 0) return 1;
    if (missing_boundary_reports_lui0008() != 0) return 1;
    if (unsupported_boundary_reports_lui0009() != 0) return 1;
    if (missing_rail_reports_lui0010() != 0) return 1;
    if (unknown_binding_prefix_reports_lui0012() != 0) return 1;
    if (missing_required_binding_reports_lui0013() != 0) return 1;
    if (unterminated_string_reports_lui0014() != 0) return 1;
    if (unbalanced_brace_reports_lui0015() != 0) return 1;
    if (forbidden_marker_reports_lui0016() != 0) return 1;
    if (source_too_large_reports_lui0017() != 0) return 1;
    if (internal_error_reports_lui0018() != 0) return 1;
    if (error_diagnostics_preserve_no_effect_flags() != 0) return 1;
    if (line_and_column_are_one_based() != 0) return 1;
    if (messages_are_stable() != 0) return 1;
    if (hints_are_stable() != 0) return 1;
    if (diagnostic_report_contains_required_fields() != 0) return 1;
    if (diagnostic_report_rejects_bad_arguments_and_small_buffers() != 0) return 1;
    if (severity_labels_are_stable() != 0) return 1;

    puts("l_ui_parser_diagnostics_invariants: ok");
    return 0;
}
