#ifndef LATTICRA_KERNEL_SCHEDULER_TICK_H
#define LATTICRA_KERNEL_SCHEDULER_TICK_H

#include "latticra/kernel_timer_source.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX 64u
#define LATTICRA_KERNEL_SCHEDULER_TICK_MAX 8u
#define LATTICRA_KERNEL_SCHEDULER_TICK_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_timer_source_request_t timer_source_request;
    size_t requested_tick_count;
} latticra_kernel_scheduler_tick_request_t;

typedef struct {
    size_t tick_index;
    unsigned long tick_token;
    unsigned long timer_token;
    unsigned long irq_vector;
    unsigned long budget_ns;
    char timer_name[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char scheduler_slot_label[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char process_label[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char tick_class[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char tick_status[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    int declared;
    int pending;
    int dispatched;
    int timer_tick_allowed;
    int scheduler_tick_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_scheduler_tick_entry_t;

typedef struct {
    latticra_status_t status;
    char tick_status[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_SCHEDULER_TICK_LABEL_MAX];
    latticra_kernel_timer_source_result_t timer_source;
    latticra_kernel_scheduler_tick_entry_t ticks[
        LATTICRA_KERNEL_SCHEDULER_TICK_MAX];
    size_t tick_count;
    int no_effect;
    int timer_tick_allowed;
    int scheduler_tick_allowed;
    int run_queue_mutation_allowed;
    int context_switch_allowed;
    int preemption_allowed;
    int time_accounting_allowed;
    int time_read_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_scheduler_tick_result_t;

latticra_status_t latticra_kernel_scheduler_tick_default_request(
    latticra_kernel_scheduler_tick_request_t *request);

latticra_status_t latticra_kernel_scheduler_tick_evaluate(
    const latticra_kernel_scheduler_tick_request_t *request,
    latticra_kernel_scheduler_tick_result_t *result);

latticra_status_t latticra_kernel_scheduler_tick_report(
    const latticra_kernel_scheduler_tick_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
