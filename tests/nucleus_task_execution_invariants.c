#include "latticra/nucleus_task.h"

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

static void authority_ok(latticra_nucleus_task_authority_summary_t *authority) {
    authority->status = LATTICRA_STATUS_OK;
    (void)snprintf(authority->status_label, sizeof(authority->status_label), "%s", "ok");
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label), "%s", "no_effect");
    (void)snprintf(authority->requested_effect_label, sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason), "%s", "none");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->recovery_allowed = 0;
    authority->hardware_allowed = 0;
}

static latticra_l_ui_source_span_t span_ok(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 12u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 13u;
    return span;
}

static latticra_nucleus_task_request_t base_request(
    latticra_nucleus_task_request_kind_t kind,
    latticra_nucleus_task_effect_t effect,
    const latticra_nucleus_task_authority_summary_t *authority) {
    latticra_nucleus_task_request_t request;
    (void)snprintf(request.task_id, sizeof(request.task_id), "%s", "task-001");
    request.request_kind = kind;
    request.requested_effect = effect;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    request.authority = authority;
    request.preview = 0;
    request.render = 0;
    request.lir = 0;
    request.lat = 0;
    request.source_identity = "fixture";
    request.source_identity_len = strlen("fixture");
    request.source_span = span_ok();
    return request;
}

static latticra_nucleus_preview_t preview_for(latticra_request_kind_t kind, latticra_effect_t effect) {
    latticra_nucleus_preview_t preview;
    memset(&preview, 0, sizeof(preview));
    (void)latticra_nucleus_classify_preview(kind, effect, &preview);
    return preview;
}

static int nucleus_task_execution_denies_unknown_request(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_UNKNOWN, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "unknown request status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_DENY, "unknown request denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST, "unknown request reason");
    return 0;
}

static int nucleus_task_execution_denies_unknown_effect(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "unknown effect status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_DENY, "unknown effect denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT, "unknown effect reason");
    return 0;
}

static int nucleus_task_execution_preserves_preview_only_boundary(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_TRANSITION_PREVIEW, LATTICRA_EFFECT_READ);
    request = base_request(LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW, LATTICRA_NUCLEUS_TASK_EFFECT_READ, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "preview boundary status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW, "preview boundary policy");
    EXPECT_TRUE(result.record.executed == 0, "preview boundary not executed");
    return 0;
}

static int nucleus_task_execution_requires_authority_success(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    authority.status = LATTICRA_STATUS_BUFFER_TOO_SMALL;
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "authority failure status");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED, "authority failure reason");
    return 0;
}

static int nucleus_task_execution_requires_effect_gate_success(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = 0;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "effect gate failure status");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED, "effect gate failure reason");
    return 0;
}

static int nucleus_task_execution_requires_no_effect_flags(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    authority.mutation_allowed = 1;
    request = base_request(LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "no-effect flag failure status");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS, "no-effect flag failure reason");
    return 0;
}

static int nucleus_task_execution_allows_state_report_preview_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "state report status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, "state report policy");
    EXPECT_TRUE(result.record.allowed_effect == LATTICRA_NUCLEUS_TASK_EFFECT_NONE, "state report allowed effect");
    return 0;
}

static int nucleus_task_execution_allows_transition_preview_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_TRANSITION_PREVIEW, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "transition preview status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW, "transition preview policy");
    return 0;
}

static int nucleus_task_execution_allows_render_report_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_l_ui_render_result_t render;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    memset(&render, 0, sizeof(render));
    render.status = LATTICRA_STATUS_OK;
    render.error = LATTICRA_L_UI_RENDER_OK;
    request = base_request(LATTICRA_NUCLEUS_TASK_RENDER_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_READ, &authority);
    request.render = &render;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "render report status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, "render report policy");
    return 0;
}

static int nucleus_task_execution_allows_lat_validation_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_lat_parse_result_t lat;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    memset(&lat, 0, sizeof(lat));
    lat.status = LATTICRA_STATUS_OK;
    lat.error = LATTICRA_LAT_PARSE_OK;
    request = base_request(LATTICRA_NUCLEUS_TASK_LAT_VALIDATE, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.lat = &lat;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "lat validation status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION, "lat validation policy");
    return 0;
}

static int nucleus_task_execution_allows_lir_validation_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_lir_module_t lir;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    memset(&lir, 0, sizeof(lir));
    lir.status = LATTICRA_STATUS_OK;
    lir.error = LATTICRA_LIR_OK;
    request = base_request(LATTICRA_NUCLEUS_TASK_LIR_VALIDATE, LATTICRA_NUCLEUS_TASK_EFFECT_READ, &authority);
    request.lir = &lir;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "lir validation status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION, "lir validation policy");
    return 0;
}

