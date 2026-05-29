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
    memset(authority, 0, sizeof(*authority));
    authority->status = LATTICRA_STATUS_OK;
    (void)snprintf(authority->status_label, sizeof(authority->status_label), "%s", "ok");
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label), "%s", "report-only-execution-refinement");
    (void)snprintf(authority->requested_effect_label, sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason), "%s", "ok");
    authority->no_effect = 1;
    authority->execution_allowed = 0;
    authority->mutation_allowed = 0;
    authority->server_allowed = 0;
    authority->network_allowed = 0;
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
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.task_id, sizeof(request.task_id), "%s", "report-only-execution");
    request.request_kind = kind;
    request.requested_effect = effect;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    request.authority = authority;
    request.source_identity = "report-only-fixture";
    request.source_identity_len = strlen("report-only-fixture");
    request.source_span = span_ok();
    return request;
}

static latticra_nucleus_preview_t preview_for(latticra_request_kind_t kind, latticra_effect_t effect) {
    latticra_nucleus_preview_t preview;
    memset(&preview, 0, sizeof(preview));
    (void)latticra_nucleus_classify_preview(kind, effect, &preview);
    return preview;
}

static int accepted_report_is_report_only(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;

    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "accepted classify status");
    EXPECT_STR_EQ(result.record.execution_status, "not-executed", "accepted execution status");
    EXPECT_STR_EQ(result.record.effect_status, "report-only", "accepted effect status");
    EXPECT_STR_EQ(result.record.runtime_status, "not-entered", "accepted runtime status");
    EXPECT_TRUE(result.record.executed == 0, "accepted execution flag remains zero");
    EXPECT_TRUE(result.record.mutation_allowed == 0, "accepted mutation remains disabled");
    EXPECT_TRUE(result.record.server_interaction_allowed == 0, "accepted server remains disabled");
    EXPECT_TRUE(result.record.network_allowed == 0, "accepted network remains disabled");
    EXPECT_TRUE(result.record.recovery_allowed == 0, "accepted recovery remains disabled");
    EXPECT_TRUE(result.record.hardware_allowed == 0, "accepted hardware remains disabled");
    EXPECT_TRUE(result.record.effect_authority_granted == 0, "accepted effect authority field denied");
    EXPECT_TRUE(result.record.task_execution_performed == 0, "accepted task execution field denied");
    EXPECT_TRUE(result.record.runtime_entered == 0, "accepted runtime field denied");
    EXPECT_TRUE(result.record.command_execution_allowed == 0, "accepted command execution field denied");
    EXPECT_TRUE(result.record.lat_execution_allowed == 0, "accepted lat execution field denied");
    EXPECT_TRUE(result.record.lir_execution_allowed == 0, "accepted lir execution field denied");
    EXPECT_TRUE(result.record.file_io_allowed == 0, "accepted file I/O field denied");
    EXPECT_TRUE(result.record.state_mutation_allowed == 0, "accepted state mutation field denied");
    EXPECT_TRUE(result.record.self_update_allowed == 0, "accepted self-update field denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "accepted boot field denied");
    EXPECT_TRUE(result.record.operator_confirmation_overrides_policy == 0, "accepted operator override field denied");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "accepted report writes");
    EXPECT_TRUE(strstr(report, "execution_status=not-executed\n") != 0, "accepted execution status emitted");
    EXPECT_TRUE(strstr(report, "effect_status=report-only\n") != 0, "accepted effect status emitted");
    EXPECT_TRUE(strstr(report, "runtime_status=not-entered\n") != 0, "accepted runtime status emitted");
    EXPECT_TRUE(strstr(report, "effect_authority_granted=0\n") != 0, "accepted effect authority denied");
    EXPECT_TRUE(strstr(report, "task_execution_performed=0\n") != 0, "accepted task execution denied");
    EXPECT_TRUE(strstr(report, "runtime_entered=0\n") != 0, "accepted runtime entry denied");
    EXPECT_TRUE(strstr(report, "command_execution_allowed=0\n") != 0, "accepted command execution denied");
    EXPECT_TRUE(strstr(report, "lat_execution_allowed=0\n") != 0, "accepted lat execution denied");
    EXPECT_TRUE(strstr(report, "lir_execution_allowed=0\n") != 0, "accepted lir execution denied");
    EXPECT_TRUE(strstr(report, "file_io_allowed=0\n") != 0, "accepted file I/O denied");
    EXPECT_TRUE(strstr(report, "state_mutation_allowed=0\n") != 0, "accepted state mutation denied");
    EXPECT_TRUE(strstr(report, "self_update_allowed=0\n") != 0, "accepted self-update denied");
    EXPECT_TRUE(strstr(report, "boot_allowed=0\n") != 0, "accepted boot denied");
    EXPECT_TRUE(strstr(report, "operator_confirmation_overrides_policy=0\n") != 0, "accepted operator override denied");
    EXPECT_TRUE(strstr(report, "executed=0\n") != 0, "accepted executed flag emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "accepted network emitted");
    return 0;
}

