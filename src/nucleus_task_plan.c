#include "latticra/nucleus_task_plan.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

const char *latticra_nucleus_task_plan_policy_label(latticra_nucleus_task_plan_policy_t policy) {
    switch (policy) {
    case LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE: return "allow-no-effect-sequence";
    case LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY: return "deny";
    case LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE: return "requires-future-gate";
    case LATTICRA_NUCLEUS_TASK_PLAN_POLICY_INTERNAL_ERROR:
    default: return "internal-error";
    }
}

const char *latticra_nucleus_task_plan_denial_label(latticra_nucleus_task_plan_denial_t denial) {
    switch (denial) {
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK: return "ok";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NULL_ARGUMENT: return "null-argument";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_EMPTY_PLAN: return "empty-plan";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TOO_MANY_TASKS: return "too-many-tasks";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_FAILED: return "task-failed";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_DENIED: return "task-denied";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NON_NO_EFFECT_FLAGS: return "non-no-effect-flags";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED: return "future-gate-required";
    case LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_INTERNAL_ERROR:
    default: return "internal-error";
    }
}

static void default_record(latticra_nucleus_task_plan_record_t *record) {
    if (record == 0) return;
    record->plan_id[0] = '\0';
    record->task_count = 0u;
    record->accepted_count = 0u;
    record->blocked_count = 0u;
    record->has_blocked_task = 0;
    record->first_blocked_index = 0u;
    record->policy = LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY;
    record->denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_EMPTY_PLAN;
    record->no_effect = 1;
    record->execution_allowed = 0;
    record->mutation_allowed = 0;
    record->server_allowed = 0;
    record->recovery_allowed = 0;
    record->hardware_allowed = 0;
    record->evidence_level = 0u;
}

