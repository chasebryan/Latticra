#include "latticra/kernel_runtime_entry_address_space_view.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void address_space_view_copy(
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
    latticra_kernel_runtime_entry_address_space_view_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    address_space_view_copy(result->address_space_view_status,
        sizeof(result->address_space_view_status), "pending");
    address_space_view_copy(result->policy_status,
        sizeof(result->policy_status), "report-only");
    result->no_effect = 1;
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
    result->preemption_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 31u;
}

latticra_status_t
latticra_kernel_runtime_entry_address_space_view_default_request(
    latticra_kernel_runtime_entry_address_space_view_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_runtime_entry_stack_view_default_request(
            &request->runtime_entry_stack_view_request) !=
            LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_address_space_view_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_runtime_entry_stack_view_entry_t *stack_view_at(
    const latticra_kernel_runtime_entry_stack_view_result_t *stack_view,
    size_t index) {
    if (index < stack_view->stack_view_count &&
        stack_view->stack_views[index].declared) {
        return &stack_view->stack_views[index];
    }
    return 0;
}

static unsigned long stack_view_value_or(
    const latticra_kernel_runtime_entry_stack_view_result_t *stack_view,
    size_t index,
    unsigned long fallback,
    unsigned long (*reader)(
        const latticra_kernel_runtime_entry_stack_view_entry_t *entry)) {
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry =
        stack_view_at(stack_view, index);
    return entry ? reader(entry) : fallback;
}

static unsigned long read_stack_view_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->stack_view_token;
}

static unsigned long read_register_view_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->register_view_token;
}

static unsigned long read_frame_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->frame_token;
}

static unsigned long read_admission_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->admission_token;
}

static unsigned long read_run_entry_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->run_entry_token;
}

static unsigned long read_activation_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->activation_token;
}

static unsigned long read_pid_token(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->pid_token;
}

static unsigned long read_run_entry_rank(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->run_entry_rank;
}

static unsigned long read_admission_rank(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->admission_rank;
}

static unsigned long read_frame_rank(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->frame_rank;
}

static unsigned long read_register_view_rank(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->register_view_rank;
}

static unsigned long read_stack_view_rank(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
    return entry->stack_view_rank;
}

static unsigned long read_remaining_budget(
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry) {
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
    const latticra_kernel_runtime_entry_stack_view_result_t *stack_view,
    size_t index,
    const char *fallback) {
    const latticra_kernel_runtime_entry_stack_view_entry_t *entry =
        stack_view_at(stack_view, index);
    return entry ? entry->process_label : fallback;
}

static const char *class_for(size_t index) {
    switch (index) {
        case 0u:
            return "kernel-report-runtime-entry-address-space-view";
        case 1u:
            return "entropy-runtime-entry-address-space-view";
        case 2u:
            return "console-runtime-entry-address-space-view";
        case 3u:
            return "idle-runtime-entry-address-space-view";
        default:
            return "reserved-runtime-entry-address-space-view";
    }
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

static void fill_address_space_view(
    latticra_kernel_runtime_entry_address_space_view_entry_t *entry,
    const latticra_kernel_runtime_entry_stack_view_result_t *stack_view,
    size_t index) {
    memset(entry, 0, sizeof(*entry));
    entry->address_space_view_index = index;
    entry->address_space_view_token =
        fallback_address_space_view_token(index);
    entry->stack_view_token = stack_view_value_or(stack_view, index,
        fallback_stack_view_token(index), read_stack_view_token);
    entry->register_view_token = stack_view_value_or(stack_view, index,
        fallback_register_view_token(index), read_register_view_token);
    entry->frame_token = stack_view_value_or(stack_view, index,
        fallback_frame_token(index), read_frame_token);
    entry->admission_token = stack_view_value_or(stack_view, index,
        fallback_admission_token(index), read_admission_token);
    entry->run_entry_token = stack_view_value_or(stack_view, index,
        fallback_run_entry_token(index), read_run_entry_token);
    entry->activation_token = stack_view_value_or(stack_view, index,
        fallback_activation_token(index), read_activation_token);
    entry->pid_token = stack_view_value_or(stack_view, index,
        2000ul + (unsigned long)index, read_pid_token);
    entry->run_entry_rank = stack_view_value_or(stack_view, index,
        (unsigned long)index + 1ul, read_run_entry_rank);
    entry->admission_rank = stack_view_value_or(stack_view, index,
        (unsigned long)index + 1ul, read_admission_rank);
    entry->frame_rank = stack_view_value_or(stack_view, index,
        (unsigned long)index + 1ul, read_frame_rank);
    entry->register_view_rank = stack_view_value_or(stack_view, index,
        (unsigned long)index + 1ul, read_register_view_rank);
    entry->stack_view_rank = stack_view_value_or(stack_view, index,
        (unsigned long)index + 1ul, read_stack_view_rank);
    entry->address_space_view_rank = (unsigned long)index + 1ul;
    entry->remaining_budget_ns = stack_view_value_or(stack_view, index,
        0ul, read_remaining_budget);
    entry->address_space_slot_count = 4ul;
    entry->address_space_window_bytes = 1048576ul;
    entry->stack_view_declared = 1;
    entry->address_space_view_declared = 1;
    entry->address_space_root_declared = 1;
    entry->user_range_declared = 1;
    entry->kernel_range_declared = 1;
    entry->guard_region_declared = 1;
    address_space_view_copy(entry->process_label,
        sizeof(entry->process_label),
        process_for(stack_view, index, fallback_process(index)));
    address_space_view_copy(entry->address_space_view_class,
        sizeof(entry->address_space_view_class), class_for(index));
    address_space_view_copy(entry->address_space_view_status,
        sizeof(entry->address_space_view_status), "declared-metadata");
    address_space_view_copy(entry->authority_status,
        sizeof(entry->authority_status),
        "runtime-entry-address-space-view-authority-denied");
    entry->declared = 1;
    entry->address_space_view_planned = 0;
    entry->address_space_view_built = 0;
    entry->address_space_view_installed = 0;
    entry->address_space_capture_planned = 0;
    entry->address_space_switch_planned = 0;
    entry->page_table_walk_planned = 0;
    entry->mmu_update_planned = 0;
    entry->admitted = 0;
    entry->runtime_entry_planned = 0;
    entry->runtime_entry_entered = 0;
    entry->execution_entered = 0;
    entry->context_switch_planned = 0;
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
    entry->preemption_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 31u;
}

static void fill_address_space_views(
    latticra_kernel_runtime_entry_address_space_view_result_t *result,
    size_t requested_address_space_view_count) {
    size_t count = requested_address_space_view_count;
    size_t i;

    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_MAX) {
        count = LATTICRA_KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_MAX;
    }

    result->address_space_view_count = count;
    for (i = 0u; i < count; ++i) {
        fill_address_space_view(&result->address_space_views[i],
            &result->runtime_entry_stack_view, i);
    }
}