static int future_gate_denial(latticra_nucleus_task_request_kind_t kind) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(kind, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "future gate status");
    EXPECT_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE, "future gate policy");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE, "future gate reason");
    EXPECT_TRUE(result.record.executed == 0, "future gate not executed");
    return 0;
}

static int nucleus_task_execution_denies_server_interaction(void) { return future_gate_denial(LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION); }
static int nucleus_task_execution_denies_self_update(void) { return future_gate_denial(LATTICRA_NUCLEUS_TASK_SELF_UPDATE); }
static int nucleus_task_execution_denies_recovery_action(void) { return future_gate_denial(LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION); }
static int nucleus_task_execution_denies_hardware_action(void) { return future_gate_denial(LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION); }
static int nucleus_task_execution_denies_boot_action(void) { return future_gate_denial(LATTICRA_NUCLEUS_TASK_BOOT_ACTION); }

static int nucleus_task_execution_report_is_deterministic(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char one[LATTICRA_NUCLEUS_TASK_REPORT_MAX];
    char two[LATTICRA_NUCLEUS_TASK_REPORT_MAX];
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "report deterministic classify");
    EXPECT_TRUE(latticra_nucleus_task_report(&result, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report");
    EXPECT_TRUE(latticra_nucleus_task_report(&result, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report");
    EXPECT_STR_EQ(one, two, "reports deterministic");
    EXPECT_TRUE(strstr(one, "LATTICRA NUCLEUS TASK REPORT\n") != 0, "report header");
    return 0;
}

static int nucleus_task_execution_report_rejects_small_buffer(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char tiny[8];
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "small report classify");
    EXPECT_TRUE(latticra_nucleus_task_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small report cleared");
    return 0;
}

static int nucleus_task_execution_does_not_mutate_state(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "no mutate classify");
    EXPECT_TRUE(result.record.mutation_allowed == 0, "mutation denied");
    return 0;
}

static int nucleus_task_execution_does_not_open_network(void) {
    return future_gate_denial(LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION);
}

static int nucleus_task_execution_does_not_touch_hardware(void) {
    return future_gate_denial(LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION);
}

static int nucleus_task_execution_does_not_write_files(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_LAT_VALIDATE, LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "write files denied classify");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT, "write files denied reason");
    EXPECT_TRUE(result.record.executed == 0, "write files not executed");
    return 0;
}

static int nucleus_task_execution_does_not_call_recovery(void) {
    return future_gate_denial(LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION);
}

static int nucleus_task_execution_does_not_override_policy_with_operator_confirmation(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_PRESENT;
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "operator confirmation classify");
    EXPECT_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED, "operator confirmation denied");
    EXPECT_TRUE(result.record.executed == 0, "operator confirmation not executed");
    return 0;
}

int main(void) {
    if (nucleus_task_execution_denies_unknown_request() != 0) return 1;
    if (nucleus_task_execution_denies_unknown_effect() != 0) return 1;
    if (nucleus_task_execution_preserves_preview_only_boundary() != 0) return 1;
    if (nucleus_task_execution_requires_authority_success() != 0) return 1;
    if (nucleus_task_execution_requires_effect_gate_success() != 0) return 1;
    if (nucleus_task_execution_requires_no_effect_flags() != 0) return 1;
    if (nucleus_task_execution_allows_state_report_preview_only() != 0) return 1;
    if (nucleus_task_execution_allows_transition_preview_only() != 0) return 1;
    if (nucleus_task_execution_allows_render_report_only() != 0) return 1;
    if (nucleus_task_execution_allows_lat_validation_only() != 0) return 1;
    if (nucleus_task_execution_allows_lir_validation_only() != 0) return 1;
    if (nucleus_task_execution_denies_server_interaction() != 0) return 1;
    if (nucleus_task_execution_denies_self_update() != 0) return 1;
    if (nucleus_task_execution_denies_recovery_action() != 0) return 1;
    if (nucleus_task_execution_denies_hardware_action() != 0) return 1;
    if (nucleus_task_execution_denies_boot_action() != 0) return 1;
    if (nucleus_task_execution_report_is_deterministic() != 0) return 1;
    if (nucleus_task_execution_report_rejects_small_buffer() != 0) return 1;
    if (nucleus_task_execution_does_not_mutate_state() != 0) return 1;
    if (nucleus_task_execution_does_not_open_network() != 0) return 1;
    if (nucleus_task_execution_does_not_touch_hardware() != 0) return 1;
    if (nucleus_task_execution_does_not_write_files() != 0) return 1;
    if (nucleus_task_execution_does_not_call_recovery() != 0) return 1;
    if (nucleus_task_execution_does_not_override_policy_with_operator_confirmation() != 0) return 1;

    puts("nucleus_task_execution_invariants: ok");
    return 0;
}
