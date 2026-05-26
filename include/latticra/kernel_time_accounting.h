#ifndef LATTICRA_KERNEL_TIME_ACCOUNTING_H
#define LATTICRA_KERNEL_TIME_ACCOUNTING_H

#include "latticra/kernel_context_switch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX 64u
#define LATTICRA_KERNEL_TIME_ACCOUNTING_MAX 8u
#define LATTICRA_KERNEL_TIME_ACCOUNTING_REPORT_MAX 32768u

typedef struct {
    latticra_kernel_context_switch_request_t context_switch_request;
    size_t requested_account_count;
} latticra_kernel_time_accounting_request_t;

typedef struct {
    size_t account_index;
    unsigned long account_token;
    unsigned long pid_token;
    unsigned long switch_token;
    unsigned long tick_token;
    unsigned long charged_budget_ns;
    unsigned long consumed_ns;
    char process_label[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    char accounting_class[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    char accounting_status[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    int declared;
    int sampled;
    int charged;
    int persisted;
    int time_accounting_allowed;
    int time_read_allowed;
    int cpu_usage_write_allowed;
    int quota_update_allowed;
    int scheduler_credit_update_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int preemption_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_time_accounting_entry_t;

typedef struct {
    latticra_status_t status;
    char accounting_status[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_TIME_ACCOUNTING_LABEL_MAX];
    latticra_kernel_context_switch_result_t context_switch;
    latticra_kernel_time_accounting_entry_t accounts[
        LATTICRA_KERNEL_TIME_ACCOUNTING_MAX];
    size_t account_count;
    int no_effect;
    int time_accounting_allowed;
    int time_read_allowed;
    int cpu_usage_write_allowed;
    int quota_update_allowed;
    int scheduler_credit_update_allowed;
    int context_switch_allowed;
    int run_queue_mutation_allowed;
    int preemption_allowed;
    int process_wake_allowed;
    int hardware_effect_allowed;
    int host_effect_allowed;
    unsigned int evidence_level;
} latticra_kernel_time_accounting_result_t;

latticra_status_t latticra_kernel_time_accounting_default_request(
    latticra_kernel_time_accounting_request_t *request);

latticra_status_t latticra_kernel_time_accounting_evaluate(
    const latticra_kernel_time_accounting_request_t *request,
    latticra_kernel_time_accounting_result_t *result);

latticra_status_t latticra_kernel_time_accounting_report(
    const latticra_kernel_time_accounting_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
