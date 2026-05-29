#include "latticra/kernel_runtime_entry_syscall_dispatch_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void syscall_dispatch_view_copy(
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
    latticra_kernel_runtime_entry_syscall_dispatch_view_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    syscall_dispatch_view_copy(result->syscall_dispatch_view_status,
        sizeof(result->syscall_dispatch_view_status), "pending");
    syscall_dispatch_view_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
    result->runtime_entry_syscall_dispatch_view_allowed = 0;
    result->runtime_entry_syscall_gate_view_allowed = 0;
    result->runtime_entry_privilege_level_view_allowed = 0;
    result->runtime_entry_address_space_view_allowed = 0;
    result->runtime_entry_stack_view_allowed = 0;
    result->runtime_entry_register_view_allowed = 0;
    result->runtime_entry_frame_allowed = 0;
    result->runtime_entry_admission_allowed = 0;
    result->runtime_entry_allowed = 0;
    result->scheduler_run_entry_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->context_switch_allowed = 0;
    result->register_save_allowed = 0;
    result->register_restore_allowed = 0;
    result->stack_switch_allowed = 0;
    result->address_space_switch_allowed = 0;
    result->page_table_write_allowed = 0;
    result->tlb_flush_allowed = 0;
    result->mmu_update_allowed = 0;
    result->privilege_transition_allowed = 0;
    result->syscall_gate_allowed = 0;
    result->syscall_dispatch_allowed = 0;
    result->syscall_argument_copy_allowed = 0;
    result->syscall_instruction_allowed = 0;
    result->syscall_handler_allowed = 0;
    result->syscall_return_allowed = 0;
    result->interrupt_return_allowed = 0;
    result->preemption_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 34u;
}

latticra_status_t
latticra_kernel_runtime_entry_syscall_dispatch_view_default_request(
    latticra_kernel_runtime_entry_syscall_dispatch_view_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_syscall_gate_view_default_request(
            &request->runtime_entry_syscall_gate_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_syscall_dispatch_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *
syscall_gate_view_at(
    const latticra_kernel_runtime_entry_syscall_gate_view_result_t *view,
    size_t index) {
    if (index < view->syscall_gate_view_count &&
        view->syscall_gate_views[index].declared) {
        return &view->syscall_gate_views[index];
    }
    return 0;
}

static unsigned long syscall_gate_view_value_or(
    const latticra_kernel_runtime_entry_syscall_gate_view_result_t *view,
    size_t index,
    unsigned long fallback,
    unsigned long (*reader)(
        const latticra_kernel_runtime_entry_syscall_gate_view_entry_t
            *entry)) {
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry =
        syscall_gate_view_at(view, index);
    return entry ? reader(entry) : fallback;
}

static unsigned long read_syscall_gate_view_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->syscall_gate_view_token;
}

static unsigned long read_privilege_level_view_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->privilege_level_view_token;
}

static unsigned long read_address_space_view_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->address_space_view_token;
}

static unsigned long read_stack_view_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->stack_view_token;
}

static unsigned long read_register_view_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->register_view_token;
}

static unsigned long read_frame_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->frame_token;
}

static unsigned long read_admission_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->admission_token;
}

static unsigned long read_run_entry_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->run_entry_token;
}

static unsigned long read_activation_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->activation_token;
}

static unsigned long read_pid_token(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->pid_token;
}

static unsigned long read_syscall_gate_view_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->syscall_gate_view_rank;
}

static unsigned long read_privilege_level_view_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->privilege_level_view_rank;
}

static unsigned long read_address_space_view_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->address_space_view_rank;
}

static unsigned long read_stack_view_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->stack_view_rank;
}

static unsigned long read_register_view_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->register_view_rank;
}

static unsigned long read_frame_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->frame_rank;
}

static unsigned long read_admission_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->admission_rank;
}

static unsigned long read_run_entry_rank(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->run_entry_rank;
}

static unsigned long read_remaining_budget(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->remaining_budget_ns;
}

static unsigned long read_privilege_level(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->privilege_level;
}

static unsigned long read_ring_number(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->ring_number;
}

static unsigned long read_syscall_number(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->syscall_number;
}

static unsigned long read_gate_vector(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->gate_vector;
}

