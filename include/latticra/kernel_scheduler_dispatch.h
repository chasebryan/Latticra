#ifndef LATTICRA_KERNEL_SCHEDULER_DISPATCH_H
#define LATTICRA_KERNEL_SCHEDULER_DISPATCH_H

#include "latticra/kernel_scheduler_selection.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_DISPATCH_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_DISPATCH_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_scheduler_selection_request_t scheduler_selection_request;
    size_t requested_dispatch_count;
} latticra_kernel_scheduler_dispatch_request_t;

typedef struct {
    size_t dispatch_index;
    unsigned long dispatch_token;
    unsigned long selection_token;
    unsigned long pid_token;
    unsigned long credit_token;
    unsigned long decision_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long candidate_rank;
    unsigned long dispatch_rank;
    unsigned long scheduler_credit_ns;
    unsigned long quota_credit_ns;
    unsigned long remaining_budget_ns;
    int candidate_declared;
    int dispatch_declared;
    char process_label[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    char dispatch_class[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    char dispatch_status[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    int declared;
    int dispatch_planned;
    int selected;
    int enqueued;
    int dequeued;
    int dispatched;
    int context_switch_planned;
    int scheduler_dispatch_allowed;
    int scheduler_selection_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int cpu_usage_write_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_scheduler_dispatch_entry_t;

typedef struct {
    latticra_status_t status;
    char dispatch_status[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_DISPATCH_LABEL_MAX];
    latticra_kernel_scheduler_selection_result_t scheduler_selection;
    latticra_kernel_scheduler_dispatch_entry_t dispatches[
        LATTICRA_KERNEL_SCHEDULER_DISPATCH_MAX];
    size_t dispatch_count;
    int no_effect;
    int scheduler_dispatch_allowed;
    int scheduler_selection_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int cpu_usage_write_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_scheduler_dispatch_result_t;

latticra_status_t latticra_kernel_scheduler_dispatch_default_request(
    latticra_kernel_scheduler_dispatch_request_t *request);

latticra_status_t latticra_kernel_scheduler_dispatch_evaluate(
    const latticra_kernel_scheduler_dispatch_request_t *request,
    latticra_kernel_scheduler_dispatch_result_t *result);

latticra_status_t latticra_kernel_scheduler_dispatch_report(
    const latticra_kernel_scheduler_dispatch_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
