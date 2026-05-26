#ifndef LATTICRA_KERNEL_SCHEDULER_SELECTION_H
#define LATTICRA_KERNEL_SCHEDULER_SELECTION_H

#include "latticra/kernel_scheduler_credit.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_SELECTION_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_SELECTION_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_scheduler_credit_request_t scheduler_credit_request;
    size_t requested_selection_count;
} latticra_kernel_scheduler_selection_request_t;

typedef struct {
    size_t selection_index;
    unsigned long selection_token;
    unsigned long pid_token;
    unsigned long credit_token;
    unsigned long decision_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long candidate_rank;
    unsigned long scheduler_credit_ns;
    unsigned long quota_credit_ns;
    unsigned long remaining_budget_ns;
    int candidate_declared;
    char process_label[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    char selection_class[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    char selection_status[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    int declared;
    int compared;
    int selected;
    int enqueued;
    int dispatched;
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
} latticra_kernel_scheduler_selection_entry_t;

typedef struct {
    latticra_status_t status;
    char selection_status[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_SELECTION_LABEL_MAX];
    latticra_kernel_scheduler_credit_result_t scheduler_credit;
    latticra_kernel_scheduler_selection_entry_t selections[
        LATTICRA_KERNEL_SCHEDULER_SELECTION_MAX];
    size_t selection_count;
    int no_effect;
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
} latticra_kernel_scheduler_selection_result_t;

latticra_status_t latticra_kernel_scheduler_selection_default_request(
    latticra_kernel_scheduler_selection_request_t *request);

latticra_status_t latticra_kernel_scheduler_selection_evaluate(
    const latticra_kernel_scheduler_selection_request_t *request,
    latticra_kernel_scheduler_selection_result_t *result);

latticra_status_t latticra_kernel_scheduler_selection_report(
    const latticra_kernel_scheduler_selection_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