static unsigned long read_handler_slot(
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry) {
    return entry->handler_slot;
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

static const char *process_for(
    const latticra_kernel_runtime_entry_syscall_gate_view_result_t *view,
    size_t index,
    const char *fallback) {
    const latticra_kernel_runtime_entry_syscall_gate_view_entry_t *entry =
        syscall_gate_view_at(view, index);
    return entry ? entry->process_label : fallback;
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-runtime-entry-syscall-dispatch-view";
        case 1u:
            return "entropy-runtime-entry-syscall-dispatch-view";
        case 2u:
            return "console-runtime-entry-syscall-dispatch-view";
        case 3u:
            return "idle-runtime-entry-syscall-dispatch-view";
        default:
            return "reserved-runtime-entry-syscall-dispatch-view";
    }
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

static unsigned long fallback_address_space_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 19000ul + (unsigned long)index;
}

static unsigned long fallback_stack_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 18000ul + (unsigned long)index;
}

static unsigned long fallback_register_view_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 17000ul + (unsigned long)index;
}

static unsigned long fallback_frame_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 16000ul + (unsigned long)index;
}

static unsigned long fallback_admission_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 15000ul + (unsigned long)index;
}

static unsigned long fallback_run_entry_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 14000ul + (unsigned long)index;
}

static unsigned long fallback_activation_token(size_t index) {
    if (index < 4u) return (unsigned long)index;
    return 13000ul + (unsigned long)index;
}

static void fill_syscall_dispatch_view(
    latticra_kernel_runtime_entry_syscall_dispatch_view_entry_t *entry,
    const latticra_kernel_runtime_entry_syscall_gate_view_result_t *view,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->syscall_dispatch_view_index = index;
    entry->syscall_dispatch_view_token =
        fallback_syscall_dispatch_view_token(index);
    entry->syscall_gate_view_token = syscall_gate_view_value_or(view, index,
        fallback_syscall_gate_view_token(index), read_syscall_gate_view_token);
    entry->privilege_level_view_token = syscall_gate_view_value_or(view,
        index, fallback_privilege_level_view_token(index),
        read_privilege_level_view_token);
    entry->address_space_view_token = syscall_gate_view_value_or(view,
        index, fallback_address_space_view_token(index),
        read_address_space_view_token);
    entry->stack_view_token = syscall_gate_view_value_or(view, index,
        fallback_stack_view_token(index), read_stack_view_token);
    entry->register_view_token = syscall_gate_view_value_or(view, index,
        fallback_register_view_token(index), read_register_view_token);
    entry->frame_token = syscall_gate_view_value_or(view, index,
        fallback_frame_token(index), read_frame_token);
    entry->admission_token = syscall_gate_view_value_or(view, index,
        fallback_admission_token(index), read_admission_token);
    entry->run_entry_token = syscall_gate_view_value_or(view, index,
        fallback_run_entry_token(index), read_run_entry_token);
    entry->activation_token = syscall_gate_view_value_or(view, index,
        fallback_activation_token(index), read_activation_token);
    entry->pid_token = syscall_gate_view_value_or(view, index,
        4000ul + (unsigned long)index, read_pid_token);
    entry->syscall_dispatch_view_rank = (unsigned long)index + 1ul;
    entry->syscall_gate_view_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_syscall_gate_view_rank);
    entry->privilege_level_view_rank = syscall_gate_view_value_or(view,
        index, (unsigned long)index + 1ul, read_privilege_level_view_rank);
    entry->address_space_view_rank = syscall_gate_view_value_or(view,
        index, (unsigned long)index + 1ul, read_address_space_view_rank);
    entry->stack_view_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_stack_view_rank);
    entry->register_view_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_register_view_rank);
    entry->frame_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_frame_rank);
    entry->admission_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_admission_rank);
    entry->run_entry_rank = syscall_gate_view_value_or(view, index,
        (unsigned long)index + 1ul, read_run_entry_rank);
    entry->remaining_budget_ns = syscall_gate_view_value_or(view, index,
        0ul, read_remaining_budget);
    entry->privilege_level = syscall_gate_view_value_or(view, index, 3ul,
        read_privilege_level);
    entry->ring_number = syscall_gate_view_value_or(view, index,
        entry->privilege_level, read_ring_number);
    entry->syscall_number = syscall_gate_view_value_or(view, index,
        512ul + (unsigned long)index, read_syscall_number);
    entry->gate_vector = syscall_gate_view_value_or(view, index, 128ul,
        read_gate_vector);
    entry->handler_slot = syscall_gate_view_value_or(view, index,
        (unsigned long)index, read_handler_slot);
    entry->dispatch_slot = 1024ul + (unsigned long)index;
    entry->argument_count = 6ul;
    entry->syscall_gate_view_declared = 1;
    entry->syscall_dispatch_view_declared = 1;
    entry->syscall_number_declared = 1;
    entry->syscall_dispatch_declared = 1;
    entry->syscall_argument_window_declared = 1;
    entry->syscall_handler_declared = 1;
    entry->syscall_return_declared = 1;
    entry->user_mode_declared = 1;
    entry->kernel_mode_declared = 1;
    entry->privilege_boundary_declared = 1;
    syscall_dispatch_view_copy(entry->process_label,
        sizeof(entry->process_label),
        process_for(view, index, fallback_process(index)));
    syscall_dispatch_view_copy(entry->syscall_dispatch_view_class,
        sizeof(entry->syscall_dispatch_view_class), class_for(index));
    syscall_dispatch_view_copy(entry->syscall_dispatch_view_status,
        sizeof(entry->syscall_dispatch_view_status), "declared-metadata");
    syscall_dispatch_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-syscall-dispatch-view-authority-denied");
    entry->declared = 1;
    entry->no_effect = 1;
    entry->evidence_level = 34u;
}

