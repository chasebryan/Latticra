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
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label), "%s", "no-effect-report-alignment");
    (void)snprintf(authority->requested_effect_label, sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason), "%s", "ok");
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
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.task_id, sizeof(request.task_id), "%s", "no-effect-alignment");
    request.request_kind = kind;
    request.requested_effect = effect;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    request.authority = authority;
    request.source_identity = "alignment-fixture";
    request.source_identity_len = strlen("alignment-fixture");
    request.source_span = span_ok();
    return request;
}

static latticra_nucleus_preview_t preview_for(latticra_request_kind_t kind, latticra_effect_t effect) {
    latticra_nucleus_preview_t preview;
    memset(&preview, 0, sizeof(preview));
    (void)latticra_nucleus_classify_preview(kind, effect, &preview);
    return preview;
}

static int accepted_report_has_alignment_labels(void) {
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
    EXPECT_STR_EQ(result.record.report_alignment, "no-effect-report-alignment", "accepted report alignment");
    EXPECT_STR_EQ(result.record.no_effect_policy, "preserved", "accepted no-effect policy");
    EXPECT_STR_EQ(result.record.representation_gate, "language-representation-reviewed", "accepted representation gate");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 1, "accepted no-effect chain");
    EXPECT_TRUE(result.record.executed == 0, "accepted no execution");
    EXPECT_TRUE(result.record.mutation_allowed == 0, "accepted no mutation");
    EXPECT_TRUE(result.record.server_interaction_allowed == 0, "accepted no server");
    EXPECT_TRUE(result.record.recovery_allowed == 0, "accepted no recovery");
    EXPECT_TRUE(result.record.hardware_allowed == 0, "accepted no hardware");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "accepted report output");
    EXPECT_TRUE(strstr(report, "report_alignment=no-effect-report-alignment\n") != 0, "accepted report alignment emitted");
    EXPECT_TRUE(strstr(report, "no_effect_policy=preserved\n") != 0, "accepted no-effect policy emitted");
    EXPECT_TRUE(strstr(report, "representation_gate=language-representation-reviewed\n") != 0, "accepted representation gate emitted");
    EXPECT_TRUE(strstr(report, "executed=0\n") != 0, "accepted executed emitted");
    return 0;
}

static int future_gated_report_keeps_alignment_labels(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_BOOT_ACTION, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);

    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "future classify status");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED, "future classification");
    EXPECT_STR_EQ(result.record.report_alignment, "no-effect-report-alignment", "future report alignment");
    EXPECT_STR_EQ(result.record.no_effect_policy, "preserved", "future no-effect policy");
    EXPECT_STR_EQ(result.record.representation_gate, "language-representation-reviewed", "future representation gate");
    EXPECT_TRUE(result.record.executed == 0, "future no execution");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "future report output");
    EXPECT_TRUE(strstr(report, "report_classification=future-gated\n") != 0, "future classification emitted");
    EXPECT_TRUE(strstr(report, "report_alignment=no-effect-report-alignment\n") != 0, "future alignment emitted");
    EXPECT_TRUE(strstr(report, "representation_gate=language-representation-reviewed\n") != 0, "future representation emitted");
    return 0;
}

static int invalid_report_keeps_alignment_labels(void) {
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    EXPECT_TRUE(latticra_nucleus_task_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "invalid classify status");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_INVALID, "invalid classification");
    EXPECT_STR_EQ(result.record.report_alignment, "no-effect-report-alignment", "invalid report alignment");
    EXPECT_STR_EQ(result.record.no_effect_policy, "preserved", "invalid no-effect policy");
    EXPECT_STR_EQ(result.record.representation_gate, "language-representation-reviewed", "invalid representation gate");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "invalid report output");
    EXPECT_TRUE(strstr(report, "report_classification=invalid\n") != 0, "invalid classification emitted");
    EXPECT_TRUE(strstr(report, "report_alignment=no-effect-report-alignment\n") != 0, "invalid alignment emitted");
    EXPECT_TRUE(strstr(report, "no_effect_policy=preserved\n") != 0, "invalid no-effect policy emitted");
    return 0;
}

int main(void) {
    if (accepted_report_has_alignment_labels() != 0) return 1;
    if (future_gated_report_keeps_alignment_labels() != 0) return 1;
    if (invalid_report_keeps_alignment_labels() != 0) return 1;

    puts("nucleus_task_no_effect_report_alignment: ok");
    return 0;
}
