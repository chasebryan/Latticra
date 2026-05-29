#include "latticra/kernel_runtime_entry_post_resume_observation_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void post_resume_observation_view_copy(
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
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    post_resume_observation_view_copy(
        result->post_resume_observation_view_status,
        sizeof(result->post_resume_observation_view_status), "pending");
    post_resume_observation_view_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->runtime_entry_post_resume_observation_view_allowed = 0;
    result->runtime_entry_user_mode_resume_view_allowed = 0;
    result->runtime_entry_syscall_exit_view_allowed = 0;
    result->runtime_entry_syscall_return_view_allowed = 0;
    result->runtime_entry_syscall_dispatch_view_allowed = 0;
    result->runtime_entry_syscall_gate_view_allowed = 0;
    result->runtime_entry_privilege_level_view_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->context_switch_allowed = 0;
    result->privilege_transition_allowed = 0;
    result->syscall_gate_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->syscall_argument_copy_allowed = 0;
    result->syscall_instruction_allowed = 0;
    result->syscall_handler_allowed = 0;
    result->syscall_return_allowed = 0;
    result->syscall_result_copy_allowed = 0;
    result->syscall_exit_allowed = 0;
    result->syscall_exit_commit_allowed = 0;
    result->user_mode_resume_allowed = 0;
    result->user_instruction_resume_allowed = 0;
    result->resume_frame_commit_allowed = 0;
    result->post_resume_observation_allowed = 0;
    result->instruction_pointer_read_allowed = 0;
    result->stack_pointer_read_allowed = 0;
    result->cpu_mode_read_allowed = 0;
    result->interrupt_return_allowed = 0;
    result->scheduler_execution_allowed = 0;
    result->preemption_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 38u;
}