static void deny_syscall_dispatch_view_authority(
    latticra_kernel_runtime_entry_syscall_dispatch_view_entry_t *entry) {
    entry->syscall_dispatch_view_planned = 0;
    entry->syscall_dispatch_view_built = 0;
    entry->syscall_dispatch_view_installed = 0;
    entry->syscall_dispatch_planned = 0;
    entry->syscall_argument_copy_planned = 0;
    entry->syscall_instruction_planned = 0;
    entry->syscall_handler_planned = 0;
    entry->syscall_return_planned = 0;
    entry->privilege_transition_planned = 0;
    entry->interrupt_return_planned = 0;
    entry->admitted = 0;
    entry->runtime_entry_planned = 0;
    entry->runtime_entry_entered = 0;
    entry->execution_entered = 0;
    entry->context_switch_planned = 0;
    entry->runtime_entry_syscall_dispatch_view_allowed = 0;
    entry->runtime_entry_syscall_gate_view_allowed = 0;
    entry->runtime_entry_privilege_level_view_allowed = 0;
    entry->runtime_entry_address_space_view_allowed = 0;
    entry->runtime_entry_stack_view_allowed = 0;
    entry->runtime_entry_register_view_allowed = 0;
    entry->runtime_entry_frame_allowed = 0;
    entry->runtime_entry_admission_allowed = 0;
    entry->runtime_entry_allowed = 0;
    entry->scheduler_run_entry_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->register_save_allowed = 0;
    entry->register_restore_allowed = 0;
    entry->stack_switch_allowed = 0;
    entry->address_space_switch_allowed = 0;
    entry->page_table_write_allowed = 0;
    entry->tlb_flush_allowed = 0;
    entry->mmu_update_allowed = 0;
    entry->privilege_transition_allowed = 0;
    entry->syscall_gate_allowed = 0;
    entry->syscall_dispatch_allowed = 0;
    entry->syscall_argument_copy_allowed = 0;
    entry->syscall_instruction_allowed = 0;
    entry->syscall_handler_allowed = 0;
    entry->syscall_return_allowed = 0;
    entry->interrupt_return_allowed = 0;
    entry->preemption_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
}

static void fill_syscall_dispatch_views(
    latticra_kernel_runtime_entry_syscall_dispatch_view_result_t *result,
    size_t requested_syscall_dispatch_view_count) {
    size_t count = requested_syscall_dispatch_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_MAX) {
        count = LATTICRA_KERNEL_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_MAX;
    }

    result->syscall_dispatch_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_syscall_dispatch_view(&result->syscall_dispatch_views[i],
            &result->runtime_entry_syscall_gate_view, i);
        deny_syscall_dispatch_view_authority(
            &result->syscall_dispatch_views[i]);
    }
}

