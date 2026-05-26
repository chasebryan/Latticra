#ifndef LATTICRA_NUCLEUS_TASK_PLAN_H
#define LATTICRA_NUCLEUS_TASK_PLAN_H

#include "latticra/nucleus_task.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_NUCLEUS_TASK_PLAN_ID_MAX 64u
#define LATTICRA_NUCLEUS_TASK_PLAN_TASK_MAX 8u
#define LATTICRA_NUCLEUS_TASK_PLAN_REPORT_MAX 2048u

typedef enum {
    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE = 0,
    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY = 1,
    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE = 2,
    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_INTERNAL_ERROR = 3
} latticra_nucleus_task_plan_policy_t;

typedef enum {
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK = 0,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NULL_ARGUMENT = 1,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_EMPTY_PLAN = 2,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TOO_MANY_TASKS = 3,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_FAILED = 4,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_DENIED = 5,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NON_NO_EFFECT_FLAGS = 6,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED = 7,
    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_INTERNAL_ERROR = 8
} latticra_nucleus_task_plan_denial_t;

typedef struct {
    char plan_id[LATTICRA_NUCLEUS_TASK_PLAN_ID_MAX];
    const latticra_nucleus_task_result_t *tasks;
    size_t task_count;
} latticra_nucleus_task_plan_request_t;

typedef struct {
    char plan_id[LATTICRA_NUCLEUS_TASK_PLAN_ID_MAX];
    size_t task_count;
    size_t accepted_count;
    size_t blocked_count;
    int has_blocked_task;
    size_t first_blocked_index;
    latticra_nucleus_task_plan_policy_t policy;
    latticra_nucleus_task_plan_denial_t denial;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int network_allowed;
    int recovery_allowed;
    int hardware_allowed;
    unsigned int evidence_level;
} latticra_nucleus_task_plan_record_t;

typedef struct {
    latticra_status_t status;
    latticra_nucleus_task_plan_record_t record;
    size_t record_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int network_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_nucleus_task_plan_result_t;

const char *latticra_nucleus_task_plan_policy_label(latticra_nucleus_task_plan_policy_t policy);
const char *latticra_nucleus_task_plan_denial_label(latticra_nucleus_task_plan_denial_t denial);

latticra_status_t latticra_nucleus_task_plan_evaluate(
    const latticra_nucleus_task_plan_request_t *request,
    latticra_nucleus_task_plan_result_t *result);

latticra_status_t latticra_nucleus_task_plan_report(
    const latticra_nucleus_task_plan_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
