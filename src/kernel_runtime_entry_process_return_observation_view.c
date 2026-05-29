#include "latticra/kernel_runtime_entry_process_return_observation_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void process_return_observation_view_copy(
    char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    process_return_observation_view_copy(
        result->process_return_observation_view_status,
        sizeof(result->process_return_observation_view_status), "pending");
    process_return_observation_view_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->runtime_entry_process_return_observation_view_allowed = 0;
    result->runtime_entry_scheduler_return_observation_view_allowed = 0;
    result->runtime_entry_post_resume_observation_view_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->scheduler_return_observation_allowed = 0;
    result->process_return_observation_allowed = 0;
    result->process_return_allowed = 0;
    result->process_state_read_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 40u;
}

latticra_status_t
latticra_kernel_runtime_entry_process_return_observation_view_default_request(
    latticra_kernel_runtime_entry_process_return_observation_view_request_t
        *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_scheduler_return_observation_view_default_request(
            &request->runtime_entry_scheduler_return_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_process_return_observation_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const
latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t *
scheduler_return_observation_view_at(
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *view,
    size_t index) {
    if (index < view->scheduler_return_observation_view_count &&
        view->scheduler_return_observation_views[index].declared) {
        return &view->scheduler_return_observation_views[index];
    }
    return 0;
}

static unsigned long fallback_process_return_observation_view_token(
    size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 28000ul + (unsigned long)index;
}

static unsigned long fallback_scheduler_return_observation_view_token(
    size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 27000ul + (unsigned long)index;
}

static unsigned long fallback_post_resume_observation_view_token(
    size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 26000ul + (unsigned long)index;
}

static unsigned long fallback_user_mode_resume_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 25000ul + (unsigned long)index;
}

static unsigned long fallback_syscall_exit_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 24000ul + (unsigned long)index;
}

static unsigned long fallback_syscall_return_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 23000ul + (unsigned long)index;
}

static const char *fallback_process(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-process-metadata";
        case 1u:
            return "entropy-report-process-metadata";
        case 2u:
            return "console-report-process-metadata";
        case 3u:
            return "idle-process-metadata";
        default:
            return "reserved-process-metadata";
    }
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return
                "kernel-report-runtime-entry-process-return-observation-view";
        case 1u:
            return "entropy-runtime-entry-process-return-observation-view";
        case 2u:
            return "console-runtime-entry-process-return-observation-view";
        case 3u:
            return "idle-runtime-entry-process-return-observation-view";
        default:
            return "reserved-runtime-entry-process-return-observation-view";
    }
}

