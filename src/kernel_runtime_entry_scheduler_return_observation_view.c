#include "latticra/kernel_runtime_entry_scheduler_return_observation_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void scheduler_return_observation_view_copy(
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
    latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    scheduler_return_observation_view_copy(
        result->scheduler_return_observation_view_status,
        sizeof(result->scheduler_return_observation_view_status), "pending");
    scheduler_return_observation_view_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->runtime_entry_scheduler_return_observation_view_allowed = 0;
    result->runtime_entry_post_resume_observation_view_allowed = 0;
    result->runtime_entry_user_mode_resume_view_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->post_resume_observation_allowed = 0;
    result->scheduler_return_observation_allowed = 0;
    result->scheduler_return_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->scheduler_dispatch_allowed = 0;
    result->scheduler_handoff_allowed = 0;
    result->scheduler_activation_allowed = 0;
    result->scheduler_run_entry_allowed = 0;
    result->dispatch_allowed = 0;
    result->context_switch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->instruction_pointer_read_allowed = 0;
    result->stack_pointer_read_allowed = 0;
    result->cpu_mode_read_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 39u;
}

latticra_status_t
latticra_kernel_runtime_entry_scheduler_return_observation_view_default_request(
    latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t
        *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
            &request->runtime_entry_post_resume_observation_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_scheduler_return_observation_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_post_resume_observation_view_entry_t *
post_resume_observation_view_at(
    const latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *view,
    size_t index) {
    if (index < view->post_resume_observation_view_count &&
        view->post_resume_observation_views[index].declared) {
        return &view->post_resume_observation_views[index];
    }
    return 0;
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

static unsigned long fallback_syscall_dispatch_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 22000ul + (unsigned long)index;
}

static unsigned long fallback_syscall_gate_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 21000ul + (unsigned long)index;
}

static unsigned long fallback_privilege_level_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 20000ul + (unsigned long)index;
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
                "kernel-report-runtime-entry-scheduler-return-observation-view";
        case 1u:
            return "entropy-runtime-entry-scheduler-return-observation-view";
        case 2u:
            return "console-runtime-entry-scheduler-return-observation-view";
        case 3u:
            return "idle-runtime-entry-scheduler-return-observation-view";
        default:
            return "reserved-runtime-entry-scheduler-return-observation-view";
    }
}

static void fill_scheduler_return_observation_view(
    latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t
        *entry,
    const latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *view,
    size_t index) {
    const latticra_kernel_runtime_entry_post_resume_observation_view_entry_t
        *post_resume_view = post_resume_observation_view_at(view, index);

    memset(entry, 0, sizeof(*entry));
    entry->scheduler_return_observation_view_index = index;
    entry->scheduler_return_observation_view_token =
        fallback_scheduler_return_observation_view_token(index);
    entry->post_resume_observation_view_token = post_resume_view ?
        post_resume_view->post_resume_observation_view_token :
        fallback_post_resume_observation_view_token(index);
    entry->user_mode_resume_view_token = post_resume_view ?
        post_resume_view->user_mode_resume_view_token :
        fallback_user_mode_resume_view_token(index);
    entry->syscall_exit_view_token = post_resume_view ?
        post_resume_view->syscall_exit_view_token :
        fallback_syscall_exit_view_token(index);
    entry->syscall_return_view_token = post_resume_view ?
        post_resume_view->syscall_return_view_token :
        fallback_syscall_return_view_token(index);
    entry->syscall_dispatch_view_token = post_resume_view ?
        post_resume_view->syscall_dispatch_view_token :
        fallback_syscall_dispatch_view_token(index);
    entry->syscall_gate_view_token = post_resume_view ?
        post_resume_view->syscall_gate_view_token :
        fallback_syscall_gate_view_token(index);
    entry->privilege_level_view_token = post_resume_view ?
        post_resume_view->privilege_level_view_token :
        fallback_privilege_level_view_token(index);
    entry->pid_token = post_resume_view ? post_resume_view->pid_token :
        4000ul + (unsigned long)index;
    entry->scheduler_return_observation_view_rank =
        (unsigned long)index + 1ul;
    entry->post_resume_observation_view_rank = post_resume_view ?
        post_resume_view->post_resume_observation_view_rank :
        (unsigned long)index + 1ul;
    entry->syscall_number = post_resume_view ?
        post_resume_view->syscall_number : 512ul + (unsigned long)index;
    entry->resume_slot = post_resume_view ? post_resume_view->resume_slot :
        4096ul + (unsigned long)index;
    entry->observation_slot = post_resume_view ?
        post_resume_view->observation_slot : 5120ul + (unsigned long)index;
    entry->scheduler_return_slot = 6144ul + (unsigned long)index;
    entry->instruction_pointer_slot = post_resume_view ?
        post_resume_view->instruction_pointer_slot : 13ul;
    entry->stack_pointer_slot = post_resume_view ?
        post_resume_view->stack_pointer_slot : 14ul;
    entry->cpu_mode_slot = post_resume_view ?
        post_resume_view->cpu_mode_slot : 15ul;
    entry->observation_epoch_slot = post_resume_view ?
        post_resume_view->observation_epoch_slot : 16ul;
    entry->scheduler_return_epoch_slot = 17ul;
    entry->scheduler_return_reason_slot = 18ul;
    entry->argument_count = post_resume_view ?
        post_resume_view->argument_count : 6ul;
    entry->post_resume_observation_view_declared = 1;
    entry->scheduler_return_observation_view_declared = 1;
    entry->post_resume_observation_declared = 1;
    entry->scheduler_return_observation_declared = 1;
    entry->scheduler_return_declared = 1;
    entry->instruction_pointer_observation_declared = 1;
    entry->stack_pointer_observation_declared = 1;
    entry->cpu_mode_observation_declared = 1;
    entry->scheduler_return_reason_declared = 1;
    scheduler_return_observation_view_copy(entry->process_label,
        sizeof(entry->process_label),
        post_resume_view ? post_resume_view->process_label :
            fallback_process(index));
    scheduler_return_observation_view_copy(
        entry->scheduler_return_observation_view_class,
        sizeof(entry->scheduler_return_observation_view_class),
        class_for(index));
    scheduler_return_observation_view_copy(
        entry->scheduler_return_observation_view_status,
        sizeof(entry->scheduler_return_observation_view_status),
        "declared-metadata");
    scheduler_return_observation_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-scheduler-return-observation-view-authority-denied");
    entry->declared = 1;
    entry->no_effect = 1;
    entry->evidence_level = 39u;
}

