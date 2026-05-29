#ifndef LATTICRA_KERNEL_SCHEDULER_CREDIT_H
#define LATTICRA_KERNEL_SCHEDULER_CREDIT_H

#include "latticra/kernel_preemption.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_CREDIT_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_CREDIT_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_preemption_request_t preemption_request;
    size_t requested_credit_count;
} latticra_kernel_scheduler_credit_request_t;

typedef struct {
    size_t credit_index;
    unsigned long credit_token;
    unsigned long pid_token;
    unsigned long decision_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long charged_budget_ns;
    unsigned long consumed_ns;
    unsigned long remaining_budget_ns;
    unsigned long scheduler_credit_ns;
    unsigned long quota_credit_ns;
    int credit_update_requested;
    char process_label[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    char credit_class[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    char credit_status[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    int declared;
    int computed;
    int queued;
    int persisted;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int cpu_usage_write_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int preemption_allowed;
    int context_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_scheduler_credit_entry_t;

typedef struct {
    latticra_status_t status;
    char credit_status[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_CREDIT_LABEL_MAX];
    latticra_kernel_preemption_result_t preemption;
    latticra_kernel_scheduler_credit_entry_t credits[
        LATTICRA_KERNEL_SCHEDULER_CREDIT_MAX];
    size_t credit_count;
    int no_effect;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int cpu_usage_write_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int preemption_allowed;
    int context_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_scheduler_credit_result_t;

latticra_status_t latticra_kernel_scheduler_credit_default_request(
    latticra_kernel_scheduler_credit_request_t *request);

latticra_status_t latticra_kernel_scheduler_credit_evaluate(
    const latticra_kernel_scheduler_credit_request_t *request,
    latticra_kernel_scheduler_credit_result_t *result);

latticra_status_t latticra_kernel_scheduler_credit_report(
    const latticra_kernel_scheduler_credit_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
