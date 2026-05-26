#include "latticra/kernel_preemption.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void preemption_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_preemption_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    preemption_copy(result->preemption_status,
        sizeof(result->preemption_status), "pending");
    preemption_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->preemption_allowed = 0;
    result->time_read_allowed = 0;
    result->time_accounting_allowed = 0;
    result->context_switch_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->scheduler_credit_update_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 20u;
}

latticra_status_t latticra_kernel_preemption_default_request(
    latticra_kernel_preemption_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_time_accounting_default_request(
            &request->time_accounting_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_decision_count = 4u;
    return LATTICRA_STATUS_OK;
}

static unsigned long remaining_budget(
    unsigned long charged_budget_ns,
    unsigned long consumed_ns) {
    return consumed_ns >= charged_budget_ns ? 0ul :
        charged_budget_ns - consumed_ns;
}

static void fill_decision(
    latticra_kernel_preemption_entry_t *entry,
    size_t index,
    unsigned long decision_token,
    unsigned long pid_token,
    unsigned long switch_token,
    unsigned long tick_token,
    unsigned long charged_budget_ns,
    unsigned long consumed_ns,
    const char *process_label,
    const char *decision_class) {
    memset(entry, 0, sizeof(*entry));
    entry->decision_index = index;
    entry->decision_token = decision_token;
    entry->pid_token = pid_token;
    entry->switch_token = switch_token;
    entry->tick_token = tick_token;
    entry->charged_budget_ns = charged_budget_ns;
    entry->consumed_ns = consumed_ns;
    entry->remaining_budget_ns = remaining_budget(charged_budget_ns, consumed_ns);
    entry->preemption_requested =
        charged_budget_ns > 0ul && consumed_ns >= charged_budget_ns;
    preemption_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    preemption_copy(entry->decision_class, sizeof(entry->decision_class),
        decision_class);
    preemption_copy(entry->decision_status, sizeof(entry->decision_status),
        "declared-metadata");
    preemption_copy(entry->authority_status, sizeof(entry->authority_status),
        "preemption-authority-denied");
    entry->declared = 1;
    entry->evaluated = 0;
    entry->armed = 0;
    entry->dispatched = 0;
    entry->preemption_allowed = 0;
    entry->time_read_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 20u;
}

static const latticra_kernel_time_accounting_entry_t *account_at(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index) {
    if (index < time_accounting->account_count &&
        time_accounting->accounts[index].declared) {
        return &time_accounting->accounts[index];
    }
    return 0;
}

static unsigned long account_pid_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->pid_token : fallback;
}

static unsigned long account_switch_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long account_tick_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long account_budget_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->charged_budget_ns : fallback;
}

static unsigned long account_consumed_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->consumed_ns : fallback;
}

static const char *account_process_for(
    const latticra_kernel_time_accounting_result_t *time_accounting,
    size_t index,
    const char *fallback) {
    const latticra_kernel_time_accounting_entry_t *entry =
        account_at(time_accounting, index);
    return entry ? entry->process_label : fallback;
}

static void fill_decisions(
    latticra_kernel_preemption_result_t *result,
    size_t requested_decision_count) {
    size_t count = requested_decision_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_PREEMPTION_MAX) {
        count = LATTICRA_KERNEL_PREEMPTION_MAX;
    }

    result->decision_count = count;
    if (count > 0u) {
        fill_decision(&result->decisions[0], 0u, 0ul,
            account_pid_for(&result->time_accounting, 0u, 1ul),
            account_switch_for(&result->time_accounting, 0u, 0ul),
            account_tick_for(&result->time_accounting, 0u, 1ul),
            account_budget_for(&result->time_accounting, 0u, 10000000ul),
            account_consumed_for(&result->time_accounting, 0u, 0ul),
            account_process_for(&result->time_accounting, 0u,
                "kernel-report-process-metadata"),
            "kernel-report-preemption-decision");
    }
    if (count > 1u) {
        fill_decision(&result->decisions[1], 1u, 1ul,
            account_pid_for(&result->time_accounting, 1u, 2ul),
            account_switch_for(&result->time_accounting, 1u, 1ul),
            account_tick_for(&result->time_accounting, 1u, 2ul),
            account_budget_for(&result->time_accounting, 1u, 1000000ul),
            account_consumed_for(&result->time_accounting, 1u, 0ul),
            account_process_for(&result->time_accounting, 1u,
                "entropy-report-process-metadata"),
            "entropy-preemption-decision");
    }
    if (count > 2u) {
        fill_decision(&result->decisions[2], 2u, 2ul,
            account_pid_for(&result->time_accounting, 2u, 3ul),
            account_switch_for(&result->time_accounting, 2u, 2ul),
            account_tick_for(&result->time_accounting, 2u, 3ul),
            account_budget_for(&result->time_accounting, 2u, 0ul),
            account_consumed_for(&result->time_accounting, 2u, 0ul),
            account_process_for(&result->time_accounting, 2u,
                "console-report-process-metadata"),
            "console-preemption-decision");
    }
    if (count > 3u) {
        fill_decision(&result->decisions[3], 3u, 3ul,
            account_pid_for(&result->time_accounting, 3u, 0ul),
            account_switch_for(&result->time_accounting, 3u, 3ul),
            account_tick_for(&result->time_accounting, 3u, 0ul),
            account_budget_for(&result->time_accounting, 3u, 0ul),
            account_consumed_for(&result->time_accounting, 3u, 0ul),
            account_process_for(&result->time_accounting, 3u,
                "idle-process-metadata"),
            "idle-preemption-decision");
    }
    for (i = 4u; i < count; ++i) {
        fill_decision(&result->decisions[i], i, 8000ul + (unsigned long)i,
            account_pid_for(&result->time_accounting, i,
                2000ul + (unsigned long)i),
            account_switch_for(&result->time_accounting, i,
                6000ul + (unsigned long)i),
            account_tick_for(&result->time_accounting, i,
                4000ul + (unsigned long)i),
            account_budget_for(&result->time_accounting, i, 0ul),
            account_consumed_for(&result->time_accounting, i, 0ul),
            account_process_for(&result->time_accounting, i,
                "reserved-process-metadata"),
            "reserved-preemption-decision");
    }
}