static int future_gated_report_is_still_not_executed(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);

    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "future classify status");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED, "future classification");
    EXPECT_STR_EQ(result.record.execution_status, "not-executed", "future execution status");
    EXPECT_STR_EQ(result.record.effect_status, "report-only", "future effect status");
    EXPECT_STR_EQ(result.record.runtime_status, "not-entered", "future runtime status");
    EXPECT_TRUE(result.record.executed == 0, "future no execution");
    EXPECT_TRUE(result.record.effect_authority_granted == 0, "future effect authority field denied");
    EXPECT_TRUE(result.record.runtime_entered == 0, "future runtime field denied");
    EXPECT_TRUE(result.record.self_update_allowed == 0, "future self-update field denied");
    EXPECT_TRUE(result.record.operator_confirmation_overrides_policy == 0, "future operator override field denied");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "future report writes");
    EXPECT_TRUE(strstr(report, "report_classification=future-gated\n") != 0, "future classification emitted");
    EXPECT_TRUE(strstr(report, "execution_status=not-executed\n") != 0, "future execution status emitted");
    EXPECT_TRUE(strstr(report, "runtime_status=not-entered\n") != 0, "future runtime status emitted");
    EXPECT_TRUE(strstr(report, "effect_authority_granted=0\n") != 0, "future effect authority denied");
    EXPECT_TRUE(strstr(report, "runtime_entered=0\n") != 0, "future runtime entry denied");
    EXPECT_TRUE(strstr(report, "operator_confirmation_overrides_policy=0\n") != 0, "future operator override denied");
    return 0;
}

static int invalid_report_is_report_only(void) {
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    EXPECT_TRUE(latticra_nucleus_task_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "invalid classify status");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_INVALID, "invalid classification");
    EXPECT_STR_EQ(result.record.execution_status, "not-executed", "invalid execution status");
    EXPECT_STR_EQ(result.record.effect_status, "report-only", "invalid effect status");
    EXPECT_STR_EQ(result.record.runtime_status, "not-entered", "invalid runtime status");
    EXPECT_TRUE(result.record.task_execution_performed == 0, "invalid task execution field denied");
    EXPECT_TRUE(result.record.runtime_entered == 0, "invalid runtime field denied");
    EXPECT_TRUE(result.record.boot_allowed == 0, "invalid boot field denied");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "invalid report writes");
    EXPECT_TRUE(strstr(report, "execution_status=not-executed\n") != 0, "invalid execution status emitted");
    EXPECT_TRUE(strstr(report, "effect_status=report-only\n") != 0, "invalid effect status emitted");
    EXPECT_TRUE(strstr(report, "runtime_status=not-entered\n") != 0, "invalid runtime status emitted");
    EXPECT_TRUE(strstr(report, "task_execution_performed=0\n") != 0, "invalid task execution denied");
    EXPECT_TRUE(strstr(report, "runtime_entered=0\n") != 0, "invalid runtime entry denied");
    EXPECT_TRUE(strstr(report, "boot_allowed=0\n") != 0, "invalid boot denied");
    return 0;
}

int main(void) {
    if (accepted_report_is_report_only() != 0) return 1;
    if (future_gated_report_is_still_not_executed() != 0) return 1;
    if (invalid_report_is_report_only() != 0) return 1;

    puts("nucleus_task_report_only_execution_refinement: ok");
    return 0;
}
