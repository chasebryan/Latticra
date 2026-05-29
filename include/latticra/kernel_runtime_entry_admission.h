#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_H

#include "latticra/kernel_scheduler_run_entry.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX 64u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_scheduler_run_entry_request_t scheduler_run_entry_request;
    size_t requested_admission_count;
} latticra_kernel_runtime_entry_admission_request_t;

typedef struct {
    size_t admission_index;
    unsigned long admission_token;
    unsigned long run_entry_token;
    unsigned long activation_token;
    unsigned long handoff_token;
    unsigned long dispatch_token;
    unsigned long selection_token;
    unsigned long pid_token;
    unsigned long credit_token;
    unsigned long decision_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long run_entry_rank;
    unsigned long admission_rank;
    unsigned long scheduler_credit_ns;
    unsigned long quota_credit_ns;
    unsigned long remaining_budget_ns;
    int run_entry_declared;
    int admission_declared;
    char process_label[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    char admission_class[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    char admission_status[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    int declared;
    int admission_planned;
    int admitted;
    int runtime_entry_planned;
    int runtime_entry_entered;
    int execution_entered;
    int context_switch_planned;
    int scheduler_run_entry_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
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
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_admission_entry_t;

typedef struct {
    latticra_status_t status;
    char admission_status[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_LABEL_MAX];
    latticra_kernel_scheduler_run_entry_result_t scheduler_run_entry;
    latticra_kernel_runtime_entry_admission_entry_t admissions[
        LATTICRA_KERNEL_RUNTIME_ENTRY_ADMISSION_MAX];
    size_t admission_count;
    int no_effect;
    int scheduler_run_entry_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
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
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_admission_result_t;

latticra_status_t latticra_kernel_runtime_entry_admission_default_request(
    latticra_kernel_runtime_entry_admission_request_t *request);

latticra_status_t latticra_kernel_runtime_entry_admission_evaluate(
    const latticra_kernel_runtime_entry_admission_request_t *request,
    latticra_kernel_runtime_entry_admission_result_t *result);

latticra_status_t latticra_kernel_runtime_entry_admission_report(
    const latticra_kernel_runtime_entry_admission_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
