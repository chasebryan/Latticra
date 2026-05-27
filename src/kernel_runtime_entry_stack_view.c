#include "latticra/kernel_runtime_entry_stack_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void stack_view_copy(char *dst, size_t dst_len, const char *src) {
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
    latticra_kernel_runtime_entry_stack_view_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    stack_view_copy(result->stack_view_status,
        sizeof(result->stack_view_status), "pending");
    stack_view_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
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
    result->preemption_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 30u;
}

latticra_status_t latticra_kernel_runtime_entry_stack_view_default_request(
    latticra_kernel_runtime_entry_stack_view_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_register_view_default_request(
            &request->runtime_entry_register_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_stack_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_register_view_entry_t *
register_view_at(
    const latticra_kernel_runtime_entry_register_view_result_t *register_view,
    size_t index) {
    if (index < register_view->register_view_count &&
        register_view->register_views[index].declared) {
        return &register_view->register_views[index];
    }
    return 0;
}

static unsigned long register_view_value_or(
    const latticra_kernel_runtime_entry_register_view_result_t *register_view,
    size_t index,
    unsigned long fallback,
    unsigned long (*reader)(
        const latticra_kernel_runtime_entry_register_view_entry_t *entry)) {
    const latticra_kernel_runtime_entry_register_view_entry_t *entry =
        register_view_at(register_view, index);
    return entry ? reader(entry) : fallback;
}

static unsigned long read_register_view_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->register_view_token;
}

static unsigned long read_frame_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->frame_token;
}

static unsigned long read_admission_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->admission_token;
}

static unsigned long read_run_entry_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->run_entry_token;
}

static unsigned long read_activation_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->activation_token;
}

static unsigned long read_pid_token(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->pid_token;
}

static unsigned long read_run_entry_rank(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->run_entry_rank;
}

static unsigned long read_admission_rank(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->admission_rank;
}

static unsigned long read_frame_rank(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->frame_rank;
}

static unsigned long read_register_view_rank(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->register_view_rank;
}

static unsigned long read_remaining_budget(
    const latticra_kernel_runtime_entry_register_view_entry_t *entry) {
    return entry->remaining_budget_ns;
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
    const latticra_kernel_runtime_entry_register_view_result_t *register_view,
    size_t index,
    const char *fallback) {
    const latticra_kernel_runtime_entry_register_view_entry_t *entry =
        register_view_at(register_view, index);
    return entry ? entry->process_label : fallback;
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-runtime-entry-stack-view";
        case 1u:
            return "entropy-runtime-entry-stack-view";
        case 2u:
            return "console-runtime-entry-stack-view";
        case 3u:
            return "idle-runtime-entry-stack-view";
        default:
            return "reserved-runtime-entry-stack-view";
    }
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

static void fill_stack_view(
    latticra_kernel_runtime_entry_stack_view_entry_t *entry,
    const latticra_kernel_runtime_entry_register_view_result_t *register_view,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->stack_view_index = index;
    entry->stack_view_token = fallback_stack_view_token(index);
    entry->register_view_token = register_view_value_or(register_view, index,
        fallback_register_view_token(index), read_register_view_token);
    entry->frame_token = register_view_value_or(register_view, index,
        fallback_frame_token(index), read_frame_token);
    entry->admission_token = register_view_value_or(register_view, index,
        fallback_admission_token(index), read_admission_token);
    entry->run_entry_token = register_view_value_or(register_view, index,
        fallback_run_entry_token(index), read_run_entry_token);
    entry->activation_token = register_view_value_or(register_view, index,
        fallback_activation_token(index), read_activation_token);
    entry->pid_token = register_view_value_or(register_view, index,
        2000ul + (unsigned long)index, read_pid_token);
    entry->run_entry_rank = register_view_value_or(register_view, index,
        (unsigned long)index + 1ul, read_run_entry_rank);
    entry->admission_rank = register_view_value_or(register_view, index,
        (unsigned long)index + 1ul, read_admission_rank);
    entry->frame_rank = register_view_value_or(register_view, index,
        (unsigned long)index + 1ul, read_frame_rank);
    entry->register_view_rank = register_view_value_or(register_view, index,
        (unsigned long)index + 1ul, read_register_view_rank);
    entry->stack_view_rank = (unsigned long)index + 1ul;
    entry->remaining_budget_ns = register_view_value_or(register_view, index,
        0ul, read_remaining_budget);
    entry->stack_slot_count = 4ul;
    entry->stack_window_bytes = 4096ul;
    entry->register_view_declared = 1;
    entry->stack_view_declared = 1;
    entry->stack_base_declared = 1;
    entry->stack_pointer_declared = 1;
    entry->stack_limit_declared = 1;
    entry->guard_page_declared = 1;
    stack_view_copy(entry->process_label, sizeof(entry->process_label),
        process_for(register_view, index, fallback_process(index)));
    stack_view_copy(entry->stack_view_class, sizeof(entry->stack_view_class),
        class_for(index));
    stack_view_copy(entry->stack_view_status, sizeof(entry->stack_view_status),
        "declared-metadata");
    stack_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-stack-view-authority-denied");
    entry->declared = 1;
    entry->stack_view_planned = 0;
    entry->stack_view_built = 0;
    entry->stack_view_installed = 0;
    entry->stack_capture_planned = 0;
    entry->stack_switch_planned = 0;
    entry->stack_map_planned = 0;
    entry->admitted = 0;
    entry->runtime_entry_planned = 0;
    entry->runtime_entry_entered = 0;
    entry->execution_entered = 0;
    entry->context_switch_planned = 0;
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
    entry->preemption_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 30u;
}

