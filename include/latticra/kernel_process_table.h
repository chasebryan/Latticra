#ifndef LATTICRA_KERNEL_PROCESS_TABLE_H
#define LATTICRA_KERNEL_PROCESS_TABLE_H

#include "latticra/kernel_memory_map.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX 64u
#define LATTICRA_KERNEL_PROCESS_TABLE_PROCESS_MAX 8u
#define LATTICRA_KERNEL_PROCESS_TABLE_REPORT_MAX 24576u

typedef struct {
    latticra_kernel_memory_map_request_t memory_map_request;
    size_t requested_process_count;
} latticra_kernel_process_table_request_t;

typedef struct {
    size_t process_index;
    unsigned long pid_token;
    char label[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    char lifecycle_status[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    char authority_status[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    char scheduler_slot_label[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    char memory_region_label[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    int declared;
    int runnable;
    int scheduled;
    int spawned;
    int no_effect;
    unsigned int evidence_level;
} latticra_kernel_process_table_entry_t;

typedef struct {
    latticra_status_t status;
    char table_status[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    char policy_status[LATTICRA_KERNEL_PROCESS_TABLE_LABEL_MAX];
    latticra_kernel_memory_map_result_t memory_map;
    latticra_kernel_process_table_entry_t processes[
        LATTICRA_KERNEL_PROCESS_TABLE_PROCESS_MAX];
    size_t process_count;
    int no_effect;
    int process_spawn_allowed;
    int context_switch_allowed;
    int signal_delivery_allowed;
    int address_space_mutation_allowed;
    unsigned int evidence_level;
} latticra_kernel_process_table_result_t;

latticra_status_t latticra_kernel_process_table_default_request(
    latticra_kernel_process_table_request_t *request);

latticra_status_t latticra_kernel_process_table_evaluate(
    const latticra_kernel_process_table_request_t *request,
    latticra_kernel_process_table_result_t *result);

latticra_status_t latticra_kernel_process_table_report(
    const latticra_kernel_process_table_result_t *result,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
