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
    "\n"
    "card NucleusPreview {\n"
    "  purpose \"operator-visible Nucleus preview report\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "\n"
    "  rail top {\n"
    "    text \"Latticra / Nucleus Preview / effect-bound\"\n"
    "  }\n"
    "\n"
    "  rail state {\n"
    "    field origin bind state.origin\n"
    "    field route bind state.route\n"
    "    field axis bind state.axis\n"
    "    field path bind state.path\n"
    "  }\n"
    "\n"
    "  rail trace {\n"
    "    field breadcrumb bind state.breadcrumb\n"
    "    field trace bind state.trace\n"
    "  }\n"
    "\n"
    "  rail safety {\n"
    "    field health bind state.health\n"
    "    field risk bind state.risk\n"
    "    field lock bind state.lock\n"
    "    field dark_phase bind state.dark_phase\n"
    "  }\n"
    "\n"
    "  rail gates {\n"
    "    field safe_portal bind state.safe_portal\n"
    "    field rollback bind state.rollback\n"
    "  }\n"
    "\n"
    "  rail effects {\n"
    "    field host bind state.host_effect\n"
    "    field external bind state.external_effect\n"
    "    field requested bind preview.requested_effect\n"
    "  }\n"
    "\n"
    "  rail policy {\n"
    "    field request bind preview.request\n"
    "    field policy bind preview.policy\n"
    "    field reason bind preview.reason\n"
    "  }\n"
    "\n"
    "  rail execution {\n"
    "    field executed bind preview.executed\n"
    "    field mutation bind preview.mutation_allowed\n"
    "    field server bind preview.server_interaction_allowed\n"
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "\n"
    "  rail bottom {\n"
    "    text \"preview-only no-live-movement no-host-effect no-external-effect\"\n"
    "  }\n"
    "}\n";

static int parse_text(const char *source, latticra_l_ui_parse_result_t *result) {
    return latticra_l_ui_parse_source(source, strlen(source), result) == LATTICRA_STATUS_OK;
}

static int valid_fixture_parses_successfully(void) {
    latticra_l_ui_parse_result_t result;

    EXPECT_TRUE(parse_text(VALID_FIXTURE, &result), "valid fixture should parse");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "valid fixture should return ok error");
    EXPECT_STR_EQ(result.card_name, "NucleusPreview", "card name");
    EXPECT_TRUE(result.rail_count == 9u, "rail count");
    EXPECT_TRUE(result.field_count == 23u, "field count");
    EXPECT_STR_EQ(result.effect, "none", "effect");
    EXPECT_STR_EQ(result.boundary, "preview_only", "boundary");

    return 0;
}

static int null_source_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(
        latticra_l_ui_parse_source(0, 1u, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL source should be rejected");
    return 0;
}

static int null_result_is_rejected(void) {
    EXPECT_TRUE(
        latticra_l_ui_parse_source(VALID_FIXTURE, strlen(VALID_FIXTURE), 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "NULL result should be rejected");
    return 0;
}

static int empty_source_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(parse_text("", &result), "empty source should return ok status with parse error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_EMPTY_SOURCE, "empty source error");
    return 0;
}

static int oversized_source_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(
        latticra_l_ui_parse_source("x", LATTICRA_L_UI_SOURCE_MAX + 1u, &result) == LATTICRA_STATUS_OK,
        "oversized source should return ok status with parse error");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE, "oversized source error");
    return 0;
}

static int unsupported_version_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(parse_text("lui 9.9\ncard NucleusPreview {}\n", &result), "unsupported version should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION, "unsupported version error");
    return 0;
}

static int missing_card_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(parse_text("lui 0.1\n", &result), "missing card should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_CARD, "missing card error");
    return 0;
}

static int missing_purpose_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  effect none\n  boundary preview_only\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "missing purpose should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_PURPOSE, "missing purpose error");
    return 0;
}

static int missing_effect_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  boundary preview_only\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "missing effect should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_EFFECT, "missing effect error");
    return 0;
}

static int unsupported_effect_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect network\n  boundary preview_only\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "unsupported effect should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "unsupported effect error");
    return 0;
}

static int missing_boundary_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "missing boundary should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_BOUNDARY, "missing boundary error");
    return 0;
}

static int unsupported_boundary_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary live\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "unsupported boundary should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY, "unsupported boundary error");
    return 0;
}

