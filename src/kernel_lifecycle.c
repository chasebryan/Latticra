#include "latticra/kernel_lifecycle.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void lifecycle_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_lifecycle_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "pending");
    lifecycle_copy(result->policy_status, sizeof(result->policy_status), "default-deny");
    result->final_state = LATTICRA_KERNEL_STATE_CREATED;
    result->step_count = 0u;
    result->state_change_count = 0u;
    result->lifecycle_complete = 0;
    result->external_effect_performed = 0;
    result->evidence_level = 10u;
}

latticra_status_t latticra_kernel_lifecycle_default_request(
    latticra_kernel_lifecycle_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    request->target_state = LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
    request->gate = LATTICRA_KERNEL_STATE_GATE_DENY;
    request->max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    return LATTICRA_STATUS_OK;
}

static int state_is_known(latticra_kernel_state_kind_t state) {
    return state == LATTICRA_KERNEL_STATE_CREATED ||
           state == LATTICRA_KERNEL_STATE_INITIALIZED ||
           state == LATTICRA_KERNEL_STATE_REGISTRY_READY ||
           state == LATTICRA_KERNEL_STATE_SCHEDULER_READY ||
           state == LATTICRA_KERNEL_STATE_MEMORY_MAP_READY ||
           state == LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY ||
           state == LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY ||
           state == LATTICRA_KERNEL_STATE_IPC_TABLE_READY ||
           state == LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY ||
           state == LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY ||
           state == LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY ||
           state == LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
}

static latticra_kernel_state_kind_t next_state_after(latticra_kernel_state_kind_t state) {
    switch (state) {
        case LATTICRA_KERNEL_STATE_CREATED:
            return LATTICRA_KERNEL_STATE_INITIALIZED;
        case LATTICRA_KERNEL_STATE_INITIALIZED:
            return LATTICRA_KERNEL_STATE_REGISTRY_READY;
        case LATTICRA_KERNEL_STATE_REGISTRY_READY:
            return LATTICRA_KERNEL_STATE_SCHEDULER_READY;
        case LATTICRA_KERNEL_STATE_SCHEDULER_READY:
            return LATTICRA_KERNEL_STATE_MEMORY_MAP_READY;
        case LATTICRA_KERNEL_STATE_MEMORY_MAP_READY:
            return LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY;
        case LATTICRA_KERNEL_STATE_PROCESS_TABLE_READY:
            return LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY;
        case LATTICRA_KERNEL_STATE_SYSCALL_TABLE_READY:
            return LATTICRA_KERNEL_STATE_IPC_TABLE_READY;
        case LATTICRA_KERNEL_STATE_IPC_TABLE_READY:
            return LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY;
        case LATTICRA_KERNEL_STATE_VFS_NAMESPACE_READY:
            return LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY;
        case LATTICRA_KERNEL_STATE_DEVICE_REGISTRY_READY:
            return LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY;
        case LATTICRA_KERNEL_STATE_DRIVER_CATALOG_READY:
            return LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY;
        case LATTICRA_KERNEL_STATE_INTERRUPT_TABLE_READY:
        default:
            return state;
    }
}

static void finalize_result(latticra_kernel_lifecycle_result_t *result) {
    result->final_state = result->machine.current_state;
    result->external_effect_performed = result->machine.external_effect_performed;
}

