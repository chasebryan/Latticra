#include "latticra/kernel_scheduler_credit.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void credit_copy(char *dst, size_t dst_len, const char *src) {
    size_t n;
    if (dst == 0 || dst_len == 0u) return;
    dst[0] = '\0';
    if (src == 0) return;
    n = strlen(src);
    if (n >= dst_len) n = dst_len - 1u;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void seed_result(latticra_kernel_scheduler_credit_result_t *result) {
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    credit_copy(result->credit_status, sizeof(result->credit_status), "pending");
    credit_copy(result->policy_status, sizeof(result->policy_status),
        "report-only");
    result->no_effect = 1;
    result->scheduler_credit_update_allowed = 0;
    result->quota_update_allowed = 0;
    result->cpu_usage_write_allowed = 0;
    result->time_accounting_allowed = 0;
    result->time_read_allowed = 0;
    result->preemption_allowed = 0;
    result->context_switch_allowed = 0;
    result->dispatch_allowed = 0;
    result->run_queue_mutation_allowed = 0;
    result->process_wake_allowed = 0;
    result->hardware_effect_allowed = 0;
    result->host_effect_allowed = 0;
    result->evidence_level = 21u;
}

latticra_status_t latticra_kernel_scheduler_credit_default_request(
    latticra_kernel_scheduler_credit_request_t *request) {
    if (request == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(request, 0, sizeof(*request));
    if (latticra_kernel_preemption_default_request(
            &request->preemption_request) != LATTICRA_STATUS_OK) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    request->requested_credit_count = 4u;
    return LATTICRA_STATUS_OK;
}

static const latticra_kernel_preemption_entry_t *decision_at(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index) {
    if (index < preemption->decision_count &&
        preemption->decisions[index].declared) {
        return &preemption->decisions[index];
    }
    return 0;
}

static unsigned long decision_pid_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->pid_token : fallback;
}

static unsigned long decision_token_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->decision_token : fallback;
}

static unsigned long decision_switch_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->switch_token : fallback;
}

static unsigned long decision_tick_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->tick_token : fallback;
}

static unsigned long decision_budget_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->charged_budget_ns : fallback;
}

static unsigned long decision_consumed_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->consumed_ns : fallback;
}

static unsigned long decision_remaining_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    unsigned long fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->remaining_budget_ns : fallback;
}

static int decision_update_request_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    int fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->preemption_requested : fallback;
}

static const char *decision_process_for(
    const latticra_kernel_preemption_result_t *preemption,
    size_t index,
    const char *fallback) {
    const latticra_kernel_preemption_entry_t *entry =
        decision_at(preemption, index);
    return entry ? entry->process_label : fallback;
}

static void fill_credit(
    latticra_kernel_scheduler_credit_entry_t *entry,
    size_t index,
    unsigned long credit_token,
    unsigned long pid_token,
    unsigned long decision_token,
    unsigned long switch_token,
    unsigned long tick_token,
    unsigned long charged_budget_ns,
    unsigned long consumed_ns,
    unsigned long remaining_budget_ns,
    int credit_update_requested,
    const char *process_label,
    const char *credit_class) {
    memset(entry, 0, sizeof(*entry));
    entry->credit_index = index;
    entry->credit_token = credit_token;
    entry->pid_token = pid_token;
    entry->decision_token = decision_token;
    entry->switch_token = switch_token;
    entry->tick_token = tick_token;
    entry->charged_budget_ns = charged_budget_ns;
    entry->consumed_ns = consumed_ns;
    entry->remaining_budget_ns = remaining_budget_ns;
    entry->scheduler_credit_ns = remaining_budget_ns;
    entry->quota_credit_ns = charged_budget_ns;
    entry->credit_update_requested = credit_update_requested;
    credit_copy(entry->process_label, sizeof(entry->process_label),
        process_label);
    credit_copy(entry->credit_class, sizeof(entry->credit_class), credit_class);
    credit_copy(entry->credit_status, sizeof(entry->credit_status),
        "declared-metadata");
    credit_copy(entry->authority_status, sizeof(entry->authority_status),
        "scheduler-credit-authority-denied");
    entry->declared = 1;
    entry->computed = 0;
    entry->queued = 0;
    entry->persisted = 0;
    entry->scheduler_credit_update_allowed = 0;
    entry->quota_update_allowed = 0;
    entry->cpu_usage_write_allowed = 0;
    entry->time_accounting_allowed = 0;
    entry->time_read_allowed = 0;
    entry->preemption_allowed = 0;
    entry->context_switch_allowed = 0;
    entry->dispatch_allowed = 0;
    entry->run_queue_mutation_allowed = 0;
    entry->process_wake_allowed = 0;
    entry->hardware_effect_allowed = 0;
    entry->host_effect_allowed = 0;
    entry->no_effect = 1;
    entry->evidence_level = 21u;
}