static void deny_scheduler_return_observation_view_authority(
    latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t
        *entry) {
    entry->scheduler_return_observation_view_planned = 0;
    entry->scheduler_return_observation_planned = 0;
    entry->scheduler_return_planned = 0;
    entry->scheduler_execution_planned = 0;
    entry->context_switch_planned = 0;
    entry->dispatch_planned = 0;
    entry->run_queue_mutation_planned = 0;
    entry->instruction_pointer_read_planned = 0;
    entry->stack_pointer_read_planned = 0;
    entry->cpu_mode_read_planned = 0;
    entry->runtime_entry_scheduler_return_observation_view_allowed = 0;
    entry->runtime_entry_post_resume_observation_view_allowed = 0;
    entry->runtime_entry_user_mode_resume_view_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->post_resume_observation_allowed = 0;
    entry->scheduler_return_observation_allowed = 0;
    entry->scheduler_return_allowed = 0;
    entry->scheduler_execution_allowed = 0;
    entry->scheduler_dispatch_allowed = 0;
    entry->scheduler_handoff_allowed = 0;
    entry->scheduler_activation_allowed = 0;
    entry->scheduler_run_entry_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->instruction_pointer_read_allowed = 0;
    entry->stack_pointer_read_allowed = 0;
    entry->cpu_mode_read_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
}

static void fill_scheduler_return_observation_views(
    latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *result,
    size_t requested_scheduler_return_observation_view_count) {
    size_t count = requested_scheduler_return_observation_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count >
        LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_MAX) {
        count =
            LATTICRA_KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_MAX;
    }

    result->scheduler_return_observation_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_scheduler_return_observation_view(
            &result->scheduler_return_observation_views[i],
            &result->runtime_entry_post_resume_observation_view, i);
        deny_scheduler_return_observation_view_authority(
            &result->scheduler_return_observation_views[i]);
    }
}

