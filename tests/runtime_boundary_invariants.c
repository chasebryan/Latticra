#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_runtime_boundary_authority_summary_t authority_ok(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    authority.no_effect = 1;
    return authority;
}

static latticra_nucleus_task_result_t task_ok(void) {
    latticra_nucleus_task_result_t task;
    memset(&task, 0, sizeof(task));
    task.status = LATTICRA_STATUS_OK;
    task.record_count = 1u;
    task.no_effect = 1;
    task.record.policy = LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT;
    task.record.denial = LATTICRA_NUCLEUS_TASK_DENIAL_OK;
    return task;
}

static latticra_runtime_boundary_request_t base_request(const latticra_runtime_boundary_authority_summary_t *authority) {
    latticra_runtime_boundary_request_t request;
    memset(&request, 0, sizeof(request));
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.authority = authority;
    return request;
}

static int runtime_boundary_smoke_classifies_without_effects(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "classify status");
    EXPECT_TRUE(result.no_effect == 1, "no-effect flag preserved");
    EXPECT_TRUE(result.record_count == 1u, "record count initialized");
    EXPECT_TRUE(result.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation denied");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "default policy denies");
    return 0;
}

static int runtime_boundary_requires_authority(void) {
    latticra_runtime_boundary_request_t request = base_request(0);
    latticra_runtime_boundary_result_t result;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "missing authority status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED, "missing authority denied");
    return 0;
}

static int runtime_boundary_requires_authority_success(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    authority.status = LATTICRA_STATUS_BUFFER_TOO_SMALL;
    request = base_request(&authority);
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "bad authority status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED, "bad authority denied");
    return 0;
}

static int runtime_boundary_requires_no_effect_authority_flags(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    authority.mutation_allowed = 1;
    request = base_request(&authority);
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "authority flags status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS, "authority flags denied");
    return 0;
}

static int runtime_boundary_denies_unknown_request(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_UNKNOWN;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "unknown request status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST, "unknown request denied");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "unknown request policy deny");
    return 0;
}

static int runtime_boundary_denies_unknown_effect(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "unknown effect status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT, "unknown effect denied");
    return 0;
}

static int runtime_boundary_requires_task_for_task_report(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "missing task status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED, "missing task denied");
    return 0;
}

static int runtime_boundary_accepts_valid_task_metadata_for_task_report(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_nucleus_task_result_t task = task_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT;
    request.task = &task;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "valid task status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED, "valid task remains runtime disabled");
    EXPECT_TRUE(result.record.task_policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, "task policy copied");
    EXPECT_TRUE(result.record.task_reason == LATTICRA_NUCLEUS_TASK_DENIAL_OK, "task reason copied");
    return 0;
}

static int runtime_boundary_future_gates_operational_requests(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "future gate status");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE, "future gate policy");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE, "future gate reason");
    EXPECT_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED, "future gate planned");
    EXPECT_TRUE(result.record.executed == 0, "future gate not executed");
    return 0;
}

static int runtime_boundary_operator_confirmation_does_not_override_policy(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_runtime_boundary_request_t request = base_request(&authority);
    latticra_runtime_boundary_result_t result;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "operator confirmation status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED, "operator confirmation denied");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "operator confirmation cannot allow");
    return 0;
}

static int runtime_boundary_report_is_bounded(void) {
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];
    char tiny[1];
    memset(&result, 0, sizeof(result));
    result.status = LATTICRA_STATUS_OK;
    result.no_effect = 1;
    result.record.request_kind = LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY;
    result.record.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    result.record.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    result.record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY;
    result.record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED;
    result.record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED;
    result.record.authority.status = LATTICRA_STATUS_OK;
    result.record.authority.no_effect = 1;
    result.record.task_policy = LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT;
    result.record.task_reason = LATTICRA_NUCLEUS_TASK_DENIAL_OK;
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "report status");
    EXPECT_TRUE(strstr(report, "LATTICRA RUNTIME BOUNDARY REPORT") != 0, "report header");
    EXPECT_TRUE(strstr(report, "request=parse-only") != 0, "report request");
    EXPECT_TRUE(strstr(report, "requested_effect=none") != 0, "report effect");
    EXPECT_TRUE(strstr(report, "mode=report-only") != 0, "report mode");
    EXPECT_TRUE(strstr(report, "policy=deny") != 0, "report policy");
    EXPECT_TRUE(strstr(report, "reason=runtime-disabled") != 0, "report reason");
    EXPECT_TRUE(strstr(report, "gate=blocked") != 0, "report gate");
    EXPECT_TRUE(strstr(report, "operator_confirmation=not-applicable") != 0, "report operator confirmation");
    EXPECT_TRUE(strstr(report, "authority_status=0") != 0, "report authority status");
    EXPECT_TRUE(strstr(report, "authority_no_effect=1") != 0, "report authority no-effect");
    EXPECT_TRUE(strstr(report, "task_policy=allow-report") != 0, "report task policy");
    EXPECT_TRUE(strstr(report, "task_reason=ok") != 0, "report task reason");
    EXPECT_TRUE(strstr(report, "no_effect=1") != 0, "report no-effect flag");
    EXPECT_TRUE(strstr(report, "execution_allowed=0") != 0, "report execution flag");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0") != 0, "report mutation flag");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    return 0;
}

static int runtime_boundary_null_arguments_are_rejected(void) {
    latticra_runtime_boundary_result_t result;
    EXPECT_TRUE(latticra_runtime_boundary_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "null request rejected");
    EXPECT_TRUE(latticra_runtime_boundary_classify(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null result rejected");
    EXPECT_TRUE(latticra_runtime_boundary_report(0, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT, "null report args rejected");
    return 0;
}

int main(void) {
    if (runtime_boundary_smoke_classifies_without_effects() != 0) return 1;
    if (runtime_boundary_requires_authority() != 0) return 1;
    if (runtime_boundary_requires_authority_success() != 0) return 1;
    if (runtime_boundary_requires_no_effect_authority_flags() != 0) return 1;
    if (runtime_boundary_denies_unknown_request() != 0) return 1;
    if (runtime_boundary_denies_unknown_effect() != 0) return 1;
    if (runtime_boundary_requires_task_for_task_report() != 0) return 1;
    if (runtime_boundary_accepts_valid_task_metadata_for_task_report() != 0) return 1;
    if (runtime_boundary_future_gates_operational_requests() != 0) return 1;
    if (runtime_boundary_operator_confirmation_does_not_override_policy() != 0) return 1;
    if (runtime_boundary_report_is_bounded() != 0) return 1;
    if (runtime_boundary_null_arguments_are_rejected() != 0) return 1;
    puts("runtime_boundary_invariants: ok");
    return 0;
}
