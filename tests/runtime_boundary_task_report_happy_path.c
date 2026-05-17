#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define CHECK_TRUE(value, label) \
    do { \
        if (!(value)) { \
            fprintf(stderr, "FAIL: %s\n", label); \
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

static latticra_nucleus_task_result_t ok_task(void) {
    latticra_nucleus_task_result_t task;
    memset(&task, 0, sizeof(task));
    task.status = LATTICRA_STATUS_OK;
    task.record_count = 1u;
    task.no_effect = 1;
    task.record.policy = LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT;
    task.record.denial = LATTICRA_NUCLEUS_TASK_DENIAL_OK;
    return task;
}

int main(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_nucleus_task_result_t task = ok_task();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", "runtime-task-report-ok");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.authority = &authority;
    request.task = &task;

    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "task report status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT, "task report policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "task report reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "task report gate");
    CHECK_TRUE(result.record.task_policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT, "task policy copied");
    CHECK_TRUE(result.record.task_reason == LATTICRA_NUCLEUS_TASK_DENIAL_OK, "task reason copied");
    CHECK_TRUE(result.record.task_executed == 0, "task not executed");
    CHECK_TRUE(result.record.executed == 0, "runtime not executed");
    CHECK_TRUE(result.execution_allowed == 0, "execution flag remains zero");

    puts("runtime_boundary_task_report_happy_path: ok");
    return 0;
}