static void fill_stack_views(
    latticra_kernel_runtime_entry_stack_view_result_t *result,
    size_t requested_stack_view_count) {
    size_t count = requested_stack_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUNTIME_ENTRY_STACK_VIEW_MAX) {
        count = LATTICRA_KERNEL_RUNTIME_ENTRY_STACK_VIEW_MAX;
    }

    result->stack_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_stack_view(&result->stack_views[i],
            &result->runtime_entry_register_view, i);
    }
}

latticra_status_t latticra_kernel_runtime_entry_stack_view_evaluate(
    const latticra_kernel_runtime_entry_stack_view_request_t *request,
    latticra_kernel_runtime_entry_stack_view_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        stack_view_copy(result->stack_view_status,
            sizeof(result->stack_view_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_register_view_evaluate(
        &request->runtime_entry_register_view_request,
        &result->runtime_entry_register_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        stack_view_copy(result->stack_view_status,
            sizeof(result->stack_view_status),
            "runtime-entry-register-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_stack_views(result, request->requested_stack_view_count);
    result->no_effect = result->runtime_entry_register_view.no_effect;
    stack_view_copy(result->stack_view_status,
        sizeof(result->stack_view_status),
        result->no_effect ? "runtime-entry-stack-view-seed-ready" :
            "runtime-entry-stack-view-seed-blocked");
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

latticra_status_t latticra_kernel_runtime_entry_stack_view_report(
    const latticra_kernel_runtime_entry_stack_view_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY STACK VIEW REPORT\n"
        "stack_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_register_view_status=%s\n"
        "runtime_entry_frame_status=%s\n"
        "runtime_entry_admission_status=%s\n"
        "scheduler_run_entry_status=%s\n"
        "stack_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_stack_view_allowed=%d\n"
        "runtime_entry_register_view_allowed=%d\n"
        "runtime_entry_frame_allowed=%d\n"
        "runtime_entry_admission_allowed=%d\n"
        "runtime_entry_allowed=%d\n"
        "scheduler_run_entry_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "register_save_allowed=%d\n"
        "register_restore_allowed=%d\n"
        "stack_switch_allowed=%d\n"
        "address_space_switch_allowed=%d\n"
        "preemption_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->stack_view_status,
        result->policy_status,
        result->runtime_entry_register_view.register_view_status,
        result->runtime_entry_register_view.runtime_entry_frame.frame_status,
        result->runtime_entry_register_view.runtime_entry_frame.
            runtime_entry_admission.admission_status,
        result->runtime_entry_register_view.runtime_entry_frame.
            runtime_entry_admission.scheduler_run_entry.run_entry_status,
        (unsigned long)result->stack_view_count,
        result->no_effect,
        result->runtime_entry_stack_view_allowed,
        result->runtime_entry_register_view_allowed,
        result->runtime_entry_frame_allowed,
        result->runtime_entry_admission_allowed,
        result->runtime_entry_allowed,
        result->scheduler_run_entry_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->context_switch_allowed,
        result->register_save_allowed,
        result->register_restore_allowed,
        result->stack_switch_allowed,
        result->address_space_switch_allowed,
        result->preemption_allowed,
        result->scheduler_credit_update_allowed,
        result->quota_update_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->stack_view_count; ++i) {
        const latticra_kernel_runtime_entry_stack_view_entry_t *entry =
            &result->stack_views[i];
        status = append_text(buffer, buffer_len, &used,
            "stack_view[%lu].process_label=%s\n"
            "stack_view[%lu].stack_view_token=%lu\n"
            "stack_view[%lu].register_view_token=%lu\n"
            "stack_view[%lu].frame_token=%lu\n"
            "stack_view[%lu].admission_token=%lu\n"
            "stack_view[%lu].run_entry_token=%lu\n"
            "stack_view[%lu].activation_token=%lu\n"
            "stack_view[%lu].pid_token=%lu\n"
            "stack_view[%lu].run_entry_rank=%lu\n"
            "stack_view[%lu].admission_rank=%lu\n"
            "stack_view[%lu].frame_rank=%lu\n"
            "stack_view[%lu].register_view_rank=%lu\n"
            "stack_view[%lu].stack_view_rank=%lu\n"
            "stack_view[%lu].remaining_budget_ns=%lu\n"
            "stack_view[%lu].stack_slot_count=%lu\n"
            "stack_view[%lu].stack_window_bytes=%lu\n"
            "stack_view[%lu].register_view_declared=%d\n"
            "stack_view[%lu].stack_view_declared=%d\n"
            "stack_view[%lu].stack_base_declared=%d\n"
            "stack_view[%lu].stack_pointer_declared=%d\n"
            "stack_view[%lu].stack_limit_declared=%d\n"
            "stack_view[%lu].guard_page_declared=%d\n"
            "stack_view[%lu].stack_view_class=%s\n"
            "stack_view[%lu].stack_view_status=%s\n"
            "stack_view[%lu].authority_status=%s\n"
            "stack_view[%lu].stack_view_planned=%d\n"
            "stack_view[%lu].stack_view_built=%d\n"
            "stack_view[%lu].stack_view_installed=%d\n"
            "stack_view[%lu].stack_capture_planned=%d\n"
            "stack_view[%lu].stack_switch_planned=%d\n"
            "stack_view[%lu].stack_map_planned=%d\n"
            "stack_view[%lu].runtime_entry_entered=%d\n"
            "stack_view[%lu].execution_entered=%d\n"
            "stack_view[%lu].context_switch_planned=%d\n"
            "stack_view[%lu].runtime_entry_stack_view_allowed=%d\n"
            "stack_view[%lu].runtime_entry_register_view_allowed=%d\n"
            "stack_view[%lu].runtime_entry_frame_allowed=%d\n"
            "stack_view[%lu].runtime_entry_admission_allowed=%d\n"
            "stack_view[%lu].runtime_entry_allowed=%d\n"
            "stack_view[%lu].scheduler_run_entry_allowed=%d\n"
            "stack_view[%lu].dispatch_allowed=%d\n"
            "stack_view[%lu].run_queue_mutation_allowed=%d\n"
            "stack_view[%lu].context_switch_allowed=%d\n"
            "stack_view[%lu].register_save_allowed=%d\n"
            "stack_view[%lu].register_restore_allowed=%d\n"
            "stack_view[%lu].stack_switch_allowed=%d\n"
            "stack_view[%lu].address_space_switch_allowed=%d\n"
            "stack_view[%lu].hardware_effect_allowed=%d\n"
            "stack_view[%lu].host_effect_allowed=%d\n"
            "stack_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i, entry->stack_view_token,
            (unsigned long)i, entry->register_view_token,
            (unsigned long)i, entry->frame_token,
            (unsigned long)i, entry->admission_token,
            (unsigned long)i, entry->run_entry_token,
            (unsigned long)i, entry->activation_token,
            (unsigned long)i, entry->pid_token,
            (unsigned long)i, entry->run_entry_rank,
            (unsigned long)i, entry->admission_rank,
            (unsigned long)i, entry->frame_rank,
            (unsigned long)i, entry->register_view_rank,
            (unsigned long)i, entry->stack_view_rank,
            (unsigned long)i, entry->remaining_budget_ns,
            (unsigned long)i, entry->stack_slot_count,
            (unsigned long)i, entry->stack_window_bytes,
            (unsigned long)i, entry->register_view_declared,
            (unsigned long)i, entry->stack_view_declared,
            (unsigned long)i, entry->stack_base_declared,
            (unsigned long)i, entry->stack_pointer_declared,
            (unsigned long)i, entry->stack_limit_declared,
            (unsigned long)i, entry->guard_page_declared,
            (unsigned long)i, entry->stack_view_class,
            (unsigned long)i, entry->stack_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i, entry->stack_view_planned,
            (unsigned long)i, entry->stack_view_built,
            (unsigned long)i, entry->stack_view_installed,
            (unsigned long)i, entry->stack_capture_planned,
            (unsigned long)i, entry->stack_switch_planned,
            (unsigned long)i, entry->stack_map_planned,
            (unsigned long)i, entry->runtime_entry_entered,
            (unsigned long)i, entry->execution_entered,
            (unsigned long)i, entry->context_switch_planned,
            (unsigned long)i, entry->runtime_entry_stack_view_allowed,
            (unsigned long)i, entry->runtime_entry_register_view_allowed,
            (unsigned long)i, entry->runtime_entry_frame_allowed,
            (unsigned long)i, entry->runtime_entry_admission_allowed,
            (unsigned long)i, entry->runtime_entry_allowed,
            (unsigned long)i, entry->scheduler_run_entry_allowed,
            (unsigned long)i, entry->dispatch_allowed,
            (unsigned long)i, entry->run_queue_mutation_allowed,
            (unsigned long)i, entry->context_switch_allowed,
            (unsigned long)i, entry->register_save_allowed,
            (unsigned long)i, entry->register_restore_allowed,
            (unsigned long)i, entry->stack_switch_allowed,
            (unsigned long)i, entry->address_space_switch_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