static void fill_credits(
    latticra_kernel_scheduler_credit_result_t *result,
    size_t requested_credit_count) {
    size_t count = requested_credit_count;
    size_t i;
    if (count == 0u) count = 4u;
    if (count > LATTICRA_KERNEL_SCHEDULER_CREDIT_MAX) {
        count = LATTICRA_KERNEL_SCHEDULER_CREDIT_MAX;
    }

    result->credit_count = count;
    if (count > 0u) {
        fill_credit(&result->credits[0], 0u, 0ul,
            decision_pid_for(&result->preemption, 0u, 1ul),
            decision_token_for(&result->preemption, 0u, 0ul),
            decision_switch_for(&result->preemption, 0u, 0ul),
            decision_tick_for(&result->preemption, 0u, 1ul),
            decision_budget_for(&result->preemption, 0u, 10000000ul),
            decision_consumed_for(&result->preemption, 0u, 0ul),
            decision_remaining_for(&result->preemption, 0u, 10000000ul),
            decision_update_request_for(&result->preemption, 0u, 0),
            decision_process_for(&result->preemption, 0u,
                "kernel-report-process-metadata"),
            "kernel-report-scheduler-credit");
    }
    if (count > 1u) {
        fill_credit(&result->credits[1], 1u, 1ul,
            decision_pid_for(&result->preemption, 1u, 2ul),
            decision_token_for(&result->preemption, 1u, 1ul),
            decision_switch_for(&result->preemption, 1u, 1ul),
            decision_tick_for(&result->preemption, 1u, 2ul),
            decision_budget_for(&result->preemption, 1u, 1000000ul),
            decision_consumed_for(&result->preemption, 1u, 0ul),
            decision_remaining_for(&result->preemption, 1u, 1000000ul),
            decision_update_request_for(&result->preemption, 1u, 0),
            decision_process_for(&result->preemption, 1u,
                "entropy-report-process-metadata"),
            "entropy-scheduler-credit");
    }
    if (count > 2u) {
        fill_credit(&result->credits[2], 2u, 2ul,
            decision_pid_for(&result->preemption, 2u, 3ul),
            decision_token_for(&result->preemption, 2u, 2ul),
            decision_switch_for(&result->preemption, 2u, 2ul),
            decision_tick_for(&result->preemption, 2u, 3ul),
            decision_budget_for(&result->preemption, 2u, 0ul),
            decision_consumed_for(&result->preemption, 2u, 0ul),
            decision_remaining_for(&result->preemption, 2u, 0ul),
            decision_update_request_for(&result->preemption, 2u, 0),
            decision_process_for(&result->preemption, 2u,
                "console-report-process-metadata"),
            "console-scheduler-credit");
    }
    if (count > 3u) {
        fill_credit(&result->credits[3], 3u, 3ul,
            decision_pid_for(&result->preemption, 3u, 0ul),
            decision_token_for(&result->preemption, 3u, 3ul),
            decision_switch_for(&result->preemption, 3u, 3ul),
            decision_tick_for(&result->preemption, 3u, 0ul),
            decision_budget_for(&result->preemption, 3u, 0ul),
            decision_consumed_for(&result->preemption, 3u, 0ul),
            decision_remaining_for(&result->preemption, 3u, 0ul),
            decision_update_request_for(&result->preemption, 3u, 0),
            decision_process_for(&result->preemption, 3u,
                "idle-process-metadata"),
            "idle-scheduler-credit");
    }
    for (i = 4u; i < count; ++i) {
        fill_credit(&result->credits[i], i, 9000ul + (unsigned long)i,
            decision_pid_for(&result->preemption, i,
                2000ul + (unsigned long)i),
            decision_token_for(&result->preemption, i,
                8000ul + (unsigned long)i),
            decision_switch_for(&result->preemption, i,
                6000ul + (unsigned long)i),
            decision_tick_for(&result->preemption, i,
                4000ul + (unsigned long)i),
            decision_budget_for(&result->preemption, i, 0ul),
            decision_consumed_for(&result->preemption, i, 0ul),
            decision_remaining_for(&result->preemption, i, 0ul),
            decision_update_request_for(&result->preemption, i, 0),
            decision_process_for(&result->preemption, i,
                "reserved-process-metadata"),
            "reserved-scheduler-credit");
    }
}