latticra_status_t
latticra_kernel_runtime_entry_post_resume_observation_view_default_request(
    latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_user_mode_resume_view_default_request(
            &request->runtime_entry_user_mode_resume_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_post_resume_observation_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_user_mode_resume_view_entry_t *
user_mode_resume_view_at(
    const latticra_kernel_runtime_entry_user_mode_resume_view_result_t *view,
    size_t index) {
    if (index < view->user_mode_resume_view_count &&
        view->user_mode_resume_views[index].declared) {
        return &view->user_mode_resume_views[index];
    }
    return 0;
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
            return "kernel-report-runtime-entry-post-resume-observation-view";
        case 1u:
            return "entropy-runtime-entry-post-resume-observation-view";
        case 2u:
            return "console-runtime-entry-post-resume-observation-view";
        case 3u:
            return "idle-runtime-entry-post-resume-observation-view";
        default:
            return "reserved-runtime-entry-post-resume-observation-view";
    }
}

static void fill_post_resume_observation_view(
    latticra_kernel_runtime_entry_post_resume_observation_view_entry_t *entry,
    const latticra_kernel_runtime_entry_user_mode_resume_view_result_t *view,
    size_t index) {
    const latticra_kernel_runtime_entry_user_mode_resume_view_entry_t
        *resume_view = user_mode_resume_view_at(view, index);

    memset(entry, 0, sizeof(*entry));
    entry->post_resume_observation_view_index = index;
    entry->post_resume_observation_view_token =
        fallback_post_resume_observation_view_token(index);
    entry->user_mode_resume_view_token = resume_view ?
        resume_view->user_mode_resume_view_token :
        fallback_user_mode_resume_view_token(index);
    entry->syscall_exit_view_token = resume_view ?
        resume_view->syscall_exit_view_token :
        fallback_syscall_exit_view_token(index);
    entry->syscall_return_view_token = resume_view ?
        resume_view->syscall_return_view_token :
        fallback_syscall_return_view_token(index);
    entry->syscall_dispatch_view_token = resume_view ?
        resume_view->syscall_dispatch_view_token :
        fallback_syscall_dispatch_view_token(index);
    entry->syscall_gate_view_token = resume_view ?
        resume_view->syscall_gate_view_token :
        fallback_syscall_gate_view_token(index);
    entry->privilege_level_view_token = resume_view ?
        resume_view->privilege_level_view_token :
        fallback_privilege_level_view_token(index);
    entry->pid_token = resume_view ? resume_view->pid_token :
        4000ul + (unsigned long)index;
    entry->post_resume_observation_view_rank = (unsigned long)index + 1ul;
    entry->user_mode_resume_view_rank = resume_view ?
        resume_view->user_mode_resume_view_rank : (unsigned long)index + 1ul;
    entry->syscall_number = resume_view ? resume_view->syscall_number :
        512ul + (unsigned long)index;
    entry->handler_slot = resume_view ? resume_view->handler_slot :
        (unsigned long)index;
    entry->dispatch_slot = resume_view ? resume_view->dispatch_slot :
        1024ul + (unsigned long)index;
    entry->return_slot = resume_view ? resume_view->return_slot :
        2048ul + (unsigned long)index;
    entry->exit_slot = resume_view ? resume_view->exit_slot :
        3072ul + (unsigned long)index;
    entry->resume_slot = resume_view ? resume_view->resume_slot :
        4096ul + (unsigned long)index;
    entry->observation_slot = 5120ul + (unsigned long)index;
    entry->instruction_pointer_slot = resume_view ?
        resume_view->instruction_pointer_slot : 13ul;
    entry->stack_pointer_slot = resume_view ?
        resume_view->stack_pointer_slot : 14ul;
    entry->cpu_mode_slot = 15ul;
    entry->observation_epoch_slot = 16ul;
    entry->argument_count = resume_view ? resume_view->argument_count : 6ul;
    entry->user_mode_resume_view_declared = 1;
    entry->post_resume_observation_view_declared = 1;
    entry->post_resume_observation_declared = 1;
    entry->user_mode_resume_declared = 1;
    entry->instruction_pointer_observation_declared = 1;
    entry->stack_pointer_observation_declared = 1;
    entry->cpu_mode_observation_declared = 1;
    post_resume_observation_view_copy(entry->process_label,
        sizeof(entry->process_label),
        resume_view ? resume_view->process_label : fallback_process(index));
    post_resume_observation_view_copy(
        entry->post_resume_observation_view_class,
        sizeof(entry->post_resume_observation_view_class), class_for(index));
    post_resume_observation_view_copy(
        entry->post_resume_observation_view_status,
        sizeof(entry->post_resume_observation_view_status),
        "declared-metadata");
    post_resume_observation_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-post-resume-observation-view-authority-denied");
    entry->declared = 1;
    entry->no_effect = 1;
    entry->evidence_level = 38u;
}

static void deny_post_resume_observation_view_authority(
    latticra_kernel_runtime_entry_post_resume_observation_view_entry_t
        *entry) {
    entry->post_resume_observation_view_planned = 0;
    entry->post_resume_observation_planned = 0;
    entry->user_mode_resume_planned = 0;
    entry->user_instruction_resume_planned = 0;
    entry->resume_frame_commit_planned = 0;
    entry->instruction_pointer_read_planned = 0;
    entry->stack_pointer_read_planned = 0;
    entry->cpu_mode_read_planned = 0;
    entry->runtime_entry_observed = 0;
    entry->execution_observed = 0;
    entry->scheduler_observation_planned = 0;
    entry->runtime_entry_post_resume_observation_view_allowed = 0;
    entry->runtime_entry_user_mode_resume_view_allowed = 0;
    entry->runtime_entry_syscall_exit_view_allowed = 0;
    entry->runtime_entry_syscall_return_view_allowed = 0;
    entry->runtime_entry_syscall_dispatch_view_allowed = 0;
    entry->runtime_entry_syscall_gate_view_allowed = 0;
    entry->runtime_entry_privilege_level_view_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->privilege_transition_allowed = 0;
    entry->syscall_gate_allowed = 0;
    entry->syscall_dispatch_allowed = 0;
    entry->syscall_argument_copy_allowed = 0;
    entry->syscall_instruction_allowed = 0;
    entry->syscall_handler_allowed = 0;
    entry->syscall_return_allowed = 0;
    entry->syscall_result_copy_allowed = 0;
    entry->syscall_exit_allowed = 0;
    entry->syscall_exit_commit_allowed = 0;
    entry->user_mode_resume_allowed = 0;
    entry->user_instruction_resume_allowed = 0;
    entry->resume_frame_commit_allowed = 0;
    entry->post_resume_observation_allowed = 0;
    entry->instruction_pointer_read_allowed = 0;
    entry->stack_pointer_read_allowed = 0;
    entry->cpu_mode_read_allowed = 0;
    entry->interrupt_return_allowed = 0;
    entry->scheduler_execution_allowed = 0;
    entry->preemption_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
}

static void fill_post_resume_observation_views(
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *result,
    size_t requested_post_resume_observation_view_count) {
    size_t count = requested_post_resume_observation_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count >
        LATTICRA_KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_MAX) {
        count =
            LATTICRA_KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_MAX;
    }

    result->post_resume_observation_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_post_resume_observation_view(
            &result->post_resume_observation_views[i],
            &result->runtime_entry_user_mode_resume_view, i);
        deny_post_resume_observation_view_authority(
            &result->post_resume_observation_views[i]);
    }
}