latticra_status_t latticra_kernel_lifecycle_run(
    const latticra_kernel_lifecycle_request_t *request,
    latticra_kernel_lifecycle_result_t *result) {
    latticra_kernel_state_machine_step_request_t step_request;
    latticra_kernel_state_machine_step_result_t step_result;
    latticra_kernel_state_kind_t next_state;
    size_t max_steps;
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_state_machine_init(&result->machine);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "machine-init-failed");
        return status;
    }

    result->final_state = result->machine.current_state;

    if (request->gate != LATTICRA_KERNEL_STATE_GATE_ALLOW) {
        lifecycle_copy(result->policy_status, sizeof(result->policy_status), "gate-denied");
        lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "not-started");
        finalize_result(result);
        return result->status;
    }

    lifecycle_copy(result->policy_status, sizeof(result->policy_status), "gate-allowed");

    if (!state_is_known(request->target_state)) {
        lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "invalid-target");
        finalize_result(result);
        return result->status;
    }

    max_steps = request->max_steps;
    if (max_steps == 0u || max_steps > LATTICRA_KERNEL_LIFECYCLE_STEP_MAX) {
        max_steps = LATTICRA_KERNEL_LIFECYCLE_STEP_MAX;
    }

    while (result->machine.current_state != request->target_state && result->step_count < max_steps) {
        if (result->machine.current_state > request->target_state) {
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "target-before-current");
            finalize_result(result);
            return result->status;
        }

        next_state = next_state_after(result->machine.current_state);
        if (next_state == result->machine.current_state) {
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "no-forward-step");
            finalize_result(result);
            return result->status;
        }

        status = latticra_kernel_state_machine_default_step_request(&step_request);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "step-request-failed");
            finalize_result(result);
            return status;
        }

        step_request.target_state = next_state;
        step_request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

        status = latticra_kernel_state_machine_step(&result->machine, &step_request, &step_result);
        if (status != LATTICRA_STATUS_OK) {
            result->status = status;
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "step-failed");
            finalize_result(result);
            return status;
        }

        result->step_count += 1u;
        if (step_result.state_mutated) result->state_change_count += 1u;

        if (step_result.external_effect_performed) {
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "external-effect-blocked");
            finalize_result(result);
            return result->status;
        }

        if (!step_result.state_mutated && result->machine.current_state != request->target_state) {
            lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status), "step-did-not-advance");
            finalize_result(result);
            return result->status;
        }
    }

    finalize_result(result);
    result->lifecycle_complete = result->final_state == request->target_state;
    lifecycle_copy(result->lifecycle_status, sizeof(result->lifecycle_status),
        result->lifecycle_complete ? "lifecycle-complete" : "step-limit-reached");
    return result->status;
}

static latticra_status_t append_text(
    char *buffer,
    size_t buffer_len,
    size_t *used,
    const char *fmt,
    ...) {
    int written;
    va_list args;
    if (*used >= buffer_len) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    va_start(args, fmt);
    written = vsnprintf(buffer + *used, buffer_len - *used, fmt, args);
    va_end(args);
    if (written < 0 || (size_t)written >= buffer_len - *used) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    *used += (size_t)written;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_kernel_lifecycle_report(
    const latticra_kernel_lifecycle_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL LIFECYCLE REPORT\n"
        "lifecycle_status=%s\n"
        "policy_status=%s\n"
        "final_state=%s\n"
        "step_count=%lu\n"
        "state_change_count=%lu\n"
        "lifecycle_complete=%d\n"
        "external_effect_performed=%d\n"
        "machine_log_count=%lu\n"
        "evidence_level=%u\n",
        result->lifecycle_status,
        result->policy_status,
        latticra_kernel_state_label(result->final_state),
        (unsigned long)result->step_count,
        (unsigned long)result->state_change_count,
        result->lifecycle_complete,
        result->external_effect_performed,
        (unsigned long)result->machine.log_count,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->machine.log_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "log[%lu].from=%s\n"
            "log[%lu].to=%s\n"
            "log[%lu].status=%s\n"
            "log[%lu].state_change_performed=%d\n"
            "log[%lu].external_effect_performed=%d\n",
            (unsigned long)i,
            latticra_kernel_state_label(result->machine.log[i].from_state),
            (unsigned long)i,
            latticra_kernel_state_label(result->machine.log[i].to_state),
            (unsigned long)i,
            result->machine.log[i].status,
            (unsigned long)i,
            result->machine.log[i].state_change_performed,
            (unsigned long)i,
            result->machine.log[i].external_effect_performed);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