static void default_result(latticra_nucleus_task_plan_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    default_record(&result->record);
    result->record_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static void copy_plan_id(char *destination, size_t destination_len, const char *source) {
    size_t i = 0u;
    if (destination == 0 || destination_len == 0u) return;
    destination[0] = '\0';
    if (source == 0) return;
    while (i + 1u < destination_len && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

static int result_flags_no_effect(const latticra_nucleus_task_result_t *task) {
    return task != 0 &&
           task->no_effect == 1 &&
           task->execution_allowed == 0 &&
           task->mutation_allowed == 0 &&
           task->server_allowed == 0 &&
           task->recovery_allowed == 0 &&
           task->hardware_allowed == 0;
}

static int record_flags_no_effect(const latticra_nucleus_task_result_t *task) {
    return task != 0 &&
           task->record.executed == 0 &&
           task->record.mutation_allowed == 0 &&
           task->record.server_interaction_allowed == 0 &&
           task->record.recovery_allowed == 0 &&
           task->record.hardware_allowed == 0;
}

static int policy_is_allowed_no_effect(latticra_nucleus_task_policy_t policy) {
    return policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW ||
           policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT ||
           policy == LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION;
}

static int task_requires_future_gate(const latticra_nucleus_task_result_t *task) {
    return task != 0 &&
           (task->record.policy == LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE ||
            task->record.denial == LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE ||
            task->record.gate_state == LATTICRA_NUCLEUS_TASK_GATE_PLANNED);
}

static void set_blocked(latticra_nucleus_task_plan_result_t *result,
                        latticra_nucleus_task_plan_policy_t policy,
                        latticra_nucleus_task_plan_denial_t denial,
                        size_t index) {
    if (result == 0) return;
    result->record.policy = policy;
    result->record.denial = denial;
    result->record.has_blocked_task = 1;
    result->record.first_blocked_index = index;
    if (result->record.task_count == 0u) {
        result->record.blocked_count = 0u;
    } else if (result->record.task_count > result->record.accepted_count) {
        result->record.blocked_count = result->record.task_count - result->record.accepted_count;
    } else {
        result->record.blocked_count = 1u;
    }
    result->record.no_effect = 1;
    result->record.execution_allowed = 0;
    result->record.mutation_allowed = 0;
    result->record.server_allowed = 0;
    result->record.recovery_allowed = 0;
    result->record.hardware_allowed = 0;
}

latticra_status_t latticra_nucleus_task_plan_evaluate(const latticra_nucleus_task_plan_request_t *request,
                                                      latticra_nucleus_task_plan_result_t *result) {
    size_t i;
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    default_result(result);
    if (request == 0) {
        result->record.denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    copy_plan_id(result->record.plan_id, sizeof(result->record.plan_id), request->plan_id);
    result->record.task_count = request->task_count;
    result->record_count = 1u;
    result->record.evidence_level = 1u;

    if (request->task_count == 0u) {
        set_blocked(result,
                    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY,
                    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_EMPTY_PLAN,
                    0u);
        return LATTICRA_STATUS_OK;
    }

    if (request->tasks == 0) {
        result->record.denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (request->task_count > LATTICRA_NUCLEUS_TASK_PLAN_TASK_MAX) {
        set_blocked(result,
                    LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY,
                    LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TOO_MANY_TASKS,
                    LATTICRA_NUCLEUS_TASK_PLAN_TASK_MAX);
        return LATTICRA_STATUS_OK;
    }

    for (i = 0u; i < request->task_count; i++) {
        const latticra_nucleus_task_result_t *task = &request->tasks[i];
        if (task->status != LATTICRA_STATUS_OK || task->record_count == 0u) {
            set_blocked(result,
                        LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY,
                        LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_FAILED,
                        i);
            return LATTICRA_STATUS_OK;
        }
        if (!result_flags_no_effect(task) || !record_flags_no_effect(task)) {
            set_blocked(result,
                        LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY,
                        LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_NON_NO_EFFECT_FLAGS,
                        i);
            return LATTICRA_STATUS_OK;
        }
        if (task_requires_future_gate(task)) {
            set_blocked(result,
                        LATTICRA_NUCLEUS_TASK_PLAN_POLICY_REQUIRES_FUTURE_GATE,
                        LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_FUTURE_GATE_REQUIRED,
                        i);
            return LATTICRA_STATUS_OK;
        }
        if (task->record.denial != LATTICRA_NUCLEUS_TASK_DENIAL_OK ||
            !policy_is_allowed_no_effect(task->record.policy)) {
            set_blocked(result,
                        LATTICRA_NUCLEUS_TASK_PLAN_POLICY_DENY,
                        LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_TASK_DENIED,
                        i);
            return LATTICRA_STATUS_OK;
        }
        result->record.accepted_count++;
    }

    result->record.policy = LATTICRA_NUCLEUS_TASK_PLAN_POLICY_ALLOW_NO_EFFECT_SEQUENCE;
    result->record.denial = LATTICRA_NUCLEUS_TASK_PLAN_DENIAL_OK;
    result->record.blocked_count = 0u;
    result->record.has_blocked_task = 0;
    result->record.first_blocked_index = 0u;
    return LATTICRA_STATUS_OK;
}

static int appendf(char *buffer, size_t buffer_len, size_t *used, const char *format, ...) {
    int written;
    va_list args;
    if (buffer == 0 || used == 0 || format == 0 || *used >= buffer_len) return 0;
    va_start(args, format);
    written = vsnprintf(buffer + *used, buffer_len - *used, format, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) return 0;
    *used += (size_t)written;
    return 1;
}

latticra_status_t latticra_nucleus_task_plan_report(const latticra_nucleus_task_plan_result_t *result,
                                                    char *buffer,
                                                    size_t buffer_len) {
    size_t used = 0u;
    const latticra_nucleus_task_plan_record_t *record;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    record = &result->record;

    if (!appendf(buffer, buffer_len, &used, "LATTICRA NUCLEUS TASK PLAN REPORT\n") ||
        !appendf(buffer, buffer_len, &used, "status=%d\n", (int)result->status) ||
        !appendf(buffer, buffer_len, &used, "plan_id=%s\n", record->plan_id) ||
        !appendf(buffer, buffer_len, &used, "record_count=%lu\n", (unsigned long)result->record_count) ||
        !appendf(buffer, buffer_len, &used, "task_count=%lu\n", (unsigned long)record->task_count) ||
        !appendf(buffer, buffer_len, &used, "accepted_count=%lu\n", (unsigned long)record->accepted_count) ||
        !appendf(buffer, buffer_len, &used, "blocked_count=%lu\n", (unsigned long)record->blocked_count) ||
        !appendf(buffer, buffer_len, &used, "has_blocked_task=%d\n", record->has_blocked_task) ||
        !appendf(buffer, buffer_len, &used, "first_blocked_index=%lu\n", (unsigned long)record->first_blocked_index) ||
        !appendf(buffer, buffer_len, &used, "policy=%s\n", latticra_nucleus_task_plan_policy_label(record->policy)) ||
        !appendf(buffer, buffer_len, &used, "reason=%s\n", latticra_nucleus_task_plan_denial_label(record->denial)) ||
        !appendf(buffer, buffer_len, &used, "no_effect=%d\n", record->no_effect) ||
        !appendf(buffer, buffer_len, &used, "execution_allowed=%d\n", record->execution_allowed) ||
        !appendf(buffer, buffer_len, &used, "mutation_allowed=%d\n", record->mutation_allowed) ||
        !appendf(buffer, buffer_len, &used, "server_allowed=%d\n", record->server_allowed) ||
        !appendf(buffer, buffer_len, &used, "recovery_allowed=%d\n", record->recovery_allowed) ||
        !appendf(buffer, buffer_len, &used, "hardware_allowed=%d\n", record->hardware_allowed) ||
        !appendf(buffer, buffer_len, &used, "evidence_level=%u\n", record->evidence_level)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