latticra_status_t latticra_kernel_runtime_entry_address_space_view_evaluate(
    const latticra_kernel_runtime_entry_address_space_view_request_t *request,
    latticra_kernel_runtime_entry_address_space_view_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        address_space_view_copy(result->address_space_view_status,
            sizeof(result->address_space_view_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_runtime_entry_stack_view_evaluate(
        &request->runtime_entry_stack_view_request,
        &result->runtime_entry_stack_view);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        address_space_view_copy(result->address_space_view_status,
            sizeof(result->address_space_view_status),
            "runtime-entry-stack-view-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_address_space_views(result,
        request->requested_address_space_view_count);
    result->no_effect = result->runtime_entry_stack_view.no_effect;
    address_space_view_copy(result->address_space_view_status,
        sizeof(result->address_space_view_status),
        result->no_effect ?
            "runtime-entry-address-space-view-seed-ready" :
            "runtime-entry-address-space-view-seed-blocked");
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

latticra_status_t latticra_kernel_runtime_entry_address_space_view_report(
    const latticra_kernel_runtime_entry_address_space_view_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL RUNTIME ENTRY ADDRESS SPACE VIEW REPORT\n"
        "address_space_view_status=%s\n"
        "policy_status=%s\n"
        "runtime_entry_stack_view_status=%s\n"
        "runtime_entry_register_view_status=%s\n"
        "runtime_entry_frame_status=%s\n"
        "runtime_entry_admission_status=%s\n"
        "scheduler_run_entry_status=%s\n"
        "address_space_view_count=%lu\n"
        "no_effect=%d\n"
        "runtime_entry_address_space_view_allowed=%d\n"
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
        "page_table_write_allowed=%d\n"
        "tlb_flush_allowed=%d\n"
        "mmu_update_allowed=%d\n"
        "preemption_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->address_space_view_status,
        result->policy_status,
        result->runtime_entry_stack_view.stack_view_status,
        result->runtime_entry_stack_view.runtime_entry_register_view.
            register_view_status,
        result->runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.frame_status,
        result->runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.runtime_entry_admission.admission_status,
        result->runtime_entry_stack_view.runtime_entry_register_view.
            runtime_entry_frame.runtime_entry_admission.scheduler_run_entry.
            run_entry_status,
        (unsigned long)result->address_space_view_count,
        result->no_effect,
        result->runtime_entry_address_space_view_allowed,
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
        result->page_table_write_allowed,
        result->tlb_flush_allowed,
        result->mmu_update_allowed,
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

    for (i = 0u; i < result->address_space_view_count; ++i) {
        const latticra_kernel_runtime_entry_address_space_view_entry_t *entry =
            &result->address_space_views[i];
        status = append_text(buffer, buffer_len, &used,
            "address_space_view[%lu].process_label=%s\n"
            "address_space_view[%lu].address_space_view_token=%lu\n"
            "address_space_view[%lu].stack_view_token=%lu\n"
            "address_space_view[%lu].register_view_token=%lu\n"
            "address_space_view[%lu].frame_token=%lu\n"
            "address_space_view[%lu].admission_token=%lu\n"
            "address_space_view[%lu].run_entry_token=%lu\n"
            "address_space_view[%lu].activation_token=%lu\n"
            "address_space_view[%lu].pid_token=%lu\n"
            "address_space_view[%lu].run_entry_rank=%lu\n"
            "address_space_view[%lu].admission_rank=%lu\n"
            "address_space_view[%lu].frame_rank=%lu\n"
            "address_space_view[%lu].register_view_rank=%lu\n"
            "address_space_view[%lu].stack_view_rank=%lu\n"
            "address_space_view[%lu].address_space_view_rank=%lu\n"
            "address_space_view[%lu].remaining_budget_ns=%lu\n"
            "address_space_view[%lu].address_space_slot_count=%lu\n"
            "address_space_view[%lu].address_space_window_bytes=%lu\n"
            "address_space_view[%lu].stack_view_declared=%d\n"
            "address_space_view[%lu].address_space_view_declared=%d\n"
            "address_space_view[%lu].address_space_root_declared=%d\n"
            "address_space_view[%lu].user_range_declared=%d\n"
            "address_space_view[%lu].kernel_range_declared=%d\n"
            "address_space_view[%lu].guard_region_declared=%d\n"
            "address_space_view[%lu].address_space_view_class=%s\n"
            "address_space_view[%lu].address_space_view_status=%s\n"
            "address_space_view[%lu].authority_status=%s\n"
            "address_space_view[%lu].address_space_view_planned=%d\n"
            "address_space_view[%lu].address_space_view_built=%d\n"
            "address_space_view[%lu].address_space_view_installed=%d\n"
            "address_space_view[%lu].address_space_capture_planned=%d\n"
            "address_space_view[%lu].address_space_switch_planned=%d\n"
            "address_space_view[%lu].page_table_walk_planned=%d\n"
            "address_space_view[%lu].mmu_update_planned=%d\n"
            "address_space_view[%lu].runtime_entry_entered=%d\n"
            "address_space_view[%lu].execution_entered=%d\n"
            "address_space_view[%lu].context_switch_planned=%d\n"
            "address_space_view[%lu].runtime_entry_address_space_view_allowed=%d\n"
            "address_space_view[%lu].runtime_entry_stack_view_allowed=%d\n"
            "address_space_view[%lu].runtime_entry_register_view_allowed=%d\n"
            "address_space_view[%lu].runtime_entry_frame_allowed=%d\n"
            "address_space_view[%lu].runtime_entry_admission_allowed=%d\n"
            "address_space_view[%lu].runtime_entry_allowed=%d\n"
            "address_space_view[%lu].scheduler_run_entry_allowed=%d\n"
            "address_space_view[%lu].dispatch_allowed=%d\n"
            "address_space_view[%lu].run_queue_mutation_allowed=%d\n"
            "address_space_view[%lu].context_switch_allowed=%d\n"
            "address_space_view[%lu].register_save_allowed=%d\n"
            "address_space_view[%lu].register_restore_allowed=%d\n"
            "address_space_view[%lu].stack_switch_allowed=%d\n"
            "address_space_view[%lu].address_space_switch_allowed=%d\n"
            "address_space_view[%lu].page_table_write_allowed=%d\n"
            "address_space_view[%lu].tlb_flush_allowed=%d\n"
            "address_space_view[%lu].mmu_update_allowed=%d\n"
            "address_space_view[%lu].hardware_effect_allowed=%d\n"
            "address_space_view[%lu].host_effect_allowed=%d\n"
            "address_space_view[%lu].no_effect=%d\n",
            (unsigned long)i, entry->process_label,
            (unsigned long)i, entry->address_space_view_token,
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
            (unsigned long)i, entry->address_space_view_rank,
            (unsigned long)i, entry->remaining_budget_ns,
            (unsigned long)i, entry->address_space_slot_count,
            (unsigned long)i, entry->address_space_window_bytes,
            (unsigned long)i, entry->stack_view_declared,
            (unsigned long)i, entry->address_space_view_declared,
            (unsigned long)i, entry->address_space_root_declared,
            (unsigned long)i, entry->user_range_declared,
            (unsigned long)i, entry->kernel_range_declared,
            (unsigned long)i, entry->guard_region_declared,
            (unsigned long)i, entry->address_space_view_class,
            (unsigned long)i, entry->address_space_view_status,
            (unsigned long)i, entry->authority_status,
            (unsigned long)i, entry->address_space_view_planned,
            (unsigned long)i, entry->address_space_view_built,
            (unsigned long)i, entry->address_space_view_installed,
            (unsigned long)i, entry->address_space_capture_planned,
            (unsigned long)i, entry->address_space_switch_planned,
            (unsigned long)i, entry->page_table_walk_planned,
            (unsigned long)i, entry->mmu_update_planned,
            (unsigned long)i, entry->runtime_entry_entered,
            (unsigned long)i, entry->execution_entered,
            (unsigned long)i, entry->context_switch_planned,
            (unsigned long)i,
                entry->runtime_entry_address_space_view_allowed,
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
            (unsigned long)i, entry->page_table_write_allowed,
            (unsigned long)i, entry->tlb_flush_allowed,
            (unsigned long)i, entry->mmu_update_allowed,
            (unsigned long)i, entry->hardware_effect_allowed,
            (unsigned long)i, entry->host_effect_allowed,
            (unsigned long)i, entry->no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
