#ifndef LATTICRA_KERNEL_CONTEXT_SWITCH_H
#define LATTICRA_KERNEL_CONTEXT_SWITCH_H

#include "latticra/kernel_run_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX 64u
#define LATTICRA_KERNEL_CONTEXT_SWITCH_MAX 8u
#define LATTICRA_KERNEL_CONTEXT_SWITCH_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_run_queue_request_t run_queue_request;
    size_t requested_switch_count;
} latticra_kernel_context_switch_request_t;

typedef struct {
    size_t switch_index;
    unsigned long switch_token;
    unsigned long from_pid_token;
    unsigned long to_pid_token;
    unsigned long queue_token;
    unsigned long tick_token;
    unsigned long priority;
    char from_process_label[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char to_process_label[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char scheduler_slot_label[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char switch_class[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char switch_status[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    int declared;
    int prepared;
    int selected;
    int committed;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int stack_switch_allowed;
    int address_space_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_context_switch_entry_t;

typedef struct {
    latticra_status_t status;
    char switch_status[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_CONTEXT_SWITCH_LABEL_MAX];
    latticra_kernel_run_queue_result_t run_queue;
    latticra_kernel_context_switch_entry_t switches[
        LATTICRA_KERNEL_CONTEXT_SWITCH_MAX];
    size_t switch_count;
    int no_effect;
    int context_switch_allowed;
    int register_save_allowed;
    int register_restore_allowed;
    int stack_switch_allowed;
    int address_space_switch_allowed;
    int dispatch_allowed;
    int run_queue_mutation_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_context_switch_result_t;

latticra_status_t latticra_kernel_context_switch_default_request(
    latticra_kernel_context_switch_request_t *request);

latticra_status_t latticra_kernel_context_switch_evaluate(
    const latticra_kernel_context_switch_request_t *request,
    latticra_kernel_context_switch_result_t *result);

latticra_status_t latticra_kernel_context_switch_report(
    const latticra_kernel_context_switch_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
