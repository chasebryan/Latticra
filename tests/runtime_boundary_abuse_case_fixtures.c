#include "latticra/runtime_boundary_domain_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

typedef enum {
    FIXTURE_AUTHORITY_NONE = 0,
    FIXTURE_AUTHORITY_OK = 1
} fixture_authority_mode_t;

typedef struct {
    const char *id;
    latticra_runtime_boundary_request_kind_t request_kind;
    latticra_runtime_boundary_effect_t requested_effect;
    latticra_runtime_boundary_mode_t mode;
    latticra_runtime_boundary_operator_confirmation_t operator_confirmation;
    fixture_authority_mode_t authority_mode;
    latticra_runtime_boundary_policy_t expected_policy;
    latticra_runtime_boundary_denial_t expected_denial;
    latticra_runtime_boundary_gate_state_t expected_gate;
    latticra_runtime_boundary_report_classification_t expected_report_classification;
    latticra_runtime_boundary_policy_matrix_cell_t expected_policy_matrix_cell;
    latticra_runtime_boundary_domain_matrix_cell_t expected_domain_matrix_cell;
} runtime_boundary_abuse_case_fixture_t;

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    (void)snprintf(authority.status_label, sizeof(authority.status_label), "%s", "ok");
    (void)snprintf(authority.validator_label, sizeof(authority.validator_label), "%s", "abuse-case-fixture");
    (void)snprintf(authority.requested_effect_label, sizeof(authority.requested_effect_label), "%s", "none");
    (void)snprintf(authority.denial_reason, sizeof(authority.denial_reason), "%s", "ok");
    authority.no_effect = 1;
    return authority;
}

static const runtime_boundary_abuse_case_fixture_t abuse_case_fixtures[] = {
    {
        "unknown-request-is-not-allowed",
        LATTICRA_RUNTIME_BOUNDARY_UNKNOWN,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID
    },
    {
        "unknown-effect-is-not-allowed",
        LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN,
        LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID
    },
    {
        "future-gated-execution-is-not-executable",
        LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE,
        LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED
    },
    {
        "operator-confirmation-cannot-override-policy",
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED
    },
    {
        "denial-reason-stays-rendered",
        LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED
    },
    {
        "authority-failure-is-not-allowed",
        LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_NONE,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED
    },
    {
        "invalid-lir-prerequisite-stays-denied",
        LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE,
        LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN
    },
    {
        "blocked-effect-stays-blocked",
        LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK,
        LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY,
        LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE,
        FIXTURE_AUTHORITY_OK,
        LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY,
        LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED,
        LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED,
        LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED,
        LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT,
        LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_BLOCKED
    }
};

static size_t abuse_case_fixture_count(void) {
    return sizeof(abuse_case_fixtures) / sizeof(abuse_case_fixtures[0]);
}

static int classify_fixture(
    const runtime_boundary_abuse_case_fixture_t *fixture,
    latticra_runtime_boundary_result_t *result) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;

    memset(&request, 0, sizeof(request));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", fixture->id);
    request.request_kind = fixture->request_kind;
    request.requested_effect = fixture->requested_effect;
    request.mode = fixture->mode;
    request.operator_confirmation = fixture->operator_confirmation;
    request.source_identity = fixture->id;
    request.source_identity_len = strlen(fixture->id);
    if (fixture->authority_mode == FIXTURE_AUTHORITY_OK) request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, result) == LATTICRA_STATUS_OK, "fixture classification status ok");
    return 0;
}

static int runtime_boundary_abuse_case_fixture_matches_policy_map(size_t index) {
    const runtime_boundary_abuse_case_fixture_t *fixture;
    latticra_runtime_boundary_result_t result;

    EXPECT_TRUE(index < abuse_case_fixture_count(), "fixture index in range");
    fixture = &abuse_case_fixtures[index];

    if (classify_fixture(fixture, &result) != 0) return 1;
    EXPECT_TRUE(result.record.policy == fixture->expected_policy, "fixture policy");
    EXPECT_TRUE(result.record.denial == fixture->expected_denial, "fixture denial");
    EXPECT_TRUE(result.record.gate_state == fixture->expected_gate, "fixture gate state");
    EXPECT_TRUE(result.record.report_classification == fixture->expected_report_classification, "fixture report classification");
    EXPECT_TRUE(result.record.policy_matrix_cell == fixture->expected_policy_matrix_cell, "fixture policy matrix cell");
    return 0;
}

static int runtime_boundary_abuse_case_fixture_table_covers_current_policy_map(void) {
    size_t index;

    EXPECT_TRUE(abuse_case_fixture_count() == 8u, "expected abuse-case fixture count");

    for (index = 0u; index < abuse_case_fixture_count(); index++) {
        if (runtime_boundary_abuse_case_fixture_matches_policy_map(index) != 0) return 1;
    }
    return 0;
}

static int runtime_boundary_abuse_case_unknown_request_is_not_allowed(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(0u);
}

static int runtime_boundary_abuse_case_unknown_effect_is_not_allowed(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(1u);
}

static int runtime_boundary_abuse_case_future_gated_request_is_not_executable(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(2u);
}

static int runtime_boundary_abuse_case_operator_confirmation_does_not_override(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(3u);
}

