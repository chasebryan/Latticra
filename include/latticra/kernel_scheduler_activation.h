#ifndef LATTICRA_KERNEL_SCHEDULER_ACTIVATION_H
#define LATTICRA_KERNEL_SCHEDULER_ACTIVATION_H

#include "latticra/kernel_scheduler_handoff.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_ACTIVATION_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_ACTIVATION_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_scheduler_handoff_request_t scheduler_handoff_request;
    size_t requested_activation_count;
} latticra_kernel_scheduler_activation_request_t;

typedef struct {
    size_t activation_index;
    unsigned long activation_token;
    unsigned long handoff_token;
    unsigned long dispatch_token;
    unsigned long selection_token;
    unsigned long pid_token;
    unsigned long credit_token;
    unsigned long decision_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long candidate_rank;
    unsigned long dispatch_rank;
    unsigned long handoff_rank;
    unsigned long activation_rank;
    unsigned long scheduler_credit_ns;
    unsigned long quota_credit_ns;
    unsigned long remaining_budget_ns;
    int candidate_declared;
    int dispatch_declared;
    int handoff_declared;
    int activation_declared;
    char process_label[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    char activation_class[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    char activation_status[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    int declared;
    int activation_planned;
    int handoff_planned;
    int dispatch_planned;
    int selected;
    int enqueued;
    int dequeued;
    int dispatched;
    int activated;
    int context_switch_planned;
    int execution_entered;
    int scheduler_activation_allowed;
    int scheduler_handoff_allowed;
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
    int runtime_entry_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_scheduler_activation_entry_t;

typedef struct {
    latticra_status_t status;
    char activation_status[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_LABEL_MAX];
    latticra_kernel_scheduler_handoff_result_t scheduler_handoff;
    latticra_kernel_scheduler_activation_entry_t activations[
        LATTICRA_KERNEL_SCHEDULER_ACTIVATION_MAX];
    size_t activation_count;
    int no_effect;
    int scheduler_activation_allowed;
    int scheduler_handoff_allowed;
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
    int runtime_entry_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_scheduler_activation_result_t;

latticra_status_t latticra_kernel_scheduler_activation_default_request(
    latticra_kernel_scheduler_activation_request_t *request);

latticra_status_t latticra_kernel_scheduler_activation_evaluate(
    const latticra_kernel_scheduler_activation_request_t *request,
    latticra_kernel_scheduler_activation_result_t *result);

latticra_status_t latticra_kernel_scheduler_activation_report(
    const latticra_kernel_scheduler_activation_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
