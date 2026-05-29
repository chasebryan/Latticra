#ifndef LATTICRA_KERNEL_RUN_QUEUE_H
#define LATTICRA_KERNEL_RUN_QUEUE_H

#include "latticra/kernel_scheduler_tick.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX 64u
#define LATTICRA_KERNEL_RUN_QUEUE_ENTRY_MAX 8u
#define LATTICRA_KERNEL_RUN_QUEUE_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_scheduler_tick_request_t scheduler_tick_request;
    size_t requested_queue_count;
} latticra_kernel_run_queue_request_t;

typedef struct {
    size_t queue_index;
    unsigned long queue_token;
    unsigned long pid_token;
    unsigned long tick_token;
    unsigned long priority;
    char process_label[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    char scheduler_slot_label[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    char queue_class[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    char queue_status[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    int declared;
    int enqueued;
    int dequeued;
    int selected;
    int run_queue_mutation_allowed;
    int enqueue_allowed;
    int dequeue_allowed;
    int dispatch_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_run_queue_entry_t;

typedef struct {
    latticra_status_t status;
    char queue_status[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_RUN_QUEUE_LABEL_MAX];
    latticra_kernel_scheduler_tick_result_t scheduler_tick;
    latticra_kernel_run_queue_entry_t queues[
        LATTICRA_KERNEL_RUN_QUEUE_ENTRY_MAX];
    size_t queue_count;
    int no_effect;
    int run_queue_mutation_allowed;
    int enqueue_allowed;
    int dequeue_allowed;
    int dispatch_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_run_queue_result_t;

latticra_status_t latticra_kernel_run_queue_default_request(
    latticra_kernel_run_queue_request_t *request);

latticra_status_t latticra_kernel_run_queue_evaluate(
    const latticra_kernel_run_queue_request_t *request,
    latticra_kernel_run_queue_result_t *result);

latticra_status_t latticra_kernel_run_queue_report(
    const latticra_kernel_run_queue_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
