#include "latticra/nucleus_task_plan.h"

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

static latticra_nucleus_task_result_t allowed_task(latticra_nucleus_task_policy_t policy) {
    latticra_nucleus_task_result_t task;
    memset(&task, 0, sizeof(task));
    task.status = LATTICRA_STATUS_OK;
    task.record_count = 1u;
    task.no_effect = 1;
    task.record.policy = policy;
    task.record.denial = LATTICRA_NUCLEUS_TASK_DENIAL_OK;
    task.record.gate_state = LATTICRA_NUCLEUS_TASK_GATE_DISABLED;
    return task;
}

static int accepted_no_effect_sequence_reports_plan(void) {
    latticra_nucleus_task_result_t tasks[3];
    latticra_nucleus_task_plan_request_t request;
    latticra_nucleus_task_plan_result_t result;
    char report[LATTICRA_NUCLEUS_TASK_PLAN_REPORT_MAX];

    tasks[0] = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT);
    tasks[1] = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW);
    tasks[2] = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION);

    memset(&request, 0, sizeof(request));
    (void)strcpy(request.plan_id, "plan-alpha");
    request.tasks = tasks;
    request.task_count = 3u;

    CHECK_TRUE(latticra_nucleus_task_plan_evaluate(&request, &result) == LATTICRA_STATUS_OK);
    CHECK_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE);
    CHECK_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK);
    CHECK_TRUE(result.record.accepted_count == 3u);
    CHECK_TRUE(result.record.blocked_count == 0u);
    CHECK_TRUE(result.record.has_blocked_task == 0);
    CHECK_TRUE(result.record.no_effect == 1);
    CHECK_TRUE(result.record.execution_allowed == 0);
    CHECK_TRUE(result.record.mutation_allowed == 0);
    CHECK_TRUE(result.record.server_allowed == 0);
    CHECK_TRUE(result.record.recovery_allowed == 0);
    CHECK_TRUE(result.record.hardware_allowed == 0);

    CHECK_TRUE(latticra_nucleus_task_plan_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK);
    CHECK_TEXT(report, "LATTICRA NUCLEUS TASK PLAN REPORT");
    CHECK_TEXT(report, "plan_id=plan-alpha");
    CHECK_TEXT(report, "task_count=3");
    CHECK_TEXT(report, "accepted_count=3");
    CHECK_TEXT(report, "policy=allow-no-effect-sequence");
    CHECK_TEXT(report, "reason=ok");
    CHECK_TEXT(report, "no_effect=1");
    CHECK_TEXT(report, "execution_allowed=0");
    CHECK_TEXT(report, "mutation_allowed=0");
    return 0;
}

static int future_gated_task_blocks_plan(void) {
    latticra_nucleus_task_result_t tasks[2];
    latticra_nucleus_task_plan_request_t request;
    latticra_nucleus_task_plan_result_t result;

    tasks[0] = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT);
    tasks[1] = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE);
    tasks[1].record.denial = LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE;
    tasks[1].record.gate_state = LATTICRA_NUCLEUS_TASK_GATE_PLANNED;

    memset(&request, 0, sizeof(request));
    (void)strcpy(request.plan_id, "plan-future-gate");
    request.tasks = tasks;
    request.task_count = 2u;

    CHECK_TRUE(latticra_nucleus_task_plan_evaluate(&request, &result) == LATTICRA_STATUS_OK);
    CHECK_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE);
    CHECK_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED);
    CHECK_TRUE(result.record.accepted_count == 1u);
    CHECK_TRUE(result.record.has_blocked_task == 1);
    CHECK_TRUE(result.record.first_blocked_index == 1u);
    CHECK_TRUE(result.record.execution_allowed == 0);
    CHECK_TRUE(result.record.mutation_allowed == 0);
    return 0;
}

static int non_no_effect_flags_block_plan(void) {
    latticra_nucleus_task_result_t task;
    latticra_nucleus_task_plan_request_t request;
    latticra_nucleus_task_plan_result_t result;

    task = allowed_task(LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT);
    task.record.executed = 1;

    memset(&request, 0, sizeof(request));
    (void)strcpy(request.plan_id, "plan-non-no-effect");
    request.tasks = &task;
    request.task_count = 1u;

    CHECK_TRUE(latticra_nucleus_task_plan_evaluate(&request, &result) == LATTICRA_STATUS_OK);
    CHECK_TRUE(result.record.policy == LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY);
    CHECK_TRUE(result.record.denial == LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NON_NO_EFFECT_FLAGS);
    CHECK_TRUE(result.record.accepted_count == 0u);
    CHECK_TRUE(result.record.has_blocked_task == 1);
    CHECK_TRUE(result.record.first_blocked_index == 0u);
    CHECK_TRUE(result.record.no_effect == 1);
    CHECK_TRUE(result.record.execution_allowed == 0);
    return 0;
}

int main(void) {
    CHECK_TRUE(accepted_no_effect_sequence_reports_plan() == 0);
    CHECK_TRUE(future_gated_task_blocks_plan() == 0);
    CHECK_TRUE(non_no_effect_flags_block_plan() == 0);
    puts("nucleus_task_plan_invariants: ok");
    return 0;
}