latticra_status_t latticra_kernel_scheduler_credit_evaluate(
    const latticra_kernel_scheduler_credit_request_t *request,
    latticra_kernel_scheduler_credit_result_t *result) {
    latticra_status_t status;

    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    seed_result(result);

    if (request == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        credit_copy(result->credit_status, sizeof(result->credit_status),
            "null-request");
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    status = latticra_kernel_preemption_evaluate(&request->preemption_request,
        &result->preemption);
    if (status != LATTICRA_STATUS_OK) {
        result->status = status;
        credit_copy(result->credit_status, sizeof(result->credit_status),
            "preemption-not-ready");
        result->no_effect = 0;
        return status;
    }

    fill_credits(result, request->requested_credit_count);
    result->no_effect = result->preemption.no_effect;
    credit_copy(result->credit_status, sizeof(result->credit_status),
        result->no_effect ? "scheduler-credit-seed-ready" :
            "scheduler-credit-seed-blocked");
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

latticra_status_t latticra_kernel_scheduler_credit_report(
    const latticra_kernel_scheduler_credit_result_t *result,
    char *buffer,
    size_t buffer_len) {
    size_t used = 0u;
    size_t i;
    latticra_status_t status;

    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';

    status = append_text(buffer, buffer_len, &used,
        "LATTICRA KERNEL SCHEDULER CREDIT REPORT\n"
        "credit_status=%s\n"
        "policy_status=%s\n"
        "preemption_status=%s\n"
        "time_accounting_status=%s\n"
        "context_switch_status=%s\n"
        "run_queue_status=%s\n"
        "scheduler_tick_status=%s\n"
        "timer_source_status=%s\n"
        "credit_count=%lu\n"
        "no_effect=%d\n"
        "scheduler_credit_update_allowed=%d\n"
        "quota_update_allowed=%d\n"
        "cpu_usage_write_allowed=%d\n"
        "time_accounting_allowed=%d\n"
        "time_read_allowed=%d\n"
        "preemption_allowed=%d\n"
        "context_switch_allowed=%d\n"
        "dispatch_allowed=%d\n"
        "run_queue_mutation_allowed=%d\n"
        "process_wake_allowed=%d\n"
        "hardware_effect_allowed=%d\n"
        "host_effect_allowed=%d\n"
        "evidence_level=%u\n",
        result->credit_status,
        result->policy_status,
        result->preemption.preemption_status,
        result->preemption.time_accounting.accounting_status,
        result->preemption.time_accounting.context_switch.switch_status,
        result->preemption.time_accounting.context_switch.run_queue.queue_status,
        result->preemption.time_accounting.context_switch.run_queue.scheduler_tick.tick_status,
        result->preemption.time_accounting.context_switch.run_queue.scheduler_tick.timer_source.timer_status,
        (unsigned long)result->credit_count,
        result->no_effect,
        result->scheduler_credit_update_allowed,
        result->quota_update_allowed,
        result->cpu_usage_write_allowed,
        result->time_accounting_allowed,
        result->time_read_allowed,
        result->preemption_allowed,
        result->context_switch_allowed,
        result->dispatch_allowed,
        result->run_queue_mutation_allowed,
        result->process_wake_allowed,
        result->hardware_effect_allowed,
        result->host_effect_allowed,
        result->evidence_level);
    if (status != LATTICRA_STATUS_OK) return status;

    for (i = 0u; i < result->credit_count; ++i) {
        status = append_text(buffer, buffer_len, &used,
            "credit[%lu].process_label=%s\n"
            "credit[%lu].credit_token=%lu\n"
            "credit[%lu].pid_token=%lu\n"
            "credit[%lu].decision_token=%lu\n"
            "credit[%lu].switch_token=%lu\n"
            "credit[%lu].tick_token=%lu\n"
            "credit[%lu].charged_budget_ns=%lu\n"
            "credit[%lu].consumed_ns=%lu\n"
            "credit[%lu].remaining_budget_ns=%lu\n"
            "credit[%lu].scheduler_credit_ns=%lu\n"
            "credit[%lu].quota_credit_ns=%lu\n"
            "credit[%lu].credit_update_requested=%d\n"
            "credit[%lu].credit_class=%s\n"
            "credit[%lu].credit_status=%s\n"
            "credit[%lu].authority_status=%s\n"
            "credit[%lu].declared=%d\n"
            "credit[%lu].computed=%d\n"
            "credit[%lu].queued=%d\n"
            "credit[%lu].persisted=%d\n"
            "credit[%lu].scheduler_credit_update_allowed=%d\n"
            "credit[%lu].quota_update_allowed=%d\n"
            "credit[%lu].cpu_usage_write_allowed=%d\n"
            "credit[%lu].time_accounting_allowed=%d\n"
            "credit[%lu].time_read_allowed=%d\n"
            "credit[%lu].preemption_allowed=%d\n"
            "credit[%lu].context_switch_allowed=%d\n"
            "credit[%lu].dispatch_allowed=%d\n"
            "credit[%lu].run_queue_mutation_allowed=%d\n"
            "credit[%lu].process_wake_allowed=%d\n"
            "credit[%lu].hardware_effect_allowed=%d\n"
            "credit[%lu].host_effect_allowed=%d\n"
            "credit[%lu].no_effect=%d\n",
            (unsigned long)i, result->credits[i].process_label,
            (unsigned long)i, result->credits[i].credit_token,
            (unsigned long)i, result->credits[i].pid_token,
            (unsigned long)i, result->credits[i].decision_token,
            (unsigned long)i, result->credits[i].switch_token,
            (unsigned long)i, result->credits[i].tick_token,
            (unsigned long)i, result->credits[i].charged_budget_ns,
            (unsigned long)i, result->credits[i].consumed_ns,
            (unsigned long)i, result->credits[i].remaining_budget_ns,
            (unsigned long)i, result->credits[i].scheduler_credit_ns,
            (unsigned long)i, result->credits[i].quota_credit_ns,
            (unsigned long)i, result->credits[i].credit_update_requested,
            (unsigned long)i, result->credits[i].credit_class,
            (unsigned long)i, result->credits[i].credit_status,
            (unsigned long)i, result->credits[i].authority_status,
            (unsigned long)i, result->credits[i].declared,
            (unsigned long)i, result->credits[i].computed,
            (unsigned long)i, result->credits[i].queued,
            (unsigned long)i, result->credits[i].persisted,
            (unsigned long)i, result->credits[i].scheduler_credit_update_allowed,
            (unsigned long)i, result->credits[i].quota_update_allowed,
            (unsigned long)i, result->credits[i].cpu_usage_write_allowed,
            (unsigned long)i, result->credits[i].time_accounting_allowed,
            (unsigned long)i, result->credits[i].time_read_allowed,
            (unsigned long)i, result->credits[i].preemption_allowed,
            (unsigned long)i, result->credits[i].context_switch_allowed,
            (unsigned long)i, result->credits[i].dispatch_allowed,
            (unsigned long)i, result->credits[i].run_queue_mutation_allowed,
            (unsigned long)i, result->credits[i].process_wake_allowed,
            (unsigned long)i, result->credits[i].hardware_effect_allowed,
            (unsigned long)i, result->credits[i].host_effect_allowed,
            (unsigned long)i, result->credits[i].no_effect);
        if (status != LATTICRA_STATUS_OK) return status;
    }

    return LATTICRA_STATUS_OK;
}