latticra_status_t
latticra_kernel_runtime_entry_post_resume_observation_view_evaluate(
    const latticra_kernel_runtime_entry_post_resume_observation_view_request_t
        *request,
    latticra_kernel_runtime_entry_post_resume_observation_view_result_t
        *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        post_resume_observation_view_copy(
            result->post_resume_observation_view_status,
            sizeof(result->post_resume_observation_view_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_user_mode_resume_view_evaluate(
        &request->runtime_entry_user_mode_resume_view_request,
        &result->runtime_entry_user_mode_resume_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        post_resume_observation_view_copy(
            result->post_resume_observation_view_status,
            sizeof(result->post_resume_observation_view_status),
            "runtime-entry-user-mode-resume-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_post_resume_observation_views(result,
        request->requested_post_resume_observation_view_count);
    result->no_effect = result->runtime_entry_user_mode_resume_view.no_effect;
    post_resume_observation_view_copy(
        result->post_resume_observation_view_status,
        sizeof(result->post_resume_observation_view_status),
        result->no_effect ?
            "runtime-entry-post-resume-observation-view-seed-ready" :
            "runtime-entry-post-resume-observation-view-seed-blocked");
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
latticra_kernel_runtime_entry_post_resume_observation_view_report(
    const latticra_kernel_runtime_entry_post_resume_observation_view_result_t
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
        "LATTICRA KERNEL RUNTIME ENTRY POST RESUME OBSERVATION VIEW REPORT\n"
        "post_resume_observation_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_user_mode_resume_view_status=%s\n"
        "runtime_entry_syscall_exit_view_status=%s\n"
        "runtime_entry_syscall_return_view_status=%s\n"
        "runtime_entry_syscall_dispatch_view_status=%s\n"
        "runtime_entry_syscall_gate_view_status=%s\n"
        "runtime_entry_privilege_level_view_status=%s\n"
        "post_resume_observation_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_post_resume_observation_view_allowed=%d\n"
        "runtime_entry_user_mode_resume_view_allowed=%d\n"
        "runtime_entry_syscall_exit_view_allowed=%d\n"
        "runtime_entry_syscall_return_view_allowed=%d\n"
        "runtime_entry_syscall_dispatch_view_allowed=%d\n"
        "runtime_entry_syscall_gate_view_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "privilege_transition_allowed=%d\n"
        "syscall_gate_allowed=%d\n"
        "syscall_dispatch_allowed=%d\n"
        "syscall_argument_copy_allowed=%d\n"
        "syscall_instruction_allowed=%d\n"
        "syscall_handler_allowed=%d\n"
        "syscall_return_allowed=%d\n"
        "syscall_result_copy_allowed=%d\n"
        "syscall_exit_allowed=%d\n"
        "syscall_exit_commit_allowed=%d\n"
        "user_mode_resume_allowed=%d\n"
        "user_instruction_resume_allowed=%d\n"
        "resume_frame_commit_allowed=%d\n"
        "post_resume_observation_allowed=%d\n"
        "instruction_pointer_read_allowed=%d\n"
        "stack_pointer_read_allowed=%d\n"
        "cpu_mode_read_allowed=%d\n"
        "interrupt_return_allowed=%d\n"
        "scheduler_execution_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->post_resume_observation_view_status,
        result->policy_status,
        result->runtime_entry_user_mode_resume_view.
            user_mode_resume_view_status,
        result->runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.syscall_exit_view_status,
        result->runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.syscall_return_view_status,
        result->runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.syscall_dispatch_view_status,
        result->runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.syscall_gate_view_status,
        result->runtime_entry_user_mode_resume_view.
            runtime_entry_syscall_exit_view.
            runtime_entry_syscall_return_view.
            runtime_entry_syscall_dispatch_view.
            runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.privilege_level_view_status,
        (unsigned long)result->post_resume_observation_view_count,
        result->no_effect,
        result->runtime_entry_post_resume_observation_view_allowed,
        result->runtime_entry_user_mode_resume_view_allowed,
        result->runtime_entry_syscall_exit_view_allowed,
        result->runtime_entry_syscall_return_view_allowed,
        result->runtime_entry_syscall_dispatch_view_allowed,
        result->runtime_entry_syscall_gate_view_allowed,
        result->runtime_entry_allowed,
        result->context_switch_allowed,
        result->privilege_transition_allowed,
        result->syscall_gate_allowed,
        result->syscall_dispatch_allowed,
        result->syscall_argument_copy_allowed,
        result->syscall_instruction_allowed,
        result->syscall_handler_allowed,
        result->syscall_return_allowed,
        result->syscall_result_copy_allowed,
        result->syscall_exit_allowed,
        result->syscall_exit_commit_allowed,
        result->user_mode_resume_allowed,
        result->user_instruction_resume_allowed,
        result->resume_frame_commit_allowed,
        result->post_resume_observation_allowed,
        result->instruction_pointer_read_allowed,
        result->stack_pointer_read_allowed,
        result->cpu_mode_read_allowed,
        result->interrupt_return_allowed,
        result->scheduler_execution_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->post_resume_observation_view_count; ++i) {
        const latticra_kernel_runtime_entry_post_resume_observation_view_entry_t
            *entry = &result->post_resume_observation_views[i];
        status = append_text(buffer, buffer_len, &used,
            "post_resume_observation_view[%lu].process_label=%s\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_token=%lu\n"
            "post_resume_observation_view[%lu].user_mode_resume_view_token=%lu\n"
            "post_resume_observation_view[%lu].syscall_exit_view_token=%lu\n"
            "post_resume_observation_view[%lu].syscall_return_view_token=%lu\n"
            "post_resume_observation_view[%lu].syscall_dispatch_view_token=%lu\n"
            "post_resume_observation_view[%lu].syscall_gate_view_token=%lu\n"
            "post_resume_observation_view[%lu].privilege_level_view_token=%lu\n"
            "post_resume_observation_view[%lu].pid_token=%lu\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_rank=%lu\n"
            "post_resume_observation_view[%lu].user_mode_resume_view_rank=%lu\n"
            "post_resume_observation_view[%lu].syscall_number=%lu\n"
            "post_resume_observation_view[%lu].handler_slot=%lu\n"
            "post_resume_observation_view[%lu].dispatch_slot=%lu\n"
            "post_resume_observation_view[%lu].return_slot=%lu\n"
            "post_resume_observation_view[%lu].exit_slot=%lu\n"
            "post_resume_observation_view[%lu].resume_slot=%lu\n"
            "post_resume_observation_view[%lu].observation_slot=%lu\n"
            "post_resume_observation_view[%lu].instruction_pointer_slot=%lu\n"
            "post_resume_observation_view[%lu].stack_pointer_slot=%lu\n"
            "post_resume_observation_view[%lu].cpu_mode_slot=%lu\n"
            "post_resume_observation_view[%lu].observation_epoch_slot=%lu\n"
            "post_resume_observation_view[%lu].argument_count=%lu\n"
            "post_resume_observation_view[%lu].user_mode_resume_view_declared=%d\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_declared=%d\n"
            "post_resume_observation_view[%lu].post_resume_observation_declared=%d\n"
            "post_resume_observation_view[%lu].instruction_pointer_observation_declared=%d\n"
            "post_resume_observation_view[%lu].stack_pointer_observation_declared=%d\n"
            "post_resume_observation_view[%lu].cpu_mode_observation_declared=%d\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_class=%s\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_status=%s\n"
            "post_resume_observation_view[%lu].authority_status=%s\n"
            "post_resume_observation_view[%lu].post_resume_observation_view_planned=%d\n"
            "post_resume_observation_view[%lu].post_resume_observation_planned=%d\n"
            "post_resume_observation_view[%lu].instruction_pointer_read_planned=%d\n"
            "post_resume_observation_view[%lu].stack_pointer_read_planned=%d\n"
            "post_resume_observation_view[%lu].runtime_entry_post_resume_observation_view_allowed=%d\n"
            "post_resume_observation_view[%lu].runtime_entry_user_mode_resume_view_allowed=%d\n"
            "post_resume_observation_view[%lu].user_mode_resume_allowed=%d\n"
            "post_resume_observation_view[%lu].post_resume_observation_allowed=%d\n"
            "post_resume_observation_view[%lu].instruction_pointer_read_allowed=%d\n"
            "post_resume_observation_view[%lu].stack_pointer_read_allowed=%d\n"
            "post_resume_observation_view[%lu].cpu_mode_read_allowed=%d\n"
            "post_resume_observation_view[%lu].runtime_entry_allowed=%d\n"
            "post_resume_observation_view[%lu].hardware_effect_allowed=%d\n"
            "post_resume_observation_view[%lu].host_effect_allowed=%d\n"
            "post_resume_observation_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i,
                entry->post_resume_observation_view_token,
            (unsigned long)i, entry->user_mode_resume_view_token,
            (unsigned long)i, entry->syscall_exit_view_token,
            (unsigned long)i, entry->syscall_return_view_token,
            (unsigned long)i, entry->syscall_dispatch_view_token,
            (unsigned long)i, entry->syscall_gate_view_token,
            (unsigned long)i, entry->privilege_level_view_token,
            (unsigned long)i, entry->pid_token,
            (unsigned long)i, entry->post_resume_observation_view_rank,
            (unsigned long)i, entry->user_mode_resume_view_rank,
            (unsigned long)i, entry->syscall_number,
            (unsigned long)i, entry->handler_slot,
            (unsigned long)i, entry->dispatch_slot,
            (unsigned long)i, entry->return_slot,
            (unsigned long)i, entry->exit_slot,
            (unsigned long)i, entry->resume_slot,
            (unsigned long)i, entry->observation_slot,
            (unsigned long)i, entry->instruction_pointer_slot,
            (unsigned long)i, entry->stack_pointer_slot,
            (unsigned long)i, entry->cpu_mode_slot,
            (unsigned long)i, entry->observation_epoch_slot,
            (unsigned long)i, entry->argument_count,
            (unsigned long)i, entry->user_mode_resume_view_declared,
            (unsigned long)i,
                entry->post_resume_observation_view_declared,
            (unsigned long)i, entry->post_resume_observation_declared,
            (unsigned long)i,
                entry->instruction_pointer_observation_declared,
            (unsigned long)i, entry->stack_pointer_observation_declared,
            (unsigned long)i, entry->cpu_mode_observation_declared,
            (unsigned long)i, entry->post_resume_observation_view_class,
            (unsigned long)i, entry->post_resume_observation_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i,
                entry->post_resume_observation_view_planned,
            (unsigned long)i, entry->post_resume_observation_planned,
            (unsigned long)i, entry->instruction_pointer_read_planned,
            (unsigned long)i, entry->stack_pointer_read_planned,
            (unsigned long)i,
                entry->runtime_entry_post_resume_observation_view_allowed,
            (unsigned long)i,
                entry->runtime_entry_user_mode_resume_view_allowed,
            (unsigned long)i, entry->user_mode_resume_allowed,
            (unsigned long)i, entry->post_resume_observation_allowed,
            (unsigned long)i, entry->instruction_pointer_read_allowed,
            (unsigned long)i, entry->stack_pointer_read_allowed,
            (unsigned long)i, entry->cpu_mode_read_allowed,
            (unsigned long)i, entry->runtime_entry_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
