#ifndef LATTICRA_KERNEL_PREEMPTION_H
#define LATTICRA_KERNEL_PREEMPTION_H

#include "latticra/kernel_time_accounting.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_PREEMPTION_LABEL_MAX 64u
#define LATTICRA_KERNEL_PREEMPTION_MAX 8u
#define LATTICRA_KERNEL_PREEMPTION_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_time_accounting_request_t time_accounting_request;
    size_t requested_decision_count;
} latticra_kernel_preemption_request_t;

typedef struct {
    size_t decision_index;
    unsigned long decision_token;
    unsigned long pid_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long charged_budget_ns;
    unsigned long consumed_ns;
    unsigned long remaining_budget_ns;
    int preemption_requested;
    char process_label[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    char decision_class[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    char decision_status[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    int declared;
    int evaluated;
    int armed;
    int dispatched;
    int preemption_allowed;
    int time_read_allowed;
    int time_accounting_allowed;
    int context_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int scheduler_credit_update_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_preemption_entry_t;

typedef struct {
    latticra_status_t status;
    char preemption_status[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_PREEMPTION_LABEL_MAX];
    latticra_kernel_time_accounting_result_t time_accounting;
    latticra_kernel_preemption_entry_t decisions[
        LATTICRA_KERNEL_PREEMPTION_MAX];
    size_t decision_count;
    int no_effect;
    int preemption_allowed;
    int time_read_allowed;
    int time_accounting_allowed;
    int context_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int scheduler_credit_update_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_preemption_result_t;

latticra_status_t latticra_kernel_preemption_default_request(
    latticra_kernel_preemption_request_t *request);

latticra_status_t latticra_kernel_preemption_evaluate(
    const latticra_kernel_preemption_request_t *request,
    latticra_kernel_preemption_result_t *result);

latticra_status_t latticra_kernel_preemption_report(
    const latticra_kernel_preemption_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
