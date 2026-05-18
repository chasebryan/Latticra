#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define CHECK_TRUE(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "check failed: %s\n", #condition); \
            return 1; \
        } \
    } while (0)

#define CHECK_TEXT(haystack, needle) \
    do { \
        if (strstr((haystack), (needle)) == 0) { \
            fprintf(stderr, "missing: %s\n", (needle)); \
            return 1; \
        } \
    } while (0)

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    authority.no_effect = 1;
    return authority;
}

static latticra_nucleus_task_plan_result_t ok_plan(void) {
    latticra_nucleus_task_plan_result_t plan;
    memset(&plan, 0, sizeof(plan));
    plan.status = LATTICRA_STATUS_OK;
    plan.record_count = 1u;
    plan.no_effect = 1;
    plan.record.policy = LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE;
    plan.record.denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK;
    plan.record.task_count = 2u;
    plan.record.accepted_count = 2u;
    plan.record.blocked_count = 0u;
    plan.record.has_blocked_task = 0;
    plan.record.first_blocked_index = 0u;
    plan.record.no_effect = 1;
    return plan;
}

static int valid_task_plan_report_is_allowed_and_visible(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    latticra_nucleus_task_plan_result_t plan;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    authority = ok_authority();
    plan = ok_plan();

    memset(&request, 0, sizeof(request));
    (void)strcpy(request.runtime_id, "runtime-plan-alpha");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_PLAN_REPORT;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.plan = &plan;

    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK);
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT);
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK);
    CHECK_TRUE(result.record.allowed_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ);
    CHECK_TRUE(result.record.plan_policy == LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE);
    CHECK_TRUE(result.record.plan_reason == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK);
    CHECK_TRUE(result.record.plan_task_count == 2u);
    CHECK_TRUE(result.record.plan_accepted_count == 2u);
    CHECK_TRUE(result.record.plan_blocked_count == 0u);
    CHECK_TRUE(result.record.plan_no_effect == 1);
    CHECK_TRUE(result.record.plan_execution_allowed == 0);
    CHECK_TRUE(result.record.plan_mutation_allowed == 0);
    CHECK_TRUE(result.record.plan_server_allowed == 0);
    CHECK_TRUE(result.record.plan_recovery_allowed == 0);
    CHECK_TRUE(result.record.plan_hardware_allowed == 0);

    CHECK_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK);
    CHECK_TEXT(report, "request=nucleus-task-plan-report");
    CHECK_TEXT(report, "policy=allow-report");
    CHECK_TEXT(report, "reason=ok");
    CHECK_TEXT(report, "plan_policy=allow-no-effect-sequence");
    CHECK_TEXT(report, "plan_reason=ok");
    CHECK_TEXT(report, "plan_task_count=2");
    CHECK_TEXT(report, "plan_accepted_count=2");
    CHECK_TEXT(report, "plan_blocked_count=0");
    CHECK_TEXT(report, "plan_no_effect=1");
    CHECK_TEXT(report, "plan_execution_allowed=0");
    CHECK_TEXT(report, "plan_mutation_allowed=0");
    return 0;
}

static int failed_task_plan_is_denied_but_reported(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    latticra_nucleus_task_plan_result_t plan;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    authority = ok_authority();
    plan = ok_plan();
    plan.record.policy = LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE;
    plan.record.denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED;
    plan.record.accepted_count = 1u;
    plan.record.blocked_count = 1u;
    plan.record.has_blocked_task = 1;
    plan.record.first_blocked_index = 1u;

    memset(&request, 0, sizeof(request));
    (void)strcpy(request.runtime_id, "runtime-plan-blocked");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_PLAN_REPORT;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.plan = &plan;

    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK);
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY);
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED);
    CHECK_TRUE(result.record.plan_policy == LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE);
    CHECK_TRUE(result.record.plan_reason == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED);
    CHECK_TRUE(result.record.plan_accepted_count == 1u);
    CHECK_TRUE(result.record.plan_blocked_count == 1u);
    CHECK_TRUE(result.record.plan_has_blocked_task == 1);
    CHECK_TRUE(result.record.plan_first_blocked_index == 1u);

    CHECK_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK);
    CHECK_TEXT(report, "policy=deny");
    CHECK_TEXT(report, "reason=task-failed");
    CHECK_TEXT(report, "plan_policy=requires-future-gate");
    CHECK_TEXT(report, "plan_reason=future-gate-required");
    CHECK_TEXT(report, "plan_accepted_count=1");
    CHECK_TEXT(report, "plan_blocked_count=1");
    CHECK_TEXT(report, "plan_has_blocked_task=1");
    CHECK_TEXT(report, "plan_first_blocked_index=1");
    return 0;
}

int main(void) {
    CHECK_TRUE(valid_task_plan_report_is_allowed_and_visible() == 0);
    CHECK_TRUE(failed_task_plan_is_denied_but_reported() == 0);
    puts("runtime_boundary_task_plan_report: ok");
    return 0;
}