latticra_status_t latticra_kernel_preemption_evaluate(
    const latticra_kernel_preemption_request_t *request,
    latticra_kernel_preemption_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        preemption_copy(result->preemption_status,
            sizeof(result->preemption_status), "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_time_accounting_evaluate(
        &request->time_accounting_request,
        &result->time_accounting);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        preemption_copy(result->preemption_status,
            sizeof(result->preemption_status), "time-accounting-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_decisions(result, request->requested_decision_count);
    result->no_effect = result->time_accounting.no_effect;
    preemption_copy(result->preemption_status, sizeof(result->preemption_status),
        result->no_effect ? "preemption-seed-ready" :
            "preemption-seed-blocked");
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

latticra_status_t latticra_kernel_preemption_report(
    const latticra_kernel_preemption_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL PREEMPTION REPORT\n"
        "preemption_status=%s\n"
        "policy_status=%s\n"
        "time_accounting_status=%s\n"
        "context_switch_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "decision_count=%lu\n"
        "no_effect=%d\n"
        "preemption_allowed=%d\n"
        "time_read_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->preemption_status,
        result->policy_status,
        result->time_accounting.accounting_status,
        result->time_accounting.context_switch.switch_status,
        result->time_accounting.context_switch.run_queue.queue_status,
        result->time_accounting.context_switch.run_queue.scheduler_tick.tick_status,
        result->time_accounting.context_switch.run_queue.scheduler_tick.timer_source.timer_status,
        (unsigned long)result->decision_count,
        result->no_effect,
        result->preemption_allowed,
        result->time_read_allowed,
        result->time_accounting_allowed,
        result->context_switch_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->scheduler_credit_update_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->decision_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "decision[%lu].process_label=%s\n"
            "decision[%lu].decision_token=%lu\n"
            "decision[%lu].pid_token=%lu\n"
            "decision[%lu].switch_token=%lu\n"
            "decision[%lu].tick_token=%lu\n"
            "decision[%lu].charged_budget_ns=%lu\n"
            "decision[%lu].consumed_ns=%lu\n"
            "decision[%lu].remaining_budget_ns=%lu\n"
            "decision[%lu].preemption_requested=%d\n"
            "decision[%lu].decision_class=%s\n"
            "decision[%lu].decision_status=%s\n"
            "decision[%lu].authority_status=%s\n"
            "decision[%lu].declared=%d\n"
            "decision[%lu].evaluated=%d\n"
            "decision[%lu].armed=%d\n"
            "decision[%lu].dispatched=%d\n"
            "decision[%lu].preemption_allowed=%d\n"
            "decision[%lu].time_read_allowed=%d\n"
            "decision[%lu].time_accounting_allowed=%d\n"
            "decision[%lu].context_switch_allowed=%d\n"
            "decision[%lu].dispatch_allowed=%d\n"
            "decision[%lu].run_queue_mutation_allowed=%d\n"
            "decision[%lu].scheduler_credit_update_allowed=%d\n"
            "decision[%lu].process_wake_allowed=%d\n"
            "decision[%lu].hardware_effect_allowed=%d\n"
            "decision[%lu].host_effect_allowed=%d\n"
            "decision[%lu].no_effect=%d\n",
            (unsigned long)i, result->decisions[i].process_label,
            (unsigned long)i, result->decisions[i].decision_token,
            (unsigned long)i, result->decisions[i].pid_token,
            (unsigned long)i, result->decisions[i].switch_token,
            (unsigned long)i, result->decisions[i].tick_token,
            (unsigned long)i, result->decisions[i].charged_budget_ns,
            (unsigned long)i, result->decisions[i].consumed_ns,
            (unsigned long)i, result->decisions[i].remaining_budget_ns,
            (unsigned long)i, result->decisions[i].preemption_requested,
            (unsigned long)i, result->decisions[i].decision_class,
            (unsigned long)i, result->decisions[i].decision_status,
            (unsigned long)i, result->decisions[i].authority_status,
            (unsigned long)i, result->decisions[i].declared,
            (unsigned long)i, result->decisions[i].evaluated,
            (unsigned long)i, result->decisions[i].armed,
            (unsigned long)i, result->decisions[i].dispatched,
            (unsigned long)i, result->decisions[i].preemption_allowed,
            (unsigned long)i, result->decisions[i].time_read_allowed,
            (unsigned long)i, result->decisions[i].time_accounting_allowed,
            (unsigned long)i, result->decisions[i].context_switch_allowed,
            (unsigned long)i, result->decisions[i].dispatch_allowed,
            (unsigned long)i, result->decisions[i].run_queue_mutation_allowed,
            (unsigned long)i, result->decisions[i].scheduler_credit_update_allowed,
            (unsigned long)i, result->decisions[i].process_wake_allowed,
            (unsigned long)i, result->decisions[i].hardware_effect_allowed,
            (unsigned long)i, result->decisions[i].host_effect_allowed,
            (unsigned long)i, result->decisions[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
