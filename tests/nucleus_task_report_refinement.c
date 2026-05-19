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
    (void)snprintf(authority->validator_label, sizeof(authority->validator_label), "%s", "task-report-refinement");
    (void)snprintf(authority->requested_effect_label, sizeof(authority->requested_effect_label), "%s", "none");
    (void)snprintf(authority->denial_reason, sizeof(authority->denial_reason), "%s", "ok");
    authority->no_effect = 1;
}

static latticra_l_ui_source_span_t span_ok(void) {
    latticra_l_ui_source_span_t span;
    span.start_offset = 0u;
    span.end_offset = 8u;
    span.start_line = 1u;
    span.start_column = 1u;
    span.end_line = 1u;
    span.end_column = 9u;
    return span;
}

static latticra_nucleus_task_request_t base_request(
    latticra_nucleus_task_request_kind_t kind,
    latticra_nucleus_task_effect_t effect,
    const latticra_nucleus_task_authority_summary_t *authority) {
    latticra_nucleus_task_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.task_id, sizeof(request.task_id), "%s", "task-report-refinement");
    request.request_kind = kind;
    request.requested_effect = effect;
    request.operator_confirmation = LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE;
    request.rollback_state = LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE;
    request.authority = authority;
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

static int nucleus_task_report_refinement_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_nucleus_task_report_classification_label(LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED), "accepted", "accepted label");
    EXPECT_STR_EQ(latticra_nucleus_task_report_classification_label(LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED), "future-gated", "future gated label");
    EXPECT_STR_EQ(latticra_nucleus_task_report_classification_label(LATTICRA_NUCLEUS_TASK_REPORT_DENIED), "denied", "denied label");
    EXPECT_STR_EQ(latticra_nucleus_task_report_classification_label(LATTICRA_NUCLEUS_TASK_REPORT_INVALID), "invalid", "invalid label");
    EXPECT_STR_EQ(latticra_nucleus_task_domain_label(LATTICRA_NUCLEUS_TASK_DOMAIN_STATE), "state", "state domain");
    EXPECT_STR_EQ(latticra_nucleus_task_domain_label(LATTICRA_NUCLEUS_TASK_DOMAIN_TRANSITION), "transition", "transition domain");
    EXPECT_STR_EQ(latticra_nucleus_task_domain_label(LATTICRA_NUCLEUS_TASK_DOMAIN_AUTHORITY), "authority", "authority domain");
    EXPECT_STR_EQ(latticra_nucleus_task_domain_label(LATTICRA_NUCLEUS_TASK_DOMAIN_BOOT), "boot", "boot domain");
    EXPECT_STR_EQ(latticra_nucleus_task_authorization_state_label(LATTICRA_NUCLEUS_TASK_AUTH_NOT_REQUESTED), "not-requested", "auth not requested");
    EXPECT_STR_EQ(latticra_nucleus_task_authorization_state_label(LATTICRA_NUCLEUS_TASK_AUTH_CHECKED), "checked", "auth checked");
    EXPECT_STR_EQ(latticra_nucleus_task_authorization_state_label(LATTICRA_NUCLEUS_TASK_AUTH_DENIED), "denied", "auth denied");
    EXPECT_STR_EQ(latticra_nucleus_task_authorization_state_label(LATTICRA_NUCLEUS_TASK_AUTH_RESERVED_FOR_FUTURE), "reserved-for-future", "auth future");
    EXPECT_STR_EQ(latticra_nucleus_task_authorization_state_label(LATTICRA_NUCLEUS_TASK_AUTH_UNAVAILABLE), "unavailable", "auth unavailable");
    return 0;
}

static int nucleus_task_report_refinement_reports_accepted_state_report(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_preview_t preview;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    authority_ok(&authority);
    preview = preview_for(LATTICRA_REQUEST_STATE_REPORT, LATTICRA_EFFECT_NONE);
    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    request.preview = &preview;

    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "state report classify");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED, "accepted classification");
    EXPECT_TRUE(result.record.task_domain == LATTICRA_NUCLEUS_TASK_DOMAIN_STATE, "state domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_NUCLEUS_TASK_AUTH_NOT_REQUESTED, "auth not requested");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 1, "prereq satisfied");
    EXPECT_TRUE(result.record.no_effect_chain_ok == 1, "no-effect chain ok");
    EXPECT_TRUE(result.record.evidence_level == 2u, "accepted evidence level");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "state report output");
    EXPECT_TRUE(strstr(report, "report_classification=accepted\n") != 0, "accepted report field");
    EXPECT_TRUE(strstr(report, "task_domain=state\n") != 0, "state domain report field");
    EXPECT_TRUE(strstr(report, "authorization_state=not-requested\n") != 0, "auth report field");
    EXPECT_TRUE(strstr(report, "prerequisites_satisfied=1\n") != 0, "prereq report field");
    EXPECT_TRUE(strstr(report, "no_effect_chain_ok=1\n") != 0, "no effect report field");
    return 0;
}

