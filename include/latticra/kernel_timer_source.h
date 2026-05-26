#ifndef LATTICRA_KERNEL_TIMER_SOURCE_H
#define LATTICRA_KERNEL_TIMER_SOURCE_H

#include "latticra/kernel_interrupt_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX 64u
#define LATTICRA_KERNEL_TIMER_SOURCE_TIMER_MAX 8u
#define LATTICRA_KERNEL_TIMER_SOURCE_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_interrupt_table_request_t interrupt_table_request;
    size_t requested_timer_count;
} latticra_kernel_timer_source_request_t;

typedef struct {
    size_t timer_index;
    unsigned long timer_token;
    unsigned long irq_vector;
    unsigned long period_ns;
    char name[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char driver_name[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char device_path[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char timer_class[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char backing[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char timer_status[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    int declared;
    int armed;
    int running;
    int tick_allowed;
    int arm_allowed;
    int disarm_allowed;
    int scheduler_tick_allowed;
    int preemption_allowed;
    int time_read_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_timer_source_entry_t;

typedef struct {
    latticra_status_t status;
    char timer_status[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_TIMER_SOURCE_LABEL_MAX];
    latticra_kernel_interrupt_table_result_t interrupt_table;
    latticra_kernel_timer_source_entry_t timers[
        LATTICRA_KERNEL_TIMER_SOURCE_TIMER_MAX];
    size_t timer_count;
    int no_effect;
    int timer_tick_allowed;
    int timer_arm_allowed;
    int timer_disarm_allowed;
    int scheduler_tick_allowed;
    int preemption_allowed;
    int time_read_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_timer_source_result_t;

latticra_status_t latticra_kernel_timer_source_default_request(
    latticra_kernel_timer_source_request_t *request);

latticra_status_t latticra_kernel_timer_source_evaluate(
    const latticra_kernel_timer_source_request_t *request,
    latticra_kernel_timer_source_result_t *result);

latticra_status_t latticra_kernel_timer_source_report(
    const latticra_kernel_timer_source_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
