#ifndef LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_H
#define LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_H

#include "latticra/kernel_runtime_entry_admission.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX 64u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_MAX 8u
#define LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_runtime_entry_admission_request_t
        runtime_entry_admission_request;
    size_t requested_frame_count;
} latticra_kernel_runtime_entry_frame_request_t;

typedef struct {
    size_t frame_index;
    unsigned long frame_token;
    unsigned long admission_token;
    unsigned long run_entry_token;
    unsigned long activation_token;
    unsigned long pid_token;
    unsigned long run_entry_rank;
    unsigned long admission_rank;
    unsigned long frame_rank;
    unsigned long remaining_budget_ns;
    int admission_declared;
    int frame_declared;
    char process_label[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    char frame_class[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    char frame_status[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    int declared;
    int frame_planned;
    int frame_built;
    int frame_installed;
    int admitted;
    int runtime_entry_planned;
    int runtime_entry_entered;
    int execution_entered;
    int context_switch_planned;
    int runtime_entry_frame_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int stack_switch_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_frame_entry_t;

typedef struct {
    latticra_status_t status;
    char frame_status[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_LABEL_MAX];
    latticra_kernel_runtime_entry_admission_result_t runtime_entry_admission;
    latticra_kernel_runtime_entry_frame_entry_t
        frames[LATTICRA_KERNEL_RUNTIME_ENTRY_FRAME_MAX];
    size_t frame_count;
    int no_effect;
    int runtime_entry_frame_allowed;
    int runtime_entry_admission_allowed;
    int runtime_entry_allowed;
    int scheduler_run_entry_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int stack_switch_allowed;
    int preemption_allowed;
    int scheduler_credit_update_allowed;
    int quota_update_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_runtime_entry_frame_result_t;

latticra_status_t latticra_kernel_runtime_entry_frame_default_request(
    latticra_kernel_runtime_entry_frame_request_t *request);

latticra_status_t latticra_kernel_runtime_entry_frame_evaluate(
    const latticra_kernel_runtime_entry_frame_request_t *request,
    latticra_kernel_runtime_entry_frame_result_t *result);

latticra_status_t latticra_kernel_runtime_entry_frame_report(
    const latticra_kernel_runtime_entry_frame_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