static int nucleus_task_report_refinement_reports_authority_check(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;

    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "authority check classify");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED, "authority accepted");
    EXPECT_TRUE(result.record.task_domain == LATTICRA_NUCLEUS_TASK_DOMAIN_AUTHORITY, "authority domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_NUCLEUS_TASK_AUTH_CHECKED, "authority checked");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 1, "authority prereq ok");
    return 0;
}

static int nucleus_task_report_refinement_reports_future_gated_task(void) {
    latticra_nucleus_task_authority_summary_t authority;
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_REPORT_MAX];

    authority_ok(&authority);
    request = base_request(LATTICRA_NUCLEUS_TASK_BOOT_ACTION, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, &authority);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "future classify");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_FUTURE_GATED, "future classification");
    EXPECT_TRUE(result.record.task_domain == LATTICRA_NUCLEUS_TASK_DOMAIN_BOOT, "boot domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_NUCLEUS_TASK_AUTH_RESERVED_FOR_FUTURE, "future auth state");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 0, "future prereq false");
    EXPECT_TRUE(result.record.evidence_level == 1u, "future evidence level");

    EXPECT_TRUE(latticra_nucleus_task_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "future report output");
    EXPECT_TRUE(strstr(report, "report_classification=future-gated\n") != 0, "future report field");
    EXPECT_TRUE(strstr(report, "task_domain=boot\n") != 0, "boot domain report field");
    EXPECT_TRUE(strstr(report, "authorization_state=reserved-for-future\n") != 0, "future auth report field");
    return 0;
}

static int nucleus_task_report_refinement_reports_denied_prerequisite(void) {
    latticra_nucleus_task_request_t request;
    latticra_nucleus_task_result_t result;

    request = base_request(LATTICRA_NUCLEUS_TASK_STATE_REPORT, LATTICRA_NUCLEUS_TASK_EFFECT_NONE, 0);
    EXPECT_TRUE(latticra_nucleus_task_classify(&request, &result) == LATTICRA_STATUS_OK, "denied classify");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_DENIED, "denied classification");
    EXPECT_TRUE(result.record.task_domain == LATTICRA_NUCLEUS_TASK_DOMAIN_STATE, "denied state domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_NUCLEUS_TASK_AUTH_DENIED, "denied auth");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 0, "denied prereq false");
    EXPECT_TRUE(result.record.evidence_level == 1u, "denied evidence level");
    return 0;
}

static int nucleus_task_report_refinement_reports_invalid_request(void) {
    latticra_nucleus_task_result_t result;

    EXPECT_TRUE(latticra_nucleus_task_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "invalid classify");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_NUCLEUS_TASK_REPORT_INVALID, "invalid classification");
    EXPECT_TRUE(result.record.task_domain == LATTICRA_NUCLEUS_TASK_DOMAIN_UNKNOWN, "invalid domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_NUCLEUS_TASK_AUTH_UNAVAILABLE, "invalid auth");
    EXPECT_TRUE(result.record.prerequisites_satisfied == 0, "invalid prereq false");
    EXPECT_TRUE(result.record.evidence_level == 0u, "invalid evidence zero");
    return 0;
}

int main(void) {
    if (nucleus_task_report_refinement_labels_are_stable() != 0) return 1;
    if (nucleus_task_report_refinement_reports_accepted_state_report() != 0) return 1;
    if (nucleus_task_report_refinement_reports_authority_check() != 0) return 1;
    if (nucleus_task_report_refinement_reports_future_gated_task() != 0) return 1;
    if (nucleus_task_report_refinement_reports_denied_prerequisite() != 0) return 1;
    if (nucleus_task_report_refinement_reports_invalid_request() != 0) return 1;

    puts("nucleus_task_report_refinement: ok");
    return 0;
}