static int runtime_boundary_abuse_case_render_report_preserves_lir_failure_reason(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    latticra_l_ui_render_result_t render;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    memset(&render, 0, sizeof(render));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", "render-report-lir-failure");
    render.status = LATTICRA_STATUS_OK;
    render.error = LATTICRA_L_UI_RENDER_LIR_FAILED;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.render = &render;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "render failure classify");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "render failure policy");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED, "render failure denial");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED, "render failure matrix");
    EXPECT_TRUE(result.record.render_error == LATTICRA_L_UI_RENDER_LIR_FAILED, "render failure error copied");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "render failure report");
    EXPECT_TRUE(strstr(report, "reason=render-failed\n") != 0, "render failure report reason");
    EXPECT_TRUE(strstr(report, "execution_allowed=0\n") != 0, "render failure execution denied");
    return 0;
}

static int runtime_boundary_abuse_case_failed_authority_metadata_is_not_allowed(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(5u);
}

static int runtime_boundary_abuse_case_invalid_lir_does_not_reach_allowed_validation(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(6u);
}

static int runtime_boundary_abuse_case_blocked_effect_stays_blocked(void) {
    return runtime_boundary_abuse_case_fixture_matches_policy_map(7u);
}

static int runtime_boundary_abuse_case_reports_include_denial_reasons(void) {
    size_t index;

    for (index = 0u; index < abuse_case_fixture_count(); index++) {
        const runtime_boundary_abuse_case_fixture_t *fixture = &abuse_case_fixtures[index];
        latticra_runtime_boundary_result_t result;
        char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];
        char needle[160];

        if (classify_fixture(fixture, &result) != 0) return 1;
        EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "fixture report status ok");
        (void)snprintf(needle, sizeof(needle), "runtime_id=%s\n", fixture->id);
        EXPECT_TRUE(strstr(report, needle) != 0, "fixture report runtime id");
        (void)snprintf(needle, sizeof(needle), "reason=%s\n", latticra_runtime_boundary_denial_label(fixture->expected_denial));
        EXPECT_TRUE(strstr(report, needle) != 0, "fixture report denial reason");
        (void)snprintf(needle, sizeof(needle), "policy_matrix_cell=%s\n", latticra_runtime_boundary_policy_matrix_cell_label(fixture->expected_policy_matrix_cell));
        EXPECT_TRUE(strstr(report, needle) != 0, "fixture report policy matrix cell");
        EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0, "fixture report no effect");
        EXPECT_TRUE(strstr(report, "execution_allowed=0\n") != 0, "fixture report execution denied");
        EXPECT_TRUE(strstr(report, "mutation_allowed=0\n") != 0, "fixture report mutation denied");
        EXPECT_TRUE(strstr(report, "file_io_allowed=0\n") != 0, "fixture report file I/O denied");
        EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "fixture report network denied");
        EXPECT_TRUE(strstr(report, "server_allowed=0\n") != 0, "fixture report server denied");
    }
    return 0;
}

static int runtime_boundary_abuse_case_domain_matrix_preserves_no_authority(void) {
    size_t index;

    for (index = 0u; index < abuse_case_fixture_count(); index++) {
        const runtime_boundary_abuse_case_fixture_t *fixture = &abuse_case_fixtures[index];
        latticra_runtime_boundary_result_t result;
        latticra_runtime_boundary_domain_matrix_result_t matrix;

        if (classify_fixture(fixture, &result) != 0) return 1;
        EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_evaluate(&result, &matrix) == LATTICRA_STATUS_OK, "fixture domain matrix status ok");
        EXPECT_TRUE(matrix.cell == fixture->expected_domain_matrix_cell, "fixture domain matrix cell");
        EXPECT_TRUE(result.no_effect == 1, "fixture no-effect flag");
        EXPECT_TRUE(result.execution_allowed == 0, "fixture execution denied");
        EXPECT_TRUE(result.mutation_allowed == 0, "fixture mutation denied");
        EXPECT_TRUE(result.file_io_allowed == 0, "fixture file I/O denied");
        EXPECT_TRUE(result.network_allowed == 0, "fixture network denied");
        EXPECT_TRUE(result.server_allowed == 0, "fixture server denied");
        EXPECT_TRUE(result.recovery_allowed == 0, "fixture recovery denied");
        EXPECT_TRUE(result.rollback_allowed == 0, "fixture rollback denied");
        EXPECT_TRUE(result.hardware_allowed == 0, "fixture hardware denied");
        EXPECT_TRUE(result.boot_allowed == 0, "fixture boot denied");
        EXPECT_TRUE(result.record.executed == 0, "fixture record not executed");
    }
    return 0;
}

int main(void) {
    if (runtime_boundary_abuse_case_fixture_table_covers_current_policy_map() != 0) return 1;
    if (runtime_boundary_abuse_case_unknown_request_is_not_allowed() != 0) return 1;
    if (runtime_boundary_abuse_case_unknown_effect_is_not_allowed() != 0) return 1;
    if (runtime_boundary_abuse_case_future_gated_request_is_not_executable() != 0) return 1;
    if (runtime_boundary_abuse_case_operator_confirmation_does_not_override() != 0) return 1;
    if (runtime_boundary_abuse_case_render_report_preserves_lir_failure_reason() != 0) return 1;
    if (runtime_boundary_abuse_case_failed_authority_metadata_is_not_allowed() != 0) return 1;
    if (runtime_boundary_abuse_case_invalid_lir_does_not_reach_allowed_validation() != 0) return 1;
    if (runtime_boundary_abuse_case_blocked_effect_stays_blocked() != 0) return 1;
    if (runtime_boundary_abuse_case_reports_include_denial_reasons() != 0) return 1;
    if (runtime_boundary_abuse_case_domain_matrix_preserves_no_authority() != 0) return 1;

    puts("runtime_boundary_abuse_case_fixtures: ok");
    return 0;
}