latticra_status_t
latticra_kernel_runtime_entry_syscall_dispatch_view_evaluate(
    const latticra_kernel_runtime_entry_syscall_dispatch_view_request_t
        *request,
    latticra_kernel_runtime_entry_syscall_dispatch_view_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        syscall_dispatch_view_copy(result->syscall_dispatch_view_status,
            sizeof(result->syscall_dispatch_view_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_syscall_gate_view_evaluate(
        &request->runtime_entry_syscall_gate_view_request,
        &result->runtime_entry_syscall_gate_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        syscall_dispatch_view_copy(result->syscall_dispatch_view_status,
            sizeof(result->syscall_dispatch_view_status),
            "runtime-entry-syscall-gate-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_syscall_dispatch_views(result,
        request->requested_syscall_dispatch_view_count);
    result->no_effect = result->runtime_entry_syscall_gate_view.no_effect;
    syscall_dispatch_view_copy(result->syscall_dispatch_view_status,
        sizeof(result->syscall_dispatch_view_status),
        result->no_effect ?
            "runtime-entry-syscall-dispatch-view-seed-ready" :
            "runtime-entry-syscall-dispatch-view-seed-blocked");
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

latticra_status_t latticra_kernel_runtime_entry_syscall_dispatch_view_report(
    const latticra_kernel_runtime_entry_syscall_dispatch_view_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY SYSCALL DISPATCH VIEW REPORT\n"
        "syscall_dispatch_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_syscall_gate_view_status=%s\n"
        "runtime_entry_privilege_level_view_status=%s\n"
        "runtime_entry_address_space_view_status=%s\n"
        "runtime_entry_stack_view_status=%s\n"
        "runtime_entry_register_view_status=%s\n"
        "runtime_entry_frame_status=%s\n"
        "runtime_entry_admission_status=%s\n"
        "scheduler_run_entry_status=%s\n"
        "syscall_dispatch_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_syscall_dispatch_view_allowed=%d\n"
        "runtime_entry_syscall_gate_view_allowed=%d\n"
        "runtime_entry_privilege_level_view_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "privilege_transition_allowed=%d\n"
        "syscall_gate_allowed=%d\n"
        "syscall_dispatch_allowed=%d\n"
        "syscall_argument_copy_allowed=%d\n"
        "syscall_instruction_allowed=%d\n"
        "syscall_handler_allowed=%d\n"
        "syscall_return_allowed=%d\n"
        "interrupt_return_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->syscall_dispatch_view_status,
        result->policy_status,
        result->runtime_entry_syscall_gate_view.syscall_gate_view_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.privilege_level_view_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            address_space_view_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            runtime_entry_stack_view.stack_view_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            runtime_entry_stack_view.runtime_entry_register_view.
            register_view_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.frame_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.runtime_entry_admission.admission_status,
        result->runtime_entry_syscall_gate_view.
            runtime_entry_privilege_level_view.runtime_entry_address_space_view.
            runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.runtime_entry_admission.scheduler_run_entry.
            run_entry_status,
        (unsigned long)result->syscall_dispatch_view_count,
        result->no_effect,
        result->runtime_entry_syscall_dispatch_view_allowed,
        result->runtime_entry_syscall_gate_view_allowed,
        result->runtime_entry_privilege_level_view_allowed,
        result->runtime_entry_allowed,
        result->context_switch_allowed,
        result->privilege_transition_allowed,
        result->syscall_gate_allowed,
        result->syscall_dispatch_allowed,
        result->syscall_argument_copy_allowed,
        result->syscall_instruction_allowed,
        result->syscall_handler_allowed,
        result->syscall_return_allowed,
        result->interrupt_return_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->syscall_dispatch_view_count; ++i) {
        const latticra_kernel_runtime_entry_syscall_dispatch_view_entry_t
            *entry = &result->syscall_dispatch_views[i];
        status = append_text(buffer, buffer_len, &used,
            "syscall_dispatch_view[%lu].process_label=%s\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_token=%lu\n"
            "syscall_dispatch_view[%lu].syscall_gate_view_token=%lu\n"
            "syscall_dispatch_view[%lu].privilege_level_view_token=%lu\n"
            "syscall_dispatch_view[%lu].pid_token=%lu\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_rank=%lu\n"
            "syscall_dispatch_view[%lu].syscall_number=%lu\n"
            "syscall_dispatch_view[%lu].gate_vector=%lu\n"
            "syscall_dispatch_view[%lu].handler_slot=%lu\n"
            "syscall_dispatch_view[%lu].dispatch_slot=%lu\n"
            "syscall_dispatch_view[%lu].argument_count=%lu\n"
            "syscall_dispatch_view[%lu].syscall_gate_view_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_argument_window_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_handler_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_return_declared=%d\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_class=%s\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_status=%s\n"
            "syscall_dispatch_view[%lu].authority_status=%s\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_view_planned=%d\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_planned=%d\n"
            "syscall_dispatch_view[%lu].syscall_argument_copy_planned=%d\n"
            "syscall_dispatch_view[%lu].syscall_instruction_planned=%d\n"
            "syscall_dispatch_view[%lu].syscall_handler_planned=%d\n"
            "syscall_dispatch_view[%lu].syscall_return_planned=%d\n"
            "syscall_dispatch_view[%lu].runtime_entry_syscall_dispatch_view_allowed=%d\n"
            "syscall_dispatch_view[%lu].runtime_entry_syscall_gate_view_allowed=%d\n"
            "syscall_dispatch_view[%lu].syscall_dispatch_allowed=%d\n"
            "syscall_dispatch_view[%lu].syscall_argument_copy_allowed=%d\n"
            "syscall_dispatch_view[%lu].syscall_instruction_allowed=%d\n"
            "syscall_dispatch_view[%lu].syscall_handler_allowed=%d\n"
            "syscall_dispatch_view[%lu].syscall_return_allowed=%d\n"
            "syscall_dispatch_view[%lu].runtime_entry_allowed=%d\n"
            "syscall_dispatch_view[%lu].hardware_effect_allowed=%d\n"
            "syscall_dispatch_view[%lu].host_effect_allowed=%d\n"
            "syscall_dispatch_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i, entry->syscall_dispatch_view_token,
            (unsigned long)i, entry->syscall_gate_view_token,
            (unsigned long)i, entry->privilege_level_view_token,
            (unsigned long)i, entry->pid_token,
            (unsigned long)i, entry->syscall_dispatch_view_rank,
            (unsigned long)i, entry->syscall_number,
            (unsigned long)i, entry->gate_vector,
            (unsigned long)i, entry->handler_slot,
            (unsigned long)i, entry->dispatch_slot,
            (unsigned long)i, entry->argument_count,
            (unsigned long)i, entry->syscall_gate_view_declared,
            (unsigned long)i, entry->syscall_dispatch_view_declared,
            (unsigned long)i, entry->syscall_dispatch_declared,
            (unsigned long)i, entry->syscall_argument_window_declared,
            (unsigned long)i, entry->syscall_handler_declared,
            (unsigned long)i, entry->syscall_return_declared,
            (unsigned long)i, entry->syscall_dispatch_view_class,
            (unsigned long)i, entry->syscall_dispatch_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i, entry->syscall_dispatch_view_planned,
            (unsigned long)i, entry->syscall_dispatch_planned,
            (unsigned long)i, entry->syscall_argument_copy_planned,
            (unsigned long)i, entry->syscall_instruction_planned,
            (unsigned long)i, entry->syscall_handler_planned,
            (unsigned long)i, entry->syscall_return_planned,
            (unsigned long)i,
                entry->runtime_entry_syscall_dispatch_view_allowed,
            (unsigned long)i,
                entry->runtime_entry_syscall_gate_view_allowed,
            (unsigned long)i, entry->syscall_dispatch_allowed,
            (unsigned long)i, entry->syscall_argument_copy_allowed,
            (unsigned long)i, entry->syscall_instruction_allowed,
            (unsigned long)i, entry->syscall_handler_allowed,
            (unsigned long)i, entry->syscall_return_allowed,
            (unsigned long)i, entry->runtime_entry_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
