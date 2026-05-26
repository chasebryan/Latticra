#include "latticra/kernel_time_accounting.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void accounting_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_time_accounting_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    accounting_copy(result->accounting_status, sizeof(result->accounting_status),
        "pending");
    accounting_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->cpu_usage_write_allowed = 0;
    result->quota_update_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->context_switch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->preemption_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 19u;
}

latticra_status_t latticra_kernel_time_accounting_default_request(
    latticra_kernel_time_accounting_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_context_switch_default_request(
            &request->context_switch_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_account_count = 4u;
    return LATTICRA_STATUS_OK;
}

static void fill_account(
    latticra_kernel_time_accounting_entry_t *entry,
    size_t index,
    unsigned long account_token,
    unsigned long pid_token,
    unsigned long switch_token,
    unsigned long tick_token,
    unsigned long charged_budget_ns,
    unsigned long consumed_ns,
    const char *process_label,
    const char *accounting_class) {
    memset(entry, 0, sizeof(*entry));
    entry->account_index = index;
    entry->account_token = account_token;
    entry->pid_token = pid_token;
    entry->switch_token = switch_token;
    entry->tick_token = tick_token;
    entry->charged_budget_ns = charged_budget_ns;
    entry->consumed_ns = consumed_ns;
    accounting_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    accounting_copy(entry->accounting_class, sizeof(entry->accounting_class),
        accounting_class);
    accounting_copy(entry->accounting_status, sizeof(entry->accounting_status),
        "declared-metadata");
    accounting_copy(entry->authority_status, sizeof(entry->authority_status),
        "time-accounting-authority-denied");
    entry->declared = 1;
    entry->sampled = 0;
    entry->charged = 0;
    entry->persisted = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->cpu_usage_write_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->preemption_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 19u;
}

static const latticra_kernel_context_switch_entry_t *switch_at(
    const latticra_kernel_context_switch_result_t *context_switch,
    size_t index) {
    if (index < context_switch->switch_count &&
        context_switch->switches[index].declared) {
        return &context_switch->switches[index];
    }
    return 0;
}

static unsigned long account_pid_for(
    const latticra_kernel_context_switch_result_t *context_switch,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_context_switch_entry_t *entry =
        switch_at(context_switch, index);
    return entry ? entry->to_pid_token : fallback;
}

static unsigned long switch_token_for(
    const latticra_kernel_context_switch_result_t *context_switch,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_context_switch_entry_t *entry =
        switch_at(context_switch, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long tick_token_for(
    const latticra_kernel_context_switch_result_t *context_switch,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_context_switch_entry_t *entry =
        switch_at(context_switch, index);
    return entry ? entry->tick_token : fallback;
}

static const char *process_label_for(
    const latticra_kernel_context_switch_result_t *context_switch,
    size_t index,
    const char *fallback) {
    const latticra_kernel_context_switch_entry_t *entry =
        switch_at(context_switch, index);
    return entry ? entry->to_process_label : fallback;
}

static void fill_accounts(
    latticra_kernel_time_accounting_result_t *result,
    size_t requested_account_count) {
    size_t count = requested_account_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_TIME_ACCOUNTING_MAX) {
        count = LATTICRA_KERNEL_TIME_ACCOUNTING_MAX;
    }

    result->account_count = count;
    if (count > 0u) {
        fill_account(&result->accounts[0], 0u, 0ul,
            account_pid_for(&result->context_switch, 0u, 1ul),
            switch_token_for(&result->context_switch, 0u, 0ul),
            tick_token_for(&result->context_switch, 0u, 1ul),
            10000000ul,
            0ul,
            process_label_for(&result->context_switch, 0u,
                "kernel-report-process-metadata"),
            "kernel-report-time-accounting");
    }
    if (count > 1u) {
        fill_account(&result->accounts[1], 1u, 1ul,
            account_pid_for(&result->context_switch, 1u, 2ul),
            switch_token_for(&result->context_switch, 1u, 1ul),
            tick_token_for(&result->context_switch, 1u, 2ul),
            1000000ul,
            0ul,
            process_label_for(&result->context_switch, 1u,
                "entropy-report-process-metadata"),
            "entropy-time-accounting");
    }
    if (count > 2u) {
        fill_account(&result->accounts[2], 2u, 2ul,
            account_pid_for(&result->context_switch, 2u, 3ul),
            switch_token_for(&result->context_switch, 2u, 2ul),
            tick_token_for(&result->context_switch, 2u, 3ul),
            0ul,
            0ul,
            process_label_for(&result->context_switch, 2u,
                "console-report-process-metadata"),
            "console-time-accounting");
    }
    if (count > 3u) {
        fill_account(&result->accounts[3], 3u, 3ul,
            account_pid_for(&result->context_switch, 3u, 0ul),
            switch_token_for(&result->context_switch, 3u, 3ul),
            tick_token_for(&result->context_switch, 3u, 0ul),
            0ul,
            0ul,
            process_label_for(&result->context_switch, 3u,
                "idle-process-metadata"),
            "idle-time-accounting");
    }
    for (i = 4u; i < count; ++i) {
        fill_account(&result->accounts[i], i, 7000ul + (unsigned long)i,
            account_pid_for(&result->context_switch, i,
                2000ul + (unsigned long)i),
            switch_token_for(&result->context_switch, i,
                6000ul + (unsigned long)i),
            tick_token_for(&result->context_switch, i,
                4000ul + (unsigned long)i),
            0ul,
            0ul,
            process_label_for(&result->context_switch, i,
                "reserved-process-metadata"),
            "reserved-time-accounting");
    }
}

latticra_status_t latticra_kernel_time_accounting_evaluate(
    const latticra_kernel_time_accounting_request_t *request,
    latticra_kernel_time_accounting_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        accounting_copy(result->accounting_status,
            sizeof(result->accounting_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_context_switch_evaluate(
        &request->context_switch_request,
        &result->context_switch);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        accounting_copy(result->accounting_status,
            sizeof(result->accounting_status), "context-switch-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_accounts(result, request->requested_account_count);
    result->no_effect = result->context_switch.no_effect;
    accounting_copy(result->accounting_status, sizeof(result->accounting_status),
        result->no_effect ? "time-accounting-seed-ready" :
            "time-accounting-seed-blocked");
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

latticra_status_t latticra_kernel_time_accounting_report(
    const latticra_kernel_time_accounting_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL TIME ACCOUNTING REPORT\n"
        "accounting_status=%s\n"
        "policy_status=%s\n"
        "context_switch_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "interrupt_table_status=%s\n"
        "process_table_status=%s\n"
        "memory_map_status=%s\n"
        "scheduler_status=%s\n"
        "account_count=%lu\n"
        "no_effect=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "cpu_usage_write_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "preemption_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->accounting_status,
        result->policy_status,
        result->context_switch.switch_status,
        result->context_switch.run_queue.queue_status,
        result->context_switch.run_queue.scheduler_tick.tick_status,
        result->context_switch.run_queue.scheduler_tick.timer_source.timer_status,
        result->context_switch.run_queue.scheduler_tick.timer_source.interrupt_table.table_status,
        result->context_switch.run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.table_status,
        result->context_switch.run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.map_status,
        result->context_switch.run_queue.scheduler_tick.timer_source.interrupt_table.driver_catalog.device_registry.vfs_namespace.ipc_table.syscall_table.process_table.memory_map.scheduler.scheduler_status,
        (unsigned long)result->account_count,
        result->no_effect,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->cpu_usage_write_allowed,
        result->quota_update_allowed,
        result->scheduler_credit_update_allowed,
        result->context_switch_allowed,
        result->run_queue_mutation_allowed,
        result->preemption_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->account_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "account[%lu].process_label=%s\n"
            "account[%lu].account_token=%lu\n"
            "account[%lu].pid_token=%lu\n"
            "account[%lu].switch_token=%lu\n"
            "account[%lu].tick_token=%lu\n"
            "account[%lu].charged_budget_ns=%lu\n"
            "account[%lu].consumed_ns=%lu\n"
            "account[%lu].accounting_class=%s\n"
            "account[%lu].accounting_status=%s\n"
            "account[%lu].authority_status=%s\n"
            "account[%lu].declared=%d\n"
            "account[%lu].sampled=%d\n"
            "account[%lu].charged=%d\n"
            "account[%lu].persisted=%d\n"
            "account[%lu].time_accounting_allowed=%d\n"
            "account[%lu].time_read_allowed=%d\n"
            "account[%lu].cpu_usage_write_allowed=%d\n"
            "account[%lu].quota_update_allowed=%d\n"
            "account[%lu].scheduler_credit_update_allowed=%d\n"
            "account[%lu].context_switch_allowed=%d\n"
            "account[%lu].run_queue_mutation_allowed=%d\n"
            "account[%lu].preemption_allowed=%d\n"
            "account[%lu].process_wake_allowed=%d\n"
            "account[%lu].hardware_effect_allowed=%d\n"
            "account[%lu].host_effect_allowed=%d\n"
            "account[%lu].no_effect=%d\n",
            (unsigned long)i, result->accounts[i].process_label,
            (unsigned long)i, result->accounts[i].account_token,
            (unsigned long)i, result->accounts[i].pid_token,
            (unsigned long)i, result->accounts[i].switch_token,
            (unsigned long)i, result->accounts[i].tick_token,
            (unsigned long)i, result->accounts[i].charged_budget_ns,
            (unsigned long)i, result->accounts[i].consumed_ns,
            (unsigned long)i, result->accounts[i].accounting_class,
            (unsigned long)i, result->accounts[i].accounting_status,
            (unsigned long)i, result->accounts[i].authority_status,
            (unsigned long)i, result->accounts[i].declared,
            (unsigned long)i, result->accounts[i].sampled,
            (unsigned long)i, result->accounts[i].charged,
            (unsigned long)i, result->accounts[i].persisted,
            (unsigned long)i, result->accounts[i].time_accounting_allowed,
            (unsigned long)i, result->accounts[i].time_read_allowed,
            (unsigned long)i, result->accounts[i].cpu_usage_write_allowed,
            (unsigned long)i, result->accounts[i].quota_update_allowed,
            (unsigned long)i, result->accounts[i].scheduler_credit_update_allowed,
            (unsigned long)i, result->accounts[i].context_switch_allowed,
            (unsigned long)i, result->accounts[i].run_queue_mutation_allowed,
            (unsigned long)i, result->accounts[i].preemption_allowed,
            (unsigned long)i, result->accounts[i].process_wake_allowed,
            (unsigned long)i, result->accounts[i].hardware_effect_allowed,
            (unsigned long)i, result->accounts[i].host_effect_allowed,
            (unsigned long)i, result->accounts[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