static int missing_required_rail_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n  effect none\n  boundary preview_only\n  rail top {}\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "missing rail should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_RAIL, "missing rail error");
    return 0;
}

static int missing_required_binding_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] =
        "lui 0.1\ncard NucleusPreview {\n"
        "  purpose \"x\"\n  effect none\n  boundary preview_only\n"
        "  rail top {}\n  rail state {}\n  rail trace {}\n  rail safety {}\n  rail gates {}\n"
        "  rail effects {}\n  rail policy {}\n  rail execution {}\n  rail bottom {}\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "missing binding should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING, "missing binding error");
    return 0;
}

static int unknown_binding_prefix_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    char source[sizeof(VALID_FIXTURE) + 64u];
    (void)snprintf(source, sizeof(source), "%s\nfield bad bind host.value\n", VALID_FIXTURE);
    EXPECT_TRUE(parse_text(source, &result), "unknown binding prefix should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX, "unknown binding prefix error");
    return 0;
}

static int forbidden_behavior_marker_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    char source[sizeof(VALID_FIXTURE) + 64u];
    (void)snprintf(source, sizeof(source), "%s\nexecute command\n", VALID_FIXTURE);
    EXPECT_TRUE(parse_text(source, &result), "forbidden marker should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER, "forbidden marker error");
    return 0;
}

static int unterminated_string_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"unterminated\n}\n";
    EXPECT_TRUE(parse_text(source, &result), "unterminated string should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNTERMINATED_STRING, "unterminated string error");
    return 0;
}

static int unbalanced_brace_is_rejected(void) {
    latticra_l_ui_parse_result_t result;
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"x\"\n";
    EXPECT_TRUE(parse_text(source, &result), "unbalanced brace should classify");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_UNBALANCED_BRACE, "unbalanced brace error");
    return 0;
}

static int valid_parse_returns_no_effect_flags(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(parse_text(VALID_FIXTURE, &result), "valid fixture should parse for flag test");
    EXPECT_TRUE(result.no_effect == 1, "valid parse no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "valid parse execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "valid parse mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "valid parse server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "valid parse recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "valid parse hardware flag");
    return 0;
}

static int error_results_preserve_no_execution_flags(void) {
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(parse_text("", &result), "empty source should parse for error flag test");
    EXPECT_TRUE(result.no_effect == 1, "error result no_effect");
    EXPECT_TRUE(result.execution_allowed == 0, "error result execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "error result mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "error result server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "error result recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "error result hardware flag");
    return 0;
}

static int parse_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_l_ui_parse_error_label(LATTICRA_L_UI_PARSE_OK), "ok", "ok label");
    EXPECT_STR_EQ(
        latticra_l_ui_parse_error_label(LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT),
        "unsupported_effect",
        "unsupported effect label");
    EXPECT_STR_EQ(
        latticra_l_ui_parse_error_label(LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER),
        "forbidden_behavior_marker",
        "forbidden marker label");
    return 0;
}

int main(void) {
    if (valid_fixture_parses_successfully() != 0) return 1;
    if (null_source_is_rejected() != 0) return 1;
    if (null_result_is_rejected() != 0) return 1;
    if (empty_source_is_rejected() != 0) return 1;
    if (oversized_source_is_rejected() != 0) return 1;
    if (unsupported_version_is_rejected() != 0) return 1;
    if (missing_card_is_rejected() != 0) return 1;
    if (missing_purpose_is_rejected() != 0) return 1;
    if (missing_effect_is_rejected() != 0) return 1;
    if (unsupported_effect_is_rejected() != 0) return 1;
    if (missing_boundary_is_rejected() != 0) return 1;
    if (unsupported_boundary_is_rejected() != 0) return 1;
    if (missing_required_rail_is_rejected() != 0) return 1;
    if (missing_required_binding_is_rejected() != 0) return 1;
    if (unknown_binding_prefix_is_rejected() != 0) return 1;
    if (forbidden_behavior_marker_is_rejected() != 0) return 1;
    if (unterminated_string_is_rejected() != 0) return 1;
    if (unbalanced_brace_is_rejected() != 0) return 1;
    if (valid_parse_returns_no_effect_flags() != 0) return 1;
    if (error_results_preserve_no_execution_flags() != 0) return 1;
    if (parse_error_labels_are_stable() != 0) return 1;

    puts("l_ui_parser_invariants: ok");
    return 0;
}