static void fill_process_return_observation_view(
    latticra_kernel_runtime_entry_process_return_observation_view_entry_t
        *entry,
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *view,
    size_t index) {
    const
    latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t
        *scheduler_view = scheduler_return_observation_view_at(view, index);

    memset(entry, 0, sizeof(*entry));
    entry->process_return_observation_view_index = index;
    entry->process_return_observation_view_token =
        fallback_process_return_observation_view_token(index);
    entry->scheduler_return_observation_view_token = scheduler_view ?
        scheduler_view->scheduler_return_observation_view_token :
        fallback_scheduler_return_observation_view_token(index);
    entry->post_resume_observation_view_token = scheduler_view ?
        scheduler_view->post_resume_observation_view_token :
        fallback_post_resume_observation_view_token(index);
    entry->user_mode_resume_view_token = scheduler_view ?
        scheduler_view->user_mode_resume_view_token :
        fallback_user_mode_resume_view_token(index);
    entry->syscall_exit_view_token = scheduler_view ?
        scheduler_view->syscall_exit_view_token :
        fallback_syscall_exit_view_token(index);
    entry->syscall_return_view_token = scheduler_view ?
        scheduler_view->syscall_return_view_token :
        fallback_syscall_return_view_token(index);
    entry->pid_token = scheduler_view ? scheduler_view->pid_token :
        4000ul + (unsigned long)index;
    entry->process_return_observation_view_rank =
        (unsigned long)index + 1ul;
    entry->scheduler_return_observation_view_rank = scheduler_view ?
        scheduler_view->scheduler_return_observation_view_rank :
        (unsigned long)index + 1ul;
    entry->syscall_number = scheduler_view ?
        scheduler_view->syscall_number : 512ul + (unsigned long)index;
    entry->resume_slot = scheduler_view ? scheduler_view->resume_slot :
        4096ul + (unsigned long)index;
    entry->observation_slot = scheduler_view ?
        scheduler_view->observation_slot : 5120ul + (unsigned long)index;
    entry->scheduler_return_slot = scheduler_view ?
        scheduler_view->scheduler_return_slot : 6144ul + (unsigned long)index;
    entry->process_return_slot = 7168ul + (unsigned long)index;
    entry->process_return_epoch_slot = 19ul;
    entry->process_return_reason_slot = 20ul;
    entry->process_state_slot = 21ul;
    entry->instruction_pointer_slot = scheduler_view ?
        scheduler_view->instruction_pointer_slot : 13ul;
    entry->stack_pointer_slot = scheduler_view ?
        scheduler_view->stack_pointer_slot : 14ul;
    entry->cpu_mode_slot = scheduler_view ? scheduler_view->cpu_mode_slot :
        15ul;
    entry->argument_count = scheduler_view ? scheduler_view->argument_count :
        6ul;
    entry->scheduler_return_observation_view_declared = 1;
    entry->process_return_observation_view_declared = 1;
    entry->scheduler_return_observation_declared = 1;
    entry->process_return_observation_declared = 1;
    entry->process_return_declared = 1;
    entry->process_state_observation_declared = 1;
    entry->process_return_reason_declared = 1;
    process_return_observation_view_copy(entry->process_label,
        sizeof(entry->process_label),
        scheduler_view ? scheduler_view->process_label :
            fallback_process(index));
    process_return_observation_view_copy(
        entry->process_return_observation_view_class,
        sizeof(entry->process_return_observation_view_class),
        class_for(index));
    process_return_observation_view_copy(
        entry->process_return_observation_view_status,
        sizeof(entry->process_return_observation_view_status),
        "declared-metadata");
    process_return_observation_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-process-return-observation-view-authority-denied");
    entry->declared = 1;
    entry->no_effect = 1;
    entry->evidence_level = 40u;
}

static void deny_process_return_observation_view_authority(
    latticra_kernel_runtime_entry_process_return_observation_view_entry_t
        *entry) {
    entry->process_return_observation_view_planned = 0;
    entry->process_return_observation_planned = 0;
    entry->process_return_planned = 0;
    entry->process_state_read_planned = 0;
    entry->scheduler_execution_planned = 0;
    entry->context_switch_planned = 0;
    entry->run_queue_mutation_planned = 0;
    entry->runtime_entry_process_return_observation_view_allowed = 0;
    entry->runtime_entry_scheduler_return_observation_view_allowed = 0;
    entry->runtime_entry_post_resume_observation_view_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->scheduler_return_observation_allowed = 0;
    entry->process_return_observation_allowed = 0;
    entry->process_return_allowed = 0;
    entry->process_state_read_allowed = 0;
    entry->scheduler_execution_allowed = 0;
    entry->scheduler_dispatch_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
}

static void fill_process_return_observation_views(
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *result,
    size_t requested_process_return_observation_view_count) {
    size_t count = requested_process_return_observation_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count >
        LATTICRA_KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_MAX) {
        count =
            LATTICRA_KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_MAX;
    }

    result->process_return_observation_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_process_return_observation_view(
            &result->process_return_observation_views[i],
            &result->runtime_entry_scheduler_return_observation_view, i);
        deny_process_return_observation_view_authority(
            &result->process_return_observation_views[i]);
    }
}