latticra_status_t
latticra_kernel_runtime_entry_scheduler_return_observation_view_evaluate(
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_request_t
        *request,
    latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
        *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        scheduler_return_observation_view_copy(
            result->scheduler_return_observation_view_status,
            sizeof(result->scheduler_return_observation_view_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
        &request->runtime_entry_post_resume_observation_view_request,
        &result->runtime_entry_post_resume_observation_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        scheduler_return_observation_view_copy(
            result->scheduler_return_observation_view_status,
            sizeof(result->scheduler_return_observation_view_status),
            "runtime-entry-post-resume-observation-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_scheduler_return_observation_views(result,
        request->requested_scheduler_return_observation_view_count);
    result->no_effect =
        result->runtime_entry_post_resume_observation_view.no_effect;
    scheduler_return_observation_view_copy(
        result->scheduler_return_observation_view_status,
        sizeof(result->scheduler_return_observation_view_status),
        result->no_effect ?
            "runtime-entry-scheduler-return-observation-view-seed-ready" :
            "runtime-entry-scheduler-return-observation-view-seed-blocked");
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
latticra_kernel_runtime_entry_scheduler_return_observation_view_report(
    const latticra_kernel_runtime_entry_scheduler_return_observation_view_result_t
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
        "LATTICRA KERNEL RUNTIME ENTRY SCHEDULER RETURN OBSERVATION VIEW REPORT\n"
        "scheduler_return_observation_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_post_resume_observation_view_status=%s\n"
        "runtime_entry_user_mode_resume_view_status=%s\n"
        "runtime_entry_syscall_exit_view_status=%s\n"
        "runtime_entry_syscall_return_view_status=%s\n"
        "runtime_entry_syscall_dispatch_view_status=%s\n"
        "runtime_entry_syscall_gate_view_status=%s\n"
        "runtime_entry_privilege_level_view_status=%s\n"
        "scheduler_return_observation_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_scheduler_return_observation_view_allowed=%d\n"
        "runtime_entry_post_resume_observation_view_allowed=%d\n"
        "runtime_entry_user_mode_resume_view_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "post_resume_observation_allowed=%d\n"
        "scheduler_return_observation_allowed=%d\n"
        "scheduler_return_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "scheduler_dispatch_allowed=%d\n"
        "scheduler_handoff_allowed=%d\n"
        "scheduler_activation_allowed=%d\n"
        "scheduler_run_entry_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "instruction_pointer_read_allowed=%d\n"
        "stack_pointer_read_allowed=%d\n"
        "cpu_mode_read_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->scheduler_return_observation_view_status,
        result->policy_status,
        result->runtime_entry_post_resume_observation_view.
            post_resume_observation_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.user_mode_resume_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.syscall_exit_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.syscall_return_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.syscall_dispatch_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.syscall_gate_view_status,
        result->runtime_entry_post_resume_observation_view.
            runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.privilege_level_view_status,
        (unsigned long)result->scheduler_return_observation_view_count,
        result->no_effect,
        result->runtime_entry_scheduler_return_observation_view_allowed,
        result->runtime_entry_post_resume_observation_view_allowed,
        result->runtime_entry_user_mode_resume_view_allowed,
        result->runtime_entry_allowed,
        result->post_resume_observation_allowed,
        result->scheduler_return_observation_allowed,
        result->scheduler_return_allowed,
        result->scheduler_execution_allowed,
        result->scheduler_dispatch_allowed,
        result->scheduler_handoff_allowed,
        result->scheduler_activation_allowed,
        result->scheduler_run_entry_allowed,
        result->dispatch_allowed,
        result->context_switch_allowed,
        result->run_queue_mutation_allowed,
        result->instruction_pointer_read_allowed,
        result->stack_pointer_read_allowed,
        result->cpu_mode_read_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->scheduler_return_observation_view_count; ++i) {
        const latticra_kernel_runtime_entry_scheduler_return_observation_view_entry_t
            *entry = &result->scheduler_return_observation_views[i];
        status = append_text(buffer, buffer_len, &used,
            "scheduler_return_observation_view[%lu].process_label=%s\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].post_resume_observation_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].user_mode_resume_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].syscall_exit_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].syscall_return_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].syscall_dispatch_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].syscall_gate_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].privilege_level_view_token=%lu\n"
            "scheduler_return_observation_view[%lu].pid_token=%lu\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_rank=%lu\n"
            "scheduler_return_observation_view[%lu].post_resume_observation_view_rank=%lu\n"
            "scheduler_return_observation_view[%lu].syscall_number=%lu\n"
            "scheduler_return_observation_view[%lu].resume_slot=%lu\n"
            "scheduler_return_observation_view[%lu].observation_slot=%lu\n"
            "scheduler_return_observation_view[%lu].scheduler_return_slot=%lu\n"
            "scheduler_return_observation_view[%lu].instruction_pointer_slot=%lu\n"
            "scheduler_return_observation_view[%lu].stack_pointer_slot=%lu\n"
            "scheduler_return_observation_view[%lu].cpu_mode_slot=%lu\n"
            "scheduler_return_observation_view[%lu].observation_epoch_slot=%lu\n"
            "scheduler_return_observation_view[%lu].scheduler_return_epoch_slot=%lu\n"
            "scheduler_return_observation_view[%lu].scheduler_return_reason_slot=%lu\n"
            "scheduler_return_observation_view[%lu].argument_count=%lu\n"
            "scheduler_return_observation_view[%lu].post_resume_observation_view_declared=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_declared=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_declared=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_declared=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_reason_declared=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_class=%s\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_status=%s\n"
            "scheduler_return_observation_view[%lu].authority_status=%s\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_view_planned=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_planned=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_planned=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_execution_planned=%d\n"
            "scheduler_return_observation_view[%lu].context_switch_planned=%d\n"
            "scheduler_return_observation_view[%lu].runtime_entry_scheduler_return_observation_view_allowed=%d\n"
            "scheduler_return_observation_view[%lu].runtime_entry_post_resume_observation_view_allowed=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_observation_allowed=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_return_allowed=%d\n"
            "scheduler_return_observation_view[%lu].scheduler_execution_allowed=%d\n"
            "scheduler_return_observation_view[%lu].context_switch_allowed=%d\n"
            "scheduler_return_observation_view[%lu].run_queue_mutation_allowed=%d\n"
            "scheduler_return_observation_view[%lu].instruction_pointer_read_allowed=%d\n"
            "scheduler_return_observation_view[%lu].stack_pointer_read_allowed=%d\n"
            "scheduler_return_observation_view[%lu].cpu_mode_read_allowed=%d\n"
            "scheduler_return_observation_view[%lu].hardware_effect_allowed=%d\n"
            "scheduler_return_observation_view[%lu].host_effect_allowed=%d\n"
            "scheduler_return_observation_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i,
                entry->scheduler_return_observation_view_token,
            (unsigned long)i,
                entry->post_resume_observation_view_token,
            (unsigned long)i, entry->user_mode_resume_view_token,
            (unsigned long)i, entry->syscall_exit_view_token,
            (unsigned long)i, entry->syscall_return_view_token,
            (unsigned long)i, entry->syscall_dispatch_view_token,
            (unsigned long)i, entry->syscall_gate_view_token,
            (unsigned long)i, entry->privilege_level_view_token,
            (unsigned long)i, entry->pid_token,
            (unsigned long)i,
                entry->scheduler_return_observation_view_rank,
            (unsigned long)i, entry->post_resume_observation_view_rank,
            (unsigned long)i, entry->syscall_number,
            (unsigned long)i, entry->resume_slot,
            (unsigned long)i, entry->observation_slot,
            (unsigned long)i, entry->scheduler_return_slot,
            (unsigned long)i, entry->instruction_pointer_slot,
            (unsigned long)i, entry->stack_pointer_slot,
            (unsigned long)i, entry->cpu_mode_slot,
            (unsigned long)i, entry->observation_epoch_slot,
            (unsigned long)i, entry->scheduler_return_epoch_slot,
            (unsigned long)i, entry->scheduler_return_reason_slot,
            (unsigned long)i, entry->argument_count,
            (unsigned long)i, entry->post_resume_observation_view_declared,
            (unsigned long)i,
                entry->scheduler_return_observation_view_declared,
            (unsigned long)i, entry->scheduler_return_observation_declared,
            (unsigned long)i, entry->scheduler_return_declared,
            (unsigned long)i, entry->scheduler_return_reason_declared,
            (unsigned long)i, entry->scheduler_return_observation_view_class,
            (unsigned long)i, entry->scheduler_return_observation_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i,
                entry->scheduler_return_observation_view_planned,
            (unsigned long)i, entry->scheduler_return_observation_planned,
            (unsigned long)i, entry->scheduler_return_planned,
            (unsigned long)i, entry->scheduler_execution_planned,
            (unsigned long)i, entry->context_switch_planned,
            (unsigned long)i,
                entry->runtime_entry_scheduler_return_observation_view_allowed,
            (unsigned long)i,
                entry->runtime_entry_post_resume_observation_view_allowed,
            (unsigned long)i, entry->scheduler_return_observation_allowed,
            (unsigned long)i, entry->scheduler_return_allowed,
            (unsigned long)i, entry->scheduler_execution_allowed,
            (unsigned long)i, entry->context_switch_allowed,
            (unsigned long)i, entry->run_queue_mutation_allowed,
            (unsigned long)i, entry->instruction_pointer_read_allowed,
            (unsigned long)i, entry->stack_pointer_read_allowed,
            (unsigned long)i, entry->cpu_mode_read_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