latticra_status_t
latticra_kernel_runtime_entry_process_return_observation_view_evaluate(
    const latticra_kernel_runtime_entry_process_return_observation_view_request_t
        *request,
    latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        process_return_observation_view_copy(
            result->process_return_observation_view_status,
            sizeof(result->process_return_observation_view_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status =
        latticra_kernel_runtime_entry_scheduler_return_observation_view_evaluate(
            &request->runtime_entry_scheduler_return_observation_view_request,
            &result->runtime_entry_scheduler_return_observation_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        process_return_observation_view_copy(
            result->process_return_observation_view_status,
            sizeof(result->process_return_observation_view_status),
            "runtime-entry-scheduler-return-observation-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_process_return_observation_views(result,
        request->requested_process_return_observation_view_count);
    result->no_effect =
        result->runtime_entry_scheduler_return_observation_view.no_effect;
    process_return_observation_view_copy(
        result->process_return_observation_view_status,
        sizeof(result->process_return_observation_view_status),
        result->no_effect ?
            "runtime-entry-process-return-observation-view-seed-ready" :
            "runtime-entry-process-return-observation-view-seed-blocked");
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

latticra_status_t
latticra_kernel_runtime_entry_process_return_observation_view_report(
    const latticra_kernel_runtime_entry_process_return_observation_view_result_t
        *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY PROCESS RETURN OBSERVATION VIEW REPORT\n"
        "process_return_observation_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_scheduler_return_observation_view_status=%s\n"
        "runtime_entry_post_resume_observation_view_status=%s\n"
        "runtime_entry_user_mode_resume_view_status=%s\n"
        "runtime_entry_syscall_exit_view_status=%s\n"
        "runtime_entry_syscall_return_view_status=%s\n"
        "process_return_observation_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_process_return_observation_view_allowed=%d\n"
        "runtime_entry_scheduler_return_observation_view_allowed=%d\n"
        "runtime_entry_post_resume_observation_view_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "scheduler_return_observation_allowed=%d\n"
        "process_return_observation_allowed=%d\n"
        "process_return_allowed=%d\n"
        "process_state_read_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "scheduler_dispatch_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->process_return_observation_view_status,
        result->policy_status,
        result->runtime_entry_scheduler_return_observation_view.
            scheduler_return_observation_view_status,
        result->runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            post_resume_observation_view_status,
        result->runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.user_mode_resume_view_status,
        result->runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.syscall_exit_view_status,
        result->runtime_entry_scheduler_return_observation_view.
            runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.syscall_return_view_status,
        (unsigned long)result->process_return_observation_view_count,
        result->no_effect,
        result->runtime_entry_process_return_observation_view_allowed,
        result->runtime_entry_scheduler_return_observation_view_allowed,
        result->runtime_entry_post_resume_observation_view_allowed,
        result->runtime_entry_allowed,
        result->scheduler_return_observation_allowed,
        result->process_return_observation_allowed,
        result->process_return_allowed,
        result->process_state_read_allowed,
        result->scheduler_execution_allowed,
        result->scheduler_dispatch_allowed,
        result->context_switch_allowed,
        result->run_queue_mutation_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->process_return_observation_view_count; ++i) {
        const latticra_kernel_runtime_entry_process_return_observation_view_entry_t
            *entry = &result->process_return_observation_views[i];
        status = append_text(buffer, buffer_len, &used,
            "process_return_observation_view[%lu].process_label=%s\n"
            "process_return_observation_view[%lu].process_return_observation_view_token=%lu\n"
            "process_return_observation_view[%lu].scheduler_return_observation_view_token=%lu\n"
            "process_return_observation_view[%lu].post_resume_observation_view_token=%lu\n"
            "process_return_observation_view[%lu].user_mode_resume_view_token=%lu\n"
            "process_return_observation_view[%lu].syscall_exit_view_token=%lu\n"
            "process_return_observation_view[%lu].syscall_return_view_token=%lu\n"
            "process_return_observation_view[%lu].pid_token=%lu\n"
            "process_return_observation_view[%lu].process_return_observation_view_rank=%lu\n"
            "process_return_observation_view[%lu].scheduler_return_observation_view_rank=%lu\n"
            "process_return_observation_view[%lu].syscall_number=%lu\n"
            "process_return_observation_view[%lu].resume_slot=%lu\n"
            "process_return_observation_view[%lu].observation_slot=%lu\n"
            "process_return_observation_view[%lu].scheduler_return_slot=%lu\n"
            "process_return_observation_view[%lu].process_return_slot=%lu\n"
            "process_return_observation_view[%lu].process_return_epoch_slot=%lu\n"
            "process_return_observation_view[%lu].process_return_reason_slot=%lu\n"
            "process_return_observation_view[%lu].process_state_slot=%lu\n"
            "process_return_observation_view[%lu].process_return_observation_view_declared=%d\n"
            "process_return_observation_view[%lu].process_return_observation_declared=%d\n"
            "process_return_observation_view[%lu].process_return_declared=%d\n"
            "process_return_observation_view[%lu].process_state_observation_declared=%d\n"
            "process_return_observation_view[%lu].process_return_observation_view_class=%s\n"
            "process_return_observation_view[%lu].process_return_observation_view_status=%s\n"
            "process_return_observation_view[%lu].authority_status=%s\n"
            "process_return_observation_view[%lu].process_return_observation_view_planned=%d\n"
            "process_return_observation_view[%lu].process_return_observation_planned=%d\n"
            "process_return_observation_view[%lu].process_return_planned=%d\n"
            "process_return_observation_view[%lu].process_state_read_planned=%d\n"
            "process_return_observation_view[%lu].scheduler_execution_planned=%d\n"
            "process_return_observation_view[%lu].runtime_entry_process_return_observation_view_allowed=%d\n"
            "process_return_observation_view[%lu].runtime_entry_scheduler_return_observation_view_allowed=%d\n"
            "process_return_observation_view[%lu].process_return_observation_allowed=%d\n"
            "process_return_observation_view[%lu].process_return_allowed=%d\n"
            "process_return_observation_view[%lu].process_state_read_allowed=%d\n"
            "process_return_observation_view[%lu].context_switch_allowed=%d\n"
            "process_return_observation_view[%lu].run_queue_mutation_allowed=%d\n"
            "process_return_observation_view[%lu].process_wake_allowed=%d\n"
            "process_return_observation_view[%lu].hardware_effect_allowed=%d\n"
            "process_return_observation_view[%lu].host_effect_allowed=%d\n"
            "process_return_observation_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i, entry->process_return_observation_view_token,
            (unsigned long)i,
                entry->scheduler_return_observation_view_token,
            (unsigned long)i, entry->post_resume_observation_view_token,
            (unsigned long)i, entry->user_mode_resume_view_token,
            (unsigned long)i, entry->syscall_exit_view_token,
            (unsigned long)i, entry->syscall_return_view_token,
            (unsigned long)i, entry->pid_token,
            (unsigned long)i, entry->process_return_observation_view_rank,
            (unsigned long)i,
                entry->scheduler_return_observation_view_rank,
            (unsigned long)i, entry->syscall_number,
            (unsigned long)i, entry->resume_slot,
            (unsigned long)i, entry->observation_slot,
            (unsigned long)i, entry->scheduler_return_slot,
            (unsigned long)i, entry->process_return_slot,
            (unsigned long)i, entry->process_return_epoch_slot,
            (unsigned long)i, entry->process_return_reason_slot,
            (unsigned long)i, entry->process_state_slot,
            (unsigned long)i,
                entry->process_return_observation_view_declared,
            (unsigned long)i, entry->process_return_observation_declared,
            (unsigned long)i, entry->process_return_declared,
            (unsigned long)i, entry->process_state_observation_declared,
            (unsigned long)i, entry->process_return_observation_view_class,
            (unsigned long)i, entry->process_return_observation_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i,
                entry->process_return_observation_view_planned,
            (unsigned long)i, entry->process_return_observation_planned,
            (unsigned long)i, entry->process_return_planned,
            (unsigned long)i, entry->process_state_read_planned,
            (unsigned long)i, entry->scheduler_execution_planned,
            (unsigned long)i,
                entry->runtime_entry_process_return_observation_view_allowed,
            (unsigned long)i,
                entry->runtime_entry_scheduler_return_observation_view_allowed,
            (unsigned long)i, entry->process_return_observation_allowed,
            (unsigned long)i, entry->process_return_allowed,
            (unsigned long)i, entry->process_state_read_allowed,
            (unsigned long)i, entry->context_switch_allowed,
            (unsigned long)i, entry->run_queue_mutation_allowed,
            (unsigned long)i, entry->process_wake_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
